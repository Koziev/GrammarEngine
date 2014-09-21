// Таблица соответствия между SGML entities и UNICODE символами.
// ----------------------------------------------------------------------------
//
// CD->29.08.2005
// LC->28.05.2007
// --------------

#include <lem/unicode.h>

using namespace lem;

std::multimap< UCString::hash_type, int/*i_sgml*/ > *lem::CodeConverter::sgml_map = NULL;

#if !defined LEM_UNICODE_EX
CodeConverter::Sgml_Char CodeConverter::sgml_list[8]={
 { "lt",          '<'  },
 { "gt",          '>'  },
 { "amp",         '&'  },
 { "quot",        '"'  },
 { "nbsp",        ' '  },
 { "raquo",       187  },       /* angle quotation mark, right */
 { "laquo",       171  },  /* angle quotation mark, left */
 { "sect",        167  }   /* section sign */
};
#endif


#if defined LEM_UNICODE_EX
CodeConverter::Sgml_Char CodeConverter::sgml_list[921]={

{ "lt",          '<'  },
{ "gt",          '>'  },
{ "amp",         '&'  },
{ "quot",        '"'  },

{ "nbsp",        160  },   /* non-breaking space */

/* ISO-8859-1 entities */
     
{ "iexcl",       161  },   /* inverted exclamation mark */
{ "cent",        162  },   /* cent sign */
{ "pound",       163  },   /* pound sign */
{ "curren",      164  },   /* currency sign */
{ "yen",         165  },   /* yen sign */
{ "brvbar",      166  },   /* broken vertical bar, (brkbar) */
{ "sect",        167  },   /* section sign */
{ "uml",         168  },   /* spacing diaresis */
{ "copy",        169  },   /* copyright sign */
{ "ordf",        170  },   /* feminine ordinal indicator */
{ "laquo",       171  },   /* angle quotation mark, left */
{ "not",         172  },   /* negation sign */
{ "shy",         173  },   /* soft hyphen */
{ "reg",         174  },   /* circled R registered sign */
{ "hibar",       175  },   /* spacing macron */
{ "macr",        175  },   /* spacing macron */
{ "deg",         176  },   /* degree sign */
{ "plusmn", 177  },   /* plus-or-minus sign */
{ "sup2",        178  },   /* superscript 2 */
{ "sup3",        179  },   /* superscript 3 */
{ "acute",  180  },   /* spacing acute (96) */
{ "micro",  181  },   /* micro sign */
{ "para",        182  },   /* paragraph sign */
{ "middot", 183  },   /* middle dot */
{ "cedil",  184  },   /* spacing cedilla */
{ "sup1",        185  },   /* superscript 1 */
{ "ordm",        186  },   /* masculine ordinal indicator */
{ "raquo",  187  },   /* angle quotation mark, right */
{ "frac14", 188  },   /* fraction 1/4 */
{ "frac12", 189  },   /* fraction 1/2 */
{ "frac34", 190  },   /* fraction 3/4 */
{ "iquest", 191  },   /* inverted question mark */
{ "Agrave", 192  },   /* capital A, grave accent */ 
{ "Aacute", 193  },   /* capital A, acute accent */ 
{ "Acirc",  194  },   /* capital A, circumflex accent */ 
{ "Atilde", 195  },   /* capital A, tilde */ 
{ "Auml",        196  },   /* capital A, dieresis or umlaut mark */ 
{ "Aring",  197  },   /* capital A, ring */ 
{ "AElig",  198  },   /* capital AE diphthong (ligature) */ 
{ "Ccedil", 199  },   /* capital C, cedilla */ 
{ "Egrave", 200  },   /* capital E, grave accent */ 
{ "Eacute", 201  },   /* capital E, acute accent */ 
{ "Ecirc",  202  },   /* capital E, circumflex accent */ 
{ "Euml",        203  },   /* capital E, dieresis or umlaut mark */ 
{ "Igrave", 204  },   /* capital I, grave accent */ 
{ "Iacute", 205  },   /* capital I, acute accent */ 
{ "Icirc",  206  },   /* capital I, circumflex accent */ 
{ "Iuml",        207  },   /* capital I, dieresis or umlaut mark */ 
{ "ETH",         208  },   /* capital Eth, Icelandic (Dstrok) */ 
{ "Ntilde", 209  },   /* capital N, tilde */ 
{ "Ograve", 210  },   /* capital O, grave accent */ 
{ "Oacute", 211  },   /* capital O, acute accent */ 
{ "Ocirc",  212  },   /* capital O, circumflex accent */ 
{ "Otilde", 213  },   /* capital O, tilde */ 
{ "Ouml",        214  },   /* capital O, dieresis or umlaut mark */ 
{ "times",  215  },   /* multiplication sign */ 
{ "Oslash", 216  },   /* capital O, slash */ 
{ "Ugrave", 217  },   /* capital U, grave accent */ 
{ "Uacute", 218  },   /* capital U, acute accent */ 
{ "Ucirc",  219  },   /* capital U, circumflex accent */ 
{ "Uuml",        220  },   /* capital U, dieresis or umlaut mark */ 
{ "Yacute", 221  },   /* capital Y, acute accent */ 
{ "THORN",  222  },   /* capital THORN, Icelandic */ 
{ "szlig",  223  },   /* small sharp s, German (sz ligature) */ 
{ "agrave", 224  },   /* small a, grave accent */ 
{ "aacute", 225  },   /* small a, acute accent */ 
{ "acirc",  226  },   /* small a, circumflex accent */ 
{ "atilde", 227  },   /* small a, tilde */
{ "auml",        228  },   /* small a, dieresis or umlaut mark */ 
{ "aring",  229  },   /* small a, ring */
{ "aelig",  230  },   /* small ae diphthong (ligature) */ 
{ "ccedil", 231  },   /* small c, cedilla */ 
{ "egrave", 232  },   /* small e, grave accent */ 
{ "eacute", 233  },   /* small e, acute accent */ 
{ "ecirc",  234  },   /* small e, circumflex accent */ 
{ "euml",        235  },   /* small e, dieresis or umlaut mark */ 
{ "igrave", 236  },   /* small i, grave accent */ 
{ "iacute", 237  },   /* small i, acute accent */ 
{ "icirc",  238  },   /* small i, circumflex accent */ 
{ "iuml",        239  },   /* small i, dieresis or umlaut mark */ 
{ "eth",         240  },   /* small eth, Icelandic */ 
{ "ntilde", 241  },   /* small n, tilde */ 
{ "ograve", 242  },   /* small o, grave accent */ 
{ "oacute", 243  },   /* small o, acute accent */ 
{ "ocirc",  244  },   /* small o, circumflex accent */ 
{ "otilde", 245  },   /* small o, tilde */ 
{ "ouml",        246  },   /* small o, dieresis or umlaut mark */ 
{ "divide", 247  },   /* division sign */
{ "oslash", 248  },   /* small o, slash */ 
{ "ugrave", 249  },   /* small u, grave accent */ 
{ "uacute", 250  },   /* small u, acute accent */ 
{ "ucirc",  251  },   /* small u, circumflex accent */ 
{ "uuml",        252  },   /* small u, dieresis or umlaut mark */ 
{ "yacute", 253  },   /* small y, acute accent */ 
{ "thorn",  254  },   /* small thorn, Icelandic */ 
{ "yuml",        255  },   /* small y, dieresis or umlaut mark */

/* Latin Extended-A */ 

{ "OElig",  338  }, 
{ "oelig",  339  }, 
{ "Scaron", 352  }, 
{ "scaron", 353  }, 
{ "Yuml",        376  }, 


/* Accents */

{ "circ",   0x5e /*710*/  }, /* SPACING CIRCUMFLEX */
{ "tilde",  0x7e /*732*/  }, /* TILDE */

/* Greek */

{ "Alpha",  913  }, 
{ "Beta",        914  }, 
{ "Gamma",  915  },
{ "Delta",  916  }, 
{ "Epsilon",     917  }, 
{ "Zeta",        918  }, 
{ "Eta",         919  }, 
{ "Theta",  920  }, 
{ "Iota",        921  }, 
{ "Kappa",  922  }, 
{ "Mu",          924  }, 
{ "Nu",          925  }, 
{ "Xi",          926  }, 
{ "Omicron",     927  }, 
{ "Pi",          928  }, 
{ "Rho",         929  }, 
{ "Sigma",  931  }, 
{ "Tau",         932  }, 
{ "Upsilon",     933  }, 
{ "Phi",         934  }, 
{ "Chi",         935  }, 
{ "Psi",         936  }, 
{ "Omega",  937  }, 
{ "alpha",  945  }, 
{ "beta",        946  }, 
{ "gamma",  947  }, 
{ "delta",  948  }, 
{ "epsilon",     949  }, 
{ "theta",  952  }, 
{ "omicron",     959  }, 
{ "sigmaf", 962  }, 
{ "upsilon",     965  }, 
{ "phi",         966  }, 
{ "chi",         967  }, 
{ "thetasym",    977  }, 
{ "upsih",  978  }, 


/* Punctuation */

{ "ensp",        8194 },   /* en space */
{ "emsp",        8195 },   /* em space */
{ "zwnj",        8204 },   /* zero width non-joiner */
{ "zwj",         8205 },   /* zero width joiner */
{ "lrm",         8206 },   /* left-to-right mark */
{ "rlm",         8207 },   /* right-to-left mark */
{ "sbquo",  8218 }, 
{ "bdquo",  8222 }, 
{ "dagger", 8224 }, 
{ "Dagger", 8225 }, 
{ "bull",        8226 }, 
{ "Prime",  8243 }, 
{ "lsaquo", 8249 }, 
{ "rsaquo", 8250 }, 
{ "oline",  8254 }, 
{ "frasl",  8260 }, 
{ "euro",        8364 }, 


/* Letter type characters */ 

{ "alefsym",     8501 }, 

/* Arrows */

{ "darr",        8595 }, 
{ "harr",        8596 }, 
{ "crarr",  8629 }, 
{ "dArr",        8659 }, 
{ "hArr",        8660 }, 

/* Math characters */

{ "lowast", 8727 }, 
{ "ang",         8736 }, 
{ "and",         8743 }, 
{ "or",          8744 }, 
{ "cap",         8745 }, 
{ "cup",         8746 }, 
{ "int",         8747 }, 
{ "cong",        8773 }, 
{ "asymp",  8776 }, 

/* Misc tech characters */

{ "clubs",  9827 }, 

/* Added from Unicode obsolete UNI2SGML.TXT */

{ "excl",   0x21 }, /* EXCLAMATION MARK */
{ "num",    0x23 }, /* NUMBER SIGN */ /* FIX? */
{ "dollar", 0x24 }, /* DOLLAR SIGN */
{ "percnt", 0x25 }, /* PERCENT SIGN */
{ "lpar",   0x28 }, /* OPENING PARENTHESIS */
{ "rpar",   0x29 }, /* CLOSING PARENTHESIS */
{ "ast",    0x2a }, /* ASTERISK */
{ "plus",   0x2b }, /* PLUS SIGN */
{ "comma",  0x2c }, /* COMMA */
{ "hyphen", 0x2d }, /* HYPHEN-MINUS */
{ "period", 0x2e }, /* PERIOD */
{ "sol",    0x2f }, /* SLASH */
{ "colon",  0x3a }, /* COLON */
{ "semi",   0x3b }, /* SEMICOLON */
{ "equals", 0x3d }, /* EQUALS SIGN */
{ "quest",  0x3f }, /* QUESTION MARK */
{ "commat", 0x40 }, /* COMMERCIAL AT */
{ "lsqb",   0x5b }, /* OPENING SQUARE BRACKET */
{ "bsol",   0x5c }, /* BACKSLASH */
{ "rsqb",   0x5d }, /* CLOSING SQUARE BRACKET */
{ "lowbar", 0x5f }, /* SPACING UNDERSCORE */
{ "grave",  0x60 }, /* SPACING GRAVE */
{ "lcub",   0x7b }, /* OPENING CURLY BRACKET */
{ "verbar", 0x7c }, /* VERTICAL BAR */
{ "rcub",   0x7d }, /* CLOSING CURLY BRACKET */
{ "die",    0xa8 }, /* SPACING DIAERESIS */
{ "Dot",    0xa8 }, /* SPACING DIAERESIS */
{ "Amacr",  0x100 }, /* LATIN CAPITAL LETTER A MACRON */
{ "amacr",  0x101 }, /* LATIN SMALL LETTER A MACRON */
{ "Abreve", 0x102 }, /* LATIN CAPITAL LETTER A BREVE */
{ "abreve", 0x103 }, /* LATIN SMALL LETTER A BREVE */
{ "Aogon",  0x104 }, /* LATIN CAPITAL LETTER A OGONEK */
{ "aogon",  0x105 }, /* LATIN SMALL LETTER A OGONEK */
{ "Cacute", 0x106 }, /* LATIN CAPITAL LETTER C ACUTE */
{ "cacute", 0x107 }, /* LATIN SMALL LETTER C ACUTE */
{ "Ccirc",  0x108 }, /* LATIN CAPITAL LETTER C CIRCUMFLEX */
{ "ccirc",  0x109 }, /* LATIN SMALL LETTER C CIRCUMFLEX */
{ "Cdot",   0x10a }, /* LATIN CAPITAL LETTER C DOT */
{ "cdot",   0x10b }, /* LATIN SMALL LETTER C DOT */
{ "Ccaron", 0x010C }, /* LATIN CAPITAL LETTER C HACEK */
{ "ccaron", 0x010D }, /* LATIN SMALL LETTER C HACEK */
{ "Dcaron", 0x010E }, /* LATIN CAPITAL LETTER D HACEK */
{ "dcaron", 0x010F }, /* LATIN SMALL LETTER D HACEK */
{ "Dstrok", 0x0110 }, /* LATIN CAPITAL LETTER D BAR */
{ "dstrok", 0x0111 }, /* LATIN SMALL LETTER D BAR */
{ "Emacr",  0x0112 }, /* LATIN CAPITAL LETTER E MACRON */
{ "emacr",  0x0113 }, /* LATIN SMALL LETTER E MACRON */
{ "Edot",   0x0116 }, /* LATIN CAPITAL LETTER E DOT */
{ "edot",   0x0117 }, /* LATIN SMALL LETTER E DOT */
{ "Eogon",  0x0118 }, /* LATIN CAPITAL LETTER E OGONEK */
{ "eogon",  0x0119 }, /* LATIN SMALL LETTER E OGONEK */
{ "Ecaron", 0x011A }, /* LATIN CAPITAL LETTER E HACEK */
{ "ecaron", 0x011B }, /* LATIN SMALL LETTER E HACEK */
{ "Gcirc",  0x011C }, /* LATIN CAPITAL LETTER G CIRCUMFLEX */
{ "gcirc",  0x011D }, /* LATIN SMALL LETTER G CIRCUMFLEX */
{ "Gbreve", 0x011E }, /* LATIN CAPITAL LETTER G BREVE */
{ "gbreve", 0x011F }, /* LATIN SMALL LETTER G BREVE */
{ "Gdot",   0x0120 }, /* LATIN CAPITAL LETTER G DOT */
{ "gdot",   0x0121 }, /* LATIN SMALL LETTER G DOT */
{ "Gcedil", 0x0122 }, /* LATIN CAPITAL LETTER G CEDILLA */
{ "gcedil", 0x0123 }, /* LATIN SMALL LETTER G CEDILLA */
{ "Hcirc",  0x0124 }, /* LATIN CAPITAL LETTER H CIRCUMFLEX */
{ "hcirc",  0x0125 }, /* LATIN SMALL LETTER H CIRCUMFLEX */
{ "Hstrok", 0x0126 }, /* LATIN CAPITAL LETTER H BAR */
{ "hstrok", 0x0127 }, /* LATIN SMALL LETTER H BAR */
{ "Itilde", 0x0128 }, /* LATIN CAPITAL LETTER I TILDE */
{ "itilde", 0x0129 }, /* LATIN SMALL LETTER I TILDE */
{ "Imacr",  0x012A }, /* LATIN CAPITAL LETTER I MACRON */
{ "imacr",  0x012B }, /* LATIN SMALL LETTER I MACRON */
{ "Iogon",  0x012E }, /* LATIN CAPITAL LETTER I OGONEK */
{ "iogon",  0x012F }, /* LATIN SMALL LETTER I OGONEK */
{ "Idot",   0x0130 }, /* LATIN CAPITAL LETTER I DOT */
{ "inodot", 0x0131 }, /* LATIN SMALL LETTER DOTLESS I */
{ "IJlig",  0x0132 }, /* LATIN CAPITAL LETTER I J */
{ "ijlig",  0x0133 }, /* LATIN SMALL LETTER I J */
{ "Jcirc",  0x0134 }, /* LATIN CAPITAL LETTER J CIRCUMFLEX */
{ "jcirc",  0x0135 }, /* LATIN SMALL LETTER J CIRCUMFLEX */
{ "Kcedil", 0x0136 }, /* LATIN CAPITAL LETTER K CEDILLA */
{ "kcedil", 0x0137 }, /* LATIN SMALL LETTER K CEDILLA */
{ "kgreen", 0x0138 }, /* LATIN SMALL LETTER KRA */
{ "Lacute", 0x0139 }, /* LATIN CAPITAL LETTER L ACUTE */
{ "lacute", 0x013A }, /* LATIN SMALL LETTER L ACUTE */
{ "Lcedil", 0x013B }, /* LATIN CAPITAL LETTER L CEDILLA */
{ "lcedil", 0x013C }, /* LATIN SMALL LETTER L CEDILLA */
{ "Lcaron", 0x013D }, /* LATIN CAPITAL LETTER L HACEK */
{ "lcaron", 0x013E }, /* LATIN SMALL LETTER L HACEK */
{ "Lmidot", 0x013F }, /* LATIN CAPITAL LETTER L WITH MIDDLE DOT */
{ "lmidot", 0x0140 }, /* LATIN SMALL LETTER L WITH MIDDLE DOT */
{ "Lstrok", 0x0141 }, /* LATIN CAPITAL LETTER L SLASH */
{ "lstrok", 0x0142 }, /* LATIN SMALL LETTER L SLASH */
{ "Nacute", 0x0143 }, /* LATIN CAPITAL LETTER N ACUTE */
{ "nacute", 0x0144 }, /* LATIN SMALL LETTER N ACUTE */
{ "Ncedil", 0x0145 }, /* LATIN CAPITAL LETTER N CEDILLA */
{ "ncedil", 0x0146 }, /* LATIN SMALL LETTER N CEDILLA */
{ "Ncaron", 0x0147 }, /* LATIN CAPITAL LETTER N HACEK */
{ "ncaron", 0x0148 }, /* LATIN SMALL LETTER N HACEK */
{ "napos",  0x0149 }, /* LATIN SMALL LETTER APOSTROPHE N */
{ "ENG",    0x014A }, /* LATIN CAPITAL LETTER ENG */
{ "eng",    0x014B }, /* LATIN SMALL LETTER ENG */
{ "Omacr",  0x014C }, /* LATIN CAPITAL LETTER O MACRON */
{ "omacr",  0x014D }, /* LATIN SMALL LETTER O MACRON */
{ "Odblac", 0x0150 }, /* LATIN CAPITAL LETTER O DOUBLE ACUTE */
{ "odblac", 0x0151 }, /* LATIN SMALL LETTER O DOUBLE ACUTE */
{ "Racute", 0x0154 }, /* LATIN CAPITAL LETTER R ACUTE */
{ "racute", 0x0155 }, /* LATIN SMALL LETTER R ACUTE */
{ "Rcedil", 0x0156 }, /* LATIN CAPITAL LETTER R CEDILLA */
{ "rcedil", 0x0157 }, /* LATIN SMALL LETTER R CEDILLA */
{ "Rcaron", 0x0158 }, /* LATIN CAPITAL LETTER R HACEK */
{ "rcaron", 0x0159 }, /* LATIN SMALL LETTER R HACEK */
{ "Sacute", 0x015A }, /* LATIN CAPITAL LETTER S ACUTE */
{ "sacute", 0x015B }, /* LATIN SMALL LETTER S ACUTE */
{ "Scirc",  0x015C }, /* LATIN CAPITAL LETTER S CIRCUMFLEX */
{ "scirc",  0x015D }, /* LATIN SMALL LETTER S CIRCUMFLEX */
{ "Scedil", 0x015E }, /* LATIN CAPITAL LETTER S CEDILLA */
{ "scedil", 0x015F }, /* LATIN SMALL LETTER S CEDILLA */
{ "Tcedil", 0x0162 }, /* LATIN CAPITAL LETTER T CEDILLA */
{ "tcedil", 0x0163 }, /* LATIN SMALL LETTER T CEDILLA */
{ "Tcaron", 0x0164 }, /* LATIN CAPITAL LETTER T HACEK */
{ "tcaron", 0x0165 }, /* LATIN SMALL LETTER T HACEK */
{ "Tstrok", 0x0166 }, /* LATIN CAPITAL LETTER T BAR */
{ "tstrok", 0x0167 }, /* LATIN SMALL LETTER T BAR */
{ "Utilde", 0x0168 }, /* LATIN CAPITAL LETTER U TILDE */
{ "utilde", 0x0169 }, /* LATIN SMALL LETTER U TILDE */
{ "Umacr",  0x016A }, /* LATIN CAPITAL LETTER U MACRON */
{ "umacr",  0x016B }, /* LATIN SMALL LETTER U MACRON */
{ "Ubreve", 0x016C }, /* LATIN CAPITAL LETTER U BREVE */
{ "ubreve", 0x016D }, /* LATIN SMALL LETTER U BREVE */
{ "Uring",  0x016E }, /* LATIN CAPITAL LETTER U RING */
{ "uring",  0x016F }, /* LATIN SMALL LETTER U RING */
{ "Udblac", 0x0170 }, /* LATIN CAPITAL LETTER U DOUBLE ACUTE */
{ "udblac", 0x0171 }, /* LATIN SMALL LETTER U DOUBLE ACUTE */
{ "Uogon",  0x0172 }, /* LATIN CAPITAL LETTER U OGONEK */
{ "uogon",  0x0173 }, /* LATIN SMALL LETTER U OGONEK */
{ "Wcirc",  0x0174 }, /* LATIN CAPITAL LETTER W CIRCUMFLEX */
{ "wcirc",  0x0175 }, /* LATIN SMALL LETTER W CIRCUMFLEX */
{ "Ycirc",  0x0176 }, /* LATIN CAPITAL LETTER Y CIRCUMFLEX */
{ "ycirc",  0x0177 }, /* LATIN SMALL LETTER Y CIRCUMFLEX */
{ "Zacute", 0x0179 }, /* LATIN CAPITAL LETTER Z ACUTE */
{ "zacute", 0x017A }, /* LATIN SMALL LETTER Z ACUTE */
{ "Zdot",   0x017B }, /* LATIN CAPITAL LETTER Z DOT */
{ "zdot",   0x017C }, /* LATIN SMALL LETTER Z DOT */
{ "Zcaron", 0x017D }, /* LATIN CAPITAL LETTER Z HACEK */
{ "zcaron", 0x017E }, /* LATIN SMALL LETTER Z HACEK */
{ "fnof",   0x0192 }, /* LATIN SMALL LETTER SCRIPT F */
{ "apos",   0x02BC }, /* MODIFIER LETTER APOSTROPHE */
{ "caron",  0x02C7 }, /* MODIFIER LETTER HACEK */
{ "breve",  0x02D8 }, /* SPACING BREVE */
{ "dot",    0x02D9 }, /* SPACING DOT ABOVE */
{ "ring",   0x02DA }, /* SPACING RING ABOVE */
{ "ogon",   0x02DB }, /* SPACING OGONEK */
{ "tilde",  0x02DC }, /* SPACING TILDE */
{ "dblac",  0x02DD }, /* SPACING DOUBLE ACUTE */
{ "Aacgr",  0x0386 }, /* GREEK CAPITAL LETTER ALPHA TONOS */
{ "Eacgr",  0x0388 }, /* GREEK CAPITAL LETTER EPSILON TONOS */
{ "EEacgr", 0x0389 }, /* GREEK CAPITAL LETTER ETA TONOS */
{ "Iacgr",  0x038A }, /* GREEK CAPITAL LETTER IOTA TONOS */
{ "Oacgr",  0x038C }, /* GREEK CAPITAL LETTER OMICRON TONOS */
{ "Uacgr",  0x038E }, /* GREEK CAPITAL LETTER UPSILON TONOS */
{ "OHacgr", 0x038F }, /* GREEK CAPITAL LETTER OMEGA TONOS */
{ "idiagr", 0x0390 }, /* GREEK SMALL LETTER IOTA DIAERESIS TONOS */
{ "Agr",    0x0391 }, /* GREEK CAPITAL LETTER ALPHA */
{ "Bgr",    0x0392 }, /* GREEK CAPITAL LETTER BETA */
{ "Ggr",    0x0393 }, /* GREEK CAPITAL LETTER GAMMA */
{ "Dgr",    0x0394 }, /* GREEK CAPITAL LETTER DELTA */
{ "Egr",    0x0395 }, /* GREEK CAPITAL LETTER EPSILON */
{ "Zgr",    0x0396 }, /* GREEK CAPITAL LETTER ZETA */
{ "EEgr",   0x0397 }, /* GREEK CAPITAL LETTER ETA */
{ "THgr",   0x0398 }, /* GREEK CAPITAL LETTER THETA */
{ "Igr",    0x0399 }, /* GREEK CAPITAL LETTER IOTA */
{ "Kgr",    0x039A }, /* GREEK CAPITAL LETTER KAPPA */
{ "Lgr",    0x039B }, /* GREEK CAPITAL LETTER LAMBDA */
{ "Lambda", 0x039B }, /* GREEK CAPITAL LETTER LAMBDA */
{ "Mgr",    0x039C }, /* GREEK CAPITAL LETTER MU */
{ "Ngr",    0x039D }, /* GREEK CAPITAL LETTER NU */
{ "Xgr",    0x039E }, /* GREEK CAPITAL LETTER XI */
{ "Ogr",    0x039F }, /* GREEK CAPITAL LETTER OMICRON */
{ "Pgr",    0x03A0 }, /* GREEK CAPITAL LETTER PI */
{ "Rgr",    0x03A1 }, /* GREEK CAPITAL LETTER RHO */
{ "Sgr",    0x03A3 }, /* GREEK CAPITAL LETTER SIGMA */
{ "Tgr",    0x03A4 }, /* GREEK CAPITAL LETTER TAU */
{ "Ugr",    0x03A5 }, /* GREEK CAPITAL LETTER UPSILON */
{ "Upsi",   0x03A5 }, /* GREEK CAPITAL LETTER UPSILON */
{ "PHgr",   0x03A6 }, /* GREEK CAPITAL LETTER PHI */
{ "KHgr",   0x03A7 }, /* GREEK CAPITAL LETTER CHI */
{ "PSgr",   0x03A8 }, /* GREEK CAPITAL LETTER PSI */
{ "OHgr",   0x03A9 }, /* GREEK CAPITAL LETTER OMEGA */
{ "Idigr",  0x03AA }, /* GREEK CAPITAL LETTER IOTA DIAERESIS */
{ "Udigr",  0x03AB }, /* GREEK CAPITAL LETTER UPSILON DIAERESIS */
{ "aacgr",  0x03AC }, /* GREEK SMALL LETTER ALPHA TONOS */
{ "eacgr",  0x03AD }, /* GREEK SMALL LETTER EPSILON TONOS */
{ "eeacgr", 0x03AE }, /* GREEK SMALL LETTER ETA TONOS */
{ "iacgr",  0x03AF }, /* GREEK SMALL LETTER IOTA TONOS */
{ "udiagr", 0x03B0 }, /* GREEK SMALL LETTER UPSILON DIAERESIS TONOS */
{ "agr",    0x03B1 }, /* GREEK SMALL LETTER ALPHA */
{ "bgr",    0x03B2 }, /* GREEK SMALL LETTER BETA */
{ "ggr",    0x03B3 }, /* GREEK SMALL LETTER GAMMA */
{ "dgr",    0x03B4 }, /* GREEK SMALL LETTER DELTA */
{ "egr",    0x03B5 }, /* GREEK SMALL LETTER EPSILON */
{ "epsi",   0x03B5 }, /* GREEK SMALL LETTER EPSILON */
{ "zgr",    0x03B6 }, /* GREEK SMALL LETTER ZETA */
{ "zeta",   0x03B6 }, /* GREEK SMALL LETTER ZETA */
{ "eegr",   0x03B7 }, /* GREEK SMALL LETTER ETA */
{ "eta",    0x03B7 }, /* GREEK SMALL LETTER ETA */
{ "thetas", 0x03B8 }, /* GREEK SMALL LETTER THETA */
{ "thgr",   0x03B8 }, /* GREEK SMALL LETTER THETA */
{ "igr",    0x03B9 }, /* GREEK SMALL LETTER IOTA */
{ "iota",   0x03B9 }, /* GREEK SMALL LETTER IOTA */
{ "kgr",    0x03BA }, /* GREEK SMALL LETTER KAPPA */
{ "kappa",  0x03BA }, /* GREEK SMALL LETTER KAPPA */
{ "lgr",    0x03BB }, /* GREEK SMALL LETTER LAMBDA */
{ "lambda", 0x03BB }, /* GREEK SMALL LETTER LAMBDA */
{ "mgr",    0x03BC }, /* GREEK SMALL LETTER MU */
{ "mu",     0x03BC }, /* GREEK SMALL LETTER MU */
{ "ngr",    0x03BD }, /* GREEK SMALL LETTER NU */
{ "nu",     0x03BD }, /* GREEK SMALL LETTER NU */
{ "xgr",    0x03BE }, /* GREEK SMALL LETTER XI */
{ "xi",     0x03BE }, /* GREEK SMALL LETTER XI */
{ "ogr",    0x03BF }, /* GREEK SMALL LETTER OMICRON */
{ "pgr",    0x03C0 }, /* GREEK SMALL LETTER PI */
{ "pi",     0x03C0 }, /* GREEK SMALL LETTER PI */
{ "rgr",    0x03C1 }, /* GREEK SMALL LETTER RHO */
{ "rho",    0x03C1 }, /* GREEK SMALL LETTER RHO */
{ "sfgr",   0x03C2 }, /* GREEK SMALL LETTER FINAL SIGMA */
{ "sigmav", 0x03C2 }, /* GREEK SMALL LETTER FINAL SIGMA */
{ "sgr",    0x03C3 }, /* GREEK SMALL LETTER SIGMA */
{ "sigma",  0x03C3 }, /* GREEK SMALL LETTER SIGMA */
{ "tgr",    0x03C4 }, /* GREEK SMALL LETTER TAU */
{ "tau",    0x03C4 }, /* GREEK SMALL LETTER TAU */
{ "ugr",    0x03C5 }, /* GREEK SMALL LETTER UPSILON */
{ "upsi",   0x03C5 }, /* GREEK SMALL LETTER UPSILON */
{ "phgr",   0x03C6 }, /* GREEK SMALL LETTER PHI */
{ "phis",   0x03C6 }, /* GREEK SMALL LETTER PHI */
{ "khgr",   0x03C7 }, /* GREEK SMALL LETTER CHI */
{ "psgr",   0x03C8 }, /* GREEK SMALL LETTER PSI */
{ "psi",    0x03C8 }, /* GREEK SMALL LETTER PSI */
{ "ohgr",   0x03C9 }, /* GREEK SMALL LETTER OMEGA */
{ "omega",  0x03C9 }, /* GREEK SMALL LETTER OMEGA */
{ "idigr",  0x03CA }, /* GREEK SMALL LETTER IOTA DIAERESIS */
{ "udigr",  0x03CB }, /* GREEK SMALL LETTER UPSILON DIAERESIS */
{ "oacgr",  0x03CC }, /* GREEK SMALL LETTER OMICRON TONOS */
{ "uacgr",  0x03CD }, /* GREEK SMALL LETTER UPSILON TONOS */
{ "ohacgr", 0x03CE }, /* GREEK SMALL LETTER OMEGA TONOS */
{ "thetav", 0x03D1 }, /* GREEK SMALL LETTER SCRIPT THETA */
{ "phiv",   0x03D5 }, /* GREEK SMALL LETTER SCRIPT PHI */
{ "piv",    0x03D6 }, /* GREEK SMALL LETTER OMEGA PI */
{ "gammad", 0x03DD }, /* GREEK SMALL LETTER DIGAMMA */
{ "kappav", 0x03F0 }, /* GREEK SMALL LETTER SCRIPT KAPPA */
{ "rhov",   0x03F1 }, /* GREEK SMALL LETTER TAILED RHO */
{ "IOcy",   0x0401 }, /* CYRILLIC CAPITAL LETTER IO */
{ "DJcy",   0x0402 }, /* CYRILLIC CAPITAL LETTER DJE */
{ "GJcy",   0x0403 }, /* CYRILLIC CAPITAL LETTER GJE */
{ "Jukcy",  0x0404 }, /* CYRILLIC CAPITAL LETTER E */
{ "DScy",   0x0405 }, /* CYRILLIC CAPITAL LETTER DZE */
{ "Iukcy",  0x0406 }, /* CYRILLIC CAPITAL LETTER I */
{ "YIcy",   0x0407 }, /* CYRILLIC CAPITAL LETTER YI */
{ "Jsercy", 0x0408 }, /* CYRILLIC CAPITAL LETTER JE */
{ "LJcy",   0x0409 }, /* CYRILLIC CAPITAL LETTER LJE */
{ "NJcy",   0x040A }, /* CYRILLIC CAPITAL LETTER NJE */
{ "TSHcy",  0x040B }, /* CYRILLIC CAPITAL LETTER TSHE */
{ "KJcy",   0x040C }, /* CYRILLIC CAPITAL LETTER KJE */
{ "Ubrcy",  0x040E }, /* CYRILLIC CAPITAL LETTER SHORT U */
{ "DZcy",   0x040F }, /* CYRILLIC CAPITAL LETTER DZHE */
{ "Acy",    0x0410 }, /* CYRILLIC CAPITAL LETTER A */
{ "Bcy",    0x0411 }, /* CYRILLIC CAPITAL LETTER BE */
{ "Vcy",    0x0412 }, /* CYRILLIC CAPITAL LETTER VE */
{ "Gcy",    0x0413 }, /* CYRILLIC CAPITAL LETTER GE */
{ "Dcy",    0x0414 }, /* CYRILLIC CAPITAL LETTER DE */
{ "IEcy",   0x0415 }, /* CYRILLIC CAPITAL LETTER IE */
{ "ZHcy",   0x0416 }, /* CYRILLIC CAPITAL LETTER ZHE */
{ "Zcy",    0x0417 }, /* CYRILLIC CAPITAL LETTER ZE */
{ "Icy",    0x0418 }, /* CYRILLIC CAPITAL LETTER II */
{ "Jcy",    0x0419 }, /* CYRILLIC CAPITAL LETTER SHORT II */
{ "Kcy",    0x041A }, /* CYRILLIC CAPITAL LETTER KA */
{ "Lcy",    0x041B }, /* CYRILLIC CAPITAL LETTER EL */
{ "Mcy",    0x041C }, /* CYRILLIC CAPITAL LETTER EM */
{ "Ncy",    0x041D }, /* CYRILLIC CAPITAL LETTER EN */
{ "Ocy",    0x041E }, /* CYRILLIC CAPITAL LETTER O */
{ "Pcy",    0x041F }, /* CYRILLIC CAPITAL LETTER PE */
{ "Rcy",    0x0420 }, /* CYRILLIC CAPITAL LETTER ER */
{ "Scy",    0x0421 }, /* CYRILLIC CAPITAL LETTER ES */
{ "Tcy",    0x0422 }, /* CYRILLIC CAPITAL LETTER TE */
{ "Ucy",    0x0423 }, /* CYRILLIC CAPITAL LETTER U */
{ "Fcy",    0x0424 }, /* CYRILLIC CAPITAL LETTER EF */
{ "KHcy",   0x0425 }, /* CYRILLIC CAPITAL LETTER KHA */
{ "TScy",   0x0426 }, /* CYRILLIC CAPITAL LETTER TSE */
{ "CHcy",   0x0427 }, /* CYRILLIC CAPITAL LETTER CHE */
{ "SHcy",   0x0428 }, /* CYRILLIC CAPITAL LETTER SHA */
{ "SHCHcy", 0x0429 }, /* CYRILLIC CAPITAL LETTER SHCHA */
{ "HARDcy", 0x042A }, /* CYRILLIC CAPITAL LETTER HARD SIGN */
{ "Ycy",    0x042B }, /* CYRILLIC CAPITAL LETTER YERI */
{ "SOFTcy", 0x042C }, /* CYRILLIC CAPITAL LETTER SOFT SIGN */
{ "Ecy",    0x042D }, /* CYRILLIC CAPITAL LETTER REVERSED E */
{ "YUcy",   0x042E }, /* CYRILLIC CAPITAL LETTER IU */
{ "YAcy",   0x042F }, /* CYRILLIC CAPITAL LETTER IA */
{ "acy",    0x0430 }, /* CYRILLIC SMALL LETTER A */
{ "bcy",    0x0431 }, /* CYRILLIC SMALL LETTER BE */
{ "vcy",    0x0432 }, /* CYRILLIC SMALL LETTER VE */
{ "gcy",    0x0433 }, /* CYRILLIC SMALL LETTER GE */
{ "dcy",    0x0434 }, /* CYRILLIC SMALL LETTER DE */
{ "iecy",   0x0435 }, /* CYRILLIC SMALL LETTER IE */
{ "zhcy",   0x0436 }, /* CYRILLIC SMALL LETTER ZHE */
{ "zcy",    0x0437 }, /* CYRILLIC SMALL LETTER ZE */
{ "icy",    0x0438 }, /* CYRILLIC SMALL LETTER II */
{ "jcy",    0x0439 }, /* CYRILLIC SMALL LETTER SHORT II */
{ "kcy",    0x043A }, /* CYRILLIC SMALL LETTER KA */
{ "lcy",    0x043B }, /* CYRILLIC SMALL LETTER EL */
{ "mcy",    0x043C }, /* CYRILLIC SMALL LETTER EM */
{ "ncy",    0x043D }, /* CYRILLIC SMALL LETTER EN */
{ "ocy",    0x043E }, /* CYRILLIC SMALL LETTER O */
{ "pcy",    0x043F }, /* CYRILLIC SMALL LETTER PE */
{ "rcy",    0x0440 }, /* CYRILLIC SMALL LETTER ER */
{ "scy",    0x0441 }, /* CYRILLIC SMALL LETTER ES */
{ "tcy",    0x0442 }, /* CYRILLIC SMALL LETTER TE */
{ "ucy",    0x0443 }, /* CYRILLIC SMALL LETTER U */
{ "fcy",    0x0444 }, /* CYRILLIC SMALL LETTER EF */
{ "khcy",   0x0445 }, /* CYRILLIC SMALL LETTER KHA */
{ "tscy",   0x0446 }, /* CYRILLIC SMALL LETTER TSE */
{ "chcy",   0x0447 }, /* CYRILLIC SMALL LETTER CHE */
{ "shcy",   0x0448 }, /* CYRILLIC SMALL LETTER SHA */
{ "shchcy", 0x0449 }, /* CYRILLIC SMALL LETTER SHCHA */
{ "hardcy", 0x044A }, /* CYRILLIC SMALL LETTER HARD SIGN */
{ "ycy",    0x044B }, /* CYRILLIC SMALL LETTER YERI */
{ "softcy", 0x044C }, /* CYRILLIC SMALL LETTER SOFT SIGN */
{ "ecy",    0x044D }, /* CYRILLIC SMALL LETTER REVERSED E */
{ "yucy",   0x044E }, /* CYRILLIC SMALL LETTER IU */
{ "yacy",   0x044F }, /* CYRILLIC SMALL LETTER IA */
{ "iocy",   0x0451 }, /* CYRILLIC SMALL LETTER IO */
{ "djcy",   0x0452 }, /* CYRILLIC SMALL LETTER DJE */
{ "gjcy",   0x0453 }, /* CYRILLIC SMALL LETTER GJE */
{ "jukcy",  0x0454 }, /* CYRILLIC SMALL LETTER E */
{ "dscy",   0x0455 }, /* CYRILLIC SMALL LETTER DZE */
{ "iukcy",  0x0456 }, /* CYRILLIC SMALL LETTER I */
{ "yicy",   0x0457 }, /* CYRILLIC SMALL LETTER YI */
{ "jsercy", 0x0458 }, /* CYRILLIC SMALL LETTER JE */
{ "ljcy",   0x0459 }, /* CYRILLIC SMALL LETTER LJE */
{ "njcy",   0x045A }, /* CYRILLIC SMALL LETTER NJE */
{ "tshcy",  0x045B }, /* CYRILLIC SMALL LETTER TSHE */
{ "kjcy",   0x045C }, /* CYRILLIC SMALL LETTER KJE */
{ "ubrcy",  0x045E }, /* CYRILLIC SMALL LETTER SHORT U */
{ "dzcy",   0x045F }, /* CYRILLIC SMALL LETTER DZHE */
{ "emsp13", 0x2004 }, /* THREE-PER-EM SPACE */
{ "emsp14", 0x2005 }, /* FOUR-PER-EM SPACE */
{ "numsp",  0x2007 }, /* FIGURE SPACE */
{ "puncsp", 0x2008 }, /* PUNCTUATION SPACE */
{ "thinsp", 0x2009 }, /* THIN SPACE */
{ "hairsp", 0x200A }, /* HAIR SPACE */
{ "dash",   0x2010 }, /* HYPHEN */
{ "ndash",  0x2013 }, /* EN DASH */
{ "mdash",  0x2014 }, /* EM DASH */
{ "horbar", 0x2015 }, /* QUOTATION DASH */
{ "Verbar", 0x2016 }, /* DOUBLE VERTICAL BAR */
{ "lsquo",  0x2018 }, /* SINGLE TURNED COMMA QUOTATION MARK */
{ "rsquor", 0x2018 }, /* SINGLE TURNED COMMA QUOTATION MARK */
{ "rsquo",  0x2019 }, /* SINGLE COMMA QUOTATION MARK */
{ "lsquor", 0x201A }, /* LOW SINGLE COMMA QUOTATION MARK */
{ "ldquo",  0x201C }, /* DOUBLE TURNED COMMA QUOTATION MARK */
{ "rdquor", 0x201C }, /* DOUBLE TURNED COMMA QUOTATION MARK */
{ "rdquo",  0x201D }, /* DOUBLE COMMA QUOTATION MARK */
{ "ldquor", 0x201E }, /* LOW DOUBLE COMMA QUOTATION MARK */
{ "nldr",   0x2025 }, /* TWO DOT LEADER */
{ "hellip", 0x2026 }, /* HORIZONTAL ELLIPSIS */
{ "mldr",   0x2026 }, /* HORIZONTAL ELLIPSIS */
{ "permil", 0x2030 }, /* PER MILLE SIGN */
{ "prime",  0x2032 }, /* PRIME */
{ "vprime", 0x2032 }, /* PRIME */
{ "tprime", 0x2034 }, /* TRIPLE PRIME */
{ "bprime", 0x2035 }, /* REVERSED PRIME */
{ "caret",  0x2041 }, /* CARET INSERTION POINT */
{ "hybull", 0x2043 }, /* HYPHEN BULLET */
{ "tdot",   0x20DB }, /* NON-SPACING THREE DOTS ABOVE */
{ "DotDot", 0x20DC }, /* NON-SPACING FOUR DOTS ABOVE */
{ "incare", 0x2105 }, /* CARE OF */
{ "hamilt", 0x210B }, /* SCRIPT H */
{ "planck", 0x210F }, /* PLANCK CONSTANT OVER 2 PI */
{ "image",  0x2111 }, /* BLACK-LETTER I */
{ "lagran", 0x2112 }, /* SCRIPT L */
{ "ell",    0x2113 }, /* SCRIPT SMALL L */
{ "numero", 0x2116 }, /* NUMERO */
{ "copysr", 0x2117 }, /* SOUND RECORDING COPYRIGHT */
{ "weierp", 0x2118 }, /* SCRIPT P */
{ "real",   0x211C }, /* BLACK-LETTER R */
{ "rx",     0x211E }, /* PRESCRIPTION TAKE */
{ "trade",  0x2122 }, /* TRADEMARK */
{ "ohm",    0x2126 }, /* OHM */
{ "angst",  0x212B }, /* ANGSTROM UNIT */
{ "bernou", 0x212C }, /* SCRIPT B */
{ "phmmat", 0x2133 }, /* SCRIPT M */
{ "order",  0x2134 }, /* SCRIPT SMALL O */
{ "aleph",  0x2135 }, /* FIRST TRANSFINITE CARDINAL */
{ "beth",   0x2136 }, /* SECOND TRANSFINITE CARDINAL */
{ "gimel",  0x2137 }, /* THIRD TRANSFINITE CARDINAL */
{ "daleth", 0x2138 }, /* FOURTH TRANSFINITE CARDINAL */
{ "frac13", 0x2153 }, /* FRACTION ONE THIRD */
{ "frac23", 0x2154 }, /* FRACTION TWO THIRDS */
{ "frac15", 0x2155 }, /* FRACTION ONE FIFTH */
{ "frac25", 0x2156 }, /* FRACTION TWO FIFTHS */
{ "frac35", 0x2157 }, /* FRACTION THREE FIFTHS */
{ "frac45", 0x2158 }, /* FRACTION FOUR FIFTHS */
{ "frac16", 0x2159 }, /* FRACTION ONE SIXTH */
{ "frac56", 0x215A }, /* FRACTION FIVE SIXTHS */
{ "frac18", 0x215B }, /* FRACTION ONE EIGHTH */
{ "frac38", 0x215C }, /* FRACTION THREE EIGHTHS */
{ "frac58", 0x215D }, /* FRACTION FIVE EIGHTHS */
{ "frac78", 0x215E }, /* FRACTION SEVEN EIGHTHS */
{ "larr",   0x2190 }, /* LEFT ARROW */
{ "uarr",   0x2191 }, /* UP ARROW */
{ "rarr",   0x2192 }, /* RIGHT ARROW */
{ "varr",   0x2195 }, /* UP DOWN ARROW */
{ "nwarr",  0x2196 }, /* UPPER LEFT ARROW */
{ "nearr",  0x2197 }, /* UPPER RIGHT ARROW */
{ "drarr",  0x2198 }, /* LOWER RIGHT ARROW */
{ "dlarr",  0x2199 }, /* LOWER LEFT ARROW */
{ "nlarr",  0x219A }, /* LEFT ARROW WITH STROKE */
{ "nrarr",  0x219B }, /* RIGHT ARROW WITH STROKE */
{ "rarrw",  0x219D }, /* RIGHT WAVE ARROW */
{ "Larr",   0x219E }, /* LEFT TWO HEADED ARROW */
{ "Rarr",   0x21A0 }, /* RIGHT TWO HEADED ARROW */
{ "larrtl", 0x21A2 }, /* LEFT ARROW WITH TAIL */
{ "rarrtl", 0x21A3 }, /* RIGHT ARROW WITH TAIL */
{ "map",    0x21A6 }, /* RIGHT ARROW FROM BAR */
{ "larrhk", 0x21A9 }, /* LEFT ARROW WITH HOOK */
{ "rarrhk", 0x21AA }, /* RIGHT ARROW WITH HOOK */
{ "larrlp", 0x21AB }, /* LEFT ARROW WITH LOOP */
{ "rarrlp", 0x21AC }, /* RIGHT ARROW WITH LOOP */
{ "harrw",  0x21AD }, /* LEFT RIGHT WAVE ARROW */
{ "nharr",  0x21AE }, /* LEFT RIGHT ARROW WITH STROKE */
{ "lsh",    0x21B0 }, /* UP ARROW WITH TIP LEFT */
{ "rsh",    0x21B1 }, /* UP ARROW WITH TIP RIGHT */
{ "cularr", 0x21B6 }, /* ANTICLOCKWISE TOP SEMICIRCLE ARROW */
{ "curarr", 0x21B7 }, /* CLOCKWISE TOP SEMICIRCLE ARROW */
{ "olarr",  0x21BA }, /* ANTICLOCKWISE OPEN CIRCLE ARROW */
{ "orarr",  0x21BB }, /* CLOCKWISE OPEN CIRCLE ARROW */
{ "lharu",  0x21BC }, /* LEFT HARPOON WITH BARB UP */
{ "lhard",  0x21BD }, /* LEFT HARPOON WITH BARB DOWN */
{ "uharr",  0x21BE }, /* UP HARPOON WITH BARB RIGHT */
{ "uharl",  0x21BF }, /* UP HARPOON WITH BARB LEFT */
{ "rharu",  0x21C0 }, /* RIGHT HARPOON WITH BARB UP */
{ "rhard",  0x21C1 }, /* RIGHT HARPOON WITH BARB DOWN */
{ "dharr",  0x21C2 }, /* DOWN HARPOON WITH BARB RIGHT */
{ "dharl",  0x21C3 }, /* DOWN HARPOON WITH BARB LEFT */
{ "rlarr2", 0x21C4 }, /* RIGHT ARROW OVER LEFT ARROW */
{ "lrarr2", 0x21C6 }, /* LEFT ARROW OVER RIGHT ARROW */
{ "larr2",  0x21C7 }, /* LEFT PAIRED ARROWS */
{ "uarr2",  0x21C8 }, /* UP PAIRED ARROWS */
{ "rarr2",  0x21C9 }, /* RIGHT PAIRED ARROWS */
{ "darr2",  0x21CA }, /* DOWN PAIRED ARROWS */
{ "lrhar2", 0x21CB }, /* LEFT HARPOON OVER RIGHT HARPOON */
{ "rlhar2", 0x21CC }, /* RIGHT HARPOON OVER LEFT HARPOON */
{ "nlArr",  0x21CD }, /* LEFT DOUBLE ARROW WITH STROKE */
{ "nhArr",  0x21CE }, /* LEFT RIGHT DOUBLE ARROW WITH STROKE */
{ "nrArr",  0x21CF }, /* RIGHT DOUBLE ARROW WITH STROKE */
{ "lArr",   0x21D0 }, /* LEFT DOUBLE ARROW */
{ "uArr",   0x21D1 }, /* UP DOUBLE ARROW */
{ "rArr",   0x21D2 }, /* RIGHT DOUBLE ARROW */
{ "iff",    0x21D4 }, /* LEFT RIGHT DOUBLE ARROW */
{ "vArr",   0x21D5 }, /* UP DOWN DOUBLE ARROW */
{ "lAarr",  0x21DA }, /* LEFT TRIPLE ARROW */
{ "rAarr",  0x21DB }, /* RIGHT TRIPLE ARROW */
{ "rarrw",  0x21DD }, /* RIGHT SQUIGGLE ARROW */
{ "forall", 0x2200 }, /* FOR ALL */
{ "comp",   0x2201 }, /* COMPLEMENT */
{ "part",   0x2202 }, /* PARTIAL DIFFERENTIAL */
{ "exist",  0x2203 }, /* THERE EXISTS */
{ "nexist", 0x2204 }, /* THERE DOES NOT EXIST */
{ "empty",  0x2205 }, /* EMPTY SET */
{ "nabla",  0x2207 }, /* NABLA */
{ "isin",   0x2208 }, /* ELEMENT OF */
{ "notin",  0x2209 }, /* NOT AN ELEMENT OF */
{ "epsis",  0x220A }, /* SMALL ELEMENT OF */
{ "ni",     0x220B }, /* CONTAINS AS MEMBER */
{ "bepsi",  0x220D }, /* SMALL CONTAINS AS MEMBER */
{ "prod",   0x220F }, /* N-ARY PRODUCT */
{ "coprod", 0x2210 }, /* N-ARY COPRODUCT */
{ "amalg",  0x2210 }, /* N-ARY COPRODUCT */
{ "samalg", 0x2210 }, /* N-ARY COPRODUCT */
{ "sum",    0x2211 }, /* N-ARY SUMMATION */
{ "minus",  0x2212 }, /* MINUS SIGN */
{ "mnplus", 0x2213 }, /* MINUS-OR-PLUS SIGN */
{ "plusdo", 0x2214 }, /* DOT PLUS */
{ "setmn",  0x2216 }, /* SET MINUS */
{ "compfn", 0x2218 }, /* RING OPERATOR */
{ "radic",  0x221A }, /* SQUARE ROOT */
{ "vprop",  0x221D }, /* PROPORTIONAL TO */
{ "prop",   0x221D }, /* PROPORTIONAL TO */
{ "infin",  0x221E }, /* INFINITY */
{ "ang90",  0x221F }, /* RIGHT ANGLE */
{ "angmsd", 0x2221 }, /* MEASURED ANGLE */
{ "angsph", 0x2222 }, /* SPHERICAL ANGLE */
{ "mid",    0x2223 }, /* DIVIDES */
{ "nmid",   0x2224 }, /* DOES NOT DIVIDE */
{ "par",    0x2225 }, /* PARALLEL TO */
{ "npar",   0x2226 }, /* NOT PARALLEL TO */
{ "conint", 0x222E }, /* CONTOUR INTEGRAL */
{ "there4", 0x2234 }, /* THEREFORE */
{ "becaus", 0x2235 }, /* BECAUSE */
{ "thksim", 0x223C }, /* TILDE OPERATOR */
{ "sim",    0x223C }, /* TILDE OPERATOR */
{ "bsim",   0x223D }, /* REVERSED TILDE */
{ "wreath", 0x2240 }, /* WREATH PRODUCT */
{ "nsim",   0x2241 }, /* NOT TILDE */
{ "sime",   0x2243 }, /* ASYMPTOTICALLY EQUAL TO */
{ "nsime",  0x2244 }, /* NOT ASYMPTOTICALLY EQUAL TO */
{ "ncong",  0x2247 }, /* NEITHER APPROXIMATELY NOR ACTUALLY EQUAL TO */
{ "thkap",  0x2248 }, /* ALMOST EQUAL TO */
{ "ap",     0x2248 }, /* ALMOST EQUAL TO */
{ "nap",    0x2249 }, /* NOT ALMOST EQUAL TO */
{ "ape",    0x224A }, /* ALMOST EQUAL OR EQUAL TO */
{ "bcong",  0x224C }, /* ALL EQUAL TO */
{ "bump",   0x224E }, /* GEOMETRICALLY EQUIVALENT TO */
{ "bumpe",  0x224F }, /* DIFFERENCE BETWEEN */
{ "esdot",  0x2250 }, /* APPROACHES THE LIMIT */
{ "eDot",   0x2251 }, /* GEOMETRICALLY EQUAL TO */
{ "efDot",  0x2252 }, /* APPROXIMATELY EQUAL TO OR THE IMAGE OF */
{ "erDot",  0x2253 }, /* IMAGE OF OR APPROXIMATELY EQUAL TO */
{ "colone", 0x2254 }, /* COLON EQUAL */
{ "ecolon", 0x2255 }, /* EQUAL COLON */
{ "ecir",   0x2256 }, /* RING IN EQUAL TO */
{ "cire",   0x2257 }, /* RING EQUAL TO */
{ "wedgeq", 0x2259 }, /* ESTIMATES */
{ "trie",   0x225C }, /* DELTA EQUAL TO */
{ "ne",     0x2260 }, /* NOT EQUAL TO */
{ "equiv",  0x2261 }, /* IDENTICAL TO */
{ "nequiv", 0x2262 }, /* NOT IDENTICAL TO */
{ "le",     0x2264 }, /* LESS THAN OR EQUAL TO */
{ "les",    0x2264 }, /* LESS THAN OR EQUAL TO */
{ "ge",     0x2265 }, /* GREATER THAN OR EQUAL TO */
{ "ges",    0x2265 }, /* GREATER THAN OR EQUAL TO */
{ "lE",     0x2266 }, /* LESS THAN OVER EQUAL TO */
{ "gE",     0x2267 }, /* GREATER THAN OVER EQUAL TO */
{ "lnE",    0x2268 }, /* LESS THAN BUT NOT EQUAL TO */
{ "lvnE",   0x2268 }, /* LESS THAN BUT NOT EQUAL TO */
{ "gnE",    0x2269 }, /* GREATER THAN BUT NOT EQUAL TO */
{ "gvnE",   0x2269 }, /* GREATER THAN BUT NOT EQUAL TO */
{ "Lt",     0x226A }, /* MUCH LESS THAN */
{ "Gt",     0x226B }, /* MUCH GREATER THAN */
{ "twixt",  0x226C }, /* BETWEEN */
{ "nlt",    0x226E }, /* NOT LESS THAN */
{ "ngt",    0x226F }, /* NOT GREATER THAN */
{ "nles",   0x2270 }, /* NEITHER LESS THAN NOR EQUAL TO */
{ "nle",    0x2270 }, /* NEITHER LESS THAN NOR EQUAL TO */
{ "nges",   0x2271 }, /* NEITHER GREATER THAN NOR EQUAL TO */
{ "nge",    0x2271 }, /* NEITHER GREATER THAN NOR EQUAL TO */
{ "lsim",   0x2272 }, /* LESS THAN OR EQUIVALENT TO */
{ "gsim",   0x2273 }, /* GREATER THAN OR EQUIVALENT TO */
{ "lg",     0x2276 }, /* LESS THAN OR GREATER THAN */
{ "gl",     0x2277 }, /* GREATER THAN OR LESS THAN */
{ "pr",     0x227A }, /* PRECEDES */
{ "sc",     0x227B }, /* SUCCEEDS */
{ "cupre",  0x227C }, /* PRECEDES OR EQUAL TO */
{ "sccue",  0x227D }, /* SUCCEEDS OR EQUAL TO */
{ "prsim",  0x227E }, /* PRECEDES OR EQUIVALENT TO */
{ "scsim",  0x227F }, /* SUCCEEDS OR EQUIVALENT TO */
{ "npr",    0x2280 }, /* DOES NOT PRECEDE */
{ "nsc",    0x2281 }, /* DOES NOT SUCCEED */
{ "sub",    0x2282 }, /* SUBSET OF */
{ "sup",    0x2283 }, /* SUPERSET OF */
{ "nsub",   0x2284 }, /* NOT A SUBSET OF */
{ "nsup",   0x2285 }, /* NOT A SUPERSET OF */
{ "sube",   0x2286 }, /* SUBSET OF OR EQUAL TO */
{ "supe",   0x2287 }, /* SUPERSET OF OR EQUAL TO */
{ "nsube",  0x2288 }, /* NEITHER A SUBSET OF NOR EQUAL TO */
{ "nsupe",  0x2289 }, /* NEITHER A SUPERSET OF NOR EQUAL TO */
{ "subnE",  0x228A }, /* SUBSET OF OR NOT EQUAL TO */
{ "supnE",  0x228B }, /* SUPERSET OF OR NOT EQUAL TO */
{ "uplus",  0x228E }, /* MULTISET UNION */
{ "sqsub",  0x228F }, /* SQUARE IMAGE OF */
{ "sqsup",  0x2290 }, /* SQUARE ORIGINAL OF */
{ "sqsube", 0x2291 }, /* SQUARE IMAGE OF OR EQUAL TO */
{ "sqsupe", 0x2292 }, /* SQUARE ORIGINAL OF OR EQUAL TO */
{ "sqcap",  0x2293 }, /* SQUARE CAP */
{ "sqcup",  0x2294 }, /* SQUARE CUP */
{ "oplus",  0x2295 }, /* CIRCLED PLUS */
{ "ominus", 0x2296 }, /* CIRCLED MINUS */
{ "otimes", 0x2297 }, /* CIRCLED TIMES */
{ "osol",   0x2298 }, /* CIRCLED DIVISION SLASH */
{ "odot",   0x2299 }, /* CIRCLED DOT OPERATOR */
{ "ocir",   0x229A }, /* CIRCLED RING OPERATOR */
{ "oast",   0x229B }, /* CIRCLED ASTERISK OPERATOR */
{ "odash",  0x229D }, /* CIRCLED DASH */
{ "plusb",  0x229E }, /* SQUARED PLUS */
{ "minusb", 0x229F }, /* SQUARED MINUS */
{ "timesb", 0x22A0 }, /* SQUARED TIMES */
{ "sdotb",  0x22A1 }, /* SQUARED DOT OPERATOR */
{ "vdash",  0x22A2 }, /* RIGHT TACK */
{ "dashv",  0x22A3 }, /* LEFT TACK */
{ "top",    0x22A4 }, /* DOWN TACK */
{ "bottom", 0x22A5 }, /* UP TACK */
{ "perp",   0x22A5 }, /* UP TACK */
{ "models", 0x22A7 }, /* MODELS */
{ "vDash",  0x22A8 }, /* TRUE */
{ "Vdash",  0x22A9 }, /* FORCES */
{ "Vvdash", 0x22AA }, /* TRIPLE VERTICAL BAR RIGHT TURNSTILE */
{ "nvdash", 0x22AC }, /* DOES NOT PROVE */
{ "nvDash", 0x22AD }, /* NOT TRUE */
{ "nVdash", 0x22AE }, /* DOES NOT FORCE */
{ "nVDash", 0x22AF }, /* NEGATED DOUBLE VERTICAL BAR DOUBLE RIGHT TURNSTILE */
{ "vltri",  0x22B2 }, /* NORMAL SUBGROUP OF */
{ "vrtri",  0x22B3 }, /* CONTAINS AS NORMAL SUBGROUP */
{ "ltrie",  0x22B4 }, /* NORMAL SUBGROUP OF OR EQUAL TO */
{ "rtrie",  0x22B5 }, /* CONTAINS AS NORMAL SUBGROUP OR EQUAL TO */
{ "mumap",  0x22B8 }, /* MULTIMAP */
{ "intcal", 0x22BA }, /* INTERCALATE */
{ "veebar", 0x22BB }, /* XOR */
{ "barwed", 0x22BC }, /* NAND */
{ "diam",   0x22C4 }, /* DIAMOND OPERATOR */
{ "sdot",   0x22C5 }, /* DOT OPERATOR */
{ "sstarf", 0x22C6 }, /* STAR OPERATOR */
{ "divonx", 0x22C7 }, /* DIVISION TIMES */
{ "bowtie", 0x22C8 }, /* BOWTIE */
{ "ltimes", 0x22C9 }, /* LEFT NORMAL FACTOR SEMIDIRECT PRODUCT */
{ "rtimes", 0x22CA }, /* RIGHT NORMAL FACTOR SEMIDIRECT PRODUCT */
{ "lthree", 0x22CB }, /* LEFT SEMIDIRECT PRODUCT */
{ "rthree", 0x22CC }, /* RIGHT SEMIDIRECT PRODUCT */
{ "bsime",  0x22CD }, /* REVERSED TILDE EQUALS */
{ "cuvee",  0x22CE }, /* CURLY LOGICAL OR */
{ "cuwed",  0x22CF }, /* CURLY LOGICAL AND */
{ "Sub",    0x22D0 }, /* DOUBLE SUBSET */
{ "Sup",    0x22D1 }, /* DOUBLE SUPERSET */
{ "Cap",    0x22D2 }, /* DOUBLE INTERSECTION */
{ "Cup",    0x22D3 }, /* DOUBLE UNION */
{ "fork",   0x22D4 }, /* PITCHFORK */
{ "ldot",   0x22D6 }, /* LESS THAN WITH DOT */
{ "gsdot",  0x22D7 }, /* GREATER THAN WITH DOT */
{ "Ll",     0x22D8 }, /* VERY MUCH LESS THAN */
{ "Gg",     0x22D9 }, /* VERY MUCH GREATER THAN */
{ "leg",    0x22DA }, /* LESS THAN EQUAL TO OR GREATER THAN */
{ "gel",    0x22DB }, /* GREATER THAN EQUAL TO OR LESS THAN */
{ "els",    0x22DC }, /* EQUAL TO OR LESS THAN */
{ "egs",    0x22DD }, /* EQUAL TO OR GREATER THAN */
{ "cuepr",  0x22DE }, /* EQUAL TO OR PRECEDES */
{ "cuesc",  0x22DF }, /* EQUAL TO OR SUCCEEDS */
{ "npre",   0x22E0 }, /* DOES NOT PRECEDE OR EQUAL */
{ "nsce",   0x22E1 }, /* DOES NOT SUCCEED OR EQUAL */
{ "lnsim",  0x22E6 }, /* LESS THAN BUT NOT EQUIVALENT TO */
{ "gnsim",  0x22E7 }, /* GREATER THAN BUT NOT EQUIVALENT TO */
{ "prnsim", 0x22E8 }, /* PRECEDES BUT NOT EQUIVALENT TO */
{ "scnsim", 0x22E9 }, /* SUCCEEDS BUT NOT EQUIVALENT TO */
{ "nltri",  0x22EA }, /* NOT NORMAL SUBGROUP OF */
{ "nrtri",  0x22EB }, /* DOES NOT CONTAIN AS NORMAL SUBGROUP */
{ "nltrie", 0x22EC }, /* NOT NORMAL SUBGROUP OF OR EQUAL TO */
{ "nrtrie", 0x22ED }, /* DOES NOT CONTAIN AS NORMAL SUBGROUP OR EQUAL */
{ "vellip", 0x22EE }, /* VERTICAL ELLIPSIS */
{ "Barwed", 0x2306 }, /* PERSPECTIVE */
{ "lceil",  0x2308 }, /* LEFT CEILING */
{ "rceil",  0x2309 }, /* RIGHT CEILING */
{ "lfloor", 0x230A }, /* LEFT FLOOR */
{ "rfloor", 0x230B }, /* RIGHT FLOOR */
{ "drcrop", 0x230C }, /* BOTTOM RIGHT CROP */
{ "dlcrop", 0x230D }, /* BOTTOM LEFT CROP */
{ "urcrop", 0x230E }, /* TOP RIGHT CROP */
{ "ulcrop", 0x230F }, /* TOP LEFT CROP */
{ "telrec", 0x2315 }, /* TELEPHONE RECORDER */
{ "target", 0x2316 }, /* POSITION INDICATOR */
{ "ulcorn", 0x231C }, /* TOP LEFT CORNER */
{ "urcorn", 0x231D }, /* TOP RIGHT CORNER */
{ "dlcorn", 0x231E }, /* BOTTOM LEFT CORNER */
{ "drcorn", 0x231F }, /* BOTTOM RIGHT CORNER */
{ "frown",  0x2322 }, /* FROWN */
{ "smile",  0x2323 }, /* SMILE */
{ "lang",   0x2329 }, /* BRA */
{ "rang",   0x232A }, /* KET */
{ "blank",  0x2423 }, /* OPEN BOX */
{ "oS",     0x24C8 }, /* CIRCLED LATIN CAPITAL LETTER S */
{ "boxh",   0x2500 }, /* FORMS LIGHT HORIZONTAL */
{ "boxv",   0x2502 }, /* FORMS LIGHT VERTICAL */
{ "boxdr",  0x250C }, /* FORMS LIGHT DOWN AND RIGHT */
{ "boxdl",  0x2510 }, /* FORMS LIGHT DOWN AND LEFT */
{ "boxur",  0x2514 }, /* FORMS LIGHT UP AND RIGHT */
{ "boxul",  0x2518 }, /* FORMS LIGHT UP AND LEFT */
{ "boxvr",  0x251C }, /* FORMS LIGHT VERTICAL AND RIGHT */
{ "boxvl",  0x2524 }, /* FORMS LIGHT VERTICAL AND LEFT */
{ "boxhd",  0x252C }, /* FORMS LIGHT DOWN AND HORIZONTAL */
{ "boxhu",  0x2534 }, /* FORMS LIGHT UP AND HORIZONTAL */
{ "boxvh",  0x253C }, /* FORMS LIGHT VERTICAL AND HORIZONTAL */
{ "boxH",   0x2550 }, /* FORMS DOUBLE HORIZONTAL */
{ "boxV",   0x2551 }, /* FORMS DOUBLE VERTICAL */
{ "boxdR",  0x2552 }, /* FORMS DOWN SINGLE AND RIGHT DOUBLE */
{ "boxDr",  0x2553 }, /* FORMS DOWN DOUBLE AND RIGHT SINGLE */
{ "boxDR",  0x2554 }, /* FORMS DOUBLE DOWN AND RIGHT */
{ "boxdL",  0x2555 }, /* FORMS DOWN SINGLE AND LEFT DOUBLE */
{ "boxDl",  0x2556 }, /* FORMS DOWN DOUBLE AND LEFT SINGLE */
{ "boxDL",  0x2557 }, /* FORMS DOUBLE DOWN AND LEFT */
{ "boxuR",  0x2558 }, /* FORMS UP SINGLE AND RIGHT DOUBLE */
{ "boxUr",  0x2559 }, /* FORMS UP DOUBLE AND RIGHT SINGLE */
{ "boxUR",  0x255A }, /* FORMS DOUBLE UP AND RIGHT */
{ "boxuL",  0x255B }, /* FORMS UP SINGLE AND LEFT DOUBLE */
{ "boxUl",  0x255C }, /* FORMS UP DOUBLE AND LEFT SINGLE */
{ "boxUL",  0x255D }, /* FORMS DOUBLE UP AND LEFT */
{ "boxvR",  0x255E }, /* FORMS VERTICAL SINGLE AND RIGHT DOUBLE */
{ "boxVr",  0x255F }, /* FORMS VERTICAL DOUBLE AND RIGHT SINGLE */
{ "boxVR",  0x2560 }, /* FORMS DOUBLE VERTICAL AND RIGHT */
{ "boxvL",  0x2561 }, /* FORMS VERTICAL SINGLE AND LEFT DOUBLE */
{ "boxVl",  0x2562 }, /* FORMS VERTICAL DOUBLE AND LEFT SINGLE */
{ "boxVL",  0x2563 }, /* FORMS DOUBLE VERTICAL AND LEFT */
{ "boxHd",  0x2564 }, /* FORMS DOWN SINGLE AND HORIZONTAL DOUBLE */
{ "boxhD",  0x2565 }, /* FORMS DOWN DOUBLE AND HORIZONTAL SINGLE */
{ "boxHD",  0x2566 }, /* FORMS DOUBLE DOWN AND HORIZONTAL */
{ "boxHu",  0x2567 }, /* FORMS UP SINGLE AND HORIZONTAL DOUBLE */
{ "boxhU",  0x2568 }, /* FORMS UP DOUBLE AND HORIZONTAL SINGLE */
{ "boxHU",  0x2569 }, /* FORMS DOUBLE UP AND HORIZONTAL */
{ "boxvH",  0x256A }, /* FORMS VERTICAL SINGLE AND HORIZONTAL DOUBLE */
{ "boxVh",  0x256B }, /* FORMS VERTICAL DOUBLE AND HORIZONTAL SINGLE */
{ "boxVH",  0x256C }, /* FORMS DOUBLE VERTICAL AND HORIZONTAL */
{ "uhblk",  0x2580 }, /* UPPER HALF BLOCK */
{ "lhblk",  0x2584 }, /* LOWER HALF BLOCK */
{ "block",  0x2588 }, /* FULL BLOCK */
{ "blk14",  0x2591 }, /* LIGHT SHADE */
{ "blk12",  0x2592 }, /* MEDIUM SHADE */
{ "blk34",  0x2593 }, /* DARK SHADE */
{ "squ",    0x25A1 }, /* WHITE SQUARE */
{ "square", 0x25A1 }, /* WHITE SQUARE */
{ "squf",   0x25AA }, /* BLACK SMALL SQUARE */
{ "rect",   0x25AD }, /* WHITE RECTANGLE */
{ "marker", 0x25AE }, /* BLACK VERTICAL RECTANGLE */
{ "xutri",  0x25B3 }, /* WHITE UP POINTING TRIANGLE */
{ "utrif",  0x25B4 }, /* BLACK UP POINTING SMALL TRIANGLE */
{ "utri",   0x25B5 }, /* WHITE UP POINTING SMALL TRIANGLE */
{ "rtrif",  0x25B8 }, /* BLACK RIGHT POINTING SMALL TRIANGLE */
{ "rtri",   0x25B9 }, /* WHITE RIGHT POINTING SMALL TRIANGLE */
{ "xdtri",  0x25BD }, /* WHITE DOWN POINTING TRIANGLE */
{ "dtrif",  0x25BE }, /* BLACK DOWN POINTING SMALL TRIANGLE */
{ "dtri",   0x25BF }, /* WHITE DOWN POINTING SMALL TRIANGLE */
{ "ltrif",  0x25C2 }, /* BLACK LEFT POINTING SMALL TRIANGLE */
{ "ltri",   0x25C3 }, /* WHITE LEFT POINTING SMALL TRIANGLE */
{ "cir",    0x25CB }, /* WHITE CIRCLE */
{ "xcirc",  0x25CB }, /* WHITE CIRCLE */
{ "starf",  0x2605 }, /* BLACK STAR */
{ "star",   0x2606 }, /* WHITE STAR */
{ "phone",  0x260E }, /* BLACK TELEPHONE */
{ "female", 0x2640 }, /* FEMALE SIGN */
{ "male",   0x2642 }, /* MALE SIGN */
{ "spades", 0x2660 }, /* BLACK SPADE SUIT */
{ "hearts", 0x2661 }, /* WHITE HEART SUIT */
{ "diams",  0x2662 }, /* WHITE DIAMOND SUIT */
{ "sung",   0x266A }, /* EIGHTH NOTE */
{ "flat",   0x266D }, /* FLAT */
{ "natur",  0x266E }, /* NATURAL */
{ "sharp",  0x266F }, /* SHARP */
{ "check",  0x2713 }, /* CHECK MARK */
{ "cross",  0x2717 }, /* BALLOT X */
{ "malt",   0x2720 }, /* MALTESE CROSS */
{ "lozf",   0x2726 }, /* BLACK FOUR POINTED STAR */
{ "loz",    0x2727 }, /* WHITE FOUR POINTED STAR */
{ "sextile", 0x2736 } /* SIX POINTED BLACK STAR */

};


#endif
