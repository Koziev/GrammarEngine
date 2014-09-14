#if !defined WordFormEnumerator__H
 #define WordFormEnumerator__H 


 namespace Solarix
 { 
  class SG_Entry;
  class WordFormEnumerator
  {
   public:
    WordFormEnumerator(void) {}
    virtual ~WordFormEnumerator(void) {}

    virtual bool Fetch(void)=0;
    virtual int GetEntryKey(void)=0;
    virtual int GetFormIndex(void)=0;
    virtual float GetValue(void)=0;
    virtual int GetMatchedWordIndex(void)=0;
  };

 }

#endif
