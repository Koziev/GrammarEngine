/*
**  DeSR
**  src/EventStream.cpp
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

#include "EventStream.h"
#include "Parser.h"

namespace Parser {

//======================================================================
// EventStream

bool EventStream::hasNext()
{
  if (state && state->hasNext())
    return true;
  while (sentenceCount++ < sentenceCutoff && reader->MoveNext()) {
    Sentence* sentence = reader->Current();
    if (sentence->size()) {
      delete state;
      state = new TrainState(*sentence, info);
      delete sentence;		// TrainState() copies it.
      return true;
    }
    delete sentence;
  }
  return false;
}

/**
 *	Generate the next training event and perform parse action.
 *	The event outcome is the next action from actions, the context is
 *	generated from the past tokens (on the stack) and later tokens in
 *	the sentence (from input).
 *	@return the next training event.
 */
Tanl::Classifier::Event* EventStream::next()
{
  Tanl::Classifier::Event* ev = state->next();
  state->transition(ev->className.c_str());
  return ev;
}

} // namespace Parser
