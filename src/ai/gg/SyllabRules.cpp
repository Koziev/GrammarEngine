#include <lem/solarix/SyllabRule.h>

using namespace Solarix;


SyllabRules::SyllabRules(void)
{
    storage = nullptr;
}



void SyllabRules::Connect(AlphabetStorage * _storage)
{
    LEM_CHECKIT_Z(_storage != nullptr);
    storage = _storage;
    rules.clear();
    lang2rules.clear();
    return;
}


const SyllabRulesForLanguage & SyllabRules::GetRules(int id_language)
{
    LEM_CHECKIT_Z(id_language != UNKNOWN);

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs);
#endif 

    auto it = lang2rules.find(id_language);
    if (it == lang2rules.end())
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        it = lang2rules.find(id_language);
        if (it == lang2rules.end())
        {
            SyllabRulesForLanguage * x = new SyllabRulesForLanguage(id_language);
            x->Load(storage);
            lang2rules.insert(std::make_pair(id_language, x));
            return *x;
        }
        else
        {
            return *it->second;
        }
    }
    else
    {
        return *it->second;
    }
}

