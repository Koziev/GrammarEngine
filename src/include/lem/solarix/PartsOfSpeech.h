#if !defined PartsOfSpeech__H
 #define PartsOfSpeech__H

 #include <map>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/ucstring.h>
 #include <lem/solarix/ClassList.h>
 #include <lem/solarix/PartOfSpeech.h>

 namespace lem
 {
  class UCString;
 }

 namespace Solarix
 {
  class LexiconStorage;
  class SynGram;

  class PartsOfSpeech : public ClassList
  {
   private:
    LexiconStorage *db;
    SynGram *sg;

    lem::PtrCollect< SG_Class > class_ptr;
    lem::MCollect<int> class_id;
 
    std::map< int /*id*/, int/*index*/ > id2class;
    std::map< lem::UCString, int > name2id;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif

    void AddNewClass( SG_Class *new_class, bool IsRealized );
    SG_Class* Get( int id );

   public:
    PartsOfSpeech( SynGram *_sg );
    virtual ~PartsOfSpeech() {}

    void Connect( LexiconStorage *_db );

    virtual const GramClass& operator[]( int id );
    virtual GramClass& GetClass( int id );

    virtual int Find( const lem::UCString &name );
    virtual int Count(void);

    virtual ClassEnumerator* Enumerate(void);

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual GramClass* LoadTxt(
                               lem::Iridium::Macro_Parser &txtfile,
                               bool IsRealized
                              );
    #endif
  };
 }

#endif
