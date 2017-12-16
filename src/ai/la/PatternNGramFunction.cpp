#include <lem/macro_parser.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/TreeScorerMatcher.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/PatternNGrams.h>

using namespace Solarix;


PatternNGramFunction::PatternNGramFunction()
{
}

PatternNGramFunction::PatternNGramFunction( const PatternNGramFunction & x )
    : function_name( x.function_name ), function_args( x.function_args ), fun( x.fun->clone() )
{
}

void PatternNGramFunction::operator=(const PatternNGramFunction & x)
{
    function_name = x.function_name;
    function_args = x.function_args;
    fun = x.fun->clone();
}

bool PatternNGramFunction::operator!=(const PatternNGramFunction & x) const
{
    return function_name != x.function_name || function_args != x.function_args;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternNGramFunction::LoadTxt(
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    VariableChecker & compilation_context
    )
{
    lem::Iridium::BSourceState beg = txtfile.tellp();

    lem::Iridium::BethToken tfun = txtfile.read();

    function_name = tfun.string();

    TrFunctions & fx = dict.GetLexAuto().GetFunctions().Get();

    const TrFunction * fun_info = fx.Find( function_name );

    // это вызов функции дл¤ проверки дерева, начинающегос¤ с заданного именем маркировки узла
    TrKnownVars known_vars( &fx.global_known_vars );

    txtfile.read_it( B_OROUNDPAREN );

    // ћожет быть перечень нескольких маркировок
    while(true)
    {
        if(txtfile.probe( B_CROUNDPAREN ))
            break;

        if(!function_args.empty())
            txtfile.read_it( B_COMMA );

        lem::UCString arg_name = txtfile.read().string();
        arg_name.to_upper();
        if(compilation_context.Find( arg_name ) == UNKNOWN)
        {
            dict.GetIO().merr().printf( "Variable [%us] is not declared", arg_name.c_str() );
            lem::Iridium::Print_Error( beg, txtfile );
            throw lem::E_BaseException();
        }

        TrType arg_type = fun_info->GetArgType( CastSizeToInt( function_args.size() ) );

        known_vars.RegisterVar( TrTreeType(), arg_name ); // провер¤мый узел и все его дети как дерево
        function_args.push_back( arg_name );
        arg_types.push_back( arg_type );
    }

    txtfile.seekp( tfun );
    fun = dict.GetLexAuto().GetFunctions().Get().CompileCall( dict.GetLexAuto(), txtfile, known_vars );

    return;
}
#endif    

void PatternNGramFunction::SaveBin( lem::Stream &bin ) const
{
    bin.write( &function_name, sizeof( function_name ) );
    function_args.SaveBin( bin );
    arg_types.SaveBin( bin );
    fun->SaveBin( bin );
    return;
}

void PatternNGramFunction::LoadBin( lem::Stream &bin )
{
    bin.read( &function_name, sizeof( function_name ) );
    function_args.LoadBin( bin );
    arg_types.LoadBin( bin );
    fun = TrFunCall::load_bin( bin );

    return;
}


void PatternNGramFunction::Link( const TrFunctions &funs )
{
    fun->Link( funs );
    return;
}


#if defined SOL_CAA
void PatternNGramFunction::AttachEdges(
    const Solarix::Word_Form * root_wf,
    Solarix::Tree_Node * root,
    Dictionary & dict,
    const lem::MCollect<int> & PatternSequenceNumber,
    const SynPatternResult * cur_result
    ) const
{
    for(lem::Container::size_type k = 0; k < cur_result->linkage_edges.size(); ++k)
    {
        const PatternLinkEdge & edge = cur_result->linkage_edges[k];

        if(edge.from == root_wf)
        {
            Solarix::Word_Form * wf_to = GetWordform4Tree( edge.to, dict, cur_result );
            Solarix::Tree_Node * child_node = new Solarix::Tree_Node( wf_to, true );
            child_node->SetLink( Solarix::Tree_Link( edge.link_type ) );
            root->Add( child_node );

            AttachEdges( edge.to, child_node, dict, PatternSequenceNumber, cur_result );
        }
    }

    return;
}
#endif


#if defined SOL_CAA
Solarix::Word_Form* PatternNGramFunction::GetWordform4Tree( const Solarix::Word_Form * src_wf, Dictionary & dict, const SynPatternResult * cur_result ) const
{
    // ќставим только подтвержденные версии словоформ
    Solarix::Word_Form * wf = NULL;
    std::pair<MATCHING_ALTS::const_iterator, MATCHING_ALTS::const_iterator> p = cur_result->matched_alts.equal_range( src_wf );
    for(MATCHING_ALTS::const_iterator it = p.first; it != p.second; ++it)
    {
        int iversion = it->second;
        if(wf == NULL)
        {
            wf = new Solarix::Word_Form( *src_wf->GetVersion( iversion ), false );
        }
        else
        {
            wf->AddAlt( new Solarix::Word_Form( *src_wf->GetVersion( iversion ), false ) );
        }
    }

    if(wf == NULL)
        wf = new Solarix::Word_Form( *src_wf );

    return wf;
}
#endif


#if defined SOL_CAA
Solarix::Tree_Node* PatternNGramFunction::GetTreeByRootName(
    const lem::UCString & root_name,
    Dictionary & dict,
    const lem::MCollect<int> & PatternSequenceNumber,
    const SynPatternResult * cur_result,
    bool attach_children
    ) const
{
    const Solarix::Word_Form * root_wf = NULL;

    if(!cur_result->trace.Contains( PatternSequenceNumber, root_name ))
    {
        lem::MemFormatter mem;
        mem.printf( "Can not find root node marker [%us]", root_name.c_str() );
        throw lem::E_BaseException( mem.string() );
        return NULL;
    }

    const BackTraceItem & mark_data = *cur_result->trace.Get( PatternSequenceNumber, root_name );

    if(mark_data.IsSingleWord())
    {
        root_wf = mark_data.GetSingleRootNode();
    }
    else
    {
        // сначала пробуем найти токен с пометкой root_node.
        const Word_Form * root_node0 = mark_data.FindNode( *dict.GetLexAuto().GetRootNodeName() );
        if(root_node0 != NULL)
        {
            root_wf = root_node0;
        }
        else
        {
            // ¬ качестве центрального берем первый токен.
            const LexerTextPos * token = mark_data.GetBeginToken();
            root_wf = token->GetWordform();
        }
    }


    Solarix::Word_Form * wf = GetWordform4Tree( root_wf, dict, cur_result );
    Solarix::Tree_Node * node = new Solarix::Tree_Node( wf, true );

    if(attach_children)
    {
        // “еперь найдем ребра и присоединим из к корню, а затем продолжим процесс вниз рекурсивно
        AttachEdges( root_wf, node, dict, PatternSequenceNumber, cur_result );
    }

    return node;
}
#endif

#if defined SOL_CAA
int PatternNGramFunction::Match(
    Dictionary & dict,
    const lem::MCollect<int> & PatternSequenceNumber,
    const SynPatternResultBackTrace * x_result,
    SynPatternResult * cur_result,
    KnowledgeBase & kbase,
    TreeMatchingExperience &experience,
    const ElapsedTimeConstraint & constraints,
    TrTrace *trace_log
    ) const
{
    /*
     #if LEM_DEBUGGING==1
     lem::mout->eol();
     cur_result->PrintLinks( *lem::mout, dict.GetSynGram() );
     lem::mout->eol();

     const SynPatternResultBackTrace * p = x_result;
     while( p!=NULL )
     {
     if( p->result!=NULL )
     {
     if( !p->result->linkage_edges.empty() )
     {
     lem::mout->eol();
     p->result->PrintLinks( *lem::mout, dict.GetSynGram() );
     lem::mout->eol();
     }
     }

     p = p->parent;
     }
     #endif
     */

    int scoring = 0;

    TrFunContext ctx0( (TrFunContext*)NULL );
    TrContextInvokation ctx2( &ctx0 );

    for(int iarg = 0; iarg < function_args.size(); ++iarg)
    {
        Tree_Node * var_root = GetTreeByRootName( function_args[iarg], dict, PatternSequenceNumber, cur_result, true );
        lem::Ptr<TrValue> arg( new TrValue( var_root, true ) );
        ctx2.AddVar( function_args[iarg], arg );
    }

    lem::Ptr<TrValue> fun_res = fun->Run( constraints, dict.GetLexAuto(), ctx2, trace_log );

    if(fun_res->GetType().IsInt())
    {
        scoring = fun_res->GetInt();

#if defined SOL_DEBUGGING
        /*
             if( trace_log!=NULL )
             {
             trace_log->Leave( new SynPatternPointCall( dbg_mark, id_src, this, current_token, parent_trace ) );
             }*/
#endif
    }
    else
    {
#if LEM_DEBUGGING==1
        if(trace_log != NULL)
            trace_log->PrintStack( *lem::mout );
#endif

        lem::UFString msg( lem::format_str( L"Pattern ngram function must return int, not %s", fun_res->GetType().GetName().c_str() ) );
        throw E_BaseException( msg.c_str() );
    }


    return scoring;
}
#endif
