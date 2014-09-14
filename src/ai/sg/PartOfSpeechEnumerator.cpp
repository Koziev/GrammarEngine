#include <lem/macros.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/PartsOfSpeech.h>
#include <lem/solarix/PartOfSpeechEnumerator.h>

using namespace Solarix;


PartOfSpeechEnumerator::PartOfSpeechEnumerator( LexiconStorage *_db, PartsOfSpeech * _p )
 : rs(NULL), db(_db), p(_p)
{
}

PartOfSpeechEnumerator::~PartOfSpeechEnumerator(void)
{
 lem_rub_off(rs);
 return;
}

bool PartOfSpeechEnumerator::Fetch(void)
{
 if( rs==NULL )
  {
   rs = db->ListPartsOfSpeech();
  }

 return rs->Fetch();
}

int PartOfSpeechEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const GramClass& PartOfSpeechEnumerator::GetItem(void)
{
 const int id = rs->GetInt(0);
 return (*p)[id]; 
}

