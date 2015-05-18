/*
**  Tanl
**  classifier/StreamTokenizer.cpp
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

#include "StreamTokenizer.h"

#ifdef _WIN32
# include "lib/strtok_r.h"
#endif

#include <fstream>
#include <iostream>

using namespace std;

namespace Tanl {
namespace Classifier {

vector<char*> StreamTokenizer::lineTokens(char const* delim) 
{
  vector<char*> as;
  while (stream->getline(line, MAX_LINE)) {
    char** next = 0;
    char* tok = ::strtok_r(line, delim, next);
    while (tok) {
      as.push_back(tok);
      tok = ::strtok_r(0, delim, next);
    }
  }
  return as;
}

int FileTokenizer::expectInt(char* s)
{
  vector<char*> res = lineTokens(" \t\r\n");
  if (!strcmp(s, res[0]))
    return atoi(res[1]);
  cerr << "Expecting " << s << " in file " << fname
       << " instead of " << res[0] << endl;
  return 0;
}

double FileTokenizer::expectDouble(char* s)
{
  vector<char*> res = lineTokens(" \t\r\n");
  if (!strcmp(s, res[0]))
    return strtod(res[1], NULL);
  cerr << "Expecting " << s << " in file " << fname
       << " instead of " << res[0] << endl;
  return 0;
}

/**
 * Carica la tabella hash con un elenco di stringhe (una per riga)
 */
void readItems(char const* fname, Text::WordIndex& hashtable)
{
  FileTokenizer ft(fname);
  vector<char*> res;
  int i = 0;
  while (!(res = ft.lineTokens(" \t\r\n")).empty())
    hashtable[res[1]] = i++;
  cerr << "Read " << hashtable.size() << " items from " << fname << endl;
}

/*
char* filesname(const char* s, const char* p)
{
  char* res = new char[strlen(s) + strlen(p) + 1];
  sprintf(res,"%s%s", s, p);
  return res;
}
*/

} // namespace Classifier
} // namespace Tanl
