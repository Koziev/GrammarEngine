#include <lem/smart_pointers.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/LanguageUsage.h>

using namespace Solarix;

LanguageUsage::LanguageUsage(SynGram * SG)
{
    sg = SG;
    storage = nullptr;
    return;
}

void LanguageUsage::Connect(LexiconStorage * Storage)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs_init);
#endif

    storage = Storage;

    id_default_input = id_default_output = UNKNOWN;
    id_langs.clear();
    id_input_langs.clear();
    id_output_langs.clear();
    loaded = false;

    return;
}


void LanguageUsage::Load()
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs);
#endif

    if (!loaded)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        loaded = true;

        std::unique_ptr<LS_ResultSet> rs(storage->ListLanguageUsage());
        while (rs->Fetch())
        {
            int id_language = rs->GetInt(0);
            bool is_input = rs->GetInt(1) == 1;
            bool is_output = rs->GetInt(2) == 1;
            bool is_default = rs->GetInt(3) == 1;

            if (id_langs.find(id_language) == UNKNOWN)
                id_langs.push_back(id_language);

            if (is_input)
                id_input_langs.push_back(id_language);

            if (is_output)
                id_output_langs.push_back(id_language);

            if (is_input && is_default)
                id_default_input = id_language;

            if (is_output && is_default)
                id_default_output = id_language;
        }
    }

    return;
}



int LanguageUsage::GetDefaultInputLanguage()
{
    Load();
    return id_default_input;
}

int LanguageUsage::GetDefaultOutputLanguage()
{
    Load();
    return id_default_output;
}

bool LanguageUsage::HasLanguage(int id_language)
{
    Load();
    return id_langs.find(id_language) != UNKNOWN;
}

void LanguageUsage::GetLanguages(lem::MCollect<int> &ids)
{
    Load();
    ids = id_langs;
    return;
}

void LanguageUsage::GetInputLanguages(lem::MCollect<int> &ids)
{
    Load();
    ids = id_input_langs;
    return;
}

void LanguageUsage::GetOutputLanguages(lem::MCollect<int> &ids)
{
    Load();
    ids = id_output_langs;
    return;
}
