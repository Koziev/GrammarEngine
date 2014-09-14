#if !defined WordEntryEnumerator_MySQL__H && defined SOL_MYSQL_DICTIONARY_STORAGE
 #define WordEntryEnumerator_MySQL__H 

 #include <lem/solarix/WordEntryEnumerator.h>

 namespace Solarix
 { 
  class SG_Entry;
  class WordEntries_MySQL;
  class LS_ResultSet_MySQL;

  class WordEntryEnumerator_MySQL : public WordEntryEnumerator
  {
   private:
    LS_ResultSet_MySQL *rs;
    WordEntries_MySQL *entries;

   public:
    WordEntryEnumerator_MySQL( LS_ResultSet_MySQL *_rs, WordEntries_MySQL *_entries );
    virtual ~WordEntryEnumerator_MySQL(void);

    virtual bool Fetch(void);
    virtual int GetId(void);
    virtual const SG_Entry& GetItem(void);
  };

 }

#endif
