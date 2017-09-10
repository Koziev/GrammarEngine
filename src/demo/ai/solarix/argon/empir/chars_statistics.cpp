// -----------------------------------------------------------------------------
// File CHARS_STATISTICS.CPP
//
// (c) Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project
// EMPIR program
//
// Модуль накопления статистики по символам.
// Chars processor - accumulate statistics for chars without their neighbours.
//
// 25.02.2008 - исправлена ошибка с выводом имен символов в файлах результатов.
//
// 29.02.2008 - из статистики по буквам исключены цифры и знаки препинания
// -----------------------------------------------------------------------------
//
// CD->04.09.2002
// LC->11.06.2011
// --------------

#include <lem/conversions.h>
#include <lem/date_time.h>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/SymbolEnumerator.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/ClassEnumerator.h>

#include "empir.h"

CharProcessor::CharProcessor(void)
{
 nchar = n_lim = 0;
 return;
}


void CharProcessor::SetSol( Dictionary* SolId )
{
 sol_id=SolId;

 // Сформируем список всех символов из всех объявленных в словаре алфавитов,
 // без повторов (латиница используется во многих алфавитах).
 const GraphGram &gg = sol_id->GetGraphGram();
 unique_chars=0;

 lem::Ptr<SymbolEnumerator> senum( gg.entries().Enumerate() );

 while( senum->Fetch() )
  {
   const GG_Entry &e = senum->GetItem();

   if( e.forms().empty() )
    {
     // Для цифр, у которых формы могут быть не объявлены.
     const wchar_t c = e.GetName();
     std::map<wchar_t,int>::const_iterator wh = chars.find(c);

     if( wh == chars.end() )
      {
       chars.insert( std::make_pair( c, unique_chars++ ) );
       char_names.push_back(c);
      } 
    }
   else
    {
     for( lem::Container::size_type j=0; j<e.forms().size(); j++ )
      {
       const wchar_t c = e.forms()[j].GetName();
       std::map<wchar_t,int>::const_iterator wh = chars.find(c);

       if( wh == chars.end() )
        {
         chars.insert( std::make_pair( c, unique_chars++ ) );
         char_names.push_back(c);
        }
      }
    } 
  }

 // Установка размеров и обнуление частотных таблиц.
 ch_freq.resize(unique_chars);  std::fill( ch_freq.begin(),  ch_freq.end(),  0 );
 org_freq.resize(unique_chars); std::fill( org_freq.begin(), org_freq.end(), 0 );
 end_freq.resize(unique_chars); std::fill( end_freq.begin(), end_freq.end(), 0 );

 return;
}


void CharProcessor::Add( const UCString &Word, lem::int64_t word_freq )
{
 // Отдельно (дополнительно) обрабатывается первый и последний символ слова,
 // если слово длиннее 1 символов
 if( Word.length()>1 )
  {
   n_lim+=word_freq;

   const wchar_t c1 = Word.front();
   if( !lem::is_udigit(c1) && !lem::is_upunct(c1) )
    org_freq[ get_ichar(c1) ]+=word_freq;

   const wchar_t c2 = Word.back();
   if( !lem::is_udigit(c2) && !lem::is_upunct(c2) )
    end_freq[ get_ichar(c2) ]+=word_freq;
  }

 // Обработка всех символов слова
 for( int i=0; i<Word.length(); i++ )
  {
   const wchar_t c = Word[i];
   if( !lem::is_udigit(c) && !lem::is_upunct(c) )
    {
     // ******************************************************************
     // Статистическая регистрация единичного символа ch в составе слова.
     // ******************************************************************
     nchar+=word_freq;
     const int ich = get_ichar(c);

     if( ich!=UNKNOWN )
      ch_freq[ich]+=word_freq;
    }
  }

 return;
}



// ***********************************************************
// Формирование отчета по накопленной статистике - для БУКВ
// ***********************************************************
void CharProcessor::Report( OFormatter &rep ) const
{
 rep.printf(
            " --- Chars statistics ---\n"
            "Total # of chars processed         = %qd\n\n"
            "Total # of border chars processed  = %qd\n\n"
            , nchar, n_lim
           );

 MCollect< std::pair<wchar_t,lem::int64_t> > chs, org_ch, end_ch;

 // Так как векторы будут перемешаны, то сохраним их
 for( lem::Container::size_type j0=0; j0<char_names.size(); j0++ )
  {
   chs.push_back( std::make_pair( char_names[j0], ch_freq[j0] ) );
   org_ch.push_back( std::make_pair( char_names[j0], org_freq[j0] ) );
   end_ch.push_back( std::make_pair( char_names[j0], end_freq[j0] ) );
  }

 sort_desc_pairs( chs );
 sort_desc_pairs( org_ch );
 sort_desc_pairs( end_ch );

 RArray A_ch, W_ch;

 // **************************************************
 // Распечатываем частоты символов
 // **************************************************

 // Частоты для начальных символов
 rep.printf( "\n\nMost frequently used beginning chars ('ch_org.csv'):\n" );
 OUFormatter txt1( GetOutPath(L"ch_org.csv") );
 for( lem::Container::size_type j1=0; j1<org_ch.size(); j1++ )
  {
   const lem::int64_t freq = org_ch[j1].second;
   const wchar_t c = org_ch[j1].first;

   if( !freq )
    break;

   rep.printf(
              "%W3d    %W3d '%uc' %W10qd (%4.1rf%%)\n"
              , j1
              , c
              , c
              , freq
              , (100.*freq)/double(n_lim)
             );

   txt1.printf( "%d;%qd;%uc\n", j1, freq, c );
  }

 txt1.GetStream()->close();


 // Частоты для символов безотносительно их положения
 rep.printf( "\n\nFrequencies of chars regardless of their position ('ch_tot.csv'):\n" );
 OUFormatter txt2( GetOutPath(L"ch_tot.csv") );
 for( lem::Container::size_type j3=0; j3<chs.size(); j3++ )
  {
   const lem::int64_t freq = chs[j3].second;
   const wchar_t c = chs[j3].first;

   if( !freq )
    break;

   rep.printf(
              "%W3d  %W3d '%uc' %W10qd (%4.1rf%%)\n"
              , j3
              , c
              , c
              , freq
              , 100.*double(freq)/double(nchar)
             );

   txt2.printf( "%d;%qd;%uc\n", j3, freq, c );
  }

 txt2.GetStream()->close();

 // Частоты для конечных символов
 rep.printf( "\n\nMost frequently used ending chars ('ch_ends.csv'):\n" );
 OUFormatter txt3( GetOutPath(L"ch_end.csv") );
 for( lem::Container::size_type j2=0; j2<end_ch.size(); j2++ )
  {
   const lem::int64_t freq = end_ch[j2].second;
   const wchar_t c = end_ch[j2].first;

   if( !freq )
    break;

   rep.printf(
             "%W3d   %W2d '%uc' %W10qd (%4.1rf%%)\n"
             , j2
             , c
             , c
             , freq
             , 100.*double(freq)/double(n_lim)
            );

   txt3.printf( "%d;%qd;%uc\n", j2, freq, c );
  }

 txt3.GetStream()->close();


 // Формирование калибровочного файла - для чтения транслятором YGRES.
 OUFormatter gg_calibr( GetOutPath(L"gg_chars.sol") );
 OUFormatter ch_mixage( GetOutPath(L"ch_mix.csv") );

 gg_calibr.printf(
                  "// This file is created [%us] by CHARS program.\n"
                  "// It contains the list of syllabs and their frequencies for\n"
                  "// beginning (Nbeg), ending (Nend) and middle (Nmid) of the words.\n"
                  "// Statistics: %qd chars processed.\n\n"
                  "// Valid formats are:\n"
                  "//         1. char C = { Nbeg Nmid Nend }\n"
                  "//         2. char C = Ntot\n\n"
                  "automat gg\n"
                  "{\n\n"
                  , lem::timestamp().c_str()
                  , nchar
                 );

 // ***********************************************************************
 // generic format for char calibrator is:
 //
 //       1.   char C = N
 //       2.   char C = { Nbeg Nmid Nend }
 //
 // where N is total frequency, Nbeg - frequency for beginning char,
 // Nmid - freq for middle (not bound) char, Nend - freq for ending char.
 //
 // ***********************************************************************
 for( lem::Container::size_type ich=0; ich<chars.size(); ich++ )
  {
   lem::int64_t Nbeg=0, Nend=0, Nmid=0, Ntot=chs[ich].second;

   for( lem::Container::size_type k=0; k<org_ch.size(); k++ )
    if( org_ch[k].first == chs[ich].first )
     {
      Nbeg = org_ch[k].second;
      break;
     }

   for( lem::Container::size_type k=0; k<end_ch.size(); k++ )
    if( end_ch[k].first == chs[ich].first )
     {
      Nend = end_ch[k].second;
      break;
     }

   Nmid = Ntot - Nbeg - Nend;

   if( Nbeg || Nmid || Nend )
    {
     if(
        chs[ich].first==L'\'' ||
        chs[ich].first==L'"'  ||
        chs[ich].first==L'\\'
       )
      {
       gg_calibr.printf( " char '\\%uc' =", chs[ich].first );
       gg_calibr.printf( " { %W10qd %W10qd %W10qd }\n", Nbeg, Nmid, Nend );
      }
     else
      {
       if( is_ulitera( chs[ich].first ) || is_upunct( chs[ich].first ) )
        {
         gg_calibr.printf( " char '%uc' =", chs[ich].first );
         gg_calibr.printf( " { %W10qd %W10qd %W10qd }\n", Nbeg, Nmid, Nend );
        }
      }

     if( is_ulitera( chs[ich].first ) || is_upunct( chs[ich].first ) )
      ch_mixage.printf(
                       "%uc;%qd;%qd;%qd\n"
                       , chs[ich].first
                       , Nbeg
                       , Nmid
                       , Nend
                      );
    }
  }

 gg_calibr.printf( "\n}\n" );


 // Frequencies of char classes

 GraphGram &gg = sol_id->GetGraphGram();

 lem::Ptr<Solarix::ClassEnumerator> cenum( gg.classes().Enumerate() );
 int max_id_class=0;
 while( cenum->Fetch() )
  max_id_class = std::max( max_id_class, cenum->GetId() );

 lem::MCollect<lem::int64_t> class_freq(max_id_class+1);
 class_freq.Nullify();

 for( lem::Container::size_type i=0; i<chars.size(); i++ )
  {
   const int ientry = gg.FindSymbol( chs[i].first ).GetEntry();
   if( ientry!=UNKNOWN )
    {
     const int id_class = gg.entries()[ ientry ].GetClass();
     class_freq[ id_class ] += chs[i].second;
    }
  }

 OUFormatter gc( GetOutPath(L"ch_class.csv") );
 lem::Ptr<Solarix::ClassEnumerator> cenum2( gg.classes().Enumerate() );
 while( cenum2->Fetch() )
  {
   gc.printf( "%us;%qd\n", cenum2->GetItem().GetName().c_str(), class_freq[cenum2->GetId()] );
  }

 return;
}



double CharProcessor::Calc_Val( const UCString &s, lem::int64_t wFreq ) const
{
 lem::int64_t S_freq=0;
 for( int i=0; i<s.length(); i++ )
  {
   int ix = get_ichar(s[i]);
   if( ix!=UNKNOWN )
    S_freq += ch_freq[ ix ];
  }

 return S_freq ? (double( wFreq ) / double(S_freq)) : 0;
}

lem::Path CharProcessor::GetOutPath( const wchar_t *filename ) const
{
 lem::Path p(outdir);
 p.ConcateLeaf(filename);
 return p;
}
