#include "Parser_API.h"


Parser_API::Parser_API(int lemmatizer_type, int parser_type)
{
    this->lemmatizer_type = lemmatizer_type;
    this->parser_type = parser_type;
}

/*
Parser_API::Parser_API(const Parser_API &)
{
    throw std::exception("copying if Parser_API is not allowed");
}
*/

Parser_API::~Parser_API()
{
}


void Parser_API::Load(const wchar_t * dictionary_path)
{
    lem::Path dict_path(dictionary_path);
    dict_path = dict_path.GetAbsolutePath();
    LoadDictionary(dict_path);
    LoadModels(dict_path);
}


ParsingResults_API * Parser_API::TagSentence(const wchar_t * sentence, bool emit_morph, bool allow_fuzzy_recognition)
{
    ParsingResults_API * results = new ParsingResults_API();
    ParseString(sentence, 0, emit_morph, allow_fuzzy_recognition, false, *results);
    return results;
}


