#if !defined LexemeEnumerator_MySQL__H && defined SOL_MYSQL_DICTIONARY_STORAGE
#define LexemeEnumerator_MySQL__H

#include <lem/solarix/LexemeEnumerator.h>

namespace Solarix
{
    class WordEntries_MySQL;
    class LS_ResultSet_MySQL;
    class LexemeEnumerator_MySQL : public LexemeEnumerator
    {
    private:
        LS_ResultSet_MySQL *rs;
        WordEntries_MySQL *entries;

    public:
        LexemeEnumerator_MySQL(WordEntries_MySQL *_entries, LS_ResultSet_MySQL *_rs);
        virtual ~LexemeEnumerator_MySQL();

        virtual bool Fetch() override;
        virtual const Lexem* Get(Solarix::Lexem &lex) override;
    };
}

#endif
