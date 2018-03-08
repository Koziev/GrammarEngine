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

    virtual void Start();
    virtual void End();
    virtual void Flush();
    virtual void StartSentence(const lem::UFString & sentence_str, int paragraph_id);
    virtual void EndSentence();

    virtual void StartChunking();
    virtual void PrintChunking( int word_position, int chunk_label);
    virtual void EndChunking();

    virtual void StartTokens();
    virtual void EndTokens();

    virtual void StartToken();
    virtual void PrintToken(
        bool known_word,
        const wchar_t * word,
        const wchar_t * lemma,
        int position,
        const wchar_t * part_of_speech);
    virtual void EndToken();

    virtual void StartTags();
    virtual void PrintTag(int tag_counter, const wchar_t * tag_name, const wchar_t * tag_value);
    virtual void EndTags();

    virtual void PrintTreeRendering( const wchar_t * tree_rendering );
    virtual void StartSyntaxTree();
    virtual void EndSyntaxTree();
    virtual void PrintSyntaxNode(
        bool is_root,
        bool is_orphant,
        const wchar_t * word,
        int word_pos,
        const wchar_t * edge_name,
        int parent_index,
        const wchar_t * parent_word_str);

};


#endif

