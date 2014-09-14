#if !defined WordFormEnumerator_File__H
 #define WordFormEnumerator_File__H 

 #include <lem/ucstring.h>
 #include <lem/containers.h>
 #include <lem/solarix/WordFormEnumerator.h>
 

 namespace Solarix
 { 
  class SG_Entry;
  class WordEntries_File;
  class WordFormEnumerator_File1 : public WordFormEnumerator
  {
   private:
    WordEntries_File *entries;
    lem::UCString word;  
    int icur_entry, icur_form;
    bool finished;

    void FetchEntry(void);

   public:
    WordFormEnumerator_File1( WordEntries_File * _entries, const lem::UCString &_word );
    virtual ~WordFormEnumerator_File1(void) {}

    virtual bool Fetch(void);
    virtual int GetEntryKey(void);
    virtual int GetFormIndex(void);

    virtual float GetValue(void);
    virtual int GetMatchedWordIndex(void);
  };


/*
  class SG_EntryGroup;
  class WordFormEnumerator_File2 : public WordFormEnumerator
  {
   private:
    WordEntries_File *entries;
    lem::UCString word;
    const SG_EntryGroup *group;
    int icur_entry, icur_form;
    bool finished;

    void FetchEntry(void);


   public:
    WordFormEnumerator_File2( WordEntries_File * _entries, const lem::UCString &_word, const SG_EntryGroup *_group );
    virtual ~WordFormEnumerator_File2(void) {}

    virtual bool Fetch(void);
    virtual int GetEntryKey(void);
    virtual int GetFormIndex(void);
    virtual float GetValue(void);
    virtual int GetMatchedWordIndex(void);
  };
*/

  struct WordEntries_LookUpItem;
  class WordEntries_LookUp;
  class WordFormEnumerator_File2 : public WordFormEnumerator
  {
   private:
    WordEntries_File *entries;
    lem::UCString word;

    const WordEntries_LookUpItem & lexem_slot;
    const WordEntries_LookUp & lookup_table;

    int icur_entry, icur_form;
    bool finished;

    void FetchEntry(void);

   public:
    WordFormEnumerator_File2( WordEntries_File * _entries, const lem::UCString &_word, const WordEntries_LookUpItem & _lexem_slot, const WordEntries_LookUp & _lookup_table );
    virtual ~WordFormEnumerator_File2(void) {}

    virtual bool Fetch(void);
    virtual int GetEntryKey(void);
    virtual int GetFormIndex(void);
    virtual float GetValue(void);
    virtual int GetMatchedWordIndex(void);
  };


  class WordFormEnumerator_File3 : public WordFormEnumerator
  {
   private:
    WordEntries_File *entries;
    lem::MCollect<lem::UCString> words;
    int icur_entry, icur_form, imatched_word;
    bool finished;

    void FetchEntry(void);


   public:
    WordFormEnumerator_File3( WordEntries_File * _entries, const lem::MCollect<lem::UCString> &forms );
    virtual ~WordFormEnumerator_File3(void) {}

    virtual bool Fetch(void);
    virtual int GetEntryKey(void);
    virtual int GetFormIndex(void);
    virtual float GetValue(void);
    virtual int GetMatchedWordIndex(void);
  };


  class WordFormEnumeratorListing_File : public WordFormEnumerator
  {
   private:
    int icur;
    bool finished;
    bool started;

   protected:
    struct Hit
    {
     int ekey, iform;
     float val; 
    };

    static bool HitsComparator( const Hit &a, const Hit &b );

    lem::MCollect<Hit> hits;

    WordEntries_File *entries;
    virtual void Prefetch(void)=0;

   public:
    WordFormEnumeratorListing_File( WordEntries_File * _entries );
    virtual ~WordFormEnumeratorListing_File(void) {}

    virtual bool Fetch(void);

    virtual int GetEntryKey(void);
    virtual int GetFormIndex(void);
    virtual float GetValue(void);
    virtual int GetMatchedWordIndex(void);
  };




  class WordFormEnumeratorFuzzy_File : public WordFormEnumeratorListing_File
  {
   private:
    lem::UCString mask;
    float min_val;

    virtual void Prefetch(void);

   public:
    WordFormEnumeratorFuzzy_File(
                                 WordEntries_File * _entries,
                                 const lem::UCString &_mask,
                                 float _min_val
                                );
    virtual ~WordFormEnumeratorFuzzy_File(void) {}
  };



  class WordFormEnumeratorGlobbing_File : public WordFormEnumeratorListing_File
  {
   private:
    lem::UFString mask;

    virtual void Prefetch(void);

   public:
    WordFormEnumeratorGlobbing_File(
                                    WordEntries_File * _entries,
                                    const lem::UFString &_mask
                                   );
    virtual ~WordFormEnumeratorGlobbing_File(void) {}
  };

 }

#endif
