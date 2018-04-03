#pragma once
#if !defined ParsingResults_XMLStream__H
#define ParsingResults_XMLStream__H

#include <lem/oformatter.h>
#include "ParsingResultFormatter.h"

class ParsingResults_XMLStream : public ParsingResultFormatter
{
private:
    lem::OFormatter & out_stream;

protected:
    lem::UFString EncodeStrXml(const wchar_t * src) const;

public:
    ParsingResults_XMLStream(lem::OFormatter & stream);

    virtual void Start() override;
    virtual void End() override;
    virtual void Flush() override;
    virtual void StartSentence(const lem::UFString & sentence_str, int paragraph_id) override;
    virtual void EndSentence() override;

    virtual void StartChunking() override;
    virtual void PrintChunking( int word_position, int chunk_label) override;
    virtual void EndChunking() override;

    virtual void StartTokens() override;
    virtual void EndTokens() override;

    virtual void StartToken() override;
    virtual void PrintToken(
        bool known_word,
        const wchar_t * word,
        const wchar_t * lemma,
        int position,
        const wchar_t * part_of_speech) override;
    virtual void EndToken() override;

    virtual void StartTags() override;
    virtual void PrintTag(int tag_counter, const wchar_t * tag_name, const wchar_t * tag_value) override;
    virtual void EndTags() override;

    virtual void PrintTreeRendering( const wchar_t * tree_rendering ) override;
    virtual void StartSyntaxTree() override;
    virtual void EndSyntaxTree() override;
    virtual void PrintSyntaxNode(
        bool is_root,
        bool is_orphant,
        const wchar_t * word,
        int word_pos,
        const wchar_t * edge_name,
        int parent_index,
        const wchar_t * parent_word_str) override;

};


#endif

