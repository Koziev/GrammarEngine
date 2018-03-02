#pragma once
#if !defined ParsingResultsFormatter__H
#define ParsingResultsFormatter__H

#include <lem/ufstring.h>

class ParsingResultFormatter
{
public:
    virtual ~ParsingResultFormatter() {}

    virtual void Start() = 0;
    virtual void End() = 0;
    virtual void Flush() = 0;
    virtual void StartSentence(const lem::UFString & sentence_str, int paragraph_id) = 0;
    virtual void EndSentence() = 0;

    virtual void StartChunking() = 0;
    virtual void PrintChunking(int word_position, int chunk_label) = 0;
    virtual void EndChunking() = 0;

    virtual void StartTokens() = 0;
    virtual void EndTokens() = 0;

    virtual void StartToken() = 0;
    virtual void PrintToken(
        bool known_word,
        const wchar_t * word,
        const wchar_t * lemma,
        int position,
        const wchar_t * part_of_speech) = 0;
    virtual void EndToken() = 0;

    virtual void StartTags() = 0;
    virtual void PrintTag(int tag_counter, const wchar_t * tag_name, const wchar_t * tag_value) = 0;
    virtual void EndTags() = 0;

    virtual void PrintTreeRendering(const wchar_t * tree_rendering) = 0;
    virtual void StartSyntaxTree() = 0;
    virtual void EndSyntaxTree() = 0;
    virtual void PrintSyntaxNode(
        bool is_root,
        bool is_orphant,
        const wchar_t * word,
        int word_pos,
        const wchar_t * edge_name,
        int parent_index,
        const wchar_t * parent_word_str)=0;


};


#endif
