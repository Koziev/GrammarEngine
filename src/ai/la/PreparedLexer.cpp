#include <lem/solarix/PreparedLexer.h>

using namespace Solarix;

PreparedLexer::PreparedLexer( const lem::MCollect<const LexerTextPos*> & _tokens, Solarix::Dictionary * _dict, const TextRecognitionParameters & _params, TrTrace * _trace )
 : BasicLexer(_dict,_params,_trace)
{
 for( int i=0; i<CastSizeToInt(_tokens.size())-1; ++i )
  next.insert( std::make_pair( _tokens[i], _tokens[i+1] ) );

 return;
}


bool PreparedLexer::Fetch( const LexerTextPos * current, const TokenExpectation * unused, lem::MCollect<const LexerTextPos*> & next_tokens )
{
 std::map<const LexerTextPos*,const LexerTextPos*>::const_iterator it = next.find(current);
 if( it==next.end() )
  return false;

 next_tokens.push_back(it->second);

 return true;
}

