#if !defined GramCoordUpdator_DB__H
 #define GramCoordUpdator_DB__H

 #include <lem/solarix/GramCoordUpdator.h>

 namespace Solarix
 {
  class LexiconStorage;
  class GramCoordUpdator_DB : public GramCoordUpdator
  {
   private:
    LexiconStorage *db;

   public:
    GramCoordUpdator_DB( LexiconStorage*_db );
    virtual ~GramCoordUpdator_DB(void) {}
    virtual void Update( GramCoord &x );
  };

 }

#endif
