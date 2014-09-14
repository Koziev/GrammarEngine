#ifndef SOL_NGRAMS_HANDLER__H
#define SOL_NGRAMS_HANDLER__H
#pragma once

 #if !defined SOL_NO_NGRAMS

 #include <lem/config.h>
 #include <map>
 #include <lem/path.h>
 #include <lem/containers.h>
 #include <lem/solarix/ngrams_dbms.h>

 namespace Solarix
 {
  class Ngrams;

  class NGramHandler
  {
   public:
    NGramHandler(void) {}
    virtual ~NGramHandler(void) {}

    virtual bool Do(
                    Solarix::Ngrams & ngrams,
                    int id_ngram,
                    int freq,
                    int id_word1,
                    const lem::UCString &word1
                   ) { return false; }

    virtual bool Do(
                    Solarix::Ngrams & ngrams,
                    int id_ngram,
                    int freq,
                    int id_word1,
                    int id_word2,
                    const lem::UCString &word1,
                    const lem::UCString &word2
                   ) { return false; }

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
                   ) { return false; }

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
                   ) { return false; }

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
                   ) { return false; }
  };
 }
#endif

#endif
