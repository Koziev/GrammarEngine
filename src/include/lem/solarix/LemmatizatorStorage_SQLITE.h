#pragma once
#if !defined SOL_LEMMATIZATOR_SQLITE__H
 #define SOL_LEMMATIZATOR_SQLITE__H

 #include <lem/process.h>
 #include <lem/RWULock.h>
 #include <lem/solarix/LemmatizatorStorage.h>

 namespace Solarix
 {
  class StorageConnection_SQLITE;
  class LemmatizatorStorage_SQLITE : public LemmatizatorStorage
  {
   private:
    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs;
    #endif

    StorageConnection_SQLITE *cnx;

    std::map<lem::UCString,lem::UCString> lemma1_cache;

   public:
    LemmatizatorStorage_SQLITE( StorageConnection_SQLITE *_cnx );
    virtual ~LemmatizatorStorage_SQLITE(void);

    virtual void Lemmatize( const lem::UCString &word, lem::MCollect<lem::UCString> &lemmas );
    virtual int Lemmatize( const lem::UCString &word, lem::UCString &lemma );
    virtual void Lemmatize( const lem::MCollect<lem::UCString> & words, lem::MCollect<lem::UCString> &lemmas );
  };
 }

#endif
