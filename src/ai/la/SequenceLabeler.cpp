#include <lem/streams.h>
#include <lem/strings.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/MorphologyModels.h>

// #9 07.01.2018  баг с многопоточным использованием CRFSuite

using namespace Solarix;


SequenceLabelerModel::SequenceLabelerModel() : BasicModel()
{
#if defined SOL_CRF_MODEL
    model = nullptr;
    attrs = nullptr;
    labels = nullptr;
    tagger = nullptr;
#endif

    CONTEXT_SIZE = -1;
    EMIT_PAIRWISE_FEATURE = false;
    EMIT_TRIPLE_FEATURE = false;
    EMIT_AA_FEATURE = true;
    EMIT_AA_FOR_CONTEXT = false;
}


SequenceLabelerModel::~SequenceLabelerModel()
{
}


bool SequenceLabelerModel::Load()
{
#if defined SOL_CRF_MODEL
    if (!folder.empty())
    {
#if defined LEM_THREADS
        lem::Process::RWU_ReaderGuard rlock(cs);
#endif

        if (!loaded)
        {
#if defined LEM_THREADS
            lem::Process::RWU_WriterGuard wlock(rlock);
#endif

            lem::Path codebook_path(folder);
            codebook_path.ConcateLeaf(L"sequence_labeler.codebook");

            if (codebook_path.DoesExist())
            {
                codebook = new ModelCodeBook();
                lem::BinaryReader rdr(codebook_path);
                codebook->LoadBin(rdr);
                SetParamsAfterLoad();

                CONTEXT_SIZE = codebook->GetContextSize();

                lem::Path model_path(folder);
                model_path.ConcateLeaf(L"sequence_labeler.model");

                int ret = crfsuite_create_instance_from_file(model_path.GetAscii().c_str(), (void**)&model);
                if (ret != 0)
                {
                    LEM_STOPIT;
                }

                /* Obtain the dictionary interface representing the labels in the model. */
                if (ret = model->get_labels(model, &labels))
                {
                    LEM_STOPIT;
                }

                /* Obtain the dictionary interface representing the attributes in the model. */
                if (ret = model->get_attrs(model, &attrs))
                {
                    LEM_STOPIT;
                }

                /* Obtain the tagger interface. */
                if (ret = model->get_tagger(model, &tagger))
                {
                    LEM_STOPIT;
                }

                // ...

            }

            available = codebook != nullptr;
            loaded = true;
        }
    }
#else
    available = false;
    loaded = false;
#endif

    return loaded;
}


void SequenceLabelerModel::Apply(BasicLexer & lexer,
    Dictionary & dict,
    const ElapsedTimeConstraint & constraints,
    bool remove_incorrect_alts)
{
#if defined SOL_CRF_MODEL && defined SOL_CAA
    lem::Process::CritSecLocker cs_locker(&crf_critsect); // #9
    Apply_CRFSuite(lexer, dict, constraints, remove_incorrect_alts);
#endif
}


void SequenceLabelerModel::Apply_CRFSuite(BasicLexer & lexer,
    Dictionary & dict,
    const ElapsedTimeConstraint & constraints,
    bool remove_incorrect_alts)
{
#if defined SOL_CRF_MODEL && defined SOL_CAA

    // Для каждого токена мы будем находить наиболее вероятный вариант распознавания.
    // Так как путей в графе токенизации может быть много, то мы пройдем по всем путям,
    // и у одного токена может оказаться несколько достоверных вариантов распознавания.
    std::multimap< const LexerTextPos*, int > token2selection;

    const LexerTextPos * begin = lexer.GetBeginToken();

    lem::MCollect<const LexerTextPos*> leafs;
    lexer.FetchEnds(begin, leafs, lexer.GetParams().GetMaxRightLeaves());

    lem::MCollect<const LexerTextPos*> nodes;
    lem::MCollect<const LexerTextPos*> nodes2;

    const int nleaf = std::min(CastSizeToInt(leafs.size()), lexer.GetParams().timeout.max_tokenization_paths);

    for (int i = 0; i < nleaf && !constraints.Exceeded(0); ++i)
    {
        const LexerTextPos * leaf = leafs[i];
        nodes.clear();
        leaf->Collect_Right2Left(begin, nodes); // собираем все словоформы на этом пути

        const int src_token_count = CastSizeToInt(nodes.size()) - 2; // Сколько исходных токенов, не учитывая пропущенные, вошло в фрагменты в nodes2.

        nodes2.clear();
        // словоформы собраны в обратном порядке, развернем его.
        for (int j = CastSizeToInt(nodes.size()) - 1; j >= 0; --j)
        {
            nodes2.push_back(nodes[j]);
        }

        // Имеем цепочку токенов в nodes2, идущих в правильном порядке.
        lem::PtrCollect<ModelTokenFeatures> token_features;
        for (lem::Container::size_type j = 0; j < nodes2.size(); ++j)
        {
            const LexerTextPos * token = nodes2[j];

            ModelTokenFeatures * f;
            if (j == 0)
                f = Get_START_Features();
            else if (j == nodes2.size() - 1)
                f = Get_END_Features();
            else
                f = GetFeatures(token, dict);

            token_features.push_back(f);
        }


        // ВЫЗЫВАЕМ МОДЕЛЬ ДЛЯ ПОЛУЧЕНИЯ выходных тегов

        int N = 0, L = 0, ret = 0, lid = -1;
        crfsuite_instance_t inst;

        /* Initialize the objects for instance and evaluation. */
        //L = labels->num(labels);
        crfsuite_instance_init(&inst);
        //   crfsuite_evaluation_init(&eval, L);


#if LEM_DEBUGGING==1
//lem::OFormatter dbg_tags;
//dbg_tags.Open(lem::Path("crf.txt"));
#endif

        lem::MCollect<lem::CString> str_features;
        for (int iword = 0; iword < CastSizeToInt(nodes2.size()); ++iword)
        {
            str_features.clear();

            if (EMIT_FORM_TAGS)
            {
                for (int k = 0; k < token_features[iword]->allform_tags.size(); ++k)
                {
                    str_features.push_back(lem::format_str("%d", token_features[iword]->allform_tags[k]).c_str());
                }
            }

            // -----------------------------
            // признаки для текущего слова
            // -----------------------------
            PullFeatures1(str_features, token_features, iword, 0, true, EMIT_AA_FEATURE);

            const bool rich_context = EMIT_POS_FOR_CONTEXT || EMIT_MORPH_FOR_CONTEXT || EMIT_FORMTAGS_FOR_CONTEXT;

            // и соседние слова
            if (CONTEXT_SIZE > 3)
                PullFeatures1(str_features, token_features, iword, -4, rich_context, EMIT_AA_FOR_CONTEXT);

            if (CONTEXT_SIZE > 2)
                PullFeatures1(str_features, token_features, iword, -3, rich_context, EMIT_AA_FOR_CONTEXT);

            if (CONTEXT_SIZE > 1)
                PullFeatures1(str_features, token_features, iword, -2, rich_context, EMIT_AA_FOR_CONTEXT);

            if (CONTEXT_SIZE > 0)
            {
                PullFeatures1(str_features, token_features, iword, -1, rich_context, EMIT_AA_FOR_CONTEXT);
                PullFeatures1(str_features, token_features, iword, 1, rich_context, EMIT_AA_FOR_CONTEXT);
            }

            if (CONTEXT_SIZE > 1)
                PullFeatures1(str_features, token_features, iword, 2, rich_context, EMIT_AA_FOR_CONTEXT);

            if (CONTEXT_SIZE > 2)
                PullFeatures1(str_features, token_features, iword, 3, rich_context, EMIT_AA_FOR_CONTEXT);

            if (CONTEXT_SIZE > 3)
                PullFeatures1(str_features, token_features, iword, 4, rich_context, EMIT_AA_FOR_CONTEXT);

            if (EMIT_PAIRWISE_FEATURE)
            {
                PullFeatures2(str_features, token_features, iword, -3, -2);
                PullFeatures2(str_features, token_features, iword, -2, -1);
                PullFeatures2(str_features, token_features, iword, -1, 0);
                PullFeatures2(str_features, token_features, iword, 0, 1);
                PullFeatures2(str_features, token_features, iword, 1, 2);
                PullFeatures2(str_features, token_features, iword, 3, 4);
            }

            if (EMIT_TRIPLE_FEATURE)
            {
                PullFeatures3(str_features, token_features, iword, -3, -2, -1);
                PullFeatures3(str_features, token_features, iword, -2, -1, 0);
                PullFeatures3(str_features, token_features, iword, -1, 0, 1);
                PullFeatures3(str_features, token_features, iword, 0, 1, 2);
                PullFeatures3(str_features, token_features, iword, 1, 2, 3);
            }


            /*
                 #if LEM_DEBUGGING==1
                 lem::mout->printf( "CRF token #%d tags==>", iword );
                 for( int q=0; q<str_features.size(); ++q )
                 {
                  lem::mout->printf( " %s", str_features[q].c_str() );
                 }
                 lem::mout->eol();
                 #endif
            */

            // конвертируем str_features в набор тегов для текущего слова в цепочке

            /* Initialize an item. */
            crfsuite_item_t item;
            crfsuite_item_init(&item);

            for (int k = 0; k < CastSizeToInt(str_features.size()); ++k)
            {
                crfsuite_attribute_t cont;

                /* Fields after the first field present attributes. */
                const char * token_attr = str_features[k].c_str();
                int aid = attrs->to_id(attrs, /*token->attr*/token_attr);
                /* Ignore attributes 'unknown' to the model. */
                if (0 <= aid)
                {
                    /* Associate the attribute with the current item. */
                    //if (token->value && *token->value)
                    //{
                    //    crfsuite_attribute_set(&cont, aid, atof(token->value));
                    //}
                    //else
                    {
                        crfsuite_attribute_set(&cont, aid, 1.0);
                    }

                    crfsuite_item_append_attribute(&item, &cont);
                }
            }

            /* Append the item to the instance. */
            crfsuite_instance_append(&inst, &item, lid);
            crfsuite_item_finish(&item);
        }

        //#if LEM_DEBUGGING==1
        //dbg_tags.close();
        //#endif

        /* Initialize the object to receive the tagging result. */
        floatval_t score = 0;
        int *output = (int*)calloc(sizeof(int), inst.num_items);

        /* Set the instance to the tagger. */
        if ((ret = tagger->set(tagger, &inst)))
        {
            LEM_STOPIT;
        }

        /* Obtain the viterbi label sequence. */
        if ((ret = tagger->viterbi(tagger, output, &score)))
        {
            LEM_STOPIT;
        }

        // output содержит вектор ID тегов для токенов.
        lem::MCollect<int> tag_ids;

        for (i = 0; i < inst.num_items; ++i)
        {
            const char *label = NULL;
            labels->to_string(labels, output[i], &label);
            //fprintf(fpo, "%s", label);
            int id = UNKNOWN;
            if (lem::is_int(label))
                id = lem::to_int(label);

            tag_ids.push_back(id);

            labels->free(labels, label);
        }

        /*
          #if LEM_DEBUGGING==1
          lem::mout->printf( "MODEL OUTPUT TAGS:\n" );
          for( int k=0; k<inst.num_items; ++k )
           {
            lem::mout->printf( "TAG[%d]=%d --> ", k, tag_ids[k] );
            const ModelTagMatcher * matcher = codebook->GetTagMatcher( tag_ids[k] );
            matcher->Print( *lem::mout, dict );
            lem::mout->eol();
           }
          lem::mout->eol();
          #endif
        */

        //++N;

        /* Accumulate the tagging performance. */
        //if (opt->evaluate) {
        //    crfsuite_evaluation_accmulate(&eval, inst.labels, output, inst.num_items);
        //}

        //if (!opt->quiet) {
        //   output_result(fpo, tagger, &inst, output, labels, score, opt);
        //}

        free(output);
        crfsuite_instance_finish(&inst);

        //const int id_unknownentry = dict.GetLexAuto().GetUnknownEntryKey();

        for (lem::Container::size_type j = 0; j < nodes2.size(); ++j)
        {
            const LexerTextPos * token = nodes2[j];

            if (token->GetWordform()->VersionCount() > 1)
            {
                const int model_tag_id = tag_ids[j];
                if (model_tag_id != UNKNOWN)
                {
                    const ModelTagMatcher * matcher = codebook->GetTagMatcher(model_tag_id);
                    for (int v = 0; v < token->GetWordform()->VersionCount(); ++v)
                    {
                        const Word_Form * wf = token->GetWordform()->GetVersion(v);
                        if (matcher->Match(*wf, dict))
                        {
                            token2selection.insert(std::make_pair(token, v));
                        }
                    }
                }
            }
        }
    }

    /*
     #if defined LEM_DEBUGGING==1
     lem::mout->printf( "BEFORE MODEL APPLICATION:\n" );

     leafs.clear();
     lexer.FetchEnds( begin, leafs, 100 );

     for( lem::Container::size_type i=0; i<leafs.size(); ++i )
      {
       const LexerTextPos * leaf = leafs[i];
       nodes.clear();
       leaf->Collect_Right2Left( begin, nodes );

       const int src_token_count=CastSizeToInt(nodes.size()-2);

       nodes2.clear();
       for( int j=CastSizeToInt(nodes.size())-1; j>=0; --j )
        {
         nodes2.push_back( nodes[j] );
        }

       for( lem::Container::size_type j=0; j<nodes2.size(); ++j )
        {
         const LexerTextPos * token = nodes2[j];
         token->GetWordform()->Print( *lem::mout, &dict.GetSynGram(), true  );
         lem::mout->eol();
        }
      }

     lem::mout->printf( "-----\n" );
     #endif
    */

    // Для токенов оставляем только выбранные моделью варианты распознавания
    // ЛИБО
    // переносим подтвержденные моделью варианты наверх
    SelectRecognition(lexer, begin, token2selection, remove_incorrect_alts);

    /*
     #if defined LEM_DEBUGGING==1
     lem::mout->printf( "AFTER MODEL APPLICATION:\n" );

     leafs.clear();
     lexer.FetchEnds( begin, leafs, 100 );

     for( lem::Container::size_type i=0; i<leafs.size(); ++i )
      {
       const LexerTextPos * leaf = leafs[i];
       nodes.clear();
       leaf->Collect_Right2Left( begin, nodes );

       const int src_token_count=CastSizeToInt(nodes.size()-2);

       nodes2.clear();
       for( int j=CastSizeToInt(nodes.size())-1; j>=0; --j )
        {
         nodes2.push_back( nodes[j] );
        }

       for( lem::Container::size_type j=0; j<nodes2.size(); ++j )
        {
         const LexerTextPos * token = nodes2[j];
         token->GetWordform()->Print( *lem::mout, &dict.GetSynGram(), true  );
         lem::mout->eol();
        }
      }

     lem::mout->printf( "-----\n" );
     #endif
    */

#endif

    return;
}


void SequenceLabelerModel::SelectRecognition(BasicLexer & lexer, const LexerTextPos * token, const std::multimap< const LexerTextPos*, int > & token2selection, bool remove_incorrect_alts) const
{
#if defined SOL_CAA

    if (token->IsEnd())
        return;

    if (token->IsRealWord() && token->GetWordform()->VersionCount() > 1)
    {
        typedef std::multimap< const LexerTextPos*, int >::const_iterator IT;
        std::pair<IT, IT> pit = token2selection.equal_range(token);
        if (pit.first != token2selection.end())
        {
            std::set<int> selected_recognitions;
            for (IT it = pit.first; it != pit.second; ++it)
            {
                const int version_index = it->second;
                selected_recognitions.insert(version_index);
            }

            if (!selected_recognitions.empty())
            {
                lexer.FilterRecognitions(token, selected_recognitions, remove_incorrect_alts);
            }
        }
    }

    lem::MCollect<const LexerTextPos*> next;
    lexer.Fetch(token, next);
    for (lem::Container::size_type i = 0; i < next.size(); ++i)
    {
        SelectRecognition(lexer, next[i], token2selection, remove_incorrect_alts);
    }

#endif

    return;
}


void SequenceLabelerModel::SetParamsAfterLoad()
{
    BasicModel::SetParamsAfterLoad();

    EMIT_PAIRWISE_FEATURE = codebook->FindModelParam(L"EMIT_PAIRWISE_FEATURE", L"false").eqi(L"true");
    EMIT_TRIPLE_FEATURE = codebook->FindModelParam(L"EMIT_TRIPLE_FEATURE", L"false").eqi(L"true");
    EMIT_AA_FEATURE = codebook->FindModelParam(L"EMIT_AA_FEATURE", L"false").eqi(L"true");
    EMIT_AA_FOR_CONTEXT = codebook->FindModelParam(L"EMIT_AA_FOR_CONTEXT", L"false").eqi(L"true");
    EMIT_MORPH_TAGS = codebook->FindModelParam(L"EMIT_MORPH_TAGS", L"false").eqi(L"true");
    EMIT_POS_FOR_CONTEXT = codebook->FindModelParam(L"EMIT_POS_FOR_CONTEXT", L"false").eqi(L"true");
    EMIT_MORPH_FOR_CONTEXT = codebook->FindModelParam(L"EMIT_MORPH_FOR_CONTEXT", L"false").eqi(L"true");

    return;
}
