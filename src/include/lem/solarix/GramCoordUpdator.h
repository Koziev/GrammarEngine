#if !defined GramCoordUpdator__H
 #define GramCoordUpdator__H

 #include <lem/noncopyable.h>

 namespace Solarix
 {

  class GramCoord;
  class GramCoordUpdator : lem::NonCopyable
  {
   public:
    GramCoordUpdator(void) {}
    virtual ~GramCoordUpdator(void) {}
    virtual void Update( GramCoord &x )=0;
  };
 }

#endif
