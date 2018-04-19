#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/solarix/LexiconStorage_MySQL.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/WordEntries_MySQL.h>
#include <lem/solarix/WordFormEnumerator_MySQL.h>

using namespace Solarix;

WordFormEnumerator_MySQL::WordFormEnumerator_MySQL(LS_ResultSet_MySQL *_rs, WordEntries_MySQL *_entries)
    : rs(_rs), entries(_entries)
{
}

WordFormEnumerator_MySQL::WordFormEnumerator_MySQL(
    LS_ResultSet_MySQL *_rs,
    WordEntries_MySQL *_entries,
    const lem::MCollect<lem::UCString> &_forms
)
    : rs(_rs), entries(_entries), forms(_forms)
{
}



WordFormEnumerator_MySQL::~WordFormEnumerator_MySQL()
{
    lem_rub_off(rs);
}

bool WordFormEnumerator_MySQL::Fetch()
{
    return rs->Fetch();
}

int WordFormEnumerator_MySQL::GetEntryKey()
{
    return rs->GetInt(0);
}

int WordFormEnumerator_MySQL::GetFormIndex()
{
    return rs->GetInt(1);
}

float WordFormEnumerator_MySQL::GetValue()
{
    return 1.0F;
}

int WordFormEnumerator_MySQL::GetMatchedWordIndex()
{
    if (forms.size() > 1)
    {
        lem::UCString matched_word = rs->GetUCString(2);
        return forms.find(matched_word);
    }
    else
    {
        return 0;
    }
}


#endif
