#if !defined LEM_SQLITE_TEXT16__H
 #define LEM_SQLITE_TEXT16__H

 #include <lem/ufstring.h>
 #include <lem/ucstring.h>
 #include <lem/sqlite/sqlite3.h>

 namespace lem
 {
  class SqliteTxGuard
  {
   private: 
    struct sqlite3* hdb;
    bool committed;

   public:
    SqliteTxGuard(struct sqlite3* hdb);
    ~SqliteTxGuard(void);
    void Commit(void);
  };

  extern bool sqlite_init_serialized_mode();

  extern struct sqlite3* sqlite_open_serialized( const lem::UFString & connection_string );
  extern lem::Path sqlite_get_absolute_filepath( const lem::UFString & connection_string );


  extern lem::UFString sqlite_column_ufstring( sqlite3_stmt *stmt, int icol );
  extern lem::FString sqlite_column_fstring( sqlite3_stmt *stmt, int icol );
  extern lem::UCString sqlite_column_ucstring( sqlite3_stmt *stmt, int icol );
  extern lem::UFString sqlite_errmsg( struct sqlite3* hdb );
  extern int sqlite_select_int( struct sqlite3* hdb, const char *Select );
  extern int sqlite_select_int( struct sqlite3* hdb, const lem::FString & Select );
  extern void sqlite_begin_tx( struct sqlite3* hdb );
  extern void sqlite_commit_tx( struct sqlite3* hdb );
  extern void sqlite_rollback_tx( struct sqlite3* hdb );
  extern bool sqlite_does_table_exist( struct sqlite3* hdb, const char *TableName );
  extern bool sqlite_does_index_exist( struct sqlite3* hdb, const char *IndexName );
  extern void sqlite_escape( lem::UFString &str );
  extern void sqlite_escape( lem::FString &str );
  extern void sqlite_vacuum( struct sqlite3* hdb );
  extern void sqlite_execute( struct sqlite3* hdb, const char *sql );
 }

#endif
