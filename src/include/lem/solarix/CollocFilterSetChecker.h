#if !defined CollocFilterSetChecker__H
 #define CollocFilterSetChecker__H

 namespace Solarix
 {

  struct CollocFilterSetChecker
  {
   lem::UCString set_name; // имя множества
   int set_type; // 0 - word_set, 1 - wordentry_set, 2 - wordform_set
   bool affirm; // 0 для отрицания
   
   CollocFilterSetChecker(void) : set_type(UNKNOWN), affirm(true) {}

   void SetWordSet(void) { set_type=0; }
   void SetWordEntrySet(void) { set_type=1; }
   void SetWordformSet(void) { set_type=2; }

   bool IsWordSet(void) const { return set_type==0; }
   bool IsWordEntrySet(void) const { return set_type==1; }
   bool IsWordformSet(void) const { return set_type==2; }
 
   bool Positive( bool x ) const { return affirm ? x : !x; }

   bool operator!=( const CollocFilterSetChecker & x ) const
   { return set_name!=x.set_name || set_type!=x.set_type || affirm!=x.affirm; }

   bool operator==( const CollocFilterSetChecker & x ) const
   { return set_name==x.set_name && set_type==x.set_type && affirm==x.affirm; }
  };

 }

#endif
