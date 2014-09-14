#if defined SOL_CAA

// CD->29.07.2009
// LC->14.08.2009

#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;


lem::Ptr<TrValue> TrFunContext::GetVar( const UCString &name )
{
 if( parent!=NULL )
  return parent->GetVar(name);

 lem::UFString msg( lem::format_str( L"Can not find variable [%s] in current scope", name.c_str() ) );
 throw E_BaseException(msg.c_str());
}


void TrFunContext::AddVar( const UCString &name, lem::Ptr<TrValue> value )
{
 LEM_STOPIT;
}

TrYield* TrFunContext::GetYield(void)
{
 if( parent!=NULL )
  return parent->GetYield();
 else
  return NULL;
}

TrWideContext* TrFunContext::GetWideContext(void)
{
 if( env!=NULL )
  return env;

 if( parent!=NULL )
  return parent->GetWideContext();
 else
  return env;
}

TrTrace * TrFunContext::GetTrace(void)
{
 if( trace_log!=NULL )
  return trace_log;

 if( parent!=NULL )
  return parent->GetTrace();
 else
  return trace_log;
}

TrMapContext * TrFunContext::GetMapping(void)
{
 if( parent!=NULL )
  return parent->GetMapping();
 else
  return NULL;
}

Solarix::Variator* TrFunContext::GetCurrentVariator(void)
{
 if( parent!=NULL )
  return parent->GetCurrentVariator();
 else
  return NULL;
}


int TrFunContext::GetCurrentPosition(void)
{
 if( parent!=NULL )
  return parent->GetCurrentPosition();
 else
  return UNKNOWN;
}


void TrFunContext::PrintVars( Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
 
 if( parent!=NULL )
  parent->PrintVars(dict,out);

 return;
}

#endif
