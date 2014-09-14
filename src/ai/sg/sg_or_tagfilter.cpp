#include <lem/solarix/dictionary.h>
#include <lem/solarix/SG_TagFilter.h>

using namespace lem;
using namespace Solarix;

SG_TF_OrFilter::SG_TF_OrFilter( const lem::Ptr<SG_TagFilter> &x1, const lem::Ptr<SG_TagFilter> &x2 )
 : arg1(x1), arg2(x2)
{
}

bool SG_TF_OrFilter::Match( SG_TagsList x ) const
{
 return arg1->Match(x) || arg2->Match(x);
}


bool SG_TF_OrFilter::Empty(void) const
{
 return arg1.NotNull() && arg2.NotNull();
}

