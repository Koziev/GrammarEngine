#include <lem/solarix/dictionary.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/sg_tag_or_null_tagfilter.h>

using namespace lem;
using namespace Solarix;


TF_TagOrNullFilter::TF_TagOrNullFilter( const Dictionary &dict, const lem::UCString & tag_name, const lem::UCString &tag_value )
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

bool TF_TagOrNullFilter::Match( SG_TagsList x ) const
{
 if( x==NULL )
  return true;

 for( lem::Container::size_type i=0; i<x->size(); ++i )
  if( x->get(i).first == itag )
   {
    if( x->get(i).second!=ivalue )
     return false;
   }

 return true;
}

bool TF_TagOrNullFilter::Empty(void) const
{
 return itag!=UNKNOWN;
}
