#if !defined PartOfSpeechEnumerator__H
#define PartOfSpeechEnumerator__H

#include <lem/solarix/ClassEnumerator.h>

namespace Solarix
{
    class PartsOfSpeech;
    class LS_ResultSet;
    class LexiconStorage;
    class GramClass;

    class PartOfSpeechEnumerator : public ClassEnumerator
    {
    private:
        LS_ResultSet *rs;
        LexiconStorage *db;
        PartsOfSpeech *p;

    public:
        PartOfSpeechEnumerator(LexiconStorage *_db, PartsOfSpeech * _p);
        virtual ~PartOfSpeechEnumerator();

        virtual bool Fetch() override;
        virtual int GetId() override;
        virtual const GramClass& GetItem() override;
    };
}

#endif
