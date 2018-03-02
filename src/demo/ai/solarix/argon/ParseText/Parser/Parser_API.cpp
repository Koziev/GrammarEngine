#include "Parser_API.h"


Parser_API::Parser_API()
{
}

Parser_API::Parser_API(const Parser_API &)
{
    throw std::exception("copying if Parser_API is not allowed");
}

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


ParsingResults_API * Parser_API::TagSentence(const wchar_t * sentence, bool emit_morph)
{
    ParsingResults_API * results = new ParsingResults_API();
    ParseString(sentence, 0, emit_morph, false, *results);
    return results;
}


