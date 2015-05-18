/*
**  DeSR
**  src/PyPipe.cpp
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

#include "PyPipe.h"

namespace Parser {

Enumerator<Sentence*>* Parser::pipe(PyObject* pit)
{
  // pit is an iterator on a list of list of tokens.
  if (PyIter_Check(pit))
    return new ParserPipePython(*this, pit);
  return 0;
}

ParserPipePython::ParserPipePython(Parser& parser, PyObject* pit) :
  parser(parser),
  pit(pit),
  language(Language::get(parser.config.lang->c_str()))
{
  Py_INCREF(pit);
}

ParserPipePython::~ParserPipePython()
{
  Py_DECREF(pit);
}

void ParserPipePython::Dispose()
{
  parser.decRef();
  delete this;
}

bool ParserPipePython::MoveNext()
{
  next = PyIter_Next(pit);
  return next;
}

static void* extract_swig_wrapped_pointer(PyObject* obj)
{
  PyObject* thisAttr = PyObject_GetAttrString(obj, "this");
  if (thisAttr == NULL)
    return NULL;
  //This Python Object is a SWIG Wrapper and contains our pointer
  void* pointer = thisAttr + 1; //(PySwigObject*)thisAttr)->ptr;
  Py_DECREF(thisAttr);
  return pointer;
}

Sentence* ParserPipePython::Current()
{
  // next is a Python list of SWIG wrapped tokens
  PyObject* iterator = PyObject_GetIter(next);
  if (iterator == NULL) {
    /* propagate error */
  }

  Sentence* sentence = new Sentence(language);
  int id = 1;
  PyObject* item;
  while (item = PyIter_Next(iterator)) {
    // extract the C++ token
    Token* tok = (Token*)extract_swig_wrapped_pointer(item);
    TreeToken* token = new TreeToken(id++, tok->form, tok->attributes, tok->links);
    sentence->push_back(token);
    Py_DECREF(item);
  }

  Py_DECREF(iterator);

  if (PyErr_Occurred()) {
    /* propagate error */
  }
  return parser.parse(sentence);
}

} // namespace Parser
