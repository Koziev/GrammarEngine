// Команды связывания для одного паттерна, то есть для правила с ключевым словом PATTERN

#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/PatternLinks.h>

using namespace Solarix;


PatternLinks::PatternLinks()
{
}


PatternLinks::PatternLinks(const PatternLinks &x)
    : links(x.links), groups(x.groups)
{
}



void PatternLinks::operator=(const PatternLinks &x)
{
    links = x.links;
    groups = x.groups;
    return;
}


bool PatternLinks::operator!=(const PatternLinks &x) const
{
    return links != x.links;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternLinks::LoadNode(
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    SynPatternCompilation & compilation_context,
    lem::UCString & marker_name,
    lem::UCString & node_name,
    std::set<lem::UCString> & linked_markers // для контроля повторного использования маркировки
) const
{
    node_name.clear();

    const bool parentess = txtfile.probe(B_OROUNDPAREN);

    lem::Iridium::BSourceState beg = txtfile.tellp();
    marker_name = txtfile.read();

    if (compilation_context.Find(marker_name) == UNKNOWN)
    {
        dict.GetIO().merr().printf("Marker [%us] is not declared in this pattern", marker_name.c_str());
        lem::Iridium::Print_Error(beg, txtfile);
        throw lem::E_BaseException();
    }

    marker_name.to_upper();

    if (linked_markers.find(marker_name) != linked_markers.end())
    {
        dict.GetIO().merr().printf("Marker [%us] is already linked by another node", marker_name.c_str());
        lem::Iridium::Print_Error(beg, txtfile);
        throw lem::E_BaseException();
    }

    linked_markers.insert(marker_name);

    if (parentess)
    {
        if (txtfile.probe(B_DOT))
        {
            node_name = txtfile.read();
            node_name.to_upper();
        }

        txtfile.read_it(B_CROUNDPAREN);
    }

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternLinks::AddGroup(
    const lem::UCString &marker_name,
    const lem::UCString & node_name,
    bool optional_node
)
{
    LEM_CHECKIT_Z(!marker_name.empty());

    for (lem::Container::size_type i = 0; i < groups.size(); ++i)
        if (groups[i]->GetMarker() == marker_name)
            return;

    PatternDefaultLinkage * new_group = new PatternDefaultLinkage(marker_name, node_name, optional_node);
    groups.push_back(new_group);
    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternLinks::AddLink(
    const lem::UCString & from_marker,
    const lem::UCString & from_node,
    int link_type,
    const lem::UCString & to_marker,
    const lem::UCString & to_node,
    bool optional_to_node
)
{
    PatternLink * new_link = new PatternLink;

    new_link->from_marker = from_marker;
    new_link->from_node = from_node;
    new_link->to_marker = to_marker;
    new_link->to_node = to_node;
    new_link->link_type = link_type;
    new_link->optional_to_node = optional_to_node;

    links.push_back(new_link);
    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternLinks::LoadNodeAndChildren(
    int to_root_link,
    bool optional_node,
    const lem::UCString &root_marker_name,
    const lem::UCString &root_node_name,
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    SynPatternCompilation & compilation_context,
    std::set<lem::UCString> & linked_markers // для контроля повторного использования маркировки
)
{
    UCString from_marker, from_node;
    LoadNode(dict, txtfile, compilation_context, from_marker, from_node, linked_markers);

    if (to_root_link != UNKNOWN)
    {
        LEM_CHECKIT_Z(!root_marker_name.empty());

        AddGroup(root_marker_name, root_node_name, false);
        AddGroup(from_marker, from_node, optional_node);
        AddLink(root_marker_name, root_node_name, to_root_link, from_marker, from_node, optional_node);
    }

    if (txtfile.probe(B_DOT))
    {
        if (txtfile.probe(B_OFIGPAREN))
        {
            while (!txtfile.eof())
            {
                if (txtfile.probe(B_CFIGPAREN))
                    break;

                const bool optional_node = txtfile.probe(B_TILDA);
                Solarix::Tree_Link link(txtfile, dict.GetSynGram());
                LoadNodeAndChildren(link.GetState(), optional_node, from_marker, from_node, dict, txtfile, compilation_context, linked_markers);
            }
        }
        else
        {
            const bool optional_node = txtfile.probe(B_TILDA);
            Solarix::Tree_Link link;
            link.LoadTxt(txtfile, dict.GetSynGram());
            LoadNodeAndChildren(link.GetState(), optional_node, from_marker, from_node, dict, txtfile, compilation_context, linked_markers);
        }
    }

    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternLinks::LoadTxt(
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    SynPatternCompilation & compilation_context
)
{
    txtfile.read_it(B_OFIGPAREN);

    lem::Iridium::BSourceState beg = txtfile.tellp();

    // Чтобы не допустить повторного упоминания одной маркировки в двух узлах, будем собирать этот список.
    // Имена - в верхнем регистре.
    std::set<lem::UCString> linked_markers;

    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CFIGPAREN))
            break;

        lem::UCString empty;
        LoadNodeAndChildren(UNKNOWN, false, empty, empty, dict, txtfile, compilation_context, linked_markers);

        // Проверим, что корень описанного дерева маркирован как ROOT_NODE
        if (!compilation_context.GetRootNodeMarker().empty() && !links.empty())
        {
            if (!links.front()->from_marker.eqi(compilation_context.GetRootNodeMarker()))
            {
                dict.GetIO().merr().printf("Marker [%us] must be declared as ROOT_NODE", links.front()->from_marker.c_str());
                lem::Iridium::Print_Error(beg, txtfile);
                throw lem::E_BaseException();
            }
        }
    }

    return;
}
#endif    


#if defined SOL_CAA
const lem::UCString& PatternLinks::GetRootNodeMarker() const
{
    return links.front()->from_marker;
}
#endif

void PatternLinks::SaveBin(lem::Stream &bin) const
{
    links.SaveBin(bin);
    groups.SaveBin(bin);
    return;
}

void PatternLinks::LoadBin(lem::Stream &bin)
{
    links.LoadBin(bin);
    groups.LoadBin(bin);
    return;
}



#if defined SOL_CAA
void PatternLinks::Generate(const LexicalAutomat & la, const lem::MCollect<int> & PatternSequenceNumber, SynPatternResult * cur_result) const
{
    for (auto group : groups)
    {
        group->Generate(la, PatternSequenceNumber, cur_result);
    }

    for (auto link : links)
    {
        link->Generate(la, PatternSequenceNumber, cur_result);
    }

    return;
}
#endif


#if defined SOL_CAA
void PatternLinks::GenerateConnections(const std::multimap<lem::UCString, const Word_Form*> & points, SynPatternResult * cur_result) const
{
    for (auto link : links)
    {
        link->GenerateConnections(points, cur_result);
    }

    return;
}
#endif
