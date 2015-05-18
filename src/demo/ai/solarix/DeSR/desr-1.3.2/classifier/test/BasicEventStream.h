/*
**	Piqasso
**	MaxEntropy/samples/BasicEventStream.h
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
*/

#ifndef BasicEventStream_H
#define BasicEventStream_H

#include <iostream>
#include "classifier/Classifier.h"

namespace Tanl {
namespace Classifier {

/**
 *	A stream of training events obtained from a text stream,
 *	one event per line, represented as a list of predicate names and
 *	an outcome.
 */
class BasicEventStream : public EventStream
{

  static int const MAX_LINE_LEN = 65535;

public:
  /**
   * Creates a new <code>BasicEventStream</code> instance which uses
   * the set of induced abbreviations.
   *
   * @param is	the input stream containing the trainig text
   */
  BasicEventStream(std::istream& is) : is(is) { }

  virtual ~BasicEventStream() { }

  bool		hasNext();
  Event*	next();

private:
  std::istream&	is;
  char		line[MAX_LINE_LEN];
};

}
}
#endif // BasicEventStream_H
