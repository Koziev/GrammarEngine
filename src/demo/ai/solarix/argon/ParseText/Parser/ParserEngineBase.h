#if !defined ParserEngine__H
#define ParserEngine__H

#include <lem/path.h>
#include <lem/ucstring.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include <lem/solarix/casing_coder.h>
#include "Lemmatizer2.h"
#include "ChunkerModel.h"

class ParserEngineBase
{
 protected:
  lem::Path dict_path;
  lem::Path input_path;
  bool input_is_joblist; // если входной файл содержит список входных файлов и файлов результата (пакетный режим)
  lem::Path out_path;
  int beam_size;
  bool verbose;
  bool eol;
  bool render_tree;
  bool emit_morph;
  int start_index;
  int max_count;
  bool httpd;
  lem::FString http_url;
  int http_port;
  bool allow_primary_fuzzy_word_recog;

  int tagger_type;
  int parser_type;
  int lemmatizer_type;
  lem::UCString language_name;

  // DeSR dependency parser data and properties
  Solarix::Dictionary dict;
  Solarix::Load_Options opt;
  Solarix::ModelCodeBook desr_codebook;
  void * hDESR;
  int language_id;

  // Lemmatizer model
  Lemmatizer2 lemmatizer2;
  Solarix::WrittenTextAnalysisSession * current_analysis;
  Solarix::CasingCoder * casing_coder;

  // Chunker model
  ChunkerModel chunker_model;

  int word_count;
  int sent_count;

  void DumpMorphTokens( const Solarix::Variator & tagging, bool emit_morph, lem::OFormatter & out_stream );
  void AssembleEdges( const Solarix::Tree_Node & node, std::map<int, std::pair<int,int> > & child_to_parent, std::map<int,lem::UCString> & node2word );

 public:
  ParserEngineBase();
  virtual ~ParserEngineBase();
  int Run( int argc, char * argv[] );

  void ParseString( const lem::UFString & sentence, int paragraph_id, lem::OFormatter * out_stream );
};

#endif
