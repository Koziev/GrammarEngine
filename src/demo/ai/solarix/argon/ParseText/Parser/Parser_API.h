#pragma once
#if !defined Parser_API__H
#define Parser_API__H

#include "ParsingResults_API.h"
#include "ParserEngineBase.h"

class Parser_API : public ParserEngineBase
{
public:
    Parser_API();
    Parser_API( const Parser_API & );
    virtual ~Parser_API();

    void Load( const wchar_t * dictionary_path );
    ParsingResults_API * TagSentence( const wchar_t * sentence, bool emit_morph );
};

#endif

