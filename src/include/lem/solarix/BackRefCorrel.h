#if !defined BACK_REF_CORREL__H
#define BACK_REF_CORREL__H
#pragma once

 #include <lem/quantors.h>
 #include <lem/solarix/ViolationHandler.h>


 namespace lem
 {
  class OFormatter;
 }

 namespace Solarix
 {
  class SynGram;

  struct BackRefCorrel
  {
   bool affirmative;
   int id_coord0; // согласуема€ координата слева, у провер€емого узла

   lem::UCString name; // им€ маркировки
   int id_coord1; // координата у маркировки
   bool for_group; // например дл€ падежа - –ќƒ»“≈Ћ№Ќџ… и ѕј–“»“»¬ считать равными, так как они в одной группе

   ViolationHandler violation_handler; // штраф за нарушение согласовани€

   BackRefCorrel(void) : affirmative(true), id_coord0(UNKNOWN), id_coord1(-1), for_group(false) {}

   bool operator==( const BackRefCorrel &x ) const
   { return affirmative==x.affirmative &&
            name==x.name &&
            id_coord0==x.id_coord0 &&
            id_coord1==x.id_coord1 &&
            for_group==x.for_group &&
            violation_handler==x.violation_handler; }

   bool operator!=( const BackRefCorrel &x ) const
   { return affirmative!=x.affirmative ||
            name!=x.name ||
            id_coord0!=x.id_coord0 ||
            id_coord0!=x.id_coord0 ||
            for_group!=x.for_group ||
            violation_handler!=x.violation_handler; }

   void SaveTxt( lem::OFormatter &txt, SynGram &sg ) const;

   const ViolationHandler& GetViolationHandler() const { return violation_handler; }
  };

 }

#endif
