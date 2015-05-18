#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/conversions.h>
#include <lem/mysql_helpers.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/CplxLeft.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/coordinate.h>
#include <lem/solarix/SG_Language.h>
#include <lem/solarix/StorageConnection_MySQL.h>
#include <lem/solarix/TransactionGuard_MySQL.h>
#include <lem/solarix/GramCoordUpdator_DB.h>
#include <lem/solarix/LS_ResultSet_MCollectCref.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/criterion.h>
#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_UnbreakableRule.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/tr_pattern_matchers.h>
#include <lem/solarix/WordEntrySetItem.h>
#include <lem/solarix/WordSetItem.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/ParadigmaForm.h>
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/EndingStat.h>
#include <lem/solarix/CollocFilter.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/TreeScorer.h>
#include <lem/solarix/MetaEntry.h>
#include <lem/solarix/WordAssociation.h>
#include <lem/solarix/PredicateTemplate.h>
#include <lem/solarix/SkipTokenRules.h>
#include <lem/solarix/PatternLinks.h>
#include <lem/solarix/TreeScorerGroupParams.h>
#include <lem/solarix/LexiconStorage_MySQL.h>

using namespace lem;
using namespace Solarix;

#define NEVER_RETURNS(x) return x;

namespace Solarix
{
 extern void Storage_Hex2Data( const lem::FString &str, unsigned char **bytes, int *size );
}

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

LexiconStorage_MySQL::LexiconStorage_MySQL(void)
{}


LexiconStorage_MySQL::LexiconStorage_MySQL( StorageConnection_MySQL *_cnx )
: cnx(_cnx)
{}


LexiconStorage_MySQL::~LexiconStorage_MySQL(void)
{
 Disconnect();
 return; 
}


void LexiconStorage_MySQL::Connect(void)
{
 return;
}


void LexiconStorage_MySQL::Disconnect(void)
{
 cnx->Release();
 return; 
}


void LexiconStorage_MySQL::BeginTx(void)
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->BeginTx();
 return;
}

void LexiconStorage_MySQL::CommitTx(void)
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->CommitTx();
 return;
}


void LexiconStorage_MySQL::RollBackTx(void)
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->RollbackTx();
 return;
}

TransactionGuard* LexiconStorage_MySQL::GetTxGuard(void)
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 return new TransactionGuard_MySQL(cnx);
}

LS_ResultSet* LexiconStorage_MySQL::ListByQuery( const lem::UFString &Select )
{
 return ListByQuery( lem::to_utf8(Select) );
}


LS_ResultSet* LexiconStorage_MySQL::ListByQuery( const lem::FString &Select )
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


lem::UFString LexiconStorage_MySQL::EncodeString( const lem::UFString &str ) const
{
 lem::UFString res(str);
 res.subst_all( L"\\", L"\\\\" );
 return res;
}


void LexiconStorage_MySQL::AddAuxFormType( int id, const lem::UCString &name )
{
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO aux_form_types( id, name ) VALUES ( %d, '%us' )", id, lem::to_upper(name).c_str() );
 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 return;
}


LS_ResultSet* LexiconStorage_MySQL::ListAuxFormTypes(void)
{
 lem::FString Select("SELECT id, name FROM aux_form_types ORDER BY id");
 return ListByQuery(Select);
}


int LexiconStorage_MySQL::AddAuxForm( int ekey, int iform, int aux_type, const lem::UFString &aux_data )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( iform!=UNKNOWN );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::UFString aux_data2(aux_data);
 lem::mysql_escape(aux_data2);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO aux_form( id_entry, iform, data_type, data_text )"
  " VALUES ( %d, %d, %d, '%us' )", ekey, iform, aux_type, aux_data2.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 int id = cnx->GetLastId();
 return id;
}


int LexiconStorage_MySQL::GetAuxForm( int ekey, int iform, int aux_type, lem::UFString &aux_data )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( iform!=UNKNOWN );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, data_text FROM aux_form "
  "WHERE id_entry=%d AND iform=%d AND data_type=%d", ekey, iform, aux_type ) );

 int id=UNKNOWN;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       id = lem::mysql_column_int(row,0);
       aux_data = lem::mysql_column_ufstring(row,1);
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 if( id==UNKNOWN )
  {
   aux_data.clear();
  }

 return id;
}


LS_ResultSet* LexiconStorage_MySQL::ListAuxForms(void)
{
 lem::FString Select("SELECT id, id_entry, iform, data_type, data_text FROM aux_form");
 return ListByQuery(Select);
}


LS_ResultSet* LexiconStorage_MySQL::ListAuxForms( int ekey, int iform )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( iform!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, data_type, data_text FROM aux_form "
  "WHERE id_entry=%d AND iform=%d", ekey, iform ) );
 return ListByQuery(Select);
}







int LexiconStorage_MySQL::AddAuxWord( const lem::UCString & src, int aux_type, const lem::UFString & aux_data )
{
 LEM_CHECKIT_Z( !src.empty() );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::UFString s2(src.c_str());
 mysql_escape(s2);

 lem::UFString aux_data2(aux_data);
 mysql_escape(aux_data2);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO aux_word( src, aux_type, res )"
  " VALUES ( '%us', %d, '%us' )", s2.c_str(), aux_type, aux_data2.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 return ExecuteAndReturnId(s);
}


int LexiconStorage_MySQL::GetAuxWord( const lem::UCString & src, int aux_type, lem::UFString & aux_data )
{
 LEM_CHECKIT_Z( !src.empty() );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::UFString s2(src.c_str());
 mysql_escape(s2);

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


LS_ResultSet* LexiconStorage_MySQL::ListAuxWords(void)
{
 return ListByQuery("SELECT id, src, aux_type, res FROM aux_word");
}

LS_ResultSet* LexiconStorage_MySQL::ListAuxWords( const lem::UCString & src )
{
 LEM_CHECKIT_Z( !src.empty() );

 lem::UFString s2(src.c_str());
 mysql_escape(s2);

 lem::MemFormatter mem;
 mem.printf( "SELECT id, aux_type, res FROM aux_word WHERE src='%us'", s2.c_str() );

 return ListByQuery(mem.string());
}








int LexiconStorage_MySQL::AddAuxEntryData( int ekey, int aux_type, const lem::UFString &aux_data )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::UFString aux_data2(aux_data);
 lem::mysql_escape(aux_data2);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO aux_entry_data( id_entry, data_type, data_text )"
  " VALUES ( %d, %d, '%us' )", ekey, aux_type, aux_data2.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 int id = cnx->GetLastId();
 return id;
}


int LexiconStorage_MySQL::GetAuxEntryData( int ekey, int aux_type, lem::UFString &aux_data )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( aux_type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, data_text FROM aux_entry_data "
  "WHERE id_entry=%d AND data_type=%d", ekey, aux_type ) );

 int id=UNKNOWN;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       id = lem::mysql_column_int(row,0);
       aux_data = lem::mysql_column_ufstring(row,1);
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 if( id==UNKNOWN )
  {
   aux_data.clear();
  }

 return id;
}


LS_ResultSet* LexiconStorage_MySQL::ListAuxEntryData(void)
{
 lem::FString Select("SELECT id, id_entry, data_type, data_text FROM aux_entry_data");
 return ListByQuery(Select);
}



LS_ResultSet* LexiconStorage_MySQL::ListAuxEntryData( int ekey )
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, data_type, data_text FROM aux_entry_data "
  "WHERE id_entry=%d", ekey ) );
 return ListByQuery(Select);
}



void LexiconStorage_MySQL::ReplaceEntryKey( int old_ekey, int new_ekey )
{
 LEM_CHECKIT_Z( old_ekey!=UNKNOWN );
 LEM_CHECKIT_Z( new_ekey!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "UPDATE aux_form SET id_entry=%d WHERE id_entry=%d", new_ekey, old_ekey );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 ms.printf( "UPDATE aux_entry_data SET id_entry=%d WHERE id_entry=%d", new_ekey, old_ekey );
 s = lem::to_utf8(ms.string());
 cnx->Execute(s);
 
 return;
}


void LexiconStorage_MySQL::CopyDatabase( const lem::Path & lexicon_db_path )
{
 LEM_STOPIT;
 return;
}



int LexiconStorage_MySQL::CountPhrases(void)
{
 return QueryInt( "SELECT count(*) FROM sg_tentry" );
}


LS_ResultSet* LexiconStorage_MySQL::ListPhrases(void)
{
 FString Select("SELECT te_id, te_text, te_utxt, te_id_language, te_id_class, te_syntax_flags FROM sg_tentry");
 return ListByQuery(Select);
}



int LexiconStorage_MySQL::FindPhrase( const lem::UFString &text, bool ignore_case )
{
 int te_id=UNKNOWN;

 UFString u(text);
 lem::mysql_escape(u);
 
 if( ignore_case )
  {
   // поиск без учета регистра

   MemFormatter ms;
   ms.printf( "SELECT te_id FROM sg_tentry WHERE te_utxt='%us'", to_upper(u).c_str() );
   FString Select=lem::to_utf8(ms.string());

   MySQLCnx *c = cnx->GetDb();
   #if defined LEM_THREADS
   lem::Process::CritSecLocker guard(&c->cs);
   #endif

   std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

   int ok = mysql_query( c->mysql, Select.c_str() );
   if( ok==0 )
    {
     MYSQL_RES *res = mysql_store_result( c->mysql );
     if( res!=NULL )
      {
       MYSQL_ROW row = mysql_fetch_row(res);
       if( row )
        {
         te_id = lem::mysql_column_int(row,0);
        }

       mysql_free_result(res);
      }
    }
   else
    {
     cnx->Error(Select);
    }
  }
 else
  {
   MemFormatter ms;
   ms.printf( "SELECT te_id FROM sg_tentry WHERE te_text='%us'", u.c_str() );
   FString Select=to_utf8(ms.string());

   MySQLCnx *c = cnx->GetDb();
   #if defined LEM_THREADS
   lem::Process::CritSecLocker guard(&c->cs);
   #endif

   std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

   int ok = mysql_query( c->mysql, Select.c_str() );
   if( ok==0 )
    {
     MYSQL_RES *res = mysql_store_result( c->mysql );
     if( res!=NULL )
      {
       MYSQL_ROW row = mysql_fetch_row(res);
       if( row )
        {
         te_id = lem::mysql_column_int(row,0);
        }

       mysql_free_result(res);
      }
    }
   else
    {
     cnx->Error(Select);
    }
  }

 return te_id;
}


LS_ResultSet* LexiconStorage_MySQL::ListPhrasesWithPrefix( const lem::UFString &mask, bool ignore_case )
{
 UFString u(mask);
 lem::mysql_escape(u);
 
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
   MemFormatter ms;
   ms.printf( "SELECT te_id FROM sg_tentry WHERE te_text LIKE '%us%%'", u.c_str() );
   FString Select=to_utf8(ms.string());
   return ListByQuery(Select);
  }
}


bool LexiconStorage_MySQL::GetPhrase( int id_phrase, SG_Phrase &phrase )
{
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );

 bool found=false;

 FString Select( lem::format_str(
  "SELECT te_text, Coalesce(te_id_language,-1), Coalesce(te_id_class,-1), Coalesce(te_syntax_flags,0)"
  " FROM sg_tentry"
  " WHERE te_id=%d", id_phrase ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       phrase.id = id_phrase; 
       phrase.text = lem::mysql_column_ufstring(row,0);
       phrase.id_language = lem::mysql_column_int(row,1);
       phrase.id_class = lem::mysql_column_int(row,2);
       phrase.syntax_flags = lem::mysql_column_int(row,3);
       found = true;
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return found;
}


int LexiconStorage_MySQL::AddPhrase( SG_Phrase &info )
{
 UFString txt(info.GetText());
 lem::mysql_escape(txt);

 UFString utxt( to_upper(txt) );

 MemFormatter mf2;
 mf2.printf( "INSERT INTO sg_tentry( te_text, te_utxt, te_id_language, te_id_class, te_syntax_flags )"
 " VALUES ( '%us', '%us', %s, %s, %s )", txt.c_str(), utxt.c_str(),
  null_if_minus8(info.id_language).c_str(),
  null_if_minus8(info.id_class).c_str(),
  null_if_minus8(info.syntax_flags).c_str() );

 lem::FString s=lem::to_utf8(mf2.string());

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 int id = cnx->GetLastId();
 info.id = id;
 return id;
}


void LexiconStorage_MySQL::DeletePhrase( int id )
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


void LexiconStorage_MySQL::UpdatePhrase( const SG_Phrase &te )
{
 lem::UFString uutf8(te.text);
 lem::mysql_escape(uutf8);

 lem::UFString uuutf8(to_upper(uutf8));

 MemFormatter mf;
 mf.printf( "UPDATE sg_tentry SET te_text='%us', te_utxt='%us', te_id_language=%s, te_id_class=%s, te_syntax_flags=%d"
            " WHERE te_id=%d", uutf8.c_str(), uuutf8.c_str(),
            null_if_minus8(te.id_language).c_str(), null_if_minus8(te.id_class).c_str(), 
            te.GetSyntaxFlags(), te.id );
 lem::FString s=lem::to_utf8(mf.string());

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 return;
}




LS_ResultSet* LexiconStorage_MySQL::ListPhraseNotes( int id_phrase )
{
 FString Select( lem::format_str(
  "SELECT tn_id, tn_type, tn_data"
  " FROM tnotes"
  " WHERE tn_te_id=%d", id_phrase ) );

 return ListByQuery(Select);
}


bool LexiconStorage_MySQL::GetPhraseNote( int id, SG_PhraseNote &note )
{
 bool found=false;

 FString Select( lem::format_str(
    "SELECT tn_type, tn_data"
    " FROM tnotes"
    " WHERE tn_id=%d", id ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       note.type = lem::mysql_column_int(row,0);
       note.data = lem::mysql_column_ufstring(row,1);
       note.tn_id = id;
       found = true; 
      }

     mysql_free_result(res);
    }

   return found;
  }
 else
  {
   cnx->Error(Select);
   NEVER_RETURNS(NULL);
  }
}


int LexiconStorage_MySQL::GetPhraseNote( int id_entry, int note_type, SG_PhraseNote &note )
{
 FString Select( lem::format_str(
    "SELECT tn_id, tn_data"
    " FROM tnotes"
    " WHERE tn_te_id=%d AND tn_type=%d", id_entry, note_type ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       note.tn_id = lem::mysql_column_int(row,0);
       note.data = lem::mysql_column_ufstring(row,1);
      }

     mysql_free_result(res);
    }

   return note.tn_id;
  }
 else
  {
   cnx->Error(Select);
   NEVER_RETURNS(NULL);
  }
}



int LexiconStorage_MySQL::FindPhraseNote( const lem::UFString &text, int type, int &te_id )
{
 int tn_id=UNKNOWN;
 te_id=UNKNOWN;

 UFString u(text);
 lem::mysql_escape(u);
  
 MemFormatter mf;
 mf.printf( "SELECT tn_id, tn_te_id"
            " FROM tnotes"
            " WHERE tn_data='%us' AND tn_type=%d", u.c_str(), type );
 FString Select=to_utf8(mf.string());

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       tn_id = lem::mysql_column_int(row,0);
       te_id = lem::mysql_column_int(row,1);
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return tn_id;
}


LS_ResultSet* LexiconStorage_MySQL::ListCplxLeft(void)
{
 FString Select("SELECT cl_id, cl_headword, cl_minlen, cl_maxlen FROM cplx_left");
 return ListByQuery(Select);
}



int LexiconStorage_MySQL::GetCplxLeft( const lem::UCString &headword, CplxLeft &info )
{
 LEM_CHECKIT_Z( !headword.empty() );

 int cl_id=UNKNOWN;

 UFString w16(headword.c_str());
 w16.to_upper();
 lem::mysql_escape(w16);

 FString uutf8(lem::to_utf8( w16 ) );

 FString Select( lem::format_str( "SELECT cl_id, cl_minlen, cl_maxlen FROM cplx_left WHERE cl_headword='%s'", to_utf8(w16).c_str() ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       cl_id = lem::mysql_column_int(row,0);
       const int cl_minlen = lem::mysql_column_int(row,1);
       const int cl_maxlen = lem::mysql_column_int(row,2);
       info.headword = headword;
       info.minlen = cl_minlen;
       info.maxlen = cl_maxlen;
      }
     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return cl_id;
}




int LexiconStorage_MySQL::StoreCplxLeft( const lem::UCString &headword, int minlen, int maxlen )
{
 LEM_CHECKIT_Z( !headword.empty() );
 LEM_CHECKIT_Z( minlen>0 );
 LEM_CHECKIT_Z( maxlen>=minlen && maxlen<100 );

 UFString w16(headword.c_str());
 w16.to_upper();
 lem::mysql_escape(w16);

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

   MySQLCnx *c = cnx->GetDb();
   #if defined LEM_THREADS
   lem::Process::CritSecLocker guard(&c->cs);
   #endif

   cnx->Execute(s);
  }
 else
  {
   // либо вносим новую запись
   lem::FString s( lem::format_str( "INSERT INTO cplx_left( cl_headword, cl_minlen, cl_maxlen )"
        " VALUES ( '%s', %d, %d )", uutf8.c_str(), minlen, maxlen ) );
   cnx->Execute(s);

   MySQLCnx *c = cnx->GetDb();
   #if defined LEM_THREADS
   lem::Process::CritSecLocker guard(&c->cs);
   #endif

   cl_id = cnx->GetLastId();
  }

 // Возвращаем ID измененной или добавленной записи.
 return cl_id;
}



void LexiconStorage_MySQL::ClearCplxLeft( const lem::UCString &headword )
{
 LEM_CHECKIT_Z( !headword.empty() );

 UFString w16(headword.c_str());
 w16.to_upper();
 lem::mysql_escape(w16);

 lem::MemFormatter ms;
 ms.printf( "DELETE FROM cplx_left WHERE cl_headword='%us'", w16.c_str() );
 lem::FString s( lem::to_utf8(ms.string()) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 return;
}


int LexiconStorage_MySQL::AddPhraseNote( int id_phrase, int type, const lem::UFString &text )
{
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );
 LEM_CHECKIT_Z( type!=UNKNOWN );

 UFString a(text);
 lem::mysql_escape(a);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO tnotes( tn_te_id, tn_type, tn_format, tn_data )"
      " VALUES ( %d, %d, 0, '%us' )", id_phrase, type, a.c_str() );
 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 const int id = cnx->GetLastId();
 return id;
}


void LexiconStorage_MySQL::DeletePhraseNotes( int id_phrase )
{
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );
 lem::FString s( lem::format_str( "DELETE FROM tnotes WHERE tn_te_id=%d", id_phrase ) );
 Execute(s);
 return;
}


void LexiconStorage_MySQL::DeletePhraseNote( int id_note )
{
 LEM_CHECKIT_Z( id_note!=UNKNOWN );
 lem::FString s( lem::format_str( "DELETE FROM tnotes WHERE tn_id=%d", id_note ) );
 Execute(s);
 return;
}



int LexiconStorage_MySQL::CountPartsOfSpeech(void)
{
 return QueryInt( "SELECT count(*) FROM sg_class" );
}


namespace
{
 inline bool char_one_of( wchar_t c, wchar_t x, wchar_t y, wchar_t z )
 { return c==x || c==y || c==z; }
}


int LexiconStorage_MySQL::FindPartOfSpeech( const lem::UCString &name )
{
 // если в проверяемом имени есть символы ', "" или пробел - сразу возвращает false.
 for( int i=0; i<name.length(); ++i )
  if( char_one_of( name[i], L'"', L'\'', L' ' ) )
   return UNKNOWN;

 UCString uname(to_upper(name));

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs_partofspeech);
 #endif

 if( partofspeech_map.empty() )
  {
   FString Select("SELECT id, name, Coalesce(name_aliase,'') FROM sg_class");

   MySQLCnx *c = cnx->GetDb();
   #if defined LEM_THREADS
   lem::Process::CritSecLocker guard(&c->cs);
   #endif

   std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

   int ok = mysql_query( c->mysql, Select.c_str() );
   if( ok==0 )
    {
     MYSQL_RES *res = mysql_store_result( c->mysql );
     if( res!=NULL )
      {
       MYSQL_ROW row=NULL;

       while( (row=mysql_fetch_row(res))!=NULL )
        {
         const int id = lem::mysql_column_int(row,0);
         lem::UCString name = lem::mysql_column_ucstring(row,1);
         lem::UCString name2 = lem::mysql_column_ucstring(row,2);

         partofspeech_map.insert( std::make_pair( lem::to_upper(name), id ) );

         if( !name2.empty() )
          partofspeech_map.insert( std::make_pair( lem::to_upper(name2), id ) );
        }

       mysql_free_result(res);
      }
    }
   else
    {
     cnx->Error(Select);
     NEVER_RETURNS(NULL);
    }
  }

 std::map<lem::UCString,int>::const_iterator it = partofspeech_map.find(uname);
 return it==partofspeech_map.end() ? UNKNOWN : it->second;
}


int LexiconStorage_MySQL::AddPartOfSpeech( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 lem::UFString s( to_upper(name).c_str());
 lem::mysql_escape(s);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_class( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard1(&c->cs);
 #endif

 cnx->Execute(as);
 int id = cnx->GetLastId();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard2(&cs_partofspeech);
 #endif
 partofspeech_map.insert( std::make_pair( lem::to_upper(name), id ) );

 return id;
}


int LexiconStorage_MySQL::AddPartOfSpeech( const Solarix::SG_Class &cls )
{
 lem::UFString s( lem::to_upper(cls.GetName()).c_str());
 lem::mysql_escape(s);

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

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard1(&c->cs);
 #endif

 cnx->Execute(as);
 const int id = cnx->GetLastId();
 StoreClassInternals(id,cls);

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard2(&cs_partofspeech);
 #endif
 partofspeech_map.insert( std::make_pair( lem::to_upper(cls.GetName()), id ) );
 if( !alist.empty() )
  {
   partofspeech_map.insert( std::make_pair( lem::to_upper(alist[0]), id ) );
  }

 return id;
}


void LexiconStorage_MySQL::StorePartOfSpeech( int id, const SG_Class &cls )
{
 lem::UFString s( lem::to_upper(cls.GetName()).c_str() );
 lem::mysql_escape(s);

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

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(as);
 StoreClassInternals( id, cls );

 return;
}


void LexiconStorage_MySQL::StoreClassInternals( int id, const SG_Class &cls )
{
 lem::MemFormatter ms;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 for( lem::Container::size_type k=0; k<cls.attrs().size(); ++k )   
  {
   const GramCoordAdr &atr = cls.attrs()[k];

   ms.printf(
             "INSERT INTO sg_class_coord( id_class, id_coord, coord_type ) VALUES( %d, %d, 0 );\n"
             , id
             , atr.GetIndex()
           );

   lem::FString s(lem::to_utf8(ms.string()));
   cnx->Execute(s);
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
   cnx->Execute(s);
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
   cnx->Execute(s);
  }

 return;
}

bool LexiconStorage_MySQL::GetPartOfSpeech( int id, SG_Class &cls )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT name, name_aliase, Coalesce(weight,0), Coalesce(id_lang,-1), closed_class"
  " FROM sg_class"
  " WHERE id=%d", id ) );

 bool found=false;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

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

       UCString aliase = lem::mysql_column_ucstring(row,1);
       if( !aliase.empty() )
        cls.aliases.Add(aliase);

       cls.value = lem::mysql_column_int(row,2);
       cls.id_lang = lem::mysql_column_int(row,3);
       cls.closed_class = lem::mysql_column_int(row,4)==1;
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

   lem::FString Select2(lem::format_str( "SELECT id_coord, coord_type FROM sg_class_coord "
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
          case 2: cls.tag_index.push_back( id_coord ); break;
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
   else
    {
     cnx->Error(Select2);
    }
  }

 return found;
}



LS_ResultSet* LexiconStorage_MySQL::ListPartsOfSpeech(void)
{
 lem::FString Select("SELECT id FROM sg_class ORDER BY id");
 return ListByQuery(Select);
}



int LexiconStorage_MySQL::CountCoords(void)
{
 return QueryInt( "SELECT count(*) FROM sg_coord" );
}


bool LexiconStorage_MySQL::GetCoord( int id, GramCoord &coord )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );
 lem::FString Select( lem::format_str("SELECT name, bistable FROM sg_coord WHERE id=%d", id) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

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
         lem::FString Select2( lem::format_str("SELECT id, id_parent, name, weight FROM sg_state WHERE id_coord=%d ORDER BY id_parent, id", id ) );

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
               const int id_parent = lem::mysql_column_int(row2,1);
               UCString state_name = lem::mysql_column_ucstring(row2,2);
               const int weight = lem::mysql_column_int(row2,3);

               if( id_state==id_parent )
                {
                 GramCoordState s(state_name,weight);

                 // это главное состояние в группе 
                 if( coord.GetTotalStates()!=id_state )
                  {
                   LEM_STOPIT;
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
 else
  {
   cnx->Error(Select);
   NEVER_RETURNS(NULL);
  }
}


LS_ResultSet* LexiconStorage_MySQL::ListCoords(void)
{
 lem::FString Select("SELECT id FROM sg_coord ORDER BY id");
 return ListByQuery(Select);
}


int LexiconStorage_MySQL::FindCoord( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 MemFormatter ms;
 ms.printf( "SELECT id FROM sg_coord WHERE Upper(name)='%us'", to_upper(name).c_str() );
 FString Select=lem::to_utf8(ms.string());

 int id=UNKNOWN;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );

   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       id = lem::mysql_column_int(row,0);
      }

     mysql_free_result(res);
    }

   return id;
  }
 else
  {
   cnx->Error(Select);
   NEVER_RETURNS(NULL);
  }
}


int LexiconStorage_MySQL::AddCoord( const lem::UCString &coord )
{
 lem::UFString s( to_upper(coord).c_str() );
 lem::mysql_escape(s);

 lem::MemFormatter ms;
 if( coord.eqi(L"net") )
  ms.printf( "INSERT INTO sg_coord( id, name ) VALUES ( 0, '%us' )", s.c_str() );
 else
  ms.printf( "INSERT INTO sg_coord( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(as);
 int id = cnx->GetLastId();
 return id;
}


int LexiconStorage_MySQL::AddCoord( Solarix::GramCoord &coord )
{
 UFString s( to_upper(coord.GetName().front()).c_str() );
 lem::mysql_escape(s);

 int bistable = coord.IsBistable() ? 1 : 0; 
 
 lem::MemFormatter ms;
 if( coord.GetName().front().eqi(L"net") )
  ms.printf( "INSERT INTO sg_coord( id, name, bistable ) VALUES ( 0, '%us', %d )", s.c_str(), bistable );
 else
  ms.printf( "INSERT INTO sg_coord( name, bistable ) VALUES ( '%us', %d )", s.c_str(), bistable );

 lem::FString as(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(as);
 int id = cnx->GetLastId();

 StoreCoordStates(id,coord);

 if( coord.updator.IsNull() )
  coord.updator = new GramCoordUpdator_DB(this);

 coord.id = id;

 return id;
}


void LexiconStorage_MySQL::StoreCoord( int id, Solarix::GramCoord &coord )
{
 lem::UFString s( lem::to_upper(coord.GetName().front()).c_str() );
 lem::mysql_escape(s);

 int bistable = coord.IsBistable() ? 1 : 0; 
 
 lem::MemFormatter ms;
 ms.printf( "UPDATE sg_coord SET name='%us', bistable=%d WHERE id=%d", s.c_str(), bistable, id );

 lem::FString as(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(as);

 lem::FString del( lem::format_str( "DELETE FROM sg_state WHERE id_coord=%d", id ) );
 cnx->Execute(as);

 StoreCoordStates(id,coord);

 if( coord.updator.IsNull() )
  coord.updator = new GramCoordUpdator_DB(this);

 return;
}




void LexiconStorage_MySQL::StoreCoordStates( int id_coord, const Solarix::GramCoord &coord )
{
 LEM_CHECKIT_Z( id_coord>=0 );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::MemFormatter ms;
 const int n=coord.GetTotalStates();
 for( int i=0; i<n; ++i )
  {
   lem::UFString s(coord.GetStateName(i).c_str());
   lem::mysql_escape(s);

   const int id_state = i;

   const int igroup = coord.GetSubgroup(id_state);
   lem::IntCollect ix = coord.GetSubgroupIndeces(igroup);
   const int id_parent = ix.front();

   const int weight = coord.GetTopState(igroup).GetWeight();
   
   ms.printf( "INSERT INTO sg_state( id, name, id_coord, id_parent, weight ) VALUES ( %d, '%us', %d, %d, %d )"
    , id_state, s.c_str(), id_coord, id_parent, weight );

   lem::FString as(lem::to_utf8(ms.string()));
   cnx->Execute(as);
  }

 return;
}



void LexiconStorage_MySQL::LoadAllLanguages(void)
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs_languages);
 #endif

 if( language_ids.empty() )
  {
   lem::FString Select("SELECT id FROM sg_language ORDER BY id");

   MySQLCnx *c = cnx->GetDb();
   #if defined LEM_THREADS
   lem::Process::CritSecLocker guard(&c->cs);
   #endif

   std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

   int ok = mysql_query( c->mysql, Select.c_str() );
   if( ok==0 )
    {
     MYSQL_RES *res = mysql_store_result( c->mysql );
     if( res!=NULL )
      {
       MYSQL_ROW row=NULL;
       while( (row = mysql_fetch_row(res))!=NULL )
        {
         const int id = lem::mysql_column_int(row,0);
         language_ids.push_back(id);
        }

       mysql_free_result(res);
      }
    }
   else
    {
     cnx->Error(Select);
     return;
    }
  }

 return;
}



int LexiconStorage_MySQL::CountLanguages(void)
{
 LoadAllLanguages();
 return CastSizeToInt(language_ids.size());
}


LS_ResultSet* LexiconStorage_MySQL::ListLanguages(void)
{
 LoadAllLanguages();
 return new LS_ResultSet_MCollectCref(language_ids);
}

int LexiconStorage_MySQL::QueryInt( const lem::UFString & sql )
{
 return QueryInt( lem::to_utf8(sql) );
}


int LexiconStorage_MySQL::QueryInt( const lem::FString & sql )
{
 LEM_CHECKIT_Z( !sql.empty() );

 int res_int=UNKNOWN;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, sql.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       res_int = lem::mysql_column_int(row,0);
      }

     mysql_free_result(res);
    }

   return res_int;
  }
 else
  {
   cnx->Error(sql);
   NEVER_RETURNS(-1);
  }
}


int LexiconStorage_MySQL::FindLanguage( const lem::UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );
 MemFormatter ms;
 ms.printf( "SELECT id FROM sg_language WHERE name='%us'", to_upper(name).c_str() );
 FString Select=lem::to_utf8(ms.string());
 return QueryInt(Select);
}


int LexiconStorage_MySQL::AddLanguage( SG_Language &lang )
{
 UFString s( lem::to_upper(lang.GetName()).c_str() );
 lem::mysql_escape(s);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_language( name ) VALUES ( '%us' )", s.c_str() );

 lem::FString as(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(as);

 const int id = cnx->GetLastId();
 language_ids.push_back(id);

 lang.id = id;
 StoreLanguageInternals(lang);

 return id;
}


bool LexiconStorage_MySQL::GetLanguage( int id, SG_Language &lang )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );
 lem::FString Select( lem::format_str("SELECT name FROM sg_language WHERE id=%d", id) );

 bool ok=false;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lang.id = id;
       lang.name = lem::mysql_column_ucstring(row,0);

       // запрос составлен так, чтобы сначала был извлечен основной алфавит
       lem::FString Select2( lem::format_str("SELECT id_alphabet FROM lang_alphabet WHERE id_language=%d ORDER BY ordering", id ) );
       rc = mysql_query( c->mysql, Select2.c_str() );
       if( rc==0 )
        {
         MYSQL_RES *res2 = mysql_store_result(c->mysql);
         if( res2!=NULL )
          {
           MYSQL_ROW row2;
           while( (row2 = mysql_fetch_row(res2))!=NULL )
            {
             const int id_alphabet = lem::mysql_column_int(row2,0);
             lang.alphabet.push_back(id_alphabet);
            }

           mysql_free_result(res2);
          }
        }
       else 
        {
         cnx->Error(Select2);
        }


       lem::FString Select3( lem::format_str("SELECT id_state, id_language2 FROM lang_link WHERE id_language=%d", id ) );
       rc = mysql_query( c->mysql, Select3.c_str() );
       if( rc==0 )
        {
         MYSQL_RES *res3 = mysql_store_result(c->mysql);
         if( res3!=NULL )
          {
           MYSQL_ROW row3;
           while( (row3 = mysql_fetch_row(res3))!=NULL )
            {
             const int id_state = lem::mysql_column_int(row3,0);
             const int id_lang2 = lem::mysql_column_int(row3,1);
             lang.lang_links.push_back( std::make_pair( Tree_Link(id_state), id_lang2 ) );
            }

           mysql_free_result(res3);
          }
        }
       else 
        {
         cnx->Error(Select3);
        }


       lem::FString Select4( lem::format_str("SELECT param_name, param_value, id, ordering"
                                             " FROM lang_param WHERE id_language=%d"
                                             " ORDER BY param_name, id, ordering", id ) );
       rc = mysql_query( c->mysql, Select4.c_str() );
       if( rc==0 )
        {
         MYSQL_RES *res4 = mysql_store_result(c->mysql);
         if( res4!=NULL )
          {
           MYSQL_ROW row4;
           while( (row4 = mysql_fetch_row(res4))!=NULL )
            {
             UCString pname = lem::mysql_column_ucstring(row4,0);
             UFString pval = lem::mysql_column_ufstring(row4,1);
             int ord = lem::mysql_column_int(row4,3);
        
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

           mysql_free_result(res4);
          }
        }
       else 
        {
         cnx->Error(Select4);
        }

       ok=true;
      }

     mysql_free_result(res);
    }

   return ok;
  }
 else
  {
   cnx->Error(Select);
   NEVER_RETURNS(NULL);
  }
}


void LexiconStorage_MySQL::StoreLanguage( const SG_Language &lang )
{
 UFString s( lem::to_upper(lang.GetName()).c_str() );
 lem::mysql_escape(s);

 lem::MemFormatter ms;
 ms.printf( "UPDATE sg_language SET name='%us' WHERE id=%d", s.c_str(), lang.id );
 lem::FString as(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(as);
 StoreLanguageInternals(lang);
 return;
}


void LexiconStorage_MySQL::StoreLanguageInternals( const SG_Language &lang )
{
 lem::MemFormatter ms;

 const int id = lang.id;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 for( lem::Container::size_type i=0; i<lang.alphabet.size(); ++i )
  {
   const int id_alphabet = lang.alphabet[i];
   
   ms.printf( "INSERT INTO lang_alphabet( id_language, id_alphabet, ordering ) VALUES ( %d, %d, %d )" 
    , id, id_alphabet, CastSizeToInt(i) );

   lem::FString as(lem::to_utf8(ms.string()));
   cnx->Execute(as);
  } 

 for( lem::Container::size_type i=0; i<lang.lang_links.size(); ++i )
  {
   const int id_state = lang.lang_links[i].first.GetState();
   const int id_lang2 = lang.lang_links[i].second;
   
   ms.printf( "INSERT INTO lang_link( id_language, id_state, id_language2 )"
              " VALUES ( %d, %d, %d )", id, id_state, id_lang2 );

   lem::FString as(lem::to_utf8(ms.string()));
   cnx->Execute(as);
  }
 
 for( lem::Container::size_type i=0; i<lang.params.size(); ++i )
  {
   const SG_LanguageParam &p = *lang.params[i];
   lem::UFString pname(p.name.c_str());
   lem::mysql_escape(pname);

   for( lem::Container::size_type j=0; j<p.values.size(); ++j )
    {
     lem::UFString pval(p.values[j].c_str());
     lem::mysql_escape(pval);
     pval.subst_all( L"\r", L"\\r" );
     pval.subst_all( L"\n", L"\\n" );
     pval.subst_all( L"\t", L"\\t" );
   
     ms.printf( "INSERT INTO lang_param( id_language, param_name, param_value, ordering )"
                " VALUES ( %d, '%us', '%us', %d )", id, pname.c_str(), pval.c_str(), CastSizeToInt(j) );

     lem::FString as(lem::to_utf8(ms.string()));
     cnx->Execute(as);
    }
  } 

 return;
}

void LexiconStorage_MySQL::CreateSchema(void)
{
}


int LexiconStorage_MySQL::FindCriterion( const lem::UCString & name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM sg_criterion WHERE Upper(name)='%us'", lem::to_upper(name).c_str() );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 return lem::mysql_select_int( c->mysql, lem::to_utf8(mem.string()).c_str() );
}

int LexiconStorage_MySQL::StoreCriterion( const Criterion &x )
{
 LEM_STOPIT;
 return -1;
}

Criterion* LexiconStorage_MySQL::GetCriterion( int id )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT name, strval FROM sg_criterion WHERE id=%d", id );
 lem::FString Select(lem::to_utf8(mem.string()));

 Criterion *a = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

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

LS_ResultSet* LexiconStorage_MySQL::EnumerateCriteria(void)
{
 lem::FString Select("SELECT id FROM sg_criterion");
 return ListByQuery(Select);
}












LS_ResultSet* LexiconStorage_MySQL::ListCropRules( int id_language )
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



LA_CropRule* LexiconStorage_MySQL::GetPreprocessorCropRule( int id )
{
 lem::FString Select(lem::format_str( "SELECT name, id_language, is_prefix, is_affix, "
  "r_condition, r_result, is_regex, case_sensitive, id_src, rel FROM crop_rule WHERE id=%d", id ) );

 LA_CropRule *rule = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UCString name = lem::mysql_column_ucstring(row,0);
       const int id_language = lem::mysql_column_int(row,1);
       const bool is_prefix = lem::mysql_column_int(row,2)==1;
       const bool is_affix = lem::mysql_column_int(row,3)==1;
       lem::UFString condition = lem::mysql_column_ufstring(row,4);
       lem::UFString result = lem::mysql_column_ufstring(row,5);
       const bool is_regex = lem::mysql_column_int(row,6)==1;
       const bool case_sensitive = lem::mysql_column_int(row,7)==1;
       const int id_src = lem::mysql_column_int(row,8);
       const int rel = lem::mysql_column_int(row,9);
  
       rule = new LA_CropRule( id, name, id_language, is_prefix, is_affix, is_regex, case_sensitive, condition, result, id_src, lem::Real1(rel) );
      }

     mysql_free_result(res);
     return rule;
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




void LexiconStorage_MySQL::StorePreprocessorCropRule( LA_CropRule *rule )
{
 lem::UFString condition(rule->GetCondition());
 mysql_escape(condition);

 lem::UFString result(rule->GetResult());
 mysql_escape(result);

 lem::MemFormatter q;
 q.printf( "INSERT INTO crop_rule( name, id_language, is_prefix, is_affix,"
           " r_condition, r_result, is_regex, case_sensitive, id_src, rel ) VALUES ( '%us', %d, %d, %d, '%us', '%us', %d, %d, %d, %d )",
           lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
           rule->IsPrefix() ? 1 : 0, rule->IsAffix() ? 1 : 0,
           condition.c_str(), result.c_str(), rule->IsRegex(), rule->IsCaseSensitive(), rule->GetSourceLocation(), rule->GetRel().GetInt() );
 
 lem::FString s(lem::to_utf8(q.string()));
 int id = ExecuteAndReturnId(s);
 rule->SetId(id);
 return;
}


void LexiconStorage_MySQL::DeletePreprocessorRules(void)
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





int LexiconStorage_MySQL::FindCropRule( const lem::UCString &rule_name )
{
 LEM_CHECKIT_Z( !rule_name.empty() );
 MemFormatter ms;
 ms.printf( "SELECT id FROM crop_rule WHERE name='%us'", to_upper(rule_name).c_str() );
 FString Select=lem::to_utf8(ms.string());
 return QueryInt(Select);
}



LS_ResultSet* LexiconStorage_MySQL::ListRecognitionRules( int id_language, bool including_word_matchers )
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



LS_ResultSet* LexiconStorage_MySQL::ListRecognitionRulesForWord( int id_language, const lem::UCString & word )
{
 lem::UFString str_word(word.c_str());
 mysql_escape( str_word );

 lem::MemFormatter mem;

 if( id_language==ANY_STATE )
  mem.printf( "SELECT id FROM recog_rule WHERE word='%us'", str_word.c_str() );
 else
  mem.printf( "SELECT id FROM recog_rule WHERE word='%us' AND id_language=%d", str_word.c_str(), id_language );

 return ListByQuery(mem.string());
}



LA_RecognitionRule* LexiconStorage_MySQL::GetRecognitionRule( int id )
{
 lem::FString Select(lem::format_str( "SELECT name, id_language, is_regex, is_prefix, is_affix, "
  "r_condition, id_entry, rel, coords, is_syllab, id_src, case_sensitive FROM recog_rule WHERE id=%d", id ) );


 LA_RecognitionRule *rule = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UCString name = lem::mysql_column_ucstring(row,0);
       const int id_language = lem::mysql_column_int(row,1);
       const bool is_regex = lem::mysql_column_int(row,2)==1;
       const bool is_prefix = lem::mysql_column_int(row,3)==1;
       const bool is_affix = lem::mysql_column_int(row,4)==1;
       lem::UFString condition = lem::mysql_column_ufstring(row,5);
       const int ekey = lem::mysql_column_int(row,6);
       const lem::Real1 rel = lem::Real1(lem::mysql_column_int(row,7));
       lem::UFString str_coords = lem::mysql_column_ufstring(row,8);
       const bool is_syllab = lem::mysql_column_int(row,9)==1;
       const int id_src = lem::mysql_column_int(row,10);
       const bool case_sensitive = lem::mysql_column_int(row,11)==1;
    
       Solarix::CP_Array coords;
       coords.Parse(str_coords);
    
       rule = new LA_RecognitionRule( id, name, case_sensitive, id_language, is_syllab, is_regex, is_prefix,
        is_affix, condition, ekey, rel, coords, id_src );
      }

     mysql_free_result(res);
     return rule;
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


void LexiconStorage_MySQL::StoreRecognitionRule( LA_RecognitionRule *rule )
{
 lem::UFString condition(rule->GetCondition());
 mysql_escape(condition);

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
   mysql_escape( word );
   word.dress( L'\'' );
  }
 else
  {
   word = L"NULL";
  }

 lem::MemFormatter q;
 q.printf( "INSERT INTO recog_rule( name, id_language, is_syllab, is_regex, is_prefix, is_affix,"
           " r_condition, id_entry, rel, coords, id_src,"
           " word, case_sensitive ) VALUES ( '%us', %d, %d, %d, %d, %d, '%us', %d, %d, '%us', %d, %us, %d )",
           lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
           rule->IsSyllab() ? 1 : 0,
           rule->IsRegex() ? 1 : 0,
           rule->IsPrefix() ? 1 : 0,
           rule->IsAffix() ? 1 : 0,
           condition.c_str(), rule->GetEntryKey(), rule->GetRel().GetInt(), coords.c_str(), rule->GetSourceLocation(),
           word.c_str(),
           case_sensitive
          );
 
 lem::FString s(lem::to_utf8(q.string()));
 int id = ExecuteAndReturnId(s);
 rule->SetId(id);
 return;
}


void LexiconStorage_MySQL::DeleteRecognitionRules(void)
{
 lem::FString sql("DELETE FROM recog_rule");
 Execute(sql);
 return;
}


int LexiconStorage_MySQL::FindRecognitionRule( const lem::UCString &rule_name )
{
 LEM_CHECKIT_Z( !rule_name.empty() );
 MemFormatter ms;
 ms.printf( "SELECT id FROM recog_rule WHERE name='%us'", to_upper(rule_name).c_str() );
 FString Select=lem::to_utf8(ms.string());
 return QueryInt(Select);
}


LS_ResultSet* LexiconStorage_MySQL::ListPhoneticRules( int id_language )
{
 lem::FString Select;

 if( id_language==ANY_STATE )
  Select = "SELECT id FROM ph_rule ORDER BY id";
 else
  Select = lem::format_str("SELECT id FROM ph_rule WHERE id_language=%d ORDER BY id",id_language); 

 return ListByQuery(Select);
}

LA_PhoneticRule* LexiconStorage_MySQL::GetPhoneticRule( int id )
{
 lem::FString Select(lem::format_str( "SELECT name, id_language, is_prefix, is_affix, "
  "r_condition, r_result, rel, id_src FROM ph_rule WHERE id=%d", id ) );

 LA_PhoneticRule *rule = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UCString name = lem::mysql_column_ucstring(row,0);
       const int id_language = lem::mysql_column_int(row,1);
       const bool is_prefix = lem::mysql_column_int(row,2)==1;
       const bool is_affix = lem::mysql_column_int(row,3)==1;
       lem::UFString condition = lem::mysql_column_ufstring(row,4);
       lem::UFString result = lem::mysql_column_ufstring(row,5);
       const lem::Real1 rel = lem::Real1(lem::mysql_column_int(row,6));
       const int id_src = lem::mysql_column_int(row,7);
    
       rule = new LA_PhoneticRule( id, name, id_language, is_prefix, is_affix, condition.c_str(), result.c_str(), rel, id_src );
      }

     mysql_free_result(res);
     return rule;
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


void LexiconStorage_MySQL::StorePhoneticRule( LA_PhoneticRule *rule )
{
 lem::UFString condition(rule->GetCondition().GetContext().c_str());
 lem::mysql_escape(condition);

 lem::UFString result(rule->GetResult().GetContext().c_str());
 lem::mysql_escape(result);

 lem::MemFormatter q;
 q.printf( "INSERT INTO ph_rule( name, id_language, is_prefix, is_affix,"
           " r_condition, r_result, rel, id_src ) VALUES ( '%us', %d, %d, %d, '%us', '%us', %d, %d )",
           lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
           rule->IsPrefix() ? 1 : 0, rule->IsAffix() ? 1 : 0,
           condition.c_str(), result.c_str(), rule->GetVal().GetInt(), rule->GetSourceLocation() );
 
 lem::FString s(lem::to_utf8(q.string()));

 int id = ExecuteAndReturnId(s);
 rule->SetId(id);
 return;
}


void LexiconStorage_MySQL::DeletePhoneticRules(void)
{
 lem::FString sql("DELETE FROM ph_rule");
 Execute(sql);
 return;
}


int LexiconStorage_MySQL::FindPhoneticRule( const lem::UCString &rule_name )
{
 LEM_CHECKIT_Z( !rule_name.empty() );
 MemFormatter ms;
 ms.printf( "SELECT id FROM ph_rule WHERE name='%us'", to_upper(rule_name).c_str() );
 FString Select=lem::to_utf8(ms.string());
 return QueryInt(Select);
}


LS_ResultSet* LexiconStorage_MySQL::ListWordEntrySet(void)
{
 return ListByQuery("SELECT id FROM word_entry_set ORDER BY id");
}

int LexiconStorage_MySQL::FindWordEntrySet( const lem::UCString &set_name )
{
 if(
    set_name.front()==L'\'' ||
    set_name.front()==L'"' ||
    set_name.back()==L'\'' ||
    set_name.back()==L'"'
   )
  return UNKNOWN;

 LEM_CHECKIT_Z( !set_name.empty() );
 MemFormatter ms;
 ms.printf( "SELECT id FROM word_entry_set WHERE name='%us'", to_upper(set_name).c_str() );
 FString Select=lem::to_utf8(ms.string());
 return QueryInt(Select);
}

void LexiconStorage_MySQL::DeleteWordEntrySets(void)
{
 lem::FString sql("DELETE FROM word_entry_set");
 Execute(sql);
 return;
}

WordEntrySetItem* LexiconStorage_MySQL::GetWordEntrySet( int id )
{
 lem::FString Select(lem::format_str( "SELECT ies, name FROM word_entry_set WHERE id=%d", id ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     WordEntrySetItem *wes = new WordEntrySetItem();
     wes->id = id;

     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UFString s = lem::mysql_column_ufstring(row,0);
  
       lem::MCollect<lem::UCString> toks;
       lem::parse( s, toks, false );
       for( lem::Container::size_type i=0; i<toks.size(); ++i )
        {
         const int id_entry = lem::to_int(toks[i]);
         wes->ies.insert(id_entry);   
        }

       wes->name = lem::mysql_column_ucstring(row,1);
      }

     mysql_free_result(res);
     return wes;
    }
   else
    {
     LEM_STOPIT;
     return NULL;
    }
  }
 else
  {
   cnx->Error(Select);
   return NULL;
  }
}

void LexiconStorage_MySQL::StoreWordEntrySet( WordEntrySetItem &wes )
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
 wes.id = ExecuteAndReturnId(sql);
 return;
}


LS_ResultSet* LexiconStorage_MySQL::ListUnbreakableRules( int id_language )
{
 lem::FString Select;

 if( id_language==ANY_STATE )
  Select = "SELECT id FROM unbreakable ORDER BY id";
 else
  Select = lem::format_str("SELECT id FROM unbreakable WHERE id_language=%d ORDER BY id",id_language); 

 return ListByQuery(Select);
}

LA_UnbreakableRule* LexiconStorage_MySQL::GetUnbreakableRule( int id )
{
 lem::FString Select(lem::format_str( "SELECT name, id_language, is_regex, pattern, id_src "
  " FROM unbreakable WHERE id=%d", id ) );

 LA_UnbreakableRule *rule = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UCString name = lem::mysql_column_ucstring(row,0);
       const int id_language = lem::mysql_column_int(row,1);
       const bool is_regex = lem::mysql_column_int(row,2)==1;
       lem::UFString pattern = lem::mysql_column_ufstring(row,3);
       const int id_src = lem::mysql_column_int(row,4);
    
       rule = new LA_UnbreakableRule( id, name, id_language, is_regex, pattern.c_str(), id_src );
      }

     mysql_free_result(res);
     return rule;
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

void LexiconStorage_MySQL::StoreUnbreakableRule( LA_UnbreakableRule *rule )
{
 lem::UFString pattern(rule->GetPattern());
 lem::mysql_escape(pattern);

 lem::MemFormatter q;
 q.printf( "INSERT INTO unbreakable( name, id_language, is_regex,"
           " pattern, id_src ) VALUES ( '%us', %d, %d, '%us', %d )",
           lem::to_upper(rule->GetName()).c_str(), rule->GetLanguage(),
           rule->IsRegex() ? 1 : 0,
           pattern.c_str(), rule->GetSourceLocation() );
 
 lem::FString s(lem::to_utf8(q.string()));
 int id = ExecuteAndReturnId(s);
 rule->SetId(id);
 return;
}


void LexiconStorage_MySQL::DeleteUnbreakableRules(void)
{
 lem::FString sql("DELETE FROM unbreakable");
 Execute(sql);
 return;
}



int LexiconStorage_MySQL::FindUnbreakableRule( const lem::UCString &rule_name )
{
 LEM_CHECKIT_Z( !rule_name.empty() );
 MemFormatter ms;
 ms.printf( "SELECT id FROM unbreakable WHERE name='%us'", to_upper(rule_name).c_str() );
 FString Select=lem::to_utf8(ms.string());
 return QueryInt(Select);
}





void LexiconStorage_MySQL::DeleteMorphologicalFilters(void)
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
 Execute("DELETE FROM ts_point");
 Execute("DELETE FROM ts_group2root");
 Execute("DELETE FROM generic_tree_scorer");
 Execute("DELETE FROM ts_predicate");

 Execute("DELETE FROM word_assoc");
 Execute("DELETE FROM predicate_template");

 return;
}


LS_ResultSet* LexiconStorage_MySQL::ListSynPatternTrees(void)
{
 lem::FString Select("SELECT id_tree, name, uname, id_language, pattern_type FROM SynPatternTree ORDER BY id_tree" );
 return ListByQuery(Select);
}


void LexiconStorage_MySQL::DeleteSynPatternTrees(void)
{
 lem::FString sql("DELETE FROM SynPatternTree");
 Execute(sql);
 return;
}


int LexiconStorage_MySQL::FindSynPatternTree( int id_language, const lem::UCString &name, int pattern_type )
{
 lem::MemFormatter mem;

 if( id_language==ANY_STATE )
  mem.printf( "SELECT id_tree FROM SynPatternTree WHERE name='%us' AND pattern_type=%d", lem::to_upper(name).c_str(), pattern_type );
 else
  mem.printf( "SELECT id_tree FROM SynPatternTree WHERE name='%us' AND id_language=%d AND pattern_type=%d", lem::to_upper(name).c_str(), id_language, pattern_type );

 return QueryInt( mem.string() );
}


void LexiconStorage_MySQL::StoreSynPatternTree( int id_language, const lem::UCString &name, int id, const SynPatternTreeNode *tree, int pattern_type )
{
 #if defined SOL_SAVEBIN
 lem::MemStream mem(true);
 tree->SaveBin(mem);
 const int sz = mem.tellp();
 const char* bytes = mem.get_Block();
 lem::FString hex;
 Storage_Data2Hex( bytes, sz, hex );
 
 lem::MemFormatter q;
 q.printf( "INSERT INTO SynPatternTree( id_tree, id_language, name, uname, pattern_type, bin )"
           " VALUES ( %d, %d, '%us', %d, '%s' )", id, id_language, name.c_str(), lem::to_upper(name).c_str(), pattern_type, hex.c_str() );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);
 #else
 LEM_STOPIT;
 #endif
}

lem::UCString LexiconStorage_MySQL::GetSynPatternTreeName( int id )
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


std::pair<SynPatternTreeNode*,lem::UCString> LexiconStorage_MySQL::GetSynPatternTree( int id )
{
 lem::FString Select(lem::format_str( "SELECT bin, name, LENGTH(bin) FROM SynPatternTree WHERE id_tree=%d", id ) );

 SynPatternTreeNode *rule = NULL;
 lem::UCString name;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       name = lem::mysql_column_ucstring(row,1);

       int blob_size = lem::mysql_column_int(row,2);
       const unsigned char *bytes = (const unsigned char*)row[0];
       MemReadStream rdr( bytes, blob_size );
       rule = new SynPatternTreeNode();
       rule->LoadBin(rdr);
      }

     mysql_free_result(res);
     return std::make_pair(rule,name);
    }

   LEM_STOPIT;
   return std::make_pair(rule,name);
  }
 else
  {
   cnx->Error(Select);
   return std::make_pair(rule,name);
  }
}


LS_ResultSet* LexiconStorage_MySQL::ListProductionRuleCategories( const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM rules_in_category WHERE marker='%us' ORDER BY id", Marker );
 lem::FString sql( lem::to_utf8( mem.string() ) );

 return ListByQuery(sql);
}


int LexiconStorage_MySQL::CountRuleGroups( const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT count(*) FROM rules_in_category WHERE marker='%us'", Marker );
 lem::FString sql( lem::to_utf8( mem.string() ) );
 return QueryInt(sql);
}




int LexiconStorage_MySQL::FindRuleGroup( const wchar_t *Marker, const lem::UCString &name )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM rules_in_category WHERE name='%us' AND marker='%us'", lem::to_upper(name).c_str(), Marker );

 lem::FString sql( lem::to_utf8( mem.string() ) );
 return QueryInt(sql);
}




int LexiconStorage_MySQL::RegisterRuleGroup( const lem::UCString &name, const wchar_t *Marker )
{
 lem::MemFormatter q;
 q.printf( "INSERT INTO rules_in_category( marker, name, bin )"
           " VALUES ( '%us', '%us', '' )", Marker, lem::to_upper(name).c_str() );
 
 lem::FString s(lem::to_utf8(q.string()));
 return ExecuteAndReturnId(s);
}



void LexiconStorage_MySQL::Execute( const lem::UFString & sql )
{
 Execute( lem::to_utf8(sql) );
}

void LexiconStorage_MySQL::Execute( const lem::FString & sql )
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> tx(cnx->GetTx());
 cnx->Execute(sql);
 return;
}

int LexiconStorage_MySQL::ExecuteAndReturnId( const lem::UFString & sql )
{
 return ExecuteAndReturnId( lem::to_utf8(sql) );
}


int LexiconStorage_MySQL::ExecuteAndReturnId( const lem::FString & sql )
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


void LexiconStorage_MySQL::DeleteProcedures( const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "DELETE FROM tr_procedure WHERE marker='%us'", Marker );
 lem::FString sql( lem::to_utf8(mem.string()) );
 Execute(sql);
 return;
}

void LexiconStorage_MySQL::DeletePatternMatchers( const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "DELETE FROM pattern_matcher WHERE marker='%us'", Marker );
 lem::FString sql( lem::to_utf8(mem.string()) );
 Execute(sql);
 return;
}

LS_ResultSet* LexiconStorage_MySQL::ListPatternMatchers( const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id, name, type FROM pattern_matcher WHERE marker='%us' ORDER BY id", Marker );
 lem::FString sql( lem::to_utf8( mem.string() ) );

 return ListByQuery(sql);
}

LS_ResultSet* LexiconStorage_MySQL::ListProcedures( const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM tr_procedure WHERE marker='%us' ORDER BY id", Marker );
 lem::FString sql( lem::to_utf8( mem.string() ) );

 return ListByQuery(sql);
}


int LexiconStorage_MySQL::RegisterProcedure( const lem::UCString &name, const wchar_t *Marker )
{
 lem::MemFormatter q;
 q.printf( "INSERT INTO tr_procedure( marker, name ) VALUES ( '%us', '%us' )", Marker, lem::to_upper(name).c_str() );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);
 const int id = cnx->GetLastId();
 return id;
}



int LexiconStorage_MySQL::FindProcedure( const lem::UCString &name, const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM tr_procedure WHERE name='%us' AND marker='%us'", lem::to_upper(name).c_str(), Marker );
 lem::FString sql( lem::to_utf8( mem.string() ) );
 return QueryInt(sql);
}




TrPatternMatcher * LexiconStorage_MySQL::GetPatternMatcher( int id )
{
 lem::FString Select(lem::format_str( "SELECT bin, type, name FROM pattern_matcher WHERE id=%d", id ) );

 TrPatternMatcher *matcher = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::FString hex = lem::mysql_column_fstring(row,0);
       const int type = lem::mysql_column_int(row,1);
       lem::UCString name = lem::mysql_column_ucstring(row,2);
    
       unsigned char *bytes=NULL;
       int size=0;
       Solarix::Storage_Hex2Data( hex, &bytes, &size );
       MemReadStream rdr( bytes, size );
        
       if( type==0 )
        {
         matcher = new TrPrefixTreeMatcher(name);
         int t0 = rdr.read_int();
         LEM_CHECKIT_Z(t0==0);
        }
       else if( type==1 )
        {
         matcher = new TrReplaceMatcher(name);
         int t1 = rdr.read_int();
         LEM_CHECKIT_Z(t1==1);
        }
       else if( type==3 )
        {
         matcher = new TrLikeMatcher(name);
         int t1 = rdr.read_int();
         LEM_CHECKIT_Z(t1==3);
        }
       else
        LEM_STOPIT;
        
       matcher->LoadBin(rdr);
       delete[] bytes;
      }

     mysql_free_result(res);
     return matcher;
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



TrProcedure * LexiconStorage_MySQL::GetProcedure( int id )
{
 lem::FString Select(lem::format_str( "SELECT bin FROM tr_procedure WHERE id=%d", id ) );

 TrProcedure *proc = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::FString hex = lem::mysql_column_fstring(row,0);
     
       unsigned char *bytes=NULL;
       int size=0;
       Solarix::Storage_Hex2Data( hex, &bytes, &size );
       MemReadStream rdr( bytes, size );
       proc = new TrProcedure();
       proc->LoadBin(rdr);
       delete[] bytes;
      }
     else
      {
       mysql_free_result(res);
       lem::MemFormatter mem;
       mem.printf( "Can not load procedure with id=%d", id );
       throw lem::E_BaseException(mem.string());
      }

     mysql_free_result(res);
     return proc;
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

void LexiconStorage_MySQL::StoreProcedure( const wchar_t *Marker, const TrProcedure *p )
{
 #if defined SOL_SAVEBIN
 lem::MemStream mem(true);
 p->SaveBin(mem);
 const int sz = mem.tellp();
 const char* bytes = mem.get_Block();
 lem::FString hex;
 Storage_Data2Hex( bytes, sz, hex );
 
 LEM_CHECKIT_Z( p->GetId()!=UNKNOWN );

 lem::MemFormatter q;
 q.printf( "UPDATE tr_procedure SET bin='%s', id_src=%d WHERE id=%d", hex.c_str(), p->GetSourceLocation(), p->GetId() );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);
 #else
 LEM_STOPIT;
 #endif
 
 return;
}

void LexiconStorage_MySQL::StorePatternMatcher( const wchar_t *Marker, int type, const lem::UCString &name, TrPatternMatcher *m )
{
 #if defined SOL_SAVEBIN
 lem::MemStream mem(true);
 m->SaveBin(mem);
 const int sz = mem.tellp();
 const char* bytes = mem.get_Block();

 lem::FString hex;
 lem::MemFormatter q;
 hex.clear();
 Storage_Data2Hex( bytes, sz, hex );
 
 q.printf( "INSERT INTO pattern_matcher( type, marker, name, bin )"
           " VALUES ( %d, '%us', '%us', '%s' )", type, Marker, lem::to_upper(name).c_str(), hex.c_str() );

 lem::FString s(lem::to_utf8(q.string()));

 const int id = ExecuteAndReturnId(s);
 m->SetId(id);

 #else
 LEM_STOPIT;
 #endif
 
 return;
}

int LexiconStorage_MySQL::FindPatternMatcher( const lem::UCString &name, const wchar_t *Marker )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM pattern_matcher WHERE name='%us' AND marker='%us'", lem::to_upper(name).c_str(), Marker );
 lem::FString sql( lem::to_utf8( mem.string() ) );
 return QueryInt(sql);
}


void LexiconStorage_MySQL::DeleteFunctions( const wchar_t *Marker )
{
 lem::UFString sql( lem::format_str( L"DELETE FROM tr_functions WHERE marker='%s'", Marker ) );
 lem::FString s( lem::to_utf8(sql) );
 Execute(s);
 return;
}

TrFunctions* LexiconStorage_MySQL::GetFunctions( const wchar_t *Marker )
{
 lem::FString Select( lem::to_utf8(lem::format_str( L"SELECT bin FROM tr_functions WHERE marker='%s'", Marker )) );

 TrFunctions *fun = NULL;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     fun = new TrFunctions();

     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::FString hex = lem::mysql_column_fstring(row,0);
    
       unsigned char *bytes=NULL;
       int size=0;
       Solarix::Storage_Hex2Data( hex, &bytes, &size );
       MemReadStream rdr( bytes, size );
       fun->LoadBin(rdr);
       delete[] bytes;
      }

     mysql_free_result(res);
     return fun;
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

void LexiconStorage_MySQL::StoreFunctions( TrFunctions *functions, const wchar_t *Marker )
{
 #if defined SOL_SAVEBIN
 lem::MemStream mem(true);
 functions->SaveBin(mem);
 const int sz = mem.tellp();
 const char* bytes = mem.get_Block();

 lem::FString hex;
 Storage_Data2Hex( bytes, sz, hex );
 
 lem::MemFormatter q;
 q.printf( "INSERT INTO tr_functions( marker, bin )"
           " VALUES ( '%us', '%s' )", Marker, hex.c_str() );
 
 lem::FString s(lem::to_utf8(q.string()));
 Execute(s);

 #else
 LEM_STOPIT;
 #endif
 
 return;
}




LS_ResultSet* LexiconStorage_MySQL::ListLanguageUsage(void)
{
 return ListByQuery("SELECT id_language, is_input, is_output, is_default FROM lang_usage ORDER BY id_language" ); 
}

void LexiconStorage_MySQL::StoreLanguageUsage( int id_language, bool is_input, bool is_output, bool is_default )
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



void LexiconStorage_MySQL::DeleteSourceLocations(void)
{
 Execute("DELETE FROM src_filename");
 Execute("DELETE FROM src_location");
 return;
}

int LexiconStorage_MySQL::RegisterSourceFilename( const lem::Path &filepath )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM src_filename WHERE filepath='%us'", EncodeString(lem::to_upper(filepath.GetUnicode())).c_str() );
 int id = QueryInt( lem::to_utf8(mem.string()) );
 if( id==UNKNOWN )
  {
   mem.printf( "INSERT INTO src_filename( filepath, filepath0 ) VALUES ( '%us', '%us' )",
    EncodeString(lem::to_upper(filepath.GetUnicode())).c_str(), EncodeString(filepath.GetUnicode()).c_str() );
   id = ExecuteAndReturnId( lem::to_utf8(mem.string()) );
  }

 return id;
}


int LexiconStorage_MySQL::RegisterSourceLocation( int id_filename, int iline, int icolumn )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO src_location( id_filename, line_no, column_no ) VALUES ( %d, %d, %d )", id_filename, iline, icolumn );
 return ExecuteAndReturnId( lem::to_utf8(mem.string()) );
}


bool LexiconStorage_MySQL::GetSourceFilename( int id_filename, lem::Path &filepath )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT filepath0 FROM src_filename WHERE id=%d", id_filename );

 lem::FString Select( lem::to_utf8(mem.string()) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 bool ret_success=false;

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UFString str = lem::mysql_column_ufstring(row,0);
       filepath = lem::Path(str);
       ret_success=true;
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return ret_success;
}


bool LexiconStorage_MySQL::GetSourceLocation( int id_location, int &id_file, int &line, int &column )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id_filename, line_no, column_no FROM src_location WHERE id=%d", id_location );
 lem::FString Select( lem::to_utf8(mem.string()) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 bool ret_success=false;

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       id_file = lem::mysql_column_int(row,0);
       line = lem::mysql_column_int(row,1);
       column = lem::mysql_column_int(row,2);
       ret_success=true;
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return ret_success;
}



int LexiconStorage_MySQL::FindSourceLineBeginning( int id_filename, int line )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT Coalesce(MIN(column_no),-1) FROM src_location WHERE id_filename=%d AND line_no=%d", id_filename, line );
 int column_no = QueryInt( lem::to_utf8(mem.string()) );
 if( column_no!=-1 )
  {
   mem.printf( "SELECT id FROM src_location WHERE id_filename=%d AND line_no=%d AND column_no=%d", id_filename, line, column_no );
   int id = QueryInt( lem::to_utf8(mem.string()) );
   return id;
  }
 else
  {
   return UNKNOWN;
  }
}



int LexiconStorage_MySQL::FindClosestSourceLocation( int id_filename, int line )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT Coalesce(MIN(ABS(line_no-%d)),-1) FROM src_location WHERE id_filename=%d", line, id_filename );
 int line_no = QueryInt( lem::to_utf8(mem.string()) );
 if( line_no!=-1 )
  {
   return FindSourceLineBeginning( id_filename, line_no );
  }
 else
  {
   return UNKNOWN;
  }
}

LS_ResultSet* LexiconStorage_MySQL::ListSourceFilenames(void)
{
 return ListByQuery("SELECT id, filepath0 FROM src_filename ORDER BY id");
}


LS_ResultSet* LexiconStorage_MySQL::ListSourceLocations(void)
{
 return ListByQuery("SELECT id, id_filename, line_no, column_no FROM src_location ORDER BY id");
}






LS_ResultSet* LexiconStorage_MySQL::ListParadigmaMatchers(void)
{
 return ListByQuery("SELECT id, r_condition, id_class FROM paradigma WHERE CHAR_LENGTH(r_condition)>0 ORDER BY id");
}


LS_ResultSet* LexiconStorage_MySQL::ListParadigmas(void)
{
 return ListByQuery("SELECT id FROM paradigma ORDER BY id");
}


int LexiconStorage_MySQL::StoreParadigma( const SG_DeclensionTable &p )
{
 lem::UFString matcher = p.GetCondition().ToString();
 mysql_escape(matcher);

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
 const int id = ExecuteAndReturnId(sql1);

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

   mysql_escape(generator);
   mysql_escape(condition_str);
   mysql_escape(flexer_flags);

   lem::MemFormatter mem3;
   mem3.printf( "INSERT INTO paradigma_form( id_paradigma, lexem_generator, rx_condition, flexer_flags, dims ) VALUES ( %d, '%us', '%us', '%us', '%us' )",
    id, generator.c_str(), condition_str.c_str(), flexer_flags.c_str(), dims.c_str() );

   lem::FString sql3( lem::to_utf8(mem3.string()) );
   Execute(sql3);
  }

 return id;
}




SG_DeclensionTable* LexiconStorage_MySQL::GetParadigma( int id )
{
 lem::FString sql1( lem::format_str( "SELECT r_condition, id_class, attrs FROM paradigma WHERE id=%d", id ) );
 
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 SG_DeclensionTable *p = NULL;

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, sql1.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UFString matcher_str = lem::mysql_column_ufstring(row,0);
       int id_class = lem::mysql_column_int(row,1);
       lem::UFString attrs_str = lem::mysql_column_ufstring(row,2);

       CP_Array attrs;
       attrs.Parse(attrs_str);

       lem::MCollect<lem::UCString> names;
     
       lem::FString sql2( lem::format_str( "SELECT name FROM paradigma_name WHERE id_paradigma=%d", id ) );

       ok = mysql_query( c->mysql, sql2.c_str() );
       if( ok==0 )
        {
         MYSQL_RES *res2 = mysql_store_result(c->mysql);
         if( res2!=NULL )
          {
           MYSQL_ROW row2;
           while( (row2 = mysql_fetch_row(res2))!=NULL )
            {
             lem::UCString name = lem::mysql_column_ucstring(row2,0);
             names.push_back(name);
            }

           mysql_free_result(res2);
          }
        }
       else
        {
         cnx->Error(sql2);
        }

       lem::MCollect<SG_DeclensionForm*> forms;
       lem::FString sql3( lem::format_str( "SELECT lexem_generator, rx_condition, flexer_flags, dims FROM paradigma_form WHERE id_paradigma=%d ORDER BY id", id ) );

       ok = mysql_query( c->mysql, sql3.c_str() );
       if( ok==0 )
        {
         MYSQL_RES *res3 = mysql_store_result(c->mysql);
         if( res3!=NULL )
          {
           MYSQL_ROW row3;
           while( (row3 = mysql_fetch_row(res3))!=NULL )
            {
             lem::UFString lexem_generator = lem::mysql_column_ufstring(row3,0);
             lem::UFString rx_condition = lem::mysql_column_ufstring(row3,1);
             lem::UFString flexer_flags = lem::mysql_column_ufstring(row3,2);
             lem::UFString dims_str = lem::mysql_column_ufstring(row3,3);
        
             CP_Array dims;
             dims.Parse(dims_str);
        
             SG_DeclensionForm *form = new SG_DeclensionForm( lexem_generator, rx_condition, flexer_flags, dims );
             forms.push_back(form);
            }

           mysql_free_result(res3);
          }
        }
       else
        {
         cnx->Error(sql2);
        }
 
 
       p = new SG_DeclensionTable( names, matcher_str, id_class, attrs, forms );
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(sql1);
  }

 if( p==NULL )
  {
   throw lem::E_BaseException( lem::format_str( "Can not load paradigma id=%d", id ) );
  }

 return p;
}


void LexiconStorage_MySQL::AddEnding( const lem::UCString &ending, int id_language, int efreq )
{
 lem::UFString s(ending.c_str());
 lem::mysql_escape(s);

 // такое окончание уже есть?
 lem::MemFormatter q;
 q.printf( "SELECT id FROM endings WHERE ending='%us' AND id_language=%d", s.c_str(), id_language );
 int id = QueryInt(q.string());

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



bool LexiconStorage_MySQL::GetEndingStat( int id_language, EndingStat &res )
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


bool LexiconStorage_MySQL::FindEnding( int id_language, const lem::UCString &ending, int &nentry, int &sumfreq )
{
 lem::UFString s(ending.c_str());
 lem::mysql_escape(s);

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


LS_ResultSet* LexiconStorage_MySQL::ListEndings(void)
{
 return ListByQuery("SELECT id, ending, id_language, nform, sumfreq FROM endings");
}


LS_ResultSet* LexiconStorage_MySQL::ListEndingStat(void)
{
 return ListByQuery("SELECT id_language, max_len FROM ending_stat");
}


void LexiconStorage_MySQL::CommitCompilation(void)
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


void LexiconStorage_MySQL::SetWordformFrequency( int id_entry, int iform, int frequency )
{
 LEM_CHECKIT_Z( id_entry!=UNKNOWN );
 LEM_CHECKIT_Z( iform!=UNKNOWN );
 LEM_CHECKIT_Z( frequency>=0 );

 // чтобы не допустить дубля и нарушения ограничения уникальности, проверим, нет ли
 // записи для этой словоформы.
 
 lem::MemFormatter q;
 q.printf( "SELECT id FROM wordform_frequency WHERE id_entry=%d AND iform=%d", id_entry, iform );
 int id = QueryInt(q.string());

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


std::pair<bool,int> LexiconStorage_MySQL::GetWordformFrequency( int id_entry, int iform )
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


LS_ResultSet* LexiconStorage_MySQL::ListWordformFrequency(void)
{
 return ListByQuery("SELECT id, id_entry, iform, freq FROM wordform_frequency");
}


void LexiconStorage_MySQL::DeleteWordformFrequency(void)
{
 Execute("DELETE FROM wordform_frequency");
 return;
}







LS_ResultSet* LexiconStorage_MySQL::ListWordSet(void)
{
 return ListByQuery("SELECT id FROM word_set ORDER BY id");
}

int LexiconStorage_MySQL::FindWordSet( const lem::UCString &set_name )
{
 if(
    set_name.front()==L'\'' ||
    set_name.front()==L'"' ||
    set_name.back()==L'\'' ||
    set_name.back()==L'"'
   )
  return UNKNOWN;

 LEM_CHECKIT_Z( !set_name.empty() );
 MemFormatter ms;
 ms.printf( "SELECT id FROM word_set WHERE name='%us'", to_upper(set_name).c_str() );
 FString Select=lem::to_utf8(ms.string());
 return QueryInt(Select);
}

void LexiconStorage_MySQL::DeleteWordSets(void)
{
 lem::FString sql("DELETE FROM word_set");
 Execute(sql);
 return;
}

WordSetItem* LexiconStorage_MySQL::GetWordSet( int id )
{
 lem::FString Select(lem::format_str( "SELECT words, name, case_sensitive FROM word_set WHERE id=%d", id ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     WordSetItem *wes = new WordSetItem();
     wes->id = id;

     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       lem::UFString s = lem::mysql_column_ufstring(row,0);
  
       lem::Collect<lem::UFString> toks;
       const wchar_t delimiters[2] = { WORD_SET_DELIMITER, 0 };
       lem::parse( s, toks, delimiters );
       for( lem::Container::size_type i=0; i<toks.size(); ++i )
        {
         wes->words.insert(toks[i].c_str());
        }

       wes->name = lem::mysql_column_ucstring(row,1);
       wes->case_sensitive = lem::mysql_column_int(row,2)==1;
      }

     mysql_free_result(res);
     return wes;
    }
   else
    {
     LEM_STOPIT;
     return NULL;
    }
  }
 else
  {
   cnx->Error(Select);
   return NULL;
  }
}

void LexiconStorage_MySQL::StoreWordSet( WordSetItem &wes )
{
 lem::UFString s;
 for( std::set<lem::UCString>::const_iterator it=wes.words.begin(); it!=wes.words.end(); ++it )
  {
   if( !s.empty() )
    s.Add_Dirty(WORD_SET_DELIMITER);

   lem::UFString word( it->c_str() );
   lem::mysql_escape(word);
   s.Add_Dirty( word.c_str() );
  } 

 lem::MemFormatter q;
 q.printf( "INSERT INTO word_set( name, case_sensitive, words ) VALUES ( '%us', %d, '%us' )",
           lem::to_upper(wes.name).c_str(), wes.case_sensitive ? 1 : 0, s.c_str() );
 
 lem::FString sql(lem::to_utf8(q.string()));
 wes.id = ExecuteAndReturnId(sql);
 return;
}







bool LexiconStorage_MySQL::FindMisspelling( int id_language, const lem::UCString &word, lem::MCollect<lem::UCString> &new_words )
{
 lem::UFString s( word.c_str() );
 s.to_upper();
 lem::mysql_escape(s);

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


void LexiconStorage_MySQL::AddMisspelling( int id_language, const lem::UCString &word, const lem::UCString &new_word )
{
 if( id_language==UNKNOWN )
  throw E_BaseException( L"Misspelling rule requires language id to be defined" );

 lem::UFString s1( word.c_str() );
 s1.to_upper();
 lem::mysql_escape(s1);

 lem::UFString s2( new_word.c_str() );
 s2.to_upper();
 lem::mysql_escape(s2);

 lem::MemFormatter mem;
 mem.printf( "SELECT count(*) FROM misspelling WHERE original_word='%us' AND substitution='%us' AND id_language=%d", s1.c_str(), s2.c_str(), id_language );
 int n = QueryInt(mem.string());

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


LS_ResultSet* LexiconStorage_MySQL::ListMisspelling(void)
{
 return ListByQuery("SELECT id, id_language, original_word, substitution FROM misspelling ORDER BY id");
}

void LexiconStorage_MySQL::DeleteMisspelling(void)
{
 Execute("DELETE FROM misspelling");
 return; 
}



int LexiconStorage_MySQL::RegisterCollocationSet( const lem::UCString &name, bool case_sensitive )
{
 LEM_CHECKIT_Z( !name.empty() );

 lem::MemFormatter q;
 q.printf( "INSERT INTO collocation_set( name, case_sensitive ) VALUES ( '%us', %d )",
           lem::to_upper(name).c_str(), case_sensitive ? 1 : 0 );
 
 lem::FString sql(lem::to_utf8(q.string()));
 const int id = ExecuteAndReturnId(sql);
 return id;
}



int LexiconStorage_MySQL::FindCollocationSet( const lem::UCString &set_name )
{
 if(
    set_name.front()==L'\'' ||
    set_name.front()==L'"' ||
    set_name.back()==L'\'' ||
    set_name.back()==L'"'
   )
  return UNKNOWN;

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM collocation_set WHERE name='%us'", to_upper(set_name).c_str() );
 return QueryInt(mem.string());
}



void LexiconStorage_MySQL::AddCollocationToSet( int id_set, const lem::MCollect<lem::UCString> &words )
{
 LEM_CHECKIT_Z( id_set!=UNKNOWN );
 LEM_CHECKIT_Z( !words.empty() );

 lem::UFString str;
 LexiconStorage::MergeCollocationWords( words, str );
 lem::mysql_escape(str);

 lem::UFString headword( words.front().c_str() );
 lem::mysql_escape(headword);

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


int LexiconStorage_MySQL::FindCollocationSetHeadword( const lem::UCString &headword, int &min_len, int &max_len )
{
 lem::UFString h(headword.c_str());
 lem::mysql_escape(h);
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


int LexiconStorage_MySQL::FindCollocationInSet( int id_set, const lem::MCollect<lem::UCString> &words )
{
 LEM_CHECKIT_Z( id_set!=UNKNOWN );
 LEM_CHECKIT_Z( !words.empty() );

 lem::UFString str;
 LexiconStorage::MergeCollocationWords( words, str );
 lem::mysql_escape(str);

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM collocation_set_item WHERE words='%us' AND id_set=%d", str.c_str(), id_set );
 return QueryInt(mem.string());
}


LS_ResultSet* LexiconStorage_MySQL::ListCollocationSets(void)
{
 return ListByQuery( "SELECT id, name, case_sensitive FROM collocation_set ORDER BY id" );
}


LS_ResultSet* LexiconStorage_MySQL::ListCollocationSetItems(void)
{
 return ListByQuery( "SELECT id, id_set, words, n_word, headword FROM collocation_set_item ORDER BY id" );
}


LS_ResultSet* LexiconStorage_MySQL::ListCollocationSetHeadwords(void)
{
 return ListByQuery( "SELECT id, headword, min_len, max_len FROM collocation_headword" );
}


void LexiconStorage_MySQL::DeleteCollocationSets(void)
{
 Execute( "DELETE from collocation_headword" );
 Execute( "DELETE from collocation_set_item" );
 Execute( "DELETE from collocation_set" );
 return;
}










int LexiconStorage_MySQL::StoreFacts( const KB_Facts * facts )
{
 lem::UFString name( facts->GetName().c_str() );
 mysql_escape(name);
 
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


void LexiconStorage_MySQL::UpdateFactsQueryMode( const KB_Facts * facts )
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


int LexiconStorage_MySQL::StoreFact( const KB_Facts &facts, const KB_Fact * fact )
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
   mysql_escape( word1 );
   word1.dress_apostrophes();

   if( fact->CountArgs()>1 )
    {
     word2 = fact->GetArg(1).word.c_str();
     mysql_escape( word2 );
     word2.dress_apostrophes();
    }

   if( fact->CountArgs()>2 )
    {
     word3 = fact->GetArg(2).word.c_str();
     mysql_escape( word3 );
     word3.dress_apostrophes();
    }

   if( fact->CountArgs()>3 )
    {
     word4 = fact->GetArg(3).word.c_str();
     mysql_escape( word4 );
     word4.dress_apostrophes();
    }

   if( fact->CountArgs()>4 )
    {
     word5 = fact->GetArg(4).word.c_str();
     mysql_escape( word5 );
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


int LexiconStorage_MySQL::StoreFactArgument(
                                            int id_fact,
                                            int arg_index,
                                            const KB_Argument & arg
                                           )
{
 lem::MemFormatter mem;

 lem::UFString word_str( arg.word.c_str() );
 mysql_escape(word_str);

 lem::UFString wordset_name_str( arg.wordset_name.c_str() );
 mysql_escape(wordset_name_str);

 lem::UFString wordentryset_name_str( arg.wordentryset_name.c_str() );
 mysql_escape(wordentryset_name_str);

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



KB_Facts* LexiconStorage_MySQL::LoadFacts( int id_facts )
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
   res->check_features = ( mode & 0x00010000 ) == 0x00010000;

   res->ret_type = rs->GetInt(5);
   res->violation_score = rs->GetInt(6);
  }
 else
  {
   LEM_STOPIT;
  }

 return res;
}


LS_ResultSet* LexiconStorage_MySQL::ListFactsInGroup( int id_facts )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM kb_fact WHERE id_group=%d ORDER BY id", id_facts );
 return ListByQuery( mem.string() );
}



KB_Fact* LexiconStorage_MySQL::LoadFact( int id )
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


KB_Argument* LexiconStorage_MySQL::LoadFactArgument( int id )
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
   bool is_regex = rs->GetInt(0)==1;

   if( is_regex )
    res->word = rs->GetUCString(1);
   else
    res->regex_str = rs->GetUFString(1);

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


LS_ResultSet* LexiconStorage_MySQL::ListFactGroups(void)
{
 const char q[] = "SELECT id, id_language, name, n_arg, n_ret, query_mode, ret_type, violation_score, violation_handler FROM kb_facts ORDER BY id";
 return ListByQuery(q);
}



LS_ResultSet* LexiconStorage_MySQL::ListFacts(void)
{
 const char q[] = "SELECT id, id_group, Coalesce(boolean_return,-1), Coalesce(integer_return,-1) false_score FROM kb_fact ORDER BY id";
 return ListByQuery(q);
}


LS_ResultSet* LexiconStorage_MySQL::ListFactIndex1(void)
{
 const char q[] = "SELECT id, id_group, id_fact,"
                  " coalesce(word1,''), coalesce(word2,''), coalesce(word3,''), coalesce(word4,''), coalesce(word5,'') FROM kb_fact_index1 ORDER BY id";
 return ListByQuery(q);
}

LS_ResultSet* LexiconStorage_MySQL::ListFactIndex2(void)
{
 const char q[] = "SELECT id, id_group, Coalesce(boolean_return,-1), Coalesce(integer_return,-1),"
                  " coalesce(id_entry1,-1), coalesce(id_entry2,-1), coalesce(id_entry3,-1), coalesce(id_entry4,-1), coalesce(id_entry5,-1)"
                  " FROM kb_fact_index2 ORDER BY id";
 return ListByQuery(q);
}



LS_ResultSet* LexiconStorage_MySQL::ListFactArguments(void)
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



int LexiconStorage_MySQL::FindFactByEntries(
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



void LexiconStorage_MySQL::FindFactsByEntries(
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



int LexiconStorage_MySQL::FindFactByWords(
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
 mysql_escape(word1_str);

 mem.printf( "SELECT F.id, Coalesce(F.boolean_return,-1), Coalesce(F.integer_return,-1), F.false_score"
             " FROM kb_fact_index1 I, kb_fact F"
             " WHERE I.id_group=%d AND I.word1=%us", id_facts, word1_str.c_str() );

 if( n_arg>1 )
  {
   lem::UFString str( word2.c_str() );
   mysql_escape(str);
   mem.printf( " AND I.word2=%us", str.c_str() );
  }

 if( n_arg>2 )
  {
   lem::UFString str( word3.c_str() );
   mysql_escape(str);
   mem.printf( " AND I.word3=%us", str.c_str() );
  }

 if( n_arg>3 )
  {
   lem::UFString str( word4.c_str() );
   mysql_escape(str);
   mem.printf( " AND I.word4=%us", str.c_str() );
  }

 if( n_arg>4 )
  {
   lem::UFString str( word5.c_str() );
   mysql_escape(str);
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



void LexiconStorage_MySQL::DeleteWordformSets(void)
{
 Execute("DELETE FROM wordform_set");
 Execute("DELETE FROM wordform_set_coords");
 Execute("DELETE FROM wordform_set_item");
 return;
}





int LexiconStorage_MySQL::RegisterWordformSet( const lem::UCString & set_name )
{
 LEM_CHECKIT_Z( !set_name.empty() );
 lem::MemFormatter mem;
 lem::UFString escaped_set_name(set_name.c_str());
 mysql_escape(escaped_set_name);
 mem.printf( "INSERT INTO wordform_set( name ) VALUES ( '%us' )", escaped_set_name.c_str() );
 return ExecuteAndReturnId(mem.string());
}



int LexiconStorage_MySQL::StoreWordformSetCoords( const CP_Array & coords )
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



void LexiconStorage_MySQL::StoreWordformSetItem( int id_set, const lem::UCString & lexeme, int ekey, int id_coords )
{
 LEM_CHECKIT_Z( id_set!=UNKNOWN );
 LEM_CHECKIT_Z( !lexeme.empty() );
 LEM_CHECKIT_Z( ekey!=UNKNOWN );
 LEM_CHECKIT_Z( id_coords!=UNKNOWN );
 
 lem::UFString escaped_lexeme(lexeme.c_str());
 mysql_escape(escaped_lexeme);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO wordform_set_item( id_set, word, id_entry, id_coords ) VALUES ( %d, '%us', %d, %d )", id_set, escaped_lexeme.c_str(), ekey, id_coords );
 Execute( mem.string() );
 return;
}


LS_ResultSet* LexiconStorage_MySQL::ListWordformSets(void)
{
 return ListByQuery( "SELECT id, name FROM wordform_set" );
}

LS_ResultSet* LexiconStorage_MySQL::ListWordformSetCoords(void)
{
 return ListByQuery( "SELECT id, coords FROM wordform_set_coords" );
}

LS_ResultSet* LexiconStorage_MySQL::ListWordformSetItems(void)
{
 return ListByQuery( "SELECT id, id_set, word, id_entry, id_coords FROM wordform_set_item" );
}



int LexiconStorage_MySQL::FindWordformSetItem( int id_set, const lem::UCString & word, int id_entry, int * id_coords )
{
 LEM_CHECKIT_Z( !word.empty() );
 LEM_CHECKIT_Z( id_set!=UNKNOWN );
 LEM_CHECKIT_Z( id_entry!=UNKNOWN );
 LEM_CHECKIT_Z( id_coords!=NULL );

 lem::MemFormatter mem;
 lem::UFString escaped_lexeme(word.c_str());
 mysql_escape(escaped_lexeme);

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



void LexiconStorage_MySQL::LoadWordformSetCoords( int id_coords, Solarix::CP_Array & pairs )
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


int LexiconStorage_MySQL::FindWordformSet( const lem::UCString & set_name )
{
 lem::MemFormatter mem;

 lem::UFString escaped_name(set_name.c_str());
 mysql_escape(escaped_name);
 mem.printf( "SELECT id FROM wordform_set WHERE name='%us'", escaped_name.c_str() );

 return QueryInt( mem.string() );
}




int LexiconStorage_MySQL::StoreTreeScorerGroup( const lem::UCString & name, const TreeScorerGroupParams & params )
{
 lem::UFString escaped_name(name.c_str());
 mysql_escape(escaped_name);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO ts_group( name, allow_unmatched_children ) VALUES ( '%us', %d )", escaped_name.c_str(), params.allow_unmatched_children );
 const int id = ExecuteAndReturnId( ms.string() );
 return id;
}

void LexiconStorage_MySQL::LoadTreeScorerGroupParams( int id, TreeScorerGroupParams & params )
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


int LexiconStorage_MySQL::FindTreeScorerGroup( const lem::UCString & name )
{
 lem::UFString escaped_name(name.c_str());
 mysql_escape(escaped_name);

 lem::MemFormatter ms;
 ms.printf( "SELECT id FROM ts_group WHERE name='%us'", escaped_name.c_str() );
 const int id = QueryInt( ms.string() );
 return id;
}


LS_ResultSet* LexiconStorage_MySQL::ListTreeScorerGroups()
{
 return ListByQuery( "SELECT id, name, allow_unmatched_children FROM ts_group" );
}


void LexiconStorage_MySQL::StoreTreeScoreGroupMember( int id_group, int id_root )
{
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO ts_group2root( id_group, id_root ) VALUES ( %d, %d )", id_group, id_root );
 Execute( ms.string() );
 return;
}


LS_ResultSet* LexiconStorage_MySQL::ListTreeScoreGroupMembers()
{
 return ListByQuery( "SELECT id_group, id_root FROM ts_group2root" );
}

void LexiconStorage_MySQL::ListTreeScoreGroupMembers( int id_group, lem::MCollect<int> & roots )
{
 LEM_CHECKIT_Z( id_group!=UNKNOWN );

 lem::Ptr<LS_ResultSet> rs( ListByQuery(lem::format_str( "SELECT id_root FROM ts_group2root WHERE id_group=%d", id_group )) );
 while( rs->Fetch() )
 {
  roots.push_back( rs->GetInt(0) );
 }

 return;
}


LS_ResultSet* LexiconStorage_MySQL::ListGenericTreeScorers()
{
 return ListByQuery( "SELECT id, id_head_point, id_group, score_expr, score_type FROM generic_tree_scorer" );
}


LS_ResultSet* LexiconStorage_MySQL::ListTreeScorerPredicates()
{
 return ListByQuery( "SELECT id, id_point, func_name, narg, id_class1 FROM ts_predicate" );
}


void LexiconStorage_MySQL::StoreTreeScorerPredicate(
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



void LexiconStorage_MySQL::LoadTreeScorerPredicates( TreeScorerPoint * p )
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


TreeScorerPredicate* LexiconStorage_MySQL::LoadTreeScorerPredicate( int id )
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



int LexiconStorage_MySQL::RegisterTreeScorer_Word( const lem::UCString & word, int id_root_point, const lem::UFString & scoring_expression, int scoring_type, bool root_node, int id_group )
{
 LEM_CHECKIT_Z( !word.empty() );
 LEM_CHECKIT_Z( id_root_point!=UNKNOWN );

 lem::UFString escaped_word(word.c_str());
 mysql_escape(escaped_word);

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO ts_head_word( word, id_head_point, score_expr, score_type, root_node, id_group ) VALUES ( '%us', %d, '%us', %d, %d, %d )", escaped_word.c_str(), id_root_point, scoring_expression.c_str(), scoring_type, root_node ? 1 : 0, id_group );
 const int id_head = ExecuteAndReturnId( ms.string() );

 return id_head;
}


int LexiconStorage_MySQL::RegisterTreeScorer_Generic( int id_root_point, const lem::UFString & scoring_expression, int scoring_type, int id_group )
{
 LEM_CHECKIT_Z( id_root_point!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO generic_tree_scorer( id_head_point, score_expr, score_type, id_group ) VALUES ( %d, '%us', %d, %d )", id_root_point, scoring_expression.c_str(), scoring_type, id_group );
 const int id = ExecuteAndReturnId( ms.string() );

 return id;
}


int LexiconStorage_MySQL::RegisterTreeScorer_Wordentry( int EntryKey, int id_root_point, const lem::UFString & scoring_expression, int scoring_type, bool root_node, int id_group )
{
 LEM_CHECKIT_Z( EntryKey!=UNKNOWN );
 LEM_CHECKIT_Z( EntryKey!=ANY_STATE );
 LEM_CHECKIT_Z( id_root_point!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO ts_head_lemma( id_entry, id_head_point, score_expr, score_type, root_node, id_group ) VALUES ( %d, %d, '%us', %d, %d, %d )", EntryKey, id_root_point, scoring_expression.c_str(), scoring_type, root_node ? 1 : 0, id_group );
 const int id_head = ExecuteAndReturnId( ms.string() );

 return id_head;
}

void LexiconStorage_MySQL::ListGenericTreeScorers(
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




int LexiconStorage_MySQL::StoreTreeScorerPoint(
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
 mysql_escape(word_str);

 lem::UFString wordset_name_str( wordset_name.c_str() );
 mysql_escape(wordset_name_str);

 lem::UFString wordentryset_name_str( wordentryset_name.c_str() );
 mysql_escape(wordentryset_name_str);

 lem::UFString wordformset_name_str( wordformset_name.c_str() );
 mysql_escape(wordformset_name_str);

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
   mysql_escape(set_name1);
   set_type1 = set_checkers[0].set_type;
   set_affirm1 = set_checkers[0].affirm;
  }

 if( n_set_checkers>1 )
  {
   set_name2 = set_checkers[1].set_name.c_str();
   mysql_escape(set_name2);
   set_type2 = set_checkers[1].set_type;
   set_affirm2 = set_checkers[1].affirm;
  }

 if( n_set_checkers>2 )
  {
   set_name3 = set_checkers[2].set_name.c_str();
   mysql_escape(set_name3);
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


void LexiconStorage_MySQL::ListTreeScorers(
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
 mysql_escape(word_str);

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


int LexiconStorage_MySQL::GetTreeScorerHeadpointSrc( int id_point )
{
 lem::MemFormatter mem;
 mem.printf( "SELECT id_src FROM ts_point WHERE id=%d", id_point );
 return QueryInt( mem.string() );
}



TreeScorerPoint* LexiconStorage_MySQL::LoadTreeScorerPoint( int id_point )
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





void LexiconStorage_MySQL::LoadTreeScorerChildNodes( int id_point, lem::MCollect<TreeScorerPoint*> & scorer_leafs )
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




TreeScorerPoint* LexiconStorage_MySQL::LoadTreeScorerPoint( const lem::UFString & query )
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



LS_ResultSet* LexiconStorage_MySQL::ListTreeScorerLemmas()
{
 return ListByQuery( "SELECT id_entry, id_head_point, score_type, score_expr, root_node, id_group FROM ts_head_lemma" );
}


LS_ResultSet* LexiconStorage_MySQL::ListTreeScorerWords()
{
 return ListByQuery( "SELECT word, id_head_point, score_type, score_expr, root_node, id_group FROM ts_head_word" );
}


LS_ResultSet* LexiconStorage_MySQL::ListTreeScorerPoints()
{
 return ListByQuery( "SELECT id, id_parent, word_text, id_entry, id_class,"
                     "wordentryset_name, wordset_name, wordformset_name, n_coords, id_coord1,"
                     "id_state1, affirm1, id_coord2, id_state2, affirm2,"
                     "id_coord3, id_state3, affirm3, id_coord4, id_state4,"
                     "affirm4, thesauruscheck_link, thesauruscheck_entry, is_positive, children_quantification_min_count, children_quantification_min_count,"
                     "n_setcheckers, set_name1, set_type1, set_affirm1, set_name2,"
                     "set_type2, set_affirm2, set_name3, set_type3, set_affirm3,"
                     "link_type, id_metaentry, relative_position, id_src, id_group"
                     "quantification_min_count, quantification_max_count, marker FROM ts_point" );
}





int LexiconStorage_MySQL::StoreMetaEntry(
                                         const lem::UCString & name,
                                         int id_class,
                                         const lem::MCollect<int> & entries
                                        )
{
 lem::UFString name_str( name.c_str() );
 mysql_escape(name_str);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO metaentry( name, id_class ) VALUES ('%us',%d)", name_str.c_str(), id_class );
 const int id = ExecuteAndReturnId( mem.string() );

 for( lem::Container::size_type i=0; i<entries.size(); ++i )
 {
  mem.printf( "INSERT INTO metaentry_item( id_metaentry, id_entry ) VALUES ( %d, %d )", id, entries[i] );
  Execute( mem.string() );
 }

 return id;
}

int LexiconStorage_MySQL::FindMetaEntry( const lem::UCString & name, int id_class )
{
 lem::UFString name_str( name.c_str() );
 mysql_escape(name_str);

 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM metaentry WHERE id_class=%d AND name='%us'", id_class, name_str.c_str() );
 const int id = QueryInt( mem.string() );
 return id;
}


void LexiconStorage_MySQL::GetMetaEntryItems( int id_metaentry, lem::MCollect<int> & entries )
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



LS_ResultSet* LexiconStorage_MySQL::ListMetaEntries()
{
 return ListByQuery( "SELECT id FROM metaentry" );
}


MetaEntry* LexiconStorage_MySQL::LoadMetaEntry( int id )
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



bool LexiconStorage_MySQL::DoesMetaEntryContains( int id_metaentry, int id_entry )
{
 LEM_CHECKIT_Z( id_metaentry!=UNKNOWN );
 lem::MemFormatter mem;
 mem.printf( "SELECT id FROM metaentry_item WHERE id_metaentry=%d AND id_entry=%d", id_metaentry, id_entry );
 return QueryInt( mem.string() )!=-1;
}


/*
LS_ResultSet* LexiconStorage_MySQL::ListLeftFilterSelectors()
{
 return ListByQuery("SELECT id, word_text,id_entry, id_language, id_body, context_length FROM left_filter_selector");
}



int LexiconStorage_MySQL::RegisterLeftFilter(
                                             const CollocFilterPoint & rear_point,
                                             int id_body,
                                             int id_language,
                                             int context_length
                                            )
{
 LEM_CHECKIT_Z( id_body!=UNKNOWN );

 lem::MemFormatter mem;

 if( rear_point.IsEntry() )
  {
   mem.printf( "INSERT INTO left_filter_selector( word_text, id_entry, id_language, id_body, context_length ) VALUES ( '', %d, %d, %d, %d )",
    rear_point.GetEntryID(), id_language, id_body, context_length );
  }
 else if( rear_point.IsWord() )
  {
   lem::UFString word_str( rear_point.GetWord().c_str() );
   mysql_escape(word_str);

   mem.printf( "INSERT INTO left_filter_selector( word_text, id_entry, id_language, id_body, context_length ) VALUES ( '%us', %d, %d, %d, %d )",
    word_str.c_str(), -1, id_language, id_body, context_length );
  }
 else
  {
   LEM_STOPIT;
  }

 return ExecuteAndReturnId( lem::to_utf8(mem.string()) );
}



bool LexiconStorage_MySQL::FindLeftFiltersByText( int id_language, const lem::UCString & word, lem::MCollect<LeftFilterInfo> & filters )
{
 filters.clear();

 lem::UFString word_str( word.c_str() );
 mysql_escape(word_str);

 lem::MemFormatter mem;
 mem.printf( "SELECT id_body, context_length FROM left_filter_selector WHERE word_text='%us' AND id_language=%d", word_str.c_str(), id_language );
 
 lem::Ptr<LS_ResultSet> rs( ListByQuery( mem.string() ) );
 while( rs->Fetch() )
  {
   LeftFilterInfo info;
   info.id_body = rs->GetInt(0);
   info.context_length = rs->GetInt(1);
   filters.push_back(info);
  }

 return !filters.empty();
}



bool LexiconStorage_MySQL::FindLeftFiltersByEntry( int id_language, int id_entry, lem::MCollect<LeftFilterInfo> & filters )
{
 filters.clear();

 lem::MemFormatter mem;
 mem.printf( "SELECT id_body, context_length FROM left_filter_selector WHERE id_entry=%d AND id_language=%d", id_entry, id_language );
 
 lem::Ptr<LS_ResultSet> rs( ListByQuery( mem.string() ) );
 while( rs->Fetch() )
  {
   LeftFilterInfo info;
   info.id_body = rs->GetInt(0);
   info.context_length = rs->GetInt(1);
   filters.push_back(info);
  }

 return !filters.empty();
}
*/




int LexiconStorage_MySQL::StoreWordAssoc_ByLemma( int src_location, int id_entry, int id_entry1, int score )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, id_entry1, score, id_entry2, link_type, link_entry, set_type, id_metaentry1, id_metaentry2 )"
             " VALUES (%d,%d,%d,%d,-1,-1,-1,-1,-1,-1)", src_location, id_entry, id_entry1, score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


int LexiconStorage_MySQL::StoreWordAssoc_ByMetaentry( int src_location, int id_entry, int id_metaentry1, int score )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, id_metaentry1, score, id_entry1, id_metaentry2, id_entry2, link_type, link_entry, set_type )"
             " VALUES (%d,%d,%d,%d,-1,-1,-1,-1,-1,-1)", src_location, id_entry, id_metaentry1, score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


int LexiconStorage_MySQL::StoreWordAssoc_ByLexem( int src_location, int id_entry, const lem::UCString & word1, int score )
{
 lem::UFString word_str( word1.c_str() );
 mysql_escape(word_str);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, word1, score, id_entry1, id_entry2, link_type, link_entry, set_type, id_metaentry1, id_metaentry2 )"
             " VALUES (%d,%d,'%us',%d,-1,-1,-1,-1,-1,-1,-1)", src_location, id_entry, word_str.c_str(), score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


int LexiconStorage_MySQL::StoreWordAssoc_ByThesaurusLink( int src_location, int id_entry, int link_type, int link_entry, int score )
{
 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, link_type, link_entry, score, id_entry1, id_entry2, set_type, id_metaentry1, id_metaentry2 )"
             " VALUES (%d,%d,%d,%d,%d,-1,-1,-1,-1,-1)", src_location, id_entry, link_type, link_entry, score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


int LexiconStorage_MySQL::StoreWordAssoc_BySet( int src_location, int id_entry, const lem::UCString & set_name, int set_type, int score )
{
 lem::UFString set_str( set_name.c_str() );
 mysql_escape(set_str);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO word_assoc( id_src, id_entry, set_name, set_type, score, id_entry1, id_entry2, link_type, link_entry, id_metaentry1, id_metaentry2 )"
             " VALUES (%d,%d,'%us',%d,%d,-1,-1,-1,-1,-1,-1)", src_location, id_entry, set_str.c_str(), set_type, score );
 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}


LS_ResultSet* LexiconStorage_MySQL::ListAssociationsForEntry( int id_entry )
{
 LEM_CHECKIT_Z( id_entry>=0 );
 return ListByQuery( lem::format_str("SELECT id FROM word_assoc WHERE id_entry=%d",id_entry) );
}


LS_ResultSet* LexiconStorage_MySQL::ListAssociatedEntries()
{
 return ListByQuery( "SELECT id FROM word_assoc" );
}


WordAssociation* LexiconStorage_MySQL::LoadAssocitation( int id )
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






LS_ResultSet* LexiconStorage_MySQL::ListPredicateTemplate()
{
 return ListByQuery( "SELECT id FROM predicate_template" );
}


PredicateTemplate* LexiconStorage_MySQL::LoadPredicateTemplate( int id )
{
 lem::Ptr<LS_ResultSet> rs( ListByQuery( lem::format_str( "SELECT src, params FROM predicate_template WHERE id=%d", id ) ) );
 lem::UFString src = rs->GetUFString(0);
 lem::UFString params = rs->GetUFString(1);
 PredicateTemplate * ret = new PredicateTemplate( id, src, params );
 return ret;
}


int LexiconStorage_MySQL::StorePredicateTemplate( const lem::UFString & src, const lem::MCollect<lem::UCString> & params )
{
 lem::UFString escaped(src);
 lem::mysql_escape(escaped);

 lem::UFString escaped_params;
 for( lem::Container::size_type i=0; i<params.size(); ++i )
  if( escaped_params.empty() )
   escaped_params.Add_Dirty( params[i].c_str() );
  else
   {
    escaped_params.Add_Dirty( L',' );
    escaped_params.Add_Dirty( params[i].c_str() );
   }

 lem::mysql_escape(escaped_params);

 lem::MemFormatter mem;
 mem.printf( "INSERT INTO predicate_template( src, params ) VALUES ( '%us', '%us' )", escaped.c_str(), escaped_params.c_str() );

 const int id = ExecuteAndReturnId( mem.string() );
 return id;
}





void LexiconStorage_MySQL::StoreOmonym( const lem::UCString & entry_name, int id_class )
{
 LEM_CHECKIT_Z( id_class!=UNKNOWN );
 LEM_CHECKIT_Z( !entry_name.empty() );

 lem::UFString escaped( entry_name.c_str() );
 lem::mysql_escape(escaped);

 lem::MemFormatter sql;
 sql.printf( "INSERT INTO omonym( entry_name, id_class ) VALUES ( '%us', %d )", escaped.c_str(), id_class );
 Execute(sql.string());

 return;
}


bool LexiconStorage_MySQL::IsOmonym( const lem::UCString & entry_name, int id_class )
{
 LEM_CHECKIT_Z( id_class!=UNKNOWN );
 LEM_CHECKIT_Z( !entry_name.empty() );

 lem::UFString escaped( entry_name.c_str() );
 lem::mysql_escape(escaped);

 lem::MemFormatter sql;
 sql.printf( "SELECT id FROM omonym WHERE entry_name='%us' AND id_class=%d", escaped.c_str(), id_class );
 return QueryInt(sql.string())!=-1;
}


LS_ResultSet* LexiconStorage_MySQL::ListOmonyms()
{
 return ListByQuery( "SELECT entry_name, id_class FROM omonym" );
}



#endif
