// libdesr.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <src\Parser.h>
#include <src\Corpus.h>

#include <string>

#define EXPORT(RetType) __declspec(dllexport) RetType __stdcall

using namespace Parser;
using namespace std;

extern void Register_MLP_Parser();

struct DesrEngine
{
 ParserConfig config;
 Language const * language;
 Corpus* corpus;
 Corpus* outCorpus;
 const char * inputFormat;
 const char * outputFormat;
 int beam;
 ::Parser::Parser* parser;

 DesrEngine()
 {
  inputFormat = "CoNLL"; // CoNLL, CoNLL08, DgaXML
  outputFormat = "CoNLL"; // CoNLL, DGAXML
  beam=-1;
 }


 void Init( const char * configFile, const char * modelFile, int BeamSize )
 {
  // ѕод Linux статическа€ инициализаци€ этого справочника не работает,
  // поэтому делаем это €вно здесь.
//  REGISTER_PARSER(MLP, MlpParserFactory);
//  REGISTER_PARSER(AP, ApParserFactory);
//  REGISTER_PARSER(ME, MeParserFactory);
//  REGISTER_PARSER(MSVM, MultiSvmParserFactory);
//  REGISTER_PARSER(SVM, SvmParserFactory);
  Register_MLP_Parser();

  beam = BeamSize;

  // First, parse the config. file (if any); then override variables
  // with options specified on the command line.
  config.load(configFile);

  // in parse mode certain parameters are fixed and stored in the modelFile
  // read parameters from modelFile
  ifstream ifs(modelFile);
  config.load(ifs);

  language = Language::get(config.lang->c_str());

  // Create the Corpus for the requested inputFormat and its
  // associated SentenceReader.
  corpus = Corpus::create(*language, inputFormat);
  outCorpus = Corpus::create(*language, outputFormat);

  parser = ::Parser::Parser::create(modelFile);
  if( beam > 0)
    parser->config.beam = beam;

  return;
 }

 char * Parse( const char * src )
 {
  std::istringstream * is = new std::istringstream(std::string(src));
  SentenceReader * sentenceReader = corpus->sentenceReader(is);

  std::ostringstream out_stream;
  parser->parse( sentenceReader, outCorpus, out_stream );

  try
  {
   parser->parse(sentenceReader, outCorpus);
  }
  catch (IXE::Error& e)
  {
   cerr << "Error: " << e.message() << endl;
  }
  catch (exception& e)
  {
   cerr << "Error: " << e.what() << endl;
  }

  std::string str = out_stream.str();
     
  char * res_str = new char[ str.length()+1 ];
  strcpy( res_str, str.c_str() );

  delete is;
  delete sentenceReader;

  return res_str;
 }

 ~DesrEngine()
 {
  delete parser;
  delete corpus;
  delete outCorpus;
 }
};





EXPORT(void*) DesrInit( int BeamSize, const char *ConfigFile, const char * ModelFile )
{
 DesrEngine * engine = new DesrEngine();
 engine->Init( ConfigFile, ModelFile, BeamSize );
 return engine;
}


EXPORT(char*) DesrTag( void * engine_ptr, const char * src )
{
 DesrEngine * engine = (DesrEngine*)engine_ptr;

 char * res_str = engine->Parse( src );

 return res_str;
}

EXPORT(int) DesrFreeResult( void * engine_ptr, char * result_str )
{
 delete[] result_str;
 return 0;
}


EXPORT(int) DesrDeleteEngine( void * engine_ptr )
{
 DesrEngine * engine = (DesrEngine*)engine_ptr;
 delete engine;
 return 0;
}
