#if !defined ALPHABET_STORAGE_MYSQL__H && defined SOL_MYSQL_DICTIONARY_STORAGE
 #define ALPHABET_STORAGE_MYSQL__H

 #include <lem/solarix/AlphabetStorage.h>

 namespace Solarix
 {
  class StorageConnection_MySQL;

  class AlphabetStorage_MySQL : public AlphabetStorage
  {
   private:
    StorageConnection_MySQL *cnx;

    LS_ResultSet* ListByQuery( const lem::FString &Select );
    LS_ResultSet* ListByQuery( const lem::UFString &Select );

    int SelectInt( const lem::FString & sql );
    int SelectInt( const char *sql );

    void Execute( const lem::UFString & sql );
    void Execute( const lem::FString & sql );
    int ExecuteAndReturnId( const lem::FString & sql );
    int ExecuteAndReturnId( const lem::UFString & sql );

   public:
    AlphabetStorage_MySQL( StorageConnection_MySQL *_cnx );
    virtual ~AlphabetStorage_MySQL(void);

    virtual Alphabet* GetAlphabet( int id );
    virtual int FindAlphabet( const lem::UCString &name );
    virtual LS_ResultSet* ListAlphabets(void);
    virtual int AddAlphabet( const lem::UCString &name );
    virtual void StoreAlphabet( const Alphabet &a );
    virtual int CountAlphabets(void);

    virtual bool GetCoord( int id, GramCoord &coord );
    virtual LS_ResultSet* ListCoords(void);
    virtual int FindCoord( const lem::UCString &name );
    virtual int CountCoords(void);
    virtual int AddCoord( const lem::UCString &coord );
    virtual int AddCoord( Solarix::GramCoord &coord );
    virtual void StoreCoord( int id, Solarix::GramCoord &coord );

    virtual bool GetClass( int id, GramClass &cls );
    virtual LS_ResultSet* ListClasses(void);
    virtual int FindClass( const lem::UCString &name );
    virtual int CountClasses(void);
    virtual int AddClass( const lem::UCString &name );
    virtual int AddClass( const Solarix::GramClass &cls );
    virtual void StoreClass( int id, const GramClass &cls );

    virtual void FindSymbol( lem::uint32_t code, lem::MCollect<Solarix::Word_Coord> &projs );
    virtual void FindSymbol( lem::uint32_t code, lem::MCollect<Solarix::Word_Coord> &projs, int AlphabetID );
    virtual void FindSymbol( lem::uint32_t code, lem::MCollect<Solarix::Word_Coord> &projs, const lem::MCollect<int> & AlphabetID );

    virtual int StorePairs( const lem::MCollect<GramCoordPair> & pairs );
    virtual void LoadPairs( int id_pairs, lem::MCollect<GramCoordPair> & pairs );

    virtual int StoreEntry( const GG_Entry &e );
    virtual GG_Entry* LoadEntry( int id );
    virtual LS_ResultSet* ListEntries(void);
    virtual int CountEntries(void);
    virtual int CountEntryForms(void);

    virtual void CopyDatabase( const lem::Path & alphabet_db_path );

    virtual int FindCriterion( const lem::UCString & name );
    virtual int StoreCriterion( const Criterion &x );
    virtual Criterion* GetCriterion( int id );
    virtual LS_ResultSet* EnumerateCriteria(void);

    virtual LS_ResultSet* ListCharOperations(void);
    virtual GG_CharOperation* GetCharOperation( int id );
    virtual int StoreCharOperation( GG_CharOperation *operation );
    virtual int FindCharOperation( const lem::UCString &name );

    virtual void DeleteSyllabRules(void);
    virtual int StoreSyllabRule( const lem::UCString &rule_name, int id_language, int id_src, int cursor_shift );
    virtual void StoreSyllabConditionPoint(
                                           int id_rule,
                                           int point_index, 
                                           const lem::MCollect<lem::uint32_t> &codes,
                                           int id_class,
                                           int id_entry,
                                           int id_coord0, int id_state0,
                                           bool is_left_boundary, bool is_right_boundary,
                                           bool is_positive
                                          );
    virtual void StoreSyllabResultPoint(
                                        int id_rule,
                                        int point_index, 
                                        int copy_index,
                                        int merge_index0,
                                        int merge_count
                                       );

    virtual LS_ResultSet* ListSyllabRulesForLanguage( int id_language );
    virtual LS_ResultSet* ListSyllabRules(void);
    virtual LS_ResultSet* ListSyllabConditionPoints(void);
    virtual LS_ResultSet* ListSyllabResultPoints(void);
    virtual SyllabRule * LoadSyllabRule( int id_rule );
    virtual LS_ResultSet* ListSyllabConditionPointsForRule( int id_rule );
    virtual LS_ResultSet* ListSyllabResultPointsForRule( int id_rule );
  };
 }

#endif
