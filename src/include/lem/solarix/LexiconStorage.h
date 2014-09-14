#if !defined LexiconStorage__h
 #define LexiconStorage__h

 #include <set>
 #include <lem/solarix/LS_ResultSet.h>
 #include <lem/solarix/CriteriaStorage.h>
 #include <lem/solarix/DictionaryStorage.h>
 #include <lem/solarix/BackRefCorrel.h>
 #include <lem/solarix/CollocFilterSetChecker.h>
 #include <lem/containers.h>

 
 namespace Solarix
 {
  class SG_Phrase;
  class SG_PhraseNote;
  class SG_LinkFlag;
  struct CplxLeft;
  class SG_Class;
  class GramCoord;
  class SG_Language;
  class CPE_Array;
  class Word_Form;

  struct TreeScorerGroupParams;
  class LA_PreprocessorRule;
  class LA_PreprocessorTokRule;
  class LA_CropRule;
  class LA_RecognitionRule;
  class FilterRule;
  class LA_PhoneticRule;
  class LA_UnbreakableRule;
  class SynPatternTreeNode;
  class PM_RulesInCategory;
  class TrFunctions;
  struct WordEntrySetItem;
  struct WordSetItem;
  class SG_DeclensionTable;
  struct EndingStat;
  class MetaEntry;

  struct CollocFilterInfo;
  struct CollocFilterDebugInfo;
  class CollocFilterPoint;
  struct CollocFilterPointHead;
  struct CollocFilterInnerConditionInfo;
  struct MorphFilterTreeNode;
  struct MorphFilterTreeNode2;
  struct MorphFilterResult;
  class TreeScorerPoint;
  class WordAssociation;
  class PredicateTemplate;
  class SynPatternPoint;
  class PatternLinks;
  class SparsePatternHandler;
  struct TreeScorerPredicateArg;
  class TreeScorerResult;

  class KB_Facts;
  class KB_Fact;
  class KB_Argument;
  class KB_CheckingResult;
  class CP_Array;

  class LexiconStorage : public DictionaryStorage, public CriteriaStorage
  {
   public:
    static wchar_t CollocationDelimiter;
    static wchar_t WORD_SET_DELIMITER;

    static void MergeCollocationWords( const lem::MCollect<lem::UCString> &words, lem::UFString &collocation );
    static void SplitCollocationWords( const lem::UFString &collocation, lem::MCollect<lem::UCString> &words );

   protected:
    LexiconStorage() {}

    void SortCoords( Solarix::CP_Array & sorted_coords ) const;
    void SerializeCoords( const Solarix::CP_Array & sorted_coords, lem::FString & str_coords );


   public:
    virtual ~LexiconStorage() {}

    virtual void CommitCompilation()=0;

    virtual void AddAuxFormType( int id, const lem::UCString &name )=0;
    virtual LS_ResultSet* ListAuxFormTypes()=0;

    virtual int AddAuxForm( int ekey, int iform, int aux_type, const lem::UFString &aux_data )=0;
    virtual int GetAuxForm( int ekey, int iform, int aux_type, lem::UFString &aux_data )=0;
    virtual LS_ResultSet* ListAuxForms()=0;
    virtual LS_ResultSet* ListAuxForms( int ekey, int iform )=0;

    virtual int AddAuxEntryData( int ekey, int aux_type, const lem::UFString &aux_data )=0;
    virtual int GetAuxEntryData( int ekey, int aux_type, lem::UFString &aux_data )=0;
    virtual LS_ResultSet* ListAuxEntryData()=0;
    virtual LS_ResultSet* ListAuxEntryData( int ekey )=0;

    virtual int AddAuxWord( const lem::UCString & src, int aux_type, const lem::UFString &aux_data )=0;
    virtual int GetAuxWord( const lem::UCString & src, int aux_type, lem::UFString &aux_data )=0;
    virtual LS_ResultSet* ListAuxWords()=0;
    virtual LS_ResultSet* ListAuxWords( const lem::UCString & src )=0;


    virtual void ReplaceEntryKey( int old_ekey, int new_ekey )=0;

    virtual int CountPhrases()=0;
    virtual int FindPhrase( const lem::UFString &text, bool ignore_case )=0;
    virtual LS_ResultSet* ListPhrasesWithPrefix( const lem::UFString &mask, bool ignore_case )=0;
    virtual LS_ResultSet* ListPhrases()=0;
    virtual bool GetPhrase( int id, SG_Phrase &phrase )=0;
    virtual int AddPhrase( SG_Phrase &info )=0;
    virtual void UpdatePhrase( const SG_Phrase &te )=0;
    virtual void DeletePhrase( int id )=0;
    virtual int FindPhraseNote( const lem::UFString &text, int type, int &te_id )=0;
    virtual LS_ResultSet* ListPhraseNotes( int id )=0;
    virtual bool GetPhraseNote( int id_note, SG_PhraseNote &note )=0;
    virtual int GetPhraseNote( int id_entry, int note_type, SG_PhraseNote &note )=0;
    virtual int AddPhraseNote( int id_phrase, int type, const lem::UFString &data )=0;
    virtual void DeletePhraseNotes( int id_phrase )=0;
    virtual void DeletePhraseNote( int id_note )=0;

    virtual LS_ResultSet* ListCplxLeft()=0;
    virtual int GetCplxLeft( const lem::UCString &headword, CplxLeft &info )=0;
    virtual int StoreCplxLeft( const lem::UCString &headword, int minlen, int maxlen )=0;
    virtual void ClearCplxLeft( const lem::UCString &headword )=0;

    virtual bool GetPartOfSpeech( int id, SG_Class &cls )=0;
    virtual LS_ResultSet* ListPartsOfSpeech()=0;
    virtual int FindPartOfSpeech( const lem::UCString &name )=0;
    virtual int CountPartsOfSpeech()=0;
    virtual int AddPartOfSpeech( const lem::UCString &name )=0;
    virtual int AddPartOfSpeech( const Solarix::SG_Class &cls )=0;
    virtual void StorePartOfSpeech( int id, const SG_Class &cls )=0;

    virtual bool GetCoord( int id, GramCoord &coord )=0;
    virtual LS_ResultSet* ListCoords()=0;
    virtual int FindCoord( const lem::UCString &name )=0;
    virtual int CountCoords()=0;
    virtual int AddCoord( const lem::UCString &coord )=0;
    virtual int AddCoord( Solarix::GramCoord &coord )=0;
    virtual void StoreCoord( int id, Solarix::GramCoord &coord )=0;

    virtual int CountLanguages()=0;
    virtual int FindLanguage( const lem::UCString &name )=0;
    virtual LS_ResultSet* ListLanguages()=0;
    virtual bool GetLanguage( int id, SG_Language &lang )=0;
    virtual int AddLanguage( SG_Language &lang )=0;
    virtual void StoreLanguage( const SG_Language &lang )=0;

    virtual LS_ResultSet* ListLanguageUsage()=0;
    virtual void StoreLanguageUsage( int id_language, bool is_input, bool is_output, bool is_default )=0;


    // Preprocessor rules
    virtual LS_ResultSet* ListCropRules( int id_language )=0;
    virtual LA_CropRule* GetPreprocessorCropRule( int id )=0;
    virtual void StorePreprocessorCropRule( LA_CropRule *rule )=0;
    virtual void DeletePreprocessorRules()=0;

    virtual int FindCropRule( const lem::UCString &rule_name )=0;

    // Recognition rules
    virtual LS_ResultSet* ListRecognitionRules( int id_language, bool including_word_matchers )=0;
    virtual LA_RecognitionRule* GetRecognitionRule( int id )=0;
    virtual void StoreRecognitionRule( LA_RecognitionRule *rule )=0;
    virtual void DeleteRecognitionRules()=0;
    virtual int FindRecognitionRule( const lem::UCString &rule_name )=0;
    virtual LS_ResultSet* ListRecognitionRulesForWord( int id_language, const lem::UCString & word )=0;

    // Phonetic-aware matching rules
    virtual LS_ResultSet* ListPhoneticRules( int id_language )=0;
    virtual LA_PhoneticRule* GetPhoneticRule( int id )=0;
    virtual void StorePhoneticRule( LA_PhoneticRule *rule )=0;
    virtual void DeletePhoneticRules()=0;
    virtual int FindPhoneticRule( const lem::UCString &rule_name )=0;

    virtual LS_ResultSet* ListWordEntrySet()=0;
    virtual int FindWordEntrySet( const lem::UCString &rule_name )=0;
    virtual void DeleteWordEntrySets()=0;
    virtual WordEntrySetItem* GetWordEntrySet( int id )=0;
    virtual void StoreWordEntrySet( WordEntrySetItem &ies )=0;

    virtual LS_ResultSet* ListWordSet()=0;
    virtual int FindWordSet( const lem::UCString &rule_name )=0;
    virtual void DeleteWordSets()=0;
    virtual WordSetItem* GetWordSet( int id )=0;
    virtual void StoreWordSet( WordSetItem &ies )=0;

    virtual LS_ResultSet* ListUnbreakableRules( int id_language )=0;
    virtual LA_UnbreakableRule* GetUnbreakableRule( int id )=0;
    virtual void StoreUnbreakableRule( LA_UnbreakableRule *rule )=0;
    virtual void DeleteUnbreakableRules()=0;
    virtual int FindUnbreakableRule( const lem::UCString &rule_name )=0;

    virtual LS_ResultSet* ListSynPatternTrees()=0;
    virtual void DeleteSynPatternTrees()=0;
    virtual void StoreSynPatternTree( int id_language, const lem::UCString &name, int id, const SynPatternTreeNode *tree, int pattern_type )=0;
    virtual lem::UCString GetSynPatternTreeName( int id )=0;
    virtual std::pair<SynPatternTreeNode*,lem::UCString> GetSynPatternTree( int id )=0;
    virtual int FindSynPatternTree( int id_language, const lem::UCString &name, int pattern_type )=0;

    virtual void DeleteFunctions( const wchar_t *Marker )=0;
    virtual TrFunctions* GetFunctions( const wchar_t *Marker )=0;
    virtual void StoreFunctions( TrFunctions *functions, const wchar_t *Marker )=0;

    virtual void DeleteSourceLocations()=0;
    virtual int RegisterSourceFilename( const lem::Path &filepath )=0;
    virtual int RegisterSourceLocation( int id_filename, int iline, int icolumn )=0;
    virtual bool GetSourceFilename( int id_filename, lem::Path &filepath )=0;
    virtual bool GetSourceLocation( int id_location, int &id_file, int &line, int &column )=0;
    virtual int FindSourceLineBeginning( int id_filename, int line )=0;
    virtual int FindClosestSourceLocation( int id_filename, int line )=0;
    virtual LS_ResultSet* ListSourceFilenames()=0;
    virtual LS_ResultSet* ListSourceLocations()=0;

    virtual LS_ResultSet* ListParadigmaMatchers()=0;
    virtual LS_ResultSet* ListParadigmas()=0;
    virtual int StoreParadigma( const SG_DeclensionTable &p )=0;
    virtual SG_DeclensionTable* GetParadigma( int id )=0;

    virtual void AddEnding( const lem::UCString &ending, int id_language, int efreq )=0;
    virtual bool GetEndingStat( int id_language, EndingStat &res )=0;
    virtual bool FindEnding( int id_language, const lem::UCString &ending, int &nform, int &sumfreq )=0;
    virtual LS_ResultSet* ListEndings()=0;
    virtual LS_ResultSet* ListEndingStat()=0;

    virtual void SetWordformFrequency( int id_entry, int iform, int frequency )=0;
    virtual std::pair<bool,int> GetWordformFrequency( int id_entry, int iform )=0;
    virtual LS_ResultSet* ListWordformFrequency()=0;
    virtual void DeleteWordformFrequency()=0;

    virtual bool FindMisspelling( int id_language, const lem::UCString &word, lem::MCollect<lem::UCString> &new_words )=0;
    virtual void AddMisspelling( int id_language, const lem::UCString &word, const lem::UCString &new_word )=0;
    virtual LS_ResultSet* ListMisspelling()=0;
    virtual void DeleteMisspelling()=0;

    virtual int RegisterCollocationSet( const lem::UCString &name, bool case_sensitive )=0;
    virtual int FindCollocationSet( const lem::UCString &name )=0;
    virtual void AddCollocationToSet( int id_set, const lem::MCollect<lem::UCString> &words )=0;
    virtual void DeleteCollocationSets()=0;
    virtual int FindCollocationInSet( int id_set, const lem::MCollect<lem::UCString> &words )=0;
    virtual int FindCollocationSetHeadword( const lem::UCString &headword, int &min_len, int &max_len )=0;    
    virtual LS_ResultSet* ListCollocationSets()=0;
    virtual LS_ResultSet* ListCollocationSetItems()=0;
    virtual LS_ResultSet* ListCollocationSetHeadwords()=0;

    virtual int StoreFacts( const KB_Facts * facts )=0;
    virtual void UpdateFactsQueryMode( const KB_Facts * facts )=0;

    virtual int StoreFact( const KB_Facts &facts, const KB_Fact * fact )=0;
    virtual int StoreFactArgument(
                                  int id_fact,
                                  int arg_index,
                                  const KB_Argument & arg
                                 )=0;

    virtual KB_Facts* LoadFacts( int id_facts )=0;
    virtual LS_ResultSet* ListFactsInGroup( int id_facts )=0;
    virtual KB_Fact* LoadFact( int id )=0;
    virtual KB_Argument* LoadFactArgument( int id )=0;

    virtual LS_ResultSet* ListFactGroups()=0;
    virtual LS_ResultSet* ListFacts()=0;
    virtual LS_ResultSet* ListFactIndex1()=0;
    virtual LS_ResultSet* ListFactIndex2()=0;
    virtual LS_ResultSet* ListFactArguments()=0;

    virtual int FindFactByEntries(
                                  int id_facts,
                                  int n_arg,
                                  int return_type,
                                  int id_entry1,
                                  int id_entry2,
                                  int id_entry3,
                                  int id_entry4,
                                  int id_entry5,
                                  KB_CheckingResult &result
                                 )=0;

    virtual void FindFactsByEntries(
                                    int id_facts,
                                    int n_arg,
                                    int id_entry1,
                                    int id_entry2,
                                    int id_entry3,
                                    int id_entry4,
                                    int id_entry5,
                                    lem::MCollect<int> & id_fact
                                   )=0;

    virtual int FindFactByWords(
                                int id_facts,
                                int n_arg,
                                int return_type,
                                const lem::UCString &word1,
                                const lem::UCString &word2,
                                const lem::UCString &word3,
                                const lem::UCString &word4,
                                const lem::UCString &word5,
                                KB_CheckingResult &result
                               )=0;

   virtual int RegisterWordformSet( const lem::UCString & set_name )=0;
   virtual int FindWordformSet( const lem::UCString & set_name )=0;
   virtual int StoreWordformSetCoords( const CP_Array & coords )=0;
   virtual void StoreWordformSetItem( int id_set, const lem::UCString & lexeme, int ekey, int id_coords )=0;
   virtual LS_ResultSet* ListWordformSets()=0;
   virtual LS_ResultSet* ListWordformSetCoords()=0;
   virtual LS_ResultSet* ListWordformSetItems()=0;
   virtual int FindWordformSetItem( int id_set, const lem::UCString & word, int id_entry, int * id_coords )=0;
   virtual void LoadWordformSetCoords( int id_coords, Solarix::CP_Array & pairs )=0;
   virtual void DeleteWordformSets()=0;


   virtual int StoreTreeScorerGroup( const lem::UCString & name, const TreeScorerGroupParams & params )=0;
   virtual int FindTreeScorerGroup( const lem::UCString & name )=0;
   virtual void LoadTreeScorerGroupParams( int id, TreeScorerGroupParams & params )=0;
   virtual LS_ResultSet* ListTreeScorerGroups()=0;
   virtual void StoreTreeScoreGroupMember( int id_group, int id_root )=0;
   virtual LS_ResultSet* ListTreeScoreGroupMembers()=0;
   virtual void ListTreeScoreGroupMembers( int id_group, lem::MCollect<int> & roots )=0;
   virtual int RegisterTreeScorer_Word( const lem::UCString & word, int id_root_point, const lem::UFString & scoring_expression, int scorin_type, bool root_node, int id_group )=0;
   virtual int RegisterTreeScorer_Wordentry( int EntryKey, int id_root_point, const lem::UFString & scoring_expression, int scorin_type, bool root_node, int id_group )=0;
   virtual int RegisterTreeScorer_Generic( int id_root_point, const lem::UFString & scoring_expression, int scorin_type, int id_group )=0;
   virtual LS_ResultSet* ListGenericTreeScorers()=0;
   virtual LS_ResultSet* ListTreeScorerPredicates()=0;


   virtual int StoreTreeScorerPoint(
                                    int id_parent_point,
                                    int id_group,
                                    const lem::UCString & word, int id_entry, int id_metaentry, int id_class,
                                    const lem::UCString & wordset_name, const lem::UCString & wordentryset_name, const lem::UCString & wordformset_name,
                                    const CPE_Array & coords,
                                    int ThesaurusCheck_Link, int ThesaurusCheck_Entry,
                                    const lem::MCollect<CollocFilterSetChecker> & set_checkers,
                                    bool is_positive,
                                    int link_type, int relative_position,
                                    int id_src,
                                    int quantification_min_count,
                                    int quantification_max_count,
                                    int children_quantification_min_count,
                                    int children_quantification_max_count,
                                    const lem::UCString & marker,
                                    const lem::MCollect<BackRefCorrel> & back_correls
                                   )=0;

   virtual void StoreTreeScorerPredicate( int id_host_point, const lem::UCString & func_name, const lem::Collect<TreeScorerPredicateArg> & args )=0;

   virtual void ListTreeScorers(
                                int id_group,
                                const Solarix::Word_Form & root,
                                lem::MCollect<int> & headpoint_ids,
                                lem::MCollect<TreeScorerResult*> & score,
                                lem::MCollect<int> & anchor_is_root
                               )=0;

   virtual void ListGenericTreeScorers(
                                       int id_group,
                                       lem::MCollect<int> & headpoint_ids,
                                       lem::MCollect<TreeScorerResult*> & score
                                      )=0;

   virtual TreeScorerPoint* LoadTreeScorerPoint( int id_point )=0;
   virtual void LoadTreeScorerChildNodes( int id_point, lem::MCollect<TreeScorerPoint*> & scorer_leafs )=0;
   virtual int GetTreeScorerHeadpointSrc( int id_point )=0;

   virtual LS_ResultSet* ListTreeScorerLemmas()=0;
   virtual LS_ResultSet* ListTreeScorerWords()=0;
   virtual LS_ResultSet* ListTreeScorerPoints()=0;

   // Группы статей
   virtual int StoreMetaEntry( const lem::UCString & name, int id_class, const lem::MCollect<int> & entries )=0;
   virtual int FindMetaEntry( const lem::UCString & name, int id_class )=0;
   virtual void GetMetaEntryItems( int id_metaentry, lem::MCollect<int> & entries )=0;
   virtual LS_ResultSet* ListMetaEntries()=0;
   virtual bool DoesMetaEntryContains( int id_metaentry, int id_entry )=0;
   virtual MetaEntry* LoadMetaEntry( int id )=0;

   // Ассоциации для снятия однотипной внешней омонимии
   virtual int StoreWordAssoc_ByLemma( int src_location, int id_entry, int id_entry1, int score )=0;
   virtual int StoreWordAssoc_ByMetaentry( int src_location, int id_entry, int id_metaentry1, int score )=0;
   virtual int StoreWordAssoc_ByLexem( int src_location, int id_entry, const lem::UCString & word1, int score )=0;
   virtual int StoreWordAssoc_ByThesaurusLink( int src_location, int id_entry, int link_type, int link_entry, int score )=0;
   virtual int StoreWordAssoc_BySet( int src_location, int id_entry, const lem::UCString & set_name, int set_type, int score )=0;
   virtual LS_ResultSet* ListAssociationsForEntry( int id_entry )=0;
   virtual LS_ResultSet* ListAssociatedEntries()=0;
   virtual WordAssociation* LoadAssocitation( int id )=0;

   virtual int StorePredicateTemplate( const lem::UFString & src, const lem::MCollect<lem::UCString> & params )=0;
   virtual PredicateTemplate* LoadPredicateTemplate( int id )=0;
   virtual LS_ResultSet* ListPredicateTemplate()=0;

   virtual void StoreOmonym( const lem::UCString & entry_name, int id_class )=0;
   virtual bool IsOmonym( const lem::UCString & entry_name, int id_class )=0;
   virtual LS_ResultSet* ListOmonyms()=0;


   virtual void DeleteMorphologicalFilters()=0;
  };

  extern void Storage_Data2Hex( const char *bytes, int size, lem::FString &str );
  extern void Storage_Hex2Data( const lem::FString &str, unsigned char **bytes, int *size );
 }

#endif
