#if !defined WordEntryEnumerator_SQLite__H
#define WordEntryEnumerator_SQLite__H 

#include <lem/solarix/WordEntryEnumerator.h>

namespace Solarix
{
    class SG_Entry;
    class WordEntries_SQLite;
    class LS_ResultSet_SQLITE;

    class WordEntryEnumerator_SQLite : public WordEntryEnumerator
    {
    private:
        LS_ResultSet_SQLITE *rs;
        WordEntries_SQLite *entries;

    public:
        WordEntryEnumerator_SQLite(LS_ResultSet_SQLITE *_rs, WordEntries_SQLite *_entries);
        virtual ~WordEntryEnumerator_SQLite();

        virtual bool Fetch() override;
        virtual int GetId() override;
        virtual const SG_Entry& GetItem() override;
    };

}

#endif
