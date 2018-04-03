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

    virtual ~CriterionEnumeratorInFile() {}

    virtual bool Fetch() override;
    virtual int GetId() override;
    virtual const Criterion& GetItem() override;
  };
 }

#endif
