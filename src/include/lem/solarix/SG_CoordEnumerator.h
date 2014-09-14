#if !defined SG_CoordEnumerator__H
 #define SG_CoordEnumerator__H

 #include <lem/solarix/CoordEnumerator.h>

 namespace Solarix
 {
  class SG_Coordinates;
  class LS_ResultSet;
  class LexiconStorage;
  class Coordinate;

  class SG_CoordEnumerator : public CoordEnumerator
  {
   private:
    LS_ResultSet *rs;
    LexiconStorage *db;
    SG_Coordinates *p;

   public:
    SG_CoordEnumerator( LexiconStorage *_db, SG_Coordinates * _p );
    virtual ~SG_CoordEnumerator(void);

    virtual bool Fetch(void);
    virtual int GetId(void);
    virtual const GramCoord& GetItem(void);
  };
 }

#endif
