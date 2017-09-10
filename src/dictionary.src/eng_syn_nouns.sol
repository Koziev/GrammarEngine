// LC->03.01.2009

automat sg
{
 #define syn( A, B, C=NULL ) \
  #begin
   extern entry A:ENG_NOUN
   extern entry B:ENG_NOUN
   link ENG_NOUN:A{} <synonym> ENG_NOUN:B{}

   #if C!=NULL
    #begin
     extern entry C:ENG_NOUN
     link ENG_NOUN:A{} <synonym> ENG_NOUN:C{}
     link ENG_NOUN:B{} <synonym> ENG_NOUN:C{}
    #end
   #endif

  #end

 syn( cat, puss )
 syn( cat, pussy )
 syn( cat, pussycat )
 syn( cat, kitty )
 syn( cop, policeman )
 syn( baby, child )
 syn( animal, beast )
 syn( joy, fun )

 syn( tv, television )
}
