#include <lem/noncopyable.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/Alphabets.h>
#include <lem/solarix/AlphabetEnumerator.h>

using namespace Solarix;

AlphabetEnumerator::AlphabetEnumerator( Alphabets *_alphabets, LS_ResultSet *_rs )
 : alphabets(_alphabets), rs(_rs)
{
}

AlphabetEnumerator::~AlphabetEnumerator(void)
{
 delete rs;
}

bool AlphabetEnumerator::Fetch(void)
{
 return rs->Fetch();
}

int AlphabetEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const Alphabet& AlphabetEnumerator::GetItem(void)
{
 const int id = GetId();
 return (*alphabets)[id];
}
