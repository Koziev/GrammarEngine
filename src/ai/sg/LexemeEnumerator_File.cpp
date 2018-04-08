#include <lem/solarix/LexemeEnumerator_File.h>
#include <lem/solarix/WordEntries_File.h>

using namespace Solarix;


LexemeEnumerator_File::LexemeEnumerator_File(WordEntries_File *_entries)
    : entries(_entries), icur(-1)
{
}


bool LexemeEnumerator_File::Fetch()
{
    icur++;
    return icur < CastSizeToInt(entries->ml_ref.size());
}


const Lexem* LexemeEnumerator_File::Get(Solarix::Lexem &lex)
{
    lex = entries->ml_ref[icur];
    return &entries->ml_ref[icur];
}

