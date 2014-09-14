#include <lem/macros.h>
#include <lem/stl.h>
#include <lem/solarix/lexem.h>
#include <lem/solarix/LexiconStorage_SQLITE.h>
#include <lem/solarix/WordEntries_SQLite.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/LexemeEnumerator_SQLite.h>

using namespace Solarix;


LexemeEnumerator_SQLite::LexemeEnumerator_SQLite( WordEntries_SQLite *_entries, LS_ResultSet_SQLITE *_rs )
 : rs(_rs), entries(_entries)
{
}


LexemeEnumerator_SQLite::~LexemeEnumerator_SQLite(void)
{
 lem_rub_off(rs);
 return;
}

    
bool LexemeEnumerator_SQLite::Fetch(void)
{
 return rs->Fetch();
}


const Lexem* LexemeEnumerator_SQLite::Get( Solarix::Lexem &lex )
{
 lex = Solarix::Lexem(rs->GetUCString(0));
 return entries->RegisterLexem(lex); 
}
