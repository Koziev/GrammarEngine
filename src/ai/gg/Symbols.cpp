#include <lem/macro_parser.h>
#include <lem/solarix/SymbolEnumerator.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/SymbolClasses.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/Symbols.h>

using namespace Solarix;

Symbols::Symbols(GraphGram *_gg)
    : storage(nullptr), gg(_gg), e_count(UNKNOWN), f_count(UNKNOWN)
{
}


Symbols::~Symbols(void)
{
    for (auto symbol : symbols)
    {
        delete symbol;
    }

#if defined SOL_LOADTXT && defined SOL_COMPILER
    for (auto e : compiled_entries)
    {
        delete e;
    }
#endif

    return;
}


void Symbols::Connect(AlphabetStorage *_storage)
{
    storage = _storage;

    for (auto symbol : symbols)
    {
        delete symbol;
    }

#if defined SOL_LOADTXT && defined SOL_COMPILER
    for (auto e : compiled_entries)
    {
        delete e;
    }
    compiled_entries.clear();
#endif 

    symbols.clear();

    id2symbol.clear();
    char2proj.clear();
    char2projs.clear();

    e_count = UNKNOWN;
    f_count = UNKNOWN;

    return;
}

int Symbols::Count(void)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_count);
#endif

    if (e_count == UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        if (e_count == UNKNOWN)
        {
            e_count = storage->CountEntries();
        }
    }

    return e_count;
}

int Symbols::CountForms(void)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_count);
#endif

    if (f_count == UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        if (f_count == UNKNOWN)
        {
            f_count = storage->CountEntryForms();
        }
    }

    return f_count;
}


SymbolEnumerator* Symbols::Enumerate(void)
{
    LS_ResultSet * rs = storage->ListEntries();
    return new SymbolEnumerator(this, rs);
}


const GG_Entry& Symbols::operator[](int id)
{
    if (id == UNKNOWN)
        throw lem::E_BaseException(L"Can not retrieve symbol with id=-1");

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_chars1);
#endif

    auto it = id2symbol.find(id);
    if (it != id2symbol.end())
        return *it->second;

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    it = id2symbol.find(id);
    if (it != id2symbol.end())
        return *it->second;

    GG_Entry *e = storage->LoadEntry(id);
    symbols.push_back(e);
    id2symbol.insert(std::make_pair(id, e));
    return *e;
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void Symbols::LoadEntry(
    Macro_Parser& txtfile,
    bool is_extern,
    const Binarization_Options &options
)
{
    lem::Iridium::BSourceState entry_org = txtfile.tellp();

    GG_Entry * dummy = new GG_Entry;
    dummy->LoadTxt(txtfile, *gg, !is_extern);

    // Is this entry unique? Проверим уникальность данной буквостатьи.
    // Следует учитывать и грамматический класс, вообще говоря.
    int ie = UNKNOWN, idx = UNKNOWN;
    GG_Entry *found_e = nullptr;

    // Ищем среди статей для такого же языка!
    for (lem::Container::size_type i = 0; i < compiled_entries.size(); i++)
    {
        if (dummy->GetAlphabet() == compiled_entries[i]->GetAlphabet() && dummy->GetName() == compiled_entries[i]->GetName())
        {
            idx = i;
            ie = compiled_entries[i]->GetKey();
            found_e = compiled_entries[i];
            break;
        }
    }

    if (found_e == nullptr)
    {
        // It is unique. Теперь можем добавлять определение буквостатьи
        // в свои списки.

        if (dummy->IsRealized())
        {
            ie = storage->StoreEntry(*dummy);
            UpdateNoCharCache(dummy);
            dummy->SetKey(ie);
            id2symbol.insert(std::make_pair(ie, dummy));
        }

        compiled_entries.push_back(dummy);
    }
    else
    {
        // Redefinition encountered. It can mean:

        if (is_extern)
        {
            // Просто ещё раз прочитано объявление статьи.
            //
            // extern entry A : B        <- previous declaration
            //         :
            // extern entry A : B        <- this redeclaration
            delete dummy;
            return;
        }

        if (!is_extern && !found_e->IsRealized())
        {
            // extern entry A : B      <- declaration
            //        :
            // entry A : B { ... }     <- definition
            //
            // Встречена РЕАЛИЗАЦИЯ статьи, нужно заменить ей предыдущее объявление.
            // Переносим себе ключ объявления, так как на него уже могли быть
            // ссылки...

            delete found_e;
            compiled_entries[idx] = dummy;

            ie = storage->StoreEntry(*dummy);
            UpdateNoCharCache(dummy);
            dummy->SetKey(ie);
            id2symbol.insert(std::make_pair(ie, dummy));

            return;
        }

        if (!is_extern && found_e->IsRealized())
        {
            // Повторная реализация словарной статьи. Redeclaration means error.
            lem::Iridium::Print_Error(entry_org, txtfile);

            const UCString& class_name = gg->classes()[dummy->GetClass()].GetName();
            const UCString entry_name(dummy->GetNameWide());
            lem::MemFormatter err;
            err.printf("SymbolEntry [%us:%us] redefinition in Alphabet\n", class_name.c_str(), entry_name.c_str());
            throw lem::E_ParserError(err.string());
        }
    }

    return;
}
#endif

// В алфавит добавлен новый символ, сбросим список символов, которые НЕ
// входят в алфавит этого символа.
void Symbols::UpdateNoCharCache(GG_Entry *dummy)
{
    const int id_alphabet = dummy->GetAlphabet();
    LEM_CHECKIT_Z(id_alphabet != UNKNOWN);

#if defined LEM_THREADS
    lem::Process::RW_UniqueGuard locker(cs_for_alphabet);
#endif

    const int idx = for_alphabet.find(id_alphabet);
    if (idx != UNKNOWN)
    {
        std::set< lem::uint32_t > & nochars = *nochar_alphabet[idx];
        nochars.clear();
    }

    return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void Symbols::FinishCompilation(void)
{
    const lem::Container::size_type nentry = compiled_entries.size();

    // Все статьи должны быть РЕАЛИЗОВАНЫ!
    for (lem::Container::size_type ientry = 0; ientry < nentry; ientry++)
    {
        if (!compiled_entries[ientry]->IsRealized())
        {
            const lem::UCString & class_name = gg->classes()[compiled_entries[ientry]->GetClass()].GetName();
            lem::UCString entry_name = compiled_entries[ientry]->GetNameWide();
            gg->GetIO().merr().printf(
                "%vfDSymbolEntry [%us:%us] not realized in Alphabet.%vn\n"
                , class_name.c_str(), entry_name.c_str()
            );
            throw lem::E_ParserError();
        }
    }

    return;
}
#endif

const Word_Coord Symbols::FindSymbol(lem::uint32_t code)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_chars1);
#endif

    auto it = char2proj.find(code);
    if (it != char2proj.end())
        return it->second;

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    it = char2proj.find(code);
    if (it != char2proj.end())
        return it->second;

    lem::MCollect<Word_Coord> projs;
    storage->FindSymbol(code, projs);

    if (projs.empty())
        return Word_Coord(UNKNOWN, UNKNOWN);

    const Word_Coord &p = projs.front();
    char2proj.insert(std::make_pair(code, p));

    return p;
}


const Word_Coord Symbols::FindSymbol(lem::uint32_t code, int AlphabetID)
{
    if (AlphabetID == UNKNOWN)
        return FindSymbol(code);

    std::map<lem::uint32_t, Word_Coord> * char2proj_x = nullptr;
    std::set<lem::uint32_t> * nochar_x = nullptr;

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock1(cs_for_alphabet);
#endif

    int i = for_alphabet.find(AlphabetID);
    if (i == UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock1(rlock1);
#endif

        int i = for_alphabet.find(AlphabetID);
        if (i == UNKNOWN)
        {
            for_alphabet.push_back(AlphabetID);

            char2proj_x = new std::map<lem::uint32_t, Word_Coord>();
            char2proj_alphabet.push_back(char2proj_x);

            std::multimap<lem::uint32_t, Word_Coord> * char2projs_x;
            char2projs_x = new std::multimap<lem::uint32_t, Word_Coord>();
            char2projs_alphabet.push_back(char2projs_x);

            nochar_x = new std::set<lem::uint32_t>();
            nochar_alphabet.push_back(nochar_x);
        }
        else
        {
            char2proj_x = char2proj_alphabet[i];
            nochar_x = nochar_alphabet[i];
        }
    }
    else
    {
        char2proj_x = char2proj_alphabet[i];
        nochar_x = nochar_alphabet[i];
    }

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock2(cs_chars);
#endif

    auto it = char2proj_x->find(code);
    if (it != char2proj_x->end())
        return it->second;

    if (nochar_x->find(code) != nochar_x->end())
        return Word_Coord(UNKNOWN, UNKNOWN);

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock2(rlock2);
#endif

    it = char2proj_x->find(code);
    if (it != char2proj_x->end())
        return it->second;

    lem::MCollect<Word_Coord> projs;
    storage->FindSymbol(code, projs, AlphabetID);

    if (projs.empty())
    {
        nochar_x->insert(code);
        return Word_Coord(UNKNOWN, UNKNOWN);
    }

    const Word_Coord &p = projs.front();
    char2proj_x->insert(std::make_pair(code, p));

    return p;
}


const Word_Coord Symbols::FindSymbol(lem::uint32_t code, const lem::MCollect<int> &AlphabetID)
{
    if (AlphabetID.empty())
        return FindSymbol(code);

    std::map<lem::uint32_t, Word_Coord> * char2proj_x = nullptr;
    std::set<lem::uint32_t> * nochar_x = nullptr;

    for (lem::Container::size_type k = 0; k < AlphabetID.size(); ++k)
    {
#if defined LEM_THREADS
        lem::Process::RWU_ReaderGuard rlock1(cs_for_alphabet);
#endif

        const int id_alphabet = AlphabetID[k];

        int i = for_alphabet.find(id_alphabet);
        if (i == UNKNOWN)
        {
#if defined LEM_THREADS
            lem::Process::RWU_WriterGuard wlock1(rlock1);
#endif
            i = for_alphabet.find(id_alphabet);
            if (i == UNKNOWN)
            {
                for_alphabet.push_back(id_alphabet);

                char2proj_x = new std::map<lem::uint32_t, Word_Coord>();
                char2proj_alphabet.push_back(char2proj_x);

                std::multimap<lem::uint32_t, Word_Coord> * char2projs_x;
                char2projs_x = new std::multimap<lem::uint32_t, Word_Coord>();
                char2projs_alphabet.push_back(char2projs_x);

                nochar_x = new std::set<lem::uint32_t>();
                nochar_alphabet.push_back(nochar_x);
            }
            else
            {
                char2proj_x = char2proj_alphabet[i];
                nochar_x = nochar_alphabet[i];
            }
        }
        else
        {
            char2proj_x = char2proj_alphabet[i];
            nochar_x = nochar_alphabet[i];
        }

#if defined LEM_THREADS
        lem::Process::RWU_ReaderGuard rlock2(cs_chars);
#endif

        auto it = char2proj_x->find(code);
        if (it != char2proj_x->end())
            return it->second;

        if (nochar_x->find(code) != nochar_x->end())
            continue;

#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock2(rlock2);
#endif

        it = char2proj_x->find(code);
        if (it != char2proj_x->end())
            return it->second;

        MCollect<Word_Coord> projs;
        storage->FindSymbol(code, projs, id_alphabet);

        if (!projs.empty())
        {
            const Word_Coord &p = projs.front();
            char2proj_x->insert(std::make_pair(code, p));
            return p;
        }
        else
        {
            nochar_x->insert(code);
        }
    }

    return Word_Coord(UNKNOWN, UNKNOWN);
}


void Symbols::FindSymbol(lem::uint32_t code, MCollect<Word_Coord> &projs)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_chars);
#endif

    typedef std::multimap<lem::uint32_t, Word_Coord>::const_iterator IT;

    std::pair<IT, IT> r = char2projs.equal_range(code);

    if (r.first == r.second)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        r = char2projs.equal_range(code);

        if (r.first == r.second)
        {
            storage->FindSymbol(code, projs);

            for (lem::Container::size_type i = 0; i < projs.size(); ++i)
                char2projs.insert(std::make_pair(code, projs[i]));

            return;
        }
    }

    projs.clear();
    for (IT it = r.first; it != r.second; ++it)
    {
        projs.push_back(it->second);
    }

    return;
}


void Symbols::FindSymbol(lem::uint32_t code, MCollect<Word_Coord> &projs, int AlphabetID)
{
    std::multimap<lem::uint32_t, Word_Coord> * char2projs_x = nullptr;

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock1(cs_for_alphabet);
#endif

    int i = for_alphabet.find(AlphabetID);
    if (i == UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock1(rlock1);
#endif

        i = for_alphabet.find(AlphabetID);
        if (i == UNKNOWN)
        {
            for_alphabet.push_back(AlphabetID);

            std::map<lem::uint32_t, Word_Coord> * char2proj_x;
            char2proj_x = new std::map<lem::uint32_t, Word_Coord>();
            char2proj_alphabet.push_back(char2proj_x);

            char2projs_x = new std::multimap<lem::uint32_t, Word_Coord>();
            char2projs_alphabet.push_back(char2projs_x);
        }
        else
        {
            char2projs_x = char2projs_alphabet[i];
        }
    }
    else
    {
        char2projs_x = char2projs_alphabet[i];
    }

    typedef std::multimap<lem::uint32_t, Word_Coord>::const_iterator IT;

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock2(cs_chars);
#endif

    std::pair<IT, IT> r = char2projs_x->equal_range(code);
    if (r.first == r.second)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock2(rlock2);
#endif

        r = char2projs_x->equal_range(code);
        if (r.first != r.second)
        {
            projs.clear();
            for (IT it = r.first; it != r.second; ++it)
            {
                projs.push_back(it->second);
            }
        }
        else
        {
            storage->FindSymbol(code, projs, AlphabetID);

            for (auto proj : projs)
            {
                char2projs_x->insert(std::make_pair(code, proj));
            }
        }
    }
    else
    {
        projs.clear();
        for (IT it = r.first; it != r.second; ++it)
        {
            projs.push_back(it->second);
        }
    }

    return;
}


void Symbols::FindSymbol(
    lem::uint32_t code,
    MCollect<Word_Coord> &projs,
    const lem::MCollect<int> & AlphabetID
)
{
    std::multimap<lem::uint32_t, Word_Coord> * char2projs_x = nullptr;

    for (lem::Container::size_type k = 0; k < AlphabetID.size(); ++k)
    {
#if defined LEM_THREADS
        lem::Process::RWU_ReaderGuard rlock1(cs_for_alphabet);
#endif

        int i = for_alphabet.find(AlphabetID[k]);
        if (i == UNKNOWN)
        {
#if defined LEM_THREADS
            lem::Process::RWU_WriterGuard wlock1(rlock1);
#endif

            i = for_alphabet.find(AlphabetID[k]);
            if (i == UNKNOWN)
            {
                for_alphabet.push_back(AlphabetID[k]);

                std::map<lem::uint32_t, Word_Coord> * char2proj_x;
                char2proj_x = new std::map<lem::uint32_t, Word_Coord>();
                char2proj_alphabet.push_back(char2proj_x);

                char2projs_x = new std::multimap<lem::uint32_t, Word_Coord>();
                char2projs_alphabet.push_back(char2projs_x);
            }
            else
            {
                char2projs_x = char2projs_alphabet[i];
            }
        }
        else
        {
            char2projs_x = char2projs_alphabet[i];
        }

#if defined LEM_THREADS
        lem::Process::RWU_ReaderGuard rlock2(cs_chars);
#endif

        typedef std::multimap<lem::uint32_t, Word_Coord>::const_iterator IT;

        std::pair<IT, IT> r = char2projs_x->equal_range(code);
        if (r.first == r.second)
        {
#if defined LEM_THREADS
            lem::Process::RWU_WriterGuard wlock2(rlock2);
#endif
            r = char2projs_x->equal_range(code);
            if (r.first == r.second)
            {
                storage->FindSymbol(code, projs, AlphabetID[k]);

                for (lem::Container::size_type i = 0; i < projs.size(); ++i)
                    char2projs_x->insert(std::make_pair(code, projs[i]));
            }
            else
            {
                projs.clear();
                for (IT it = r.first; it != r.second; ++it)
                {
                    projs.push_back(it->second);
                }
            }
        }
        else
        {
            projs.clear();
            for (IT it = r.first; it != r.second; ++it)
            {
                projs.push_back(it->second);
            }
        }
    }

    return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
int Symbols::FindEntry(int id_class, lem::uint32_t code)
{
    for (auto e : compiled_entries)
    {
        if (e->GetClass() == id_class && e->GetName() == code)
        {
            return e->GetKey();
        }
    }

    return UNKNOWN;
}
#endif 
