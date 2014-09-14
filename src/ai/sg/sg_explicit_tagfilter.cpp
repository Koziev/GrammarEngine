#include <lem/solarix/dictionary.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/sg_explicit_tagfilter.h>

using namespace lem;
using namespace Solarix;


TF_ExplicitFilter::TF_ExplicitFilter( const Dictionary &dict, const lem::UCString & tag_name, const lem::UCString &tag_value )
{
 LEM_CHECKIT_Z( !tag_name.empty() );
 LEM_CHECKIT_Z( !tag_value.empty() );

 std::pair<int,int> p = dict.GetSynGram().Get_Net().FindTagValue(tag_name,tag_value);

 itag = p.first;
 ivalue = p.second;

 LEM_CHECKIT_Z(itag!=UNKNOWN);
 LEM_CHECKIT_Z(ivalue!=UNKNOWN);


 return;
}

bool TF_ExplicitFilter::Match( SG_TagsList x ) const
{
 if( x==NULL )
  return false;

 for( lem::Container::size_type i=0; i<x->size(); ++i )
  if( x->get(i).first == itag )
   {
    if( x->get(i).second!=ivalue )
     return false;
   }

 return true;
}

bool TF_ExplicitFilter::Empty(void) const
{
 return itag!=UNKNOWN;
}
