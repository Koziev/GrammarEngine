#include <lem/macros.h>
#include <lem/stl.h>

#include <lem/solarix/lexem.h>
#include <lem/solarix/LexiconStorage_SQLITE.h>
#include <lem/solarix/WordEntries_SQLite.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/WordEntryEnumerator_SQLite.h>

using namespace Solarix;

WordEntryEnumerator_SQLite::WordEntryEnumerator_SQLite(LS_ResultSet_SQLITE *_rs, WordEntries_SQLite *_entries)
    : rs(_rs), entries(_entries)
{
}


WordEntryEnumerator_SQLite::~WordEntryEnumerator_SQLite()
{
    lem_rub_off(rs);
}


bool WordEntryEnumerator_SQLite::Fetch()
{
    return rs->Fetch();
}


int WordEntryEnumerator_SQLite::GetId()
{
    return rs->GetInt(0);
}


const SG_Entry& WordEntryEnumerator_SQLite::GetItem()
{
    const int ekey = GetId();
    return entries->GetEntry(ekey);
}
