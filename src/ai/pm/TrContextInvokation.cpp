#if defined SOL_CAA

#include <lem/solarix/variator.h>
#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;


TrContextInvokation::TrContextInvokation( TrFunContext *parent )
 : TrFunContext(parent)
{
}

lem::Ptr<TrValue> TrContextInvokation::GetVar( const UCString &name )
{
 LEM_CHECKIT_Z(!name.empty());

 for( lem::Container::size_type i=0; i<arg_name.size(); ++i )
  if( arg_name[i].eqi(name) )
   return lem::Ptr<TrValue>( arg_value[i], null_deleter() );

 return TrFunContext::GetVar(name);
}

void TrContextInvokation::AddVar( const UCString &name, lem::Ptr<TrValue> value )
{
 LEM_CHECKIT_Z(!name.empty());

 arg_name.push_back(name);
 arg_value.push_back( new TrValue(*value) );
 return;
}

void TrContextInvokation::PrintVars( Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
 for( lem::Container::size_type i=0; i<arg_name.size(); ++i )
  {
   if( arg_name[i]==L"((return))" )
    continue;

   out.printf( "%vfF%us%vn %vfA%us%vn=", arg_value[i]->GetType().GetName().c_str(), arg_name[i].c_str() );
   arg_value[i]->Print(dict,out);
   out.eol();
  } 

 TrFunContext::PrintVars(dict,out);
 return;
}

#endif
