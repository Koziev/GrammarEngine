#if defined SOL_CAA

// CD->07.07.2009
// LC->06.03.2011

#include <lem/solarix/tokens.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/TrMorphologyTracer.h>
#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;

TrTrace::TrTrace(void)
{
 morphology_tracer = new TrMorphologyTracer();
}


TrTrace::~TrTrace(void)
{
 lem_rub_off(morphology_tracer);
 return;
}


TrMorphologyTracer& TrTrace::GetMorphologyTracer(void)
{
 return *morphology_tracer;
}


void TrTrace::Enter( TrTraceActor *a )
{
 a->entering = true;
 return;
}


void TrTrace::Leave( TrTraceActor *a )
{
 a->entering = false;
 return;
}

void TrTrace::StartNewSentence(void)
{
 GetMorphologyTracer().Clear();
 return;
}



TrTraceTTY::TrTraceTTY( Dictionary *d )
 : dict(d)
{}


void TrTraceTTY::Enter( TrTraceActor *a )
{
 TrTrace::Enter(a);
 a->Print(*dict,*mout);
 call_stack.push_back(a);
 return;
}


void TrTraceTTY::Leave( TrTraceActor *a )
{
 TrTrace::Leave(a);

 if( !call_stack.empty() && call_stack.back()->Match(a) )
  {
   a->Print( *dict, *mout, call_stack.back() );
   call_stack.resize( CastSizeToInt(call_stack.size())-1 );
  }
 else
  {
   a->Print( *dict, *mout );
  }

 delete a;
 return;
}



void TrTraceTTY::Print( const UFString &str )
{
 mout->printf( "%us\n", str.c_str() );
 return;
}

#endif
