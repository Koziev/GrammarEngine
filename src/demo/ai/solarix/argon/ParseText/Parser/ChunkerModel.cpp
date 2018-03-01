#include <lem/config.h>
#include <lem/streams.h>
#include <lem/conversions.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/WordEntry.h>
#include "ChunkerModel.h"

// 01.03.2018 добавлена критсекция на входе в Apply, так как CRFSuite tagger не многопоточен.


ChunkerModel::ChunkerModel() :
    window(-1000000), shingle_len(-1), emit_shingles(false), emit_morphtags(false),
    model(NULL), attrs(NULL), labels(NULL), tagger(NULL)
{}

ChunkerModel::~ChunkerModel()
{
}


static void load_utf8_string( lem::Stream & bin, lem::UCString & str )
{
    lem::uint32_t utf8_len=0;
    bin.read( &utf8_len, sizeof(utf8_len) );

    lem::uint8_t buffer[ lem::UCString::max_len*6+1 ];
    bin.read( buffer, utf8_len );
    buffer[utf8_len] = 0;
    lem::FString u( (const char*)buffer );
    str = lem::UCString(lem::from_utf8(u).c_str());

    return;
}


void ChunkerModel::Load(const lem::Path &codebook_path, const lem::Path &model_path)
{
    lem::BinaryReader codebook(codebook_path);

    lem::int32_t dummy;
    codebook.read(&dummy, sizeof(dummy));
    codebook.read(&window, sizeof(window));
    codebook.read(&shingle_len, sizeof(shingle_len));
    emit_shingles = codebook.read_bool();
    emit_morphtags = codebook.read_bool();

    lem::int32_t nb_shingles = -1;
    codebook.read(&nb_shingles, sizeof(nb_shingles));

    for (int i = 0; i < nb_shingles; ++i)
    {
        lem::UCString shingle;
        load_utf8_string(codebook, shingle);

        lem::int32_t index;
        codebook.read(&index, sizeof(index));

        shingle2index[shingle] = index;
    }

    // Грузим CRFSuite модель.
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


    return;
}


void ChunkerModel::GetContextWordFeatures(Solarix::Dictionary & dict,
    const lem::MCollect<Solarix::Tree_Node*> & words,
    int word_index,
    int word_offset,
    lem::MCollect<lem::CString> & features) const
{
    const Solarix::Tree_Node* word = words[word_index];

    if (emit_shingles)
    {
        // шинглы
        lem::UCString word2(L"\t");
        word2 += word->GetNode().GetName()->to_lower().c_str();
        word2 += L'\t';

        for (int i = 0; i < word2.length() - shingle_len+1; ++i)
        {
            lem::UCString shingle( word2.c_str()+i, word2.c_str()+i+shingle_len );
            if( shingle2index.find(shingle) != shingle2index.end() )
            {
             int index = shingle2index.find(shingle)->second;
             features.push_back( lem::format_str("shingle[%d]=%d", word_offset, index).c_str() );
            }
        }
    }

    if (emit_morphtags)
    {
        // морфологические фичи

        // Код части речи.
        const int ekey = word->GetNode().GetEntryKey();
        const Solarix::SG_Entry & e = dict.GetSynGram().GetEntry(ekey);
        const int id_class = e.GetClass();
        features.push_back(lem::format_str("class[%d]=%d", word_offset, id_class).c_str());

        // Морфологические тэги
        int nfeat = word->GetNode().GetnPair();
        for (int i = 0; i < nfeat; ++i)
        {
            int id_coord = word->GetNode().GetPair(i).GetCoord().GetIndex();
            int id_state = word->GetNode().GetPair(i).GetState();
            features.push_back(lem::format_str("%d[%d]=%d", id_coord, word_offset, id_state).c_str());
        }

        // Признаки первое/последнее слово
        if (word_index == 1)
        {
            features.push_back(lem::format_str("start[%d]", word_offset).c_str());
        }
        
        if (word_index == words.size()-2)
        {
            features.push_back(lem::format_str("end[%d]", word_offset).c_str());
        }

    }

    return;
}


void ChunkerModel::GetWordFeatures(Solarix::Dictionary & dict,
    const lem::MCollect<Solarix::Tree_Node*> & words,
    int focus_index,
    lem::MCollect<lem::CString> & features) const
{
    for (int offset = -window; offset <= window; ++offset)
    {
        int word_index = focus_index + offset;
        if (word_index >= 1 && word_index < words.size()-1)
        {
            GetContextWordFeatures( dict, words, word_index, offset, features );
        }
    }

    return;
}


std::vector<int> ChunkerModel::Apply(Solarix::Dictionary & dict, const lem::MCollect<Solarix::Tree_Node*> & words)
{
    // CRFSuite tagger API не работает многопоточно, поэтому критсекция.
    lem::Process::CritSecLocker cs_locker(&crf_critsect); // #9

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
    for (int iword = 1; iword < CastSizeToInt(words.size())-1; ++iword)
    {
        str_features.clear();

        // признаки для текущего слова и его контекста
        GetWordFeatures(dict, words, iword, str_features);
        

        
        #if LEM_DEBUGGING==1
        lem::mout->printf( "CRF token #%d word=%us tags==>", iword, words[iword]->GetNode().GetName()->c_str() );
        for( int q=0; q<str_features.size(); ++q )
        {
        lem::mout->printf( " %s", str_features[q].c_str() );
        }
        lem::mout->eol();
        #endif
        

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

    std::vector<int> res_labels;
    res_labels.resize(words.size());

    for (int i = 0; i < inst.num_items; ++i)
    {
        const char *label = NULL;
        labels->to_string(labels, output[i], &label);
        //fprintf(fpo, "%s", label);
        int id = UNKNOWN;
        if (lem::is_int(label))
            id = lem::to_int(label);

        res_labels[i] = id;

        labels->free(labels, label);
    }

    free(output);
    crfsuite_instance_finish(&inst);


    return res_labels;
}

