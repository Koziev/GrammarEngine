#if !defined LA_PHONETIC_RULE_ENUMERATOR_MCOLLECT__H
#define LA_PHONETIC_RULE_ENUMERATOR_MCOLLECT__H

#include <lem/containers.h>
#include <lem/solarix/LA_PhoneticRuleEnumerator.h>

namespace Solarix
{
    class LA_PhoneticRule;
    class LA_PhoneticRuleEnumerator_MCollect : public LA_PhoneticRuleEnumerator
    {
    private:
        int icur;
        const lem::MCollect<LA_PhoneticRule*> &rules;

    public:
        LA_PhoneticRuleEnumerator_MCollect(const lem::MCollect<LA_PhoneticRule*> &Rules);

        virtual bool Fetch();
        virtual const LA_PhoneticRule& Get();
    };
}

#endif
