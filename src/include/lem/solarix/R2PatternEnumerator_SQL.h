#if !defined RECO2_RPatternEnumerator_SQL__H
 #define RECO2_RPatternEnumerator_SQL__H
 
 #include <lem/solarix/R2PatternEnumerator.h>

 namespace Solarix
 {
  class LS_ResultSet;
 }

 namespace Reco2
 {
  class RPatternEnumerator_SQL : public RPatternEnumerator
  {
   private:
    Solarix::LS_ResultSet *rs;

   public:
    RPatternEnumerator_SQL( Solarix::LS_ResultSet *_rs ) : rs(_rs) {}

    virtual ~RPatternEnumerator_SQL(void);

    virtual bool Fetch(void);
    virtual int GetId(void);
  };
 }

#endif
