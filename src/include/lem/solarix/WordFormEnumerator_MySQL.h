#if !defined WordFormEnumerator_MySQL__H
 #define WordFormEnumerator_MySQL__H 

 #include <lem/containers.h>
 #include <lem/solarix/WordFormEnumerator.h>
  

 namespace Solarix
 { 
  class LS_ResultSet_MySQL;
  class WordEntries_MySQL;

  class WordFormEnumerator_MySQL : public WordFormEnumerator
  {
   private:
    lem::MCollect<lem::UCString> forms;
    LS_ResultSet_MySQL *rs;
    WordEntries_MySQL *entries;
   
   public:
    WordFormEnumerator_MySQL( LS_ResultSet_MySQL *_rs, WordEntries_MySQL *_entries );
    WordFormEnumerator_MySQL(
                             LS_ResultSet_MySQL *_rs,
                             WordEntries_MySQL *_entries,
                             const lem::MCollect<lem::UCString> &_forms
                            );

    virtual ~WordFormEnumerator_MySQL(void);

    virtual bool Fetch(void);
    virtual int GetEntryKey(void);
    virtual int GetFormIndex(void);
    virtual float GetValue(void);
    virtual int GetMatchedWordIndex(void);
  };

 }

#endif

