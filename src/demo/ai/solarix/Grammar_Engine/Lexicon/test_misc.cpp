#include <stdio.h>
#include <string>

#include "../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../include/lem/solarix/_sg_api.h"

extern std::wstring from_utf8( const std::string & src );
extern void failed( HGREN hEngine );


void TestMiscellaneous( HGREN hEngine )
{
 int ie1 = sol_FindEntry8( hEngine, "МАМА", /*Solarix::API::*/NOUN_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE );
 if( ie1!=-1 )
  {
   wchar_t Word[64];
   wcscpy( Word, from_utf8("КОШКОЮ").c_str() );

   int changed = sol_TranslateToBase( hEngine, Word, 0 );
   if( changed!=1 || from_utf8("кошка")!=Word )
    failed(hEngine);

   wcscpy( Word, from_utf8("Аргентиной").c_str() );
   changed = sol_TranslateToBase( hEngine, Word, 0 );
   if( changed!=1 || from_utf8("Аргентина")!=Word )
    failed(hEngine);
  }

 return;
}
