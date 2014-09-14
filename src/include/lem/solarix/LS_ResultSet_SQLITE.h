#if !defined LS_ResultSet_SQLITE__H
 #define LS_ResultSet_SQLITE__H

 #include <lem/sqlite.h>
 #include <lem/fstring.h>
 #include <lem/solarix/LS_ResultSet.h>

 namespace Solarix
 {
  class LS_ResultSet_SQLITE : public LS_ResultSet
  {
   private:
    sqlite3_stmt *stmt;

   public:
    LS_ResultSet_SQLITE( sqlite3_stmt *h );
    virtual ~LS_ResultSet_SQLITE(void);
    virtual bool Fetch(void);
    virtual int GetInt( int FieldIndex );
    virtual lem::UCString GetUCString( int FieldIndex );
    virtual lem::UFString GetUFString( int FieldIndex );
    virtual lem::FString GetFString( int FieldIndex );
  };
 }
#endif
