#include <lem/solarix/SG_EntryGroup.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordEntryEnumerator_File.h>

using namespace Solarix;

WordEntryEnumerator_File_ByGroup::WordEntryEnumerator_File_ByGroup(
                                                                   WordEntries_File *_entries,
                                                                   const SG_EntryGroup *_group
                                                                  )
 : entries(_entries), group(_group), icur(-1), finished(false), N(CastSizeToInt(group->size()))
{
}


bool WordEntryEnumerator_File_ByGroup::Fetch(void)
{
 if(!finished)
  {
   icur++;
   if( icur>=N )
    finished=true;
  }

 return !finished;
}


int WordEntryEnumerator_File_ByGroup::GetId(void)
{
 if( finished )
  return UNKNOWN;

 const int ie = (*group)[icur];
 return entries->GetWordEntry(ie).GetKey();
}

const SG_Entry& WordEntryEnumerator_File_ByGroup::GetItem(void)
{
 LEM_CHECKIT_Z(!finished);
 const int ie = (*group)[icur];
 return entries->GetWordEntry(ie);
}
