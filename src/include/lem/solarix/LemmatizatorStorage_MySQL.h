#pragma once
#if !defined SOL_LEMMATIZATOR_MYSQL__H && defined SOL_MYSQL_DICTIONARY_STORAGE
#define SOL_LEMMATIZATOR_MYSQL__H

#include <lem/process.h>
#include <lem/RWULock.h>
#include <lem/solarix/LemmatizatorStorage.h>

namespace Solarix
{
    class StorageConnection_MySQL;
    class LemmatizatorStorage_MySQL : public LemmatizatorStorage
    {
    private:
#if defined LEM_THREADS
        lem::Process::RWU_Lock cs;
#endif

        StorageConnection_MySQL *cnx;

        std::map<lem::UCString, lem::UCString> lemma1_cache;

    public:
        LemmatizatorStorage_MySQL(StorageConnection_MySQL *_cnx);
        virtual ~LemmatizatorStorage_MySQL();

        virtual void Lemmatize(const lem::UCString &word, lem::MCollect<lem::UCString> &lemmas) override;
        virtual int Lemmatize(const lem::UCString &word, lem::UCString &lemma) override;
        virtual void Lemmatize(const lem::MCollect<lem::UCString> & words, lem::MCollect<lem::UCString> &lemmas) override;
    };
}

#endif
