#if !defined CoordList__H
 #define CoordList__H

 namespace lem
 {
  class UCString;
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class GramCoord;
  class Grammar;
  class CoordEnumerator;

  class CoordList
  {
   protected:
    CoordList(void) {}

   public:
    virtual ~CoordList() {}

    virtual const GramCoord& operator[]( int id )=0;
    virtual GramCoord& GetCoord( int id )=0;

    virtual int Find( const lem::UCString &name )=0;
    virtual int Count(void)=0;
    virtual CoordEnumerator* Enumerate(void)=0;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual GramCoord* LoadTxt(
                               lem::Iridium::Macro_Parser &txtfile,
                               bool IsRealized
                              )=0;
    #endif
  };
 }

#endif
