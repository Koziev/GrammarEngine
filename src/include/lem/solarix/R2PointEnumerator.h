#if !defined RECO2_RPOINTENUMERATOR__H
 #define RECO2_RPOINTENUMERATOR__H

 #include <lem/noncopyable.h>

 namespace Reco2
 {
  class RPoints;

  class RPointEnumerator : lem::NonCopyable
  {
   protected:
    RPointEnumerator(void) {}

   public:
    virtual ~RPointEnumerator(void) {}
    virtual bool Fetch(void)=0;
    virtual int GetId(void)=0;
  };
 }
#endif
