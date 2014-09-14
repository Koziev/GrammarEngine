#if !defined RECO2__RWordEnumerator__H
 #define RECO2__RWordEnumerator__H
 
 #include <lem/noncopyable.h>

 namespace Reco2
 {
  class RWordEnumerator : lem::NonCopyable
  {
   protected:
    RWordEnumerator(void) {}

   public:
    virtual ~RWordEnumerator(void) {}

    virtual bool Fetch(void)=0;
    virtual int GetId(void)=0;
  };
 }
#endif
