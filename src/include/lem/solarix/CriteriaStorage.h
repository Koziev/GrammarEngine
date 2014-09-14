#ifndef SOL_CRITERIA_STORAGE__H
#define SOL_CRITERIA_STORAGE__H
#pragma once

 #include <lem/noncopyable.h>

 namespace lem
 {
  class UCString;
 }

 namespace Solarix
 {
  class LS_ResultSet;
  class Criterion;
  
  class CriteriaStorage : lem::NonCopyable
  {
   protected:
    CriteriaStorage(void) {}

   public:
    virtual ~CriteriaStorage(void) {}

    virtual int FindCriterion( const lem::UCString & name )=0;
    virtual int StoreCriterion( const Criterion &x )=0;
    virtual Criterion* GetCriterion( int id )=0;
    virtual LS_ResultSet* EnumerateCriteria(void)=0;
  };
 }

#endif
