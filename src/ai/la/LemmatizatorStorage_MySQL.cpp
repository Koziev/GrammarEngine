#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/smart_pointers.h>
#include <lem/unicode.h>
#include <lem/oformatter.h>
#include <lem/mysql_helpers.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/StorageConnection_MySQL.h>
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/LemmatizatorStorage_MySQL.h>

using namespace Solarix;

LemmatizatorStorage_MySQL::LemmatizatorStorage_MySQL( StorageConnection_MySQL *_cnx )
 : cnx(_cnx)
{
}

LemmatizatorStorage_MySQL::~LemmatizatorStorage_MySQL(void)
{
 cnx->Release();
 return;
}

int LemmatizatorStorage_MySQL::Lemmatize( const lem::UCString &word, lem::UCString &lemma )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 std::map<lem::UCString,lem::UCString>::const_iterator it = lemma1_cache.find(word);
 if( it!=lemma1_cache.end() )
  {
   lemma = it->second;
   return 1;
  }
 
 #if defined LEM_THREADS
 lem::Process::RWU_WriterGuard wlock(rlock);
 #endif

 it = lemma1_cache.find(word);
 if( it!=lemma1_cache.end() )
  {
   lemma = it->second;
   return 1;
  }

 lem::MemFormatter mem;
 mem.printf( "SELECT Coalesce( L.lemma, '' )"
             " FROM lexemes_1 X, lemmas L"
             " WHERE X.lexeme='%us' AND L.id=X.id_lemma", to_upper(word).c_str() );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard2(&c->cs);
 #endif

 lem::Ptr<LS_ResultSet> rs( cnx->Select( lem::to_utf8(mem.string())) );
 if( rs->Fetch() )
  {
   lemma = rs->GetUCString(0);
  }
 else
  {
   lemma = word;
  }

 lemma1_cache.insert( std::make_pair( word, lemma ) );

 return 1;
}

void LemmatizatorStorage_MySQL::Lemmatize(
                                          const lem::UCString &word,
                                          lem::MCollect<lem::UCString> &lemmas
                                         )
{
 lemmas.clear();

 lem::MemFormatter mem;
 mem.printf( "SELECT L.lemma"
             " FROM lexemes_n X, lemmas L"
             " WHERE X.lexeme='%us' AND L.id=X.id_lemma", to_upper(word).c_str() );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 lem::Ptr<LS_ResultSet> rs(cnx->Select(lem::to_utf8(mem.string())));
 while( rs->Fetch() )
  {
   lemmas.push_back( rs->GetUCString(0) );
  }

 if( lemmas.empty() )
  {
   lemmas.push_back(word);
  }

 return;
}


void LemmatizatorStorage_MySQL::Lemmatize( const lem::MCollect<lem::UCString> & words, lem::MCollect<lem::UCString> &lemmas )
{
 LEM_STOPIT;
 return;
}


#endif
