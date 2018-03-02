#pragma once
#if !defined ParserEngine__H
#define ParserEngine__H

#include <lem/path.h>
#include <lem/ucstring.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include <lem/solarix/casing_coder.h>
#include <lem/solarix/variator.h>
#include "Lemmatizer2.h"
#include "ChunkerModel.h"
#include "ParsingResultFormatter.h"

class ParserEngineBase
{
 protected:
  int beam_size;
  bool verbose;
  bool allow_primary_fuzzy_word_recog;

  int tagger_type;
  int parser_type;
  int lemmatizer_type;

  lem::UCString language_name; // "Russian" or "English"
  int language_id;

  int word_count;
  int sent_count;

  // DeSR dependency parser model data and properties
  Solarix::Dictionary dict;
  Solarix::Load_Options opt;
  Solarix::ModelCodeBook desr_codebook;
  void * hDESR;

  // Lemmatizer model
  Lemmatizer2 lemmatizer2;
  Solarix::WrittenTextAnalysisSession * current_analysis;
  Solarix::CasingCoder * casing_coder;

  // Chunker model
  ChunkerModel chunker_model;

  void DumpMorphTokens( const Solarix::Variator & tagging, bool emit_morph, ParsingResultFormatter & out_stream );
  void AssembleEdges( const Solarix::Tree_Node & node, std::map<int, std::pair<int,int> > & child_to_parent, std::map<int,lem::UCString> & node2word );

 public:
  ParserEngineBase();
  virtual ~ParserEngineBase();

  void LoadDictionary(const lem::Path & dict_path);
  void LoadModels(const lem::Path & dict_path);

  void ParseString( const lem::UFString & sentence,
      int paragraph_id,
      bool emit_morph,
      bool render_tree,
      ParsingResultFormatter & out_stream );
};

#endif
