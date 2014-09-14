#ifndef SOL_CRITERIA_IN_STORAGE__H
#define SOL_CRITERIA_IN_STORAGE__H
#pragma once

 #include <map>
 #include <lem/process.h>
 #include <lem/solarix/criterion.h>
 #include <lem/ptr_container.h>

 namespace Solarix
 {
  class CriteriaStorage;

  class CriteriaInStorage : public Criteria_List
  {
   private:
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif
    
    CriteriaStorage *storage;
    std::map< lem::UCString, int > name2id;
    std::map< int, const Criterion* > id2x;
    lem::PtrCollect<Criterion> list;

   public:
    CriteriaInStorage(void);
   
    void Connect( CriteriaStorage *_storage );

    virtual ~CriteriaInStorage(void) {}

    #if defined SOL_LOADTXT
    void LoadTxt( const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile );
    #endif

    int Find( const lem::UCString &name );
    const Criterion& operator[]( int id );
    const Criterion& operator[]( const lem::UCString &name );

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    virtual CriterionEnumerator* Enumerate(void);
  };
 } // end of namespace 'Solarix'

#endif
