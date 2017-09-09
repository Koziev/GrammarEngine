#define Adj_5015( Name, Noun=NULL ) \
 #begin
  Name : ПРИЛАГАТЕЛЬНОЕ { paradigm Прил_5015 }
  
   #if Noun!=NULL
    #begin
     extern entry Noun : СУЩЕСТВИТЕЛЬНОЕ
     link СУЩЕСТВИТЕЛЬНОЕ:Noun {} <в_прил> ПРИЛАГАТЕЛЬНОЕ:Name{}
     link ПРИЛАГАТЕЛЬНОЕ:Name {} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:Noun{}   
    #end
   #endif 
 #end
 
#define Adj_5035( Name ) Name : ПРИЛАГАТЕЛЬНОЕ { paradigm Прил_5035 }

#define antonyms( A ) \
 #begin
  extern entry A : ПРИЛАГАТЕЛЬНОЕ
  extern entry НЕ##A : ПРИЛАГАТЕЛЬНОЕ
  link ПРИЛАГАТЕЛЬНОЕ:A{} <antonym> ПРИЛАГАТЕЛЬНОЕ:НЕ##A{}
 #end
