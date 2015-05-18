/*
**  DeSR
**  src/PyPipe.h
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

#ifndef DeSR_PyPipe_H
#define DeSR_PyPipe_H

#include "Parser.h"

namespace Parser {

/**
 *	@ingroup parser
 *
 * A pipe that parses sentences from a Python iterator.
 */
struct ParserPipePython : public Enumerator<Sentence*>
{
public:
  /** Use a Python enumerator @c pit as source of sentences. */
  ParserPipePython(Parser& parser, PyObject* pit);

  bool		MoveNext();

  Sentence*	Current();

  ~ParserPipePython();

  /** This is to be called by SWIG when releasing the object.
   *  Release the parser object and then call destructor.
   */
  void		Dispose();

private:
  Parser&	parser;		///< the parser to use
  PyObject*	pit;		///< python iterator
  PyObject*	next;		///< next item from iterator
  Language const*	language;
};

} // namespace Parser

#endif // DeSR_PyPipe_H
