#if !defined SymbolClasses__H
 #define SymbolClasses__H

 #include <map>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/ucstring.h>
 #include <lem/solarix/ClassList.h>
 #include <lem/solarix/gram_class.h>

 namespace lem
 {
  class UCString;
 }

 namespace Solarix
 {
  class AlphabetStorage;
  class GraphGram;

  class SymbolClasses : public ClassList
  {
   private:
    AlphabetStorage *db;
    GraphGram *gg;

    lem::PtrCollect< GramClass > class_ptr;
    lem::MCollect<int> class_id;
 
    std::map< int /*id*/, int/*index*/ > id2class;
    std::map< lem::UCString, int > name2id;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif

    void AddNewClass( GramClass *new_class, bool IsRealized );
    GramClass* Get( int id );

   public:
    SymbolClasses( GraphGram *_sg );
    virtual ~SymbolClasses() {}

    void Connect( AlphabetStorage *_db );

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
