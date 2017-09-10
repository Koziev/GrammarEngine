// -----------------------------------------------------------------------------
// File SYLLAB_STATISTICS.CPP
//
// (c) Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project
// EMPIR program
//
// Syllabs processor - part of EMPIR code.
// -----------------------------------------------------------------------------
//
// CD->04.09.2002
// LC->10.01.2012
// --------------

#if defined EMPIR_SYLLAB

#include <lem/quantors.h>
#include <lem/conversions.h>
#include <lem/unicode.h>

#include <algorithm>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntryEnumerator.h>

#include "empir.h"

using namespace std;

SyllabProcessor::SyllabProcessor(void)
{
 words_count=0;
 id_language=UNKNOWN;
}

// *********************************************************************
// Распечатка списка слогов с частотами в текстовый поток - обычно этот
// файл потом используется для отображения гистограмм.
// *********************************************************************
void SyllabProcessor::Dump_Syllabs( OFormatter &out, const ws_list &slb ) const
{
 for( lem::Container::size_type i=0; i<slb.size(); i++ )
  out.printf( "%d;%us;%d\n", i, slb[i].first.c_str(), slb[i].second );

 return;
}


// ****************************************************
// Слово поступило на обработку.
// ****************************************************
void SyllabProcessor::Add( const UCString &l, int word_freq )
{
 if(
    lem::is_int(l.c_str()) ||
    lem::is_upunct(l.front()) ||
    lem::is_udigit(l.front()) ||
    l.front()==L'_'
   )
  // цифры и знаки препинания исключаем
  return;
  
 #if !defined SOL_NO_AA
 words_count++; // Подсчет слов, поступивших на обработку

 const int len = l.length();

 // Вырезаем окончания: 2, 3х-буквенные
 const UCString e2 = lem::right( l, 2 );
 const UCString e3 = lem::right( l, 3 );

 if( e2.length()==2 ) process_ending_2( e2, word_freq );
 if( e3.length()==3 ) process_ending_3( e3, word_freq );

 // Вырезаем всевозможные сочетания букв по 2 ...
 for( int j2=0; j2<len-2; j2++ )
  process_syllab_2( mid( l, j2, 2 ), word_freq );

 // ... и по 3 символа
 for( int j3=0; j3<len-3; j3++ )
  process_syllab_3( mid( l, j3, 3 ), word_freq );

 MCollect<UCString> slb_list;

 // Start the SOLARIX syllab-broker. It returns the list of syllabs
 // using big set of rules.
 sol_id->GetGraphGram().FindSyllabs( l, id_language, false, slb_list, NULL );

 for( lem::Container::size_type islb=0; islb<slb_list.size(); islb++ )
  {
   process_real_mid( slb_list[islb], word_freq );

   // Last syllab (excluding END). For one-syllab words nothing is done.
   if( slb_list.size()>1 && islb==slb_list.size()-1 )
    process_real_end( slb_list[islb], word_freq );

   // First syllab (excluding BEG). For one-syllab words nothing is done.
   if( slb_list.size()>1 && !islb )
    process_real_org( slb_list[islb], word_freq );
  }
 #endif

 return;
}


// ******************************************************************
// Stores the real syllab 'e' with frequency of word 'word_freq'
// ******************************************************************
void SyllabProcessor::process_real_mid( const UCString &e, int word_freq )
{
 if( is_upunct(e.front()) || is_udigit(e.front()) )
  // Delimiters are not syllabs.
  return;

 int ifound=UNKNOWN;
 for( lem::Container::size_type j=0; j<real_mid_slb.size(); j++ )
  if( real_mid_slb[j].first==e )
   {
    real_mid_slb[ifound=j].second+=word_freq;
    break;
   }

 if( ifound==UNKNOWN )
  real_mid_slb.push_back( make_pair( e, word_freq ) );

 return;
}



void SyllabProcessor::process_real_end(
                                       const UCString &e,
                                       int word_freq
                                      )
{
 if( is_upunct(e.front()) || is_udigit(e.front()) )
  // Delimiters are not syllabs.
  return;

 int ifound=UNKNOWN;
 for( lem::Container::size_type j=0; j<real_end_slb.size(); j++ )
  if( real_end_slb[j].first==e )
   {
    real_end_slb[ifound=j].second+=word_freq;
    break;
   }

 if( ifound==UNKNOWN )
  real_end_slb.push_back( make_pair( e, word_freq ) );

 return;
}


void SyllabProcessor::process_real_org(
                                       const UCString &e,
                                       int word_freq
                                      )
{
 if( is_upunct(e.front()) || is_udigit(e.front()) )
  // Delimiters are not syllabs.
  return;

 int ifound=UNKNOWN;
 for( lem::Container::size_type j=0; j<real_org_slb.size(); j++ )
  if( real_org_slb[j].first==e )
   {
    real_org_slb[ifound=j].second+=word_freq;
    break;
   }

 if( ifound==UNKNOWN )
  real_org_slb.push_back( make_pair( e, word_freq ) );

 return;
}


// *********************************************************
// Учет очередного окончания.
// *********************************************************
void SyllabProcessor::process_ending_2( const UCString &e, int word_freq )
{
 if( e.length()!=2 )
  return;

 int ifound=UNKNOWN;
 for( lem::Container::size_type j=0; j<endings_2.size(); j++ )
  if( endings_2[j].first==e )
   {
    endings_2[ifound=j].second+=word_freq;
    break;
   }

 if( ifound==UNKNOWN )
  endings_2.push_back( make_pair( e, word_freq ) );

 process_syllab_2(e,word_freq);

 return;
}


void SyllabProcessor::process_ending_3( const UCString &e, int word_freq )
{
 if( e.length()!=3 )
  return;

 int ifound=UNKNOWN;
 for( lem::Container::size_type j=0; j<endings_3.size(); j++ )
  if( endings_3[j].first==e )
   {
    endings_3[ifound=j].second+=word_freq;
    break;
   }

 if( ifound==UNKNOWN )
  endings_3.push_back( make_pair( e, word_freq ) );

 process_syllab_3(e,word_freq);

 return;
}


// *********************************************************
// Обработка выделенного слога.
// *********************************************************
void SyllabProcessor::process_syllab_2( const UCString &e, int word_freq )
{
 if( e.length()!=2 )
  return;

 int ifound=UNKNOWN;
 for( lem::Container::size_type j=0; j<syllabs_2.size(); j++ )
  if( syllabs_2[j].first==e )
   {
    syllabs_2[ifound=j].second+=word_freq;
    break;
   }

 if( ifound==UNKNOWN )
  syllabs_2.push_back( make_pair( e, word_freq ) );

 return;
}


void SyllabProcessor::process_syllab_3( const UCString &e, int word_freq )
{
 if( e.length()!=3 )
  return;

 int ifound=UNKNOWN;
 for( lem::Container::size_type j=0; j<syllabs_3.size(); j++ )
  if( syllabs_3[j].first==e )
   {
    syllabs_3[ifound=j].second+=word_freq;
    break;
   }

 if( ifound==UNKNOWN )
  syllabs_3.push_back( make_pair( e, word_freq ) );

 return;
}



void SyllabProcessor::Post_Process( const WordProcessor &words )
{
 #if !defined SOL_NO_AA

 const int n_syllabs = real_end_slb.size() +real_org_slb.size() + real_mid_slb.size() +
                       syllabs_2.size() + syllabs_3.size();
                 

 mout->printf( "Post processing %vfE%d%vn syllabs: ", n_syllabs );

 // We take a lot of preparations because of extremely 'heavy' loop that
 // makes the main work: about 1,000,000 passes of external loop and some 10,000
 // for inner one, total 1e11 passes!!!


 // All string hash range is divided onto many subranges. Syllabs are
 // spread (by way of index lists) over this subranges.
 const int N_HASH_CLASS = 256;

 typedef MCollect< pair<int,UINT8> > I2_Array;

 I2_Array s_group[N_HASH_CLASS+1];

 // Fill the groups.
 const int HashClass = lem_get_hash_subrange(N_HASH_CLASS);
 MCollect< UCString > u_slb;
 u_slb.reserve( real_end_slb.size() );

 for( lem::Container::size_type is=0; is<real_end_slb.size(); is++ )
  {
   u_slb.push_back( real_end_slb[is].first );

   // Get the index of list form this has code.
   const int i_group = u_slb.back().GetHash() / HashClass;
   s_group[i_group].push_back( make_pair( is, u_slb.back().GetHash() ) );
  }

// int max_hashed=0, min_hashed=MAXINT, count=0;
// MPairSorter<int,UINT8> sorter;
 for( int i=0; i<N_HASH_CLASS; i++ )
  {
   // Sort up the indeces, ordering them ascending manner.
   sort_asc_pairs( s_group[i] );
  }

 // Groups are made ready.

 // Search the correspondence between ending syllabs and grammatic attributes.

 // Allocate the room...
 real_ctx.reserve( real_end_slb.size() );

 for( lem::Container::size_type ia=0; ia<real_end_slb.size(); ia++ )
  real_ctx.push_back(
                     new Syllab_Ctx(
                                    real_end_slb[ia].first,
                                    real_end_slb[ia].second
                                   )
                    );

 // Number of entries in lexicon.
 const int nEntry = sol_id->GetSynGram().GetnEntry();

 int nlast=16;
 const int nperc = nEntry/nlast;

 int ecount=0;
 
 lem::Ptr<Solarix::WordEntryEnumerator> entries( sol_id->GetSynGram().GetEntries().ListEntries() );

 while( entries->Fetch() )
  {
   const int ientry = entries->GetId();
   const SG_Entry &e = entries->GetItem();

   if( !(ecount++%nperc) )
    {
     // Progress bar - print decreasing numbers.
     mout->printf( "%d.", nlast-- );
     mout->flush();
    }

   const int iclass = e.GetClass();

   // For each form of the entry
   for( lem::Container::size_type iform=0; iform<e.forms().size(); iform++ )
    {
     const SG_EntryForm &form = e.forms()[iform];
     const CP_Array dims = form.coords();
     const UCString& last = form.name();

     const int word_freq = words.GetWordFrequency(last);

     if( word_freq==0 )
      continue;

     // Get the list of syllabs for this wordform...
     MCollect<UCString> slb_list;
     sol_id->GetGraphGram().FindSyllabs( last, id_language, false, slb_list, NULL );

     if( slb_list.size()<2 ) // если 1 слог, то не будем использовать для распознавания
      continue;

     // Take pre-last item (last one is special syllab 'END').
     const UCString &end_syllab = slb_list.back();

#if LEM_DEBUGGING==1
//if( end_syllab==L"А" )
 //lem::mout->printf( "%us\n", last.c_str() );
#endif

     const lem::uint8_t Hash = end_syllab.GetHash();
     const I2_Array &grp = s_group[ Hash / HashClass ];

     // Now loop thru the list of syllabs and process the matching ones.
     for( lem::Container::size_type islb1=0; islb1<grp.size(); islb1++ )
      {
       if( grp[islb1].second > Hash )
        // There is no reason to continue, as the list is ordered ascending...
        break;

       if( u_slb[ grp[islb1].first ] == end_syllab )
        real_ctx[ grp[islb1].first ]->Add( iclass, dims, word_freq );
      }
    }
  }

 mout->printf( "%vfAOK%vn\n" );
 #endif

 return;
}

lem::Path SyllabProcessor::GetOutPath( const wchar_t *filename ) const
{
 lem::Path p(outdir);
 p.ConcateLeaf(filename);
 return p;
}


// *******************************************************
// Подготовка и сохранение результатов обработки.
// *******************************************************
void SyllabProcessor::Report(
                             OFormatter &rep,
                             const CharProcessor &CH
                            ) const
{
 // Сколько слогов по 2 и по 3 буквы
 const int ns2=syllabs_2.size();
 const int ns3=syllabs_3.size();

 const int ns = ns2+ns3; // Всего слогов
 const int ne = endings_2.size()+endings_3.size(); // Всего окончаний

 // Теоретическое число слогов
 const int NCHAR = CH.Total_Chars();
 const int mns2 = NCHAR * NCHAR;
 const int mns3 = mns2 * NCHAR;

 rep.printf(
            "          --- SYLLABS ---\n"
            "Number of accumulated syllabs      = %d\n"
            "..................... 2 chars      = %d (of %d possible)\n"
            "..................... 3 chars      = %d (of %d possible)\n"
            "Number of accumulated endings      = %d\n\n"
            "Number of accumulated real syllabs = %d\n"
            , ns, ns2, mns2, ns3, mns3, ne
            , real_mid_slb.size()
           );


 mout->printf( "Sorting syllabs..." );
 mout->flush();

 // ********************************************************************
 // Сортируем список слогов. Используется сортер для шаблона pair
 // ********************************************************************
 sort_desc_pairs( (MCollect<pair<UCString,int> >&)syllabs_2 );
 sort_desc_pairs( (MCollect<pair<UCString,int> >&)syllabs_3 );

 sort_desc_pairs( (MCollect<pair<UCString,int> >&)endings_2 );
 sort_desc_pairs( (MCollect<pair<UCString,int> >&)endings_3 );

 sort_desc_pairs( (MCollect<pair<UCString,int> >&)real_mid_slb );
 sort_desc_pairs( (MCollect<pair<UCString,int> >&)real_org_slb );
 sort_desc_pairs( (MCollect<pair<UCString,int> >&)real_end_slb );

 mout->printf( "done\n" );

 mout->printf( "Storing the syllabs lists..." );
 mout->flush();

 // *******************************************************
 // Stores the real syllabs in binary file for later use.
 // *******************************************************
 BinaryFile bin( GetOutPath(L"syllabs.bin"), false, true );

// syllabs_2.SaveBin(bin);
// syllabs_3.SaveBin(bin);
// endings_2.SaveBin(bin);
// endings_3.SaveBin(bin);

 real_mid_slb.SaveBin(bin);
 real_end_slb.SaveBin(bin);

 {
  OUFormatter txt_2( GetOutPath(L"2chars.csv") );
  Dump_Syllabs( txt_2, syllabs_2 );
  txt_2.GetStream()->close();

  OUFormatter txt_3( GetOutPath(L"3chars.csv") );
  Dump_Syllabs( txt_3, syllabs_3 );
  txt_3.GetStream()->close();

  OUFormatter txt4( GetOutPath(L"real_org_slb.csv") );
  Dump_Syllabs( txt4, real_org_slb );
  txt4.GetStream()->close();

  OUFormatter txt5( GetOutPath(L"real_mid_slb.csv") );
  Dump_Syllabs( txt5, real_mid_slb );
  txt5.GetStream()->close();

  OUFormatter txt6( GetOutPath(L"real_end_slb.csv") );
  Dump_Syllabs( txt6, real_end_slb );
  txt6.GetStream()->close();
 }

 mout->printf( "%vfAOK%vn\n" );
 mout->printf( "List out the syllabs..." ); mout->flush();

 OUFormatter txt1( GetOutPath(L"gg_mid.sol") );

 txt1.printf(
             "// Generated by EMPIR program [%us]\n\n"
	         "automat gg\n"
	         "{\n"
	         " array MID_GROUPS = {\n"
             , lem::timestamp().c_str()
            );

 for( lem::Container::size_type j2=0; j2<syllabs_2.size(); j2++ )
  {
   // Ценность данного слога - отношение его частоты к сумме частот символов
   txt1.printf(
               "  { \"%us\", %W5d, %7.5f },\n"
               , syllabs_2[j2].first.c_str()
               , syllabs_2[j2].second
               , CH.Calc_Val( syllabs_2[j2].first, syllabs_2[j2].second )
              );
  }

 for( lem::Container::size_type j3=0; j3<syllabs_3.size(); j3++ )
  {
   double v = CH.Calc_Val( syllabs_3[j3].first, syllabs_3[j3].second );
   txt1.printf(
               "  { \"%us\", %W5d, %7.5f },\n"
               , syllabs_3[j3].first.c_str()
               , syllabs_3[j3].second
               , v
              );
  }


 txt1.printf( "   }\n }\n" );

 txt1.GetStream()->close();


 OUFormatter txt2( GetOutPath(L"endings.csv") );
 for( lem::Container::size_type k2=0; k2<endings_2.size(); k2++ )
  {
   txt2.printf( "%W10us;%d\n", endings_2[k2].first.c_str(), endings_2[k2].second );
  }

 for( lem::Container::size_type k3=0; k3<endings_3.size(); k3++ )
  {
   txt2.printf( "%W10us;%d\n", endings_3[k3].first.c_str(), endings_3[k3].second );
  }

 txt2.GetStream()->close();

 // ***************************************************
 // List the real syllabs to the file which will be
 // consumed by Solarix compiler YGRES.
 // ***************************************************
 OFormatter txt3( GetOutPath(L"gg_slb.sol") );
 txt3.printf(
             "// This file is created [%us] by CHARS program.\n"
             "// It contains the list of syllabs and their frequencies.\n\n"
             "\n\n"
             "// Valid formats are:\n"
             "//         1. syllab SSS = { Nbeg Nmid Nend }\n"
             "//         2. syllab SSS = Ntot\n\n"
             "automat gg\n"
             "{\n\n"
             , lem::timestamp().c_str()
            );

 for( lem::Container::size_type k3=0; k3<real_mid_slb.size(); k3++ )
  {
   int Nbeg=0, Nend=0, Nmid=real_mid_slb[k3].second;

   for( lem::Container::size_type i=0; i<real_org_slb.size(); i++ )
    if( real_org_slb[i].first == real_mid_slb[k3].first )
     {
      Nbeg = real_org_slb[i].second;
      break;
     }

   for( lem::Container::size_type i=0; i<real_end_slb.size(); i++ )
    if( real_end_slb[i].first == real_mid_slb[k3].first )
     {
      Nend = real_end_slb[i].second;
      break;
     }

   Nmid = Nmid - Nbeg - Nend;

   txt3.printf(
               " syllab %W10us = { %W10d %W10d %W10d }\n"
               , real_mid_slb[k3].first.c_str()
               , Nbeg, Nmid, Nend
              );
  }

 txt3.printf( "\n}\n" );
 txt3.GetStream()->close();

 mout->printf( "%vfAOK%vn\n" );
 mout->printf( "List out the syllabic recognition rules..." ); mout->flush();

 OUFormatter txt4( GetOutPath(L"sg_slb.sol") );

 SynGram &sg = sol_id->GetSynGram();

 txt4.printf(
             "// This file is created [%us] by EMPIRIKA program.\n"
             "// (c) by Elijah Koziev www.solarix.ru, 2011\n"
             "// It contains the list of syllabs guess rules.\n\n"
             "// Source data: %d words.\n"
             "// Dictionary:  %d word entries.\n\n"
             "automat la\n"
             "{\n\n"
             , timestamp().c_str()
             , words_count
             , sg.GetnEntry()
            );

 int counter=0; // Number of listed rules...
 for( lem::Container::size_type k4=0; k4<real_ctx.size(); k4++ )
  if( real_ctx[k4]->gram_contx.size() )
   {
    // Sort contexts by frequency, so the first in listing is most frequent.
    int norm=0;
    MCollect< pair<int,int> > sorted; sorted.reserve(64);
    for( lem::Container::size_type i=0; i<real_ctx[k4]->gram_contx.size(); i++ )
     {
      sorted.push_back( make_pair( i, real_ctx[k4]->gram_contx[i].second ) );
      norm = std::max( norm, real_ctx[k4]->gram_contx[i].second );
     }

    if( norm==0 )
     norm=1;

    sort_desc_pairs( sorted );

    for( lem::Container::size_type j=0; j<real_ctx[k4]->gram_contx.size(); j++ )
     {
      const pair<SG_CoordContext,int> &coords = real_ctx[k4]->gram_contx[ sorted[j].first ];

      int rel = 100*(0.9*double(coords.second)/double(norm));

      if( rel==0 )
       {
        txt4.printf( "// " );
       }
      else 
       {
        counter++;
       }

      txt4.printf( " recognition \"%us_%d\" language=Russian { ", real_ctx[k4]->syllab.c_str(), CastSizeToInt(j) );
      txt4.printf( "if syllab \"(.+)%us\" then ", real_ctx[k4]->syllab.c_str() );
      coords.first.SaveTxt( txt4, sg );
      txt4.printf( " = %d }\n\n", rel );
     }
   }

 txt4.printf( "// %d rules has been created\n}\n", counter );

 txt4.GetStream()->close();

 mout->printf( "%vfE%d%vn rules %vfAOK%vn\n", counter );

 return;
}



void Syllab_Ctx::Add( int iClass, const CP_Array& Dims, int Freq )
{
 bool found=false;

 for( lem::Container::size_type ii=0; ii<gram_contx.size(); ii++ )
  if(
     gram_contx[ii].first.iclass == iClass
     &&
     gram_contx[ii].first.coords == Dims
    )
   {
    gram_contx[ii].second+=Freq;
    found=true;
    break;
   }

 if( !found )
  {
   const SG_CoordContext cc( iClass, Dims );
   gram_contx.push_back( make_pair( cc, Freq ) );
  }

 return;
}

#endif
