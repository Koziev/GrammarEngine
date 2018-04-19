#include <lem/solarix/LA_PhoneticRuleEnumerator_MCollect.h>

using namespace Solarix;

LA_PhoneticRuleEnumerator_MCollect::LA_PhoneticRuleEnumerator_MCollect( const lem::MCollect<LA_PhoneticRule*> &Rules )
  : rules(Rules), icur(-1)
{}

bool LA_PhoneticRuleEnumerator_MCollect::Fetch()
{
 icur++;
 return icur<CastSizeToInt(rules.size());
}

const LA_PhoneticRule& LA_PhoneticRuleEnumerator_MCollect::Get()
{
 return *rules[icur];
}

