// CD->07.03.2009
// LC->02.04.2018
// --------------

#if defined SOL_CAA

#include <lem/solarix/dictionary.h>
#include <lem/solarix/sentencebroker.h>
#include <lem/solarix/prefix_tree.h>

using namespace lem;
using namespace Solarix;

SegmentingSentenceTokenizer::SegmentingSentenceTokenizer(const Solarix::Dictionary &dict, int language)
    : SentenceTokenizer(dict, language)
{
    lookup = lem::Ptr<Solarix::CharNode>((Solarix::CharNode*)&dict.GetSynGram().GetPrefixTree(), null_deleter());
    seeker = dict.seeker;

    const SG_Language &lang = dict.GetSynGram().languages()[language];
    int ipar = lang.FindParam(L"WordDelimiters");

    if (ipar != UNKNOWN)
        delimiters += lang.params[ipar]->values.front().c_str();

    return;
}


bool SegmentingSentenceTokenizer::IsTokenDelimiter(wchar_t c) const
{
    if (delimiters.empty() && (lem::is_udelim(c) || lem::is_uspace(c) || c == L'\r' || c == L'\n'))
        return true;

    if (!delimiters.empty() && delimiters.find(c) != 0)
        return true;

    return false;
}


bool SegmentingSentenceTokenizer::IsUnbreakableFront(wchar_t c) const
{
    return lookup->probe(c) != nullptr;
}


bool SegmentingSentenceTokenizer::IsUnbreakableFront(const lem::UCString &s) const
{
    return lookup->match(s);
}

bool SegmentingSentenceTokenizer::IsMatched(const lem::UCString &s) const
{
    return seeker->Find(s, false) != UNKNOWN;
}

int SegmentingSentenceTokenizer::MatchLen(const lem::UFString & s, int i0) const
{
    return lookup->match_len(s.c_str() + i0);
}

#endif
