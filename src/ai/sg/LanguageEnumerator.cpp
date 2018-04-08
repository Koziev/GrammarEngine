#include <lem/solarix/Languages.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/LanguageEnumerator.h>

using namespace Solarix;

LanguageEnumerator::LanguageEnumerator(Languages *_langs, LexiconStorage *_db)
    : langs(_langs), db(_db), rs(nullptr)
{
}

LanguageEnumerator::~LanguageEnumerator()
{
    lem_rub_off(rs);
}


bool LanguageEnumerator::Fetch()
{
    if (rs == nullptr)
    {
        rs = db->ListLanguages();
    }

    return rs->Fetch();
}

int LanguageEnumerator::GetId()
{
    return rs->GetInt(0);
}

const SG_Language& LanguageEnumerator::GetItem()
{
    const int id = rs->GetInt(0);
    return (*langs)[id];
}
