#include <lem/macro_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/KnowledgeBase.h>

using namespace Solarix;

KB_Fact::KB_Fact() : id_group(UNKNOWN), bool_return(UNKNOWN), false_score(0), int_return(UNKNOWN)
{
}

KB_Fact::~KB_Fact()
{
    for (auto a : args)
    {
        delete a;
    }

    return;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void KB_Fact::LoadTxt(KnowledgeBase &kb, Solarix::Dictionary &dict, lem::Iridium::Macro_Parser &txtfile)
{
    lem::Iridium::BethToken t_groupname = txtfile.read();
    id_group = kb.FindFacts(t_groupname.string());
    if (id_group == UNKNOWN)
    {
        lem::Iridium::Print_Error(t_groupname, txtfile);
        dict.GetIO().merr().printf("Unknown facts group name %us\n", t_groupname.string().c_str());
        throw lem::E_BaseException();
    }

    const KB_Facts & facts = kb.GetFacts(id_group);

    txtfile.read_it(B_OFIGPAREN);

    txtfile.read_it(B_IF);
    txtfile.read_it(B_CONTEXT);
    txtfile.read_it(B_OFIGPAREN);

    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CFIGPAREN))
            break;

        KB_Argument * point = new KB_Argument();
        point->LoadTxt(facts, dict, txtfile);

        args.push_back(point);
    }

    if (args.size() != facts.CountOfArg())
    {
        lem::Iridium::Print_Error(t_groupname, txtfile);
        dict.GetIO().merr().printf("Incorrect number of arguments: %d extected, %d got\n", facts.CountOfArg(), CastSizeToInt(args.size()));
        throw lem::E_BaseException();
    }

    txtfile.read_it(B_THEN);
    txtfile.read_it(L"return");

    if (facts.DoesReturnBoolean())
    {
        lem::Iridium::BethToken t_ret = txtfile.read();

        if (t_ret.string().eqi(L"true"))
            bool_return = 1;
        else if (t_ret.string().eqi(L"false"))
            bool_return = 0;
        else
        {
            lem::Iridium::Print_Error(t_groupname, txtfile);
            dict.GetIO().merr().printf("Invalid return value %us\n", t_ret.string().c_str());
            throw lem::E_BaseException();
        }

        if (txtfile.probe(B_COMMA))
        {
            // опционально - штраф за false (предполагается, что он всегда отрицательный).
            txtfile.read_it(B_SUB);
            false_score = -txtfile.read_int();
        }
        else
        {
            false_score = facts.violation_score;
        }
    }
    else if (facts.DoesReturnInteger())
    {
        // Допускаем отрицательные значения, поэтому сначала пытаемся прочитать "-"
        if (txtfile.probe(L"-"))
            int_return = -txtfile.read_int();
        else
            int_return = txtfile.read_int();
    }
    else
    {
        LEM_STOPIT;
    }

    txtfile.read_it(B_CFIGPAREN);

    return;
}
#endif


#if defined SOL_CAA
KB_CheckingResult KB_Fact::Match(Solarix::Dictionary *dict, const KB_Facts & facts, const lem::MCollect<const Solarix::Word_Form*> & values) const
{
    LEM_CHECKIT_Z(dict != NULL);
    LEM_CHECKIT_Z(args.size() == values.size());

    bool args_ok = true;
    for (lem::Container::size_type i = 0; i < args.size(); ++i)
    {
        if (!args[i]->Match(dict, *values[i]))
        {
            args_ok = false;
            break;
        }
    }

    if (args_ok)
    {
        if (facts.DoesReturnBoolean())
        {
            return KB_BoolResult(GetBooleanReturn(), GetFalseScore());
        }
        else if (facts.DoesReturnInteger())
        {
            return KB_IntResult(GetIntegerReturn());
        }
        else
        {
            LEM_STOPIT;
            return KB_NotMatchedResult();
        }
    }
    else
    {
        return KB_NotMatchedResult();
    }
}
#endif



bool KB_Fact::IsQueryableByEntries(void) const
{
    for (auto a : args)
    {
        if (!a->IsQueryableByEntry())
        {
            return false;
        }
    }

    return true;
}


bool KB_Fact::IsQueryableByWords(void) const
{
    for (auto a : args)
    {
        if (!a->IsQueryableByWord())
        {
            return false;
        }
    }

    return true;
}


bool KB_Fact::NeedsFeatureCheck() const
{
    for (auto a : args)
    {
        if (a->NeedsFeatureCheck())
        {
            return true;
        }
    }

    return false;
}

bool KB_Fact::IsMultiIndexed() const
{
    for (auto a : args)
    {
        if (a->IsMetaEntry())
        {
            return true;
        }
    }

    return false;
}


