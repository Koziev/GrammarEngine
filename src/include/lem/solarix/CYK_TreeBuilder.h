#if !defined CYK_TreeBuilder__H && defined SOL_CAA
#define CYK_TreeBuilder__H

#include <lem/solarix/CYK_Engine.h>

namespace Solarix
{
 class TreeMatchingExperience;


class CYK_TreeBuilder : lem::NonCopyable
{
 private:
  lem::MCollect<CYK_SyntaxTree*> all_trees; // для сборки мусора

  typedef std::multimap< const Rule2_Matching *, const CYK_SyntaxTree * > M2TREE;
  M2TREE m2tree; // кэшируем уже построенные деревья в промежуточных узлах

  #if defined SOL_DEBUGGING
  lem::MCollect<Rule2_Matching*> all_mx; // сборка мусора
  lem::MCollect<CYK_DebugNGram*> debug_ngram;
  #endif

 private: 
  #if defined SOL_DEBUGGING
  void AddDebug( CYK_SyntaxTree * t, const Rule2_Matching * m, int depth );
  void AddDebugNGram( CYK_SyntaxTree * t, const CYK_Rule2 * r, const Word_Form * arg1, const Word_Form * arg2, bool matched, int score );
  #endif

  void ExtractB(
                const Rule2_Matching & m,
                const P_matrix & P,
                const lem::MCollect<CYK_TokenMatching*> & words,
                lem::MCollect<const CYK_SyntaxTree*> & res_nodes
               );

  void ExtractC(
                const Rule2_Matching & m,
                const P_matrix & P,
                const lem::MCollect<CYK_TokenMatching*> & words,
                lem::MCollect<const CYK_SyntaxTree*> & res_nodes
               );


  void BuildTreeNode(
                     int depth,
                     Dictionary & dict,
                     TreeMatchingExperience & experience,
                     const Rule2_Matching & m,
                     const P_matrix & P,
                     const lem::MCollect<CYK_TokenMatching*> & words,
                     lem::MCollect<const CYK_SyntaxTree*> & res_nodes
                    );

  inline const CYK_SyntaxTree * SelectNodeByIndex( const CYK_SyntaxTree * Bnode, const CYK_SyntaxTree * Cnode, int index ) const
  {
   return index==0 ? Bnode : Cnode;
  }


  int ApplyNGram(
                 Dictionary &dict,
                 TreeMatchingExperience & experience,
                 const Rule2_Matching & m,
                 CYK_SyntaxTree * Root,
                 const CYK_SyntaxTree * Bnode,
                 const CYK_SyntaxTree * Cnode
                );

 public:
  CYK_TreeBuilder() {}
  ~CYK_TreeBuilder();
  
  void BuildTrees(
                  Dictionary & dict,
                  TreeMatchingExperience & experience,
                  const Rule2_Matching & S_matching,
                  const P_matrix & P,
                  const lem::MCollect<CYK_TokenMatching*> & word_matchings,
                  lem::MCollect<const CYK_SyntaxTree*> & trees
                 );
};


// ---------------------------------

class CYK_Enumerator_Leaf;
class CYK_Enumerator_Backpointers;

class CYK_Enumerator
{
 public:
  CYK_Enumerator * next;

 public:
  CYK_Enumerator() : next(NULL) {}
  virtual ~CYK_Enumerator() { delete next; }

  virtual bool Next()=0;
  virtual void Reset() { lem_rub_off(next); }

  virtual bool IsLeaf() { return false; }
  virtual bool IsBackpointers() { return false; }
  virtual bool Is2() { return false; }

  virtual void Print( lem::OFormatter & out, Dictionary & dict, const CYK_Engine & engine ) const;

  virtual const CYK_Enumerator_Leaf * FindLeaf( int req_start, int req_id_left ) const;
  virtual const CYK_Enumerator_Backpointers * FindBackpointer( const P_cell & c ) const;
};


// конечный переборщик вариантов листа.
class CYK_Enumerator_Leaf : public CYK_Enumerator
{
 public:
  int start, id_left;

  int index;
  lem::MCollect<const CYK_WordNonTerm*> rules;
  lem::MCollect<const CYK_SyntaxTree*> leafs;

 public:
  CYK_Enumerator_Leaf( int _start, int _id_left ) : start(_start), id_left(_id_left), index(-1) {}
  virtual bool Next();
  virtual void Reset() { index=-1; CYK_Enumerator::Reset(); }
  virtual bool IsLeaf() { return true; }
  virtual void Print( lem::OFormatter & out, Dictionary & dict, const CYK_Engine & engine ) const;

  const CYK_SyntaxTree * GetCurrentLeaf() const { return leafs[index]; }

  virtual const CYK_Enumerator_Leaf * FindLeaf( int req_start, int req_id_left ) const;
};



class CYK_Scorer
{
 private:
  typedef std::map<const Rule2_Matching *,int> M2SCORE;
  M2SCORE m2score;
  enum { MAX_VARIANT_COUNT=1000000 };

  int GetScore( const P_matrix & P, const Rule2_Matching * m, int variants_counter );

 public:
  CYK_Scorer() {}

  int GetScore( const P_matrix & P, const Rule2_Matching * m );
};



class CYK_Enumerator_Backpointers : public CYK_Enumerator
{
 public:
  int index;
  const P_cell & c;
  lem::MCollect< std::pair<const Rule2_Matching*,int> > weighted_backpointers;
  int n_total;

 public:
  CYK_Enumerator_Backpointers( CYK_Scorer & scorer, const P_cell & _c, const P_matrix & P );
  virtual ~CYK_Enumerator_Backpointers() {}

  virtual bool Next();
  virtual void Reset() { index=-1; CYK_Enumerator::Reset(); }

  virtual bool IsBackpointers() { return true; }
  virtual void Print( lem::OFormatter & out, Dictionary & dict, const CYK_Engine & engine ) const;

  const Rule2_Matching & GetCurrentRuleMatching() const
  {
   LEM_CHECKIT_Z( index>=0 && index<n_total );
   return * weighted_backpointers[index].first;
  }

  virtual const CYK_Enumerator_Backpointers * FindBackpointer( const P_cell & c ) const;
};


class CYK_Enumerator_2 : public CYK_Enumerator
{
 public:
  const Rule2_Matching & m;
  CYK_Enumerator *x,*y;
  bool first;

 public:
  CYK_Enumerator_2( CYK_Enumerator * _x, CYK_Enumerator * _y, const Rule2_Matching & _m ) : m(_m), x(_x), y(_y), first(true) {}
  virtual ~CYK_Enumerator_2();

  virtual void Print( lem::OFormatter & out, Dictionary & dict, const CYK_Engine & engine ) const;

  virtual bool Next();
  virtual void Reset();

  virtual bool Is2() { return true; }

  virtual const CYK_Enumerator_Leaf * FindLeaf( int req_start, int req_id_left ) const;
  virtual const CYK_Enumerator_Backpointers * FindBackpointer( const P_cell & c ) const;
};









class CYK_TreeBuilder_Enum : lem::NonCopyable
{
 private:
  CYK_Engine & engine;
  Dictionary & dict;
  TreeMatchingExperience & experience;
  const P_matrix & P;
  CYK_Scorer & scorer;
  const lem::MCollect<const CYK_TokenMatching*> & words;

  CYK_Enumerator * BuildEnumerator( const Rule2_Matching & m );
  CYK_Enumerator * CreateEnumerator( int start, int len, int id_rule );
  CYK_Enumerator * Multiply( CYK_Enumerator * x, CYK_Enumerator * y );

 private:
  lem::MCollect<CYK_SyntaxTree*> all_trees; // для сборки мусора

  #if defined SOL_DEBUGGING
  lem::MCollect<Rule2_Matching*> all_mx; // сборка мусора
  lem::MCollect<CYK_DebugNGram*> debug_ngram;
  #endif

  #if defined SOL_DEBUGGING
  void AddDebug( CYK_SyntaxTree * t, const Rule2_Matching * m, int depth );
  void AddDebugNGram( CYK_SyntaxTree * t, const CYK_Rule2 * r, const Word_Form * arg1, const Word_Form * arg2, bool matched, int score );
  #endif

  const CYK_SyntaxTree* ExtractB( int depth, const Rule2_Matching & m, const CYK_Enumerator * enumerator );
  const CYK_SyntaxTree* ExtractC( int depth, const Rule2_Matching & m, const CYK_Enumerator * enumerator );
  const CYK_SyntaxTree* BuildTreeNode( int depth, const Rule2_Matching & m, const CYK_Enumerator * enumerator );

  inline const CYK_SyntaxTree * SelectNodeByIndex( const CYK_SyntaxTree * Bnode, const CYK_SyntaxTree * Cnode, int index ) const
  {
   return index==0 ? Bnode : Cnode;
  }

  int ApplyNGram(
                 const Rule2_Matching & m,
                 CYK_SyntaxTree * Root,
                 const CYK_SyntaxTree * Bnode,
                 const CYK_SyntaxTree * Cnode
                );


 public:
  CYK_TreeBuilder_Enum(
                       Dictionary & _dict,
                       CYK_Engine & engine,
                       TreeMatchingExperience & _experience,
                       const P_matrix & _P,
                       const lem::MCollect<const CYK_TokenMatching*> & _words,
                       CYK_Scorer &_scorer
                      );

  ~CYK_TreeBuilder_Enum();
  
  CYK_Enumerator* Start( const P_cell & c_S );
  bool Fetch( CYK_Enumerator * e );
  const CYK_SyntaxTree* Create( const CYK_Enumerator * enumerator );
};



}

#endif
