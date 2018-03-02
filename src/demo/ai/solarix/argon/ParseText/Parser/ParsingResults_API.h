#pragma once
#if !defined ParsingResults_API__H
#define ParsingResults_API__H

#include <string>
#include <boost/ptr_container/ptr_vector.hpp>
#include <lem/noncopyable.h>
#include <lem/oformatter.h>
#include "ParsingResultFormatter.h"


struct ParsingResult_Tag : lem::NonCopyable
{
    std::wstring tag_name;
    std::wstring tag_value;

    ParsingResult_Tag(const wchar_t * name, const wchar_t * value)
        :tag_name(name), tag_value(value)
    {}
};

struct ParsingResult_Token : lem::NonCopyable
{
    int position;
    std::wstring word;
    std::wstring lemma;
    std::wstring part_of_speech;
    boost::ptr_vector<ParsingResult_Tag> tags;

    void AddTag(const wchar_t * tag_name, const wchar_t * tag_value)
    {
        tags.push_back(new ParsingResult_Tag(tag_name, tag_value));
    }
};


struct ParsingResult_Sentence
{
    boost::ptr_vector<ParsingResult_Token> tokens;

    void AddToken(ParsingResult_Token * token) { tokens.push_back(token); }
};


class ParsingResults_API : public ParsingResultFormatter
{
private:
    boost::ptr_vector<ParsingResult_Sentence> sentences;
    ParsingResult_Sentence * sentence_being_created;
    ParsingResult_Token * token_being_created;

    void NotImplementedMethod();

public:
    ParsingResults_API();
    virtual ~ParsingResults_API();

    const ParsingResult_Sentence & GetSentence( int index=0 ) const { return sentences[index]; }

    virtual void Start();
    virtual void End();
    virtual void Flush();
    virtual void StartSentence(const lem::UFString & sentence_str, int paragraph_id);
    virtual void EndSentence();

    virtual void StartChunking();
    virtual void PrintChunking(int word_position, int chunk_label);
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

    virtual void PrintTreeRendering(const wchar_t * tree_rendering);
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


