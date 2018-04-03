#include "../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../include/lem/solarix/_sg_api.h"
#include <string.h>

extern void failed( HGREN hEngine );
extern bool ProbeRussian( HGREN hEngine );


void Test_Phrases( HGREN hEngine )
{
 // Проверяем функции работы с фразовыми статьями
 if( ProbeRussian(hEngine) )
  {
   // http://www.solarix.ru/api/en/sol_FindPhrase.shtml
   int id_phrase1 = sol_FindPhrase8( hEngine, "грамматический словарь русского языка", 0 );
   if( id_phrase1==-1 )
    failed(hEngine);

   const char phrase2[]="укатился в речку мячик";

   // http://www.solarix.ru/api/en/sol_AddPhrase.shtml
   int id_phrase2 = sol_AddPhrase8( hEngine, phrase2, RUSSIAN_LANGUAGE, NOUN_ru, 0 );
   if( id_phrase2==-1 )
    failed(hEngine);

   int id_phrase3 = sol_FindPhrase8( hEngine, phrase2, 0 );
   if( id_phrase3!=id_phrase2 )
    failed(hEngine);

   // http://www.solarix.ru/api/en/sol_GetPhraseText.shtml
   char *text = sol_GetPhraseText8( hEngine, id_phrase2 );

   if( strcmp( text, phrase2 )!=0 )
    failed(hEngine);

   sol_Free(hEngine,text);

   // http://www.solarix.ru/api/en/sol_DeletePhrase.shtml
   sol_DeletePhrase( hEngine, id_phrase2 );

   id_phrase2 = sol_FindPhrase8( hEngine, phrase2, 0 );
   if( id_phrase2!=-1 )
    failed(hEngine);
  }


 return;
}
