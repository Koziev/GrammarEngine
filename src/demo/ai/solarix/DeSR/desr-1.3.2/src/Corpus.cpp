/*
**  DeSR
**  src/Corpus.cpp
** ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
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

#include "Corpus.h"
#include "text/XmlReader.h"
#include "SplitSentenceReader.h"

// library
#include "io/File.h"

// standard
#include <sstream>

using namespace std;

namespace Tanl {

// ======================================================================
// Corpus

Corpus::Corpus(Language const& lang, char const* formatFile) :
  language(lang)
{
  CorpusFormat* cf = parseFormat(formatFile);
  if (cf) {
    tokenFields = cf->tokenFields; // copy
    index = cf->index;		   // copy
    delete cf;			   // no longer needed
  } else
    throw CorpusFormatError(string("Reading file: ") + formatFile);
}

Corpus* Corpus::create(Language const& language, char const* inputFormat)
{
  Corpus* corpus = 0;
  CorpusFactory* cfactory = CorpusMap::get(inputFormat);
  if (cfactory)
    corpus = cfactory(language, 0); // builtin corpus
  else if (IXE::io::File(inputFormat).exists()) {
    CorpusFormat* inFormat = Corpus::parseFormat(inputFormat);
    if (!inFormat) {
      cerr << "Bad format file: " << *inputFormat << endl;
      return 0;
    }
    cfactory = CorpusMap::get(inFormat->name.c_str());
    if (cfactory)
      corpus = cfactory(language, inFormat);
    else
      corpus = new Corpus(language, *inFormat);	// default tab format
  }
  return corpus;
}

Corpus* Corpus::create(char const* language, char const* inputFormat)
{
  Language const* lang = Language::get(language);
  if (!lang)
    lang = Language::get("en");
  return create(*lang, inputFormat);
}

CorpusFormat* Corpus::parseFormat(char const* formatFile)
{
  ifstream fmt(formatFile);
  return parseFormat(fmt);
}

CorpusFormat* Corpus::parseFormat(istream& fmt)
{
  Tanl::XML::XmlReader reader(fmt);
  CorpusFormat* format = new CorpusFormat();
  AttributeIndex& index = format->index;
  while (reader.Read()) {
    switch (reader.NodeType) {
    case Tanl::XML::Element:
      string& name = reader.Name;
      if (name == "CorpusFormat") {
	if (reader.MoveToFirstAttribute()) {
	  do {
	    string& name = reader.Name;
	    string& value = reader.Value;
	    if (name == "name") {
	      format->name = value;
	    }
	  } while (reader.MoveToNextAttribute());
	}
      } else if (name == "field") {
	// read field
	TokenField field;
	if (reader.MoveToFirstAttribute()) {
	  do {
	    string& name = reader.Name;
	    string& value = reader.Value;
	    if (name == "name") {
	      field.name = value;
	      index.insert(value.c_str()); // names of attributes go into index
	    } else if (name == "use")
	      field.use = (value == "INPUT" ? TokenField::input :
			   (value == "OUTPUT" ? TokenField::output :
			    (value == "ECHO" ? TokenField::echo :
			     (value == "IGNORE" ? TokenField::ignore :
			      TokenField::input))));
	    else if (name == "value")
	      field.value = (value == "STRING" ? TokenField::string :
			     (value == "INTEGER" ? TokenField::integer : TokenField::string));
	    else if (name == "role")
	      field.role = (value == "FORM" ? TokenField::form :
			    (value == "HEAD" ? TokenField::head :
			     (value == "DEPREL" ? TokenField::deprel :
			      (value == "PREDICATE" ? TokenField::predicate :
			       (value == "MORPH" ? TokenField::morph :
				(value == "POS" ? TokenField::pos :
				 TokenField::none))))));
	    else if (name == "link")
	      field.link = value;
	    else if (name == "label")
	      field.label = value;
	    else if (name == "default")
	      field.default_ = value;
	  } while (reader.MoveToNextAttribute());
	}
	format->tokenFields.push_back(field);
      } else {
	delete format;
	return 0;
      }
    }
  }
  return format;
}

SentenceReader* Corpus::sentenceReader(istream* is) {
  return new SentenceReader(is, this);
}

void Corpus::print(ostream& os, Sentence const& sent) const
{
  FOR_EACH (Sentence, sent, tit) {
    (*tit)->printTab(os, *this);
    os << endl;
  }
}

std::string Corpus::toString(Sentence const& sent) const
{
  std::ostringstream ss;
  FOR_EACH (Sentence, sent, tit) {
    (*tit)->printTab(ss, *this);
    ss << endl;
  }
  return ss.str().c_str();
}

// ======================================================================
// Conll08Corpus

void Conll08Corpus::print(ostream& os, Sentence const& sent) const
{
  // collect attributes except PRED:
  vector<int> preds;
  FOR_EACH (Sentence, sent, tit) {
    if (!(*tit)->get("PRED")->empty())
      preds.push_back((*tit)->id);
  }
  FOR_EACH (Sentence, sent, tit) {
    (*tit)->printConll08(os, *this, &preds);
    os << endl;
  }
}

/**
 *	Constructor for Conll08Corpus
 */
Corpus*	Conll08CorpusFactory(Language const& lang, CorpusFormat* format)
{
  return new Conll08Corpus(lang, *format);
}

REGISTER_CORPUS(conll08, Conll08CorpusFactory);

// ======================================================================
// CombCorpus

/**
 *	Used to produce difference files, representing arg/predicates in
 *	dependency labels using a pair <arg, pathDiff>, where arg is the
 *	proper ARG label and pathDiff is the path difference to the predicate,
 *	with respect to the dependency link.
*/
void CombCorpus::print(ostream& os, Sentence const& sent) const
{
  FOR_EACH (Sentence, sent, tit) {
    bool first = true;
    TreeToken const& node = **tit;
    Token const& tok = *node.token;
    // print ARG if present and not reflexive
    TokenLink const* arg = 0;
    if (!tok.links.empty()) {
      FOR_EACH (TokenLinks, tok.links, lit)
	if (lit->head != node.id) { // non reflexive
	  arg = &*lit;
	  break;
	}
    }
    TokenFields::const_iterator tfit = tokenFields.begin();
    FOR_EACH (vector<char const*>, index.names, it) {
      string const* tag = tok.attributes.get(*it);
      if (first)
	first = false;
      else
	os << "\t";
      switch (tfit->role) {
      case TokenField::head:
	  os << node.linkHead();	// dont change or else cycles may arise
	break;
      case TokenField::deprel:
	if (arg && arg->label.substr(0, 2) != "SU") // SU are not scored
#	  ifdef PATH_DIFF
	  {
	  if (arg->head == node.linkHead())
	    os << arg->label;
	  else {
	    // tree distance
	    int upDep = node.linkHead();
	    int upArg = arg->head;
	    if (upDep && (upDep = sent[upDep-1]->linkHead()) == arg->head) {
	      os << arg->label << "!"; // one down
	      break;
	    } else if (upArg && upDep == sent[upArg-1]->linkHead()) {
	      os << arg->label << "!^"; // one down, one up
	      break;
	    } else if (upDep == node.id) {
	      os << arg->label << "!="; // one reverse down
	      break;
	    } else if (upDep && (upDep = sent[upDep-1]->linkHead()) == arg->head) {
	      os << arg->label << "!!"; // two down
	      break;
	    } else if (upArg && upDep == sent[upArg-1]->linkHead()) {
	      os << arg->label << "!!^"; // two down, one up
	      break;
	    } else if (upDep == node.id) {
	      os << arg->label << "!!="; // two reverse down
	      break;
	    } else if (upDep && (upDep = sent[upDep-1]->linkHead()) == arg->head) {
	      os << arg->label << "!!!"; // three down
	      break;
	    } else if (upDep == node.id) {
	      os << arg->label << "!!!="; // three reverse down
	      break;
	    } else if (upDep && (upDep = sent[upDep-1]->linkHead()) == arg->head) {
	      os << arg->label << "!!!!"; // four down
	      break;
	    } else if (upArg && (upArg = sent[upArg-1]->linkHead()) == node.linkHead()) {
	      os << arg->label << "^"; // one up
	      break;
	    } else if (upArg == node.id) {
	      os << arg->label << "^="; // one reverse up
	      break;
	    } else if (upArg && (upArg = sent[upArg-1]->linkHead()) == node.linkHead()) {
	      os << arg->label << "^^"; // two up
	      break;
	    } else if (upArg == node.id) {
	      os << arg->label << "^^="; // two reverse up
	      break;
	    } else if (upArg && (upArg = sent[upArg-1]->linkHead()) == node.linkHead()) {
	      os << arg->label << "^^^"; // three up
	      break;
	    } else if (upArg == node.id) {
	      os << arg->label << "^^^="; // three reverse up
	      break;
	    } else if (upArg && (upArg = sent[upArg-1]->linkHead()) == node.linkHead()) {
	      os << arg->label << "^^^^"; // four up
	      break;
	    }
	    // linear distance
	    // if root token, consider distance from itself
	    int dist = arg->head - (node.linkHead() ? node.linkHead() : node.id);
	    char buf[20];
	    snprintf(buf, sizeof(buf), "%s%+i",
		     arg->label.c_str(), dist);
	    os << buf;
	  }
	}
#	else
	  os << arg->label;
#	endif
	else
	  os << node.linkLabel();
	break;
      default:
	os << ((!tag || tag->empty()) ? tfit->default_ : *tag);
      }
      ++tfit;
    }
//    os << endl;
  }
}

// ======================================================================
// ConllXCorpus

char const* conllXFormat =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<CorpusFormat name=\"conllX\">"
  "	<field name=\"ID\" use=\"ECHO\" value=\"INTEGER\"/>"
  "	<field name=\"FORM\" use=\"INPUT\" value=\"STRING\" role=\"FORM\"/>"
  "	<field name=\"LEMMA\" use=\"INPUT\" value=\"STRING\"/>"
  "	<field name=\"CPOSTAG\" use=\"INPUT\" value=\"STRING\"/>"
  "	<field name=\"POSTAG\" use=\"INPUT\" value=\"STRING\"/>"
  "	<field name=\"FEATS\" use=\"INPUT\" value=\"STRING\" role=\"MORPH\"/>"
  "	<field name=\"HEAD\" use=\"OUTPUT\" link=\"DEP\" role=\"HEAD\"/>"
  "	<field name=\"DEPREL\" use=\"OUTPUT\" label=\"DEP\" role=\"DEPREL\"/>"
  "	<field name=\"PHEAD\" use=\"IGNORE\" default=\"_\"/>"
  "	<field name=\"PDEPREL\" use=\"IGNORE\" default=\"_\"/>"
  "</CorpusFormat>";

ConllXCorpus::ConllXCorpus(Language const& lang) :
  Corpus(lang)
{
  istringstream iss(conllXFormat);
  CorpusFormat* cf = parseFormat(iss);
  if (cf) {
    tokenFields = cf->tokenFields;
    index = cf->index;
    delete cf;
  } else
    throw CorpusFormatError("conllXFormat");
}

SentenceReader* ConllXCorpus::sentenceReader(istream* is)
{
  return new ConllXSentenceReader(is, this);
}

void ConllXCorpus::print(ostream& os, Sentence const& sent) const
{
  FOR_EACH (Sentence, sent, tit) {
    (*tit)->printTab(os, *this);
    os << endl;
  }
}

/**
 *	Constructor for ConllXCorpus
 */
Corpus*	ConllXCorpusFactory(Language const& lang, CorpusFormat* format)
{
  return new ConllXCorpus(lang);
}

REGISTER_CORPUS(CoNLL, ConllXCorpusFactory);

// ======================================================================
// DGACorpus

char const* DgaFormat =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<CorpusFormat name=\"DGA\">"
"	<field name=\"id\" use=\"ECHO\" value=\"INTEGER\"/>"
"	<field name=\"orth\" use=\"INPUT\" value=\"STRING\" role=\"FORM\"/>"
"	<field name=\"lemma\" use=\"INPUT\" value=\"STRING\"/>"
"	<field name=\"pos\" use=\"INPUT\" value=\"STRING\"/>"
"	<field name=\"gen\" use=\"INPUT\" value=\"STRING\"/>"
"	<field name=\"num\" use=\"INPUT\" value=\"STRING\"/>"
"	<field name=\"per\" use=\"INPUT\" value=\"STRING\"/>"
"	<field name=\"head\" use=\"OUTPUT\" link=\"DEP\" role=\"HEAD\"/>"
"	<field name=\"type\" use=\"OUTPUT\" label=\"DEP\" role=\"DEPREL\"/>"
"</CorpusFormat>";

DgaCorpus::DgaCorpus(Language const& lang) :
  Corpus(lang)
{
  istringstream iss(DgaFormat);
  CorpusFormat* cf = parseFormat(iss);
  if (cf) {
    tokenFields = cf->tokenFields;
    index = cf->index;
    delete cf;
  } else
    throw CorpusFormatError("DgaFormat");
}

SentenceReader* DgaCorpus::sentenceReader(istream* is)
{
  return new DgaSentenceReader(is, this);
}

void DgaCorpus::print(ostream& os, Sentence const& sent) const
{
  FOR_EACH (Sentence, sent, tit) {
    (*tit)->print(os);
    os << endl;
  }
}

/**
 *	Constructor for DgaXMLCorpus
 */
Corpus*	DgaXMLCorpusFactory(Language const& lang, CorpusFormat* format)
{
  return new DgaCorpus(lang);
}

REGISTER_CORPUS(DgaXML, DgaXMLCorpusFactory);

// ======================================================================
// TextCorpus

SentenceReader* TextCorpus::sentenceReader(istream* is)
{
  return new SplitSentenceReader(is, this);
}

/**
 *	Constructor for TextCorpus
 */
Corpus*	TextCorpusFactory(Language const& lang, CorpusFormat* format)
{
  return new TextCorpus(lang);
}

REGISTER_CORPUS(Text, TextCorpusFactory);

// ======================================================================
// TokenizedTextCorpus

SentenceReader* TokenizedTextCorpus::sentenceReader(istream* is)
{
  return new TokenSentenceReader(is, this);
}

/**
 *	Constructor for TokenizedTextCorpus
 */
Corpus*	TokenizedTextCorpusFactory(Language const& lang, CorpusFormat* format)
{
  return new TokenizedTextCorpus(lang);
}

REGISTER_CORPUS(TokenizedText, TokenizedTextCorpusFactory);

// ======================================================================
// Corpus Factory

CorpusMap::CorpusMap(char const* type, CorpusFactory* rf)
{
  get()[type] = rf;
}

/**
 *      Define and initialize (exactly once) the static data member corpusFor
 *      and return a reference to it.  This function is needed to
 *      guarantee that the map is initialized before its first use across all
 *      translation units, something that would not be guaranteed if it were a
 *      static data member initialized at file scope.
 */
std::map<char const*, CorpusFactory*>& CorpusMap::get()
{
  static std::map<char const*, CorpusFactory*> corpusFor;
  return corpusFor;
}

CorpusFactory* CorpusMap::get(char const* type)
{
  std::map<char const*, CorpusFactory*>& corpusMap = get();
  map<char const*, CorpusFactory*>::const_iterator rit = corpusMap.find(type);
  return (rit == corpusMap.end()) ? 0 : rit->second;
}

} // namespace Tanl
