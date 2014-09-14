#if defined SOL_CAA

#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>

using namespace lem;
using namespace Solarix;


TrClosureVars::TrClosureVars( const TrClosureVars &x )
 : local_name(x.local_name), local_value(x.local_value), arg_name(x.arg_name)
{
}


void TrClosureVars::operator=( const TrClosureVars &x )
{
 local_name = x.local_name;
 local_value = x.local_value;
 arg_name = x.arg_name;
 return;
}



void TrClosureVars::AddVar( const UCString &name, const TrValue &value )
{
 if( local_name.find(name)==UNKNOWN )
  {
   local_name.push_back(name);
   local_value.push_back( new TrValue(value) );
  }
}

#endif
