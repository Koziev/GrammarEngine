#include <lem/quantors.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntryEnumerator_File.h>

using namespace Solarix;

WordEntryEnumerator_File::WordEntryEnumerator_File(WordEntries_File *_entries)
    : entries(_entries), started(false), finished(false), ifound(UNKNOWN), id_class(UNKNOWN)
{
}


WordEntryEnumerator_File::WordEntryEnumerator_File(WordEntries_File *_entries, const lem::UCString &_name, int _id_class)
    : entries(_entries), started(false), finished(false), ifound(UNKNOWN), name(_name), id_class(_id_class)
{
}


bool WordEntryEnumerator_File::Fetch()
{
    if (!started)
    {
        started = true;
        finished = false;
        ifound = -1;
    }

    ifound++;

    if (!name.empty() || (id_class != UNKNOWN && id_class != ANY_STATE))
    {
        while (ifound < CastSizeToInt(entries->entry.size()))
        {
            const SG_Entry &e = entries->GetWordEntry(ifound);

            if (!name.empty() && !e.GetName().eqi(name))
            {
                ifound++;
                continue;
            }

            if (id_class != UNKNOWN && id_class != ANY_STATE && e.GetClass() != id_class)
            {
                ifound++;
                continue;
            }

            break;
        }
    }

    if (ifound >= CastSizeToInt(entries->size()))
        finished = true;

    return !finished;
}

int WordEntryEnumerator_File::GetId()
{
    LEM_CHECKIT_Z(!finished);
    return entries->GetWordEntry(ifound).GetKey();
}


const SG_Entry& WordEntryEnumerator_File::GetItem()
{
    LEM_CHECKIT_Z(!finished);
    return entries->GetWordEntry(ifound);
}
