#if !defined SOL_NGRAMFILTER__H
 #define SOL_NGRAMFILTER__H

 #include <lem/solarix/NGramsCollectors.h>

 namespace Solarix
 {
  // пропускает N-грамму на регистрацию, если в ее составе есть хоть одно
  // слово из белого списка.
  class NGramFilter_AnyInWhiteList : public NGramFilter
  {
   private:
    std::set<lem::UCString> words;
    std::set<int> id_words;

    NGramFilter_AnyInWhiteList(void) {}

   public:
    NGramFilter_AnyInWhiteList( const lem::Path &filename );

    virtual NGramFilter* Clone(void) const;

    virtual void AttachCollector( RawNGramsCollector *collector );

    virtual bool Probe( RawNGramsCollector *collector, int ie1 );
    virtual bool Probe( RawNGramsCollector *collector, int ie1, int ie2 );
    virtual bool Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3 );
    virtual bool Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3, int ie4 );
    virtual bool Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3, int ie4, int ie5 );
  };

 }
#endif
