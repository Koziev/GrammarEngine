#if !defined LexiconStorage_SQLITE__h
 #define LexiconStorage_SQLITE__h

 #include <lem/sqlite.h>
 #include <lem/path.h>
 #include <lem/solarix/LexiconStorage.h>

 namespace Solarix
 {
  struct EndingStat;
  class KB_Facts;
  class TreeScorerPredicate;
  class TreeScorerResult;

  class LexiconStorage_SQLITE : public LexiconStorage
  {
   private:
    lem::UFString sqlite_connection_string;
    struct sqlite3* hdb; // дескриптор БД тезауруса

    void Connect();
    void Disconnect();
    LexiconStorage_SQLITE();

    void Execute( const lem::UFString &sql );
    void Execute( const lem::FString &sql );
    void Execute( const char *sql );
    int ExecuteAndReturnId( const lem::UFString &sql );
    int ExecuteAndReturnId( const lem::FString &sql );

    void RaiseError( void );
    void RaiseError( const lem::FString &sql );
    void RaiseError( const char * sql );
    void RaiseError( const char *filename, int line );

    LS_ResultSet* ListByQuery( const lem::UFString & sql );
    LS_ResultSet* ListByQuery( const lem::FString & sql );
    LS_ResultSet* ListByQuery( const char *sql );

    int SelectInt( const lem::FString &Select );
    int SelectInt( const lem::UFString &Select );

    void CreateTables_MetaEntries();
    void CreateTables_AuxFormTypes();
    void CreateTables_AuxForms();
    void CreateTables_AuxEntryData();
    void CreateTables_Phrases();
    void CreateTables_PartsOfSpeech();
    void CreateTables_Coords();
    void CreateTables_Languages();
    void CreateTables_Criteria();
    void CreateTables_Preprocessor();
    void CreateTables_Recognizer();
    void CreateTables_PhoneticMatcher();
    void CreateTables_WordEntrySets();
    void CreateTables_Unbreakable();
    void CreateTables_Filters();
    void CreateTables_Functions();
    void CreateTables_SourceLocations();
    void CreateTables_Paradigmas();
    void CreateTables_Endings();
    void CreateTables_WordformFrequency();
    void CreateTables_WordAssoc();
    void CreateTables_Predicates();
    void CreateTables_Omonyms();


    void StoreClassInternals( int id, const SG_Class &cls );
    void StoreCoordStates( int id_coord, const Solarix::GramCoord &coord );
    void StoreLanguageInternals( const SG_Language &lang );

    TreeScorerPoint* LoadTreeScorerPoint( const lem::UFString & sql );
    void LoadTreeScorerPredicates( TreeScorerPoint * p );
    TreeScorerPredicate* LoadTreeScorerPredicate( int id );

   public:
    LexiconStorage_SQLITE( const lem::UFString &connection_string );

    virtual ~LexiconStorage_SQLITE();

    virtual void CreateSchema();
    virtual void CopyDatabase( const lem::Path & lexicon_db_path );

    virtual void BeginTx();
    virtual void CommitTx();
    virtual void RollBackTx();

    virtual TransactionGuard* GetTxGuard();

    virtual void CommitCompilation();

    virtual void AddAuxFormType( int id, const lem::UCString &name );
    virtual LS_ResultSet* ListAuxFormTypes();

    virtual int AddAuxForm( int ekey, int iform, int aux_type, const lem::UFString &aux_data );
    virtual int GetAuxForm( int ekey, int iform, int aux_type, lem::UFString &aux_data );
    virtual LS_ResultSet* ListAuxForms();
    virtual LS_ResultSet* ListAuxForms( int ekey, int iform );

    virtual int AddAuxEntryData( int ekey, int aux_type, const lem::UFString &aux_data );
    virtual int GetAuxEntryData( int ekey, int aux_type, lem::UFString &aux_data );
    virtual LS_ResultSet* ListAuxEntryData();
    virtual LS_ResultSet* ListAuxEntryData( int ekey );

    virtual int AddAuxWord( const lem::UCString & src, int aux_type, const lem::UFString &aux_data );
    virtual int GetAuxWord( const lem::UCString & src, int aux_type, lem::UFString &aux_data );
    virtual LS_ResultSet* ListAuxWords();
    virtual LS_ResultSet* ListAuxWords( const lem::UCString & src );

    virtual void ReplaceEntryKey( int old_ekey, int new_ekey );

    virtual int CountPhrases();
    virtual LS_ResultSet* ListPhrases();
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

    virtual LS_ResultSet* ListCplxLeft();
    virtual int GetCplxLeft( const lem::UCString &headword, CplxLeft &info );
    virtual int StoreCplxLeft( const lem::UCString &headword, int minlen, int maxlen );
    virtual void ClearCplxLeft( const lem::UCString &headword );

    virtual bool GetPartOfSpeech( int id, SG_Class &cls );
    virtual LS_ResultSet* ListPartsOfSpeech();
    virtual int FindPartOfSpeech( const lem::UCString &name );
    virtual int CountPartsOfSpeech();
    virtual int AddPartOfSpeech( const lem::UCString &name );
    virtual int AddPartOfSpeech( const Solarix::SG_Class &cls );
    virtual void StorePartOfSpeech( int id, const SG_Class &cls );

    virtual bool GetCoord( int id, Solarix::GramCoord &coord );
    virtual LS_ResultSet* ListCoords();
    virtual int FindCoord( const lem::UCString &name );
    virtual int CountCoords();
    virtual int AddCoord( const lem::UCString &coord );
    virtual int AddCoord( Solarix::GramCoord &coord );
    virtual void StoreCoord( int id, Solarix::GramCoord &coord );

    virtual int CountLanguages();
    virtual int FindLanguage( const lem::UCString &name );
    virtual LS_ResultSet* ListLanguages();
    virtual bool GetLanguage( int id, SG_Language &lang );
    virtual int AddLanguage( SG_Language &lang );
    virtual void StoreLanguage( const SG_Language &lang );

    virtual LS_ResultSet* ListLanguageUsage();
    virtual void StoreLanguageUsage( int id_language, bool is_input, bool is_output, bool is_default );

    virtual int FindCriterion( const lem::UCString & name );
    virtual int StoreCriterion( const Criterion &x );
    virtual Criterion* GetCriterion( int id );
    virtual LS_ResultSet* EnumerateCriteria();

    // Preprocessor rules
    virtual LS_ResultSet* ListCropRules( int id_language );
    virtual LA_CropRule* GetPreprocessorCropRule( int id );
    virtual void StorePreprocessorCropRule( LA_CropRule *rule );
    virtual void DeletePreprocessorRules();

    virtual int FindCropRule( const lem::UCString &rule_name );

    // Recognition rules
    virtual LS_ResultSet* ListRecognitionRules( int id_language, bool including_word_matchers );
    virtual LA_RecognitionRule* GetRecognitionRule( int id );
    virtual void StoreRecognitionRule( LA_RecognitionRule *rule );
    virtual void DeleteRecognitionRules();
    virtual int FindRecognitionRule( const lem::UCString &rule_name );
    virtual LS_ResultSet* ListRecognitionRulesForWord( int id_language, const lem::UCString & word );


    virtual LS_ResultSet* ListPhoneticRules( int id_language );
    virtual LA_PhoneticRule* GetPhoneticRule( int id );
    virtual void StorePhoneticRule( LA_PhoneticRule *rule );
    virtual void DeletePhoneticRules();
    virtual int FindPhoneticRule( const lem::UCString &rule_name );

    virtual LS_ResultSet* ListWordEntrySet();
    virtual int FindWordEntrySet( const lem::UCString &rule_name );
    virtual void DeleteWordEntrySets();
    virtual WordEntrySetItem* GetWordEntrySet( int id );
    virtual void StoreWordEntrySet( WordEntrySetItem &ies );

    virtual LS_ResultSet* ListWordSet();
    virtual int FindWordSet( const lem::UCString &rule_name );
    virtual void DeleteWordSets();
    virtual WordSetItem* GetWordSet( int id );
    virtual void StoreWordSet( WordSetItem &ies );

    virtual LS_ResultSet* ListUnbreakableRules( int id_language );
    virtual LA_UnbreakableRule* GetUnbreakableRule( int id );
    virtual void StoreUnbreakableRule( LA_UnbreakableRule *rule );
    virtual void DeleteUnbreakableRules();
    virtual int FindUnbreakableRule( const lem::UCString &rule_name );

    virtual LS_ResultSet* ListSynPatternTrees();
    virtual void DeleteSynPatternTrees();
    virtual void StoreSynPatternTree( int id_language, const lem::UCString &name, int id, const SynPatternTreeNode *tree, int pattern_type );
    virtual std::pair<SynPatternTreeNode*,lem::UCString> GetSynPatternTree( int id );
    virtual int FindSynPatternTree( int id_language, const lem::UCString & name, int pattern_type );
    virtual lem::UCString GetSynPatternTreeName( int id );

    virtual void DeleteFunctions( const wchar_t *Marker );
    virtual TrFunctions* GetFunctions( const wchar_t *Marker );
    virtual void StoreFunctions( TrFunctions *functions, const wchar_t *Marker );

    virtual void DeleteSourceLocations();
    virtual int RegisterSourceFilename( const lem::Path &filepath );
    virtual int RegisterSourceLocation( int id_filename, int iline, int icolumn );
    virtual bool GetSourceFilename( int id_filename, lem::Path &filepath );
    virtual bool GetSourceLocation( int id_location, int &id_file, int &line, int &column );
    virtual int FindSourceLineBeginning( int id_filename, int line );
    virtual int FindClosestSourceLocation( int id_filename, int line );
    virtual LS_ResultSet* ListSourceFilenames();
    virtual LS_ResultSet* ListSourceLocations();

    virtual LS_ResultSet* ListParadigmaMatchers();
    virtual LS_ResultSet* ListParadigmas();
    virtual int StoreParadigma( const SG_DeclensionTable &p );
    virtual SG_DeclensionTable* GetParadigma( int id );

    virtual void AddEnding( const lem::UCString &ending, int id_language, int efreq );
    virtual bool GetEndingStat( int id_language, EndingStat &res );
    virtual bool FindEnding( int id_language, const lem::UCString &ending, int &nform, int &sumfreq );
    virtual LS_ResultSet* ListEndings();
    virtual LS_ResultSet* ListEndingStat();

    virtual void SetWordformFrequency( int id_entry, int iform, int frequency );
    virtual std::pair<bool,int> GetWordformFrequency( int id_entry, int iform );
    virtual LS_ResultSet* ListWordformFrequency();
    virtual void DeleteWordformFrequency();

    virtual bool FindMisspelling( int id_language, const lem::UCString &word, lem::MCollect<lem::UCString> &new_words );
    virtual void AddMisspelling( int id_language, const lem::UCString &word, const lem::UCString &new_word );
    virtual LS_ResultSet* ListMisspelling();
    virtual void DeleteMisspelling();

    virtual int RegisterCollocationSet( const lem::UCString &name, bool case_sensitive );
    virtual int FindCollocationSet( const lem::UCString &name );
    virtual void AddCollocationToSet( int id_set, const lem::MCollect<lem::UCString> &words );
    virtual LS_ResultSet* ListCollocationSets();
    virtual LS_ResultSet* ListCollocationSetItems();
    virtual LS_ResultSet* ListCollocationSetHeadwords();
    virtual void DeleteCollocationSets();
    virtual int FindCollocationInSet( int id_set, const lem::MCollect<lem::UCString> &words );
    virtual int FindCollocationSetHeadword( const lem::UCString &headword, int &min_len, int &max_len );

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

    virtual LS_ResultSet* ListFactGroups();
    virtual LS_ResultSet* ListFacts();
    virtual LS_ResultSet* ListFactIndex1();
    virtual LS_ResultSet* ListFactIndex2();

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
   virtual void ListTreeScoreGroupMembers( int id_group, lem::MCollect<int> & roots );
   virtual LS_ResultSet* ListGenericTreeScorers();
   virtual LS_ResultSet* ListTreeScorerPredicates();

   virtual int RegisterTreeScorer_Word( const lem::UCString & word, int id_root_point, const lem::UFString & scoring_expression, int scorin_type, bool root_node, int id_group );
   virtual int RegisterTreeScorer_Wordentry( int EntryKey, int id_root_point, const lem::UFString & scoring_expression, int scorin_type, bool root_node, int id_group );
   virtual int RegisterTreeScorer_Generic( int id_root_point, const lem::UFString & scoring_expression, int scorin_type, int id_group );

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

   virtual void StoreTreeScorerPredicate(
                                         int id_host_point,
                                         const lem::UCString & func_name,
                                         const lem::Collect<TreeScorerPredicateArg> & args
                                        );

   virtual void ListTreeScorers(
                                int id_group,
                                const Solarix::Word_Form & root,
                                lem::MCollect<int> & headpoint_ids,
                                lem::MCollect<TreeScorerResult*> & score,
                                lem::MCollect<int> & anchor_is_root
                               );

   virtual void ListGenericTreeScorers(
                                       int id_group,
                                       lem::MCollect<int> & headpoint_ids,
                                       lem::MCollect<TreeScorerResult*> & score
                                      );

   virtual TreeScorerPoint* LoadTreeScorerPoint( int id_point );
   virtual void LoadTreeScorerChildNodes( int id_point, lem::MCollect<TreeScorerPoint*> & scorer_leafs );
   virtual int GetTreeScorerHeadpointSrc( int id_point );

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

   virtual int StorePredicateTemplate( const lem::UFString & src, const lem::MCollect<lem::UCString> & params );
   virtual PredicateTemplate* LoadPredicateTemplate( int id );
   virtual LS_ResultSet* ListPredicateTemplate();

   virtual void StoreOmonym( const lem::UCString & entry_name, int id_class );
   virtual bool IsOmonym( const lem::UCString & entry_name, int id_class );
   virtual LS_ResultSet* ListOmonyms();

   virtual void DeleteMorphologicalFilters();
  };

 }

#endif
