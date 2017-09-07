#include <lem/solarix/Dictionary.h>
#include "SentenceEOL.h"

using namespace Solarix;

SentenceEOL::SentenceEOL(lem::Char_Stream::WideStream &stream, Solarix::Dictionary * dict, int language)
    : Solarix::SentenceBroker(stream, dict, language) {}

SentenceEOL::SentenceEOL(lem::Ptr<lem::Char_Stream::WideStream> stream, Solarix::Dictionary * dict, int language)
    : Solarix::SentenceBroker(stream, dict, language) {}

bool SentenceEOL::Fetch(lem::UFString & line, int & line_paragraph_id)
{
    line.clear();
    line_paragraph_id = cur_paragraph_id;

    if (eof)
        return false;

    while (!eof)
    {
        wchar_t c = GetChar();

        if (SentenceBroker::IsEndOfParagraphMarker(c))
        {
            cur_paragraph_id++;
            break;
        }
        else if (SentenceBroker::IsEndOfSentenceMarker(c))
        {
            break;
        }
        else if (c == WEOF)
        {
            eof = true;
            return true;
        }
        else if (c == '\n')
        {
            break;
        }
        else line.Add_Dirty(c);
    }

    line.calc_hash();
    line.trim();

    return true;
}
