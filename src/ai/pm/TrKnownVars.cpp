#if defined SOL_LOADTXT && defined SOL_COMPILER

#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;

   
TrKnownVars::TrKnownVars(void)
{
 parent = NULL;
}


TrKnownVars::TrKnownVars( const TrKnownVars *OuterBlock )
 : parent(OuterBlock)
{
}

TrKnownVars::~TrKnownVars(void)
{
}

bool TrKnownVars::IsVariable( const UCString &name ) const
{
 return name==L'_' || // для closure
        vars.find(to_lower(name))!=vars.end() ||
        (parent!=NULL && parent->IsVariable(name));
}

const TrType& TrKnownVars::GetVarType( const UCString &name ) const
{
 LEM_CHECKIT_Z( IsVariable(name) );

 UCString lname = to_lower(name);

 if( vars.find(lname)!=vars.end() )
  return vars.find(lname)->second;

 return parent->GetVarType(name);
}


void TrKnownVars::RegisterVar( const TrType &type, const UCString &name )
{
 UCString lname = to_lower(name);
 if( vars.find(lname)!=vars.end() )
  {
   lem::UFString msg( lem::format_str( L"Variable [%s] is already declared in a scope", name.c_str() ) );
   throw E_ParserError(msg.c_str());
  }

 vars.insert( std::make_pair(lname,type) );
 return;
}

#endif
