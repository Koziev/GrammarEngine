#include <lem/startup.h>
#include "ParserEngineBase.h"



int main( int argc, char *argv[] )
{
 lem::LemInit initer;

 ParserEngineBase parser_engine;
 parser_engine.Run( argc, argv );
 
 return 0;
}
