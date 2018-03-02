#include "ParsingResults_API.h"


ParsingResults_API::ParsingResults_API()
{
    sentence_being_created = NULL;
    token_being_created = NULL;
}

ParsingResults_API::~ParsingResults_API()
{
    delete sentence_being_created;
    sentence_being_created = NULL;
}

void ParsingResults_API::Start()
{
}

void ParsingResults_API::End()
{
}

void ParsingResults_API::Flush() {}

void ParsingResults_API::StartSentence(const lem::UFString & sentence_str, int paragraph_id)
{
    assert(sentence_being_created == NULL);
    assert(token_being_created == NULL);
    sentence_being_created = new ParsingResult_Sentence();
}

void ParsingResults_API::EndSentence()
{
    assert(sentence_being_created != NULL);
    assert(token_being_created == NULL);
    sentences.push_back(sentence_being_created);
    sentence_being_created = NULL;
}


void ParsingResults_API::NotImplementedMethod()
{
    throw std::exception("not implemented method in ParsingResults_API");
}

void ParsingResults_API::StartChunking()
{
    NotImplementedMethod();
}

void ParsingResults_API::PrintChunking(int word_position, int chunk_label)
{
    NotImplementedMethod();
}

void ParsingResults_API::EndChunking()
{
    NotImplementedMethod();
}


void ParsingResults_API::StartTokens() {}
void ParsingResults_API::EndTokens() {}

void ParsingResults_API::StartToken()
{
    assert(token_being_created == NULL);
    token_being_created = new ParsingResult_Token();
}

void ParsingResults_API::PrintToken(
    bool known_word,
    const wchar_t * word,
    const wchar_t * lemma,
    int position,
    const wchar_t * part_of_speech)
{
    assert(token_being_created != NULL);

    token_being_created->word = word;
    token_being_created->lemma = lemma;
    token_being_created->position = position;
    token_being_created->part_of_speech = part_of_speech;
}

void ParsingResults_API::EndToken()
{
    assert(token_being_created != NULL);
    assert(sentence_being_created != NULL);
    sentence_being_created->AddToken(token_being_created);
    token_being_created = NULL;
}

void ParsingResults_API::StartTags()
{}


void ParsingResults_API::PrintTag(int tag_counter, const wchar_t * tag_name, const wchar_t * tag_value)
{
    assert(token_being_created != NULL);
    token_being_created->AddTag(tag_name, tag_value);
}

void ParsingResults_API::EndTags()
{}

void ParsingResults_API::PrintTreeRendering(const wchar_t * tree_rendering)
{
    NotImplementedMethod();
}

void ParsingResults_API::StartSyntaxTree()
{
    NotImplementedMethod();
}

void ParsingResults_API::EndSyntaxTree()
{
    NotImplementedMethod();
}

void ParsingResults_API::PrintSyntaxNode(
    bool is_root,
    bool is_orphant,
    const wchar_t * word,
    int word_pos,
    const wchar_t * edge_name,
    int parent_index,
    const wchar_t * parent_word_str)
{
    NotImplementedMethod();
}

