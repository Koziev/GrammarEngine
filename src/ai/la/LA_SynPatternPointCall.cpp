#if defined SOL_CAA

#include <lem/solarix/dictionary.h>
#include <lem/solarix/BackTrace.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/LA_SynPatternPointCall.h>

using namespace lem;
using namespace Solarix;

SynPatternPointCall::SynPatternPointCall(
                                         int mark,
                                         const lem::MCollect<int> & Location,
                                         const SynPatternPoint * p,
                                         const LexerTextPos * _token,
                                         const BackTrace * _markers
                                        )
 : TrTraceActor(mark,Location), point(p), token(_token), markers(_markers)
{
 return;
}

void SynPatternPointCall::Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening )
{
 PrintContext(dict,out);
 return;
}

void SynPatternPointCall::PrintCurrentToken( Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
 out.printf( "\nCurrent token: index=%d wordform=", token->GetWordIndex() );
 token->GetWordform()->Print( out, &dict.GetSynGram(), true );
 out.eol();
 return;
}

void SynPatternPointCall::PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
 out.printf( "\nCurrent token: index=%d wordform=", token->GetWordIndex() );
 token->GetWordform()->Print( out, &dict.GetSynGram(), true );
 out.eol();

 if( !markers->Empty() )
  {
   out.printf( "\n%vf6Back markers:%vn\n" );
   markers->Print( out, dict.GetSynGram(), true );
  }

 return;
}

#endif
