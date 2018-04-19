 #define дп( Name, Aspect, Verb=NULL ) \
 #begin
 entry Name : ДЕЕПРИЧАСТИЕ
  {
   ВИД:Aspect
  }

 #if Verb!=NULL
  #begin
   extern entry Verb : ИНФИНИТИВ    
   link ДЕЕПРИЧАСТИЕ:Name{ВИД:Aspect} <в_инфинитив> ИНФИНИТИВ:Verb{ ВИД:Aspect }

   tag ДЕЕПРИЧАСТИЕ:Name
   {
    ПЕРЕХОДНОСТЬ:<в_инфинитив>
    ПАДЕЖ:<в_инфинитив>
    МОДАЛЬНЫЙ:<в_инфинитив>
//    Глаг_Предл_Вал:<в_инфинитив>
   }

  #end
 #endif
 #end
