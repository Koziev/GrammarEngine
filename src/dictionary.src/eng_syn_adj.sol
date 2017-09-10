// LC->29.12.2008

automat sg
{
 #define syn( A, B, C=NULL ) \
  #begin
   extern entry A:ENG_ADJECTIVE
   extern entry B:ENG_ADJECTIVE
   link ENG_ADJECTIVE:A{} <synonym> ENG_ADJECTIVE:B{}

   #if C!=NULL
    #begin
     extern entry C:ENG_ADJECTIVE
     link ENG_ADJECTIVE:A{} <synonym> ENG_ADJECTIVE:C{}
     link ENG_ADJECTIVE:B{} <synonym> ENG_ADJECTIVE:C{}
    #end
   #endif

  #end

 syn( joyful, funny )
 syn( joyful, merry )
 syn( joyful, jolly )
 syn( funny, jolly )
 syn( merry, jolly )

 syn( huge, tremendous )

}
