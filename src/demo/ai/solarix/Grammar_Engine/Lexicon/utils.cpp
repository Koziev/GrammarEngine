#include <iostream>
#include "../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../include/lem/solarix/_sg_api.h"


#include <memory.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


#if defined WIN32
#include <windows.h>
#endif

extern void print8( const char *utf8 );

int fault_count=0;
void failed( HGREN hEngine )
{
 fault_count++;
 std::cout << "Failed!\n";

 // Last error reporting function.
 // http://www.solarix.ru/for_developers/api/grammar-engine-api.shtml#sol_GetError
 char err_text[1001];
 *err_text=0;
 sol_GetError8( hEngine, err_text, 1000 );
 if( strlen(err_text)>0 )
  {
   printf( "Engine error: " );
   print8( err_text );
   printf( "\n" );
  }

 return;
}

void failed( HGREN hEngine, const char * SentenceUTF8 )
{
 fault_count++;
 printf( "Failed on sentence: " );
 print8( SentenceUTF8 );
 printf( "\n" );

 char err_text[1001];
 *err_text=0;
 sol_GetError8( hEngine, err_text, 1000 );
 if( strlen(err_text)>0 )
  {
   printf( "Engine error: " );
   print8( err_text );
   printf( "\n" );
  }

 return;
}


void print8( const char *utf8 )
{
 #if defined WIN32
 const int l8 = strlen(utf8);
 char * a = new char[ l8+1 ];

 wchar_t *w = new wchar_t[ l8+1 ];

 MultiByteToWideChar( CP_UTF8, 0, utf8, l8+1, w, l8+1 );

 int w8 = wcslen(w);
 
 memset( a, 0, l8 );
 WideCharToMultiByte( CP_OEMCP, 0, w, w8+1, a, l8+1, NULL, NULL );
 
 printf( "%s", a );

 delete[] w;
 delete[] a;
 #else
 printf( "%s", utf8 );
 #endif
 return;
}

#if defined WIN32
void wide( const wchar_t *ustr, FILE *f=stdout, int cp=CP_OEMCP )
{
 const int l = wcslen(ustr);
 char *abuffer = new char[l*6+1];
 memset( abuffer, 0, l*6+1 );
 WideCharToMultiByte( cp, 0, ustr, l+1, abuffer, l*6+1, NULL, NULL );
 fprintf( f, "%s", abuffer );
 fflush(f);
 delete[] abuffer;

 return;
}
#else
void wide( const wchar_t *ustr, FILE *f=stdout, int cp=0 )
{
 wprintf( L"%s", ustr );
 return;
}
#endif


void PrintNode( HGREN_RESPACK hPack, HGREN_TREENODE hNode )
{
 #if defined WIN32
 wchar_t word[32];
 memset( word, 0, sizeof(word) );
 sol_GetNodeContents( hNode, word );

 if( wcschr( word, L' ' )!=NULL )
  {
   wide(L"[");
   wide(word);
   wide(L"]");
  }
 else
  {
   wide(word);
  }
 #else
 char word[100];
 memset( word, 0, sizeof(word) );
 sol_GetNodeContents8( hNode, word );

 if( strchr( word, ' ' )!=NULL )
  {
   printf("[");
   print8(word);
   printf("]");
  }
 else
  {
   print8(word);
  }
 #endif
  
 
 int nleaf = sol_CountLeafs( hNode );
 if( nleaf>0 )
  {
   printf( "(" );

   for( int i=0; i<nleaf; i++ )
    {
     printf( " " );
     PrintNode( hPack, sol_GetLeaf( hNode, i ) );
    }

   printf( " )" );
  }

 return;
}




void PrintGraph( HGREN_RESPACK hPack, int igraf )
{
 int nroot = sol_CountRoots( hPack, igraf );
 
 for( int i=1; i<nroot-1; i++ )
  {
   PrintNode( hPack, sol_GetRoot(hPack,igraf,i) ); 
   printf( " " );
  }

 printf( "\n" );
 return;
}


void PrintGraphs( HGREN_RESPACK hPack )
{
 if( hPack!=NULL )
  {
   const int ngrafs = sol_CountGrafs(hPack);

   for( int i=0; i<ngrafs; ++i )
    {
     printf( "\nTree #%d:\n", i+1 );
     PrintGraph( hPack, i );
    }
  }
 
 return;
}


bool TestSyntaxAnalysis( HGREN hEngine, const wchar_t *Phrase, int Language, bool must_be_complete_analysis )
{
 HGREN_RESPACK hPack = sol_SyntaxAnalysis( hEngine, Phrase, SOL_GREN_ALLOW_FUZZY, 0, 1000000, Language );

 if( hPack==NULL )
  {
   failed(hEngine);
   return false;
  }

 if( hPack )
  {
   const int ngrafs = sol_CountGrafs(hPack);
   printf( "There is %d alternative graph(s)\n", ngrafs );

   if( ngrafs==0 )
    {
     printf( "ERROR: syntax analysis has failed\n" );
     failed(hEngine);
     return false;
    }

   // Выберем среди результатов альтернативу с минимальным количеством корневых
   // узлов. Два узла присутствуют в каждой альтернативе - это метки начала $BEGIN$
   // и конца $END$. В случае полностью успешного анализа альтернатива имеет 3
   // корневых узла - средний узел представляет из себя искомое синтаксическое дерево.

   int imin_graf=-1, minv=INT_MAX;
   for( int i=0; i<ngrafs; i++ )
    {
     const int nroots = sol_CountRoots(hPack,i);
     if( nroots<minv ) 
      {
       minv = nroots;
       imin_graf = i; 
      }  
    }

   if( imin_graf!=-1 )
    {
     // Наиболее компактный граф содержит minv узлов верхнего уровня.
     // Распечатаем содержимое этого графа.
     PrintGraph( hPack, imin_graf );
    }

   // 3 узла - это полностью завершенный анализ.
   if( must_be_complete_analysis && minv!=3 )
    {
     printf( "ERROR: syntax analysis has failed\n" );
     failed(hEngine);
     return false;
    }
 
   sol_DeleteResPack( hPack );
  }

 return true;
}


void Print_StrList( HGREN hEngine, HGREN_STR hStr )
{
 const int MAX_LEN = sol_MaxLexemLen(hEngine);

 int nstr = sol_CountStrings( hStr );

 wchar_t ** str_list = new wchar_t*[nstr];
 for( int i=0; i<nstr; i++ )
  str_list[i] = new wchar_t[ MAX_LEN+1 ];

 sol_GetStrings( hStr, str_list );

 printf( "forms={ " );
 for( int i=0; i<nstr; i++ )
  {
   wide(str_list[i]);
   printf( " " );   
  }
 printf( "}\n\n" );

 sol_DeleteStrings( hStr );
 for( int i=0; i<nstr; i++ )
  delete[] str_list[i];

 delete[] str_list;
 return;
}

void Print_IntList( HGREN hEngine, HGREN_INTARRAY hList )
{
 if( hList!=NULL )
  {
   wchar_t buffer[64];
   const int ne = sol_CountInts( hList );

   // выведем список с именами статей
   printf( "Number of links: %d\n", ne );
   for( int i=0; i<ne; i++ )
    {
     // элементы списка - это внутренние индексы статей. Для получения лексического имени
     // статьи используем вызов API:
     const int ientry = sol_GetInt(hList,i);
     sol_GetEntryName( hEngine, ientry, buffer );

     // печатаем имя статьи
     wide(buffer);
     printf("\n");
    }
  }

 return;
}

// *************************************************************************
// Проверям, что в тезаурусе есть связь между двумя словарными статьями.
// *************************************************************************
bool TestLink( HGREN hEngine, const wchar_t *Word1, int Class1, const wchar_t *Word2, int Class2 )
{
 bool ok = false;

 int ie1 = sol_FindEntry( hEngine, Word1, Class1, -1 );
 if( ie1==-1 || sol_GetEntryClass( hEngine, ie1 )!=Class1 )
  {
   failed(hEngine);
   return false;
  } 

 int ie2 = sol_FindEntry( hEngine, Word2, Class2, -1 );
 if( ie2==-1 || sol_GetEntryClass( hEngine, ie2 )!=Class2 )
  {
   failed(hEngine);
   return false;
  } 

 HGREN_INTARRAY hList = sol_SeekThesaurus( hEngine, ie1, true, true, true, true, 1 );

 if( hList==NULL )
  { 
   failed(hEngine);
   return false;
  } 

 const int ne = sol_CountInts( hList );

 for( int i=0; i<ne; i++ )
  {
   // элементы списка - это внутренние индексы статей. Для получения лексического имени
   // статьи используем вызов API:
   const int ientry = sol_GetInt(hList,i);
   if( ientry==ie2 )
    {
     ok = true;
     break;
    }
  }

 sol_DeleteInts( hList );

 if( !ok )
  failed(hEngine);

 return ok;
}


// аналог strcmp, но исключает пробелы из сравнения
int strcmp_sp( const char *s1, const char *s2 )
{
 int i1=0, i2=0;
 while( s1[i1]!=0 && s2[i2]!=0 )
  {
   if( s1[i1]==' ' )
    {
     i1++;
     continue;
    }

   if( s2[i2]==' ' )
    {
     i2++;
     continue;
    }

   if( s1[i1]==s2[i2] )
    {
     i1++;
     i2++;
     continue;
    }

   if( s1[i1]>s2[i2] )
    return 1;
   else
    return -1;
  }

 if( s1[i1]==s2[i2] )
  return 0;
 else if( s1[i1]>s2[i2] )
  return 1;
 else
  return -1;
}




void utf8toWStr( std::wstring & dest, const std::string & src )
{
 dest.clear();
 wchar_t w = 0;
 int bytes = 0;
 wchar_t err = L' ';

 for (size_t i = 0; i < src.size(); i++){
  unsigned char c = (unsigned char)src[i];
  if (c <= 0x7f){//first byte
   if (bytes){
    dest.push_back(err);
    bytes = 0;
   }
   dest.push_back((wchar_t)c);
  }
  else if (c <= 0xbf){//second/third/etc byte
   if (bytes){
    w = ((w << 6)|(c & 0x3f));
    bytes--;
    if (bytes == 0)
     dest.push_back(w);
   }
   else
    dest.push_back(err);
  }
  else if (c <= 0xdf){//2byte sequence start
   bytes = 1;
   w = c & 0x1f;
  }
  else if (c <= 0xef){//3byte sequence start
   bytes = 2;
   w = c & 0x0f;
  }
  else if (c <= 0xf7){//3byte sequence start
   bytes = 3;
   w = c & 0x07;
  }
  else{
   dest.push_back(err);
   bytes = 0;
  }
 }
 if (bytes)
  dest.push_back(err);
}

std::wstring from_utf8( const std::string & src )
{
 std::wstring dest;
 utf8toWStr( dest, src );
 return dest;
}




void wstrToUtf8( std::string& dest, const std::wstring & src )
{
 dest.clear();
 for (size_t i = 0; i < src.size(); i++){
  wchar_t w = src[i];
  if (w <= 0x7f)
   dest.push_back((char)w);
  else if (w <= 0x7ff){
   dest.push_back(0xc0 | ((w >> 6)& 0x1f));
   dest.push_back(0x80| (w & 0x3f));
  }
  else if (w <= 0xffff){
   dest.push_back(0xe0 | ((w >> 12)& 0x0f));
   dest.push_back(0x80| ((w >> 6) & 0x3f));
   dest.push_back(0x80| (w & 0x3f));
  }
  else if (w <= 0x10ffff){
   dest.push_back(0xf0 | ((w >> 18)& 0x07));
   dest.push_back(0x80| ((w >> 12) & 0x3f));
   dest.push_back(0x80| ((w >> 6) & 0x3f));
   dest.push_back(0x80| (w & 0x3f));
  }
  else
   dest.push_back('?');
 }
}



bool ProbeRussian( HGREN hEngine )
{
 // Мы не можем заранее знать, содержит ли загруженный словарь русский лексикон.
 // Более того, даже наличие нескольких словарных статей, принадлежащих
 // русскому языку, еще не доказывает наличие всего лексикона - это могут быть
 // специальные технические статьи. Поэтому поступаем так: ищем в словаре
 // распространенное слово, и если оно там есть - значит русский лексикон загружен.
 int ie1 = sol_FindEntry8( hEngine, "МАМА", /*Solarix::API::*/NOUN_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE );
 if( ie1==-1 )
  {
   printf( "Russian lexicon is missing.\n" );
   return false;
  }

 return true;
}


bool ProbeEnglish( HGREN hEngine )
{
 const int MAX_LEN = sol_MaxLexemLen(hEngine);

 const int ie1 = sol_FindEntry( hEngine, L"MOTHER", /*Solarix::API::*/NOUN_en, /*Solarix::API::*/ENGLISH_LANGUAGE );
 if( ie1==-1 )
  {
   printf( "English lexicon is missing.\n" );
   return false;
  }

 return true;
}
