#if !defined WordEntryEnumerator__H
 #define WordEntryEnumerator__H 

 namespace Solarix
 { 
  class SG_Entry;
  class WordEntryEnumerator
  {
   public:
    WordEntryEnumerator(void) {}
    virtual ~WordEntryEnumerator(void) {}

    virtual bool Fetch(void)=0;
    virtual int GetId(void)=0;
    virtual const SG_Entry& GetItem(void)=0;
  };

 }

#endif
