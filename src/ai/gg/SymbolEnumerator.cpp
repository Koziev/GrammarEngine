#include <lem/noncopyable.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/SymbolEnumerator.h>

using namespace Solarix;

SymbolEnumerator::SymbolEnumerator( Symbols *_symbols, LS_ResultSet *_rs )
 : symbols(_symbols), rs(_rs)
{
}

SymbolEnumerator::~SymbolEnumerator(void)
{
 delete rs;
}

bool SymbolEnumerator::Fetch(void)
{
 return rs->Fetch();
}

int SymbolEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const GG_Entry& SymbolEnumerator::GetItem(void)
{
 const int id = GetId();
 return (*symbols)[id];
}
