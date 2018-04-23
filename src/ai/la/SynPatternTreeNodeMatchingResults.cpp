#if defined SOL_CAA && !defined SOL_NO_AA

#include <lem/math/integer_math.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/GrafBuilder.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/TreeScorer.h>
#include <lem/solarix/WordAssociation.h>
#include <lem/solarix/TreeScorerApplicationContext.h>
#include <lem/solarix/TreeScorerMatcher.h>
#include <lem/solarix/TreeScorerGroupParams.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/SynPatternTreeNodeMatchingResults.h>

using namespace Solarix;


SynPatternTreeNodeMatchingResults::SynPatternTreeNodeMatchingResults()
    : null_trace(nullptr), merge_results(true)
{
}


SynPatternTreeNodeMatchingResults::~SynPatternTreeNodeMatchingResults()
{
    Clear();
    return;
}


void SynPatternTreeNodeMatchingResults::Clear()
{
    for (lem::Container::size_type i = 0; i < results.size(); ++i)
        delete results[i];

    results.clear();

    for (lem::Container::size_type i = 0; i < tokens_garbage_collector.size(); ++i)
        delete tokens_garbage_collector[i];

    return;
}



void SynPatternTreeNodeMatchingResults::SetResults(const lem::MCollect<SynPatternResult*> & new_results)
{
    for (lem::Container::size_type i = 0; i < results.size(); ++i)
        delete results[i];

    results = new_results;
    return;
}



// Добавим к результатирующим баллам также баллы у затронутых токенов.
void SynPatternTreeNodeMatchingResults::ApplyTokenScores()
{
    for (lem::Container::size_type k = 0; k < results.size(); ++k)
    {
        SynPatternResult * result_k = results[k];

        const int len = result_k->res.Length();

        //   NGramScore & freq = result_k->res.GetNGramFreq();

           // Учтем баллы у затронутых токенов.
        const LexerTextPos * cur_token = result_k->res.GetFinalToken();
        int token_scores = 0;
        while (cur_token != nullptr)
        {
            token_scores += cur_token->GetScore();

            cur_token = cur_token->GetPrev();
            if (cur_token == nullptr)
                break;
        }

        result_k->res.AddNGramFreq(NGramScore(token_scores));
    }

    return;
}



Res_Pack * SynPatternTreeNodeMatchingResults::BuildGrafs(
    Dictionary &dict,
    BasicLexer & lexer,
    bool DoLinkNodes,
    bool CompleteAnalysisOnly,
    const ElapsedTimeConstraint & constraints,
    TrTrace *trace_log
)
{
    if (results.empty())
    {
        // Анализ не выполнен, поэтому просто генерируем варианты из всех путей от начального токена до листьев.
        return GenerateAllPaths(dict, lexer, trace_log);
    }
    else
    {
        return GenerateFilteredPaths(dict, lexer, DoLinkNodes, CompleteAnalysisOnly, constraints, trace_log);
    }
}


// Генерация набора вариантов без связывания, только по результатам токенизации.
Res_Pack * SynPatternTreeNodeMatchingResults::GenerateAllPaths(Dictionary & dict, BasicLexer & lexer, TrTrace *trace_log)
{
    Res_Pack * pack = new Res_Pack();

    const LexerTextPos * begin = lexer.GetBeginToken();

    // находим все листья

    lem::MCollect<const LexerTextPos*> leafs;
    lexer.FetchEnds(begin, leafs, lexer.GetParams().GetMaxRightLeaves());

    lem::MCollect<Tree_Node*> tree_nodes;
    lem::MCollect<const LexerTextPos*> nodes;

    for (lem::Container::size_type i = 0; i < leafs.size(); ++i)
    {
        const LexerTextPos * leaf = leafs[i];
        nodes.clear();
        leaf->Collect_Right2Left(begin, nodes); // собираем все словоформы на этом пути

        tree_nodes.clear();

        int n_versions = 0;

        // словоформы собраны в обратном порядке, развернем его.
        for (int j = CastSizeToInt(nodes.size()) - 1; j >= 0; --j)
        {
            Tree_Node * tn = new Tree_Node(*nodes[j]->GetWordform());
            tree_nodes.push_back(tn);

            n_versions += nodes[j]->GetWordform()->VersionCount();
        }

        Variator * new_var = new Variator(tree_nodes);
        pack->Add(new_var);
    }

    return pack;
}




namespace {
    static void Append(
        std::multimap< const Word_Form*, int /*iversion*/ > &dst,
        const std::multimap< const Word_Form*, int /*iversion*/ > &src
    )
    {
        for (std::multimap< const Word_Form*, int >::const_iterator it = src.begin(); it != src.end(); ++it)
            dst.insert(*it);

        return;
    }


    static int SumDistOnEdges(const SynPatternResult * result)
    {
        int d = 0;

        for (lem::Container::size_type i = 0; i < result->linkage_edges.size(); ++i)
        {
            const PatternLinkEdge & edge = result->linkage_edges[i];
            const int dd = lem::Math::iabs(edge.from->GetOriginPos() - edge.to->GetOriginPos());
            d += dd;
        }

        return d;
    }
}


Res_Pack * SynPatternTreeNodeMatchingResults::GenerateFilteredPaths(
    Dictionary &dict,
    BasicLexer & lexer,
    bool DoLinkNodes,
    bool CompleteAnalysisOnly,
    const ElapsedTimeConstraint & constraints,
    TrTrace *trace_log
)
{
    LEM_CHECKIT_Z(!results.empty());

    Res_Pack * pack = new Res_Pack();

    const LexerTextPos * begin = lexer.GetBeginToken();

    lem::MCollect<const LexerTextPos *> right_ends;
    lem::MCollect<Tree_Node*> tree_nodes;
    lem::MCollect<const LexerTextPos*> nodes;
    std::map<const LexerTextPos*, int> token2index;
    std::map< const Word_Form *, int > version2index;

    typedef std::multimap< const Word_Form*, int > MATCHED_ALTS;
    MATCHED_ALTS matched_alts;

    // Если есть несколько альтернативных результатов, то попробуем использовать tree scorers
    // для выбора лучших.

    WordEntrySet & wordsets = dict.GetLexAuto().GetWordEntrySet();

    if (results.size() > 1)
    {
        for (lem::Container::size_type k = 0; k < results.size(); ++k)
        {
            // не будем проверять неполные варианты, если они запрещены.
            if (CompleteAnalysisOnly && !results[k]->res.GetFinalToken()->IsEnd())
                continue;

            ApplyTreeScorers(dict.GetSynGram(), wordsets, *results[k], constraints, trace_log);
        }

        ApplyWordAssociations(dict);
    }

#if defined SOL_DEBUGGING
    if (trace_log != nullptr)
    {
        trace_log->BreakOnRightBoundary(results);
    }
#endif

    // Определим параметры самого лучшего результата.
    // Выберем результаты с максимальной частотностью и с минимальной длиной, то есть предпочинаем мультилексемы.
    NGramScore best_ngram(lem::int_min); // среди результатов могут быть все со штрафами, поэтому инициализируемся макс. минусом.
    int best_len = lem::int_max;
    bool best_found = false;
    bool select_with_edges = false;

    /*
     #if LEM_DEBUGGING==1
     for( lem::Container::size_type k=0; k<results.size(); ++k )
      {
       const SynPatternResult * result_k = results[k];
       const LexerTextPos * final_token = result_k->res.GetFinalToken();
       lem::mout->printf( "RESULT #%d len=%d final_token=%us ngrams=(%vfA%d%vn,%vfC%d%vn)\n", CastSizeToInt(k),  result_k->res.Length(), final_token->GetWordform()->GetName()->c_str(), result_k->res.GetNGramFreq().positive, result_k->res.GetNGramFreq().negative );
       result_k->Print( *lem::mout, dict.GetSynGram() );
       result_k->PrintLinks( *lem::mout, dict.GetSynGram() );
       lem::mout->printf( "%40h-\n" );
      }
     #endif
    */

    for (int pass = 0; pass < 2 && !best_found; ++pass)
    {
        for (lem::Container::size_type k = 0; k < results.size(); ++k)
        {
            const SynPatternResult * result_k = results[k];

            if ((!result_k->linkage_edges.empty() || result_k->res.Length() == 3) || pass == 1)
            {
                if (result_k->res.GetFinalToken()->IsEnd())
                {
                    const int len = result_k->res.Length();

                    const NGramScore & freq = result_k->res.GetNGramFreq();

                    if (freq.Greater(best_ngram) || (freq.Equal(best_ngram) && len < best_len))
                    {
                        best_len = len;
                        best_ngram = freq;
                        best_found = true;
                        select_with_edges = pass == 0;
                    }
                }
            }
        }
    }


    // Если найти лучший результат не получилось, то значит ни один из results не заканчивается на END.
    // TODO: сделать тут второй проход выбора, уже просто на максимально длинный результат...

    int min_sumdist = lem::int_max;
    std::map<const SynPatternResult*, int> result2dist;

    if (best_found)
    {
        // Если есть несколько одинаково хороших результатов, то попробуем выбрать среди них тот, у которого сумма расстояний между
        // узлами в ребрах графа - минимальное.
        int nbest = 0;
        for (lem::Container::size_type k = 0; k < results.size(); ++k)
        {
            const SynPatternResult * result_k = results[k];

            if (!result_k->linkage_edges.empty() || (result_k->res.Length() == 3 && result_k->res.GetFinalToken()->IsEnd()))
            {
                const int len = result_k->res.Length();

                const NGramScore & freq = result_k->res.GetNGramFreq();

                if ((freq.Equal(best_ngram) || freq.Greater(best_ngram)) && len == best_len)
                {
                    nbest++;
                }
            }
        }

        if (nbest > 1)
        {
            // Еще один проход - для каждого результата получаем суммарное расстояние между узлами на ребрах графа.

            for (lem::Container::size_type k = 0; k < results.size(); ++k)
            {
                const SynPatternResult * result_k = results[k];

                if (!result_k->linkage_edges.empty() || (result_k->res.Length() == 3 && result_k->res.GetFinalToken()->IsEnd()))
                {
                    const int len = result_k->res.Length();

                    const NGramScore & freq = result_k->res.GetNGramFreq();

                    if ((freq.Equal(best_ngram) || freq.Greater(best_ngram)) && len == best_len)
                    {
                        const int sumdist = SumDistOnEdges(result_k);

                        result2dist.insert(std::make_pair(result_k, sumdist));

                        if (sumdist < min_sumdist)
                            min_sumdist = sumdist;
                    }
                }
            }
        }
    }


    // Один путь в графе токенизации может дать несколько вариантов решения паттернами.
    // Поэтому мы должны сгруппировать элементы results по адресу финального токена, так как он
    // для каждого пути будет свой.
    typedef std::pair<const LexerTextPos *, int> TOKEN_KEY;
    std::set< TOKEN_KEY > final_tokens;
    typedef std::multimap< TOKEN_KEY, const SynPatternResult * > FINAL2RESULT;
    FINAL2RESULT final2result;
    for (lem::Container::size_type i = 0; i < results.size(); ++i)
    {
        const LexerTextPos * final_token = results[i]->res.GetFinalToken();
        TOKEN_KEY token_key = std::make_pair(final_token, merge_results ? UNKNOWN : CastSizeToInt(i));

        final_tokens.insert(token_key);
        final2result.insert(std::make_pair(token_key, results[i]));
    }

    for (std::set<TOKEN_KEY>::const_iterator it = final_tokens.begin(); it != final_tokens.end(); ++it)
    {
        const LexerTextPos * final_token = it->first;

        // Получим результаты, связанные с этим путем токенизации.
        std::pair<FINAL2RESULT::const_iterator, FINAL2RESULT::const_iterator> p_resx = final2result.equal_range(*it);

        // Пройдем по всем этим результатам, отбирая самые частотные и короткие, и добавим сопоставленные в них версии в этот контейнер.
        matched_alts.clear();
        const SynPatternResult * selected_result = nullptr;

        // Для каждого набора результатов строим своё связывание и свой вариатор.
        for (FINAL2RESULT::const_iterator it = p_resx.first; it != p_resx.second; ++it)
        {
            const SynPatternResult * result_q = it->second;

#if defined SOL_DEBUGGING
            //lem::mout->printf( "\nResult ngrams=(%vfA%d%vn,%vfC%d%vn):\n", result_q->res.GetNGramFreq().positive, result_q->res.GetNGramFreq().negative );
            //result_q->PrintLinks( *lem::mout, dict.GetSynGram() );
#endif

            const bool has_edges = !result_q->linkage_edges.empty() || (result_q->res.Length() == 3 && result_q->res.GetFinalToken()->IsEnd());

            if (select_with_edges && !has_edges)
                continue;

            const int len = result_q->res.Length();

            const NGramScore& freq = result_q->res.GetNGramFreq();

            if (freq.Equal(best_ngram) && len == best_len)
            {
                bool mindist_matched = true;
                if (min_sumdist != lem::int_max)
                {
                    mindist_matched = false;

                    std::map<const SynPatternResult*, int>::const_iterator it = result2dist.find(result_q);
                    if (it != result2dist.end())
                    {
                        int d = it->second;
                        mindist_matched = d == min_sumdist;
                    }
                }

                if (mindist_matched)
                {
                    if (selected_result == nullptr)
                        selected_result = result_q;

                    Append(matched_alts, result_q->matched_alts);
                }
            }
        }

        if (selected_result != nullptr)
        {
            // Теперь начинаем генерацию вариатора.
            // Нам надо сделать 2 вещи.
            // 1. Создать набор узлов синтаксического дерева, причем словоформы в них нужно отфильтровать по списку matched_alts.
            // 2. Выполнить связывание этих узлов согласно информации о ребрах в selected_result.

            // В нашем случае этот токен - обязательно правая граница. Для неполного анализа это может быть и какой-то токен внутри пути.
            const LexerTextPos * final_token = selected_result->res.GetFinalToken();

            // Список словоформ в этом пути.
            nodes.clear();
            final_token->Collect_Right2Left(begin, nodes); // собираем все словоформы на этом пути

       /*
            #if defined LEM_DEBUGGING==1
            lem::mout->eol();
            int nt = nodes.size();
            for( int itok=nt-1; itok>=0; --itok )
             {
              lem::mout->printf( "%us[%d] --> ", nodes[itok]->GetWordform()->GetName()->c_str(), nodes[itok]->GetWordform()->VersionCount() );

              for( int i=0; i<nodes[itok]->GetWordform()->VersionCount(); ++i )
               {
                const Word_Form * alt = nodes[itok]->GetWordform()->GetVersion(i);
                lem::mout->printf( " %p", alt );
               }

              lem::mout->eol();
             }
            lem::mout->eol();
            #endif
       */


            token2index.clear();
            version2index.clear();
            tree_nodes.clear();

            int n_versions = 0;

            // словоформы собраны в обратном порядке, развернем его.
            for (int j = CastSizeToInt(nodes.size()) - 1; j >= 0; --j)
            {
                const LexerTextPos * token = nodes[j];
                const Word_Form * src_wf = token->GetWordform();

                // Вставляемый в список корней элемент будет иметь такой порядковый индекс.
                const int node_index = CastSizeToInt(tree_nodes.size());

                // переход от токена к индексу корня в tree_nodes, созданного на его основе.
                token2index.insert(std::make_pair(token, node_index));

                // также сделаем таблицу перехода от версии словофоры к индексу корня в tree_nodes, в котором содержится КОПИЯ этой версии.
                const int n_version = src_wf->VersionCount();
                for (int iver = 0; iver < n_version; ++iver)
                    version2index.insert(std::make_pair(src_wf->GetVersion(iver), node_index));

                Word_Form * new_wf = nullptr;

                if (src_wf->VersionCount() > 1)
                {
                    // Для этой словоформы есть фильтрация версий?
                    std::pair<MATCHED_ALTS::const_iterator, MATCHED_ALTS::const_iterator> p_alts = matched_alts.equal_range(src_wf);
                    if (p_alts.first != p_alts.second)
                    {
                        // да, соберем копию с фильтрацией версий.
                        std::set<int> ialt;

                        for (MATCHED_ALTS::const_iterator it2 = p_alts.first; it2 != p_alts.second; ++it2)
                            ialt.insert(it2->second);

                        new_wf = src_wf->CreateNewVersioned(ialt);
                    }
                }

                if (new_wf == nullptr)
                {
                    // нет, просто собираем копию.
                    new_wf = new Word_Form(*src_wf, true);
                }

                Tree_Node * tn = new Tree_Node(new_wf, true);
                tree_nodes.push_back(tn);

                n_versions += new_wf->VersionCount();
            }

            if (DoLinkNodes)
            {
                // Для синтаксического анализа нужно генерировать синтаксическое дерево на основе списке ребер в selected_result.
                GrafBuilder builder;
                builder.BuildGraf(
                    selected_result->linkage_groups,
                    selected_result->linkage_edges,
                    token2index,
                    version2index,
                    tree_nodes,
                    selected_result->has_prelinked_nodes,
                    lexer.GetParams().ReorderTree
                );

                Variator * new_var = new Variator(tree_nodes);
                // 23.04.2018 переносим оценку качества разбора 
                new_var->AddScore(selected_result->res.GetNGramFreq().Composite());
                pack->Add(new_var);
            }
            else
            {
                // Для морфологического анализа достаточно создать вариатор из этих узлов.
                Variator * new_var = new Variator(tree_nodes);
                new_var->AddScore(selected_result->res.GetNGramFreq().Composite());
                pack->Add(new_var);
            }
        }
    }


    if (pack->vars().empty())
    {
        // Тут мы окажемся, если результаты анализа есть, но нет ни одного ПОЛНОГО покрытия всего пути правилами.
        // В таком случае просто генерируем вариаторы по результатам токенизации.
        GenerateAllPaths(dict, lexer, trace_log);
    }

    return pack;
}


void SynPatternTreeNodeMatchingResults::ApplyWordAssociations(Dictionary & dict)
{
    // Есть ли среди результатов такие словоформы, в которых несколько альтернативных версий относятся к разным
    // словарным статьям?

    std::set<const Word_Form*> score_them;
    typedef MATCHING_ALTS::const_iterator IT;

    for (lem::Container::size_type i = 0; i < results.size(); ++i)
    {
        const SynPatternResult * q_result = results[i];

        for (IT it = q_result->matched_alts.begin(); it != q_result->matched_alts.end(); ++it)
        {
            const Solarix::Word_Form & wf = *it->first;
            if (wf.VersionCount() > 1)
            {
                const int ekey0 = wf.GetEntryKey();
                for (int k = 1; k < wf.VersionCount(); ++k)
                    if (wf.GetVersion(k)->GetEntryKey() != ekey0)
                    {
                        for (int j = 0; j < wf.VersionCount(); ++j)
                            score_them.insert(wf.GetVersion(j));

                        break;
                    }
            }
        }
    }

    if (!score_them.empty())
    {
        std::set<const Solarix::Word_Form *> processed_wf;
        std::multimap<const Solarix::Word_Form *, const Solarix::Word_Form *> edges_down;
        std::multimap<const Solarix::Word_Form *, const Solarix::Word_Form *> edges_up;

        typedef std::pair<const Solarix::Word_Form *, const Solarix::Word_Form *> EDGE;
        std::set<EDGE> visited_edges;

        for (lem::Container::size_type i = 0; i < results.size(); ++i)
        {
            processed_wf.clear();
            edges_down.clear();
            edges_up.clear();
            visited_edges.clear();

            SynPatternResult * q_result = results[i];

            // Составим матрицу связанности
            for (LINKAGE_EDGES::const_iterator it = q_result->linkage_edges.begin(); it != q_result->linkage_edges.end(); ++it)
            {
                const PatternLinkEdge & l = *it;
                edges_down.insert(std::make_pair(l.from, l.to));
                edges_up.insert(std::make_pair(l.to, l.from));
            }

            for (IT it = q_result->matched_alts.begin(); it != q_result->matched_alts.end(); ++it)
            {
                const Solarix::Word_Form * wf0 = it->first;
                const int iver = it->second;

                // Для этой словоформы ищем ассоциации.
                const Solarix::Word_Form * wf = wf0->GetVersion(iver);

                if (score_them.find(wf) != score_them.end() && processed_wf.find(wf) == processed_wf.end())
                {
                    processed_wf.insert(wf);

                    // Ищем ассоциации для словоформы wf.
                    lem::PtrCollect<WordAssociation> assocs;
                    lem::MCollect<int> id_assocs;
                    dict.GetLexAuto().ListAssociationsForEntry(wf->GetEntryKey(), id_assocs);

                    if (!id_assocs.empty())
                    {
                        for (lem::Container::size_type q = 0; q < id_assocs.size(); ++q)
                        {
                            WordAssociation * assoc = dict.GetSynGram().GetStorage().LoadAssocitation(id_assocs[q]);
                            assocs.push_back(assoc);
                        }

                        // надо пройтись по всем связанным ребрам в графе
                        float score = ApplyLinkedAssocs(
                            dict, wf, assocs, edges_down, edges_up, visited_edges, processed_wf
#if defined SOL_DEBUGGING
                            , results[i]->scorer_id_src
#endif
                        );

                        if (score > 0.0F && score < 1.0F)
                            q_result->res.AddNGramFreq(NGramScore(1));
                        else
                            q_result->res.AddNGramFreq(NGramScore(ceil(score)));
                    }
                }
            }
        }
    }

    return;
}


float SynPatternTreeNodeMatchingResults::ApplyLinkedAssocs(
    Dictionary & dict,
    const Solarix::Word_Form * wf,
    const lem::MCollect<WordAssociation*> & assocs,
    const std::multimap<const Solarix::Word_Form *, const Solarix::Word_Form *> & edges_down,
    const std::multimap<const Solarix::Word_Form *, const Solarix::Word_Form *> & edges_up,
    std::set< std::pair<const Solarix::Word_Form *, const Solarix::Word_Form *> > & visited_edges,
    std::set<const Solarix::Word_Form *> & processed_wf
#if defined SOL_DEBUGGING
    , lem::MCollect<int> & scorer_id_src
#endif
) const
{
    float s = 0.0F;

    typedef std::multimap<const Solarix::Word_Form *, const Solarix::Word_Form *> M;
    typedef M::const_iterator IT;

    typedef std::pair<const Solarix::Word_Form *, const Solarix::Word_Form *> EDGE;

    // Все ребра, для которых узел wf вляется корнем.
    std::pair<IT, IT> p_down = edges_down.equal_range(wf);
    for (IT it = p_down.first; it != p_down.second; ++it)
    {
        EDGE e(wf, it->second);
        EDGE e_rev(it->second, wf);
        if (visited_edges.find(e) == visited_edges.end() && visited_edges.find(e_rev) == visited_edges.end())
        {
            visited_edges.insert(e);
            s += ApplyLinkedAssocs(
                dict, wf, it->second, 1, assocs, edges_down, edges_up, visited_edges, processed_wf
#if defined SOL_DEBUGGING
                , scorer_id_src
#endif
            );
        }
    }

    // Все ребра, для которых wf является веткой
    std::pair<IT, IT> p_up = edges_up.equal_range(wf);
    for (IT it = p_up.first; it != p_up.second; ++it)
    {
        EDGE e(it->second, wf);
        EDGE e_rev(wf, it->second);
        if (visited_edges.find(e) == visited_edges.end() && visited_edges.find(e_rev) == visited_edges.end())
        {
            visited_edges.insert(e);

            s += ApplyLinkedAssocs(
                dict, wf, it->second, 1, assocs, edges_down, edges_up, visited_edges, processed_wf
#if defined SOL_DEBUGGING
                , scorer_id_src
#endif
            );
        }
    }

    return s;
}



float SynPatternTreeNodeMatchingResults::ApplyLinkedAssocs(
    Dictionary & dict,
    const Solarix::Word_Form * wf,
    const Solarix::Word_Form * current_wf,
    int current_distance,
    const lem::MCollect<WordAssociation*> & assocs,
    const std::multimap<const Solarix::Word_Form *, const Solarix::Word_Form *> & edges_down,
    const std::multimap<const Solarix::Word_Form *, const Solarix::Word_Form *> & edges_up,
    std::set< std::pair<const Solarix::Word_Form *, const Solarix::Word_Form *> > & visited_edges,
    std::set<const Solarix::Word_Form *> & processed_wf
#if defined SOL_DEBUGGING
    , lem::MCollect<int> & scorer_id_src
#endif
) const
{
    float score_sum = 0;

    for (lem::Container::size_type i = 0; i < assocs.size(); ++i)
    {
        const WordAssociation & assoc = *assocs[i];

        if (assoc.Match(*current_wf, dict))
        {
            score_sum += float(assoc.GetScore()) / current_distance;

#if defined SOL_DEBUGGING
            scorer_id_src.push_back(assoc.GetSourceLocation());
#endif
        }
    }

    processed_wf.insert(current_wf);

    typedef std::pair<const Solarix::Word_Form *, const Solarix::Word_Form *> EDGE;

    typedef std::multimap<const Solarix::Word_Form *, const Solarix::Word_Form *> M;
    typedef M::const_iterator IT;

    // Все ребра, для которых узел current_wf вляется корнем.
    std::pair<IT, IT> p_down = edges_down.equal_range(current_wf);
    for (IT it = p_down.first; it != p_down.second; ++it)
    {
        EDGE e(std::make_pair(current_wf, it->second));
        EDGE e_rev(std::make_pair(it->second, current_wf));

        if (visited_edges.find(e) == visited_edges.end() && visited_edges.find(e_rev) == visited_edges.end())//&& processed_wf.find(it->second)==processed_wf.end() )
        {
            visited_edges.insert(e);
            score_sum += ApplyLinkedAssocs(
                dict, wf, it->second, current_distance + 1, assocs, edges_down, edges_up, visited_edges, processed_wf
#if defined SOL_DEBUGGING
                , scorer_id_src
#endif
            );
        }
    }

    // Все ребра, для которых current_wf является веткой
    std::pair<IT, IT> p_up = edges_up.equal_range(current_wf);
    for (IT it = p_up.first; it != p_up.second; ++it)
    {
        EDGE e(std::make_pair(it->second, current_wf));
        EDGE e_rev(std::make_pair(current_wf, it->second));

        if (visited_edges.find(e) == visited_edges.end() && visited_edges.find(e_rev) == visited_edges.end())//&& processed_wf.find(it->second)==processed_wf.end() )
        {
            visited_edges.insert(e);
            score_sum += ApplyLinkedAssocs(
                dict, wf, it->second, current_distance + 1, assocs, edges_down, edges_up, visited_edges, processed_wf
#if defined SOL_DEBUGGING
                , scorer_id_src
#endif
            );
        }
    }

    return score_sum;
}


class LinkEdgeContainer_Wrapper : public LinkEdgeContainer
{
private:
    const lem::MCollect<PatternLinkEdge> & edges;

public:
    LinkEdgeContainer_Wrapper(const SynPatternResult & cur_result) : edges(cur_result.linkage_edges) {}

    virtual ~LinkEdgeContainer_Wrapper() {}
    virtual int size() const { return CastSizeToInt(edges.size()); }
    virtual const PatternLinkEdge& operator[](int index) const { return edges[index]; }
};



void SynPatternTreeNodeMatchingResults::ApplyTreeScorers(
    SynGram &sg,
    WordEntrySet &sets,
    SynPatternResult & res,
    const ElapsedTimeConstraint & constraints,
    TrTrace *trace_log
) const
{
    lem::MCollect<int> headpoint_ids, is_root;
    lem::PtrCollect<TreeScorerResult> scores;

    typedef std::set<const Solarix::Word_Form*> PROCESSED_NODES;
    PROCESSED_NODES processed_nodes, processed_nodes2, try_second_nodes;

    // Отдельно накопим id тех правил, которые привязаны не через корень.
    lem::MCollect<int> id_headpoint_nonroots;
    lem::PtrCollect<TreeScorerResult> nonroot_scores;

    TreeScorerApplicationContext empty_context(nullptr);

    TreeScorerGroupParams default_params;

    LinkEdgeContainer_Wrapper edge_container(res);

    // Идем по узлам, которые упомянуты в связках в res.
    for (lem::Container::size_type i = 0; i < res.linkage_edges.size(); ++i)
    {
        const PatternLinkEdge & edge = res.linkage_edges[i];

        const Solarix::Word_Form & node = *edge.from;

        if (processed_nodes.find(&node) == processed_nodes.end())
        {
            processed_nodes.insert(&node);

            // Найдем все правила, которые применимы к дереву с таким корнем.
            headpoint_ids.clear();
            scores.clear();
            is_root.clear();

            sg.GetStorage().ListTreeScorers(UNKNOWN, node, headpoint_ids, scores, is_root);

            // Теперь каждое правило пытаемся сопоставить.
            TreeScorerBoundVariables bound_variables;
            for (lem::Container::size_type j = 0; j < headpoint_ids.size(); ++j)
            {
                const int id_headpoint = headpoint_ids[j];

                if (!is_root[j])
                {
                    if (id_headpoint_nonroots.find(id_headpoint) == UNKNOWN)
                    {
                        id_headpoint_nonroots.push_back(id_headpoint);
                        nonroot_scores.push_back(scores[j]);
                        scores[j] = nullptr;
                    }
                }
                else
                {
                    bound_variables.Clear();
                    if (TreeScorerMatcher::MatchTreeScorer(sg, sets, id_headpoint, node, edge_container, empty_context, default_params, bound_variables, constraints, trace_log))
                    {
                        scores[j]->Link(sg.GetDict().GetLexAuto().GetFunctions().Get());
                        const int delta_score = scores[j]->Calculate(sg.GetDict(), bound_variables, constraints, trace_log);
                        res.res.AddNGramFreq(NGramScore(delta_score));

#if defined SOL_DEBUGGING
                        const int id_src = sg.GetStorage().GetTreeScorerHeadpointSrc(id_headpoint);
                        res.scorer_id_src.push_back(id_src);
#endif
                    }
                }
            }
        }

        const Solarix::Word_Form & node2 = *edge.to;

        if (processed_nodes2.find(&node2) != processed_nodes2.end())
            continue;

        processed_nodes2.insert(&node2);

        // Найдем все правила, которые применимы к дереву с таким корнем.
        headpoint_ids.clear();
        scores.clear();
        is_root.clear();

        sg.GetStorage().ListTreeScorers(UNKNOWN, node2, headpoint_ids, scores, is_root);

        // Теперь каждое правило пытаемся сопоставить.
        for (lem::Container::size_type j = 0; j < headpoint_ids.size(); ++j)
        {
            const int id_headpoint = headpoint_ids[j];

            if (!is_root[j] && id_headpoint_nonroots.find(id_headpoint) == UNKNOWN)
            {
                id_headpoint_nonroots.push_back(id_headpoint);
                nonroot_scores.push_back(scores[j]);
                scores[j] = nullptr;
            }
            else if (is_root[j])
            {
                // можем потом попробовать применить правила с одним термом в опорном контексте.
                try_second_nodes.insert(&node2);
            }
        }
    }

    TreeScorerBoundVariables bound_variables;
    for (PROCESSED_NODES::const_iterator it = try_second_nodes.begin(); it != try_second_nodes.end(); ++it)
    {
        const Word_Form * node = *it;
        if (processed_nodes.find(node) == processed_nodes.end())
        {
            headpoint_ids.clear();
            scores.clear();
            is_root.clear();

            sg.GetStorage().ListTreeScorers(UNKNOWN, *node, headpoint_ids, scores, is_root);

            // Теперь каждое правило пытаемся сопоставить.
            for (lem::Container::size_type j = 0; j < headpoint_ids.size(); ++j)
            {
                const int id_headpoint = headpoint_ids[j];

                if (is_root[j])
                {
                    bound_variables.Clear();
                    if (TreeScorerMatcher::MatchTreeScorer(sg, sets, id_headpoint, *node, edge_container, empty_context, default_params, bound_variables, constraints, trace_log))
                    {
                        scores[j]->Link(sg.GetDict().GetLexAuto().GetFunctions().Get());
                        const int delta_score = scores[j]->Calculate(sg.GetDict(), bound_variables, constraints, trace_log);
                        res.res.AddNGramFreq(NGramScore(delta_score));

#if defined SOL_DEBUGGING
                        const int id_src = sg.GetStorage().GetTreeScorerHeadpointSrc(id_headpoint);
                        res.scorer_id_src.push_back(id_src);
#endif
                    }
                }
            }
        }
    }

    if (!id_headpoint_nonroots.empty())
    {
        // придется делать еще один обход дерева и применять все правила, которые привязаны не через корень.
        std::set<const Solarix::Word_Form*> visited;

        for (lem::Container::size_type i = 0; i < res.linkage_edges.size(); ++i)
        {
            const PatternLinkEdge & edge = res.linkage_edges[i];
            const Solarix::Word_Form & node = *edge.from;
            if (visited.find(&node) == visited.end())
            {
                visited.insert(&node);

                for (lem::Container::size_type j = 0; j < id_headpoint_nonroots.size(); ++j)
                {
                    const int id_headpoint = id_headpoint_nonroots[j];

                    if (TreeScorerMatcher::MatchTreeScorer(sg, sets, id_headpoint, node, edge_container, empty_context, default_params, bound_variables, constraints, trace_log))
                    {
                        nonroot_scores[j]->Link(sg.GetDict().GetLexAuto().GetFunctions().Get());
                        const int delta_score = nonroot_scores[j]->Calculate(sg.GetDict(), bound_variables, constraints, trace_log);

                        res.res.AddNGramFreq(NGramScore(delta_score));

#if defined SOL_DEBUGGING
                        const int id_src = sg.GetStorage().GetTreeScorerHeadpointSrc(id_headpoint);
                        res.scorer_id_src.push_back(id_src);
#endif
                    }
                }
            }
        }
    }

    return;
}



void SynPatternTreeNodeMatchingResults::Print(Dictionary & dict, lem::OFormatter & out) const
{
    for (lem::Container::size_type i = 0; i < results.size(); ++i)
    {
        out.printf("%60h-\n");
        const SynPatternResult * r = results[i];
        r->Print(out, dict.GetSynGram());
        r->PrintLinks(out, dict.GetSynGram());
        r->PrintLinkageGroups(out, dict.GetSynGram());
        out.eol();
    }

    return;
}


void SynPatternTreeNodeMatchingResults::FilterMaxCoverage()
{
    int max_coverage = 0;

    for (lem::Container::size_type i = 0; i < results.size(); ++i)
    {
        const SynPatternResult * r = results[i];
        const int n_edge = CastSizeToInt(r->linkage_edges.size());
        max_coverage = std::max(max_coverage, n_edge);
    }

    if (max_coverage > 0)
    {
        for (int i = CastSizeToInt(results.size()) - 1; i >= 0; i--)
        {
            if (CastSizeToInt(results[i]->linkage_edges.size()) < max_coverage)
                results.Remove(i);
        }
    }

    return;
}



void SynPatternTreeNodeMatchingResults::AddResult(SynPatternResult * r)
{
    LEM_CHECKIT_Z(r != nullptr);
    results.push_back(r);
    return;
}

#endif
