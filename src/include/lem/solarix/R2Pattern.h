#if !defined RECO2_RPattern__H
 #define RECO2_RPattern__H

 #include <lem/noncopyable.h>
 #include <lem/solarix/R2Utils.h>

 namespace Reco2
 {
  struct PatternMatching;
  class Reconstructor2;
  struct MatchContext;

  class RPattern : lem::NonCopyable
  {
   private:
    int id;
    int id_ngram;
    int freq;
    ints id_points;

   public: 
    RPattern(void);
    RPattern( int _id, int _id_ngram, int _freq, const ints & _id_points );

    ~RPattern(void);

    int GetId(void) const { return id; }

    int CountPoints(void) const { return CastSizeToInt(id_points.size()); }
    int GetPoint( int i ) const { return id_points[i]; }
    int GetFreq() const { return freq; }
 
    PatternMatching* Match(
                           Reconstructor2 &reco,
                           int pos0,
                           int len,
                           MatchContext &ctx,
                           int ipoint0
                          ) const;

    void Produce(
                 Reconstructor2 &reco,
                 int pos0,
                 int len,
                 MatchContext &ctx,
                 PatternMatching &matching,
                 lem::MCollect<lem::UCString> &out_words
                ) const;
  };
 }
#endif
