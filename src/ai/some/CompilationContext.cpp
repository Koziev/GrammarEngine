#include <lem/conversions.h>
#include <lem/solarix/compilation_context.h>

using namespace lem;
using namespace std;
using namespace Solarix;

int CompilationContext::id_seq=1000000;

bool CompilationContext::FindVar( const lem::UCString & Name, bool parents ) const
{
 for( lem::Container::size_type i=0; i<vars.size(); i++ )
  if( vars[i]->GetName()==Name )
   return true;
  
 if( parent!=NULL && parents )
  return parent->FindVar(Name,parents);

 return false;
}


int CompilationContext::AddVar( const lem::UCString & Name )
{
 if( FindVar(Name,true) )
  {
   return UNKNOWN;
  }

 int id=UNKNOWN;

 if( Name.length()==1 && lem::is_lat(Name.front()) )
  id = (int)Name.front();
 else
  id = id_seq++;
    
 vars.push_back( new DeclaredVar(Name,id) );
 return id;
}


int CompilationContext::GetVarId( const UCString & varname ) const
{
 for( lem::Container::size_type i=0; i<vars.size(); i++ )
  if( vars[i]->GetName()==varname )
   return vars[i]->GetId();
  
 if( parent!=NULL )
  return parent->GetVarId(varname);

 return UNKNOWN;
}
