#if !defined SOL_ALPHABETS__H
 #define SOL_ALPHABETS__H

 #include <lem/noncopyable.h>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/RWULock.h>

 namespace lem 
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class AlphabetEnumerator;
  class Alphabet;
  class AlphabetStorage;
  class Dictionary;

  class Alphabets : lem::NonCopyable
  {
   private:
    AlphabetStorage *storage;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs, cs_count;
    #endif

    lem::MCollect<Alphabet*> alphabets;
    std::map< lem::UCString, int > name2id;
    std::map< int, const Alphabet* > id2alphabet;
    lem::Process::InterlockedInt a_count;

   public: 
    Alphabets(void);

    ~Alphabets(void);

    void Connect( AlphabetStorage *_storage );

    int Count(void);
    AlphabetEnumerator* List(void);
    const Alphabet& operator[]( int id );
    int Find( const lem::UCString &name );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( lem::Iridium::Macro_Parser &txtfile, Solarix::Dictionary &dict );
    #endif
  };
 }

#endif
