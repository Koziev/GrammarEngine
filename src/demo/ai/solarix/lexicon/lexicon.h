#if !defined LEXICON__H
 #define LEXICON__H

 #include <lem/solarix/dictionary.h>
 #include <lem/solarix/LA_ProjectInfo.h>
 #include <lem/solarix/PhraseEntries.h>
 #include <lem/solarix/SG_TagFilter.h>
 #include <lem/solarix/ProjScore.h>
 #include <lem/solarix/LA_RecognitionTrace.h>

 using namespace lem;
 using namespace Solarix;

 class LexiconDebugger : public LA_RecognitionTrace
 {
  private:
   Solarix::Dictionary *dict;
   lem::zbool trace;

  public:
   LexiconDebugger( Solarix::Dictionary *Dict ) : dict(Dict) {}

   void Trace( bool f ) { trace=f; }

   virtual ~LexiconDebugger(void) {}

   virtual void CropRuleApplied(
                                const lem::UCString &word_before,
                                const lem::UCString &word_after,
                                const LA_CropRule *rule
                               );

   virtual void Matched( const lem::UCString &word, const LA_RecognitionRule *rule );
   virtual void MatchedSyllable( const lem::UCString &word, const lem::UCString &syllable, const LA_RecognitionRule *rule );
   virtual void PhoneticRuleProduction( const lem::UCString &source, const lem::UCString &result, lem::Real1 val, const LA_PhoneticRule *rule );
   virtual void WordSyllabs( const lem::UCString &word, const lem::MCollect<lem::UCString> &slb_list );

   virtual void SyllabicBreakRuleHit(
                                     const SyllabContext & context,
                                     int cursor_pos,
                                     const SyllabRule & rule
                                    );

   virtual void SyllabicBreakRuleApplied(
                                         const SyllabContext & context,
                                         int cursor_pos,
                                         const SyllabRule & rule
                                        );
 };


 class LexiconShell
 {
  private:
   lem::Ptr<Dictionary> sol_id;
   lem::Ptr<LexiconDebugger> debugger;

   SynGram *SG;
   const GraphGram *GG;

   OFormatter nul_tty;

   // Text stream to store the unrecognized words.
   OUFormatter unfound_entry;

   lem::zbool fuzzy;
   lem::zbool first_turn;
   lem::zbool batch_mode;

   bool proj_words;
   bool print_proj;
   bool do_print_proj_coords; // Отображать координатные пары при проекции слов

   void LoadDictionary( const lem::Path &dict_path );

   LexiconDebugger* GetDebugger(void);

   int ShowMenu();
   void ExecuteMenu( int choice );
   void EnterMenuLoop();


   const UFString enter_cmd( const char *Prompt ) const;
   void ShowHelp(void) const;
   void SetMode( const UFString &str );
   void Exiting(void);
   void TestStemmer(void);
   void TestFlexer(void);
   void ShowParadigma(void);
   void TestThesaurus();
   void TestProjector(void);
   void TestNGrams();
   void SearchByIE();
   void FullMorphologyAnalysis(
                               const UFString &word,
                               bool print_projections,
                               bool print_links
                              );
   void MorphologyAnalysis( const UFString &word );
   void ThesaurusQuery( const UFString &word, bool synonyms, bool translations, const Solarix::SG_TagFilter* tags );
   void Show_Semnet( const UFString &word, bool synonyms, bool translations, const Solarix::SG_TagFilter* tags );
   void Display_Projects(
                         const MCollect<Word_Coord> &res,
                         const MCollect<ProjScore> &val_list,
                         const lem::PtrCollect<LA_ProjectInfo> &prj_extra_inf,
                         bool print_projections,
                         bool print_links
                        );

   void PrintPhrase( SynGram &sg, SG_Phrase & frz );
   void SearchByName(void);

   void ShowStatistics(void);
   void ShowThesaurusStatistics(void);
   void ShowLexiconStatistics(void);
   void ShowSyllabicBreaks(void);


  public:
   LexiconShell( const lem::Path &dict_path, bool batch=false, bool write_unfound_entries=false );
   ~LexiconShell(void);

   void main_loop( bool show_menu, const lem::MCollect<int>& menu );
   void ProcessFile( const lem::Path &filename );
   void SearchNGrams( const lem::Path &filename );
 };

#endif
