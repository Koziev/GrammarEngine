#if !defined RECO2_RWORDS__H
 #define RECO2_RWORDS__H

 #include <lem/noncopyable.h>
 #include <lem/process.h>
 #include <lem/ucstring.h>

 namespace Reco2
 {
  class RWordEnumerator;
  class Reconstructor2Storage;

  class RWords : lem::NonCopyable
  {
   private:
    Reconstructor2Storage *db;

    // êýø
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif
    std::map<lem::UCString,int> words;
    std::map<int,lem::UCString> id2word;

   public:
    RWords(void);

    virtual void Connect( Reconstructor2Storage *_db );
    virtual int Register( const lem::UCString & word );
    virtual int Find( const lem::UCString & word );
    virtual const lem::UCString& operator[]( int id );
    virtual RWordEnumerator* Enumerate(void);
  };
 }
#endif
