#ifndef SOL_CRITERIA_IN_FILE__H
#define SOL_CRITERIA_IN_FILE__H
#pragma once

 #include <lem/solarix/criterion.h>

 namespace Solarix
 {
  class CriteriaInFile : public Criteria_List
  {
   private:
    lem::Collect<Criterion> list;
    friend class CriterionEnumeratorInFile;

   public:
    CriteriaInFile(void) {}

    virtual ~CriteriaInFile(void) {}

    #if defined SOL_LOADTXT
    virtual void LoadTxt( const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile );
    #endif

    virtual int Find( const lem::UCString &name );
    virtual const Criterion& operator[]( int id );
    virtual const Criterion& operator[]( const lem::UCString &name );

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );

    virtual CriterionEnumerator* Enumerate(void);
  };

 } // end of namespace 'Solarix'

#endif
