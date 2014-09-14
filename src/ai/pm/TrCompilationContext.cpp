#if defined SOL_LOADTXT && defined SOL_COMPILER

#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;

TrCompilationContext::TrCompilationContext(void)
{
}
   
void TrCompilationContext::RegisterVariable( const UCString &name )
{
 lem::UCString uname( lem::to_upper(name) );

 if( vars.find(uname)!=UNKNOWN )
  {
   lem::UFString msg( lem::format_str( L"Variable [%s] is already declared", name.c_str() ) );
   throw E_ParserError(msg.c_str());
  }

 vars.push_back(uname);
 return;
}

bool TrCompilationContext::IsVariable( const UCString &name ) const
{
 return vars.find( lem::to_upper(name) )!=UNKNOWN;
}


void TrCompilationContext::LoadTxt( PM_Automat &pm, lem::Iridium::Macro_Parser & txtfile, int BrokerToken )
{
 int nvar=0;
 while( !txtfile.eof() )
  {
   if( txtfile.pick().GetToken()==BrokerToken )
    break;

   if( nvar>0 )
    txtfile.read_it( B_COMMA );

   const lem::Iridium::BethToken &t = txtfile.read();
   if( IsVariable(t.string()) )
    {
     lem::Iridium::Print_Error( t, txtfile );
     lem::UFString msg( lem::format_str( L"Variable [%s] is already declared", t.c_str() ) );
     throw E_ParserError(msg.c_str());
    }

   RegisterVariable(t.string());
   nvar++;
  }

 txtfile.read_it( BrokerToken );
 return;
}

int TrCompilationContext::Find( const lem::UCString & variable_name ) const
{
 return vars.find( lem::to_upper(variable_name) );
}


#endif


