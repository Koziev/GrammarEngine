/*
**  DeSR
**  src/SentenceReader.h
** ----------------------------------------------------------------------
**  Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef DeSR_SentenceReader_H
#define DeSR_SentenceReader_H

// library
#include "text/RegExp.h"
#include "text/XmlReader.h"

// standard
#include <istream>
#include <deque>

// local
#include "PosTagger.h"
#include "Sentence.h"
#include "Enumerator.h"

namespace Tanl {

class Corpus;

/**
 *	@ingroup parser
 */
class SentenceReader : public Enumerator<Sentence*>
{
public:

  SentenceReader() { }

  /** 
   *	Creates a new @c SentenceReader. 
   *	@param is	the stream containing the annotated sentences.
   *	@param corpus Corpus to which the sentences belong.
   */
  SentenceReader(std::istream* is, Corpus* corpus);

  /// ------------------------------------------------------------
  /// Enumerator<Sentence*>

  /** @return true if there is another sentence available */
  virtual bool		MoveNext();

  /** @Return the next sentence from the stream */
  virtual Sentence*	Current();

  /**	Restart */
  virtual void		Reset() {}

  /// ------------------------------------------------------------

  virtual ~SentenceReader() {}

  Corpus*	corpus;

protected:
  Sentence*		sentence; ///< the sentence read
  std::istream*		is;	///< stream where to read from
};

/**
 *	@ingroup parser
 *
 *	Reader of sentences in CoNLL format: one token per line,
 *	attributes tab separated.
 */
class ConllXSentenceReader : public SentenceReader
{
public:

  /** 
   *	Creates a new @c SentenceReader. 
   *	@param is	the stream containing the annotated sentences.
   *	@param corpus Corpus to which the sentences belong.
   */
  ConllXSentenceReader(std::istream* is, Corpus* corpus);

  /** Return true if there is another sentence available */
  bool		MoveNext();
};

/**
 *	@ingroup parser
 * 
 *	Read a corpus and iterate over it returning one sentence at time 
 */
class DgaSentenceReader : public SentenceReader
{
 public:

  /** 
   *	Creates a new @c DgaSentenceReader. 
   *	@param is	the sream containing the annotated sentences.
   */
  DgaSentenceReader(std::istream* is, Corpus* corpus);

  /** Return true if there is another sentence available */
  bool		MoveNext();

 private:
  Tanl::XML::XmlReader	reader;
};

/**
 *	@ingroup parser
 *
 *	Read a text split into space-separated tokens, one sentence per line,
 *	and iterate over it returning one sentence at time.
 */
class TokenSentenceReader : public SentenceReader
{
 public:

  /** 
   *	Creates a new @c TokenSentenceReader. 
   *	@param filename	the file containing the annotated sentences
   */
  TokenSentenceReader(std::istream* is, Corpus* corpus = 0);

  /** Return true if there is another sentence available */
  bool		MoveNext();

 private:
  static Tanl::Text::RegExp::Pattern reTok;

# ifdef STEMMER
  sb_stemmer* stemmer;
# endif
};

/**
 *	@ingroup parser
 */
class TaggedSentenceReader : public SentenceReader
{
 public:
  TaggedSentenceReader(SentenceReader* reader, Parser::PosTagger* tagger) :
    reader(reader),
    tagger(tagger)
      { }

  /** @return true if there is another sentence available */
  bool			MoveNext();

  SentenceReader*	reader;
  Parser::PosTagger*	tagger;

};

/**
 *	@ingroup parser
 *
 *	Reads sentences from a queue in memory.
 */
class SentenceQueueReader : public Enumerator<Sentence*>
{
public:
  SentenceQueueReader(std::deque<Sentence*>& vs) :
    sentences(vs)
  { }

  bool		MoveNext() {
    if (sentences.empty())
      return false;
    current = sentences.front();
    sentences.pop_front();
    return true;
  }

  Sentence*	Current() { return current; }

  void		reset() {}

private:
  Sentence* current;
  std::deque<Sentence*>& sentences;
};

} // namespace Tanl

#endif // DeSR_SentenceReader_H
