#if !defined LA_PREPROCESSOR__H
 #define LA_PREPROCESSOR__H

 #include <lem/RWULock.h>
 #include <lem/process.h>
 #include <lem/solarix/LA_CropRule.h>
 #include <lem/solarix/phrasema.h>

 namespace lem
 {
  namespace Iridium
  {
   class BethToken;
  }
 }

 namespace Solarix
 {
  class LA_RecognitionTrace;
  class LA_CropRule;

  // Набор правил для единственного языка
  struct LA_PreprocessorRules : lem::NonCopyable
  {
   lem::MCollect<LA_CropRule*> crop_rules; // для отсечения продуктивных приставок у несловарных форм в ходе проекции

   typedef std::multimap< LA_CropRule::HashType, const LA_CropRule* > CROP_RULES;
   CROP_RULES prefix_crop_rules;
   CROP_RULES affix_crop_rules;

   LA_PreprocessorRules(void) {}
   ~LA_PreprocessorRules(void);

   bool Crop(
             const lem::UCString &word,
             lem::MCollect<lem::UCString> &results,
             lem::MCollect<lem::Real1> &rels,
             LA_RecognitionTrace *trace
            ) const;
  };


  class Dictionary;
  class LexiconStorage;

  class LA_Preprocessor : lem::NonCopyable
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
    lem::MCollect<LA_PreprocessorRules*> rules;
    
    void DeleteRules(void);

    void LoadRules( int id_language );
    void LoadRulesFromStorage( int id_language );
    const LA_PreprocessorRules* GetRules( int id_language ) const;

    void LoadAllLangs(void);

   public:
    LA_Preprocessor( Solarix::Dictionary *Dict );
    ~LA_Preprocessor(void);

    void Connect( LexiconStorage *Storage );

    bool Crop(
              const lem::UCString &word,
              lem::MCollect<lem::UCString> &results,
              lem::MCollect<lem::Real1> &rels,
              int id_language,
              LA_RecognitionTrace *trace
             );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( const lem::Iridium::BethToken &head_token, lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    #endif
  
  };

 }

#endif
