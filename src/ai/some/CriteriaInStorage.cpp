#include <lem/macro_parser.h>
#include <lem/solarix/CriteriaStorage.h>
#include <lem/solarix/CriterionEnumerator_SQL.h>
#include <lem/solarix/CriteriaInStorage.h>

using namespace Solarix;
using namespace lem::Iridium;

CriteriaInStorage::CriteriaInStorage()
{}

void CriteriaInStorage::Connect(CriteriaStorage *_storage)
{
    storage = _storage;
    list.clear();
    name2id.clear();
    id2x.clear();
    return;
}

#if defined SOL_LOADTXT
void CriteriaInStorage::LoadTxt(const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile)
{
    BSourceState begin = txtfile.tellp();
    Criterion *to_add = new Criterion(io, txtfile);

    if (Find(to_add->GetName()) != UNKNOWN)
    {
        // Повторное определение параметра.
        io.merr().printf(
            "Criterion [%us] is already defined\n"
            , to_add->GetName().c_str()
        );
        Print_Error(begin, txtfile);
        throw lem::E_ParserError();
    }

    int id = storage->StoreCriterion(*to_add);
    name2id.insert(std::make_pair(lem::to_upper(to_add->GetName()), id));

    id2x.insert(std::make_pair(id, to_add));
    list.push_back(to_add);

    return;
}
#endif


int CriteriaInStorage::Find(const lem::UCString &name)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    lem::UCString uname(lem::to_upper(name));
    auto it = name2id.find(uname);
    if (it != name2id.end())
    {
        return it->second;
    }

    const int id = storage->FindCriterion(name);

    if (id != UNKNOWN)
        name2id.insert(std::make_pair(uname, id));

    return id;
}


const Criterion& CriteriaInStorage::operator[](int id)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    auto it = id2x.find(id);
    if (it != id2x.end())
        return *it->second;

    Criterion * x = storage->GetCriterion(id);
    id2x.insert(std::make_pair(id, x));
    list.push_back(x);
    return *x;
}


const Criterion& CriteriaInStorage::operator[](const lem::UCString &name)
{
    const int id = Find(name);
    return operator[](id);
}


void CriteriaInStorage::SaveBin(lem::Stream &bin) const
{}

void CriteriaInStorage::LoadBin(lem::Stream &bin)
{}

CriterionEnumerator* CriteriaInStorage::Enumerate()
{
    return new CriterionEnumerator_SQL(storage->EnumerateCriteria(), this);
}
