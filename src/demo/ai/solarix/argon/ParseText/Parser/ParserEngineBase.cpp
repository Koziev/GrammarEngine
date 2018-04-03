#undef HTTP_PARSER_SERVICE

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <boost/regex.hpp>

#include <lem/console_streams.h>
#include <lem/date_time.h>
#include <lem/xml_parser.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/MorphologyModels.h>
#include <lem/solarix/print_variator.h>
#include <lem/solarix/la_autom.h>

#if defined HTTP_PARSER_SERVICE
#include "HttpServer.h"
#endif


#if defined LEM_WINDOWS
#include <windows.h>
#endif

#include <libdesr.h>

#include "ParserEngineBase.h"

using namespace Solarix;

ParserEngineBase::ParserEngineBase()
{
    current_analysis = NULL;
    hDESR = NULL;
    casing_coder = NULL;

    beam_size = 20;
    verbose = false;

    tagger_type = 0; // -1 - none, 0 - CRF POS tagger
    parser_type = -1; // -1 - none, 0 - DeSR, 1 - top-down Early, 2 - chunker
    lemmatizer_type = -1; // -1 none

    word_count = 0;
    sent_count = 0;
}



ParserEngineBase::~ParserEngineBase()
{
    if (parser_type == 0 && hDESR != NULL)
    {
        DesrDeleteEngine(hDESR);
        hDESR = NULL;
    }

    delete current_analysis;
    current_analysis = NULL;
}


void ParserEngineBase::LoadDictionary(const lem::Path & dict_path)
{
    opt.load_semnet = true;
    opt.ngrams = true;
    opt.lexicon = true;

    bool ok = false;

    try
    {
        ok = dict.LoadModules(dict_path, opt);
    }
    catch (...)
    {
        ok = false;
    }

    if (!ok)
    {
        throw E_BaseException(lem::format_str(L"Could not load the dictionary using [%ws]\n", dict_path.GetUnicode().c_str()));
    }

    return;
}


void ParserEngineBase::LoadModels(const lem::Path & dict_path)
{
    hDESR = NULL;

    lem::Xml::Parser xml_dict;
    xml_dict.Load(dict_path);

    if (parser_type == 0)
    {
        // Загрузим модель для синт. парсера DeSR
        lem::UFString desr_path = xml_dict.Get_By_Path(L"dataroot.models.desr");

        lem::Path desr_folder(dict_path);
        desr_folder.RemoveLastLeaf();
        desr_folder.ConcateLeaf(desr_path);
        desr_folder = desr_folder.GetAbsolutePath();

        // В этом файле сохранены параметры для получения фич предложения.
        lem::Path desr_codebook_path(desr_folder);
        desr_codebook_path.ConcateLeaf(L"syntax.codebook");

        lem::Path desr_model(desr_folder);
        desr_model.ConcateLeaf(L"syntax.model");

        if (verbose)
        {
            lem::mout->printf("syntax parser model file=%s\n", desr_model.GetAscii().c_str());
        }

        if (!desr_model.DoesExist())
        {
            throw E_BaseException(lem::format_str(L"File [%ws] does not exist", desr_model.GetUnicode().c_str()));
        }

        lem::Path desr_conf(desr_folder);
        desr_conf.ConcateLeaf(L"desr.conf");

        lem::BinaryReader desr_codebook_stream(desr_codebook_path);
        desr_codebook.LoadBin(desr_codebook_stream);
        hDESR = DesrInit(10, desr_conf.GetAscii().c_str(), desr_model.GetAscii().c_str());
    }

    if (parser_type == 2)
    {
        // Используется чанкер.
        lem::UFString desr_path = xml_dict.Get_By_Path(L"dataroot.models.chunker");

        lem::Path chunker_folder(dict_path);
        chunker_folder.RemoveLastLeaf();
        chunker_folder.ConcateLeaf(desr_path);
        chunker_folder = chunker_folder.GetAbsolutePath();

        // В этом файле сохранены параметры для получения фич предложения.
        lem::Path desr_codebook_path(chunker_folder);
        desr_codebook_path.ConcateLeaf(L"chunker.codebook");

        lem::Path chunker_model_path(chunker_folder);
        chunker_model_path.ConcateLeaf(L"chunker.model");

        if (verbose)
        {
            lem::mout->printf("chunker model file=%s\n", chunker_model_path.GetAscii().c_str());
        }

        if (!chunker_model_path.DoesExist())
        {
            throw E_BaseException(lem::format_str(L"File [%ws] does not exist", chunker_model_path.GetUnicode().c_str()));
        }

        chunker_model.Load(desr_codebook_path, chunker_model_path);
    }



    // -------------------------------------------------------------------------

    // Определим язык разбираемых текстов.
    // По умолчанию берем тот, который указан базовым в словарной базе.
    // Но пользователь может указать в командной строке явно другой язык.
    language_id = UNKNOWN;
    if (language_name.empty())
    {
        language_id = dict.GetDefaultLanguage();
    }
    else
    {
        language_id = dict.GetSynGram().Find_Language(language_name);
        if (language_id == UNKNOWN)
        {
            throw E_BaseException(lem::format_str(L"Unknown language [%ws]", language_name.c_str()));
        }
    }


    // ---------------------------------------------------------------------------


    if (lemmatizer_type == 0)
    {
        lem::Path lemm2_folder(dict_path);
        lemm2_folder.RemoveLastLeaf();
        lemm2_folder = lemm2_folder.GetAbsolutePath();
        lemmatizer2.Load(lemm2_folder);
    }


    // ---------------------------------------------------------------------------

    current_analysis = new Solarix::WrittenTextAnalysisSession(&dict, NULL);
    current_analysis->params.SetLanguageID(language_id);
    current_analysis->params.AllowPrimaryFuzzyWordRecog = false;
    current_analysis->params.AllowDynform = true;
    current_analysis->params.ApplyModel = true;

    // Ограничение на суммарное затраченное время в миллисекундах
    const int MaxMillisecTimeout = 0; //180000;
    current_analysis->params.timeout.max_elapsed_millisecs = MaxMillisecTimeout > 0 ? MaxMillisecTimeout : lem::int_max;

    // Ограничение на макс. число параллельно проверяемых альтернативных путей построения синтаксического дерева
    current_analysis->params.timeout.max_alt = beam_size;

    current_analysis->params.CompleteAnalysisOnly = false;
    current_analysis->params.ConfigureSkipToken();

    casing_coder = &dict.GetLexAuto().GetCasingCoder();
}


void ParserEngineBase::ParseString(const lem::UFString & sentence,
    int paragraph_id,
    bool emit_morph,
    bool allow_fuzzy_recognition,
    bool render_tree,
    ParsingResultFormatter & out_stream)
{
    out_stream.StartSentence(sentence, paragraph_id);

    current_analysis->params.AllowPrimaryFuzzyWordRecog = allow_fuzzy_recognition; // тут многопоточность заканчивается.

    if (parser_type == -1)
    {
        // Выполняется только part-of-speech tagging, синтаксический анализ не используется.

        if (tagger_type == 0)
        {
            // применяем вероятностную модель морфологии для снятия неоднозначностей, но правила не применяем.
            current_analysis->ApplyFilters(sentence);
        }
        else
        {
            // точный и медленный POS Tagger...
            current_analysis->MorphologicalAnalysis(sentence);
        }

        const Res_Pack & pack0 = current_analysis->GetPack();
        const Solarix::Variator & tagging = *pack0.vars().front();
        DumpMorphTokens(tagging, emit_morph, out_stream);

        const int n_token = CastSizeToInt(tagging.roots_list().size() - 2);
        word_count += n_token;
    }
    else if (parser_type == 0)
    {
        // DESR вероятностный парсер

        // Вытащим некоторые параметры формирования фич
        bool EMIT_FEAT = lem::to_bool(desr_codebook.FindModelParam(L"EMIT_FEAT", L"0"));
        // TODO - потом надо учесть остальные параметры, если они окажутся эффективными.

        // применяем вероятностную модель морфологии для снятия неоднозначностей, но правила не применяем.
        current_analysis->ApplyFilters(sentence);

        const Res_Pack & pack0 = current_analysis->GetPack();
        const Solarix::Variator & tagging = *pack0.vars().front();

        if (tagger_type != -1)
        {
            DumpMorphTokens(tagging, emit_morph, out_stream);
        }

        const int n_token = CastSizeToInt(tagging.roots_list().size() - 2);
        word_count += n_token;


        // выполним парсинг, используя результаты POS Tagger'а
        out_stream.StartSyntaxTree();

        lem::FString desr_input;

        for (lem::Container::size_type i = 1; i < tagging.roots_list().size() - 1; ++i)
        {
            const Solarix::Word_Form & wf = tagging.roots_list()[i]->GetNode();

            const ModelTagMatcher * tm = desr_codebook.Match(&wf, dict);
            int id_tag = tm == NULL ? -1 : tm->GetId();

            /*
                     #if LEM_DEBUGGING==1
                     lem::mout->printf( "token #%d word=%us tag=%d ", i, wf.GetName()->c_str(), id_tag );
                     tm->Print( *lem::mout, dict );
                     lem::mout->eol();
                     tm->Match( wf, dict );
                     #endif
                     */


            lem::FString feats;
            if (EMIT_FEAT)
            {
                for (int i = 0; i < wf.GetnPair(); ++i)
                {
                    auto pair = wf.GetPair(i);
                    if (!feats.empty())
                    {
                        // Predefined delimiter of individual tags
                        feats += '|';
                    }

                    feats += lem::format_str("%d=%d", pair.GetCoord().GetIndex(), pair.GetState());
                }
            }

            if (feats.empty())
            {
                feats = "_";
            }

            desr_input += lem::format_str("%d\t_\t_\t_\t%d\t%s\t?\t?\t_\t_\n", CastSizeToInt(i), id_tag, feats.c_str());
        }

        // lem::mout->printf( "DEBUG: Before syntax...\n" );
        char * desr_res_str = DesrTag(hDESR, desr_input.c_str());
        // lem::mout->printf( "DEBUG: After syntax...\n" );

        std::string s_res(desr_res_str);

        // разбиваем выдачу на строки
        boost::regex rx_line("^(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)$", boost::regex_constants::icase);

        boost::sregex_iterator m2;
        int itoken = 1;
        for (boost::sregex_iterator it(s_res.begin(), s_res.end(), rx_line); it != m2; ++it, ++itoken)
        {
            const boost::match_results<std::string::const_iterator> & mx = *it;
            const std::string & parent_id = mx[7].str();
            lem::UFString link_name = lem::from_utf8(mx[8].str().c_str());

            int word_index = itoken - 1;
            int parent_index = lem::to_int(parent_id) - 1;

            const Solarix::Word_Form & node_wf = tagging.roots_list()[itoken]->GetNode();
            const lem::UCString & node_word = *node_wf.GetName();

            if (parent_index == -1)
            {
                out_stream.PrintSyntaxNode(true, false, node_word.c_str(), word_index, NULL, -1, NULL);
            }
            else
            {
                const Solarix::Word_Form & parent_wf = tagging.roots_list()[parent_index + 1]->GetNode();
                const lem::UCString & parent_word(*parent_wf.GetName());
                out_stream.PrintSyntaxNode(false, false, node_word.c_str(), word_index, link_name.c_str(), parent_index, parent_word.c_str());
            }
        }

        DesrFreeResult(hDESR, desr_res_str);

        out_stream.EndSyntaxTree();
    }
    else if (parser_type == 1)
    {
        // Медленный top-down парсер
        // Отдельный POS Tagger не запускаем.

        current_analysis->SyntacticAnalysis(sentence);
        const Res_Pack & linkage = current_analysis->GetPack();

        const Solarix::Variator & var = *linkage.vars().front();
        int nroot = var.roots_list().size();

        Solarix::Variator tagging;
        for (lem::Container::size_type i = 0; i < var.roots_list().size(); ++i)
        {
            Solarix::Tree_Node * node = var.roots_list()[i];
            tagging.Add(node);
        }

        const int n_token = tagging.roots_list().size() - 2;

        if (tagger_type != -1)
        {
            DumpMorphTokens(tagging, emit_morph, out_stream);

            for (lem::Container::size_type i = 0; i < var.roots_list().size(); ++i)
            {
                tagging.ForgetTree(i);
            }
        }

        std::set<int> roots;
        std::map<int, std::pair<int, int> > child_to_parent;
        std::map<int, lem::UCString> node2word;

        out_stream.StartSyntaxTree();
        for (lem::Container::size_type i = 1; i < var.roots_list().size() - 1; ++i)
        {
            const Solarix::Tree_Node & node = *var.roots_list()[i];

            roots.insert(node.GetNode().GetOriginPos());
            node2word.insert(std::make_pair(node.GetNode().GetOriginPos(), *node.GetNode().GetName()));

            AssembleEdges(node, child_to_parent, node2word);
        }

        for (int word_pos = 0; word_pos < n_token; ++word_pos)
        {
            const lem::UCString & node_word(node2word[word_pos].c_str());

            if (roots.find(word_pos) != roots.end())
            {
                out_stream.PrintSyntaxNode(true, false, node_word.c_str(), word_pos, NULL, -1, NULL);
            }
            else if (child_to_parent.find(word_pos) == child_to_parent.end())
            {
                out_stream.PrintSyntaxNode(true, false, node_word.c_str(), word_pos, NULL, -1, NULL);
            }
            else
            {
                const std::pair<int, int> & parent_and_link = child_to_parent[word_pos];
                const UCString & link_name = dict.GetSynGram().coords()[0].GetStateName(parent_and_link.second);
                const lem::UCString & parent_word(node2word[parent_and_link.first]);
                int parent_index = parent_and_link.first;
                out_stream.PrintSyntaxNode(false, false, node_word.c_str(), word_pos, link_name.c_str(), parent_index, parent_word.c_str());
            }
        }

        out_stream.EndSyntaxTree();

        if (render_tree)
        {
            lem::MemFormatter mem;
            Solarix::print_syntax_tree(L"", linkage, dict, mem, false, false);
            lem::UFString str = mem.string();
            out_stream.PrintTreeRendering(str.c_str());
        }
    }
    else if (parser_type == 2)
    {
        // Chunker в качестве синтаксического парсера.

        // применяем вероятностную модель морфологии для снятия неоднозначностей, но правила не применяем.
        current_analysis->ApplyFilters(sentence);

        const Res_Pack & pack0 = current_analysis->GetPack();
        const Solarix::Variator & tagging = *pack0.vars().front();

        if (tagger_type != -1)
        {
            DumpMorphTokens(tagging, emit_morph, out_stream);
        }

        // Теперь чанкер.
        std::vector<int> chunk_labels = chunker_model.Apply(dict, tagging.roots_list());

        const int n_token = CastSizeToInt(tagging.roots_list().size() - 2);
        word_count += n_token;

        out_stream.StartChunking();
        for (lem::Container::size_type i = 1; i < tagging.roots_list().size() - 1; ++i)
        {
            int word_position = CastSizeToInt(i) - 1;
            out_stream.PrintChunking(word_position, chunk_labels[word_position]);
        }
        out_stream.EndChunking();
    }


    out_stream.EndSentence();

    return;
}



void ParserEngineBase::AssembleEdges(const Solarix::Tree_Node & node,
    std::map<int, std::pair<int, int> > & child_to_parent,
    std::map<int, lem::UCString> & node2word)
{
    for (int j = 0; j < node.leafs().size(); ++j)
    {
        const Solarix::Tree_Node & child = node.leafs()[j];
        node2word.insert(std::make_pair(child.GetNode().GetOriginPos(), *child.GetNode().GetName()));

        child_to_parent.insert(std::make_pair(child.GetNode().GetOriginPos(), std::make_pair(node.GetNode().GetOriginPos(), node.GetLinkIndex(j).GetState())));

        AssembleEdges(child, child_to_parent, node2word);
    }

    return;
}



void ParserEngineBase::DumpMorphTokens(const Solarix::Variator & tagging, bool emit_morph, ParsingResultFormatter & out_stream)
{
    static lem::UCString NUMBER_CLASS = L"NUM_WORD";

    out_stream.StartTokens();
    for (lem::Container::size_type i = 1; i < tagging.roots_list().size() - 1; ++i)
    {
        out_stream.StartToken();

        const Solarix::Word_Form & wf = tagging.roots_list()[i]->GetNode();
        const lem::UCString & sword(*wf.GetName());

        lem::UFString slemma;
        bool is_unknown = false;
        int id_entry = wf.GetEntryKey();
        const SG_Entry & e = dict.GetSynGram().GetEntry(id_entry);
        const SG_Class & e_class = dict.GetSynGram().GetClass(e.GetClass());

        if (e_class.GetName() == NUMBER_CLASS)
        {
            slemma = wf.GetName()->c_str();
        }
        else if (dict.GetSynGram().GetUEntries().find(id_entry) == UNKNOWN)
        {
            lem::UFString w(e.GetName().c_str());
            casing_coder->RestoreCasing(w, id_entry);
            w.subst_all(L" - ", L"-");
            w.subst_all(L" ' ", L"'");
            slemma = w;
        }
        else
        {
            is_unknown = true;
            lem::UFString word_lemma;
            lemmatizer2.Lemmatize(wf, word_lemma, dict);
            slemma = word_lemma;
        }

        out_stream.PrintToken(!is_unknown, sword.c_str(), slemma.c_str(), wf.GetOriginPos(), e_class.GetName().c_str());

        if (emit_morph)
        {
            out_stream.StartTags();
            for (int itag = 0; itag < wf.GetnPair(); ++itag)
            {
                int id_coord = wf.GetPair(itag).GetCoord().GetIndex();
                int id_state = wf.GetPair(itag).GetState();

                if (dict.GetSynGram().coords().GetCoord(id_coord).IsBistable())
                {
                    out_stream.PrintTag( itag,
                        dict.GetSynGram().coords().GetCoord(id_coord).GetName().string().c_str(),
                        lem::to_ustr(id_state).c_str() );
                }
                else
                {
                    out_stream.PrintTag( itag, 
                        dict.GetSynGram().coords().GetCoord(id_coord).GetName().string().c_str(),
                        dict.GetSynGram().coords().GetCoord(id_coord).GetStateName(id_state).c_str());
                }
            }

            out_stream.EndTags();
        }

        out_stream.EndToken();
    }

    out_stream.EndTokens();

    return;
}
