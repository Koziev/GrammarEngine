#if !defined CoordinatesInFile__H
 #define CoordinatesInFile__H

 #include <map>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/ucstring.h>
 #include <lem/solarix/CoordList.h>

 namespace Solarix
 {
  class CoordsInFile : public CoordList
  {
   private:
    Grammar *gram;
    lem::PtrCollect< GramCoord > coord;
 
    std::map< lem::UCString, int > name2id;

    GramCoord* AddNewCoord( GramCoord *cl );

   public:
    CoordsInFile( Grammar *_gg );
    virtual ~CoordsInFile() {}

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

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif

    void LoadBin( lem::Stream &bin );
  };
 }

#endif
