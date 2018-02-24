#pragma once

#include <map>
#include <lem/path.h>
#include <lem/integer.h>
#include <lem/containers.h>
#include <lem/solarix/tree_node.h>
#include <lem/process.h>
#include <lem/solarix/dictionary.h>
#include <crfsuite.h>


class ChunkerModel
{
private:
    lem::int32_t window;
    lem::int32_t shingle_len;
    bool emit_shingles;
    bool emit_morphtags;

    std::map<lem::UCString, int> shingle2index;

    lem::Process::CriticalSection crf_critsect;
    crfsuite_model_t *model;
    crfsuite_dictionary_t *attrs, *labels;
    crfsuite_tagger_t *tagger;

    void GetWordFeatures(Solarix::Dictionary & dict,
        const lem::MCollect<Solarix::Tree_Node*> & words,
        int iword,
        lem::MCollect<lem::CString> & str_features) const;

    void GetContextWordFeatures(Solarix::Dictionary & dict,
        const lem::MCollect<Solarix::Tree_Node*> & words,
        int word_index,
        int word_offset,
        lem::MCollect<lem::CString> & features) const;

public:
    ChunkerModel();
    ~ChunkerModel();
    void Load(const lem::Path &codebook_path, const lem::Path &model_path);

    std::vector<int> Apply(Solarix::Dictionary & dict, const lem::MCollect<Solarix::Tree_Node*> & words);

};
