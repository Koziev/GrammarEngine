#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/Languages.h>

using namespace Solarix;

Languages::Languages(SynGram *_sg)
    :sg(_sg), db(nullptr)
{
}

void Languages::Connect(LexiconStorage *_db)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    db = _db;
    id2index.clear();
    name2id.clear();
    lang_ptr.clear();
    return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void Languages::LoadTxt(lem::Iridium::Macro_Parser &txtfile)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    SG_Language *lang = new SG_Language();
    lang->LoadTxt(UNKNOWN, txtfile, sg->GetDict().GetGraphGram());

    // Повтора объявления языков не допускаем
    int id_lang = Find(lang->GetName());
    if (id_lang != UNKNOWN)
    {
        const int ilang = id2index.find(id_lang)->second;

        if (!GetByIndex(ilang)->empty())
        {
            sg->GetIO().merr().printf("Language [%us] is already declared\n", lang->GetName().c_str());
            throw E_ParserError();
        }

        GetByIndex(ilang)->Copy_Definition(*lang);
        delete lang;
        db->StoreLanguage(*GetByIndex(ilang));
        return;
    }
    else
    {
        const int id = db->AddLanguage(*lang);
        name2id.insert(std::make_pair(lem::to_upper(lang->GetName()), id));
        id2index.insert(std::make_pair(id, CastSizeToInt(lang_ptr.size())));
        lang_ptr.push_back(lang);
        return;
    }
}
#endif


int Languages::Find(const lem::UCString &name)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    auto it = name2id.find(lem::to_upper(name));
    if (it == name2id.end())
    {
        const int id = db->FindLanguage(name);
        if (id == UNKNOWN)
            return UNKNOWN;
        else
        {
            SG_Language *lang = new SG_Language();
            if (db->GetLanguage(id, *lang))
            {
                name2id.insert(std::make_pair(lem::to_upper(name), id));
                id2index.insert(std::make_pair(id, CastSizeToInt(lang_ptr.size())));
                lang_ptr.push_back(lang);
                return id;
            }
            else
            {
                return UNKNOWN;
            }
        }
    }
    else
    {
        return it->second;
    }
}

const SG_Language& Languages::operator[](int id)
{
    LEM_CHECKIT_Z(id != UNKNOWN);

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs);
#endif

    auto it = id2index.find(id);
    if (it == id2index.end())
    {
        SG_Language *lang = new SG_Language();
        if (db->GetLanguage(id, *lang))
        {
            name2id.insert(std::make_pair(lem::to_upper(lang->GetName()), id));
            id2index.insert(std::make_pair(id, CastSizeToInt(lang_ptr.size())));
            lang_ptr.push_back(lang);
            return *lang;
        }
        else
        {
            lem::MemFormatter mem;
            mem.printf("Could not load the language id=%d", id);
            throw E_BaseException(mem.string());
        }
    }
    else
    {
        return *GetByIndex(it->second);
    }
}

LanguageEnumerator* Languages::Enumerate()
{
    return new LanguageEnumerator(this, db);
}

SG_Language* Languages::GetByIndex(int i)
{
    return lang_ptr[i];
}

int Languages::Count()
{
    return db->CountLanguages();
}
