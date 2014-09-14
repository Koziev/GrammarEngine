// -----------------------------------------------------------------------------
// File TOKENS.H
//
// (c) Koziev Elijah       SOLARIX Intellectronix Project  http://www.solarix.ru
//
//
// Список ТОКЕНОВ - символических констант для ссылок на ключевые слова Системы.
// Обслуживание таблицы токенов, доступ к ней для поиска.
// Сами лексические значения токенов находятся в [Lem\IO\Iridium\ir_tokl.cpp]
//
// 06.05.2006 - добавлен токен id
// 28.08.2008 - добавлены токены tags и tag
// 13.12.2008 - добавлен токен import для автокопирования некоторых атрибутов
//              типа переходности и падежной валентности из инфинитивов в
//              глаголы.
// 02.01.2009 - добавлен тэг 'flexer' для управляемых парадигм
// 05.01.2009 - добавлен тэг 'filter' для задания фильтров миксера варианторов
// 23.03.2009 - добавлен тэг 'count' для нового кондиктора
// 20.04.2009 - добавлен тэг 'text' для нового кондиктора
// 07.08.2009 - добавлен токен B_LSHIFT "<<"
// -----------------------------------------------------------------------------
//
// CD->06.06.1997
// LC->27.09.2011
// --------------

#ifndef IR_TOKENS__H
#define IR_TOKENS__H
#pragma once

 #include <lem/lexers.h>

 namespace Solarix
 {
  using lem::UCString;
  using lem::USrcLookUpTable;

  // ***************************************************
  // *                                                 *
  // * Индексы для извлечения имен токенов Транслятора *
  // *                                                 *
  // ***************************************************
  const int B_ATTRIBUTES  = 0;
  const int B_CLASS       = 1;
  const int B_DIMENTIONS  = 2;
  const int B_RULE        = 3;
  const int B_ENUM        = 4;
  const int B_CENTER      = 5;
  const int B_TILDA       = 6;
  const int B_OFIGPAREN   = 7;
  const int B_CFIGPAREN   = 8;
  const int B_OROUNDPAREN = 9;
  const int B_CROUNDPAREN = 10;
  const int B_COLON       = 11;
  const int B_EQUAL       = 12;
  const int B_ANY         = 13;
  const int B_OSPAREN     = 14;
  const int B_CSPAREN     = 15;
  const int B_IF          = 16;
  const int B_THEN        = 17;
  const int B_CORRELATE   = 18;
  const int B_ITERATION   = 19;
  const int B_NET         = 20;
  const int B_AMPERSAND   = 21;
  const int B_ORSIGN      = 22;
  const int B_COMMA       = 23;
  const int B_ENTRY       = 24;
  const int B_INCLUDE     = 25;
  const int B_DIEZ        = 26;
  const int B_DOT         = 27;
  const int B_OTRIPAREN   = 28;
  const int B_CTRIPAREN   = 29;
  const int B_PLUS        = 30;
  const int B_INT         = 31;
  const int B_FLAG        = 32;
  const int B_BOOL        = 33;
  const int B_PASS        = 34;
  const int B_CONTEXT     = 35;
  const int B_STRING      = 36;
  const int B_TRUE        = 37;
  const int B_FALSE       = 38;
  const int B_DEFINE      = 39;
  const int B_UNDEFINE    = 40;
  const int B_IFDEF       = 41;
  const int B_IFNDEF      = 42;
  const int B_ELSE        = 43;
  const int B_ENDIF       = 44;
  const int B_USER_ERROR  = 45;
  const int B_PRINT       = 46;
  const int B_STOP        = 47;
  const int B_SAY         = 48;
  const int B_UNKNOWN     = 49;
  const int B_ELLIPSIS    = 50;
  const int B_ITERATE     = 51;
  const int B_SET         = 52;
  const int B_CUT         = 53;
  const int B_PARADIGMA   = 54;
  const int B_CRITERION   = 55;
  const int B_PREDICATE   = 56;
  const int B_IFTHEN      = 57; // :-
  const int B_CONVOLUTION = 58;
  const int B_ADD         = 59;
  const int B_TREE        = 60;
  const int B_PRIORITY    = 61;
  const int B_LOGNOT      = 62;
  const int B_LOGEQ       = 63;
  const int B_LOGNE       = 64;
  const int B_LOGOR       = 65;
  const int B_LOGAND      = 66;
  const int B_DEFINED     = 67;
  const int B_SEMICOLON   = 68;
  const int B_UPARROW     = 69;
  const int B_SLASH       = 70;
  const int B_PERCENT     = 71;
  const int B_SUB         = 72;
  const int B_LOGLE       = 73; // <=
  const int B_LOGGE       = 74; // >=
  const int B_FILE        = 75;
  const int B_PRAGMA      = 76;
  const int B_LINE        = 77;
  const int B_DO          = 78;
  const int B_AUTOMAT     = 79;
  const int B_BACKSLASH   = 80;
  const int B_DIEZ_DUP    = 81;
  const int B_ELIF        = 82;
  const int B_EXTERN      = 83;
  const int B_CALIBRATE   = 84;
  const int B_SOUND       = 85;
  const int B_PA_PREC_NEQ = 86; // !==
  const int B_WAITER      = 87;
  const int B_WAITE       = 88;
  const int B_ARROW_R     = 89; // ->
  const int B_SWITCH      = 90;
  const int B_CASE        = 91;
  const int B_DEFAULT     = 92;
  const int B_BREAK       = 93;
  const int B_BEGIN       = 94;
  const int B_END         = 95;
  const int B_RSHIFT      = 96; // >>
  const int B_LEXEM       = 97;
  const int B_BARROW_R    = 98; // =>
  const int B_CHAR        = 99; // char
  const int B_SYLLAB      = 100; // syllab
  const int B_ARRAY       = 101; // array
  const int B_TRY         = 102; // try
  const int B_CLEAR       = 103; // clear
  const int B_REFRESH     = 104; // refresh
  const int B_COMMIT      = 105; // commit
  const int B_ROLLBACK    = 106; // rollback
  const int B_DCOLON      = 107; // ::
  const int B_MERGE       = 108; // merge
  const int B_RANDOM      = 109; // random
  const int B_LINK        = 110; // link
  const int B_RULEGROUP   = 111; // rulegroup
  const int B_QUANTOR     = 112; // quantor 
  const int B_FOR         = 113; // quantor 
  const int B_AUTO        = 114; // auto
  const int B_LANGUAGE    = 115; // language
  const int B_DECLARE     = 116; // declare
  const int B_AS          = 117; // as
  const int B_ITERATOR    = 118; // iterator
  const int B_ALPHABET    = 119; // alphabet
  const int B_GENERATOR   = 120; // generator
  const int B_COMPLEX     = 121; // complex
  const int B_TAGS        = 122; // tags
  const int B_TAG         = 123; // tag
  const int B_IMPORT      = 124; // import
  const int B_FROM        = 125; // from
  const int B_NGRAMS      = 126; // ngrams
  const int B_IMPART      = 127; // impart
  const int B_FLEXER      = 128; // flexer
  const int B_FILTER      = 129; // filter
  const int B_COUNT       = 130; // count
  const int B_OR          = 131; // or
  const int B_AND         = 132; // and
  const int B_NOT         = 133; // not
  const int B_TEXT        = 134; // text
  const int B_PATTERN     = 135; // pattern
  const int B_VALUE       = 136; // value 
  const int B_FUNCTION    = 137; // function
  const int B_LSHIFT      = 138; // <<
  const int B_PHRASE      = 139; // phrase
  const int B_OMONYM      = 140; // omonym
  

  // Aliases for token names.
  #define B_QUESTION    B_UNKNOWN
  #define B_LOGGT       B_OTRIPAREN
  #define B_LOGLT       B_CTRIPAREN
  #define B_COORDINATE  B_ENUM
  #define B_NEGATIVE    B_TILDA
  #define B_SOME        B_ELLIPSIS
  #define B_MOD         B_PERCENT
  #define B_DIV         B_SLASH

  const int SOL_NTOKEN = 141;    // Общее число токенов
  extern UCString *SOL_TOKEN;

  extern int SOL_NDELIM; // Сложные разделители
  extern wchar_t **SOL_COMPLEX;
  extern UCString* SOL_UCOMPLEX; // Список сложных разделителей

  extern USrcLookUpTable *SOL_LOOK_UP_TABLE;

  extern const UCString& sol_get_token( int i );
  extern bool sol_is_token( const wchar_t *str );
  extern int sol_ir_find_token( const UCString &s );

  extern const char* sol_toktable[];

 } // namespace 'Solarix'

#endif
