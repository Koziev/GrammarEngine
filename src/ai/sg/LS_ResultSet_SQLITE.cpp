#include <lem/sqlite_helpers.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>

using namespace lem;
using namespace Solarix;

LS_ResultSet_SQLITE::LS_ResultSet_SQLITE( sqlite3_stmt *h )
 : LS_ResultSet(NULL)
{
 LEM_CHECKIT_Z(h!=NULL);
 stmt = h;
 return;
}


LS_ResultSet_SQLITE::~LS_ResultSet_SQLITE(void)
{
 LEM_CHECKIT_Z(stmt!=NULL);
 sqlite3_finalize(stmt);
 stmt=NULL;
 return; 
}


bool LS_ResultSet_SQLITE::Fetch(void)
{
 LEM_CHECKIT_Z(stmt!=NULL);
 return sqlite3_step( stmt ) == SQLITE_ROW;
}


int LS_ResultSet_SQLITE::GetInt( int FieldIndex )
{
 LEM_CHECKIT_Z(stmt!=NULL);
 int res = sqlite3_column_int(stmt,FieldIndex);
 return res;  
}


lem::UCString LS_ResultSet_SQLITE::GetUCString( int FieldIndex )
{
 LEM_CHECKIT_Z(stmt!=NULL);
 return lem::sqlite_column_ucstring(stmt,FieldIndex);
}


lem::UFString LS_ResultSet_SQLITE::GetUFString( int FieldIndex )
{
 LEM_CHECKIT_Z(stmt!=NULL);
 return lem::sqlite_column_ufstring(stmt,FieldIndex);
}


lem::FString LS_ResultSet_SQLITE::GetFString( int FieldIndex )
{
 LEM_CHECKIT_Z(stmt!=NULL);
 return lem::sqlite_column_fstring(stmt,FieldIndex);
}
