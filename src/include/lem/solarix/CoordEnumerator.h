#if !defined CoordEnumerator__H
 #define CoordEnumerator__H

 #include <lem/noncopyable.h>

 namespace Solarix
 {
  class GramCoord;
  class CoordEnumerator : lem::NonCopyable
  {
   protected:
    CoordEnumerator(void) {}

   public:
    virtual ~CoordEnumerator(void) {}
    virtual bool Fetch(void)=0;
    virtual int GetId(void)=0;
    virtual const GramCoord& GetItem(void)=0;
  };
 }

#endif
