#if !defined ClassEnumerator__H
 #define ClassEnumerator__H

 #include <lem/noncopyable.h>

 namespace Solarix
 {
  class GramClass;
  class ClassEnumerator : lem::NonCopyable
  {
   protected:
    ClassEnumerator(void) {}

   public:
    virtual ~ClassEnumerator(void) {}
    virtual bool Fetch(void)=0;
    virtual int GetId(void)=0;
    virtual const GramClass& GetItem(void)=0;
  };
 }

#endif
