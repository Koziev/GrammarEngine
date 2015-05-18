/*
**  DeSR
**  src/Language.cpp
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

// standard
#include <string.h>

#include "Language.h"

namespace Tanl {

class Languages {
public:
typedef std::pair<char const*, Language const*> tableItem;

  /**
   * Table associating Language to ISO-639 language code.
   */
  static tableItem languageTable[];

  ~Languages();

  static Language const* get(char const* code);

  static char const* code(Language const* lang);
};

/**
 * Language codes.
 * @see http://ftp.ics.uci.edu/pub/ietf/http/related/iso639.txt
 */
Languages::tableItem Languages::languageTable[] = {
  tableItem("ar", new ArabicLanguage),
  tableItem("bn", new BanglaLanguage),
  tableItem("eu", new BasqueLanguage),
  tableItem("bg", new BulgarianLanguage),
  tableItem("ca", new CatalanLanguage),
  tableItem("zh", new ChineseLanguage),
  tableItem("cs", new CzechLanguage),
  tableItem("da", new DanishLanguage),
  tableItem("nl", new DutchLanguage),
  tableItem("en", new EnglishLanguage),
  tableItem("en.stanford", new EnglishStanfordLanguage),
  tableItem("fr", new FrenchLanguage),
  tableItem("de", new GermanLanguage),
  tableItem("el", new GreekLanguage),
  tableItem("hi", new HindiLanguage),
  tableItem("hu", new HungarianLanguage),
  tableItem("it", new ItalianLanguage),
  tableItem("it-tut", new ItalianTutLanguage),
  tableItem("ja", new JapaneseLanguage),
  tableItem("nn", new Language), // no language
  tableItem("pt", new PortugueseLanguage),
  tableItem("sl", new SloveneLanguage),
  tableItem("es", new SpanishLanguage),
  tableItem("sv", new SwedishLanguage),
  tableItem("te", new TeluguLanguage),
  tableItem("tr", new TurkishLanguage),
  tableItem("ru", new RussianLanguage)
};

Languages::~Languages()
{
  int len = sizeof(languageTable)/sizeof(tableItem);
  for (int i = 0; i < len; i++)
    delete languageTable[i].second;
}

Language const* Languages::get(char const* code)
{
  for (int i = 0; i < sizeof(languageTable)/sizeof(tableItem); i++)
    if (!strcmp(code, languageTable[i].first))
      return languageTable[i].second;
  return 0;
}

char const* Languages::code(Language const* lang)
{
  for (int i = 0; i < sizeof(languageTable)/sizeof(tableItem); i++)
    if (lang == languageTable[i].second)
      return languageTable[i].first;
  return "";
}

// Create single instance to be destroyed at exit
static Languages languagesInstance;

static char const* DEFAULT_ROOT_LABEL = "ROOT";

Language const* Language::get(char const* code)
{
  return Languages::get(code);
}

char const* Language::code() const
{
  return Languages::code(this);
}

//////////////////////////////////////////////////////////////////////

char const* Language::rootLabel() const
{
 return DEFAULT_ROOT_LABEL;
}

char const* EnglishStanfordLanguage::rootLabel() const
{
 return "null";
}

char const* CatalanLanguage::rootLabel() const
{
  return "S";
}

char const* FrenchLanguage::rootLabel() const
{
  return "root";
}

char const* IndianLanguage::rootLabel() const
{
  return "main";
}

char const* ItalianTutLanguage::rootLabel() const
{
  return "TOP";
}

char const* SpanishLanguage::rootLabel() const
{
  return "sentence";
}

} // namespace Tanl
