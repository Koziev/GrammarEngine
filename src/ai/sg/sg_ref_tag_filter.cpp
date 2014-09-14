#include <lem/solarix/SG_TagFilter.h>

using namespace lem;
using namespace Solarix;


SG_RefTagFilter::SG_RefTagFilter( const lem::MCollect< std::pair<int,int> > &_tags, bool _matches_null )
:tags(_tags), matches_null(_matches_null)
{}


bool SG_RefTagFilter::Match( SG_TagsList x ) const
{
 if( x==NULL )
  return matches_null;

 if( x->size() < tags.size() )
  return false;

 // Каждый из требуемых тэгов должен быть задан для связки, хотя связка может
 // быть обвешена еще многими другими тэгами.
 for( lem::Container::size_type i=0; i<tags.size(); ++i )
  if( x->find( tags[i] )==UNKNOWN )
   return false;

 return true; 
}
