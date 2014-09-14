// -----------------------------------------------------------------------------
// File LA_LEX.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Часть кода Лексического Автомата, то есть реализация части методов класса
// LexicalAutomat.
// -----------------------------------------------------------------------------
//
// CD->01.09.1997
// LC->09.06.2011
// --------------

#include <lem/solarix/gg_autom.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/WideStringUcs4.h>
#include <lem/Ucs4ToWideString.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LA_FuzzyMatching.h>
#include <lem/solarix/la_autom.h>

using namespace lem;
using namespace Solarix;

/*************************************************************************
 Для каждого символа слова word находим соответствующую статью и форму
 в Алфавите Графической Грамматике. Результатом работы процедуры является
 структура с подробной информацией о графической структуре слова. Именно
 эта процедура преобразует некое слово в настоящую лексему (она
 возвращается как Lexem).

 Если поле substitute_entries=false, то вместо имен буквостатей будут
 использованы имена буквоформ.

 23.12.2008: UNSAFE из-за того, что длина результата может быть больше
             длины исходной строки!
**************************************************************************/
void LexicalAutomat::ToLexemX(
                              const wchar_t *word,
                              bool substitute_entries,
                              Lexem &res,
                              int LanguageID
                             )
{
 WideStringUcs4 cenum(word);
 lem::uint32_t c;
 lem::uint32_t prev_c=0;

 lem::Ucs4ToUCString yield;

 while( (c=cenum.Fetch())!=0 )
  {
   if( c==L'$' )
    {
     yield.Add(c);

     lem::uint32_t c2 = cenum.Fetch();
     if( c2!=0 )
      {
       // Символ $ используется для escape-последовательностей
       yield.Add(c2);
      }

     continue;
    }

   if( c==L' ' )
    {
     // Оставляем всегда единственный пробел (точнее - символ разделения лексем
     // в мультилексеме).
     if( prev_c!=Lexem::DelimiterChar )
      {
       yield.Add(Lexem::DelimiterChar);
       prev_c = c;
      }

     continue;
    }

   if( c==L'-' || c==L',' || c==L'\'' )
    {
     if( prev_c!=Lexem::DelimiterChar && prev_c!=0 )
      yield.Add(Lexem::DelimiterChar);

     yield.Add(c);

     if( cenum.Fetch()!=0 )
      {
       yield.Add( Lexem::DelimiterChar );
       cenum.Back();
      }

     prev_c = Lexem::DelimiterChar;

     continue;
    }

   Word_Coord wc;
   if( LanguageID==ANY_STATE ) 
    {
     wc = GG->FindSymbol(c);
    }
   else if( LanguageID==UNKNOWN )
    {
     wc = GG->FindSymbol(c,GetDefaultAlphabets());
    }
   else
    {
     const Solarix::SG_Language &lang = GetDict().GetSynGram().languages()[LanguageID];
     const lem::MCollect<int> &id_alphabets = lang.GetAlphabets();
     wc = GG->FindSymbol(c,id_alphabets);
    }

   if( wc.GetEntry()==UNKNOWN )
    {
     // Символ не найден в графической грамматике.
     yield.Add(c);
    }
   else
    {
     const GG_Entry &entry = GG->entries()[ wc.GetEntry() ];

     if(
        !substitute_entries ||
        wc.GetForm()==UNKNOWN ||
        wc.GetForm()==ANY_STATE
       )
      yield.Add( entry.GetForm(wc.GetForm()).GetName() );
     else
      yield.Add( entry.GetName() );
    }

   prev_c = c;
  }

 res = yield.ToString();

 return;
}


void LexicalAutomat::TranslateLexem(
                                    Lexem &mlex,
                                    bool substitute_entries,
                                    int LanguageID
                                   )
{
 Lexem res;
 ToLexemX( mlex.c_str(), substitute_entries, res, LanguageID );
 mlex = res;
 return;
}


void LexicalAutomat::TranslateLexem(
                                    lem::UFString &str,
                                    bool substitute_entries,
                                    int LanguageID
                                   )
{
 WideStringUcs4 cenum(str.c_str());
 lem::uint32_t c;
 lem::uint32_t prev_c=0;

 lem::Ucs4ToUFString yield;

 while( (c=cenum.Fetch())!=0 )
  {
   if( c==L' ' )
    {
     // Оставляем всегда единственный пробел (точнее - символ разделения лексем
     // в мультилексеме).
     if( prev_c!=Lexem::DelimiterChar )
      {
       yield.Add(Lexem::DelimiterChar);
       prev_c = c;
      }

     continue;
    }

   if( c==L'-' || c==L',' || c==L'\'' )
    {
     if( prev_c!=Lexem::DelimiterChar && prev_c!=0 )
      yield.Add(Lexem::DelimiterChar);

     yield.Add(c);

     if( cenum.Fetch()!=0 )
      {
       yield.Add( Lexem::DelimiterChar );
       cenum.Back();
      }

     prev_c = Lexem::DelimiterChar;

     continue;
    }

   Word_Coord wc;
   if( LanguageID==ANY_STATE ) 
    wc = GG->FindSymbol(c);
   else if( LanguageID==UNKNOWN )
    wc = GG->FindSymbol(c,GetDefaultAlphabets());
   else
    wc = GG->FindSymbol(c,LanguageID);

   if( wc.GetEntry()==UNKNOWN )
    {
     // Символ не найден в графической грамматике.
     yield.Add(c);
    }
   else
    {
     const GG_Entry &entry = GG->entries()[ wc.GetEntry() ];

     if(
        !substitute_entries ||
        wc.GetForm()==UNKNOWN ||
        wc.GetForm()==ANY_STATE
       )
      yield.Add( entry.GetForm(wc.GetForm()).GetName() );
     else
      yield.Add( entry.GetName() );
    }

   prev_c = c;
  }

 str = yield.ToString();

 return;
}


/****************************************************************
 Если каждому символу слова можно поставить в соответствие
 статью графической грамматики, то слово считаем корректной
 словоформой.
*****************************************************************/
bool LexicalAutomat::IsCorrectWord( const UCString& word ) const
{
 for( UCString::size_type i=0; i<word.length(); i++ )
  if( GG->FindSymbol(word[i]).GetEntry()==UNKNOWN )
   return false;

 return true;
}

