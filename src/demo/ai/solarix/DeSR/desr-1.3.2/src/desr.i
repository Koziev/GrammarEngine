/*
**  Tanl
**  desr/src/desr.i
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of Tanl.
**
**  Tanl is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  Tanl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

/*
Test:

from desr import *
c = Corpus.create("it", "CoNLL")
ifs = ifstream("test.conll")
sr = c.sentenceReader(ifs)
p = Parser.create("simple.ME")
pp = p.pipe(sr)
for x in pp:
  print c.toString(x)
*/

%module desr

// Tanl Library 

// Defines 
//   EnumeratorInterface(Sentence, Tanl::Sentence*);
// which provides Python iteration protocol to classes inheriting from
//   Enumerator<Sentence*>
%include Sentence.i

%{
#include "Parser.h"
%}

using namespace std;

namespace Parser {

#ifdef SWIGPYTHON

// Avoid that the parser gets destroyed by Python.
// When writing:
//   pp = Parser.create("model").pipe(sr)
// the parser proxy returned by Parser.create() must survive as long as pp.
// The exception below ensures that the refCount of the parser gets
// incremented. The ref/Parse below ensures that whenever Python creates
// a reference, the count also gets incremente.
// When pp disappears, the unref/Tanl::Enumerator<Tanl::Sentence*> in
// Sentence.i decreases the count of the embedded parser object.

%allowexception;

// Constructor increases count
%exception Parser::create { $action; result->incRef(); }

%exception Parser::pipe {
   $action
   arg1->incRef();	// the pipe has a reference to the parser
}
#endif

%newobject Parser::create;
%newobject Parser::pipe;
%newobject Parser::parse;

class Parser : //public IPipe<Sentence*, Sentence*>,
	       public virtual Tanl::RefCountable
{
public:
  static Parser*			create(char const* modelFile);
  Tanl::Enumerator<Tanl::Sentence*>*	pipe(Tanl::Enumerator<Tanl::Sentence*>& tve);
  Tanl::Enumerator<Tanl::Sentence*>*	pipe(Tanl::Enumerator<vector<Tanl::Token*>*>& tve);
#ifdef SWIGPYTHON
  Tanl::Enumerator<Tanl::Sentence*>*	pipe(PyObject* pit);
#endif

  Tanl::Sentence*			parse(Tanl::Sentence* sentence);

  %extend {
    void showPerplexity() { self->config.ShowPerplexity = true; }
  }

private:
  Parser(); // no constructor
};

} // namespace Parser
