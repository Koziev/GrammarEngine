#if !defined WordEntries_SQLite__H
 #define WordEntries_SQLite__H

 #include <map>
 #include <lem/process.h>
 #include <lem/sqlite_helpers.h>
 #include <lem/solarix/BaseRef.h>
 #include <lem/solarix/coord_pair.h>
 #include <lem/RWULock.h>

 #if defined SOL_LOADTXT
 #include <lem/solarix/LexemDictionary.h>
 #endif

 #include <lem/solarix/WordEntries_SQL.h>

 namespace Solarix
 {
  class StorageConnection_SQLITE;
  class SynGram;
  struct Dictionary_Config;

  class WordEntries_SQLite : public WordEntries_SQL
  {
   private:
    StorageConnection_SQLITE *cnx;

    virtual SG_Entry* LoadEntryFromDb_Impl( int ekey );
    virtual int RegisterLexemeInDatabase( const lem::UCString & lex );
    virtual int RegisterCoordPairsInDatabase( const lem::UFString &int_pairs, const lem::UFString &str_pairs );
    virtual int GetMaxMultilexemLen_Impl(void);
    virtual bool IsMultilexemHead_Impl( const lem::UCString &word, MultiLexemInfo &info );
    virtual bool IsMultilexemForm_Impl( const Solarix::Lexem &lex );
    virtual int FindEntry_Impl( const lem::UCString &word_name, int id_class );
    virtual void GetUEntries_Impl(void);
    virtual int GetPredefinedEntryKey_Impl( int index );
    virtual int FindQuantorEntry_Impl( int id_class );

   public:
    WordEntries_SQLite( SynGram &_sg, StorageConnection_SQLITE *_cnx, const Dictionary_Config &cfg );
    virtual ~WordEntries_SQLite(void);

    virtual int CountEntries( int id_class, int id_language );
    virtual int CountForms( int id_language );

    virtual bool IsWordForm( const Solarix::Lexem &lex );

    virtual int FindEntryOmonym( const Lexem& lname, int iclass, const Solarix::GramCoordPair &p );
    virtual int FindEntryOmonym( const Lexem& lname, int iclass, const lem::MCollect<Solarix::GramCoordPair> &p );
    virtual int FindEntryOmonym( const Lexem& lname, int iclass, const ExactWordEntryLocator &locator );

    //virtual WordEntryEnumerator* ListEntries( const lem::triple<wchar_t,wchar_t,wchar_t> & prefix3 );
    virtual WordEntryEnumerator* ListEntries( const lem::UCString &name, int id_class );
    virtual WordEntryEnumerator* ListEntries(void);

    virtual Word_Coord FindWordForm( const lem::UCString& name );
    virtual WordFormEnumerator* ListWordForms( const lem::UCString &form, bool allow_nonterminals );
    virtual WordFormEnumerator* ListWordForms( const lem::MCollect<lem::UCString> &forms );
    virtual WordFormEnumerator* ListWordForms_Fuzzy( const lem::UCString &word, float min_val );
    virtual WordFormEnumerator* ListWordForms_Globbing( const lem::UFString &mask );

    virtual int CountLexemes(void);
    virtual LexemeEnumerator* ListLexemes(void);

    #if defined SOL_LOADTXT
    virtual int LoadEntry( lem::StrParser<lem::UFString> &txt );
    #endif
  };

 }

#endif
