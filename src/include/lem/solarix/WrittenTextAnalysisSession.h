#if !defined WrittenTextAnalysisSession__H
#define WrittenTextAnalysisSession__H

#include <lem/solarix/TextAnalysisSession.h>

namespace Solarix {

class WrittenTextLexer;

class WrittenTextAnalysisSession : public TextAnalysisSession
{
 private:
  lem::UFString processed_str;

  void AnalyzeIt( const lem::UFString & str, bool ApplyPatterns, bool DoSyntacticLinks, const ElapsedTimeConstraint & constraints );

 public:
  WrittenTextAnalysisSession( Solarix::Dictionary * _dict, TrTrace * _trace );
  
  void MorphologicalAnalysis( const lem::UFString & str );
  void SyntacticAnalysis( const lem::UFString & str );
  void ApplyFilters( const lem::UFString & str );
  void Tokenize( const lem::UFString & str );

  void SyntacticAnalysis( BasicLexer & lexer, const ElapsedTimeConstraint & constraints );

  const lem::UFString & GetString() const { return processed_str; }
};

}

#endif
