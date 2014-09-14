#if !defined LEM_MYSQL_HELPERS__H && defined SOL_MYSQL_DICTIONARY_STORAGE
 #define LEM_MYSQL_HELPERS__H

 #include <lem/config.h>

 #if defined LEM_WINDOWS
  #include <windows.h>
 #endif

 #include <lem/mysql/mysql.h>

 #include <lem/ufstring.h>
 #include <lem/fstring.h>
 #include <lem/ucstring.h>

 namespace lem
 {
  extern int mysql_select_int( MYSQL* hdb, const char *Select );
  extern int mysql_column_int( MYSQL_ROW row, int icol );
  extern lem::UFString mysql_column_ufstring( MYSQL_ROW row, int icol );
  extern lem::FString mysql_column_fstring( MYSQL_ROW row, int icol );
  extern lem::UCString mysql_column_ucstring( MYSQL_ROW row, int icol );
  extern lem::UFString mysql_errmsg( MYSQL* hdb );
  extern void mysql_begin_tx( MYSQL* hdb );
  extern void mysql_commit_tx( MYSQL* hdb );
  extern void mysql_rollback_tx( MYSQL* hdb );
  extern void mysql_escape( lem::UFString &str );
  extern void mysql_escape( lem::FString &str );
 }

#endif
