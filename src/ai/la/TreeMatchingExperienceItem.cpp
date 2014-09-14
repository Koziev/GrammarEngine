#include <lem/solarix/TreeMatchingExperience.h>

using namespace Solarix;

TreeMatchingExperienceItem::TreeMatchingExperienceItem( bool src_success, const lem::PtrCollect<SynPatternResult> &src )
{
 success = src_success;
 for( lem::Container::size_type i=0; i<src.size(); ++i )
  results.push_back( src[i]->Copy1(NULL) );
}

void TreeMatchingExperienceItem::Add( const SynPatternResult & src )
{
 results.push_back( src.Copy1(NULL) );
 return;
}



void TreeMatchingExperienceItem::Copy( const BackTrace *parent_trace, lem::PtrCollect<SynPatternResult> &ext ) const
{
 for( lem::Container::size_type i=0; i<results.size(); ++i )
  ext.push_back( results[i]->Copy1(parent_trace) );

 return;
}
