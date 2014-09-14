#pragma once
#if !defined SOL_LEMMATIZATOR_INTERFACE__H
 #define SOL_LEMMATIZATOR_INTERFACE__H

 #include <lem/noncopyable.h>
 #include <lem/ucstring.h>
 #include <lem/containers.h>

 namespace Solarix
 {
  class LemmatizatorStorage : lem::NonCopyable
  {
   public:
    LemmatizatorStorage(void) {}
    virtual ~LemmatizatorStorage(void) {}

    virtual void Lemmatize( const lem::UCString &word, lem::MCollect<lem::UCString> &lemmas )=0;
    virtual int Lemmatize( const lem::UCString &word, lem::UCString &lemma )=0;
    virtual void Lemmatize( const lem::MCollect<lem::UCString> & words, lem::MCollect<lem::UCString> &lemmas )=0;
  };
 }

#endif
