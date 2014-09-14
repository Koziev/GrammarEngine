#if !defined WordSetEnumerator__H
 #define WordSetEnumerator__H

 namespace Solarix
 {
  class LS_ResultSet;
  class WordEntrySet;
  struct WordSetItem;

  class WordSetEnumerator
  {
   private:
    LS_ResultSet *rs;
    WordEntrySet *sets;

   public:
    WordSetEnumerator( LS_ResultSet *RS, WordEntrySet *Sets );
    ~WordSetEnumerator(void);

    bool Fetch(void);
    int GetId(void);
    const WordSetItem& GetItem(void);
  };
 }

#endif
