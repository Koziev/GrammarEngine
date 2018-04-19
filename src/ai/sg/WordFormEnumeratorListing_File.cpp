#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordFormEnumerator_File.h>

using namespace Solarix;

WordFormEnumeratorListing_File::WordFormEnumeratorListing_File(WordEntries_File * _entries)
    : entries(_entries)
{
    started = false;
    finished = false;
    icur = -1;
    return;
}

bool WordFormEnumeratorListing_File::Fetch()
{
    if (!started)
    {
        Prefetch();
        started = true;
    }

    if (!finished)
    {
        icur++;
        finished = icur >= CastSizeToInt(hits.size());
    }

    return !finished;
}

int WordFormEnumeratorListing_File::GetEntryKey()
{
    return hits[icur].ekey;
}

int WordFormEnumeratorListing_File::GetFormIndex()
{
    return hits[icur].iform;
}

float WordFormEnumeratorListing_File::GetValue()
{
    return hits[icur].val;
}

int WordFormEnumeratorListing_File::GetMatchedWordIndex()
{
    return 0;
}

bool WordFormEnumeratorListing_File::HitsComparator(const Hit &a, const Hit &b)
{
    return a.val > b.val;
}
