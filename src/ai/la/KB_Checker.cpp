#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/SynPattern.h>


using namespace Solarix;

KB_Checker::KB_Checker( const KB_Checker & x )
    : id_facts( x.id_facts ), backref_name( x.backref_name ), node_name( x.node_name )
{
}


void KB_Checker::operator=(const KB_Checker & x)
{
    id_facts = x.id_facts;
    backref_name = x.backref_name;
    node_name = x.node_name;
    return;
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void KB_Checker::LoadTxt( 
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    SynPatternCompilation & compilation_context
    )
{
    lem::Iridium::BethToken t_fact = txtfile.read();
    id_facts = dict.GetLexAuto().GetKnowledgeBase().FindFacts( t_fact.string() );

    if( id_facts==UNKNOWN )
    {
        dict.GetIO().merr().printf( "Unknown fact name [%us]\n", t_fact.string().c_str() );
        lem::Iridium::Print_Error(t_fact,txtfile);
        throw lem::E_BaseException();
    }

    const KB_Facts & facts = dict.GetLexAuto().GetKnowledgeBase().GetFacts( id_facts );

    // —читываем фактические аргументы вызова
    txtfile.read_it( B_OROUNDPAREN );
    while(!txtfile.eof())
    {
        if( txtfile.probe(B_CROUNDPAREN) )
            break;

        if( !backref_name.empty() )
            txtfile.read_it( B_COMMA );

        lem::Iridium::BethToken t_backref = txtfile.read();
        lem::UCString backref = t_backref.string();
        backref.to_upper();
        if( backref!=L'_' )
        {
            if( compilation_context.Find(backref)==UNKNOWN )
            {
                dict.GetIO().merr().printf( "Unknown variable name [%us]\n", t_backref.string().c_str() );
                lem::Iridium::Print_Error(t_backref,txtfile);
                throw lem::E_BaseException();
            }
        }

        lem::UCString node;
        if( txtfile.probe(B_DOT) )
        {
            node = txtfile.read().string();
            node.to_upper();
        }

        backref_name.push_back( backref );
        node_name.push_back( node );
    }

    if( backref_name.size() != facts.CountOfArg() )
    {
        dict.GetIO().merr().printf( "Mismatching number of arguments for fact [%us]: %d required, %d defined\n", t_fact.string().c_str(), facts.CountOfArg(), CastSizeToInt(backref_name.size()) );
        lem::Iridium::Print_Error(t_fact,txtfile);
        throw lem::E_BaseException();
    }

    return;
}
#endif

bool KB_Checker::operator==(const KB_Checker & x) const
{
    if(id_facts != x.id_facts)
        return false;

    if(backref_name.size() != x.backref_name.size())
        return false;

    for(lem::Container::size_type i = 0; i < backref_name.size(); ++i)
        if(backref_name[i] != x.backref_name[i] ||
            node_name[i] != x.node_name[i])
            return false;

    return true;
}


bool KB_Checker::operator!=(const KB_Checker & x) const
{
    return !operator==(x);
}

#if defined SOL_SAVEBIN
void KB_Checker::SaveBin( lem::Stream& bin ) const
{
    bin.write_int( id_facts );
    backref_name.SaveBin( bin );
    node_name.SaveBin( bin );
    return;
}
#endif

#if defined SOL_LOADBIN 
void KB_Checker::LoadBin( lem::Stream& bin )
{
    id_facts = bin.read_int();
    backref_name.LoadBin( bin );
    node_name.LoadBin( bin );
    return;
}
#endif


#if defined SOL_CAA
KB_CheckerReturn KB_Checker::Check(
    const lem::MCollect<int> & PatternSequenceNumber,
    const BackTrace * parent_trace,
    const SynPatternResult * cur_result,
    const Solarix::Word_Form * this_wordform,
    KnowledgeBase & kbase,
    TreeMatchingExperience &experience
    ) const
{
    KB_CheckerReturn ret;

    // —оберем фактические значени€ дл€ формальных аргументов вызова предиката в базе знаний
    lem::MCollect< const Solarix::Word_Form * > arg_values;
    for(lem::Container::size_type i = 0; i < backref_name.size(); ++i)
    {
        const lem::UCString & mark = backref_name[i];
        const lem::UCString & var = node_name[i];
        if(mark == L'_')
        {
            const Word_Form * this_node = this_wordform == NULL ? cur_result->FindExportNode( var ) : this_wordform;

            if(this_node == NULL)
            {
                this_node = cur_result->FindExportNode( L"ROOT_NODE" );

                if(this_node == NULL)
                {
                    lem::MemFormatter mem;
                    mem.printf( "Can not find exported node %us.%us", mark.c_str(), var.c_str() );
                    throw lem::E_BaseException( mem.string() );
                }
            }

            if(this_node == NULL)
            {
                ret.success = true;
                return ret;
            }

            arg_values.push_back( this_node );
        }
        else
        {
            const BackTraceItem & mark_data = *parent_trace->Get( PatternSequenceNumber, mark );

            if(var.empty())
            {
                const Word_Form * mark_node = mark_data.GetWordform();

                if(mark_node == NULL)
                {
                    mark_node = mark_data.FindNode( L"ROOT_NODE" );
                    if(mark_node == NULL)
                    {
                        lem::MemFormatter mem;
                        mem.printf( "Can not find exported node %us", mark.c_str() );
                        throw lem::E_BaseException( mem.string() );
                    }
                }

                arg_values.push_back( mark_node );
            }
            else
            {
                const Word_Form * mark_node = mark_data.FindNode( var );
                if(mark_node == NULL)
                {
                    lem::MemFormatter mem;
                    mem.printf( "Can not find exported node %us.%us", mark.c_str(), var.c_str() );
                    throw lem::E_BaseException( mem.string() );
                }

                arg_values.push_back( mark_node );
            }
        }
    }

    LEM_CHECKIT_Z( arg_values.size() > 0 );

    KB_CheckingResult res;

    if(!experience.FindKBCheckerMatching( id_facts, arg_values, &res ))
    {
        res = kbase.Prove( id_facts, arg_values );
        experience.AddKBCheckerMatching( id_facts, arg_values, res );
    }

    if(res.IsMatched())
    {
        if(res.GetBool() == 0)
        {
            if(res.GetFalseScore() != 0)
            {
                // м€гкое нарушение - считаем успехом со штрафом
                ret.success = true;
                ret.false_score = res.GetFalseScore();
            }
            else
            {
                return ret; // false
            }
        }
        else
        {
            ret.success = res.GetBool() == 1;
            return ret;
        }
    }

    ret.success = true;
    return ret;
}
#endif
