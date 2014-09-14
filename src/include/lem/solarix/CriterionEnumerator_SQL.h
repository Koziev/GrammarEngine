#ifndef CriterionEnumerator_SQL__H
#define CriterionEnumerator_SQL__H
#pragma once

 #include <lem/solarix/CriterionEnumerator.h>

 namespace Solarix
 {
  class CriteriaInStorage;
  class LS_ResultSet;

  class CriterionEnumerator_SQL : public CriterionEnumerator
  {
   private:
    LS_ResultSet *rs;
    CriteriaInStorage *db;

   public:
    CriterionEnumerator_SQL( LS_ResultSet *_rs, CriteriaInStorage *_db );

    virtual ~CriterionEnumerator_SQL(void);

    virtual bool Fetch(void);
    virtual int GetId(void);
    virtual const Criterion& GetItem(void);
  };
 }

#endif
