#if !defined ViolationHandler__H
#define ViolationHandler__H

namespace lem
{
 namespace Iridium
 {
  class Macro_Parser;
 }
}

namespace Solarix
{
 struct ViolationHandler
 {
  int violation_score; // штраф за нарушение условия

  ViolationHandler() : violation_score(0) {}

  #if defined SOL_COMPILER && defined SOL_LOADTXT
  void LoadTxt( lem::Iridium::Macro_Parser & txtfile );
  #endif

  bool HasFalseScore() const { return violation_score!=0; }
  int GetFalseScore() const { return violation_score; }

  inline bool operator==( const ViolationHandler & x ) const { return violation_score==x.violation_score; }
  inline bool operator!=( const ViolationHandler & x ) const { return violation_score!=x.violation_score; }
 };
}

#endif
