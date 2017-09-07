#if !defined SentenceEOL__H
#define SentenceEOL__H

#include <lem/solarix/sentencebroker.h>

class SentenceEOL : public Solarix::SentenceBroker
{
public:
    SentenceEOL(lem::Char_Stream::WideStream &stream, Solarix::Dictionary * dict, int language);
    SentenceEOL(lem::Ptr<lem::Char_Stream::WideStream> stream, Solarix::Dictionary * dict, int language);

    virtual bool Fetch(lem::UFString & line, int & line_paragraph_id);
};

#endif
