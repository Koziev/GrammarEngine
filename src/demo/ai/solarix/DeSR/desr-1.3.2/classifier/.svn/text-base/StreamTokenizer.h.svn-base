/*
**  Tanl
**  classifier/StreamTokenizer.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef Tanl_classifier_StreamTokenizer_H
#define Tanl_classifier_StreamTokenizer_H

#include <fstream>
#include <string>
#include <vector>

#include "text/WordIndex.h"

#define MAX_LINE 1024

namespace Tanl {
namespace Classifier {

class StreamTokenizer
{
public:
  StreamTokenizer() { }
  StreamTokenizer(std::ifstream& stream) :
    stream(&stream) { }

  std::vector<char*>	lineTokens(char const* delim);

protected:
  std::ifstream*	stream;
  char		line[MAX_LINE];
};

class FileTokenizer : public StreamTokenizer
{
public:
  FileTokenizer(std::string file) :
    fname(file.c_str()), ifs(fname)
  {
    stream = &ifs;
  }

  FileTokenizer(char const* fname) :
    fname(fname), ifs(fname)
  {
    stream = &ifs;
  }


  FileTokenizer(char const* fname, std::ifstream& ifs) :
    fname(fname)
  {
    stream = &ifs;
  }

  int		expectInt(char* s);

  double	expectDouble(char* s);

private:
  char const*		fname;
  std::ifstream		ifs;
};

void	readItems(char const* fname, Tanl::Text::WordIndex& hashtable);

} // namespace Classifier
} // namespace Tanl

#endif //  Tanl_classifier_StreamTokenizer_H
