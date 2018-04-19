#include <lem/solarix/PatternLinkEdge.h>
#include <lem/solarix/BackTraceItem.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/PatternLinks.h>

using namespace Solarix;


PatternLink::PatternLink() : link_type(UNKNOWN), optional_to_node(false)
{}


bool PatternLink::operator!=(const PatternLink & x) const
{
    return from_marker != x.from_marker ||
        from_node != x.from_node ||
        to_marker != x.to_marker ||
        to_node != x.to_node ||
        link_type != x.link_type ||
        optional_to_node != x.optional_to_node;
}


void PatternLink::SaveBin(lem::Stream &bin) const
{
    bin.write(&from_marker, sizeof(from_marker));
    bin.write(&from_node, sizeof(from_node));
    bin.write(&to_marker, sizeof(to_marker));
    bin.write(&to_node, sizeof(to_node));
    bin.write(&link_type, sizeof(link_type));
    bin.write_bool(optional_to_node);
    return;
}


void PatternLink::LoadBin(lem::Stream &bin)
{
    bin.read(&from_marker, sizeof(from_marker));
    bin.read(&from_node, sizeof(from_node));
    bin.read(&to_marker, sizeof(to_marker));
    bin.read(&to_node, sizeof(to_node));
    bin.read(&link_type, sizeof(link_type));
    optional_to_node = bin.read_bool();
    return;
}

#if defined SOL_CAA
const Solarix::Word_Form* PatternLink::GetNode(
    const LexicalAutomat & la,
    const lem::MCollect<int> & PatternSequenceNumber,
    SynPatternResult * cur_result,
    const lem::UCString & marker_name,
    const lem::UCString & node_name,
    bool optional
) const
{
    if (optional && !cur_result->trace.Contains(PatternSequenceNumber, marker_name))
        return nullptr;

    const BackTraceItem & mark_data = *cur_result->trace.Get(PatternSequenceNumber, marker_name);

    if (node_name.empty())
    {
        if (mark_data.IsSingleWord())
        {
            const Word_Form * root_node = mark_data.GetSingleRootNode();
            return root_node;
        }
        else
        {
            // сначала пробуем найти токен с пометкой root_node.
            const Word_Form * root_node0 = mark_data.FindNode(*la.GetRootNodeName());
            if (root_node0 != nullptr)
            {
                return root_node0;
            }
            else
            {
                // В качестве центрального берем первый токен.
                const LexerTextPos * token = mark_data.GetBeginToken();
                const Solarix::Word_Form * root_node = token->GetWordform();
                return root_node;
            }
        }
    }
    else
    {
        // Центральный узел указан явно.

        const Word_Form * root_node = mark_data.FindNode(node_name);
        return root_node;
    }
}
#endif


#if defined SOL_CAA
void PatternLink::Generate(const LexicalAutomat & la, const lem::MCollect<int> & PatternSequenceNumber, SynPatternResult * cur_result) const
{
    const Solarix::Word_Form * node0 = GetNode(la, PatternSequenceNumber, cur_result, from_marker, from_node, false);
    if (node0 == nullptr)
    {
        lem::MemFormatter mem;
        mem.printf("Can not find node %us.%us to create link head", from_marker.c_str(), from_node.c_str());
        throw lem::E_BaseException(mem.string());
    }

    const Solarix::Word_Form * node1 = GetNode(la, PatternSequenceNumber, cur_result, to_marker, to_node, optional_to_node);

    if (node1 != nullptr)
    {
        PatternLinkEdge new_edge(node0, link_type, node1);
        cur_result->AddLinkageEdge(new_edge);
        /*
           #if LEM_DEBUGGING==1
           if( node0->GetName()->eqi(L"установить") && node1->GetName()->eqi(L"всегда") )
            {
             lem::mout->printf( "!!! DEBUG !!!\n" );

             lem::Path fname;
             int line=-1, column=-1;
             if( la.GetDict().GetDebugSymbols().GetLocation( 36375, fname, line, column ) )
              {
               lem::mout->printf( "DEBUG: (%vf6%us:%d%vn)\n", fname.GetUnicode().c_str(), line );
              }

             lem::mout->printf( "%vfATRACE%vn:\n" );
             cur_result->trace.Print( *lem::mout, la.GetDict().GetSynGram(), false );
             lem::mout->eol();
            }
           #endif
        */
    }
    else if (!optional_to_node)
    {
        lem::MemFormatter mem;
        mem.printf("Can not find node %us.%us to create link tail", to_marker.c_str(), to_node.c_str());
        throw lem::E_BaseException(mem.string());
    }

    return;
}
#endif



#if defined SOL_CAA
void PatternLink::GenerateConnections(const std::multimap<lem::UCString, const Word_Form*> & points, SynPatternResult * cur_result) const
{
    auto it_from = points.find(from_marker);
    if (it_from == points.end())
    {
        lem::MemFormatter mem;
        mem.printf("Can not find node %us.%us to create link head", from_marker.c_str(), from_node.c_str());
        throw lem::E_BaseException(mem.string());
    }

    const Word_Form * node0 = it_from->second;

    typedef std::multimap<lem::UCString, const Word_Form*>::const_iterator IT;
    std::pair<IT, IT> pit = points.equal_range(to_marker);
    if (pit.first == points.end() && !optional_to_node)
    {
        lem::MemFormatter mem;
        mem.printf("Can not find node %us to create link tail", to_marker.c_str());
        throw lem::E_BaseException(mem.string());
    }

    for (auto it = pit.first; it != pit.second; ++it)
    {
        const Solarix::Word_Form * node1 = it->second;

        PatternLinkEdge new_edge(node0, link_type, node1);

        cur_result->AddLinkageEdge(new_edge);
    }

    return;
}
#endif
