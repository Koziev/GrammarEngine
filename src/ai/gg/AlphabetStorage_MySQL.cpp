#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/Ucs4ToWideString.h>
#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/conversions.h>
#include <lem/mysql_helpers.h>
#include <lem/solarix/coordinate.h>
#include <lem/solarix/gram_class.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/Alphabet.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/criterion.h>
#include <lem/solarix/StorageConnection_MySQL.h>
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/GG_CharOperation.h>
#include <lem/solarix/SyllabRule.h>
#include <lem/solarix/AlphabetStorage_MySQL.h>

using namespace Solarix;

AlphabetStorage_MySQL::AlphabetStorage_MySQL( StorageConnection_MySQL *_cnx )
 : cnx(_cnx)
{
 return;
}

AlphabetStorage_MySQL::~AlphabetStorage_MySQL(void)
{
 cnx->Release();
 return;
}



void AlphabetStorage_MySQL::Execute( const lem::UFString & sql )
{
 Execute( lem::to_utf8(sql) );
}

void AlphabetStorage_MySQL::Execute( const lem::FString & sql )
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> tx(cnx->GetTx());
 cnx->Execute(sql);
 return;
}

int AlphabetStorage_MySQL::ExecuteAndReturnId( const lem::UFString & sql )
{
 return ExecuteAndReturnId(lem::to_utf8(sql) );
}

int AlphabetStorage_MySQL::ExecuteAndReturnId( const lem::FString & sql )
{
 MySQLCnx *c = cnx->GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> tx(cnx->GetTx());

 cnx->Execute(sql);
 const int id = cnx->GetLastId();

 return id;
}



int AlphabetStorage_MySQL::SelectInt( const lem::FString & sql )
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 return lem::mysql_select_int( c->mysql, sql.c_str() );
}


int AlphabetStorage_MySQL::SelectInt( const char *sql )
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 return lem::mysql_select_int( c->mysql, sql );
}




int AlphabetStorage_MySQL::CountAlphabets(void)
{
 return SelectInt("SELECT count(*) from abc_alphabet");
}


Alphabet* AlphabetStorage_MySQL::GetAlphabet( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name FROM abc_alphabet WHERE id=%d", id );
 lem::FString Select(lem::to_utf8(mem.string()));

 Alphabet *a = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UCString name = lem::mysql_column_ucstring( row, 0 );
       a = new Alphabet( id, name );
      }

     mysql_free_result(res);
     return a;
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 return NULL;
}


int AlphabetStorage_MySQL::FindAlphabet( const lem::UCString &name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM abc_alphabet WHERE Upper(name)='%us'", lem::to_upper(name).c_str() );
 return SelectInt(lem::to_utf8(mem.string()));
}


LS_ResultSet* AlphabetStorage_MySQL::ListAlphabets(void)
{
 lem::FString Select("SELECT id FROM abc_alphabet" );
 return ListByQuery(Select);
}


int AlphabetStorage_MySQL::AddAlphabet( const lem::UCString &name )
{
 LEM_STOPIT;
 return -1;
}

void AlphabetStorage_MySQL::StoreAlphabet( const Alphabet &a )
{
 LEM_STOPIT;
 return;
}


int AlphabetStorage_MySQL::CountCoords(void)
{
 return SelectInt( "SELECT count(*) from abc_coord" );
}


bool AlphabetStorage_MySQL::GetCoord( int id, GramCoord &coord )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );
 lem::FString Select( lem::format_str("SELECT name, bistable FROM abc_coord WHERE id=%d", id) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   bool ok=false;

   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       ok=true;

       coord.id = id;
       coord.name = lem::mysql_column_ucstring(row,0);
       bool bistable = lem::mysql_column_int(row,1)==1;

       if( !bistable )
        {
         lem::FString Select2( lem::format_str("SELECT id, name FROM abc_state WHERE id_coord=%d ORDER BY id", id ) );

         rc = mysql_query( c->mysql, Select2.c_str() );
         if( rc==0 )
          {
           MYSQL_RES *res2 = mysql_store_result(c->mysql);
           if( res2!=NULL )
            {
             MYSQL_ROW row2;
             while( (row2 = mysql_fetch_row(res2))!=NULL )
              {
               const int id_state = lem::mysql_column_int(row2,0);
               UCString state_name = lem::mysql_column_ucstring(row2,1);

               GramCoordState s(state_name);
               coord.Add(s);
              }

             mysql_free_result(res2);
            }
          }
         else 
          {
           cnx->Error(Select2);
          }
        }
      }

     mysql_free_result(res);

     #if defined SOL_LOADTXT
     coord.SetRealized();
     #endif
    }

   return ok;
  }

 cnx->Error(Select);
 return false;
}


LS_ResultSet* AlphabetStorage_MySQL::ListCoords(void)
{
 lem::FString Select("SELECT id FROM abc_coord ORDER BY id");
 return ListByQuery(Select);
}


int AlphabetStorage_MySQL::FindCoord( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 lem::MemFormatter ms;
 ms.printf( "SELECT id FROM abc_coord WHERE Upper(name)='%us'", lem::to_upper(name).c_str() );
 lem::FString Select=lem::to_utf8(ms.string());
 return SelectInt(Select);
}


int AlphabetStorage_MySQL::AddCoord( const lem::UCString &coord )
{
 LEM_STOPIT;
 return -1;
}


int AlphabetStorage_MySQL::AddCoord( Solarix::GramCoord &coord )
{
 LEM_STOPIT;
 return -1;
}


void AlphabetStorage_MySQL::StoreCoord( int id, Solarix::GramCoord &coord )
{
 LEM_STOPIT;
 return;
}




int AlphabetStorage_MySQL::CountClasses(void)
{
 return SelectInt( "SELECT count(*) from abc_class" );
}


int AlphabetStorage_MySQL::FindClass( const lem::UCString &name )
{
 lem::MemFormatter ms;
 UCString uname(to_upper(name));
 ms.printf( "SELECT id FROM abc_class WHERE Upper(name)='%us'", uname.c_str() );
 lem::FString Select=lem::to_utf8(ms.string());
 return SelectInt(Select);
}


int AlphabetStorage_MySQL::AddClass( const lem::UCString &name )
{
 LEM_STOPIT;
 return -1;
}


int AlphabetStorage_MySQL::AddClass( const Solarix::GramClass &cls )
{
 LEM_STOPIT;
 return -1;
}


void AlphabetStorage_MySQL::StoreClass( int id, const GramClass & cls )
{
 LEM_STOPIT;
 return;
}


bool AlphabetStorage_MySQL::GetClass( int id, GramClass & cls )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT name FROM abc_class WHERE id=%d", id ) );

 bool found=false;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       found=true;
       cls.name = lem::mysql_column_ucstring(row,0);
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 if( found )
  { 
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   cls.is_realized=true;
   #endif

   lem::FString Select2(lem::format_str( "SELECT id_coord, coord_type FROM abc_class_coord "
    "WHERE id_class=%d", id ) );

   int ok = mysql_query( c->mysql, Select2.c_str() );
   if( ok==0 )
    {
     MYSQL_RES *res = mysql_store_result( c->mysql );
     if( res!=NULL )
      {
       MYSQL_ROW row;
       while( (row = mysql_fetch_row(res))!=NULL )
        {
         const int id_coord = lem::mysql_column_int(row,0);
         const int coord_type = lem::mysql_column_int(row,1);

         switch( coord_type )
         {
          case 0: cls.attr_index.push_back( id_coord ); break;
          case 1: cls.dim_index.push_back( id_coord ); break;
          default: LEM_STOPIT;
         }
        }

       mysql_free_result(res);
      }
     else
      {
       cnx->Error(Select2);
      }
    }
  }

 return found;
}


LS_ResultSet* AlphabetStorage_MySQL::ListClasses(void)
{
 lem::FString Select("SELECT id FROM abc_class ORDER BY id");
 return ListByQuery(Select);
}


void AlphabetStorage_MySQL::FindSymbol( lem::uint32_t code, lem::MCollect<Word_Coord> &projs )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id_entry, ordnum FROM abc_form WHERE code=%ud", code );
 lem::FString Select(lem::to_utf8(mem.string()));
 projs.clear();

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row;
     while( (row = mysql_fetch_row(res))!=NULL )
      {
       const int id_entry = lem::mysql_column_int(row,0);
       const int id_form = lem::mysql_column_int(row,1);
       projs.push_back( Word_Coord(id_entry,id_form) );
      }

     mysql_free_result(res);
    }
   else
    {
     cnx->Error(Select);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return;
}


void AlphabetStorage_MySQL::FindSymbol(
                                       lem::uint32_t code,
                                       lem::MCollect<Word_Coord> &projs,
                                       int AlphabetID
                                      )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT F.id_entry, F.ordnum FROM abc_form F, abc_entry E"
             " WHERE F.code=%ud AND E.id=F.id_entry AND E.id_alphabet=%d", code, AlphabetID );
 lem::FString Select(lem::to_utf8(mem.string()));
 projs.clear();

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row;
     while( (row = mysql_fetch_row(res))!=NULL )
      {
       const int id_entry = lem::mysql_column_int(row,0);
       const int id_form = lem::mysql_column_int(row,1);
       projs.push_back( Word_Coord(id_entry,id_form) );
      }

     mysql_free_result(res);
    }
   else
    {
     cnx->Error(Select);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return;
}



void AlphabetStorage_MySQL::FindSymbol(
                                       lem::uint32_t code,
                                       lem::MCollect<Word_Coord> &projs,
                                       const lem::MCollect<int> & AlphabetID
                                      )
{
 lem::FString in;
 if( AlphabetID.size()==1 )
  {
   in = lem::format_str( "=%d", AlphabetID.front() );
  }
 else
  {
   in = " in (";
   for( lem::Container::size_type i=0; i<AlphabetID.size(); ++i )
    {
     if( i>0 )
      in.Add_Dirty( "," );

     in.Add_Dirty( lem::to_str(AlphabetID[i]).c_str() );
    }

   in += ")";
  }

 lem::MemFormatter mem;
 mem.printf( "SELECT F.id_entry, F.ordnum FROM abc_form F, abc_entry E"
             " WHERE F.code=%ud AND E.id=F.id_entry AND E.id_alphabet %s", code, in.c_str() );
 lem::FString Select(lem::to_utf8(mem.string()));
 projs.clear();

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row;
     while( (row = mysql_fetch_row(res))!=NULL )
      {
       const int id_entry = lem::mysql_column_int(row,0);
       const int id_form = lem::mysql_column_int(row,1);
       projs.push_back( Word_Coord(id_entry,id_form) );
      }

     mysql_free_result(res);
    }
   else
    {
     cnx->Error(Select);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return;
}



int AlphabetStorage_MySQL::StorePairs( const MCollect<GramCoordPair> & _pairs )
{
 LEM_STOPIT;
 return -1;
}


void AlphabetStorage_MySQL::LoadPairs( int id_pairs, MCollect<GramCoordPair> & pairs )
{
 pairs.clear();
 
 if( id_pairs==0 )
  return;

 lem::FString Select(lem::format_str( "SELECT id_coord, id_state FROM abc_pair"
  " WHERE id_pairs=%d", id_pairs ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row;
     while( (row = mysql_fetch_row(res))!=NULL )
      {
       const int id_coord = lem::mysql_column_int(row,0);
       const int id_state = lem::mysql_column_int(row,1);
       pairs.push_back( GramCoordPair( id_coord, id_state ) );
      }

     mysql_free_result(res);
    }
   else
    {
     cnx->Error(Select);
    }
  }
 else
  {
   cnx->Error(Select);
  }


 return;
}


int AlphabetStorage_MySQL::StoreEntry( const GG_Entry &e )
{
 LEM_STOPIT;
 return -1;
}


GG_Entry* AlphabetStorage_MySQL::LoadEntry( int id )
{
 lem::FString Select(lem::format_str( "SELECT code, id_class, id_alphabet, id_pairs FROM abc_entry"
  " WHERE id=%d", id ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   GG_Entry *e=NULL;

   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       const int ucs4 = lem::mysql_column_int(row,0);
       const int id_class = lem::mysql_column_int(row,1);
       const int id_alphabet = lem::mysql_column_int(row,2);
       const int id_pairs = lem::mysql_column_int(row,3);
  
       lem::MCollect<GramCoordPair> attrs;
       LoadPairs( id_pairs, attrs );
  
       e = new GG_Entry( ucs4, id_class, id_alphabet, attrs );
  
       lem::FString Select(lem::format_str( "SELECT code, id_pairs FROM abc_form"
        " WHERE id_entry=%d ORDER BY ordnum", id ) );
  
       lem::MCollect<GramCoordPair> dims;

       ok = mysql_query( c->mysql, Select.c_str() );
       if( ok==0 )
        {
         MYSQL_RES *res = mysql_store_result( c->mysql );
         if( res!=NULL )
          {
           MYSQL_ROW row=NULL;
 
           while( (row=mysql_fetch_row(res))!=NULL )
            {
             const lem::uint32_t Ucs4Name = lem::mysql_column_int(row,0);
             const int id_pairs = lem::mysql_column_int(row,1);
             dims.clear();
             LoadPairs( id_pairs, dims );
             e->Add( GG_EntryForm( dims, Ucs4Name ) );
            }
 
           mysql_free_result(res);
          }

         return e;
        }
       else
        {
         cnx->Error(Select);
         return NULL;
        }
      }

     mysql_free_result(res);
    }

   return e;
  }
 else
  {
   cnx->Error(Select);
   return NULL;
  }
}


LS_ResultSet* AlphabetStorage_MySQL::ListEntries(void)
{
 lem::FString Select("SELECT id FROM abc_entry" );
 return ListByQuery(Select);
}


int AlphabetStorage_MySQL::CountEntries(void)
{
 return SelectInt( "SELECT count(*) from abc_entry" );
}

int AlphabetStorage_MySQL::CountEntryForms(void)
{
 return SelectInt( "SELECT count(*) from abc_form" );
}

void AlphabetStorage_MySQL::CopyDatabase( const lem::Path & alphabet_db_path )
{
 return;
}

LS_ResultSet* AlphabetStorage_MySQL::ListByQuery( const lem::UFString &Select )
{
 return ListByQuery(lem::to_utf8(Select));
}

LS_ResultSet* AlphabetStorage_MySQL::ListByQuery( const lem::FString &Select )
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 return NULL;
}


int AlphabetStorage_MySQL::FindCriterion( const lem::UCString & name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM abc_criterion WHERE Upper(name)='%us'", lem::to_upper(name).c_str() );
 return SelectInt( lem::to_utf8(mem.string()) );
}

int AlphabetStorage_MySQL::StoreCriterion( const Criterion &x )
{
 LEM_STOPIT;
 return -1;
}

Criterion* AlphabetStorage_MySQL::GetCriterion( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name, strval FROM abc_criterion WHERE id=%d", id );
 lem::FString Select(lem::to_utf8(mem.string()));

 Criterion *a = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UCString name = lem::mysql_column_ucstring( row, 0 );
       lem::UFString str = lem::mysql_column_ufstring( row, 1 );
       a = new Criterion( name, str );
      }

     mysql_free_result(res);
     return a;
    }

   LEM_STOPIT;
   return NULL;
  }
 else
  {
   cnx->Error(Select);
   return NULL;
  }
}

LS_ResultSet* AlphabetStorage_MySQL::EnumerateCriteria(void)
{
 lem::FString Select("SELECT id FROM abc_criterion" );
 return ListByQuery(Select);
}


LS_ResultSet* AlphabetStorage_MySQL::ListCharOperations(void)
{
 lem::FString Select("SELECT id FROM abc_operation ORDER BY id");
 return ListByQuery(Select);
}

GG_CharOperation* AlphabetStorage_MySQL::GetCharOperation( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name FROM abc_operation WHERE id=%d", id );
 lem::FString Select(lem::to_utf8(mem.string()));

 GG_CharOperation *a = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UCString name = lem::mysql_column_ucstring( row, 0 );
       std::map< lem::uint32_t, lem::uint32_t > items;

       mem.printf( "SELECT src_char_ucs4, res_char_ucs4 FROM abc_operation_item WHERE id_operation=%d", id );
       lem::FString Select2(lem::to_utf8(mem.string()));

       int ok2 = mysql_query( c->mysql, Select2.c_str() );
       if( ok2==0 )
        {
         MYSQL_RES *res2 = mysql_store_result( c->mysql );
         if( res2!=NULL )
          {
           MYSQL_ROW row2;
           while( (row2 = mysql_fetch_row(res2))!=NULL )
            {
             const int src_char = lem::mysql_column_int(row2,0);
             const int res_char = lem::mysql_column_int(row2,1);
             items.insert( std::make_pair(src_char,res_char) );
            }

           a = new GG_CharOperation( id, name, items );
           mysql_free_result(res2);
          }
        }
       else
        {
         cnx->Error(Select);
         return NULL;
        }
      }

     mysql_free_result(res);
     return a;
    }

   LEM_STOPIT;
   return NULL;
  }
 else
  {
   cnx->Error(Select);
   return NULL;
  }
}

int AlphabetStorage_MySQL::StoreCharOperation( GG_CharOperation *operation )
{
 LEM_STOPIT;
 return -1;
}


int AlphabetStorage_MySQL::FindCharOperation( const lem::UCString &name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM abc_operation WHERE name='%us'", lem::to_upper(name).c_str() );
 return SelectInt( lem::to_utf8(mem.string()) );
}



void AlphabetStorage_MySQL::DeleteSyllabRules(void)
{
 Execute("DELETE FROM slb_rule");
 Execute("DELETE FROM slb_condition_point");
 Execute("DELETE FROM slb_result_point");

 return;
}


int AlphabetStorage_MySQL::StoreSyllabRule( const lem::UCString &rule_name, int id_language, int id_src, int cursor_shift )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO slb_rule( name, id_src, id_language, cursor_shift ) VALUES ( '%us', %d, %d, %d )", rule_name.c_str(), id_src, id_language, cursor_shift );
 return ExecuteAndReturnId(mem.string());
}


void AlphabetStorage_MySQL::StoreSyllabConditionPoint(
                                                       int id_rule,
                                                       int point_index, 
                                                       const lem::MCollect<lem::uint32_t> &codes,
                                                       int id_class,
                                                       int id_entry,
                                                       int id_coord0, int id_state0,
                                                       bool is_left_boundary, bool is_right_boundary,
                                                       bool is_positive
                                                      )
{
 const int n_char = CastSizeToInt(codes.size());

 lem::UFString char_text, char_ucs4;
 lem::Ucs4ToUFString ucs42wchar;
 wchar_t ibuf[10];
 for( int i=0; i<n_char; ++i )
  {
   if( i>0 )
    { char_text += L' '; char_ucs4+=L' '; }

   ucs42wchar.Clear();
   ucs42wchar.Add( codes[i] );
   char_text += ucs42wchar.ToString();
   char_ucs4 += lem::uint32_to_str(codes[i],ibuf);
  }

 const int n_coord = id_coord0==UNKNOWN ? 0 : 1;

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO slb_condition_point( id_rule, point_index, n_char, char_text, char_ucs4,"
                                             " id_class, id_entry, id_coord0, id_state0, is_left_boundary,"
                                             " is_right_boundary, n_coord, is_positive ) VALUES ("
                                             " %d, %d, %d, '%us', '%us',"
                                             " %d, %d, %d, %d, %d,"
                                             " %d, %d, %d )",
                                             id_rule, point_index, n_char, char_text.c_str(), char_ucs4.c_str(),
                                             id_class, id_entry, id_coord0, id_state0, is_left_boundary ? 1 : 0,
                                             is_right_boundary ? 1 : 0, n_coord, is_positive ? 1 : 0
           );
 Execute(mem.string());
 return;
}



void AlphabetStorage_MySQL::StoreSyllabResultPoint(
                                                    int id_rule,
                                                    int point_index, 
                                                    int copy_index,
                                                    int merge_index0,
                                                    int merge_count
                                                   )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO slb_result_point( id_rule, point_index, copy_index, merge_index0, merge_count )"
             " VALUES ( %d, %d, %d, %d, %d )", id_rule, point_index, copy_index, merge_index0, merge_count );
 Execute( mem.string() );
 return;
}



LS_ResultSet* AlphabetStorage_MySQL::ListSyllabRulesForLanguage( int id_language )
{
 return ListByQuery( lem::format_str("SELECT id FROM slb_rule WHERE id_language=%d ORDER BY id",id_language) );
}


LS_ResultSet* AlphabetStorage_MySQL::ListSyllabRules(void)
{
 return ListByQuery( "SELECT id, name, id_src, id_language, cursor_shift FROM slb_rule ORDER BY id" );
}



LS_ResultSet* AlphabetStorage_MySQL::ListSyllabConditionPoints(void)
{
 return ListByQuery( "SELECT id, id_rule, point_index, n_char, char_text, char_ucs4,"
                     " id_class, id_entry, n_coord, id_coord0, id_state0, is_left_boundary,"
                     " is_right_boundary, is_positive FROM slb_condition_point ORDER BY id" );
}

LS_ResultSet* AlphabetStorage_MySQL::ListSyllabResultPoints(void)
{
 return ListByQuery( "SELECT id, id_rule, point_index, copy_index, merge_index0, merge_count FROM slb_result_point ORDER BY id" );
}



SyllabRule * AlphabetStorage_MySQL::LoadSyllabRule( int id_rule )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name, id_src, id_language, cursor_shift FROM slb_rule WHERE id=%d", id_rule );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   lem::UCString name = rs->GetUCString(0);
   const int id_src = rs->GetInt(1);
   const int id_language = rs->GetInt(2);
   const int cursor_shift = rs->GetInt(3);  

   SyllabRule * rule = new SyllabRule( name, id_src, id_language );
   rule->GetCondition().Load( this, id_rule );
   rule->GetResult().Load( this, id_rule, cursor_shift );
   return rule;
  }
 else
  {
   LEM_STOPIT;
   return NULL;
  }
}



LS_ResultSet* AlphabetStorage_MySQL::ListSyllabConditionPointsForRule( int id_rule )
{
 LEM_CHECKIT_Z( id_rule!=UNKNOWN );

 lem::MemFormatter mem;
 mem.printf( "SELECT char_ucs4, id_class, id_entry, id_coord0, id_state0, is_left_boundary,"
                     " is_right_boundary, is_positive FROM slb_condition_point WHERE id_rule=%d ORDER BY point_index", id_rule );

 return ListByQuery( mem.string() );
}


LS_ResultSet* AlphabetStorage_MySQL::ListSyllabResultPointsForRule( int id_rule )
{
 LEM_CHECKIT_Z( id_rule!=UNKNOWN );

 lem::MemFormatter mem;
 mem.printf( "SELECT copy_index, merge_index0, merge_count FROM slb_result_point WHERE id_rule=%d ORDER BY point_index", id_rule );

 return ListByQuery( mem.string() );
}



#endif
