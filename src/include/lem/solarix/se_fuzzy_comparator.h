// -----------------------------------------------------------------------------
// File SE_FUZZY_COMPARATOR.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Fuzzy_Comparator - автомат для выполнения нечетких сравнений слов
// -----------------------------------------------------------------------------
//
// CD->22.08.2005
// LC->30.05.2011
// --------------

#ifndef SE_FUZZY_COMPARATOR__H
#define SE_FUZZY_COMPARATOR__H
#pragma once

 #include <map>
 #include <lem/cstring.h>
 #include <lem/streams.h>
 #include <lem/unicode.h>
 #include <lem/conversions.h>
 #include <lem/math/fp1.h>
 #include <lem/tuple.h>

 namespace Solarix
 {
  class Affix_Table;
  class Dictionary;
  class LA_PhoneticRule;

  namespace Search_Engine
  {
   struct Search_Options;

   class Fuzzy_Comparator
   {
    private:
     enum { UNCOMPARABLE=1000000000 };

     int max_miss;  // максимальное число пропусков букв
     int max_subst; // максимальное число нечетких сравнений букв

     int max_diff; // итоговое максимальное число отличий

     const Search_Options *flags; // опции управления 

     boost::shared_ptr<Solarix::Affix_Table> affixes; // Таблица аффиксов
     
     // Справочник для перевода символов в базовую форму.
     std::map< wchar_t, wchar_t > char_to_base;
     typedef std::map< wchar_t, wchar_t >::const_iterator CB_ITER;

     // Справочники для нечеткого сравнения символов

     typedef std::pair<wchar_t,wchar_t> pair_char;


     std::map< pair_char, float > char_eq;
     typedef std::map< pair_char, float >::const_iterator CE_ITER;

     typedef std::pair<pair_char,pair_char> pair_str22;
     typedef std::pair<pair_char,wchar_t> pair_str21;
     typedef std::pair< lem::triple<wchar_t,wchar_t,wchar_t>,wchar_t> pair_str31;


     std::map< pair_str22, float > char22_eq;
     typedef std::map< pair_str22, float >::const_iterator C22E_ITER;

     std::map< pair_str21, float > char21_eq;
     typedef std::map< pair_str21, float >::const_iterator C21E_ITER;

     std::map< pair_str31, float > char31_eq;
     typedef std::map< pair_str31, float >::const_iterator C31E_ITER;


     std::multimap< pair_char /*первые буквы условия и следствия*/, const Solarix::LA_PhoneticRule* > charN1_eq;
     typedef std::multimap< pair_char /*первые буквы условия и следствия*/, const Solarix::LA_PhoneticRule* >::const_iterator CN1E_ITER;

     // *************************************************************
     // Символ приводится к некоторому базовому (частный случай - 
     // к заглавным буквам, Ё к Е, и так далее).
     // *************************************************************
     inline wchar_t To_Base( wchar_t ch ) const
     {
      #if defined LEM_UNICODE_EX
      return lem::CodeConverter::to_upper( lem::CodeConverter::Strip_Diaktrices(ch) );
      #else
      CB_ITER i = char_to_base.find( ch );
      if( i==char_to_base.end() )
       return lem::to_uupper( ch );
      return i->second;
      #endif
     }

     // *************************************************************
     // Сравнимы ли два символа
     // *************************************************************
     inline bool Eq_Char( wchar_t A, wchar_t B, float &rel ) const
     {
      CE_ITER i = char_eq.find( pair_char(A,B) );
      if( i!=char_eq.end() )
       {
        rel = i->second;
        return true;
       }

      return false;
     }
    

     // **********************************************************************
     // Оценивает разницу между лексемами, возвращает число отличий.
     // **********************************************************************
     float Compare( const wchar_t *A, const wchar_t *B, float cur_miss=0 ) const;

    public:
     Fuzzy_Comparator(void);
     ~Fuzzy_Comparator(void);

     void ApplyDictionary( const Solarix::Dictionary &dict );

     void SetOptions( const Search_Options *Flags );

     // Интерфейсный метод для использования внешними процедурами - нечеткое
     // сравнение двух лексем.
     //
     // Возвращается - проценты (0...100) сопоставимости лексем. 0 - лексемы
     // несопоставимы, 100 - полное совпадение лексем.
     int Eq( const lem::UCString& A, const lem::UCString& B ) const;

     inline int GetMaxDiff(void) const { return max_diff; }
     inline void SetMaxDiff( int x ) { max_diff=x; }

     inline const Affix_Table& GetAffixTable(void) const { return *affixes; }
     inline bool HasAffixTable(void) const { return !!affixes; }

     void LoadBin( lem::Stream &bin );
   };

  }
 }
#endif
