// LC->17.04.2018

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/LA_SynPatternTrees.h>

using namespace Solarix;

LA_SynPatternTrees::LA_SynPatternTrees(Solarix::Dictionary *Dict)
{
    dict = Dict;
    storage = nullptr;
    return;
}

LA_SynPatternTrees::~LA_SynPatternTrees()
{
    Delete();
    return;
}


void LA_SynPatternTrees::Delete()
{
    for (auto &x : pattern_tree)
    {
        delete x.second;
    }

    for (auto x : named_filter_trees)
    {
        delete x;
    }

    pattern_tree.clear();
    named_filter_trees.clear();

    id2filter.clear();
    id2name.clear();

    return;
}



void LA_SynPatternTrees::Connect(LexiconStorage *Storage)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs_init);
#endif

    Delete();
    storage = Storage;

    return;
}



const SynPatternTreeNode& LA_SynPatternTrees::GetDefaultFilter(int id_language)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_default_filter);
#endif

    // Просматриваем кэш, возможно нужное дерево для указанного языка уже загружено.
    for (lem::Container::size_type i = 0; i < pattern_tree.size(); ++i)
    {
        if (pattern_tree[i].first == id_language)
            return *pattern_tree[i].second;
    }

    // Нет, в кэше нет. Сейчас надо поставить блокировку от имени писателя и снова поискать в кэше,
    // а потом в случае промаха подгружать из БД.
#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    for (lem::Container::size_type i = 0; i < pattern_tree.size(); ++i)
    {
        if (pattern_tree[i].first == id_language)
            return *pattern_tree[i].second;
    }

    std::pair<SynPatternTreeNode*, lem::UCString> tree = std::make_pair<SynPatternTreeNode*, lem::UCString>(NULL, lem::UCString());

    const int id = storage->FindSynPatternTree(id_language, L"", SOLID_PATTERN);
    if (id == UNKNOWN)
    {
        tree.first = new SynPatternTreeNode();
    }
    else
    {
        tree = storage->GetSynPatternTree(id);
    }

    LEM_CHECKIT_Z(tree.second.empty());

    tree.first->Link(dict->GetLexAuto().GetFunctions().Get());

    pattern_tree.push_back(std::make_pair(id_language, tree.first));
    id2name.insert(std::make_pair(id, tree.second));
    id2filter.insert(std::make_pair(id, tree.first));

    return *tree.first;
}







const SynPatternTreeNode& LA_SynPatternTrees::GetIncompleteFilter(int id_language)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_default_filter);
#endif

    for (lem::Container::size_type i = 0; i < incomplete_pattern_tree.size(); ++i)
    {
        if (incomplete_pattern_tree[i].first == id_language)
            return *incomplete_pattern_tree[i].second;
    }

#if defined LEM_THREADS
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    for (lem::Container::size_type i = 0; i < incomplete_pattern_tree.size(); ++i)
    {
        if (incomplete_pattern_tree[i].first == id_language)
            return *incomplete_pattern_tree[i].second;
    }

    std::pair<SynPatternTreeNode*, lem::UCString> tree(nullptr, lem::UCString());

    const int id = storage->FindSynPatternTree(id_language, L"", INCOMPLETE_PATTERN);
    if (id == UNKNOWN)
    {
        tree.first = new SynPatternTreeNode();
    }
    else
    {
        tree = storage->GetSynPatternTree(id);
    }

    LEM_CHECKIT_Z(tree.second.empty());

    tree.first->Link(dict->GetLexAuto().GetFunctions().Get());
    incomplete_pattern_tree.push_back(std::make_pair(id_language, tree.first));

    id2name.insert(std::make_pair(id, tree.second));
    id2filter.insert(std::make_pair(id, tree.first));

    return *tree.first;
}



const lem::UCString & LA_SynPatternTrees::GetPatternName(int id_tree)
{
    if (id2name.find(id_tree) == id2name.end())
    {
        LEM_STOPIT;
        return id2name.begin()->second;
    }
    else
        return id2name.find(id_tree)->second;
}


const SynPatternTreeNode& LA_SynPatternTrees::GetNamedFilter(int id_tree)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_named);
#endif

    // Сначала смотрим в кэше, возможно мы уже загрузили это дерево.
    auto it = id2filter.find(id_tree);
    if (it != id2filter.end())
    {
        // да, нашли.
        return *it->second;
    }
    else
    {
        // В кэше нету. Так как в этот самый момент другой поток может начать загрузку в кэш этого же
        // дерева, то мы сначала поставим блокировку писателя, затем еще раз поищем в кэше, и уже затем
        // начнем подгрузку дерева из хранилища и сохранение его в кэше.
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        it = id2filter.find(id_tree);
        if (it != id2filter.end())
        {
            // ну вот, другой поток успел загрузить дерево в кэш.
            return *it->second;
        }

        std::pair<SynPatternTreeNode*, lem::UCString> info = storage->GetSynPatternTree(id_tree);

        LEM_CHECKIT_Z(!info.second.empty());
        info.first->Link(dict->GetLexAuto().GetFunctions().Get());

        named_filter_trees.push_back(info.first);
        id2filter.insert(std::make_pair(id_tree, info.first));
        id2name.insert(std::make_pair(id_tree, info.second));

        return *info.first;
    }
}


void LA_SynPatternTrees::StoreFilterTree(int id, const lem::UCString &name, SynPatternTreeNode *tree, int id_language, int pattern_type)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_named);
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    if (name.empty())
    {
        if (pattern_type == LA_SynPatternTrees::SOLID_PATTERN)
        {
            for (lem::Container::size_type i = 0; i < pattern_tree.size(); ++i)
            {
                if (pattern_tree[i].first == id_language)
                {
                    lem::MemFormatter mem;
                    mem.printf("Filter tree is already stored for language=%d", id_language);
                    throw lem::E_BaseException(mem.string());
                }
            }

            pattern_tree.push_back(std::make_pair(id_language, tree));
        }
        else if (pattern_type == LA_SynPatternTrees::INCOMPLETE_PATTERN)
        {
            for (lem::Container::size_type i = 0; i < incomplete_pattern_tree.size(); ++i)
            {
                if (incomplete_pattern_tree[i].first == id_language)
                {
                    lem::MemFormatter mem;
                    mem.printf("Incomplete tree is already stored for language=%d", id_language);
                    throw lem::E_BaseException(mem.string());
                }
            }

            incomplete_pattern_tree.push_back(std::make_pair(id_language, tree));
        }
        else
        {
            LEM_STOPIT;
        }
    }
    else
    {
        lem::UCString uname(lem::to_upper(name));

        named_filter_trees.push_back(tree);
        id2filter.insert(std::make_pair(id, tree));
        id2name.insert(std::make_pair(id, uname));
    }

    storage->StoreSynPatternTree(id_language, name, id, tree, pattern_type);

    return;
}
