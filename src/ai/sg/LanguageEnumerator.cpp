#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/Languages.h>
#include <lem/solarix/LexiconStorage.h>

using namespace Solarix;

LanguageEnumerator::LanguageEnumerator( Languages *_langs, LexiconStorage *_db )
 : langs(_langs), db(_db), rs(NULL)
{
}

LanguageEnumerator::~LanguageEnumerator(void)
{
 lem_rub_off(rs);
}


bool LanguageEnumerator::Fetch(void)
{
 if(rs==NULL)
  {
   rs = db->ListLanguages();
  }

 return rs->Fetch();
}

int LanguageEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const SG_Language& LanguageEnumerator::GetItem(void)
{
 const int id = rs->GetInt(0);
 return (*langs)[id];
}
