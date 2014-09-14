#if !defined RECO2_ProductionNode__H
 #define RECO2_ProductionNode__H

 #include <list>
 #include <lem/noncopyable.h>
 #include <lem/containers.h>
 #include <lem/ucstring.h>

 namespace Solarix
 {
  class Ngrams;
  class Tree_Node;
 }

 namespace Reco2
 {
  struct ProductionNodeMatching
  {
   int WordHits;
   int WordMisses;
   double WordHitFreq;
   int Words;

   ProductionNodeMatching(void) : WordHits(0), WordMisses(0), WordHitFreq(0.0), Words(0) {}
  };

  struct ProductionNode : lem::NonCopyable
  {
   lem::UCString word;
   const Solarix::Word_Form *var_node;

   double rel;
   double ngram_scores, ngram_misses;

   ProductionNode *prev;
   lem::MCollect<ProductionNode*> next;

   ProductionNode(void);
   ~ProductionNode(void);

   void AttachParent(void);

   #if defined SOL_CAA
   void GenerateSentence(
                         Solarix::Dictionary &dict,
                         lem::MCollect<Solarix::Tree_Node*> & out_words
                        ) const;
   #endif

   const lem::UCString & GetWord() const { return word; }

   double CalculateReliability( double rel0 ) const;

   #if defined SOL_CAA
   ProductionNodeMatching GetNGramScores( Solarix::Ngrams &ngrams ) const;
   #endif

   void FindRightmostNodes( lem::MCollect<const ProductionNode*> &rightmost ) const;

   const ProductionNode* GetNodeRTL( int shift ) const;

   void PrintRTL( lem::OFormatter &out ) const;
   void CollectRTL( lem::MCollect<const ProductionNode*> &chain ) const;

   void CollectWordsToLeft(
                           int n,
                           lem::MCollect<lem::UCString> & words,
                           lem::MCollect<const Solarix::Word_Form*> & var_nodes,
                           lem::MCollect<const ProductionNode*> & nodes
                          ) const;

   //void ProbeNgrams( Solarix::Ngrams &ngrams );
 };
}
#endif
