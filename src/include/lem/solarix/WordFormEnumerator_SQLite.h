#if !defined WordFormEnumerator_SQLite__H
 #define WordFormEnumerator_SQLite__H 

 #include <lem/containers.h>
 #include <lem/solarix/WordFormEnumerator.h>
  

 namespace Solarix
 { 
  class LS_ResultSet_SQLITE;
  class WordEntries_SQLite;

  class WordFormEnumerator_SQLite : public WordFormEnumerator
  {
   private:
    lem::MCollect<lem::UCString> forms;
    LS_ResultSet_SQLITE *rs;
    WordEntries_SQLite *entries;
   
   public:
    WordFormEnumerator_SQLite( LS_ResultSet_SQLITE *_rs, WordEntries_SQLite *_entries );
    WordFormEnumerator_SQLite(
                              LS_ResultSet_SQLITE *_rs,
                              WordEntries_SQLite *_entries,
                              const lem::MCollect<lem::UCString> &_forms
                             );

    virtual ~WordFormEnumerator_SQLite(void);

    virtual bool Fetch(void);
    virtual int GetEntryKey(void);
    virtual int GetFormIndex(void);
    virtual float GetValue(void);
    virtual int GetMatchedWordIndex(void);
  };

 }

#endif
