#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/Charpos2EntryEnumerator_SQL.h>

using namespace Solarix;


Charpos2EntryEnumerator_SQL::Charpos2EntryEnumerator_SQL( LS_ResultSet * _rs)
 : rs(_rs)
{}

Charpos2EntryEnumerator_SQL::~Charpos2EntryEnumerator_SQL(void)
{
 delete rs;
 return;
}

bool Charpos2EntryEnumerator_SQL::Fetch(void)
{
 return rs->Fetch();
}

lem::uint32_t Charpos2EntryEnumerator_SQL::GetChar(void)
{
 const lem::uint32_t charpos = (lem::uint32_t)rs->GetInt(0);
 return 0x00ffffff & charpos;
}


int Charpos2EntryEnumerator_SQL::GetPos(void)
{
 const lem::uint32_t charpos = (lem::uint32_t)rs->GetInt(0);
 return (0xff000000&charpos) >> 24;
}
