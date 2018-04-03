#include <lem/oformatter.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/CharOperationEnumerator.h>
#include <lem/solarix/GG_CharOperation.h>
#include <lem/solarix/GG_CharOperations.h>

using namespace Solarix;

GG_CharOperations::GG_CharOperations(GraphGram * GG)
{
    gg = GG;
    storage = nullptr;
    return;
}

GG_CharOperations::~GG_CharOperations(void)
{
    Delete();
    return;
}

void GG_CharOperations::Delete(void)
{
    for (auto oper : opers)
    {
        delete oper;
    }

    opers.clear();
    name2oper.clear();
    id2oper.clear();
    return;
}



void GG_CharOperations::Connect(AlphabetStorage * Storage)
{
    LEM_CHECKIT_Z(Storage != nullptr);

#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs_init);
#endif

    Delete();
    storage = Storage;
    return;
}

const GG_CharOperation* GG_CharOperations::operator[](const lem::UCString &name)
{
    LEM_CHECKIT_Z(!name.empty());

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs);
#endif

    std::map< lem::UCString, const GG_CharOperation *>::const_iterator it = name2oper.find(lem::to_upper(name));
    if (it == name2oper.end())
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        const int id = storage->FindCharOperation(name);
        if (id == UNKNOWN)
        {
            lem::MemFormatter mem;
            mem.printf("Can not find character operation %us", name.c_str());
            throw lem::E_BaseException(mem.string());
        }
        else
        {
            GG_CharOperation *x = storage->GetCharOperation(id);
            opers.push_back(x);
            name2oper.insert(std::make_pair(lem::to_upper(name), x));
            id2oper.insert(std::make_pair(id, x));
            return x;
        }
    }
    else
    {
        return it->second;
    }
}


const GG_CharOperation* GG_CharOperations::operator[](int id)
{
    LEM_CHECKIT_Z(id != UNKNOWN);

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs);
#endif

    auto it = id2oper.find(id);
    if (it == id2oper.end())
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        it = id2oper.find(id);
        if (it == id2oper.end())
        {
            GG_CharOperation *x = storage->GetCharOperation(id);
            opers.push_back(x);
            id2oper.insert(std::make_pair(id, x));
            name2oper.insert(std::make_pair(lem::to_upper(x->GetName()), x));
            return x;
        }
        else
            return it->second;
    }
    else
    {
        return it->second;
    }
}



CharOperationEnumerator* GG_CharOperations::ListOperations(void)
{
    return new CharOperationEnumerator(storage->ListCharOperations(), this);
}
