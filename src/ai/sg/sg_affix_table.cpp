// -----------------------------------------------------------------------------
// File SG_AFFIX_TABLE.CPP
//
// (c) by Elijah Koziev
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Affix_Table - класс для генерации возможных корней по полным формам и 
// заранее приготовленному списку аффиксов.
// 23.01.2013 - закрытые части речи не участвуют в генерации правил распознавания.
// -----------------------------------------------------------------------------
//
// CD->06.08.2005
// LC->23.01.2013
// --------------

#include <lem/solarix/la_autom.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/PartsOfSpeech.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/SG_Affixtable.h>
#include <lem/console_streams.h>

using namespace std;
using namespace lem;
using namespace Solarix;

Affix_Table::Affix_Table(void)
{
}


#if defined SOL_LOADTXT
// **************************************************************************
// Конструктор строит таблицу по информации в SynGrammar. Обычно вызывается
// после компиляции словаря для подготовки всех двоичных файлов словаря.
// **************************************************************************
Affix_Table::Affix_Table( SynGram &sg )
{
 rules.reserve(4096);

 for( int i=0; i<NLIST; i++ )
  {
   list[i].reserve(256);
   base_afx_list1[i].reserve(256);
  }

 // Строим таблицу аффиксов для языков
 // Для этого просматриваем все словарные статьи.
 lem::Ptr<WordEntryEnumerator> wenum( sg.GetEntries().ListEntries() );
 while( wenum->Fetch() )
  {
   const SG_Entry &e = wenum->GetItem();

//printf( "ientry=%d e=%x\n", ientry, sg.entries()[ientry] );

   const UCString& eroot = e.GetRoot();

   if( eroot.length()<2 )
    continue;

   // Многолексемные статьи (типа английских фразовых глаголов) не участвуют
   // в генерации аффиксов.
   if( e.GetName().Count_Lexems()>1 )
    continue;

   const int id_class = e.GetClass();

   // Часть речи может быть помечена как неучаствующая в генерации правил распознавания.
   if( sg.GetClass( id_class ).IsClosed() )
    continue;

   int id_language=UNKNOWN;
   if( !lem::is_quantor(id_class) )
    {
     const SG_Class &cls = static_cast<const SG_Class&>( sg.classes()[id_class] );
     id_language = cls.GetLanguage();
    }

   if( e.GetName().length() <= eroot.length() )
    {
     // Такое может быть для некоторых слов с нетипичной парадигмой, 
     // когда для статьи (ПОЛУЧАС) определены не все словоформы из
     // возможных (ПОЛУЧАСА и ПОЛУЧАСОМ).
     continue;
    } 

   // Аффикс для приведения к базовой форме.
   const UCString base_afx = right( e.GetName(), e.GetName().length() - eroot.length() ); 

   for( Container::size_type iform=0; iform<e.forms().size(); iform++ )
    {
     const Lexem& name = e.forms()[iform].name();

     if( name.Count_Lexems()>1 )
      continue;

     if( name.length() > eroot.length() )
      {
       // Выделяем аффикс.   
       UCString afx = right( name, name.length() - eroot.length() );

       // Запоминаем этот аффикс.
       StoreAffix( afx, base_afx, id_language );
//out.printf( "%W20us: root=%W20us afx=%W8us base_afx=%W8us\n", name.c_str(), eroot.c_str(), afx.c_str(), base_afx.c_str() );
      }
    }
  }

 #if defined SOL_LOADTXT && defined SOL_COMPILER
 GenerateDynformsRules();
 #endif

 return;
}
#endif


#if defined SOL_LOADTXT
void Affix_Table::StoreAffix(
                             const UCString &afx,
                             const UCString &base_afx,
                             int id_language
                            )
{
 LEM_CHECKIT_Z( !afx.empty() );
 const int ilist = afx.length()-1;

 if( ilist>=NLIST )
 {
     return;
 }

// mout->printf("DEBUG Affix_Table::StoreAffix afx=%us base_afx=%us ilist=%d list.count()=", afx, base_afx, ilist, list.size());

// if( afx == L"НОМУ" )
//  mout.printf( "!" );

// if( list1.insert( afx ).second )
 std::pair<ITER,ITER> range = list1.equal_range( afx.GetHash() );
 bool found=false;

 int i_afx = UNKNOWN;

 if( range.first!=list1.end() )
  for( ITER i=range.first; i!=range.second; i++ ) 
   if( i->second.first==ilist && list[ilist][i->second.second]  == afx )
    {
     found = true;
     i_afx = i->second.second;
     break;
    }

 if( !found )
  {
   if( ilist<NLIST )
    {
     i_afx = CastSizeToInt(list[ilist].size());
     list1.insert( make_pair( afx.GetHash(), make_pair( ilist, i_afx ) ) );
     base_afx_list1[ilist].push_back( new MCollect<BaseAffix>() );
     list[ilist].push_back(afx);
    }
  }

 if( afx!=base_afx )
  {
   MCollect<BaseAffix> &lst = *base_afx_list1[ilist][i_afx];
 
   found=false;
   for( lem::Container::size_type i=0; i<lst.size(); i++ )
    if( lst[i].base_afx==base_afx && lst[i].id_language==id_language )
     {
      lst[i].n++;
      found=true;
      break;
     }

   if( !found )
    lst.push_back( BaseAffix(base_afx,id_language) );
  }

 return;
}
#endif

/*
#if defined SOL_LOADTXT && defined SOL_COMPILER
void Affix_Table::GenerateDynformsRules(void)
{
 // Выбираем наиболее достоверные (самые частые) правила для нормализатора
 for( int i=0; i<NLIST; i++ )
  {
   for( lem::Container::size_type j=0; j<base_afx_list1[i].size(); j++ )
    {
     MCollect<BaseAffix> lst = *base_afx_list1[i][j];

     int imax_afx=UNKNOWN, max_freq=0;
     for( lem::Container::size_type k=0; k<lst.size(); k++ )
      if( lst[k].n>max_freq )
       {
        max_freq = lst[k].n;
        imax_afx = k;
       }

     if( imax_afx!=UNKNOWN && lst[imax_afx].n>10 && !lst[imax_afx].base_afx.empty() )
      {
       rules.push_back( lem::make_triple( list[i][j], lst[imax_afx].base_afx, lst[imax_afx].id_language ) );
//       base_afx_list[i][j] = lst[imax_afx].base_afx;

//static int acount=1;
//out.printf( "%d afx=%W8us base_afx=%W8us\n", acount++, list[i][j].c_str(), lst[imax_afx].base_afx.c_str() );
      }
    }
  }

 return;
}
#endif
*/


#if defined SOL_SAVEBIN
void Affix_Table::SaveBin( lem::Stream &bin ) const
{
 int count=0;
 for( int i=0; i<NLIST; i++ )
  {
   count += CastSizeToInt(list[i].size());
   list[i].SaveBin(bin);
//   base_afx_list[i].SaveBin(bin);
  }

 lem::mout->printf( " %vfE%d%vn affixes ", count );

 return;
}
#endif


#if defined SOL_LOADBIN
void Affix_Table::LoadBin( lem::Stream &bin )
{
 for( int i=0; i<NLIST; i++ )
  {
   list[i].LoadBin(bin);
//   base_afx_list[i].LoadBin(bin);
  }

 return;
}
#endif


// *************************************************************
// Генерируем список возможных корней для слова word (убираем
// аффиксы).
// *************************************************************
void Affix_Table::GenerateRoots(
                                const UCString &word, // исходное слово
                                float MinBound,       // нижняя граница достоверности 
                                lem::MCollect<UCString> &res,
                                lem::MCollect<float>& str_val
                               ) const
{
 LEM_CHECKIT_Z( !word.empty() );

 for( int i=0; i<NLIST; i++ )
  {
   const int l = i+1;

   // Слово короче, чем все последующие аффиксы
   if( word.length() <= l )
    break;

   if( !list[i].empty() )
    {
     UCString afx = right( word, l );

     const int n = CastSizeToInt(list[i].size());
     for( int j=0; j<n; j++ )
      if( list[i][j] == afx )
       {
        // Достоверность.
        const float v = static_cast<float>(word.length()-afx.length()) / word.length();

        if( v < MinBound )
         // Слишком мала достоверность.
         continue;

        // Выделяем очередной корень.
        UCString r = left(word,word.length()-l);
        res.push_back(r); 

        str_val.push_back(v);
       }
    }  
  }

 if( res.empty() )
  {
   res.push_back(word);
   str_val.push_back(1.0F);
  }

 LEM_CHECKIT_Z( res.size()==str_val.size() );

 return;
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void Affix_Table::PrintInfo( OFormatter &out ) const
{
/*
 int count=0;
 for( int i=0; i<NLIST; i++ )
  count += list[i].size();

 out.printf( "Stemming rules: %vfE%d%vn total records, %vfE%d%vn dynforms rules\n", count, rules.size() );
*/
 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void Affix_Table::GenerateDynformsRules(void)
{
 // Выбираем наиболее достоверные (самые частые) правила для нормализатора
 for( int i=0; i<NLIST; i++ )
  {
   for( lem::Container::size_type j=0; j<base_afx_list1[i].size(); j++ )
    {
     MCollect<BaseAffix> lst = *base_afx_list1[i][j];

     int imax_afx=UNKNOWN, max_freq=0;
     for( lem::Container::size_type k=0; k<lst.size(); k++ )
      if( lst[k].n>max_freq )
       {
        max_freq = lst[k].n;
        imax_afx = k;
       }

     if( imax_afx!=UNKNOWN && lst[imax_afx].n>10 && !lst[imax_afx].base_afx.empty() )
      {
       rules.push_back( lem::make_triple( list[i][j], lst[imax_afx].base_afx, lst[imax_afx].id_language ) );
//       base_afx_list[i][j] = lst[imax_afx].base_afx;

//static int acount=1;
//out.printf( "%d afx=%W8us base_afx=%W8us\n", acount++, list[i][j].c_str(), lst[imax_afx].base_afx.c_str() );
      }
    }
  }

 return;
}
#endif

