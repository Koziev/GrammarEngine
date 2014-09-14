#if !defined LexemeEnumerator_SQLite__H
 #define LexemeEnumerator_SQLite__H

 #include <lem/solarix/LexemeEnumerator.h>

 namespace Solarix
 {
  class WordEntries_SQLite;
  class LS_ResultSet_SQLITE;
  class LexemeEnumerator_SQLite : public LexemeEnumerator
  {
   private:
    LS_ResultSet_SQLITE *rs;
    WordEntries_SQLite *entries;

   public:
    LexemeEnumerator_SQLite( WordEntries_SQLite *_entries, LS_ResultSet_SQLITE *_rs );
    virtual ~LexemeEnumerator_SQLite(void);
    
    virtual bool Fetch(void);
    virtual const Lexem* Get( Solarix::Lexem &lex );
  };
 }

#endif
