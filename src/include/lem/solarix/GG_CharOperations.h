#if !defined GG_CHAR_OPERATIONS__H
 #define GG_CHAR_OPERATIONS__H

 #include <lem/ucstring.h>
 #include <lem/containers.h>
 #include <lem/noncopyable.h>
 #include <lem/process.h>
 #include <lem/RWULock.h>
 #include <map>
 

 namespace Solarix
 {
  class AlphabetStorage;
  class GraphGram;
  class GG_CharOperation;
  class CharOperationEnumerator;

  class GG_CharOperations : lem::NonCopyable
  {
   private:
    AlphabetStorage * storage;
    GraphGram * gg;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs;
    #endif

    lem::MCollect< GG_CharOperation* > opers;
    std::map< lem::UCString, const GG_CharOperation *> name2oper;
    std::map< int, const GG_CharOperation *> id2oper;

    void Delete(void);
  
   public:
    GG_CharOperations( GraphGram * GG );
    ~GG_CharOperations(void);

    void Connect( AlphabetStorage * Storage );

    const GG_CharOperation* operator[]( const lem::UCString &name );
    const GG_CharOperation* operator[]( int id );

    CharOperationEnumerator* ListOperations(void);
  };
 }

#endif
