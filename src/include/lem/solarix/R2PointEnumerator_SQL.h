#if !defined RECO2__RPointEnumerator_SQL__H
 #define RECO2__RPointEnumerator_SQL__H
 
 #include <lem/solarix/R2PointEnumerator.h>

 namespace Solarix
 {
  class LS_ResultSet;
 }

 namespace Reco2
 {
  class RPointEnumerator_SQL : public RPointEnumerator
  {
   private:
    Solarix::LS_ResultSet *rs;

   public:
    RPointEnumerator_SQL( Solarix::LS_ResultSet *_rs ) : rs(_rs) {}

    virtual ~RPointEnumerator_SQL(void);

    virtual bool Fetch(void);
    virtual int GetId(void);
  };
 }
#endif
