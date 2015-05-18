/*
**	Piqasso
**	MaxEntropy/samples/BasicEventStream.cpp
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
*/

#include "BasicEventStream.h"

#ifdef _WIN32
#include "lib/strtok_r.h"
#endif

using namespace std;

namespace Tanl {
namespace Classifier {

  /**
   *	Watch out: this is not idempotent!
   */
bool BasicEventStream::hasNext() {
  return is.getline(line, MAX_LINE_LEN);
}

/** 
  * Builds up the list of predicates for the current item.
  * Variable tok holds the next token already read.
  */ 
Event* BasicEventStream::next()
{
  Event* event = new Event();
  vector<string>& predicates = event->features;

  char* rest = line;
  char* token = ::strtok_r(0, " \t", &rest);
  if (!token)
    return event;
  event->className = token;
  while ((token = ::strtok_r(0, " \t", &rest))) {
      predicates.push_back(token);
  }
  return event;
}

}
}
