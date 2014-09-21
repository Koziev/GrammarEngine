#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/solarix/MySQLCnx.h>
#include <lem/mysql_helpers.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>

using namespace lem;
using namespace Solarix;

LS_ResultSet_MySQL::LS_ResultSet_MySQL( MySQLCnx *_cnx, MYSQL_RES *h, TransactionGuard *tx )
 : LS_ResultSet(tx), cnx(_cnx), stmt(h)
{
 LEM_CHECKIT_Z(h!=NULL);
 row = NULL;
 return;
}


LS_ResultSet_MySQL::~LS_ResultSet_MySQL(void)
{
 LEM_CHECKIT_Z(stmt!=NULL);
 mysql_free_result(stmt);
 stmt=NULL;

 if( read_tx.get()!=NULL )
  read_tx->Commit();

 #if defined LEM_THREADS
 cnx->cs.Leave();
 #endif
 return; 
}


bool LS_ResultSet_MySQL::Fetch(void)
{
 LEM_CHECKIT_Z(stmt!=NULL);
 row = mysql_fetch_row(stmt);
 return row!=NULL;
}


int LS_ResultSet_MySQL::GetInt( int FieldIndex )
{
 LEM_CHECKIT_Z(stmt!=NULL);
 int res = lem::mysql_column_int(row,FieldIndex);
 return res;  
}


lem::UCString LS_ResultSet_MySQL::GetUCString( int FieldIndex )
{
 LEM_CHECKIT_Z(stmt!=NULL);
 return lem::mysql_column_ucstring(row,FieldIndex);
}

lem::UFString LS_ResultSet_MySQL::GetUFString( int FieldIndex )
{
 LEM_CHECKIT_Z(stmt!=NULL);
 return lem::mysql_column_ufstring(row,FieldIndex);
}


lem::FString LS_ResultSet_MySQL::GetFString( int FieldIndex )
{
 LEM_CHECKIT_Z(stmt!=NULL);
 return lem::mysql_column_fstring(row,FieldIndex);
}

#endif
