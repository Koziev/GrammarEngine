#if !defined SLOT_PROPERTIES__H
#define SLOT_PROPERTIES__H

namespace Solarix
{
 class SlotProperties
 {
  public:
   bool left, right, key, obligatory, multiple;

  public:
   SlotProperties();

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt(
                Dictionary &dict,
                lem::Iridium::Macro_Parser & txtfile
               );
   #endif

   bool IsOptional() const { return !obligatory; }
   bool IsObligatory() const { return obligatory; }
 };

}

#endif
