#if !defined CYK_WordNonTerm__H
#define CYK_WordNonTerm__H

#include <lem/solarix/SynPattern.h>

namespace Solarix
{
 class LexiconStorage;
 class CYK_NonTerminals;
 class Dictionary;
 class SynPatternTreeNode;

 class CYK_WordNonTerm : lem::NonCopyable
 {
  public:
   int id_src;
   lem::UCString left;
   int id_left;
   int score;
   Solarix::SynPatternTreeNode * tree;

  private:
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   lem::Ptr<SynPatternCompilation> compilation_context; // объявления переменных, для последующего
                                                         // сравнения у всех одноименных контекстов
   lem::PtrCollect<SynPatternPoint> points;
   #endif


  public:
   CYK_WordNonTerm();
   ~CYK_WordNonTerm();

   bool IsUNK() const;

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
