/*
**  DeSR
**  src/PosTagger.cpp
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

#include "PosTagger.h"

extern "C" {
#include "tree-tagger-api.h"
}

namespace Parser {

PosTagger::PosTagger(char const* PosParameters)
{
  if (!init_treetagger((char *)PosParameters))
    throw PosTaggerError("POS Tagger initialization failed");
  int num_tags;
  for (char** tagit = tagger_tags(&num_tags); num_tags; --num_tags, ++tagit)
    tags.insert(*tagit);
}

bool PosTagger::tag(Tagged& sentence)
{
  size_t len = sentence.length();
  // ensure space
  sentence.tags.resize(len);
  sentence.lemmas.resize(len);

  // create structure for TreeTagger
  TAGGER_STRUCT ts;
  ts.word  = (char**)&(*sentence.words.begin());
  ts.tag   = (char**)&(*sentence.tags.begin());
  ts.lemma = (char**)&(*sentence.lemmas.begin());
  ts.number_of_words = (int)len;
  // perform tagging
  return tag_sentence(&ts);
}

// ======================================================================
// Penn TreeBank Tagger

struct Correspondence
{
  char const* TT;
  char const* Penn;
};

static Correspondence const PosCorrespondenceTable[] = {
  // TT	Penn
  "NP", "NNP",
  "NPS", "NNPS",
  "PP", "PRP",
  "PP$", "PRP$",
  "VV",	"VB",
  "VVD", "VBD",
  "VVG", "VBG",
  "VVN", "VBN",
  "VVP", "VBP",
  "VVZ", "VBZ",
  "VH",	"VB",
  "VHD", "VBD",
  "VHG", "VBG",
  "VHN", "VBN",
  "VHP", "VBP",
  "VHZ", "VBZ",
  "SENT", ".",
  0
};

PennPosTagger::PosMap		PennPosTagger::posMap;
PennPosTagger::PosMap		PennPosTagger::inversePosMap;

PennPosTagger::PennPosTagger(const char* PosParameters) :
  PosTagger(PosParameters)
{
  // fill PosMap
  if (posMap.empty()) {
    for (Correspondence const* e = PosCorrespondenceTable; e->TT; ++e) {
      posMap[string(e->TT)] = e->Penn;
      inversePosMap[string(e->Penn)] = e->TT;
    }
  }
}

bool PennPosTagger::tag(Tagged& sentence)
{
  size_t len = sentence.length();
  // ensure space
  sentence.tags.resize(len);
  sentence.lemmas.resize(len);

  // create structure for TreeTagger
  TAGGER_STRUCT ts;
  ts.word  = (char**)&(*sentence.words.begin());
  // convert tags from PennTreebank
  for (vector<char const*>::iterator sit = sentence.tags.begin();
       sit != sentence.tags.end(); ++sit) {
    if (*sit)
      *sit = inversePosMap[*sit];
  }
  ts.tag   = (char**)&(*sentence.tags.begin());
  ts.lemma = (char**)&(*sentence.lemmas.begin());
  ts.number_of_words = (int)len;
  // perform tagging
  bool res = tag_sentence(&ts);
  if (res) {
    // transform to Penn Treebank tagset:
    // http://www.ims.uni-stuttgart.de/projekte/corplex/TreeTagger/Penn-Treebank-Tagset.ps
    for (int i = 0; i < len; i++) {
      PosMap::const_iterator mit = posMap.find(ts.tag[i]);
      if (mit != posMap.end())
	ts.tag[i] = (char*)mit->second;
    }
  }
  return res;
}

} // namespace Parser

