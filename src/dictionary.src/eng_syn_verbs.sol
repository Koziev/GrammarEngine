// LC->01.01.2009

automat sg
{
 #define syn( A, B ) \
  #begin
   extern entry A:ENG_VERB
   extern entry B:ENG_VERB
   link ENG_VERB:A{} <synonym> ENG_VERB:B{}
   link ENG_VERB:B{} <synonym> ENG_VERB:A{}
  #end


// syn( "get in", "come in" )
// syn( "get back", "come back" )

// syn( "surrender", "give up" )
 syn( "ask", "inquire" )

}
