#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/conversions.h>
#include <lem/sqlite_helpers.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/CplxLeft.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/coordinate.h>
#include <lem/solarix/SG_Language.h>
#include <lem/solarix/TransactionGuard_SQLITE.h>
#include <lem/solarix/GramCoordUpdator_DB.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/criterion.h>
#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_UnbreakableRule.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/WordEntrySetItem.h>
#include <lem/solarix/WordSetItem.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/ParadigmaForm.h>
#include <lem/solarix/EndingStat.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/TreeScorer.h>
#include <lem/solarix/MetaEntry.h>
#include <lem/solarix/WordAssociation.h>
#include <lem/solarix/PredicateTemplate.h>
#include <lem/solarix/PatternLinks.h>
#include <lem/solarix/TreeScorerGroupParams.h>
#include <lem/solarix/LexiconStorage_SQLITE.h>


using namespace lem;
using namespace Solarix;

static lem::UCString null_if_minus( int x )
{
 if( x==UNKNOWN )
  return UCString(L"null");
 else
  return lem::to_ustr(x);
}


static lem::CString null_if_minus8( int x )
{
 if( x==UNKNOWN )
  return lem::CString("null");
 else
  return to_str(x);
}



 static char to_ch( unsigned char b )
 {
  LEM_CHECKIT_Z( b<16 );
  return "0123456789abcdef"[b];
 }

 static char N2C[63]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
 static char n2c( int n )
 {
  LEM_CHECKIT_Z( n>0 && n<62 );
  return N2C[n];
 }

 static int c2n( char c )
 {
  if( c>='0' && c<='9' )
   return lem::uint8_t(c)-lem::uint8_t('0');
  else if( c>='a' && c>='z' )
   return 10 + lem::uint8_t(c)-lem::uint8_t('a');
  else return 36 + lem::uint8_t(c)-lem::uint8_t('A');
 }




 void Solarix::Storage_Data2Hex( const char *bytes, int size, lem::FString &str )
 {
  str.reserve( size*2+1 );
  for( int i=0; i<size; ++i )
   {
    const lem::uint8_t byte = (lem::uint8_t)bytes[i];
    if( byte<0x10 )
     {
      str.Add_Dirty( '0' );
      str.Add_Dirty( lem::int_to_str( (unsigned)byte, 16 ).c_str() );
     }
    else
     {
      str.Add_Dirty( lem::int_to_str( (unsigned)byte, 16 ).c_str() );
     }
   }

  return;
 }



 static lem::uint8_t hex2char( char c )
 {
  if( c>='0' && c<='9' )
   return lem::uint8_t(c)-lem::uint8_t('0');

  char l = tolower(c);
  if( l>='a' && l<='f' )
   return 10+lem::uint8_t(l)-lem::uint8_t('a');

  LEM_STOPIT;
  return 0;  
 }


 void Solarix::Storage_Hex2Data( const lem::FString &str, unsigned char **bytes, int *size )
 {
  *size = str.length()/2;
  
  *bytes = new unsigned char[*size];
  
  for( int i=0, j=0; i<str.length(); i+=2, j++ )
   {
    const char hi = str[i];
    const char lo = str[i+1];
    
    unsigned char byte = 16*hex2char(hi) + hex2char(lo);
    (*bytes)[j] = byte;
   }

//  chksum_crc32gentab();
//  lem::uint32_t crc32 = chksum_crc32( *bytes, *size );
//  printf( "crc32=%d\n", crc32 );

  return;
 }


LexiconStorage_SQLITE::LexiconStorage_SQLITE()
{
}


LexiconStorage_SQLITE::LexiconStorage_SQLITE( const lem::UFString &connection_string )
:sqlite_connection_string(connection_string)
{
 Connect();
 return;
}


LexiconStorage_SQLITE::~LexiconStorage_SQLITE(void)
{
 Disconnect();
 return; 
}


void LexiconStorage_SQLITE::Connect(void)
{
 hdb = lem::sqlite_open_serialized(sqlite_connection_string);
 return;
}


void LexiconStorage_SQLITE::Disconnect(void)
{
 if( hdb!=NULL )
  {
   sqlite3_close(hdb);
   hdb=NULL;
  }

 return; 
}


void LexiconStorage_SQLITE::BeginTx(void)
{
 sqlite_begin_tx(hdb);
 return;
}

void LexiconStorage_SQLITE::CommitTx(void)
{
 sqlite_commit_tx(hdb);
 return;
}


void LexiconStorage_SQLITE::RollBackTx(void)
{
 sqlite_rollback_tx(hdb);
 return;
}

TransactionGuard* LexiconStorage_SQLITE::GetTxGuard(void)
{
 return new TransactionGuard_SQLITE(hdb);
}


void LexiconStorage_SQLITE::RaiseError(void)
{
 lem::MemFormatter msg;
 msg.printf( "SQLite error, message=%us", lem::sqlite_errmsg(hdb).c_str() );
 throw E_BaseException(msg.string());
}

void LexiconStorage_SQLITE::RaiseError( const char *filename, int line )
{
 lem::MemFormatter msg;
 msg.printf( "SQLite error in file %s:%d, message=%us", filename, line, lem::sqlite_errmsg(hdb).c_str() );
 throw E_BaseException(msg.string());
}

void LexiconStorage_SQLITE::RaiseError( const lem::FString &sql )
{
 lem::UFString err(lem::sqlite_errmsg(hdb));

 lem::MemFormatter msg;
 if( sql.length()>2000 )
  msg.printf( "SQLite error sql=%s ...(string has been truncated)..., message=%us", lem::left(sql,2000).c_str(), err.c_str() );
 else
  msg.printf( "SQLite error sql=%s, message=%us", sql.c_str(), err.c_str() );

 throw E_BaseException(msg.string());
}

void LexiconStorage_SQLITE::RaiseError( const char * sql )
{
 lem::MemFormatter msg;
 msg.printf( "SQLite error sql=%s, message=%us", sql, lem::sqlite_errmsg(hdb).c_str() );
 throw E_BaseException(msg.string());
}

void LexiconStorage_SQLITE::Execute( const lem::UFString &sql )
{
 Execute( lem::to_utf8(sql) );
 return;
}

void LexiconStorage_SQLITE::Execute( const lem::FString &sql )
{
 int res = sqlite3_exec( hdb, sql.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   RaiseError(sql);
  }

 return;
}

void LexiconStorage_SQLITE::Execute( const char *sql )
{
 int res = sqlite3_exec( hdb, sql, NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   RaiseError(sql);
  }

 return;
}

int LexiconStorage_SQLITE::ExecuteAndReturnId( const lem::UFString &sql )
{
 return ExecuteAndReturnId( lem::to_utf8(sql) );
}

int LexiconStorage_SQLITE::ExecuteAndReturnId( const lem::FString &sql )
{
 int res = sqlite3_exec( hdb, sql.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   RaiseError(sql);
  }

 const int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}



LS_ResultSet* LexiconStorage_SQLITE::ListByQuery( const char *sql )
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

LS_ResultSet* LexiconStorage_SQLITE::ListByQuery( const lem::UFString & sql )
{
 return ListByQuery( lem::to_utf8(sql) );
}

LS_ResultSet* LexiconStorage_SQLITE::ListByQuery( const lem::FString & sql )
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

int LexiconStorage_SQLITE::SelectInt( const lem::UFString &Select )
{
 return SelectInt( lem::to_utf8(Select) );
}

int LexiconStorage_SQLITE::SelectInt( const lem::FString &Select )
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



void LexiconStorage_SQLITE::CreateSchema(void)
{
 CreateTables_Omonyms();
 CreateTables_MetaEntries();
 CreateTables_AuxFormTypes();
 CreateTables_AuxForms();
 CreateTables_AuxEntryData();
 CreateTables_Phrases();
 CreateTables_PartsOfSpeech();
 CreateTables_Coords();
 CreateTables_Languages();
 CreateTables_Criteria();
 CreateTables_WordEntrySets();
 CreateTables_Unbreakable();
 CreateTables_Recognizer();
 CreateTables_PhoneticMatcher();
 CreateTables_Filters();
 CreateTables_Preprocessor();
 CreateTables_Functions();
 CreateTables_SourceLocations();
 CreateTables_Paradigmas();
 CreateTables_Endings();
 CreateTables_WordformFrequency();
 CreateTables_WordAssoc();
 CreateTables_Predicates();
 
 return;
}


void LexiconStorage_SQLITE::CreateTables_Omonyms()
{
 if( !lem::sqlite_does_table_exist(hdb,"omonym") )
  {
   const char create_ddl1[] = "CREATE TABLE omonym( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " entry_name varchar(100) NOT NULL,"
                              " id_class integer NOT NULL"
                              ")";

   Execute(create_ddl1);
   Execute( "CREATE UNIQUE INDEX omonym_idx1 ON omonym(entry_name,id_class)" );
  }

 return;
}




void LexiconStorage_SQLITE::CreateTables_Predicates()
{
 if( !lem::sqlite_does_table_exist(hdb,"predicate_template") )
  {
   const char create_ddl1[] = "CREATE TABLE predicate_template( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_src integer,"
                              " src varchar(250) NOT NULL,"
                              " params varchar(100)"
                              ")";

   Execute(create_ddl1);
  }

 return;
}




void LexiconStorage_SQLITE::CreateTables_WordAssoc()
{
 if( !lem::sqlite_does_table_exist(hdb,"word_assoc") )
  {
   const char create_ddl1[] = "CREATE TABLE word_assoc( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_src integer,"
                              " id_entry integer NOT NULL,"
                              " id_entry1 integer,"
                              " id_metaentry1 integer,"
                              " word1 varchar(40),"
                              " id_entry2 integer,"
                              " id_metaentry2 integer,"
                              " word2 varchar(40),"
                              " link_type integer,"
                              " link_entry integer,"
                              " set_name varchar(40),"
                              " set_type integer,"
                              " score integer NOT NULL"
                              ")";

   Execute(create_ddl1);
   Execute("CREATE INDEX word_assoc_idx1 ON word_assoc(id_entry)");
  }

 return;
}



void LexiconStorage_SQLITE::CreateTables_MetaEntries()
{
 if( !lem::sqlite_does_table_exist(hdb,"metaentry") )
  {
   const char create_ddl1[] = "CREATE TABLE metaentry( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_class integer NOT NULL,"
                              " name varchar(40) NOT NULL"
                              ")";

   const char create_ddl2[] = "CREATE TABLE metaentry_item( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_metaentry integer NOT NULL,"
                              " id_entry integer NOT NULL"
                              ")";

   Execute(create_ddl1);
   Execute(create_ddl2);
   Execute("CREATE UNIQUE INDEX metaentry_idx1 ON metaentry(id_class,name)");
   Execute("CREATE INDEX metaentry_item_idx1 ON metaentry_item(id_metaentry)");
   Execute("CREATE UNIQUE INDEX metaentry_item_idx2 ON metaentry_item(id_metaentry,id_entry)");
  }


 return;
}


void LexiconStorage_SQLITE::CreateTables_Endings(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"endings") )
  {
   const char create_ddl1[] = "CREATE TABLE endings( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_language integer NOT NULL,"
                              " ending varchar(40),"
                              " nform integer NOT NULL,"
                              " sumfreq integer NOT NULL"
                              ")";

   const char create_ddl2[] = "CREATE TABLE ending_stat( "
                              " id_language integer PRIMARY KEY NOT NULL,"
                              " max_len integer"
                              ")";

   Execute(create_ddl1);
   Execute(create_ddl2);
   Execute("CREATE UNIQUE INDEX endings_idx1 ON endings(ending,id_language)");
  }

 return;
}


void LexiconStorage_SQLITE::CreateTables_WordformFrequency(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"wordform_frequency") )
  {
   const char create_ddl1[] = "CREATE TABLE wordform_frequency( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_entry integer NOT NULL,"
                              " iform integer NOT NULL,"
                              " freq integer NOT NULL"
                              ")";

   Execute(create_ddl1);
   Execute("CREATE UNIQUE INDEX wordform_frequency_idx1 ON wordform_frequency(id_entry,iform)");
  }

 return;
}




void LexiconStorage_SQLITE::CreateTables_Preprocessor(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"crop_rule") )
  { 
   const char create_ddl9[] = "CREATE TABLE crop_rule( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " name varchar(32),"
                              " r_condition varchar(256) NOT NULL,"
                              " r_result varchar(256) NOT NULL,"
                              " id_language integer NOT NULL,"
                              " id_src integer,"
                              " is_prefix integer NOT NULL,"
                              " is_affix integer NOT NULL,"
                              " is_regex integer NOT NULL,"
                              " case_sensitive integer NOT NULL,"
                              " rel integer not null"
                              ")";


   const int N=9;
   const char* create_ddl[N] = { create_ddl9 };

   for( int i=0; i<N; ++i )
    {
     Execute(create_ddl[i]);
    }
  }
 
 return;
}

void LexiconStorage_SQLITE::CreateTables_Recognizer(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"recog_rule") )
  { 
   const char create_ddl1[] = "CREATE TABLE recog_rule( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL,"
                             " id_language integer NOT NULL,"
                             " id_src integer,"
                             " is_regex integer not null,"
                             " is_syllab integer not null,"
                             " is_prefix integer not null,"
                             " is_affix integer not null,"
                             " r_condition varchar(100) not null,"
                             " case_sensitive integer not null,"
                             " word varchar(100),"
                             " id_entry integer not null,"
                             " rel integer not null,"
                             " coords varchar(300) not null"
                             ")";

   const char create_ddl1_1[] = "CREATE INDEX recog_rule_idx1 ON recog_rule(word,id_language)";

   const char create_ddl2[] = "CREATE TABLE misspelling( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_language integer NOT NULL,"
                             " original_word varchar(30) not null,"
                             " substitution varchar(30) not null"
                             ")";

   const char create_ddl3[] = "CREATE INDEX misspelling_idx1 ON misspelling(original_word,id_language)";
   const char create_ddl4[] = "CREATE INDEX misspelling_idx2 ON misspelling(original_word)";

   Execute(create_ddl1);
   Execute(create_ddl2);
   Execute(create_ddl3);
   Execute(create_ddl4);
  }

 return;
}



void LexiconStorage_SQLITE::CreateTables_Functions(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"tr_functions") )
  { 
   const char create_ddl[] = "CREATE TABLE tr_functions( "
                             " marker varchar(3) NOT NULL,"
                             " segment_no integer NOT NULL,"
                             " bin varchar(100000) NOT NULL"
                             ")";

   Execute(create_ddl);
  }

 return;
}


void LexiconStorage_SQLITE::CreateTables_PhoneticMatcher(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"ph_rule") )
  { 
   const char create_ddl[] = "CREATE TABLE ph_rule( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL,"
                             " id_language integer NOT NULL,"
                             " id_src integer,"
                             " r_condition varchar(30) not null,"
                             " r_result varchar(30) not null,"
                             " is_prefix integer not null,"
                             " is_affix integer not null,"
                             " rel integer not null"
                             ")";

   Execute(create_ddl);
  }

 return;
}

void LexiconStorage_SQLITE::CreateTables_SourceLocations(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"src_filename") )
  { 
   const char create_ddl1[] = "CREATE TABLE src_filename( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " filepath varchar(2000) NOT NULL,"
                              " filepath0 varchar(2000) NOT NULL"
                              ")";
   Execute(create_ddl1);

   const char create_ddl2[] = "CREATE TABLE src_location( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_filename integer NOT NULL,"
                              " line_no integer NOT NULL,"
                              " column_no integer NOT NULL"
                              ")";
   Execute(create_ddl2);
  }

 return;
}




void LexiconStorage_SQLITE::CreateTables_WordEntrySets(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"word_entry_set") )
  { 
   const char create_ddl1[] = "CREATE TABLE word_entry_set( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " name varchar(32) NOT NULL,"
                              " ies varchar(1000) NOT NULL"
                              ")";

   const char create_ddl2[] = "CREATE TABLE word_set( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " name varchar(32) NOT NULL,"
                              " case_sensitive integer NOT NULL,"
                              " words varchar(10000) NOT NULL"
                              ")";

   const char create_ddl3[] = "CREATE UNIQUE INDEX word_entry_set_idx1 ON word_entry_set(name)";
   const char create_ddl4[] = "CREATE UNIQUE INDEX word_set_idx1 ON word_set(name)";

   Execute(create_ddl1);
   Execute(create_ddl2);
   Execute(create_ddl3);
   Execute(create_ddl4);

   const char create_ddl5[] = "CREATE TABLE collocation_set( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " name varchar(32) NOT NULL,"
                              " case_sensitive integer NOT NULL"
                              ")";


   const char create_ddl6[] = "CREATE TABLE collocation_set_item( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_set integer NOT NULL,"
                              " words varchar(1000) NOT NULL,"
                              " n_word integer NOT NULL,"
                              " headword varchar(30) NOT NULL"
                              ")";

   const char create_ddl7[] = "CREATE TABLE collocation_headword( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " headword varchar(32) NOT NULL,"
                              " min_len integer NOT NULL,"
                              " max_len integer NOT NULL"
                              ")";

   Execute(create_ddl5);
   Execute(create_ddl6);
   Execute(create_ddl7);

   const char create_ddl8[] = "CREATE UNIQUE INDEX collocation_set_idx1 ON collocation_set(name)";
   const char create_ddl9[] = "CREATE UNIQUE INDEX collocation_headword_idx1 ON collocation_headword(headword)";
   const char create_ddl10[] = "CREATE INDEX collocation_set_item_idx1 ON collocation_set_item(headword,id_set)";
   const char create_ddl11[] = "CREATE UNIQUE INDEX collocation_set_item_idx2 ON collocation_set_item(words,id_set)";

   Execute(create_ddl8);
   Execute(create_ddl9);
   Execute(create_ddl10);
   Execute(create_ddl11);


   const char create_ddl20[] = "CREATE TABLE wordform_set( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " name varchar(32) NOT NULL"
                              ")";

   const char create_ddl21[] = "CREATE TABLE wordform_set_item( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_set integer NOT NULL,"
                              " word varchar(32) NOT NULL,"
                              " id_entry integer NOT NULL,"
                              " id_coords integer NOT NULL"
                              ")";

   const char create_ddl22[] = "CREATE TABLE wordform_set_coords( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " coords varchar(1000) NOT NULL"
                              ")";

   const char create_ddl23[] = "CREATE UNIQUE INDEX wordform_set_idx1 ON wordform_set(name)";
   const char create_ddl24[] = "CREATE INDEX wordform_set_item_idx1 ON wordform_set_item(id_set,word,id_entry)";
   const char create_ddl25[] = "CREATE UNIQUE INDEX wordform_set_coords_idx1 ON wordform_set_coords(coords)";

   Execute(create_ddl20);
   Execute(create_ddl21);
   Execute(create_ddl22);
   Execute(create_ddl23);
   Execute(create_ddl24);
   Execute(create_ddl25);
  }

 return;
}


void LexiconStorage_SQLITE::CreateTables_Unbreakable(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"unbreakable") )
  { 
   const char create_ddl[] = "CREATE TABLE unbreakable( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL,"
                             " id_language integer NOT NULL,"
                             " id_src integer,"
                             " pattern varchar(100) NOT NULL,"
                             " is_regex integer NOT NULL"
                             ")";
   Execute(create_ddl);
  }

 return;
}


void LexiconStorage_SQLITE::CreateTables_AuxFormTypes(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"aux_form_types") )
  { 
   const char create_ddl[] = "CREATE TABLE aux_form_types( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE"
                             ")";
   Execute(create_ddl);
  }

 return;
}





void LexiconStorage_SQLITE::AddAuxFormType( int id, const lem::UCString &name )
{
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO aux_form_types( id, name ) VALUES ( %d, '%us' )", id, lem::to_upper(name).c_str() );
 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);
 return;
}


LS_ResultSet* LexiconStorage_SQLITE::ListAuxFormTypes(void)
{
 return ListByQuery("SELECT id, name FROM aux_form_types ORDER BY id");
}

void LexiconStorage_SQLITE::CreateTables_AuxForms(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"aux_form") )
  { 
   const char create_ddl[] = "CREATE TABLE aux_form( "
                             "id integer PRIMARY KEY,"
                             "id_entry INTEGER NOT NULL,"
                             "iform INTEGER NOT NULL,"
                             "data_type INTEGER NOT NULL,"
                             "data_text varchar(200)"
                             ")";

   Execute(create_ddl);
   Execute("CREATE INDEX aux_form_idx1 ON aux_form(id_entry,iform)");

   const char create_ddl2[] = "CREATE TABLE aux_word( "
                             "id integer PRIMARY KEY,"
                             "aux_type INTEGER NOT NULL,"
                             "src varchar(30),"
                             "res varchar(200)"
                             ")";

   Execute(create_ddl2);
   Execute("CREATE INDEX aux_word_idx1 ON aux_word(aux_type,src)");
  }

 return;
}

int LexiconStorage_SQLITE::AddAuxForm( int ekey, int iform, int aux_type, const lem::UFString &aux_data )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( iform!=UNKNOWN );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::UFString aux_data2(aux_data);
 sqlite_escape(aux_data2);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO aux_form( id_entry, iform, data_type, data_text )"
  " VALUES ( %d, %d, %d, '%us' )", ekey, iform, aux_type, aux_data2.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


int LexiconStorage_SQLITE::GetAuxForm( int ekey, int iform, int aux_type, lem::UFString &aux_data )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( iform!=UNKNOWN );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, data_text FROM aux_form "
  "WHERE id_entry=%d AND iform=%d AND data_type=%d", ekey, iform, aux_type ) );

 int id=UNKNOWN;

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     id = sqlite3_column_int(stmt,0);
     aux_data = lem::sqlite_column_ufstring(stmt,1);
    }
  }
 else
  {
   RaiseError( __FILE__, __LINE__ );
  }

 if( id==UNKNOWN )
  {
   aux_data.clear();
  }

 sqlite3_finalize(stmt);

 return id;
}


LS_ResultSet* LexiconStorage_SQLITE::ListAuxForms(void)
{
 return ListByQuery("SELECT id, id_entry, iform, data_type, data_text FROM aux_form");
}


LS_ResultSet* LexiconStorage_SQLITE::ListAuxForms( int ekey, int iform )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( iform!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, data_type, data_text FROM aux_form "
  "WHERE id_entry=%d AND iform=%d", ekey, iform ) );

 return ListByQuery(Select);
}









int LexiconStorage_SQLITE::AddAuxWord( const lem::UCString & src, int aux_type, const lem::UFString & aux_data )
{
 LEM_CHECKIT_Z( !src.empty() );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::UFString s2(src.c_str());
 sqlite_escape(s2);

 lem::UFString aux_data2(aux_data);
 sqlite_escape(aux_data2);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO aux_word( src, aux_type, res )"
  " VALUES ( '%us', %d, '%us' )", s2.c_str(), aux_type, aux_data2.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


int LexiconStorage_SQLITE::GetAuxWord( const lem::UCString & src, int aux_type, lem::UFString & aux_data )
{
 LEM_CHECKIT_Z( !src.empty() );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::UFString s2(src.c_str());
 sqlite_escape(s2);

 lem::MemFormatter mem;
 mem.printf( "SELECT id, res FROM aux_word WHERE src='%us' AND aux_type=%d", s2.c_str(), aux_type );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   aux_data = rs->GetUFString(1);
   return rs->GetInt(0);
  }
 else
  return UNKNOWN;
}


LS_ResultSet* LexiconStorage_SQLITE::ListAuxWords(void)
{
 return ListByQuery("SELECT id, src, aux_type, res FROM aux_word");
}


LS_ResultSet* LexiconStorage_SQLITE::ListAuxWords( const lem::UCString & src )
{
 LEM_CHECKIT_Z( !src.empty() );

 lem::UFString s2(src.c_str());
 sqlite_escape(s2);

 lem::MemFormatter mem;
 mem.printf( "SELECT id, aux_type, res FROM aux_word WHERE src='%us'", s2.c_str() );

 return ListByQuery(mem.string());
}




void LexiconStorage_SQLITE::CreateTables_AuxEntryData(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"aux_entry_data") )
  { 
   const char create_ddl[] = "CREATE TABLE aux_entry_data( "
                             "id integer PRIMARY KEY,"
                             "id_entry INTEGER NOT NULL,"
                             "data_type INTEGER NOT NULL,"
                             "data_text varchar(200)"
                             ")";

   Execute(create_ddl);
   Execute("CREATE INDEX aux_entry_data_idx1 ON aux_entry_data(id_entry)");
  }

 return;
}

int LexiconStorage_SQLITE::AddAuxEntryData( int ekey, int aux_type, const lem::UFString &aux_data )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::UFString aux_data2(aux_data);
 sqlite_escape(aux_data2);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO aux_entry_data( id_entry, data_type, data_text )"
  " VALUES ( %d, %d, '%us' )", ekey, aux_type, aux_data2.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


int LexiconStorage_SQLITE::GetAuxEntryData( int ekey, int aux_type, lem::UFString &aux_data )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, data_text FROM aux_entry_data "
  "WHERE id_entry=%d AND data_type=%d", ekey, aux_type ) );

 int id=UNKNOWN;

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     id = sqlite3_column_int(stmt,0);
     aux_data = lem::sqlite_column_ufstring(stmt,1);
    }
  }
 else
  {
   RaiseError( __FILE__, __LINE__ );
  }

 if( id==UNKNOWN )
  {
   aux_data.clear();
  }

 sqlite3_finalize(stmt);

 return id;
}


LS_ResultSet* LexiconStorage_SQLITE::ListAuxEntryData(void)
{
 return ListByQuery("SELECT id, id_entry, data_type, data_text FROM aux_entry_data");
}



LS_ResultSet* LexiconStorage_SQLITE::ListAuxEntryData( int ekey )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, data_type, data_text FROM aux_entry_data "
  "WHERE id_entry=%d", ekey ) );

 return ListByQuery(Select);
}



void LexiconStorage_SQLITE::ReplaceEntryKey( int old_ekey, int new_ekey )
{
 LEM_CHECKIT_Z( old_ekey!=UNKNOWN );
 LEM_CHECKIT_Z( new_ekey!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "UPDATE aux_form SET id_entry=%d WHERE id_entry=%d", new_ekey, old_ekey );

 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);

 ms.printf( "UPDATE aux_entry_data SET id_entry=%d WHERE id_entry=%d", new_ekey, old_ekey );
 s = lem::to_utf8(ms.string());
 Execute(s);
 
 return;
}


void LexiconStorage_SQLITE::CopyDatabase( const lem::Path & lexicon_db_path )
{
 //lem::sqlite_vacuum(hdb);

 Disconnect();

 lem::Path sqlite_file = lem::sqlite_get_absolute_filepath(sqlite_connection_string);
 if( sqlite_file.DoesExist() )
  {
   lem::Path::CopyFile( sqlite_file, lexicon_db_path );
  }

 return;
}

void LexiconStorage_SQLITE::CreateTables_Phrases(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"sg_tentry") )
  { 
   const char create_twords[] = "CREATE TABLE sg_tentry( "
                                " te_id integer PRIMARY KEY NOT NULL,"
                                " te_text varchar(1024) NOT NULL UNIQUE,"
                                " te_utxt varchar(1024) NOT NULL,"
                                " te_id_language integer,"
                                " te_id_class integer,"
                                " te_syntax_flags integer"
                                ")";
   Execute(create_twords);


   // Таблица со служебной информацией для комплексных связей с многословной левой частью
   const char create_cplx[] = "CREATE TABLE cplx_left( "
                              " cl_id integer PRIMARY KEY NOT NULL,"
                              " cl_headword varchar(32) NOT NULL,"
                              " cl_minlen integer NOT NULL,"
                              " cl_maxlen integer NOT NULL"
                              ")";
   Execute(create_cplx);

   const char create_tnotes[] = "CREATE TABLE tnotes( "
                                " tn_id integer PRIMARY KEY NOT NULL,"
                                " tn_te_id integer NOT NULL,"
                                " tn_type integer NOT NULL,"
                                " tn_format integer NOT NULL,"
                                " tn_data varchar(4096)"
                                ")";
   Execute(create_tnotes);


   const char* ci[] = {
                       "CREATE UNIQUE INDEX sg_tentry_idx1 ON sg_tentry(te_id)",
                       "CREATE INDEX sg_tentry_idx2 ON sg_tentry(te_utxt)",
                       "CREATE INDEX cplx1 ON CPLX_LEFT(cl_headword)",
                       "CREATE INDEX inotes1 ON TNOTES(tn_te_id)",
                       NULL
                      };

   int i=0;
   while( ci[i]!=NULL )
    {
     Execute(ci[i]);
     i++;
    }

 }

 return;
}


int LexiconStorage_SQLITE::CountPhrases(void)
{
 return lem::sqlite_select_int( hdb, "SELECT count(*) FROM sg_tentry" );
}


LS_ResultSet* LexiconStorage_SQLITE::ListPhrases(void)
{
 return ListByQuery("SELECT te_id, te_text, te_utxt, te_id_language, te_id_class, te_syntax_flags FROM sg_tentry");
}



int LexiconStorage_SQLITE::FindPhrase( const lem::UFString &text, bool ignore_case )
{
 int te_id=UNKNOWN;

 UFString u(text);
 sqlite_escape(u);
 
 if( ignore_case )
  {
   // поиск без учета регистра

   MemFormatter ms;
   ms.printf( "SELECT te_id FROM sg_tentry WHERE te_utxt='%us'", to_upper(u).c_str() );
   FString Select=lem::to_utf8(ms.string());

   sqlite3_stmt *stmt=NULL;
   const char *dummy=NULL;
   int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
   if( res==SQLITE_OK )
    {
     if( sqlite3_step( stmt ) == SQLITE_ROW )
      {
       te_id = sqlite3_column_int(stmt,0);
      }

     sqlite3_finalize(stmt);
    }
   else
    {
     RaiseError( __FILE__, __LINE__ );
    }
  }
 else
  {
   MemFormatter ms;
   ms.printf( "SELECT id FROM sg_tentry WHERE txt='%us'", u.c_str() );
   FString Select=to_utf8(ms.string());

   sqlite3_stmt *stmt=NULL;
   const char *dummy=NULL;
   int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
   if( res==SQLITE_OK )
    {
     if( sqlite3_step( stmt ) == SQLITE_ROW )
      {
       te_id = sqlite3_column_int(stmt,0);
      }

     sqlite3_finalize(stmt);
    }
   else
    {
     RaiseError( __FILE__, __LINE__ );
    }
  }

 return te_id;
}


LS_ResultSet* LexiconStorage_SQLITE::ListPhrasesWithPrefix( const lem::UFString &mask, bool ignore_case )
{
 UFString u(mask);
 sqlite_escape(u);
 
 if( ignore_case )
  {
   // поиск без учета регистра
   MemFormatter ms;
   ms.printf( "SELECT te_id FROM sg_tentry WHERE te_utxt LIKE '%us%%'", to_upper(u).c_str() );
   FString Select=lem::to_utf8(ms.string());
   return ListByQuery(Select);
  }
 else
  {
   // с учетом регистра
   MemFormatter ms;
   ms.printf( "SELECT te_id FROM sg_tentry WHERE te_text LIKE '%us%%'", u.c_str() );
   FString Select=to_utf8(ms.string());
   return ListByQuery(Select);
  }
}


bool LexiconStorage_SQLITE::GetPhrase( int id_phrase, SG_Phrase &phrase )
{
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );

 bool found=false;

 FString Select( lem::format_str(
  "SELECT te_text, Coalesce(te_id_language,-1), Coalesce(te_id_class,-1), Coalesce(te_syntax_flags,0)"
  " FROM sg_tentry"
  " WHERE te_id=%d", id_phrase ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     phrase.id = id_phrase; 
     phrase.text = lem::sqlite_column_ufstring(stmt,0);
     phrase.id_language = sqlite3_column_int(stmt,1);
     phrase.id_class = sqlite3_column_int(stmt,2);
     phrase.syntax_flags = sqlite3_column_int(stmt,3);
     found = true;
    }

   sqlite3_finalize(stmt);
  }
 else
  {
   RaiseError( __FILE__, __LINE__ );
  }

 return found;
}


int LexiconStorage_SQLITE::AddPhrase( SG_Phrase &info )
{
 UFString txt(info.GetText());
 sqlite_escape(txt);

 UFString utxt( to_upper(txt) );

 MemFormatter mf2;
 mf2.printf( "INSERT INTO sg_tentry( te_text, te_utxt, te_id_language, te_id_class, te_syntax_flags )"
 " VALUES ( '%us', '%us', %s, %s, %s )", txt.c_str(), utxt.c_str(),
  null_if_minus8(info.id_language).c_str(),
  null_if_minus8(info.id_class).c_str(),
  null_if_minus8(info.syntax_flags).c_str() );

 lem::FString s=lem::to_utf8(mf2.string());
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 info.id = id;
 return id;
}


void LexiconStorage_SQLITE::DeletePhrase( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::MemFormatter ms;

 // удалим ссылающиеся на sg_tentry записи

 ms.printf( "DELETE FROM tnotes WHERE tn_te_id=%d", id );
 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);

 ms.printf( "DELETE FROM sg_tentry WHERE te_id=%d", id );
 s = lem::to_utf8(ms.string());
 Execute(s);

 return;
}


void LexiconStorage_SQLITE::UpdatePhrase( const SG_Phrase &te )
{
 lem::UFString uutf8(te.text);
 sqlite_escape(uutf8);

 lem::UFString uuutf8(to_upper(uutf8));

 MemFormatter mf;
 mf.printf( "UPDATE sg_tentry SET te_text='%us', te_utxt='%us', te_id_language=%s, te_id_class=%s, te_syntax_flags=%d"
            " WHERE te_id=%d", uutf8.c_str(), uuutf8.c_str(),
            null_if_minus8(te.id_language).c_str(), null_if_minus8(te.id_class).c_str(), 
            te.GetSyntaxFlags(), te.id );
 lem::FString s=lem::to_utf8(mf.string());
 Execute(s);

 return;
}




LS_ResultSet* LexiconStorage_SQLITE::ListPhraseNotes( int id_phrase )
{
 FString Select( lem::format_str(
  "SELECT tn_id, tn_type, tn_data"
  " FROM tnotes"
  " WHERE tn_te_id=%d", id_phrase ) );

 return ListByQuery(Select);
}


bool LexiconStorage_SQLITE::GetPhraseNote( int id, SG_PhraseNote &note )
{
 bool found=false;

 FString Select( lem::format_str(
    "SELECT tn_type, tn_data"
    " FROM tnotes"
    " WHERE tn_id=%d", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     note.type = sqlite3_column_int(stmt,0);
     note.data = lem::sqlite_column_ufstring(stmt,1);
     note.tn_id = id;
     found = true; 
    }

   sqlite3_finalize(stmt);
   return found;
  }
 else
  {
   RaiseError( __FILE__, __LINE__ );
   return false;
  }
}


int LexiconStorage_SQLITE::GetPhraseNote( int id_entry, int note_type, SG_PhraseNote &note )
{
 FString Select( lem::format_str(
    "SELECT tn_id, tn_data"
    " FROM tnotes"
    " WHERE tn_te_id=%d AND tn_type=%d", id_entry, note_type ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     note.tn_id = sqlite3_column_int(stmt,0);
     note.data = lem::sqlite_column_ufstring(stmt,1);
    }

   sqlite3_finalize(stmt);
   return note.tn_id;
  }
 else
  {
   RaiseError( __FILE__, __LINE__ );
   return -1;
  }
}



int LexiconStorage_SQLITE::FindPhraseNote( const lem::UFString &text, int type, int &te_id )
{
 int tn_id=UNKNOWN;
 te_id=UNKNOWN;

 UFString u(text);
 sqlite_escape(u);
  
 MemFormatter mf;
 mf.printf( "SELECT tn_id, tn_te_id"
            " FROM TNOTES"
            " WHERE tn_data='%us' AND tn_type=%d", u.c_str(), type );
 FString Select=to_utf8(mf.string());

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     tn_id = sqlite3_column_int(stmt,0);
     te_id = sqlite3_column_int(stmt,1);
    }

   sqlite3_finalize(stmt);
  }
 else
  {
   RaiseError( __FILE__, __LINE__ );
  }

 return tn_id;
}


LS_ResultSet* LexiconStorage_SQLITE::ListCplxLeft(void)
{
 return ListByQuery("SELECT cl_id, cl_headword, cl_minlen, cl_maxlen FROM cplx_left");
}



int LexiconStorage_SQLITE::GetCplxLeft( const lem::UCString &headword, CplxLeft &info )
{
 LEM_CHECKIT_Z( !headword.empty() );

 int cl_id=UNKNOWN;

 UFString w16(headword.c_str());
 w16.to_upper();
 sqlite_escape(w16);

 lem::MemFormatter mem;
 mem.printf( "SELECT cl_id, cl_minlen, cl_maxlen FROM cplx_left WHERE cl_headword='%us'", w16.c_str() );
 FString Select( lem::to_utf8(mem.string()) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     cl_id = sqlite3_column_int(stmt,0);
     const int cl_minlen = sqlite3_column_int(stmt,1);
     const int cl_maxlen = sqlite3_column_int(stmt,2);
     info.headword = headword;
     info.minlen = cl_minlen;
     info.maxlen = cl_maxlen;
    }

   sqlite3_finalize(stmt);
  }
 else
  {
   RaiseError( __FILE__, __LINE__ );
  }

 return cl_id;
}




int LexiconStorage_SQLITE::StoreCplxLeft( const lem::UCString &headword, int minlen, int maxlen )
{
 LEM_CHECKIT_Z( !headword.empty() );
 LEM_CHECKIT_Z( minlen>0 );
 LEM_CHECKIT_Z( maxlen>=minlen && maxlen<100 );

 UFString w16(headword.c_str());
 w16.to_upper();
 sqlite_escape(w16);

 FString uutf8(lem::to_utf8( w16 ) );

 // Если запись для такого слова уже есть - например при слиянии двух тезаурусов...
 CplxLeft old_info;
 int cl_id = GetCplxLeft( headword, old_info );

 if( cl_id!=UNKNOWN )
  {
   // ... тогда обновим ее
   const int minlen2 = std::min( minlen, old_info.minlen );
   const int maxlen2 = std::max( maxlen, old_info.maxlen );

   lem::FString s( lem::format_str( "UPDATE cplx_left SET cl_minlen=%d, cl_maxlen=%d"
      " WHERE cl_id=%d", minlen2, maxlen2, cl_id ) );
   Execute(s);
  }
 else
  {
   // либо вносим новую запись
   lem::MemFormatter mem;
   mem.printf( "INSERT INTO cplx_left( cl_headword, cl_minlen, cl_maxlen )"
        " VALUES ( '%us', %d, %d )", w16.c_str(), minlen, maxlen );
   cl_id = ExecuteAndReturnId(mem.string());
  }

 // Возвращаем ID измененной или добавленной записи.
 return cl_id;
}



void LexiconStorage_SQLITE::ClearCplxLeft( const lem::UCString &headword )
{
 LEM_CHECKIT_Z( !headword.empty() );

 UFString w16(headword.c_str());
 w16.to_upper();
 sqlite_escape(w16);

 FString uutf8(lem::to_utf8( w16 ) );
 lem::MemFormatter ms;
 ms.printf( "DELETE cplx_left WHERE cl_headword='%s'", uutf8.c_str() );
 lem::FString s( lem::to_utf8(ms.string()) );
 Execute(s);

 return;
}


int LexiconStorage_SQLITE::AddPhraseNote( int id_phrase, int type, const lem::UFString &text )
{
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );
 LEM_CHECKIT_Z( type!=UNKNOWN );

 UFString a(text);
 sqlite_escape(a);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO tnotes( tn_te_id, tn_type, tn_format, tn_data )"
      " VALUES ( %d, %d, 0, '%us' )", id_phrase, type, a.c_str() );
 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


void LexiconStorage_SQLITE::DeletePhraseNotes( int id_phrase )
{
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );
 lem::FString s( lem::format_str( "DELETE FROM tnotes WHERE tn_te_id=%d", id_phrase ) );
 Execute(s);
 return;
}


void LexiconStorage_SQLITE::DeletePhraseNote( int id_note )
{
 LEM_CHECKIT_Z( id_note!=UNKNOWN );
 lem::FString s( lem::format_str( "DELETE FROM tnotes WHERE tn_id=%d", id_note ) );
 Execute(s);
 return;
}

void LexiconStorage_SQLITE::CreateTables_PartsOfSpeech(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"sg_class") )
  { 
   const char create_ddl[] = "CREATE TABLE sg_class( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE,"
                             " name_aliase varchar(32),"
                             " weight int,"
                             " id_lang int,"
                             " closed_class int"
                             ")";
   Execute( create_ddl );

   const char create_ddl2[] = "CREATE TABLE sg_class_coord( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_class int NOT NULL,"
                             " id_coord int NOT NULL,"
                             " coord_type int NOT NULL"
                             ")";
   Execute( create_ddl2 );

   const char create_ddl3[] = "CREATE TABLE class_attr_def( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_class int NOT NULL,"
                             " id_coord int NOT NULL,"
                             " default_state int NOT NULL"
                             ")";
   Execute( create_ddl3 );
  }

 return;
}




int LexiconStorage_SQLITE::CountPartsOfSpeech(void)
{
 return lem::sqlite_select_int( hdb, "SELECT count(*) FROM sg_class" );
}

namespace
{
 inline bool char_one_of( wchar_t c, wchar_t x, wchar_t y, wchar_t z )
 { return c==x || c==y || c==z; }
}

int LexiconStorage_SQLITE::FindPartOfSpeech( const lem::UCString &name )
{
 // если в проверяемом имени есть символы ', "" или пробел - сразу возвращает false.
 for( int i=0; i<name.length(); ++i )
  if( char_one_of( name[i], L'"', L'\'', L' ' ) )
   return UNKNOWN;

 MemFormatter ms;
 UCString uname(to_upper(name));

 ms.printf( "SELECT id FROM sg_class WHERE name='%us' OR name_aliase='%us'"
  , uname.c_str(), uname.c_str() );

 FString Select=lem::to_utf8(ms.string());

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
   RaiseError( __FILE__, __LINE__ );
   return -1;
  }
}


int LexiconStorage_SQLITE::AddPartOfSpeech( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 lem::UFString s( to_upper(name).c_str());
 sqlite_escape(s);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_class( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


int LexiconStorage_SQLITE::AddPartOfSpeech( const Solarix::SG_Class &cls )
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
 ms.printf( "INSERT INTO sg_class( name, name_aliase, weight, id_lang, closed_class )"
           " VALUES ( '%us', '%us', %d, %d, %d )", s.c_str(), aliases.c_str(), cls.GetValue(), cls.GetLanguage(), cls.IsClosed() ? 1 : 0 );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 const int id = (int)sqlite3_last_insert_rowid(hdb);
 StoreClassInternals(id,cls);

 return id;
}


void LexiconStorage_SQLITE::StorePartOfSpeech( int id, const SG_Class &cls )
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
 ms.printf( "UPDATE sg_class SET name='%us', name_aliase='%us', weight=%d, id_lang=%d, closed_class=%d "
           " WHERE id=%d", s.c_str(), aliases.c_str(), cls.GetValue(), cls.GetLanguage(), cls.IsClosed() ? 1 : 0, id );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 StoreClassInternals( id, cls );

 return;
}


void LexiconStorage_SQLITE::StoreClassInternals( int id, const SG_Class &cls )
{
 lem::MemFormatter ms;

 for( lem::Container::size_type k=0; k<cls.attrs().size(); ++k )   
  {
   const GramCoordAdr &atr = cls.attrs()[k];

   ms.printf(
             "INSERT INTO sg_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 0 );\n"
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
             "INSERT INTO sg_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 1 );\n"
             , id
             , dim.GetIndex()
            );

   lem::FString s(lem::to_utf8(ms.string()));
   Execute(s);
  }

 for( lem::Container::size_type k=0; k<cls.tags().size(); ++k )   
  {
   const GramCoordAdr &tag = cls.tags()[k];

   ms.printf(
             "INSERT INTO sg_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 2 );\n"
             , id
             , tag.GetIndex()
           );

   lem::FString s(lem::to_utf8(ms.string()));
   Execute(s);
  }


 for( lem::Container::size_type k=0; k<cls.attr_defaults.size(); ++k )   
  {
   const GramCoordAdr &attr = cls.attr_defaults[k].first;
   const int def_state = cls.attr_defaults[k].second;

   ms.printf(
             "INSERT INTO class_attr_def( id_class, id_coord, default_state ) VALUES( %d, %d, %d );\n"
             , id
             , attr.GetIndex()
             , def_state
           );

   lem::FString s(lem::to_utf8(ms.string()));
   Execute(s);
  }


 return;
}

bool LexiconStorage_SQLITE::GetPartOfSpeech( int id, SG_Class &cls )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT name, name_aliase, Coalesce(weight,0), Coalesce(id_lang,-1), closed_class"
  " FROM sg_class"
  " WHERE id=%d", id ) );

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

     UCString aliase = lem::sqlite_column_ucstring(stmt,1);
     if( !aliase.empty() )
      cls.aliases.Add(aliase);

     cls.value = sqlite3_column_int(stmt,2);
     cls.id_lang = sqlite3_column_int(stmt,3);
     cls.closed_class = sqlite3_column_int(stmt,4)==1;
    }
  }
 else
  {
   RaiseError( __FILE__, __LINE__ );
  }

 sqlite3_finalize(stmt);

 if( found )
  { 
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   cls.is_realized=true;
   #endif

   lem::FString Select2(lem::format_str( "SELECT id_coord, coord_type FROM sg_class_coord "
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
        case 2: cls.tag_index.push_back( id_coord ); break;
        default: LEM_STOPIT;
       }
      }
    }
   else
    {
     RaiseError( __FILE__, __LINE__ );
    }

   sqlite3_finalize(stmt2);


   cls.attr_defaults.clear();
   lem::FString Select3(lem::format_str( "SELECT id_coord, default_state FROM class_attr_def "
    "WHERE id_class=%d", id ) );

   sqlite3_stmt *stmt3=NULL;
   const char *dummy3=NULL;
   int res3 = sqlite3_prepare_v2( hdb, Select3.c_str(), Select3.length(), &stmt3, &dummy3 );
   if( res3==SQLITE_OK )
    {
     while( sqlite3_step( stmt3 ) == SQLITE_ROW )
      {
       const int id_coord = sqlite3_column_int(stmt3,0);
       const int def_state = sqlite3_column_int(stmt3,1);
       cls.attr_defaults.push_back( std::make_pair( GramCoordAdr(id_coord), def_state ) );
      }
    }
   else
    {
     RaiseError( __FILE__, __LINE__ );
    }

   sqlite3_finalize(stmt3);
  }

 return found;
}

LS_ResultSet* LexiconStorage_SQLITE::ListPartsOfSpeech(void)
{
 return ListByQuery("SELECT id FROM sg_class ORDER BY id");
}


void LexiconStorage_SQLITE::CreateTables_Coords(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"sg_coord") )
  { 
   const char create_ddl[] = "CREATE TABLE sg_coord( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE,"
                             " bistable int"
                             ")";

   Execute(create_ddl);

   const char create_ddl2[] = "CREATE TABLE sg_state( "
                             " id_pk integer PRIMARY KEY NOT NULL,"
                             " id int NOT NULL,"
                             " id_coord int NOT NULL,"
                             " name varchar(32) NOT NULL,"
                             " id_parent int NOT NULL,"
                             " weight int NOT NULL" 
                             ")";

   Execute(create_ddl2);
  }

 return;
}

int LexiconStorage_SQLITE::CountCoords(void)
{
 return lem::sqlite_select_int( hdb, "SELECT count(*) FROM sg_coord" );
}


bool LexiconStorage_SQLITE::GetCoord( int id, GramCoord &coord )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );
 lem::FString Select( lem::format_str("SELECT name, bistable FROM sg_coord WHERE id=%d", id) );

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
       lem::FString Select2( lem::format_str("SELECT id, id_parent, name, weight FROM sg_state WHERE id_coord=%d ORDER BY id_parent, id", id ) );
       sqlite3_stmt *stmt2=NULL;
       const char *dummy2=NULL;
       int res2 = sqlite3_prepare_v2( hdb, Select2.c_str(), Select2.length(), &stmt2, &dummy2 );
       if( res2==SQLITE_OK )
        {
         while( sqlite3_step( stmt2 ) == SQLITE_ROW )
          {
           const int id_state = sqlite3_column_int(stmt2,0);
           const int id_parent = sqlite3_column_int(stmt2,1);
           UCString state_name = lem::sqlite_column_ucstring(stmt2,2);
           const int weight = sqlite3_column_int(stmt2,3);

           if( id_state==id_parent )
            {
             GramCoordState s(state_name,weight);

             // это главное состояние в группе 
             if( coord.GetTotalStates()!=id_state )
              {
               MemFormatter mem;
               mem.printf( "Corrupted description of coordinate id=%d: non uniformly increasing of state ids", id );
               throw E_BaseException( mem.string() );
              }

             coord.Add(s);
            }
           else
            {
             // надо найти в описании координаты родительскую группу состояний
             const int igroup = coord.GetSubgroup(id_parent); 
             GramCoordState &parent = coord.GetTopState(igroup);
             parent.Add(state_name);
            }
          }

         sqlite3_finalize(stmt2);
        }
       else 
        {
         RaiseError( __FILE__, __LINE__ );
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
   RaiseError( __FILE__, __LINE__ );
   return false;
  }
}


LS_ResultSet* LexiconStorage_SQLITE::ListCoords(void)
{
 return ListByQuery("SELECT id FROM sg_coord ORDER BY id");
}


int LexiconStorage_SQLITE::FindCoord( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 MemFormatter ms;
 ms.printf( "SELECT id FROM sg_coord WHERE name='%us'", to_upper(name).c_str() );
 FString Select=lem::to_utf8(ms.string());
 return SelectInt(Select);
}


int LexiconStorage_SQLITE::AddCoord( const lem::UCString &coord )
{
 lem::UFString s( to_upper(coord).c_str() );
 sqlite_escape(s);

 lem::MemFormatter ms;
 if( coord.eqi(L"net") )
  ms.printf( "INSERT INTO sg_coord( id, name ) VALUES ( 0, '%us' )", s.c_str() );
 else
  ms.printf( "INSERT INTO sg_coord( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


int LexiconStorage_SQLITE::AddCoord( Solarix::GramCoord &coord )
{
 UFString s( to_upper(coord.GetName().front()).c_str() );
 sqlite_escape(s);

 int bistable = coord.IsBistable() ? 1 : 0; 
 
 lem::MemFormatter ms;
 if( coord.GetName().front().eqi(L"net") )
  ms.printf( "INSERT INTO sg_coord( id, name, bistable ) VALUES ( 0, '%us', %d )", s.c_str(), bistable );
 else
  ms.printf( "INSERT INTO sg_coord( name, bistable ) VALUES ( '%us', %d )", s.c_str(), bistable );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 const int id = (int)sqlite3_last_insert_rowid(hdb);
 StoreCoordStates(id,coord);

 if( coord.updator.IsNull() )
  coord.updator = new GramCoordUpdator_DB(this);

 coord.id = id;

 return id;
}


void LexiconStorage_SQLITE::StoreCoord( int id, Solarix::GramCoord &coord )
{
 lem::UFString s( lem::to_upper(coord.GetName().front()).c_str() );
 sqlite_escape(s);

 int bistable = coord.IsBistable() ? 1 : 0; 
 
 lem::MemFormatter ms;
 ms.printf( "UPDATE sg_coord SET name='%us', bistable=%d WHERE id=%d", s.c_str(), bistable, id );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 lem::FString del( lem::format_str( "DELETE FROM sg_state WHERE id_coord=%d", id ) );
 Execute(del);

 StoreCoordStates(id,coord);

 if( coord.updator.IsNull() )
  coord.updator = new GramCoordUpdator_DB(this);

 return;
}




void LexiconStorage_SQLITE::StoreCoordStates( int id_coord, const Solarix::GramCoord &coord )
{
 lem::MemFormatter ms;
 const int n=coord.GetTotalStates();
 for( int i=0; i<n; ++i )
  {
   lem::UFString s(coord.GetStateName(i).c_str());
   sqlite_escape(s);

   const int id_state = i;

   const int igroup = coord.GetSubgroup(id_state);
   lem::IntCollect ix = coord.GetSubgroupIndeces(igroup);
   const int id_parent = ix.front();

   const int weight = coord.GetTopState(igroup).GetWeight();
   
   ms.printf( "INSERT INTO sg_state( id, name, id_coord, id_parent, weight ) VALUES ( %d, '%us', %d, %d, %d )"
    , id_state, s.c_str(), id_coord, id_parent, weight );

   lem::FString as(lem::to_utf8(ms.string()));
   Execute(as);
  }

 return;
}


void LexiconStorage_SQLITE::CreateTables_Languages(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"sg_language") )
  { 
   const char create_ddl1[] = "CREATE TABLE sg_language( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " name varchar(32) NOT NULL UNIQUE"
                              ")";

   const char create_ddl2[] = "CREATE TABLE lang_alphabet( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " ordering integer not null,"
                              " id_language integer not null,"
                              " id_alphabet integer not null"
                              ")";

   const char create_ddl3[] = "CREATE TABLE lang_link( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_language integer not null,"
                              " id_state integer not null,"
                              " id_language2 integer not null"
                              ")";

   const char create_ddl4[] = "CREATE TABLE lang_param( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_language integer not null,"
                              " param_name varchar(32) not null,"
                              " param_value varchar(200) not null,"
                              " ordering integer not null"
                              ")";

   const char create_ddl5[] = "CREATE TABLE lang_usage( "
                              " id_language integer not null,"
                              " is_input integer not null,"
                              " is_output integer not null,"
                              " is_default integer not null"
                              ")";

   for( int i=0; i<5; ++i )
    {
     const char *sql;
     switch(i)
     {
      case 0: sql=create_ddl1; break;
      case 1: sql=create_ddl2; break;
      case 2: sql=create_ddl3; break;
      case 3: sql=create_ddl4; break;
      case 4: sql=create_ddl5; break;
     }

     Execute(sql);
    }
  }

 return;
}


int LexiconStorage_SQLITE::CountLanguages(void)
{
 return lem::sqlite_select_int( hdb, "SELECT count(*) FROM sg_language" );
}


LS_ResultSet* LexiconStorage_SQLITE::ListLanguages(void)
{
 return ListByQuery("SELECT id FROM sg_language WHERE id!=-1 ORDER BY id");
}

int LexiconStorage_SQLITE::FindLanguage( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 MemFormatter ms;
 ms.printf( "SELECT id FROM sg_language WHERE name='%us'", to_upper(name).c_str() );
 FString Select=lem::to_utf8(ms.string());

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
   RaiseError(__FILE__,__LINE__);
   return -1;
  }
}


int LexiconStorage_SQLITE::AddLanguage( SG_Language &lang )
{
 UFString s( lem::to_upper(lang.GetName()).c_str() );
 sqlite_escape(s);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_language( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 const int id = (int)sqlite3_last_insert_rowid(hdb);
 lang.id = id;
 StoreLanguageInternals(lang);

 return id;
}


bool LexiconStorage_SQLITE::GetLanguage( int id, SG_Language &lang )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );
 lem::FString Select( lem::format_str("SELECT name FROM sg_language WHERE id=%d", id) );

 bool ok=false;
 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lang.id = id;
     lang.name = lem::sqlite_column_ucstring(stmt,0);

     // запрос составлен так, чтобы сначала был извлечен основной алфавит
     lem::FString Select2( lem::format_str("SELECT id_alphabet FROM lang_alphabet WHERE id_language=%d ORDER BY ordering", id ) );
     sqlite3_stmt *stmt2=NULL;
     const char *dummy2=NULL;
     int res2 = sqlite3_prepare_v2( hdb, Select2.c_str(), Select2.length(), &stmt2, &dummy2 );
     lang.alphabet.clear();
     if( res2==SQLITE_OK )
      {
       while( sqlite3_step( stmt2 ) == SQLITE_ROW )
        {
         const int id_alphabet = sqlite3_column_int(stmt2,0);
         lang.alphabet.push_back(id_alphabet);
        }

       sqlite3_finalize(stmt2);
      }
     else 
      {
       RaiseError(__FILE__,__LINE__);
      }

     lem::FString Select3( lem::format_str("SELECT id_state, id_language2 FROM lang_link WHERE id_language=%d", id ) );
     sqlite3_stmt *stmt3=NULL;
     const char *dummy3=NULL;
     int res3 = sqlite3_prepare_v2( hdb, Select3.c_str(), Select3.length(), &stmt3, &dummy3 );
     lang.lang_links.clear();
     if( res3==SQLITE_OK )
      {
       while( sqlite3_step( stmt3 ) == SQLITE_ROW )
        {
         const int id_state = sqlite3_column_int(stmt3,0);
         const int id_lang2 = sqlite3_column_int(stmt3,1);
         lang.lang_links.push_back( std::make_pair( Tree_Link(id_state), id_lang2 ) );
        }

       sqlite3_finalize(stmt3);
      }
     else 
      {
       RaiseError(__FILE__,__LINE__);
      }


     lem::FString Select4( lem::format_str("SELECT param_name, param_value, id, ordering"
                                           " FROM lang_param WHERE id_language=%d"
                                           " ORDER BY param_name, id, ordering", id ) );
     sqlite3_stmt *stmt4=NULL;
     const char *dummy4=NULL;
     int res4 = sqlite3_prepare_v2( hdb, Select4.c_str(), Select4.length(), &stmt4, &dummy4 );
     lang.params.clear();
     if( res4==SQLITE_OK )
      {
       while( sqlite3_step( stmt4 ) == SQLITE_ROW )
        {
         UCString pname = lem::sqlite_column_ucstring(stmt4,0);
         UFString pval = lem::sqlite_column_ufstring(stmt4,1);
         int ord = sqlite3_column_int(stmt4,3);
        
         pval.subst_all( L"\\r", L"\r" );
         pval.subst_all( L"\\n", L"\n" );
         pval.subst_all( L"\\t", L"\t" );
         
         if( ord==0 )
          {
           SG_LanguageParam *p = new SG_LanguageParam();
           p->name = pname;
           p->values.push_back( pval );
           lang.params.push_back(p);
          }
         else
          {
           int iparam = lang.FindLastParam(pname);
           if( iparam==UNKNOWN )
            {
             LEM_STOPIT;
            }
           else
            {
             lang.params[iparam]->values.push_back(pval);
            }
          }  
        }

       sqlite3_finalize(stmt4);
      }
     else 
      {
       RaiseError(__FILE__,__LINE__);
      }

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


void LexiconStorage_SQLITE::StoreLanguage( const SG_Language &lang )
{
 UFString s( lem::to_upper(lang.GetName()).c_str() );
 sqlite_escape(s);

 lem::MemFormatter ms;
 ms.printf( "UPDATE sg_language SET name='%us' WHERE id=%d", s.c_str(), lang.id );
 lem::FString as(lem::to_utf8(ms.string()));
 Execute(as);

 StoreLanguageInternals(lang);
 return;
}


void LexiconStorage_SQLITE::StoreLanguageInternals( const SG_Language &lang )
{
 lem::MemFormatter ms;

 const int id = lang.id;

 for( lem::Container::size_type i=0; i<lang.alphabet.size(); ++i )
  {
   const int id_alphabet = lang.alphabet[i];
   
   // при вставке списка алфавитов сохраняем порядок, в котором они были заявлены в описании языка.
   // это позволит точно знать основной алфавит.
   ms.printf( "INSERT INTO lang_alphabet( id_language, id_alphabet, ordering ) VALUES ( %d, %d, %d )" 
    , id, id_alphabet, CastSizeToInt(i) );

   lem::FString as(lem::to_utf8(ms.string()));
   Execute(as);
  } 

 for( lem::Container::size_type i=0; i<lang.lang_links.size(); ++i )
  {
   const int id_state = lang.lang_links[i].first.GetState();
   const int id_lang2 = lang.lang_links[i].second;
   
   ms.printf( "INSERT INTO lang_link( id_language, id_state, id_language2 )"
              " VALUES ( %d, %d, %d )", id, id_state, id_lang2 );

   lem::FString as(lem::to_utf8(ms.string()));
   Execute(as);
  }
 
 for( lem::Container::size_type i=0; i<lang.params.size(); ++i )
  {
   const SG_LanguageParam &p = *lang.params[i];
   lem::UFString pname(p.name.c_str());
   sqlite_escape(pname);

   for( lem::Container::size_type j=0; j<p.values.size(); ++j )
    {
     lem::UFString pval(p.values[j].c_str());
     sqlite_escape(pval);
     pval.subst_all( L"\r", L"\\r" );
     pval.subst_all( L"\n", L"\\n" );
     pval.subst_all( L"\t", L"\\t" );
   
     ms.printf( "INSERT INTO lang_param( id_language, param_name, param_value, ordering )"
                " VALUES ( %d, '%us', '%us', %d )", id, pname.c_str(), pval.c_str(), CastSizeToInt(j) );

     lem::FString as(lem::to_utf8(ms.string()));
     Execute(as);
    }
  } 

 return;
}




int LexiconStorage_SQLITE::FindCriterion( const lem::UCString & name )
{
 lem::UCString uname( lem::to_upper(name) );
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM sg_criterion WHERE name='%us'", uname.c_str() );
 return lem::sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}


int LexiconStorage_SQLITE::StoreCriterion( const Criterion &x )
{
 lem::UFString name_str( lem::to_upper(x.GetName()).c_str());
 sqlite_escape(name_str);

 lem::UFString str_str( x.GetString() );
 sqlite_escape(str_str);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_criterion( name, strval )"
  " VALUES ( '%us', '%us' )", name_str.c_str(), str_str.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 Execute(s);

 const int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


Criterion* LexiconStorage_SQLITE::GetCriterion( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name, strval FROM sg_criterion WHERE id=%d", id );

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
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return NULL;
  }
}


LS_ResultSet* LexiconStorage_SQLITE::EnumerateCriteria(void)
{
 return ListByQuery("SELECT id FROM sg_criterion ORDER BY id");
}

void LexiconStorage_SQLITE::CreateTables_Criteria(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"abc_alphabet") )
  { 
   const char create_ddl[] = "CREATE TABLE sg_criterion( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(32) NOT NULL UNIQUE,"
                             " strval varchar(100) NOT NULL"
                             ")";

   Execute(create_ddl);
  }

 return;
}


LS_ResultSet* LexiconStorage_SQLITE::ListCropRules( int id_language )
{
 lem::FString Select;

 if( id_language==ANY_STATE )
  // enumerate ALL rules for all languages
  Select = "SELECT id FROM crop_rule ORDER BY Length(r_condition)";
 else
  // enumerate rules for a given language
  Select = lem::format_str("SELECT id FROM crop_rule WHERE id_language=%d ORDER BY Length(r_condition)", id_language );

 return ListByQuery(Select);
}



void LexiconStorage_SQLITE::StorePreprocessorCropRule( LA_CropRule *rule )
{
 lem::UFString condition(rule->GetCondition());
 sqlite_escape(condition);

 lem::UFString result(rule->GetResult());
 sqlite_escape(result);

 lem::MemFormatter q;
 q.printf( "INSERT INTO crop_rule( name, id_language, is_prefix, is_affix,"
           " r_condition, r_result, is_regex, case_sensitive, id_src, rel ) VALUES ( '%us', %d, %d, %d, '%us', '%us', %d, %d, %d, %d )",
           lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
           rule->IsPrefix() ? 1 : 0, rule->IsAffix() ? 1 : 0,
           condition.c_str(), result.c_str(), rule->IsRegex(), rule->IsCaseSensitive(), rule->GetSourceLocation(), rule->GetRel().GetInt() );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 rule->SetId(id);
 return;
}


LA_CropRule* LexiconStorage_SQLITE::GetPreprocessorCropRule( int id )
{
 lem::FString Select(lem::format_str( "SELECT name, id_language, is_prefix, is_affix, "
  "r_condition, r_result, is_regex, case_sensitive, id_src, rel FROM crop_rule WHERE id=%d", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UCString name = lem::sqlite_column_ucstring(stmt,0);
     const int id_language = sqlite3_column_int(stmt,1);
     const bool is_prefix = sqlite3_column_int(stmt,2)==1;
     const bool is_affix = sqlite3_column_int(stmt,3)==1;
     lem::UFString condition = lem::sqlite_column_ufstring(stmt,4);
     lem::UFString result = lem::sqlite_column_ufstring(stmt,5);
     const bool is_regex = sqlite3_column_int(stmt,6)==1;
     const bool case_sensitive = sqlite3_column_int(stmt,7)==1;
     const int id_src = sqlite3_column_int(stmt,8);
     const int rel = sqlite3_column_int(stmt,9);

     sqlite3_finalize(stmt);

     return new LA_CropRule( id, name, id_language, is_prefix, is_affix, is_regex, case_sensitive,
                             condition, result, id_src, lem::Real1(rel) );
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




void LexiconStorage_SQLITE::DeletePreprocessorRules()
{
 const char* tables[]= { "crop_rule", NULL };

 MemFormatter ms;

 int i=0;
 while( tables[i]!=NULL )
  {
   ms.printf( "DELETE FROM %s", tables[i] );

   lem::FString s(lem::to_utf8(ms.string()));
   Execute(s);
   i++;
  }

 return;
}



int LexiconStorage_SQLITE::FindCropRule( const lem::UCString &rule_name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM crop_rule WHERE name='%us'", to_upper(rule_name).c_str() );
 return sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}



LS_ResultSet* LexiconStorage_SQLITE::ListRecognitionRules( int id_language, bool including_word_matchers )
{
 lem::FString Select;

 if( id_language==ANY_STATE )
  {
   // enumerate ALL rules for all languages
   Select = "SELECT id FROM recog_rule";

   if( !including_word_matchers )
    Select += " WHERE word is NULL";
  }
 else
  {
   // enumerate rules for a given language
   Select = lem::format_str("SELECT id FROM recog_rule WHERE id_language=%d",id_language); 

   if( !including_word_matchers )
    Select += " AND word is NULL";
  }

 Select += " ORDER BY id";

 return ListByQuery(Select);
}



LS_ResultSet* LexiconStorage_SQLITE::ListRecognitionRulesForWord( int id_language, const lem::UCString & word )
{
 lem::UFString str_word(word.c_str());
 sqlite_escape( str_word );

 lem::MemFormatter mem;

 if( id_language==ANY_STATE )
  mem.printf( "SELECT id FROM recog_rule WHERE word='%us'", str_word.c_str() );
 else
  mem.printf( "SELECT id FROM recog_rule WHERE word='%us' AND id_language=%d", str_word.c_str(), id_language );

 return ListByQuery( mem.string() );
}



LA_RecognitionRule* LexiconStorage_SQLITE::GetRecognitionRule( int id )
{
 lem::FString Select(lem::format_str( "SELECT name, id_language, is_regex, is_prefix, is_affix, "
  "r_condition, id_entry, rel, coords, is_syllab, id_src, case_sensitive FROM recog_rule WHERE id=%d", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UCString name = lem::sqlite_column_ucstring(stmt,0);
     const int id_language = sqlite3_column_int(stmt,1);
     const bool is_regex = sqlite3_column_int(stmt,2)==1;
     const bool is_prefix = sqlite3_column_int(stmt,3)==1;
     const bool is_affix = sqlite3_column_int(stmt,4)==1;
     lem::UFString condition = lem::sqlite_column_ufstring(stmt,5);
     const int ekey = sqlite3_column_int(stmt,6);
     const lem::Real1 rel = lem::Real1(sqlite3_column_int(stmt,7));
     lem::UFString str_coords = lem::sqlite_column_ufstring(stmt,8);
     const bool is_syllab = sqlite3_column_int(stmt,9)==1;
     const int id_src = sqlite3_column_int(stmt,10);
     const bool case_sensitive = sqlite3_column_int(stmt,11)==1;

     Solarix::CP_Array coords;
     coords.Parse(str_coords);

     sqlite3_finalize(stmt);

     return new LA_RecognitionRule( id, name, case_sensitive, id_language, is_syllab, is_regex, is_prefix, is_affix,
        condition, ekey, rel, coords, id_src );
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


void LexiconStorage_SQLITE::StoreRecognitionRule( LA_RecognitionRule *rule )
{
 lem::UFString condition(rule->GetCondition());
 sqlite_escape(condition);

 lem::UFString coords;
 coords.reserve(64);
 for( lem::Container::size_type i=0; i<rule->GetCoords().size(); ++i )
  {
   if( i>0 )
    coords.Add_Dirty(L' ');

   coords.Add_Dirty( to_ustr( rule->GetCoords()[i].GetCoord().GetIndex() ).c_str() );
   coords.Add_Dirty( L':' );
   coords.Add_Dirty( to_ustr( rule->GetCoords()[i].GetState() ).c_str() );
  }

 lem::UFString word;
 if( rule->IsWordMatcher() )
  {
   word = rule->GetCondition();
   sqlite_escape( word );
   word.dress( L'\'' );
  }
 else
  {
   word = L"NULL";
  }
 

 lem::MemFormatter q;
 q.printf( "INSERT INTO RECOG_RULE( name, id_language, is_syllab, is_regex, is_prefix, is_affix,"
           " r_condition, id_entry, rel, coords, id_src,"
           " word, case_sensitive ) VALUES ( '%us', %d, %d, %d, %d, %d, '%us', %d, %d, '%us', %d, %us, %d )",
           lem::to_upper(rule->GetName()).c_str(),
           rule->GetLanguage(),
           rule->IsSyllab() ? 1 : 0,
           rule->IsRegex() ? 1 : 0,
           rule->IsPrefix() ? 1 : 0,
           rule->IsAffix() ? 1 : 0,
           condition.c_str(),
           rule->GetEntryKey(),
           rule->GetRel().GetInt(),
           coords.c_str(),
           rule->GetSourceLocation(),
           word.c_str(),
           rule->IsCaseSensitive() ? 1 : 0
         );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 rule->SetId(id);

 return;
}


int LexiconStorage_SQLITE::FindRecognitionRule( const lem::UCString &rule_name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM recog_rule WHERE name='%us'", to_upper(rule_name).c_str() );
 return sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}


void LexiconStorage_SQLITE::DeleteRecognitionRules(void)
{
 Execute("DELETE FROM recog_rule");
 return;
}





LS_ResultSet* LexiconStorage_SQLITE::ListPhoneticRules( int id_language )
{
 lem::FString Select;

 if( id_language==ANY_STATE )
  Select = "SELECT id FROM ph_rule ORDER BY id";
 else
  Select = lem::format_str("SELECT id FROM ph_rule WHERE id_language=%d ORDER BY id",id_language); 

 return ListByQuery(Select);
}


LA_PhoneticRule* LexiconStorage_SQLITE::GetPhoneticRule( int id )
{
 lem::FString Select(lem::format_str( "SELECT name, id_language, is_prefix, is_affix, "
  "r_condition, r_result, rel, id_src FROM ph_rule WHERE id=%d", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UCString name = lem::sqlite_column_ucstring(stmt,0);
     const int id_language = sqlite3_column_int(stmt,1);
     const bool is_prefix = sqlite3_column_int(stmt,2)==1;
     const bool is_affix = sqlite3_column_int(stmt,3)==1;
     lem::UFString condition = lem::sqlite_column_ufstring(stmt,4);
     lem::UFString result = lem::sqlite_column_ufstring(stmt,5);
     const lem::Real1 rel = lem::Real1(sqlite3_column_int(stmt,6));
     const int id_src = sqlite3_column_int(stmt,7);

     sqlite3_finalize(stmt);

     return new LA_PhoneticRule( id, name, id_language, is_prefix, is_affix, condition.c_str(), result.c_str(), rel, id_src );
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


void LexiconStorage_SQLITE::StorePhoneticRule( LA_PhoneticRule *rule )
{
 lem::UFString condition(rule->GetCondition().GetContext().c_str());
 sqlite_escape(condition);

 lem::UFString result(rule->GetResult().GetContext().c_str());
 sqlite_escape(result);

 lem::MemFormatter q;
 q.printf( "INSERT INTO PH_RULE( name, id_language, is_prefix, is_affix,"
           " r_condition, r_result, rel, id_src ) VALUES ( '%us', %d, %d, %d, '%us', '%us', %d, %d )",
           lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
           rule->IsPrefix() ? 1 : 0, rule->IsAffix() ? 1 : 0,
           condition.c_str(), result.c_str(), rule->GetVal().GetInt(), rule->GetSourceLocation() );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 rule->SetId(id);

 return;
}



int LexiconStorage_SQLITE::FindPhoneticRule( const lem::UCString &rule_name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM ph_rule WHERE name='%us'", to_upper(rule_name).c_str() );
 return sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}


void LexiconStorage_SQLITE::DeletePhoneticRules(void)
{
 Execute("DELETE FROM ph_rule");
 return;
}



int LexiconStorage_SQLITE::FindWordEntrySet( const lem::UCString &set_name )
{
 if(
    set_name.front()==L'\'' ||
    set_name.front()==L'"' ||
    set_name.back()==L'\'' ||
    set_name.back()==L'"'
   )
  return UNKNOWN;

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM word_entry_set WHERE name='%us'", to_upper(set_name).c_str() );
 return sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}

void LexiconStorage_SQLITE::DeleteWordEntrySets(void)
{
 Execute("DELETE FROM word_entry_set");
 return;
}


WordEntrySetItem* LexiconStorage_SQLITE::GetWordEntrySet( int id )
{
 lem::FString Select(lem::format_str( "SELECT ies, name FROM word_entry_set WHERE id=%d", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     WordEntrySetItem *res = new WordEntrySetItem();
     res->id = id;

     res->name = lem::sqlite_column_ucstring(stmt,1);
     lem::UFString s = lem::sqlite_column_ufstring(stmt,0);

     lem::MCollect<lem::UCString> toks;
     lem::parse( s, toks, false );
     for( lem::Container::size_type i=0; i<toks.size(); ++i )
      {
       const int id_entry = lem::to_int(toks[i]);
       res->ies.insert(id_entry);   
      }

     sqlite3_finalize(stmt);
     return res;
    }
   else
    {
     lem::MemFormatter mem;
     mem.printf( "Co not find word entry set with id=%d", id );
     throw lem::E_BaseException(mem.string());
    } 
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return NULL;
  }
}



void LexiconStorage_SQLITE::StoreWordEntrySet( WordEntrySetItem &wes )
{
 lem::UFString s;
 for( std::set<int>::const_iterator it=wes.ies.begin(); it!=wes.ies.end(); ++it )
  {
   if( !s.empty() )
    s.Add_Dirty(L' ');

   s.Add_Dirty( lem::to_ustr(*it).c_str() );
  } 

 lem::MemFormatter q;
 q.printf( "INSERT INTO word_entry_set( name, ies ) VALUES ( '%us', '%us' )",
           lem::to_upper(wes.name).c_str(), s.c_str() );
 
 lem::FString sql(lem::to_utf8(q.string()));
 Execute(sql);

 wes.id = (int)sqlite3_last_insert_rowid(hdb);
 return;
}


LS_ResultSet* LexiconStorage_SQLITE::ListWordEntrySet(void)
{
 return ListByQuery("SELECT id FROM word_entry_set ORDER BY id");
}



LS_ResultSet* LexiconStorage_SQLITE::ListUnbreakableRules( int id_language )
{
 lem::FString Select;

 if( id_language==ANY_STATE )
  Select = "SELECT id FROM unbreakable ORDER BY id";
 else
  Select = lem::format_str("SELECT id FROM unbreakable WHERE id_language=%d ORDER BY id",id_language); 

 return ListByQuery(Select);
}


LA_UnbreakableRule* LexiconStorage_SQLITE::GetUnbreakableRule( int id )
{
 lem::FString Select(lem::format_str( "SELECT name, id_language, is_regex, pattern, id_src "
  " FROM unbreakable WHERE id=%d", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UCString name = lem::sqlite_column_ucstring(stmt,0);
     const int id_language = sqlite3_column_int(stmt,1);
     const bool is_regex = sqlite3_column_int(stmt,2)==1;
     lem::UFString pattern = lem::sqlite_column_ufstring(stmt,3);
     const int id_src = sqlite3_column_int(stmt,4);

     sqlite3_finalize(stmt);

     return new LA_UnbreakableRule( id, name, id_language, is_regex, pattern.c_str(), id_src );
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


void LexiconStorage_SQLITE::StoreUnbreakableRule( LA_UnbreakableRule *rule )
{
 lem::UFString pattern(rule->GetPattern());
 sqlite_escape(pattern);

 lem::MemFormatter q;
 q.printf( "INSERT INTO unbreakable( name, id_language, is_regex,"
           " pattern, id_src ) VALUES ( '%us', %d, %d, '%us', %d )",
           lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
           rule->IsRegex() ? 1 : 0,
           pattern.c_str(), rule->GetSourceLocation() );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);

 int id = (int)sqlite3_last_insert_rowid(hdb);
 rule->SetId(id);

 return;
}

void LexiconStorage_SQLITE::DeleteUnbreakableRules(void)
{
 Execute("DELETE FROM unbreakable");
 return;
}

int LexiconStorage_SQLITE::FindUnbreakableRule( const lem::UCString &rule_name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM unbreakable WHERE name='%us'", to_upper(rule_name).c_str() );
 return sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}


LS_ResultSet* LexiconStorage_SQLITE::ListLanguageUsage(void)
{
 return ListByQuery("SELECT id_language, is_input, is_output, is_default FROM lang_usage ORDER BY id_language" ); 
}


void LexiconStorage_SQLITE::StoreLanguageUsage( int id_language, bool is_input, bool is_output, bool is_default )
{
 LEM_CHECKIT_Z( !lem::is_quantor(id_language) );

 lem::MemFormatter q;

 // Сначала удалим упоминания этого языка для входного или выходного набора, чтобы не получилось дублирования
 q.printf( "DELETE FROM lang_usage WHERE id_language=%d AND is_input=%d AND is_output=%d",
   id_language, is_input ? 1 : 0, is_output ? 1 : 0 );

 Execute( lem::to_utf8(q.string()) );
 

 q.printf( "INSERT INTO lang_usage( id_language, is_input, is_output, is_default )"
           " VALUES ( %d, %d, %d, %d )", id_language, is_input ? 1 : 0, is_output ? 1 : 0, is_default ? 1 : 0 );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);

 return;
}




void LexiconStorage_SQLITE::CreateTables_Filters(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"SynPatternTree") )
  { 
   const char ddl2[] = "CREATE TABLE SynPatternTree( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_tree integer NOT NULL,"
                       " id_language integer NOT NULL,"
                       " id0 integer not null,"
                       " name varchar(32) NOT NULL,"
                       " uname varchar(32) NOT NULL,"
                       " segment_no integer NOT NULL,"
                       " pattern_type integer NOT NULL,"
                       " bin BLOB NOT NULL"
                       ")";

   Execute(ddl2);

   Execute( "CREATE INDEX SynPatternTree_idx1 ON SynPatternTree(id_tree)" );

   const char ddl11[] = "CREATE TABLE kb_facts( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_language integer NOT NULL,"
                       " name varchar(100) NOT NULL,"
                       " n_arg integer NOT NULL,"
                       " n_ret integer NOT NULL,"
                       " ret_type integer NOT NULL,"
                       " query_mode integer NOT NULL,"
                       " violation_score integer NOT NULL,"
                       " violation_handler integer NOT NULL"
                       ")";

   Execute(ddl11);


   const char ddl12[] = "CREATE TABLE kb_fact("
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_group integer NOT NULL,"
                       " boolean_return integer,"
                       " false_score integer,"
                       " integer_return integer"
                       ")";
   Execute(ddl12);
   Execute("CREATE INDEX kb_fact_idx1 ON kb_fact(id_group)");

   const char ddl13[] = "CREATE TABLE kb_fact_index1("
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_group integer NOT NULL,"
                       " id_fact integer NOT NULL,"
                       " word1 varchar(32),"
                       " word2 varchar(32),"
                       " word3 varchar(32),"
                       " word4 varchar(32),"
                       " word5 varchar(32)"
                       ")";
   Execute(ddl13);

   const char ddl14[] = "CREATE TABLE kb_fact_index2("
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_group integer NOT NULL,"
                       " id_fact integer NOT NULL,"
                       " id_entry1 integer,"
                       " id_entry2 integer,"
                       " id_entry3 integer,"
                       " id_entry4 integer,"
                       " id_entry5 integer"
                       ")";
   Execute(ddl14);

   Execute("CREATE INDEX kb_fact_index_idx1 ON kb_fact_index1(id_group,word1,word2)");
   Execute("CREATE INDEX kb_fact_index_idx2 ON kb_fact_index1(id_group,word1,word2,word3)");
   Execute("CREATE INDEX kb_fact_index_idx3 ON kb_fact_index2(id_group,id_entry1,id_entry2)");
   Execute("CREATE INDEX kb_fact_index_idx4 ON kb_fact_index2(id_group,id_entry1,id_entry2,id_entry3)");

   const char ddl15[] = "CREATE TABLE kb_argument_point( "
                        " id integer PRIMARY KEY NOT NULL,"
                        " id_fact integer,"
                        " argument_index integer NOT NULL,"
                        " word_text varchar(100),"
                        " is_regex integer NOT NULL,"
                        " case_sensitive integer NOT NULL,"
                        " id_entry integer NOT NULL,"
                        " id_metaentry integer NOT NULL,"
                        " id_class integer NOT NULL,"
                        " wordentryset_name varchar(100),"
                        " wordset_name varchar(100),"
                      
                        " n_coords integer,"
                      
                        " id_coord1 integer,"
                        " id_state1 integer,"
                        " affirm1 integer,"
                        " id_coord2 integer,"
                        " id_state2 integer,"
                        " affirm2 integer,"
                      
                        " id_coord3 integer,"
                        " id_state3 integer,"
                        " affirm3 integer,"
                      
                        " id_coord4 integer,"
                        " id_state4 integer,"
                        " affirm4 integer,"
                      
                        " thesauruscheck_link integer,"
                        " thesauruscheck_entry integer,"
                        " is_positive integer NOT NULL"
                        ")";
   Execute(ddl15);

   const char ddl16[] = "CREATE INDEX kb_argument_point_idx1 ON kb_argument_point(id_fact)";
   Execute(ddl16);


/*
   const char ddl17[] = "CREATE TABLE left_filter_selector( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_language integer NOT NULL,"
                       " word_text varchar(100),"
                       " id_entry integer,"
                       " context_length integer NOT NULL,"
                       " id_body integer NOT NULL"
                       ")";
   Execute(ddl17);

   const char ddl18[] = "CREATE INDEX left_filter_selector_idx1 ON left_filter_selector(word_text,id_language)";
   Execute(ddl18);

   const char ddl19[] = "CREATE INDEX left_filter_selector_idx2 ON left_filter_selector(id_entry,id_language)";
   Execute(ddl19);
*/
   // -------------------------

   const char ddl20[] = "CREATE TABLE ts_head_word( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " word varchar(100) NOT NULL,"
                       " id_head_point integer NOT NULL,"
                       " score_type integer NOT NULL,"
                       " score_expr varchar(100),"
                       " root_node integer NOT NULL,"
                       " id_group integer NOT NULL"
                       ")";
   Execute(ddl20);

   const char ddl20_1[] = "CREATE INDEX ts_head_word_idx1 ON ts_head_word(word,id_group)";
   Execute(ddl20_1);

   const char ddl21[] = "CREATE TABLE ts_head_lemma( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_entry integer NOT NULL,"
                       " id_head_point integer NOT NULL,"
                       " score_type integer NOT NULL,"
                       " score_expr varchar(100),"
                       " root_node integer NOT NULL,"
                       " id_group integer NOT NULL"
                       ")";

   Execute(ddl21);

   const char ddl21_1[] = "CREATE INDEX ts_head_lemma_idx1 ON ts_head_lemma(id_entry,id_group)";
   Execute(ddl21_1);

   const char ddl22[] = "CREATE TABLE ts_point( "
                        " id integer PRIMARY KEY NOT NULL,"
                        " id_parent integer,"
                        " id_group integer,"
                        " word_text varchar(100),"
                        " id_entry integer NOT NULL,"
                        " id_metaentry integer NOT NULL,"
                        " id_class integer NOT NULL,"
                        " wordentryset_name varchar(100),"
                        " wordset_name varchar(100),"
                        " wordformset_name varchar(100),"
                      
                        " n_coords integer,"
                      
                        " id_coord1 integer,"
                        " id_state1 integer,"
                        " affirm1 integer,"
                        " id_coord2 integer,"
                        " id_state2 integer,"
                        " affirm2 integer,"
                      
                        " id_coord3 integer,"
                        " id_state3 integer,"
                        " affirm3 integer,"
                      
                        " id_coord4 integer,"
                        " id_state4 integer,"
                        " affirm4 integer,"
                      
                        " thesauruscheck_link integer,"
                        " thesauruscheck_entry integer,"
                        " is_positive integer NOT NULL,"

                        " children_quantification_min_count integer NOT NULL,"
                        " children_quantification_max_count integer NOT NULL,"

                        " n_setcheckers integer NOT NULL,"
                        " set_name1 varchar(50),"
                        " set_type1 integer NOT NULL,"
                        " set_affirm1 integer NOT NULL,"
                        " set_name2 varchar(50),"
                        " set_type2 integer NOT NULL,"
                        " set_affirm2 integer NOT NULL,"
                        " set_name3 varchar(50),"
                        " set_type3 integer NOT NULL,"
                        " set_affirm3 integer NOT NULL,"

                        " link_type integer NOT NULL,"
                        " relative_position integer NOT NULL,"
                        " quantification_min_count integer NOT NULL,"
                        " quantification_max_count integer NOT NULL,"
                        " marker varchar(30),"
                        " n_backref integer NOT NULL,"

                        " br_affirm_0 integer,\n"
                        " br_coord0_0 integer,\n"
                        " br_marker_0 varchar(30),\n"
                        " br_coord1_0 integer,\n"
                        " br_for_group_0 integer,\n"

                        " br_affirm_1 integer,\n"
                        " br_coord0_1 integer,\n"
                        " br_marker_1 varchar(30),\n"
                        " br_coord1_1 integer,\n"
                        " br_for_group_1 integer,\n"

                        " br_affirm_2 integer,\n"
                        " br_coord0_2 integer,\n"
                        " br_marker_2 varchar(30),\n"
                        " br_coord1_2 integer,\n"
                        " br_for_group_2 integer,\n"

                        " id_src integer"
                        ")";
   Execute(ddl22);

   Execute("CREATE INDEX ts_point_idx1 ON ts_point(id_parent)");

   const char ddl23[] = "CREATE TABLE generic_tree_scorer( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_head_point integer NOT NULL,"
                       " id_group integer NOT NULL,"
                       " score_expr varchar(100),"
                       " score_type integer NOT NULL"
                       ")";

   Execute(ddl23);

   const char ddl23_1[] = "CREATE INDEX generic_tree_scorer_idx1 ON generic_tree_scorer(id_group)";
   Execute(ddl23_1);


   const char ddl31[] = "CREATE TABLE ts_group( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " name varchar(30) NOT NULL,"
                       " allow_unmatched_children integer NOT NULL"
                       ")";

   Execute(ddl31);

   const char ddl41[] = "CREATE TABLE ts_group2root( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_group integer NOT NULL,"
                       " id_root integer NOT NULL"
                       ")";
   Execute(ddl41);
   Execute( "CREATE INDEX ts_group2root_idx1 ON ts_group2root(id_group)" );


   const char ddl42[] = "CREATE TABLE ts_predicate( "
                       " id integer PRIMARY KEY NOT NULL,"
                       " id_point integer NOT NULL,"
                       " func_name varchar(20) NOT NULL,"
                       " narg integer NOT NULL,"
                       " id_class1 integer NOT NULL"
                       ")";

   Execute(ddl42);
   Execute( "CREATE INDEX ts_predicate_idx1 ON ts_predicate(id_point)" );
  }

 return;
}



void LexiconStorage_SQLITE::DeleteMorphologicalFilters(void)
{
 Execute("DELETE FROM kb_argument_point");
 Execute("DELETE FROM kb_fact");
 Execute("DELETE FROM kb_facts");
 Execute("DELETE FROM kb_fact_index1");
 Execute("DELETE FROM kb_fact_index2");

 Execute("DELETE FROM ts_head_word");
 Execute("DELETE FROM ts_head_lemma");
 Execute("DELETE FROM ts_point");
 Execute("DELETE FROM ts_group");
 Execute("DELETE FROM ts_group2root");
 Execute("DELETE FROM generic_tree_scorer");
 Execute("DELETE FROM ts_predicate");


 Execute("DELETE FROM word_assoc");
 Execute("DELETE FROM predicate_template");

 return;
}







LS_ResultSet* LexiconStorage_SQLITE::ListSynPatternTrees(void)
{
 return ListByQuery("SELECT id_tree, name, uname, id_language, pattern_type FROM SynPatternTree WHERE id0=-1 ORDER BY id_tree" );
}


void LexiconStorage_SQLITE::DeleteSynPatternTrees(void)
{
 Execute("DELETE FROM SynPatternTree");
 return;
}


int LexiconStorage_SQLITE::FindSynPatternTree( int id_language, const lem::UCString &name, int pattern_type )
{
 lem::MemFormatter mem;

 if( id_language==ANY_STATE )
  mem.printf( "SELECT id_tree FROM SynPatternTree WHERE uname='%us' AND id0=-1 AND pattern_type=%d", lem::to_upper(name).c_str(), pattern_type );
 else
  mem.printf( "SELECT id_tree FROM SynPatternTree WHERE uname='%us' AND id_language=%d and id0=-1 AND pattern_type=%d", lem::to_upper(name).c_str(), id_language, pattern_type );

 return SelectInt( mem.string() );
}



void LexiconStorage_SQLITE::StoreSynPatternTree( int id_language, const lem::UCString &name, int id, const SynPatternTreeNode *tree, int pattern_type )
{
 #if defined SOL_SAVEBIN

 lem::MemStream mem(true);
 tree->SaveBin(mem);
 const int sz = mem.tellp();
 const char* bytes = mem.get_Block();
 
/*
 const int segment_size=10000;
 const int nsegment = (sz/segment_size) + ((sz%segment_size)>0 ? 1 : 0);
 
 lem::FString hex;
 lem::MemFormatter q;
 for( int isegment=0, bcount=0; isegment<nsegment; ++isegment, bcount+=segment_size )
  {
   const char *segment = bytes + bcount;
   const int seg_sz = std::min( segment_size, sz-bcount );

   hex.clear();
   Storage_Data2Hex( segment, seg_sz, hex );
 
   if( isegment==0 )
    q.printf( "INSERT INTO SynPatternTree( id_tree, id_language, id0, name, uname, segment_no, pattern_type, bin )"
              " VALUES ( %d, %d, %d, '%us', '%us', %d, %d, '%s' )", id, id_language, -1, name.c_str(), lem::to_upper(name).c_str(), isegment, pattern_type, hex.c_str() );
   else
    q.printf( "INSERT INTO SynPatternTree( id_tree, id_language, id0, name, uname, segment_no, pattern_type, bin )"
              " VALUES ( %d, %d, %d, '%us', '%us', %d, %d, '%s' )", id, id_language, id, name.c_str(), lem::to_upper(name).c_str(), isegment, pattern_type, hex.c_str() );

   lem::FString s(lem::to_utf8(q.string()));
   Execute(s);
  }
*/

 lem::MemFormatter q;
 q.printf( "INSERT INTO SynPatternTree( id_tree, id_language, id0, name, uname, segment_no, pattern_type, bin )"
              " VALUES ( %d, %d, %d, '%us', '%us', 0, %d, ?1 )", id, id_language, -1, name.c_str(), lem::to_upper(name).c_str(), pattern_type );

 lem::FString s(lem::to_utf8(q.string()));
 
 sqlite3_stmt * stmt1=NULL;
 int rc = sqlite3_prepare( hdb, s.c_str(), -1, &stmt1, NULL );
 rc = sqlite3_bind_blob( stmt1, 1, bytes, sz, SQLITE_STATIC ); 
 rc = sqlite3_step(stmt1);

 sqlite3_finalize(stmt1);

 #else
 LEM_STOPIT;
 #endif
 return;
}

lem::UCString LexiconStorage_SQLITE::GetSynPatternTreeName( int id )
{
 lem::FString Select(lem::format_str( "SELECT name FROM SynPatternTree WHERE id_tree=%d AND id0=-1", id ) );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(Select) );
 if( rs->Fetch() )
  return rs->GetUCString(0);
 else
  {
   lem::MemFormatter msg;
   msg.printf( "Can not file pattern tree id=%d", id );
   throw E_BaseException(msg.string());
  }
}



std::pair<SynPatternTreeNode*,lem::UCString> LexiconStorage_SQLITE::GetSynPatternTree( int id )
{
/*
 lem::FString Select(lem::format_str( "SELECT bin, name FROM SynPatternTree WHERE id_tree=%d AND id0=-1", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::FString hex = lem::sqlite_column_fstring(stmt,0);

     lem::UCString name = lem::sqlite_column_ucstring(stmt,1);
     const int pattern_type = sqlite3_column_int(stmt,2);
     sqlite3_finalize(stmt);

     Select = lem::format_str( "SELECT bin FROM SynPatternTree WHERE id0=%d ORDER BY segment_no", id );

     sqlite3_stmt *stmt2=NULL;
     const char *dummy2=NULL;
     res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt2, &dummy2 );
     if( res==SQLITE_OK )
      {
       while( sqlite3_step( stmt2 ) == SQLITE_ROW )
        {
         hex.Add_Dirty( lem::sqlite_column_fstring(stmt2,0) );
        }

       sqlite3_finalize(stmt2);
      }
     else
      {
       RaiseError(Select);
      }

     unsigned char *bytes=NULL;
     int size=0;
     Solarix::Storage_Hex2Data( hex, &bytes, &size );
     MemReadStream rdr( bytes, size );
     SynPatternTreeNode *rule = new SynPatternTreeNode();
     rule->LoadBin(rdr);
     delete[] bytes;
     return std::make_pair(rule,name);
    }
   else
    {
     lem::MemFormatter err;
     err.printf( "Can not fetch a record by query: %s", Select.c_str() );
     throw lem::E_BaseException( err.string() );
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
  }

 return std::make_pair( (SynPatternTreeNode*)NULL, lem::UCString() );
*/

 lem::FString Select(lem::format_str( "SELECT bin, name FROM SynPatternTree WHERE id_tree=%d AND id0=-1", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     const unsigned char * bytes = (const unsigned char*)sqlite3_column_blob(stmt,0);
     int size=sqlite3_column_bytes(stmt,0);

     lem::UCString name = lem::sqlite_column_ucstring(stmt,1);
     const int pattern_type = sqlite3_column_int(stmt,2);

     MemReadStream rdr( bytes, size );
     SynPatternTreeNode *rule = new SynPatternTreeNode();
     rule->LoadBin(rdr);

     sqlite3_finalize(stmt);

     return std::make_pair(rule,name);
    }
   else
    {
     lem::MemFormatter err;
     err.printf( "Can not fetch a record by query: %s", Select.c_str() );
     throw lem::E_BaseException( err.string() );
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
  }

 return std::make_pair( (SynPatternTreeNode*)NULL, lem::UCString() );
}



void LexiconStorage_SQLITE::DeleteFunctions( const wchar_t *Marker )
{
 lem::MemFormatter sql;
 sql.printf( "DELETE FROM tr_functions WHERE marker='%us'", Marker );
 Execute( lem::to_utf8(sql.string()) );
 return;
}

TrFunctions* LexiconStorage_SQLITE::GetFunctions( const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT bin FROM tr_functions WHERE marker='%us' ORDER BY segment_no", Marker );
 lem::FString Select( lem::to_utf8(mem.string() ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   lem::FString hex;
   while( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     hex.Add_Dirty( lem::sqlite_column_fstring(stmt,0) );
    }

   sqlite3_finalize(stmt);

   if( !hex.empty() )
    {
     unsigned char *bytes=NULL;
     int size=0;
     Solarix::Storage_Hex2Data( hex, &bytes, &size );
     MemReadStream rdr( bytes, size );
     TrFunctions *f = new TrFunctions();
     f->LoadBin(rdr);
     delete[] bytes;
     return f;
    }
   else
    {
     // Сохраненных функций пока нет
     return new TrFunctions();
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return NULL;
  }
}


void LexiconStorage_SQLITE::StoreFunctions( TrFunctions *functions, const wchar_t *Marker )
{
 #if defined SOL_SAVEBIN
 lem::MemStream mem(true);
 functions->SaveBin(mem);
 const int sz = mem.tellp();
 const char* bytes = mem.get_Block();

 const int segment_size=10000;
 const int nsegment = (sz/segment_size) + ((sz%segment_size)>0 ? 1 : 0);
 
 lem::FString hex;
 for( int isegment=0, bcount=0; isegment<nsegment; ++isegment, bcount+=segment_size )
  {
   const char *segment = bytes + bcount;
   const int seg_sz = std::min( segment_size, sz-bcount );

   hex.clear();
   Storage_Data2Hex( segment, seg_sz, hex );
 
   lem::MemFormatter q;
   q.printf( "INSERT INTO tr_functions( marker, segment_no, bin )"
             " VALUES ( '%us', %d, '%s' )", Marker, isegment, hex.c_str() );
 
   lem::FString s(lem::to_utf8(q.string()));
   Execute(s);
  }

 #else
 LEM_STOPIT;
 #endif
 
 return;
}



void LexiconStorage_SQLITE::DeleteSourceLocations(void)
{
 Execute("DELETE FROM src_filename");
 Execute("DELETE FROM src_location");
 return;
}

int LexiconStorage_SQLITE::RegisterSourceFilename( const lem::Path &filepath )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM src_filename WHERE filepath='%us'"
  , lem::to_upper(filepath.GetUnicode()).c_str() );

 int id = SelectInt( lem::to_utf8(mem.string()) );
 if( id==UNKNOWN )
  {
   mem.printf( "INSERT INTO src_filename( filepath, filepath0 ) VALUES ( '%us', '%us' )"
    , lem::to_upper(filepath.GetUnicode()).c_str(), filepath.GetUnicode().c_str() );
   Execute( lem::to_utf8(mem.string()) );
   id = (int)sqlite3_last_insert_rowid(hdb);
  }

 return id;
}


int LexiconStorage_SQLITE::RegisterSourceLocation( int id_filename, int iline, int icolumn )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO src_location( id_filename, line_no, column_no ) VALUES ( %d, %d, %d )", id_filename, iline, icolumn );
 Execute( lem::to_utf8(mem.string()) );
 const int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


bool LexiconStorage_SQLITE::GetSourceFilename( int id_filename, lem::Path &filepath )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT filepath0 FROM src_filename WHERE id=%d", id_filename );

 lem::FString Select( lem::to_utf8(mem.string()) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UFString s = lem::sqlite_column_ufstring(stmt,0);

     sqlite3_finalize(stmt);

     filepath = lem::Path(s);
     return true;
    }
   else
    {
     return false;
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return false;
  }
}


bool LexiconStorage_SQLITE::GetSourceLocation( int id_location, int &id_file, int &line, int &column )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id_filename, line_no, column_no FROM src_location WHERE id=%d", id_location );
 lem::FString Select( lem::to_utf8(mem.string()) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     id_file = sqlite3_column_int(stmt,0);
     line = sqlite3_column_int(stmt,1);
     column = sqlite3_column_int(stmt,2);
     sqlite3_finalize(stmt);
     return true;
    }
   else
    {
     return false;
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return false;
  }
}



int LexiconStorage_SQLITE::FindSourceLineBeginning( int id_filename, int line )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT Coalesce(MIN(column_no),-1) FROM src_location WHERE id_filename=%d AND line_no=%d", id_filename, line );
 int column_no = SelectInt( lem::to_utf8(mem.string()) );
 if( column_no!=-1 )
  {
   mem.printf( "SELECT id FROM src_location WHERE id_filename=%d AND line_no=%d AND column_no=%d", id_filename, line, column_no );
   int id = SelectInt( lem::to_utf8(mem.string()) );
   return id;
  }
 else
  {
   return UNKNOWN;
  }
}



int LexiconStorage_SQLITE::FindClosestSourceLocation( int id_filename, int line )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT Coalesce(MIN(ABS(line_no-%d)),-1) FROM src_location WHERE id_filename=%d", line, id_filename );
 int line_no = SelectInt( lem::to_utf8(mem.string()) );
 if( line_no!=-1 )
  {
   return FindSourceLineBeginning( id_filename, line_no );
  }
 else
  {
   return UNKNOWN;
  }
}


LS_ResultSet* LexiconStorage_SQLITE::ListSourceFilenames(void)
{
 return ListByQuery("SELECT id, filepath0 FROM src_filename ORDER BY id");
}


LS_ResultSet* LexiconStorage_SQLITE::ListSourceLocations(void)
{
 return ListByQuery("SELECT id, id_filename, line_no, column_no FROM src_location ORDER BY id");
}



void LexiconStorage_SQLITE::CreateTables_Paradigmas(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"paradigma") )
  { 
   const char create_ddl1[] = "CREATE TABLE paradigma( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " front_name varchar(32),"
                              " r_condition varchar(256),"
                              " id_class integer,"
                              " attrs VARCHAR(100)"
                              ")";

   const char create_ddl2[] = "CREATE UNIQUE INDEX paradigma_name_idx1 ON paradigma(front_name)";

   const char create_ddl3[] = "CREATE TABLE paradigma_name( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_paradigma integer not null,"
                              " name varchar(32),"
                              " uname varchar(32)"
                              ")";

   const char create_ddl4[] = "CREATE UNIQUE INDEX paradigma_name_idx2 ON paradigma_name(uname)";

   const char create_ddl5[] = "CREATE TABLE paradigma_form( "
                              " id integer PRIMARY KEY NOT NULL,"
                              " id_paradigma integer NOT NULL,"
                              " rx_condition VARCHAR(100),"
                              " flexer_flags VARCHAR(100),"
                              " lexem_generator varchar(100) NOT NULL,"
                              " dims varchar(256)"
                              ")";

   const char create_ddl6[] = "CREATE INDEX paradigma_form_idx1 ON paradigma_form(id_paradigma)";

   const int N=6;
   const char* create_ddl[N] = { create_ddl1, create_ddl2, create_ddl3, create_ddl4, create_ddl5, create_ddl6 };

   for( int i=0; i<N; ++i )
    {
     Execute(create_ddl[i]);
    }
  }

 return;
}


LS_ResultSet* LexiconStorage_SQLITE::ListParadigmaMatchers(void)
{
 return ListByQuery("SELECT id, r_condition, id_class FROM paradigma WHERE length(r_condition)>0 ORDER BY id");
}


LS_ResultSet* LexiconStorage_SQLITE::ListParadigmas(void)
{
 return ListByQuery("SELECT id FROM paradigma ORDER BY id");
}


int LexiconStorage_SQLITE::StoreParadigma( const SG_DeclensionTable &p )
{
 lem::UFString matcher = p.GetCondition().ToString();
 sqlite_escape(matcher);

 lem::UFString attrs;
 for( lem::Container::size_type i=0; i<p.attrs().size(); ++i )
  {
   if( i>0 )
    attrs.Add_Dirty( L' ' );

   attrs.Add_Dirty( lem::format_str( L"%d:%d", p.attrs()[i].GetCoord().GetIndex(), p.attrs()[i].GetState() ).c_str() );
  }

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO paradigma( front_name, r_condition, id_class, attrs ) VALUES ( '%us', '%us', %d, '%us' )",
  lem::to_upper(p.GetName()).c_str(), matcher.c_str(), p.GetClass(), attrs.c_str() );
 lem::FString sql1( lem::to_utf8(mem.string()) );
 Execute(sql1);
 const int id = (int)sqlite3_last_insert_rowid(hdb);

 for( lem::Container::size_type i=0; i<p.GetNames().size(); ++i )
  {
   lem::MemFormatter mem2;
   mem2.printf( "INSERT INTO paradigma_name( id_paradigma, name, uname ) VALUES ( %d, '%us', '%us' )",
    id, p.GetNames()[i].c_str(), lem::to_upper(p.GetNames()[i]).c_str() );
   lem::FString sql2( lem::to_utf8(mem2.string()) );
   Execute(sql2);
  }

 for( lem::Container::size_type i=0; i<p.GetForms().size(); ++i )
  {
   const SG_DeclensionForm & f = * p.GetForms()[i];
   
   lem::UFString dims;
   for( lem::Container::size_type i=0; i<f.GetDim().size(); ++i )
    {
     if( i>0 )
      dims.Add_Dirty( L' ' );

     dims.Add_Dirty( lem::format_str( L"%d:%d", f.GetDim()[i].GetCoord().GetIndex(), f.GetDim()[i].GetState() ).c_str() );
    }

   lem::UFString generator( f.GetLexemGenerator().c_str() );
   lem::UFString condition_str( f.GetConditionStr() );
   lem::UFString flexer_flags( f.GetFlexerFlagsStr() );

   sqlite_escape(generator);
   sqlite_escape(condition_str);
   sqlite_escape(flexer_flags);  


   lem::MemFormatter mem3;
   mem3.printf( "INSERT INTO paradigma_form( id_paradigma, lexem_generator, rx_condition, flexer_flags, dims ) VALUES ( %d, '%us', '%us', '%us', '%us' )",
    id, generator.c_str(), condition_str.c_str(), flexer_flags.c_str(), dims.c_str() );

   lem::FString sql3( lem::to_utf8(mem3.string()) );
   Execute(sql3);
  }

 return id;
}




SG_DeclensionTable* LexiconStorage_SQLITE::GetParadigma( int id )
{
 lem::FString sql1( lem::format_str( "SELECT r_condition, id_class, attrs FROM paradigma WHERE id=%d", id ) );
 
 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, sql1.c_str(), sql1.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::UFString matcher_str = lem::sqlite_column_ufstring(stmt,0);
     int id_class = sqlite3_column_int(stmt,1);
     lem::UFString attrs_str = lem::sqlite_column_ufstring(stmt,2);
     sqlite3_finalize(stmt);

     CP_Array attrs;
     attrs.Parse(attrs_str);

     lem::MCollect<lem::UCString> names;
     
     lem::FString sql2( lem::format_str( "SELECT name FROM paradigma_name WHERE id_paradigma=%d ORDER BY id", id ) );
    
     sqlite3_stmt *stmt2=NULL;
     const char *dummy2=NULL;
     res = sqlite3_prepare_v2( hdb, sql2.c_str(), sql2.length(), &stmt2, &dummy2 );
     if( res==SQLITE_OK )
      {
       while( sqlite3_step( stmt2 ) == SQLITE_ROW )
        {
         lem::UCString name = lem::sqlite_column_ucstring(stmt2,0);
         names.push_back(name);
        }
       sqlite3_finalize(stmt2);
      }
     else
      {
       RaiseError(__FILE__,__LINE__);
      }

     lem::MCollect<SG_DeclensionForm*> forms;
     lem::FString sql3( lem::format_str( "SELECT lexem_generator, rx_condition, flexer_flags, dims FROM paradigma_form WHERE id_paradigma=%d ORDER BY id", id ) );
    
     sqlite3_stmt *stmt3=NULL;
     const char *dummy3=NULL;
     res = sqlite3_prepare_v2( hdb, sql3.c_str(), sql3.length(), &stmt3, &dummy3 );
     if( res==SQLITE_OK )
      {
       while( sqlite3_step( stmt3 ) == SQLITE_ROW )
        {
         lem::UFString lexem_generator = lem::sqlite_column_ufstring(stmt3,0);
         lem::UFString rx_condition = lem::sqlite_column_ufstring(stmt3,1);
         lem::UFString flexer_flags = lem::sqlite_column_ufstring(stmt3,2);
         lem::UFString dims_str = lem::sqlite_column_ufstring(stmt3,3);

         CP_Array dims;
         dims.Parse(dims_str);

         SG_DeclensionForm *form = new SG_DeclensionForm( lexem_generator, rx_condition, flexer_flags, dims );
         forms.push_back(form);
        }

       sqlite3_finalize(stmt3);
      }
     else
      {
       RaiseError(__FILE__,__LINE__);
      }

     SG_DeclensionTable *p = new SG_DeclensionTable( names, matcher_str, id_class, attrs, forms );
     return p;
    }
   else
    {
     throw lem::E_BaseException( lem::format_str( "Can not load paradigma id=%d", id ) );
    }
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return false;
  }
}


void LexiconStorage_SQLITE::AddEnding( const lem::UCString &ending, int id_language, int efreq )
{
 UFString s(ending.c_str());
 sqlite_escape(s);

if( lem::is_uspace(ending.back()) )
 {
  lem::MemFormatter mem;
  mem.printf( "Precondition violation for ending [%us]: ending must not ends with space character!", ending.c_str() );
  throw E_BaseException(mem.string());
 }

 // такое окончание уже есть?
 lem::MemFormatter q;
 q.printf( "SELECT id FROM endings WHERE ending='%us' AND id_language=%d", s.c_str(), id_language );
 int id = SelectInt(q.string());

 if( id==-1 )
  {
   q.printf( "INSERT INTO endings( ending, id_language, nform, sumfreq ) VALUES ( '%us', %d, 1, %d )",
    s.c_str(), id_language, efreq );
  }
 else
  {
   q.printf( "UPDATE endings SET nform=nform+1, sumfreq=sumfreq+%d WHERE id=%d", efreq, id );
  }

 Execute( q.string() );
 return;
}



bool LexiconStorage_SQLITE::GetEndingStat( int id_language, EndingStat &res )
{
 lem::MemFormatter q;
 q.printf( "SELECT max_len FROM ending_stat WHERE id_language=%d", id_language );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(q.string()) );
 if( rs->Fetch() )
  {
   res.max_len = rs->GetInt(0);
   return true;
  }
 else
  {
   return false;
  }
}


bool LexiconStorage_SQLITE::FindEnding( int id_language, const lem::UCString &ending, int &nentry, int &sumfreq )
{
 UFString s(ending.c_str());
 sqlite_escape(s);

 lem::MemFormatter q;
 q.printf( "SELECT nform, sumfreq FROM endings WHERE ending='%us' AND id_language=%d", s.c_str(), id_language );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(q.string()) );
 if( rs->Fetch() )
  {
   nentry = rs->GetInt(0);
   sumfreq = rs->GetInt(1);
   return true;
  }
 else
  {
   nentry=sumfreq=0;
   return false;
  }
}


LS_ResultSet* LexiconStorage_SQLITE::ListEndings(void)
{
 return ListByQuery("SELECT id, ending, id_language, nform, sumfreq FROM endings");
}


LS_ResultSet* LexiconStorage_SQLITE::ListEndingStat(void)
{
 return ListByQuery("SELECT id_language, max_len FROM ending_stat");
}

void LexiconStorage_SQLITE::CommitCompilation(void)
{
 Execute( "DELETE FROM ending_stat" );

 lem::MemFormatter q;

 lem::Ptr<LS_ResultSet> rs = ListByQuery("SELECT id_language, MAX(Length(ending)) FROM endings GROUP BY id_language");
 while( rs->Fetch() )
  {
   int id_language = rs->GetInt(0);
   int max_len = rs->GetInt(1);
   q.printf( "INSERT INTO ending_stat( id_language, max_len ) VALUES ( %d, %d )", id_language, max_len );
   Execute( q.string() );
  }

 return;
}


void LexiconStorage_SQLITE::SetWordformFrequency( int id_entry, int iform, int frequency )
{
 LEM_CHECKIT_Z( id_entry!=UNKNOWN );
 LEM_CHECKIT_Z( iform!=UNKNOWN );
 LEM_CHECKIT_Z( frequency>=0 );

 // чтобы не допустить дубля и нарушения ограничения уникальности, проверим, нет ли
 // записи для этой словоформы.
 
 lem::MemFormatter q;
 q.printf( "SELECT id FROM wordform_frequency WHERE id_entry=%d AND iform=%d", id_entry, iform );
 int id = SelectInt(q.string());

 if( id==-1 )
  {
   q.printf( "INSERT INTO wordform_frequency( id_entry, iform, freq ) VALUES ( %d, %d, %d )",
    id_entry, iform, frequency );
  }
 else
  {
   q.printf( "UPDATE wordform_frequency SET freq=%d WHERE id=%d", frequency, id );
  }

 Execute( q.string() );
 return;
}


std::pair<bool,int> LexiconStorage_SQLITE::GetWordformFrequency( int id_entry, int iform )
{
 lem::MemFormatter q;
 q.printf( "SELECT freq FROM wordform_frequency WHERE id_entry=%d AND iform=%d", id_entry, iform );
 lem::Ptr<LS_ResultSet> rc( ListByQuery(q.string()) );
 if( rc->Fetch() )
  {
   return std::make_pair(true,rc->GetInt(0));
  }
 else
  {
   return std::make_pair(false,0);
  }
}


LS_ResultSet* LexiconStorage_SQLITE::ListWordformFrequency(void)
{
 return ListByQuery("SELECT id, id_entry, iform, freq FROM wordform_frequency");
}


void LexiconStorage_SQLITE::DeleteWordformFrequency(void)
{
 Execute("DELETE FROM wordform_frequency");
 return;
}





int LexiconStorage_SQLITE::FindWordSet( const lem::UCString &set_name )
{
 if(
    set_name.front()==L'\'' ||
    set_name.front()==L'"' ||
    set_name.back()==L'\'' ||
    set_name.back()==L'"'
   )
  return UNKNOWN;

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM word_set WHERE name='%us'", to_upper(set_name).c_str() );
 return sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}


void LexiconStorage_SQLITE::DeleteWordSets(void)
{
 Execute("DELETE FROM word_set");
 return;
}

WordSetItem* LexiconStorage_SQLITE::GetWordSet( int id )
{
 lem::FString Select(lem::format_str( "SELECT words, name, case_sensitive FROM word_set WHERE id=%d", id ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     WordSetItem *res = new WordSetItem();
     res->id = id;

     res->name = lem::sqlite_column_ucstring(stmt,1);
     lem::UFString s = lem::sqlite_column_ufstring(stmt,0);

     lem::Collect<lem::UFString> toks;
     const wchar_t delimiters[2] = { WORD_SET_DELIMITER, 0 };
     lem::parse( s, toks, delimiters );
     for( lem::Container::size_type i=0; i<toks.size(); ++i )
      {
       res->words.insert(toks[i].c_str());
      }

     res->case_sensitive = sqlite3_column_int(stmt,2)==1;

     sqlite3_finalize(stmt);
     return res;
    }
   else
    {
     lem::MemFormatter mem;
     mem.printf( "Co not find word set with id=%d", id );
     throw lem::E_BaseException(mem.string());
    } 
  }
 else
  {
   RaiseError(__FILE__,__LINE__);
   return NULL;
  }
}



void LexiconStorage_SQLITE::StoreWordSet( WordSetItem &wes )
{
 lem::UFString s;
 for( std::set<lem::UCString>::const_iterator it=wes.words.begin(); it!=wes.words.end(); ++it )
  {
   if( !s.empty() )
    s.Add_Dirty(WORD_SET_DELIMITER);

   UFString word( it->c_str() );
   sqlite_escape(word);
   s.Add_Dirty( word.c_str() );
  }

 lem::MemFormatter q;
 q.printf( "INSERT INTO word_set( name, case_sensitive, words ) VALUES ( '%us', %d, '%us' )",
           lem::to_upper(wes.name).c_str(), wes.case_sensitive ? 1 : 0, s.c_str() );
 
 lem::FString sql(lem::to_utf8(q.string()));
 Execute(sql);

 wes.id = (int)sqlite3_last_insert_rowid(hdb);
 return;
}


LS_ResultSet* LexiconStorage_SQLITE::ListWordSet(void)
{
 return ListByQuery("SELECT id FROM word_set ORDER BY id");
}




bool LexiconStorage_SQLITE::FindMisspelling( int id_language, const lem::UCString &word, lem::MCollect<lem::UCString> &new_words )
{
 lem::UFString s( word.c_str() );
 s.to_upper();
 sqlite_escape(s);

 lem::MemFormatter mem;

 if( id_language==UNKNOWN || id_language==ANY_STATE )
  mem.printf( "SELECT substitution FROM misspelling WHERE original_word='%us'", s.c_str() );
 else 
  mem.printf( "SELECT substitution FROM misspelling WHERE original_word='%us' AND id_language=%d", s.c_str(), id_language );

 LS_ResultSet *rs = ListByQuery(mem.string());

 while( rs->Fetch() )
  {
   new_words.push_back( rs->GetUCString(0) );
  }

 delete rs;
 return !new_words.empty();
}


void LexiconStorage_SQLITE::AddMisspelling( int id_language, const lem::UCString &word, const lem::UCString &new_word )
{
 if( id_language==UNKNOWN )
  throw E_BaseException( L"Misspelling rule requires language id to be defined" );

 lem::UFString s1( word.c_str() );
 s1.to_upper();
 sqlite_escape(s1);

 lem::UFString s2( new_word.c_str() );
 s2.to_upper();
 sqlite_escape(s2);

 lem::MemFormatter mem;
 mem.printf( "SELECT count(*) FROM misspelling WHERE original_word='%us' AND substitution='%us' AND id_language=%d", s1.c_str(), s2.c_str(), id_language );
 int n = SelectInt(mem.string());

 if( n>0 )
  {
   mem.printf( "Misspelling rule is already defined for %us --> %us", word.c_str(), new_word.c_str() );
   throw E_BaseException( mem.string() );
  }

 mem.printf( "INSERT INTO misspelling( id_language, original_word, substitution ) VALUES ( %d, '%us', '%us' )",
  id_language, s1.c_str(), s2.c_str() );

 Execute( mem.string() );
 return; 
}


LS_ResultSet* LexiconStorage_SQLITE::ListMisspelling(void)
{
 return ListByQuery("SELECT id, id_language, original_word, substitution FROM misspelling ORDER BY id");
}


void LexiconStorage_SQLITE::DeleteMisspelling(void)
{
 Execute("DELETE FROM misspelling");
 return; 
}








int LexiconStorage_SQLITE::RegisterCollocationSet( const lem::UCString &name, bool case_sensitive )
{
 LEM_CHECKIT_Z( !name.empty() );

 lem::MemFormatter q;
 q.printf( "INSERT INTO collocation_set( name, case_sensitive ) VALUES ( '%us', %d )",
           lem::to_upper(name).c_str(), case_sensitive ? 1 : 0 );
 
 lem::FString sql(lem::to_utf8(q.string()));
 Execute(sql);

 const int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


int LexiconStorage_SQLITE::FindCollocationSet( const lem::UCString &name )
{
 if(
    name.front()==L'\'' ||
    name.front()==L'"' ||
    name.back()==L'\'' ||
    name.back()==L'"'
   )
  return UNKNOWN;

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM collocation_set WHERE name='%us'", to_upper(name).c_str() );
 return sqlite_select_int( hdb, lem::to_utf8(mem.string()) );
}



void LexiconStorage_SQLITE::AddCollocationToSet( int id_set, const lem::MCollect<lem::UCString> &words )
{
 LEM_CHECKIT_Z( id_set!=UNKNOWN );
 LEM_CHECKIT_Z( !words.empty() );

 lem::UFString str;
 LexiconStorage::MergeCollocationWords( words, str );
 sqlite_escape(str);

 lem::UFString headword( words.front().c_str() );
 sqlite_escape(headword);

 const int n_word = CastSizeToInt(words.size());

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO collocation_set_item( id_set, words, n_word, headword ) VALUES ( %d, '%us', %d, '%us' )",
  id_set, str.c_str(), n_word, headword.c_str() );
 Execute(mem.string());

 // обновим поисковую информацию.
 int id_headword=-1;
 int min_len=-1, max_len=-1;
 mem.printf( "SELECT id, min_len, max_len FROM collocation_headword WHERE headword='%us'", headword.c_str() );
 LS_ResultSet *rs = ListByQuery( mem.string() );
 if( rs->Fetch() )
  {
   id_headword = rs->GetInt(0);
   min_len = rs->GetInt(1);
   max_len = rs->GetInt(2);
  }
 lem_rub_off(rs);
 
 if( id_headword==-1 )
  {
   min_len=max_len=n_word;
   mem.printf( "INSERT INTO collocation_headword( headword, min_len, max_len ) VALUES ( '%us', %d, %d )",
    headword.c_str(), min_len, max_len );

   Execute( mem.string() );
  }
 else
  {
   min_len = std::min( min_len, n_word );
   max_len = std::max( max_len, n_word );
   mem.printf( "UPDATE collocation_headword SET min_len=%d, max_len=%d WHERE id=%d", min_len, max_len, id_headword );
   Execute( mem.string() );   
  }

 return;
}


int LexiconStorage_SQLITE::FindCollocationSetHeadword( const lem::UCString &headword, int &min_len, int &max_len )
{
 lem::UFString h(headword.c_str());
 sqlite_escape(h);
 lem::MemFormatter mem;
 mem.printf( "SELECT id, min_len, max_len FROM collocation_headword WHERE headword='%us'",
  h.c_str() );

 int id=-1; 
 LS_ResultSet *rs = ListByQuery( mem.string() );
 if( rs->Fetch() )
  {
   id = rs->GetInt(0);
   min_len = rs->GetInt(1);
   max_len = rs->GetInt(2);
  }
 else
  {
   min_len=max_len=0;
  }
 lem_rub_off(rs);
 
 return id;
}


int LexiconStorage_SQLITE::FindCollocationInSet( int id_set, const lem::MCollect<lem::UCString> &words )
{
 LEM_CHECKIT_Z( id_set!=UNKNOWN );
 LEM_CHECKIT_Z( !words.empty() );

 lem::UFString str;
 LexiconStorage::MergeCollocationWords( words, str );
 sqlite_escape(str);

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM collocation_set_item WHERE words='%us' AND id_set=%d", str.c_str(), id_set );
 return SelectInt(mem.string());
}


LS_ResultSet* LexiconStorage_SQLITE::ListCollocationSets(void)
{
 return ListByQuery( "SELECT id, name, case_sensitive FROM collocation_set ORDER BY id" );
}


LS_ResultSet* LexiconStorage_SQLITE::ListCollocationSetItems(void)
{
 return ListByQuery( "SELECT id, id_set, words, n_word, headword FROM collocation_set_item ORDER BY id" );
}


LS_ResultSet* LexiconStorage_SQLITE::ListCollocationSetHeadwords(void)
{
 return ListByQuery( "SELECT id, headword, min_len, max_len FROM collocation_headword" );
}


void LexiconStorage_SQLITE::DeleteCollocationSets(void)
{
 Execute( "DELETE from collocation_headword" );
 Execute( "DELETE from collocation_set_item" );
 Execute( "DELETE from collocation_set" );
 return;
}






int LexiconStorage_SQLITE::StoreFacts( const KB_Facts * facts )
{
 lem::UFString name( facts->GetName().c_str() );
 sqlite_escape(name);

 int id_violation_handler=-1;
 if( facts->violation_handler!=NULL )
  {
   id_violation_handler = facts->violation_handler->Store(this);
  }

 int CompositeQueryMode = facts->GetQueryMode();
 if( facts->NeedsFeaturesCheck() )
  CompositeQueryMode |= 0x00010000;
 

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO kb_facts( name, id_language, n_arg, n_ret, query_mode, ret_type, violation_handler, violation_score )"
             " VALUES ( '%us', %d, %d, %d, %d, %d, %d, %d )"
  , name.c_str(), facts->GetLanguage(), facts->CountOfArg(), facts->CountOfRet(), CompositeQueryMode, facts->GetReturnType()
  , id_violation_handler, facts->violation_score );

 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


void LexiconStorage_SQLITE::UpdateFactsQueryMode( const KB_Facts * facts )
{
 LEM_CHECKIT_Z( facts->GetId()!=UNKNOWN );

 int CompositeQueryMode = facts->GetQueryMode();
 if( facts->NeedsFeaturesCheck() )
  CompositeQueryMode |= 0x00010000;

 lem::MemFormatter mem;
 mem.printf( "UPDATE kb_facts SET query_mode=%d WHERE id=%d", CompositeQueryMode, facts->GetId() );
 Execute( mem.string() );
 return;
}



int LexiconStorage_SQLITE::StoreFact( const KB_Facts & facts, const KB_Fact * fact )
{
 lem::MemFormatter mem;

 lem::CString boolean_return, integer_return;

 if( facts.DoesReturnBoolean() )
  boolean_return = lem::to_str( fact->GetBooleanReturn() );
 else
  boolean_return = "NULL";

 if( facts.DoesReturnInteger() )
  integer_return = lem::to_str( fact->GetIntegerReturn() );
 else
  integer_return = "NULL";

 mem.printf( "INSERT INTO kb_fact( id_group, boolean_return, integer_return, false_score )"
             " VALUES ( %d, %s, %s, %d )"
              , fact->GetGroupId()
              , boolean_return.c_str()
              , integer_return.c_str()
              , fact->GetFalseScore() );

 const int id = ExecuteAndReturnId( mem.string() );

 for( int i=0; i<fact->CountArgs(); ++i )
  StoreFactArgument( id, i, fact->GetArg(i) );

 if( facts.IsQueryableByEntries() )
  {
   if( fact->IsMultiIndexed() )
    {
     lem::Collect< lem::MCollect<int> > id_entries;
     lem::MCollect<int> index;
     int n_total=1;

     for( int i=0; i<fact->CountArgs(); ++i )
      {
       lem::MCollect<int> arg_lemmas;
       if( fact->GetArg(i).IsMetaEntry() )
        {
         GetMetaEntryItems( fact->GetArg(i).id_metaentry, arg_lemmas );
        }
       else
        {
         arg_lemmas.push_back( fact->GetArg(i).id_entry );
        }

       id_entries.push_back(arg_lemmas);
       index.push_back(0);
       n_total *= CastSizeToInt( arg_lemmas.size() );
      }

     lem::CString id_entry1("NULL"), id_entry2("NULL"), id_entry3("NULL"), id_entry4("NULL"), id_entry5("NULL");
     for( int k=0; k<n_total; ++k )
      {
       id_entry1 = lem::to_str( id_entries[0][index[0]] );

       if( fact->CountArgs()>1 )
        id_entry2 = lem::to_str( id_entries[1][index[1]] );
    
       if( fact->CountArgs()>2 )
        id_entry3 = lem::to_str( id_entries[2][index[2]] );
    
       if( fact->CountArgs()>3 )
        id_entry4 = lem::to_str( id_entries[3][index[3]] );
    
       if( fact->CountArgs()>4 )
        id_entry5 = lem::to_str( id_entries[4][index[4]] );
    
       mem.printf( "INSERT INTO kb_fact_index2( id_group, id_fact,"
               " id_entry1, id_entry2, id_entry3, id_entry4, id_entry5 )"
               " VALUES ( %d, %d,"
               " %s, %s, %s, %s, %s )"
                , fact->GetGroupId()
                , id
                , id_entry1.c_str(), id_entry2.c_str(), id_entry3.c_str(), id_entry4.c_str(), id_entry5.c_str() );
    
       Execute( mem.string() );

       for( int j=CastSizeToInt(index.size())-1; j>=0; --j )
        {
         index[j]++;
         if( index[j]==CastSizeToInt(id_entries[j].size()) )
          index[j]=0;
         else
          break;
        }
      }     
    }
   else
    {
     lem::CString id_entry1("NULL"), id_entry2("NULL"), id_entry3("NULL"), id_entry4("NULL"), id_entry5("NULL");
     id_entry1 = lem::to_str(fact->GetArg(0).id_entry);

     if( fact->CountArgs()>1 )
      id_entry2 = lem::to_str(fact->GetArg(1).id_entry);

     if( fact->CountArgs()>2 )
      id_entry3 = lem::to_str(fact->GetArg(2).id_entry);

     if( fact->CountArgs()>3 )
      id_entry4 = lem::to_str(fact->GetArg(3).id_entry);

     if( fact->CountArgs()>4 )
      id_entry5 = lem::to_str(fact->GetArg(4).id_entry);

     mem.printf( "INSERT INTO kb_fact_index2( id_group, id_fact,"
             " id_entry1, id_entry2, id_entry3, id_entry4, id_entry5 )"
             " VALUES ( %d, %d,"
             " %s, %s, %s, %s, %s )"
              , fact->GetGroupId()
              , id
              , id_entry1.c_str(), id_entry2.c_str(), id_entry3.c_str(), id_entry4.c_str(), id_entry5.c_str() );

     Execute( mem.string() );
    }
  }
 else if( facts.IsQueryableByWords() )
  {
   lem::UFString word1(L"NULL"), word2(L"NULL"), word3(L"NULL"), word4(L"NULL"), word5(L"NULL");

   word1 = fact->GetArg(0).word.c_str();
   sqlite_escape( word1 );
   word1.dress_apostrophes();

   if( fact->CountArgs()>1 )
    {
     word2 = fact->GetArg(1).word.c_str();
     sqlite_escape( word2 );
     word2.dress_apostrophes();
    }

   if( fact->CountArgs()>2 )
    {
     word3 = fact->GetArg(2).word.c_str();
     sqlite_escape( word3 );
     word3.dress_apostrophes();
    }

   if( fact->CountArgs()>3 )
    {
     word4 = fact->GetArg(3).word.c_str();
     sqlite_escape( word4 );
     word4.dress_apostrophes();
    }

   if( fact->CountArgs()>4 )
    {
     word5 = fact->GetArg(4).word.c_str();
     sqlite_escape( word5 );
     word5.dress_apostrophes();
    }

   mem.printf( "INSERT INTO kb_fact_index1( id_group, id_fact,"
             " word1, word2, word3, word4, word5 )"
             " VALUES ( %d, %d,"
             " %us, %us, %us, %us, %us )"
              , fact->GetGroupId()
              , id
              , word1.c_str(), word2.c_str(), word3.c_str(), word4.c_str(), word5.c_str() );

   Execute( mem.string() );
  }


 return id;
}


int LexiconStorage_SQLITE::StoreFactArgument(
                                             int id_fact,
                                             int arg_index,
                                             const KB_Argument & arg
                                            )
{
 lem::MemFormatter mem;

 lem::UFString word_str( arg.is_regex ? arg.regex_str.c_str() : arg.word.c_str() );
 sqlite_escape(word_str);

 lem::UFString wordset_name_str( arg.wordset_name.c_str() );
 sqlite_escape(wordset_name_str);

 lem::UFString wordentryset_name_str( arg.wordentryset_name.c_str() );
 sqlite_escape(wordentryset_name_str);

 const int n_coords = CastSizeToInt( arg.coords.size() );

 int id_coord1=UNKNOWN, id_state1=UNKNOWN, affirm1=UNKNOWN, id_coord2=UNKNOWN,
     id_state2=UNKNOWN, affirm2=UNKNOWN, id_coord3=UNKNOWN, id_state3=UNKNOWN, affirm3=UNKNOWN,
     id_coord4=UNKNOWN, id_state4=UNKNOWN, affirm4=UNKNOWN;

 if( n_coords>0 )
  {
   id_coord1 = arg.coords[0].GetCoord().GetIndex();
   id_state1 = arg.coords[0].GetState();
   affirm1 = arg.coords[0].GetAffirm();
  }

 if( n_coords>1 )
  {
   id_coord2 = arg.coords[1].GetCoord().GetIndex();
   id_state2 = arg.coords[1].GetState();
   affirm2 = arg.coords[1].GetAffirm();
  }
 
 if( n_coords>2 )
  {
   id_coord3 = arg.coords[2].GetCoord().GetIndex();
   id_state3 = arg.coords[2].GetState();
   affirm3 = arg.coords[2].GetAffirm();
  }

 if( n_coords>3 )
  {
   id_coord4 = arg.coords[3].GetCoord().GetIndex();
   id_state4 = arg.coords[3].GetState();
   affirm4 = arg.coords[3].GetAffirm();
  }

 if( n_coords>4 )
  {
   LEM_STOPIT;
  }

 mem.printf( "INSERT INTO kb_argument_point( id_fact, argument_index, word_text, id_entry, id_class,"
             "   wordset_name, wordentryset_name,"
             "   n_coords, id_coord1, id_state1, affirm1, id_coord2,"
             "   id_state2, affirm2, id_coord3, id_state3, affirm3,"
             "   id_coord4, id_state4, affirm4, thesauruscheck_link, thesauruscheck_entry,"
             "   is_positive, is_regex, case_sensitive, id_metaentry )"
           );

 mem.printf( "   VALUES ( %d, %d, '%us', %d, %d,",
                 id_fact, arg_index, word_str.c_str(), arg.id_entry, arg.id_class );

 mem.printf( "            '%us', '%us',",
                 wordset_name_str.c_str(), wordentryset_name_str.c_str() );

 mem.printf( "            %d, %d, %d, %d, %d,",
                 n_coords, id_coord1, id_state1, affirm1, id_coord2 );

 mem.printf( "            %d, %d, %d, %d, %d,",
                 id_state2, affirm2, id_coord3, id_state3, affirm3 );

 mem.printf( "            %d, %d, %d, %d, %d,",
                 id_coord4, id_state4, affirm4, arg.ThesaurusCheck_Link, arg.ThesaurusCheck_Entry );

 mem.printf( "            %d, %d, %d, %d )",
                 arg.is_positive ? 1 : 0, arg.is_regex ?  1 : 0, arg.case_sensitive ?  1 : 0, arg.id_metaentry );

 int new_id = ExecuteAndReturnId( lem::to_utf8(mem.string()) );
 return new_id;
}



KB_Facts* LexiconStorage_SQLITE::LoadFacts( int id_facts )
{
 KB_Facts * res = new KB_Facts();
 res->id = id_facts;

 lem::MemFormatter mem;
 mem.printf( "SELECT id_language, name, n_arg, n_ret, query_mode, ret_type, violation_score FROM kb_facts WHERE id=%d", id_facts );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   res->id_language = rs->GetInt(0);
   res->name = rs->GetUCString(1);
   res->n_arg = rs->GetInt(2);
   res->n_ret = rs->GetInt(3);

   int mode = rs->GetInt(4);
   res->query_mode = 0x0000ffff & mode;
   res->check_features =  (mode & 0x00010000)==0x00010000;

   res->ret_type = rs->GetInt(5);
   res->violation_score = rs->GetInt(6);
  }
 else
  {
   LEM_STOPIT;
  }

 return res;
}


LS_ResultSet* LexiconStorage_SQLITE::ListFactsInGroup( int id_facts )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM kb_fact WHERE id_group=%d ORDER BY id", id_facts );
 return ListByQuery( mem.string() );
}



KB_Fact* LexiconStorage_SQLITE::LoadFact( int id )
{
 KB_Fact * res = new KB_Fact();
 res->id_group = id;

 lem::MemFormatter mem;
 mem.printf( "SELECT id_group, Coalesce(boolean_return,-1), Coalesce(integer_return,-1), false_score FROM kb_fact WHERE id=%d", id );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   res->id_group = rs->GetInt(0);
   res->bool_return = rs->GetInt(1);
   res->int_return = rs->GetInt(2);
   res->false_score = rs->GetInt(3);
  }
 else
  {
   LEM_STOPIT;
  }

 mem.printf( "SELECT id FROM kb_argument_point WHERE id_fact=%d ORDER BY argument_index", id );

 lem::Ptr<LS_ResultSet> rs2( ListByQuery(mem.string()) );
 while( rs2->Fetch() )
 {
  const int id_arg = rs2->GetInt(0);
  KB_Argument * arg = LoadFactArgument(id_arg);
  res->args.push_back(arg);
 }

 return res;
}


KB_Argument* LexiconStorage_SQLITE::LoadFactArgument( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT is_regex, word_text, id_entry, id_class,"
             "   wordset_name, wordentryset_name,"
             "   n_coords, id_coord1, id_state1, affirm1, id_coord2,"
             "   id_state2, affirm2, id_coord3, id_state3, affirm3,"
             "   id_coord4, id_state4, affirm4,"
             "   thesauruscheck_link, thesauruscheck_entry,"
             "   is_positive, case_sensitive, id_metaentry"
             " FROM kb_argument_point WHERE id=%d"
             , id );


 KB_Argument * res = new KB_Argument();

 lem::Ptr<LS_ResultSet> rs( ListByQuery( mem.string() ) );
 if( rs->Fetch() )
  {
   res->is_regex = rs->GetInt(0)==1;

   if( res->is_regex )
    res->regex_str = rs->GetUFString(1);
   else
    res->word = rs->GetUCString(1);

   res->id_entry = rs->GetInt(2);
   res->id_class = rs->GetInt(3);

   res->wordset_name = rs->GetUCString(4);
   res->wordentryset_name = rs->GetUCString(5);

   const int n_coords = rs->GetInt(6);

   int id_coord1 = rs->GetInt(7);
   int id_state1 = rs->GetInt(8);
   int affirm1 = rs->GetInt(9);

   int id_coord2 = rs->GetInt(10);
   int id_state2 = rs->GetInt(11);
   int affirm2 = rs->GetInt(12);
 
   int id_coord3 = rs->GetInt(13);
   int id_state3 = rs->GetInt(14);
   int affirm3 = rs->GetInt(15);

   int id_coord4 = rs->GetInt(16);
   int id_state4 = rs->GetInt(17);
   int affirm4 = rs->GetInt(18);

   if( n_coords>0 )
    res->coords.push_back( GramCoordEx( id_coord1, id_state1, affirm1==1 ) );
   
   if( n_coords>1 )
    res->coords.push_back( GramCoordEx( id_coord2, id_state2, affirm2==1 ) );

   if( n_coords>2 )
    res->coords.push_back( GramCoordEx( id_coord3, id_state3, affirm3==1 ) );

   if( n_coords>3 )
    res->coords.push_back( GramCoordEx( id_coord4, id_state4, affirm4==1 ) );

   if( n_coords>4 )
    {
     LEM_STOPIT;
    }

   res->ThesaurusCheck_Link = rs->GetInt(19);
   res->ThesaurusCheck_Entry = rs->GetInt(20);
   res->is_positive = rs->GetInt(21)==1;

   res->case_sensitive = rs->GetInt(22)==1;

   if( res->is_regex )
    res->InitRegularExpression();

   res->id_metaentry = rs->GetInt(23);
  }
 else
  {
   LEM_STOPIT;
  }

 return res;
}


LS_ResultSet* LexiconStorage_SQLITE::ListFactGroups(void)
{
 const char q[] = "SELECT id, id_language, name, n_arg, n_ret, query_mode, ret_type, violation_score, violation_handler FROM kb_facts ORDER BY id";
 return ListByQuery(q);
}

LS_ResultSet* LexiconStorage_SQLITE::ListFacts(void)
{
 const char q[] = "SELECT id, id_group, Coalesce(boolean_return,-1), Coalesce(integer_return,-1) false_score FROM kb_fact ORDER BY id";
 return ListByQuery(q);
}


LS_ResultSet* LexiconStorage_SQLITE::ListFactIndex1(void)
{
 const char q[] = "SELECT id, id_group, id_fact,"
                  " coalesce(word1,''), coalesce(word2,''), coalesce(word3,''), coalesce(word4,''), coalesce(word5,'') FROM kb_fact_index1 ORDER BY id";
 return ListByQuery(q);
}

LS_ResultSet* LexiconStorage_SQLITE::ListFactIndex2(void)
{
 const char q[] = "SELECT id, id_group, id_fact,"
                  " coalesce(id_entry1,-1), coalesce(id_entry2,-1), coalesce(id_entry3,-1), coalesce(id_entry4,-1), coalesce(id_entry5,-1)"
                  " FROM kb_fact_index2 ORDER BY id";
 return ListByQuery(q);
}




LS_ResultSet* LexiconStorage_SQLITE::ListFactArguments(void)
{
 const char q[] = "SELECT id, id_fact, argument_index, word_text, id_entry,"
                  " id_class, wordentryset_name, wordset_name, n_coords, id_coord1,"
                  " id_state1, affirm1, id_coord2, id_state2, affirm2,"
                  " id_coord3, id_state3, affirm3, id_coord4, id_state4,"
                  " affirm4, thesauruscheck_link, thesauruscheck_entry, is_positive,"
                  " is_regex, case_sensitive, id_metaentry"
                  " FROM kb_argument_point"
                  " ORDER BY id";
 return ListByQuery(q);
}



int LexiconStorage_SQLITE::FindFactByEntries(
                                             int id_facts,
                                             int n_arg,
                                             int return_type,
                                             int id_entry1,
                                             int id_entry2,
                                             int id_entry3,
                                             int id_entry4,
                                             int id_entry5,
                                             KB_CheckingResult &result
                                            )
{
 lem::MemFormatter mem;

 mem.printf( "SELECT F.id, Coalesce(F.boolean_return,-1), Coalesce(F.integer_return,-1), F.false_score"
             " FROM kb_fact_index2 I, kb_fact F"
             " WHERE I.id_group=%d AND I.id_entry1=%d", id_facts, id_entry1 );

 if( n_arg>1 )
  mem.printf( " AND I.id_entry2=%d", id_entry2 );

 if( n_arg>2 )
  mem.printf( " AND I.id_entry3=%d", id_entry3 );

 if( n_arg>3 )
  mem.printf( " AND I.id_entry4=%d", id_entry4 );

 if( n_arg>4 )
  mem.printf( " AND I.id_entry5=%d", id_entry5 );

  mem.printf(" AND F.id=I.id_fact" );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   const int id_fact = rs->GetInt(0);
   const int boolean_return = rs->GetInt(1);
   const int integer_return = rs->GetInt(2);
   
   if( boolean_return!=-1 )
    {
     const int false_score = rs->GetInt(3);
     result = KB_BoolResult(boolean_return,false_score);
    }
   else if( integer_return!=-1 )
    result = KB_IntResult(integer_return);
   else
    {
     LEM_STOPIT;
    }
   
   return id_fact;
  }
 else
  {
   result = KB_NotMatchedResult();
   return UNKNOWN;
  }
}




void LexiconStorage_SQLITE::FindFactsByEntries(
                                               int id_facts,
                                               int n_arg,
                                               int id_entry1,
                                               int id_entry2,
                                               int id_entry3,
                                               int id_entry4,
                                               int id_entry5,
                                               lem::MCollect<int> & id_fact
                                              )
{
 lem::MemFormatter mem;

 mem.printf( "SELECT id_fact"
             " FROM kb_fact_index2"
             " WHERE id_group=%d AND id_entry1=%d", id_facts, id_entry1 );

 if( n_arg>1 )
  mem.printf( " AND id_entry2=%d", id_entry2 );

 if( n_arg>2 )
  mem.printf( " AND id_entry3=%d", id_entry3 );

 if( n_arg>3 )
  mem.printf( " AND id_entry4=%d", id_entry4 );

 if( n_arg>4 )
  mem.printf( " AND id_entry5=%d", id_entry5 );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 while( rs->Fetch() )
  {
   const int id = rs->GetInt(0);
   id_fact.push_back(id);
  }

 return;
}





int LexiconStorage_SQLITE::FindFactByWords(
                                           int id_facts,
                                           int n_arg,
                                           int return_type,
                                           const lem::UCString &word1,
                                           const lem::UCString &word2,
                                           const lem::UCString &word3,
                                           const lem::UCString &word4,
                                           const lem::UCString &word5,
                                           KB_CheckingResult &result
                                          )
{
 lem::MemFormatter mem;

 lem::UFString word1_str( word1.c_str() );
 sqlite_escape(word1_str);

 mem.printf( "SELECT F.id, Coalesce(F.boolean_return,-1), Coalesce(F.integer_return,-1), F.false_score"
             " FROM kb_fact_index1 I, kb_fact F"
             " WHERE I.id_group=%d AND I.word1=%us", id_facts, word1_str.c_str() );

 if( n_arg>1 )
  {
   lem::UFString str( word2.c_str() );
   sqlite_escape(str);
   mem.printf( " AND I.word2=%us", str.c_str() );
  }

 if( n_arg>2 )
  {
   lem::UFString str( word3.c_str() );
   sqlite_escape(str);
   mem.printf( " AND I.word3=%us", str.c_str() );
  }

 if( n_arg>3 )
  {
   lem::UFString str( word4.c_str() );
   sqlite_escape(str);
   mem.printf( " AND I.word4=%us", str.c_str() );
  }

 if( n_arg>4 )
  {
   lem::UFString str( word5.c_str() );
   sqlite_escape(str);
   mem.printf( " AND I.word5=%us", str.c_str() );
  }

 mem.printf( " AND F.id=I.id_fact" );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   const int id_fact = rs->GetInt(0);
   const int boolean_return = rs->GetInt(1);
   const int integer_return = rs->GetInt(2);
   
   if( boolean_return!=-1 )
    {
     const int false_score = rs->GetInt(3);
     result = KB_BoolResult(boolean_return,false_score);
    }
   else if( integer_return!=-1 )
    result = KB_IntResult(integer_return);
   else
    {
     LEM_STOPIT;
    }
   
   return id_fact;
  }
 else
  {
   result = KB_NotMatchedResult();
   return UNKNOWN;
  }
}




int LexiconStorage_SQLITE::RegisterWordformSet( const lem::UCString & set_name )
{
 LEM_CHECKIT_Z( !set_name.empty() );
 lem::MemFormatter mem;
 lem::UFString escaped_set_name(set_name.c_str());
 sqlite_escape(escaped_set_name);
 mem.printf( "INSERT INTO wordform_set( name ) VALUES ( '%us' )", escaped_set_name.c_str() );
 return ExecuteAndReturnId(mem.string());
}



int LexiconStorage_SQLITE::StoreWordformSetCoords( const CP_Array & coords )
{
 CP_Array sorted_coords(coords);
 SortCoords(sorted_coords);

 lem::FString str_coords;
 SerializeCoords( sorted_coords, str_coords );

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM wordform_set_coords WHERE coords='%s'", str_coords.c_str() );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  return rs->GetInt(0);

 mem.printf( "INSERT INTO wordform_set_coords( coords ) VALUES ( '%s' )", str_coords.c_str() );
 return ExecuteAndReturnId(mem.string());
}



void LexiconStorage_SQLITE::StoreWordformSetItem( int id_set, const lem::UCString & lexeme, int ekey, int id_coords )
{
 LEM_CHECKIT_Z( id_set!=UNKNOWN );
 LEM_CHECKIT_Z( !lexeme.empty() );
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( id_coords!=UNKNOWN );
 
 lem::UFString escaped_lexeme(lexeme.c_str());
 sqlite_escape(escaped_lexeme);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO wordform_set_item( id_set, word, id_entry, id_coords ) VALUES ( %d, '%us', %d, %d )", id_set, escaped_lexeme.c_str(), ekey, id_coords );
 Execute( mem.string() );
 return;
}


LS_ResultSet* LexiconStorage_SQLITE::ListWordformSets(void)
{
 return ListByQuery( "SELECT id, name FROM wordform_set" );
}

LS_ResultSet* LexiconStorage_SQLITE::ListWordformSetCoords(void)
{
 return ListByQuery( "SELECT id, coords FROM wordform_set_coords" );
}

LS_ResultSet* LexiconStorage_SQLITE::ListWordformSetItems(void)
{
 return ListByQuery( "SELECT id, id_set, word, id_entry, id_coords FROM wordform_set_item" );
}



int LexiconStorage_SQLITE::FindWordformSetItem( int id_set, const lem::UCString & word, int id_entry, int * id_coords )
{
 LEM_CHECKIT_Z( !word.empty() );
 LEM_CHECKIT_Z( id_set!=UNKNOWN );
 LEM_CHECKIT_Z( id_entry!=UNKNOWN );
 LEM_CHECKIT_Z( id_coords!=NULL );

 lem::MemFormatter mem;
 lem::UFString escaped_lexeme(word.c_str());
 sqlite_escape(escaped_lexeme);

 mem.printf( "SELECT id, id_coords FROM wordform_set_item WHERE id_set=%d AND word='%us' AND id_entry=%d", id_set, escaped_lexeme.c_str(), id_entry );
 
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   * id_coords = rs->GetInt(1);
   return rs->GetInt(0);
  }
 else
  return UNKNOWN;
}



void LexiconStorage_SQLITE::LoadWordformSetCoords( int id_coords, Solarix::CP_Array & pairs )
{
 LEM_CHECKIT_Z( id_coords!=UNKNOWN );

 lem::MemFormatter mem;
 mem.printf( "SELECT coords FROM wordform_set_coords WHERE id=%d", id_coords );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   lem::UFString str = rs->GetUFString(0);

   lem::Collect<lem::UFString> toks;
   lem::parse( str, toks, L" " );

   lem::Collect<lem::UFString> toks2;

   for( lem::Container::size_type i=0; i<toks.size(); ++i )
    {
     toks2.clear();
     lem::parse( toks[i], toks2, L":" );
     int id_coord = lem::to_int( toks2[0].c_str() );
     int id_state = lem::to_int( toks2[1].c_str() );
     pairs.push_back( GramCoordPair(id_coord,id_state) );
    }
  }
 else
  {
   mem.printf( "Can not find wordform set coords id=%d", id_coords );
   throw lem::E_BaseException( mem.string() );
  } 
}


int LexiconStorage_SQLITE::FindWordformSet( const lem::UCString & set_name )
{
 lem::MemFormatter mem;

 lem::UFString escaped_name(set_name.c_str());
 sqlite_escape(escaped_name);
 mem.printf( "SELECT id FROM wordform_set WHERE name='%us'", escaped_name.c_str() );

 return SelectInt( mem.string() );
}



void LexiconStorage_SQLITE::DeleteWordformSets(void)
{
 Execute("DELETE FROM wordform_set");
 Execute("DELETE FROM wordform_set_coords");
 Execute("DELETE FROM wordform_set_item");
 return;
}




int LexiconStorage_SQLITE::StoreTreeScorerGroup( const lem::UCString & name, const TreeScorerGroupParams & params )
{
 lem::UFString escaped_name(name.c_str());
 sqlite_escape(escaped_name);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO ts_group( name, allow_unmatched_children ) VALUES ( '%us', %d )", escaped_name.c_str(), params.allow_unmatched_children );
 const int id = ExecuteAndReturnId( ms.string() );
 return id;
}

void LexiconStorage_SQLITE::LoadTreeScorerGroupParams( int id, TreeScorerGroupParams & params )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT allow_unmatched_children FROM ts_group WHERE id=%d", id );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 if( rs->Fetch() )
  {
   params.allow_unmatched_children = rs->GetInt(0)==1;
  }
 else
  {
   LEM_STOPIT;
  }
}


int LexiconStorage_SQLITE::FindTreeScorerGroup( const lem::UCString & name )
{
 lem::UFString escaped_name(name.c_str());
 sqlite_escape(escaped_name);

 lem::MemFormatter ms;
 ms.printf( "SELECT id FROM ts_group WHERE name='%us'", escaped_name.c_str() );
 const int id = SelectInt( ms.string() );
 return id;
}


LS_ResultSet* LexiconStorage_SQLITE::ListTreeScorerGroups()
{
 return ListByQuery( "SELECT id, name, allow_unmatched_children FROM ts_group" );
}





int LexiconStorage_SQLITE::RegisterTreeScorer_Word( const lem::UCString & word, int id_root_point, const lem::UFString & scoring_expression, int scoring_type, bool root_node, int id_group )
{
 LEM_CHECKIT_Z( !word.empty() );
 LEM_CHECKIT_Z( id_root_point!=UNKNOWN );

 lem::UFString escaped_word(word.c_str());
 sqlite_escape(escaped_word);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO ts_head_word( word, id_head_point, score_expr, score_type, root_node, id_group ) VALUES ( '%us', %d, '%us', %d, %d, %d )", escaped_word.c_str(), id_root_point, scoring_expression.c_str(), scoring_type, root_node ? 1 : 0, id_group );
 const int id_head = ExecuteAndReturnId( ms.string() );

 return id_head;
}



int LexiconStorage_SQLITE::RegisterTreeScorer_Generic( int id_root_point, const lem::UFString & scoring_expression, int scoring_type, int id_group )
{
 LEM_CHECKIT_Z( id_root_point!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO generic_tree_scorer( id_head_point, score_expr, score_type, id_group ) VALUES ( %d, '%us', %d, %d )", id_root_point, scoring_expression.c_str(), scoring_type, id_group );
 const int id = ExecuteAndReturnId( ms.string() );

 return id;
}


int LexiconStorage_SQLITE::RegisterTreeScorer_Wordentry( int EntryKey, int id_root_point, const lem::UFString & scoring_expression, int scoring_type, bool root_node, int id_group )
{
 LEM_CHECKIT_Z( EntryKey!=UNKNOWN );
 LEM_CHECKIT_Z( EntryKey!=ANY_STATE );
 LEM_CHECKIT_Z( id_root_point!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO ts_head_lemma( id_entry, id_head_point, score_expr, score_type, root_node, id_group ) VALUES ( %d, %d, '%us', %d, %d, %d )", EntryKey, id_root_point, scoring_expression.c_str(), scoring_type, root_node ? 1 : 0, id_group );
 const int id_head = ExecuteAndReturnId( ms.string() );

 return id_head;
}


void LexiconStorage_SQLITE::StoreTreeScoreGroupMember( int id_group, int id_root )
{
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO ts_group2root( id_group, id_root ) VALUES ( %d, %d )", id_group, id_root );
 Execute( ms.string() );
 return;
}


LS_ResultSet* LexiconStorage_SQLITE::ListTreeScoreGroupMembers()
{
 return ListByQuery( "SELECT id_group, id_root FROM ts_group2root" );
}


void LexiconStorage_SQLITE::ListTreeScoreGroupMembers( int id_group, lem::MCollect<int> & roots )
{
 LEM_CHECKIT_Z( id_group!=UNKNOWN );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(lem::format_str( "SELECT id_root FROM ts_group2root WHERE id_group=%d", id_group )) );
 while( rs->Fetch() )
 {
  roots.push_back( rs->GetInt(0) );
 }

 return;
}



LS_ResultSet* LexiconStorage_SQLITE::ListGenericTreeScorers()
{
 return ListByQuery( "SELECT id, id_head_point, id_group, score_expr, score_type FROM generic_tree_scorer" );
}


LS_ResultSet* LexiconStorage_SQLITE::ListTreeScorerPredicates()
{
 return ListByQuery( "SELECT id, id_point, func_name, narg, id_class1 FROM ts_predicate" );
}




int LexiconStorage_SQLITE::StoreTreeScorerPoint(
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
                                               )
{
 lem::MemFormatter mem;

 lem::UFString word_str( word.c_str() );
 sqlite_escape(word_str);

 lem::UFString wordset_name_str( wordset_name.c_str() );
 sqlite_escape(wordset_name_str);

 lem::UFString wordentryset_name_str( wordentryset_name.c_str() );
 sqlite_escape(wordentryset_name_str);

 lem::UFString wordformset_name_str( wordformset_name.c_str() );
 sqlite_escape(wordformset_name_str);

 const int n_coords = CastSizeToInt( coords.size() );

 int id_coord1=UNKNOWN, id_state1=UNKNOWN, affirm1=UNKNOWN, id_coord2=UNKNOWN,
     id_state2=UNKNOWN, affirm2=UNKNOWN, id_coord3=UNKNOWN, id_state3=UNKNOWN, affirm3=UNKNOWN,
     id_coord4=UNKNOWN, id_state4=UNKNOWN, affirm4=UNKNOWN;

 if( n_coords>0 )
  {
   id_coord1 = coords[0].GetCoord().GetIndex();
   id_state1 = coords[0].GetState();
   affirm1 = coords[0].GetAffirm();
  }

 if( n_coords>1 )
  {
   id_coord2 = coords[1].GetCoord().GetIndex();
   id_state2 = coords[1].GetState();
   affirm2 = coords[1].GetAffirm();
  }
 
 if( n_coords>2 )
  {
   id_coord3 = coords[2].GetCoord().GetIndex();
   id_state3 = coords[2].GetState();
   affirm3 = coords[2].GetAffirm();
  }

 if( n_coords>3 )
  {
   id_coord4 = coords[3].GetCoord().GetIndex();
   id_state4 = coords[3].GetState();
   affirm4 = coords[3].GetAffirm();
  }

 if( n_coords>4 )
  {
   LEM_STOPIT;
  }


 lem::UFString set_name1, set_name2, set_name3;
 int set_type1=-1, set_type2=-1, set_type3=-1;
 int set_affirm1=-1, set_affirm2=-1, set_affirm3=-1;

 const int n_set_checkers = CastSizeToInt( set_checkers.size() );
 
 if( n_set_checkers>0 )
  {
   set_name1 = set_checkers[0].set_name.c_str();
   sqlite_escape(set_name1);
   set_type1 = set_checkers[0].set_type;
   set_affirm1 = set_checkers[0].affirm;
  }

 if( n_set_checkers>1 )
  {
   set_name2 = set_checkers[1].set_name.c_str();
   sqlite_escape(set_name2);
   set_type2 = set_checkers[1].set_type;
   set_affirm2 = set_checkers[1].affirm;
  }

 if( n_set_checkers>2 )
  {
   set_name3 = set_checkers[2].set_name.c_str();
   sqlite_escape(set_name3);
   set_type3 = set_checkers[2].set_type;
   set_affirm3 = set_checkers[2].affirm;
  }

 if( n_set_checkers>3 )
  {
   throw lem::E_BaseException( L"Only 3 set checkers are allowed" );
  }


 const int n_backref = CastSizeToInt( back_correls.size() );
 
 int br_affirm_0=-1;
 int br_coord0_0=-1;
 lem::UFString br_marker_0;
 int br_coord1_0=-1;
 int br_for_group_0=-1;

 int br_affirm_1=-1;
 int br_coord0_1=-1;
 lem::UFString br_marker_1;
 int br_coord1_1=-1;
 int br_for_group_1=-1;

 int br_affirm_2=-1;
 int br_coord0_2=-1;
 lem::UFString br_marker_2;
 int br_coord1_2=-1;
 int br_for_group_2=-1;

 if( n_backref>0 )
  {
   br_affirm_0 = back_correls[0].affirmative;
   br_coord0_0 = back_correls[0].id_coord0;
   br_marker_0 = back_correls[0].name.c_str();
   br_coord1_0 = back_correls[0].id_coord1;
   br_for_group_0 = back_correls[0].for_group;
  }

 if( n_backref>1 )
  {
   br_affirm_1 = back_correls[1].affirmative;
   br_coord0_1 = back_correls[1].id_coord0;
   br_marker_1 = back_correls[1].name.c_str();
   br_coord1_1 = back_correls[1].id_coord1;
   br_for_group_1 = back_correls[1].for_group;
  }

 if( n_backref>2 )
  {
   br_affirm_2 = back_correls[2].affirmative;
   br_coord0_2 = back_correls[2].id_coord0;
   br_marker_2 = back_correls[2].name.c_str();
   br_coord1_2 = back_correls[2].id_coord1;
   br_for_group_2 = back_correls[2].for_group;
  }
 
 LEM_CHECKIT_Z( n_backref<=3 );

 mem.printf( "INSERT INTO ts_point( id_parent, word_text, id_entry, id_metaentry, id_class,"
             " wordset_name, wordentryset_name, wordformset_name,"
             " n_coords, id_coord1, id_state1, affirm1, id_coord2,"
             " id_state2, affirm2, id_coord3, id_state3, affirm3,"
             " id_coord4, id_state4, affirm4,"
             " thesauruscheck_link, thesauruscheck_entry,"
             " is_positive, children_quantification_min_count, children_quantification_max_count,"
             " n_setcheckers, set_name1, set_type1, set_affirm1, set_name2,"
             " set_type2, set_affirm2, set_name3, set_type3, set_affirm3,"
             " link_type, relative_position, id_src, id_group, quantification_min_count,"
             " quantification_max_count, marker,"
             " n_backref,"
             " br_affirm_0, br_coord0_0, br_marker_0, br_coord1_0, br_for_group_0,"
             " br_affirm_1, br_coord0_1, br_marker_1, br_coord1_1, br_for_group_1,"
             " br_affirm_2, br_coord0_2, br_marker_2, br_coord1_2, br_for_group_2"
             " )"
           );

 mem.printf( " VALUES ( %d, '%us', %d, %d, %d,",
                 id_parent_point, word_str.c_str(), id_entry, id_metaentry, id_class );

 mem.printf( " '%us', '%us', '%us',",
                 wordset_name_str.c_str(), wordentryset_name_str.c_str(), wordformset_name_str.c_str() );

 mem.printf( " %d, %d, %d, %d, %d,",
                 n_coords, id_coord1, id_state1, affirm1, id_coord2 );

 mem.printf( " %d, %d, %d, %d, %d,",
                 id_state2, affirm2, id_coord3, id_state3, affirm3 );

 mem.printf( " %d, %d, %d, ",
                 id_coord4, id_state4, affirm4 );

 mem.printf( " %d, %d,",
                 ThesaurusCheck_Link, ThesaurusCheck_Entry );

 mem.printf( " %d, %d, %d,",
                 is_positive ? 1 : 0, children_quantification_min_count, children_quantification_max_count );

 mem.printf( " %d, '%us', %d, %d, '%us', %d, %d, '%us', %d, %d,",
               n_set_checkers, set_name1.c_str(), set_type1, set_affirm1, set_name2.c_str(), set_type2, set_affirm2, set_name3.c_str(), set_type3, set_affirm3 );

 mem.printf( " %d, %d, %d, %d, %d,", link_type, relative_position, id_src, id_group, quantification_min_count );
 mem.printf( " %d, '%us',", quantification_max_count, marker.c_str() );

 mem.printf( " %d,", n_backref );

 mem.printf( " %d, %d, '%us', %d, %d,", br_affirm_0, br_coord0_0, br_marker_0.c_str(), br_coord1_0, br_for_group_0 );
 mem.printf( " %d, %d, '%us', %d, %d,", br_affirm_1, br_coord0_1, br_marker_1.c_str(), br_coord1_1, br_for_group_1 );
 mem.printf( " %d, %d, '%us', %d, %d", br_affirm_2, br_coord0_2, br_marker_2.c_str(), br_coord1_2, br_for_group_2 );

 mem.printf( " )" );


 int new_id = ExecuteAndReturnId( mem.string() );
 return new_id;
}





void LexiconStorage_SQLITE::StoreTreeScorerPredicate(
                                                     int id_host_point,
                                                     const lem::UCString & func_name,
                                                     const lem::Collect<TreeScorerPredicateArg> & args
                                                    )
{
 lem::MemFormatter mem;

 const int n_arg = CastSizeToInt( args.size() );

 int id_class1=UNKNOWN;

 if( n_arg>0 )
  {
   id_class1 = args[0].id_class;
  }

 if( n_arg>1 )
  {
   LEM_STOPIT;
  }

 mem.printf( "INSERT INTO ts_predicate( id_point, func_name, narg, id_class1 )" );

 mem.printf( " VALUES ( %d, '%us', %d, %d )",
                 id_host_point, func_name.c_str(), n_arg, id_class1 );

 ExecuteAndReturnId( mem.string() );
 return;
}





void LexiconStorage_SQLITE::ListTreeScorers(
                                            int id_group,
                                            const Solarix::Word_Form & root,
                                            lem::MCollect<int> & headpoint_ids,
                                            lem::MCollect<TreeScorerResult*> & scores,
                                            lem::MCollect<int> & anchor_is_root
                                           )
{
 lem::MemFormatter mem;

 const int id_entry = root.GetEntryKey();
 mem.printf( "SELECT id_head_point, score_type, score_expr, root_node FROM ts_head_lemma WHERE id_entry=%d AND id_group=%d", id_entry, id_group );
 
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 while( rs->Fetch() )
  {
   int id_headpoint = rs->GetInt(0);
   int score_type = rs->GetInt(1);
   lem::UFString score_expr = rs->GetUFString(2);
   int root_node = rs->GetInt(3);

   TreeScorerResult * score = new TreeScorerResult();
   score->DeserializeExpression( score_type, score_expr );

   headpoint_ids.push_back( id_headpoint );
   scores.push_back( score );
   anchor_is_root.push_back( root_node );
  }
 rs.Delete();


 lem::UFString word_str( root.GetNormalized()->c_str() );
 sqlite_escape(word_str);

 mem.printf( "SELECT id_head_point, score_type, score_expr, root_node FROM ts_head_word WHERE word='%us'", word_str.c_str() );
 rs = ListByQuery(mem.string());
 while( rs->Fetch() )
  {
   int id_headpoint = rs->GetInt(0);
   int score_type = rs->GetInt(1);
   lem::UFString score_expr = rs->GetUFString(2);
   int root_node = rs->GetInt(3);

   TreeScorerResult * score = new TreeScorerResult();
   score->DeserializeExpression( score_type, score_expr );

   headpoint_ids.push_back( id_headpoint );
   scores.push_back( score );
   anchor_is_root.push_back( root_node );
  }

 return;
}



void LexiconStorage_SQLITE::ListGenericTreeScorers(
                                                   int id_group,
                                                   lem::MCollect<int> & headpoint_ids,
                                                   lem::MCollect<TreeScorerResult*> & scores
                                                  )
{
 lem::MemFormatter mem;

 mem.printf( "SELECT id_head_point, score_type, score_expr FROM generic_tree_scorer WHERE id_group=%d", id_group );
 
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 while( rs->Fetch() )
  {
   int id_headpoint = rs->GetInt(0);
   int score_type = rs->GetInt(1);
   lem::UFString score_expr = rs->GetUFString(2);

   TreeScorerResult * score = new TreeScorerResult();
   score->DeserializeExpression( score_type, score_expr );

   headpoint_ids.push_back( id_headpoint );
   scores.push_back( score );
  }
 rs.Delete();

 return;
}




int LexiconStorage_SQLITE::GetTreeScorerHeadpointSrc( int id_point )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id_src FROM ts_point WHERE id=%d", id_point );
 return SelectInt( mem.string() );
}



TreeScorerPoint* LexiconStorage_SQLITE::LoadTreeScorerPoint( int id_point )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id, word_text, id_entry, id_class,"
             " wordset_name, wordentryset_name, wordformset_name,"
             " n_coords, id_coord1, id_state1, affirm1, id_coord2,"
             " id_state2, affirm2, id_coord3, id_state3, affirm3,"
             " id_coord4, id_state4, affirm4,"
             " thesauruscheck_link, thesauruscheck_entry,"
             " is_positive, children_quantification_min_count, children_quantification_max_count,"
             " n_setcheckers, set_name1, set_type1, set_affirm1, set_name2,"
             " set_type2, set_affirm2, set_name3, set_type3, set_affirm3,"
             " link_type, id_metaentry, relative_position, id_group, quantification_min_count,"
             " quantification_max_count, marker, n_backref, br_affirm_0, br_coord0_0,"
             " br_marker_0, br_coord1_0, br_for_group_0,"
             " br_affirm_1, br_coord0_1, br_marker_1, br_coord1_1, br_for_group_1,"
             " br_affirm_2, br_coord0_2, br_marker_2, br_coord1_2, br_for_group_2"
             " FROM ts_point WHERE id=%d"
             , id_point );

 return LoadTreeScorerPoint( mem.string() );
}





void LexiconStorage_SQLITE::LoadTreeScorerChildNodes( int id_point, lem::MCollect<TreeScorerPoint*> & scorer_leafs )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM ts_point WHERE id_parent=%d", id_point );

 lem::Ptr<LS_ResultSet> rs( ListByQuery( mem.string() ) );
 while( rs->Fetch() )
  {
   int id = rs->GetInt(0);
   scorer_leafs.push_back( LoadTreeScorerPoint( id ) );
  }

 return; 
}




TreeScorerPoint* LexiconStorage_SQLITE::LoadTreeScorerPoint( const lem::UFString & query )
{ 
 TreeScorerPoint * res = new TreeScorerPoint();

 lem::Ptr<LS_ResultSet> rs( ListByQuery(lem::to_utf8(query) ) );
 if( rs->Fetch() )
  {
   res->id = rs->GetInt(0);
   res->word = rs->GetUCString(1);
   res->id_entry = rs->GetInt(2);
   res->id_class = rs->GetInt(3);

   res->wordset_name = rs->GetUCString(4);
   res->wordentryset_name = rs->GetUCString(5);
   res->wordformset_name = rs->GetUCString(6);

   const int n_coords = rs->GetInt(7);

   int id_coord1 = rs->GetInt(8);
   int id_state1 = rs->GetInt(9);
   int affirm1 = rs->GetInt(10);

   int id_coord2 = rs->GetInt(11);
   int id_state2 = rs->GetInt(12);
   int affirm2 = rs->GetInt(13);
 
   int id_coord3 = rs->GetInt(14);
   int id_state3 = rs->GetInt(15);
   int affirm3 = rs->GetInt(16);

   int id_coord4 = rs->GetInt(17);
   int id_state4 = rs->GetInt(18);
   int affirm4 = rs->GetInt(19);

   if( n_coords>0 )
    res->coords.push_back( GramCoordEx( id_coord1, id_state1, affirm1==1 ) );
   
   if( n_coords>1 )
    res->coords.push_back( GramCoordEx( id_coord2, id_state2, affirm2==1 ) );

   if( n_coords>2 )
    res->coords.push_back( GramCoordEx( id_coord3, id_state3, affirm3==1 ) );

   if( n_coords>3 )
    res->coords.push_back( GramCoordEx( id_coord4, id_state4, affirm4==1 ) );

   if( n_coords>4 )
    {
     LEM_STOPIT;
    }


   res->ThesaurusCheck_Link = rs->GetInt(20);
   res->ThesaurusCheck_Entry = rs->GetInt(21);
   res->is_positive = rs->GetInt(22)==1;

   res->children_quantification.min_count = rs->GetInt(23);
   res->children_quantification.max_count = rs->GetInt(24);

   const int n_set_checkers = rs->GetInt(25);

   CollocFilterSetChecker set_checker;

   if( n_set_checkers>0 )
    {
     set_checker.set_name = rs->GetUCString(26);
     set_checker.set_type = rs->GetInt(27);
     set_checker.affirm = rs->GetInt(28)==1;
     res->set_checkers.push_back(set_checker);
    }

   if( n_set_checkers>1 )
    {
     set_checker.set_name = rs->GetUCString(29);
     set_checker.set_type = rs->GetInt(30);
     set_checker.affirm = rs->GetInt(31)==1;
     res->set_checkers.push_back(set_checker);
    }

   if( n_set_checkers>2 )
    {
     set_checker.set_name = rs->GetUCString(32);
     set_checker.set_type = rs->GetInt(33);
     set_checker.affirm = rs->GetInt(34)==1;
     res->set_checkers.push_back(set_checker);
    }

   LEM_CHECKIT_Z( n_set_checkers<=3 );

   res->link_type = rs->GetInt(35);

   res->id_metaentry = rs->GetInt(36);
   res->relative_position = rs->GetInt(37);
   res->id_group = rs->GetInt(38);

   res->quantification.min_count = rs->GetInt(39);
   res->quantification.max_count = rs->GetInt(40);

   res->marker = rs->GetUCString(41);

   int n_backref = rs->GetInt(42);
   int index=43;
   for( int k=0; k<n_backref; ++k )
    {
     BackRefCorrel r;
     r.affirmative = rs->GetInt(index++)==1;
     r.id_coord0 = rs->GetInt(index++);
     r.name = rs->GetUCString(index++);
     r.id_coord1 = rs->GetInt(index++);
     r.for_group = rs->GetInt(index++)==1;
     res->back_correls.push_back(r);
    }

   LoadTreeScorerPredicates( res );
  }
 else
  {
   LEM_STOPIT;
  }

 return res;
}


void LexiconStorage_SQLITE::LoadTreeScorerPredicates( TreeScorerPoint * p )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM ts_predicate WHERE id_point=%d", p->id );
 lem::Ptr<LS_ResultSet> rs( ListByQuery( mem.string() ) );
 while( rs->Fetch() )
  {
   TreeScorerPredicate * predicate = LoadTreeScorerPredicate(rs->GetInt(0));
   p->predicates.push_back(predicate);
  }


 return;
}


TreeScorerPredicate* LexiconStorage_SQLITE::LoadTreeScorerPredicate( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT func_name, narg, id_class1 FROM ts_predicate WHERE id=%d", id );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );
 rs->Fetch();

 lem::UCString func_name = rs->GetUCString(0);
 int narg = rs->GetInt(1);

 lem::Collect<TreeScorerPredicateArg> args;
 if( narg>0 )
  {
   TreeScorerPredicateArg a;
   a.id_class = rs->GetInt(2);
   args.push_back(a);
  }

 TreeScorerPredicate * res = new TreeScorerPredicate(func_name,args);
 return res;
}


LS_ResultSet* LexiconStorage_SQLITE::ListTreeScorerLemmas()
{
 return ListByQuery( "SELECT id_entry, id_head_point, score_type, score_expr, root_node, id_group FROM ts_head_lemma" );
}


LS_ResultSet* LexiconStorage_SQLITE::ListTreeScorerWords()
{
 return ListByQuery( "SELECT word, id_head_point, score_type, score_expr, root_node, id_group FROM ts_head_word" );
}


LS_ResultSet* LexiconStorage_SQLITE::ListTreeScorerPoints()
{
 return ListByQuery( "SELECT id, id_parent, word_text, id_entry, id_class,"
                     "wordentryset_name, wordset_name, wordformset_name, n_coords, id_coord1,"
                     "id_state1, affirm1, id_coord2, id_state2, affirm2,"
                     "id_coord3, id_state3, affirm3, id_coord4, id_state4,"
                     "affirm4, thesauruscheck_link, thesauruscheck_entry, is_positive, children_quantification_min_count, children_quantification_min_count,"
                     "n_setcheckers, set_name1, set_type1, set_affirm1, set_name2,"
                     "set_type2, set_affirm2, set_name3, set_type3, set_affirm3,"
                     "link_type, id_metaentry, relative_position, id_src, id_group,"
                     "quantification_min_count, quantification_max_count, marker, n_backref, br_affirm_0,"
                     " br_coord0_0, br_marker_0, br_coord1_0, br_for_group_0"
                     " FROM ts_point" );
}




int LexiconStorage_SQLITE::StoreMetaEntry(
                                          const lem::UCString & name,
                                          int id_class,
                                          const lem::MCollect<int> & entries
                                         )
{
 LEM_CHECKIT_Z( !entries.empty() );
 LEM_CHECKIT_Z( !name.empty() );
 LEM_CHECKIT_Z( !lem::is_quantor(id_class) ); 

 lem::UFString name_str( name.c_str() );
 sqlite_escape(name_str);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO metaentry( name, id_class ) VALUES ('%us',%d)", name_str.c_str(), id_class );
 const int id = ExecuteAndReturnId( mem.string() );


 for( lem::Container::size_type i=0; i<entries.size(); ++i )
 {
  LEM_CHECKIT_Z( !lem::is_quantor(entries[i]) );
  mem.printf( "INSERT INTO metaentry_item( id_metaentry, id_entry ) VALUES ( %d, %d )", id, entries[i] );
  Execute( mem.string() );
 }

 return id;
}

int LexiconStorage_SQLITE::FindMetaEntry( const lem::UCString & name, int id_class )
{
 LEM_CHECKIT_Z( !name.empty() );
 LEM_CHECKIT_Z( !lem::is_quantor(id_class) ); 

 lem::UFString name_str( name.c_str() );
 sqlite_escape(name_str);

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM metaentry WHERE id_class=%d AND name='%us'", id_class, name_str.c_str() );
 const int id = SelectInt( mem.string() );
 return id;
}


void LexiconStorage_SQLITE::GetMetaEntryItems( int id_metaentry, lem::MCollect<int> & entries )
{
 LEM_CHECKIT_Z( id_metaentry!=UNKNOWN );
 entries.clear();

 lem::MemFormatter mem;
 mem.printf( "SELECT id_entry FROM metaentry_item WHERE id_metaentry=%d", id_metaentry );
 
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );

 while( rs->Fetch() )
 {
  int id_entry = rs->GetInt(0);
  entries.push_back(id_entry);
 }

 return;
}



LS_ResultSet* LexiconStorage_SQLITE::ListMetaEntries()
{
 return ListByQuery( "SELECT id FROM metaentry" );
}


MetaEntry* LexiconStorage_SQLITE::LoadMetaEntry( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id_class, name FROM metaentry WHERE id=%d", id );
 lem::Ptr<LS_ResultSet> rs( ListByQuery(mem.string()) );

 if( rs->Fetch() )
 {
  int id_class = rs->GetInt(0);
  lem::UCString name( rs->GetUCString(1) );

  lem::MCollect<int> entries;
  GetMetaEntryItems( id, entries );
  return new MetaEntry( id, id_class, name, entries );
 }
 else
 {
  mem.printf( "Can not load metaentry id=%d", id );
  throw lem::E_BaseException( mem.string() );
 }
}



bool LexiconStorage_SQLITE::DoesMetaEntryContains( int id_metaentry, int id_entry )
{
 LEM_CHECKIT_Z( id_metaentry!=UNKNOWN );
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM metaentry_item WHERE id_metaentry=%d AND id_entry=%d", id_metaentry, id_entry );
 return SelectInt( mem.string() )!=-1;
}





int LexiconStorage_SQLITE::StoreWordAssoc_ByLemma( int src_location, int id_entry, int id_entry1, int score )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, id_entry1, score, id_metaentry1, id_metaentry2, id_entry2, link_type, link_entry, set_type )"
             " VALUES (%d,%d,%d,%d,-1,-1,-1,-1,-1,-1)", src_location, id_entry, id_entry1, score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}



int LexiconStorage_SQLITE::StoreWordAssoc_ByMetaentry( int src_location, int id_entry, int id_metaentry, int score )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, id_metaentry1, score, id_entry1, id_metaentry2, id_entry2, link_type, link_entry, set_type )"
             " VALUES (%d,%d,%d,%d,-1,-1,-1,-1,-1,-1)", src_location, id_entry, id_metaentry, score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


int LexiconStorage_SQLITE::StoreWordAssoc_ByLexem( int src_location, int id_entry, const lem::UCString & word1, int score )
{
 lem::UFString word_str( word1.c_str() );
 sqlite_escape(word_str);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, word1, score, id_entry1, id_entry2, id_metaentry1, id_metaentry2, link_type, link_entry, set_type )"
             " VALUES (%d,%d,'%us',%d,-1,-1,-1,-1,-1,-1,-1)", src_location, id_entry, word_str.c_str(), score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


int LexiconStorage_SQLITE::StoreWordAssoc_ByThesaurusLink( int src_location, int id_entry, int link_type, int link_entry, int score )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, link_type, link_entry, score, id_entry1, id_entry2, set_type, id_metaentry1, id_metaentry2 )"
             " VALUES (%d,%d,%d,%d,%d,-1,-1,-1,-1,-1)", src_location, id_entry, link_type, link_entry, score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


int LexiconStorage_SQLITE::StoreWordAssoc_BySet( int src_location, int id_entry, const lem::UCString & set_name, int set_type, int score )
{
 lem::UFString set_str( set_name.c_str() );
 sqlite_escape(set_str);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, set_name, set_type, score, id_entry1, id_entry2, link_type, link_entry, id_metaentry1, id_metaentry2 )"
             " VALUES (%d,%d,'%us',%d,%d,-1,-1,-1,-1,-1,-1)", src_location, id_entry, set_str.c_str(), set_type, score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


LS_ResultSet* LexiconStorage_SQLITE::ListAssociationsForEntry( int id_entry )
{
 LEM_CHECKIT_Z( id_entry>=0 );
 return ListByQuery( lem::format_str("SELECT id FROM word_assoc WHERE id_entry=%d",id_entry) );
}


LS_ResultSet* LexiconStorage_SQLITE::ListAssociatedEntries()
{
 return ListByQuery( "SELECT id FROM word_assoc" );
}


WordAssociation* LexiconStorage_SQLITE::LoadAssocitation( int id )
{
 LEM_CHECKIT_Z( id>=0 );

 lem::MemFormatter sql;
 sql.printf( "SELECT id_src, id_entry, id_entry1, word1, id_entry2, word2, link_type, link_entry, set_name, set_type, score, id_metaentry1, id_metaentry2"
             " FROM word_assoc WHERE id=%d", id );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(sql.string()) );
 if( rs->Fetch() )
  {
   int id_src = rs->GetInt(0);
   int id_entry = rs->GetInt(1);
   int id_entry1 = rs->GetInt(2);
   lem::UCString word1 = rs->GetUCString(3);
   int id_entry2 = rs->GetInt(4);
   lem::UCString word2 = rs->GetUCString(5);
   int link_type = rs->GetInt(6);
   int link_entry = rs->GetInt(7);
   lem::UCString set_name = rs->GetUCString(8);
   int set_type = rs->GetInt(9);
   int score = rs->GetInt(10);
   int id_metaentry1 = rs->GetInt(11);
   int id_metaentry2 = rs->GetInt(12);

   return new WordAssociation( id, id_src, id_entry, id_entry1, word1, id_metaentry1, id_entry2, word2, id_metaentry2, link_type, link_entry, set_name, set_type, score );
  }
 else
  {
   sql.printf( "Can not find word_assoc record with id=%d", id );
   throw E_BaseException( sql.string() );
  }
}




LS_ResultSet* LexiconStorage_SQLITE::ListPredicateTemplate()
{
 return ListByQuery( "SELECT id FROM predicate_template" );
}


PredicateTemplate* LexiconStorage_SQLITE::LoadPredicateTemplate( int id )
{
 lem::Ptr<LS_ResultSet> rs( ListByQuery( lem::format_str( "SELECT src, params FROM predicate_template WHERE id=%d", id ) ) );
 lem::UFString src = rs->GetUFString(0);
 lem::UFString params = rs->GetUFString(1);
 PredicateTemplate * ret = new PredicateTemplate( id, src, params );
 return ret;
}


int LexiconStorage_SQLITE::StorePredicateTemplate( const lem::UFString & src, const lem::MCollect<lem::UCString> & params )
{
 lem::UFString escaped(src);
 lem::sqlite_escape(escaped);

 lem::UFString escaped_params;
 for( lem::Container::size_type i=0; i<params.size(); ++i )
  if( escaped_params.empty() )
   escaped_params.Add_Dirty( params[i].c_str() );
  else
   {
    escaped_params.Add_Dirty( L',' );
    escaped_params.Add_Dirty( params[i].c_str() );
   }

 lem::sqlite_escape(escaped_params);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO predicate_template( src, params ) VALUES ( '%us', '%us' )", escaped.c_str(), escaped_params.c_str() );

 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}



void LexiconStorage_SQLITE::StoreOmonym( const lem::UCString & entry_name, int id_class )
{
 LEM_CHECKIT_Z( id_class!=UNKNOWN );
 LEM_CHECKIT_Z( !entry_name.empty() );

 lem::UFString escaped( entry_name.c_str() );
 lem::sqlite_escape(escaped);

 lem::MemFormatter sql;
 sql.printf( "INSERT INTO omonym( entry_name, id_class ) VALUES ( '%us', %d )", escaped.c_str(), id_class );
 Execute(sql.string());

 return;
}


bool LexiconStorage_SQLITE::IsOmonym( const lem::UCString & entry_name, int id_class )
{
 LEM_CHECKIT_Z( id_class!=UNKNOWN );
 LEM_CHECKIT_Z( !entry_name.empty() );

 lem::UFString escaped( entry_name.c_str() );
 lem::sqlite_escape(escaped);

 lem::MemFormatter sql;
 sql.printf( "SELECT id FROM omonym WHERE entry_name='%us' AND id_class=%d", escaped.c_str(), id_class );
 return SelectInt(sql.string())!=-1;
}


LS_ResultSet* LexiconStorage_SQLITE::ListOmonyms()
{
 return ListByQuery( "SELECT entry_name, id_class FROM omonym" );
}

