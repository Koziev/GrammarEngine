#if !defined CoordEnumeratorInFile__H
 #define CoordEnumeratorInFile__H

 #include <lem/solarix/CoordEnumerator.h>

 namespace Solarix
 {
  class Grammar;
  class CoordEnumeratorInFile : public CoordEnumerator
  {
   private:
    Grammar *gram;
    int i;
   
   public:
    CoordEnumeratorInFile( Grammar *_gg );
    virtual ~CoordEnumeratorInFile(void) {}
 
    virtual bool Fetch(void);
    virtual int GetId(void);
    virtual const GramCoord& GetItem(void);
  };
 }

#endif
