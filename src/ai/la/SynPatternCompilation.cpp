#if defined SOL_LOADTXT && defined SOL_COMPILER

#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/SynPatternCompilation.h>

using namespace lem;
using namespace Solarix;


SynPatternCompilation::SynPatternCompilation(const SynPattern * p)
    : pattern_being_compiled(p), wordentry_set(nullptr), ipoint(0)
{
    static int _seq = 0;

    seq = ++_seq;
    tr_compilation = new TrCompilationContext();
    return;
}


SynPatternCompilation::~SynPatternCompilation()
{
    lem_rub_off(tr_compilation);
    return;
}



void SynPatternCompilation::RegisterRootNode(const lem::UCString & marker_name)
{
    root_node_marker = marker_name;
    return;
}




void SynPatternCompilation::AddExportCoord(int id_coord, bool null_export)
{
    if (export_coords.find(id_coord) != UNKNOWN)
    {
        lem::MemFormatter mem;
        mem.printf("Coordinate id=%d is already declared as exportable", id_coord);
        throw lem::E_BaseException(mem.string());
    }

    export_coords.push_back(id_coord);

    if (null_export)
        null_export_coords.push_back(id_coord);

    return;
}


void SynPatternCompilation::AddExportNode(const lem::UCString &name, bool null_export)
{
    lem::UCString uname(lem::to_upper(name));

    if (export_nodes.find(uname) != UNKNOWN)
    {
        lem::MemFormatter mem;
        mem.printf("Node %us is already declared as exportable", uname.c_str());
        throw lem::E_BaseException(mem.string());
    }

    export_nodes.push_back(uname);

    if (null_export)
        null_export_nodes.push_back(uname);

    return;
}


bool SynPatternCompilation::CoordIsExported(SynGram &sg, int id_coord)
{
    if (actually_exported_coords.find(id_coord) != UNKNOWN)
        return false;

    actually_exported_coords.push_back(id_coord);
    return true;
}


bool SynPatternCompilation::NodeIsExported(const lem::UCString & name)
{
    lem::UCString uname(name);
    uname.to_upper();

    if (actually_exported_nodes.find(uname) != UNKNOWN)
        return false;

    actually_exported_nodes.push_back(uname);
    return true;
}


// Проверяем, что в теле паттерна на самом деле экспортированы все координаты и именованные узлы, которые объявлены
// в секции export. В случае неуспеха проверки возвращается false.
bool SynPatternCompilation::PatternHasBeenCompiled(SynGram &sg) const
{
    bool ok = true;

    for (lem::Container::size_type i = 0; i < export_coords.size(); ++i)
    {
        if (actually_exported_coords.find(export_coords[i]) == UNKNOWN && null_export_coords.find(export_coords[i]) == UNKNOWN)
        {
            sg.GetIO().merr().printf("Coordinate [%us] is declared as exportable but was not actually exported\n"
                , sg.coords()[export_coords[i]].GetName().string().c_str());
            ok = false;
        }
    }

    for (lem::Container::size_type i = 0; i < export_nodes.size(); ++i)
    {
        lem::UCString uname = lem::to_upper(export_nodes[i]);

        if (actually_exported_nodes.find(uname) == UNKNOWN && null_export_nodes.find(uname) == UNKNOWN)
        {
            sg.GetIO().merr().printf("Node [%us] is declared as exportable but was not actually exported\n", export_nodes[i].c_str());
            ok = false;
        }
    }

    return ok;
}



bool SynPatternCompilation::IsExportNode(const lem::UCString & node_name) const
{
    return export_nodes.find(lem::to_upper(node_name)) != UNKNOWN;
}


bool SynPatternCompilation::IsExportCoord(int id_coord) const
{
    return export_coords.find(id_coord) != UNKNOWN;
}


void SynPatternCompilation::Set(WordEntrySet *_sets)
{
    wordentry_set = _sets;
}


void SynPatternCompilation::Add(const lem::UCString &name)
{
    names.push_back(name);
}


int SynPatternCompilation::Find(const lem::UCString &name) const
{
    for (lem::Container::size_type i = 0; i < names.size(); ++i)
    {
        if (names[i].eqi(name))
            return i;
    }

    return UNKNOWN;
}


bool SynPatternCompilation::IsWordEntrySet(const lem::UCString &name)
{
    return wordentry_set->IsWordEntrySetName(name);
}

bool SynPatternCompilation::IsWordformSet(const lem::UCString &name)
{
    return wordentry_set->IsWordformSetName(name);
}

bool SynPatternCompilation::IsWordSet(const lem::UCString &name)
{
    return wordentry_set->IsWordSetName(name);
}

bool SynPatternCompilation::IsCollocationSet(const lem::UCString &name)
{
    return wordentry_set->IsCollocationSetName(name);
}


void SynPatternCompilation::CheckThatVariablesTheSame(const SynPatternCompilation &x) const
{
    for (lem::Container::size_type i = 0; i < tr_compilation->GetVars().size(); ++i)
    {
        if (!x.tr_compilation->IsVariable(tr_compilation->GetVars()[i]))
        {
            lem::MemFormatter mem;
            mem.printf("Mismatching variables set in patterns: variable [%us] is not found", tr_compilation->GetVars()[i].c_str());
            throw lem::E_BaseException(mem.string());
        }
    }

    return;
}

#endif
