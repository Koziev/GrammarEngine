#if !defined RECO2_RPatternEnumerator__H
 #define RECO2_RPatternEnumerator__H
 
 #include <lem/noncopyable.h>

 namespace Reco2
 {
  class RPatternEnumerator : lem::NonCopyable
  {
   protected:
    RPatternEnumerator(void) {}

   public:
    virtual ~RPatternEnumerator(void) {}

    virtual bool Fetch(void)=0;
    virtual int GetId(void)=0;
  };
 }

#endif
