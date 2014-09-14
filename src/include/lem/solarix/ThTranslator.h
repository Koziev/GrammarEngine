#pragma once
#if !defined TH_TRANSLATOR__H
 #define TH_TRANSLATOR__H

 #include <lem/path.h>
 #include <lem/ptr_container.h>
 #include <lem/sqlite.h>

 namespace Solarix
 {

  class TranslatorThesaurus
  {
   private:
    struct sqlite3* hdb;

   public:
    TranslatorThesaurus(void);
    ~TranslatorThesaurus(void);
    void Open( const lem::Path &p );
    void Translate( const lem::UFString &in, lem::PtrCollect<lem::UFString> &outs );
    void GetTags( lem::PtrCollect<lem::UFString> &tags );
    bool IsLeftHeadword( const lem::UFString &w, int &minlen, int &maxlen );
  };
 
 }


#endif