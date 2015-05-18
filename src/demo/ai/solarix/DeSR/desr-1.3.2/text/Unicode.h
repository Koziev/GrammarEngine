/*
**  Tanl C++ Library
**  ixe/text/Unicode.h
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

#ifndef Tanl_Text_Unicode_h
#define Tanl_Text_Unicode_h

#include "text.h"

namespace Tanl {
namespace Text {
namespace Unicode {

/**
 * @see http://www.unicode.org/Public/3.1-Update/UnicodeData-3.1.0.html
 *
 * Category	Flags
 *
 * Lu Letter, Uppercase 
 * Ll Letter, Lowercase 
 * Lt Letter, Titlecase 
 * Lm Letter, Modifier 
 * Lo Letter, Other 
 * Mn Mark, Non-Spacing 
 * Mc Mark, Spacing Combining 
 * Me Mark, Enclosing 
 * Nd Number, Decimal Digit 
 * Nl Number, Letter 
 * No Number, Other 
 * Pc Punctuation, Connector 
 * Pd Punctuation, Dash 
 * Ps Punctuation, Open 
 * Pe Punctuation, Close 
 * Pi Punctuation, Initial quote
 * Pf Punctuation, Final quote
 * Po Punctuation, Other 
 * Sm Symbol, Math 
 * Sc Symbol, Currency 
 * Sk Symbol, Modifier 
 * So Symbol, Other 
 * Zs Separator, Space 
 * Zl Separator, Line 
 * Zp Separator, Paragraph 
 * Cc Other, Control 
 * Cf Other, Format 
 * Cs Other, Surrogate 
 * Co Other, Private Use 
 * Cn Other, Not Assigned 

*/

enum Masks
{
  Letter	= 0x0100,	// Letter
  Number	= 0x0200,	// Number
  Mark		= 0x0400,	// Mark
  Punctuation	= 0x0800,	// Punctuation
  Symbol	= 0x1000,	// Symbol
  Separator	= 0x2000,	// Separator
  Other		= 0x4000,	// Other

  Uppercase	= 0x0010,	// Uppercase
  Lowercase	= 0x0020,	// Lowercase
  Titlecase	= 0x0040,	// Titlecase
  Whitespace	= 0x0080,	// WS, B, S

  Lu		= 0x0110,	// Letter, Uppercase
  Ll		= 0x0120,	// Letter, Lowercase
  Lt		= 0x0140,	// Letter, Titlecase
  Lm		= 0x0180,	// Letter, Modifier
  Lo		= 0x0100,	// Letter, Other

  Nd		= 0x0201,	// Number, Decimal Digit
  No		= 0x0202,	// Number, Other
  Nl		= 0x0300,	// Number, Letter (ORed with uppercase/lowercase)

  Mn		= 0x0400,	// Mark, Non-Spacing
  Mc		= 0x0401,	// Mark, Spacing Combining
  Me		= 0x0402,	// Mark, Enclosing

  Pc		= 0x0800,	// Punctuation, Connector
  Pd		= 0x0801,	// Punctuation, Dash
  Ps		= 0x0802,	// Punctuation, Open
  Pe		= 0x0803,	// Punctuation, Close
  Pi		= 0x0804,	// Punctuation, Initial quote
  Pf		= 0x0805,	// Punctuation, Final quote
  Po		= 0x0806,	// Punctuation, Other

  Sm		= 0x1000,	// Symbol, Math
  Sc		= 0x1001,	// Symbol, Currency
  Sk		= 0x1002,	// Symbol, Modifier
  So		= 0x1003,	// Symbol, Other

  Zs		= 0x2001,	// Separator, Space
  Zl		= 0x2002,	// Separator, Line
  Zp		= 0x2004,	// Separator, Paragraph

  Cc		= 0x4000,	// Other, Control
  Cf		= 0x4001,	// Other, Format
  Cs		= 0x4002,	// Other, Surrogate
  Co		= 0x4003,	// Other, Private Use
  Cn		= 0x4004	// Other, Not Assigned
};

enum Category
{
  UppercaseLetter			= 0,
  LowercaseLetter			= 1,
  TitlecaseLetter			= 2,
  ModifierLetter			= 3,
  OtherLetter				= 4,
  NonSpacingMark			= 5,
  SpaceCombiningMark			= 6,
  EnclosingMark				= 7,
  DecimalDigitNumber			= 8,
  LetterNumber				= 9,
  OtherNumber				= 10,
  SpaceSeparator			= 11,
  LineSeparator				= 12,
  ParagraphSeparator			= 13,
  Control				= 14,
  Format				= 15,
  Surrogate				= 16,
  PrivateUse				= 17,
  ConnectorPunctuation			= 18,
  DashPunctuation			= 19,
  OpenPunctuation			= 20,
  ClosePunctuation			= 21,
  InitialQuotePunctuation		= 22,
  FinalQuotePunctuation			= 23,
  OtherPunctuation			= 24,
  MathSymbol				= 25,
  CurrencySymbol			= 26,
  ModifierSymbol			= 27,
  OtherSymbol				= 28,
  OtherNotAssigned			= 29
};

  /**
   * Constants for Unicode blocks.
   */
enum BlockCode {

  NoBlock			= 0, /* Special range indicating no block */
  BasicLatin			= 1, /*[0000]*/
  Latin1Supplement		= 2, /*[0080]*/
  LatinExtendedA		= 3, /*[0100]*/
  LatinExtendedB		= 4, /*[0180]*/
  IPAExtensions			= 5, /*[0250]*/
  SpacingModifierLetters	= 6, /*[02B0]*/
  CombiningDiacriticalMarks	= 7, /*[0300]*/
  Greek				= 8, /*[0370]*/
  Cyrillic			= 9, /*[0400]*/
  CyrillicSupplement		= 10, /*[0500]*/
  Armenian			= 11, /*[0530]*/
  Hebrew			= 12, /*[0590]*/
  Arabic			= 13, /*[0600]*/
  Syriac			= 14, /*[0700]*/
  Thaana			= 15, /*[0780]*/
  Devanagari			= 16, /*[0900]*/
  Bengali			= 17, /*[0980]*/
  Gurmukhi			= 18, /*[0A00]*/
  Gujarati			= 19, /*[0A80]*/
  Oriya				= 20, /*[0B00]*/
  Tamil				= 21, /*[0B80]*/
  Telugu			= 22, /*[0C00]*/
  Kannada			= 23, /*[0C80]*/
  Malayalam			= 24, /*[0D00]*/
  Sinhala			= 25, /*[0D80]*/
  Thai				= 26, /*[0E00]*/
  Lao				= 27, /*[0E80]*/
  Tibetan			= 28, /*[0F00]*/
  Myanmar			= 29, /*[1000]*/
  Georgian			= 30, /*[10A0]*/
  HangulJamo			= 31, /*[1100]*/
  Ethiopic			= 32, /*[1200]*/
  Cherokee			= 33, /*[13A0]*/
  UnifiedCanadianAboriginalSyllabics	= 34, /*[1400]*/
  Ogham				= 35, /*[1680]*/
  Runic				= 36, /*[16A0]*/
  Tagalog			= 37, /*[1700]*/
  Hanunoo			= 38, /*[1720]*/
  Buhid				= 39, /*[1740]*/
  Tagbanwa			= 40, /*[1760]*/
  Khmer				= 41, /*[1780]*/
  Mongolian			= 42, /*[1800]*/
  Limbu				= 43, /*[1900]*/
  TaiLe				= 44, /*[1950]*/
  KhmerSymbols			= 45, /*[19E0]*/
  PhoneticExtensions		= 46, /*[1D00]*/
  LatinExtendedAdditional	= 47, /*[1E00]*/
  GreekExtended			= 48, /*[1F00]*/
  GeneralPunctuation		= 49, /*[2000]*/
  SuperscriptsAndSubscripts	= 50, /*[2070]*/
  CurrencySymbols		= 51, /*[20A0]*/
  CombiningDiacriticalMarksForSymbols	= 52, /*[20D0]*/
  LetterlikeSymbols		= 53, /*[2100]*/
  NumberForms			= 54, /*[2150]*/
  Arrows			= 55, /*[2190]*/
  MathematicalOperators		= 56, /*[2200]*/
  MiscellaneousTechnical	= 56, /*[2300]*/
  ControlPictures		= 57, /*[2400]*/
  OpticalCharacterRecognition	= 58, /*[2440]*/
  EnclosedAlphanumerics		= 59, /*[2460]*/
  BoxDrawing			= 60, /*[2500]*/
  BlockElements			= 61, /*[2580]*/
  GeometricShapes		= 62, /*[25A0]*/
  MiscellaneousSymbols		= 63, /*[2600]*/
  Dingbats			= 64, /*[2700]*/
  MiscellaneousMathematicalSymbolsA	= 65, /*[27C0]*/
  SupplementalArrowsA		= 66, /*[27F0]*/
  BraillePatterns		= 67, /*[2800]*/
  SupplementalArrowsB		= 68, /*[2900]*/
  MiscellaneousMathematicalSymbolsB	= 69, /*[2980]*/
  SupplementalMathematicalOperators	= 70, /*[2A00]*/
  MiscellaneousSymbolsAndArrows		= 71, /*[2B00]*/
  CJKRadicalsSupplement		= 72, /*[2E80]*/
  KangxiRadicals		= 73, /*[2F00]*/
  IdeographicDescriptionCharacters	= 74, /*[2FF0]*/
  CJKSymbolsAndPunctuation		= 75, /*[3000]*/
  Hiragana			= 76, /*[3040]*/
  Katakana			= 77, /*[30A0]*/
  Bopomofo			= 78, /*[3100]*/
  HangulCompatibilityJamo	= 79, /*[3130]*/
  Kanbun			= 80, /*[3190]*/
  BopomofoExtended		= 81, /*[31A0]*/
  KatakanaPhoneticExtensions	= 82, /*[31F0]*/
  EnclosedCJKLettersAndMonths	= 83, /*[3200]*/
  CJKCompatibility		= 84, /*[3300]*/
  CJKUnifiedIdeographsExtensionA= 85, /*[3400]*/
  YijingHexagramSymbols		= 86, /*[4DC0]*/
  CJKUnifiedIdeographs		= 87, /*[4E00]*/
  YiSyllables			= 88, /*[A000]*/
  YiRadicals			= 89, /*[A490]*/
  HangulSyllables		= 90, /*[AC00]*/
  HighSurrogates		= 91, /*[D800]*/
  HighPrivateUseSurrogates	= 92, /*[DB80]*/
  LowSurrogates			= 93, /*[DC00]*/
  PrivateUseArea		= 94, /*[E000]*/
  CJKCompatibilityIdeographs	= 95, /*[F900]*/
  AlphabeticPresentationForms	= 96, /*[FB00]*/
  ArabicPresentationFormsA	= 97, /*[FB50]*/
  VariationSelectors		= 98, /*[FE00]*/
  CombiningHalfMarks		= 99, /*[FE20]*/
  CJKCompatibilityForms		= 100, /*[FE30]*/
  SmallFormVariants		= 101, /*[FE50]*/
  ArabicPresentationFormsB	= 102, /*[FE70]*/
  HalfwidthAndFullwidthForms	= 103, /*[FF00]*/
  Specials			= 104, /*[FFF0]*/
  LinearBSyllabary		= 105, /*[10000]*/
  LinearBIdeograms		= 106, /*[10080]*/
  AegeanNumbers			= 107, /*[10100]*/
  OldItalic			= 108, /*[10300]*/
  Gothic			= 109, /*[10330]*/
  Ugaritic			= 110, /*[10380]*/
  Deseret			= 111, /*[10400]*/
  Shavian			= 112, /*[10450]*/
  Osmanya			= 113, /*[10480]*/
  CypriotSyllabary		= 114, /*[10800]*/
  ByzantineMusicalSymbols	= 115, /*[1D000]*/
  MusicalSymbols		= 116, /*[1D100]*/
  TaiXuanJingSymbols		= 117, /*[1D300]*/
  MathematicalAlphanumericSymbols	= 118, /*[1D400]*/
  CJKUnifiedIdeographsExtensionB	= 119, /*[20000]*/
  CJKCompatibilityIdeographsSupplement	= 120, /*[2F800]*/
  Tags				= 121, /*[E0000]*/
  VariationSelectorsSupplement	= 122, /*[E0100]*/
  SupplementaryPrivateUseAreaA	= 123, /*[F0000]*/
  SupplementaryPrivateUseAreaB	= 124, /*[100000]*/
  BlockCount
};

struct BlockInfo
{
  UCS4		first;
  UCS4		last;
  char const*	name;
};

extern BlockInfo BlockTable[];

/**
 *	Return the code block to which the character @a uc belongs.
 */
BlockInfo& Block(UCS2 uc);

/**
 *	Return the code for the block to which the character @a uc belongs.
 */
BlockCode GetBlockCode(UCS2 uc);

struct UnicodeInfo
{
  short		flags;
  short		category;	///< general category
				/// (@see http://www.unicode.org/Public/UNIDATA/UCD.html#General_Category_Values)
  UCS2*		decomp;		///< decomposition mapping
				/// (@see http://www.unicode.org/Public/UNIDATA/UCD.html#Character_Decomposition_Mappings)
  int		decval;		///< numeric value
  UCS2		upcase;		///< upper case mapping
  UCS2		downcase;	///< lower case mapping
  UCS2		titlecase;	///< title case mapping
};

extern UnicodeInfo UnicodeTable[65536];

/**
 * Provides the decomposition mapping for those characters which have it.
 */
extern UCS2 decompositionMap[];

} // Unicode
} // Text
} // Tanl

#endif //Tanl_Text_Unicode_h
