#if defined SOL_LOADTXT && defined SOL_COMPILER

#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;

TrProcedureDeclaration::TrProcedureDeclaration(void)
{
}
   
void TrProcedureDeclaration::RegisterProcedure( const UCString &name )
{
 if( procs.find(name)!=UNKNOWN )
  {
   lem::UFString msg( lem::format_str( L"Procedure [%s] is already declared", name.c_str() ) );
   throw E_ParserError(msg.c_str());
  }

 procs.push_back(name);
 return;
}

bool TrProcedureDeclaration::IsProcedure( const UCString &name ) const
{
 return procs.find(name)!=UNKNOWN;
}


bool TrProcedureDeclaration::IsRuleGroup( const UCString &name ) const
{
 return rulegroups.find(name)!=UNKNOWN;
}



void TrProcedureDeclaration::RegisterRuleGroup( const UCString &name )
{
 if( rulegroups.find(name)!=UNKNOWN )
  {
   lem::UFString msg( lem::format_str( L"Rule group [%s] is already declared", name.c_str() ) );
   throw E_ParserError(msg.c_str());
  }

 rulegroups.push_back(name);
 return;
}

#endif
