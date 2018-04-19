#include <lem/oformatter.h>
#include <lem/solarix/lexem.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/ExactWordEntryLocator.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/WordEntries_SQL.h>

#if defined SOL_LOADTXT
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#endif

using namespace Solarix;

WordEntries_SQL::WordEntries_SQL(SynGram &_sg, const Dictionary_Config &cfg)
    : sg(_sg)
#if defined SOL_LOADTXT
    , ml_ref(cfg.ldsize)
    , coord_ref(1024)
#endif
{
    max_multilexem_len = UNKNOWN;
    return;
}


WordEntries_SQL::~WordEntries_SQL()
{
}


void WordEntries_SQL::CreateDefaultEntries()
{
}


int WordEntries_SQL::GetMaxMultilexemLen()
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_multilexem);
#endif

    if (max_multilexem_len == UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        if (max_multilexem_len == UNKNOWN)
        {
            max_multilexem_len = GetMaxMultilexemLen_Impl();
        }
    }

    return max_multilexem_len;
}



bool WordEntries_SQL::IsMultilexemHead(const lem::UCString &word, MultiLexemInfo &info)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_multilexem);
#endif

    auto it = multilexem_head.find(word);
    if (it != multilexem_head.end())
    {
        info = it->second;
        return true;
    }

    if (not_multilexem_head.find(word) != not_multilexem_head.end())
    {
        return false;
    }

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    it = multilexem_head.find(word);

    if (it == multilexem_head.end() && not_multilexem_head.find(word) == not_multilexem_head.end())
    {
        const bool r = IsMultilexemHead_Impl(word, info);

        if (r)
        {
            multilexem_head.insert(std::make_pair(word, info));
        }
        else
        {
            not_multilexem_head.insert(word);
        }

        return r;
    }
    else
    {
        it = multilexem_head.find(word);
        if (it != multilexem_head.end())
        {
            info = it->second;
            return true;
        }

        if (not_multilexem_head.find(word) == not_multilexem_head.end())
        {
            // внесем ее как не-мультилексему
            not_multilexem_head.insert(word);
        }

        return false;
    }
}


bool WordEntries_SQL::IsMultilexemForm(const Solarix::Lexem &lex)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_multilexem);
#endif

    if (multilexems.find(lex) != multilexems.end())
        return true;

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    if (multilexems.find(lex) != multilexems.end())
        return true;

    const bool ok = IsMultilexemForm_Impl(lex);

    if (ok)
        multilexems.insert(lex);

    return ok;
}






bool WordEntries_SQL::PreferPrefixSearch()
{
    return false;
}



int WordEntries_SQL::FindEntry(const lem::UCString &word_name, int id_class)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_entry_lookup);
#endif

    auto it = entry_class_lookup.find(std::make_pair(word_name, id_class));
    if (it != entry_class_lookup.end())
        return it->second;

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    it = entry_class_lookup.find(std::make_pair(word_name, id_class));
    if (it != entry_class_lookup.end())
        return it->second;

    const int ekey = FindEntry_Impl(word_name, id_class);
    entry_class_lookup.insert(std::make_pair(std::make_pair(word_name, id_class), ekey));

    return ekey;
}


const SG_Entry& WordEntries_SQL::GetEntry(int ekey)
{
    return LoadEntryFromDb(ekey);
}


SG_Entry& WordEntries_SQL::GetEntryForChange(int ekey)
{
    return LoadEntryFromDb(ekey);
}



int WordEntries_SQL::CreateEntry(const lem::UCString &ename, int id_class)
{
    LEM_STOPIT;
    return UNKNOWN;
}




int WordEntries_SQL::AddEntry(SG_Entry *new_entry)
{
#if defined SOL_LOADTXT && defined SOL_COMPILER
    if (new_entry->IsRealized())
    {
        LEM_STOPIT;
    }
#else
    LEM_STOPIT;
#endif

    return UNKNOWN;
}


const Lexem* WordEntries_SQL::AddLexeme(const Solarix::Lexem &lex)
{
    const int id_lexem = RegisterLexemeInDatabase(lex);
    return RegisterLexemeInCache(lex);
}



const CP_Array* WordEntries_SQL::AddCoordPairs(const CP_Array &x)
{
    if (!x.empty())
    {
        lem::UFString int_pairs, str_pairs;

        sg.SerializeCoords(x, int_pairs, false);
        sg.SerializeCoords(x, str_pairs, false);

        int_pairs.re_clear();
        str_pairs.re_clear();

        const int id_pairs = RegisterCoordPairsInDatabase(int_pairs, str_pairs);
    }

    return RegisterCoordPairsInCache(x);
}



const CP_Array* WordEntries_SQL::RegisterCoordPairsInCache(const CP_Array & pairs)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&cs0);
#endif

    return coord_ref.Add(pairs);
}





const Lexem* WordEntries_SQL::ReattachLexeme(const Lexem *ptr)
{
    return ptr;
}


const CP_Array* WordEntries_SQL::ReattachCoordPairs(const CP_Array *ptr)
{
    return ptr;
}


void WordEntries_SQL::PrepareForMerging()
{
    return;
}


void WordEntries_SQL::CommitCompilation(lem::OFormatter &err)
{
    return;
}

CharNode* WordEntries_SQL::GetPrefixTreeForAllLanguages()
{
    LEM_STOPIT;
    return nullptr;
}


CharNode* WordEntries_SQL::GetPrefixTree(const std::set<int>& allowed_langs)
{
    LEM_STOPIT;
    return nullptr;
}


void WordEntries_SQL::ReplaceEntry(int ekey, SG_Entry *dummy)
{
    LEM_STOPIT;
    return;
}


void WordEntries_SQL::PostRead(lem::Iridium::Macro_Parser &txtfile, const Binarization_Options &options)
{
    return;
}


void WordEntries_SQL::LoadBin(lem::Stream &bin)
{
    return;
}


void WordEntries_SQL::SaveBin(lem::Stream &bin) const
{
    return;
}


void WordEntries_SQL::DetailedReport(lem::OFormatter &txtfile)
{
    return;
}


LD_Seeker* WordEntries_SQL::Get_Seeker()
{
    LEM_STOPIT;
    return nullptr;
}


#if defined SOL_LOADBIN
LD_Seeker* WordEntries_SQL::Load_Seeker(lem::Stream &bin)
{
    LEM_STOPIT;
    return nullptr;
}
#endif


const lem::IntCollect& WordEntries_SQL::GetUEntries()
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_uentries);
#endif

    if (uentries_loaded == 0)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        if (uentries_loaded == 0)
        {
            GetUEntries_Impl();
            uentries_loaded = 1;
        }
    }

    return uentries;
}



int WordEntries_SQL::GetPredefinedEntryKey(int index)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_uentries);
#endif

    auto it = predefined.find(index);
    if (it != predefined.end())
        return it->second;

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    it = predefined.find(index);
    if (it != predefined.end())
        return it->second;

    const int ret = GetPredefinedEntryKey_Impl(index);
    LEM_CHECKIT_Z(ret != UNKNOWN);
    predefined.insert(std::make_pair(index, ret));

    return ret;
}


int WordEntries_SQL::FindQuantorEntry(int id_class)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_uentries);
#endif

    auto it = quantors.find(id_class);
    if (it != quantors.end())
        return it->second;

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    it = quantors.find(id_class);
    if (it != quantors.end())
        return it->second;

    const int ret = FindQuantorEntry_Impl(id_class);
    quantors.insert(std::make_pair(id_class, ret));

    LEM_CHECKIT_Z(ret != UNKNOWN);
    return ret;
}




const Solarix::Lexem* WordEntries_SQL::RegisterLexem(const Solarix::Lexem &lex)
{
    return RegisterLexemeInCache(lex);
}


const Solarix::Lexem* WordEntries_SQL::RegisterLexemeInCache(const Solarix::Lexem &lex)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_lexemes);
#endif

    auto it = lexemes_map.find(lex);
    if (it != lexemes_map.end())
        return lexemes[it->second];

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    it = lexemes_map.find(lex);
    if (it != lexemes_map.end())
        return lexemes[it->second];

    Lexem *ptr = new Lexem(lex);
    const int idx = CastSizeToInt(lexemes.size());
    lexemes.push_back(ptr);
    lexemes_map.insert(std::make_pair(lex, idx));
    return ptr;
}


int WordEntries_SQL::GetUnknownEntryKey()
{
    const lem::IntCollect &u_entry = GetUEntries();

    for (lem::Container::size_type i = 0; i < u_entry.size(); ++i)
    {
        const SG_Entry &e = GetEntry(u_entry[i]);
        if (e.GetName() == SOL_UNKNOWN_ENTRY2)
            return u_entry[i];
    }

    LEM_STOPIT;
    return UNKNOWN;
}




SG_Entry& WordEntries_SQL::LoadEntryFromDb(int ekey)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_entries);
#endif

    auto it = entries_map.find(ekey);
    if (it != entries_map.end())
        return *it->second;

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    it = entries_map.find(ekey);
    if (it != entries_map.end())
        return *it->second;

    SG_Entry * e = LoadEntryFromDb_Impl(ekey);

    e->PrepareAfterLoadingFromDatabase(sg);

    entries.push_back(e);
    entries_map.insert(std::make_pair(ekey, e));

    return *e;
}
