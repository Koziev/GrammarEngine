#if !defined RTransforms__H
 #define RTransforms__H

 #include <lem/noncopyable.h>
 #include <lem/containers.h>

 namespace Reco2
 {
  class RTransform;
  class RTransformEnumerator;

  class RTransforms : lem::NonCopyable
  {
   private:
    lem::MCollect<RTransform*> list;

   public:
    RTransforms(void);

    ~RTransforms(void);

    const RTransform& operator[]( int id ) const;
    const RTransform& operator[]( const lem::UCString &name ) const;
    RTransformEnumerator* Enumerate(void);
  };
 }

#endif
