#if !defined ALPHABET_STORAGE_SQLITE__H
 #define ALPHABET_STORAGE_SQLITE__H

 #include <lem/sqlite.h>
 #include <lem/solarix/AlphabetStorage.h>

 namespace Solarix
 {
  class AlphabetStorage_SQLITE : public AlphabetStorage
  {
   private:
    lem::UFString sqlite_connection_string;
    struct sqlite3* hdb; // дескриптор БД тезауруса

    void CreateTables_Alphabets(void);
    void CreateTables_Coords(void);
    void CreateTables_Classes(void);
    void CreateTables_Entries(void);
    void CreateTables_Criteria(void);
    void CreateTables_Operations(void);
    void CreateTables_SyllabRules(void);

    void StoreCoordStates( int id_coord, const Solarix::GramCoord &coord );
    void StoreClassInternals( int id, const Solarix::GramClass &cls );

    void Execute( const lem::UFString &sql );
    void Execute( const lem::FString &sql );
    void Execute( const char *sql );
    void RaiseError( void );
    void RaiseError( const lem::FString &sql );
    void RaiseError( const char * sql );
    void RaiseError( const char *filename, int line );
    LS_ResultSet* ListByQuery( const char *sql );
    LS_ResultSet* ListByQuery( const lem::FString & sql );
    LS_ResultSet* ListByQuery( const lem::UFString & sql );
    int SelectInt( const lem::FString &Select );
    int LastInsertID(void);

   public:
    AlphabetStorage_SQLITE( const lem::UFString &connection_string );
    virtual ~AlphabetStorage_SQLITE(void);

    void CreateSchema(void);

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
