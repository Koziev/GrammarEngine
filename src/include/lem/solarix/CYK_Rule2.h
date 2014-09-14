#if !defined CYK_Rule2__H
#define CYK_Rule2__H

#include <lem/solarix/SynPattern.h>

namespace Solarix
{
 class LexiconStorage;
 class CYK_NonTerminals;
 class Dictionary;

 struct CYK_NGramChecker
 {
  enum { Unknown=-1, Normalized, Raw, Predicate };
  
  int type;
  lem::UCString name;
  int id_fact;
  int arg1_index, arg2_index;

  CYK_NGramChecker() : type(UNKNOWN), id_fact(UNKNOWN), arg1_index(UNKNOWN), arg2_index(UNKNOWN) {}

  bool Defined() const { return type!=Unknown; }
  bool IsPredicate() const { return type==Predicate; }
 };

 class CYK_Rule2 : lem::NonCopyable
 {
  public:
   int id_src;
   lem::UCString left;
   int id_left;

   int arity;
   lem::UFString right1, right2;
   lem::MCollect<int> id_right1, id_right2;

   int root_index, link_type;
   int score;
   CYK_NGramChecker ngram;

  private:
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   lem::UCString marker1, marker2;

   bool IsValidMarker( const lem::UCString & marker ) const;
   int FindMarkerIndex( const lem::UCString & t, const lem::UCString & marker1, const lem::UCString & marker2 ) const;
   void StripLiteral( lem::UFString & token ) const;
   void ReadPoint( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, lem::UFString & right, lem::UCString & marker ) const;
   void ReadNGram( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile );
   #endif

  public:
   CYK_Rule2();
   
   bool Is2() const { return arity==2; }
   bool Is1() const { return arity==1; }
   bool IsZ() const;
   bool IsStart() const;
   bool HasNGram() const { return ngram.Defined(); }

   bool MatchRight1( int id_rule ) const { return id_right1.find(id_rule)!=UNKNOWN; }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt(
                Dictionary & dict,
                lem::Iridium::Macro_Parser & txtfile,
                const SynPatterns &patterns,
                WordEntrySet &wordentry_set,
                const TrProcedureDeclaration &procs,
                TrFunctions &functions
               );

   void CollectNonTerminals( CYK_NonTerminals & nonterms ) const;
   void CompileNonTerminals( CYK_NonTerminals & nonterms );
   void Store( LexiconStorage & storage ) const;
   #endif
 };




 class CYK_PatternRule : lem::NonCopyable
 {
  public:
   int id_src;
   lem::UCString left;
   int id_left;

   int id_tree;
   int score;

  private:
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void ReadNGram( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile );
   #endif

  public:
   CYK_PatternRule();
   
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt(
                Dictionary & dict,
                lem::Iridium::Macro_Parser & txtfile,
                const SynPatterns &patterns,
                WordEntrySet &wordentry_set,
                const TrProcedureDeclaration &procs,
                TrFunctions &functions
               );

   void CollectNonTerminals( CYK_NonTerminals & nonterms ) const;
   void CompileNonTerminals( CYK_NonTerminals & nonterms );
   void Store( LexiconStorage & storage ) const;
   #endif
 };

}

#endif
