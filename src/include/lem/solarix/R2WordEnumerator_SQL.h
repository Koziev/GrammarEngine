#if !defined RECO2__RWordEnumerator_SQL__H
 #define RECO2__RWordEnumerator_SQL__H
 
 #include <lem/solarix/R2WordEnumerator.h>

 namespace Solarix
 {
  class LS_ResultSet;
 }

 namespace Reco2
 {
  class RWordEnumerator_SQL : public RWordEnumerator
  {
   private:
    Solarix::LS_ResultSet *rs;

   public:
    RWordEnumerator_SQL( Solarix::LS_ResultSet *_rs ) : rs(_rs) {}

    virtual ~RWordEnumerator_SQL(void);

    virtual bool Fetch(void);
    virtual int GetId(void);
  };
 }
#endif
