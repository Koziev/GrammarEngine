#if !defined SG_Coordinates__H
 #define SG_Coordinates__H

 #include <map>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/ucstring.h>
 #include <lem/solarix/coordinate.h>
 #include <lem/solarix/CoordList.h>

 namespace lem
 {
  class UCString;
 }

 namespace Solarix
 {
  class LexiconStorage;
  class SynGram;

  class SG_Coordinates : public CoordList
  {
   private:
    SynGram *sg;
    LexiconStorage *db;

    lem::PtrCollect< GramCoord > coord_ptr;
    lem::MCollect<int> coord_id;
 
    std::map< int /*id*/, int/*index*/ > id2coord;
    std::map< lem::UCString, int > name2id;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif

    void AddNewCoord( GramCoord *new_coord, bool IsRealized );
    GramCoord* Get( int id );
    int Id2Index( int id );

   public:
    SG_Coordinates( SynGram *_sg );
    virtual ~SG_Coordinates() {}

    void Connect( LexiconStorage *_db );

    virtual const GramCoord& operator[]( int id );
    virtual GramCoord& GetCoord( int id );

    virtual int Find( const lem::UCString &name );
    virtual int Count(void);

    virtual CoordEnumerator* Enumerate(void);

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual GramCoord* LoadTxt(
                               lem::Iridium::Macro_Parser &txtfile,
                               bool IsRealized
                              );
    #endif
  };
 }

#endif
