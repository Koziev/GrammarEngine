/*
**  DeSR
**  src/ReviseEventStream.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef DesR_ReviseEventStream_H
#define DesR_ReviseEventStream_H

// library
#include "Classifier.h"

// local
#include "SentenceReader.h"

namespace Parser {

/**
 *	@ingroup parser
 */
class ReviseStream
{
 public:
  ReviseStream() { }

  virtual ~ReviseStream() { delete sentence; }

  /**
   *	Actions to revise each node of the parser tree.
   */
  std::vector<std::string>	actions;

 protected:

  ReviseStream(Tanl::SentenceReader* reader);

  void			clear();
  void			predicates(Tanl::Classifier::Features& preds);
  void			childFeatures(Tanl::TreeToken* tok, char const* tag,
				      Tanl::Classifier::Features& preds);

  /**
   *	The reader used to read tokens from the stream
   */
  Tanl::SentenceReader*	reader;

  Tanl::Sentence*		sentence;

 public:			/* FIXME: temporary */
  unsigned			cur;	///< current position on the sentence

};

/**
 *	@ingroup parser
 */
class ReviseEventStream : public ReviseStream
{
  ReviseEventStream() { }
};

/**
 *	@ingroup parser
 */
class ReviseContextStream : public ReviseStream, public Tanl::Classifier::ContextStream
{
 public:
  /**
   *	@param reader	the reader used to read sentences
   *	@param predIndex	the mapping from predicates to PIDs from the
   *				model
   */
  ReviseContextStream(Tanl::SentenceReader* reader, WordIndex& predIndex) :
    ReviseStream(reader),
    predIndex(predIndex)
    { }

  bool		hasNext();
  Tanl::Classifier::Context*	next();
  char const*	Outcome();

  /**
   *	Revise parse tree according to actions
   */
  void		revise();

 private:
  int		performAction(Tanl::TreeToken* to, int from, char const* action);

  WordIndex& predIndex;
  Tanl::Classifier::Context context;
};

} // namespace Parser

#endif // DesR_ReviseEventStream_H
