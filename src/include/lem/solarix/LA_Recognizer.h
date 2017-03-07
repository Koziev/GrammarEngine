#if !defined LA_RECOGNIZER__H
 #define LA_RECOGNIZER__H

 #include <lem/process.h>
 #include <lem/ptr_container.h>
 #include <lem/RWULock.h>
 #include <lem/math/fp1.h>
 #include <lem/solarix/WordCoord.h>
 #include <lem/solarix/LA_ProjectInfo.h>
 #include <lem/solarix/ProjScore.h>

 namespace Solarix
 {
  struct LA_RecognitionRules;
  class Dictionary;
  class LexiconStorage;
  class LA_RecognitionTrace;

  class LA_Recognizer : lem::NonCopyable
  {
   private:
    Solarix::Dictionary *dict;
    LexiconStorage *storage;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs,cs_langs;
    #endif    

    lem::MCollect<int> all_langs;

    lem::MCollect<int> id_langs;
    lem::MCollect<LA_RecognitionRules*> rules;
    
    void DeleteRules(void);

    void LoadRules( int id_language );
    void LoadRulesFromStorage( int id_language );
    const LA_RecognitionRules* GetRules( int id_language ) const;

    void LoadAllLangs(void);

   public:
    LA_Recognizer( Solarix::Dictionary *Dict );
    ~LA_Recognizer(void);

    void Connect( LexiconStorage *Storage );

    bool Apply(
               const lem::UCString & normalized_word,
               const lem::UCString & original_word,
               float word_score,
               float min_bound,
               MCollect<Solarix::Word_Coord> &found_list,
               MCollect<ProjScore> &val_list,
               lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list,
               int id_language,
               bool only_forced,
               LA_RecognitionTrace *trace
              );

    bool RewriteMisspeltWord( int id_language, const lem::UCString &word, lem::MCollect<lem::UCString> &new_words );

    bool ApplyForSyllabs(
                         const lem::UCString &word,
                         float word_score,
                         const lem::MCollect<lem::UCString> & syllabs,
                         float min_bound,
                         lem::MCollect<Solarix::Word_Coord> &found_list,
                         lem::MCollect<ProjScore> &val_list,
                         lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list,
                         int id_language,
                         LA_RecognitionTrace *trace
                        );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt_Recognition( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    void LoadTxt_Misspelling( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    #endif
  };

 }

#endif
