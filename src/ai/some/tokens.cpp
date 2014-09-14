// -----------------------------------------------------------------------------
// File TOKENS.CPP
//
// (c) Koziev Elijah       SOLARIX Intellectronix Project  http://www.solarix.ru
//
//
// Tokens - dictionary description language PRIISK keywords.
// Tokens table loading procedure.
// -----------------------------------------------------------------------------
//
// CD->28.07.1997
// LC->06.07.2011
// --------------

#include <lem/lexers.h>
#include <lem/solarix/tokens.h>

using namespace Solarix;
using namespace lem;

// Общая таблица определений токенов
UCString* Solarix::SOL_TOKEN=NULL;

// Общая таблица определений разделителей
int Solarix::SOL_NDELIM=0;
wchar_t ** Solarix::SOL_COMPLEX=NULL;
UCString* Solarix::SOL_UCOMPLEX=NULL;

// Хэш-таблица со средствами быстрого поиска токена.
USrcLookUpTable* Solarix::SOL_LOOK_UP_TABLE=NULL;

const UCString& Solarix::sol_get_token( int i )
{
 LEM_CHECKIT_Z( i>=0 && i<SOL_NTOKEN );
 return Solarix::SOL_TOKEN[i];
}

/**************************************
 Строка является токеном?
***************************************/
bool Solarix::sol_is_token( const wchar_t *str )
{
 LEM_CHECKIT_Z( str!=NULL );
 return sol_ir_find_token(str)!=UNKNOWN;
}

/***************************************************************************
 Поиск лексемы как токена в глобальной таблице. В случае успеха возвращается
 индекс токена, иначе UNKNOWN.
****************************************************************************/
int Solarix::sol_ir_find_token( const UCString &s )
{ 
 LEM_CHECKIT_Z( !s.empty() );

 if( SOL_LOOK_UP_TABLE )
  // Возможен быстрый поиск через хэш-таблицу.
 return SOL_LOOK_UP_TABLE->Find(s);

 // Хэш-таблица не создана. Выполняем медленный поиск.
 for( int i=0; i<SOL_NTOKEN; i++ )
  if( s==sol_toktable[i] )
   return i;

 return UNKNOWN;
}


/*****************************************************************************
  Список всех токенов, используемых парсерами Соляриса.

   The following is a list of Solaris System reserved identifiers which
 can not be used as general identifiers (that is name of a class, a variable,
 a function and so on) for they have already been defined for other purposes.

   Combination of '!' keychar and lexem in apostrofes is used to declare so
 called complex delimiter, that composed of number of simple one-character
 delimiters like dot (.) or comma (,).
******************************************************************************/
const char* Solarix::sol_toktable[] = {
          "attributes",      // 0
          "class",           // 1
          "dimentions",      // 2
          "operator",        // 3
          "enum",            // 4
          "center",          // 5
          "~",               // 6
          "{",               // 7
          "}",               // 8
          "(",               // 9
          ")",               // 10
          ":",               // 11
          "=",               // 12
          "*",               // 13 Квантор ANY
          "[",               // 14
          "]",               // 15
          "if",              // 16
          "then",            // 17
          "correlate",       // 18
          "iteration",       // 19
          "net",             // 20
          "&",               // 21
          "|",               // 22
          ",",               // 23
          "entry",           // 24
          "include",         // 25
          "#",               // 26
          ".",               // 27
          "<",               // 28
          ">",               // 29
          "+",               // 30
          "int",             // 31
          "flag",            // 32
          "bool",            // 33
          "pass",            // 34
          "context",         // 35
          "string",          // 36
          "true",            // 37
          "false",           // 38
          "define",          // 39
          "undef",           // 40
          "ifdef",           // 41
          "ifndef",          // 42
          "else",            // 43
          "endif",           // 44
          "error",           // 45
          "print",           // 46
          "stop",            // 47
          "say",             // 48
          "?",               // 49 Квантор UNKNOWN
          "!", "...",        // 50 Квантор SOME
          "iterate",         // 51
          "set",             // 52
          "cut",             // 53
          "paradigm",        // 54
          "criterion",       // 55
          "predicate",       // 56
          "!", ":-",         // 57
          "convolution",     // 58
          "add",             // 59
          "tree",            // 60
          "priority",        // 61
          "!", "!",          // 62
          "!", "==",         // 63
          "!", "!=",         // 64
          "!", "||",         // 65
          "!", "&&",         // 66
          "defined",         // 67
          ";",               // 68
          "^",               // 69
          "/",               // 70
          "%",               // 71
          "-",               // 72
          "!", "<=",         // 73
          "!", ">=",         // 74
          "file",            // 75
          "pragma",          // 76
          "line",            // 77
          "do",              // 78
          "automat",         // 79
          "\\",              // 80
          "!", "##",         // 81
          "elif",            // 82
          "extern",          // 83
          "calibrate",       // 84
          "sound",           // 85
          "!", "!==",        // 86
          "waiter",          // 87
          "wait",            // 88
          "!", "->",         // 89
          "switch",          // 90
          "case",            // 91
          "default",         // 92
          "break",           // 93
          "begin",           // 94
          "end",             // 95
          "!", ">>",         // 96
          "lexem",           // 97
          "!", "=>",         // 98
          "char",            // 99
          "syllab",          // 100
          "array",           // 101
          "try",             // 102
          "clear",           // 103
          "refresh",         // 104
          "commit",          // 105
          "rollback",        // 106
          "!", "::",         // 107
          "merge",           // 108
          "random",          // 109
          "link",            // 110
          "rulegroup",       // 111
          "quantor",         // 112
          "for",             // 113 
          "auto",            // 114
          "language",        // 115
          "declare",         // 116
          "as",              // 117
          "iterator",        // 118 
          "alphabet",        // 119 
          "generator",       // 120
          "complex",         // 121
          "tags",            // 122
          "tag",             // 123
          "import",          // 124
          "from",            // 125
          "ngrams",          // 126 
          "impart",          // 127
          "flexer",          // 128
          "filter",          // 129
          "count",           // 130
          "or",              // 131
          "and",             // 132
          "not",             // 133                                      
          "text",            // 134
          "pattern",         // 135
          "value",           // 136
          "function",        // 137
          "!", "<<",         // 138
          "phrase",          // 139
          "omonym"           // 140  
         };
