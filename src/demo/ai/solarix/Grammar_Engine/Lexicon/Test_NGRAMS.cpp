#include "../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../include/lem/solarix/_sg_api.h"

extern void failed( HGREN hEngine );

void Test_NGRAMS( HGREN hEngine )
{
 int freq;
 unsigned int Hi, Lo;

 sol_CountNGrams( hEngine, 0, 1, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   // http://www.solarix.ru/api/en/sol_Seek1Grams.shtml
   freq = sol_Seek1Grams8( hEngine, 0, "СОБАКА" ); // без лемматизации
   if( freq<=0 ) failed(hEngine);
   freq = sol_Seek1Grams8( hEngine, 1, "СОБАКА" ); // с лемматизацией
   if( freq<=0 ) failed(hEngine);
  }

 sol_CountNGrams( hEngine, 0, 2, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   // http://www.solarix.ru/api/en/sol_Seek2Grams.shtml
   freq = sol_Seek2Grams8( hEngine, 0, "СОБАКА", "И" );
   if( freq<=0 ) failed(hEngine);
   freq = sol_Seek2Grams8( hEngine, 1, "СОБАКА", "И" );
   if( freq<=0 ) failed(hEngine);
  }

 sol_CountNGrams( hEngine, 0, 3, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   // http://www.solarix.ru/api/en/sol_Seek3Grams.shtml
   freq = sol_Seek3Grams8( hEngine, 0, "СОБАКА", "И", "КОШКА" );
   if( freq<=0 ) failed(hEngine);
   freq = sol_Seek3Grams8( hEngine, 1, "СОБАКА", "И", "КОШКА" );
   if( freq<=0 ) failed(hEngine);
  }
 
 sol_CountNGrams( hEngine, 0, 4, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   // http://www.solarix.ru/api/en/sol_Seek4Grams.shtml
   freq = sol_Seek4Grams8( hEngine, 0, "СОБАКА", "И", "КОШКА", "НАШЛИ" );
   if( freq<=0 ) failed(hEngine);
   freq = sol_Seek4Grams8( hEngine, 1, "СОБАКА", "И", "КОШКА", "НАШЛИ" );
   if( freq<=0 ) failed(hEngine);
  }

 sol_CountNGrams( hEngine, 0, 5, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   // http://www.solarix.ru/api/en/sol_Seek5Grams.shtml
   freq = sol_Seek5Grams8( hEngine, 0, "СОБАКА", "И", "КОШКА", "НАШЛИ", "БОЛЬШОЕ" );
   if( freq<=0 ) failed(hEngine);
   freq = sol_Seek5Grams8( hEngine, 1, "СОБАКА", "И", "КОШКА", "НАШЛИ", "БОЛЬШОЕ" );
   if( freq<=0 ) failed(hEngine);
  }

 // http://www.solarix.ru/api/en/sol_CountNGrams.shtml
 sol_CountNGrams( hEngine, 0, 1, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   int f = sol_Seek1Grams8( hEngine, 0, "раз" );
   if(f<=0) failed(hEngine);
  }

 sol_CountNGrams( hEngine, 0, 2, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   int f = sol_Seek2Grams8( hEngine, 0, "раз", "два" );
   if(f<=0) failed(hEngine);
  }
 
 sol_CountNGrams( hEngine, 0, 3, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   int f = sol_Seek3Grams8( hEngine, 0, "раз", "два", "три" );
   if(f<=0) failed(hEngine);
  }

 sol_CountNGrams( hEngine, 0, 4, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   int f = sol_Seek4Grams8( hEngine, 0, "раз", "два", "три", "четыре" );
   if(f<=0) failed(hEngine);
  }

 sol_CountNGrams( hEngine, 0, 5, &Hi, &Lo );
 if( Hi+Lo > 0 )
  {
   int f = sol_Seek5Grams8( hEngine, 0, "раз", "два", "три", "четыре", "пять" );
   if(f<=0) failed(hEngine);
  }
 

 return;
}
