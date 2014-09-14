#ifndef CriterionEnumerator__H
#define CriterionEnumerator__H
#pragma once

 #include <lem/noncopyable.h>

 namespace Solarix
 {
  class Criterion;

  class CriterionEnumerator : lem::NonCopyable
  {
   protected:
    CriterionEnumerator(void) {}

   public:
    virtual ~CriterionEnumerator(void) {}

    virtual bool Fetch(void)=0;
    virtual int GetId(void)=0;
    virtual const Criterion& GetItem(void)=0;
  };
 }

#endif
