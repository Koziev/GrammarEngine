#if !defined PreparedLexer__H
#define PreparedLexer__H

#include <map>
#include <lem/solarix/BasicLexer.h>
#include <lem/noncopyable.h>

namespace Solarix
{
 class Dictionary;
 struct TextRecognitionParameters;
 class TrTrace;

 class PreparedLexer : public BasicLexer
 {
  private:
   std::map<const LexerTextPos*,const LexerTextPos*> next;

  public:
   PreparedLexer(
                 const lem::MCollect<const LexerTextPos*> & _tokens,
                 Solarix::Dictionary * _dict,
                 const TextRecognitionParameters & _params,
                 TrTrace * _trace
                );
 
   virtual bool Fetch( const LexerTextPos * current, const TokenExpectation * unused, lem::MCollect<const LexerTextPos*> & next );
 };


 class Variator;

 class VariatorLexerTokens : lem::NonCopyable
 {
  private:
   const Variator & var;
   lem::MCollect<LexerTextPos*> tokens;
   lem::MCollect<const LexerTextPos*> word2token;
   const LexerTextPos * right_terminator;

  public:
   VariatorLexerTokens( const Variator & _var, Solarix::Dictionary * _dict );

   virtual ~VariatorLexerTokens();

   // после изменения корней в вариаторе надо обязательно переформировать список токенов тут.
   void Refresh( Solarix::Dictionary * dict );
   int Size() const;
   const LexerTextPos * GetToken( int index ) const { return word2token[index]; }
   const LexerTextPos * GetRightTerminator() const { return right_terminator; }
   void Print( lem::OFormatter & out, Dictionary & dict ) const;
 };

 class VariatorLexer : public BasicLexer
 {
  private:
   const VariatorLexerTokens & var;
   int start_token;
   std::map<const LexerTextPos*,const LexerTextPos*> t2next;
   std::map<const LexerTextPos*,int> token2pos;

  public:
   VariatorLexer(
                 const VariatorLexerTokens & _var,
                 int start_token,
                 Solarix::Dictionary * _dict,
                 const TextRecognitionParameters & _params,
                 TrTrace * _trace
                );

   virtual bool Fetch( const LexerTextPos * current, const TokenExpectation * unused, lem::MCollect<const LexerTextPos*> & next );
 };


}

#endif
