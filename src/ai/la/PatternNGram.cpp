#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/PatternNGrams.h>

using namespace Solarix;


PatternNGram::PatternNGram() : id_facts(UNKNOWN)
{
}

PatternNGram::PatternNGram(const PatternNGram & x)
    : id_facts(x.id_facts), backref_name(x.backref_name), node_name(x.node_name)
{
}

void PatternNGram::operator=(const PatternNGram & x)
{
    id_facts = x.id_facts;
    backref_name = x.backref_name;
    node_name = x.node_name;
}

bool PatternNGram::operator!=(const PatternNGram & x) const
{
    if (id_facts != x.id_facts)
        return true;

    if (backref_name != x.backref_name)
        return true;

    if (node_name != x.node_name)
        return true;

    return false;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternNGram::LoadTxt(
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    VariableChecker & compilation_context
)
{
    lem::Iridium::BethToken t_fact = txtfile.read();
    id_facts = dict.GetLexAuto().GetKnowledgeBase().FindFacts(t_fact.string());

    lem::Iridium::BSourceState beg = txtfile.tellp();

    if (id_facts == UNKNOWN)
    {
        dict.GetIO().merr().printf("Unknown fact name [%us]\n", t_fact.string().c_str());
        lem::Iridium::Print_Error(beg, txtfile);
        throw lem::E_BaseException();
    }

    const KB_Facts & facts = dict.GetLexAuto().GetKnowledgeBase().GetFacts(id_facts);

    // Возвращаемое значение должно быть INTEGER.
    if (!facts.DoesReturnInteger())
    {
        dict.GetIO().merr().printf("Fact [%us] must return an integer\n", t_fact.string().c_str());
        lem::Iridium::Print_Error(beg, txtfile);
        throw lem::E_BaseException();
    }

    // Считываем фактические аргументы вызова
    txtfile.read_it(B_OROUNDPAREN);
    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CROUNDPAREN))
            break;

        if (!backref_name.empty())
            txtfile.read_it(B_COMMA);

        lem::Iridium::BethToken t_backref = txtfile.read();
        lem::UCString backref = t_backref.string();
        backref.to_upper();
        if (backref != L'_')
        {
            if (compilation_context.Find(backref) == UNKNOWN)
            {
                dict.GetIO().merr().printf("Unknown variable name [%us]\n", t_backref.string().c_str());
                lem::Iridium::Print_Error(t_backref, txtfile);
                throw lem::E_BaseException();
            }
        }

        lem::UCString node;
        if (txtfile.probe(B_DOT))
        {
            node = txtfile.read().string();
            node.to_upper();
        }

        backref_name.push_back(backref);
        node_name.push_back(node);
    }

    if (backref_name.size() != facts.CountOfArg())
    {
        dict.GetIO().merr().printf("Mismatching number of arguments for fact [%us]: %d required, %d defined\n", t_fact.string().c_str(), facts.CountOfArg(), CastSizeToInt(backref_name.size()));
        lem::Iridium::Print_Error(t_fact, txtfile);
        throw lem::E_BaseException();
    }

    return;
}
#endif    

void PatternNGram::SaveBin(lem::Stream &bin) const
{
    bin.write_int(id_facts);
    backref_name.SaveBin(bin);
    node_name.SaveBin(bin);

    return;
}

void PatternNGram::LoadBin(lem::Stream &bin)
{
    id_facts = bin.read_int();
    backref_name.LoadBin(bin);
    node_name.LoadBin(bin);
    return;
}


#if defined SOL_CAA
int PatternNGram::Match(
    Dictionary & dict,
    const lem::MCollect<int> & PatternSequenceNumber,
    const SynPatternResult * cur_result,
    KnowledgeBase & kbase,
    TreeMatchingExperience &experience
) const
{
    // Соберем фактические значения для формальных аргументов вызова предиката в базе знаний
    bool all_found = true;
    lem::MCollect< const Solarix::Word_Form * > arg_values;
    for (lem::Container::size_type i = 0; i < backref_name.size(); ++i)
    {
        const lem::UCString & mark = backref_name[i];
        const lem::UCString & var = node_name[i];
        const BackTraceItem * mark_data = cur_result->trace.Get(PatternSequenceNumber, mark, false);
        if (mark_data == nullptr)
        {
            // Это бывает, если аргумент ссылается на @optional маркировку.
            all_found = false;
            break;
        }

        if (var.empty())
        {
            const Word_Form * mark_node = mark_data->GetWordform();
            if (mark_node == nullptr)
            {
                // попробуем дефолтную переменную ROOT_NODE
                mark_node = mark_data->FindNode(*dict.GetLexAuto().GetRootNodeName());
            }

            LEM_CHECKIT_Z(mark_node != nullptr);
            arg_values.push_back(mark_node);
        }
        else
        {
            const Word_Form * mark_node = mark_data->FindNode(var);
            if (mark_node == nullptr)
                return 0;

            arg_values.push_back(mark_node);
        }
    }

    if (!all_found)
        return 0;

    LEM_CHECKIT_Z(arg_values.size() > 0);

    KB_CheckingResult res;

    if (!experience.FindKBCheckerMatching(id_facts, arg_values, &res))
    {
        res = kbase.Prove(id_facts, arg_values);
        experience.AddKBCheckerMatching(id_facts, arg_values, res);
    }

    /*
     #if LEM_DEBUGGING==1
     lem::mout->printf( "NGRAM: (" );
     for( int i=0; i<arg_values.size(); ++i )
      lem::mout->printf( " %vfE%us%vn", arg_values[i]->GetName()->c_str() );
     lem::mout->printf( " ) = %vfA%d%vn\n\n", res.IsMatched() ? res.GetInt() : 0 );
     #endif
    */


    return res.IsMatched() ? res.GetInt() : 0;
}
#endif
