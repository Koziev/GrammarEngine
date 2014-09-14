#if !defined LexiconStorage_MySQL__h && defined SOL_MYSQL_DICTIONARY_STORAGE
 #define LexiconStorage_MySQL__h

 #include <lem/mysql_helpers.h>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/solarix/LexiconStorage.h>

 namespace Solarix
 {
  class LS_ResultSet_MySQL;
  class StorageConnection_MySQL;
  class TreeScorerPredicate;
  class TreeScorerResult;

  class LexiconStorage_MySQL : public LexiconStorage
  {
   private:
    StorageConnection_MySQL* cnx;

    void Connect(void);
    void Disconnect(void);

    LexiconStorage_MySQL(void);

    lem::UFString EncodeString( const lem::UFString &str ) const;

    void StoreClassInternals( int id, const SG_Class &cls );
    void StoreCoordStates( int id_coord, const Solarix::GramCoord &coord );
    void StoreLanguageInternals( const SG_Language &lang );

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_partofspeech;
    #endif
    std::map< lem::UCString, int > partofspeech_map;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_languages;
    #endif
    lem::MCollect<int> language_ids;
    void LoadAllLanguages(void);

    LS_ResultSet* ListByQuery( const lem::FString &Select );
    LS_ResultSet* ListByQuery( const lem::UFString &Select );

    int QueryInt( const lem::FString & sql );
    int QueryInt( const lem::UFString & sql );
    void Execute( const lem::FString & sql );
    void Execute( const lem::UFString & sql );
    int ExecuteAndReturnId( const lem::UFString & sql );
    int ExecuteAndReturnId( const lem::FString & sql );

    TreeScorerPoint* LoadTreeScorerPoint( const lem::UFString & sql );

   public:
    LexiconStorage_MySQL( StorageConnection_MySQL *_cnx );

    virtual ~LexiconStorage_MySQL(void);

    virtual void CreateSchema(void);
    virtual void CopyDatabase( const lem::Path & lexicon_db_path );

    virtual void BeginTx(void);
    virtual void CommitTx(void);
    virtual void RollBackTx(void);

    virtual TransactionGuard* GetTxGuard(void);

    virtual void CommitCompilation(void);

    virtual void AddAuxFormType( int id, const lem::UCString &name );
    virtual LS_ResultSet* ListAuxFormTypes(void);

    virtual int AddAuxForm( int ekey, int iform, int aux_type, const lem::UFString &aux_data );
    virtual int GetAuxForm( int ekey, int iform, int aux_type, lem::UFString &aux_data );
    virtual LS_ResultSet* ListAuxForms(void);
    virtual LS_ResultSet* ListAuxForms( int ekey, int iform );

    virtual int AddAuxEntryData( int ekey, int aux_type, const lem::UFString &aux_data );
    virtual int GetAuxEntryData( int ekey, int aux_type, lem::UFString &aux_data );
    virtual LS_ResultSet* ListAuxEntryData(void);
    virtual LS_ResultSet* ListAuxEntryData( int ekey );

    virtual int AddAuxWord( const lem::UCString & src, int aux_type, const lem::UFString &aux_data );
    virtual int GetAuxWord( const lem::UCString & src, int aux_type, lem::UFString &aux_data );
    virtual LS_ResultSet* ListAuxWords(void);
    virtual LS_ResultSet* ListAuxWords( const lem::UCString & src );

    virtual void ReplaceEntryKey( int old_ekey, int new_ekey );

    virtual int CountPhrases(void);
    virtual LS_ResultSet* ListPhrases(void);
    virtual int FindPhrase( const lem::UFString &text, bool ignore_case );
    virtual LS_ResultSet* ListPhrasesWithPrefix( const lem::UFString &mask, bool ignore_case );
    virtual bool GetPhrase( int id, SG_Phrase &phrase );
    virtual int AddPhrase( SG_Phrase &info );
    virtual void UpdatePhrase( const SG_Phrase &te );
    virtual void DeletePhrase( int id );
    virtual LS_ResultSet* ListPhraseNotes( int id_phrase );
    virtual bool GetPhraseNote( int id_note, SG_PhraseNote &note );
    virtual int GetPhraseNote( int id_entry, int note_type, SG_PhraseNote &note );
    virtual int FindPhraseNote( const lem::UFString &text, int type, int &te_id );
    virtual int AddPhraseNote( int id_phrase, int type, const lem::UFString &data );
    virtual void DeletePhraseNotes( int id_phrase );
    virtual void DeletePhraseNote( int id_note );

    virtual LS_ResultSet* ListCplxLeft(void);
    virtual int GetCplxLeft( const lem::UCString &headword, CplxLeft &info );
    virtual int StoreCplxLeft( const lem::UCString &headword, int minlen, int maxlen );
    virtual void ClearCplxLeft( const lem::UCString &headword );

    virtual bool GetPartOfSpeech( int id, SG_Class &cls );
    virtual LS_ResultSet* ListPartsOfSpeech(void);
    virtual int FindPartOfSpeech( const lem::UCString &name );
    virtual int CountPartsOfSpeech(void);
    virtual int AddPartOfSpeech( const lem::UCString &name );
    virtual int AddPartOfSpeech( const Solarix::SG_Class &cls );
    virtual void StorePartOfSpeech( int id, const SG_Class &cls );

    virtual bool GetCoord( int id, Solarix::GramCoord &coord );
    virtual LS_ResultSet* ListCoords(void);
    virtual int FindCoord( const lem::UCString &name );
    virtual int CountCoords(void);
    virtual int AddCoord( const lem::UCString &coord );
    virtual int AddCoord( Solarix::GramCoord &coord );
    virtual void StoreCoord( int id, Solarix::GramCoord &coord );

    virtual int CountLanguages(void);
    virtual int FindLanguage( const lem::UCString &name );
    virtual LS_ResultSet* ListLanguages(void);
    virtual bool GetLanguage( int id, SG_Language &lang );
    virtual int AddLanguage( SG_Language &lang );
    virtual void StoreLanguage( const SG_Language &lang );

    virtual int FindCriterion( const lem::UCString & name );
    virtual int StoreCriterion( const Criterion &x );
    virtual Criterion* GetCriterion( int id );
    virtual LS_ResultSet* EnumerateCriteria(void);

    // Preprocessor rules
    virtual LS_ResultSet* ListCropRules( int id_language );
    virtual LA_CropRule* GetPreprocessorCropRule( int id );
    virtual void DeletePreprocessorRules(void);
    virtual int FindCropRule( const lem::UCString &rule_name );

    // Recognition rules
    virtual LS_ResultSet* ListRecognitionRules( int id_language, bool including_word_matchers );
    virtual LA_RecognitionRule* GetRecognitionRule( int id );
    virtual void StoreRecognitionRule( LA_RecognitionRule *rule );
    virtual void DeleteRecognitionRules(void);
    virtual int FindRecognitionRule( const lem::UCString &rule_name );
    virtual LS_ResultSet* ListRecognitionRulesForWord( int id_language, const lem::UCString & word );


    virtual LS_ResultSet* ListPhoneticRules( int id_language );
    virtual LA_PhoneticRule* GetPhoneticRule( int id );
    virtual void StorePhoneticRule( LA_PhoneticRule *rule );
    virtual void DeletePhoneticRules(void);
    virtual int FindPhoneticRule( const lem::UCString &rule_name );

    virtual LS_ResultSet* ListWordEntrySet(void);
    virtual int FindWordEntrySet( const lem::UCString &rule_name );
    virtual void DeleteWordEntrySets(void);
    virtual WordEntrySetItem* GetWordEntrySet( int id );
    virtual void StoreWordEntrySet( WordEntrySetItem &ies );

    virtual LS_ResultSet* ListWordSet(void);
    virtual int FindWordSet( const lem::UCString &rule_name );
    virtual void DeleteWordSets(void);
    virtual WordSetItem* GetWordSet( int id );
    virtual void StoreWordSet( WordSetItem &words );

    virtual LS_ResultSet* ListUnbreakableRules( int id_language );
    virtual LA_UnbreakableRule* GetUnbreakableRule( int id );
    virtual void StoreUnbreakableRule( LA_UnbreakableRule *rule );
    virtual void DeleteUnbreakableRules(void);
    virtual int FindUnbreakableRule( const lem::UCString &rule_name );

    virtual LS_ResultSet* ListSynPatternTrees(void);
    virtual void DeleteSynPatternTrees(void);
    virtual void StoreSynPatternTree( int id_language, const lem::UCString &name, int id, const SynPatternTreeNode *tree, int pattern_type );
    virtual std::pair<SynPatternTreeNode*,lem::UCString> GetSynPatternTree( int id );
    virtual int FindSynPatternTree( int id_language, const lem::UCString &name, int pattern_type );
    virtual lem::UCString GetSynPatternTreeName( int id );

    virtual void DeleteProductionRules( const wchar_t *Marker );
    virtual int RegisterRuleGroup( const lem::UCString &name, const wchar_t *Marker );
    virtual int CountRuleGroups( const wchar_t *Marker );
    virtual int FindRuleGroup( const wchar_t *Marker, const lem::UCString &name );
    virtual LS_ResultSet* ListProductionRuleCategories( const wchar_t *Marker );


    virtual int RegisterProcedure( const lem::UCString &name, const wchar_t *Marker );
    virtual int FindProcedure( const lem::UCString &name, const wchar_t *Marker );
    virtual void DeleteProcedures( const wchar_t *Marker );
    virtual void DeletePatternMatchers( const wchar_t *Marker );
    virtual LS_ResultSet* ListPatternMatchers( const wchar_t *Marker );
    virtual LS_ResultSet* ListProcedures( const wchar_t *Marker );
    virtual TrPatternMatcher * GetPatternMatcher( int id );
    virtual TrProcedure * GetProcedure( int id );
    virtual void StoreProcedure( const wchar_t *Marker, const TrProcedure *p );
    virtual void StorePatternMatcher( const wchar_t *Marker, int type, const lem::UCString &name, TrPatternMatcher *m );
    virtual int FindPatternMatcher( const lem::UCString &name, const wchar_t *Marker );


    virtual void DeleteFunctions( const wchar_t *Marker );
    virtual TrFunctions* GetFunctions( const wchar_t *Marker );
    virtual void StoreFunctions( TrFunctions *functions, const wchar_t *Marker );

    virtual LS_ResultSet* ListLanguageUsage(void);
    virtual void StoreLanguageUsage( int id_language, bool is_input, bool is_output, bool is_default );

    virtual void DeleteSourceLocations(void);
    virtual int RegisterSourceFilename( const lem::Path &filepath );
    virtual int RegisterSourceLocation( int id_filename, int iline, int icolumn );
    virtual bool GetSourceFilename( int id_filename, lem::Path &filepath );
    virtual bool GetSourceLocation( int id_location, int &id_file, int &line, int &column );
    virtual int FindSourceLineBeginning( int id_filename, int line );
    virtual int FindClosestSourceLocation( int id_filename, int line );
    virtual LS_ResultSet* ListSourceFilenames(void);
    virtual LS_ResultSet* ListSourceLocations(void);

    virtual LS_ResultSet* ListParadigmaMatchers(void);
    virtual LS_ResultSet* ListParadigmas(void);
    virtual int StoreParadigma( const SG_DeclensionTable &p );
    virtual SG_DeclensionTable* GetParadigma( int id );

    virtual void AddEnding( const lem::UCString &ending, int id_language, int efreq );
    virtual bool GetEndingStat( int id_language, EndingStat &res );
    virtual bool FindEnding( int id_language, const lem::UCString &ending, int &nform, int &sumfreq );
    virtual LS_ResultSet* ListEndings(void);
    virtual LS_ResultSet* ListEndingStat(void);

    virtual void SetWordformFrequency( int id_entry, int iform, int frequency );
    virtual std::pair<bool,int> GetWordformFrequency( int id_entry, int iform );
    virtual LS_ResultSet* ListWordformFrequency(void);
    virtual void DeleteWordformFrequency(void);

    virtual bool FindMisspelling( int id_language, const lem::UCString &word, lem::MCollect<lem::UCString> &new_words );
    virtual void AddMisspelling( int id_language, const lem::UCString &word, const lem::UCString &new_word );
    virtual LS_ResultSet* ListMisspelling(void);
    virtual void DeleteMisspelling(void);

    virtual int RegisterCollocationSet( const lem::UCString &name, bool case_sensitive );
    virtual int FindCollocationSet( const lem::UCString &name );
    virtual void AddCollocationToSet( int id_set, const lem::MCollect<lem::UCString> &words );
    virtual void DeleteCollocationSets(void);
    virtual int FindCollocationInSet( int id_set, const lem::MCollect<lem::UCString> &words );
    virtual int FindCollocationSetHeadword( const lem::UCString &headword, int &min_len, int &max_len );
    virtual LS_ResultSet* ListCollocationSets(void);
    virtual LS_ResultSet* ListCollocationSetItems(void);
    virtual LS_ResultSet* ListCollocationSetHeadwords(void);

    virtual int StoreFacts( const KB_Facts * facts );
    virtual void UpdateFactsQueryMode( const KB_Facts * facts );
    virtual int StoreFact( const KB_Facts &facts, const KB_Fact * fact );
    virtual int StoreFactArgument(
                                  int id_fact,
                                  int arg_index,
                                  const KB_Argument & arg
                                 );
    virtual KB_Facts* LoadFacts( int id_facts );
    virtual LS_ResultSet* ListFactsInGroup( int id_facts );

    virtual KB_Fact* LoadFact( int id );
    virtual KB_Argument* LoadFactArgument( int id );
    virtual LS_ResultSet* ListFactIndex1();
    virtual LS_ResultSet* ListFactIndex2();

    virtual LS_ResultSet* ListFactGroups();
    virtual LS_ResultSet* ListFacts();
    virtual LS_ResultSet* ListFactArguments();

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
                                 );

    virtual void FindFactsByEntries(
                                    int id_facts,
                                    int n_arg,
                                    int id_entry1,
                                    int id_entry2,
                                    int id_entry3,
                                    int id_entry4,
                                    int id_entry5,
                                    lem::MCollect<int> & id_fact
                                   );

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
                               );

   virtual int RegisterWordformSet( const lem::UCString & set_name );
   virtual int FindWordformSet( const lem::UCString & set_name );
   virtual int StoreWordformSetCoords( const CP_Array & coords );
   virtual void StoreWordformSetItem( int id_set, const lem::UCString & lexeme, int ekey, int id_coords );
   virtual LS_ResultSet* ListWordformSets();
   virtual LS_ResultSet* ListWordformSetCoords();
   virtual LS_ResultSet* ListWordformSetItems();
   virtual int FindWordformSetItem( int id_set, const lem::UCString & word, int id_entry, int * id_coords );
   virtual void LoadWordformSetCoords( int id_coords, Solarix::CP_Array & pairs );
   virtual void DeleteWordformSets();


   virtual int StoreTreeScorerGroup( const lem::UCString & name, const TreeScorerGroupParams & params );
   virtual int FindTreeScorerGroup( const lem::UCString & name );
   virtual void LoadTreeScorerGroupParams( int id, TreeScorerGroupParams & params );
   virtual LS_ResultSet* ListTreeScorerGroups();
   virtual void StoreTreeScoreGroupMember( int id_group, int id_root );
   virtual LS_ResultSet* ListTreeScoreGroupMembers();
   virtual LS_ResultSet* ListGenericTreeScorers();

   virtual void ListTreeScoreGroupMembers( int id_group, lem::MCollect<int> & roots );

   virtual int RegisterTreeScorer_Word( const lem::UCString & word, int id_root_point, const lem::UFString & scoring_expression, int scoring_type, bool root_node, int id_group );
   virtual int RegisterTreeScorer_Wordentry( int EntryKey, int id_root_point, const lem::UFString & scoring_expression, int scoring_type, bool root_node, int id_group );
   virtual int RegisterTreeScorer_Generic( int id_root_point, const lem::UFString & scoring_expression, int scoring_type, int id_group );

   virtual int StoreTreeScorerPoint(
                                    int id_parent_point,
                                    int id_group,
                                    const lem::UCString & word, int id_entry, int id_metaentry, int id_class,
                                    const lem::UCString & wordset_name, const lem::UCString & wordentryset_name, const lem::UCString & wordformset_name,
                                    const CPE_Array & coords,
                                    int ThesaurusCheck_Link, int ThesaurusCheck_Entry,
                                    const lem::MCollect<CollocFilterSetChecker> & set_checkers,
                                    bool is_positive,
                                    int link_type,
                                    int relative_position,
                                    int id_src,
                                    int quantification_min_count,
                                    int quantification_max_count,
                                    int children_quantification_min_count,
                                    int children_quantification_max_count,
                                    const lem::UCString & marker,
                                    const lem::MCollect<BackRefCorrel> & back_correls
                                   );

   virtual void ListTreeScorers(
                                int id_group,
                                const Solarix::Word_Form & root,
                                lem::MCollect<int> & headpoint_ids,
                                lem::MCollect<TreeScorerResult*> & scores,
                                lem::MCollect<int> & anchor_is_root
                               );

   virtual void ListGenericTreeScorers(
                                       int id_group,
                                       lem::MCollect<int> & headpoint_ids,
                                       lem::MCollect<TreeScorerResult*> & scores
                                      );

   virtual TreeScorerPoint* LoadTreeScorerPoint( int id_point );
   virtual void LoadTreeScorerChildNodes( int id_point, lem::MCollect<TreeScorerPoint*> & scorer_leafs );
   virtual int GetTreeScorerHeadpointSrc( int id_point );

   virtual void StoreTreeScorerPredicate(
                                         int id_host_point,
                                         const lem::UCString & func_name,
                                         const lem::Collect<TreeScorerPredicateArg> & args
                                        );

   virtual void LoadTreeScorerPredicates( TreeScorerPoint * p );
   virtual TreeScorerPredicate* LoadTreeScorerPredicate( int id );

   virtual LS_ResultSet* ListTreeScorerPredicates();
   virtual LS_ResultSet* ListTreeScorerLemmas();
   virtual LS_ResultSet* ListTreeScorerWords();
   virtual LS_ResultSet* ListTreeScorerPoints();

   virtual int StoreMetaEntry( const lem::UCString & name, int id_class, const lem::MCollect<int> & entries );
   virtual int FindMetaEntry( const lem::UCString & name, int id_class );
   virtual void GetMetaEntryItems( int id_metaentry, lem::MCollect<int> & entries );
   virtual LS_ResultSet* ListMetaEntries();
   virtual bool DoesMetaEntryContains( int id_metaentry, int id_entry );
   virtual MetaEntry* LoadMetaEntry( int id );

   virtual int StoreWordAssoc_ByLemma( int src_location, int id_entry, int id_entry1, int score );
   virtual int StoreWordAssoc_ByMetaentry( int src_location, int id_entry, int id_metaentry1, int score );
   virtual int StoreWordAssoc_ByLexem( int src_location, int id_entry, const lem::UCString & word1, int score );
   virtual int StoreWordAssoc_ByThesaurusLink( int src_location, int id_entry, int link_type, int link_entry, int score );
   virtual int StoreWordAssoc_BySet( int src_location, int id_entry, const lem::UCString & set_name, int set_type, int score );
   virtual LS_ResultSet* ListAssociationsForEntry( int id_entry );
   virtual LS_ResultSet* ListAssociatedEntries();
   virtual WordAssociation* LoadAssocitation( int id );

   virtual LS_ResultSet* ListSkipTokenRules( int id_language );
   virtual SkipTokenRule* LoadSkipTokenRule( int id );
   virtual void StoreSkipTokenRule( int id_language, int src_location, int id_pattern, int score );

   virtual int StorePredicateTemplate( const lem::UFString & src, const lem::MCollect<lem::UCString> & params );
   virtual PredicateTemplate* LoadPredicateTemplate( int id );
   virtual LS_ResultSet* ListPredicateTemplate();

   virtual void StoreOmonym( const lem::UCString & entry_name, int id_class );
   virtual bool IsOmonym( const lem::UCString & entry_name, int id_class );
   virtual LS_ResultSet* ListOmonyms();
  };

 }

#endif
