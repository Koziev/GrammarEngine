#if !defined LanguageEnumerator__H
#define LanguageEnumerator__H

#include <lem/noncopyable.h>

namespace Solarix
{
    class Languages;
    class LS_ResultSet;
    class LexiconStorage;
    class SG_Language;

    class LanguageEnumerator : lem::NonCopyable
    {
    private:
        Languages *langs;
        LexiconStorage *db;
        LS_ResultSet *rs;

    public:
        LanguageEnumerator(Languages *_langs, LexiconStorage *_db);
        ~LanguageEnumerator();

        bool Fetch();
        int GetId();
        const SG_Language& GetItem();
    };
}

#endif
