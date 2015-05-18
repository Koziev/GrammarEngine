/*
**	IXE
**	MaxEntropy/model/BasicContextStream.h
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
*/

#ifndef BasicContextStream_H
#define BasicContextStream_H

#include <iostream>
#include "classifier/Classifier.h"
#include "text/WordIndex.h"

namespace Tanl {
namespace Classifier {

/**
 *	A stream of contexts obtained from a text stream,
 *	one context per line, represented as a list of predicate names.
 */
class BasicContextStream : public ContextStream
{

  static int const MAX_LINE_LEN = 65535;

public:
  /**
   * Creates a new @c BasicContextStream instance which uses
   * the set of induced abbreviations.
   *
   * @param is	the input stream containing the text to be analysed
   */
  BasicContextStream(std::istream& is, Tanl::Text::WordIndex& predIndex);

  virtual ~BasicContextStream() { }

  bool		hasNext();
  Context*	next();

private:
  std::istream&	is;
  char		line[MAX_LINE_LEN];
  Context	context;
  Tanl::Text::WordIndex&	predIndex;
};

}
}
#endif // BasicContextStream_H
