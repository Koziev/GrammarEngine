#include <lem/macros.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/PartsOfSpeech.h>
#include <lem/solarix/PartOfSpeechEnumerator.h>

using namespace Solarix;


PartOfSpeechEnumerator::PartOfSpeechEnumerator( LexiconStorage *_db, PartsOfSpeech * _p )
 : rs(nullptr), db(_db), p(_p)
{
}

PartOfSpeechEnumerator::~PartOfSpeechEnumerator()
{
 lem_rub_off(rs);
 return;
}

bool PartOfSpeechEnumerator::Fetch()
{
 if( rs==nullptr )
  {
   rs = db->ListPartsOfSpeech();
  }

 return rs->Fetch();
}

int PartOfSpeechEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const GramClass& PartOfSpeechEnumerator::GetItem()
{
 const int id = rs->GetInt(0);
 return (*p)[id]; 
}

