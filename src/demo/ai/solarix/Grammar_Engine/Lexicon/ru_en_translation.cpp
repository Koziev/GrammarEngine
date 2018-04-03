#include <assert.h>
#include <iostream>
#include <windows.h>

// API documentation: http://www.solarix.ru/for_developers/api/grammar-engine-api.shtml
// Other samples: http://www.solarix.ru/for_developers/api/grammar-engine-examples.shtml
// Troubleshooting: http://www.solarix.ru/contacts/contacts.shtml

// Grammar Engine API
// API грамматической машины
#include "..\..\..\..\..\include\lem\solarix\solarix_grammar_engine.h"
#include "..\..\..\..\..\include\lem\solarix\_sg_api.h"

using namespace std;


extern void failed( HGREN hEngine );
extern bool ProbeEnglish( HGREN hEngine );
extern bool ProbeRussian( HGREN hEngine );


static bool TestTranslation( HGREN hEngine, int icls_from, const wchar_t *word_from, int icls_to, const wchar_t *word_to )
{
 for( int j=0; j<2; ++j )
  {
   int ie1 = sol_FindEntry( hEngine, word_from, /*Solarix::API::*/icls_from, -1 );
   int ie2 = sol_FindEntry( hEngine, word_to, /*Solarix::API::*/icls_to, -1 );

   if( j==1 )
    std::swap(ie1,ie2);

   if( ie1==-1 || ie2==-1 )
    {
     failed(hEngine);
     return false;
    }

   HGREN_INTARRAY hList = sol_SeekThesaurus( hEngine, ie1, false, false, true, false, 1 );

   if( hList==NULL )
    { 
     failed(hEngine);
     return false;
    } 

   bool found=false;
   if( hList!=NULL )
    {
     // кол-во связанных статей
     const int ne = sol_CountInts( hList );

     for( int i=0; i<ne; i++ )
      {
       // элементы списка - это внутренние индексы статей. Для получения лексического имени
       // статьи используем вызов API:
       const int ientry = sol_GetInt(hList,i);
  
       if( ientry==ie2 )
        {
         found=true;
         break;
        }   

/*
     if( iclass==NOUN_en )
      {
       wchar_t buffer[64];
       char abuffer[64];
       sol_GetEntryName( hEngine, ientry, buffer );

       // печатаем словарной статьи имя
       WideCharToMultiByte( CP_OEMCP, 0, buffer, wcslen(buffer)+1, abuffer, sizeof(abuffer), NULL, NULL );
       cout << abuffer << "\n";
      }
*/
      }
    }

   if( !found )
    failed(hEngine);
  }

 return true;
}


void Test_Ru_En_Translation( HGREN hEngine )
{
 if( !ProbeEnglish(hEngine) || !ProbeRussian(hEngine) )
  return;

 TestTranslation( hEngine, /*Solarix::API::*/NOUN_ru, L"МАМА", /*Solarix::API::*/NOUN_en, L"MOTHER" );
 TestTranslation( hEngine, /*Solarix::API::*/NOUN_ru, L"КОШКА", /*Solarix::API::*/NOUN_en, L"CAT" );
 TestTranslation( hEngine, /*Solarix::API::*/NOUN_ru, L"СОБАКА", /*Solarix::API::*/NOUN_en, L"DOG" );

 TestTranslation( hEngine, /*Solarix::API::*/INFINITIVE_ru, L"ЛЮБИТЬ", /*Solarix::API::*/VERB_en, L"LOVE" );
 TestTranslation( hEngine, /*Solarix::API::*/INFINITIVE_ru, L"ДУМАТЬ", /*Solarix::API::*/VERB_en, L"THINK" );

 TestTranslation( hEngine, /*Solarix::API::*/ADJ_ru, L"БЕЛЫЙ", /*Solarix::API::*/ADJ_en, L"WHITE" );
 TestTranslation( hEngine, /*Solarix::API::*/ADJ_ru, L"БОЛЬШОЙ", /*Solarix::API::*/ADJ_en, L"BIG" );

 return;
}

