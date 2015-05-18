/*
**  DeSR
**  src/Corpus.h
** ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
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

#ifndef DeSR_Corpus_H
#define DeSR_Corpus_H

// local
#include "TokenAttributes.h"
#include "Language.h"

// library
//#include "include/error.h"

// standard
#include <map>

namespace Tanl {

class Sentence;
class SentenceReader;

/**
 *	@ingroup parser
 *
 *	Describes the fields in each token in a corpus.
 */
struct TokenField
{
  /** What use of the field in training */
  enum Use {
    input,			// default
    output,
    echo,
    ignore
  };

  /** Type of value */
  enum Value {
    string,			// default
    integer
  };

  enum Role {
    none,			// default
    form,
    head,
    deprel,
    predicate,
    morph,
    pos
  };

  TokenField() :
    use(input),
    value(string),
    role(none),
    default_("_")
  { }

  std::string	name;
  Use		use;
  Value		value;
  Role		role;
  std::string	default_;	///< default value for the field
  std::string	link;		///< if present, names the link for which it provides the head ID
  std::string	label;		///< if present, names the link for which it provides the label
};

/**
 * Fields are listed in the order in which they appear in the CorpusFormat file.
 */
typedef std::vector<TokenField> TokenFields;

/**
 *	@ingroup parser
 *
 *	Representatation of Corpus data format
 */
struct CorpusFormat
{
  std::string		name;
  TokenFields		tokenFields; ///< properties of fields of tokens.
  AttributeIndex	index;	///< associates an index to field names
};

/**
 *	@ingroup parser
 */
class CorpusFormatError : public IXE::RuntimeError
{
public:
  CorpusFormatError(std::string const& msg) : IXE::RuntimeError(msg) {}
};

/**
 *	@ingroup parser
 *
 *	Represents common aspects of a Corpus.
 */
class Corpus
{
 public:
  Language const&	language;
  AttributeIndex	index;	     ///< associates an index to field names
  TokenFields		tokenFields; ///< describes properties of fields in tokens

  /**
   *	@param lang the default language for sentences in the corpus.
   */
  Corpus(Language const& lang) :
    language(lang)
  { }

  /**
   *	Create from specified CorpusFormat.
   *	@param lang the default language for sentences in the corpus.
   */
  Corpus(Language const& lang, CorpusFormat& format) :
    language(lang),
    tokenFields(format.tokenFields),
    index(format.index)
  { }

  /**
   *	Read the corpus format from file @c formatFile.
   *	@param lang the default language for sentences in the corpus.
   */
  Corpus(Language const& lang, char const* formatFile);

  Corpus() : language(Language("en")) { } // for Java.

  /**
   *	Factory pattern for creating a Corpus based on the provided format.
   *	@param lang the default language for sentences in the corpus.
   *	@param inputFormat is either the name of a builtin format
   *	(either CoNLL, conll08, DgaXML, Text, TokenizedText) or the name of
   *	a file containing the specifications of the format.
   */
  static Corpus* create(Language const& language, char const* inputFormat);

  static Corpus* create(char const* language, char const* inputFormat);

  virtual ~Corpus() {}

  /**
   *	Read the corpus format from file @c formatFile.
   *	@return created format or 0 if reading failed.
   */
  static CorpusFormat*		parseFormat(char const* formatFile);

  /**	@return the index (into the vector of values for tokens) of the
     	attribute with the given @param name. */
  AttributeId		attributeId(const char* name) {
    return index.insert(name);
  }

  /**
   *	@return an appropriate reader for reading sentences of the corpus from
   *	the given stream @c is.
   */
  virtual SentenceReader* sentenceReader(std::istream* is);

  /**
   *	Print the sentence in the standard format for the corpus.
   */
  virtual void		print(std::ostream& os, Sentence const& sent) const;
  virtual std::string	toString(Sentence const& sent) const;

protected:
  static CorpusFormat*	parseFormat(std::istream& is);

};

/**
 *	@ingroup parser
 */
struct ConllXCorpus : public Corpus
{

  ConllXCorpus(Language const& lang);

  SentenceReader*	sentenceReader(std::istream* is);

  void			print(std::ostream& os, Sentence const& sent) const;
};

/**
 *	@ingroup parser
 */
struct Conll08Corpus : public Corpus
{
  /**
   *	Create from specified CorpusFormat.
   *	@param lang the default language for sentences in the corpus.
   */
  Conll08Corpus(Language const& lang, CorpusFormat& format) :
    Corpus(lang, format)
  { }

  void			print(std::ostream& os, Sentence const& sent) const;
};

/**
 *	@ingroup parser
 */
struct DgaCorpus : public Corpus
{

  DgaCorpus(Language const& lang);

  SentenceReader*	sentenceReader(std::istream* is);

  void			print(std::ostream& os, Sentence const& sent) const;
};

/**
 *	@ingroup parser
 *
 *	Used to convert a Conll08 corpus replacing dependency links with the
 *	first non relexive arg link.
 */
struct CombCorpus : public Corpus
{
  CombCorpus(Language const& lang, char const* formatFile) :
    Corpus(lang, formatFile)
  { }

  void			print(std::ostream& os, Sentence const& sent) const;
};

/**
 *	@ingroup parser
 *
 *	Plain text corpus.
 */
struct TextCorpus : public Corpus
{
  TextCorpus(Language const& lang) :
    Corpus(lang)
  {}

  SentenceReader* sentenceReader(std::istream* is);
};

/**
 *	@ingroup parser
 *
 *	Corpus made of tokens.
 */
struct TokenizedTextCorpus : public Corpus
{
  TokenizedTextCorpus(Language const& lang) :
    Corpus(lang)
  {}

  SentenceReader* sentenceReader(std::istream* is);
};

/////////// Mechanism for self registering corpora ///////////////////

// Doesn't compile on VS2008 SP1 (_MSC_VER = 1500)
//typedef Corpus* CorpusFactory(Language const& lang, CorpusFormat* format = 0);
typedef Corpus* CorpusFactory(Language const& lang, CorpusFormat* format);

/**
 *	@ingroup parser
 *
 *	Associates a Corpus constructor to a corpus name.
 */
struct CorpusMap
{
public:
  CorpusMap(char const* type, CorpusFactory* rf);

  static CorpusFactory*		get(char const* type);

private:
  static std::map<char const*, CorpusFactory*>& get();
};

#define REGISTER_CORPUS(type, factory) static CorpusMap __dummy ## type(#type, factory)

} // namespace Tanl

#endif // DeSR_Corpus_H
