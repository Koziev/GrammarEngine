#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/macros.h>

#include <lem/solarix/LexiconStorage_MySQL.h>
#include <lem/solarix/WordEntries_MySQL.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/WordEntryEnumerator_MySQL.h>

using namespace Solarix;

WordEntryEnumerator_MySQL::WordEntryEnumerator_MySQL(LS_ResultSet_MySQL *_rs, WordEntries_MySQL *_entries)
    : rs(_rs), entries(_entries)
{
}


WordEntryEnumerator_MySQL::~WordEntryEnumerator_MySQL()
{
    lem_rub_off(rs);
}


bool WordEntryEnumerator_MySQL::Fetch()
{
    return rs->Fetch();
}


int WordEntryEnumerator_MySQL::GetId()
{
    return rs->GetInt(0);
}


const SG_Entry& WordEntryEnumerator_MySQL::GetItem()
{
    const int ekey = GetId();
    return entries->GetEntry(ekey);
}

#endif
