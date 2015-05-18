/*
**  DeSR
**  src/SplitSentenceReader.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
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

// local
#include "SplitSentenceReader.h"

namespace Tanl {

char const* SplitSentenceReader::BoundarySet::defaultBoundaryTokens[] =
  {".", "!", "?", 0 };
char const* SplitSentenceReader::BoundarySet::defaultBoundaryFollowers[] =
  {")", "]", "\"", "\'", "''", "-RRB-", "-RSB-", 0 };

SplitSentenceReader::BoundarySet const SplitSentenceReader::defaultBS;


  SplitSentenceReader::SplitSentenceReader(std::istream* is,
					 Corpus* corpus,
					 BoundarySet const* bs) :
  SentenceReader(is, corpus),
  tokenizer(is),
  boundarySet(bs),
  insideRegion(false)
{
}

bool SplitSentenceReader::MoveNext()
{
  if (!tokenizer.MoveNext())
    return false;

  sentence = new Sentence;
  int id = 1;
  do {
    char const* scanTok = tokenizer.Current()->text;
    TreeToken* tok = new TreeToken(id++, scanTok);
    sentence->push_back(tok);
    if (boundarySet->ends(scanTok))
      break;
  } while (tokenizer.MoveNext());
  return true;
}

} // namespace Tanl
