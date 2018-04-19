#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PatternLinkEdge.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/TreeScorer.h>

using namespace Solarix;

TreeScorerPredicate::TreeScorerPredicate(const lem::UCString &_func_name, const lem::Collect<TreeScorerPredicateArg> &_args)
    : func_name(_func_name), args(_args)
{
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerPredicate::LoadTxt(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile)
{
    txtfile.read_it(L"@");
    func_name = txtfile.read();

    txtfile.read_it(B_OROUNDPAREN);
    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CROUNDPAREN))
            break;

        if (!args.empty())
            txtfile.read_it(B_COMMA);

        TreeScorerPredicateArg arg;
        arg.LoadTxt(dict, txtfile);
        args.push_back(arg);
    }

    return;
}
#endif


void TreeScorerPredicate::Store(LexiconStorage & storage, int id_host_point)
{
    storage.StoreTreeScorerPredicate(id_host_point, func_name, args);
    return;
}


#if defined SOL_CAA
bool TreeScorerPredicate::DoesMatch(
    SynGram &sg,
    const Word_Form & version,
    const LinkEdgeContainer & edges,
    const TreeScorerApplicationContext & context
) const
{
    if (func_name == "sequence_pos")
    {
        const int id_class = args.front().id_class;

        const int n_edge = edges.size();
        for (int i = 0; i < n_edge; ++i)
        {
            const PatternLinkEdge & e1 = edges[i];

            if (e1.from == &version)
            {
                const int key1 = e1.to->GetEntryKey();
                if (!lem::is_quantor(key1))
                {
                    const SG_Entry & w1 = sg.GetEntry(key1);
                    if (w1.GetClass() == id_class)
                    {
                        for (int j = 0; j < n_edge; ++j)
                        {
                            if (i != j)
                            {
                                const PatternLinkEdge & e2 = edges[j];

                                if (e2.from == &version)
                                {
                                    const int key2 = e2.to->GetEntryKey();
                                    if (!lem::is_quantor(key2))
                                    {
                                        const SG_Entry & w2 = sg.GetEntry(key2);
                                        if (w2.GetClass() == id_class)
                                        {
                                            const int delta = e1.to->GetOriginPos() - e2.to->GetOriginPos();
                                            if (delta == 1 || delta == -1)
                                            {
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}
#endif
