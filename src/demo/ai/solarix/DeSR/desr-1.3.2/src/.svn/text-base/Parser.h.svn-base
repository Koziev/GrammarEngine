/*
**  DeSR
**  src/Parser.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of DeSR.
**
**  DeSR is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  DeSR is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#ifndef DeSR_Parser_H
#define DeSR_Parser_H

// local
#include "State.h"
#include "IPipe.h"
#include "RefCountable.h"
#include "SentenceReader.h"
#include "conf_Replacements.h"

// IXE library
#include "conf/conf_bool.h"
#include "conf/conf_int.h"
#include "conf/conf_string.h"

// Tanl
using Tanl::Corpus;
using Tanl::Enumerator;
using Tanl::IPipe;
using Tanl::Language;
using Tanl::RefCountable;
using Tanl::Sentence;
using Tanl::SentenceReader;
using Tanl::Token;
using Tanl::TreeToken;

/**
 * 	@defgroup parser Dependency Parser
 */

namespace Parser {

/**
 *	Generic Parser parameters.
 *	Each parser will add its own.
 *
 *	Configuration Protocol.
 *
 * A Configuration consists in:
 * - a set of conf<T> variables
 * - a map of names to those variables
 *
 * conf<T> objects store a value of type T and have a name that can be used to
 * assign a value to the variable read from a file.
 * Values are read by calling method:
 *	conf<T>::parseValue(char*& line)
 * @see conf.h
 *
 * A global map exists in Configuration::variables(), that stores all
 * parameters defined at global scope.
 * For example, one can define:
 *
 * conf<int>	verbose("Verbosity", 0);
 *
 * which creates a parameter named "Verbosity" to set the value of verbose to
 * a value from the configuration file.
 * Method Configuration::serialize(ostream&) is used to dump them in the same
 * input format.
 *
 * Class @c Parser has a member variable @c config that contains a @c
 * ParserConfig, a class that specializes @c Configuration, for storing
 * generic parse parameters, e.g. "Language".
 *
 * Class Parser has also a member variable @c params, that is referenced as
 * @c config.params (passed to @c ParserConfig constructor).
 *
 * Specific parsers further specialize ParserConfig, adding their own
 * parameters, e.g. MlpConfig.
 * Since MlpConfig inherits @c params, all parameters will be listed there,
 * so that they can be saved by a single call to Configuration::serialize().
 *
 */
struct ParserConfig : public FeatureConfig
{
  ParserConfig(IXE::Configuration::Params& params = IXE::Configuration::variables());

  void		writeHeader(std::ostream& os);

  IXE::conf<std::string> algorithm;
  IXE::conf<std::string> lang;
  IXE::conf<int>	 beam;	    ///< beam size
  IXE::conf<IXE::Replacements> normLemma; ///< patterns for lemma normalization
  /** Drop features which occur less than this number of times. */
  IXE::conf<int>	 featureCutoff;
  /** Control output */
  IXE::conf<bool>	 verbose;
  IXE::conf<bool>	 ShowActions;
  IXE::conf<bool>	 ShowPerplexity;
  IXE::conf<bool>	 RightToLeft;

};

extern bool showTreelets;

struct ParserPipe;

/**
 *	@ingroup parser
 *
 *	Base class for parsers.
 */
class Parser : public IPipe<Sentence*, Sentence*>,
	       public virtual RefCountable
{
public:

  Parser(WordIndex& predIndex, ParserConfig& config) :
    predIndex(predIndex),
    config(config),
    info(config)
  { }

  virtual ~Parser() { }

  /**
   *	Create a Parser based data in file @c modelFile, when training or in @c configFile when parsing.
   *
   *	When training @c modelFile must be 0 (since it will be created by
   *	train).
   *	When parsing, @c configFile must be 0 (since configuration is obtained
   *	from model).
   */
  static Parser*	create(char const* modelFile = 0, char const* configFile = 0);

  /**
   *	Train statistical model using sentences obtained through a
   *	@c sentenceReader, and save the generated model to @c modelFile.
   */
  virtual void		train(SentenceReader* sentenceReader,
			      char const* modelFile) {}
  /**
   *	Parse the given Sentence @c sentence.
   *	@return a newly allocated @see Sentence.
   */
  virtual Sentence*	parse(Sentence* sentence) { return 0; }

  /**
   *	Parse all sentences extracted by @c sentenceReader, sending output to
   *	@c os.
   */
  virtual void		parse(SentenceReader* sentenceReader,
			      Corpus* outCorpus,
			      std::ostream& os = std::cout);

  /**
   *	Produce a revision of a document parses, using either a model
   *	or an action file.
   *	If an @c actionFile is provided, it must contain a list of actions,
   *	one per line, to apply to the parse trees, otherwise
   *	the actions to perform revisions are determined using the model.
   */
  virtual void		revise(SentenceReader* sentenceReader,
			       char const* actionFile = 0) { }

  /**
   *	Collect sentences and replace unfrequent token attributes with UNKNOWN.
   */
  std::deque<Sentence*>	collectSentences(Enumerator<Sentence*>* sentenceReader);

  /**	Print accuracy estimates. */
  virtual void		showEval(int tokenCount, int las, int uas,
				 int sentCount);

  /**	Write model header to stream @param os*/
  void			writeHeader(std::ostream& os);

  /**
   *	IPipe interface.
   *	@return an Enumerator connected in pipeline to @param tve.
   */
  Enumerator<Sentence*>* pipe(Enumerator<std::vector<Token*>*>& tve);

# ifdef HAVE_PYTHON
  /**
   *	Create a pipe pulling from a Python iterator @a pit.
   *	@return an Enumerator connected in pipeline to @param pit.
   */
  Enumerator<Sentence*>* pipe(PyObject* pit);

# endif

  /**
   *	Alternative pipeline interface, that allows connecting directly to
   *	a SentenceReader.
   */
  Enumerator<Sentence*>* pipe(Enumerator<Sentence*>& tce);

  /**
   *	Preprocess sentence, e.g. normalize tokens.
   */
  virtual void		preprocess(Sentence* sentence);

  /**
   * Return a string of process statistics:
   *  time: user+sys elapsed, realtime elapsed, CPU usage, memory usage
  */
  static std::string	procStat();

  WordIndex&		predIndex;
  GlobalInfo		info;
  ParserConfig&		config;	///< configuration parameters
  IXE::Configuration::Params	params; ///< params in config
};

/**
 * A pipe that parses sentences from a stream.
 */
struct ParserPipe : public Enumerator<Sentence*>
{
public:
  ParserPipe(Parser& parser, Enumerator<std::vector<Token*>*>& tve);

  bool		MoveNext();

  Sentence*	Current();

  /** This is to be called by SWIG when releasing the object.
   *  Release the parser object and then call destructor.
   */
  void		Dispose();

private:
  Parser&	parser;
  Enumerator<std::vector<Token*>*>& tve;
  Language const* language;
};

/**
 * A pipe that parses sentences from a stream of sentences.
 */
struct ParserSentPipe : public Enumerator<Sentence*>
{
public:
  ParserSentPipe(Parser& parser, Enumerator<Sentence*>& tve);

  bool		MoveNext();

  Sentence*	Current();

  /** This is to be called by SWIG when releasing the object.
   *  Release the parser object and then call destructor.
   */
  void		Dispose();

private:
  Parser&	parser;
  Enumerator<Sentence*>& tve;
};

/////////// Mechanism for self registering parsers ///////////////////

typedef Parser* ParserFactory(char const*);

/**
 *	Associates a Parser constructor to an algorithm name
 */
struct ParserMap
{
public:
  ParserMap(char const* type, ParserFactory* pf)
  {
    get()[type] = pf;
  }

  static ParserFactory*		get(char const* type);

private:
  static std::map<char const*, ParserFactory*>& get();
};

#define REGISTER_PARSER(type, factory) static ParserMap __dummy ## type(#type, factory)

} // namespace Parser

#endif // DeSR_Parser_H
