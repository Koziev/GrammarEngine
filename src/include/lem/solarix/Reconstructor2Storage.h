#if !defined Reconstructor2Storage__H
 #define Reconstructor2Storage__H

 #include <lem/ucstring.h>
 #include <lem/noncopyable.h>
 #include <lem/solarix/R2Utils.h>

 namespace Reco2
 {
  class RWordEnumerator;
  class RPatternEnumerator;
  class RPointEnumerator;

  class RPoint;
  class RPattern;

  class Reconstructor2Storage : lem::NonCopyable
  {
   protected:
    Reconstructor2Storage(void) {}
  
   public:
    virtual void BeginTx(void)=0;
    virtual void CommitTx(void)=0;

    virtual void CleanData(void)=0;

    virtual bool IsNGramUsed( int id_ngram, int order )=0;
    virtual void NGramIsUsed( int id_ngram, int order )=0;

    virtual int AddWord( const lem::UCString &word )=0;
    virtual int FindWord( const lem::UCString &word )=0;
    virtual lem::UCString GetWord( int id_word )=0;
    virtual RWordEnumerator* EnumerateWords(void)=0;

    virtual RPoint* AddPoint( int id_word, int weight )=0;
    virtual void Store( const RPoint &p )=0;
    virtual int FindPointByHeadword( int id_word )=0;
    virtual RPoint * GetPoint( int id )=0;
    virtual RPointEnumerator* EnumeratePoints(void)=0;
    virtual int CountPoints(void)=0;

    virtual void AddWord2Point( int id_word, int id_point )=0;
    virtual void MapWord2Points( int id_word, ints & id_points )=0;

    virtual void MapPoint2Patterns( int id_point, ints & id_patterns )=0;

    virtual int CountPatterns(void)=0;
    virtual RPattern * AddPattern( int _id_ngram, int _freq, const ints & _id_points )=0;
    virtual RPattern * GetPattern( int id )=0;
    virtual RPatternEnumerator* EnumeratePatterns(void)=0;
  };
 }
#endif
