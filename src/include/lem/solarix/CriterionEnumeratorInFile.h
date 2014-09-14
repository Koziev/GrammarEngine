#ifndef SOL_CRITERIA_FILE__H
#define SOL_CRITERIA_FILE__H
#pragma once

 #include <lem/solarix/CriteriaInFile.h>
 #include <lem/solarix/CriterionEnumerator.h>

 namespace Solarix
 {
  class CriteriaInFile;
  class Criterion;

  class CriterionEnumeratorInFile : public CriterionEnumerator
  {
   private:
    const CriteriaInFile *criteria;
    int i;

   public:
    CriterionEnumeratorInFile( const CriteriaInFile *_criteria );

    virtual ~CriterionEnumeratorInFile(void) {}

    virtual bool Fetch(void);
    virtual int GetId(void);
    virtual const Criterion& GetItem(void);
  };
 }

#endif
