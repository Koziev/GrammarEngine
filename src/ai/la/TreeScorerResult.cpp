#include <lem/macro_parser.h>
#include <lem/string_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/TreeScorerApplicationContext.h>
#include <lem/solarix/TreeScorer.h>

using namespace Solarix;

TreeScorerResult::TreeScorerResult() : type(UNKNOWN), score(0), id_fact(UNKNOWN)
{
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerResult::LoadBoundVars(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, const TreeScorerMarkers & markers)
{
    txtfile.read_it(B_OROUNDPAREN);
    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CROUNDPAREN))
            break;

        if (!args.empty())
            txtfile.read_it(B_COMMA);

        const lem::Iridium::BethToken & var = txtfile.read();
        lem::UCString upper_var = lem::to_upper(var.string());
        if (!markers.IsAlreadyBound(upper_var))
        {
            lem::Iridium::Print_Error(var, txtfile);
            dict.GetIO().merr().printf("Variable %us is not bound\n", var.string().c_str());
            throw lem::E_BaseException();
        }

        args.push_back(upper_var);
    }

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerResult::LoadTxt(
    Dictionary & dict,
    lem::Iridium::Macro_Parser & txtfile,
    const TreeScorerMarkers & markers
)
{
    // ќценка может быть отрицательной.
    if (txtfile.probe(B_SUB))
    {
        type = NumberScoreType;
        score = -txtfile.read_int();
    }
    else
    {
        if (lem::is_int(txtfile.pick().string()))
        {
            type = NumberScoreType;
            score = txtfile.read_int();
        }
        else
        {
            const lem::Iridium::BethToken & t = txtfile.read();
            id_fact = dict.GetLexAuto().GetKnowledgeBase().FindFacts(t.string());
            if (id_fact == UNKNOWN)
            {
                type = FuncScoreType;

                Solarix::TrKnownVars vars;

                Solarix::TrTreeType tree_type;
                for (lem::Container::size_type k = 0; k < markers.CountMarkers(); ++k)
                {
                    vars.RegisterVar(tree_type, markers.GetMarker(k));
                    args.push_back(markers.GetMarker(k));
                }

                txtfile.seekp(t);
                score_fun = dict.GetLexAuto().GetFunctions().Get().CompileCall(dict.GetLexAuto(), txtfile, vars);
            }
            else
            {
                LoadBoundVars(dict, txtfile, markers);
                type = NGramScoreType;
            }
        }
    }

    return;
}
#endif




lem::UFString TreeScorerResult::SerializeExpression() const
{
    lem::MemFormatter mem;

#if defined SOL_SAVEBIN
    if (type == NumberScoreType)
    {
        return UFString(lem::to_ustr(score).c_str());
    }
    else if (type == NGramScoreType)
    {
        mem.printf("%d(", id_fact);

        for (lem::Container::size_type i = 0; i < args.size(); ++i)
        {
            if (i > 0)
                mem.printf(",");

            mem.printf("%us", args[i].c_str());
        }

        mem.printf(")");
    }
    else if (type == FuncScoreType)
    {
        lem::MemStream bin(true);
        args.SaveBin(bin);
        score_fun->SaveBin(bin);
        mem.printf("%s", bin.Hex().c_str());
    }
    else
    {
        LEM_STOPIT;
    }
#endif

    return mem.string();
}



void TreeScorerResult::DeserializeExpression(int expr_type, const lem::UFString & serialized)
{
    type = expr_type;

    if (type == NumberScoreType)
    {
        score = lem::to_int(serialized);
    }
    else if (type == NGramScoreType)
    {
        lem::StrParser<lem::UFString> txt(serialized);

        id_fact = lem::to_int(txt.read());
        txt.read_it(L"(");
        while (!txt.eof())
        {
            if (txt.probe(L")"))
                break;

            if (!args.empty())
                txt.read_it(L",");

            args.push_back(lem::UCString(txt.read().c_str()));
        }
    }
    else if (type == FuncScoreType)
    {
        lem::MemReadHexStream bin2(serialized.c_str());
        args.LoadBin(bin2);
        score_fun = TrFunCall::load_bin(bin2);
    }
    else
    {
        LEM_STOPIT;
    }

    return;
}


void TreeScorerResult::Link(const TrFunctions &funs)
{
    if (score_fun.NotNull())
        score_fun->Link(funs);

    return;
}




#if defined SOL_CAA
int TreeScorerResult::Calculate(
    Dictionary & dict,
    const TreeScorerBoundVariables & bound_variables,
    const ElapsedTimeConstraint & constraints,
    TrTrace *trace_log
) const
{
    if (type == NumberScoreType)
        return score;
    else if (type == NGramScoreType)
    {
        lem::MCollect<const Solarix::Word_Form*> vars;
        for (lem::Container::size_type i = 0; i < args.size(); ++i)
        {
            const Solarix::Word_Form * wf = bound_variables.GetVariable(args[i]);
            if (wf == NULL)
            {
                lem::MemFormatter mem;
                mem.printf("tree_scorer: can not find bound variable %us", args[i].c_str());
                throw lem::E_BaseException(mem.string());
            }

            vars.push_back(wf);
        }

        KB_CheckingResult res = dict.GetLexAuto().GetKnowledgeBase().Prove(id_fact, vars);
        if (res.IsMatched())
            return res.GetInt();
        else
            return 0;
    }
    else if (type == FuncScoreType)
    {
        TrFunContext ctx0((TrFunContext*)NULL);

        TrContextInvokation ctx2(&ctx0);

        for (lem::Container::size_type i = 0; i < args.size(); ++i)
        {
            const Solarix::Word_Form * wf = bound_variables.GetVariable(args[i]);
            if (wf == NULL)
            {
                lem::MemFormatter mem;
                mem.printf("tree_scorer: can not find bound variable %us", args[i].c_str());
                throw lem::E_BaseException(mem.string());
            }

            lem::Ptr<TrValue> this_wordform(new TrValue(new Tree_Node(*wf), true));
            ctx2.AddVar(args[i], this_wordform);
        }

        lem::Ptr<TrValue> fun_res = score_fun->Run(constraints, dict.GetLexAuto(), ctx2, trace_log);

        if (fun_res->GetType().IsInt())
        {
            int res_int = fun_res->GetInt();
            return res_int;
        }
        else
        {
#if LEM_DEBUGGING==1
            if (trace_log != NULL)
                trace_log->PrintStack(*lem::mout);
#endif

            lem::UFString msg(lem::format_str(L"Score function must return int, not %s", fun_res->GetType().GetName().c_str()));
            throw E_BaseException(msg.c_str());
        }
    }
    else
    {
        LEM_STOPIT;
    }

    return 0;
}
#endif

