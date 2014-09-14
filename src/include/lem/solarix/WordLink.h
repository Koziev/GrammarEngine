#if !defined WordLink__H
 #define WordLink__H

 namespace Solarix
 {
  struct WordLink
  {
   int id, ekey1, ekey2, link_type;
 
   WordLink(void) : id(-1), ekey1(-1), ekey2(-1), link_type(-1) {}
  };
 }

#endif
