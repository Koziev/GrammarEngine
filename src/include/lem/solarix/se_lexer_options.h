#ifndef SE_LEXER_OPTIONS__H
#define SE_LEXER_OPTIONS__H
#pragma once

 #include <map>
 #include <lem/ucstring.h>
 #include <lem/solarix/se_general_options.h>

 namespace Solarix
 {
  namespace Search_Engine 
  {
    // *************************************************
   // Хранилище стоп-слов и других параметров лексеров
   // *************************************************
   struct Lexer_Options
   {
    // список стоп-слов
    std::multimap< lem::UCString::hash_type, lem::UCString > stopwords_list;
    typedef std::multimap< lem::UCString::hash_type, lem::UCString >::const_iterator SW_ITER; 

    // Загрузка списка из указанного файла
    void LoadStopwords( const General_Options& generals );

    // Нужно ли игнорировать слово (принадлежит к списку стоп-слов)?
    bool IsStopword( const lem::UCString &Word ) const;

    // Лексемы . ? !
    bool IsSentenceBreak( const lem::UCString &Word ) const;
   };

  }
 }
#endif

