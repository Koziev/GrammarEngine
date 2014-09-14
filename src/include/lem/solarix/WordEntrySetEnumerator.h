#if !defined WordEntrySetEnumerator__H
 #define WordEntrySetEnumerator__H

 namespace Solarix
 {
  class LS_ResultSet;
  class WordEntrySet;
  struct WordEntrySetItem;

  class WordEntrySetEnumerator
  {
   private:
    LS_ResultSet *rs;
    WordEntrySet *sets;

   public:
    WordEntrySetEnumerator( LS_ResultSet *RS, WordEntrySet *Sets );
    ~WordEntrySetEnumerator(void);

    bool Fetch(void);
    int GetId(void);
    const WordEntrySetItem& GetItem(void);   
  };
 }

#endif
