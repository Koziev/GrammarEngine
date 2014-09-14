#if !defined RECO2_RPoint__H
 #define RECO2_RPoint__H

 #include <lem/noncopyable.h>
 #include <lem/solarix/R2Utils.h>
 #include <lem/solarix/R2Word.h>
 #include <lem/solarix/R2Word2PointMatching.h>

 namespace Reco2
 {
  class RPoint : lem::NonCopyable
  {
   private:
    int id;
    int weight;
    int id_word; // исходное слово
    lem::MCollect<RWord> alts; // результаты трансформаций

   public:
    RPoint(void);

    RPoint( int _id, int _id_word, int _weight );

    int GetHeadword(void) const { return id_word; }
    int GetId(void) const { return id; }
    int GetWeight(void) const { return weight; }
    const lem::MCollect<RWord>& GetAlts(void) const { return alts; }

    void Add( const RWord &x );
 
    Word2PointMatching MatchWord( const ints & id_words, const floats &word_rels ) const;
  };
 }

#endif
