#include <lem/solarix/word_form.h>
#include <lem/solarix/TreeScorerApplicationContext.h>

using namespace Solarix;

void TreeScorerBoundVariables::Clear()
{
    bound_variables.clear();
    return;
}


void TreeScorerBoundVariables::AddVariable(const lem::UCString & upper_name, const Solarix::Word_Form * wordform)
{
    LEM_CHECKIT_Z(!upper_name.empty());
    LEM_CHECKIT_Z(wordform != nullptr);

    bound_variables[upper_name] = wordform;
    return;
}

const Solarix::Word_Form* TreeScorerBoundVariables::GetVariable(const lem::UCString & upper_name) const
{
    LEM_CHECKIT_Z(!upper_name.empty());

    auto it = bound_variables.find(upper_name);
    if (it == bound_variables.end())
        return nullptr;
    else
        return it->second;
}

