#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/macros.h>
#include <lem/solarix/lexem.h>
#include <lem/solarix/LexiconStorage_MySQL.h>
#include <lem/solarix/WordEntries_MySQL.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/LexemeEnumerator_MySQL.h>

using namespace Solarix;


LexemeEnumerator_MySQL::LexemeEnumerator_MySQL( WordEntries_MySQL *_entries, LS_ResultSet_MySQL *_rs )
 : rs(_rs), entries(_entries)
{
}


LexemeEnumerator_MySQL::~LexemeEnumerator_MySQL(void)
{
 lem_rub_off(rs);
 return;
}

    
bool LexemeEnumerator_MySQL::Fetch(void)
{
 return rs->Fetch();
}


const Lexem* LexemeEnumerator_MySQL::Get( Solarix::Lexem &lex )
{
 lex = Solarix::Lexem(rs->GetUCString(0));
 return entries->RegisterLexem(lex); 
}

#endif
