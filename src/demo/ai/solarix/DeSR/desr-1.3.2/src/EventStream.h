/*
**  DeSR
**  src/EventStream.h
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

#ifndef DeSR_EventStream_H
#define DeSR_EventStream_H

// local
#include "State.h"
#include "Enumerator.h"
#include "Corpus.h"

namespace Parser {

/**
 *	@ingroup parser
 *
 *	Creates a stream of Classifier::Event's from an annotated dependency corpus.
 */
class EventStream : public Tanl::Classifier::EventStream, public Iterator<Tanl::Classifier::Event*>
{
 public:

  /**
   *	Constructor.
   *	@param reader the SentenceReader for a Dependency Grammar Corpus.
   *	@param info	where to store information collected from sentences.
   *	@param sentenceCutoff	max number of sentences to read. Default INT_MAX.
   */
  EventStream(Tanl::Enumerator<Sentence*>* reader, GlobalInfo* info,
	      int sentenceCutoff = INT_MAX) :
    reader(reader),
    info(info),
    sentenceCutoff(sentenceCutoff),
    sentenceCount(0),
    state(0)
  { }

  virtual ~EventStream() {
    delete state;
  }

  /** 
   *	@return true if there are other events.
   */
  bool		hasNext();

  /**
   *	@return next event from stream, and perform corresponding action.
   */
  Tanl::Classifier::Event*	next();

  /**
   *	Restart
   */
  void		reset() {
    reader->Reset();
    sentenceCount = 0;
  }
  
  /**	Tells whether it is the end of a sentence.*/
  bool		EoS() { return !state->hasNext(); }
  
  Tanl::Enumerator<Sentence*>*	reader;	///< used to read sentences
  TrainState*		state;	///< parser state
  GlobalInfo*		info;	///< collected information

  /**	@return the feature indicated for splitting the model */
  std::string&		splitFeature() { return state->splitFeature; }

  /**	Max number of sentence to read	*/
  int			sentenceCutoff;
  /**	Sentence read so far	*/
  int			sentenceCount;
};

} // namespace Parser

#endif // DeSR_EventStream_H
