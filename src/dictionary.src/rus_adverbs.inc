// CD->05.10.1995
// LC->16.09.2013
// --------------

#define adv_comp(a) entry a : НАРЕЧИЕ { paradigm Нареч_Быстро }
#define adv_comp0(a) entry a : НАРЕЧИЕ { paradigm Нареч_Алогично }

 #define adv( f1, f2=NULL, f22=NULL, f23=NULL, f24=NULL, f25=NULL, f26=NULL ) \
  #begin
   #if f1==NULL && f2!=NULL
    #begin
    entry f2 : НАРЕЧИЕ
    {
     СТЕПЕНЬ:СРАВН { {f2} }
     #if f22!=NULL
     СТЕПЕНЬ:СРАВН { {f22} }
     #endif
     #if f23!=NULL
     СТЕПЕНЬ:СРАВН { {f23} }
     #endif
     #if f24!=NULL
     СТЕПЕНЬ:СРАВН { {f24} }
     #endif
     #if f25!=NULL
     СТЕПЕНЬ:СРАВН { {f25} }
     #endif
     #if f26!=NULL
     СТЕПЕНЬ:СРАВН { {f26} }
     #endif
    }
    #end  
   #endif

   #if f1!=NULL && f2!=NULL
    #begin
    entry f1 : НАРЕЧИЕ
    {
     СТЕПЕНЬ:АТРИБ { {f1}  }
     СТЕПЕНЬ:СРАВН { {f2}  }
     #if f22!=NULL
     СТЕПЕНЬ:СРАВН { {f22} }
     #endif
     #if f23!=NULL
     СТЕПЕНЬ:СРАВН { {f23} }
     #endif
     #if f24!=NULL
     СТЕПЕНЬ:СРАВН { {f24} }
     #endif
     #if f25!=NULL
     СТЕПЕНЬ:СРАВН { {f25} }
     #endif
     #if f26!=NULL
     СТЕПЕНЬ:СРАВН { {f26} }
     #endif
    }
    #end  
   #endif

   #if f2==NULL
    #begin
    entry f1 : НАРЕЧИЕ
    {
     СТЕПЕНЬ:АТРИБ { {f1} }
    }
    #end  
   #endif 
  #end

 // в нескольких исключительных случаях у наречий
 // есть превосходная степень 
 #define adv3( базовая, сравн, превосх ) \
  #begin
    #if базовая!=NULL
     entry базовая : НАРЕЧИЕ
    #else 
     #if сравн!=NULL
      entry сравн : НАРЕЧИЕ
     #else
      entry превосх : НАРЕЧИЕ
     #endif
    #endif 
    {
     #if базовая!=NULL 
     СТЕПЕНЬ:АТРИБ { базовая }
     #endif
     
     #if сравн!=NULL
     СТЕПЕНЬ:СРАВН { сравн }
     #endif
     
     #if превосх!=NULL
     СТЕПЕНЬ:ПРЕВОСХ { превосх }
     #endif
    }
  #end

 
 #define в_гл( adv, v, Aspect=NULL ) \
 #begin
  // для контроля опечаток объявим требования на присутствие этих словарных статей
  extern entry v : ИНФИНИТИВ    
  extern entry adv : НАРЕЧИЕ
  
  #if Aspect==NULL
   #begin
    link наречие:adv{} <в_инфинитив> инфинитив:v{}
    link инфинитив:v{} <в_наречие> наречие:adv{}
   #end
  #else   
   #begin
    link наречие:adv{} <в_инфинитив> инфинитив:v{ВИД:Aspect}
    link инфинитив:v{ВИД:Aspect} <в_наречие> наречие:adv{}
   #end
  #endif
  
 #end
 
 #define в_пр( adv, adj ) \
 #begin
  extern entry adj : ПРИЛАГАТЕЛЬНОЕ
  extern entry adv : НАРЕЧИЕ    
  link наречие:adv{} <в_прил> ПРИЛАГАТЕЛЬНОЕ:adj{}
  link ПРИЛАГАТЕЛЬНОЕ:adj{} <в_наречие> наречие:adv{}
 #end
 
