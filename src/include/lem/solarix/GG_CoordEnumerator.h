#if !defined GG_CoordEnumerator__H
 #define GG_CoordEnumerator__H

 #include <lem/solarix/CoordEnumerator.h>

 namespace Solarix
 {
  class GG_Coordinates;
  class LS_ResultSet;
  class AlphabetStorage;
  class Coordinate;

  class GG_CoordEnumerator : public CoordEnumerator
  {
   private:
    LS_ResultSet *rs;
    AlphabetStorage *db;
    GG_Coordinates *p;

   public:
    GG_CoordEnumerator( AlphabetStorage *_db, GG_Coordinates * _p );
    virtual ~GG_CoordEnumerator(void);

    virtual bool Fetch(void);
    virtual int GetId(void);
    virtual const GramCoord& GetItem(void);
  };
 }

#endif
