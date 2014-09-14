#include <lem/solarix/lexem.h>
#include <lem/stl.h>
#include <lem/solarix/LexiconStorage_SQLITE.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/WordEntries_SQLite.h>
#include <lem/solarix/WordFormEnumerator_SQLite.h>

using namespace Solarix;

WordFormEnumerator_SQLite::WordFormEnumerator_SQLite( LS_ResultSet_SQLITE *_rs, WordEntries_SQLite *_entries )
 : rs(_rs), entries(_entries)
{
}

WordFormEnumerator_SQLite::WordFormEnumerator_SQLite(
                                                     LS_ResultSet_SQLITE *_rs,
                                                     WordEntries_SQLite *_entries,
                                                     const lem::MCollect<lem::UCString> &_forms
                                                    )
 : rs(_rs), entries(_entries), forms(_forms)
{
}



WordFormEnumerator_SQLite::~WordFormEnumerator_SQLite(void)
{
 lem_rub_off(rs);
}

bool WordFormEnumerator_SQLite::Fetch(void)
{
 return rs->Fetch();
}

int WordFormEnumerator_SQLite::GetEntryKey(void)
{
 return rs->GetInt(0);
}

int WordFormEnumerator_SQLite::GetFormIndex(void)
{
 return rs->GetInt(1);
}

float WordFormEnumerator_SQLite::GetValue(void)
{
 return 1.0F;
}

int WordFormEnumerator_SQLite::GetMatchedWordIndex(void)
{
 if( forms.size()>1 )
  {
   lem::UCString matched_word = rs->GetUCString(2);
   return forms.find(matched_word);
  }
 else
  {
   return 0;
  }
}
