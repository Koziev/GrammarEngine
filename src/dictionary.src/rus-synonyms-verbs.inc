 #define s2( A, B1 ) \
  #begin
   link ИНФИНИТИВ:A{} <synonym> ИНФИНИТИВ:B1{}
  #end

 #define s2_perfect( A, B1 ) \
  #begin
   link ИНФИНИТИВ:A{ВИД:СОВЕРШ} <synonym> ИНФИНИТИВ:B1{ВИД:СОВЕРШ}
  #end

 #define s2_imperfect( A, B1 ) \
  #begin
   link ИНФИНИТИВ:A{ВИД:НЕСОВЕРШ} <synonym> ИНФИНИТИВ:B1{ВИД:НЕСОВЕРШ}
  #end



 #define Synonym( A, B1, B2=NULL, B3=NULL, B4=NULL, B5=NULL, B6=NULL, B7=NULL, B8=NULL, B9=NULL, B10=NULL, B11=NULL, B12=NULL, B13=NULL, B14=NULL, B15=NULL ) \
  #begin

   s2(A,B1)            

   #if B15!=NULL
    #begin
    s2(A,B15)  
    s2(B1,B15)
    s2(B2,B15)
    s2(B3,B15)
    s2(B4,B15)
    s2(B5,B15)
    s2(B6,B15)
    s2(B7,B15)
    s2(B8,B15)
    s2(B9,B15)
    s2(B10,B15)
    s2(B11,B15)
    s2(B12,B15)
    s2(B13,B15)
    s2(B14,B15)
    #end 
   #endif
   
   #if B14!=NULL
    #begin
     s2(A,B14)  
     s2(B1,B14) 
     s2(B2,B14) 
     s2(B3,B14) 
     s2(B4,B14) 
     s2(B5,B14) 
     s2(B6,B14) 
     s2(B7,B14) 
     s2(B8,B14) 
     s2(B9,B14) 
     s2(B10,B14)
     s2(B11,B14)
     s2(B12,B14)
     s2(B13,B14)
    #end
   #endif
   
   #if B13!=NULL
    #begin
   s2(A,B13)  
   s2(B1,B13) 
   s2(B2,B13) 
   s2(B3,B13) 
   s2(B4,B13) 
   s2(B5,B13) 
   s2(B6,B13) 
   s2(B7,B13) 
   s2(B8,B13) 
   s2(B9,B13) 
   s2(B10,B13)
   s2(B11,B13)
   s2(B12,B13)
    #end
   #endif
   
   #if B12!=NULL
    #begin
   s2(A,B12)  
   s2(B1,B12) 
   s2(B2,B12) 
   s2(B3,B12) 
   s2(B4,B12) 
   s2(B5,B12) 
   s2(B6,B12) 
   s2(B7,B12) 
   s2(B8,B12) 
   s2(B9,B12) 
   s2(B10,B12)
   s2(B11,B12)
    #end
   #endif
   
   #if B11!=NULL
    #begin
   s2(A,B11)  
   s2(B1,B11) 
   s2(B2,B11) 
   s2(B3,B11) 
   s2(B4,B11) 
   s2(B5,B11) 
   s2(B6,B11) 
   s2(B7,B11) 
   s2(B8,B11) 
   s2(B9,B11) 
   s2(B10,B11)
    #end
   #endif
   
   #if B10!=NULL
    #begin
   s2(A,B10) 
   s2(B1,B10)
   s2(B2,B10)
   s2(B3,B10)
   s2(B4,B10)
   s2(B5,B10)
   s2(B6,B10)
   s2(B7,B10)
   s2(B8,B10)
   s2(B9,B10)
    #end
   #endif
   
   #if B9!=NULL
    #begin
   s2(A,B9) 
   s2(B1,B9)
   s2(B2,B9)
   s2(B3,B9)
   s2(B4,B9)
   s2(B5,B9)
   s2(B6,B9)
   s2(B7,B9)
   s2(B8,B9)
    #end
   #endif
   
   #if B8!=NULL
    #begin
   s2(A,B8) 
   s2(B1,B8)
   s2(B2,B8)
   s2(B3,B8)
   s2(B4,B8)
   s2(B5,B8)
   s2(B6,B8)
   s2(B7,B8)
    #end
   #endif
   
   #if B7!=NULL
    #begin
   s2(A,B7) 
   s2(B1,B7)
   s2(B2,B7)
   s2(B3,B7)
   s2(B4,B7)
   s2(B5,B7)
   s2(B6,B7)
    #end
   #endif
   
   #if B6!=NULL
    #begin
   s2(A,B6) 
   s2(B1,B6)
   s2(B2,B6)
   s2(B3,B6)
   s2(B4,B6)
   s2(B5,B6)
    #end
   #endif
   
   #if B5!=NULL
    #begin
   s2(A,B5) 
   s2(B1,B5)
   s2(B2,B5)
   s2(B3,B5)
   s2(B4,B5)
    #end
   #endif
   
   #if B4!=NULL
    #begin
   s2(A,B4) 
   s2(B1,B4)
   s2(B2,B4)
   s2(B3,B4)
    #end
   #endif
   
   
   #if B3!=NULL
    #begin
   s2(A,B3) 
   s2(B1,B3)
   s2(B2,B3)
    #end
   #endif
   
   #if B2!=NULL
    #begin
   s2(A,B2) 
   s2(B1,B2)
    #end
   #endif

 #end





 #define Imperfect( A, B1, B2=NULL, B3=NULL, B4=NULL, B5=NULL, B6=NULL, B7=NULL, B8=NULL, B9=NULL, B10=NULL, B11=NULL, B12=NULL, B13=NULL, B14=NULL, B15=NULL ) \
  #begin

   s2_imperfect(A,B1)            

   #if B15!=NULL
    #begin
    s2_imperfect(A,B15)  
    s2_imperfect(B1,B15)
    s2_imperfect(B2,B15)
    s2_imperfect(B3,B15)
    s2_imperfect(B4,B15)
    s2_imperfect(B5,B15)
    s2_imperfect(B6,B15)
    s2_imperfect(B7,B15)
    s2_imperfect(B8,B15)
    s2_imperfect(B9,B15)
    s2_imperfect(B10,B15)
    s2_imperfect(B11,B15)
    s2_imperfect(B12,B15)
    s2_imperfect(B13,B15)
    s2_imperfect(B14,B15)
    #end 
   #endif
   
   #if B14!=NULL
    #begin
     s2_imperfect(A,B14)  
     s2_imperfect(B1,B14) 
     s2_imperfect(B2,B14) 
     s2_imperfect(B3,B14) 
     s2_imperfect(B4,B14) 
     s2_imperfect(B5,B14) 
     s2_imperfect(B6,B14) 
     s2_imperfect(B7,B14) 
     s2_imperfect(B8,B14) 
     s2_imperfect(B9,B14) 
     s2_imperfect(B10,B14)
     s2_imperfect(B11,B14)
     s2_imperfect(B12,B14)
     s2_imperfect(B13,B14)
    #end
   #endif
   
   #if B13!=NULL
    #begin
   s2_imperfect(A,B13)  
   s2_imperfect(B1,B13) 
   s2_imperfect(B2,B13) 
   s2_imperfect(B3,B13) 
   s2_imperfect(B4,B13) 
   s2_imperfect(B5,B13) 
   s2_imperfect(B6,B13) 
   s2_imperfect(B7,B13) 
   s2_imperfect(B8,B13) 
   s2_imperfect(B9,B13) 
   s2_imperfect(B10,B13)
   s2_imperfect(B11,B13)
   s2_imperfect(B12,B13)
    #end
   #endif
   
   #if B12!=NULL
    #begin
   s2_imperfect(A,B12)  
   s2_imperfect(B1,B12) 
   s2_imperfect(B2,B12) 
   s2_imperfect(B3,B12) 
   s2_imperfect(B4,B12) 
   s2_imperfect(B5,B12) 
   s2_imperfect(B6,B12) 
   s2_imperfect(B7,B12) 
   s2_imperfect(B8,B12) 
   s2_imperfect(B9,B12) 
   s2_imperfect(B10,B12)
   s2_imperfect(B11,B12)
    #end
   #endif
   
   #if B11!=NULL
    #begin
   s2_imperfect(A,B11)  
   s2_imperfect(B1,B11) 
   s2_imperfect(B2,B11) 
   s2_imperfect(B3,B11) 
   s2_imperfect(B4,B11) 
   s2_imperfect(B5,B11) 
   s2_imperfect(B6,B11) 
   s2_imperfect(B7,B11) 
   s2_imperfect(B8,B11) 
   s2_imperfect(B9,B11) 
   s2_imperfect(B10,B11)
    #end
   #endif
   
   #if B10!=NULL
    #begin
   s2_imperfect(A,B10) 
   s2_imperfect(B1,B10)
   s2_imperfect(B2,B10)
   s2_imperfect(B3,B10)
   s2_imperfect(B4,B10)
   s2_imperfect(B5,B10)
   s2_imperfect(B6,B10)
   s2_imperfect(B7,B10)
   s2_imperfect(B8,B10)
   s2_imperfect(B9,B10)
    #end
   #endif
   
   #if B9!=NULL
    #begin
   s2_imperfect(A,B9) 
   s2_imperfect(B1,B9)
   s2_imperfect(B2,B9)
   s2_imperfect(B3,B9)
   s2_imperfect(B4,B9)
   s2_imperfect(B5,B9)
   s2_imperfect(B6,B9)
   s2_imperfect(B7,B9)
   s2_imperfect(B8,B9)
    #end
   #endif
   
   #if B8!=NULL
    #begin
   s2_imperfect(A,B8) 
   s2_imperfect(B1,B8)
   s2_imperfect(B2,B8)
   s2_imperfect(B3,B8)
   s2_imperfect(B4,B8)
   s2_imperfect(B5,B8)
   s2_imperfect(B6,B8)
   s2_imperfect(B7,B8)
    #end
   #endif
   
   #if B7!=NULL
    #begin
   s2_imperfect(A,B7) 
   s2_imperfect(B1,B7)
   s2_imperfect(B2,B7)
   s2_imperfect(B3,B7)
   s2_imperfect(B4,B7)
   s2_imperfect(B5,B7)
   s2_imperfect(B6,B7)
    #end
   #endif
   
   #if B6!=NULL
    #begin
   s2_imperfect(A,B6) 
   s2_imperfect(B1,B6)
   s2_imperfect(B2,B6)
   s2_imperfect(B3,B6)
   s2_imperfect(B4,B6)
   s2_imperfect(B5,B6)
    #end
   #endif
   
   #if B5!=NULL
    #begin
   s2_imperfect(A,B5) 
   s2_imperfect(B1,B5)
   s2_imperfect(B2,B5)
   s2_imperfect(B3,B5)
   s2_imperfect(B4,B5)
    #end
   #endif
   
   #if B4!=NULL
    #begin
   s2_imperfect(A,B4) 
   s2_imperfect(B1,B4)
   s2_imperfect(B2,B4)
   s2_imperfect(B3,B4)
    #end
   #endif
   
   
   #if B3!=NULL
    #begin
   s2_imperfect(A,B3) 
   s2_imperfect(B1,B3)
   s2_imperfect(B2,B3)
    #end
   #endif
   
   #if B2!=NULL
    #begin
   s2_imperfect(A,B2) 
   s2_imperfect(B1,B2)
    #end
   #endif

 #end


 #define Perfect( A, B1, B2=NULL, B3=NULL, B4=NULL, B5=NULL, B6=NULL, B7=NULL, B8=NULL, B9=NULL, B10=NULL, B11=NULL, B12=NULL, B13=NULL, B14=NULL, B15=NULL ) \
  #begin

   s2_perfect(A,B1)            

   #if B15!=NULL
    #begin
    s2_perfect(A,B15)  
    s2_perfect(B1,B15)
    s2_perfect(B2,B15)
    s2_perfect(B3,B15)
    s2_perfect(B4,B15)
    s2_perfect(B5,B15)
    s2_perfect(B6,B15)
    s2_perfect(B7,B15)
    s2_perfect(B8,B15)
    s2_perfect(B9,B15)
    s2_perfect(B10,B15)
    s2_perfect(B11,B15)
    s2_perfect(B12,B15)
    s2_perfect(B13,B15)
    s2_perfect(B14,B15)
    #end 
   #endif
   
   #if B14!=NULL
    #begin
     s2_perfect(A,B14)  
     s2_perfect(B1,B14) 
     s2_perfect(B2,B14) 
     s2_perfect(B3,B14) 
     s2_perfect(B4,B14) 
     s2_perfect(B5,B14) 
     s2_perfect(B6,B14) 
     s2_perfect(B7,B14) 
     s2_perfect(B8,B14) 
     s2_perfect(B9,B14) 
     s2_perfect(B10,B14)
     s2_perfect(B11,B14)
     s2_perfect(B12,B14)
     s2_perfect(B13,B14)
    #end
   #endif
   
   #if B13!=NULL
    #begin
   s2_perfect(A,B13)  
   s2_perfect(B1,B13) 
   s2_perfect(B2,B13) 
   s2_perfect(B3,B13) 
   s2_perfect(B4,B13) 
   s2_perfect(B5,B13) 
   s2_perfect(B6,B13) 
   s2_perfect(B7,B13) 
   s2_perfect(B8,B13) 
   s2_perfect(B9,B13) 
   s2_perfect(B10,B13)
   s2_perfect(B11,B13)
   s2_perfect(B12,B13)
    #end
   #endif
   
   #if B12!=NULL
    #begin
   s2_perfect(A,B12)  
   s2_perfect(B1,B12) 
   s2_perfect(B2,B12) 
   s2_perfect(B3,B12) 
   s2_perfect(B4,B12) 
   s2_perfect(B5,B12) 
   s2_perfect(B6,B12) 
   s2_perfect(B7,B12) 
   s2_perfect(B8,B12) 
   s2_perfect(B9,B12) 
   s2_perfect(B10,B12)
   s2_perfect(B11,B12)
    #end
   #endif
   
   #if B11!=NULL
    #begin
   s2_perfect(A,B11)  
   s2_perfect(B1,B11) 
   s2_perfect(B2,B11) 
   s2_perfect(B3,B11) 
   s2_perfect(B4,B11) 
   s2_perfect(B5,B11) 
   s2_perfect(B6,B11) 
   s2_perfect(B7,B11) 
   s2_perfect(B8,B11) 
   s2_perfect(B9,B11) 
   s2_perfect(B10,B11)
    #end
   #endif
   
   #if B10!=NULL
    #begin
   s2_perfect(A,B10) 
   s2_perfect(B1,B10)
   s2_perfect(B2,B10)
   s2_perfect(B3,B10)
   s2_perfect(B4,B10)
   s2_perfect(B5,B10)
   s2_perfect(B6,B10)
   s2_perfect(B7,B10)
   s2_perfect(B8,B10)
   s2_perfect(B9,B10)
    #end
   #endif
   
   #if B9!=NULL
    #begin
   s2_perfect(A,B9) 
   s2_perfect(B1,B9)
   s2_perfect(B2,B9)
   s2_perfect(B3,B9)
   s2_perfect(B4,B9)
   s2_perfect(B5,B9)
   s2_perfect(B6,B9)
   s2_perfect(B7,B9)
   s2_perfect(B8,B9)
    #end
   #endif
   
   #if B8!=NULL
    #begin
   s2_perfect(A,B8) 
   s2_perfect(B1,B8)
   s2_perfect(B2,B8)
   s2_perfect(B3,B8)
   s2_perfect(B4,B8)
   s2_perfect(B5,B8)
   s2_perfect(B6,B8)
   s2_perfect(B7,B8)
    #end
   #endif
   
   #if B7!=NULL
    #begin
   s2_perfect(A,B7) 
   s2_perfect(B1,B7)
   s2_perfect(B2,B7)
   s2_perfect(B3,B7)
   s2_perfect(B4,B7)
   s2_perfect(B5,B7)
   s2_perfect(B6,B7)
    #end
   #endif
   
   #if B6!=NULL
    #begin
   s2_perfect(A,B6) 
   s2_perfect(B1,B6)
   s2_perfect(B2,B6)
   s2_perfect(B3,B6)
   s2_perfect(B4,B6)
   s2_perfect(B5,B6)
    #end
   #endif
   
   #if B5!=NULL
    #begin
   s2_perfect(A,B5) 
   s2_perfect(B1,B5)
   s2_perfect(B2,B5)
   s2_perfect(B3,B5)
   s2_perfect(B4,B5)
    #end
   #endif
   
   #if B4!=NULL
    #begin
   s2_perfect(A,B4) 
   s2_perfect(B1,B4)
   s2_perfect(B2,B4)
   s2_perfect(B3,B4)
    #end
   #endif
   
   
   #if B3!=NULL
    #begin
   s2_perfect(A,B3) 
   s2_perfect(B1,B3)
   s2_perfect(B2,B3)
    #end
   #endif
   
   #if B2!=NULL
    #begin
   s2_perfect(A,B2) 
   s2_perfect(B1,B2)
    #end
   #endif

 #end





 #define Synonym0( Aspect, A, B, C=NULL ) \
  #begin
   extern entry A : ИНФИНИТИВ
   extern entry B : ИНФИНИТИВ

   #if Aspect==NULL
   link ИНФИНИТИВ:A{} <synonym> ИНФИНИТИВ:B{}
   #else
   link ИНФИНИТИВ:A{вид:Aspect} <synonym> ИНФИНИТИВ:B{вид:Aspect}
   #endif

   #if C!=NULL
    #begin
     extern entry C : ИНФИНИТИВ

     #if Aspect==NULL
      #begin
       link ИНФИНИТИВ:A{} <synonym> ИНФИНИТИВ:C{}
       link ИНФИНИТИВ:B{} <synonym> ИНФИНИТИВ:C{}
      #end
     #else
      #begin
       link ИНФИНИТИВ:A{вид:Aspect} <synonym> ИНФИНИТИВ:C{вид:Aspect}
       link ИНФИНИТИВ:B{вид:Aspect} <synonym> ИНФИНИТИВ:C{вид:Aspect}
      #end
     #endif
    #end
   #endif 

  #end
