
#define begin( verb, transitive=NULL ) \
#begin

 omonym add Глагол:verb{}
 omonym add Инфинитив:verb{}

 #if transitive==NULL
  #begin
   entry verb : ИНФИНИТИВ { ВИД:НЕСОВЕРШ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
   entry verb : ИНФИНИТИВ { ВИД:СОВЕРШ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
  #end  
 #else
  #begin
  entry verb : ИНФИНИТИВ { ВИД:НЕСОВЕРШ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:transitive }
  entry verb : ИНФИНИТИВ { ВИД:СОВЕРШ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:transitive }
  #end
 #endif
 
 link ИНФИНИТИВ:verb { ВИД:НЕСОВЕРШ } <в_сов> ИНФИНИТИВ:verb{ ВИД:СОВЕРШ }
 link ИНФИНИТИВ:verb { ВИД:СОВЕРШ } <в_несов> ИНФИНИТИВ:verb{ ВИД:НЕСОВЕРШ }
#end

#define end( verb ) \
#begin
 omonym remove Глагол:verb{}
 omonym remove Инфинитив:verb{}
#end 



#define нач_гл( verb ) omonym add Глагол:verb{}
#define кон_гл( verb ) omonym remove Глагол:verb{}



#define инф( verb, transitive=NULL ) \
#begin

 omonym add Инфинитив:verb{}

 #if transitive==NULL
  #begin
   entry verb : ИНФИНИТИВ { ВИД:НЕСОВЕРШ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
   entry verb : ИНФИНИТИВ { ВИД:СОВЕРШ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
  #end  
 #else
  #begin
  entry verb : ИНФИНИТИВ { ВИД:НЕСОВЕРШ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:transitive }
  entry verb : ИНФИНИТИВ { ВИД:СОВЕРШ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:transitive }
  #end
 #endif
 
 link ИНФИНИТИВ:verb { ВИД:НЕСОВЕРШ } <в_сов> ИНФИНИТИВ:verb{ ВИД:СОВЕРШ }
 link ИНФИНИТИВ:verb { ВИД:СОВЕРШ } <в_несов> ИНФИНИТИВ:verb{ ВИД:НЕСОВЕРШ }
 
 omonym remove Инфинитив:verb{}
 
#end



#define сов2несов( сов, несов ) link ИНФИНИТИВ:сов { ВИД:СОВЕРШ } <в_несов> ИНФИНИТИВ:несов{ ВИД:НЕСОВЕРШ }



#define v2inf(verb) \
#begin
 link Глагол : verb { вид:несоверш }  <в_инфинитив> ИНФИНИТИВ : verb { вид:несоверш }
 link Глагол : verb { вид:соверш }  <в_инфинитив> ИНФИНИТИВ : verb { вид:соверш }
#end

#define complete(verb) \
#begin
 omonym remove Глагол:verb{}
 omonym remove Инфинитив:verb{}
#end


#define v2(                   \
           Name, ПадежВал,    \
           F1, F2,            \
           F3, F4,            \
           F5, F6,            \
           F7, F8, F9, F10,   \
           F11,               \
           F12, F13           \
          )                   \
#begin

 begin(Name,ПадежВал)

 VEntry( Name, СОВЕРШ,
         F1, F2,
         F3, F4,
         F5, F6,
         F7, F8, F9, F10,
         F11, F12, ? ) 

 VEntry( Name, НЕСОВЕРШ,
         F1, F2,
         F3, F4,
         F5, F6,
         F7, F8, F9, F10,
         F11, F12, ? ) 

 v2inf(Name)
 complete(Name)
 
#end		  

#define овать( Name, ПадежВал=NULL ) \
#begin

 omonym add Инфинитив:Name{}

 #if ПадежВал==NULL
  #begin
   entry Name : ИНФИНИТИВ { ВИД:НЕСОВЕРШ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
   entry Name : ИНФИНИТИВ { ВИД:СОВЕРШ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
  #end  
 #else
  #begin
  entry Name : ИНФИНИТИВ { ВИД:НЕСОВЕРШ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ПадежВал }
  entry Name : ИНФИНИТИВ { ВИД:СОВЕРШ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ПадежВал }
  #end
 #endif
 
 link ИНФИНИТИВ:Name { ВИД:НЕСОВЕРШ } <в_сов> ИНФИНИТИВ:Name{ ВИД:СОВЕРШ }
 link ИНФИНИТИВ:Name { ВИД:СОВЕРШ } <в_несов> ИНФИНИТИВ:Name{ ВИД:НЕСОВЕРШ }
 
 omonym remove Инфинитив:Name{}
 
 нач_гл(Name)
 entry Name : Глагол { paradigm Глагол_6011 }
 entry Name : Глагол { paradigm Глагол_7031 }
 v2inf(Name)
 кон_гл(Name)
 
#end		  


#define оваться( Name, ПадежВал=NULL ) \
#begin

 begin(Name,(ПадежВал))

 entry Name : ГЛАГОЛ { paradigm Глагол_6035 }
 entry Name : ГЛАГОЛ { paradigm Глагол_7052 }
 
 v2inf(Name)
 complete(Name)
 
#end		  
