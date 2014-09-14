#if !defined ExactWordEntryLocator__H
 #define ExactWordEntryLocator__H

 #include <lem/noncopyable.h>
 #include <lem/solarix/coord_pair.h>


 namespace lem
 {
  namespace Iridium { class Macro_Parser; }
 }

 namespace Solarix
 {
  class SynGram;
  class SG_Entry;

  struct ExactWordEntryLocator : lem::NonCopyable
  {
   Solarix::CP_Array pairs;
   lem::UCString aux_type;
   lem::UCString aux_value;

   #if defined SOL_LOADTXT
   void LoadTxt( Macro_Parser &txtfile, SynGram &sg );
   void LoadAuxSelector( Macro_Parser &txtfile, SynGram &sg );
   #endif

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
   bool Empty(void) const;
   bool HasAuxSelector(void) const { return !aux_type.empty(); }

   bool Check( const SG_Entry & e, SynGram & sg ) const;

   void Print( lem::OFormatter & to, SynGram & sg ) const;
  };
 }

#endif
