#if !defined WrittenTextLexer__H
 #define WrittenTextLexer__H

#include <lem/solarix/BasicLexer.h>

namespace Solarix {

struct TextTokenizationRules;
class GG_CharOperation;
class CasingCoder;

class WrittenTextLexer : public BasicLexer
{
 private:
  int UNKNOWN_ENTRY_KEY;

  TextTokenizationRules * rules; // все необходимые правила токенизации для заданного набора языков.
  
  lem::UFString text; // разбираемый текст.

  bool use_charcase_filter; // использовать фильтрацию распознаваний слов по регистру первого символа.
  const GG_CharOperation *upper_xlat;
  const CasingCoder * casing_coder;

  std::set<const LexerTextPos*> filtered_next_after;

  std::set<const LexerTextPos*> token_is_split;
  std::set< std::pair<const LexerTextPos*,const LexerTextPos*> > tokens_are_merged;

  const Word_Form * Recognize( const lem::UCString & word, int WordIndex, int WordParts, const wchar_t * TokenizationFlags );
  
  void Extract(
               const lem::UFString & Text,
               int CurrentPosition,
               const LexerTextPos *PreviousToken,
               lem::MCollect<const LexerTextPos*> & tokens
              );

  void ExtractUnfiltered(
                         const lem::UFString & Text,
                         int CurrentPosition,
                         const LexerTextPos *PreviousToken,
                         lem::MCollect<LexerTextPos*> & tokens
                        );

  void ExtractAhead(
                    int n_tokens,
                    const lem::UFString & Text,
                    int CurrentPosition,
                    const LexerTextPos *PreviousToken,
                    lem::MCollect<LexerTextPos*> & tokens
                   );

  void TryToSplitToken(
                       const LexerTextPos * previous_token,
                       const LexerTextPos * token,
                       lem::MCollect<const LexerTextPos*> & tokens
                      );

  lem::UCString RemoveDash( const lem::UCString & word ) const;

  void CallExternalTokenizer();

 public:
  WrittenTextLexer(
                   const lem::UFString & _text,
                   const TextRecognitionParameters & _params,
                   Solarix::Dictionary * _dict,
                   TrTrace * _trace
                  );

 
  virtual bool Fetch(
                     const LexerTextPos * current,
                     const TokenExpectation * expectations,
                     lem::MCollect<const LexerTextPos*> & next
                    );
};

}
#endif
