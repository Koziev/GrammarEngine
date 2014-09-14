#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_notag_filter.h>

using namespace lem;
using namespace Solarix;


NoTagFilter::NoTagFilter(void)
{
 return;
}

bool NoTagFilter::Match( SG_TagsList x ) const
{
 return x==NULL || x->size()==0;
}

bool NoTagFilter::Empty(void) const
{
 return false;
}
