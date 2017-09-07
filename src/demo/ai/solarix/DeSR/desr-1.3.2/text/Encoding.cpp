/*
**  Tanl C++ Library
**  text/Encoding.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2002  Giuseppe Attardi (attardi@di.unipi.it).
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

#include "Encoding.h"

// standard
#include <map>
#include <iconv.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

namespace Tanl {
  namespace Text {

namespace {			// anonymous namespace

  /*
   *	These are the encodings supported by libiconv, i.e.:
    European languages
        ASCII, ISO-8859-{1,2,3,4,5,7,9,10,13,14,15,16},
        KOI8-R, KOI8-U, KOI8-RU,
        CP{1250,1251,1252,1253,1254,1257}, CP{850,866},
        Mac{Roman,CentralEurope,Iceland,Croatian,Romania},
        Mac{Cyrillic,Ukraine,Greek,Turkish},
        Macintosh
    Semitic languages
        ISO-8859-{6,8}, CP{1255,1256}, CP862, Mac{Hebrew,Arabic}
    Japanese
        EUC-JP, SHIFT_JIS, CP932, ISO-2022-JP, ISO-2022-JP-2, ISO-2022-JP-1
    Chinese
        EUC-CN, HZ, GBK, GB18030, EUC-TW, BIG5, CP950, BIG5-HKSCS,
        ISO-2022-CN, ISO-2022-CN-EXT
    Korean
        EUC-KR, CP949, ISO-2022-KR, JOHAB
    Armenian
        ARMSCII-8
    Georgian
        Georgian-Academy, Georgian-PS
    Tajik
        KOI8-T
    Thai
        TIS-620, CP874, MacThai
    Laotian
        MuleLao-1, CP1133
    Vietnamese
        VISCII, TCVN, CP1258
    Platform specifics
        HP-ROMAN8, NEXTSTEP
    Full Unicode
        UTF-8
        UCS-2, UCS-2BE, UCS-2LE
        UCS-4, UCS-4BE, UCS-4LE
        UTF-16, UTF-16BE, UTF-16LE
        UTF-32, UTF-32BE, UTF-32LE
        UTF-7
        C99, JAVA
    Full Unicode, in terms of `uint16_t' or `uint32_t'
        (with machine dependent endianness and alignment)
        UCS-2-INTERNAL, UCS-4-INTERNAL
   */

#define E(n,i,a,m) Encoding(n,i,(float)a,m)

  static Tanl::Text::Encoding const encodingTable[] = {
    // name		id	avg sz	max sz
    // ---------------------------------------
    E("ISO-8859-1",	0,	1.0,	1.0),
    E("ISO-8859-2",	1,	1.0,	1.0),
    E("ISO-8859-3",	2,	1.0,	1.0),
    E("ISO-8859-4",	3,	1.0,	1.0),
    E("ISO-8859-5",	4,	1.0,	1.0),
    E("ISO-8859-6",	5,	1.0,	1.0),
    E("ISO-8859-7",	6,	1.0,	1.0),
    E("ISO-8859-8",	7,	1.0,	1.0),
    E("ISO-8859-9",	8,	1.0,	1.0),
    E("ISO-8859-10",	9,	1.0,	1.0),
    E("ISO-8859-13",	10,	1.0,	1.0),
    E("ISO-8859-14",	11,	1.0,	1.0),
    E("ISO-8859-15",	12,	1.0,	1.0),
    E("ISO-8859-16",	13,	1.0,	1.0),
    E("US-ASCII",	16, 	1.0,	1.0),
    E("UTF-8",		17,	1.2,	6.0),
    E("UCS-2",		18,	2.1,	6.0),
    E("UCS-2BE",	19,	2.1,	6.0),
    E("UCS-2LE",	20,	2.1,	6.0),
    E("UCS-4",		21,	4.0,	6.0),
    E("UCS-4BE",	22,	4.0,	6.0),
    E("UCS-4LE",	23,	4.0,	6.0),
    E("UTF-16",		24,	2.1,	6.0),
    E("UTF-16BE",	25,	2.1,	6.0),
    E("UTF-16LE",	26,	2.1,	6.0),
    E("UTF-32",		27,	4.0,	6.0),
    E("UTF-32BE",	28,	4.0,	6.0),
    E("UTF-32LE",	29,	4.0,	6.0),
    E("UTF-7",		30,	1.0,	6.0),
    E("UCS-2-INTERNAL",	31,	2.0,	6.0),
    E("UCS-2-SWAPPED",	32,	2.0,	6.0),
    E("UCS-4-INTERNAL",	33,	4.0,	6.0),
    E("UCS-4-SWAPPED",	34,	4.0,	6.0),
    E("C99",		35,	1.2,	10.0),
    E("JAVA",		36,	1.2,	6.0),
    E("KOI8-R",		37,	1.5,	6.0),
    E("KOI8-U",		38,	1.5,	6.0),
    E("KOI8-RU",	39,	1.5,	6.0),
    E("KOI8-T",		40,	1.5,	6.0),
    E("CP850",		41,	1.0,	1.0),
    E("CP862",		42,	1.0,	1.0),
    E("CP866",		43,	1.0,	1.0),
    E("CP874",		44,	1.5,	6.0),
    E("CP932",		45,	1.5,	6.0),
    E("CP949",		46,	1.5,	6.0),
    E("CP950",		47,	1.5,	6.0),
    E("CP1133",		48,	1.0,	1.0),
    E("CP1250",		49,	1.0,	1.0),
    E("CP1251",		50,	1.0,	1.0),
    E("CP1252",		51,	1.0,	1.0),
    E("CP1253",		52,	1.0,	1.0),
    E("CP1254",		53,	1.0,	1.0),
    E("CP1255",		54,	1.0,	1.0),
    E("CP1256",		55,	1.0,	1.0),
    E("CP1257",		56,	1.0,	1.0),
    E("CP1258",		57,	1.0,	1.0),
    E("MacRoman",	58,	1.5,	6.0),
    E("MacCentralEuope",	59,	1.5,	6.0),
    E("MacIceland",	60,	1.5,	6.0),
    E("MacCroatian",	61,	1.5,	6.0),
    E("MacRomania",	62,	1.5,	6.0),
    E("MacCyrillic",	63,	1.5,	6.0),
    E("MacUkraine",	64,	1.5,	6.0),
    E("MacGreek",	65,	1.5,	6.0),
    E("MacTurkish",	66,	1.5,	6.0),
    E("MacHebrew",	67,	1.5,	6.0),
    E("MacArabic",	68,	1.5,	6.0),
    E("MacThai",	69,	1.5,	6.0),
    E("HP-ROMAN8",	70,	1.5,	6.0),
    E("NEXTSTEP",	71,	1.5,	6.0),
    E("ARMSCII-8",	72,	1.5,	6.0),
    E("GEORGIAN-ACADEMY",	73,	1.5,	6.0),
    E("GEORGIAN-PS",	74,	1.5,	6.0),
    E("MULELAO-1",	75,	1.5,	6.0),
    E("TIS-620",	76,	1.5,	6.0),
    E("ISO-IR-166",	77,	1.5,	6.0),
    E("VISCII",		78,	1.5,	6.0),
    E("TCVN",		79,	1.5,	6.0),
    E("JIS_C6220-1969-RO",80,	1.5,	6.0),
    E("JIS_X0201",	81,	1.5,	6.0),
    E("JIS_X0208",	82,	1.5,	6.0),
    E("JIS_X0212",	83,	1.5,	6.0),
    E("GB_1988-80",	84,	1.5,	6.0),
    E("GB_2312-80",	85,	1.5,	6.0),
    E("ISO-IR-165",	86,	1.5,	6.0),
    E("KSC_5601",	87,	1.5,	6.0),
    E("EUC-JP",		88,	1.5,	6.0),
    E("SHIFT_JIS",	89,	1.5,	6.0),
    E("ISO-2022-JP",	90,	1.5,	6.0),
    E("ISO-2022-JP-1",	91,	1.5,	6.0),
    E("ISO-2022-JP-2",	92,	1.5,	6.0),
    E("EUC-CN",		93,	1.5,	6.0),
    E("GBK",		94,	1.5,	6.0),
    E("GB18030",	95,	1.5,	6.0),
    E("ISO-2022-CN",	96,	1.5,	6.0),
    E("ISO-2022-CN-EXT",	97,	1.5,	6.0),
    E("HZ",		98,	1.5,	6.0),
    E("EUC-TW",		99,	1.5,	6.0),
    E("BIG5",		100,	1.5,	6.0),
    E("BIG5-HKSCS",	101,	1.5,	6.0),
    E("EUC-KR",		102,	1.5,	6.0),
    E("JOHAB",		103,	1.5,	6.0),
   };

  static char const* const aliasTable[] = {
    //	name            aliases
    //	--------------- --------------------------------------------
    "US-ASCII",		"ASCII", "ISO646-US", "ISO_646.IRV:1991", "ISO-IR-6", "ANSI_X3.4-1968", "ANSI_X3.4-1986", "CP367", "IBM367", "US", "csASCII", 0,
    "UCS-2",		"ISO-10646-UCS-2", "csUnicode", 0,
    "UCS-2BE",		"UNICODEBIG", "UNICODE-1-1", "csUnicode11", 0,
    "UCS-2LE",		"UNICODELITTLE", 0,
    "UCS-4",		"ISO-10646-UCS-4", "csUCS4", 0,
    "UTF-7",		"UNICODE-1-1-UTF-7", "csUnicode11UTF7", 0,
    "ISO-8859-1",	"ISO_8859-1", "ISO_8859-1:1987", "ISO-IR-100", "CP819", "IBM819", "LATIN1", "L1", "csISOLatin1", "ISO8859-1", 0,
    "ISO-8859-2",	"ISO_8859-2", "ISO_8859-2:1987", "ISO-IR-101", "LATIN2", "L2", "csISOLatin2", "ISO8859-2", 0,
    "ISO-8859-3",	"ISO_8859-3", "ISO_8859-3:1988", "ISO-IR-109", "LATIN3", "L3", "csISOLatin3", "ISO8859-3", 0,
    "ISO-8859-4",	"ISO_8859-4", "ISO_8859-4:1988", "ISO-IR-110", "LATIN4", "L4", "csISOLatin4", "ISO8859-4", 0,
    "ISO-8859-5",	"ISO_8859-5", "ISO_8859-5:1988", "ISO-IR-144", "CYRILLIC", "csISOLatinCyrillic", "ISO8859-5", 0,
    "ISO-8859-6",	"ISO_8859-6", "ISO_8859-6:1987", "ISO-IR-127", "ECMA-114", "ASMO-708", "ARABIC", "csISOLatinArabic", "ISO8859-6", 0,
    "ISO-8859-7",	"ISO_8859-7", "ISO_8859-7:1987", "ISO-IR-126", "ECMA-118", "ELOT_928", "GREEK8", "GREEK", "csISOLatinGreek", "ISO8859-7", 0,
    "ISO-8859-8",	"ISO_8859-8", "ISO_8859-8:1988", "ISO-IR-138", "HEBREW", "csISOLatinHebrew", "ISO8859-8", 0,
    "ISO-8859-9",	"ISO_8859-9", "ISO_8859-9:1989", "ISO-IR-148", "LATIN5", "L5", "csISOLatin5", "ISO8859-9", 0,
    "ISO-8859-10",	"ISO_8859-10", "ISO_8859-10:1992", "ISO-IR-157", "LATIN6", "L6", "csISOLatin6", "ISO8859-10", 0,
    "ISO-8859-13",	"ISO_8859-13", "ISO-IR-179", "LATIN7", "L7", "ISO8859-13", 0,
    "ISO-8859-14",	"ISO_8859-14", "ISO_8859-14:1998", "ISO-IR-199", "LATIN8", "L8", "ISO-CELTIC", "ISO8859-14", 0,
    "ISO-8859-15",	"ISO_8859-15", "ISO_8859-15:1998", "ISO-IR-203", "ISO8859-15", 0,
    "ISO-8859-16",	"ISO_8859-16", "ISO_8859-16:2000", "ISO-IR-226", "ISO8859-16", 0,
    "KOI8-R",		"csKOI8R", 0,
    "CP1250",		"WINDOWS-1250", "MS-EE", 0,
    "CP1251",		"WINDOWS-1251", "MS-CYRL", 0,
    "CP1252",		"WINDOWS-1252", "MS-ANSI", 0,
    "CP1253",		"WINDOWS-1253", "MS-GREEK", 0,
    "CP1254",		"WINDOWS-1254", "MS-TURK", 0,
    "CP1255",		"WINDOWS-1255", "MS-HEBR", 0,
    "CP1256",		"WINDOWS-1256", "MS-ARAB", 0,
    "CP1257",		"WINDOWS-1257", "WINBALTRIM", 0,
    "CP1258",		"WINDOWS-1258", 0,
    "CP850",		"IBM850", "850", "csPC850Multilingual", 0,
    "CP862",		"IBM862", "862", "csPC862LatinHebrew", 0,
    "CP866",		"IBM866", "866", "csIBM866", 0,
    "MacRoman",		"MACINTOSH", "MAC", "csMacintosh", 0,
    "HP-ROMAN8",	"ROMAN8", "R8", "csHPRoman8", 0,
    "CP1133",		"IBM-CP1133", 0,
    "TIS-620",		"TIS620", "TIS620-0", "TIS620.2529-1", "TIS620.2533-0", "TIS620.2533-1", "ISO-IR-166", 0,
    "CP874",		"WINDOWS-874", 0,
    "VISCII",		"VISCII1.1-1", "csVISCII", 0,
    "TCVN",		"TCVN-5712", "TCVN5712-1", "TCVN5712-1:1993", 0,
    "JIS_C6220-1969-RO",	"ISO646-JP", "ISO-IR-14", "JP", "csISO14JISC6220ro", 0,
    "JIS_X0201",	"JISX0201-1976", "X0201", "csHalfWidthKatakana", 0,
    "JIS_X0208",	"JIS_X0208-1983", "JIS_X0208-1990", "JIS0208", "X0208", "ISO-IR-87", "JIS_C6226-1983", "csISO87JISX0208", 0,
    "JIS_X0212",	"JIS_X0212.1990-0", "JIS_X0212-1990", "X0212", "ISO-IR-159", "csISO159JISX02121990", 0,
    "GB_1988-80",	"ISO646-CN", "ISO-IR-57", "CN", "csISO57GB1988", 0,
    "GB_2312-80",	"ISO-IR-58", "csISO58GB231280", "CHINESE", 0,
    "ISO-IR-165",	"CN-GB-ISOIR165", 0,
    "KSC_5601",		"KS_C_5601-1987", "KS_C_5601-1989", "ISO-IR-149", "csKSC56011987", "KOREAN", 0,
    "EUC-JP",		"EUCJP", "Extended_UNIX_Code_Packed_Format_for_Japanese", "csEUCPkdFmtJapanese", 0,
    "SHIFT_JIS",	"SHIFT-JIS", "SJIS", "MS_KANJI", "csShiftJIS", 0,
    "ISO-2022-JP",	"csISO2022JP", 0,
    "ISO-2022-JP-2",	"csISO2022JP2", 0,
    "EUC-CN",		"EUCCN", "GB2312", "CN-GB", "csGB2312", 0,
    "GBK",		"CP936", 0,
    "ISO-2022-CN",	"csISO2022CN", 0,
    "HZ",		"HZ-GB-2312", 0,
    "EUC-TW",		"EUCTW", "csEUCTW", 0,
    "BIG5",		"BIG-5", "BIG-FIVE", "BIGFIVE", "CN-BIG5", "csBig5", 0,
    "BIG5-HKSCS",	"BIG5HKSCS", 0,
    "EUC-KR",		"EUCKR", "csEUCKR", 0,
    "CP949",		"UHC", 0,
    "JOHAB",		"CP1361", 0,

    0
  };

struct lessCase : std::binary_function<char const*, char const*, bool>
{
  bool operator ()(char const* a, char const* b) const {
    return ::strcasecmp(a, b) < 0;
  }
};

class Encoders : public map<char const*, const Tanl::Text::Encoding*, lessCase>
{
public:
  Encoders() {
    // build initial map of encodings
    Encoding const* tend = encodingTable + sizeof(encodingTable)/sizeof(Encoding);
    for (Encoding const* e = encodingTable; e < tend; ++e) {
      (*this)[::strdup(e->name)] = e;
    }
    // add known aliases
    for (char const* const* names = aliasTable; *names; ) {
      char const* name = names[0];
      Encoding const* e = 0;
      const_iterator found = find(name);
      if (found != end())
	e = found->second;
      char const* const* alias = names + 1;
      for (; *alias; ++alias) {
	if (e)
	  (*this)[::strdup(*alias)] = e;
      }
      names = alias + 1;
    }
  }
};

static Encoders& getEncoders()
{
  static Encoders encoders;
  return encoders;
}

} // anon namespace

Encoding const* Encoding::get(char const* name)
{
  Encoders& encoders = getEncoders();
  Encoders::const_iterator found = encoders.find(name);
  return (found == encoders.end()) ? 0 : found->second;
}

Encoding const* Encoding::get(ID id)
{
  Encoders& encoders = getEncoders();
  for (Encoders::const_iterator eit = encoders.begin();
       eit != encoders.end(); ++eit) {
    if (eit->second->id == id)
      return eit->second;
  }
  return 0;
}

//static 
void 
Encoding::Register(Encoding* encoding)
{
  Encoders& e = getEncoders();
  Encoders::iterator eit = e.find(encoding->name);
  if (eit != e.end())
    return;
  encoding->id = e.size();
  e[::strdup(encoding->name)] = encoding;
}

void 
Encoding::Register(char const* alias, char const* canonical)
{
  Encoding const* e = Encoding::get(canonical);
  if (e)
    getEncoders()[::strdup(alias)] = e;
}

size_t Encoding::Encode(Encoding const* from, char const* in, size_t inlen,
			char*& out, size_t outlen) const
{
  char* allocated = 0;
  if (outlen == 0) {
    outlen = size_t(inlen / from->averageBytesPerChar * averageBytesPerChar);
    if (outlen < inlen)
      outlen = inlen;		// be safe
    out = allocated = (char*)malloc(outlen);
  }
  char* outend = out;
  iconv_t converter = iconv_open(name, from->name);

#ifdef _WIN32
  size_t rlen = iconv(converter, &in, &inlen, &outend, &outlen);
#else
  size_t rlen = iconv(converter, (const char **)&in, &inlen, &outend, &outlen);
#endif
  
  iconv_close(converter);
  if (rlen < 0) {
    free(allocated);		// FIXME: increase size
    return 0;
  }
  return outend - out;
}

} // namespace Text
} // namespace Tanl
