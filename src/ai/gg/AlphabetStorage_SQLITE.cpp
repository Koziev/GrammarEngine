#include <lem/oformatter.h>
#include <lem/conversions.h>
#include <lem/unicode.h>
#include <lem/Ucs4ToWideString.h>
#include <lem/sqlite_helpers.h>
#include <lem/solarix/coordinate.h>
#include <lem/solarix/gram_class.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/Alphabet.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/criterion.h>
#include <lem/solarix/GG_CharOperation.h>
#include <lem/solarix/SyllabRule.h>
#include <lem/solarix/AlphabetStorage_SQLITE.h>

using namespace Solarix;

AlphabetStorage_SQLITE::AlphabetStorage_SQLITE( const lem::UFString &connection_string )
 : sqlite_connection_string(connection_string)
{
 hdb = lem::sqlite_open_serialized(connection_string);
 return;
}

AlphabetStorage_SQLITE::~AlphabetStorage_SQLITE(void)
{
 if( hdb!=NULL )
  {
   sqlite3_close(hdb);
   hdb=NULL;
  }

 return;
}


void AlphabetStorage_SQLITE::RaiseError(void)
{
 lem::MemFormatter msg;
 msg.printf( "SQLite error, message=%us", lem::sqlite_errmsg(hdb).c_str() );
 throw lem::E_BaseException(msg.string());
}

void AlphabetStorage_SQLITE::RaiseError( const char *filename, int line )
{
 lem::MemFormatter msg;
 msg.printf( "SQLite error in file %s:%d, message=%us", filename, line, lem::sqlite_errmsg(hdb).c_str() );
 throw lem::E_BaseException(msg.string());
}

void AlphabetStorage_SQLITE::RaiseError( const lem::FString &sql )
{
 lem::MemFormatter msg;
 msg.printf( "SQLite error sql=%s, message=%us", sql.c_str(), lem::sqlite_errmsg(hdb).c_str() );
 throw lem::E_BaseException(msg.string());
}

void AlphabetStorage_SQLITE::RaiseError( const char * sql )
{
 lem::MemFormatter msg;
 msg.printf( "SQLite error sql=%s, message=%us", sql, lem::sqlite_errmsg(hdb).c_str() );
 throw lem::E_BaseException(msg.string());
}

void AlphabetStorage_SQLITE::Execute( const lem::UFString &sql )
{
 Execute( lem::to_utf8(sql) );
 return;
}

void AlphabetStorage_SQLITE::Execute( const lem::FString &sql )
{
 int res = sqlite3_exec( hdb, sql.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   RaiseError(sql);
  }

 return;
}

void AlphabetStorage_SQLITE::Execute( const char *sql )
{
 int res = sqlite3_exec( hdb, sql, NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   RaiseError(sql);
  }

 return;
}


int AlphabetStorage_SQLITE::LastInsertID(void)
{
 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


LS_ResultSet* AlphabetStorage_SQLITE::ListByQuery( const char *sql )
{
 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, sql, strlen(sql), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   return new LS_ResultSet_SQLITE(stmt);
  }
 else
  {
   RaiseError(sql);
   return NULL;
  }
}

LS_ResultSet* AlphabetStorage_SQLITE::ListByQuery( const lem::UFString & sql )
{
 return ListByQuery( lem::to_utf8(sql) );
}

LS_ResultSet* AlphabetStorage_SQLITE::ListByQuery( const lem::FString & sql )
{
 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, sql.c_str(), sql.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   return new LS_ResultSet_SQLITE(stmt);
  }
 else
  {
   RaiseError(sql);
   return NULL;
  }
}


int AlphabetStorage_SQLITE::SelectInt( const lem::FString &Select )
{
 int id=UNKNOWN;

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     id = sqlite3_column_int(stmt,0);
    }

   sqlite3_finalize(stmt);
   return id;
  }
 else
  {
   RaiseError(Select);
   return -1;
  }
}


void AlphabetStorage_SQLITE::CreateSchema(void)
{
 CreateTables_Alphabets();
 CreateTables_Coords();
 CreateTables_Classes();
 CreateTables_Entries();
 CreateTables_Criteria();
 CreateTables_Operations();
 CreateTables_SyllabRules();
 return;
}



void AlphabetStorage_SQLITE::CreateTables_Operations(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"abc_operation") )
  { 
   const char create_ddl1[] = "CREATE TABLE abc_operation( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE"
                             ")";
   Execute( create_ddl1 );


   const char create_ddl2[] = "CREATE TABLE abc_operation_item( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_operation integer NOT NULL,"
                             " src_char_ucs4 integer NOT NULL,"
                             " res_char_ucs4 integer NOT NULL,"
                             " src_char varchar(2) NOT NULL,"
                             " res_char varchar(2) NOT NULL"
                             ")";

   Execute( create_ddl2 );
  }

 return;
}



void AlphabetStorage_SQLITE::CreateTables_Alphabets(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"abc_alphabet") )
  { 
   const char create_ddl[] = "CREATE TABLE abc_alphabet( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE"
                             ")";

   Execute(create_ddl);
  }

 return;
}


int AlphabetStorage_SQLITE::CountAlphabets(void)
{
 return lem::sqlite_select_int( hdb, "SELECT count(*) from abc_alphabet" );
}


Alphabet* AlphabetStorage_SQLITE::GetAlphabet( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name FROM abc_alphabet WHERE id=%d", id );

 lem::FString Select(lem::to_utf8(mem.string()));

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UCString name = lem::sqlite_column_ucstring( stmt, 0 );
     Alphabet *a = new Alphabet( id, name );
     return a;
    }
   else
    {
     lem::MemFormatter mem;
     mem.printf( "Can not load the requested alphabet with id=%d", id );
     throw lem::E_BaseException(mem.string());
    }
  
   sqlite3_finalize(stmt);
   return NULL;
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return NULL;
  }
}


int AlphabetStorage_SQLITE::FindAlphabet( const lem::UCString &name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM abc_alphabet WHERE Upper(name)='%us'", lem::to_upper(name).c_str() );
 return lem::sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}


LS_ResultSet* AlphabetStorage_SQLITE::ListAlphabets(void)
{
 return ListByQuery("SELECT id FROM abc_alphabet ORDER BY id");
}


int AlphabetStorage_SQLITE::AddAlphabet( const lem::UCString &name )
{
 lem::UFString name_str( lem::to_upper(name).c_str());
 sqlite_escape(name_str);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO abc_alphabet( name )"
  " VALUES ( '%us' )", name_str.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);
 return LastInsertID();
}

void AlphabetStorage_SQLITE::StoreAlphabet( const Alphabet &a )
{
 // ...

 return;
}

void AlphabetStorage_SQLITE::CreateTables_Coords(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"abc_coord") )
  { 
   const char create_ddl[] = "CREATE TABLE abc_coord( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE,"
                             " bistable int NOT NULL"
                             ")";

   Execute(create_ddl);

   const char create_ddl2[] = "CREATE TABLE abc_state( "
                             " id_pk integer PRIMARY KEY NOT NULL,"
                             " id int NOT NULL,"
                             " id_coord int NOT NULL,"
                             " name varchar(32) NOT NULL"
                             ")";

   Execute(create_ddl2);
  }

 return;
}

int AlphabetStorage_SQLITE::CountCoords(void)
{
 return lem::sqlite_select_int( hdb, "SELECT count(*) FROM abc_coord" );
}


bool AlphabetStorage_SQLITE::GetCoord( int id, GramCoord &coord )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );
 lem::FString Select( lem::format_str("SELECT name, bistable FROM abc_coord WHERE id=%d", id) );

 bool ok=false;
 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     coord.id = id;
     coord.name = lem::sqlite_column_ucstring(stmt,0);
     bool bistable = sqlite3_column_int(stmt,1)==1;

     if( !bistable )
      {
       lem::FString Select2( lem::format_str("SELECT id, name FROM abc_state WHERE id_coord=%d ORDER BY id", id ) );
       sqlite3_stmt *stmt2=NULL;
       const char *dummy2=NULL;
       int res2 = sqlite3_prepare_v2( hdb, Select2.c_str(), Select2.length(), &stmt2, &dummy2 );
       if( res2==SQLITE_OK )
        {
         while( sqlite3_step( stmt2 ) == SQLITE_ROW )
          {
           const int id_state = sqlite3_column_int(stmt2,0);
           UCString state_name = lem::sqlite_column_ucstring(stmt2,1);

           GramCoordState s(state_name);
           coord.Add(s);
          }

         sqlite3_finalize(stmt2);
        }
       else 
        {
         RaiseError(__FILE__,__LINE__);
        }
      }

     #if defined SOL_LOADTXT
     coord.SetRealized();
     #endif

     ok=true;
    }

   sqlite3_finalize(stmt);
   return ok;
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return false;
  }
}


LS_ResultSet* AlphabetStorage_SQLITE::ListCoords(void)
{
 return ListByQuery("SELECT id FROM abc_coord ORDER BY id");
}


int AlphabetStorage_SQLITE::FindCoord( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 lem::MemFormatter ms;
 ms.printf( "SELECT id FROM abc_coord WHERE name='%us'", to_upper(name).c_str() );
 lem::FString Select=lem::to_utf8(ms.string());
 return SelectInt(Select);
}


int AlphabetStorage_SQLITE::AddCoord( const lem::UCString &coord )
{
 lem::UFString s( to_upper(coord).c_str() );
 sqlite_escape(s);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO abc_coord( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);
 return LastInsertID();
}


int AlphabetStorage_SQLITE::AddCoord( Solarix::GramCoord &coord )
{
 UFString s( to_upper(coord.GetName().front()).c_str() );
 sqlite_escape(s);

 int bistable = coord.IsBistable() ? 1 : 0; 
 
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO abc_coord( name, bistable ) VALUES ( '%us', %d )", s.c_str(), bistable );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 const int id = LastInsertID();
 StoreCoordStates(id,coord);

 coord.id = id;

 return id;
}


void AlphabetStorage_SQLITE::StoreCoord( int id, Solarix::GramCoord &coord )
{
 lem::UFString s( lem::to_upper(coord.GetName().front()).c_str() );
 sqlite_escape(s);

 int bistable = coord.IsBistable() ? 1 : 0; 
 
 lem::MemFormatter ms;
 ms.printf( "UPDATE abc_coord SET name='%us', bistable=%d WHERE id=%d", s.c_str(), bistable, id );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 lem::FString del( lem::format_str( "DELETE FROM abc_state WHERE id_coord=%d", id ) );
 Execute(del);
 StoreCoordStates(id,coord);

 return;
}

void AlphabetStorage_SQLITE::StoreCoordStates( int id_coord, const Solarix::GramCoord &coord )
{
 lem::MemFormatter ms;
 const int n=coord.GetTotalStates();
 for( int i=0; i<n; ++i )
  {
   lem::UFString s(coord.GetStateName(i).c_str());
   sqlite_escape(s);

   const int id_state = i;
 
   ms.printf( "INSERT INTO abc_state( id, name, id_coord ) VALUES ( %d, '%us', %d )"
    , id_state, s.c_str(), id_coord );

   lem::FString as(lem::to_utf8(ms.string()));
   Execute(as);
  }

 return;
}




void AlphabetStorage_SQLITE::CreateTables_Classes(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"abc_class") )
  { 
   const char create_ddl[] = "CREATE TABLE abc_class( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE"
                             ")";

   Execute(create_ddl);

   const char create_ddl2[] = "CREATE TABLE abc_class_coord( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_class int NOT NULL,"
                             " id_coord int NOT NULL,"
                             " coord_type int NOT NULL"
                             ")";

   Execute(create_ddl2);
  }

 return;
}




int AlphabetStorage_SQLITE::CountClasses(void)
{
 return lem::sqlite_select_int( hdb, "SELECT count(*) FROM abc_class" );
}


int AlphabetStorage_SQLITE::FindClass( const lem::UCString &name )
{
 lem::MemFormatter ms;
 lem::UCString uname(lem::to_upper(name));

 ms.printf( "SELECT id FROM abc_class WHERE name='%us'"
  , uname.c_str(), uname.c_str() );

 lem::FString Select=lem::to_utf8(ms.string());
 return SelectInt(Select);
}


int AlphabetStorage_SQLITE::AddClass( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 lem::UFString s( to_upper(name).c_str());
 sqlite_escape(s);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO abc_class( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 int id = LastInsertID();
 return id;
}


int AlphabetStorage_SQLITE::AddClass( const Solarix::GramClass &cls )
{
 lem::UFString s( lem::to_upper(cls.GetName()).c_str());
 sqlite_escape(s);

 lem::UFString aliases;
 const UCStringSet &alist = cls.GetAliases();
 LEM_CHECKIT_Z( alist.size()<2 );
 if( !alist.empty() )
  {
   aliases = lem::to_upper(alist[0]).c_str();
  }

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO abc_class( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 const int id = LastInsertID();
 StoreClassInternals(id,cls);

 return id;
}


void AlphabetStorage_SQLITE::StoreClass( int id, const GramClass & cls )
{
 lem::UFString s( lem::to_upper(cls.GetName()).c_str() );
 sqlite_escape(s);

 lem::UFString aliases;
 const UCStringSet &alist = cls.GetAliases();
 LEM_CHECKIT_Z( alist.size()<2 );
 if( !alist.empty() )
  {
   aliases = alist[0].c_str();
  }

 lem::MemFormatter ms;
 ms.printf( "UPDATE abc_class SET name='%us' WHERE id=%d", s.c_str(), id );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 StoreClassInternals( id, cls );

 return;
}


void AlphabetStorage_SQLITE::StoreClassInternals( int id, const GramClass &cls )
{
 lem::MemFormatter ms;

 for( lem::Container::size_type k=0; k<cls.attrs().size(); ++k )   
  {
   const GramCoordAdr &atr = cls.attrs()[k];

   ms.printf(
             "INSERT INTO abc_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 0 );\n"
             , id
             , atr.GetIndex()
           );

   lem::FString s(lem::to_utf8(ms.string()));
   Execute(s);
  }

 for( lem::Container::size_type k=0; k<cls.dims().size(); ++k )   
  {
   const GramCoordAdr &dim = cls.dims()[k];

   ms.printf(
             "INSERT INTO abc_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 1 );\n"
             , id
             , dim.GetIndex()
            );

   lem::FString s(lem::to_utf8(ms.string()));
   Execute(s);
  }

 return;
}

bool AlphabetStorage_SQLITE::GetClass( int id, GramClass & cls )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT name FROM abc_class WHERE id=%d", id ) );

 bool found=false;

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     found=true;
     cls.name = lem::sqlite_column_ucstring(stmt,0);
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
  }

 sqlite3_finalize(stmt);

 if( found )
  { 
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   cls.is_realized=true;
   #endif

   lem::FString Select2(lem::format_str( "SELECT id_coord, coord_type FROM abc_class_coord "
    "WHERE id_class=%d", id ) );

   sqlite3_stmt *stmt2=NULL;
   const char *dummy2=NULL;
   int res2 = sqlite3_prepare_v2( hdb, Select2.c_str(), Select2.length(), &stmt2, &dummy2 );
   if( res2==SQLITE_OK )
    {
     while( sqlite3_step( stmt2 ) == SQLITE_ROW )
      {
       const int id_coord = sqlite3_column_int(stmt2,0);
       const int coord_type = sqlite3_column_int(stmt2,1);

       switch( coord_type )
       {
        case 0: cls.attr_index.push_back( id_coord ); break;
        case 1: cls.dim_index.push_back( id_coord ); break;
        default: LEM_STOPIT;
       }
      }
    }
   else
    {
     RaiseError(__FILE__,__LINE__);
    }

   sqlite3_finalize(stmt2);
  }

 return found;
}


LS_ResultSet* AlphabetStorage_SQLITE::ListClasses(void)
{
 return ListByQuery("SELECT id FROM abc_class ORDER BY id");
}


void AlphabetStorage_SQLITE::FindSymbol( lem::uint32_t code, lem::MCollect<Word_Coord> &projs )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id_entry, ordnum FROM abc_form WHERE code=%ud", code );
 lem::FString Select(lem::to_utf8(mem.string()));
 projs.clear();

 sqlite3_stmt *stmt2=NULL;
 const char *dummy2=NULL;
 int res2 = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt2, &dummy2 );
 if( res2==SQLITE_OK )
  {
   while( sqlite3_step( stmt2 ) == SQLITE_ROW )
    {
     const int id_entry = sqlite3_column_int(stmt2,0);
     const int id_form = sqlite3_column_int(stmt2,1);
     projs.push_back( Word_Coord(id_entry,id_form) );
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
  }

 sqlite3_finalize(stmt2);
 
 return;
}


void AlphabetStorage_SQLITE::FindSymbol(
                                        lem::uint32_t code,
                                        lem::MCollect<Solarix::Word_Coord> &projs,
                                        int AlphabetID
                                       )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT F.id_entry, F.ordnum FROM abc_form F, abc_entry E"
             " WHERE F.code=%ud AND E.id=F.id_entry AND E.id_alphabet=%d", code, AlphabetID );
 lem::FString Select(lem::to_utf8(mem.string()));
 projs.clear();

 sqlite3_stmt *stmt2=NULL;
 const char *dummy2=NULL;
 int res2 = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt2, &dummy2 );
 if( res2==SQLITE_OK )
  {
   while( sqlite3_step( stmt2 ) == SQLITE_ROW )
    {
     const int id_entry = sqlite3_column_int(stmt2,0);
     const int id_form = sqlite3_column_int(stmt2,1);
     projs.push_back( Word_Coord(id_entry,id_form) );
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
  }

 sqlite3_finalize(stmt2);
 
 return;
}

void AlphabetStorage_SQLITE::FindSymbol(
                                        lem::uint32_t code,
                                        lem::MCollect<Solarix::Word_Coord> &projs,
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
      in += ",";

     in += lem::to_str(AlphabetID[i]).c_str();
    }

   in += ")";
  }

 lem::MemFormatter mem;
 mem.printf( "SELECT F.id_entry, F.ordnum FROM abc_form F, abc_entry E"
             " WHERE F.code=%ud AND E.id=F.id_entry AND E.id_alphabet %s", code, in.c_str() );
 lem::FString Select(lem::to_utf8(mem.string()));
 projs.clear();

 sqlite3_stmt *stmt2=NULL;
 const char *dummy2=NULL;
 int res2 = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt2, &dummy2 );
 if( res2==SQLITE_OK )
  {
   while( sqlite3_step( stmt2 ) == SQLITE_ROW )
    {
     const int id_entry = sqlite3_column_int(stmt2,0);
     const int id_form = sqlite3_column_int(stmt2,1);
     projs.push_back( Word_Coord(id_entry,id_form) );
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
  }

 sqlite3_finalize(stmt2);
 
 return;
}



void AlphabetStorage_SQLITE::CreateTables_Entries(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"abc_entry") )
  { 
   const char create_ddl[] = "CREATE TABLE abc_entry( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(1) NOT NULL,"
                             " id_class integer not null,"
                             " id_alphabet integer not null,"
                             " id_pairs integer NOT NULL,"
                             " code integer not null"
                             ")";

   Execute(create_ddl);
   Execute("CREATE INDEX abc_entry_idx1 ON abc_entry(code)");


   const char create_ddl2[] = "CREATE TABLE abc_form( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " ordnum integer NOT NULL," 
                             " id_entry int NOT NULL,"
                             " id_pairs int NOT NULL,"
                             " name char(1) NOT NULL,"
                             " code integer not null" 
                             ")";

   Execute(create_ddl2);
   Execute("CREATE INDEX abc_form_idx1 ON abc_form(code)");

   const char create_ddl3[] = "CREATE TABLE abc_pairs( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " str_pairs varchar(60) NOT NULL UNIQUE"
                             ")";

   Execute(create_ddl3);
   Execute("INSERT INTO abc_pairs( id, str_pairs ) VALUES ( 0, '' )");

   const char create_ddl4[] = "CREATE TABLE abc_pair( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_pairs integer not null,"
                             " id_coord integer not null,"
                             " id_state integer not null"
                             ")";

   Execute(create_ddl4);
  }

 return;
}

static bool pair_sorter( const GramCoordPair &x, const GramCoordPair &y )
{
 return x.GetCoord().GetIndex() > y.GetCoord().GetIndex();
}

int AlphabetStorage_SQLITE::StorePairs( const MCollect<GramCoordPair> & _pairs )
{
 if( _pairs.empty() )
  return 0; // predefined ID for an empty tuple

 lem::FString str_pairs;

 MCollect<GramCoordPair> pairs(_pairs);

 if( _pairs.size()==1 )
  {
   str_pairs = lem::format_str( " %d:%d ", _pairs.front().GetCoord().GetIndex(), _pairs.front().GetState() );
  }
 else
  {
   std::sort( pairs.begin(), pairs.end(), pair_sorter );
   for( lem::Container::size_type i=0; i<pairs.size(); ++i )
    str_pairs += lem::format_str( " %d:%d", pairs[i].GetCoord().GetIndex(), pairs[i].GetState() );

   str_pairs += ' ';
  }

 lem::FString sql = lem::format_str( "SELECT id FROM abc_pairs WHERE str_pairs='%s'", str_pairs.c_str() );
 int id_pairs = lem::sqlite_select_int( hdb, sql );
 if( id_pairs==-1 )
  {
   sql = lem::format_str( "INSERT INTO abc_pairs( str_pairs ) VALUES ( '%s' )", str_pairs.c_str() );
   Execute(sql);
   id_pairs = (int)sqlite3_last_insert_rowid(hdb);

   for( lem::Container::size_type i=0; i<pairs.size(); ++i )
    {
     sql = lem::format_str( "INSERT INTO abc_pair( id_pairs, id_coord, id_state ) VALUES ( %d, %d, %d )",
      id_pairs, pairs[i].GetCoord().GetIndex(), pairs[i].GetState() );
     
     Execute(sql);
    }
  }

 return id_pairs;
}


void AlphabetStorage_SQLITE::LoadPairs( int id_pairs, MCollect<GramCoordPair> & pairs )
{
 pairs.clear();
 
 if( id_pairs==0 )
  return;

 lem::FString Select(lem::format_str( "SELECT id_coord, id_state FROM abc_pair"
  " WHERE id_pairs=%d", id_pairs ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   while( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     const int id_coord = sqlite3_column_int(stmt,0);
     const int id_state = sqlite3_column_int(stmt,1);
     pairs.push_back( GramCoordPair( id_coord, id_state ) );
    }

   sqlite3_finalize(stmt);
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw lem::E_BaseException(msg.string());
  }

 return;
}


int AlphabetStorage_SQLITE::StoreEntry( const GG_Entry &e )
{
 lem::sqlite_begin_tx(hdb);

 const int id_pairs = StorePairs( e.attrs() );

 lem::FString ename( e.GetNameUtf8().c_str() );
 lem::sqlite_escape(ename);
 
 lem::FString sql = lem::format_str( "INSERT INTO abc_entry( name, code, id_class, id_alphabet, id_pairs )"
                                     " VALUES ( '%s', %d, %d, %d, %d )",
   ename.c_str(), e.GetName(), e.GetClass(), e.GetAlphabet(), id_pairs );

 Execute(sql);
 const int id_entry = LastInsertID();

 if( e.forms().empty() )
  {
   lem::FString sql = lem::format_str( "INSERT INTO abc_form( name, code, id_entry, id_pairs, ordnum )"
                                         " VALUES ( '%s', %d, %d, 0, 0 )",
       ename.c_str(), e.GetName(), id_entry );

   Execute(sql);
  }
 else
  {
   for( lem::Container::size_type i=0; i<e.forms().size(); ++i )
    {
     const GG_EntryForm &f = e.forms()[i];
 
     const int id_dims = StorePairs( f.dims() );
 
     lem::FString fname( f.GetNameUtf8().c_str() );
     lem::sqlite_escape(fname);
 
     lem::FString sql = lem::format_str( "INSERT INTO abc_form( name, code, id_entry, id_pairs, ordnum )"
                                         " VALUES ( '%s', %d, %d, %d, %d )",
       fname.c_str(), f.GetName(), id_entry, id_dims, CastSizeToInt(i) );
 
     Execute(sql);
    }
  }

 lem::sqlite_commit_tx(hdb);
 
 return id_entry;
}


GG_Entry* AlphabetStorage_SQLITE::LoadEntry( int id )
{
 lem::FString Select(lem::format_str( "SELECT code, id_class, id_alphabet, id_pairs FROM abc_entry"
  " WHERE id=%d", id ) );

 sqlite3_stmt *stmt1=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt1, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt1 ) == SQLITE_ROW )
    {
     const int ucs4 = sqlite3_column_int(stmt1,0);
     const int id_class = sqlite3_column_int(stmt1,1);
     const int id_alphabet = sqlite3_column_int(stmt1,2);
     const int id_pairs = sqlite3_column_int(stmt1,3);

     lem::MCollect<GramCoordPair> attrs;
     LoadPairs( id_pairs, attrs );

     GG_Entry *e = new GG_Entry( ucs4, id_class, id_alphabet, attrs );

     lem::FString Select(lem::format_str( "SELECT code, id_pairs FROM abc_form"
      " WHERE id_entry=%d ORDER BY ordnum", id ) );

     lem::MCollect<GramCoordPair> dims;

     sqlite3_stmt *stmt2=NULL;
     const char *dummy=NULL;
     int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt2, &dummy );
     if( res==SQLITE_OK )
      {
       while( sqlite3_step( stmt2 ) == SQLITE_ROW )
        {
         const lem::uint32_t Ucs4Name = sqlite3_column_int(stmt2,0);
         const int id_pairs = sqlite3_column_int(stmt2,1);
         dims.clear();
         LoadPairs( id_pairs, dims );
         e->Add( GG_EntryForm( dims, Ucs4Name ) );
        }

       sqlite3_finalize(stmt2);
      }
     else
      {
       RaiseError(__FILE__,__LINE__);
      }
    
     sqlite3_finalize(stmt1);
 
     return e;
    }
   else
    {
     lem::MemFormatter msg;
     msg.printf( "Can not find symbol entry with id=%d", id );
     throw lem::E_BaseException(msg.string());
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return NULL;
  }
}


LS_ResultSet* AlphabetStorage_SQLITE::ListEntries(void)
{
 return ListByQuery("SELECT id FROM abc_entry" );
}


int AlphabetStorage_SQLITE::CountEntries(void)
{
 int n = lem::sqlite_select_int( hdb, "SELECT count(*) from abc_entry" );
 return n;
}

int AlphabetStorage_SQLITE::CountEntryForms(void)
{
 int n = lem::sqlite_select_int( hdb, "SELECT count(*) from abc_form" );
 return n;
}


void AlphabetStorage_SQLITE::CopyDatabase( const lem::Path & alphabet_db_path )
{
 //lem::sqlite_vacuum(hdb);

 sqlite3_close(hdb);

 lem::Path sqlite_file = lem::sqlite_get_absolute_filepath(sqlite_connection_string);
 if( sqlite_file.DoesExist() )
  {
   lem::Path::CopyFile( sqlite_file, alphabet_db_path );
  }

 return;
}


int AlphabetStorage_SQLITE::FindCriterion( const lem::UCString & name )
{
 lem::UCString uname( lem::to_upper(name) );
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM abc_criterion WHERE name='%us'", uname.c_str() );
 return lem::sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}


int AlphabetStorage_SQLITE::StoreCriterion( const Criterion &x )
{
 lem::UFString name_str( lem::to_upper(x.GetName()).c_str());
 sqlite_escape(name_str);

 lem::UFString str_str( x.GetString() );
 sqlite_escape(str_str);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO abc_criterion( name, strval )"
  " VALUES ( '%us', '%us' )", name_str.c_str(), str_str.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);

 const int id = LastInsertID();
 return id;
}


Criterion* AlphabetStorage_SQLITE::GetCriterion( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name, strval FROM abc_criterion WHERE id=%d", id );

 lem::FString Select(lem::to_utf8(mem.string()));

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UCString name = lem::sqlite_column_ucstring( stmt, 0 );
     lem::UFString str = lem::sqlite_column_ufstring( stmt, 1 );
     Criterion *x = new Criterion( name, str );
     return x;
    }
   else
    {
     lem::MemFormatter mem;
     mem.printf( "Can not load the requested criterion with id=%d", id );
     throw lem::E_BaseException(mem.string());
    }

   sqlite3_finalize(stmt);
   return NULL;
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return NULL;
  }
}


LS_ResultSet* AlphabetStorage_SQLITE::EnumerateCriteria(void)
{
 return ListByQuery("SELECT id FROM abc_criterion");
}

void AlphabetStorage_SQLITE::CreateTables_Criteria(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"abc_criterion") )
  { 
   const char create_ddl[] = "CREATE TABLE abc_criterion( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE,"
                             " strval varchar(100) NOT NULL"
                             ")";

   Execute(create_ddl);
  }

 return;
}


LS_ResultSet* AlphabetStorage_SQLITE::ListCharOperations(void)
{
 return ListByQuery("SELECT id FROM abc_operation ORDER BY id" );
}


GG_CharOperation* AlphabetStorage_SQLITE::GetCharOperation( int id )
{
 lem::FString Select(lem::format_str( "SELECT name FROM abc_operation WHERE id=%d", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UCString name = lem::sqlite_column_ucstring(stmt,0);
     sqlite3_finalize(stmt);

     std::map< lem::uint32_t, lem::uint32_t > items;
     lem::FString Select2(lem::format_str( "SELECT src_char_ucs4, res_char_ucs4 FROM abc_operation_item WHERE id_operation=%d", id ) );

     sqlite3_stmt *stmt2=NULL;
     const char *dummy2=NULL;
     int res2 = sqlite3_prepare_v2( hdb, Select2.c_str(), Select2.length(), &stmt2, &dummy2 );
     if( res2==SQLITE_OK )
      {
       while( sqlite3_step( stmt2 ) == SQLITE_ROW )
        {
         const int src_char = sqlite3_column_int(stmt2,0);
         const int res_char = sqlite3_column_int(stmt2,1);
         items.insert( std::make_pair(src_char,res_char) );
        }
      }
     else
      {
       RaiseError(__FILE__,__LINE__);
      }
 
     sqlite3_finalize(stmt2);     

     return new GG_CharOperation( id, name, items );
    }
   else
    {
     LEM_STOPIT;
     return NULL;
    } 
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return NULL;
  }
}


int AlphabetStorage_SQLITE::StoreCharOperation( GG_CharOperation *operation )
{
 lem::MemFormatter q;
 q.printf( "INSERT INTO abc_operation( name ) VALUES ( '%us' )", lem::to_upper(operation->GetName()).c_str() );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);

 const int id = (int)sqlite3_last_insert_rowid(hdb);

 const std::map< lem::uint32_t, lem::uint32_t >& items = operation->Items();
 for( std::map< lem::uint32_t, lem::uint32_t >::const_iterator it=items.begin(); it!=items.end(); ++it )
  {
   lem::UCString src_char = Solarix::EncodeChar32ToWide(it->first);
   lem::UCString res_char = Solarix::EncodeChar32ToWide(it->second);

   lem::MemFormatter q;
   q.printf( "INSERT INTO abc_operation_item( id_operation, src_char, res_char, src_char_ucs4, res_char_ucs4 )"
    " VALUES ( %d, '%us', '%us', %d, %d )", 
    id, src_char.c_str(), res_char.c_str(), it->first, it->second );
   
   lem::FString s(lem::to_utf8(q.string()));
   Execute(s);
  }

 return id;
}


int AlphabetStorage_SQLITE::FindCharOperation( const lem::UCString &name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM abc_operation WHERE name='%us'", to_upper(name).c_str() );
 return sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}


void AlphabetStorage_SQLITE::CreateTables_SyllabRules(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"slb_rule") )
  { 
   const char create_ddl1[] = "CREATE TABLE slb_rule( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE,"
                             " id_src integer NOT NULL,"
                             " id_language integer NOT NULL,"
                             " cursor_shift integer NOT NULL"
                             ")";
   Execute( create_ddl1 );


   const char create_ddl2[] = "CREATE TABLE slb_condition_point( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_rule integer NOT NULL,"
                             " point_index integer NOT NULL,"
                             " n_char integer NOT NULL,"
                             " char_text varchar(30) NOT NULL,"
                             " char_ucs4 varchar(30) NOT NULL,"
                             " id_class integer NOT NULL,"
                             " id_entry integer NOT NULL,"
                             " n_coord integer NOT NULL,"
                             " id_coord0 integer NOT NULL,"
                             " id_state0 integer NOT NULL,"
                             " is_left_boundary integer NOT NULL,"
                             " is_right_boundary integer NOT NULL,"
                             " is_positive integer NOT NULL"
                             ")";
   Execute( create_ddl2 );


   const char create_ddl3[] = "CREATE TABLE slb_result_point( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_rule integer NOT NULL,"
                             " point_index integer NOT NULL,"
                             " copy_index integer NOT NULL,"
                             " merge_index0 integer NOT NULL,"
                             " merge_count integer NOT NULL"
                             ")";
   Execute( create_ddl3 );

   Execute("CREATE INDEX slb_condition_point_idx1 ON slb_condition_point(id_rule)");
   Execute("CREATE INDEX slb_result_point_idx1 ON slb_result_point(id_rule)");
  }

 return;
}



void AlphabetStorage_SQLITE::DeleteSyllabRules(void)
{
 Execute("DELETE FROM slb_rule");
 Execute("DELETE FROM slb_condition_point");
 Execute("DELETE FROM slb_result_point");

 return;
}


int AlphabetStorage_SQLITE::StoreSyllabRule( const lem::UCString &rule_name, int id_language, int id_src, int cursor_shift )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO slb_rule( name, id_src, id_language, cursor_shift ) VALUES ( '%us', %d, %d, %d )", rule_name.c_str(), id_src, id_language, cursor_shift );
 Execute(mem.string());
 return LastInsertID();
}


void AlphabetStorage_SQLITE::StoreSyllabConditionPoint(
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



void AlphabetStorage_SQLITE::StoreSyllabResultPoint(
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



LS_ResultSet* AlphabetStorage_SQLITE::ListSyllabRulesForLanguage( int id_language )
{
 return ListByQuery( lem::format_str("SELECT id FROM slb_rule WHERE id_language=%d ORDER BY id",id_language) );
}


LS_ResultSet* AlphabetStorage_SQLITE::ListSyllabRules(void)
{
 return ListByQuery( "SELECT id, name, id_src, id_language, cursor_shift FROM slb_rule ORDER BY id" );
}



LS_ResultSet* AlphabetStorage_SQLITE::ListSyllabConditionPoints(void)
{
 return ListByQuery( "SELECT id, id_rule, point_index, n_char, char_text, char_ucs4,"
                     " id_class, id_entry, n_coord, id_coord0, id_state0, is_left_boundary,"
                     " is_right_boundary, is_positive FROM slb_condition_point ORDER BY id" );
}

LS_ResultSet* AlphabetStorage_SQLITE::ListSyllabResultPoints(void)
{
 return ListByQuery( "SELECT id, id_rule, point_index, copy_index, merge_index0, merge_count FROM slb_result_point ORDER BY id" );
}



SyllabRule * AlphabetStorage_SQLITE::LoadSyllabRule( int id_rule )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name, id_src, id_language, cursor_shift FROM slb_rule WHERE id=%d", id_rule );
 std::unique_ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
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



LS_ResultSet* AlphabetStorage_SQLITE::ListSyllabConditionPointsForRule( int id_rule )
{
 LEM_CHECKIT_Z( id_rule!=UNKNOWN );

 lem::MemFormatter mem;
 mem.printf( "SELECT char_ucs4, id_class, id_entry, id_coord0, id_state0, is_left_boundary,"
                     " is_right_boundary, is_positive FROM slb_condition_point WHERE id_rule=%d ORDER BY point_index", id_rule );

 return ListByQuery( mem.string() );
}


LS_ResultSet* AlphabetStorage_SQLITE::ListSyllabResultPointsForRule( int id_rule )
{
 LEM_CHECKIT_Z( id_rule!=UNKNOWN );

 lem::MemFormatter mem;
 mem.printf( "SELECT copy_index, merge_index0, merge_count FROM slb_result_point WHERE id_rule=%d ORDER BY point_index", id_rule );

 return ListByQuery( mem.string() );
}

