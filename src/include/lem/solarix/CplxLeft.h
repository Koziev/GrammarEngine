#if !defined CplxLeft__H
 #define CplxLeft__H

 namespace Solarix
 {

  struct CplxLeft
  {
   lem::UCString headword;
   int minlen, maxlen;
   CplxLeft(void) : minlen(0), maxlen(0) {}
  };

 }

#endif
