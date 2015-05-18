/*
**	IXE
**	MaxEntropy/model/BasicContextStream.cpp
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
*/

#include "BasicContextStream.h"

#ifdef _WIN32
#include "lib/strtok_r.h"
#endif

using namespace std;
using namespace Tanl::Text;

namespace Tanl {
namespace Classifier {

BasicContextStream::BasicContextStream(istream& is, WordIndex& predIndex) :
  is(is),
  predIndex(predIndex)
{ }

  /**
   *	Watch out: this is not idempotent!
   */
bool BasicContextStream::hasNext() {
  return is.getline(line, MAX_LINE_LEN);
}

/** 
  * Builds up the list of predicates for the current item.
  * Variable tok holds the next token already read.
  */ 
Context* BasicContextStream::next()
{
  context.clear();

  char* rest = line;
  char* tok;
  while ((tok = ::strtok_r(0, " \t", &rest))) {
    if (predIndex.find(tok) != predIndex.end())
      context.push_back(predIndex[tok]);
  }
  return &context;
}

}
}
