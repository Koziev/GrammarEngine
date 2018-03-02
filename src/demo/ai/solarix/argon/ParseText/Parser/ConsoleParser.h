#pragma once
#if !defined ConsoleParser__H
#define ConsoleParser__H

#include "ParserEngineBase.h"

class ConsoleParser : public ParserEngineBase
{
public:
    ConsoleParser();

    int Run( int argc, char * argv[] );
};

#endif
