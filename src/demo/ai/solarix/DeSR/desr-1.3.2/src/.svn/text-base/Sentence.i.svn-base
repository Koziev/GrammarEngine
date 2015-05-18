/*
**  Tanl
**  desr/src/Sentence.i
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

%{
#include "Sentence.h"
#include "Corpus.h"
#include <sstream>
#include <fstream>
%}

// Standard
%include std_string.i
%include std_vector.i
%include std_fstream.i

// Tanl Library 
%include Enumerator.i
%include Token.i

%template(VectorTreeToken) std::vector<Tanl::TreeToken*>;

// Instantiate Enumerator template and provide Python iterator interface.
// (outside namespace)
EnumeratorInterface(Sentence, Tanl::Sentence*);

namespace Tanl {

%newobject Sentence::__repr__();

class Sentence : public std::vector<TreeToken*>
{
public:
  Sentence(Language const* language = 0);

  Language const* language;

# ifdef SWIGJAVA
%rename(toString) __repr__;
# endif

  %extend {

    Sentence& deref() { return *$self; }

    const char* __repr__() {
      std::ostringstream ss;
      for (int i = 0; i < $self->size(); i++) {
	Tanl::TreeToken* tok = (*$self)[i];
	tok->printTab(ss);
	ss << std::endl;
      }
      return strdup(ss.str().c_str());
    }
  }
};

class SentenceReader : public Enumerator<Sentence*>
{
public:
  SentenceReader(std::istream* is, Corpus* corpus);
  //SentenceReader(char const* fn, Corpus* corpus);
  virtual bool		MoveNext();
  virtual Sentence*	Current();
};

} // namespace Tanl
