#if !defined RTransformEnumerator__H
 #define RTransformEnumerator__H

 #include <lem/noncopyable.h>
 #include <lem/containers.h>

 namespace Reco2
 { 
  class RTransform;
  class RTransformEnumerator : lem::NonCopyable
  {
   private:
    lem::MCollect<RTransform*> &list;
    int i;

   public:
    RTransformEnumerator( lem::MCollect<RTransform*> &_list );
    virtual ~RTransformEnumerator(void) {}

    virtual bool Fetch(void);
    virtual const RTransform& GetItem(void);
  };

 }

#endif
