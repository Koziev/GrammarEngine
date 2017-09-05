#if !defined NGRAM_PRINTER__H
#define NGRAM_PRINTER__H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/LA_ProjectInfo.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/ProjScore.h>

#include <lem/solarix/NGramHandler.h>

// Класс-visitor для распечатки содержимого базы N-грамм.
class NGramPrinter : public Solarix::NGramHandler
{
public:
    NGramPrinter();

    virtual bool Do(
        Solarix::Ngrams & ngrams,
        int id_ngram,
        int freq,
        int id_word1,
        const lem::UCString &word1
    );

    virtual bool Do(
        Solarix::Ngrams & ngrams,
        int id_ngram,
        int freq,
        int id_word1,
        int id_word2,
        const lem::UCString &word1,
        const lem::UCString &word2
    );

    virtual bool Do(
        Solarix::Ngrams &ngrams,
        int id_ngram,
        int freq,
        int id_word1,
        int id_word2,
        int id_word3,
        const lem::UCString &word1,
        const lem::UCString &word2,
        const lem::UCString &word3
    );

    virtual bool Do(
        Solarix::Ngrams &ngrams,
        int id_ngram,
        int freq,
        int id_word1,
        int id_word2,
        int id_word3,
        int id_word4,
        const lem::UCString &word1,
        const lem::UCString &word2,
        const lem::UCString &word3,
        const lem::UCString &word4
    );

    virtual bool Do(
        Solarix::Ngrams &ngrams,
        int id_ngram,
        int freq,
        int id_word1,
        int id_word2,
        int id_word3,
        int id_word4,
        int id_word5,
        const lem::UCString &word1,
        const lem::UCString &word2,
        const lem::UCString &word3,
        const lem::UCString &word4,
        const lem::UCString &word5
    );
};

#endif
