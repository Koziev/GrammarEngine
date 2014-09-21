// 27-09-2006 - символ подчеркивания переведен из категории "Delim" в обычные символы
//
// 23.01.2007 - символ 'Й' теперь не является связанным с 'И' через диактрический значек

#include <lem/unicode.h>


#if defined LEM_UNICODE_EX
using namespace lem;

lem::CodeConverter::Unicode_Char lem::CodeConverter::unicode_table[0x2100] = {
/* 0000 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0001 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0002 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0003 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0004 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0005 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0006 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0007 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0008 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0009 */ { lem::CP_Char_Flags::Space,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 000A */ { lem::CP_Char_Flags::Space,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 000B */ { lem::CP_Char_Flags::Space,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 000C */ { lem::CP_Char_Flags::Space,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 000D */ { lem::CP_Char_Flags::Space,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 000E */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 000F */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0010 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0011 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0012 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0013 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0014 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0015 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0016 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0017 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0018 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0019 */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 001A */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 001B */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 001C */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 001D */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 001E */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 001F */ { lem::CP_Char_Flags::Control, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0020 */ { lem::CP_Char_Flags::Space,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SPACE 
/* 0021 */ { lem::CP_Char_Flags::Punkt,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXCLAMATION MARK 
/* 0022 */ { lem::CP_Char_Flags::Punkt,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // QUOTATION MARK 
/* 0023 */ { lem::CP_Char_Flags::Punkt,   0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NUMBER SIGN 
/* 0024 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOLLAR SIGN 
/* 0025 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PERCENT SIGN 
/* 0026 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // AMPERSAND 
/* 0027 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // APOSTROPHE 
/* 0028 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT PARENTHESIS 
/* 0029 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT PARENTHESIS 
/* 002A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ASTERISK 
/* 002B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PLUS SIGN 
/* 002C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMMA 
/* 002D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HYPHEN-MINUS 
/* 002E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FULL STOP 
/* 002F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SOLIDUS 
/* 0030 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT ZERO 
/* 0031 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT ONE 
/* 0032 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT TWO 
/* 0033 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT THREE 
/* 0034 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT FOUR 
/* 0035 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT FIVE 
/* 0036 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT SIX 
/* 0037 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT SEVEN 
/* 0038 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT EIGHT 
/* 0039 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIGIT NINE 
/* 003A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COLON 
/* 003B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SEMICOLON 
/* 003C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LESS-THAN SIGN 
/* 003D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EQUALS SIGN 
/* 003E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREATER-THAN SIGN 
/* 003F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // QUESTION MARK 
/* 0040 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMMERCIAL AT 
/* 0041 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0061, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER A 
/* 0042 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0062, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER B 
/* 0043 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0063, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER C 
/* 0044 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0064, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER D 
/* 0045 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0065, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER E 
/* 0046 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0066, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER F 
/* 0047 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0067, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER G 
/* 0048 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0068, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER H 
/* 0049 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0069, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER I 
/* 004A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x006A, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER J 
/* 004B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x006B, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER K 
/* 004C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x006C, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER L 
/* 004D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x006D, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER M 
/* 004E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x006E, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER N 
/* 004F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x006F, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER O 
/* 0050 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0070, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER P 
/* 0051 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0071, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER Q 
/* 0052 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0072, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER R 
/* 0053 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0073, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER S 
/* 0054 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0074, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER T 
/* 0055 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0075, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER U 
/* 0056 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0076, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER V 
/* 0057 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0077, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER W 
/* 0058 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0078, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER X 
/* 0059 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0079, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y 
/* 005A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x007A, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z 
/* 005B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT SQUARE BRACKET 
/* 005C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // REVERSE SOLIDUS 
/* 005D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT SQUARE BRACKET 
/* 005E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CIRCUMFLEX ACCENT 
/* 005F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LOW LINE 
/* 0060 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GRAVE ACCENT 
/* 0061 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0041, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER A 
/* 0062 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0042, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER B 
/* 0063 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0043, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER C 
/* 0064 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0044, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D 
/* 0065 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0045, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER E 
/* 0066 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0046, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER F 
/* 0067 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0047, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER G 
/* 0068 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0048, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER H 
/* 0069 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0049, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER I 
/* 006A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x004A, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER J 
/* 006B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x004B, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER K 
/* 006C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x004C, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L 
/* 006D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x004D, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER M 
/* 006E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x004E, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER N 
/* 006F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x004F, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER O 
/* 0070 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0050, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER P 
/* 0071 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0051, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Q 
/* 0072 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0052, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER R 
/* 0073 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0053, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER S 
/* 0074 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0054, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER T 
/* 0075 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0055, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER U 
/* 0076 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0056, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER V 
/* 0077 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0057, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER W 
/* 0078 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0058, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER X 
/* 0079 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0059, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Y 
/* 007A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x005A, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Z 
/* 007B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT CURLY BRACKET 
/* 007C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // VERTICAL LINE 
/* 007D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT CURLY BRACKET 
/* 007E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TILDE 
/* 007F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0080 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0081 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0082 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0083 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0084 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0085 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0086 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0087 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0088 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0089 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 008A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 008B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 008C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 008D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 008E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 008F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0090 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0091 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0092 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0093 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0094 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0095 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0096 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0097 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0098 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 0099 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 009A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 009B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 009C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 009D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 009E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 009F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // <control> 
/* 00A0 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NO-BREAK SPACE 
/* 00A1 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // INVERTED EXCLAMATION MARK 
/* 00A2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CENT SIGN 
/* 00A3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // POUND SIGN 
/* 00A4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CURRENCY SIGN 
/* 00A5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // YEN SIGN 
/* 00A6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BROKEN BAR 
/* 00A7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SECTION SIGN 
/* 00A8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIAERESIS 
/* 00A9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COPYRIGHT SIGN 
/* 00AA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FEMININE ORDINAL INDICATOR 
/* 00AB */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK 
/* 00AC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NOT SIGN 
/* 00AD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SOFT HYPHEN 
/* 00AE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // REGISTERED SIGN 
/* 00AF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MACRON 
/* 00B0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEGREE SIGN 
/* 00B1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PLUS-MINUS SIGN 
/* 00B2 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT TWO 
/* 00B3 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT THREE 
/* 00B4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ACUTE ACCENT 
/* 00B5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x039C, 0x0000,0x0000,0x0000,0x0000 }, // MICRO SIGN 
/* 00B6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PILCROW SIGN 
/* 00B7 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MIDDLE DOT 
/* 00B8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CEDILLA 
/* 00B9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT ONE 
/* 00BA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MASCULINE ORDINAL INDICATOR 
/* 00BB */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK 
/* 00BC */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // VULGAR FRACTION ONE QUARTER 
/* 00BD */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // VULGAR FRACTION ONE HALF 
/* 00BE */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // VULGAR FRACTION THREE QUARTERS 
/* 00BF */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // INVERTED QUESTION MARK 
/* 00C0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E0, 0x0041,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH GRAVE 
/* 00C1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E1, 0x0041,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH ACUTE 
/* 00C2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E2, 0x0041,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH CIRCUMFLEX 
/* 00C3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E3, 0x0041,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH TILDE 
/* 00C4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E4, 0x0041,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH DIAERESIS 
/* 00C5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E5, 0x0041,0x030A,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH RING ABOVE 
/* 00C6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E6, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER AE 
/* 00C7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E7, 0x0043,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER C WITH CEDILLA 
/* 00C8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E8, 0x0045,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH GRAVE 
/* 00C9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00E9, 0x0045,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH ACUTE 
/* 00CA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00EA, 0x0045,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CIRCUMFLEX 
/* 00CB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00EB, 0x0045,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH DIAERESIS 
/* 00CC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00EC, 0x0049,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH GRAVE 
/* 00CD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00ED, 0x0049,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH ACUTE 
/* 00CE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00EE, 0x0049,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH CIRCUMFLEX 
/* 00CF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00EF, 0x0049,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH DIAERESIS 
/* 00D0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F0, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER ETH 
/* 00D1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F1, 0x004E,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH TILDE 
/* 00D2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F2, 0x004F,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH GRAVE 
/* 00D3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F3, 0x004F,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH ACUTE 
/* 00D4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F4, 0x004F,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH CIRCUMFLEX 
/* 00D5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F5, 0x004F,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH TILDE 
/* 00D6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F6, 0x004F,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH DIAERESIS 
/* 00D7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MULTIPLICATION SIGN 
/* 00D8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F8, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH STROKE 
/* 00D9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00F9, 0x0055,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH GRAVE 
/* 00DA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00FA, 0x0055,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH ACUTE 
/* 00DB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00FB, 0x0055,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH CIRCUMFLEX 
/* 00DC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00FC, 0x0055,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DIAERESIS 
/* 00DD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00FD, 0x0059,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH ACUTE 
/* 00DE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00FE, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER THORN 
/* 00DF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SHARP S 
/* 00E0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C0, 0x0061,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH GRAVE 
/* 00E1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C1, 0x0061,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH ACUTE 
/* 00E2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C2, 0x0061,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH CIRCUMFLEX 
/* 00E3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C3, 0x0061,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH TILDE 
/* 00E4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C4, 0x0061,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH DIAERESIS 
/* 00E5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C5, 0x0061,0x030A,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH RING ABOVE 
/* 00E6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C6, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER AE 
/* 00E7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C7, 0x0063,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH CEDILLA 
/* 00E8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C8, 0x0065,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH GRAVE 
/* 00E9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00C9, 0x0065,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH ACUTE 
/* 00EA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00CA, 0x0065,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CIRCUMFLEX 
/* 00EB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00CB, 0x0065,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH DIAERESIS 
/* 00EC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00CC, 0x0069,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH GRAVE 
/* 00ED */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00CD, 0x0069,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH ACUTE 
/* 00EE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00CE, 0x0069,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH CIRCUMFLEX 
/* 00EF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00CF, 0x0069,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH DIAERESIS 
/* 00F0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D0, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER ETH 
/* 00F1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D1, 0x006E,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH TILDE 
/* 00F2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D2, 0x006F,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH GRAVE 
/* 00F3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D3, 0x006F,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH ACUTE 
/* 00F4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D4, 0x006F,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH CIRCUMFLEX 
/* 00F5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D5, 0x006F,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH TILDE 
/* 00F6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D6, 0x006F,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH DIAERESIS 
/* 00F7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DIVISION SIGN 
/* 00F8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D8, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH STROKE 
/* 00F9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00D9, 0x0075,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH GRAVE 
/* 00FA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00DA, 0x0075,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH ACUTE 
/* 00FB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00DB, 0x0075,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH CIRCUMFLEX 
/* 00FC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00DC, 0x0075,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DIAERESIS 
/* 00FD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00DD, 0x0079,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH ACUTE 
/* 00FE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x00DE, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER THORN 
/* 00FF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0178, 0x0079,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH DIAERESIS 
/* 0100 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0101, 0x0041,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH MACRON 
/* 0101 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0100, 0x0061,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH MACRON 
/* 0102 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0103, 0x0041,0x0306,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH BREVE 
/* 0103 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0102, 0x0061,0x0306,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH BREVE 
/* 0104 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0105, 0x0041,0x0328,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH OGONEK 
/* 0105 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0104, 0x0061,0x0328,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH OGONEK 
/* 0106 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0107, 0x0043,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER C WITH ACUTE 
/* 0107 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0106, 0x0063,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH ACUTE 
/* 0108 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0109, 0x0043,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER C WITH CIRCUMFLEX 
/* 0109 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0108, 0x0063,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH CIRCUMFLEX 
/* 010A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x010B, 0x0043,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER C WITH DOT ABOVE 
/* 010B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x010A, 0x0063,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH DOT ABOVE 
/* 010C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x010D, 0x0043,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER C WITH CARON 
/* 010D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x010C, 0x0063,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH CARON 
/* 010E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x010F, 0x0044,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH CARON 
/* 010F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x010E, 0x0064,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH CARON 
/* 0110 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0111, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH STROKE 
/* 0111 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0110, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH STROKE 
/* 0112 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0113, 0x0045,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH MACRON 
/* 0113 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0112, 0x0065,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH MACRON 
/* 0114 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0115, 0x0045,0x0306,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH BREVE 
/* 0115 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0114, 0x0065,0x0306,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH BREVE 
/* 0116 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0117, 0x0045,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH DOT ABOVE 
/* 0117 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0116, 0x0065,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH DOT ABOVE 
/* 0118 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0119, 0x0045,0x0328,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH OGONEK 
/* 0119 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0118, 0x0065,0x0328,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH OGONEK 
/* 011A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x011B, 0x0045,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CARON 
/* 011B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x011A, 0x0065,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CARON 
/* 011C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x011D, 0x0047,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH CIRCUMFLEX 
/* 011D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x011C, 0x0067,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH CIRCUMFLEX 
/* 011E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x011F, 0x0047,0x0306,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH BREVE 
/* 011F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x011E, 0x0067,0x0306,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH BREVE 
/* 0120 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0121, 0x0047,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH DOT ABOVE 
/* 0121 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0120, 0x0067,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH DOT ABOVE 
/* 0122 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0123, 0x0047,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH CEDILLA 
/* 0123 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0122, 0x0067,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH CEDILLA 
/* 0124 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0125, 0x0048,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER H WITH CIRCUMFLEX 
/* 0125 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0124, 0x0068,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH CIRCUMFLEX 
/* 0126 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0127, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER H WITH STROKE 
/* 0127 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0126, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH STROKE 
/* 0128 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0129, 0x0049,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH TILDE 
/* 0129 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0128, 0x0069,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH TILDE 
/* 012A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x012B, 0x0049,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH MACRON 
/* 012B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x012A, 0x0069,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH MACRON 
/* 012C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x012D, 0x0049,0x0306,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH BREVE 
/* 012D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x012C, 0x0069,0x0306,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH BREVE 
/* 012E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x012F, 0x0049,0x0328,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH OGONEK 
/* 012F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x012E, 0x0069,0x0328,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH OGONEK 
/* 0130 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0069, 0x0049,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH DOT ABOVE 
/* 0131 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0049, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DOTLESS I 
/* 0132 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0133, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LIGATURE IJ 
/* 0133 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0132, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LIGATURE IJ 
/* 0134 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0135, 0x004A,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER J WITH CIRCUMFLEX 
/* 0135 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0134, 0x006A,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER J WITH CIRCUMFLEX 
/* 0136 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0137, 0x004B,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER K WITH CEDILLA 
/* 0137 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0136, 0x006B,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER K WITH CEDILLA 
/* 0138 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER KRA 
/* 0139 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x013A, 0x004C,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH ACUTE 
/* 013A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0139, 0x006C,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH ACUTE 
/* 013B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x013C, 0x004C,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH CEDILLA 
/* 013C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x013B, 0x006C,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH CEDILLA 
/* 013D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x013E, 0x004C,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH CARON 
/* 013E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x013D, 0x006C,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH CARON 
/* 013F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0140, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH MIDDLE DOT 
/* 0140 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x013F, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH MIDDLE DOT 
/* 0141 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0142, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH STROKE 
/* 0142 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0141, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH STROKE 
/* 0143 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0144, 0x004E,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH ACUTE 
/* 0144 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0143, 0x006E,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH ACUTE 
/* 0145 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0146, 0x004E,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH CEDILLA 
/* 0146 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0145, 0x006E,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH CEDILLA 
/* 0147 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0148, 0x004E,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH CARON 
/* 0148 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0147, 0x006E,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH CARON 
/* 0149 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER N PRECEDED BY APOSTROPHE 
/* 014A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x014B, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER ENG 
/* 014B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x014A, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER ENG 
/* 014C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x014D, 0x004F,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH MACRON 
/* 014D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x014C, 0x006F,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH MACRON 
/* 014E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x014F, 0x004F,0x0306,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH BREVE 
/* 014F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x014E, 0x006F,0x0306,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH BREVE 
/* 0150 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0151, 0x004F,0x030B,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH DOUBLE ACUTE 
/* 0151 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0150, 0x006F,0x030B,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH DOUBLE ACUTE 
/* 0152 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0153, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LIGATURE OE 
/* 0153 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0152, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LIGATURE OE 
/* 0154 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0155, 0x0052,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH ACUTE 
/* 0155 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0154, 0x0072,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH ACUTE 
/* 0156 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0157, 0x0052,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH CEDILLA 
/* 0157 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0156, 0x0072,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH CEDILLA 
/* 0158 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0159, 0x0052,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH CARON 
/* 0159 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0158, 0x0072,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH CARON 
/* 015A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x015B, 0x0053,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH ACUTE 
/* 015B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x015A, 0x0073,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH ACUTE 
/* 015C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x015D, 0x0053,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH CIRCUMFLEX 
/* 015D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x015C, 0x0073,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH CIRCUMFLEX 
/* 015E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x015F, 0x0053,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH CEDILLA 
/* 015F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x015E, 0x0073,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH CEDILLA 
/* 0160 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0161, 0x0053,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH CARON 
/* 0161 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0160, 0x0073,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH CARON 
/* 0162 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0163, 0x0054,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH CEDILLA 
/* 0163 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0162, 0x0074,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH CEDILLA 
/* 0164 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0165, 0x0054,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH CARON 
/* 0165 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0164, 0x0074,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH CARON 
/* 0166 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0167, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH STROKE 
/* 0167 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0166, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH STROKE 
/* 0168 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0169, 0x0055,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH TILDE 
/* 0169 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0168, 0x0075,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH TILDE 
/* 016A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x016B, 0x0055,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH MACRON 
/* 016B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x016A, 0x0075,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH MACRON 
/* 016C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x016D, 0x0055,0x0306,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH BREVE 
/* 016D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x016C, 0x0075,0x0306,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH BREVE 
/* 016E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x016F, 0x0055,0x030A,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH RING ABOVE 
/* 016F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x016E, 0x0075,0x030A,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH RING ABOVE 
/* 0170 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0171, 0x0055,0x030B,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DOUBLE ACUTE 
/* 0171 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0170, 0x0075,0x030B,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DOUBLE ACUTE 
/* 0172 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0173, 0x0055,0x0328,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH OGONEK 
/* 0173 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0172, 0x0075,0x0328,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH OGONEK 
/* 0174 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0175, 0x0057,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER W WITH CIRCUMFLEX 
/* 0175 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0174, 0x0077,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER W WITH CIRCUMFLEX 
/* 0176 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0177, 0x0059,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH CIRCUMFLEX 
/* 0177 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0176, 0x0079,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH CIRCUMFLEX 
/* 0178 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x00FF, 0x0059,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH DIAERESIS 
/* 0179 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x017A, 0x005A,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z WITH ACUTE 
/* 017A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0179, 0x007A,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH ACUTE 
/* 017B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x017C, 0x005A,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z WITH DOT ABOVE 
/* 017C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x017B, 0x007A,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH DOT ABOVE 
/* 017D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x017E, 0x005A,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z WITH CARON 
/* 017E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x017D, 0x007A,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH CARON 
/* 017F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0053, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER LONG S 
/* 0180 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER B WITH STROKE 
/* 0181 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0253, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER B WITH HOOK 
/* 0182 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0183, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER B WITH TOPBAR 
/* 0183 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0182, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER B WITH TOPBAR 
/* 0184 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0185, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER TONE SIX 
/* 0185 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0184, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TONE SIX 
/* 0186 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0254, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER OPEN O 
/* 0187 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0188, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER C WITH HOOK 
/* 0188 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0187, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH HOOK 
/* 0189 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0256, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER AFRICAN D 
/* 018A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0257, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH HOOK 
/* 018B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x018C, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH TOPBAR 
/* 018C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x018B, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH TOPBAR 
/* 018D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED DELTA 
/* 018E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01DD, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER REVERSED E 
/* 018F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0259, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER SCHWA 
/* 0190 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x025B, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER OPEN E 
/* 0191 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0192, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER F WITH HOOK 
/* 0192 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0191, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER F WITH HOOK 
/* 0193 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0260, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH HOOK 
/* 0194 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0263, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER GAMMA 
/* 0195 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01F6, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER HV 
/* 0196 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0269, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER IOTA 
/* 0197 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0268, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH STROKE 
/* 0198 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0199, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER K WITH HOOK 
/* 0199 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0198, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER K WITH HOOK 
/* 019A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x023D, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH BAR 
/* 019B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER LAMBDA WITH STROKE 
/* 019C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x026F, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER TURNED M 
/* 019D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0272, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH LEFT HOOK 
/* 019E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0220, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH LONG RIGHT LEG 
/* 019F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0275, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH MIDDLE TILDE 
/* 01A0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01A1, 0x004F,0x031B,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH HORN 
/* 01A1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01A0, 0x006F,0x031B,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH HORN 
/* 01A2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01A3, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER OI 
/* 01A3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01A2, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER OI 
/* 01A4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01A5, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER P WITH HOOK 
/* 01A5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01A4, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER P WITH HOOK 
/* 01A6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0280, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER YR 
/* 01A7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01A8, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER TONE TWO 
/* 01A8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01A7, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TONE TWO 
/* 01A9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0283, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER ESH 
/* 01AA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER REVERSED ESH LOOP 
/* 01AB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH PALATAL HOOK 
/* 01AC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01AD, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH HOOK 
/* 01AD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01AC, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH HOOK 
/* 01AE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0288, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH RETROFLEX HOOK 
/* 01AF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01B0, 0x0055,0x031B,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH HORN 
/* 01B0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01AF, 0x0075,0x031B,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH HORN 
/* 01B1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x028A, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER UPSILON 
/* 01B2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x028B, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER V WITH HOOK 
/* 01B3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01B4, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH HOOK 
/* 01B4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01B3, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH HOOK 
/* 01B5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01B6, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z WITH STROKE 
/* 01B6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01B5, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH STROKE 
/* 01B7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0292, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER EZH 
/* 01B8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01B9, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER EZH REVERSED 
/* 01B9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01B8, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER EZH REVERSED 
/* 01BA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER EZH WITH TAIL 
/* 01BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER TWO WITH STROKE 
/* 01BC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01BD, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER TONE FIVE 
/* 01BD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01BC, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TONE FIVE 
/* 01BE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER INVERTED GLOTTAL STOP WITH STROKE 
/* 01BF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01F7, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER WYNN 
/* 01C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER DENTAL CLICK 
/* 01C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER LATERAL CLICK 
/* 01C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER ALVEOLAR CLICK 
/* 01C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER RETROFLEX CLICK 
/* 01C4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01C6, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER DZ WITH CARON 
/* 01C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON 
/* 01C6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01C4, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DZ WITH CARON 
/* 01C7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01C9, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER LJ 
/* 01C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH SMALL LETTER J 
/* 01C9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01C7, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER LJ 
/* 01CA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01CC, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER NJ 
/* 01CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH SMALL LETTER J 
/* 01CC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01CA, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER NJ 
/* 01CD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01CE, 0x0041,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH CARON 
/* 01CE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01CD, 0x0061,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH CARON 
/* 01CF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01D0, 0x0049,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH CARON 
/* 01D0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01CF, 0x0069,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH CARON 
/* 01D1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01D2, 0x004F,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH CARON 
/* 01D2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01D1, 0x006F,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH CARON 
/* 01D3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01D4, 0x0055,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH CARON 
/* 01D4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01D3, 0x0075,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH CARON 
/* 01D5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01D6, 0x00DC,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DIAERESIS AND MACRON 
/* 01D6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01D5, 0x00FC,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DIAERESIS AND MACRON 
/* 01D7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01D8, 0x00DC,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DIAERESIS AND ACUTE 
/* 01D8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01D7, 0x00FC,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE 
/* 01D9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01DA, 0x00DC,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DIAERESIS AND CARON 
/* 01DA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01D9, 0x00FC,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DIAERESIS AND CARON 
/* 01DB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01DC, 0x00DC,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DIAERESIS AND GRAVE 
/* 01DC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01DB, 0x00FC,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE 
/* 01DD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x018E, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED E 
/* 01DE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01DF, 0x00C4,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH DIAERESIS AND MACRON 
/* 01DF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01DE, 0x00E4,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH DIAERESIS AND MACRON 
/* 01E0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01E1, 0x0226,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH DOT ABOVE AND MACRON 
/* 01E1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01E0, 0x0227,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH DOT ABOVE AND MACRON 
/* 01E2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01E3, 0x00C6,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER AE WITH MACRON 
/* 01E3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01E2, 0x00E6,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER AE WITH MACRON 
/* 01E4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01E5, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH STROKE 
/* 01E5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01E4, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH STROKE 
/* 01E6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01E7, 0x0047,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH CARON 
/* 01E7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01E6, 0x0067,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH CARON 
/* 01E8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01E9, 0x004B,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER K WITH CARON 
/* 01E9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01E8, 0x006B,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER K WITH CARON 
/* 01EA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01EB, 0x004F,0x0328,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH OGONEK 
/* 01EB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01EA, 0x006F,0x0328,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH OGONEK 
/* 01EC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01ED, 0x01EA,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH OGONEK AND MACRON 
/* 01ED */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01EC, 0x01EB,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH OGONEK AND MACRON 
/* 01EE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01EF, 0x01B7,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER EZH WITH CARON 
/* 01EF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01EE, 0x0292,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER EZH WITH CARON 
/* 01F0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x006A,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER J WITH CARON 
/* 01F1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01F3, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER DZ 
/* 01F2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH SMALL LETTER Z 
/* 01F3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01F1, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DZ 
/* 01F4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01F5, 0x0047,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH ACUTE 
/* 01F5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01F4, 0x0067,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH ACUTE 
/* 01F6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0195, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER HWAIR 
/* 01F7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01BF, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER WYNN 
/* 01F8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01F9, 0x004E,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH GRAVE 
/* 01F9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01F8, 0x006E,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH GRAVE 
/* 01FA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01FB, 0x00C5,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH RING ABOVE AND ACUTE 
/* 01FB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01FA, 0x00E5,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH RING ABOVE AND ACUTE 
/* 01FC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01FD, 0x00C6,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER AE WITH ACUTE 
/* 01FD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01FC, 0x00E6,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER AE WITH ACUTE 
/* 01FE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x01FF, 0x00D8,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH STROKE AND ACUTE 
/* 01FF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01FE, 0x00F8,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH STROKE AND ACUTE 
/* 0200 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0201, 0x0041,0x030F,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH DOUBLE GRAVE 
/* 0201 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0200, 0x0061,0x030F,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH DOUBLE GRAVE 
/* 0202 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0203, 0x0041,0x0311,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH INVERTED BREVE 
/* 0203 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0202, 0x0061,0x0311,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH INVERTED BREVE 
/* 0204 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0205, 0x0045,0x030F,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH DOUBLE GRAVE 
/* 0205 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0204, 0x0065,0x030F,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH DOUBLE GRAVE 
/* 0206 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0207, 0x0045,0x0311,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH INVERTED BREVE 
/* 0207 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0206, 0x0065,0x0311,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH INVERTED BREVE 
/* 0208 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0209, 0x0049,0x030F,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH DOUBLE GRAVE 
/* 0209 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0208, 0x0069,0x030F,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH DOUBLE GRAVE 
/* 020A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x020B, 0x0049,0x0311,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH INVERTED BREVE 
/* 020B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x020A, 0x0069,0x0311,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH INVERTED BREVE 
/* 020C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x020D, 0x004F,0x030F,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH DOUBLE GRAVE 
/* 020D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x020C, 0x006F,0x030F,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH DOUBLE GRAVE 
/* 020E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x020F, 0x004F,0x0311,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH INVERTED BREVE 
/* 020F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x020E, 0x006F,0x0311,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH INVERTED BREVE 
/* 0210 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0211, 0x0052,0x030F,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH DOUBLE GRAVE 
/* 0211 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0210, 0x0072,0x030F,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH DOUBLE GRAVE 
/* 0212 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0213, 0x0052,0x0311,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH INVERTED BREVE 
/* 0213 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0212, 0x0072,0x0311,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH INVERTED BREVE 
/* 0214 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0215, 0x0055,0x030F,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DOUBLE GRAVE 
/* 0215 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0214, 0x0075,0x030F,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DOUBLE GRAVE 
/* 0216 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0217, 0x0055,0x0311,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH INVERTED BREVE 
/* 0217 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0216, 0x0075,0x0311,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH INVERTED BREVE 
/* 0218 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0219, 0x0053,0x0326,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH COMMA BELOW 
/* 0219 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0218, 0x0073,0x0326,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH COMMA BELOW 
/* 021A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x021B, 0x0054,0x0326,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH COMMA BELOW 
/* 021B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x021A, 0x0074,0x0326,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH COMMA BELOW 
/* 021C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x021D, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER YOGH 
/* 021D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x021C, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER YOGH 
/* 021E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x021F, 0x0048,0x030C,0x0000,0x0000 }, // LATIN CAPITAL LETTER H WITH CARON 
/* 021F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x021E, 0x0068,0x030C,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH CARON 
/* 0220 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x019E, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH LONG RIGHT LEG 
/* 0221 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH CURL 
/* 0222 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0223, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER OU 
/* 0223 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0222, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER OU 
/* 0224 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0225, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z WITH HOOK 
/* 0225 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0224, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH HOOK 
/* 0226 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0227, 0x0041,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH DOT ABOVE 
/* 0227 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0226, 0x0061,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH DOT ABOVE 
/* 0228 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0229, 0x0045,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CEDILLA 
/* 0229 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0228, 0x0065,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CEDILLA 
/* 022A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x022B, 0x00D6,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH DIAERESIS AND MACRON 
/* 022B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x022A, 0x00F6,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH DIAERESIS AND MACRON 
/* 022C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x022D, 0x00D5,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH TILDE AND MACRON 
/* 022D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x022C, 0x00F5,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH TILDE AND MACRON 
/* 022E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x022F, 0x004F,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH DOT ABOVE 
/* 022F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x022E, 0x006F,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH DOT ABOVE 
/* 0230 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0231, 0x022E,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH DOT ABOVE AND MACRON 
/* 0231 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0230, 0x022F,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON 
/* 0232 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0233, 0x0059,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH MACRON 
/* 0233 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0232, 0x0079,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH MACRON 
/* 0234 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH CURL 
/* 0235 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH CURL 
/* 0236 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH CURL 
/* 0237 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DOTLESS J 
/* 0238 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DB DIGRAPH 
/* 0239 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER QP DIGRAPH 
/* 023A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH STROKE 
/* 023B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x023C, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER C WITH STROKE 
/* 023C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x023B, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH STROKE 
/* 023D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x019A, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH BAR 
/* 023E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH DIAGONAL STROKE 
/* 023F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH SWASH TAIL 
/* 0240 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH SWASH TAIL 
/* 0241 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0294, 0x0000,0x0000,0x0000,0x0000 }, // LATIN CAPITAL LETTER GLOTTAL STOP 
/*  242 */ { 0x0000, 0x0000, 0x0000 },
/*  243 */ { 0x0000, 0x0000, 0x0000 },
/*  244 */ { 0x0000, 0x0000, 0x0000 },
/*  245 */ { 0x0000, 0x0000, 0x0000 },
/*  246 */ { 0x0000, 0x0000, 0x0000 },
/*  247 */ { 0x0000, 0x0000, 0x0000 },
/*  248 */ { 0x0000, 0x0000, 0x0000 },
/*  249 */ { 0x0000, 0x0000, 0x0000 },
/*  24a */ { 0x0000, 0x0000, 0x0000 },
/*  24b */ { 0x0000, 0x0000, 0x0000 },
/*  24c */ { 0x0000, 0x0000, 0x0000 },
/*  24d */ { 0x0000, 0x0000, 0x0000 },
/*  24e */ { 0x0000, 0x0000, 0x0000 },
/*  24f */ { 0x0000, 0x0000, 0x0000 },
/* 0250 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED A 
/* 0251 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER ALPHA 
/* 0252 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED ALPHA 
/* 0253 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0181, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER B WITH HOOK 
/* 0254 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0186, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER OPEN O 
/* 0255 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH CURL 
/* 0256 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0189, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH TAIL 
/* 0257 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x018A, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH HOOK 
/* 0258 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER REVERSED E 
/* 0259 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x018F, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SCHWA 
/* 025A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SCHWA WITH HOOK 
/* 025B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0190, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER OPEN E 
/* 025C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER REVERSED OPEN E 
/* 025D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER REVERSED OPEN E WITH HOOK 
/* 025E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER CLOSED REVERSED OPEN E 
/* 025F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DOTLESS J WITH STROKE 
/* 0260 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0193, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH HOOK 
/* 0261 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SCRIPT G 
/* 0262 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL G 
/* 0263 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0194, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER GAMMA 
/* 0264 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER RAMS HORN 
/* 0265 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED H 
/* 0266 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH HOOK 
/* 0267 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER HENG WITH HOOK 
/* 0268 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0197, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH STROKE 
/* 0269 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0196, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER IOTA 
/* 026A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL I 
/* 026B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH MIDDLE TILDE 
/* 026C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH BELT 
/* 026D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH RETROFLEX HOOK 
/* 026E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER LEZH 
/* 026F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x019C, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED M 
/* 0270 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED M WITH LONG LEG 
/* 0271 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER M WITH HOOK 
/* 0272 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x019D, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH LEFT HOOK 
/* 0273 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH RETROFLEX HOOK 
/* 0274 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL N 
/* 0275 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x019F, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER BARRED O 
/* 0276 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL OE 
/* 0277 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER CLOSED OMEGA 
/* 0278 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER PHI 
/* 0279 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED R 
/* 027A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED R WITH LONG LEG 
/* 027B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED R WITH HOOK 
/* 027C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH LONG LEG 
/* 027D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH TAIL 
/* 027E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH FISHHOOK 
/* 027F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER REVERSED R WITH FISHHOOK 
/* 0280 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01A6, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL R 
/* 0281 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL INVERTED R 
/* 0282 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH HOOK 
/* 0283 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01A9, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER ESH 
/* 0284 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DOTLESS J WITH STROKE AND HOOK 
/* 0285 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SQUAT REVERSED ESH 
/* 0286 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER ESH WITH CURL 
/* 0287 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED T 
/* 0288 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01AE, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH RETROFLEX HOOK 
/* 0289 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER U BAR 
/* 028A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01B1, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER UPSILON 
/* 028B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01B2, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER V WITH HOOK 
/* 028C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED V 
/* 028D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED W 
/* 028E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED Y 
/* 028F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL Y 
/* 0290 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH RETROFLEX HOOK 
/* 0291 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH CURL 
/* 0292 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x01B7, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER EZH 
/* 0293 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER EZH WITH CURL 
/* 0294 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0241, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER GLOTTAL STOP 
/* 0295 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER PHARYNGEAL VOICED FRICATIVE 
/* 0296 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER INVERTED GLOTTAL STOP 
/* 0297 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER STRETCHED C 
/* 0298 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER BILABIAL CLICK 
/* 0299 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL B 
/* 029A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER CLOSED OPEN E 
/* 029B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL G WITH HOOK 
/* 029C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL H 
/* 029D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER J WITH CROSSED-TAIL 
/* 029E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED K 
/* 029F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL L 
/* 02A0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Q WITH HOOK 
/* 02A1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER GLOTTAL STOP WITH STROKE 
/* 02A2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER REVERSED GLOTTAL STOP WITH STROKE 
/* 02A3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DZ DIGRAPH 
/* 02A4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DEZH DIGRAPH 
/* 02A5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER DZ DIGRAPH WITH CURL 
/* 02A6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TS DIGRAPH 
/* 02A7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TESH DIGRAPH 
/* 02A8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TC DIGRAPH WITH CURL 
/* 02A9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER FENG DIGRAPH 
/* 02AA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER LS DIGRAPH 
/* 02AB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER LZ DIGRAPH 
/* 02AC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER BILABIAL PERCUSSIVE 
/* 02AD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER BIDENTAL PERCUSSIVE 
/* 02AE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED H WITH FISHHOOK 
/* 02AF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED H WITH FISHHOOK AND TAIL 
/* 02B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL H 
/* 02B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL H WITH HOOK 
/* 02B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL J 
/* 02B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL R 
/* 02B4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED R 
/* 02B5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED R WITH HOOK 
/* 02B6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL CAPITAL INVERTED R 
/* 02B7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL W 
/* 02B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL Y 
/* 02B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER PRIME 
/* 02BA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER DOUBLE PRIME 
/* 02BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER TURNED COMMA 
/* 02BC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER APOSTROPHE 
/* 02BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER REVERSED COMMA 
/* 02BE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER RIGHT HALF RING 
/* 02BF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LEFT HALF RING 
/* 02C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER GLOTTAL STOP 
/* 02C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER REVERSED GLOTTAL STOP 
/* 02C2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LEFT ARROWHEAD 
/* 02C3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER RIGHT ARROWHEAD 
/* 02C4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER UP ARROWHEAD 
/* 02C5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER DOWN ARROWHEAD 
/* 02C6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CIRCUMFLEX ACCENT 
/* 02C7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CARON 
/* 02C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER VERTICAL LINE 
/* 02C9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER MACRON 
/* 02CA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER ACUTE ACCENT 
/* 02CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER GRAVE ACCENT 
/* 02CC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW VERTICAL LINE 
/* 02CD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW MACRON 
/* 02CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW GRAVE ACCENT 
/* 02CF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW ACUTE ACCENT 
/* 02D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER TRIANGULAR COLON 
/* 02D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER HALF TRIANGULAR COLON 
/* 02D2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CENTRED RIGHT HALF RING 
/* 02D3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CENTRED LEFT HALF RING 
/* 02D4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER UP TACK 
/* 02D5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER DOWN TACK 
/* 02D6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER PLUS SIGN 
/* 02D7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER MINUS SIGN 
/* 02D8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BREVE 
/* 02D9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOT ABOVE 
/* 02DA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RING ABOVE 
/* 02DB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGONEK 
/* 02DC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SMALL TILDE 
/* 02DD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE ACUTE ACCENT 
/* 02DE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER RHOTIC HOOK 
/* 02DF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CROSS ACCENT 
/* 02E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL GAMMA 
/* 02E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL L 
/* 02E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL S 
/* 02E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL X 
/* 02E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL REVERSED GLOTTAL STOP 
/* 02E5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER EXTRA-HIGH TONE BAR 
/* 02E6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER HIGH TONE BAR 
/* 02E7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER MID TONE BAR 
/* 02E8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW TONE BAR 
/* 02E9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER EXTRA-LOW TONE BAR 
/* 02EA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER YIN DEPARTING TONE MARK 
/* 02EB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER YANG DEPARTING TONE MARK 
/* 02EC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER VOICING 
/* 02ED */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER UNASPIRATED 
/* 02EE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER DOUBLE APOSTROPHE 
/* 02EF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW DOWN ARROWHEAD 
/* 02F0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW UP ARROWHEAD 
/* 02F1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW LEFT ARROWHEAD 
/* 02F2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW RIGHT ARROWHEAD 
/* 02F3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW RING 
/* 02F4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER MIDDLE GRAVE ACCENT 
/* 02F5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER MIDDLE DOUBLE GRAVE ACCENT 
/* 02F6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER MIDDLE DOUBLE ACUTE ACCENT 
/* 02F7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW TILDE 
/* 02F8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER RAISED COLON 
/* 02F9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER BEGIN HIGH TONE 
/* 02FA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER END HIGH TONE 
/* 02FB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER BEGIN LOW TONE 
/* 02FC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER END LOW TONE 
/* 02FD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SHELF 
/* 02FE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER OPEN SHELF 
/* 02FF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER LOW LEFT ARROW 
/* 0300 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING GRAVE ACCENT 
/* 0301 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ACUTE ACCENT 
/* 0302 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CIRCUMFLEX ACCENT 
/* 0303 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING TILDE 
/* 0304 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING MACRON 
/* 0305 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING OVERLINE 
/* 0306 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING BREVE 
/* 0307 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOT ABOVE 
/* 0308 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DIAERESIS 
/* 0309 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING HOOK ABOVE 
/* 030A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RING ABOVE 
/* 030B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE ACUTE ACCENT 
/* 030C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CARON 
/* 030D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING VERTICAL LINE ABOVE 
/* 030E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE VERTICAL LINE ABOVE 
/* 030F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE GRAVE ACCENT 
/* 0310 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CANDRABINDU 
/* 0311 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING INVERTED BREVE 
/* 0312 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING TURNED COMMA ABOVE 
/* 0313 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING COMMA ABOVE 
/* 0314 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING REVERSED COMMA ABOVE 
/* 0315 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING COMMA ABOVE RIGHT 
/* 0316 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING GRAVE ACCENT BELOW 
/* 0317 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ACUTE ACCENT BELOW 
/* 0318 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT TACK BELOW 
/* 0319 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RIGHT TACK BELOW 
/* 031A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT ANGLE ABOVE 
/* 031B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING HORN 
/* 031C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT HALF RING BELOW 
/* 031D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING UP TACK BELOW 
/* 031E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOWN TACK BELOW 
/* 031F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING PLUS SIGN BELOW 
/* 0320 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING MINUS SIGN BELOW 
/* 0321 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING PALATALIZED HOOK BELOW 
/* 0322 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RETROFLEX HOOK BELOW 
/* 0323 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOT BELOW 
/* 0324 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DIAERESIS BELOW 
/* 0325 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RING BELOW 
/* 0326 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING COMMA BELOW 
/* 0327 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CEDILLA 
/* 0328 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING OGONEK 
/* 0329 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING VERTICAL LINE BELOW 
/* 032A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING BRIDGE BELOW 
/* 032B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING INVERTED DOUBLE ARCH BELOW 
/* 032C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CARON BELOW 
/* 032D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CIRCUMFLEX ACCENT BELOW 
/* 032E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING BREVE BELOW 
/* 032F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING INVERTED BREVE BELOW 
/* 0330 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING TILDE BELOW 
/* 0331 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING MACRON BELOW 
/* 0332 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LOW LINE 
/* 0333 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE LOW LINE 
/* 0334 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING TILDE OVERLAY 
/* 0335 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING SHORT STROKE OVERLAY 
/* 0336 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LONG STROKE OVERLAY 
/* 0337 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING SHORT SOLIDUS OVERLAY 
/* 0338 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LONG SOLIDUS OVERLAY 
/* 0339 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RIGHT HALF RING BELOW 
/* 033A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING INVERTED BRIDGE BELOW 
/* 033B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING SQUARE BELOW 
/* 033C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING SEAGULL BELOW 
/* 033D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING X ABOVE 
/* 033E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING VERTICAL TILDE 
/* 033F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE OVERLINE 
/* 0340 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0300,0x0000,0x0000,0x0000 }, // COMBINING GRAVE TONE MARK 
/* 0341 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0301,0x0000,0x0000,0x0000 }, // COMBINING ACUTE TONE MARK 
/* 0342 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING GREEK PERISPOMENI 
/* 0343 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0313,0x0000,0x0000,0x0000 }, // COMBINING GREEK KORONIS 
/* 0344 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0308,0x0301,0x0000,0x0000 }, // COMBINING GREEK DIALYTIKA TONOS 
/* 0345 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING GREEK YPOGEGRAMMENI 
/* 0346 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING BRIDGE ABOVE 
/* 0347 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING EQUALS SIGN BELOW 
/* 0348 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE VERTICAL LINE BELOW 
/* 0349 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT ANGLE BELOW 
/* 034A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING NOT TILDE ABOVE 
/* 034B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING HOMOTHETIC ABOVE 
/* 034C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ALMOST EQUAL TO ABOVE 
/* 034D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT RIGHT ARROW BELOW 
/* 034E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING UPWARDS ARROW BELOW 
/* 034F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING GRAPHEME JOINER 
/* 0350 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RIGHT ARROWHEAD ABOVE 
/* 0351 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT HALF RING ABOVE 
/* 0352 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING FERMATA 
/* 0353 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING X BELOW 
/* 0354 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT ARROWHEAD BELOW 
/* 0355 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RIGHT ARROWHEAD BELOW 
/* 0356 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RIGHT ARROWHEAD AND UP ARROWHEAD BELOW 
/* 0357 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RIGHT HALF RING ABOVE 
/* 0358 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOT ABOVE RIGHT 
/* 0359 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ASTERISK BELOW 
/* 035A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE RING BELOW 
/* 035B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ZIGZAG ABOVE 
/* 035C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE BREVE BELOW 
/* 035D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE BREVE 
/* 035E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE MACRON 
/* 035F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE MACRON BELOW 
/* 0360 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE TILDE 
/* 0361 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE INVERTED BREVE 
/* 0362 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE RIGHTWARDS ARROW BELOW 
/* 0363 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER A 
/* 0364 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER E 
/* 0365 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER I 
/* 0366 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER O 
/* 0367 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER U 
/* 0368 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER C 
/* 0369 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER D 
/* 036A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER H 
/* 036B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER M 
/* 036C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER R 
/* 036D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER T 
/* 036E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER V 
/* 036F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LATIN SMALL LETTER X 
/*  370 */ { 0x0000, 0x0000, 0x0000 },
/*  371 */ { 0x0000, 0x0000, 0x0000 },
/*  372 */ { 0x0000, 0x0000, 0x0000 },
/*  373 */ { 0x0000, 0x0000, 0x0000 },
/* 0374 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x02B9,0x0000,0x0000,0x0000 }, // GREEK NUMERAL SIGN 
/* 0375 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LOWER NUMERAL SIGN 
/*  376 */ { 0x0000, 0x0000, 0x0000 },
/*  377 */ { 0x0000, 0x0000, 0x0000 },
/*  378 */ { 0x0000, 0x0000, 0x0000 },
/*  379 */ { 0x0000, 0x0000, 0x0000 },
/* 037A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK YPOGEGRAMMENI 
/*  37b */ { 0x0000, 0x0000, 0x0000 },
/*  37c */ { 0x0000, 0x0000, 0x0000 },
/*  37d */ { 0x0000, 0x0000, 0x0000 },
/* 037E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x003B,0x0000,0x0000,0x0000 }, // GREEK QUESTION MARK 
/*  37f */ { 0x0000, 0x0000, 0x0000 },
/*  380 */ { 0x0000, 0x0000, 0x0000 },
/*  381 */ { 0x0000, 0x0000, 0x0000 },
/*  382 */ { 0x0000, 0x0000, 0x0000 },
/*  383 */ { 0x0000, 0x0000, 0x0000 },
/* 0384 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK TONOS 
/* 0385 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x00A8,0x0301,0x0000,0x0000 }, // GREEK DIALYTIKA TONOS 
/* 0386 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03AC, 0x0391,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH TONOS 
/* 0387 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x00B7,0x0000,0x0000,0x0000 }, // GREEK ANO TELEIA 
/* 0388 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03AD, 0x0395,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH TONOS 
/* 0389 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03AE, 0x0397,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH TONOS 
/* 038A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03AF, 0x0399,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH TONOS 
/*  38b */ { 0x0000, 0x0000, 0x0000 },
/* 038C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03CC, 0x039F,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH TONOS 
/*  38d */ { 0x0000, 0x0000, 0x0000 },
/* 038E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03CD, 0x03A5,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH TONOS 
/* 038F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03CE, 0x03A9,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH TONOS 
/* 0390 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03CA,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS 
/* 0391 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B1, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA 
/* 0392 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B2, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER BETA 
/* 0393 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B3, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER GAMMA 
/* 0394 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B4, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER DELTA 
/* 0395 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B5, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON 
/* 0396 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B6, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER ZETA 
/* 0397 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B7, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA 
/* 0398 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B8, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER THETA 
/* 0399 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B9, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA 
/* 039A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03BA, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER KAPPA 
/* 039B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03BB, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER LAMDA 
/* 039C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03BC, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER MU 
/* 039D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03BD, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER NU 
/* 039E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03BE, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER XI 
/* 039F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03BF, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON 
/* 03A0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C0, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER PI 
/* 03A1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C1, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER RHO 
/*  3a2 */ { 0x0000, 0x0000, 0x0000 },
/* 03A3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C3, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER SIGMA 
/* 03A4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C4, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER TAU 
/* 03A5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C5, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON 
/* 03A6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C6, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER PHI 
/* 03A7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C7, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER CHI 
/* 03A8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C8, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER PSI 
/* 03A9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03C9, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA 
/* 03AA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03CA, 0x0399,0x0308,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH DIALYTIKA 
/* 03AB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03CB, 0x03A5,0x0308,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA 
/* 03AC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0386, 0x03B1,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH TONOS 
/* 03AD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0388, 0x03B5,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH TONOS 
/* 03AE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0389, 0x03B7,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH TONOS 
/* 03AF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x038A, 0x03B9,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH TONOS 
/* 03B0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03CB,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS 
/* 03B1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0391, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA 
/* 03B2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0392, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER BETA 
/* 03B3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0393, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER GAMMA 
/* 03B4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0394, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER DELTA 
/* 03B5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0395, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON 
/* 03B6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0396, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER ZETA 
/* 03B7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0397, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER ETA 
/* 03B8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0398, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER THETA 
/* 03B9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0399, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA 
/* 03BA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x039A, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER KAPPA 
/* 03BB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x039B, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER LAMDA 
/* 03BC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x039C, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER MU 
/* 03BD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x039D, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER NU 
/* 03BE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x039E, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER XI 
/* 03BF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x039F, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON 
/* 03C0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A0, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER PI 
/* 03C1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A1, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER RHO 
/* 03C2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A3, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER FINAL SIGMA 
/* 03C3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A3, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER SIGMA 
/* 03C4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A4, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER TAU 
/* 03C5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A5, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON 
/* 03C6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A6, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER PHI 
/* 03C7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A7, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER CHI 
/* 03C8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A8, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER PSI 
/* 03C9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A9, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA 
/* 03CA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03AA, 0x03B9,0x0308,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DIALYTIKA 
/* 03CB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03AB, 0x03C5,0x0308,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA 
/* 03CC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x038C, 0x03BF,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH TONOS 
/* 03CD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x038E, 0x03C5,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH TONOS 
/* 03CE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x038F, 0x03C9,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH TONOS 
/*  3cf */ { 0x0000, 0x0000, 0x0000 },
/* 03D0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0392, 0x0000,0x0000,0x0000,0x0000 }, // GREEK BETA SYMBOL 
/* 03D1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0398, 0x0000,0x0000,0x0000,0x0000 }, // GREEK THETA SYMBOL 
/* 03D2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK UPSILON WITH HOOK SYMBOL 
/* 03D3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x03D2,0x0301,0x0000,0x0000 }, // GREEK UPSILON WITH ACUTE AND HOOK SYMBOL 
/* 03D4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x03D2,0x0308,0x0000,0x0000 }, // GREEK UPSILON WITH DIAERESIS AND HOOK SYMBOL 
/* 03D5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A6, 0x0000,0x0000,0x0000,0x0000 }, // GREEK PHI SYMBOL 
/* 03D6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A0, 0x0000,0x0000,0x0000,0x0000 }, // GREEK PI SYMBOL 
/* 03D7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK KAI SYMBOL 
/* 03D8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03D9, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER ARCHAIC KOPPA 
/* 03D9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03D8, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER ARCHAIC KOPPA 
/* 03DA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03DB, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER STIGMA 
/* 03DB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03DA, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER STIGMA 
/* 03DC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03DD, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER DIGAMMA 
/* 03DD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03DC, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER DIGAMMA 
/* 03DE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03DF, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER KOPPA 
/* 03DF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03DE, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER KOPPA 
/* 03E0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03E1, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER SAMPI 
/* 03E1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03E0, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER SAMPI 
/* 03E2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03E3, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC CAPITAL LETTER SHEI 
/* 03E3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03E2, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC SMALL LETTER SHEI 
/* 03E4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03E5, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC CAPITAL LETTER FEI 
/* 03E5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03E4, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC SMALL LETTER FEI 
/* 03E6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03E7, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC CAPITAL LETTER KHEI 
/* 03E7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03E6, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC SMALL LETTER KHEI 
/* 03E8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03E9, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC CAPITAL LETTER HORI 
/* 03E9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03E8, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC SMALL LETTER HORI 
/* 03EA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03EB, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC CAPITAL LETTER GANGIA 
/* 03EB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03EA, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC SMALL LETTER GANGIA 
/* 03EC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03ED, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC CAPITAL LETTER SHIMA 
/* 03ED */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03EC, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC SMALL LETTER SHIMA 
/* 03EE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03EF, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC CAPITAL LETTER DEI 
/* 03EF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03EE, 0x0000,0x0000,0x0000,0x0000 }, // COPTIC SMALL LETTER DEI 
/* 03F0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x039A, 0x0000,0x0000,0x0000,0x0000 }, // GREEK KAPPA SYMBOL 
/* 03F1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03A1, 0x0000,0x0000,0x0000,0x0000 }, // GREEK RHO SYMBOL 
/* 03F2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03F9, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LUNATE SIGMA SYMBOL 
/* 03F3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER YOT 
/* 03F4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03B8, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL THETA SYMBOL 
/* 03F5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0395, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LUNATE EPSILON SYMBOL 
/* 03F6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK REVERSED LUNATE EPSILON SYMBOL 
/* 03F7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03F8, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER SHO 
/* 03F8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03F7, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER SHO 
/* 03F9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03F2, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LUNATE SIGMA SYMBOL 
/* 03FA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x03FB, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER SAN 
/* 03FB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x03FA, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER SAN 
/* 03FC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK RHO WITH STROKE SYMBOL 
/* 03FD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL REVERSED LUNATE SIGMA SYMBOL 
/* 03FE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL DOTTED LUNATE SIGMA SYMBOL 
/* 03FF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK CAPITAL REVERSED DOTTED LUNATE SIGMA SYMBOL 
/* 0400 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0450, 0x0415,0x0300,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IE WITH GRAVE 
/* 0401 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0451, 0x0415,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IO 
/* 0402 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0452, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER DJE 
/* 0403 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0453, 0x0413,0x0301,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER GJE 
/* 0404 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0454, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER UKRAINIAN IE 
/* 0405 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0455, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER DZE 
/* 0406 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0456, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I 
/* 0407 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0457, 0x0406,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER YI 
/* 0408 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0458, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER JE 
/* 0409 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0459, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER LJE 
/* 040A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x045A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER NJE 
/* 040B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x045B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER TSHE 
/* 040C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x045C, 0x041A,0x0301,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KJE 
/* 040D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x045D, 0x0418,0x0300,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER I WITH GRAVE 
/* 040E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x045E, 0x0423,0x0306,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SHORT U 
/* 040F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x045F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER DZHE 
/* 0410 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0430, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER A 
/* 0411 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0431, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER BE 
/* 0412 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0432, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER VE 
/* 0413 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0433, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER GHE 
/* 0414 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0434, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER DE 
/* 0415 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0435, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IE 
/* 0416 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0436, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ZHE 
/* 0417 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0437, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ZE 
/* 0418 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0438, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER I 
/* 0419 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0439, 0x0000,0x0000,0x0000,0x0000 }, //0x0418,0x0306,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SHORT I 
/* 041A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x043A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KA 
/* 041B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x043B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EL 
/* 041C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x043C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EM 
/* 041D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x043D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EN 
/* 041E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x043E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER O 
/* 041F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x043F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER PE 
/* 0420 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0440, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ER 
/* 0421 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0441, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ES 
/* 0422 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0442, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER TE 
/* 0423 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0443, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER U 
/* 0424 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0444, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EF 
/* 0425 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0445, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER HA 
/* 0426 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0446, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER TSE 
/* 0427 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0447, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER CHE 
/* 0428 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0448, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SHA 
/* 0429 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0449, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SHCHA 
/* 042A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x044A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER HARD SIGN 
/* 042B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x044B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER YERU 
/* 042C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x044C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SOFT SIGN 
/* 042D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x044D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER E 
/* 042E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x044E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER YU 
/* 042F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x044F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER YA 
/* 0430 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0410, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER A 
/* 0431 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0411, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER BE 
/* 0432 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0412, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER VE 
/* 0433 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0413, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER GHE 
/* 0434 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0414, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER DE 
/* 0435 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0415, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IE 
/* 0436 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0416, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ZHE 
/* 0437 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0417, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ZE 
/* 0438 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0418, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER I 
/* 0439 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0419, 0x0000,0x0000,0x0000,0x0000 }, //0x0438,0x0306,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SHORT I 
/* 043A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x041A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KA 
/* 043B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x041B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EL 
/* 043C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x041C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EM 
/* 043D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x041D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EN 
/* 043E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x041E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER O 
/* 043F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x041F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER PE 
/* 0440 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0420, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ER 
/* 0441 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0421, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ES 
/* 0442 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0422, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER TE 
/* 0443 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0423, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER U 
/* 0444 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0424, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EF 
/* 0445 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0425, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER HA 
/* 0446 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0426, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER TSE 
/* 0447 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0427, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER CHE 
/* 0448 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0428, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SHA 
/* 0449 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0429, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SHCHA 
/* 044A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x042A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER HARD SIGN 
/* 044B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x042B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER YERU 
/* 044C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x042C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SOFT SIGN 
/* 044D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x042D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER E 
/* 044E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x042E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER YU 
/* 044F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x042F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER YA 
/* 0450 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0400, 0x0435,0x0300,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IE WITH GRAVE 
/* 0451 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0401, 0x0435,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IO 
/* 0452 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0402, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER DJE 
/* 0453 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0403, 0x0433,0x0301,0x0000,0x0000 }, // CYRILLIC SMALL LETTER GJE 
/* 0454 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0404, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER UKRAINIAN IE 
/* 0455 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0405, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER DZE 
/* 0456 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0406, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I 
/* 0457 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0407, 0x0456,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER YI 
/* 0458 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0408, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER JE 
/* 0459 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0409, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER LJE 
/* 045A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x040A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER NJE 
/* 045B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x040B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER TSHE 
/* 045C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x040C, 0x043A,0x0301,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KJE 
/* 045D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x040D, 0x0438,0x0300,0x0000,0x0000 }, // CYRILLIC SMALL LETTER I WITH GRAVE 
/* 045E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x040E, 0x0443,0x0306,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SHORT U 
/* 045F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x040F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER DZHE 
/* 0460 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0461, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER OMEGA 
/* 0461 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0460, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER OMEGA 
/* 0462 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0463, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER YAT 
/* 0463 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0462, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER YAT 
/* 0464 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0465, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IOTIFIED E 
/* 0465 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0464, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IOTIFIED E 
/* 0466 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0467, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER LITTLE YUS 
/* 0467 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0466, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER LITTLE YUS 
/* 0468 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0469, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IOTIFIED LITTLE YUS 
/* 0469 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0468, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IOTIFIED LITTLE YUS 
/* 046A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x046B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER BIG YUS 
/* 046B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x046A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER BIG YUS 
/* 046C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x046D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IOTIFIED BIG YUS 
/* 046D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x046C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IOTIFIED BIG YUS 
/* 046E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x046F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KSI 
/* 046F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x046E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KSI 
/* 0470 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0471, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER PSI 
/* 0471 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0470, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER PSI 
/* 0472 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0473, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER FITA 
/* 0473 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0472, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER FITA 
/* 0474 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0475, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IZHITSA 
/* 0475 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0474, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IZHITSA 
/* 0476 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0477, 0x0474,0x030F,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IZHITSA WITH DOUBLE GRAVE ACCENT 
/* 0477 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0476, 0x0475,0x030F,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IZHITSA WITH DOUBLE GRAVE ACCENT 
/* 0478 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0479, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER UK 
/* 0479 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0478, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER UK 
/* 047A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x047B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ROUND OMEGA 
/* 047B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x047A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ROUND OMEGA 
/* 047C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x047D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER OMEGA WITH TITLO 
/* 047D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x047C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER OMEGA WITH TITLO 
/* 047E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x047F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER OT 
/* 047F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x047E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER OT 
/* 0480 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0481, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOPPA 
/* 0481 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0480, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOPPA 
/* 0482 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC THOUSANDS SIGN 
/* 0483 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CYRILLIC TITLO 
/* 0484 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CYRILLIC PALATALIZATION 
/* 0485 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CYRILLIC DASIA PNEUMATA 
/* 0486 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CYRILLIC PSILI PNEUMATA 
/*  487 */ { 0x0000, 0x0000, 0x0000 },
/* 0488 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CYRILLIC HUNDRED THOUSANDS SIGN 
/* 0489 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CYRILLIC MILLIONS SIGN 
/* 048A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x048B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SHORT I WITH TAIL 
/* 048B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x048A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SHORT I WITH TAIL 
/* 048C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x048D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SEMISOFT SIGN 
/* 048D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x048C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SEMISOFT SIGN 
/* 048E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x048F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ER WITH TICK 
/* 048F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x048E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ER WITH TICK 
/* 0490 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0491, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER GHE WITH UPTURN 
/* 0491 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0490, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER GHE WITH UPTURN 
/* 0492 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0493, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER GHE WITH STROKE 
/* 0493 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0492, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER GHE WITH STROKE 
/* 0494 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0495, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER GHE WITH MIDDLE HOOK 
/* 0495 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0494, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER GHE WITH MIDDLE HOOK 
/* 0496 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0497, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ZHE WITH DESCENDER 
/* 0497 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0496, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ZHE WITH DESCENDER 
/* 0498 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0499, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ZE WITH DESCENDER 
/* 0499 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0498, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ZE WITH DESCENDER 
/* 049A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x049B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KA WITH DESCENDER 
/* 049B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x049A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KA WITH DESCENDER 
/* 049C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x049D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KA WITH VERTICAL STROKE 
/* 049D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x049C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KA WITH VERTICAL STROKE 
/* 049E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x049F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KA WITH STROKE 
/* 049F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x049E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KA WITH STROKE 
/* 04A0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04A1, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER BASHKIR KA 
/* 04A1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04A0, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER BASHKIR KA 
/* 04A2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04A3, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EN WITH DESCENDER 
/* 04A3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04A2, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EN WITH DESCENDER 
/* 04A4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04A5, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LIGATURE EN GHE 
/* 04A5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04A4, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LIGATURE EN GHE 
/* 04A6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04A7, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER PE WITH MIDDLE HOOK 
/* 04A7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04A6, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER PE WITH MIDDLE HOOK 
/* 04A8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04A9, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ABKHASIAN HA 
/* 04A9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04A8, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ABKHASIAN HA 
/* 04AA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04AB, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ES WITH DESCENDER 
/* 04AB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04AA, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ES WITH DESCENDER 
/* 04AC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04AD, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER TE WITH DESCENDER 
/* 04AD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04AC, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER TE WITH DESCENDER 
/* 04AE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04AF, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER STRAIGHT U 
/* 04AF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04AE, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER STRAIGHT U 
/* 04B0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04B1, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER STRAIGHT U WITH STROKE 
/* 04B1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04B0, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER STRAIGHT U WITH STROKE 
/* 04B2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04B3, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER HA WITH DESCENDER 
/* 04B3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04B2, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER HA WITH DESCENDER 
/* 04B4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04B5, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LIGATURE TE TSE 
/* 04B5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04B4, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LIGATURE TE TSE 
/* 04B6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04B7, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER CHE WITH DESCENDER 
/* 04B7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04B6, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER CHE WITH DESCENDER 
/* 04B8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04B9, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER CHE WITH VERTICAL STROKE 
/* 04B9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04B8, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER CHE WITH VERTICAL STROKE 
/* 04BA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04BB, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SHHA 
/* 04BB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04BA, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SHHA 
/* 04BC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04BD, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ABKHASIAN CHE 
/* 04BD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04BC, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ABKHASIAN CHE 
/* 04BE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04BF, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ABKHASIAN CHE WITH DESCENDER 
/* 04BF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04BE, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ABKHASIAN CHE WITH DESCENDER 
/* 04C0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC LETTER PALOCHKA 
/* 04C1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04C2, 0x0416,0x0306,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ZHE WITH BREVE 
/* 04C2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04C1, 0x0436,0x0306,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ZHE WITH BREVE 
/* 04C3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04C4, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KA WITH HOOK 
/* 04C4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04C3, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KA WITH HOOK 
/* 04C5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04C6, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EL WITH TAIL 
/* 04C6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04C5, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EL WITH TAIL 
/* 04C7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04C8, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EN WITH HOOK 
/* 04C8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04C7, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EN WITH HOOK 
/* 04C9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04CA, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EN WITH TAIL 
/* 04CA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04C9, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EN WITH TAIL 
/* 04CB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04CC, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KHAKASSIAN CHE 
/* 04CC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04CB, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KHAKASSIAN CHE 
/* 04CD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04CE, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER EM WITH TAIL 
/* 04CE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04CD, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER EM WITH TAIL 
/*  4cf */ { 0x0000, 0x0000, 0x0000 },
/* 04D0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04D1, 0x0410,0x0306,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER A WITH BREVE 
/* 04D1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04D0, 0x0430,0x0306,0x0000,0x0000 }, // CYRILLIC SMALL LETTER A WITH BREVE 
/* 04D2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04D3, 0x0410,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER A WITH DIAERESIS 
/* 04D3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04D2, 0x0430,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER A WITH DIAERESIS 
/* 04D4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04D5, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LIGATURE A IE 
/* 04D5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04D4, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LIGATURE A IE 
/* 04D6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04D7, 0x0415,0x0306,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER IE WITH BREVE 
/* 04D7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04D6, 0x0435,0x0306,0x0000,0x0000 }, // CYRILLIC SMALL LETTER IE WITH BREVE 
/* 04D8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04D9, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SCHWA 
/* 04D9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04D8, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SCHWA 
/* 04DA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04DB, 0x04D8,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER SCHWA WITH DIAERESIS 
/* 04DB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04DA, 0x04D9,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER SCHWA WITH DIAERESIS 
/* 04DC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04DD, 0x0416,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ZHE WITH DIAERESIS 
/* 04DD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04DC, 0x0436,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ZHE WITH DIAERESIS 
/* 04DE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04DF, 0x0417,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ZE WITH DIAERESIS 
/* 04DF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04DE, 0x0437,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ZE WITH DIAERESIS 
/* 04E0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04E1, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER ABKHASIAN DZE 
/* 04E1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04E0, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER ABKHASIAN DZE 
/* 04E2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04E3, 0x0418,0x0304,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER I WITH MACRON 
/* 04E3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04E2, 0x0438,0x0304,0x0000,0x0000 }, // CYRILLIC SMALL LETTER I WITH MACRON 
/* 04E4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04E5, 0x0418,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER I WITH DIAERESIS 
/* 04E5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04E4, 0x0438,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER I WITH DIAERESIS 
/* 04E6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04E7, 0x041E,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER O WITH DIAERESIS 
/* 04E7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04E6, 0x043E,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER O WITH DIAERESIS 
/* 04E8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04E9, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER BARRED O 
/* 04E9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04E8, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER BARRED O 
/* 04EA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04EB, 0x04E8,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER BARRED O WITH DIAERESIS 
/* 04EB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04EA, 0x04E9,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER BARRED O WITH DIAERESIS 
/* 04EC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04ED, 0x042D,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER E WITH DIAERESIS 
/* 04ED */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04EC, 0x044D,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER E WITH DIAERESIS 
/* 04EE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04EF, 0x0423,0x0304,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER U WITH MACRON 
/* 04EF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04EE, 0x0443,0x0304,0x0000,0x0000 }, // CYRILLIC SMALL LETTER U WITH MACRON 
/* 04F0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04F1, 0x0423,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER U WITH DIAERESIS 
/* 04F1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04F0, 0x0443,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER U WITH DIAERESIS 
/* 04F2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04F3, 0x0423,0x030B,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER U WITH DOUBLE ACUTE 
/* 04F3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04F2, 0x0443,0x030B,0x0000,0x0000 }, // CYRILLIC SMALL LETTER U WITH DOUBLE ACUTE 
/* 04F4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04F5, 0x0427,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER CHE WITH DIAERESIS 
/* 04F5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04F4, 0x0447,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER CHE WITH DIAERESIS 
/* 04F6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04F7, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER GHE WITH DESCENDER 
/* 04F7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04F6, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER GHE WITH DESCENDER 
/* 04F8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x04F9, 0x042B,0x0308,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER YERU WITH DIAERESIS 
/* 04F9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x04F8, 0x044B,0x0308,0x0000,0x0000 }, // CYRILLIC SMALL LETTER YERU WITH DIAERESIS 
/*  4fa */ { 0x0000, 0x0000, 0x0000 },
/*  4fb */ { 0x0000, 0x0000, 0x0000 },
/*  4fc */ { 0x0000, 0x0000, 0x0000 },
/*  4fd */ { 0x0000, 0x0000, 0x0000 },
/*  4fe */ { 0x0000, 0x0000, 0x0000 },
/*  4ff */ { 0x0000, 0x0000, 0x0000 },
/* 0500 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0501, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOMI DE 
/* 0501 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0500, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOMI DE 
/* 0502 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0503, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOMI DJE 
/* 0503 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0502, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOMI DJE 
/* 0504 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0505, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOMI ZJE 
/* 0505 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0504, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOMI ZJE 
/* 0506 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0507, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOMI DZJE 
/* 0507 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0506, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOMI DZJE 
/* 0508 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0509, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOMI LJE 
/* 0509 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0508, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOMI LJE 
/* 050A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x050B, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOMI NJE 
/* 050B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x050A, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOMI NJE 
/* 050C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x050D, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOMI SJE 
/* 050D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x050C, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOMI SJE 
/* 050E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x050F, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC CAPITAL LETTER KOMI TJE 
/* 050F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x050E, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC SMALL LETTER KOMI TJE 
/*  510 */ { 0x0000, 0x0000, 0x0000 },
/*  511 */ { 0x0000, 0x0000, 0x0000 },
/*  512 */ { 0x0000, 0x0000, 0x0000 },
/*  513 */ { 0x0000, 0x0000, 0x0000 },
/*  514 */ { 0x0000, 0x0000, 0x0000 },
/*  515 */ { 0x0000, 0x0000, 0x0000 },
/*  516 */ { 0x0000, 0x0000, 0x0000 },
/*  517 */ { 0x0000, 0x0000, 0x0000 },
/*  518 */ { 0x0000, 0x0000, 0x0000 },
/*  519 */ { 0x0000, 0x0000, 0x0000 },
/*  51a */ { 0x0000, 0x0000, 0x0000 },
/*  51b */ { 0x0000, 0x0000, 0x0000 },
/*  51c */ { 0x0000, 0x0000, 0x0000 },
/*  51d */ { 0x0000, 0x0000, 0x0000 },
/*  51e */ { 0x0000, 0x0000, 0x0000 },
/*  51f */ { 0x0000, 0x0000, 0x0000 },
/*  520 */ { 0x0000, 0x0000, 0x0000 },
/*  521 */ { 0x0000, 0x0000, 0x0000 },
/*  522 */ { 0x0000, 0x0000, 0x0000 },
/*  523 */ { 0x0000, 0x0000, 0x0000 },
/*  524 */ { 0x0000, 0x0000, 0x0000 },
/*  525 */ { 0x0000, 0x0000, 0x0000 },
/*  526 */ { 0x0000, 0x0000, 0x0000 },
/*  527 */ { 0x0000, 0x0000, 0x0000 },
/*  528 */ { 0x0000, 0x0000, 0x0000 },
/*  529 */ { 0x0000, 0x0000, 0x0000 },
/*  52a */ { 0x0000, 0x0000, 0x0000 },
/*  52b */ { 0x0000, 0x0000, 0x0000 },
/*  52c */ { 0x0000, 0x0000, 0x0000 },
/*  52d */ { 0x0000, 0x0000, 0x0000 },
/*  52e */ { 0x0000, 0x0000, 0x0000 },
/*  52f */ { 0x0000, 0x0000, 0x0000 },
/*  530 */ { 0x0000, 0x0000, 0x0000 },
/* 0531 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0561, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER AYB 
/* 0532 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0562, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER BEN 
/* 0533 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0563, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER GIM 
/* 0534 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0564, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER DA 
/* 0535 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0565, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER ECH 
/* 0536 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0566, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER ZA 
/* 0537 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0567, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER EH 
/* 0538 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0568, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER ET 
/* 0539 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0569, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER TO 
/* 053A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x056A, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER ZHE 
/* 053B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x056B, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER INI 
/* 053C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x056C, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER LIWN 
/* 053D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x056D, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER XEH 
/* 053E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x056E, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER CA 
/* 053F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x056F, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER KEN 
/* 0540 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0570, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER HO 
/* 0541 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0571, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER JA 
/* 0542 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0572, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER GHAD 
/* 0543 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0573, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER CHEH 
/* 0544 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0574, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER MEN 
/* 0545 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0575, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER YI 
/* 0546 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0576, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER NOW 
/* 0547 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0577, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER SHA 
/* 0548 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0578, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER VO 
/* 0549 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0579, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER CHA 
/* 054A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x057A, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER PEH 
/* 054B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x057B, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER JHEH 
/* 054C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x057C, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER RA 
/* 054D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x057D, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER SEH 
/* 054E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x057E, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER VEW 
/* 054F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x057F, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER TIWN 
/* 0550 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0580, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER REH 
/* 0551 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0581, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER CO 
/* 0552 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0582, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER YIWN 
/* 0553 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0583, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER PIWR 
/* 0554 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0584, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER KEH 
/* 0555 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0585, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER OH 
/* 0556 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x0586, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN CAPITAL LETTER FEH 
/*  557 */ { 0x0000, 0x0000, 0x0000 },
/*  558 */ { 0x0000, 0x0000, 0x0000 },
/* 0559 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN MODIFIER LETTER LEFT HALF RING 
/* 055A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN APOSTROPHE 
/* 055B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN EMPHASIS MARK 
/* 055C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN EXCLAMATION MARK 
/* 055D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN COMMA 
/* 055E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN QUESTION MARK 
/* 055F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN ABBREVIATION MARK 
/*  560 */ { 0x0000, 0x0000, 0x0000 },
/* 0561 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0531, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER AYB 
/* 0562 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0532, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER BEN 
/* 0563 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0533, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER GIM 
/* 0564 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0534, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER DA 
/* 0565 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0535, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER ECH 
/* 0566 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0536, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER ZA 
/* 0567 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0537, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER EH 
/* 0568 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0538, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER ET 
/* 0569 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0539, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER TO 
/* 056A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x053A, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER ZHE 
/* 056B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x053B, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER INI 
/* 056C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x053C, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER LIWN 
/* 056D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x053D, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER XEH 
/* 056E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x053E, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER CA 
/* 056F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x053F, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER KEN 
/* 0570 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0540, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER HO 
/* 0571 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0541, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER JA 
/* 0572 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0542, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER GHAD 
/* 0573 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0543, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER CHEH 
/* 0574 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0544, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER MEN 
/* 0575 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0545, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER YI 
/* 0576 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0546, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER NOW 
/* 0577 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0547, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER SHA 
/* 0578 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0548, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER VO 
/* 0579 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0549, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER CHA 
/* 057A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x054A, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER PEH 
/* 057B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x054B, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER JHEH 
/* 057C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x054C, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER RA 
/* 057D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x054D, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER SEH 
/* 057E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x054E, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER VEW 
/* 057F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x054F, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER TIWN 
/* 0580 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0550, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER REH 
/* 0581 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0551, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER CO 
/* 0582 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0552, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER YIWN 
/* 0583 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0553, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER PIWR 
/* 0584 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0554, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER KEH 
/* 0585 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0555, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER OH 
/* 0586 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0556, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LETTER FEH 
/* 0587 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN SMALL LIGATURE ECH YIWN 
/*  588 */ { 0x0000, 0x0000, 0x0000 },
/* 0589 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN FULL STOP 
/* 058A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARMENIAN HYPHEN 
/*  58b */ { 0x0000, 0x0000, 0x0000 },
/*  58c */ { 0x0000, 0x0000, 0x0000 },
/*  58d */ { 0x0000, 0x0000, 0x0000 },
/*  58e */ { 0x0000, 0x0000, 0x0000 },
/*  58f */ { 0x0000, 0x0000, 0x0000 },
/*  590 */ { 0x0000, 0x0000, 0x0000 },
/* 0591 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT ETNAHTA 
/* 0592 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT SEGOL 
/* 0593 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT SHALSHELET 
/* 0594 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT ZAQEF QATAN 
/* 0595 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT ZAQEF GADOL 
/* 0596 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT TIPEHA 
/* 0597 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT REVIA 
/* 0598 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT ZARQA 
/* 0599 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT PASHTA 
/* 059A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT YETIV 
/* 059B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT TEVIR 
/* 059C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT GERESH 
/* 059D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT GERESH MUQDAM 
/* 059E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT GERSHAYIM 
/* 059F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT QARNEY PARA 
/* 05A0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT TELISHA GEDOLA 
/* 05A1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT PAZER 
/* 05A2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT ATNAH HAFUKH 
/* 05A3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT MUNAH 
/* 05A4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT MAHAPAKH 
/* 05A5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT MERKHA 
/* 05A6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT MERKHA KEFULA 
/* 05A7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT DARGA 
/* 05A8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT QADMA 
/* 05A9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT TELISHA QETANA 
/* 05AA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT YERAH BEN YOMO 
/* 05AB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT OLE 
/* 05AC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT ILUY 
/* 05AD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT DEHI 
/* 05AE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW ACCENT ZINOR 
/* 05AF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW MARK MASORA CIRCLE 
/* 05B0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT SHEVA 
/* 05B1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT HATAF SEGOL 
/* 05B2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT HATAF PATAH 
/* 05B3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT HATAF QAMATS 
/* 05B4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT HIRIQ 
/* 05B5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT TSERE 
/* 05B6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT SEGOL 
/* 05B7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT PATAH 
/* 05B8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT QAMATS 
/* 05B9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT HOLAM 
/*  5ba */ { 0x0000, 0x0000, 0x0000 },
/* 05BB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT QUBUTS 
/* 05BC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT DAGESH OR MAPIQ 
/* 05BD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT METEG 
/* 05BE */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW PUNCTUATION MAQAF 
/* 05BF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT RAFE 
/* 05C0 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW PUNCTUATION PASEQ 
/* 05C1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT SHIN DOT 
/* 05C2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT SIN DOT 
/* 05C3 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW PUNCTUATION SOF PASUQ 
/* 05C4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW MARK UPPER DOT 
/* 05C5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW MARK LOWER DOT 
/* 05C6 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW PUNCTUATION NUN HAFUKHA 
/* 05C7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW POINT QAMATS QATAN 
/*  5c8 */ { 0x0000, 0x0000, 0x0000 },
/*  5c9 */ { 0x0000, 0x0000, 0x0000 },
/*  5ca */ { 0x0000, 0x0000, 0x0000 },
/*  5cb */ { 0x0000, 0x0000, 0x0000 },
/*  5cc */ { 0x0000, 0x0000, 0x0000 },
/*  5cd */ { 0x0000, 0x0000, 0x0000 },
/*  5ce */ { 0x0000, 0x0000, 0x0000 },
/*  5cf */ { 0x0000, 0x0000, 0x0000 },
/* 05D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER ALEF 
/* 05D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER BET 
/* 05D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER GIMEL 
/* 05D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER DALET 
/* 05D4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER HE 
/* 05D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER VAV 
/* 05D6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER ZAYIN 
/* 05D7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER HET 
/* 05D8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER TET 
/* 05D9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER YOD 
/* 05DA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER FINAL KAF 
/* 05DB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER KAF 
/* 05DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER LAMED 
/* 05DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER FINAL MEM 
/* 05DE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER MEM 
/* 05DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER FINAL NUN 
/* 05E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER NUN 
/* 05E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER SAMEKH 
/* 05E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER AYIN 
/* 05E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER FINAL PE 
/* 05E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER PE 
/* 05E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER FINAL TSADI 
/* 05E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER TSADI 
/* 05E7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER QOF 
/* 05E8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER RESH 
/* 05E9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER SHIN 
/* 05EA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LETTER TAV 
/*  5eb */ { 0x0000, 0x0000, 0x0000 },
/*  5ec */ { 0x0000, 0x0000, 0x0000 },
/*  5ed */ { 0x0000, 0x0000, 0x0000 },
/*  5ee */ { 0x0000, 0x0000, 0x0000 },
/*  5ef */ { 0x0000, 0x0000, 0x0000 },
/* 05F0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LIGATURE YIDDISH DOUBLE VAV 
/* 05F1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LIGATURE YIDDISH VAV YOD 
/* 05F2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW LIGATURE YIDDISH DOUBLE YOD 
/* 05F3 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW PUNCTUATION GERESH 
/* 05F4 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HEBREW PUNCTUATION GERSHAYIM 
/*  5f5 */ { 0x0000, 0x0000, 0x0000 },
/*  5f6 */ { 0x0000, 0x0000, 0x0000 },
/*  5f7 */ { 0x0000, 0x0000, 0x0000 },
/*  5f8 */ { 0x0000, 0x0000, 0x0000 },
/*  5f9 */ { 0x0000, 0x0000, 0x0000 },
/*  5fa */ { 0x0000, 0x0000, 0x0000 },
/*  5fb */ { 0x0000, 0x0000, 0x0000 },
/*  5fc */ { 0x0000, 0x0000, 0x0000 },
/*  5fd */ { 0x0000, 0x0000, 0x0000 },
/*  5fe */ { 0x0000, 0x0000, 0x0000 },
/*  5ff */ { 0x0000, 0x0000, 0x0000 },
/* 0600 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC NUMBER SIGN 
/* 0601 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN SANAH 
/* 0602 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC FOOTNOTE MARKER 
/* 0603 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN SAFHA 
/*  604 */ { 0x0000, 0x0000, 0x0000 },
/*  605 */ { 0x0000, 0x0000, 0x0000 },
/*  606 */ { 0x0000, 0x0000, 0x0000 },
/*  607 */ { 0x0000, 0x0000, 0x0000 },
/*  608 */ { 0x0000, 0x0000, 0x0000 },
/*  609 */ { 0x0000, 0x0000, 0x0000 },
/*  60a */ { 0x0000, 0x0000, 0x0000 },
/* 060B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // AFGHANI SIGN 
/* 060C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC COMMA 
/* 060D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC DATE SEPARATOR 
/* 060E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC POETIC VERSE SIGN 
/* 060F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN MISRA 
/* 0610 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN SALLALLAHOU ALAYHE WASSALLAM 
/* 0611 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN ALAYHE ASSALLAM 
/* 0612 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN RAHMATULLAH ALAYHE 
/* 0613 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN RADI ALLAHOU ANHU 
/* 0614 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN TAKHALLUS 
/* 0615 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH TAH 
/*  616 */ { 0x0000, 0x0000, 0x0000 },
/*  617 */ { 0x0000, 0x0000, 0x0000 },
/*  618 */ { 0x0000, 0x0000, 0x0000 },
/*  619 */ { 0x0000, 0x0000, 0x0000 },
/*  61a */ { 0x0000, 0x0000, 0x0000 },
/* 061B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SEMICOLON 
/*  61c */ { 0x0000, 0x0000, 0x0000 },
/*  61d */ { 0x0000, 0x0000, 0x0000 },
/* 061E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC TRIPLE DOT PUNCTUATION MARK 
/* 061F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC QUESTION MARK 
/*  620 */ { 0x0000, 0x0000, 0x0000 },
/* 0621 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HAMZA 
/* 0622 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0627,0x0653,0x0000,0x0000 }, // ARABIC LETTER ALEF WITH MADDA ABOVE 
/* 0623 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0627,0x0654,0x0000,0x0000 }, // ARABIC LETTER ALEF WITH HAMZA ABOVE 
/* 0624 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0648,0x0654,0x0000,0x0000 }, // ARABIC LETTER WAW WITH HAMZA ABOVE 
/* 0625 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0627,0x0655,0x0000,0x0000 }, // ARABIC LETTER ALEF WITH HAMZA BELOW 
/* 0626 */ { lem::CP_Char_Flags::Char, 0x0000, 0x064A,0x0654,0x0000,0x0000 }, // ARABIC LETTER YEH WITH HAMZA ABOVE 
/* 0627 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER ALEF 
/* 0628 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEH 
/* 0629 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TEH MARBUTA 
/* 062A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TEH 
/* 062B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER THEH 
/* 062C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER JEEM 
/* 062D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HAH 
/* 062E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KHAH 
/* 062F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL 
/* 0630 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER THAL 
/* 0631 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH 
/* 0632 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER ZAIN 
/* 0633 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SEEN 
/* 0634 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SHEEN 
/* 0635 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SAD 
/* 0636 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAD 
/* 0637 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TAH 
/* 0638 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER ZAH 
/* 0639 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER AIN 
/* 063A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER GHAIN 
/*  63b */ { 0x0000, 0x0000, 0x0000 },
/*  63c */ { 0x0000, 0x0000, 0x0000 },
/*  63d */ { 0x0000, 0x0000, 0x0000 },
/*  63e */ { 0x0000, 0x0000, 0x0000 },
/*  63f */ { 0x0000, 0x0000, 0x0000 },
/* 0640 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC TATWEEL 
/* 0641 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER FEH 
/* 0642 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER QAF 
/* 0643 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KAF 
/* 0644 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER LAM 
/* 0645 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER MEEM 
/* 0646 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NOON 
/* 0647 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HEH 
/* 0648 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER WAW 
/* 0649 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER ALEF MAKSURA 
/* 064A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER YEH 
/* 064B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC FATHATAN 
/* 064C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC DAMMATAN 
/* 064D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC KASRATAN 
/* 064E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC FATHA 
/* 064F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC DAMMA 
/* 0650 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC KASRA 
/* 0651 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SHADDA 
/* 0652 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SUKUN 
/* 0653 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC MADDAH ABOVE 
/* 0654 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC HAMZA ABOVE 
/* 0655 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC HAMZA BELOW 
/* 0656 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SUBSCRIPT ALEF 
/* 0657 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC INVERTED DAMMA 
/* 0658 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC MARK NOON GHUNNA 
/* 0659 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC ZWARAKAY 
/* 065A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC VOWEL SIGN SMALL V ABOVE 
/* 065B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC VOWEL SIGN INVERTED SMALL V ABOVE 
/* 065C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC VOWEL SIGN DOT BELOW 
/* 065D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC REVERSED DAMMA 
/* 065E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC FATHA WITH TWO DOTS 
/*  65f */ { 0x0000, 0x0000, 0x0000 },
/* 0660 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT ZERO 
/* 0661 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT ONE 
/* 0662 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT TWO 
/* 0663 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT THREE 
/* 0664 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT FOUR 
/* 0665 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT FIVE 
/* 0666 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT SIX 
/* 0667 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT SEVEN 
/* 0668 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT EIGHT 
/* 0669 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC-INDIC DIGIT NINE 
/* 066A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC PERCENT SIGN 
/* 066B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC DECIMAL SEPARATOR 
/* 066C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC THOUSANDS SEPARATOR 
/* 066D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC FIVE POINTED STAR 
/* 066E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DOTLESS BEH 
/* 066F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DOTLESS QAF 
/* 0670 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SUPERSCRIPT ALEF 
/* 0671 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER ALEF WASLA 
/* 0672 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER ALEF WITH WAVY HAMZA ABOVE 
/* 0673 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER ALEF WITH WAVY HAMZA BELOW 
/* 0674 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HIGH HAMZA 
/* 0675 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HIGH HAMZA ALEF 
/* 0676 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HIGH HAMZA WAW 
/* 0677 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER U WITH HAMZA ABOVE 
/* 0678 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HIGH HAMZA YEH 
/* 0679 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TTEH 
/* 067A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TTEHEH 
/* 067B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEEH 
/* 067C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TEH WITH RING 
/* 067D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TEH WITH THREE DOTS ABOVE DOWNWARDS 
/* 067E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER PEH 
/* 067F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TEHEH 
/* 0680 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEHEH 
/* 0681 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HAH WITH HAMZA ABOVE 
/* 0682 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HAH WITH TWO DOTS VERTICAL ABOVE 
/* 0683 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NYEH 
/* 0684 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DYEH 
/* 0685 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HAH WITH THREE DOTS ABOVE 
/* 0686 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TCHEH 
/* 0687 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TCHEHEH 
/* 0688 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DDAL 
/* 0689 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL WITH RING 
/* 068A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL WITH DOT BELOW 
/* 068B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL WITH DOT BELOW AND SMALL TAH 
/* 068C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAHAL 
/* 068D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DDAHAL 
/* 068E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DUL 
/* 068F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL WITH THREE DOTS ABOVE DOWNWARDS 
/* 0690 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL WITH FOUR DOTS ABOVE 
/* 0691 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER RREH 
/* 0692 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH SMALL V 
/* 0693 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH RING 
/* 0694 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH DOT BELOW 
/* 0695 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH SMALL V BELOW 
/* 0696 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH DOT BELOW AND DOT ABOVE 
/* 0697 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH TWO DOTS ABOVE 
/* 0698 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER JEH 
/* 0699 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH FOUR DOTS ABOVE 
/* 069A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SEEN WITH DOT BELOW AND DOT ABOVE 
/* 069B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SEEN WITH THREE DOTS BELOW 
/* 069C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SEEN WITH THREE DOTS BELOW AND THREE DOTS ABOVE 
/* 069D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SAD WITH TWO DOTS BELOW 
/* 069E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SAD WITH THREE DOTS ABOVE 
/* 069F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TAH WITH THREE DOTS ABOVE 
/* 06A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER AIN WITH THREE DOTS ABOVE 
/* 06A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DOTLESS FEH 
/* 06A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER FEH WITH DOT MOVED BELOW 
/* 06A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER FEH WITH DOT BELOW 
/* 06A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER VEH 
/* 06A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER FEH WITH THREE DOTS BELOW 
/* 06A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER PEHEH 
/* 06A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER QAF WITH DOT ABOVE 
/* 06A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER QAF WITH THREE DOTS ABOVE 
/* 06A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KEHEH 
/* 06AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SWASH KAF 
/* 06AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KAF WITH RING 
/* 06AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KAF WITH DOT ABOVE 
/* 06AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NG 
/* 06AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KAF WITH THREE DOTS BELOW 
/* 06AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER GAF 
/* 06B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER GAF WITH RING 
/* 06B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NGOEH 
/* 06B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER GAF WITH TWO DOTS BELOW 
/* 06B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER GUEH 
/* 06B4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER GAF WITH THREE DOTS ABOVE 
/* 06B5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER LAM WITH SMALL V 
/* 06B6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER LAM WITH DOT ABOVE 
/* 06B7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER LAM WITH THREE DOTS ABOVE 
/* 06B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER LAM WITH THREE DOTS BELOW 
/* 06B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NOON WITH DOT BELOW 
/* 06BA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NOON GHUNNA 
/* 06BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER RNOON 
/* 06BC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NOON WITH RING 
/* 06BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NOON WITH THREE DOTS ABOVE 
/* 06BE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HEH DOACHASHMEE 
/* 06BF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TCHEH WITH DOT ABOVE 
/* 06C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x06D5,0x0654,0x0000,0x0000 }, // ARABIC LETTER HEH WITH YEH ABOVE 
/* 06C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HEH GOAL 
/* 06C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x06C1,0x0654,0x0000,0x0000 }, // ARABIC LETTER HEH GOAL WITH HAMZA ABOVE 
/* 06C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER TEH MARBUTA GOAL 
/* 06C4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER WAW WITH RING 
/* 06C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KIRGHIZ OE 
/* 06C6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER OE 
/* 06C7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER U 
/* 06C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER YU 
/* 06C9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KIRGHIZ YU 
/* 06CA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER WAW WITH TWO DOTS ABOVE 
/* 06CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER VE 
/* 06CC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER FARSI YEH 
/* 06CD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER YEH WITH TAIL 
/* 06CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER YEH WITH SMALL V 
/* 06CF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER WAW WITH DOT ABOVE 
/* 06D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER E 
/* 06D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER YEH WITH THREE DOTS BELOW 
/* 06D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER YEH BARREE 
/* 06D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x06D2,0x0654,0x0000,0x0000 }, // ARABIC LETTER YEH BARREE WITH HAMZA ABOVE 
/* 06D4 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC FULL STOP 
/* 06D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER AE 
/* 06D6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH LIGATURE SAD WITH LAM WITH ALEF MAKSURA 
/* 06D7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH LIGATURE QAF WITH LAM WITH ALEF MAKSURA 
/* 06D8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH MEEM INITIAL FORM 
/* 06D9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH LAM ALEF 
/* 06DA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH JEEM 
/* 06DB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH THREE DOTS 
/* 06DC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH SEEN 
/* 06DD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC END OF AYAH 
/* 06DE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC START OF RUB EL HIZB 
/* 06DF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH ROUNDED ZERO 
/* 06E0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH UPRIGHT RECTANGULAR ZERO 
/* 06E1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH DOTLESS HEAD OF KHAH 
/* 06E2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH MEEM ISOLATED FORM 
/* 06E3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL LOW SEEN 
/* 06E4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH MADDA 
/* 06E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL WAW 
/* 06E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL YEH 
/* 06E7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH YEH 
/* 06E8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL HIGH NOON 
/* 06E9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC PLACE OF SAJDAH 
/* 06EA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC EMPTY CENTRE LOW STOP 
/* 06EB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC EMPTY CENTRE HIGH STOP 
/* 06EC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC ROUNDED HIGH STOP WITH FILLED CENTRE 
/* 06ED */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SMALL LOW MEEM 
/* 06EE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL WITH INVERTED V 
/* 06EF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH INVERTED V 
/* 06F0 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT ZERO 
/* 06F1 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT ONE 
/* 06F2 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT TWO 
/* 06F3 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT THREE 
/* 06F4 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT FOUR 
/* 06F5 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT FIVE 
/* 06F6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT SIX 
/* 06F7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT SEVEN 
/* 06F8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT EIGHT 
/* 06F9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXTENDED ARABIC-INDIC DIGIT NINE 
/* 06FA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SHEEN WITH DOT BELOW 
/* 06FB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAD WITH DOT BELOW 
/* 06FC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER GHAIN WITH DOT BELOW 
/* 06FD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN SINDHI AMPERSAND 
/* 06FE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC SIGN SINDHI POSTPOSITION MEN 
/* 06FF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HEH WITH INVERTED V 
/* 0700 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC END OF PARAGRAPH 
/* 0701 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC SUPRALINEAR FULL STOP 
/* 0702 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC SUBLINEAR FULL STOP 
/* 0703 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC SUPRALINEAR COLON 
/* 0704 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC SUBLINEAR COLON 
/* 0705 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC HORIZONTAL COLON 
/* 0706 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC COLON SKEWED LEFT 
/* 0707 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC COLON SKEWED RIGHT 
/* 0708 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC SUPRALINEAR COLON SKEWED LEFT 
/* 0709 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC SUBLINEAR COLON SKEWED RIGHT 
/* 070A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC CONTRACTION 
/* 070B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC HARKLEAN OBELUS 
/* 070C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC HARKLEAN METOBELUS 
/* 070D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC HARKLEAN ASTERISCUS 
/*  70e */ { 0x0000, 0x0000, 0x0000 },
/* 070F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC ABBREVIATION MARK 
/* 0710 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER ALAPH 
/* 0711 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER SUPERSCRIPT ALAPH 
/* 0712 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER BETH 
/* 0713 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER GAMAL 
/* 0714 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER GAMAL GARSHUNI 
/* 0715 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER DALATH 
/* 0716 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER DOTLESS DALATH RISH 
/* 0717 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER HE 
/* 0718 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER WAW 
/* 0719 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER ZAIN 
/* 071A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER HETH 
/* 071B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER TETH 
/* 071C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER TETH GARSHUNI 
/* 071D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER YUDH 
/* 071E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER YUDH HE 
/* 071F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER KAPH 
/* 0720 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER LAMADH 
/* 0721 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER MIM 
/* 0722 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER NUN 
/* 0723 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER SEMKATH 
/* 0724 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER FINAL SEMKATH 
/* 0725 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER E 
/* 0726 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER PE 
/* 0727 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER REVERSED PE 
/* 0728 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER SADHE 
/* 0729 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER QAPH 
/* 072A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER RISH 
/* 072B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER SHIN 
/* 072C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER TAW 
/* 072D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER PERSIAN BHETH 
/* 072E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER PERSIAN GHAMAL 
/* 072F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER PERSIAN DHALATH 
/* 0730 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC PTHAHA ABOVE 
/* 0731 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC PTHAHA BELOW 
/* 0732 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC PTHAHA DOTTED 
/* 0733 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC ZQAPHA ABOVE 
/* 0734 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC ZQAPHA BELOW 
/* 0735 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC ZQAPHA DOTTED 
/* 0736 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC RBASA ABOVE 
/* 0737 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC RBASA BELOW 
/* 0738 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC DOTTED ZLAMA HORIZONTAL 
/* 0739 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC DOTTED ZLAMA ANGULAR 
/* 073A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC HBASA ABOVE 
/* 073B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC HBASA BELOW 
/* 073C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC HBASA-ESASA DOTTED 
/* 073D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC ESASA ABOVE 
/* 073E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC ESASA BELOW 
/* 073F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC RWAHA 
/* 0740 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC FEMININE DOT 
/* 0741 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC QUSHSHAYA 
/* 0742 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC RUKKAKHA 
/* 0743 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC TWO VERTICAL DOTS ABOVE 
/* 0744 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC TWO VERTICAL DOTS BELOW 
/* 0745 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC THREE DOTS ABOVE 
/* 0746 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC THREE DOTS BELOW 
/* 0747 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC OBLIQUE LINE ABOVE 
/* 0748 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC OBLIQUE LINE BELOW 
/* 0749 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC MUSIC 
/* 074A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC BARREKH 
/*  74b */ { 0x0000, 0x0000, 0x0000 },
/*  74c */ { 0x0000, 0x0000, 0x0000 },
/* 074D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER SOGDIAN ZHAIN 
/* 074E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER SOGDIAN KHAPH 
/* 074F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SYRIAC LETTER SOGDIAN FE 
/* 0750 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEH WITH THREE DOTS HORIZONTALLY BELOW 
/* 0751 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEH WITH DOT BELOW AND THREE DOTS ABOVE 
/* 0752 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEH WITH THREE DOTS POINTING UPWARDS BELOW 
/* 0753 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEH WITH THREE DOTS POINTING UPWARDS BELOW AND TWO DOTS ABOVE 
/* 0754 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEH WITH TWO DOTS BELOW AND DOT ABOVE 
/* 0755 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEH WITH INVERTED SMALL V BELOW 
/* 0756 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER BEH WITH SMALL V 
/* 0757 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HAH WITH TWO DOTS ABOVE 
/* 0758 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER HAH WITH THREE DOTS POINTING UPWARDS BELOW 
/* 0759 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL WITH TWO DOTS VERTICALLY BELOW AND SMALL TAH 
/* 075A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER DAL WITH INVERTED SMALL V BELOW 
/* 075B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH STROKE 
/* 075C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SEEN WITH FOUR DOTS ABOVE 
/* 075D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER AIN WITH TWO DOTS ABOVE 
/* 075E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER AIN WITH THREE DOTS POINTING DOWNWARDS ABOVE 
/* 075F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER AIN WITH TWO DOTS VERTICALLY ABOVE 
/* 0760 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER FEH WITH TWO DOTS BELOW 
/* 0761 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER FEH WITH THREE DOTS POINTING UPWARDS BELOW 
/* 0762 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KEHEH WITH DOT ABOVE 
/* 0763 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KEHEH WITH THREE DOTS ABOVE 
/* 0764 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER KEHEH WITH THREE DOTS POINTING UPWARDS BELOW 
/* 0765 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER MEEM WITH DOT ABOVE 
/* 0766 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER MEEM WITH DOT BELOW 
/* 0767 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NOON WITH TWO DOTS BELOW 
/* 0768 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NOON WITH SMALL TAH 
/* 0769 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER NOON WITH SMALL V 
/* 076A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER LAM WITH BAR 
/* 076B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH TWO DOTS VERTICALLY ABOVE 
/* 076C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER REH WITH HAMZA ABOVE 
/* 076D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ARABIC LETTER SEEN WITH TWO DOTS VERTICALLY ABOVE 
/*  76e */ { 0x0000, 0x0000, 0x0000 },
/*  76f */ { 0x0000, 0x0000, 0x0000 },
/*  770 */ { 0x0000, 0x0000, 0x0000 },
/*  771 */ { 0x0000, 0x0000, 0x0000 },
/*  772 */ { 0x0000, 0x0000, 0x0000 },
/*  773 */ { 0x0000, 0x0000, 0x0000 },
/*  774 */ { 0x0000, 0x0000, 0x0000 },
/*  775 */ { 0x0000, 0x0000, 0x0000 },
/*  776 */ { 0x0000, 0x0000, 0x0000 },
/*  777 */ { 0x0000, 0x0000, 0x0000 },
/*  778 */ { 0x0000, 0x0000, 0x0000 },
/*  779 */ { 0x0000, 0x0000, 0x0000 },
/*  77a */ { 0x0000, 0x0000, 0x0000 },
/*  77b */ { 0x0000, 0x0000, 0x0000 },
/*  77c */ { 0x0000, 0x0000, 0x0000 },
/*  77d */ { 0x0000, 0x0000, 0x0000 },
/*  77e */ { 0x0000, 0x0000, 0x0000 },
/*  77f */ { 0x0000, 0x0000, 0x0000 },
/* 0780 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER HAA 
/* 0781 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER SHAVIYANI 
/* 0782 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER NOONU 
/* 0783 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER RAA 
/* 0784 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER BAA 
/* 0785 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER LHAVIYANI 
/* 0786 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER KAAFU 
/* 0787 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER ALIFU 
/* 0788 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER VAAVU 
/* 0789 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER MEEMU 
/* 078A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER FAAFU 
/* 078B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER DHAALU 
/* 078C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER THAA 
/* 078D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER LAAMU 
/* 078E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER GAAFU 
/* 078F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER GNAVIYANI 
/* 0790 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER SEENU 
/* 0791 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER DAVIYANI 
/* 0792 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER ZAVIYANI 
/* 0793 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER TAVIYANI 
/* 0794 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER YAA 
/* 0795 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER PAVIYANI 
/* 0796 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER JAVIYANI 
/* 0797 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER CHAVIYANI 
/* 0798 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER TTAA 
/* 0799 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER HHAA 
/* 079A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER KHAA 
/* 079B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER THAALU 
/* 079C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER ZAA 
/* 079D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER SHEENU 
/* 079E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER SAADHU 
/* 079F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER DAADHU 
/* 07A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER TO 
/* 07A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER ZO 
/* 07A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER AINU 
/* 07A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER GHAINU 
/* 07A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER QAAFU 
/* 07A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER WAAVU 
/* 07A6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA ABAFILI 
/* 07A7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA AABAAFILI 
/* 07A8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA IBIFILI 
/* 07A9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA EEBEEFILI 
/* 07AA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA UBUFILI 
/* 07AB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA OOBOOFILI 
/* 07AC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA EBEFILI 
/* 07AD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA EYBEYFILI 
/* 07AE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA OBOFILI 
/* 07AF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA OABOAFILI 
/* 07B0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA SUKUN 
/* 07B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAANA LETTER NAA 
/*  7b2 */ { 0x0000, 0x0000, 0x0000 },
/*  7b3 */ { 0x0000, 0x0000, 0x0000 },
/*  7b4 */ { 0x0000, 0x0000, 0x0000 },
/*  7b5 */ { 0x0000, 0x0000, 0x0000 },
/*  7b6 */ { 0x0000, 0x0000, 0x0000 },
/*  7b7 */ { 0x0000, 0x0000, 0x0000 },
/*  7b8 */ { 0x0000, 0x0000, 0x0000 },
/*  7b9 */ { 0x0000, 0x0000, 0x0000 },
/*  7ba */ { 0x0000, 0x0000, 0x0000 },
/*  7bb */ { 0x0000, 0x0000, 0x0000 },
/*  7bc */ { 0x0000, 0x0000, 0x0000 },
/*  7bd */ { 0x0000, 0x0000, 0x0000 },
/*  7be */ { 0x0000, 0x0000, 0x0000 },
/*  7bf */ { 0x0000, 0x0000, 0x0000 },
/*  7c0 */ { 0x0000, 0x0000, 0x0000 },
/*  7c1 */ { 0x0000, 0x0000, 0x0000 },
/*  7c2 */ { 0x0000, 0x0000, 0x0000 },
/*  7c3 */ { 0x0000, 0x0000, 0x0000 },
/*  7c4 */ { 0x0000, 0x0000, 0x0000 },
/*  7c5 */ { 0x0000, 0x0000, 0x0000 },
/*  7c6 */ { 0x0000, 0x0000, 0x0000 },
/*  7c7 */ { 0x0000, 0x0000, 0x0000 },
/*  7c8 */ { 0x0000, 0x0000, 0x0000 },
/*  7c9 */ { 0x0000, 0x0000, 0x0000 },
/*  7ca */ { 0x0000, 0x0000, 0x0000 },
/*  7cb */ { 0x0000, 0x0000, 0x0000 },
/*  7cc */ { 0x0000, 0x0000, 0x0000 },
/*  7cd */ { 0x0000, 0x0000, 0x0000 },
/*  7ce */ { 0x0000, 0x0000, 0x0000 },
/*  7cf */ { 0x0000, 0x0000, 0x0000 },
/*  7d0 */ { 0x0000, 0x0000, 0x0000 },
/*  7d1 */ { 0x0000, 0x0000, 0x0000 },
/*  7d2 */ { 0x0000, 0x0000, 0x0000 },
/*  7d3 */ { 0x0000, 0x0000, 0x0000 },
/*  7d4 */ { 0x0000, 0x0000, 0x0000 },
/*  7d5 */ { 0x0000, 0x0000, 0x0000 },
/*  7d6 */ { 0x0000, 0x0000, 0x0000 },
/*  7d7 */ { 0x0000, 0x0000, 0x0000 },
/*  7d8 */ { 0x0000, 0x0000, 0x0000 },
/*  7d9 */ { 0x0000, 0x0000, 0x0000 },
/*  7da */ { 0x0000, 0x0000, 0x0000 },
/*  7db */ { 0x0000, 0x0000, 0x0000 },
/*  7dc */ { 0x0000, 0x0000, 0x0000 },
/*  7dd */ { 0x0000, 0x0000, 0x0000 },
/*  7de */ { 0x0000, 0x0000, 0x0000 },
/*  7df */ { 0x0000, 0x0000, 0x0000 },
/*  7e0 */ { 0x0000, 0x0000, 0x0000 },
/*  7e1 */ { 0x0000, 0x0000, 0x0000 },
/*  7e2 */ { 0x0000, 0x0000, 0x0000 },
/*  7e3 */ { 0x0000, 0x0000, 0x0000 },
/*  7e4 */ { 0x0000, 0x0000, 0x0000 },
/*  7e5 */ { 0x0000, 0x0000, 0x0000 },
/*  7e6 */ { 0x0000, 0x0000, 0x0000 },
/*  7e7 */ { 0x0000, 0x0000, 0x0000 },
/*  7e8 */ { 0x0000, 0x0000, 0x0000 },
/*  7e9 */ { 0x0000, 0x0000, 0x0000 },
/*  7ea */ { 0x0000, 0x0000, 0x0000 },
/*  7eb */ { 0x0000, 0x0000, 0x0000 },
/*  7ec */ { 0x0000, 0x0000, 0x0000 },
/*  7ed */ { 0x0000, 0x0000, 0x0000 },
/*  7ee */ { 0x0000, 0x0000, 0x0000 },
/*  7ef */ { 0x0000, 0x0000, 0x0000 },
/*  7f0 */ { 0x0000, 0x0000, 0x0000 },
/*  7f1 */ { 0x0000, 0x0000, 0x0000 },
/*  7f2 */ { 0x0000, 0x0000, 0x0000 },
/*  7f3 */ { 0x0000, 0x0000, 0x0000 },
/*  7f4 */ { 0x0000, 0x0000, 0x0000 },
/*  7f5 */ { 0x0000, 0x0000, 0x0000 },
/*  7f6 */ { 0x0000, 0x0000, 0x0000 },
/*  7f7 */ { 0x0000, 0x0000, 0x0000 },
/*  7f8 */ { 0x0000, 0x0000, 0x0000 },
/*  7f9 */ { 0x0000, 0x0000, 0x0000 },
/*  7fa */ { 0x0000, 0x0000, 0x0000 },
/*  7fb */ { 0x0000, 0x0000, 0x0000 },
/*  7fc */ { 0x0000, 0x0000, 0x0000 },
/*  7fd */ { 0x0000, 0x0000, 0x0000 },
/*  7fe */ { 0x0000, 0x0000, 0x0000 },
/*  7ff */ { 0x0000, 0x0000, 0x0000 },
/*  800 */ { 0x0000, 0x0000, 0x0000 },
/*  801 */ { 0x0000, 0x0000, 0x0000 },
/*  802 */ { 0x0000, 0x0000, 0x0000 },
/*  803 */ { 0x0000, 0x0000, 0x0000 },
/*  804 */ { 0x0000, 0x0000, 0x0000 },
/*  805 */ { 0x0000, 0x0000, 0x0000 },
/*  806 */ { 0x0000, 0x0000, 0x0000 },
/*  807 */ { 0x0000, 0x0000, 0x0000 },
/*  808 */ { 0x0000, 0x0000, 0x0000 },
/*  809 */ { 0x0000, 0x0000, 0x0000 },
/*  80a */ { 0x0000, 0x0000, 0x0000 },
/*  80b */ { 0x0000, 0x0000, 0x0000 },
/*  80c */ { 0x0000, 0x0000, 0x0000 },
/*  80d */ { 0x0000, 0x0000, 0x0000 },
/*  80e */ { 0x0000, 0x0000, 0x0000 },
/*  80f */ { 0x0000, 0x0000, 0x0000 },
/*  810 */ { 0x0000, 0x0000, 0x0000 },
/*  811 */ { 0x0000, 0x0000, 0x0000 },
/*  812 */ { 0x0000, 0x0000, 0x0000 },
/*  813 */ { 0x0000, 0x0000, 0x0000 },
/*  814 */ { 0x0000, 0x0000, 0x0000 },
/*  815 */ { 0x0000, 0x0000, 0x0000 },
/*  816 */ { 0x0000, 0x0000, 0x0000 },
/*  817 */ { 0x0000, 0x0000, 0x0000 },
/*  818 */ { 0x0000, 0x0000, 0x0000 },
/*  819 */ { 0x0000, 0x0000, 0x0000 },
/*  81a */ { 0x0000, 0x0000, 0x0000 },
/*  81b */ { 0x0000, 0x0000, 0x0000 },
/*  81c */ { 0x0000, 0x0000, 0x0000 },
/*  81d */ { 0x0000, 0x0000, 0x0000 },
/*  81e */ { 0x0000, 0x0000, 0x0000 },
/*  81f */ { 0x0000, 0x0000, 0x0000 },
/*  820 */ { 0x0000, 0x0000, 0x0000 },
/*  821 */ { 0x0000, 0x0000, 0x0000 },
/*  822 */ { 0x0000, 0x0000, 0x0000 },
/*  823 */ { 0x0000, 0x0000, 0x0000 },
/*  824 */ { 0x0000, 0x0000, 0x0000 },
/*  825 */ { 0x0000, 0x0000, 0x0000 },
/*  826 */ { 0x0000, 0x0000, 0x0000 },
/*  827 */ { 0x0000, 0x0000, 0x0000 },
/*  828 */ { 0x0000, 0x0000, 0x0000 },
/*  829 */ { 0x0000, 0x0000, 0x0000 },
/*  82a */ { 0x0000, 0x0000, 0x0000 },
/*  82b */ { 0x0000, 0x0000, 0x0000 },
/*  82c */ { 0x0000, 0x0000, 0x0000 },
/*  82d */ { 0x0000, 0x0000, 0x0000 },
/*  82e */ { 0x0000, 0x0000, 0x0000 },
/*  82f */ { 0x0000, 0x0000, 0x0000 },
/*  830 */ { 0x0000, 0x0000, 0x0000 },
/*  831 */ { 0x0000, 0x0000, 0x0000 },
/*  832 */ { 0x0000, 0x0000, 0x0000 },
/*  833 */ { 0x0000, 0x0000, 0x0000 },
/*  834 */ { 0x0000, 0x0000, 0x0000 },
/*  835 */ { 0x0000, 0x0000, 0x0000 },
/*  836 */ { 0x0000, 0x0000, 0x0000 },
/*  837 */ { 0x0000, 0x0000, 0x0000 },
/*  838 */ { 0x0000, 0x0000, 0x0000 },
/*  839 */ { 0x0000, 0x0000, 0x0000 },
/*  83a */ { 0x0000, 0x0000, 0x0000 },
/*  83b */ { 0x0000, 0x0000, 0x0000 },
/*  83c */ { 0x0000, 0x0000, 0x0000 },
/*  83d */ { 0x0000, 0x0000, 0x0000 },
/*  83e */ { 0x0000, 0x0000, 0x0000 },
/*  83f */ { 0x0000, 0x0000, 0x0000 },
/*  840 */ { 0x0000, 0x0000, 0x0000 },
/*  841 */ { 0x0000, 0x0000, 0x0000 },
/*  842 */ { 0x0000, 0x0000, 0x0000 },
/*  843 */ { 0x0000, 0x0000, 0x0000 },
/*  844 */ { 0x0000, 0x0000, 0x0000 },
/*  845 */ { 0x0000, 0x0000, 0x0000 },
/*  846 */ { 0x0000, 0x0000, 0x0000 },
/*  847 */ { 0x0000, 0x0000, 0x0000 },
/*  848 */ { 0x0000, 0x0000, 0x0000 },
/*  849 */ { 0x0000, 0x0000, 0x0000 },
/*  84a */ { 0x0000, 0x0000, 0x0000 },
/*  84b */ { 0x0000, 0x0000, 0x0000 },
/*  84c */ { 0x0000, 0x0000, 0x0000 },
/*  84d */ { 0x0000, 0x0000, 0x0000 },
/*  84e */ { 0x0000, 0x0000, 0x0000 },
/*  84f */ { 0x0000, 0x0000, 0x0000 },
/*  850 */ { 0x0000, 0x0000, 0x0000 },
/*  851 */ { 0x0000, 0x0000, 0x0000 },
/*  852 */ { 0x0000, 0x0000, 0x0000 },
/*  853 */ { 0x0000, 0x0000, 0x0000 },
/*  854 */ { 0x0000, 0x0000, 0x0000 },
/*  855 */ { 0x0000, 0x0000, 0x0000 },
/*  856 */ { 0x0000, 0x0000, 0x0000 },
/*  857 */ { 0x0000, 0x0000, 0x0000 },
/*  858 */ { 0x0000, 0x0000, 0x0000 },
/*  859 */ { 0x0000, 0x0000, 0x0000 },
/*  85a */ { 0x0000, 0x0000, 0x0000 },
/*  85b */ { 0x0000, 0x0000, 0x0000 },
/*  85c */ { 0x0000, 0x0000, 0x0000 },
/*  85d */ { 0x0000, 0x0000, 0x0000 },
/*  85e */ { 0x0000, 0x0000, 0x0000 },
/*  85f */ { 0x0000, 0x0000, 0x0000 },
/*  860 */ { 0x0000, 0x0000, 0x0000 },
/*  861 */ { 0x0000, 0x0000, 0x0000 },
/*  862 */ { 0x0000, 0x0000, 0x0000 },
/*  863 */ { 0x0000, 0x0000, 0x0000 },
/*  864 */ { 0x0000, 0x0000, 0x0000 },
/*  865 */ { 0x0000, 0x0000, 0x0000 },
/*  866 */ { 0x0000, 0x0000, 0x0000 },
/*  867 */ { 0x0000, 0x0000, 0x0000 },
/*  868 */ { 0x0000, 0x0000, 0x0000 },
/*  869 */ { 0x0000, 0x0000, 0x0000 },
/*  86a */ { 0x0000, 0x0000, 0x0000 },
/*  86b */ { 0x0000, 0x0000, 0x0000 },
/*  86c */ { 0x0000, 0x0000, 0x0000 },
/*  86d */ { 0x0000, 0x0000, 0x0000 },
/*  86e */ { 0x0000, 0x0000, 0x0000 },
/*  86f */ { 0x0000, 0x0000, 0x0000 },
/*  870 */ { 0x0000, 0x0000, 0x0000 },
/*  871 */ { 0x0000, 0x0000, 0x0000 },
/*  872 */ { 0x0000, 0x0000, 0x0000 },
/*  873 */ { 0x0000, 0x0000, 0x0000 },
/*  874 */ { 0x0000, 0x0000, 0x0000 },
/*  875 */ { 0x0000, 0x0000, 0x0000 },
/*  876 */ { 0x0000, 0x0000, 0x0000 },
/*  877 */ { 0x0000, 0x0000, 0x0000 },
/*  878 */ { 0x0000, 0x0000, 0x0000 },
/*  879 */ { 0x0000, 0x0000, 0x0000 },
/*  87a */ { 0x0000, 0x0000, 0x0000 },
/*  87b */ { 0x0000, 0x0000, 0x0000 },
/*  87c */ { 0x0000, 0x0000, 0x0000 },
/*  87d */ { 0x0000, 0x0000, 0x0000 },
/*  87e */ { 0x0000, 0x0000, 0x0000 },
/*  87f */ { 0x0000, 0x0000, 0x0000 },
/*  880 */ { 0x0000, 0x0000, 0x0000 },
/*  881 */ { 0x0000, 0x0000, 0x0000 },
/*  882 */ { 0x0000, 0x0000, 0x0000 },
/*  883 */ { 0x0000, 0x0000, 0x0000 },
/*  884 */ { 0x0000, 0x0000, 0x0000 },
/*  885 */ { 0x0000, 0x0000, 0x0000 },
/*  886 */ { 0x0000, 0x0000, 0x0000 },
/*  887 */ { 0x0000, 0x0000, 0x0000 },
/*  888 */ { 0x0000, 0x0000, 0x0000 },
/*  889 */ { 0x0000, 0x0000, 0x0000 },
/*  88a */ { 0x0000, 0x0000, 0x0000 },
/*  88b */ { 0x0000, 0x0000, 0x0000 },
/*  88c */ { 0x0000, 0x0000, 0x0000 },
/*  88d */ { 0x0000, 0x0000, 0x0000 },
/*  88e */ { 0x0000, 0x0000, 0x0000 },
/*  88f */ { 0x0000, 0x0000, 0x0000 },
/*  890 */ { 0x0000, 0x0000, 0x0000 },
/*  891 */ { 0x0000, 0x0000, 0x0000 },
/*  892 */ { 0x0000, 0x0000, 0x0000 },
/*  893 */ { 0x0000, 0x0000, 0x0000 },
/*  894 */ { 0x0000, 0x0000, 0x0000 },
/*  895 */ { 0x0000, 0x0000, 0x0000 },
/*  896 */ { 0x0000, 0x0000, 0x0000 },
/*  897 */ { 0x0000, 0x0000, 0x0000 },
/*  898 */ { 0x0000, 0x0000, 0x0000 },
/*  899 */ { 0x0000, 0x0000, 0x0000 },
/*  89a */ { 0x0000, 0x0000, 0x0000 },
/*  89b */ { 0x0000, 0x0000, 0x0000 },
/*  89c */ { 0x0000, 0x0000, 0x0000 },
/*  89d */ { 0x0000, 0x0000, 0x0000 },
/*  89e */ { 0x0000, 0x0000, 0x0000 },
/*  89f */ { 0x0000, 0x0000, 0x0000 },
/*  8a0 */ { 0x0000, 0x0000, 0x0000 },
/*  8a1 */ { 0x0000, 0x0000, 0x0000 },
/*  8a2 */ { 0x0000, 0x0000, 0x0000 },
/*  8a3 */ { 0x0000, 0x0000, 0x0000 },
/*  8a4 */ { 0x0000, 0x0000, 0x0000 },
/*  8a5 */ { 0x0000, 0x0000, 0x0000 },
/*  8a6 */ { 0x0000, 0x0000, 0x0000 },
/*  8a7 */ { 0x0000, 0x0000, 0x0000 },
/*  8a8 */ { 0x0000, 0x0000, 0x0000 },
/*  8a9 */ { 0x0000, 0x0000, 0x0000 },
/*  8aa */ { 0x0000, 0x0000, 0x0000 },
/*  8ab */ { 0x0000, 0x0000, 0x0000 },
/*  8ac */ { 0x0000, 0x0000, 0x0000 },
/*  8ad */ { 0x0000, 0x0000, 0x0000 },
/*  8ae */ { 0x0000, 0x0000, 0x0000 },
/*  8af */ { 0x0000, 0x0000, 0x0000 },
/*  8b0 */ { 0x0000, 0x0000, 0x0000 },
/*  8b1 */ { 0x0000, 0x0000, 0x0000 },
/*  8b2 */ { 0x0000, 0x0000, 0x0000 },
/*  8b3 */ { 0x0000, 0x0000, 0x0000 },
/*  8b4 */ { 0x0000, 0x0000, 0x0000 },
/*  8b5 */ { 0x0000, 0x0000, 0x0000 },
/*  8b6 */ { 0x0000, 0x0000, 0x0000 },
/*  8b7 */ { 0x0000, 0x0000, 0x0000 },
/*  8b8 */ { 0x0000, 0x0000, 0x0000 },
/*  8b9 */ { 0x0000, 0x0000, 0x0000 },
/*  8ba */ { 0x0000, 0x0000, 0x0000 },
/*  8bb */ { 0x0000, 0x0000, 0x0000 },
/*  8bc */ { 0x0000, 0x0000, 0x0000 },
/*  8bd */ { 0x0000, 0x0000, 0x0000 },
/*  8be */ { 0x0000, 0x0000, 0x0000 },
/*  8bf */ { 0x0000, 0x0000, 0x0000 },
/*  8c0 */ { 0x0000, 0x0000, 0x0000 },
/*  8c1 */ { 0x0000, 0x0000, 0x0000 },
/*  8c2 */ { 0x0000, 0x0000, 0x0000 },
/*  8c3 */ { 0x0000, 0x0000, 0x0000 },
/*  8c4 */ { 0x0000, 0x0000, 0x0000 },
/*  8c5 */ { 0x0000, 0x0000, 0x0000 },
/*  8c6 */ { 0x0000, 0x0000, 0x0000 },
/*  8c7 */ { 0x0000, 0x0000, 0x0000 },
/*  8c8 */ { 0x0000, 0x0000, 0x0000 },
/*  8c9 */ { 0x0000, 0x0000, 0x0000 },
/*  8ca */ { 0x0000, 0x0000, 0x0000 },
/*  8cb */ { 0x0000, 0x0000, 0x0000 },
/*  8cc */ { 0x0000, 0x0000, 0x0000 },
/*  8cd */ { 0x0000, 0x0000, 0x0000 },
/*  8ce */ { 0x0000, 0x0000, 0x0000 },
/*  8cf */ { 0x0000, 0x0000, 0x0000 },
/*  8d0 */ { 0x0000, 0x0000, 0x0000 },
/*  8d1 */ { 0x0000, 0x0000, 0x0000 },
/*  8d2 */ { 0x0000, 0x0000, 0x0000 },
/*  8d3 */ { 0x0000, 0x0000, 0x0000 },
/*  8d4 */ { 0x0000, 0x0000, 0x0000 },
/*  8d5 */ { 0x0000, 0x0000, 0x0000 },
/*  8d6 */ { 0x0000, 0x0000, 0x0000 },
/*  8d7 */ { 0x0000, 0x0000, 0x0000 },
/*  8d8 */ { 0x0000, 0x0000, 0x0000 },
/*  8d9 */ { 0x0000, 0x0000, 0x0000 },
/*  8da */ { 0x0000, 0x0000, 0x0000 },
/*  8db */ { 0x0000, 0x0000, 0x0000 },
/*  8dc */ { 0x0000, 0x0000, 0x0000 },
/*  8dd */ { 0x0000, 0x0000, 0x0000 },
/*  8de */ { 0x0000, 0x0000, 0x0000 },
/*  8df */ { 0x0000, 0x0000, 0x0000 },
/*  8e0 */ { 0x0000, 0x0000, 0x0000 },
/*  8e1 */ { 0x0000, 0x0000, 0x0000 },
/*  8e2 */ { 0x0000, 0x0000, 0x0000 },
/*  8e3 */ { 0x0000, 0x0000, 0x0000 },
/*  8e4 */ { 0x0000, 0x0000, 0x0000 },
/*  8e5 */ { 0x0000, 0x0000, 0x0000 },
/*  8e6 */ { 0x0000, 0x0000, 0x0000 },
/*  8e7 */ { 0x0000, 0x0000, 0x0000 },
/*  8e8 */ { 0x0000, 0x0000, 0x0000 },
/*  8e9 */ { 0x0000, 0x0000, 0x0000 },
/*  8ea */ { 0x0000, 0x0000, 0x0000 },
/*  8eb */ { 0x0000, 0x0000, 0x0000 },
/*  8ec */ { 0x0000, 0x0000, 0x0000 },
/*  8ed */ { 0x0000, 0x0000, 0x0000 },
/*  8ee */ { 0x0000, 0x0000, 0x0000 },
/*  8ef */ { 0x0000, 0x0000, 0x0000 },
/*  8f0 */ { 0x0000, 0x0000, 0x0000 },
/*  8f1 */ { 0x0000, 0x0000, 0x0000 },
/*  8f2 */ { 0x0000, 0x0000, 0x0000 },
/*  8f3 */ { 0x0000, 0x0000, 0x0000 },
/*  8f4 */ { 0x0000, 0x0000, 0x0000 },
/*  8f5 */ { 0x0000, 0x0000, 0x0000 },
/*  8f6 */ { 0x0000, 0x0000, 0x0000 },
/*  8f7 */ { 0x0000, 0x0000, 0x0000 },
/*  8f8 */ { 0x0000, 0x0000, 0x0000 },
/*  8f9 */ { 0x0000, 0x0000, 0x0000 },
/*  8fa */ { 0x0000, 0x0000, 0x0000 },
/*  8fb */ { 0x0000, 0x0000, 0x0000 },
/*  8fc */ { 0x0000, 0x0000, 0x0000 },
/*  8fd */ { 0x0000, 0x0000, 0x0000 },
/*  8fe */ { 0x0000, 0x0000, 0x0000 },
/*  8ff */ { 0x0000, 0x0000, 0x0000 },
/*  900 */ { 0x0000, 0x0000, 0x0000 },
/* 0901 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI SIGN CANDRABINDU 
/* 0902 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI SIGN ANUSVARA 
/* 0903 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI SIGN VISARGA 
/* 0904 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER SHORT A 
/* 0905 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER A 
/* 0906 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER AA 
/* 0907 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER I 
/* 0908 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER II 
/* 0909 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER U 
/* 090A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER UU 
/* 090B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER VOCALIC R 
/* 090C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER VOCALIC L 
/* 090D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER CANDRA E 
/* 090E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER SHORT E 
/* 090F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER E 
/* 0910 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER AI 
/* 0911 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER CANDRA O 
/* 0912 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER SHORT O 
/* 0913 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER O 
/* 0914 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER AU 
/* 0915 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER KA 
/* 0916 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER KHA 
/* 0917 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER GA 
/* 0918 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER GHA 
/* 0919 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER NGA 
/* 091A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER CA 
/* 091B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER CHA 
/* 091C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER JA 
/* 091D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER JHA 
/* 091E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER NYA 
/* 091F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER TTA 
/* 0920 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER TTHA 
/* 0921 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER DDA 
/* 0922 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER DDHA 
/* 0923 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER NNA 
/* 0924 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER TA 
/* 0925 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER THA 
/* 0926 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER DA 
/* 0927 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER DHA 
/* 0928 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER NA 
/* 0929 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0928,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER NNNA 
/* 092A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER PA 
/* 092B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER PHA 
/* 092C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER BA 
/* 092D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER BHA 
/* 092E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER MA 
/* 092F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER YA 
/* 0930 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER RA 
/* 0931 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0930,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER RRA 
/* 0932 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER LA 
/* 0933 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER LLA 
/* 0934 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0933,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER LLLA 
/* 0935 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER VA 
/* 0936 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER SHA 
/* 0937 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER SSA 
/* 0938 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER SA 
/* 0939 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER HA 
/*  93a */ { 0x0000, 0x0000, 0x0000 },
/*  93b */ { 0x0000, 0x0000, 0x0000 },
/* 093C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI SIGN NUKTA 
/* 093D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI SIGN AVAGRAHA 
/* 093E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN AA 
/* 093F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN I 
/* 0940 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN II 
/* 0941 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN U 
/* 0942 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN UU 
/* 0943 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN VOCALIC R 
/* 0944 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN VOCALIC RR 
/* 0945 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN CANDRA E 
/* 0946 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN SHORT E 
/* 0947 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN E 
/* 0948 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN AI 
/* 0949 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN CANDRA O 
/* 094A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN SHORT O 
/* 094B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN O 
/* 094C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN AU 
/* 094D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI SIGN VIRAMA 
/*  94e */ { 0x0000, 0x0000, 0x0000 },
/*  94f */ { 0x0000, 0x0000, 0x0000 },
/* 0950 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI OM 
/* 0951 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI STRESS SIGN UDATTA 
/* 0952 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI STRESS SIGN ANUDATTA 
/* 0953 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI GRAVE ACCENT 
/* 0954 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI ACUTE ACCENT 
/*  955 */ { 0x0000, 0x0000, 0x0000 },
/*  956 */ { 0x0000, 0x0000, 0x0000 },
/*  957 */ { 0x0000, 0x0000, 0x0000 },
/* 0958 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0915,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER QA 
/* 0959 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0916,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER KHHA 
/* 095A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0917,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER GHHA 
/* 095B */ { lem::CP_Char_Flags::Char, 0x0000, 0x091C,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER ZA 
/* 095C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0921,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER DDDHA 
/* 095D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0922,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER RHA 
/* 095E */ { lem::CP_Char_Flags::Char, 0x0000, 0x092B,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER FA 
/* 095F */ { lem::CP_Char_Flags::Char, 0x0000, 0x092F,0x093C,0x0000,0x0000 }, // DEVANAGARI LETTER YYA 
/* 0960 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER VOCALIC RR 
/* 0961 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER VOCALIC LL 
/* 0962 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN VOCALIC L 
/* 0963 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI VOWEL SIGN VOCALIC LL 
/* 0964 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DANDA 
/* 0965 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DOUBLE DANDA 
/* 0966 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT ZERO 
/* 0967 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT ONE 
/* 0968 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT TWO 
/* 0969 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT THREE 
/* 096A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT FOUR 
/* 096B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT FIVE 
/* 096C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT SIX 
/* 096D */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT SEVEN 
/* 096E */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT EIGHT 
/* 096F */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI DIGIT NINE 
/* 0970 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI ABBREVIATION SIGN 
/*  971 */ { 0x0000, 0x0000, 0x0000 },
/*  972 */ { 0x0000, 0x0000, 0x0000 },
/*  973 */ { 0x0000, 0x0000, 0x0000 },
/*  974 */ { 0x0000, 0x0000, 0x0000 },
/*  975 */ { 0x0000, 0x0000, 0x0000 },
/*  976 */ { 0x0000, 0x0000, 0x0000 },
/*  977 */ { 0x0000, 0x0000, 0x0000 },
/*  978 */ { 0x0000, 0x0000, 0x0000 },
/*  979 */ { 0x0000, 0x0000, 0x0000 },
/*  97a */ { 0x0000, 0x0000, 0x0000 },
/*  97b */ { 0x0000, 0x0000, 0x0000 },
/*  97c */ { 0x0000, 0x0000, 0x0000 },
/* 097D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DEVANAGARI LETTER GLOTTAL STOP 
/*  97e */ { 0x0000, 0x0000, 0x0000 },
/*  97f */ { 0x0000, 0x0000, 0x0000 },
/*  980 */ { 0x0000, 0x0000, 0x0000 },
/* 0981 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI SIGN CANDRABINDU 
/* 0982 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI SIGN ANUSVARA 
/* 0983 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI SIGN VISARGA 
/*  984 */ { 0x0000, 0x0000, 0x0000 },
/* 0985 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER A 
/* 0986 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER AA 
/* 0987 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER I 
/* 0988 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER II 
/* 0989 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER U 
/* 098A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER UU 
/* 098B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER VOCALIC R 
/* 098C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER VOCALIC L 
/*  98d */ { 0x0000, 0x0000, 0x0000 },
/*  98e */ { 0x0000, 0x0000, 0x0000 },
/* 098F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER E 
/* 0990 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER AI 
/*  991 */ { 0x0000, 0x0000, 0x0000 },
/*  992 */ { 0x0000, 0x0000, 0x0000 },
/* 0993 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER O 
/* 0994 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER AU 
/* 0995 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER KA 
/* 0996 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER KHA 
/* 0997 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER GA 
/* 0998 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER GHA 
/* 0999 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER NGA 
/* 099A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER CA 
/* 099B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER CHA 
/* 099C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER JA 
/* 099D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER JHA 
/* 099E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER NYA 
/* 099F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER TTA 
/* 09A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER TTHA 
/* 09A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER DDA 
/* 09A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER DDHA 
/* 09A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER NNA 
/* 09A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER TA 
/* 09A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER THA 
/* 09A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER DA 
/* 09A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER DHA 
/* 09A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER NA 
/*  9a9 */ { 0x0000, 0x0000, 0x0000 },
/* 09AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER PA 
/* 09AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER PHA 
/* 09AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER BA 
/* 09AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER BHA 
/* 09AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER MA 
/* 09AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER YA 
/* 09B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER RA 
/*  9b1 */ { 0x0000, 0x0000, 0x0000 },
/* 09B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER LA 
/*  9b3 */ { 0x0000, 0x0000, 0x0000 },
/*  9b4 */ { 0x0000, 0x0000, 0x0000 },
/*  9b5 */ { 0x0000, 0x0000, 0x0000 },
/* 09B6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER SHA 
/* 09B7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER SSA 
/* 09B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER SA 
/* 09B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER HA 
/*  9ba */ { 0x0000, 0x0000, 0x0000 },
/*  9bb */ { 0x0000, 0x0000, 0x0000 },
/* 09BC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI SIGN NUKTA 
/* 09BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI SIGN AVAGRAHA 
/* 09BE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN AA 
/* 09BF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN I 
/* 09C0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN II 
/* 09C1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN U 
/* 09C2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN UU 
/* 09C3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN VOCALIC R 
/* 09C4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN VOCALIC RR 
/*  9c5 */ { 0x0000, 0x0000, 0x0000 },
/*  9c6 */ { 0x0000, 0x0000, 0x0000 },
/* 09C7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN E 
/* 09C8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN AI 
/*  9c9 */ { 0x0000, 0x0000, 0x0000 },
/*  9ca */ { 0x0000, 0x0000, 0x0000 },
/* 09CB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x09C7,0x09BE,0x0000,0x0000 }, // BENGALI VOWEL SIGN O 
/* 09CC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x09C7,0x09D7,0x0000,0x0000 }, // BENGALI VOWEL SIGN AU 
/* 09CD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI SIGN VIRAMA 
/* 09CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER KHANDA TA 
/*  9cf */ { 0x0000, 0x0000, 0x0000 },
/*  9d0 */ { 0x0000, 0x0000, 0x0000 },
/*  9d1 */ { 0x0000, 0x0000, 0x0000 },
/*  9d2 */ { 0x0000, 0x0000, 0x0000 },
/*  9d3 */ { 0x0000, 0x0000, 0x0000 },
/*  9d4 */ { 0x0000, 0x0000, 0x0000 },
/*  9d5 */ { 0x0000, 0x0000, 0x0000 },
/*  9d6 */ { 0x0000, 0x0000, 0x0000 },
/* 09D7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI AU LENGTH MARK 
/*  9d8 */ { 0x0000, 0x0000, 0x0000 },
/*  9d9 */ { 0x0000, 0x0000, 0x0000 },
/*  9da */ { 0x0000, 0x0000, 0x0000 },
/*  9db */ { 0x0000, 0x0000, 0x0000 },
/* 09DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x09A1,0x09BC,0x0000,0x0000 }, // BENGALI LETTER RRA 
/* 09DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x09A2,0x09BC,0x0000,0x0000 }, // BENGALI LETTER RHA 
/*  9de */ { 0x0000, 0x0000, 0x0000 },
/* 09DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x09AF,0x09BC,0x0000,0x0000 }, // BENGALI LETTER YYA 
/* 09E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER VOCALIC RR 
/* 09E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER VOCALIC LL 
/* 09E2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN VOCALIC L 
/* 09E3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI VOWEL SIGN VOCALIC LL 
/*  9e4 */ { 0x0000, 0x0000, 0x0000 },
/*  9e5 */ { 0x0000, 0x0000, 0x0000 },
/* 09E6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT ZERO 
/* 09E7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT ONE 
/* 09E8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT TWO 
/* 09E9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT THREE 
/* 09EA */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT FOUR 
/* 09EB */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT FIVE 
/* 09EC */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT SIX 
/* 09ED */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT SEVEN 
/* 09EE */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT EIGHT 
/* 09EF */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI DIGIT NINE 
/* 09F0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER RA WITH MIDDLE DIAGONAL 
/* 09F1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI LETTER RA WITH LOWER DIAGONAL 
/* 09F2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI RUPEE MARK 
/* 09F3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI RUPEE SIGN 
/* 09F4 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI CURRENCY NUMERATOR ONE 
/* 09F5 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI CURRENCY NUMERATOR TWO 
/* 09F6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI CURRENCY NUMERATOR THREE 
/* 09F7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI CURRENCY NUMERATOR FOUR 
/* 09F8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI CURRENCY NUMERATOR ONE LESS THAN THE DENOMINATOR 
/* 09F9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI CURRENCY DENOMINATOR SIXTEEN 
/* 09FA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BENGALI ISSHAR 
/*  9fb */ { 0x0000, 0x0000, 0x0000 },
/*  9fc */ { 0x0000, 0x0000, 0x0000 },
/*  9fd */ { 0x0000, 0x0000, 0x0000 },
/*  9fe */ { 0x0000, 0x0000, 0x0000 },
/*  9ff */ { 0x0000, 0x0000, 0x0000 },
/*  a00 */ { 0x0000, 0x0000, 0x0000 },
/* 0A01 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI SIGN ADAK BINDI 
/* 0A02 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI SIGN BINDI 
/* 0A03 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI SIGN VISARGA 
/*  a04 */ { 0x0000, 0x0000, 0x0000 },
/* 0A05 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER A 
/* 0A06 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER AA 
/* 0A07 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER I 
/* 0A08 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER II 
/* 0A09 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER U 
/* 0A0A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER UU 
/*  a0b */ { 0x0000, 0x0000, 0x0000 },
/*  a0c */ { 0x0000, 0x0000, 0x0000 },
/*  a0d */ { 0x0000, 0x0000, 0x0000 },
/*  a0e */ { 0x0000, 0x0000, 0x0000 },
/* 0A0F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER EE 
/* 0A10 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER AI 
/*  a11 */ { 0x0000, 0x0000, 0x0000 },
/*  a12 */ { 0x0000, 0x0000, 0x0000 },
/* 0A13 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER OO 
/* 0A14 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER AU 
/* 0A15 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER KA 
/* 0A16 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER KHA 
/* 0A17 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER GA 
/* 0A18 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER GHA 
/* 0A19 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER NGA 
/* 0A1A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER CA 
/* 0A1B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER CHA 
/* 0A1C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER JA 
/* 0A1D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER JHA 
/* 0A1E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER NYA 
/* 0A1F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER TTA 
/* 0A20 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER TTHA 
/* 0A21 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER DDA 
/* 0A22 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER DDHA 
/* 0A23 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER NNA 
/* 0A24 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER TA 
/* 0A25 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER THA 
/* 0A26 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER DA 
/* 0A27 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER DHA 
/* 0A28 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER NA 
/*  a29 */ { 0x0000, 0x0000, 0x0000 },
/* 0A2A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER PA 
/* 0A2B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER PHA 
/* 0A2C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER BA 
/* 0A2D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER BHA 
/* 0A2E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER MA 
/* 0A2F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER YA 
/* 0A30 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER RA 
/*  a31 */ { 0x0000, 0x0000, 0x0000 },
/* 0A32 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER LA 
/* 0A33 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0A32,0x0A3C,0x0000,0x0000 }, // GURMUKHI LETTER LLA 
/*  a34 */ { 0x0000, 0x0000, 0x0000 },
/* 0A35 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER VA 
/* 0A36 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0A38,0x0A3C,0x0000,0x0000 }, // GURMUKHI LETTER SHA 
/*  a37 */ { 0x0000, 0x0000, 0x0000 },
/* 0A38 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER SA 
/* 0A39 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER HA 
/*  a3a */ { 0x0000, 0x0000, 0x0000 },
/*  a3b */ { 0x0000, 0x0000, 0x0000 },
/* 0A3C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI SIGN NUKTA 
/*  a3d */ { 0x0000, 0x0000, 0x0000 },
/* 0A3E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN AA 
/* 0A3F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN I 
/* 0A40 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN II 
/* 0A41 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN U 
/* 0A42 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN UU 
/*  a43 */ { 0x0000, 0x0000, 0x0000 },
/*  a44 */ { 0x0000, 0x0000, 0x0000 },
/*  a45 */ { 0x0000, 0x0000, 0x0000 },
/*  a46 */ { 0x0000, 0x0000, 0x0000 },
/* 0A47 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN EE 
/* 0A48 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN AI 
/*  a49 */ { 0x0000, 0x0000, 0x0000 },
/*  a4a */ { 0x0000, 0x0000, 0x0000 },
/* 0A4B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN OO 
/* 0A4C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI VOWEL SIGN AU 
/* 0A4D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI SIGN VIRAMA 
/*  a4e */ { 0x0000, 0x0000, 0x0000 },
/*  a4f */ { 0x0000, 0x0000, 0x0000 },
/*  a50 */ { 0x0000, 0x0000, 0x0000 },
/*  a51 */ { 0x0000, 0x0000, 0x0000 },
/*  a52 */ { 0x0000, 0x0000, 0x0000 },
/*  a53 */ { 0x0000, 0x0000, 0x0000 },
/*  a54 */ { 0x0000, 0x0000, 0x0000 },
/*  a55 */ { 0x0000, 0x0000, 0x0000 },
/*  a56 */ { 0x0000, 0x0000, 0x0000 },
/*  a57 */ { 0x0000, 0x0000, 0x0000 },
/*  a58 */ { 0x0000, 0x0000, 0x0000 },
/* 0A59 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0A16,0x0A3C,0x0000,0x0000 }, // GURMUKHI LETTER KHHA 
/* 0A5A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0A17,0x0A3C,0x0000,0x0000 }, // GURMUKHI LETTER GHHA 
/* 0A5B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0A1C,0x0A3C,0x0000,0x0000 }, // GURMUKHI LETTER ZA 
/* 0A5C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI LETTER RRA 
/*  a5d */ { 0x0000, 0x0000, 0x0000 },
/* 0A5E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0A2B,0x0A3C,0x0000,0x0000 }, // GURMUKHI LETTER FA 
/*  a5f */ { 0x0000, 0x0000, 0x0000 },
/*  a60 */ { 0x0000, 0x0000, 0x0000 },
/*  a61 */ { 0x0000, 0x0000, 0x0000 },
/*  a62 */ { 0x0000, 0x0000, 0x0000 },
/*  a63 */ { 0x0000, 0x0000, 0x0000 },
/*  a64 */ { 0x0000, 0x0000, 0x0000 },
/*  a65 */ { 0x0000, 0x0000, 0x0000 },
/* 0A66 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT ZERO 
/* 0A67 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT ONE 
/* 0A68 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT TWO 
/* 0A69 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT THREE 
/* 0A6A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT FOUR 
/* 0A6B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT FIVE 
/* 0A6C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT SIX 
/* 0A6D */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT SEVEN 
/* 0A6E */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT EIGHT 
/* 0A6F */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI DIGIT NINE 
/* 0A70 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI TIPPI 
/* 0A71 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI ADDAK 
/* 0A72 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI IRI 
/* 0A73 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI URA 
/* 0A74 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GURMUKHI EK ONKAR 
/*  a75 */ { 0x0000, 0x0000, 0x0000 },
/*  a76 */ { 0x0000, 0x0000, 0x0000 },
/*  a77 */ { 0x0000, 0x0000, 0x0000 },
/*  a78 */ { 0x0000, 0x0000, 0x0000 },
/*  a79 */ { 0x0000, 0x0000, 0x0000 },
/*  a7a */ { 0x0000, 0x0000, 0x0000 },
/*  a7b */ { 0x0000, 0x0000, 0x0000 },
/*  a7c */ { 0x0000, 0x0000, 0x0000 },
/*  a7d */ { 0x0000, 0x0000, 0x0000 },
/*  a7e */ { 0x0000, 0x0000, 0x0000 },
/*  a7f */ { 0x0000, 0x0000, 0x0000 },
/*  a80 */ { 0x0000, 0x0000, 0x0000 },
/* 0A81 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI SIGN CANDRABINDU 
/* 0A82 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI SIGN ANUSVARA 
/* 0A83 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI SIGN VISARGA 
/*  a84 */ { 0x0000, 0x0000, 0x0000 },
/* 0A85 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER A 
/* 0A86 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER AA 
/* 0A87 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER I 
/* 0A88 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER II 
/* 0A89 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER U 
/* 0A8A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER UU 
/* 0A8B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER VOCALIC R 
/* 0A8C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER VOCALIC L 
/* 0A8D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL CANDRA E 
/*  a8e */ { 0x0000, 0x0000, 0x0000 },
/* 0A8F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER E 
/* 0A90 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER AI 
/* 0A91 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL CANDRA O 
/*  a92 */ { 0x0000, 0x0000, 0x0000 },
/* 0A93 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER O 
/* 0A94 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER AU 
/* 0A95 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER KA 
/* 0A96 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER KHA 
/* 0A97 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER GA 
/* 0A98 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER GHA 
/* 0A99 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER NGA 
/* 0A9A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER CA 
/* 0A9B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER CHA 
/* 0A9C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER JA 
/* 0A9D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER JHA 
/* 0A9E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER NYA 
/* 0A9F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER TTA 
/* 0AA0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER TTHA 
/* 0AA1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER DDA 
/* 0AA2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER DDHA 
/* 0AA3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER NNA 
/* 0AA4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER TA 
/* 0AA5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER THA 
/* 0AA6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER DA 
/* 0AA7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER DHA 
/* 0AA8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER NA 
/*  aa9 */ { 0x0000, 0x0000, 0x0000 },
/* 0AAA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER PA 
/* 0AAB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER PHA 
/* 0AAC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER BA 
/* 0AAD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER BHA 
/* 0AAE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER MA 
/* 0AAF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER YA 
/* 0AB0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER RA 
/*  ab1 */ { 0x0000, 0x0000, 0x0000 },
/* 0AB2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER LA 
/* 0AB3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER LLA 
/*  ab4 */ { 0x0000, 0x0000, 0x0000 },
/* 0AB5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER VA 
/* 0AB6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER SHA 
/* 0AB7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER SSA 
/* 0AB8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER SA 
/* 0AB9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER HA 
/*  aba */ { 0x0000, 0x0000, 0x0000 },
/*  abb */ { 0x0000, 0x0000, 0x0000 },
/* 0ABC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI SIGN NUKTA 
/* 0ABD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI SIGN AVAGRAHA 
/* 0ABE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN AA 
/* 0ABF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN I 
/* 0AC0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN II 
/* 0AC1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN U 
/* 0AC2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN UU 
/* 0AC3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN VOCALIC R 
/* 0AC4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN VOCALIC RR 
/* 0AC5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN CANDRA E 
/*  ac6 */ { 0x0000, 0x0000, 0x0000 },
/* 0AC7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN E 
/* 0AC8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN AI 
/* 0AC9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN CANDRA O 
/*  aca */ { 0x0000, 0x0000, 0x0000 },
/* 0ACB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN O 
/* 0ACC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN AU 
/* 0ACD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI SIGN VIRAMA 
/*  ace */ { 0x0000, 0x0000, 0x0000 },
/*  acf */ { 0x0000, 0x0000, 0x0000 },
/* 0AD0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI OM 
/*  ad1 */ { 0x0000, 0x0000, 0x0000 },
/*  ad2 */ { 0x0000, 0x0000, 0x0000 },
/*  ad3 */ { 0x0000, 0x0000, 0x0000 },
/*  ad4 */ { 0x0000, 0x0000, 0x0000 },
/*  ad5 */ { 0x0000, 0x0000, 0x0000 },
/*  ad6 */ { 0x0000, 0x0000, 0x0000 },
/*  ad7 */ { 0x0000, 0x0000, 0x0000 },
/*  ad8 */ { 0x0000, 0x0000, 0x0000 },
/*  ad9 */ { 0x0000, 0x0000, 0x0000 },
/*  ada */ { 0x0000, 0x0000, 0x0000 },
/*  adb */ { 0x0000, 0x0000, 0x0000 },
/*  adc */ { 0x0000, 0x0000, 0x0000 },
/*  add */ { 0x0000, 0x0000, 0x0000 },
/*  ade */ { 0x0000, 0x0000, 0x0000 },
/*  adf */ { 0x0000, 0x0000, 0x0000 },
/* 0AE0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER VOCALIC RR 
/* 0AE1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI LETTER VOCALIC LL 
/* 0AE2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN VOCALIC L 
/* 0AE3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI VOWEL SIGN VOCALIC LL 
/*  ae4 */ { 0x0000, 0x0000, 0x0000 },
/*  ae5 */ { 0x0000, 0x0000, 0x0000 },
/* 0AE6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT ZERO 
/* 0AE7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT ONE 
/* 0AE8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT TWO 
/* 0AE9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT THREE 
/* 0AEA */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT FOUR 
/* 0AEB */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT FIVE 
/* 0AEC */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT SIX 
/* 0AED */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT SEVEN 
/* 0AEE */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT EIGHT 
/* 0AEF */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI DIGIT NINE 
/*  af0 */ { 0x0000, 0x0000, 0x0000 },
/* 0AF1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUJARATI RUPEE SIGN 
/*  af2 */ { 0x0000, 0x0000, 0x0000 },
/*  af3 */ { 0x0000, 0x0000, 0x0000 },
/*  af4 */ { 0x0000, 0x0000, 0x0000 },
/*  af5 */ { 0x0000, 0x0000, 0x0000 },
/*  af6 */ { 0x0000, 0x0000, 0x0000 },
/*  af7 */ { 0x0000, 0x0000, 0x0000 },
/*  af8 */ { 0x0000, 0x0000, 0x0000 },
/*  af9 */ { 0x0000, 0x0000, 0x0000 },
/*  afa */ { 0x0000, 0x0000, 0x0000 },
/*  afb */ { 0x0000, 0x0000, 0x0000 },
/*  afc */ { 0x0000, 0x0000, 0x0000 },
/*  afd */ { 0x0000, 0x0000, 0x0000 },
/*  afe */ { 0x0000, 0x0000, 0x0000 },
/*  aff */ { 0x0000, 0x0000, 0x0000 },
/*  b00 */ { 0x0000, 0x0000, 0x0000 },
/* 0B01 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA SIGN CANDRABINDU 
/* 0B02 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA SIGN ANUSVARA 
/* 0B03 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA SIGN VISARGA 
/*  b04 */ { 0x0000, 0x0000, 0x0000 },
/* 0B05 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER A 
/* 0B06 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER AA 
/* 0B07 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER I 
/* 0B08 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER II 
/* 0B09 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER U 
/* 0B0A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER UU 
/* 0B0B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER VOCALIC R 
/* 0B0C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER VOCALIC L 
/*  b0d */ { 0x0000, 0x0000, 0x0000 },
/*  b0e */ { 0x0000, 0x0000, 0x0000 },
/* 0B0F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER E 
/* 0B10 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER AI 
/*  b11 */ { 0x0000, 0x0000, 0x0000 },
/*  b12 */ { 0x0000, 0x0000, 0x0000 },
/* 0B13 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER O 
/* 0B14 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER AU 
/* 0B15 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER KA 
/* 0B16 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER KHA 
/* 0B17 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER GA 
/* 0B18 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER GHA 
/* 0B19 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER NGA 
/* 0B1A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER CA 
/* 0B1B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER CHA 
/* 0B1C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER JA 
/* 0B1D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER JHA 
/* 0B1E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER NYA 
/* 0B1F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER TTA 
/* 0B20 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER TTHA 
/* 0B21 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER DDA 
/* 0B22 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER DDHA 
/* 0B23 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER NNA 
/* 0B24 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER TA 
/* 0B25 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER THA 
/* 0B26 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER DA 
/* 0B27 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER DHA 
/* 0B28 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER NA 
/*  b29 */ { 0x0000, 0x0000, 0x0000 },
/* 0B2A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER PA 
/* 0B2B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER PHA 
/* 0B2C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER BA 
/* 0B2D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER BHA 
/* 0B2E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER MA 
/* 0B2F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER YA 
/* 0B30 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER RA 
/*  b31 */ { 0x0000, 0x0000, 0x0000 },
/* 0B32 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER LA 
/* 0B33 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER LLA 
/*  b34 */ { 0x0000, 0x0000, 0x0000 },
/* 0B35 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER VA 
/* 0B36 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER SHA 
/* 0B37 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER SSA 
/* 0B38 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER SA 
/* 0B39 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER HA 
/*  b3a */ { 0x0000, 0x0000, 0x0000 },
/*  b3b */ { 0x0000, 0x0000, 0x0000 },
/* 0B3C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA SIGN NUKTA 
/* 0B3D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA SIGN AVAGRAHA 
/* 0B3E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA VOWEL SIGN AA 
/* 0B3F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA VOWEL SIGN I 
/* 0B40 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA VOWEL SIGN II 
/* 0B41 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA VOWEL SIGN U 
/* 0B42 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA VOWEL SIGN UU 
/* 0B43 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA VOWEL SIGN VOCALIC R 
/*  b44 */ { 0x0000, 0x0000, 0x0000 },
/*  b45 */ { 0x0000, 0x0000, 0x0000 },
/*  b46 */ { 0x0000, 0x0000, 0x0000 },
/* 0B47 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA VOWEL SIGN E 
/* 0B48 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0B47,0x0B56,0x0000,0x0000 }, // ORIYA VOWEL SIGN AI 
/*  b49 */ { 0x0000, 0x0000, 0x0000 },
/*  b4a */ { 0x0000, 0x0000, 0x0000 },
/* 0B4B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0B47,0x0B3E,0x0000,0x0000 }, // ORIYA VOWEL SIGN O 
/* 0B4C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0B47,0x0B57,0x0000,0x0000 }, // ORIYA VOWEL SIGN AU 
/* 0B4D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA SIGN VIRAMA 
/*  b4e */ { 0x0000, 0x0000, 0x0000 },
/*  b4f */ { 0x0000, 0x0000, 0x0000 },
/*  b50 */ { 0x0000, 0x0000, 0x0000 },
/*  b51 */ { 0x0000, 0x0000, 0x0000 },
/*  b52 */ { 0x0000, 0x0000, 0x0000 },
/*  b53 */ { 0x0000, 0x0000, 0x0000 },
/*  b54 */ { 0x0000, 0x0000, 0x0000 },
/*  b55 */ { 0x0000, 0x0000, 0x0000 },
/* 0B56 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA AI LENGTH MARK 
/* 0B57 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA AU LENGTH MARK 
/*  b58 */ { 0x0000, 0x0000, 0x0000 },
/*  b59 */ { 0x0000, 0x0000, 0x0000 },
/*  b5a */ { 0x0000, 0x0000, 0x0000 },
/*  b5b */ { 0x0000, 0x0000, 0x0000 },
/* 0B5C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0B21,0x0B3C,0x0000,0x0000 }, // ORIYA LETTER RRA 
/* 0B5D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0B22,0x0B3C,0x0000,0x0000 }, // ORIYA LETTER RHA 
/*  b5e */ { 0x0000, 0x0000, 0x0000 },
/* 0B5F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER YYA 
/* 0B60 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER VOCALIC RR 
/* 0B61 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER VOCALIC LL 
/*  b62 */ { 0x0000, 0x0000, 0x0000 },
/*  b63 */ { 0x0000, 0x0000, 0x0000 },
/*  b64 */ { 0x0000, 0x0000, 0x0000 },
/*  b65 */ { 0x0000, 0x0000, 0x0000 },
/* 0B66 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT ZERO 
/* 0B67 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT ONE 
/* 0B68 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT TWO 
/* 0B69 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT THREE 
/* 0B6A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT FOUR 
/* 0B6B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT FIVE 
/* 0B6C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT SIX 
/* 0B6D */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT SEVEN 
/* 0B6E */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT EIGHT 
/* 0B6F */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA DIGIT NINE 
/* 0B70 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA ISSHAR 
/* 0B71 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ORIYA LETTER WA 
/*  b72 */ { 0x0000, 0x0000, 0x0000 },
/*  b73 */ { 0x0000, 0x0000, 0x0000 },
/*  b74 */ { 0x0000, 0x0000, 0x0000 },
/*  b75 */ { 0x0000, 0x0000, 0x0000 },
/*  b76 */ { 0x0000, 0x0000, 0x0000 },
/*  b77 */ { 0x0000, 0x0000, 0x0000 },
/*  b78 */ { 0x0000, 0x0000, 0x0000 },
/*  b79 */ { 0x0000, 0x0000, 0x0000 },
/*  b7a */ { 0x0000, 0x0000, 0x0000 },
/*  b7b */ { 0x0000, 0x0000, 0x0000 },
/*  b7c */ { 0x0000, 0x0000, 0x0000 },
/*  b7d */ { 0x0000, 0x0000, 0x0000 },
/*  b7e */ { 0x0000, 0x0000, 0x0000 },
/*  b7f */ { 0x0000, 0x0000, 0x0000 },
/*  b80 */ { 0x0000, 0x0000, 0x0000 },
/*  b81 */ { 0x0000, 0x0000, 0x0000 },
/* 0B82 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL SIGN ANUSVARA 
/* 0B83 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL SIGN VISARGA 
/*  b84 */ { 0x0000, 0x0000, 0x0000 },
/* 0B85 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER A 
/* 0B86 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER AA 
/* 0B87 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER I 
/* 0B88 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER II 
/* 0B89 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER U 
/* 0B8A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER UU 
/*  b8b */ { 0x0000, 0x0000, 0x0000 },
/*  b8c */ { 0x0000, 0x0000, 0x0000 },
/*  b8d */ { 0x0000, 0x0000, 0x0000 },
/* 0B8E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER E 
/* 0B8F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER EE 
/* 0B90 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER AI 
/*  b91 */ { 0x0000, 0x0000, 0x0000 },
/* 0B92 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER O 
/* 0B93 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER OO 
/* 0B94 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0B92,0x0BD7,0x0000,0x0000 }, // TAMIL LETTER AU 
/* 0B95 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER KA 
/*  b96 */ { 0x0000, 0x0000, 0x0000 },
/*  b97 */ { 0x0000, 0x0000, 0x0000 },
/*  b98 */ { 0x0000, 0x0000, 0x0000 },
/* 0B99 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER NGA 
/* 0B9A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER CA 
/*  b9b */ { 0x0000, 0x0000, 0x0000 },
/* 0B9C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER JA 
/*  b9d */ { 0x0000, 0x0000, 0x0000 },
/* 0B9E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER NYA 
/* 0B9F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER TTA 
/*  ba0 */ { 0x0000, 0x0000, 0x0000 },
/*  ba1 */ { 0x0000, 0x0000, 0x0000 },
/*  ba2 */ { 0x0000, 0x0000, 0x0000 },
/* 0BA3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER NNA 
/* 0BA4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER TA 
/*  ba5 */ { 0x0000, 0x0000, 0x0000 },
/*  ba6 */ { 0x0000, 0x0000, 0x0000 },
/*  ba7 */ { 0x0000, 0x0000, 0x0000 },
/* 0BA8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER NA 
/* 0BA9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER NNNA 
/* 0BAA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER PA 
/*  bab */ { 0x0000, 0x0000, 0x0000 },
/*  bac */ { 0x0000, 0x0000, 0x0000 },
/*  bad */ { 0x0000, 0x0000, 0x0000 },
/* 0BAE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER MA 
/* 0BAF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER YA 
/* 0BB0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER RA 
/* 0BB1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER RRA 
/* 0BB2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER LA 
/* 0BB3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER LLA 
/* 0BB4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER LLLA 
/* 0BB5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER VA 
/* 0BB6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER SHA 
/* 0BB7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER SSA 
/* 0BB8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER SA 
/* 0BB9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL LETTER HA 
/*  bba */ { 0x0000, 0x0000, 0x0000 },
/*  bbb */ { 0x0000, 0x0000, 0x0000 },
/*  bbc */ { 0x0000, 0x0000, 0x0000 },
/*  bbd */ { 0x0000, 0x0000, 0x0000 },
/* 0BBE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL VOWEL SIGN AA 
/* 0BBF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL VOWEL SIGN I 
/* 0BC0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL VOWEL SIGN II 
/* 0BC1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL VOWEL SIGN U 
/* 0BC2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL VOWEL SIGN UU 
/*  bc3 */ { 0x0000, 0x0000, 0x0000 },
/*  bc4 */ { 0x0000, 0x0000, 0x0000 },
/*  bc5 */ { 0x0000, 0x0000, 0x0000 },
/* 0BC6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL VOWEL SIGN E 
/* 0BC7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL VOWEL SIGN EE 
/* 0BC8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL VOWEL SIGN AI 
/*  bc9 */ { 0x0000, 0x0000, 0x0000 },
/* 0BCA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0BC6,0x0BBE,0x0000,0x0000 }, // TAMIL VOWEL SIGN O 
/* 0BCB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0BC7,0x0BBE,0x0000,0x0000 }, // TAMIL VOWEL SIGN OO 
/* 0BCC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0BC6,0x0BD7,0x0000,0x0000 }, // TAMIL VOWEL SIGN AU 
/* 0BCD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL SIGN VIRAMA 
/*  bce */ { 0x0000, 0x0000, 0x0000 },
/*  bcf */ { 0x0000, 0x0000, 0x0000 },
/*  bd0 */ { 0x0000, 0x0000, 0x0000 },
/*  bd1 */ { 0x0000, 0x0000, 0x0000 },
/*  bd2 */ { 0x0000, 0x0000, 0x0000 },
/*  bd3 */ { 0x0000, 0x0000, 0x0000 },
/*  bd4 */ { 0x0000, 0x0000, 0x0000 },
/*  bd5 */ { 0x0000, 0x0000, 0x0000 },
/*  bd6 */ { 0x0000, 0x0000, 0x0000 },
/* 0BD7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL AU LENGTH MARK 
/*  bd8 */ { 0x0000, 0x0000, 0x0000 },
/*  bd9 */ { 0x0000, 0x0000, 0x0000 },
/*  bda */ { 0x0000, 0x0000, 0x0000 },
/*  bdb */ { 0x0000, 0x0000, 0x0000 },
/*  bdc */ { 0x0000, 0x0000, 0x0000 },
/*  bdd */ { 0x0000, 0x0000, 0x0000 },
/*  bde */ { 0x0000, 0x0000, 0x0000 },
/*  bdf */ { 0x0000, 0x0000, 0x0000 },
/*  be0 */ { 0x0000, 0x0000, 0x0000 },
/*  be1 */ { 0x0000, 0x0000, 0x0000 },
/*  be2 */ { 0x0000, 0x0000, 0x0000 },
/*  be3 */ { 0x0000, 0x0000, 0x0000 },
/*  be4 */ { 0x0000, 0x0000, 0x0000 },
/*  be5 */ { 0x0000, 0x0000, 0x0000 },
/* 0BE6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT ZERO 
/* 0BE7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT ONE 
/* 0BE8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT TWO 
/* 0BE9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT THREE 
/* 0BEA */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT FOUR 
/* 0BEB */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT FIVE 
/* 0BEC */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT SIX 
/* 0BED */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT SEVEN 
/* 0BEE */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT EIGHT 
/* 0BEF */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DIGIT NINE 
/* 0BF0 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL NUMBER TEN 
/* 0BF1 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL NUMBER ONE HUNDRED 
/* 0BF2 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL NUMBER ONE THOUSAND 
/* 0BF3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DAY SIGN 
/* 0BF4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL MONTH SIGN 
/* 0BF5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL YEAR SIGN 
/* 0BF6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL DEBIT SIGN 
/* 0BF7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL CREDIT SIGN 
/* 0BF8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL AS ABOVE SIGN 
/* 0BF9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL RUPEE SIGN 
/* 0BFA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAMIL NUMBER SIGN 
/*  bfb */ { 0x0000, 0x0000, 0x0000 },
/*  bfc */ { 0x0000, 0x0000, 0x0000 },
/*  bfd */ { 0x0000, 0x0000, 0x0000 },
/*  bfe */ { 0x0000, 0x0000, 0x0000 },
/*  bff */ { 0x0000, 0x0000, 0x0000 },
/*  c00 */ { 0x0000, 0x0000, 0x0000 },
/* 0C01 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU SIGN CANDRABINDU 
/* 0C02 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU SIGN ANUSVARA 
/* 0C03 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU SIGN VISARGA 
/*  c04 */ { 0x0000, 0x0000, 0x0000 },
/* 0C05 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER A 
/* 0C06 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER AA 
/* 0C07 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER I 
/* 0C08 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER II 
/* 0C09 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER U 
/* 0C0A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER UU 
/* 0C0B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER VOCALIC R 
/* 0C0C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER VOCALIC L 
/*  c0d */ { 0x0000, 0x0000, 0x0000 },
/* 0C0E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER E 
/* 0C0F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER EE 
/* 0C10 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER AI 
/*  c11 */ { 0x0000, 0x0000, 0x0000 },
/* 0C12 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER O 
/* 0C13 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER OO 
/* 0C14 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER AU 
/* 0C15 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER KA 
/* 0C16 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER KHA 
/* 0C17 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER GA 
/* 0C18 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER GHA 
/* 0C19 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER NGA 
/* 0C1A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER CA 
/* 0C1B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER CHA 
/* 0C1C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER JA 
/* 0C1D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER JHA 
/* 0C1E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER NYA 
/* 0C1F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER TTA 
/* 0C20 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER TTHA 
/* 0C21 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER DDA 
/* 0C22 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER DDHA 
/* 0C23 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER NNA 
/* 0C24 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER TA 
/* 0C25 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER THA 
/* 0C26 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER DA 
/* 0C27 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER DHA 
/* 0C28 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER NA 
/*  c29 */ { 0x0000, 0x0000, 0x0000 },
/* 0C2A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER PA 
/* 0C2B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER PHA 
/* 0C2C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER BA 
/* 0C2D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER BHA 
/* 0C2E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER MA 
/* 0C2F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER YA 
/* 0C30 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER RA 
/* 0C31 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER RRA 
/* 0C32 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER LA 
/* 0C33 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER LLA 
/*  c34 */ { 0x0000, 0x0000, 0x0000 },
/* 0C35 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER VA 
/* 0C36 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER SHA 
/* 0C37 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER SSA 
/* 0C38 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER SA 
/* 0C39 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER HA 
/*  c3a */ { 0x0000, 0x0000, 0x0000 },
/*  c3b */ { 0x0000, 0x0000, 0x0000 },
/*  c3c */ { 0x0000, 0x0000, 0x0000 },
/*  c3d */ { 0x0000, 0x0000, 0x0000 },
/* 0C3E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN AA 
/* 0C3F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN I 
/* 0C40 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN II 
/* 0C41 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN U 
/* 0C42 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN UU 
/* 0C43 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN VOCALIC R 
/* 0C44 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN VOCALIC RR 
/*  c45 */ { 0x0000, 0x0000, 0x0000 },
/* 0C46 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN E 
/* 0C47 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN EE 
/* 0C48 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0C46,0x0C56,0x0000,0x0000 }, // TELUGU VOWEL SIGN AI 
/*  c49 */ { 0x0000, 0x0000, 0x0000 },
/* 0C4A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN O 
/* 0C4B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN OO 
/* 0C4C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU VOWEL SIGN AU 
/* 0C4D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU SIGN VIRAMA 
/*  c4e */ { 0x0000, 0x0000, 0x0000 },
/*  c4f */ { 0x0000, 0x0000, 0x0000 },
/*  c50 */ { 0x0000, 0x0000, 0x0000 },
/*  c51 */ { 0x0000, 0x0000, 0x0000 },
/*  c52 */ { 0x0000, 0x0000, 0x0000 },
/*  c53 */ { 0x0000, 0x0000, 0x0000 },
/*  c54 */ { 0x0000, 0x0000, 0x0000 },
/* 0C55 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LENGTH MARK 
/* 0C56 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU AI LENGTH MARK 
/*  c57 */ { 0x0000, 0x0000, 0x0000 },
/*  c58 */ { 0x0000, 0x0000, 0x0000 },
/*  c59 */ { 0x0000, 0x0000, 0x0000 },
/*  c5a */ { 0x0000, 0x0000, 0x0000 },
/*  c5b */ { 0x0000, 0x0000, 0x0000 },
/*  c5c */ { 0x0000, 0x0000, 0x0000 },
/*  c5d */ { 0x0000, 0x0000, 0x0000 },
/*  c5e */ { 0x0000, 0x0000, 0x0000 },
/*  c5f */ { 0x0000, 0x0000, 0x0000 },
/* 0C60 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER VOCALIC RR 
/* 0C61 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU LETTER VOCALIC LL 
/*  c62 */ { 0x0000, 0x0000, 0x0000 },
/*  c63 */ { 0x0000, 0x0000, 0x0000 },
/*  c64 */ { 0x0000, 0x0000, 0x0000 },
/*  c65 */ { 0x0000, 0x0000, 0x0000 },
/* 0C66 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT ZERO 
/* 0C67 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT ONE 
/* 0C68 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT TWO 
/* 0C69 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT THREE 
/* 0C6A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT FOUR 
/* 0C6B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT FIVE 
/* 0C6C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT SIX 
/* 0C6D */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT SEVEN 
/* 0C6E */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT EIGHT 
/* 0C6F */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TELUGU DIGIT NINE 
/*  c70 */ { 0x0000, 0x0000, 0x0000 },
/*  c71 */ { 0x0000, 0x0000, 0x0000 },
/*  c72 */ { 0x0000, 0x0000, 0x0000 },
/*  c73 */ { 0x0000, 0x0000, 0x0000 },
/*  c74 */ { 0x0000, 0x0000, 0x0000 },
/*  c75 */ { 0x0000, 0x0000, 0x0000 },
/*  c76 */ { 0x0000, 0x0000, 0x0000 },
/*  c77 */ { 0x0000, 0x0000, 0x0000 },
/*  c78 */ { 0x0000, 0x0000, 0x0000 },
/*  c79 */ { 0x0000, 0x0000, 0x0000 },
/*  c7a */ { 0x0000, 0x0000, 0x0000 },
/*  c7b */ { 0x0000, 0x0000, 0x0000 },
/*  c7c */ { 0x0000, 0x0000, 0x0000 },
/*  c7d */ { 0x0000, 0x0000, 0x0000 },
/*  c7e */ { 0x0000, 0x0000, 0x0000 },
/*  c7f */ { 0x0000, 0x0000, 0x0000 },
/*  c80 */ { 0x0000, 0x0000, 0x0000 },
/*  c81 */ { 0x0000, 0x0000, 0x0000 },
/* 0C82 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA SIGN ANUSVARA 
/* 0C83 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA SIGN VISARGA 
/*  c84 */ { 0x0000, 0x0000, 0x0000 },
/* 0C85 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER A 
/* 0C86 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER AA 
/* 0C87 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER I 
/* 0C88 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER II 
/* 0C89 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER U 
/* 0C8A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER UU 
/* 0C8B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER VOCALIC R 
/* 0C8C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER VOCALIC L 
/*  c8d */ { 0x0000, 0x0000, 0x0000 },
/* 0C8E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER E 
/* 0C8F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER EE 
/* 0C90 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER AI 
/*  c91 */ { 0x0000, 0x0000, 0x0000 },
/* 0C92 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER O 
/* 0C93 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER OO 
/* 0C94 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER AU 
/* 0C95 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER KA 
/* 0C96 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER KHA 
/* 0C97 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER GA 
/* 0C98 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER GHA 
/* 0C99 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER NGA 
/* 0C9A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER CA 
/* 0C9B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER CHA 
/* 0C9C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER JA 
/* 0C9D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER JHA 
/* 0C9E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER NYA 
/* 0C9F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER TTA 
/* 0CA0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER TTHA 
/* 0CA1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER DDA 
/* 0CA2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER DDHA 
/* 0CA3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER NNA 
/* 0CA4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER TA 
/* 0CA5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER THA 
/* 0CA6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER DA 
/* 0CA7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER DHA 
/* 0CA8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER NA 
/*  ca9 */ { 0x0000, 0x0000, 0x0000 },
/* 0CAA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER PA 
/* 0CAB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER PHA 
/* 0CAC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER BA 
/* 0CAD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER BHA 
/* 0CAE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER MA 
/* 0CAF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER YA 
/* 0CB0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER RA 
/* 0CB1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER RRA 
/* 0CB2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER LA 
/* 0CB3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER LLA 
/*  cb4 */ { 0x0000, 0x0000, 0x0000 },
/* 0CB5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER VA 
/* 0CB6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER SHA 
/* 0CB7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER SSA 
/* 0CB8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER SA 
/* 0CB9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER HA 
/*  cba */ { 0x0000, 0x0000, 0x0000 },
/*  cbb */ { 0x0000, 0x0000, 0x0000 },
/* 0CBC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA SIGN NUKTA 
/* 0CBD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA SIGN AVAGRAHA 
/* 0CBE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA VOWEL SIGN AA 
/* 0CBF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA VOWEL SIGN I 
/* 0CC0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0CBF,0x0CD5,0x0000,0x0000 }, // KANNADA VOWEL SIGN II 
/* 0CC1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA VOWEL SIGN U 
/* 0CC2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA VOWEL SIGN UU 
/* 0CC3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA VOWEL SIGN VOCALIC R 
/* 0CC4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA VOWEL SIGN VOCALIC RR 
/*  cc5 */ { 0x0000, 0x0000, 0x0000 },
/* 0CC6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA VOWEL SIGN E 
/* 0CC7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0CC6,0x0CD5,0x0000,0x0000 }, // KANNADA VOWEL SIGN EE 
/* 0CC8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0CC6,0x0CD6,0x0000,0x0000 }, // KANNADA VOWEL SIGN AI 
/*  cc9 */ { 0x0000, 0x0000, 0x0000 },
/* 0CCA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0CC6,0x0CC2,0x0000,0x0000 }, // KANNADA VOWEL SIGN O 
/* 0CCB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0CCA,0x0CD5,0x0000,0x0000 }, // KANNADA VOWEL SIGN OO 
/* 0CCC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA VOWEL SIGN AU 
/* 0CCD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA SIGN VIRAMA 
/*  cce */ { 0x0000, 0x0000, 0x0000 },
/*  ccf */ { 0x0000, 0x0000, 0x0000 },
/*  cd0 */ { 0x0000, 0x0000, 0x0000 },
/*  cd1 */ { 0x0000, 0x0000, 0x0000 },
/*  cd2 */ { 0x0000, 0x0000, 0x0000 },
/*  cd3 */ { 0x0000, 0x0000, 0x0000 },
/*  cd4 */ { 0x0000, 0x0000, 0x0000 },
/* 0CD5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LENGTH MARK 
/* 0CD6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA AI LENGTH MARK 
/*  cd7 */ { 0x0000, 0x0000, 0x0000 },
/*  cd8 */ { 0x0000, 0x0000, 0x0000 },
/*  cd9 */ { 0x0000, 0x0000, 0x0000 },
/*  cda */ { 0x0000, 0x0000, 0x0000 },
/*  cdb */ { 0x0000, 0x0000, 0x0000 },
/*  cdc */ { 0x0000, 0x0000, 0x0000 },
/*  cdd */ { 0x0000, 0x0000, 0x0000 },
/* 0CDE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER FA 
/*  cdf */ { 0x0000, 0x0000, 0x0000 },
/* 0CE0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER VOCALIC RR 
/* 0CE1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA LETTER VOCALIC LL 
/*  ce2 */ { 0x0000, 0x0000, 0x0000 },
/*  ce3 */ { 0x0000, 0x0000, 0x0000 },
/*  ce4 */ { 0x0000, 0x0000, 0x0000 },
/*  ce5 */ { 0x0000, 0x0000, 0x0000 },
/* 0CE6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT ZERO 
/* 0CE7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT ONE 
/* 0CE8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT TWO 
/* 0CE9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT THREE 
/* 0CEA */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT FOUR 
/* 0CEB */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT FIVE 
/* 0CEC */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT SIX 
/* 0CED */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT SEVEN 
/* 0CEE */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT EIGHT 
/* 0CEF */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KANNADA DIGIT NINE 
/*  cf0 */ { 0x0000, 0x0000, 0x0000 },
/*  cf1 */ { 0x0000, 0x0000, 0x0000 },
/*  cf2 */ { 0x0000, 0x0000, 0x0000 },
/*  cf3 */ { 0x0000, 0x0000, 0x0000 },
/*  cf4 */ { 0x0000, 0x0000, 0x0000 },
/*  cf5 */ { 0x0000, 0x0000, 0x0000 },
/*  cf6 */ { 0x0000, 0x0000, 0x0000 },
/*  cf7 */ { 0x0000, 0x0000, 0x0000 },
/*  cf8 */ { 0x0000, 0x0000, 0x0000 },
/*  cf9 */ { 0x0000, 0x0000, 0x0000 },
/*  cfa */ { 0x0000, 0x0000, 0x0000 },
/*  cfb */ { 0x0000, 0x0000, 0x0000 },
/*  cfc */ { 0x0000, 0x0000, 0x0000 },
/*  cfd */ { 0x0000, 0x0000, 0x0000 },
/*  cfe */ { 0x0000, 0x0000, 0x0000 },
/*  cff */ { 0x0000, 0x0000, 0x0000 },
/*  d00 */ { 0x0000, 0x0000, 0x0000 },
/*  d01 */ { 0x0000, 0x0000, 0x0000 },
/* 0D02 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM SIGN ANUSVARA 
/* 0D03 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM SIGN VISARGA 
/*  d04 */ { 0x0000, 0x0000, 0x0000 },
/* 0D05 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER A 
/* 0D06 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER AA 
/* 0D07 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER I 
/* 0D08 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER II 
/* 0D09 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER U 
/* 0D0A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER UU 
/* 0D0B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER VOCALIC R 
/* 0D0C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER VOCALIC L 
/*  d0d */ { 0x0000, 0x0000, 0x0000 },
/* 0D0E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER E 
/* 0D0F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER EE 
/* 0D10 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER AI 
/*  d11 */ { 0x0000, 0x0000, 0x0000 },
/* 0D12 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER O 
/* 0D13 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER OO 
/* 0D14 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER AU 
/* 0D15 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER KA 
/* 0D16 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER KHA 
/* 0D17 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER GA 
/* 0D18 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER GHA 
/* 0D19 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER NGA 
/* 0D1A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER CA 
/* 0D1B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER CHA 
/* 0D1C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER JA 
/* 0D1D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER JHA 
/* 0D1E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER NYA 
/* 0D1F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER TTA 
/* 0D20 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER TTHA 
/* 0D21 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER DDA 
/* 0D22 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER DDHA 
/* 0D23 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER NNA 
/* 0D24 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER TA 
/* 0D25 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER THA 
/* 0D26 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER DA 
/* 0D27 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER DHA 
/* 0D28 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER NA 
/*  d29 */ { 0x0000, 0x0000, 0x0000 },
/* 0D2A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER PA 
/* 0D2B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER PHA 
/* 0D2C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER BA 
/* 0D2D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER BHA 
/* 0D2E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER MA 
/* 0D2F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER YA 
/* 0D30 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER RA 
/* 0D31 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER RRA 
/* 0D32 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER LA 
/* 0D33 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER LLA 
/* 0D34 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER LLLA 
/* 0D35 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER VA 
/* 0D36 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER SHA 
/* 0D37 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER SSA 
/* 0D38 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER SA 
/* 0D39 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER HA 
/*  d3a */ { 0x0000, 0x0000, 0x0000 },
/*  d3b */ { 0x0000, 0x0000, 0x0000 },
/*  d3c */ { 0x0000, 0x0000, 0x0000 },
/*  d3d */ { 0x0000, 0x0000, 0x0000 },
/* 0D3E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN AA 
/* 0D3F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN I 
/* 0D40 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN II 
/* 0D41 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN U 
/* 0D42 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN UU 
/* 0D43 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN VOCALIC R 
/*  d44 */ { 0x0000, 0x0000, 0x0000 },
/*  d45 */ { 0x0000, 0x0000, 0x0000 },
/* 0D46 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN E 
/* 0D47 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN EE 
/* 0D48 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN AI 
/*  d49 */ { 0x0000, 0x0000, 0x0000 },
/* 0D4A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0D46,0x0D3E,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN O 
/* 0D4B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0D47,0x0D3E,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN OO 
/* 0D4C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0D46,0x0D57,0x0000,0x0000 }, // MALAYALAM VOWEL SIGN AU 
/* 0D4D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM SIGN VIRAMA 
/*  d4e */ { 0x0000, 0x0000, 0x0000 },
/*  d4f */ { 0x0000, 0x0000, 0x0000 },
/*  d50 */ { 0x0000, 0x0000, 0x0000 },
/*  d51 */ { 0x0000, 0x0000, 0x0000 },
/*  d52 */ { 0x0000, 0x0000, 0x0000 },
/*  d53 */ { 0x0000, 0x0000, 0x0000 },
/*  d54 */ { 0x0000, 0x0000, 0x0000 },
/*  d55 */ { 0x0000, 0x0000, 0x0000 },
/*  d56 */ { 0x0000, 0x0000, 0x0000 },
/* 0D57 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM AU LENGTH MARK 
/*  d58 */ { 0x0000, 0x0000, 0x0000 },
/*  d59 */ { 0x0000, 0x0000, 0x0000 },
/*  d5a */ { 0x0000, 0x0000, 0x0000 },
/*  d5b */ { 0x0000, 0x0000, 0x0000 },
/*  d5c */ { 0x0000, 0x0000, 0x0000 },
/*  d5d */ { 0x0000, 0x0000, 0x0000 },
/*  d5e */ { 0x0000, 0x0000, 0x0000 },
/*  d5f */ { 0x0000, 0x0000, 0x0000 },
/* 0D60 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER VOCALIC RR 
/* 0D61 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM LETTER VOCALIC LL 
/*  d62 */ { 0x0000, 0x0000, 0x0000 },
/*  d63 */ { 0x0000, 0x0000, 0x0000 },
/*  d64 */ { 0x0000, 0x0000, 0x0000 },
/*  d65 */ { 0x0000, 0x0000, 0x0000 },
/* 0D66 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT ZERO 
/* 0D67 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT ONE 
/* 0D68 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT TWO 
/* 0D69 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT THREE 
/* 0D6A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT FOUR 
/* 0D6B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT FIVE 
/* 0D6C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT SIX 
/* 0D6D */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT SEVEN 
/* 0D6E */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT EIGHT 
/* 0D6F */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MALAYALAM DIGIT NINE 
/*  d70 */ { 0x0000, 0x0000, 0x0000 },
/*  d71 */ { 0x0000, 0x0000, 0x0000 },
/*  d72 */ { 0x0000, 0x0000, 0x0000 },
/*  d73 */ { 0x0000, 0x0000, 0x0000 },
/*  d74 */ { 0x0000, 0x0000, 0x0000 },
/*  d75 */ { 0x0000, 0x0000, 0x0000 },
/*  d76 */ { 0x0000, 0x0000, 0x0000 },
/*  d77 */ { 0x0000, 0x0000, 0x0000 },
/*  d78 */ { 0x0000, 0x0000, 0x0000 },
/*  d79 */ { 0x0000, 0x0000, 0x0000 },
/*  d7a */ { 0x0000, 0x0000, 0x0000 },
/*  d7b */ { 0x0000, 0x0000, 0x0000 },
/*  d7c */ { 0x0000, 0x0000, 0x0000 },
/*  d7d */ { 0x0000, 0x0000, 0x0000 },
/*  d7e */ { 0x0000, 0x0000, 0x0000 },
/*  d7f */ { 0x0000, 0x0000, 0x0000 },
/*  d80 */ { 0x0000, 0x0000, 0x0000 },
/*  d81 */ { 0x0000, 0x0000, 0x0000 },
/* 0D82 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA SIGN ANUSVARAYA 
/* 0D83 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA SIGN VISARGAYA 
/*  d84 */ { 0x0000, 0x0000, 0x0000 },
/* 0D85 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER AYANNA 
/* 0D86 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER AAYANNA 
/* 0D87 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER AEYANNA 
/* 0D88 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER AEEYANNA 
/* 0D89 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER IYANNA 
/* 0D8A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER IIYANNA 
/* 0D8B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER UYANNA 
/* 0D8C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER UUYANNA 
/* 0D8D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER IRUYANNA 
/* 0D8E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER IRUUYANNA 
/* 0D8F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ILUYANNA 
/* 0D90 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ILUUYANNA 
/* 0D91 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER EYANNA 
/* 0D92 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER EEYANNA 
/* 0D93 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER AIYANNA 
/* 0D94 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER OYANNA 
/* 0D95 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER OOYANNA 
/* 0D96 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER AUYANNA 
/*  d97 */ { 0x0000, 0x0000, 0x0000 },
/*  d98 */ { 0x0000, 0x0000, 0x0000 },
/*  d99 */ { 0x0000, 0x0000, 0x0000 },
/* 0D9A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA KAYANNA 
/* 0D9B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA KAYANNA 
/* 0D9C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA GAYANNA 
/* 0D9D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA GAYANNA 
/* 0D9E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER KANTAJA NAASIKYAYA 
/* 0D9F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER SANYAKA GAYANNA 
/* 0DA0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA CAYANNA 
/* 0DA1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA CAYANNA 
/* 0DA2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA JAYANNA 
/* 0DA3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA JAYANNA 
/* 0DA4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER TAALUJA NAASIKYAYA 
/* 0DA5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER TAALUJA SANYOOGA NAAKSIKYAYA 
/* 0DA6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER SANYAKA JAYANNA 
/* 0DA7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA TTAYANNA 
/* 0DA8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA TTAYANNA 
/* 0DA9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA DDAYANNA 
/* 0DAA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA DDAYANNA 
/* 0DAB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MUURDHAJA NAYANNA 
/* 0DAC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER SANYAKA DDAYANNA 
/* 0DAD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA TAYANNA 
/* 0DAE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA TAYANNA 
/* 0DAF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA DAYANNA 
/* 0DB0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA DAYANNA 
/* 0DB1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER DANTAJA NAYANNA 
/*  db2 */ { 0x0000, 0x0000, 0x0000 },
/* 0DB3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER SANYAKA DAYANNA 
/* 0DB4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA PAYANNA 
/* 0DB5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA PAYANNA 
/* 0DB6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER ALPAPRAANA BAYANNA 
/* 0DB7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAHAAPRAANA BAYANNA 
/* 0DB8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MAYANNA 
/* 0DB9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER AMBA BAYANNA 
/* 0DBA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER YAYANNA 
/* 0DBB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER RAYANNA 
/*  dbc */ { 0x0000, 0x0000, 0x0000 },
/* 0DBD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER DANTAJA LAYANNA 
/*  dbe */ { 0x0000, 0x0000, 0x0000 },
/*  dbf */ { 0x0000, 0x0000, 0x0000 },
/* 0DC0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER VAYANNA 
/* 0DC1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER TAALUJA SAYANNA 
/* 0DC2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MUURDHAJA SAYANNA 
/* 0DC3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER DANTAJA SAYANNA 
/* 0DC4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER HAYANNA 
/* 0DC5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER MUURDHAJA LAYANNA 
/* 0DC6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA LETTER FAYANNA 
/*  dc7 */ { 0x0000, 0x0000, 0x0000 },
/*  dc8 */ { 0x0000, 0x0000, 0x0000 },
/*  dc9 */ { 0x0000, 0x0000, 0x0000 },
/* 0DCA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA SIGN AL-LAKUNA 
/*  dcb */ { 0x0000, 0x0000, 0x0000 },
/*  dcc */ { 0x0000, 0x0000, 0x0000 },
/*  dcd */ { 0x0000, 0x0000, 0x0000 },
/*  dce */ { 0x0000, 0x0000, 0x0000 },
/* 0DCF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN AELA-PILLA 
/* 0DD0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN KETTI AEDA-PILLA 
/* 0DD1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN DIGA AEDA-PILLA 
/* 0DD2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN KETTI IS-PILLA 
/* 0DD3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN DIGA IS-PILLA 
/* 0DD4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN KETTI PAA-PILLA 
/*  dd5 */ { 0x0000, 0x0000, 0x0000 },
/* 0DD6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN DIGA PAA-PILLA 
/*  dd7 */ { 0x0000, 0x0000, 0x0000 },
/* 0DD8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN GAETTA-PILLA 
/* 0DD9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN KOMBUVA 
/* 0DDA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0DD9,0x0DCA,0x0000,0x0000 }, // SINHALA VOWEL SIGN DIGA KOMBUVA 
/* 0DDB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN KOMBU DEKA 
/* 0DDC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0DD9,0x0DCF,0x0000,0x0000 }, // SINHALA VOWEL SIGN KOMBUVA HAA AELA-PILLA 
/* 0DDD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0DDC,0x0DCA,0x0000,0x0000 }, // SINHALA VOWEL SIGN KOMBUVA HAA DIGA AELA-PILLA 
/* 0DDE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0DD9,0x0DDF,0x0000,0x0000 }, // SINHALA VOWEL SIGN KOMBUVA HAA GAYANUKITTA 
/* 0DDF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN GAYANUKITTA 
/*  de0 */ { 0x0000, 0x0000, 0x0000 },
/*  de1 */ { 0x0000, 0x0000, 0x0000 },
/*  de2 */ { 0x0000, 0x0000, 0x0000 },
/*  de3 */ { 0x0000, 0x0000, 0x0000 },
/*  de4 */ { 0x0000, 0x0000, 0x0000 },
/*  de5 */ { 0x0000, 0x0000, 0x0000 },
/*  de6 */ { 0x0000, 0x0000, 0x0000 },
/*  de7 */ { 0x0000, 0x0000, 0x0000 },
/*  de8 */ { 0x0000, 0x0000, 0x0000 },
/*  de9 */ { 0x0000, 0x0000, 0x0000 },
/*  dea */ { 0x0000, 0x0000, 0x0000 },
/*  deb */ { 0x0000, 0x0000, 0x0000 },
/*  dec */ { 0x0000, 0x0000, 0x0000 },
/*  ded */ { 0x0000, 0x0000, 0x0000 },
/*  dee */ { 0x0000, 0x0000, 0x0000 },
/*  def */ { 0x0000, 0x0000, 0x0000 },
/*  df0 */ { 0x0000, 0x0000, 0x0000 },
/*  df1 */ { 0x0000, 0x0000, 0x0000 },
/* 0DF2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN DIGA GAETTA-PILLA 
/* 0DF3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA VOWEL SIGN DIGA GAYANUKITTA 
/* 0DF4 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINHALA PUNCTUATION KUNDDALIYA 
/*  df5 */ { 0x0000, 0x0000, 0x0000 },
/*  df6 */ { 0x0000, 0x0000, 0x0000 },
/*  df7 */ { 0x0000, 0x0000, 0x0000 },
/*  df8 */ { 0x0000, 0x0000, 0x0000 },
/*  df9 */ { 0x0000, 0x0000, 0x0000 },
/*  dfa */ { 0x0000, 0x0000, 0x0000 },
/*  dfb */ { 0x0000, 0x0000, 0x0000 },
/*  dfc */ { 0x0000, 0x0000, 0x0000 },
/*  dfd */ { 0x0000, 0x0000, 0x0000 },
/*  dfe */ { 0x0000, 0x0000, 0x0000 },
/*  dff */ { 0x0000, 0x0000, 0x0000 },
/*  e00 */ { 0x0000, 0x0000, 0x0000 },
/* 0E01 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER KO KAI 
/* 0E02 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER KHO KHAI 
/* 0E03 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER KHO KHUAT 
/* 0E04 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER KHO KHWAI 
/* 0E05 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER KHO KHON 
/* 0E06 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER KHO RAKHANG 
/* 0E07 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER NGO NGU 
/* 0E08 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER CHO CHAN 
/* 0E09 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER CHO CHING 
/* 0E0A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER CHO CHANG 
/* 0E0B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SO SO 
/* 0E0C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER CHO CHOE 
/* 0E0D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER YO YING 
/* 0E0E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER DO CHADA 
/* 0E0F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER TO PATAK 
/* 0E10 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER THO THAN 
/* 0E11 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER THO NANGMONTHO 
/* 0E12 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER THO PHUTHAO 
/* 0E13 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER NO NEN 
/* 0E14 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER DO DEK 
/* 0E15 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER TO TAO 
/* 0E16 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER THO THUNG 
/* 0E17 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER THO THAHAN 
/* 0E18 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER THO THONG 
/* 0E19 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER NO NU 
/* 0E1A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER BO BAIMAI 
/* 0E1B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER PO PLA 
/* 0E1C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER PHO PHUNG 
/* 0E1D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER FO FA 
/* 0E1E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER PHO PHAN 
/* 0E1F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER FO FAN 
/* 0E20 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER PHO SAMPHAO 
/* 0E21 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER MO MA 
/* 0E22 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER YO YAK 
/* 0E23 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER RO RUA 
/* 0E24 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER RU 
/* 0E25 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER LO LING 
/* 0E26 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER LU 
/* 0E27 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER WO WAEN 
/* 0E28 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SO SALA 
/* 0E29 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SO RUSI 
/* 0E2A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SO SUA 
/* 0E2B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER HO HIP 
/* 0E2C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER LO CHULA 
/* 0E2D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER O ANG 
/* 0E2E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER HO NOKHUK 
/* 0E2F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER PAIYANNOI 
/* 0E30 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA A 
/* 0E31 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER MAI HAN-AKAT 
/* 0E32 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA AA 
/* 0E33 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA AM 
/* 0E34 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA I 
/* 0E35 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA II 
/* 0E36 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA UE 
/* 0E37 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA UEE 
/* 0E38 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA U 
/* 0E39 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA UU 
/* 0E3A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER PHINTHU 
/*  e3b */ { 0x0000, 0x0000, 0x0000 },
/*  e3c */ { 0x0000, 0x0000, 0x0000 },
/*  e3d */ { 0x0000, 0x0000, 0x0000 },
/*  e3e */ { 0x0000, 0x0000, 0x0000 },
/* 0E3F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CURRENCY SYMBOL BAHT 
/* 0E40 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA E 
/* 0E41 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA AE 
/* 0E42 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA O 
/* 0E43 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA AI MAIMUAN 
/* 0E44 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER SARA AI MAIMALAI 
/* 0E45 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER LAKKHANGYAO 
/* 0E46 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER MAIYAMOK 
/* 0E47 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER MAITAIKHU 
/* 0E48 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER MAI EK 
/* 0E49 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER MAI THO 
/* 0E4A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER MAI TRI 
/* 0E4B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER MAI CHATTAWA 
/* 0E4C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER THANTHAKHAT 
/* 0E4D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER NIKHAHIT 
/* 0E4E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER YAMAKKAN 
/* 0E4F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER FONGMAN 
/* 0E50 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT ZERO 
/* 0E51 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT ONE 
/* 0E52 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT TWO 
/* 0E53 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT THREE 
/* 0E54 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT FOUR 
/* 0E55 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT FIVE 
/* 0E56 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT SIX 
/* 0E57 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT SEVEN 
/* 0E58 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT EIGHT 
/* 0E59 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI DIGIT NINE 
/* 0E5A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER ANGKHANKHU 
/* 0E5B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THAI CHARACTER KHOMUT 
/*  e5c */ { 0x0000, 0x0000, 0x0000 },
/*  e5d */ { 0x0000, 0x0000, 0x0000 },
/*  e5e */ { 0x0000, 0x0000, 0x0000 },
/*  e5f */ { 0x0000, 0x0000, 0x0000 },
/*  e60 */ { 0x0000, 0x0000, 0x0000 },
/*  e61 */ { 0x0000, 0x0000, 0x0000 },
/*  e62 */ { 0x0000, 0x0000, 0x0000 },
/*  e63 */ { 0x0000, 0x0000, 0x0000 },
/*  e64 */ { 0x0000, 0x0000, 0x0000 },
/*  e65 */ { 0x0000, 0x0000, 0x0000 },
/*  e66 */ { 0x0000, 0x0000, 0x0000 },
/*  e67 */ { 0x0000, 0x0000, 0x0000 },
/*  e68 */ { 0x0000, 0x0000, 0x0000 },
/*  e69 */ { 0x0000, 0x0000, 0x0000 },
/*  e6a */ { 0x0000, 0x0000, 0x0000 },
/*  e6b */ { 0x0000, 0x0000, 0x0000 },
/*  e6c */ { 0x0000, 0x0000, 0x0000 },
/*  e6d */ { 0x0000, 0x0000, 0x0000 },
/*  e6e */ { 0x0000, 0x0000, 0x0000 },
/*  e6f */ { 0x0000, 0x0000, 0x0000 },
/*  e70 */ { 0x0000, 0x0000, 0x0000 },
/*  e71 */ { 0x0000, 0x0000, 0x0000 },
/*  e72 */ { 0x0000, 0x0000, 0x0000 },
/*  e73 */ { 0x0000, 0x0000, 0x0000 },
/*  e74 */ { 0x0000, 0x0000, 0x0000 },
/*  e75 */ { 0x0000, 0x0000, 0x0000 },
/*  e76 */ { 0x0000, 0x0000, 0x0000 },
/*  e77 */ { 0x0000, 0x0000, 0x0000 },
/*  e78 */ { 0x0000, 0x0000, 0x0000 },
/*  e79 */ { 0x0000, 0x0000, 0x0000 },
/*  e7a */ { 0x0000, 0x0000, 0x0000 },
/*  e7b */ { 0x0000, 0x0000, 0x0000 },
/*  e7c */ { 0x0000, 0x0000, 0x0000 },
/*  e7d */ { 0x0000, 0x0000, 0x0000 },
/*  e7e */ { 0x0000, 0x0000, 0x0000 },
/*  e7f */ { 0x0000, 0x0000, 0x0000 },
/*  e80 */ { 0x0000, 0x0000, 0x0000 },
/* 0E81 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER KO 
/* 0E82 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER KHO SUNG 
/*  e83 */ { 0x0000, 0x0000, 0x0000 },
/* 0E84 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER KHO TAM 
/*  e85 */ { 0x0000, 0x0000, 0x0000 },
/*  e86 */ { 0x0000, 0x0000, 0x0000 },
/* 0E87 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER NGO 
/* 0E88 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER CO 
/*  e89 */ { 0x0000, 0x0000, 0x0000 },
/* 0E8A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER SO TAM 
/*  e8b */ { 0x0000, 0x0000, 0x0000 },
/*  e8c */ { 0x0000, 0x0000, 0x0000 },
/* 0E8D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER NYO 
/*  e8e */ { 0x0000, 0x0000, 0x0000 },
/*  e8f */ { 0x0000, 0x0000, 0x0000 },
/*  e90 */ { 0x0000, 0x0000, 0x0000 },
/*  e91 */ { 0x0000, 0x0000, 0x0000 },
/*  e92 */ { 0x0000, 0x0000, 0x0000 },
/*  e93 */ { 0x0000, 0x0000, 0x0000 },
/* 0E94 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER DO 
/* 0E95 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER TO 
/* 0E96 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER THO SUNG 
/* 0E97 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER THO TAM 
/*  e98 */ { 0x0000, 0x0000, 0x0000 },
/* 0E99 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER NO 
/* 0E9A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER BO 
/* 0E9B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER PO 
/* 0E9C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER PHO SUNG 
/* 0E9D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER FO TAM 
/* 0E9E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER PHO TAM 
/* 0E9F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER FO SUNG 
/*  ea0 */ { 0x0000, 0x0000, 0x0000 },
/* 0EA1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER MO 
/* 0EA2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER YO 
/* 0EA3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER LO LING 
/*  ea4 */ { 0x0000, 0x0000, 0x0000 },
/* 0EA5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER LO LOOT 
/*  ea6 */ { 0x0000, 0x0000, 0x0000 },
/* 0EA7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER WO 
/*  ea8 */ { 0x0000, 0x0000, 0x0000 },
/*  ea9 */ { 0x0000, 0x0000, 0x0000 },
/* 0EAA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER SO SUNG 
/* 0EAB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER HO SUNG 
/*  eac */ { 0x0000, 0x0000, 0x0000 },
/* 0EAD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER O 
/* 0EAE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO LETTER HO TAM 
/* 0EAF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO ELLIPSIS 
/* 0EB0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN A 
/* 0EB1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN MAI KAN 
/* 0EB2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN AA 
/* 0EB3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN AM 
/* 0EB4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN I 
/* 0EB5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN II 
/* 0EB6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN Y 
/* 0EB7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN YY 
/* 0EB8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN U 
/* 0EB9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN UU 
/*  eba */ { 0x0000, 0x0000, 0x0000 },
/* 0EBB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN MAI KON 
/* 0EBC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO SEMIVOWEL SIGN LO 
/* 0EBD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO SEMIVOWEL SIGN NYO 
/*  ebe */ { 0x0000, 0x0000, 0x0000 },
/*  ebf */ { 0x0000, 0x0000, 0x0000 },
/* 0EC0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN E 
/* 0EC1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN EI 
/* 0EC2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN O 
/* 0EC3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN AY 
/* 0EC4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO VOWEL SIGN AI 
/*  ec5 */ { 0x0000, 0x0000, 0x0000 },
/* 0EC6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO KO LA 
/*  ec7 */ { 0x0000, 0x0000, 0x0000 },
/* 0EC8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO TONE MAI EK 
/* 0EC9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO TONE MAI THO 
/* 0ECA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO TONE MAI TI 
/* 0ECB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO TONE MAI CATAWA 
/* 0ECC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO CANCELLATION MARK 
/* 0ECD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO NIGGAHITA 
/*  ece */ { 0x0000, 0x0000, 0x0000 },
/*  ecf */ { 0x0000, 0x0000, 0x0000 },
/* 0ED0 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT ZERO 
/* 0ED1 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT ONE 
/* 0ED2 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT TWO 
/* 0ED3 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT THREE 
/* 0ED4 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT FOUR 
/* 0ED5 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT FIVE 
/* 0ED6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT SIX 
/* 0ED7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT SEVEN 
/* 0ED8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT EIGHT 
/* 0ED9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO DIGIT NINE 
/*  eda */ { 0x0000, 0x0000, 0x0000 },
/*  edb */ { 0x0000, 0x0000, 0x0000 },
/* 0EDC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO HO NO 
/* 0EDD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LAO HO MO 
/*  ede */ { 0x0000, 0x0000, 0x0000 },
/*  edf */ { 0x0000, 0x0000, 0x0000 },
/*  ee0 */ { 0x0000, 0x0000, 0x0000 },
/*  ee1 */ { 0x0000, 0x0000, 0x0000 },
/*  ee2 */ { 0x0000, 0x0000, 0x0000 },
/*  ee3 */ { 0x0000, 0x0000, 0x0000 },
/*  ee4 */ { 0x0000, 0x0000, 0x0000 },
/*  ee5 */ { 0x0000, 0x0000, 0x0000 },
/*  ee6 */ { 0x0000, 0x0000, 0x0000 },
/*  ee7 */ { 0x0000, 0x0000, 0x0000 },
/*  ee8 */ { 0x0000, 0x0000, 0x0000 },
/*  ee9 */ { 0x0000, 0x0000, 0x0000 },
/*  eea */ { 0x0000, 0x0000, 0x0000 },
/*  eeb */ { 0x0000, 0x0000, 0x0000 },
/*  eec */ { 0x0000, 0x0000, 0x0000 },
/*  eed */ { 0x0000, 0x0000, 0x0000 },
/*  eee */ { 0x0000, 0x0000, 0x0000 },
/*  eef */ { 0x0000, 0x0000, 0x0000 },
/*  ef0 */ { 0x0000, 0x0000, 0x0000 },
/*  ef1 */ { 0x0000, 0x0000, 0x0000 },
/*  ef2 */ { 0x0000, 0x0000, 0x0000 },
/*  ef3 */ { 0x0000, 0x0000, 0x0000 },
/*  ef4 */ { 0x0000, 0x0000, 0x0000 },
/*  ef5 */ { 0x0000, 0x0000, 0x0000 },
/*  ef6 */ { 0x0000, 0x0000, 0x0000 },
/*  ef7 */ { 0x0000, 0x0000, 0x0000 },
/*  ef8 */ { 0x0000, 0x0000, 0x0000 },
/*  ef9 */ { 0x0000, 0x0000, 0x0000 },
/*  efa */ { 0x0000, 0x0000, 0x0000 },
/*  efb */ { 0x0000, 0x0000, 0x0000 },
/*  efc */ { 0x0000, 0x0000, 0x0000 },
/*  efd */ { 0x0000, 0x0000, 0x0000 },
/*  efe */ { 0x0000, 0x0000, 0x0000 },
/*  eff */ { 0x0000, 0x0000, 0x0000 },
/* 0F00 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYLLABLE OM 
/* 0F01 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK GTER YIG MGO TRUNCATED A 
/* 0F02 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK GTER YIG MGO -UM RNAM BCAD MA 
/* 0F03 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK GTER YIG MGO -UM GTER TSHEG MA 
/* 0F04 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK INITIAL YIG MGO MDUN MA 
/* 0F05 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK CLOSING YIG MGO SGAB MA 
/* 0F06 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK CARET YIG MGO PHUR SHAD MA 
/* 0F07 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK YIG MGO TSHEG SHAD MA 
/* 0F08 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK SBRUL SHAD 
/* 0F09 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK BSKUR YIG MGO 
/* 0F0A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK BKA- SHOG YIG MGO 
/* 0F0B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK INTERSYLLABIC TSHEG 
/* 0F0C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK DELIMITER TSHEG BSTAR 
/* 0F0D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK SHAD 
/* 0F0E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK NYIS SHAD 
/* 0F0F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK TSHEG SHAD 
/* 0F10 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK NYIS TSHEG SHAD 
/* 0F11 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK RIN CHEN SPUNGS SHAD 
/* 0F12 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK RGYA GRAM SHAD 
/* 0F13 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK CARET -DZUD RTAGS ME LONG CAN 
/* 0F14 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK GTER TSHEG 
/* 0F15 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LOGOTYPE SIGN CHAD RTAGS 
/* 0F16 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LOGOTYPE SIGN LHAG RTAGS 
/* 0F17 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN ASTROLOGICAL SIGN SGRA GCAN -CHAR RTAGS 
/* 0F18 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN ASTROLOGICAL SIGN -KHYUD PA 
/* 0F19 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN ASTROLOGICAL SIGN SDONG TSHUGS 
/* 0F1A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RDEL DKAR GCIG 
/* 0F1B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RDEL DKAR GNYIS 
/* 0F1C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RDEL DKAR GSUM 
/* 0F1D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RDEL NAG GCIG 
/* 0F1E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RDEL NAG GNYIS 
/* 0F1F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RDEL DKAR RDEL NAG 
/* 0F20 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT ZERO 
/* 0F21 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT ONE 
/* 0F22 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT TWO 
/* 0F23 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT THREE 
/* 0F24 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT FOUR 
/* 0F25 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT FIVE 
/* 0F26 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT SIX 
/* 0F27 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT SEVEN 
/* 0F28 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT EIGHT 
/* 0F29 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT NINE 
/* 0F2A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF ONE 
/* 0F2B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF TWO 
/* 0F2C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF THREE 
/* 0F2D */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF FOUR 
/* 0F2E */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF FIVE 
/* 0F2F */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF SIX 
/* 0F30 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF SEVEN 
/* 0F31 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF EIGHT 
/* 0F32 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF NINE 
/* 0F33 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN DIGIT HALF ZERO 
/* 0F34 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK BSDUS RTAGS 
/* 0F35 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK NGAS BZUNG NYI ZLA 
/* 0F36 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK CARET -DZUD RTAGS BZHI MIG CAN 
/* 0F37 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK NGAS BZUNG SGOR RTAGS 
/* 0F38 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK CHE MGO 
/* 0F39 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK TSA -PHRU 
/* 0F3A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK GUG RTAGS GYON 
/* 0F3B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK GUG RTAGS GYAS 
/* 0F3C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK ANG KHANG GYON 
/* 0F3D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK ANG KHANG GYAS 
/* 0F3E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN YAR TSHES 
/* 0F3F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN MAR TSHES 
/* 0F40 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER KA 
/* 0F41 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER KHA 
/* 0F42 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER GA 
/* 0F43 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0F42,0x0FB7,0x0000,0x0000 }, // TIBETAN LETTER GHA 
/* 0F44 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER NGA 
/* 0F45 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER CA 
/* 0F46 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER CHA 
/* 0F47 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER JA 
/*  f48 */ { 0x0000, 0x0000, 0x0000 },
/* 0F49 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER NYA 
/* 0F4A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER TTA 
/* 0F4B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER TTHA 
/* 0F4C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER DDA 
/* 0F4D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0F4C,0x0FB7,0x0000,0x0000 }, // TIBETAN LETTER DDHA 
/* 0F4E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER NNA 
/* 0F4F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER TA 
/* 0F50 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER THA 
/* 0F51 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER DA 
/* 0F52 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0F51,0x0FB7,0x0000,0x0000 }, // TIBETAN LETTER DHA 
/* 0F53 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER NA 
/* 0F54 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER PA 
/* 0F55 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER PHA 
/* 0F56 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER BA 
/* 0F57 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0F56,0x0FB7,0x0000,0x0000 }, // TIBETAN LETTER BHA 
/* 0F58 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER MA 
/* 0F59 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER TSA 
/* 0F5A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER TSHA 
/* 0F5B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER DZA 
/* 0F5C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0F5B,0x0FB7,0x0000,0x0000 }, // TIBETAN LETTER DZHA 
/* 0F5D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER WA 
/* 0F5E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER ZHA 
/* 0F5F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER ZA 
/* 0F60 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER -A 
/* 0F61 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER YA 
/* 0F62 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER RA 
/* 0F63 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER LA 
/* 0F64 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER SHA 
/* 0F65 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER SSA 
/* 0F66 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER SA 
/* 0F67 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER HA 
/* 0F68 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER A 
/* 0F69 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0F40,0x0FB5,0x0000,0x0000 }, // TIBETAN LETTER KSSA 
/* 0F6A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN LETTER FIXED-FORM RA 
/*  f6b */ { 0x0000, 0x0000, 0x0000 },
/*  f6c */ { 0x0000, 0x0000, 0x0000 },
/*  f6d */ { 0x0000, 0x0000, 0x0000 },
/*  f6e */ { 0x0000, 0x0000, 0x0000 },
/*  f6f */ { 0x0000, 0x0000, 0x0000 },
/*  f70 */ { 0x0000, 0x0000, 0x0000 },
/* 0F71 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN AA 
/* 0F72 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN I 
/* 0F73 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0F71,0x0F72,0x0000,0x0000 }, // TIBETAN VOWEL SIGN II 
/* 0F74 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN U 
/* 0F75 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0F71,0x0F74,0x0000,0x0000 }, // TIBETAN VOWEL SIGN UU 
/* 0F76 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0FB2,0x0F80,0x0000,0x0000 }, // TIBETAN VOWEL SIGN VOCALIC R 
/* 0F77 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN VOCALIC RR 
/* 0F78 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0FB3,0x0F80,0x0000,0x0000 }, // TIBETAN VOWEL SIGN VOCALIC L 
/* 0F79 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN VOCALIC LL 
/* 0F7A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN E 
/* 0F7B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN EE 
/* 0F7C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN O 
/* 0F7D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN OO 
/* 0F7E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RJES SU NGA RO 
/* 0F7F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RNAM BCAD 
/* 0F80 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN VOWEL SIGN REVERSED I 
/* 0F81 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0F71,0x0F80,0x0000,0x0000 }, // TIBETAN VOWEL SIGN REVERSED II 
/* 0F82 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN NYI ZLA NAA DA 
/* 0F83 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN SNA LDAN 
/* 0F84 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK HALANTA 
/* 0F85 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK PALUTA 
/* 0F86 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN LCI RTAGS 
/* 0F87 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN YANG RTAGS 
/* 0F88 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN LCE TSA CAN 
/* 0F89 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN MCHU CAN 
/* 0F8A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN GRU CAN RGYINGS 
/* 0F8B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN GRU MED RGYINGS 
/*  f8c */ { 0x0000, 0x0000, 0x0000 },
/*  f8d */ { 0x0000, 0x0000, 0x0000 },
/*  f8e */ { 0x0000, 0x0000, 0x0000 },
/*  f8f */ { 0x0000, 0x0000, 0x0000 },
/* 0F90 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER KA 
/* 0F91 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER KHA 
/* 0F92 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER GA 
/* 0F93 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0F92,0x0FB7,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER GHA 
/* 0F94 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER NGA 
/* 0F95 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER CA 
/* 0F96 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER CHA 
/* 0F97 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER JA 
/*  f98 */ { 0x0000, 0x0000, 0x0000 },
/* 0F99 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER NYA 
/* 0F9A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER TTA 
/* 0F9B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER TTHA 
/* 0F9C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER DDA 
/* 0F9D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0F9C,0x0FB7,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER DDHA 
/* 0F9E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER NNA 
/* 0F9F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER TA 
/* 0FA0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER THA 
/* 0FA1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER DA 
/* 0FA2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0FA1,0x0FB7,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER DHA 
/* 0FA3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER NA 
/* 0FA4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER PA 
/* 0FA5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER PHA 
/* 0FA6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER BA 
/* 0FA7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0FA6,0x0FB7,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER BHA 
/* 0FA8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER MA 
/* 0FA9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER TSA 
/* 0FAA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER TSHA 
/* 0FAB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER DZA 
/* 0FAC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0FAB,0x0FB7,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER DZHA 
/* 0FAD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER WA 
/* 0FAE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER ZHA 
/* 0FAF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER ZA 
/* 0FB0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER -A 
/* 0FB1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER YA 
/* 0FB2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER RA 
/* 0FB3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER LA 
/* 0FB4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER SHA 
/* 0FB5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER SSA 
/* 0FB6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER SA 
/* 0FB7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER HA 
/* 0FB8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER A 
/* 0FB9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0F90,0x0FB5,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER KSSA 
/* 0FBA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER FIXED-FORM WA 
/* 0FBB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER FIXED-FORM YA 
/* 0FBC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SUBJOINED LETTER FIXED-FORM RA 
/*  fbd */ { 0x0000, 0x0000, 0x0000 },
/* 0FBE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN KU RU KHA 
/* 0FBF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN KU RU KHA BZHI MIG CAN 
/* 0FC0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN CANTILLATION SIGN HEAVY BEAT 
/* 0FC1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN CANTILLATION SIGN LIGHT BEAT 
/* 0FC2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN CANTILLATION SIGN CANG TE-U 
/* 0FC3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN CANTILLATION SIGN SBUB -CHAL 
/* 0FC4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL DRIL BU 
/* 0FC5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL RDO RJE 
/* 0FC6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL PADMA GDAN 
/* 0FC7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL RDO RJE RGYA GRAM 
/* 0FC8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL PHUR PA 
/* 0FC9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL NOR BU 
/* 0FCA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL NOR BU NYIS -KHYIL 
/* 0FCB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL NOR BU GSUM -KHYIL 
/* 0FCC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SYMBOL NOR BU BZHI -KHYIL 
/*  fcd */ { 0x0000, 0x0000, 0x0000 },
/*  fce */ { 0x0000, 0x0000, 0x0000 },
/* 0FCF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN SIGN RDEL NAG GSUM 
/* 0FD0 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK BSKA- SHOG GI MGO RGYAN 
/* 0FD1 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIBETAN MARK MNYAM YIG GI MGO RGYAN 
/*  fd2 */ { 0x0000, 0x0000, 0x0000 },
/*  fd3 */ { 0x0000, 0x0000, 0x0000 },
/*  fd4 */ { 0x0000, 0x0000, 0x0000 },
/*  fd5 */ { 0x0000, 0x0000, 0x0000 },
/*  fd6 */ { 0x0000, 0x0000, 0x0000 },
/*  fd7 */ { 0x0000, 0x0000, 0x0000 },
/*  fd8 */ { 0x0000, 0x0000, 0x0000 },
/*  fd9 */ { 0x0000, 0x0000, 0x0000 },
/*  fda */ { 0x0000, 0x0000, 0x0000 },
/*  fdb */ { 0x0000, 0x0000, 0x0000 },
/*  fdc */ { 0x0000, 0x0000, 0x0000 },
/*  fdd */ { 0x0000, 0x0000, 0x0000 },
/*  fde */ { 0x0000, 0x0000, 0x0000 },
/*  fdf */ { 0x0000, 0x0000, 0x0000 },
/*  fe0 */ { 0x0000, 0x0000, 0x0000 },
/*  fe1 */ { 0x0000, 0x0000, 0x0000 },
/*  fe2 */ { 0x0000, 0x0000, 0x0000 },
/*  fe3 */ { 0x0000, 0x0000, 0x0000 },
/*  fe4 */ { 0x0000, 0x0000, 0x0000 },
/*  fe5 */ { 0x0000, 0x0000, 0x0000 },
/*  fe6 */ { 0x0000, 0x0000, 0x0000 },
/*  fe7 */ { 0x0000, 0x0000, 0x0000 },
/*  fe8 */ { 0x0000, 0x0000, 0x0000 },
/*  fe9 */ { 0x0000, 0x0000, 0x0000 },
/*  fea */ { 0x0000, 0x0000, 0x0000 },
/*  feb */ { 0x0000, 0x0000, 0x0000 },
/*  fec */ { 0x0000, 0x0000, 0x0000 },
/*  fed */ { 0x0000, 0x0000, 0x0000 },
/*  fee */ { 0x0000, 0x0000, 0x0000 },
/*  fef */ { 0x0000, 0x0000, 0x0000 },
/*  ff0 */ { 0x0000, 0x0000, 0x0000 },
/*  ff1 */ { 0x0000, 0x0000, 0x0000 },
/*  ff2 */ { 0x0000, 0x0000, 0x0000 },
/*  ff3 */ { 0x0000, 0x0000, 0x0000 },
/*  ff4 */ { 0x0000, 0x0000, 0x0000 },
/*  ff5 */ { 0x0000, 0x0000, 0x0000 },
/*  ff6 */ { 0x0000, 0x0000, 0x0000 },
/*  ff7 */ { 0x0000, 0x0000, 0x0000 },
/*  ff8 */ { 0x0000, 0x0000, 0x0000 },
/*  ff9 */ { 0x0000, 0x0000, 0x0000 },
/*  ffa */ { 0x0000, 0x0000, 0x0000 },
/*  ffb */ { 0x0000, 0x0000, 0x0000 },
/*  ffc */ { 0x0000, 0x0000, 0x0000 },
/*  ffd */ { 0x0000, 0x0000, 0x0000 },
/*  ffe */ { 0x0000, 0x0000, 0x0000 },
/*  fff */ { 0x0000, 0x0000, 0x0000 },
/* 1000 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER KA 
/* 1001 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER KHA 
/* 1002 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER GA 
/* 1003 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER GHA 
/* 1004 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER NGA 
/* 1005 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER CA 
/* 1006 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER CHA 
/* 1007 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER JA 
/* 1008 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER JHA 
/* 1009 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER NYA 
/* 100A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER NNYA 
/* 100B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER TTA 
/* 100C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER TTHA 
/* 100D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER DDA 
/* 100E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER DDHA 
/* 100F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER NNA 
/* 1010 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER TA 
/* 1011 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER THA 
/* 1012 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER DA 
/* 1013 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER DHA 
/* 1014 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER NA 
/* 1015 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER PA 
/* 1016 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER PHA 
/* 1017 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER BA 
/* 1018 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER BHA 
/* 1019 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER MA 
/* 101A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER YA 
/* 101B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER RA 
/* 101C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER LA 
/* 101D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER WA 
/* 101E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER SA 
/* 101F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER HA 
/* 1020 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER LLA 
/* 1021 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER A 
/* 1022 */ { 0x0000, 0x0000, 0x0000 },
/* 1023 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER I 
/* 1024 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER II 
/* 1025 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER U 
/* 1026 */ { lem::CP_Char_Flags::Char, 0x0000, 0x1025,0x102E,0x0000,0x0000 }, // MYANMAR LETTER UU 
/* 1027 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER E 
/* 1028 */ { 0x0000, 0x0000, 0x0000 },
/* 1029 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER O 
/* 102A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER AU 
/* 102b */ { 0x0000, 0x0000, 0x0000 },
/* 102C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN AA 
/* 102D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN I 
/* 102E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN II 
/* 102F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN U 
/* 1030 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN UU 
/* 1031 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN E 
/* 1032 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN AI 
/* 1033 */ { 0x0000, 0x0000, 0x0000 },
/* 1034 */ { 0x0000, 0x0000, 0x0000 },
/* 1035 */ { 0x0000, 0x0000, 0x0000 },
/* 1036 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SIGN ANUSVARA 
/* 1037 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SIGN DOT BELOW 
/* 1038 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SIGN VISARGA 
/* 1039 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SIGN VIRAMA 
/* 103a */ { 0x0000, 0x0000, 0x0000 },
/* 103b */ { 0x0000, 0x0000, 0x0000 },
/* 103c */ { 0x0000, 0x0000, 0x0000 },
/* 103d */ { 0x0000, 0x0000, 0x0000 },
/* 103e */ { 0x0000, 0x0000, 0x0000 },
/* 103f */ { 0x0000, 0x0000, 0x0000 },
/* 1040 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT ZERO 
/* 1041 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT ONE 
/* 1042 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT TWO 
/* 1043 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT THREE 
/* 1044 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT FOUR 
/* 1045 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT FIVE 
/* 1046 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT SIX 
/* 1047 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT SEVEN 
/* 1048 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT EIGHT 
/* 1049 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR DIGIT NINE 
/* 104A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SIGN LITTLE SECTION 
/* 104B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SIGN SECTION 
/* 104C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SYMBOL LOCATIVE 
/* 104D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SYMBOL COMPLETED 
/* 104E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SYMBOL AFOREMENTIONED 
/* 104F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR SYMBOL GENITIVE 
/* 1050 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER SHA 
/* 1051 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER SSA 
/* 1052 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER VOCALIC R 
/* 1053 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER VOCALIC RR 
/* 1054 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER VOCALIC L 
/* 1055 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR LETTER VOCALIC LL 
/* 1056 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN VOCALIC R 
/* 1057 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN VOCALIC RR 
/* 1058 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN VOCALIC L 
/* 1059 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MYANMAR VOWEL SIGN VOCALIC LL 
/* 105a */ { 0x0000, 0x0000, 0x0000 },
/* 105b */ { 0x0000, 0x0000, 0x0000 },
/* 105c */ { 0x0000, 0x0000, 0x0000 },
/* 105d */ { 0x0000, 0x0000, 0x0000 },
/* 105e */ { 0x0000, 0x0000, 0x0000 },
/* 105f */ { 0x0000, 0x0000, 0x0000 },
/* 1060 */ { 0x0000, 0x0000, 0x0000 },
/* 1061 */ { 0x0000, 0x0000, 0x0000 },
/* 1062 */ { 0x0000, 0x0000, 0x0000 },
/* 1063 */ { 0x0000, 0x0000, 0x0000 },
/* 1064 */ { 0x0000, 0x0000, 0x0000 },
/* 1065 */ { 0x0000, 0x0000, 0x0000 },
/* 1066 */ { 0x0000, 0x0000, 0x0000 },
/* 1067 */ { 0x0000, 0x0000, 0x0000 },
/* 1068 */ { 0x0000, 0x0000, 0x0000 },
/* 1069 */ { 0x0000, 0x0000, 0x0000 },
/* 106a */ { 0x0000, 0x0000, 0x0000 },
/* 106b */ { 0x0000, 0x0000, 0x0000 },
/* 106c */ { 0x0000, 0x0000, 0x0000 },
/* 106d */ { 0x0000, 0x0000, 0x0000 },
/* 106e */ { 0x0000, 0x0000, 0x0000 },
/* 106f */ { 0x0000, 0x0000, 0x0000 },
/* 1070 */ { 0x0000, 0x0000, 0x0000 },
/* 1071 */ { 0x0000, 0x0000, 0x0000 },
/* 1072 */ { 0x0000, 0x0000, 0x0000 },
/* 1073 */ { 0x0000, 0x0000, 0x0000 },
/* 1074 */ { 0x0000, 0x0000, 0x0000 },
/* 1075 */ { 0x0000, 0x0000, 0x0000 },
/* 1076 */ { 0x0000, 0x0000, 0x0000 },
/* 1077 */ { 0x0000, 0x0000, 0x0000 },
/* 1078 */ { 0x0000, 0x0000, 0x0000 },
/* 1079 */ { 0x0000, 0x0000, 0x0000 },
/* 107a */ { 0x0000, 0x0000, 0x0000 },
/* 107b */ { 0x0000, 0x0000, 0x0000 },
/* 107c */ { 0x0000, 0x0000, 0x0000 },
/* 107d */ { 0x0000, 0x0000, 0x0000 },
/* 107e */ { 0x0000, 0x0000, 0x0000 },
/* 107f */ { 0x0000, 0x0000, 0x0000 },
/* 1080 */ { 0x0000, 0x0000, 0x0000 },
/* 1081 */ { 0x0000, 0x0000, 0x0000 },
/* 1082 */ { 0x0000, 0x0000, 0x0000 },
/* 1083 */ { 0x0000, 0x0000, 0x0000 },
/* 1084 */ { 0x0000, 0x0000, 0x0000 },
/* 1085 */ { 0x0000, 0x0000, 0x0000 },
/* 1086 */ { 0x0000, 0x0000, 0x0000 },
/* 1087 */ { 0x0000, 0x0000, 0x0000 },
/* 1088 */ { 0x0000, 0x0000, 0x0000 },
/* 1089 */ { 0x0000, 0x0000, 0x0000 },
/* 108a */ { 0x0000, 0x0000, 0x0000 },
/* 108b */ { 0x0000, 0x0000, 0x0000 },
/* 108c */ { 0x0000, 0x0000, 0x0000 },
/* 108d */ { 0x0000, 0x0000, 0x0000 },
/* 108e */ { 0x0000, 0x0000, 0x0000 },
/* 108f */ { 0x0000, 0x0000, 0x0000 },
/* 1090 */ { 0x0000, 0x0000, 0x0000 },
/* 1091 */ { 0x0000, 0x0000, 0x0000 },
/* 1092 */ { 0x0000, 0x0000, 0x0000 },
/* 1093 */ { 0x0000, 0x0000, 0x0000 },
/* 1094 */ { 0x0000, 0x0000, 0x0000 },
/* 1095 */ { 0x0000, 0x0000, 0x0000 },
/* 1096 */ { 0x0000, 0x0000, 0x0000 },
/* 1097 */ { 0x0000, 0x0000, 0x0000 },
/* 1098 */ { 0x0000, 0x0000, 0x0000 },
/* 1099 */ { 0x0000, 0x0000, 0x0000 },
/* 109a */ { 0x0000, 0x0000, 0x0000 },
/* 109b */ { 0x0000, 0x0000, 0x0000 },
/* 109c */ { 0x0000, 0x0000, 0x0000 },
/* 109d */ { 0x0000, 0x0000, 0x0000 },
/* 109e */ { 0x0000, 0x0000, 0x0000 },
/* 109f */ { 0x0000, 0x0000, 0x0000 },
/* 10A0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D00, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER AN 
/* 10A1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D01, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER BAN 
/* 10A2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D02, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER GAN 
/* 10A3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D03, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER DON 
/* 10A4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D04, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER EN 
/* 10A5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D05, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER VIN 
/* 10A6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D06, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER ZEN 
/* 10A7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D07, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER TAN 
/* 10A8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D08, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER IN 
/* 10A9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D09, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER KAN 
/* 10AA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D0A, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER LAS 
/* 10AB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D0B, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER MAN 
/* 10AC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D0C, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER NAR 
/* 10AD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D0D, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER ON 
/* 10AE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D0E, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER PAR 
/* 10AF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D0F, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER ZHAR 
/* 10B0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D10, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER RAE 
/* 10B1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D11, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER SAN 
/* 10B2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D12, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER TAR 
/* 10B3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D13, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER UN 
/* 10B4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D14, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER PHAR 
/* 10B5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D15, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER KHAR 
/* 10B6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D16, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER GHAN 
/* 10B7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D17, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER QAR 
/* 10B8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D18, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER SHIN 
/* 10B9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D19, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER CHIN 
/* 10BA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D1A, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER CAN 
/* 10BB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D1B, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER JIL 
/* 10BC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D1C, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER CIL 
/* 10BD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D1D, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER CHAR 
/* 10BE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D1E, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER XAN 
/* 10BF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D1F, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER JHAN 
/* 10C0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D20, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER HAE 
/* 10C1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D21, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER HE 
/* 10C2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D22, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER HIE 
/* 10C3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D23, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER WE 
/* 10C4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D24, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER HAR 
/* 10C5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x2D25, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN CAPITAL LETTER HOE 
/* 10c6 */ { 0x0000, 0x0000, 0x0000 },
/* 10c7 */ { 0x0000, 0x0000, 0x0000 },
/* 10c8 */ { 0x0000, 0x0000, 0x0000 },
/* 10c9 */ { 0x0000, 0x0000, 0x0000 },
/* 10ca */ { 0x0000, 0x0000, 0x0000 },
/* 10cb */ { 0x0000, 0x0000, 0x0000 },
/* 10cc */ { 0x0000, 0x0000, 0x0000 },
/* 10cd */ { 0x0000, 0x0000, 0x0000 },
/* 10ce */ { 0x0000, 0x0000, 0x0000 },
/* 10cf */ { 0x0000, 0x0000, 0x0000 },
/* 10D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER AN 
/* 10D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER BAN 
/* 10D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER GAN 
/* 10D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER DON 
/* 10D4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER EN 
/* 10D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER VIN 
/* 10D6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER ZEN 
/* 10D7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER TAN 
/* 10D8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER IN 
/* 10D9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER KAN 
/* 10DA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER LAS 
/* 10DB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER MAN 
/* 10DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER NAR 
/* 10DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER ON 
/* 10DE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER PAR 
/* 10DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER ZHAR 
/* 10E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER RAE 
/* 10E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER SAN 
/* 10E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER TAR 
/* 10E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER UN 
/* 10E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER PHAR 
/* 10E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER KHAR 
/* 10E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER GHAN 
/* 10E7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER QAR 
/* 10E8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER SHIN 
/* 10E9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER CHIN 
/* 10EA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER CAN 
/* 10EB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER JIL 
/* 10EC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER CIL 
/* 10ED */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER CHAR 
/* 10EE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER XAN 
/* 10EF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER JHAN 
/* 10F0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER HAE 
/* 10F1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER HE 
/* 10F2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER HIE 
/* 10F3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER WE 
/* 10F4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER HAR 
/* 10F5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER HOE 
/* 10F6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER FI 
/* 10F7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER YN 
/* 10F8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER ELIFI 
/* 10F9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER TURNED GAN 
/* 10FA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN LETTER AIN 
/* 10FB */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GEORGIAN PARAGRAPH SEPARATOR 
/* 10FC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER GEORGIAN NAR 
/* 10fd */ { 0x0000, 0x0000, 0x0000 },
/* 10fe */ { 0x0000, 0x0000, 0x0000 },
/* 10ff */ { 0x0000, 0x0000, 0x0000 },
/* 1100 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG KIYEOK 
/* 1101 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGKIYEOK 
/* 1102 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG NIEUN 
/* 1103 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG TIKEUT 
/* 1104 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGTIKEUT 
/* 1105 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG RIEUL 
/* 1106 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG MIEUM 
/* 1107 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP 
/* 1108 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGPIEUP 
/* 1109 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS 
/* 110A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGSIOS 
/* 110B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG 
/* 110C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CIEUC 
/* 110D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGCIEUC 
/* 110E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CHIEUCH 
/* 110F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG KHIEUKH 
/* 1110 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG THIEUTH 
/* 1111 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PHIEUPH 
/* 1112 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG HIEUH 
/* 1113 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG NIEUN-KIYEOK 
/* 1114 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGNIEUN 
/* 1115 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG NIEUN-TIKEUT 
/* 1116 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG NIEUN-PIEUP 
/* 1117 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG TIKEUT-KIYEOK 
/* 1118 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG RIEUL-NIEUN 
/* 1119 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGRIEUL 
/* 111A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG RIEUL-HIEUH 
/* 111B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG KAPYEOUNRIEUL 
/* 111C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG MIEUM-PIEUP 
/* 111D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG KAPYEOUNMIEUM 
/* 111E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-KIYEOK 
/* 111F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-NIEUN 
/* 1120 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-TIKEUT 
/* 1121 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-SIOS 
/* 1122 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-SIOS-KIYEOK 
/* 1123 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-SIOS-TIKEUT 
/* 1124 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-SIOS-PIEUP 
/* 1125 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-SSANGSIOS 
/* 1126 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-SIOS-CIEUC 
/* 1127 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-CIEUC 
/* 1128 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-CHIEUCH 
/* 1129 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-THIEUTH 
/* 112A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PIEUP-PHIEUPH 
/* 112B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG KAPYEOUNPIEUP 
/* 112C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG KAPYEOUNSSANGPIEUP 
/* 112D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-KIYEOK 
/* 112E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-NIEUN 
/* 112F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-TIKEUT 
/* 1130 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-RIEUL 
/* 1131 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-MIEUM 
/* 1132 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-PIEUP 
/* 1133 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-PIEUP-KIYEOK 
/* 1134 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-SSANGSIOS 
/* 1135 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-IEUNG 
/* 1136 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-CIEUC 
/* 1137 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-CHIEUCH 
/* 1138 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-KHIEUKH 
/* 1139 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-THIEUTH 
/* 113A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-PHIEUPH 
/* 113B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SIOS-HIEUH 
/* 113C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CHITUEUMSIOS 
/* 113D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CHITUEUMSSANGSIOS 
/* 113E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CEONGCHIEUMSIOS 
/* 113F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CEONGCHIEUMSSANGSIOS 
/* 1140 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PANSIOS 
/* 1141 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-KIYEOK 
/* 1142 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-TIKEUT 
/* 1143 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-MIEUM 
/* 1144 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-PIEUP 
/* 1145 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-SIOS 
/* 1146 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-PANSIOS 
/* 1147 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGIEUNG 
/* 1148 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-CIEUC 
/* 1149 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-CHIEUCH 
/* 114A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-THIEUTH 
/* 114B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG IEUNG-PHIEUPH 
/* 114C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG YESIEUNG 
/* 114D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CIEUC-IEUNG 
/* 114E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CHITUEUMCIEUC 
/* 114F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CHITUEUMSSANGCIEUC 
/* 1150 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CEONGCHIEUMCIEUC 
/* 1151 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CEONGCHIEUMSSANGCIEUC 
/* 1152 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CHIEUCH-KHIEUKH 
/* 1153 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CHIEUCH-HIEUH 
/* 1154 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CHITUEUMCHIEUCH 
/* 1155 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG CEONGCHIEUMCHIEUCH 
/* 1156 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG PHIEUPH-PIEUP 
/* 1157 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG KAPYEOUNPHIEUPH 
/* 1158 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG SSANGHIEUH 
/* 1159 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG YEORINHIEUH 
/* 115a */ { 0x0000, 0x0000, 0x0000 },
/* 115b */ { 0x0000, 0x0000, 0x0000 },
/* 115c */ { 0x0000, 0x0000, 0x0000 },
/* 115d */ { 0x0000, 0x0000, 0x0000 },
/* 115e */ { 0x0000, 0x0000, 0x0000 },
/* 115F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL CHOSEONG FILLER 
/* 1160 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG FILLER 
/* 1161 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG A 
/* 1162 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG AE 
/* 1163 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YA 
/* 1164 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YAE 
/* 1165 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG EO 
/* 1166 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG E 
/* 1167 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YEO 
/* 1168 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YE 
/* 1169 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG O 
/* 116A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG WA 
/* 116B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG WAE 
/* 116C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG OE 
/* 116D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YO 
/* 116E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG U 
/* 116F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG WEO 
/* 1170 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG WE 
/* 1171 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG WI 
/* 1172 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YU 
/* 1173 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG EU 
/* 1174 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YI 
/* 1175 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG I 
/* 1176 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG A-O 
/* 1177 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG A-U 
/* 1178 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YA-O 
/* 1179 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YA-YO 
/* 117A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG EO-O 
/* 117B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG EO-U 
/* 117C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG EO-EU 
/* 117D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YEO-O 
/* 117E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YEO-U 
/* 117F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG O-EO 
/* 1180 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG O-E 
/* 1181 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG O-YE 
/* 1182 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG O-O 
/* 1183 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG O-U 
/* 1184 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YO-YA 
/* 1185 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YO-YAE 
/* 1186 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YO-YEO 
/* 1187 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YO-O 
/* 1188 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YO-I 
/* 1189 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG U-A 
/* 118A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG U-AE 
/* 118B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG U-EO-EU 
/* 118C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG U-YE 
/* 118D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG U-U 
/* 118E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YU-A 
/* 118F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YU-EO 
/* 1190 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YU-E 
/* 1191 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YU-YEO 
/* 1192 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YU-YE 
/* 1193 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YU-U 
/* 1194 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YU-I 
/* 1195 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG EU-U 
/* 1196 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG EU-EU 
/* 1197 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG YI-U 
/* 1198 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG I-A 
/* 1199 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG I-YA 
/* 119A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG I-O 
/* 119B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG I-U 
/* 119C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG I-EU 
/* 119D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG I-ARAEA 
/* 119E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG ARAEA 
/* 119F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG ARAEA-EO 
/* 11A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG ARAEA-U 
/* 11A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG ARAEA-I 
/* 11A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JUNGSEONG SSANGARAEA 
/* 11a3 */ { 0x0000, 0x0000, 0x0000 },
/* 11a4 */ { 0x0000, 0x0000, 0x0000 },
/* 11a5 */ { 0x0000, 0x0000, 0x0000 },
/* 11a6 */ { 0x0000, 0x0000, 0x0000 },
/* 11a7 */ { 0x0000, 0x0000, 0x0000 },
/* 11A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG KIYEOK 
/* 11A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SSANGKIYEOK 
/* 11AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG KIYEOK-SIOS 
/* 11AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG NIEUN 
/* 11AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG NIEUN-CIEUC 
/* 11AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG NIEUN-HIEUH 
/* 11AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG TIKEUT 
/* 11AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL 
/* 11B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-KIYEOK 
/* 11B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-MIEUM 
/* 11B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-PIEUP 
/* 11B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-SIOS 
/* 11B4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-THIEUTH 
/* 11B5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-PHIEUPH 
/* 11B6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-HIEUH 
/* 11B7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM 
/* 11B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG PIEUP 
/* 11B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG PIEUP-SIOS 
/* 11BA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SIOS 
/* 11BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SSANGSIOS 
/* 11BC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG IEUNG 
/* 11BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG CIEUC 
/* 11BE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG CHIEUCH 
/* 11BF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG KHIEUKH 
/* 11C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG THIEUTH 
/* 11C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG PHIEUPH 
/* 11C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG HIEUH 
/* 11C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG KIYEOK-RIEUL 
/* 11C4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG KIYEOK-SIOS-KIYEOK 
/* 11C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG NIEUN-KIYEOK 
/* 11C6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG NIEUN-TIKEUT 
/* 11C7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG NIEUN-SIOS 
/* 11C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG NIEUN-PANSIOS 
/* 11C9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG NIEUN-THIEUTH 
/* 11CA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG TIKEUT-KIYEOK 
/* 11CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG TIKEUT-RIEUL 
/* 11CC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-KIYEOK-SIOS 
/* 11CD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-NIEUN 
/* 11CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-TIKEUT 
/* 11CF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-TIKEUT-HIEUH 
/* 11D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SSANGRIEUL 
/* 11D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-MIEUM-KIYEOK 
/* 11D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-MIEUM-SIOS 
/* 11D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-PIEUP-SIOS 
/* 11D4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-PIEUP-HIEUH 
/* 11D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-KAPYEOUNPIEUP 
/* 11D6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-SSANGSIOS 
/* 11D7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-PANSIOS 
/* 11D8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-KHIEUKH 
/* 11D9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG RIEUL-YEORINHIEUH 
/* 11DA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM-KIYEOK 
/* 11DB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM-RIEUL 
/* 11DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM-PIEUP 
/* 11DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM-SIOS 
/* 11DE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM-SSANGSIOS 
/* 11DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM-PANSIOS 
/* 11E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM-CHIEUCH 
/* 11E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG MIEUM-HIEUH 
/* 11E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG KAPYEOUNMIEUM 
/* 11E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG PIEUP-RIEUL 
/* 11E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG PIEUP-PHIEUPH 
/* 11E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG PIEUP-HIEUH 
/* 11E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG KAPYEOUNPIEUP 
/* 11E7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SIOS-KIYEOK 
/* 11E8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SIOS-TIKEUT 
/* 11E9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SIOS-RIEUL 
/* 11EA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SIOS-PIEUP 
/* 11EB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG PANSIOS 
/* 11EC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG IEUNG-KIYEOK 
/* 11ED */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG IEUNG-SSANGKIYEOK 
/* 11EE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG SSANGIEUNG 
/* 11EF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG IEUNG-KHIEUKH 
/* 11F0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG YESIEUNG 
/* 11F1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG YESIEUNG-SIOS 
/* 11F2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG YESIEUNG-PANSIOS 
/* 11F3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG PHIEUPH-PIEUP 
/* 11F4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG KAPYEOUNPHIEUPH 
/* 11F5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG HIEUH-NIEUN 
/* 11F6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG HIEUH-RIEUL 
/* 11F7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG HIEUH-MIEUM 
/* 11F8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG HIEUH-PIEUP 
/* 11F9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANGUL JONGSEONG YEORINHIEUH 
/* 11fa */ { 0x0000, 0x0000, 0x0000 },
/* 11fb */ { 0x0000, 0x0000, 0x0000 },
/* 11fc */ { 0x0000, 0x0000, 0x0000 },
/* 11fd */ { 0x0000, 0x0000, 0x0000 },
/* 11fe */ { 0x0000, 0x0000, 0x0000 },
/* 11ff */ { 0x0000, 0x0000, 0x0000 },
/* 1200 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HA 
/* 1201 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HU 
/* 1202 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HI 
/* 1203 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HAA 
/* 1204 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HEE 
/* 1205 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HE 
/* 1206 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HO 
/* 1207 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HOA 
/* 1208 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE LA 
/* 1209 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE LU 
/* 120A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE LI 
/* 120B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE LAA 
/* 120C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE LEE 
/* 120D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE LE 
/* 120E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE LO 
/* 120F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE LWA 
/* 1210 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HHA 
/* 1211 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HHU 
/* 1212 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HHI 
/* 1213 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HHAA 
/* 1214 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HHEE 
/* 1215 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HHE 
/* 1216 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HHO 
/* 1217 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE HHWA 
/* 1218 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MA 
/* 1219 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MU 
/* 121A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MI 
/* 121B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MAA 
/* 121C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MEE 
/* 121D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ME 
/* 121E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MO 
/* 121F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MWA 
/* 1220 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SZA 
/* 1221 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SZU 
/* 1222 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SZI 
/* 1223 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SZAA 
/* 1224 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SZEE 
/* 1225 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SZE 
/* 1226 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SZO 
/* 1227 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SZWA 
/* 1228 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE RA 
/* 1229 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE RU 
/* 122A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE RI 
/* 122B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE RAA 
/* 122C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE REE 
/* 122D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE RE 
/* 122E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE RO 
/* 122F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE RWA 
/* 1230 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SA 
/* 1231 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SU 
/* 1232 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SI 
/* 1233 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SAA 
/* 1234 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SEE 
/* 1235 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SE 
/* 1236 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SO 
/* 1237 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SWA 
/* 1238 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SHA 
/* 1239 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SHU 
/* 123A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SHI 
/* 123B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SHAA 
/* 123C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SHEE 
/* 123D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SHE 
/* 123E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SHO 
/* 123F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SHWA 
/* 1240 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QA 
/* 1241 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QU 
/* 1242 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QI 
/* 1243 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QAA 
/* 1244 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QEE 
/* 1245 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QE 
/* 1246 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QO 
/* 1247 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QOA 
/* 1248 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QWA 
/* 1249 */ { 0x0000, 0x0000, 0x0000 },
/* 124A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QWI 
/* 124B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QWAA 
/* 124C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QWEE 
/* 124D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QWE 
/* 124e */ { 0x0000, 0x0000, 0x0000 },
/* 124f */ { 0x0000, 0x0000, 0x0000 },
/* 1250 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHA 
/* 1251 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHU 
/* 1252 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHI 
/* 1253 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHAA 
/* 1254 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHEE 
/* 1255 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHE 
/* 1256 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHO 
/* 1257 */ { 0x0000, 0x0000, 0x0000 },
/* 1258 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHWA 
/* 1259 */ { 0x0000, 0x0000, 0x0000 },
/* 125A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHWI 
/* 125B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHWAA 
/* 125C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHWEE 
/* 125D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE QHWE 
/* 125e */ { 0x0000, 0x0000, 0x0000 },
/* 125f */ { 0x0000, 0x0000, 0x0000 },
/* 1260 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BA 
/* 1261 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BU 
/* 1262 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BI 
/* 1263 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BAA 
/* 1264 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BEE 
/* 1265 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BE 
/* 1266 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BO 
/* 1267 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BWA 
/* 1268 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE VA 
/* 1269 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE VU 
/* 126A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE VI 
/* 126B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE VAA 
/* 126C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE VEE 
/* 126D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE VE 
/* 126E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE VO 
/* 126F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE VWA 
/* 1270 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TA 
/* 1271 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TU 
/* 1272 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TI 
/* 1273 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TAA 
/* 1274 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TEE 
/* 1275 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TE 
/* 1276 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TO 
/* 1277 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TWA 
/* 1278 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CA 
/* 1279 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CU 
/* 127A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CI 
/* 127B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CAA 
/* 127C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CEE 
/* 127D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CE 
/* 127E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CO 
/* 127F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CWA 
/* 1280 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XA 
/* 1281 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XU 
/* 1282 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XI 
/* 1283 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XAA 
/* 1284 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XEE 
/* 1285 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XE 
/* 1286 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XO 
/* 1287 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XOA 
/* 1288 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XWA 
/* 1289 */ { 0x0000, 0x0000, 0x0000 },
/* 128A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XWI 
/* 128B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XWAA 
/* 128C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XWEE 
/* 128D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE XWE 
/* 128e */ { 0x0000, 0x0000, 0x0000 },
/* 128f */ { 0x0000, 0x0000, 0x0000 },
/* 1290 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NA 
/* 1291 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NU 
/* 1292 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NI 
/* 1293 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NAA 
/* 1294 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NEE 
/* 1295 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NE 
/* 1296 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NO 
/* 1297 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NWA 
/* 1298 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NYA 
/* 1299 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NYU 
/* 129A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NYI 
/* 129B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NYAA 
/* 129C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NYEE 
/* 129D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NYE 
/* 129E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NYO 
/* 129F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE NYWA 
/* 12A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GLOTTAL A 
/* 12A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GLOTTAL U 
/* 12A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GLOTTAL I 
/* 12A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GLOTTAL AA 
/* 12A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GLOTTAL EE 
/* 12A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GLOTTAL E 
/* 12A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GLOTTAL O 
/* 12A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GLOTTAL WA 
/* 12A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KA 
/* 12A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KU 
/* 12AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KI 
/* 12AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KAA 
/* 12AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KEE 
/* 12AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KE 
/* 12AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KO 
/* 12AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KOA 
/* 12B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KWA 
/* 12b1 */ { 0x0000, 0x0000, 0x0000 },
/* 12B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KWI 
/* 12B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KWAA 
/* 12B4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KWEE 
/* 12B5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KWE 
/* 12b6 */ { 0x0000, 0x0000, 0x0000 },
/* 12b7 */ { 0x0000, 0x0000, 0x0000 },
/* 12B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXA 
/* 12B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXU 
/* 12BA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXI 
/* 12BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXAA 
/* 12BC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXEE 
/* 12BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXE 
/* 12BE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXO 
/* 12bf */ { 0x0000, 0x0000, 0x0000 },
/* 12C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXWA 
/* 12c1 */ { 0x0000, 0x0000, 0x0000 },
/* 12C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXWI 
/* 12C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXWAA 
/* 12C4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXWEE 
/* 12C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE KXWE 
/* 12c6 */ { 0x0000, 0x0000, 0x0000 },
/* 12c7 */ { 0x0000, 0x0000, 0x0000 },
/* 12C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE WA 
/* 12C9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE WU 
/* 12CA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE WI 
/* 12CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE WAA 
/* 12CC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE WEE 
/* 12CD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE WE 
/* 12CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE WO 
/* 12CF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE WOA 
/* 12D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHARYNGEAL A 
/* 12D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHARYNGEAL U 
/* 12D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHARYNGEAL I 
/* 12D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHARYNGEAL AA 
/* 12D4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHARYNGEAL EE 
/* 12D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHARYNGEAL E 
/* 12D6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHARYNGEAL O 
/* 12d7 */ { 0x0000, 0x0000, 0x0000 },
/* 12D8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZA 
/* 12D9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZU 
/* 12DA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZI 
/* 12DB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZAA 
/* 12DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZEE 
/* 12DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZE 
/* 12DE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZO 
/* 12DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZWA 
/* 12E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZHA 
/* 12E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZHU 
/* 12E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZHI 
/* 12E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZHAA 
/* 12E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZHEE 
/* 12E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZHE 
/* 12E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZHO 
/* 12E7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE ZHWA 
/* 12E8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE YA 
/* 12E9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE YU 
/* 12EA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE YI 
/* 12EB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE YAA 
/* 12EC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE YEE 
/* 12ED */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE YE 
/* 12EE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE YO 
/* 12EF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE YOA 
/* 12F0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DA 
/* 12F1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DU 
/* 12F2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DI 
/* 12F3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DAA 
/* 12F4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DEE 
/* 12F5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DE 
/* 12F6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DO 
/* 12F7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DWA 
/* 12F8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DDA 
/* 12F9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DDU 
/* 12FA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DDI 
/* 12FB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DDAA 
/* 12FC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DDEE 
/* 12FD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DDE 
/* 12FE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DDO 
/* 12FF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE DDWA 
/* 1300 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE JA 
/* 1301 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE JU 
/* 1302 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE JI 
/* 1303 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE JAA 
/* 1304 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE JEE 
/* 1305 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE JE 
/* 1306 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE JO 
/* 1307 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE JWA 
/* 1308 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GA 
/* 1309 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GU 
/* 130A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GI 
/* 130B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GAA 
/* 130C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GEE 
/* 130D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GE 
/* 130E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GO 
/* 130F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GOA 
/* 1310 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GWA 
/* 1311 */ { 0x0000, 0x0000, 0x0000 },
/* 1312 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GWI 
/* 1313 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GWAA 
/* 1314 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GWEE 
/* 1315 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GWE 
/* 1316 */ { 0x0000, 0x0000, 0x0000 },
/* 1317 */ { 0x0000, 0x0000, 0x0000 },
/* 1318 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GGA 
/* 1319 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GGU 
/* 131A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GGI 
/* 131B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GGAA 
/* 131C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GGEE 
/* 131D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GGE 
/* 131E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GGO 
/* 131F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE GGWAA 
/* 1320 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE THA 
/* 1321 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE THU 
/* 1322 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE THI 
/* 1323 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE THAA 
/* 1324 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE THEE 
/* 1325 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE THE 
/* 1326 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE THO 
/* 1327 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE THWA 
/* 1328 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CHA 
/* 1329 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CHU 
/* 132A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CHI 
/* 132B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CHAA 
/* 132C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CHEE 
/* 132D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CHE 
/* 132E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CHO 
/* 132F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE CHWA 
/* 1330 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHA 
/* 1331 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHU 
/* 1332 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHI 
/* 1333 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHAA 
/* 1334 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHEE 
/* 1335 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHE 
/* 1336 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHO 
/* 1337 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PHWA 
/* 1338 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TSA 
/* 1339 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TSU 
/* 133A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TSI 
/* 133B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TSAA 
/* 133C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TSEE 
/* 133D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TSE 
/* 133E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TSO 
/* 133F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TSWA 
/* 1340 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TZA 
/* 1341 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TZU 
/* 1342 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TZI 
/* 1343 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TZAA 
/* 1344 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TZEE 
/* 1345 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TZE 
/* 1346 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TZO 
/* 1347 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE TZOA 
/* 1348 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FA 
/* 1349 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FU 
/* 134A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FI 
/* 134B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FAA 
/* 134C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FEE 
/* 134D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FE 
/* 134E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FO 
/* 134F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FWA 
/* 1350 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PA 
/* 1351 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PU 
/* 1352 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PI 
/* 1353 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PAA 
/* 1354 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PEE 
/* 1355 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PE 
/* 1356 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PO 
/* 1357 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PWA 
/* 1358 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE RYA 
/* 1359 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MYA 
/* 135A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FYA 
/* 135b */ { 0x0000, 0x0000, 0x0000 },
/* 135c */ { 0x0000, 0x0000, 0x0000 },
/* 135d */ { 0x0000, 0x0000, 0x0000 },
/* 135e */ { 0x0000, 0x0000, 0x0000 },
/* 135F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC COMBINING GEMINATION MARK 
/* 1360 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SECTION MARK 
/* 1361 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC WORDSPACE 
/* 1362 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC FULL STOP 
/* 1363 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC COMMA 
/* 1364 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SEMICOLON 
/* 1365 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC COLON 
/* 1366 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC PREFACE COLON 
/* 1367 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC QUESTION MARK 
/* 1368 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC PARAGRAPH SEPARATOR 
/* 1369 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT ONE 
/* 136A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT TWO 
/* 136B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT THREE 
/* 136C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT FOUR 
/* 136D */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT FIVE 
/* 136E */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT SIX 
/* 136F */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT SEVEN 
/* 1370 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT EIGHT 
/* 1371 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC DIGIT NINE 
/* 1372 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER TEN 
/* 1373 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER TWENTY 
/* 1374 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER THIRTY 
/* 1375 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER FORTY 
/* 1376 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER FIFTY 
/* 1377 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER SIXTY 
/* 1378 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER SEVENTY 
/* 1379 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER EIGHTY 
/* 137A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER NINETY 
/* 137B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER HUNDRED 
/* 137C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC NUMBER TEN THOUSAND 
/* 137d */ { 0x0000, 0x0000, 0x0000 },
/* 137e */ { 0x0000, 0x0000, 0x0000 },
/* 137f */ { 0x0000, 0x0000, 0x0000 },
/* 1380 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SEBATBEIT MWA 
/* 1381 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MWI 
/* 1382 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MWEE 
/* 1383 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE MWE 
/* 1384 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SEBATBEIT BWA 
/* 1385 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BWI 
/* 1386 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BWEE 
/* 1387 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE BWE 
/* 1388 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SEBATBEIT FWA 
/* 1389 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FWI 
/* 138A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FWEE 
/* 138B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE FWE 
/* 138C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE SEBATBEIT PWA 
/* 138D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PWI 
/* 138E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PWEE 
/* 138F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC SYLLABLE PWE 
/* 1390 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK YIZET 
/* 1391 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK DERET 
/* 1392 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK RIKRIK 
/* 1393 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK SHORT RIKRIK 
/* 1394 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK DIFAT 
/* 1395 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK KENAT 
/* 1396 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK CHIRET 
/* 1397 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK HIDET 
/* 1398 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK DERET-HIDET 
/* 1399 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ETHIOPIC TONAL MARK KURT 
/* 139a */ { 0x0000, 0x0000, 0x0000 },
/* 139b */ { 0x0000, 0x0000, 0x0000 },
/* 139c */ { 0x0000, 0x0000, 0x0000 },
/* 139d */ { 0x0000, 0x0000, 0x0000 },
/* 139e */ { 0x0000, 0x0000, 0x0000 },
/* 139f */ { 0x0000, 0x0000, 0x0000 },
/* 13A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER A 
/* 13A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER E 
/* 13A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER I 
/* 13A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER O 
/* 13A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER U 
/* 13A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER V 
/* 13A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER GA 
/* 13A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER KA 
/* 13A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER GE 
/* 13A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER GI 
/* 13AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER GO 
/* 13AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER GU 
/* 13AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER GV 
/* 13AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER HA 
/* 13AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER HE 
/* 13AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER HI 
/* 13B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER HO 
/* 13B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER HU 
/* 13B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER HV 
/* 13B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER LA 
/* 13B4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER LE 
/* 13B5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER LI 
/* 13B6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER LO 
/* 13B7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER LU 
/* 13B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER LV 
/* 13B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER MA 
/* 13BA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER ME 
/* 13BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER MI 
/* 13BC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER MO 
/* 13BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER MU 
/* 13BE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER NA 
/* 13BF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER HNA 
/* 13C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER NAH 
/* 13C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER NE 
/* 13C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER NI 
/* 13C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER NO 
/* 13C4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER NU 
/* 13C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER NV 
/* 13C6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER QUA 
/* 13C7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER QUE 
/* 13C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER QUI 
/* 13C9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER QUO 
/* 13CA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER QUU 
/* 13CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER QUV 
/* 13CC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER SA 
/* 13CD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER S 
/* 13CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER SE 
/* 13CF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER SI 
/* 13D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER SO 
/* 13D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER SU 
/* 13D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER SV 
/* 13D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER DA 
/* 13D4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TA 
/* 13D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER DE 
/* 13D6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TE 
/* 13D7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER DI 
/* 13D8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TI 
/* 13D9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER DO 
/* 13DA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER DU 
/* 13DB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER DV 
/* 13DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER DLA 
/* 13DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TLA 
/* 13DE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TLE 
/* 13DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TLI 
/* 13E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TLO 
/* 13E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TLU 
/* 13E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TLV 
/* 13E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TSA 
/* 13E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TSE 
/* 13E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TSI 
/* 13E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TSO 
/* 13E7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TSU 
/* 13E8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER TSV 
/* 13E9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER WA 
/* 13EA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER WE 
/* 13EB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER WI 
/* 13EC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER WO 
/* 13ED */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER WU 
/* 13EE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER WV 
/* 13EF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER YA 
/* 13F0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER YE 
/* 13F1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER YI 
/* 13F2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER YO 
/* 13F3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER YU 
/* 13F4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHEROKEE LETTER YV 
/* 13f5 */ { 0x0000, 0x0000, 0x0000 },
/* 13f6 */ { 0x0000, 0x0000, 0x0000 },
/* 13f7 */ { 0x0000, 0x0000, 0x0000 },
/* 13f8 */ { 0x0000, 0x0000, 0x0000 },
/* 13f9 */ { 0x0000, 0x0000, 0x0000 },
/* 13fa */ { 0x0000, 0x0000, 0x0000 },
/* 13fb */ { 0x0000, 0x0000, 0x0000 },
/* 13fc */ { 0x0000, 0x0000, 0x0000 },
/* 13fd */ { 0x0000, 0x0000, 0x0000 },
/* 13fe */ { 0x0000, 0x0000, 0x0000 },
/* 13ff */ { 0x0000, 0x0000, 0x0000 },
/* 1400 */ { 0x0000, 0x0000, 0x0000 },
/* 1401 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS E 
/* 1402 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS AAI 
/* 1403 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS I 
/* 1404 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS II 
/* 1405 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS O 
/* 1406 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS OO 
/* 1407 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE OO 
/* 1408 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER EE 
/* 1409 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER I 
/* 140A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS A 
/* 140B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS AA 
/* 140C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WE 
/* 140D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE WE 
/* 140E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WI 
/* 140F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE WI 
/* 1410 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WII 
/* 1411 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE WII 
/* 1412 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WO 
/* 1413 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE WO 
/* 1414 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WOO 
/* 1415 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE WOO 
/* 1416 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI WOO 
/* 1417 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WA 
/* 1418 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE WA 
/* 1419 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WAA 
/* 141A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE WAA 
/* 141B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI WAA 
/* 141C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS AI 
/* 141D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE W 
/* 141E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS GLOTTAL STOP 
/* 141F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL ACUTE 
/* 1420 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL GRAVE 
/* 1421 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL BOTTOM HALF RING 
/* 1422 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL TOP HALF RING 
/* 1423 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL RIGHT HALF RING 
/* 1424 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL RING 
/* 1425 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL DOUBLE ACUTE 
/* 1426 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL DOUBLE SHORT VERTICAL STROKES 
/* 1427 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL MIDDLE DOT 
/* 1428 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL SHORT HORIZONTAL STROKE 
/* 1429 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL PLUS 
/* 142A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FINAL DOWN TACK 
/* 142B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS EN 
/* 142C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS IN 
/* 142D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS ON 
/* 142E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS AN 
/* 142F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PE 
/* 1430 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PAAI 
/* 1431 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PI 
/* 1432 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PII 
/* 1433 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PO 
/* 1434 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS POO 
/* 1435 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE POO 
/* 1436 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER HEE 
/* 1437 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER HI 
/* 1438 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PA 
/* 1439 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PAA 
/* 143A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PWE 
/* 143B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE PWE 
/* 143C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PWI 
/* 143D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE PWI 
/* 143E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PWII 
/* 143F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE PWII 
/* 1440 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PWO 
/* 1441 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE PWO 
/* 1442 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PWOO 
/* 1443 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE PWOO 
/* 1444 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PWA 
/* 1445 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE PWA 
/* 1446 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS PWAA 
/* 1447 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE PWAA 
/* 1448 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE PWAA 
/* 1449 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS P 
/* 144A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE P 
/* 144B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER H 
/* 144C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TE 
/* 144D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TAAI 
/* 144E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TI 
/* 144F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TII 
/* 1450 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TO 
/* 1451 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TOO 
/* 1452 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE TOO 
/* 1453 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DEE 
/* 1454 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DI 
/* 1455 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TA 
/* 1456 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TAA 
/* 1457 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TWE 
/* 1458 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE TWE 
/* 1459 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TWI 
/* 145A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE TWI 
/* 145B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TWII 
/* 145C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE TWII 
/* 145D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TWO 
/* 145E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE TWO 
/* 145F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TWOO 
/* 1460 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE TWOO 
/* 1461 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TWA 
/* 1462 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE TWA 
/* 1463 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TWAA 
/* 1464 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE TWAA 
/* 1465 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI TWAA 
/* 1466 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS T 
/* 1467 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTE 
/* 1468 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTI 
/* 1469 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTO 
/* 146A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTA 
/* 146B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KE 
/* 146C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KAAI 
/* 146D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KI 
/* 146E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KII 
/* 146F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KO 
/* 1470 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KOO 
/* 1471 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE KOO 
/* 1472 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KA 
/* 1473 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KAA 
/* 1474 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KWE 
/* 1475 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE KWE 
/* 1476 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KWI 
/* 1477 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE KWI 
/* 1478 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KWII 
/* 1479 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE KWII 
/* 147A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KWO 
/* 147B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE KWO 
/* 147C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KWOO 
/* 147D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE KWOO 
/* 147E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KWA 
/* 147F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE KWA 
/* 1480 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KWAA 
/* 1481 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE KWAA 
/* 1482 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI KWAA 
/* 1483 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS K 
/* 1484 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS KW 
/* 1485 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SOUTH-SLAVEY KEH 
/* 1486 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SOUTH-SLAVEY KIH 
/* 1487 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SOUTH-SLAVEY KOH 
/* 1488 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SOUTH-SLAVEY KAH 
/* 1489 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CE 
/* 148A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CAAI 
/* 148B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CI 
/* 148C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CII 
/* 148D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CO 
/* 148E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS COO 
/* 148F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE COO 
/* 1490 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CA 
/* 1491 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CAA 
/* 1492 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CWE 
/* 1493 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE CWE 
/* 1494 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CWI 
/* 1495 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE CWI 
/* 1496 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CWII 
/* 1497 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE CWII 
/* 1498 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CWO 
/* 1499 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE CWO 
/* 149A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CWOO 
/* 149B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE CWOO 
/* 149C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CWA 
/* 149D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE CWA 
/* 149E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CWAA 
/* 149F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE CWAA 
/* 14A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI CWAA 
/* 14A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS C 
/* 14A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI TH 
/* 14A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS ME 
/* 14A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MAAI 
/* 14A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MI 
/* 14A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MII 
/* 14A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MO 
/* 14A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MOO 
/* 14A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE MOO 
/* 14AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MA 
/* 14AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MAA 
/* 14AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MWE 
/* 14AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE MWE 
/* 14AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MWI 
/* 14AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE MWI 
/* 14B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MWII 
/* 14B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE MWII 
/* 14B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MWO 
/* 14B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE MWO 
/* 14B4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MWOO 
/* 14B5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE MWOO 
/* 14B6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MWA 
/* 14B7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE MWA 
/* 14B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MWAA 
/* 14B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE MWAA 
/* 14BA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI MWAA 
/* 14BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS M 
/* 14BC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE M 
/* 14BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MH 
/* 14BE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS ATHAPASCAN M 
/* 14BF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI M 
/* 14C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NE 
/* 14C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NAAI 
/* 14C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NI 
/* 14C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NII 
/* 14C4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NO 
/* 14C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NOO 
/* 14C6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE NOO 
/* 14C7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NA 
/* 14C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NAA 
/* 14C9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NWE 
/* 14CA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE NWE 
/* 14CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NWA 
/* 14CC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE NWA 
/* 14CD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NWAA 
/* 14CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE NWAA 
/* 14CF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI NWAA 
/* 14D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS N 
/* 14D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER NG 
/* 14D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NH 
/* 14D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LE 
/* 14D4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LAAI 
/* 14D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LI 
/* 14D6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LII 
/* 14D7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LO 
/* 14D8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LOO 
/* 14D9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE LOO 
/* 14DA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LA 
/* 14DB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LAA 
/* 14DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LWE 
/* 14DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LWE 
/* 14DE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LWI 
/* 14DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LWI 
/* 14E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LWII 
/* 14E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LWII 
/* 14E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LWO 
/* 14E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LWO 
/* 14E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LWOO 
/* 14E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LWOO 
/* 14E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LWA 
/* 14E7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LWA 
/* 14E8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LWAA 
/* 14E9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LWAA 
/* 14EA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS L 
/* 14EB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE L 
/* 14EC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MEDIAL L 
/* 14ED */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SE 
/* 14EE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAAI 
/* 14EF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SI 
/* 14F0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SII 
/* 14F1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SO 
/* 14F2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SOO 
/* 14F3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE SOO 
/* 14F4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SA 
/* 14F5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAA 
/* 14F6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SWE 
/* 14F7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SWE 
/* 14F8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SWI 
/* 14F9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SWI 
/* 14FA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SWII 
/* 14FB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SWII 
/* 14FC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SWO 
/* 14FD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SWO 
/* 14FE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SWOO 
/* 14FF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SWOO 
/* 1500 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SWA 
/* 1501 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SWA 
/* 1502 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SWAA 
/* 1503 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SWAA 
/* 1504 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI SWAA 
/* 1505 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS S 
/* 1506 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS ATHAPASCAN S 
/* 1507 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SW 
/* 1508 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT S 
/* 1509 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MOOSE-CREE SK 
/* 150A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI SKW 
/* 150B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI S-W 
/* 150C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI SPWA 
/* 150D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI STWA 
/* 150E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI SKWA 
/* 150F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI SCWA 
/* 1510 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHE 
/* 1511 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHI 
/* 1512 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHII 
/* 1513 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHO 
/* 1514 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHOO 
/* 1515 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHA 
/* 1516 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHAA 
/* 1517 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHWE 
/* 1518 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SHWE 
/* 1519 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHWI 
/* 151A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SHWI 
/* 151B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHWII 
/* 151C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SHWII 
/* 151D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHWO 
/* 151E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SHWO 
/* 151F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHWOO 
/* 1520 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SHWOO 
/* 1521 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHWA 
/* 1522 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SHWA 
/* 1523 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SHWAA 
/* 1524 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE SHWAA 
/* 1525 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SH 
/* 1526 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YE 
/* 1527 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YAAI 
/* 1528 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YI 
/* 1529 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YII 
/* 152A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YO 
/* 152B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YOO 
/* 152C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y-CREE YOO 
/* 152D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YA 
/* 152E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YAA 
/* 152F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YWE 
/* 1530 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE YWE 
/* 1531 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YWI 
/* 1532 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE YWI 
/* 1533 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YWII 
/* 1534 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE YWII 
/* 1535 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YWO 
/* 1536 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE YWO 
/* 1537 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YWOO 
/* 1538 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE YWOO 
/* 1539 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YWA 
/* 153A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE YWA 
/* 153B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS YWAA 
/* 153C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE YWAA 
/* 153D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NASKAPI YWAA 
/* 153E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Y 
/* 153F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BIBLE-CREE Y 
/* 1540 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE Y 
/* 1541 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI YI 
/* 1542 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS RE 
/* 1543 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS R-CREE RE 
/* 1544 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LE 
/* 1545 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS RAAI 
/* 1546 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS RI 
/* 1547 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS RII 
/* 1548 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS RO 
/* 1549 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS ROO 
/* 154A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LO 
/* 154B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS RA 
/* 154C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS RAA 
/* 154D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE LA 
/* 154E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS RWAA 
/* 154F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE RWAA 
/* 1550 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS R 
/* 1551 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE R 
/* 1552 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS MEDIAL R 
/* 1553 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FE 
/* 1554 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FAAI 
/* 1555 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FI 
/* 1556 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FII 
/* 1557 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FO 
/* 1558 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FOO 
/* 1559 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FA 
/* 155A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FAA 
/* 155B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FWAA 
/* 155C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE FWAA 
/* 155D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS F 
/* 155E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS THE 
/* 155F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS N-CREE THE 
/* 1560 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS THI 
/* 1561 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS N-CREE THI 
/* 1562 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS THII 
/* 1563 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS N-CREE THII 
/* 1564 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS THO 
/* 1565 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS THOO 
/* 1566 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS THA 
/* 1567 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS THAA 
/* 1568 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS THWAA 
/* 1569 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE THWAA 
/* 156A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH 
/* 156B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTHE 
/* 156C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTHI 
/* 156D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTHO 
/* 156E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTHA 
/* 156F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TTH 
/* 1570 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TYE 
/* 1571 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TYI 
/* 1572 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TYO 
/* 1573 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TYA 
/* 1574 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVIK HE 
/* 1575 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVIK HI 
/* 1576 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVIK HII 
/* 1577 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVIK HO 
/* 1578 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVIK HOO 
/* 1579 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVIK HA 
/* 157A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVIK HAA 
/* 157B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVIK H 
/* 157C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NUNAVUT H 
/* 157D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS HK 
/* 157E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS QAAI 
/* 157F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS QI 
/* 1580 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS QII 
/* 1581 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS QO 
/* 1582 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS QOO 
/* 1583 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS QA 
/* 1584 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS QAA 
/* 1585 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS Q 
/* 1586 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TLHE 
/* 1587 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TLHI 
/* 1588 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TLHO 
/* 1589 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TLHA 
/* 158A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE RE 
/* 158B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE RI 
/* 158C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE RO 
/* 158D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WEST-CREE RA 
/* 158E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NGAAI 
/* 158F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NGI 
/* 1590 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NGII 
/* 1591 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NGO 
/* 1592 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NGOO 
/* 1593 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NGA 
/* 1594 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NGAA 
/* 1595 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NG 
/* 1596 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NNG 
/* 1597 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI SHE 
/* 1598 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI SHI 
/* 1599 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI SHO 
/* 159A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI SHA 
/* 159B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WOODS-CREE THE 
/* 159C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WOODS-CREE THI 
/* 159D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WOODS-CREE THO 
/* 159E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WOODS-CREE THA 
/* 159F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS WOODS-CREE TH 
/* 15A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LHI 
/* 15A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LHII 
/* 15A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LHO 
/* 15A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LHOO 
/* 15A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LHA 
/* 15A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LHAA 
/* 15A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS LH 
/* 15A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH-CREE THE 
/* 15A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH-CREE THI 
/* 15A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH-CREE THII 
/* 15AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH-CREE THO 
/* 15AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH-CREE THOO 
/* 15AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH-CREE THA 
/* 15AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH-CREE THAA 
/* 15AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS TH-CREE TH 
/* 15AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS AIVILIK B 
/* 15B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT E 
/* 15B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT I 
/* 15B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT O 
/* 15B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT A 
/* 15B4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT WE 
/* 15B5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT WI 
/* 15B6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT WO 
/* 15B7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT WA 
/* 15B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT NE 
/* 15B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT NI 
/* 15BA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT NO 
/* 15BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT NA 
/* 15BC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT KE 
/* 15BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT KI 
/* 15BE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT KO 
/* 15BF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS BLACKFOOT KA 
/* 15C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI HE 
/* 15C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI HI 
/* 15C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI HO 
/* 15C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI HA 
/* 15C4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GHU 
/* 15C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GHO 
/* 15C6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GHE 
/* 15C7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GHEE 
/* 15C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GHI 
/* 15C9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GHA 
/* 15CA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER RU 
/* 15CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER RO 
/* 15CC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER RE 
/* 15CD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER REE 
/* 15CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER RI 
/* 15CF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER RA 
/* 15D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER WU 
/* 15D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER WO 
/* 15D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER WE 
/* 15D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER WEE 
/* 15D4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER WI 
/* 15D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER WA 
/* 15D6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER HWU 
/* 15D7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER HWO 
/* 15D8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER HWE 
/* 15D9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER HWEE 
/* 15DA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER HWI 
/* 15DB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER HWA 
/* 15DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER THU 
/* 15DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER THO 
/* 15DE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER THE 
/* 15DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER THEE 
/* 15E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER THI 
/* 15E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER THA 
/* 15E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTU 
/* 15E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTO 
/* 15E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTE 
/* 15E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTEE 
/* 15E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTI 
/* 15E7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTA 
/* 15E8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER PU 
/* 15E9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER PO 
/* 15EA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER PE 
/* 15EB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER PEE 
/* 15EC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER PI 
/* 15ED */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER PA 
/* 15EE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER P 
/* 15EF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GU 
/* 15F0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GO 
/* 15F1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GE 
/* 15F2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GEE 
/* 15F3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GI 
/* 15F4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER GA 
/* 15F5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KHU 
/* 15F6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KHO 
/* 15F7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KHE 
/* 15F8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KHEE 
/* 15F9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KHI 
/* 15FA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KHA 
/* 15FB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KKU 
/* 15FC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KKO 
/* 15FD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KKE 
/* 15FE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KKEE 
/* 15FF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KKI 
/* 1600 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KKA 
/* 1601 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER KK 
/* 1602 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER NU 
/* 1603 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER NO 
/* 1604 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER NE 
/* 1605 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER NEE 
/* 1606 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER NI 
/* 1607 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER NA 
/* 1608 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER MU 
/* 1609 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER MO 
/* 160A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER ME 
/* 160B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER MEE 
/* 160C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER MI 
/* 160D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER MA 
/* 160E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER YU 
/* 160F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER YO 
/* 1610 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER YE 
/* 1611 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER YEE 
/* 1612 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER YI 
/* 1613 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER YA 
/* 1614 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JU 
/* 1615 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI JU 
/* 1616 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JO 
/* 1617 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JE 
/* 1618 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JEE 
/* 1619 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JI 
/* 161A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS SAYISI JI 
/* 161B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JA 
/* 161C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JJU 
/* 161D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JJO 
/* 161E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JJE 
/* 161F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JJEE 
/* 1620 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JJI 
/* 1621 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER JJA 
/* 1622 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LU 
/* 1623 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LO 
/* 1624 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LE 
/* 1625 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LEE 
/* 1626 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LI 
/* 1627 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LA 
/* 1628 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DLU 
/* 1629 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DLO 
/* 162A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DLE 
/* 162B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DLEE 
/* 162C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DLI 
/* 162D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DLA 
/* 162E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LHU 
/* 162F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LHO 
/* 1630 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LHE 
/* 1631 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LHEE 
/* 1632 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LHI 
/* 1633 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER LHA 
/* 1634 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLHU 
/* 1635 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLHO 
/* 1636 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLHE 
/* 1637 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLHEE 
/* 1638 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLHI 
/* 1639 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLHA 
/* 163A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLU 
/* 163B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLO 
/* 163C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLE 
/* 163D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLEE 
/* 163E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLI 
/* 163F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TLA 
/* 1640 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER ZU 
/* 1641 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER ZO 
/* 1642 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER ZE 
/* 1643 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER ZEE 
/* 1644 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER ZI 
/* 1645 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER ZA 
/* 1646 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER Z 
/* 1647 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER INITIAL Z 
/* 1648 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DZU 
/* 1649 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DZO 
/* 164A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DZE 
/* 164B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DZEE 
/* 164C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DZI 
/* 164D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER DZA 
/* 164E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SU 
/* 164F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SO 
/* 1650 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SE 
/* 1651 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SEE 
/* 1652 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SI 
/* 1653 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SA 
/* 1654 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SHU 
/* 1655 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SHO 
/* 1656 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SHE 
/* 1657 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SHEE 
/* 1658 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SHI 
/* 1659 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SHA 
/* 165A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER SH 
/* 165B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TSU 
/* 165C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TSO 
/* 165D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TSE 
/* 165E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TSEE 
/* 165F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TSI 
/* 1660 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TSA 
/* 1661 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER CHU 
/* 1662 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER CHO 
/* 1663 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER CHE 
/* 1664 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER CHEE 
/* 1665 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER CHI 
/* 1666 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER CHA 
/* 1667 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTSU 
/* 1668 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTSO 
/* 1669 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTSE 
/* 166A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTSEE 
/* 166B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTSI 
/* 166C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CARRIER TTSA 
/* 166D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS CHI SIGN 
/* 166E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS FULL STOP 
/* 166F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS QAI 
/* 1670 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NGAI 
/* 1671 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NNGI 
/* 1672 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NNGII 
/* 1673 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NNGO 
/* 1674 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NNGOO 
/* 1675 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NNGA 
/* 1676 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CANADIAN SYLLABICS NNGAA 
/* 1677 */ { 0x0000, 0x0000, 0x0000 },
/* 1678 */ { 0x0000, 0x0000, 0x0000 },
/* 1679 */ { 0x0000, 0x0000, 0x0000 },
/* 167a */ { 0x0000, 0x0000, 0x0000 },
/* 167b */ { 0x0000, 0x0000, 0x0000 },
/* 167c */ { 0x0000, 0x0000, 0x0000 },
/* 167d */ { 0x0000, 0x0000, 0x0000 },
/* 167e */ { 0x0000, 0x0000, 0x0000 },
/* 167f */ { 0x0000, 0x0000, 0x0000 },
/* 1680 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM SPACE MARK 
/* 1681 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER BEITH 
/* 1682 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER LUIS 
/* 1683 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER FEARN 
/* 1684 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER SAIL 
/* 1685 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER NION 
/* 1686 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER UATH 
/* 1687 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER DAIR 
/* 1688 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER TINNE 
/* 1689 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER COLL 
/* 168A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER CEIRT 
/* 168B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER MUIN 
/* 168C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER GORT 
/* 168D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER NGEADAL 
/* 168E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER STRAIF 
/* 168F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER RUIS 
/* 1690 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER AILM 
/* 1691 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER ONN 
/* 1692 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER UR 
/* 1693 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER EADHADH 
/* 1694 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER IODHADH 
/* 1695 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER EABHADH 
/* 1696 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER OR 
/* 1697 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER UILLEANN 
/* 1698 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER IFIN 
/* 1699 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER EAMHANCHOLL 
/* 169A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM LETTER PEITH 
/* 169B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM FEATHER MARK 
/* 169C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OGHAM REVERSED FEATHER MARK 
/* 169d */ { 0x0000, 0x0000, 0x0000 },
/* 169e */ { 0x0000, 0x0000, 0x0000 },
/* 169f */ { 0x0000, 0x0000, 0x0000 },
/* 16A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER FEHU FEOH FE F 
/* 16A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER V 
/* 16A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER URUZ UR U 
/* 16A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER YR 
/* 16A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER Y 
/* 16A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER W 
/* 16A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER THURISAZ THURS THORN 
/* 16A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER ETH 
/* 16A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER ANSUZ A 
/* 16A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER OS O 
/* 16AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER AC A 
/* 16AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER AESC 
/* 16AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER LONG-BRANCH-OSS O 
/* 16AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-OSS O 
/* 16AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER O 
/* 16AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER OE 
/* 16B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER ON 
/* 16B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER RAIDO RAD REID R 
/* 16B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER KAUNA 
/* 16B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER CEN 
/* 16B4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER KAUN K 
/* 16B5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER G 
/* 16B6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER ENG 
/* 16B7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER GEBO GYFU G 
/* 16B8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER GAR 
/* 16B9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER WUNJO WYNN W 
/* 16BA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER HAGLAZ H 
/* 16BB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER HAEGL H 
/* 16BC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER LONG-BRANCH-HAGALL H 
/* 16BD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-HAGALL H 
/* 16BE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER NAUDIZ NYD NAUD N 
/* 16BF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-NAUD N 
/* 16C0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER DOTTED-N 
/* 16C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER ISAZ IS ISS I 
/* 16C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER E 
/* 16C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER JERAN J 
/* 16C4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER GER 
/* 16C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER LONG-BRANCH-AR AE 
/* 16C6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-AR A 
/* 16C7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER IWAZ EOH 
/* 16C8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER PERTHO PEORTH P 
/* 16C9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER ALGIZ EOLHX 
/* 16CA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SOWILO S 
/* 16CB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SIGEL LONG-BRANCH-SOL S 
/* 16CC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-SOL S 
/* 16CD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER C 
/* 16CE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER Z 
/* 16CF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER TIWAZ TIR TYR T 
/* 16D0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-TYR T 
/* 16D1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER D 
/* 16D2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER BERKANAN BEORC BJARKAN B 
/* 16D3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-BJARKAN B 
/* 16D4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER DOTTED-P 
/* 16D5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER OPEN-P 
/* 16D6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER EHWAZ EH E 
/* 16D7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER MANNAZ MAN M 
/* 16D8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER LONG-BRANCH-MADR M 
/* 16D9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-MADR M 
/* 16DA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER LAUKAZ LAGU LOGR L 
/* 16DB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER DOTTED-L 
/* 16DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER INGWAZ 
/* 16DD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER ING 
/* 16DE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER DAGAZ DAEG D 
/* 16DF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER OTHALAN ETHEL O 
/* 16E0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER EAR 
/* 16E1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER IOR 
/* 16E2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER CWEORTH 
/* 16E3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER CALC 
/* 16E4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER CEALC 
/* 16E5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER STAN 
/* 16E6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER LONG-BRANCH-YR 
/* 16E7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER SHORT-TWIG-YR 
/* 16E8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER ICELANDIC-YR 
/* 16E9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER Q 
/* 16EA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC LETTER X 
/* 16EB */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC SINGLE PUNCTUATION 
/* 16EC */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC MULTIPLE PUNCTUATION 
/* 16ED */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC CROSS PUNCTUATION 
/* 16EE */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC ARLAUG SYMBOL 
/* 16EF */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC TVIMADUR SYMBOL 
/* 16F0 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUNIC BELGTHOR SYMBOL 
/* 16f1 */ { 0x0000, 0x0000, 0x0000 },
/* 16f2 */ { 0x0000, 0x0000, 0x0000 },
/* 16f3 */ { 0x0000, 0x0000, 0x0000 },
/* 16f4 */ { 0x0000, 0x0000, 0x0000 },
/* 16f5 */ { 0x0000, 0x0000, 0x0000 },
/* 16f6 */ { 0x0000, 0x0000, 0x0000 },
/* 16f7 */ { 0x0000, 0x0000, 0x0000 },
/* 16f8 */ { 0x0000, 0x0000, 0x0000 },
/* 16f9 */ { 0x0000, 0x0000, 0x0000 },
/* 16fa */ { 0x0000, 0x0000, 0x0000 },
/* 16fb */ { 0x0000, 0x0000, 0x0000 },
/* 16fc */ { 0x0000, 0x0000, 0x0000 },
/* 16fd */ { 0x0000, 0x0000, 0x0000 },
/* 16fe */ { 0x0000, 0x0000, 0x0000 },
/* 16ff */ { 0x0000, 0x0000, 0x0000 },
/* 1700 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER A 
/* 1701 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER I 
/* 1702 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER U 
/* 1703 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER KA 
/* 1704 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER GA 
/* 1705 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER NGA 
/* 1706 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER TA 
/* 1707 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER DA 
/* 1708 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER NA 
/* 1709 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER PA 
/* 170A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER BA 
/* 170B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER MA 
/* 170C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER YA 
/* 170d */ { 0x0000, 0x0000, 0x0000 },
/* 170E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER LA 
/* 170F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER WA 
/* 1710 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER SA 
/* 1711 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG LETTER HA 
/* 1712 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG VOWEL SIGN I 
/* 1713 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG VOWEL SIGN U 
/* 1714 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGALOG SIGN VIRAMA 
/* 1715 */ { 0x0000, 0x0000, 0x0000 },
/* 1716 */ { 0x0000, 0x0000, 0x0000 },
/* 1717 */ { 0x0000, 0x0000, 0x0000 },
/* 1718 */ { 0x0000, 0x0000, 0x0000 },
/* 1719 */ { 0x0000, 0x0000, 0x0000 },
/* 171a */ { 0x0000, 0x0000, 0x0000 },
/* 171b */ { 0x0000, 0x0000, 0x0000 },
/* 171c */ { 0x0000, 0x0000, 0x0000 },
/* 171d */ { 0x0000, 0x0000, 0x0000 },
/* 171e */ { 0x0000, 0x0000, 0x0000 },
/* 171f */ { 0x0000, 0x0000, 0x0000 },
/* 1720 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER A 
/* 1721 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER I 
/* 1722 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER U 
/* 1723 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER KA 
/* 1724 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER GA 
/* 1725 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER NGA 
/* 1726 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER TA 
/* 1727 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER DA 
/* 1728 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER NA 
/* 1729 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER PA 
/* 172A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER BA 
/* 172B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER MA 
/* 172C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER YA 
/* 172D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER RA 
/* 172E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER LA 
/* 172F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER WA 
/* 1730 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER SA 
/* 1731 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO LETTER HA 
/* 1732 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO VOWEL SIGN I 
/* 1733 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO VOWEL SIGN U 
/* 1734 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HANUNOO SIGN PAMUDPOD 
/* 1735 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PHILIPPINE SINGLE PUNCTUATION 
/* 1736 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PHILIPPINE DOUBLE PUNCTUATION 
/* 1737 */ { 0x0000, 0x0000, 0x0000 },
/* 1738 */ { 0x0000, 0x0000, 0x0000 },
/* 1739 */ { 0x0000, 0x0000, 0x0000 },
/* 173a */ { 0x0000, 0x0000, 0x0000 },
/* 173b */ { 0x0000, 0x0000, 0x0000 },
/* 173c */ { 0x0000, 0x0000, 0x0000 },
/* 173d */ { 0x0000, 0x0000, 0x0000 },
/* 173e */ { 0x0000, 0x0000, 0x0000 },
/* 173f */ { 0x0000, 0x0000, 0x0000 },
/* 1740 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER A 
/* 1741 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER I 
/* 1742 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER U 
/* 1743 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER KA 
/* 1744 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER GA 
/* 1745 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER NGA 
/* 1746 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER TA 
/* 1747 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER DA 
/* 1748 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER NA 
/* 1749 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER PA 
/* 174A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER BA 
/* 174B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER MA 
/* 174C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER YA 
/* 174D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER RA 
/* 174E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER LA 
/* 174F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER WA 
/* 1750 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER SA 
/* 1751 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID LETTER HA 
/* 1752 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID VOWEL SIGN I 
/* 1753 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUHID VOWEL SIGN U 
/* 1754 */ { 0x0000, 0x0000, 0x0000 },
/* 1755 */ { 0x0000, 0x0000, 0x0000 },
/* 1756 */ { 0x0000, 0x0000, 0x0000 },
/* 1757 */ { 0x0000, 0x0000, 0x0000 },
/* 1758 */ { 0x0000, 0x0000, 0x0000 },
/* 1759 */ { 0x0000, 0x0000, 0x0000 },
/* 175a */ { 0x0000, 0x0000, 0x0000 },
/* 175b */ { 0x0000, 0x0000, 0x0000 },
/* 175c */ { 0x0000, 0x0000, 0x0000 },
/* 175d */ { 0x0000, 0x0000, 0x0000 },
/* 175e */ { 0x0000, 0x0000, 0x0000 },
/* 175f */ { 0x0000, 0x0000, 0x0000 },
/* 1760 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER A 
/* 1761 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER I 
/* 1762 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER U 
/* 1763 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER KA 
/* 1764 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER GA 
/* 1765 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER NGA 
/* 1766 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER TA 
/* 1767 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER DA 
/* 1768 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER NA 
/* 1769 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER PA 
/* 176A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER BA 
/* 176B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER MA 
/* 176C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER YA 
/* 176d */ { 0x0000, 0x0000, 0x0000 },
/* 176E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER LA 
/* 176F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER WA 
/* 1770 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA LETTER SA 
/* 1771 */ { 0x0000, 0x0000, 0x0000 },
/* 1772 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA VOWEL SIGN I 
/* 1773 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAGBANWA VOWEL SIGN U 
/* 1774 */ { 0x0000, 0x0000, 0x0000 },
/* 1775 */ { 0x0000, 0x0000, 0x0000 },
/* 1776 */ { 0x0000, 0x0000, 0x0000 },
/* 1777 */ { 0x0000, 0x0000, 0x0000 },
/* 1778 */ { 0x0000, 0x0000, 0x0000 },
/* 1779 */ { 0x0000, 0x0000, 0x0000 },
/* 177a */ { 0x0000, 0x0000, 0x0000 },
/* 177b */ { 0x0000, 0x0000, 0x0000 },
/* 177c */ { 0x0000, 0x0000, 0x0000 },
/* 177d */ { 0x0000, 0x0000, 0x0000 },
/* 177e */ { 0x0000, 0x0000, 0x0000 },
/* 177f */ { 0x0000, 0x0000, 0x0000 },
/* 1780 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER KA 
/* 1781 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER KHA 
/* 1782 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER KO 
/* 1783 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER KHO 
/* 1784 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER NGO 
/* 1785 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER CA 
/* 1786 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER CHA 
/* 1787 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER CO 
/* 1788 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER CHO 
/* 1789 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER NYO 
/* 178A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER DA 
/* 178B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER TTHA 
/* 178C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER DO 
/* 178D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER TTHO 
/* 178E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER NNO 
/* 178F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER TA 
/* 1790 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER THA 
/* 1791 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER TO 
/* 1792 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER THO 
/* 1793 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER NO 
/* 1794 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER BA 
/* 1795 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER PHA 
/* 1796 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER PO 
/* 1797 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER PHO 
/* 1798 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER MO 
/* 1799 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER YO 
/* 179A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER RO 
/* 179B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER LO 
/* 179C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER VO 
/* 179D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER SHA 
/* 179E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER SSO 
/* 179F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER SA 
/* 17A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER HA 
/* 17A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER LA 
/* 17A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER LETTER QA 
/* 17A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QAQ 
/* 17A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QAA 
/* 17A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QI 
/* 17A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QII 
/* 17A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QU 
/* 17A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QUK 
/* 17A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QUU 
/* 17AA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QUUV 
/* 17AB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL RY 
/* 17AC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL RYY 
/* 17AD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL LY 
/* 17AE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL LYY 
/* 17AF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QE 
/* 17B0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QAI 
/* 17B1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QOO TYPE ONE 
/* 17B2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QOO TYPE TWO 
/* 17B3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER INDEPENDENT VOWEL QAU 
/* 17B4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL INHERENT AQ 
/* 17B5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL INHERENT AA 
/* 17B6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN AA 
/* 17B7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN I 
/* 17B8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN II 
/* 17B9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN Y 
/* 17BA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN YY 
/* 17BB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN U 
/* 17BC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN UU 
/* 17BD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN UA 
/* 17BE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN OE 
/* 17BF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN YA 
/* 17C0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN IE 
/* 17C1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN E 
/* 17C2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN AE 
/* 17C3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN AI 
/* 17C4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN OO 
/* 17C5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER VOWEL SIGN AU 
/* 17C6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN NIKAHIT 
/* 17C7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN REAHMUK 
/* 17C8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN YUUKALEAPINTU 
/* 17C9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN MUUSIKATOAN 
/* 17CA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN TRIISAP 
/* 17CB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN BANTOC 
/* 17CC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN ROBAT 
/* 17CD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN TOANDAKHIAT 
/* 17CE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN KAKABAT 
/* 17CF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN AHSDA 
/* 17D0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN SAMYOK SANNYA 
/* 17D1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN VIRIAM 
/* 17D2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN COENG 
/* 17D3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN BATHAMASAT 
/* 17D4 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN KHAN 
/* 17D5 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN BARIYOOSAN 
/* 17D6 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN CAMNUC PII KUUH 
/* 17D7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN LEK TOO 
/* 17D8 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN BEYYAL 
/* 17D9 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN PHNAEK MUAN 
/* 17DA */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN KOOMUUT 
/* 17DB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER CURRENCY SYMBOL RIEL 
/* 17DC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN AVAKRAHASANYA 
/* 17DD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SIGN ATTHACAN 
/* 17de */ { 0x0000, 0x0000, 0x0000 },
/* 17df */ { 0x0000, 0x0000, 0x0000 },
/* 17E0 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT ZERO 
/* 17E1 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT ONE 
/* 17E2 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT TWO 
/* 17E3 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT THREE 
/* 17E4 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT FOUR 
/* 17E5 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT FIVE 
/* 17E6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT SIX 
/* 17E7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT SEVEN 
/* 17E8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT EIGHT 
/* 17E9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER DIGIT NINE 
/* 17ea */ { 0x0000, 0x0000, 0x0000 },
/* 17eb */ { 0x0000, 0x0000, 0x0000 },
/* 17ec */ { 0x0000, 0x0000, 0x0000 },
/* 17ed */ { 0x0000, 0x0000, 0x0000 },
/* 17ee */ { 0x0000, 0x0000, 0x0000 },
/* 17ef */ { 0x0000, 0x0000, 0x0000 },
/* 17F0 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK SON 
/* 17F1 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK MUOY 
/* 17F2 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK PII 
/* 17F3 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK BEI 
/* 17F4 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK BUON 
/* 17F5 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK PRAM 
/* 17F6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK PRAM-MUOY 
/* 17F7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK PRAM-PII 
/* 17F8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK PRAM-BEI 
/* 17F9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL LEK ATTAK PRAM-BUON 
/* 17fa */ { 0x0000, 0x0000, 0x0000 },
/* 17fb */ { 0x0000, 0x0000, 0x0000 },
/* 17fc */ { 0x0000, 0x0000, 0x0000 },
/* 17fd */ { 0x0000, 0x0000, 0x0000 },
/* 17fe */ { 0x0000, 0x0000, 0x0000 },
/* 17ff */ { 0x0000, 0x0000, 0x0000 },
/* 1800 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN BIRGA 
/* 1801 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN ELLIPSIS 
/* 1802 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN COMMA 
/* 1803 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN FULL STOP 
/* 1804 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN COLON 
/* 1805 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN FOUR DOTS 
/* 1806 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN TODO SOFT HYPHEN 
/* 1807 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN SIBE SYLLABLE BOUNDARY MARKER 
/* 1808 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN MANCHU COMMA 
/* 1809 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN MANCHU FULL STOP 
/* 180A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN NIRUGU 
/* 180B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN FREE VARIATION SELECTOR ONE 
/* 180C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN FREE VARIATION SELECTOR TWO 
/* 180D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN FREE VARIATION SELECTOR THREE 
/* 180E */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN VOWEL SEPARATOR 
/* 180f */ { 0x0000, 0x0000, 0x0000 },
/* 1810 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT ZERO 
/* 1811 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT ONE 
/* 1812 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT TWO 
/* 1813 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT THREE 
/* 1814 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT FOUR 
/* 1815 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT FIVE 
/* 1816 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT SIX 
/* 1817 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT SEVEN 
/* 1818 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT EIGHT 
/* 1819 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN DIGIT NINE 
/* 181a */ { 0x0000, 0x0000, 0x0000 },
/* 181b */ { 0x0000, 0x0000, 0x0000 },
/* 181c */ { 0x0000, 0x0000, 0x0000 },
/* 181d */ { 0x0000, 0x0000, 0x0000 },
/* 181e */ { 0x0000, 0x0000, 0x0000 },
/* 181f */ { 0x0000, 0x0000, 0x0000 },
/* 1820 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER A 
/* 1821 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER E 
/* 1822 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER I 
/* 1823 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER O 
/* 1824 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER U 
/* 1825 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER OE 
/* 1826 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER UE 
/* 1827 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER EE 
/* 1828 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER NA 
/* 1829 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ANG 
/* 182A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER BA 
/* 182B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER PA 
/* 182C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER QA 
/* 182D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER GA 
/* 182E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MA 
/* 182F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER LA 
/* 1830 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SA 
/* 1831 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SHA 
/* 1832 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TA 
/* 1833 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER DA 
/* 1834 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER CHA 
/* 1835 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER JA 
/* 1836 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER YA 
/* 1837 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER RA 
/* 1838 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER WA 
/* 1839 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER FA 
/* 183A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER KA 
/* 183B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER KHA 
/* 183C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TSA 
/* 183D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ZA 
/* 183E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER HAA 
/* 183F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ZRA 
/* 1840 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER LHA 
/* 1841 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ZHI 
/* 1842 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER CHI 
/* 1843 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO LONG VOWEL SIGN 
/* 1844 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO E 
/* 1845 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO I 
/* 1846 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO O 
/* 1847 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO U 
/* 1848 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO OE 
/* 1849 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO UE 
/* 184A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO ANG 
/* 184B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO BA 
/* 184C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO PA 
/* 184D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO QA 
/* 184E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO GA 
/* 184F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO MA 
/* 1850 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO TA 
/* 1851 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO DA 
/* 1852 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO CHA 
/* 1853 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO JA 
/* 1854 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO TSA 
/* 1855 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO YA 
/* 1856 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO WA 
/* 1857 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO KA 
/* 1858 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO GAA 
/* 1859 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO HAA 
/* 185A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO JIA 
/* 185B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO NIA 
/* 185C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO DZA 
/* 185D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE E 
/* 185E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE I 
/* 185F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE IY 
/* 1860 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE UE 
/* 1861 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE U 
/* 1862 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE ANG 
/* 1863 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE KA 
/* 1864 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE GA 
/* 1865 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE HA 
/* 1866 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE PA 
/* 1867 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE SHA 
/* 1868 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE TA 
/* 1869 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE DA 
/* 186A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE JA 
/* 186B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE FA 
/* 186C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE GAA 
/* 186D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE HAA 
/* 186E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE TSA 
/* 186F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE ZA 
/* 1870 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE RAA 
/* 1871 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE CHA 
/* 1872 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER SIBE ZHA 
/* 1873 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU I 
/* 1874 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU KA 
/* 1875 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU RA 
/* 1876 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU FA 
/* 1877 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ZHA 
/* 1878 */ { 0x0000, 0x0000, 0x0000 },
/* 1879 */ { 0x0000, 0x0000, 0x0000 },
/* 187a */ { 0x0000, 0x0000, 0x0000 },
/* 187b */ { 0x0000, 0x0000, 0x0000 },
/* 187c */ { 0x0000, 0x0000, 0x0000 },
/* 187d */ { 0x0000, 0x0000, 0x0000 },
/* 187e */ { 0x0000, 0x0000, 0x0000 },
/* 187f */ { 0x0000, 0x0000, 0x0000 },
/* 1880 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI ANUSVARA ONE 
/* 1881 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI VISARGA ONE 
/* 1882 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI DAMARU 
/* 1883 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI UBADAMA 
/* 1884 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI INVERTED UBADAMA 
/* 1885 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI BALUDA 
/* 1886 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI THREE BALUDA 
/* 1887 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI A 
/* 1888 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI I 
/* 1889 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI KA 
/* 188A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI NGA 
/* 188B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI CA 
/* 188C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI TTA 
/* 188D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI TTHA 
/* 188E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI DDA 
/* 188F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI NNA 
/* 1890 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI TA 
/* 1891 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI DA 
/* 1892 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI PA 
/* 1893 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI PHA 
/* 1894 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI SSA 
/* 1895 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI ZHA 
/* 1896 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI ZA 
/* 1897 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI AH 
/* 1898 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO ALI GALI TA 
/* 1899 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER TODO ALI GALI ZHA 
/* 189A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI GHA 
/* 189B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI NGA 
/* 189C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI CA 
/* 189D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI JHA 
/* 189E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI TTA 
/* 189F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI DDHA 
/* 18A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI TA 
/* 18A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI DHA 
/* 18A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI SSA 
/* 18A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI CYA 
/* 18A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI ZHA 
/* 18A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI ZA 
/* 18A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI HALF U 
/* 18A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI HALF YA 
/* 18A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER MANCHU ALI GALI BHA 
/* 18A9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MONGOLIAN LETTER ALI GALI DAGALGA 
/* 18aa */ { 0x0000, 0x0000, 0x0000 },
/* 18ab */ { 0x0000, 0x0000, 0x0000 },
/* 18ac */ { 0x0000, 0x0000, 0x0000 },
/* 18ad */ { 0x0000, 0x0000, 0x0000 },
/* 18ae */ { 0x0000, 0x0000, 0x0000 },
/* 18af */ { 0x0000, 0x0000, 0x0000 },
/* 18b0 */ { 0x0000, 0x0000, 0x0000 },
/* 18b1 */ { 0x0000, 0x0000, 0x0000 },
/* 18b2 */ { 0x0000, 0x0000, 0x0000 },
/* 18b3 */ { 0x0000, 0x0000, 0x0000 },
/* 18b4 */ { 0x0000, 0x0000, 0x0000 },
/* 18b5 */ { 0x0000, 0x0000, 0x0000 },
/* 18b6 */ { 0x0000, 0x0000, 0x0000 },
/* 18b7 */ { 0x0000, 0x0000, 0x0000 },
/* 18b8 */ { 0x0000, 0x0000, 0x0000 },
/* 18b9 */ { 0x0000, 0x0000, 0x0000 },
/* 18ba */ { 0x0000, 0x0000, 0x0000 },
/* 18bb */ { 0x0000, 0x0000, 0x0000 },
/* 18bc */ { 0x0000, 0x0000, 0x0000 },
/* 18bd */ { 0x0000, 0x0000, 0x0000 },
/* 18be */ { 0x0000, 0x0000, 0x0000 },
/* 18bf */ { 0x0000, 0x0000, 0x0000 },
/* 18c0 */ { 0x0000, 0x0000, 0x0000 },
/* 18c1 */ { 0x0000, 0x0000, 0x0000 },
/* 18c2 */ { 0x0000, 0x0000, 0x0000 },
/* 18c3 */ { 0x0000, 0x0000, 0x0000 },
/* 18c4 */ { 0x0000, 0x0000, 0x0000 },
/* 18c5 */ { 0x0000, 0x0000, 0x0000 },
/* 18c6 */ { 0x0000, 0x0000, 0x0000 },
/* 18c7 */ { 0x0000, 0x0000, 0x0000 },
/* 18c8 */ { 0x0000, 0x0000, 0x0000 },
/* 18c9 */ { 0x0000, 0x0000, 0x0000 },
/* 18ca */ { 0x0000, 0x0000, 0x0000 },
/* 18cb */ { 0x0000, 0x0000, 0x0000 },
/* 18cc */ { 0x0000, 0x0000, 0x0000 },
/* 18cd */ { 0x0000, 0x0000, 0x0000 },
/* 18ce */ { 0x0000, 0x0000, 0x0000 },
/* 18cf */ { 0x0000, 0x0000, 0x0000 },
/* 18d0 */ { 0x0000, 0x0000, 0x0000 },
/* 18d1 */ { 0x0000, 0x0000, 0x0000 },
/* 18d2 */ { 0x0000, 0x0000, 0x0000 },
/* 18d3 */ { 0x0000, 0x0000, 0x0000 },
/* 18d4 */ { 0x0000, 0x0000, 0x0000 },
/* 18d5 */ { 0x0000, 0x0000, 0x0000 },
/* 18d6 */ { 0x0000, 0x0000, 0x0000 },
/* 18d7 */ { 0x0000, 0x0000, 0x0000 },
/* 18d8 */ { 0x0000, 0x0000, 0x0000 },
/* 18d9 */ { 0x0000, 0x0000, 0x0000 },
/* 18da */ { 0x0000, 0x0000, 0x0000 },
/* 18db */ { 0x0000, 0x0000, 0x0000 },
/* 18dc */ { 0x0000, 0x0000, 0x0000 },
/* 18dd */ { 0x0000, 0x0000, 0x0000 },
/* 18de */ { 0x0000, 0x0000, 0x0000 },
/* 18df */ { 0x0000, 0x0000, 0x0000 },
/* 18e0 */ { 0x0000, 0x0000, 0x0000 },
/* 18e1 */ { 0x0000, 0x0000, 0x0000 },
/* 18e2 */ { 0x0000, 0x0000, 0x0000 },
/* 18e3 */ { 0x0000, 0x0000, 0x0000 },
/* 18e4 */ { 0x0000, 0x0000, 0x0000 },
/* 18e5 */ { 0x0000, 0x0000, 0x0000 },
/* 18e6 */ { 0x0000, 0x0000, 0x0000 },
/* 18e7 */ { 0x0000, 0x0000, 0x0000 },
/* 18e8 */ { 0x0000, 0x0000, 0x0000 },
/* 18e9 */ { 0x0000, 0x0000, 0x0000 },
/* 18ea */ { 0x0000, 0x0000, 0x0000 },
/* 18eb */ { 0x0000, 0x0000, 0x0000 },
/* 18ec */ { 0x0000, 0x0000, 0x0000 },
/* 18ed */ { 0x0000, 0x0000, 0x0000 },
/* 18ee */ { 0x0000, 0x0000, 0x0000 },
/* 18ef */ { 0x0000, 0x0000, 0x0000 },
/* 18f0 */ { 0x0000, 0x0000, 0x0000 },
/* 18f1 */ { 0x0000, 0x0000, 0x0000 },
/* 18f2 */ { 0x0000, 0x0000, 0x0000 },
/* 18f3 */ { 0x0000, 0x0000, 0x0000 },
/* 18f4 */ { 0x0000, 0x0000, 0x0000 },
/* 18f5 */ { 0x0000, 0x0000, 0x0000 },
/* 18f6 */ { 0x0000, 0x0000, 0x0000 },
/* 18f7 */ { 0x0000, 0x0000, 0x0000 },
/* 18f8 */ { 0x0000, 0x0000, 0x0000 },
/* 18f9 */ { 0x0000, 0x0000, 0x0000 },
/* 18fa */ { 0x0000, 0x0000, 0x0000 },
/* 18fb */ { 0x0000, 0x0000, 0x0000 },
/* 18fc */ { 0x0000, 0x0000, 0x0000 },
/* 18fd */ { 0x0000, 0x0000, 0x0000 },
/* 18fe */ { 0x0000, 0x0000, 0x0000 },
/* 18ff */ { 0x0000, 0x0000, 0x0000 },
/* 1900 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL-CARRIER LETTER 
/* 1901 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER KA 
/* 1902 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER KHA 
/* 1903 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER GA 
/* 1904 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER GHA 
/* 1905 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER NGA 
/* 1906 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER CA 
/* 1907 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER CHA 
/* 1908 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER JA 
/* 1909 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER JHA 
/* 190A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER YAN 
/* 190B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER TA 
/* 190C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER THA 
/* 190D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER DA 
/* 190E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER DHA 
/* 190F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER NA 
/* 1910 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER PA 
/* 1911 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER PHA 
/* 1912 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER BA 
/* 1913 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER BHA 
/* 1914 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER MA 
/* 1915 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER YA 
/* 1916 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER RA 
/* 1917 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER LA 
/* 1918 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER WA 
/* 1919 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER SHA 
/* 191A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER SSA 
/* 191B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER SA 
/* 191C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU LETTER HA 
/* 191d */ { 0x0000, 0x0000, 0x0000 },
/* 191e */ { 0x0000, 0x0000, 0x0000 },
/* 191f */ { 0x0000, 0x0000, 0x0000 },
/* 1920 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN A 
/* 1921 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN I 
/* 1922 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN U 
/* 1923 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN EE 
/* 1924 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN AI 
/* 1925 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN OO 
/* 1926 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN AU 
/* 1927 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN E 
/* 1928 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU VOWEL SIGN O 
/* 1929 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SUBJOINED LETTER YA 
/* 192A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SUBJOINED LETTER RA 
/* 192B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SUBJOINED LETTER WA 
/* 192c */ { 0x0000, 0x0000, 0x0000 },
/* 192d */ { 0x0000, 0x0000, 0x0000 },
/* 192e */ { 0x0000, 0x0000, 0x0000 },
/* 192f */ { 0x0000, 0x0000, 0x0000 },
/* 1930 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER KA 
/* 1931 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER NGA 
/* 1932 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER ANUSVARA 
/* 1933 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER TA 
/* 1934 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER NA 
/* 1935 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER PA 
/* 1936 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER MA 
/* 1937 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER RA 
/* 1938 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SMALL LETTER LA 
/* 1939 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SIGN MUKPHRENG 
/* 193A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SIGN KEMPHRENG 
/* 193B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SIGN SA-I 
/* 193c */ { 0x0000, 0x0000, 0x0000 },
/* 193d */ { 0x0000, 0x0000, 0x0000 },
/* 193e */ { 0x0000, 0x0000, 0x0000 },
/* 193f */ { 0x0000, 0x0000, 0x0000 },
/* 1940 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU SIGN LOO 
/* 1941 */ { 0x0000, 0x0000, 0x0000 },
/* 1942 */ { 0x0000, 0x0000, 0x0000 },
/* 1943 */ { 0x0000, 0x0000, 0x0000 },
/* 1944 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU EXCLAMATION MARK 
/* 1945 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU QUESTION MARK 
/* 1946 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT ZERO 
/* 1947 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT ONE 
/* 1948 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT TWO 
/* 1949 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT THREE 
/* 194A */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT FOUR 
/* 194B */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT FIVE 
/* 194C */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT SIX 
/* 194D */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT SEVEN 
/* 194E */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT EIGHT 
/* 194F */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIMBU DIGIT NINE 
/* 1950 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER KA 
/* 1951 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER XA 
/* 1952 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER NGA 
/* 1953 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER TSA 
/* 1954 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER SA 
/* 1955 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER YA 
/* 1956 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER TA 
/* 1957 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER THA 
/* 1958 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER LA 
/* 1959 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER PA 
/* 195A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER PHA 
/* 195B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER MA 
/* 195C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER FA 
/* 195D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER VA 
/* 195E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER HA 
/* 195F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER QA 
/* 1960 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER KHA 
/* 1961 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER TSHA 
/* 1962 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER NA 
/* 1963 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER A 
/* 1964 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER I 
/* 1965 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER EE 
/* 1966 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER EH 
/* 1967 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER U 
/* 1968 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER OO 
/* 1969 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER O 
/* 196A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER UE 
/* 196B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER E 
/* 196C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER AUE 
/* 196D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER AI 
/* 196e */ { 0x0000, 0x0000, 0x0000 },
/* 196f */ { 0x0000, 0x0000, 0x0000 },
/* 1970 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER TONE-2 
/* 1971 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER TONE-3 
/* 1972 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER TONE-4 
/* 1973 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER TONE-5 
/* 1974 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TAI LE LETTER TONE-6 
/* 1975 */ { 0x0000, 0x0000, 0x0000 },
/* 1976 */ { 0x0000, 0x0000, 0x0000 },
/* 1977 */ { 0x0000, 0x0000, 0x0000 },
/* 1978 */ { 0x0000, 0x0000, 0x0000 },
/* 1979 */ { 0x0000, 0x0000, 0x0000 },
/* 197a */ { 0x0000, 0x0000, 0x0000 },
/* 197b */ { 0x0000, 0x0000, 0x0000 },
/* 197c */ { 0x0000, 0x0000, 0x0000 },
/* 197d */ { 0x0000, 0x0000, 0x0000 },
/* 197e */ { 0x0000, 0x0000, 0x0000 },
/* 197f */ { 0x0000, 0x0000, 0x0000 },
/* 1980 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH QA 
/* 1981 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW QA 
/* 1982 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH KA 
/* 1983 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH XA 
/* 1984 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH NGA 
/* 1985 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW KA 
/* 1986 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW XA 
/* 1987 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW NGA 
/* 1988 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH TSA 
/* 1989 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH SA 
/* 198A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH YA 
/* 198B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW TSA 
/* 198C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW SA 
/* 198D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW YA 
/* 198E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH TA 
/* 198F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH THA 
/* 1990 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH NA 
/* 1991 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW TA 
/* 1992 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW THA 
/* 1993 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW NA 
/* 1994 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH PA 
/* 1995 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH PHA 
/* 1996 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH MA 
/* 1997 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW PA 
/* 1998 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW PHA 
/* 1999 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW MA 
/* 199A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH FA 
/* 199B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH VA 
/* 199C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH LA 
/* 199D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW FA 
/* 199E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW VA 
/* 199F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW LA 
/* 19A0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH HA 
/* 19A1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH DA 
/* 19A2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH BA 
/* 19A3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW HA 
/* 19A4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW DA 
/* 19A5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW BA 
/* 19A6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH KVA 
/* 19A7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER HIGH XVA 
/* 19A8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW KVA 
/* 19A9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER LOW XVA 
/* 19aa */ { 0x0000, 0x0000, 0x0000 },
/* 19ab */ { 0x0000, 0x0000, 0x0000 },
/* 19ac */ { 0x0000, 0x0000, 0x0000 },
/* 19ad */ { 0x0000, 0x0000, 0x0000 },
/* 19ae */ { 0x0000, 0x0000, 0x0000 },
/* 19af */ { 0x0000, 0x0000, 0x0000 },
/* 19B0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN VOWEL SHORTENER 
/* 19B1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN AA 
/* 19B2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN II 
/* 19B3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN U 
/* 19B4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN UU 
/* 19B5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN E 
/* 19B6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN AE 
/* 19B7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN O 
/* 19B8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN OA 
/* 19B9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN UE 
/* 19BA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN AY 
/* 19BB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN AAY 
/* 19BC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN UY 
/* 19BD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN OY 
/* 19BE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN OAY 
/* 19BF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN UEY 
/* 19C0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE VOWEL SIGN IY 
/* 19C1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER FINAL V 
/* 19C2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER FINAL NG 
/* 19C3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER FINAL N 
/* 19C4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER FINAL M 
/* 19C5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER FINAL K 
/* 19C6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER FINAL D 
/* 19C7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE LETTER FINAL B 
/* 19C8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE TONE MARK-1 
/* 19C9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE TONE MARK-2 
/* 19ca */ { 0x0000, 0x0000, 0x0000 },
/* 19cb */ { 0x0000, 0x0000, 0x0000 },
/* 19cc */ { 0x0000, 0x0000, 0x0000 },
/* 19cd */ { 0x0000, 0x0000, 0x0000 },
/* 19ce */ { 0x0000, 0x0000, 0x0000 },
/* 19cf */ { 0x0000, 0x0000, 0x0000 },
/* 19D0 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT ZERO 
/* 19D1 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT ONE 
/* 19D2 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT TWO 
/* 19D3 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT THREE 
/* 19D4 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT FOUR 
/* 19D5 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT FIVE 
/* 19D6 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT SIX 
/* 19D7 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT SEVEN 
/* 19D8 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT EIGHT 
/* 19D9 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE DIGIT NINE 
/* 19da */ { 0x0000, 0x0000, 0x0000 },
/* 19db */ { 0x0000, 0x0000, 0x0000 },
/* 19dc */ { 0x0000, 0x0000, 0x0000 },
/* 19dd */ { 0x0000, 0x0000, 0x0000 },
/* 19DE */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE SIGN LAE 
/* 19DF */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW TAI LUE SIGN LAEV 
/* 19E0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PATHAMASAT 
/* 19E1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL MUOY KOET 
/* 19E2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PII KOET 
/* 19E3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL BEI KOET 
/* 19E4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL BUON KOET 
/* 19E5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM KOET 
/* 19E6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM-MUOY KOET 
/* 19E7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM-PII KOET 
/* 19E8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM-BEI KOET 
/* 19E9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM-BUON KOET 
/* 19EA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP KOET 
/* 19EB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-MUOY KOET 
/* 19EC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-PII KOET 
/* 19ED */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-BEI KOET 
/* 19EE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-BUON KOET 
/* 19EF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-PRAM KOET 
/* 19F0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL TUTEYASAT 
/* 19F1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL MUOY ROC 
/* 19F2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PII ROC 
/* 19F3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL BEI ROC 
/* 19F4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL BUON ROC 
/* 19F5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM ROC 
/* 19F6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM-MUOY ROC 
/* 19F7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM-PII ROC 
/* 19F8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM-BEI ROC 
/* 19F9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL PRAM-BUON ROC 
/* 19FA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP ROC 
/* 19FB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-MUOY ROC 
/* 19FC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-PII ROC 
/* 19FD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-BEI ROC 
/* 19FE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-BUON ROC 
/* 19FF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KHMER SYMBOL DAP-PRAM ROC 
/* 1A00 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER KA 
/* 1A01 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER GA 
/* 1A02 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER NGA 
/* 1A03 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER NGKA 
/* 1A04 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER PA 
/* 1A05 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER BA 
/* 1A06 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER MA 
/* 1A07 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER MPA 
/* 1A08 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER TA 
/* 1A09 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER DA 
/* 1A0A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER NA 
/* 1A0B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER NRA 
/* 1A0C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER CA 
/* 1A0D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER JA 
/* 1A0E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER NYA 
/* 1A0F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER NYCA 
/* 1A10 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER YA 
/* 1A11 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER RA 
/* 1A12 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER LA 
/* 1A13 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER VA 
/* 1A14 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER SA 
/* 1A15 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER A 
/* 1A16 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE LETTER HA 
/* 1A17 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE VOWEL SIGN I 
/* 1A18 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE VOWEL SIGN U 
/* 1A19 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE VOWEL SIGN E 
/* 1A1A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE VOWEL SIGN O 
/* 1A1B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE VOWEL SIGN AE 
/* 1a1c */ { 0x0000, 0x0000, 0x0000 },
/* 1a1d */ { 0x0000, 0x0000, 0x0000 },
/* 1A1E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE PALLAWA 
/* 1A1F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BUGINESE END OF SECTION 
/* 1a20 */ { 0x0000, 0x0000, 0x0000 },
/* 1a21 */ { 0x0000, 0x0000, 0x0000 },
/* 1a22 */ { 0x0000, 0x0000, 0x0000 },
/* 1a23 */ { 0x0000, 0x0000, 0x0000 },
/* 1a24 */ { 0x0000, 0x0000, 0x0000 },
/* 1a25 */ { 0x0000, 0x0000, 0x0000 },
/* 1a26 */ { 0x0000, 0x0000, 0x0000 },
/* 1a27 */ { 0x0000, 0x0000, 0x0000 },
/* 1a28 */ { 0x0000, 0x0000, 0x0000 },
/* 1a29 */ { 0x0000, 0x0000, 0x0000 },
/* 1a2a */ { 0x0000, 0x0000, 0x0000 },
/* 1a2b */ { 0x0000, 0x0000, 0x0000 },
/* 1a2c */ { 0x0000, 0x0000, 0x0000 },
/* 1a2d */ { 0x0000, 0x0000, 0x0000 },
/* 1a2e */ { 0x0000, 0x0000, 0x0000 },
/* 1a2f */ { 0x0000, 0x0000, 0x0000 },
/* 1a30 */ { 0x0000, 0x0000, 0x0000 },
/* 1a31 */ { 0x0000, 0x0000, 0x0000 },
/* 1a32 */ { 0x0000, 0x0000, 0x0000 },
/* 1a33 */ { 0x0000, 0x0000, 0x0000 },
/* 1a34 */ { 0x0000, 0x0000, 0x0000 },
/* 1a35 */ { 0x0000, 0x0000, 0x0000 },
/* 1a36 */ { 0x0000, 0x0000, 0x0000 },
/* 1a37 */ { 0x0000, 0x0000, 0x0000 },
/* 1a38 */ { 0x0000, 0x0000, 0x0000 },
/* 1a39 */ { 0x0000, 0x0000, 0x0000 },
/* 1a3a */ { 0x0000, 0x0000, 0x0000 },
/* 1a3b */ { 0x0000, 0x0000, 0x0000 },
/* 1a3c */ { 0x0000, 0x0000, 0x0000 },
/* 1a3d */ { 0x0000, 0x0000, 0x0000 },
/* 1a3e */ { 0x0000, 0x0000, 0x0000 },
/* 1a3f */ { 0x0000, 0x0000, 0x0000 },
/* 1a40 */ { 0x0000, 0x0000, 0x0000 },
/* 1a41 */ { 0x0000, 0x0000, 0x0000 },
/* 1a42 */ { 0x0000, 0x0000, 0x0000 },
/* 1a43 */ { 0x0000, 0x0000, 0x0000 },
/* 1a44 */ { 0x0000, 0x0000, 0x0000 },
/* 1a45 */ { 0x0000, 0x0000, 0x0000 },
/* 1a46 */ { 0x0000, 0x0000, 0x0000 },
/* 1a47 */ { 0x0000, 0x0000, 0x0000 },
/* 1a48 */ { 0x0000, 0x0000, 0x0000 },
/* 1a49 */ { 0x0000, 0x0000, 0x0000 },
/* 1a4a */ { 0x0000, 0x0000, 0x0000 },
/* 1a4b */ { 0x0000, 0x0000, 0x0000 },
/* 1a4c */ { 0x0000, 0x0000, 0x0000 },
/* 1a4d */ { 0x0000, 0x0000, 0x0000 },
/* 1a4e */ { 0x0000, 0x0000, 0x0000 },
/* 1a4f */ { 0x0000, 0x0000, 0x0000 },
/* 1a50 */ { 0x0000, 0x0000, 0x0000 },
/* 1a51 */ { 0x0000, 0x0000, 0x0000 },
/* 1a52 */ { 0x0000, 0x0000, 0x0000 },
/* 1a53 */ { 0x0000, 0x0000, 0x0000 },
/* 1a54 */ { 0x0000, 0x0000, 0x0000 },
/* 1a55 */ { 0x0000, 0x0000, 0x0000 },
/* 1a56 */ { 0x0000, 0x0000, 0x0000 },
/* 1a57 */ { 0x0000, 0x0000, 0x0000 },
/* 1a58 */ { 0x0000, 0x0000, 0x0000 },
/* 1a59 */ { 0x0000, 0x0000, 0x0000 },
/* 1a5a */ { 0x0000, 0x0000, 0x0000 },
/* 1a5b */ { 0x0000, 0x0000, 0x0000 },
/* 1a5c */ { 0x0000, 0x0000, 0x0000 },
/* 1a5d */ { 0x0000, 0x0000, 0x0000 },
/* 1a5e */ { 0x0000, 0x0000, 0x0000 },
/* 1a5f */ { 0x0000, 0x0000, 0x0000 },
/* 1a60 */ { 0x0000, 0x0000, 0x0000 },
/* 1a61 */ { 0x0000, 0x0000, 0x0000 },
/* 1a62 */ { 0x0000, 0x0000, 0x0000 },
/* 1a63 */ { 0x0000, 0x0000, 0x0000 },
/* 1a64 */ { 0x0000, 0x0000, 0x0000 },
/* 1a65 */ { 0x0000, 0x0000, 0x0000 },
/* 1a66 */ { 0x0000, 0x0000, 0x0000 },
/* 1a67 */ { 0x0000, 0x0000, 0x0000 },
/* 1a68 */ { 0x0000, 0x0000, 0x0000 },
/* 1a69 */ { 0x0000, 0x0000, 0x0000 },
/* 1a6a */ { 0x0000, 0x0000, 0x0000 },
/* 1a6b */ { 0x0000, 0x0000, 0x0000 },
/* 1a6c */ { 0x0000, 0x0000, 0x0000 },
/* 1a6d */ { 0x0000, 0x0000, 0x0000 },
/* 1a6e */ { 0x0000, 0x0000, 0x0000 },
/* 1a6f */ { 0x0000, 0x0000, 0x0000 },
/* 1a70 */ { 0x0000, 0x0000, 0x0000 },
/* 1a71 */ { 0x0000, 0x0000, 0x0000 },
/* 1a72 */ { 0x0000, 0x0000, 0x0000 },
/* 1a73 */ { 0x0000, 0x0000, 0x0000 },
/* 1a74 */ { 0x0000, 0x0000, 0x0000 },
/* 1a75 */ { 0x0000, 0x0000, 0x0000 },
/* 1a76 */ { 0x0000, 0x0000, 0x0000 },
/* 1a77 */ { 0x0000, 0x0000, 0x0000 },
/* 1a78 */ { 0x0000, 0x0000, 0x0000 },
/* 1a79 */ { 0x0000, 0x0000, 0x0000 },
/* 1a7a */ { 0x0000, 0x0000, 0x0000 },
/* 1a7b */ { 0x0000, 0x0000, 0x0000 },
/* 1a7c */ { 0x0000, 0x0000, 0x0000 },
/* 1a7d */ { 0x0000, 0x0000, 0x0000 },
/* 1a7e */ { 0x0000, 0x0000, 0x0000 },
/* 1a7f */ { 0x0000, 0x0000, 0x0000 },
/* 1a80 */ { 0x0000, 0x0000, 0x0000 },
/* 1a81 */ { 0x0000, 0x0000, 0x0000 },
/* 1a82 */ { 0x0000, 0x0000, 0x0000 },
/* 1a83 */ { 0x0000, 0x0000, 0x0000 },
/* 1a84 */ { 0x0000, 0x0000, 0x0000 },
/* 1a85 */ { 0x0000, 0x0000, 0x0000 },
/* 1a86 */ { 0x0000, 0x0000, 0x0000 },
/* 1a87 */ { 0x0000, 0x0000, 0x0000 },
/* 1a88 */ { 0x0000, 0x0000, 0x0000 },
/* 1a89 */ { 0x0000, 0x0000, 0x0000 },
/* 1a8a */ { 0x0000, 0x0000, 0x0000 },
/* 1a8b */ { 0x0000, 0x0000, 0x0000 },
/* 1a8c */ { 0x0000, 0x0000, 0x0000 },
/* 1a8d */ { 0x0000, 0x0000, 0x0000 },
/* 1a8e */ { 0x0000, 0x0000, 0x0000 },
/* 1a8f */ { 0x0000, 0x0000, 0x0000 },
/* 1a90 */ { 0x0000, 0x0000, 0x0000 },
/* 1a91 */ { 0x0000, 0x0000, 0x0000 },
/* 1a92 */ { 0x0000, 0x0000, 0x0000 },
/* 1a93 */ { 0x0000, 0x0000, 0x0000 },
/* 1a94 */ { 0x0000, 0x0000, 0x0000 },
/* 1a95 */ { 0x0000, 0x0000, 0x0000 },
/* 1a96 */ { 0x0000, 0x0000, 0x0000 },
/* 1a97 */ { 0x0000, 0x0000, 0x0000 },
/* 1a98 */ { 0x0000, 0x0000, 0x0000 },
/* 1a99 */ { 0x0000, 0x0000, 0x0000 },
/* 1a9a */ { 0x0000, 0x0000, 0x0000 },
/* 1a9b */ { 0x0000, 0x0000, 0x0000 },
/* 1a9c */ { 0x0000, 0x0000, 0x0000 },
/* 1a9d */ { 0x0000, 0x0000, 0x0000 },
/* 1a9e */ { 0x0000, 0x0000, 0x0000 },
/* 1a9f */ { 0x0000, 0x0000, 0x0000 },
/* 1aa0 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa1 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa2 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa3 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa4 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa5 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa6 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa7 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa8 */ { 0x0000, 0x0000, 0x0000 },
/* 1aa9 */ { 0x0000, 0x0000, 0x0000 },
/* 1aaa */ { 0x0000, 0x0000, 0x0000 },
/* 1aab */ { 0x0000, 0x0000, 0x0000 },
/* 1aac */ { 0x0000, 0x0000, 0x0000 },
/* 1aad */ { 0x0000, 0x0000, 0x0000 },
/* 1aae */ { 0x0000, 0x0000, 0x0000 },
/* 1aaf */ { 0x0000, 0x0000, 0x0000 },
/* 1ab0 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab1 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab2 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab3 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab4 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab5 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab6 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab7 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab8 */ { 0x0000, 0x0000, 0x0000 },
/* 1ab9 */ { 0x0000, 0x0000, 0x0000 },
/* 1aba */ { 0x0000, 0x0000, 0x0000 },
/* 1abb */ { 0x0000, 0x0000, 0x0000 },
/* 1abc */ { 0x0000, 0x0000, 0x0000 },
/* 1abd */ { 0x0000, 0x0000, 0x0000 },
/* 1abe */ { 0x0000, 0x0000, 0x0000 },
/* 1abf */ { 0x0000, 0x0000, 0x0000 },
/* 1ac0 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac1 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac2 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac3 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac4 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac5 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac6 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac7 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac8 */ { 0x0000, 0x0000, 0x0000 },
/* 1ac9 */ { 0x0000, 0x0000, 0x0000 },
/* 1aca */ { 0x0000, 0x0000, 0x0000 },
/* 1acb */ { 0x0000, 0x0000, 0x0000 },
/* 1acc */ { 0x0000, 0x0000, 0x0000 },
/* 1acd */ { 0x0000, 0x0000, 0x0000 },
/* 1ace */ { 0x0000, 0x0000, 0x0000 },
/* 1acf */ { 0x0000, 0x0000, 0x0000 },
/* 1ad0 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad1 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad2 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad3 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad4 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad5 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad6 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad7 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad8 */ { 0x0000, 0x0000, 0x0000 },
/* 1ad9 */ { 0x0000, 0x0000, 0x0000 },
/* 1ada */ { 0x0000, 0x0000, 0x0000 },
/* 1adb */ { 0x0000, 0x0000, 0x0000 },
/* 1adc */ { 0x0000, 0x0000, 0x0000 },
/* 1add */ { 0x0000, 0x0000, 0x0000 },
/* 1ade */ { 0x0000, 0x0000, 0x0000 },
/* 1adf */ { 0x0000, 0x0000, 0x0000 },
/* 1ae0 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae1 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae2 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae3 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae4 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae5 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae6 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae7 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae8 */ { 0x0000, 0x0000, 0x0000 },
/* 1ae9 */ { 0x0000, 0x0000, 0x0000 },
/* 1aea */ { 0x0000, 0x0000, 0x0000 },
/* 1aeb */ { 0x0000, 0x0000, 0x0000 },
/* 1aec */ { 0x0000, 0x0000, 0x0000 },
/* 1aed */ { 0x0000, 0x0000, 0x0000 },
/* 1aee */ { 0x0000, 0x0000, 0x0000 },
/* 1aef */ { 0x0000, 0x0000, 0x0000 },
/* 1af0 */ { 0x0000, 0x0000, 0x0000 },
/* 1af1 */ { 0x0000, 0x0000, 0x0000 },
/* 1af2 */ { 0x0000, 0x0000, 0x0000 },
/* 1af3 */ { 0x0000, 0x0000, 0x0000 },
/* 1af4 */ { 0x0000, 0x0000, 0x0000 },
/* 1af5 */ { 0x0000, 0x0000, 0x0000 },
/* 1af6 */ { 0x0000, 0x0000, 0x0000 },
/* 1af7 */ { 0x0000, 0x0000, 0x0000 },
/* 1af8 */ { 0x0000, 0x0000, 0x0000 },
/* 1af9 */ { 0x0000, 0x0000, 0x0000 },
/* 1afa */ { 0x0000, 0x0000, 0x0000 },
/* 1afb */ { 0x0000, 0x0000, 0x0000 },
/* 1afc */ { 0x0000, 0x0000, 0x0000 },
/* 1afd */ { 0x0000, 0x0000, 0x0000 },
/* 1afe */ { 0x0000, 0x0000, 0x0000 },
/* 1aff */ { 0x0000, 0x0000, 0x0000 },
/* 1b00 */ { 0x0000, 0x0000, 0x0000 },
/* 1b01 */ { 0x0000, 0x0000, 0x0000 },
/* 1b02 */ { 0x0000, 0x0000, 0x0000 },
/* 1b03 */ { 0x0000, 0x0000, 0x0000 },
/* 1b04 */ { 0x0000, 0x0000, 0x0000 },
/* 1b05 */ { 0x0000, 0x0000, 0x0000 },
/* 1b06 */ { 0x0000, 0x0000, 0x0000 },
/* 1b07 */ { 0x0000, 0x0000, 0x0000 },
/* 1b08 */ { 0x0000, 0x0000, 0x0000 },
/* 1b09 */ { 0x0000, 0x0000, 0x0000 },
/* 1b0a */ { 0x0000, 0x0000, 0x0000 },
/* 1b0b */ { 0x0000, 0x0000, 0x0000 },
/* 1b0c */ { 0x0000, 0x0000, 0x0000 },
/* 1b0d */ { 0x0000, 0x0000, 0x0000 },
/* 1b0e */ { 0x0000, 0x0000, 0x0000 },
/* 1b0f */ { 0x0000, 0x0000, 0x0000 },
/* 1b10 */ { 0x0000, 0x0000, 0x0000 },
/* 1b11 */ { 0x0000, 0x0000, 0x0000 },
/* 1b12 */ { 0x0000, 0x0000, 0x0000 },
/* 1b13 */ { 0x0000, 0x0000, 0x0000 },
/* 1b14 */ { 0x0000, 0x0000, 0x0000 },
/* 1b15 */ { 0x0000, 0x0000, 0x0000 },
/* 1b16 */ { 0x0000, 0x0000, 0x0000 },
/* 1b17 */ { 0x0000, 0x0000, 0x0000 },
/* 1b18 */ { 0x0000, 0x0000, 0x0000 },
/* 1b19 */ { 0x0000, 0x0000, 0x0000 },
/* 1b1a */ { 0x0000, 0x0000, 0x0000 },
/* 1b1b */ { 0x0000, 0x0000, 0x0000 },
/* 1b1c */ { 0x0000, 0x0000, 0x0000 },
/* 1b1d */ { 0x0000, 0x0000, 0x0000 },
/* 1b1e */ { 0x0000, 0x0000, 0x0000 },
/* 1b1f */ { 0x0000, 0x0000, 0x0000 },
/* 1b20 */ { 0x0000, 0x0000, 0x0000 },
/* 1b21 */ { 0x0000, 0x0000, 0x0000 },
/* 1b22 */ { 0x0000, 0x0000, 0x0000 },
/* 1b23 */ { 0x0000, 0x0000, 0x0000 },
/* 1b24 */ { 0x0000, 0x0000, 0x0000 },
/* 1b25 */ { 0x0000, 0x0000, 0x0000 },
/* 1b26 */ { 0x0000, 0x0000, 0x0000 },
/* 1b27 */ { 0x0000, 0x0000, 0x0000 },
/* 1b28 */ { 0x0000, 0x0000, 0x0000 },
/* 1b29 */ { 0x0000, 0x0000, 0x0000 },
/* 1b2a */ { 0x0000, 0x0000, 0x0000 },
/* 1b2b */ { 0x0000, 0x0000, 0x0000 },
/* 1b2c */ { 0x0000, 0x0000, 0x0000 },
/* 1b2d */ { 0x0000, 0x0000, 0x0000 },
/* 1b2e */ { 0x0000, 0x0000, 0x0000 },
/* 1b2f */ { 0x0000, 0x0000, 0x0000 },
/* 1b30 */ { 0x0000, 0x0000, 0x0000 },
/* 1b31 */ { 0x0000, 0x0000, 0x0000 },
/* 1b32 */ { 0x0000, 0x0000, 0x0000 },
/* 1b33 */ { 0x0000, 0x0000, 0x0000 },
/* 1b34 */ { 0x0000, 0x0000, 0x0000 },
/* 1b35 */ { 0x0000, 0x0000, 0x0000 },
/* 1b36 */ { 0x0000, 0x0000, 0x0000 },
/* 1b37 */ { 0x0000, 0x0000, 0x0000 },
/* 1b38 */ { 0x0000, 0x0000, 0x0000 },
/* 1b39 */ { 0x0000, 0x0000, 0x0000 },
/* 1b3a */ { 0x0000, 0x0000, 0x0000 },
/* 1b3b */ { 0x0000, 0x0000, 0x0000 },
/* 1b3c */ { 0x0000, 0x0000, 0x0000 },
/* 1b3d */ { 0x0000, 0x0000, 0x0000 },
/* 1b3e */ { 0x0000, 0x0000, 0x0000 },
/* 1b3f */ { 0x0000, 0x0000, 0x0000 },
/* 1b40 */ { 0x0000, 0x0000, 0x0000 },
/* 1b41 */ { 0x0000, 0x0000, 0x0000 },
/* 1b42 */ { 0x0000, 0x0000, 0x0000 },
/* 1b43 */ { 0x0000, 0x0000, 0x0000 },
/* 1b44 */ { 0x0000, 0x0000, 0x0000 },
/* 1b45 */ { 0x0000, 0x0000, 0x0000 },
/* 1b46 */ { 0x0000, 0x0000, 0x0000 },
/* 1b47 */ { 0x0000, 0x0000, 0x0000 },
/* 1b48 */ { 0x0000, 0x0000, 0x0000 },
/* 1b49 */ { 0x0000, 0x0000, 0x0000 },
/* 1b4a */ { 0x0000, 0x0000, 0x0000 },
/* 1b4b */ { 0x0000, 0x0000, 0x0000 },
/* 1b4c */ { 0x0000, 0x0000, 0x0000 },
/* 1b4d */ { 0x0000, 0x0000, 0x0000 },
/* 1b4e */ { 0x0000, 0x0000, 0x0000 },
/* 1b4f */ { 0x0000, 0x0000, 0x0000 },
/* 1b50 */ { 0x0000, 0x0000, 0x0000 },
/* 1b51 */ { 0x0000, 0x0000, 0x0000 },
/* 1b52 */ { 0x0000, 0x0000, 0x0000 },
/* 1b53 */ { 0x0000, 0x0000, 0x0000 },
/* 1b54 */ { 0x0000, 0x0000, 0x0000 },
/* 1b55 */ { 0x0000, 0x0000, 0x0000 },
/* 1b56 */ { 0x0000, 0x0000, 0x0000 },
/* 1b57 */ { 0x0000, 0x0000, 0x0000 },
/* 1b58 */ { 0x0000, 0x0000, 0x0000 },
/* 1b59 */ { 0x0000, 0x0000, 0x0000 },
/* 1b5a */ { 0x0000, 0x0000, 0x0000 },
/* 1b5b */ { 0x0000, 0x0000, 0x0000 },
/* 1b5c */ { 0x0000, 0x0000, 0x0000 },
/* 1b5d */ { 0x0000, 0x0000, 0x0000 },
/* 1b5e */ { 0x0000, 0x0000, 0x0000 },
/* 1b5f */ { 0x0000, 0x0000, 0x0000 },
/* 1b60 */ { 0x0000, 0x0000, 0x0000 },
/* 1b61 */ { 0x0000, 0x0000, 0x0000 },
/* 1b62 */ { 0x0000, 0x0000, 0x0000 },
/* 1b63 */ { 0x0000, 0x0000, 0x0000 },
/* 1b64 */ { 0x0000, 0x0000, 0x0000 },
/* 1b65 */ { 0x0000, 0x0000, 0x0000 },
/* 1b66 */ { 0x0000, 0x0000, 0x0000 },
/* 1b67 */ { 0x0000, 0x0000, 0x0000 },
/* 1b68 */ { 0x0000, 0x0000, 0x0000 },
/* 1b69 */ { 0x0000, 0x0000, 0x0000 },
/* 1b6a */ { 0x0000, 0x0000, 0x0000 },
/* 1b6b */ { 0x0000, 0x0000, 0x0000 },
/* 1b6c */ { 0x0000, 0x0000, 0x0000 },
/* 1b6d */ { 0x0000, 0x0000, 0x0000 },
/* 1b6e */ { 0x0000, 0x0000, 0x0000 },
/* 1b6f */ { 0x0000, 0x0000, 0x0000 },
/* 1b70 */ { 0x0000, 0x0000, 0x0000 },
/* 1b71 */ { 0x0000, 0x0000, 0x0000 },
/* 1b72 */ { 0x0000, 0x0000, 0x0000 },
/* 1b73 */ { 0x0000, 0x0000, 0x0000 },
/* 1b74 */ { 0x0000, 0x0000, 0x0000 },
/* 1b75 */ { 0x0000, 0x0000, 0x0000 },
/* 1b76 */ { 0x0000, 0x0000, 0x0000 },
/* 1b77 */ { 0x0000, 0x0000, 0x0000 },
/* 1b78 */ { 0x0000, 0x0000, 0x0000 },
/* 1b79 */ { 0x0000, 0x0000, 0x0000 },
/* 1b7a */ { 0x0000, 0x0000, 0x0000 },
/* 1b7b */ { 0x0000, 0x0000, 0x0000 },
/* 1b7c */ { 0x0000, 0x0000, 0x0000 },
/* 1b7d */ { 0x0000, 0x0000, 0x0000 },
/* 1b7e */ { 0x0000, 0x0000, 0x0000 },
/* 1b7f */ { 0x0000, 0x0000, 0x0000 },
/* 1b80 */ { 0x0000, 0x0000, 0x0000 },
/* 1b81 */ { 0x0000, 0x0000, 0x0000 },
/* 1b82 */ { 0x0000, 0x0000, 0x0000 },
/* 1b83 */ { 0x0000, 0x0000, 0x0000 },
/* 1b84 */ { 0x0000, 0x0000, 0x0000 },
/* 1b85 */ { 0x0000, 0x0000, 0x0000 },
/* 1b86 */ { 0x0000, 0x0000, 0x0000 },
/* 1b87 */ { 0x0000, 0x0000, 0x0000 },
/* 1b88 */ { 0x0000, 0x0000, 0x0000 },
/* 1b89 */ { 0x0000, 0x0000, 0x0000 },
/* 1b8a */ { 0x0000, 0x0000, 0x0000 },
/* 1b8b */ { 0x0000, 0x0000, 0x0000 },
/* 1b8c */ { 0x0000, 0x0000, 0x0000 },
/* 1b8d */ { 0x0000, 0x0000, 0x0000 },
/* 1b8e */ { 0x0000, 0x0000, 0x0000 },
/* 1b8f */ { 0x0000, 0x0000, 0x0000 },
/* 1b90 */ { 0x0000, 0x0000, 0x0000 },
/* 1b91 */ { 0x0000, 0x0000, 0x0000 },
/* 1b92 */ { 0x0000, 0x0000, 0x0000 },
/* 1b93 */ { 0x0000, 0x0000, 0x0000 },
/* 1b94 */ { 0x0000, 0x0000, 0x0000 },
/* 1b95 */ { 0x0000, 0x0000, 0x0000 },
/* 1b96 */ { 0x0000, 0x0000, 0x0000 },
/* 1b97 */ { 0x0000, 0x0000, 0x0000 },
/* 1b98 */ { 0x0000, 0x0000, 0x0000 },
/* 1b99 */ { 0x0000, 0x0000, 0x0000 },
/* 1b9a */ { 0x0000, 0x0000, 0x0000 },
/* 1b9b */ { 0x0000, 0x0000, 0x0000 },
/* 1b9c */ { 0x0000, 0x0000, 0x0000 },
/* 1b9d */ { 0x0000, 0x0000, 0x0000 },
/* 1b9e */ { 0x0000, 0x0000, 0x0000 },
/* 1b9f */ { 0x0000, 0x0000, 0x0000 },
/* 1ba0 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba1 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba2 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba3 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba4 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba5 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba6 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba7 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba8 */ { 0x0000, 0x0000, 0x0000 },
/* 1ba9 */ { 0x0000, 0x0000, 0x0000 },
/* 1baa */ { 0x0000, 0x0000, 0x0000 },
/* 1bab */ { 0x0000, 0x0000, 0x0000 },
/* 1bac */ { 0x0000, 0x0000, 0x0000 },
/* 1bad */ { 0x0000, 0x0000, 0x0000 },
/* 1bae */ { 0x0000, 0x0000, 0x0000 },
/* 1baf */ { 0x0000, 0x0000, 0x0000 },
/* 1bb0 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb1 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb2 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb3 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb4 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb5 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb6 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb7 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb8 */ { 0x0000, 0x0000, 0x0000 },
/* 1bb9 */ { 0x0000, 0x0000, 0x0000 },
/* 1bba */ { 0x0000, 0x0000, 0x0000 },
/* 1bbb */ { 0x0000, 0x0000, 0x0000 },
/* 1bbc */ { 0x0000, 0x0000, 0x0000 },
/* 1bbd */ { 0x0000, 0x0000, 0x0000 },
/* 1bbe */ { 0x0000, 0x0000, 0x0000 },
/* 1bbf */ { 0x0000, 0x0000, 0x0000 },
/* 1bc0 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc1 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc2 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc3 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc4 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc5 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc6 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc7 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc8 */ { 0x0000, 0x0000, 0x0000 },
/* 1bc9 */ { 0x0000, 0x0000, 0x0000 },
/* 1bca */ { 0x0000, 0x0000, 0x0000 },
/* 1bcb */ { 0x0000, 0x0000, 0x0000 },
/* 1bcc */ { 0x0000, 0x0000, 0x0000 },
/* 1bcd */ { 0x0000, 0x0000, 0x0000 },
/* 1bce */ { 0x0000, 0x0000, 0x0000 },
/* 1bcf */ { 0x0000, 0x0000, 0x0000 },
/* 1bd0 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd1 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd2 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd3 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd4 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd5 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd6 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd7 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd8 */ { 0x0000, 0x0000, 0x0000 },
/* 1bd9 */ { 0x0000, 0x0000, 0x0000 },
/* 1bda */ { 0x0000, 0x0000, 0x0000 },
/* 1bdb */ { 0x0000, 0x0000, 0x0000 },
/* 1bdc */ { 0x0000, 0x0000, 0x0000 },
/* 1bdd */ { 0x0000, 0x0000, 0x0000 },
/* 1bde */ { 0x0000, 0x0000, 0x0000 },
/* 1bdf */ { 0x0000, 0x0000, 0x0000 },
/* 1be0 */ { 0x0000, 0x0000, 0x0000 },
/* 1be1 */ { 0x0000, 0x0000, 0x0000 },
/* 1be2 */ { 0x0000, 0x0000, 0x0000 },
/* 1be3 */ { 0x0000, 0x0000, 0x0000 },
/* 1be4 */ { 0x0000, 0x0000, 0x0000 },
/* 1be5 */ { 0x0000, 0x0000, 0x0000 },
/* 1be6 */ { 0x0000, 0x0000, 0x0000 },
/* 1be7 */ { 0x0000, 0x0000, 0x0000 },
/* 1be8 */ { 0x0000, 0x0000, 0x0000 },
/* 1be9 */ { 0x0000, 0x0000, 0x0000 },
/* 1bea */ { 0x0000, 0x0000, 0x0000 },
/* 1beb */ { 0x0000, 0x0000, 0x0000 },
/* 1bec */ { 0x0000, 0x0000, 0x0000 },
/* 1bed */ { 0x0000, 0x0000, 0x0000 },
/* 1bee */ { 0x0000, 0x0000, 0x0000 },
/* 1bef */ { 0x0000, 0x0000, 0x0000 },
/* 1bf0 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf1 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf2 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf3 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf4 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf5 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf6 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf7 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf8 */ { 0x0000, 0x0000, 0x0000 },
/* 1bf9 */ { 0x0000, 0x0000, 0x0000 },
/* 1bfa */ { 0x0000, 0x0000, 0x0000 },
/* 1bfb */ { 0x0000, 0x0000, 0x0000 },
/* 1bfc */ { 0x0000, 0x0000, 0x0000 },
/* 1bfd */ { 0x0000, 0x0000, 0x0000 },
/* 1bfe */ { 0x0000, 0x0000, 0x0000 },
/* 1bff */ { 0x0000, 0x0000, 0x0000 },
/* 1c00 */ { 0x0000, 0x0000, 0x0000 },
/* 1c01 */ { 0x0000, 0x0000, 0x0000 },
/* 1c02 */ { 0x0000, 0x0000, 0x0000 },
/* 1c03 */ { 0x0000, 0x0000, 0x0000 },
/* 1c04 */ { 0x0000, 0x0000, 0x0000 },
/* 1c05 */ { 0x0000, 0x0000, 0x0000 },
/* 1c06 */ { 0x0000, 0x0000, 0x0000 },
/* 1c07 */ { 0x0000, 0x0000, 0x0000 },
/* 1c08 */ { 0x0000, 0x0000, 0x0000 },
/* 1c09 */ { 0x0000, 0x0000, 0x0000 },
/* 1c0a */ { 0x0000, 0x0000, 0x0000 },
/* 1c0b */ { 0x0000, 0x0000, 0x0000 },
/* 1c0c */ { 0x0000, 0x0000, 0x0000 },
/* 1c0d */ { 0x0000, 0x0000, 0x0000 },
/* 1c0e */ { 0x0000, 0x0000, 0x0000 },
/* 1c0f */ { 0x0000, 0x0000, 0x0000 },
/* 1c10 */ { 0x0000, 0x0000, 0x0000 },
/* 1c11 */ { 0x0000, 0x0000, 0x0000 },
/* 1c12 */ { 0x0000, 0x0000, 0x0000 },
/* 1c13 */ { 0x0000, 0x0000, 0x0000 },
/* 1c14 */ { 0x0000, 0x0000, 0x0000 },
/* 1c15 */ { 0x0000, 0x0000, 0x0000 },
/* 1c16 */ { 0x0000, 0x0000, 0x0000 },
/* 1c17 */ { 0x0000, 0x0000, 0x0000 },
/* 1c18 */ { 0x0000, 0x0000, 0x0000 },
/* 1c19 */ { 0x0000, 0x0000, 0x0000 },
/* 1c1a */ { 0x0000, 0x0000, 0x0000 },
/* 1c1b */ { 0x0000, 0x0000, 0x0000 },
/* 1c1c */ { 0x0000, 0x0000, 0x0000 },
/* 1c1d */ { 0x0000, 0x0000, 0x0000 },
/* 1c1e */ { 0x0000, 0x0000, 0x0000 },
/* 1c1f */ { 0x0000, 0x0000, 0x0000 },
/* 1c20 */ { 0x0000, 0x0000, 0x0000 },
/* 1c21 */ { 0x0000, 0x0000, 0x0000 },
/* 1c22 */ { 0x0000, 0x0000, 0x0000 },
/* 1c23 */ { 0x0000, 0x0000, 0x0000 },
/* 1c24 */ { 0x0000, 0x0000, 0x0000 },
/* 1c25 */ { 0x0000, 0x0000, 0x0000 },
/* 1c26 */ { 0x0000, 0x0000, 0x0000 },
/* 1c27 */ { 0x0000, 0x0000, 0x0000 },
/* 1c28 */ { 0x0000, 0x0000, 0x0000 },
/* 1c29 */ { 0x0000, 0x0000, 0x0000 },
/* 1c2a */ { 0x0000, 0x0000, 0x0000 },
/* 1c2b */ { 0x0000, 0x0000, 0x0000 },
/* 1c2c */ { 0x0000, 0x0000, 0x0000 },
/* 1c2d */ { 0x0000, 0x0000, 0x0000 },
/* 1c2e */ { 0x0000, 0x0000, 0x0000 },
/* 1c2f */ { 0x0000, 0x0000, 0x0000 },
/* 1c30 */ { 0x0000, 0x0000, 0x0000 },
/* 1c31 */ { 0x0000, 0x0000, 0x0000 },
/* 1c32 */ { 0x0000, 0x0000, 0x0000 },
/* 1c33 */ { 0x0000, 0x0000, 0x0000 },
/* 1c34 */ { 0x0000, 0x0000, 0x0000 },
/* 1c35 */ { 0x0000, 0x0000, 0x0000 },
/* 1c36 */ { 0x0000, 0x0000, 0x0000 },
/* 1c37 */ { 0x0000, 0x0000, 0x0000 },
/* 1c38 */ { 0x0000, 0x0000, 0x0000 },
/* 1c39 */ { 0x0000, 0x0000, 0x0000 },
/* 1c3a */ { 0x0000, 0x0000, 0x0000 },
/* 1c3b */ { 0x0000, 0x0000, 0x0000 },
/* 1c3c */ { 0x0000, 0x0000, 0x0000 },
/* 1c3d */ { 0x0000, 0x0000, 0x0000 },
/* 1c3e */ { 0x0000, 0x0000, 0x0000 },
/* 1c3f */ { 0x0000, 0x0000, 0x0000 },
/* 1c40 */ { 0x0000, 0x0000, 0x0000 },
/* 1c41 */ { 0x0000, 0x0000, 0x0000 },
/* 1c42 */ { 0x0000, 0x0000, 0x0000 },
/* 1c43 */ { 0x0000, 0x0000, 0x0000 },
/* 1c44 */ { 0x0000, 0x0000, 0x0000 },
/* 1c45 */ { 0x0000, 0x0000, 0x0000 },
/* 1c46 */ { 0x0000, 0x0000, 0x0000 },
/* 1c47 */ { 0x0000, 0x0000, 0x0000 },
/* 1c48 */ { 0x0000, 0x0000, 0x0000 },
/* 1c49 */ { 0x0000, 0x0000, 0x0000 },
/* 1c4a */ { 0x0000, 0x0000, 0x0000 },
/* 1c4b */ { 0x0000, 0x0000, 0x0000 },
/* 1c4c */ { 0x0000, 0x0000, 0x0000 },
/* 1c4d */ { 0x0000, 0x0000, 0x0000 },
/* 1c4e */ { 0x0000, 0x0000, 0x0000 },
/* 1c4f */ { 0x0000, 0x0000, 0x0000 },
/* 1c50 */ { 0x0000, 0x0000, 0x0000 },
/* 1c51 */ { 0x0000, 0x0000, 0x0000 },
/* 1c52 */ { 0x0000, 0x0000, 0x0000 },
/* 1c53 */ { 0x0000, 0x0000, 0x0000 },
/* 1c54 */ { 0x0000, 0x0000, 0x0000 },
/* 1c55 */ { 0x0000, 0x0000, 0x0000 },
/* 1c56 */ { 0x0000, 0x0000, 0x0000 },
/* 1c57 */ { 0x0000, 0x0000, 0x0000 },
/* 1c58 */ { 0x0000, 0x0000, 0x0000 },
/* 1c59 */ { 0x0000, 0x0000, 0x0000 },
/* 1c5a */ { 0x0000, 0x0000, 0x0000 },
/* 1c5b */ { 0x0000, 0x0000, 0x0000 },
/* 1c5c */ { 0x0000, 0x0000, 0x0000 },
/* 1c5d */ { 0x0000, 0x0000, 0x0000 },
/* 1c5e */ { 0x0000, 0x0000, 0x0000 },
/* 1c5f */ { 0x0000, 0x0000, 0x0000 },
/* 1c60 */ { 0x0000, 0x0000, 0x0000 },
/* 1c61 */ { 0x0000, 0x0000, 0x0000 },
/* 1c62 */ { 0x0000, 0x0000, 0x0000 },
/* 1c63 */ { 0x0000, 0x0000, 0x0000 },
/* 1c64 */ { 0x0000, 0x0000, 0x0000 },
/* 1c65 */ { 0x0000, 0x0000, 0x0000 },
/* 1c66 */ { 0x0000, 0x0000, 0x0000 },
/* 1c67 */ { 0x0000, 0x0000, 0x0000 },
/* 1c68 */ { 0x0000, 0x0000, 0x0000 },
/* 1c69 */ { 0x0000, 0x0000, 0x0000 },
/* 1c6a */ { 0x0000, 0x0000, 0x0000 },
/* 1c6b */ { 0x0000, 0x0000, 0x0000 },
/* 1c6c */ { 0x0000, 0x0000, 0x0000 },
/* 1c6d */ { 0x0000, 0x0000, 0x0000 },
/* 1c6e */ { 0x0000, 0x0000, 0x0000 },
/* 1c6f */ { 0x0000, 0x0000, 0x0000 },
/* 1c70 */ { 0x0000, 0x0000, 0x0000 },
/* 1c71 */ { 0x0000, 0x0000, 0x0000 },
/* 1c72 */ { 0x0000, 0x0000, 0x0000 },
/* 1c73 */ { 0x0000, 0x0000, 0x0000 },
/* 1c74 */ { 0x0000, 0x0000, 0x0000 },
/* 1c75 */ { 0x0000, 0x0000, 0x0000 },
/* 1c76 */ { 0x0000, 0x0000, 0x0000 },
/* 1c77 */ { 0x0000, 0x0000, 0x0000 },
/* 1c78 */ { 0x0000, 0x0000, 0x0000 },
/* 1c79 */ { 0x0000, 0x0000, 0x0000 },
/* 1c7a */ { 0x0000, 0x0000, 0x0000 },
/* 1c7b */ { 0x0000, 0x0000, 0x0000 },
/* 1c7c */ { 0x0000, 0x0000, 0x0000 },
/* 1c7d */ { 0x0000, 0x0000, 0x0000 },
/* 1c7e */ { 0x0000, 0x0000, 0x0000 },
/* 1c7f */ { 0x0000, 0x0000, 0x0000 },
/* 1c80 */ { 0x0000, 0x0000, 0x0000 },
/* 1c81 */ { 0x0000, 0x0000, 0x0000 },
/* 1c82 */ { 0x0000, 0x0000, 0x0000 },
/* 1c83 */ { 0x0000, 0x0000, 0x0000 },
/* 1c84 */ { 0x0000, 0x0000, 0x0000 },
/* 1c85 */ { 0x0000, 0x0000, 0x0000 },
/* 1c86 */ { 0x0000, 0x0000, 0x0000 },
/* 1c87 */ { 0x0000, 0x0000, 0x0000 },
/* 1c88 */ { 0x0000, 0x0000, 0x0000 },
/* 1c89 */ { 0x0000, 0x0000, 0x0000 },
/* 1c8a */ { 0x0000, 0x0000, 0x0000 },
/* 1c8b */ { 0x0000, 0x0000, 0x0000 },
/* 1c8c */ { 0x0000, 0x0000, 0x0000 },
/* 1c8d */ { 0x0000, 0x0000, 0x0000 },
/* 1c8e */ { 0x0000, 0x0000, 0x0000 },
/* 1c8f */ { 0x0000, 0x0000, 0x0000 },
/* 1c90 */ { 0x0000, 0x0000, 0x0000 },
/* 1c91 */ { 0x0000, 0x0000, 0x0000 },
/* 1c92 */ { 0x0000, 0x0000, 0x0000 },
/* 1c93 */ { 0x0000, 0x0000, 0x0000 },
/* 1c94 */ { 0x0000, 0x0000, 0x0000 },
/* 1c95 */ { 0x0000, 0x0000, 0x0000 },
/* 1c96 */ { 0x0000, 0x0000, 0x0000 },
/* 1c97 */ { 0x0000, 0x0000, 0x0000 },
/* 1c98 */ { 0x0000, 0x0000, 0x0000 },
/* 1c99 */ { 0x0000, 0x0000, 0x0000 },
/* 1c9a */ { 0x0000, 0x0000, 0x0000 },
/* 1c9b */ { 0x0000, 0x0000, 0x0000 },
/* 1c9c */ { 0x0000, 0x0000, 0x0000 },
/* 1c9d */ { 0x0000, 0x0000, 0x0000 },
/* 1c9e */ { 0x0000, 0x0000, 0x0000 },
/* 1c9f */ { 0x0000, 0x0000, 0x0000 },
/* 1ca0 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca1 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca2 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca3 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca4 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca5 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca6 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca7 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca8 */ { 0x0000, 0x0000, 0x0000 },
/* 1ca9 */ { 0x0000, 0x0000, 0x0000 },
/* 1caa */ { 0x0000, 0x0000, 0x0000 },
/* 1cab */ { 0x0000, 0x0000, 0x0000 },
/* 1cac */ { 0x0000, 0x0000, 0x0000 },
/* 1cad */ { 0x0000, 0x0000, 0x0000 },
/* 1cae */ { 0x0000, 0x0000, 0x0000 },
/* 1caf */ { 0x0000, 0x0000, 0x0000 },
/* 1cb0 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb1 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb2 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb3 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb4 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb5 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb6 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb7 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb8 */ { 0x0000, 0x0000, 0x0000 },
/* 1cb9 */ { 0x0000, 0x0000, 0x0000 },
/* 1cba */ { 0x0000, 0x0000, 0x0000 },
/* 1cbb */ { 0x0000, 0x0000, 0x0000 },
/* 1cbc */ { 0x0000, 0x0000, 0x0000 },
/* 1cbd */ { 0x0000, 0x0000, 0x0000 },
/* 1cbe */ { 0x0000, 0x0000, 0x0000 },
/* 1cbf */ { 0x0000, 0x0000, 0x0000 },
/* 1cc0 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc1 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc2 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc3 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc4 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc5 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc6 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc7 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc8 */ { 0x0000, 0x0000, 0x0000 },
/* 1cc9 */ { 0x0000, 0x0000, 0x0000 },
/* 1cca */ { 0x0000, 0x0000, 0x0000 },
/* 1ccb */ { 0x0000, 0x0000, 0x0000 },
/* 1ccc */ { 0x0000, 0x0000, 0x0000 },
/* 1ccd */ { 0x0000, 0x0000, 0x0000 },
/* 1cce */ { 0x0000, 0x0000, 0x0000 },
/* 1ccf */ { 0x0000, 0x0000, 0x0000 },
/* 1cd0 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd1 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd2 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd3 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd4 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd5 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd6 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd7 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd8 */ { 0x0000, 0x0000, 0x0000 },
/* 1cd9 */ { 0x0000, 0x0000, 0x0000 },
/* 1cda */ { 0x0000, 0x0000, 0x0000 },
/* 1cdb */ { 0x0000, 0x0000, 0x0000 },
/* 1cdc */ { 0x0000, 0x0000, 0x0000 },
/* 1cdd */ { 0x0000, 0x0000, 0x0000 },
/* 1cde */ { 0x0000, 0x0000, 0x0000 },
/* 1cdf */ { 0x0000, 0x0000, 0x0000 },
/* 1ce0 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce1 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce2 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce3 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce4 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce5 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce6 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce7 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce8 */ { 0x0000, 0x0000, 0x0000 },
/* 1ce9 */ { 0x0000, 0x0000, 0x0000 },
/* 1cea */ { 0x0000, 0x0000, 0x0000 },
/* 1ceb */ { 0x0000, 0x0000, 0x0000 },
/* 1cec */ { 0x0000, 0x0000, 0x0000 },
/* 1ced */ { 0x0000, 0x0000, 0x0000 },
/* 1cee */ { 0x0000, 0x0000, 0x0000 },
/* 1cef */ { 0x0000, 0x0000, 0x0000 },
/* 1cf0 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf1 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf2 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf3 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf4 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf5 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf6 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf7 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf8 */ { 0x0000, 0x0000, 0x0000 },
/* 1cf9 */ { 0x0000, 0x0000, 0x0000 },
/* 1cfa */ { 0x0000, 0x0000, 0x0000 },
/* 1cfb */ { 0x0000, 0x0000, 0x0000 },
/* 1cfc */ { 0x0000, 0x0000, 0x0000 },
/* 1cfd */ { 0x0000, 0x0000, 0x0000 },
/* 1cfe */ { 0x0000, 0x0000, 0x0000 },
/* 1cff */ { 0x0000, 0x0000, 0x0000 },
/* 1D00 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL A 
/* 1D01 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL AE 
/* 1D02 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED AE 
/* 1D03 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL BARRED B 
/* 1D04 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL C 
/* 1D05 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL D 
/* 1D06 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL ETH 
/* 1D07 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL E 
/* 1D08 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED OPEN E 
/* 1D09 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED I 
/* 1D0A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL J 
/* 1D0B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL K 
/* 1D0C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL L WITH STROKE 
/* 1D0D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL M 
/* 1D0E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL REVERSED N 
/* 1D0F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL O 
/* 1D10 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL OPEN O 
/* 1D11 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SIDEWAYS O 
/* 1D12 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SIDEWAYS OPEN O 
/* 1D13 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SIDEWAYS O WITH STROKE 
/* 1D14 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED OE 
/* 1D15 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL OU 
/* 1D16 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TOP HALF O 
/* 1D17 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER BOTTOM HALF O 
/* 1D18 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL P 
/* 1D19 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL REVERSED R 
/* 1D1A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL TURNED R 
/* 1D1B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL T 
/* 1D1C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL U 
/* 1D1D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SIDEWAYS U 
/* 1D1E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SIDEWAYS DIAERESIZED U 
/* 1D1F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SIDEWAYS TURNED M 
/* 1D20 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL V 
/* 1D21 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL W 
/* 1D22 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL Z 
/* 1D23 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER SMALL CAPITAL EZH 
/* 1D24 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER VOICED LARYNGEAL SPIRANT 
/* 1D25 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN LETTER AIN 
/* 1D26 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER SMALL CAPITAL GAMMA 
/* 1D27 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER SMALL CAPITAL LAMDA 
/* 1D28 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER SMALL CAPITAL PI 
/* 1D29 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER SMALL CAPITAL RHO 
/* 1D2A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK LETTER SMALL CAPITAL PSI 
/* 1D2B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CYRILLIC LETTER SMALL CAPITAL EL 
/* 1D2C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL A 
/* 1D2D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL AE 
/* 1D2E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL B 
/* 1D2F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL BARRED B 
/* 1D30 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL D 
/* 1D31 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL E 
/* 1D32 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL REVERSED E 
/* 1D33 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL G 
/* 1D34 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL H 
/* 1D35 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL I 
/* 1D36 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL J 
/* 1D37 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL K 
/* 1D38 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL L 
/* 1D39 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL M 
/* 1D3A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL N 
/* 1D3B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL REVERSED N 
/* 1D3C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL O 
/* 1D3D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL OU 
/* 1D3E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL P 
/* 1D3F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL R 
/* 1D40 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL T 
/* 1D41 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL U 
/* 1D42 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CAPITAL W 
/* 1D43 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL A 
/* 1D44 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED A 
/* 1D45 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL ALPHA 
/* 1D46 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED AE 
/* 1D47 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL B 
/* 1D48 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL D 
/* 1D49 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL E 
/* 1D4A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL SCHWA 
/* 1D4B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL OPEN E 
/* 1D4C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED OPEN E 
/* 1D4D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL G 
/* 1D4E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED I 
/* 1D4F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL K 
/* 1D50 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL M 
/* 1D51 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL ENG 
/* 1D52 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL O 
/* 1D53 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL OPEN O 
/* 1D54 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TOP HALF O 
/* 1D55 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL BOTTOM HALF O 
/* 1D56 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL P 
/* 1D57 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL T 
/* 1D58 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL U 
/* 1D59 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL SIDEWAYS U 
/* 1D5A */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED M 
/* 1D5B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL V 
/* 1D5C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL AIN 
/* 1D5D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL BETA 
/* 1D5E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL GREEK GAMMA 
/* 1D5F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL DELTA 
/* 1D60 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL GREEK PHI 
/* 1D61 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL CHI 
/* 1D62 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER I 
/* 1D63 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER R 
/* 1D64 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER U 
/* 1D65 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER V 
/* 1D66 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SUBSCRIPT SMALL LETTER BETA 
/* 1D67 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SUBSCRIPT SMALL LETTER GAMMA 
/* 1D68 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SUBSCRIPT SMALL LETTER RHO 
/* 1D69 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SUBSCRIPT SMALL LETTER PHI 
/* 1D6A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK SUBSCRIPT SMALL LETTER CHI 
/* 1D6B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER UE 
/* 1D6C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER B WITH MIDDLE TILDE 
/* 1D6D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH MIDDLE TILDE 
/* 1D6E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER F WITH MIDDLE TILDE 
/* 1D6F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER M WITH MIDDLE TILDE 
/* 1D70 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH MIDDLE TILDE 
/* 1D71 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER P WITH MIDDLE TILDE 
/* 1D72 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH MIDDLE TILDE 
/* 1D73 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH FISHHOOK AND MIDDLE TILDE 
/* 1D74 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH MIDDLE TILDE 
/* 1D75 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH MIDDLE TILDE 
/* 1D76 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH MIDDLE TILDE 
/* 1D77 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TURNED G 
/* 1D78 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER CYRILLIC EN 
/* 1D79 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER INSULAR G 
/* 1D7A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER TH WITH STRIKETHROUGH 
/* 1D7B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL CAPITAL LETTER I WITH STROKE 
/* 1D7C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER IOTA WITH STROKE 
/* 1D7D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER P WITH STROKE 
/* 1D7E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL CAPITAL LETTER U WITH STROKE 
/* 1D7F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER UPSILON WITH STROKE 
/* 1D80 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER B WITH PALATAL HOOK 
/* 1D81 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH PALATAL HOOK 
/* 1D82 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER F WITH PALATAL HOOK 
/* 1D83 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH PALATAL HOOK 
/* 1D84 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER K WITH PALATAL HOOK 
/* 1D85 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH PALATAL HOOK 
/* 1D86 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER M WITH PALATAL HOOK 
/* 1D87 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH PALATAL HOOK 
/* 1D88 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER P WITH PALATAL HOOK 
/* 1D89 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH PALATAL HOOK 
/* 1D8A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH PALATAL HOOK 
/* 1D8B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER ESH WITH PALATAL HOOK 
/* 1D8C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER V WITH PALATAL HOOK 
/* 1D8D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER X WITH PALATAL HOOK 
/* 1D8E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH PALATAL HOOK 
/* 1D8F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH RETROFLEX HOOK 
/* 1D90 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER ALPHA WITH RETROFLEX HOOK 
/* 1D91 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH HOOK AND TAIL 
/* 1D92 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH RETROFLEX HOOK 
/* 1D93 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER OPEN E WITH RETROFLEX HOOK 
/* 1D94 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER REVERSED OPEN E WITH RETROFLEX HOOK 
/* 1D95 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER SCHWA WITH RETROFLEX HOOK 
/* 1D96 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH RETROFLEX HOOK 
/* 1D97 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER OPEN O WITH RETROFLEX HOOK 
/* 1D98 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER ESH WITH RETROFLEX HOOK 
/* 1D99 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH RETROFLEX HOOK 
/* 1D9A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER EZH WITH RETROFLEX HOOK 
/* 1D9B */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED ALPHA 
/* 1D9C */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL C 
/* 1D9D */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL C WITH CURL 
/* 1D9E */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL ETH 
/* 1D9F */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL REVERSED OPEN E 
/* 1DA0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL F 
/* 1DA1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL DOTLESS J WITH STROKE 
/* 1DA2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL SCRIPT G 
/* 1DA3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED H 
/* 1DA4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL I WITH STROKE 
/* 1DA5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL IOTA 
/* 1DA6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL CAPITAL I 
/* 1DA7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL CAPITAL I WITH STROKE 
/* 1DA8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL J WITH CROSSED-TAIL 
/* 1DA9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL L WITH RETROFLEX HOOK 
/* 1DAA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL L WITH PALATAL HOOK 
/* 1DAB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL CAPITAL L 
/* 1DAC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL M WITH HOOK 
/* 1DAD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED M WITH LONG LEG 
/* 1DAE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL N WITH LEFT HOOK 
/* 1DAF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL N WITH RETROFLEX HOOK 
/* 1DB0 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL CAPITAL N 
/* 1DB1 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL BARRED O 
/* 1DB2 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL PHI 
/* 1DB3 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL S WITH HOOK 
/* 1DB4 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL ESH 
/* 1DB5 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL T WITH PALATAL HOOK 
/* 1DB6 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL U BAR 
/* 1DB7 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL UPSILON 
/* 1DB8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL CAPITAL U 
/* 1DB9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL V WITH HOOK 
/* 1DBA */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL TURNED V 
/* 1DBB */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL Z 
/* 1DBC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL Z WITH RETROFLEX HOOK 
/* 1DBD */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL Z WITH CURL 
/* 1DBE */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL EZH 
/* 1DBF */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MODIFIER LETTER SMALL THETA 
/* 1DC0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOTTED GRAVE ACCENT 
/* 1DC1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOTTED ACUTE ACCENT 
/* 1DC2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING SNAKE BELOW 
/* 1DC3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING SUSPENSION MARK 
/* 1dc4 */ { 0x0000, 0x0000, 0x0000 },
/* 1dc5 */ { 0x0000, 0x0000, 0x0000 },
/* 1dc6 */ { 0x0000, 0x0000, 0x0000 },
/* 1dc7 */ { 0x0000, 0x0000, 0x0000 },
/* 1dc8 */ { 0x0000, 0x0000, 0x0000 },
/* 1dc9 */ { 0x0000, 0x0000, 0x0000 },
/* 1dca */ { 0x0000, 0x0000, 0x0000 },
/* 1dcb */ { 0x0000, 0x0000, 0x0000 },
/* 1dcc */ { 0x0000, 0x0000, 0x0000 },
/* 1dcd */ { 0x0000, 0x0000, 0x0000 },
/* 1dce */ { 0x0000, 0x0000, 0x0000 },
/* 1dcf */ { 0x0000, 0x0000, 0x0000 },
/* 1dd0 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd1 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd2 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd3 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd4 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd5 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd6 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd7 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd8 */ { 0x0000, 0x0000, 0x0000 },
/* 1dd9 */ { 0x0000, 0x0000, 0x0000 },
/* 1dda */ { 0x0000, 0x0000, 0x0000 },
/* 1ddb */ { 0x0000, 0x0000, 0x0000 },
/* 1ddc */ { 0x0000, 0x0000, 0x0000 },
/* 1ddd */ { 0x0000, 0x0000, 0x0000 },
/* 1dde */ { 0x0000, 0x0000, 0x0000 },
/* 1ddf */ { 0x0000, 0x0000, 0x0000 },
/* 1de0 */ { 0x0000, 0x0000, 0x0000 },
/* 1de1 */ { 0x0000, 0x0000, 0x0000 },
/* 1de2 */ { 0x0000, 0x0000, 0x0000 },
/* 1de3 */ { 0x0000, 0x0000, 0x0000 },
/* 1de4 */ { 0x0000, 0x0000, 0x0000 },
/* 1de5 */ { 0x0000, 0x0000, 0x0000 },
/* 1de6 */ { 0x0000, 0x0000, 0x0000 },
/* 1de7 */ { 0x0000, 0x0000, 0x0000 },
/* 1de8 */ { 0x0000, 0x0000, 0x0000 },
/* 1de9 */ { 0x0000, 0x0000, 0x0000 },
/* 1dea */ { 0x0000, 0x0000, 0x0000 },
/* 1deb */ { 0x0000, 0x0000, 0x0000 },
/* 1dec */ { 0x0000, 0x0000, 0x0000 },
/* 1ded */ { 0x0000, 0x0000, 0x0000 },
/* 1dee */ { 0x0000, 0x0000, 0x0000 },
/* 1def */ { 0x0000, 0x0000, 0x0000 },
/* 1df0 */ { 0x0000, 0x0000, 0x0000 },
/* 1df1 */ { 0x0000, 0x0000, 0x0000 },
/* 1df2 */ { 0x0000, 0x0000, 0x0000 },
/* 1df3 */ { 0x0000, 0x0000, 0x0000 },
/* 1df4 */ { 0x0000, 0x0000, 0x0000 },
/* 1df5 */ { 0x0000, 0x0000, 0x0000 },
/* 1df6 */ { 0x0000, 0x0000, 0x0000 },
/* 1df7 */ { 0x0000, 0x0000, 0x0000 },
/* 1df8 */ { 0x0000, 0x0000, 0x0000 },
/* 1df9 */ { 0x0000, 0x0000, 0x0000 },
/* 1dfa */ { 0x0000, 0x0000, 0x0000 },
/* 1dfb */ { 0x0000, 0x0000, 0x0000 },
/* 1dfc */ { 0x0000, 0x0000, 0x0000 },
/* 1dfd */ { 0x0000, 0x0000, 0x0000 },
/* 1dfe */ { 0x0000, 0x0000, 0x0000 },
/* 1dff */ { 0x0000, 0x0000, 0x0000 },
/* 1E00 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E01, 0x0041,0x0325,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH RING BELOW 
/* 1E01 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E00, 0x0061,0x0325,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH RING BELOW 
/* 1E02 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E03, 0x0042,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER B WITH DOT ABOVE 
/* 1E03 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E02, 0x0062,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER B WITH DOT ABOVE 
/* 1E04 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E05, 0x0042,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER B WITH DOT BELOW 
/* 1E05 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E04, 0x0062,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER B WITH DOT BELOW 
/* 1E06 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E07, 0x0042,0x0331,0x0000,0x0000 }, // LATIN CAPITAL LETTER B WITH LINE BELOW 
/* 1E07 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E06, 0x0062,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER B WITH LINE BELOW 
/* 1E08 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E09, 0x00C7,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER C WITH CEDILLA AND ACUTE 
/* 1E09 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E08, 0x00E7,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER C WITH CEDILLA AND ACUTE 
/* 1E0A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E0B, 0x0044,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH DOT ABOVE 
/* 1E0B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E0A, 0x0064,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH DOT ABOVE 
/* 1E0C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E0D, 0x0044,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH DOT BELOW 
/* 1E0D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E0C, 0x0064,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH DOT BELOW 
/* 1E0E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E0F, 0x0044,0x0331,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH LINE BELOW 
/* 1E0F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E0E, 0x0064,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH LINE BELOW 
/* 1E10 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E11, 0x0044,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH CEDILLA 
/* 1E11 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E10, 0x0064,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH CEDILLA 
/* 1E12 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E13, 0x0044,0x032D,0x0000,0x0000 }, // LATIN CAPITAL LETTER D WITH CIRCUMFLEX BELOW 
/* 1E13 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E12, 0x0064,0x032D,0x0000,0x0000 }, // LATIN SMALL LETTER D WITH CIRCUMFLEX BELOW 
/* 1E14 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E15, 0x0112,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH MACRON AND GRAVE 
/* 1E15 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E14, 0x0113,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH MACRON AND GRAVE 
/* 1E16 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E17, 0x0112,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH MACRON AND ACUTE 
/* 1E17 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E16, 0x0113,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH MACRON AND ACUTE 
/* 1E18 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E19, 0x0045,0x032D,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CIRCUMFLEX BELOW 
/* 1E19 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E18, 0x0065,0x032D,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CIRCUMFLEX BELOW 
/* 1E1A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E1B, 0x0045,0x0330,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH TILDE BELOW 
/* 1E1B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E1A, 0x0065,0x0330,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH TILDE BELOW 
/* 1E1C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E1D, 0x0228,0x0306,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CEDILLA AND BREVE 
/* 1E1D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E1C, 0x0229,0x0306,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CEDILLA AND BREVE 
/* 1E1E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E1F, 0x0046,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER F WITH DOT ABOVE 
/* 1E1F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E1E, 0x0066,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER F WITH DOT ABOVE 
/* 1E20 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E21, 0x0047,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER G WITH MACRON 
/* 1E21 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E20, 0x0067,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER G WITH MACRON 
/* 1E22 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E23, 0x0048,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER H WITH DOT ABOVE 
/* 1E23 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E22, 0x0068,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH DOT ABOVE 
/* 1E24 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E25, 0x0048,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER H WITH DOT BELOW 
/* 1E25 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E24, 0x0068,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH DOT BELOW 
/* 1E26 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E27, 0x0048,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER H WITH DIAERESIS 
/* 1E27 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E26, 0x0068,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH DIAERESIS 
/* 1E28 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E29, 0x0048,0x0327,0x0000,0x0000 }, // LATIN CAPITAL LETTER H WITH CEDILLA 
/* 1E29 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E28, 0x0068,0x0327,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH CEDILLA 
/* 1E2A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E2B, 0x0048,0x032E,0x0000,0x0000 }, // LATIN CAPITAL LETTER H WITH BREVE BELOW 
/* 1E2B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E2A, 0x0068,0x032E,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH BREVE BELOW 
/* 1E2C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E2D, 0x0049,0x0330,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH TILDE BELOW 
/* 1E2D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E2C, 0x0069,0x0330,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH TILDE BELOW 
/* 1E2E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E2F, 0x00CF,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH DIAERESIS AND ACUTE 
/* 1E2F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E2E, 0x00EF,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH DIAERESIS AND ACUTE 
/* 1E30 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E31, 0x004B,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER K WITH ACUTE 
/* 1E31 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E30, 0x006B,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER K WITH ACUTE 
/* 1E32 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E33, 0x004B,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER K WITH DOT BELOW 
/* 1E33 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E32, 0x006B,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER K WITH DOT BELOW 
/* 1E34 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E35, 0x004B,0x0331,0x0000,0x0000 }, // LATIN CAPITAL LETTER K WITH LINE BELOW 
/* 1E35 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E34, 0x006B,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER K WITH LINE BELOW 
/* 1E36 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E37, 0x004C,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH DOT BELOW 
/* 1E37 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E36, 0x006C,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH DOT BELOW 
/* 1E38 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E39, 0x1E36,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH DOT BELOW AND MACRON 
/* 1E39 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E38, 0x1E37,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH DOT BELOW AND MACRON 
/* 1E3A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E3B, 0x004C,0x0331,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH LINE BELOW 
/* 1E3B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E3A, 0x006C,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH LINE BELOW 
/* 1E3C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E3D, 0x004C,0x032D,0x0000,0x0000 }, // LATIN CAPITAL LETTER L WITH CIRCUMFLEX BELOW 
/* 1E3D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E3C, 0x006C,0x032D,0x0000,0x0000 }, // LATIN SMALL LETTER L WITH CIRCUMFLEX BELOW 
/* 1E3E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E3F, 0x004D,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER M WITH ACUTE 
/* 1E3F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E3E, 0x006D,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER M WITH ACUTE 
/* 1E40 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E41, 0x004D,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER M WITH DOT ABOVE 
/* 1E41 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E40, 0x006D,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER M WITH DOT ABOVE 
/* 1E42 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E43, 0x004D,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER M WITH DOT BELOW 
/* 1E43 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E42, 0x006D,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER M WITH DOT BELOW 
/* 1E44 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E45, 0x004E,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH DOT ABOVE 
/* 1E45 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E44, 0x006E,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH DOT ABOVE 
/* 1E46 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E47, 0x004E,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH DOT BELOW 
/* 1E47 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E46, 0x006E,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH DOT BELOW 
/* 1E48 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E49, 0x004E,0x0331,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH LINE BELOW 
/* 1E49 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E48, 0x006E,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH LINE BELOW 
/* 1E4A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E4B, 0x004E,0x032D,0x0000,0x0000 }, // LATIN CAPITAL LETTER N WITH CIRCUMFLEX BELOW 
/* 1E4B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E4A, 0x006E,0x032D,0x0000,0x0000 }, // LATIN SMALL LETTER N WITH CIRCUMFLEX BELOW 
/* 1E4C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E4D, 0x00D5,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH TILDE AND ACUTE 
/* 1E4D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E4C, 0x00F5,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH TILDE AND ACUTE 
/* 1E4E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E4F, 0x00D5,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH TILDE AND DIAERESIS 
/* 1E4F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E4E, 0x00F5,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH TILDE AND DIAERESIS 
/* 1E50 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E51, 0x014C,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH MACRON AND GRAVE 
/* 1E51 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E50, 0x014D,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH MACRON AND GRAVE 
/* 1E52 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E53, 0x014C,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH MACRON AND ACUTE 
/* 1E53 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E52, 0x014D,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH MACRON AND ACUTE 
/* 1E54 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E55, 0x0050,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER P WITH ACUTE 
/* 1E55 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E54, 0x0070,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER P WITH ACUTE 
/* 1E56 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E57, 0x0050,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER P WITH DOT ABOVE 
/* 1E57 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E56, 0x0070,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER P WITH DOT ABOVE 
/* 1E58 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E59, 0x0052,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH DOT ABOVE 
/* 1E59 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E58, 0x0072,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH DOT ABOVE 
/* 1E5A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E5B, 0x0052,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH DOT BELOW 
/* 1E5B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E5A, 0x0072,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH DOT BELOW 
/* 1E5C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E5D, 0x1E5A,0x0304,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH DOT BELOW AND MACRON 
/* 1E5D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E5C, 0x1E5B,0x0304,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH DOT BELOW AND MACRON 
/* 1E5E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E5F, 0x0052,0x0331,0x0000,0x0000 }, // LATIN CAPITAL LETTER R WITH LINE BELOW 
/* 1E5F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E5E, 0x0072,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER R WITH LINE BELOW 
/* 1E60 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E61, 0x0053,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH DOT ABOVE 
/* 1E61 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E60, 0x0073,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH DOT ABOVE 
/* 1E62 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E63, 0x0053,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH DOT BELOW 
/* 1E63 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E62, 0x0073,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH DOT BELOW 
/* 1E64 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E65, 0x015A,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH ACUTE AND DOT ABOVE 
/* 1E65 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E64, 0x015B,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH ACUTE AND DOT ABOVE 
/* 1E66 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E67, 0x0160,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH CARON AND DOT ABOVE 
/* 1E67 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E66, 0x0161,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH CARON AND DOT ABOVE 
/* 1E68 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E69, 0x1E62,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER S WITH DOT BELOW AND DOT ABOVE 
/* 1E69 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E68, 0x1E63,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER S WITH DOT BELOW AND DOT ABOVE 
/* 1E6A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E6B, 0x0054,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH DOT ABOVE 
/* 1E6B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E6A, 0x0074,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH DOT ABOVE 
/* 1E6C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E6D, 0x0054,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH DOT BELOW 
/* 1E6D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E6C, 0x0074,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH DOT BELOW 
/* 1E6E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E6F, 0x0054,0x0331,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH LINE BELOW 
/* 1E6F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E6E, 0x0074,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH LINE BELOW 
/* 1E70 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E71, 0x0054,0x032D,0x0000,0x0000 }, // LATIN CAPITAL LETTER T WITH CIRCUMFLEX BELOW 
/* 1E71 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E70, 0x0074,0x032D,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH CIRCUMFLEX BELOW 
/* 1E72 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E73, 0x0055,0x0324,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DIAERESIS BELOW 
/* 1E73 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E72, 0x0075,0x0324,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DIAERESIS BELOW 
/* 1E74 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E75, 0x0055,0x0330,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH TILDE BELOW 
/* 1E75 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E74, 0x0075,0x0330,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH TILDE BELOW 
/* 1E76 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E77, 0x0055,0x032D,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH CIRCUMFLEX BELOW 
/* 1E77 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E76, 0x0075,0x032D,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH CIRCUMFLEX BELOW 
/* 1E78 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E79, 0x0168,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH TILDE AND ACUTE 
/* 1E79 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E78, 0x0169,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH TILDE AND ACUTE 
/* 1E7A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E7B, 0x016A,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH MACRON AND DIAERESIS 
/* 1E7B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E7A, 0x016B,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH MACRON AND DIAERESIS 
/* 1E7C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E7D, 0x0056,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER V WITH TILDE 
/* 1E7D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E7C, 0x0076,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER V WITH TILDE 
/* 1E7E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E7F, 0x0056,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER V WITH DOT BELOW 
/* 1E7F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E7E, 0x0076,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER V WITH DOT BELOW 
/* 1E80 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E81, 0x0057,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER W WITH GRAVE 
/* 1E81 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E80, 0x0077,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER W WITH GRAVE 
/* 1E82 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E83, 0x0057,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER W WITH ACUTE 
/* 1E83 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E82, 0x0077,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER W WITH ACUTE 
/* 1E84 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E85, 0x0057,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER W WITH DIAERESIS 
/* 1E85 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E84, 0x0077,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER W WITH DIAERESIS 
/* 1E86 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E87, 0x0057,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER W WITH DOT ABOVE 
/* 1E87 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E86, 0x0077,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER W WITH DOT ABOVE 
/* 1E88 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E89, 0x0057,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER W WITH DOT BELOW 
/* 1E89 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E88, 0x0077,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER W WITH DOT BELOW 
/* 1E8A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E8B, 0x0058,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER X WITH DOT ABOVE 
/* 1E8B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E8A, 0x0078,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER X WITH DOT ABOVE 
/* 1E8C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E8D, 0x0058,0x0308,0x0000,0x0000 }, // LATIN CAPITAL LETTER X WITH DIAERESIS 
/* 1E8D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E8C, 0x0078,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER X WITH DIAERESIS 
/* 1E8E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E8F, 0x0059,0x0307,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH DOT ABOVE 
/* 1E8F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E8E, 0x0079,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH DOT ABOVE 
/* 1E90 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E91, 0x005A,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z WITH CIRCUMFLEX 
/* 1E91 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E90, 0x007A,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH CIRCUMFLEX 
/* 1E92 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E93, 0x005A,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z WITH DOT BELOW 
/* 1E93 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E92, 0x007A,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH DOT BELOW 
/* 1E94 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1E95, 0x005A,0x0331,0x0000,0x0000 }, // LATIN CAPITAL LETTER Z WITH LINE BELOW 
/* 1E95 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E94, 0x007A,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER Z WITH LINE BELOW 
/* 1E96 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0068,0x0331,0x0000,0x0000 }, // LATIN SMALL LETTER H WITH LINE BELOW 
/* 1E97 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0074,0x0308,0x0000,0x0000 }, // LATIN SMALL LETTER T WITH DIAERESIS 
/* 1E98 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0077,0x030A,0x0000,0x0000 }, // LATIN SMALL LETTER W WITH RING ABOVE 
/* 1E99 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0079,0x030A,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH RING ABOVE 
/* 1E9A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH RIGHT HALF RING 
/* 1E9B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1E60, 0x017F,0x0307,0x0000,0x0000 }, // LATIN SMALL LETTER LONG S WITH DOT ABOVE 
/* 1e9c */ { 0x0000, 0x0000, 0x0000 },
/* 1e9d */ { 0x0000, 0x0000, 0x0000 },
/* 1e9e */ { 0x0000, 0x0000, 0x0000 },
/* 1e9f */ { 0x0000, 0x0000, 0x0000 },
/* 1EA0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EA1, 0x0041,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH DOT BELOW 
/* 1EA1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EA0, 0x0061,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH DOT BELOW 
/* 1EA2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EA3, 0x0041,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH HOOK ABOVE 
/* 1EA3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EA2, 0x0061,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH HOOK ABOVE 
/* 1EA4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EA5, 0x00C2,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND ACUTE 
/* 1EA5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EA4, 0x00E2,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH CIRCUMFLEX AND ACUTE 
/* 1EA6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EA7, 0x00C2,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND GRAVE 
/* 1EA7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EA6, 0x00E2,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH CIRCUMFLEX AND GRAVE 
/* 1EA8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EA9, 0x00C2,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE 
/* 1EA9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EA8, 0x00E2,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE 
/* 1EAA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EAB, 0x00C2,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND TILDE 
/* 1EAB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EAA, 0x00E2,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH CIRCUMFLEX AND TILDE 
/* 1EAC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EAD, 0x1EA0,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND DOT BELOW 
/* 1EAD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EAC, 0x1EA1,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH CIRCUMFLEX AND DOT BELOW 
/* 1EAE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EAF, 0x0102,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH BREVE AND ACUTE 
/* 1EAF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EAE, 0x0103,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH BREVE AND ACUTE 
/* 1EB0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EB1, 0x0102,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH BREVE AND GRAVE 
/* 1EB1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EB0, 0x0103,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH BREVE AND GRAVE 
/* 1EB2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EB3, 0x0102,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH BREVE AND HOOK ABOVE 
/* 1EB3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EB2, 0x0103,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE 
/* 1EB4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EB5, 0x0102,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH BREVE AND TILDE 
/* 1EB5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EB4, 0x0103,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH BREVE AND TILDE 
/* 1EB6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EB7, 0x1EA0,0x0306,0x0000,0x0000 }, // LATIN CAPITAL LETTER A WITH BREVE AND DOT BELOW 
/* 1EB7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EB6, 0x1EA1,0x0306,0x0000,0x0000 }, // LATIN SMALL LETTER A WITH BREVE AND DOT BELOW 
/* 1EB8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EB9, 0x0045,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH DOT BELOW 
/* 1EB9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EB8, 0x0065,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH DOT BELOW 
/* 1EBA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EBB, 0x0045,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH HOOK ABOVE 
/* 1EBB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EBA, 0x0065,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH HOOK ABOVE 
/* 1EBC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EBD, 0x0045,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH TILDE 
/* 1EBD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EBC, 0x0065,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH TILDE 
/* 1EBE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EBF, 0x00CA,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND ACUTE 
/* 1EBF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EBE, 0x00EA,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CIRCUMFLEX AND ACUTE 
/* 1EC0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EC1, 0x00CA,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND GRAVE 
/* 1EC1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EC0, 0x00EA,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CIRCUMFLEX AND GRAVE 
/* 1EC2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EC3, 0x00CA,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE 
/* 1EC3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EC2, 0x00EA,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE 
/* 1EC4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EC5, 0x00CA,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND TILDE 
/* 1EC5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EC4, 0x00EA,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CIRCUMFLEX AND TILDE 
/* 1EC6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EC7, 0x1EB8,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND DOT BELOW 
/* 1EC7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EC6, 0x1EB9,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER E WITH CIRCUMFLEX AND DOT BELOW 
/* 1EC8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EC9, 0x0049,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH HOOK ABOVE 
/* 1EC9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EC8, 0x0069,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH HOOK ABOVE 
/* 1ECA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1ECB, 0x0049,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER I WITH DOT BELOW 
/* 1ECB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1ECA, 0x0069,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER I WITH DOT BELOW 
/* 1ECC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1ECD, 0x004F,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH DOT BELOW 
/* 1ECD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1ECC, 0x006F,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH DOT BELOW 
/* 1ECE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1ECF, 0x004F,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH HOOK ABOVE 
/* 1ECF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1ECE, 0x006F,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH HOOK ABOVE 
/* 1ED0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1ED1, 0x00D4,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND ACUTE 
/* 1ED1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1ED0, 0x00F4,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH CIRCUMFLEX AND ACUTE 
/* 1ED2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1ED3, 0x00D4,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND GRAVE 
/* 1ED3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1ED2, 0x00F4,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE 
/* 1ED4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1ED5, 0x00D4,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE 
/* 1ED5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1ED4, 0x00F4,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE 
/* 1ED6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1ED7, 0x00D4,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND TILDE 
/* 1ED7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1ED6, 0x00F4,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH CIRCUMFLEX AND TILDE 
/* 1ED8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1ED9, 0x1ECC,0x0302,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND DOT BELOW 
/* 1ED9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1ED8, 0x1ECD,0x0302,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW 
/* 1EDA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EDB, 0x01A0,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH HORN AND ACUTE 
/* 1EDB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EDA, 0x01A1,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH HORN AND ACUTE 
/* 1EDC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EDD, 0x01A0,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH HORN AND GRAVE 
/* 1EDD */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EDC, 0x01A1,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH HORN AND GRAVE 
/* 1EDE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EDF, 0x01A0,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH HORN AND HOOK ABOVE 
/* 1EDF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EDE, 0x01A1,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE 
/* 1EE0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EE1, 0x01A0,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH HORN AND TILDE 
/* 1EE1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EE0, 0x01A1,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH HORN AND TILDE 
/* 1EE2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EE3, 0x01A0,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER O WITH HORN AND DOT BELOW 
/* 1EE3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EE2, 0x01A1,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER O WITH HORN AND DOT BELOW 
/* 1EE4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EE5, 0x0055,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH DOT BELOW 
/* 1EE5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EE4, 0x0075,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH DOT BELOW 
/* 1EE6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EE7, 0x0055,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH HOOK ABOVE 
/* 1EE7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EE6, 0x0075,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH HOOK ABOVE 
/* 1EE8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EE9, 0x01AF,0x0301,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH HORN AND ACUTE 
/* 1EE9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EE8, 0x01B0,0x0301,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH HORN AND ACUTE 
/* 1EEA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EEB, 0x01AF,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH HORN AND GRAVE 
/* 1EEB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EEA, 0x01B0,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH HORN AND GRAVE 
/* 1EEC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EED, 0x01AF,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH HORN AND HOOK ABOVE 
/* 1EED */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EEC, 0x01B0,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH HORN AND HOOK ABOVE 
/* 1EEE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EEF, 0x01AF,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH HORN AND TILDE 
/* 1EEF */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EEE, 0x01B0,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH HORN AND TILDE 
/* 1EF0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EF1, 0x01AF,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER U WITH HORN AND DOT BELOW 
/* 1EF1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EF0, 0x01B0,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER U WITH HORN AND DOT BELOW 
/* 1EF2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EF3, 0x0059,0x0300,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH GRAVE 
/* 1EF3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EF2, 0x0079,0x0300,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH GRAVE 
/* 1EF4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EF5, 0x0059,0x0323,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH DOT BELOW 
/* 1EF5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EF4, 0x0079,0x0323,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH DOT BELOW 
/* 1EF6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EF7, 0x0059,0x0309,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH HOOK ABOVE 
/* 1EF7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EF6, 0x0079,0x0309,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH HOOK ABOVE 
/* 1EF8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1EF9, 0x0059,0x0303,0x0000,0x0000 }, // LATIN CAPITAL LETTER Y WITH TILDE 
/* 1EF9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1EF8, 0x0079,0x0303,0x0000,0x0000 }, // LATIN SMALL LETTER Y WITH TILDE 
/* 1efa */ { 0x0000, 0x0000, 0x0000 },
/* 1efb */ { 0x0000, 0x0000, 0x0000 },
/* 1efc */ { 0x0000, 0x0000, 0x0000 },
/* 1efd */ { 0x0000, 0x0000, 0x0000 },
/* 1efe */ { 0x0000, 0x0000, 0x0000 },
/* 1eff */ { 0x0000, 0x0000, 0x0000 },
/* 1F00 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F08, 0x03B1,0x0313,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PSILI 
/* 1F01 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F09, 0x03B1,0x0314,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH DASIA 
/* 1F02 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F0A, 0x1F00,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA 
/* 1F03 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F0B, 0x1F01,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH DASIA AND VARIA 
/* 1F04 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F0C, 0x1F00,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA 
/* 1F05 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F0D, 0x1F01,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH DASIA AND OXIA 
/* 1F06 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F0E, 0x1F00,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PSILI AND PERISPOMENI 
/* 1F07 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F0F, 0x1F01,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI 
/* 1F08 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F00, 0x0391,0x0313,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PSILI 
/* 1F09 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F01, 0x0391,0x0314,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH DASIA 
/* 1F0A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F02, 0x1F08,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND VARIA 
/* 1F0B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F03, 0x1F09,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND VARIA 
/* 1F0C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F04, 0x1F08,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND OXIA 
/* 1F0D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F05, 0x1F09,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND OXIA 
/* 1F0E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F06, 0x1F08,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PERISPOMENI 
/* 1F0F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F07, 0x1F09,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI 
/* 1F10 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F18, 0x03B5,0x0313,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH PSILI 
/* 1F11 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F19, 0x03B5,0x0314,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH DASIA 
/* 1F12 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F1A, 0x1F10,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH PSILI AND VARIA 
/* 1F13 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F1B, 0x1F11,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH DASIA AND VARIA 
/* 1F14 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F1C, 0x1F10,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH PSILI AND OXIA 
/* 1F15 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F1D, 0x1F11,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH DASIA AND OXIA 
/* 1f16 */ { 0x0000, 0x0000, 0x0000 },
/* 1f17 */ { 0x0000, 0x0000, 0x0000 },
/* 1F18 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F10, 0x0395,0x0313,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH PSILI 
/* 1F19 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F11, 0x0395,0x0314,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH DASIA 
/* 1F1A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F12, 0x1F18,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH PSILI AND VARIA 
/* 1F1B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F13, 0x1F19,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH DASIA AND VARIA 
/* 1F1C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F14, 0x1F18,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH PSILI AND OXIA 
/* 1F1D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F15, 0x1F19,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH DASIA AND OXIA 
/* 1f1e */ { 0x0000, 0x0000, 0x0000 },
/* 1f1f */ { 0x0000, 0x0000, 0x0000 },
/* 1F20 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F28, 0x03B7,0x0313,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PSILI 
/* 1F21 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F29, 0x03B7,0x0314,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH DASIA 
/* 1F22 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F2A, 0x1F20,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PSILI AND VARIA 
/* 1F23 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F2B, 0x1F21,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH DASIA AND VARIA 
/* 1F24 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F2C, 0x1F20,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PSILI AND OXIA 
/* 1F25 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F2D, 0x1F21,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH DASIA AND OXIA 
/* 1F26 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F2E, 0x1F20,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI 
/* 1F27 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F2F, 0x1F21,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI 
/* 1F28 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F20, 0x0397,0x0313,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PSILI 
/* 1F29 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F21, 0x0397,0x0314,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH DASIA 
/* 1F2A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F22, 0x1F28,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PSILI AND VARIA 
/* 1F2B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F23, 0x1F29,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH DASIA AND VARIA 
/* 1F2C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F24, 0x1F28,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PSILI AND OXIA 
/* 1F2D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F25, 0x1F29,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH DASIA AND OXIA 
/* 1F2E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F26, 0x1F28,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PSILI AND PERISPOMENI 
/* 1F2F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F27, 0x1F29,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI 
/* 1F30 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F38, 0x03B9,0x0313,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH PSILI 
/* 1F31 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F39, 0x03B9,0x0314,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DASIA 
/* 1F32 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F3A, 0x1F30,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH PSILI AND VARIA 
/* 1F33 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F3B, 0x1F31,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DASIA AND VARIA 
/* 1F34 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F3C, 0x1F30,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH PSILI AND OXIA 
/* 1F35 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F3D, 0x1F31,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DASIA AND OXIA 
/* 1F36 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F3E, 0x1F30,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH PSILI AND PERISPOMENI 
/* 1F37 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F3F, 0x1F31,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DASIA AND PERISPOMENI 
/* 1F38 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F30, 0x0399,0x0313,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH PSILI 
/* 1F39 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F31, 0x0399,0x0314,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH DASIA 
/* 1F3A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F32, 0x1F38,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH PSILI AND VARIA 
/* 1F3B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F33, 0x1F39,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH DASIA AND VARIA 
/* 1F3C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F34, 0x1F38,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH PSILI AND OXIA 
/* 1F3D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F35, 0x1F39,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH DASIA AND OXIA 
/* 1F3E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F36, 0x1F38,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH PSILI AND PERISPOMENI 
/* 1F3F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F37, 0x1F39,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH DASIA AND PERISPOMENI 
/* 1F40 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F48, 0x03BF,0x0313,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH PSILI 
/* 1F41 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F49, 0x03BF,0x0314,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH DASIA 
/* 1F42 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F4A, 0x1F40,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH PSILI AND VARIA 
/* 1F43 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F4B, 0x1F41,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH DASIA AND VARIA 
/* 1F44 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F4C, 0x1F40,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH PSILI AND OXIA 
/* 1F45 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F4D, 0x1F41,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH DASIA AND OXIA 
/* 1f46 */ { 0x0000, 0x0000, 0x0000 },
/* 1f47 */ { 0x0000, 0x0000, 0x0000 },
/* 1F48 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F40, 0x039F,0x0313,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH PSILI 
/* 1F49 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F41, 0x039F,0x0314,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH DASIA 
/* 1F4A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F42, 0x1F48,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH PSILI AND VARIA 
/* 1F4B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F43, 0x1F49,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH DASIA AND VARIA 
/* 1F4C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F44, 0x1F48,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH PSILI AND OXIA 
/* 1F4D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F45, 0x1F49,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH DASIA AND OXIA 
/* 1f4e */ { 0x0000, 0x0000, 0x0000 },
/* 1f4f */ { 0x0000, 0x0000, 0x0000 },
/* 1F50 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03C5,0x0313,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH PSILI 
/* 1F51 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F59, 0x03C5,0x0314,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DASIA 
/* 1F52 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1F50,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH PSILI AND VARIA 
/* 1F53 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F5B, 0x1F51,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DASIA AND VARIA 
/* 1F54 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1F50,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH PSILI AND OXIA 
/* 1F55 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F5D, 0x1F51,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DASIA AND OXIA 
/* 1F56 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1F50,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH PSILI AND PERISPOMENI 
/* 1F57 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F5F, 0x1F51,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI 
/* 1f58 */ { 0x0000, 0x0000, 0x0000 },
/* 1F59 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F51, 0x03A5,0x0314,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH DASIA 
/* 1f5a */ { 0x0000, 0x0000, 0x0000 },
/* 1F5B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F53, 0x1F59,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH DASIA AND VARIA 
/* 1f5c */ { 0x0000, 0x0000, 0x0000 },
/* 1F5D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F55, 0x1F59,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH DASIA AND OXIA 
/* 1f5e */ { 0x0000, 0x0000, 0x0000 },
/* 1F5F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F57, 0x1F59,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH DASIA AND PERISPOMENI 
/* 1F60 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F68, 0x03C9,0x0313,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PSILI 
/* 1F61 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F69, 0x03C9,0x0314,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH DASIA 
/* 1F62 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F6A, 0x1F60,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA 
/* 1F63 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F6B, 0x1F61,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA 
/* 1F64 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F6C, 0x1F60,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA 
/* 1F65 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F6D, 0x1F61,0x0301,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA 
/* 1F66 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F6E, 0x1F60,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI 
/* 1F67 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F6F, 0x1F61,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI 
/* 1F68 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F60, 0x03A9,0x0313,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PSILI 
/* 1F69 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F61, 0x03A9,0x0314,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH DASIA 
/* 1F6A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F62, 0x1F68,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA 
/* 1F6B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F63, 0x1F69,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA 
/* 1F6C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F64, 0x1F68,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA 
/* 1F6D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F65, 0x1F69,0x0301,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA 
/* 1F6E */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F66, 0x1F68,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI 
/* 1F6F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F67, 0x1F69,0x0342,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI 
/* 1F70 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FBA, 0x03B1,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH VARIA 
/* 1F71 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FBB, 0x03AC,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH OXIA 
/* 1F72 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FC8, 0x03B5,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH VARIA 
/* 1F73 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FC9, 0x03AD,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER EPSILON WITH OXIA 
/* 1F74 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FCA, 0x03B7,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH VARIA 
/* 1F75 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FCB, 0x03AE,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH OXIA 
/* 1F76 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FDA, 0x03B9,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH VARIA 
/* 1F77 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FDB, 0x03AF,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH OXIA 
/* 1F78 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FF8, 0x03BF,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH VARIA 
/* 1F79 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FF9, 0x03CC,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER OMICRON WITH OXIA 
/* 1F7A */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FEA, 0x03C5,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH VARIA 
/* 1F7B */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FEB, 0x03CD,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH OXIA 
/* 1F7C */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FFA, 0x03C9,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH VARIA 
/* 1F7D */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FFB, 0x03CE,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH OXIA 
/* 1f7e */ { 0x0000, 0x0000, 0x0000 },
/* 1f7f */ { 0x0000, 0x0000, 0x0000 },
/* 1F80 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F88, 0x1F00,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PSILI AND YPOGEGRAMMENI 
/* 1F81 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F89, 0x1F01,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH DASIA AND YPOGEGRAMMENI 
/* 1F82 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F8A, 0x1F02,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI 
/* 1F83 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F8B, 0x1F03,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH DASIA AND VARIA AND YPOGEGRAMMENI 
/* 1F84 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F8C, 0x1F04,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI 
/* 1F85 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F8D, 0x1F05,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH DASIA AND OXIA AND YPOGEGRAMMENI 
/* 1F86 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F8E, 0x1F06,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI 
/* 1F87 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F8F, 0x1F07,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI 
/* 1F88 */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F08,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PROSGEGRAMMENI 
/* 1F89 */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F09,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PROSGEGRAMMENI 
/* 1F8A */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F0A,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND VARIA AND PROSGEGRAMMENI 
/* 1F8B */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F0B,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND VARIA AND PROSGEGRAMMENI 
/* 1F8C */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F0C,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND OXIA AND PROSGEGRAMMENI 
/* 1F8D */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F0D,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND OXIA AND PROSGEGRAMMENI 
/* 1F8E */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F0E,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI 
/* 1F8F */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F0F,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI 
/* 1F90 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F98, 0x1F20,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI 
/* 1F91 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F99, 0x1F21,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH DASIA AND YPOGEGRAMMENI 
/* 1F92 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F9A, 0x1F22,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PSILI AND VARIA AND YPOGEGRAMMENI 
/* 1F93 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F9B, 0x1F23,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI 
/* 1F94 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F9C, 0x1F24,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PSILI AND OXIA AND YPOGEGRAMMENI 
/* 1F95 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F9D, 0x1F25,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH DASIA AND OXIA AND YPOGEGRAMMENI 
/* 1F96 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F9E, 0x1F26,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI 
/* 1F97 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1F9F, 0x1F27,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI 
/* 1F98 */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F28,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PSILI AND PROSGEGRAMMENI 
/* 1F99 */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F29,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH DASIA AND PROSGEGRAMMENI 
/* 1F9A */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F2A,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PSILI AND VARIA AND PROSGEGRAMMENI 
/* 1F9B */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F2B,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH DASIA AND VARIA AND PROSGEGRAMMENI 
/* 1F9C */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F2C,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PSILI AND OXIA AND PROSGEGRAMMENI 
/* 1F9D */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F2D,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH DASIA AND OXIA AND PROSGEGRAMMENI 
/* 1F9E */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F2E,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI 
/* 1F9F */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F2F,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI 
/* 1FA0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FA8, 0x1F60,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PSILI AND YPOGEGRAMMENI 
/* 1FA1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FA9, 0x1F61,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI 
/* 1FA2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FAA, 0x1F62,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA AND YPOGEGRAMMENI 
/* 1FA3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FAB, 0x1F63,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA AND YPOGEGRAMMENI 
/* 1FA4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FAC, 0x1F64,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA AND YPOGEGRAMMENI 
/* 1FA5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FAD, 0x1F65,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI 
/* 1FA6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FAE, 0x1F66,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI 
/* 1FA7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FAF, 0x1F67,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI 
/* 1FA8 */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F68,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PROSGEGRAMMENI 
/* 1FA9 */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F69,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PROSGEGRAMMENI 
/* 1FAA */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F6A,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA AND PROSGEGRAMMENI 
/* 1FAB */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F6B,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA AND PROSGEGRAMMENI 
/* 1FAC */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F6C,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA AND PROSGEGRAMMENI 
/* 1FAD */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F6D,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA AND PROSGEGRAMMENI 
/* 1FAE */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F6E,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI 
/* 1FAF */ { lem::CP_Char_Flags::Char, 0x0000, 0x1F6F,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI 
/* 1FB0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FB8, 0x03B1,0x0306,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH VRACHY 
/* 1FB1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FB9, 0x03B1,0x0304,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH MACRON 
/* 1FB2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1F70,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH VARIA AND YPOGEGRAMMENI 
/* 1FB3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FBC, 0x03B1,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH YPOGEGRAMMENI 
/* 1FB4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03AC,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH OXIA AND YPOGEGRAMMENI 
/* 1fb5 */ { 0x0000, 0x0000, 0x0000 },
/* 1FB6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03B1,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PERISPOMENI 
/* 1FB7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1FB6,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ALPHA WITH PERISPOMENI AND YPOGEGRAMMENI 
/* 1FB8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1FB0, 0x0391,0x0306,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH VRACHY 
/* 1FB9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1FB1, 0x0391,0x0304,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH MACRON 
/* 1FBA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F70, 0x0391,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH VARIA 
/* 1FBB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F71, 0x0386,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH OXIA 
/* 1FBC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0391,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ALPHA WITH PROSGEGRAMMENI 
/* 1FBD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK KORONIS 
/* 1FBE */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0399, 0x03B9,0x0000,0x0000,0x0000 }, // GREEK PROSGEGRAMMENI 
/* 1FBF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK PSILI 
/* 1FC0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK PERISPOMENI 
/* 1FC1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x00A8,0x0342,0x0000,0x0000 }, // GREEK DIALYTIKA AND PERISPOMENI 
/* 1FC2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1F74,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH VARIA AND YPOGEGRAMMENI 
/* 1FC3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FCC, 0x03B7,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH YPOGEGRAMMENI 
/* 1FC4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03AE,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH OXIA AND YPOGEGRAMMENI 
/* 1fc5 */ { 0x0000, 0x0000, 0x0000 },
/* 1FC6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03B7,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PERISPOMENI 
/* 1FC7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1FC6,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER ETA WITH PERISPOMENI AND YPOGEGRAMMENI 
/* 1FC8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F72, 0x0395,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH VARIA 
/* 1FC9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F73, 0x0388,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER EPSILON WITH OXIA 
/* 1FCA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F74, 0x0397,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH VARIA 
/* 1FCB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F75, 0x0389,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH OXIA 
/* 1FCC */ { lem::CP_Char_Flags::Char, 0x0000, 0x0397,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER ETA WITH PROSGEGRAMMENI 
/* 1FCD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x1FBF,0x0300,0x0000,0x0000 }, // GREEK PSILI AND VARIA 
/* 1FCE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x1FBF,0x0301,0x0000,0x0000 }, // GREEK PSILI AND OXIA 
/* 1FCF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x1FBF,0x0342,0x0000,0x0000 }, // GREEK PSILI AND PERISPOMENI 
/* 1FD0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FD8, 0x03B9,0x0306,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH VRACHY 
/* 1FD1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FD9, 0x03B9,0x0304,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH MACRON 
/* 1FD2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03CA,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND VARIA 
/* 1FD3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0390,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND OXIA 
/* 1fd4 */ { 0x0000, 0x0000, 0x0000 },
/* 1fd5 */ { 0x0000, 0x0000, 0x0000 },
/* 1FD6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03B9,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH PERISPOMENI 
/* 1FD7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03CA,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND PERISPOMENI 
/* 1FD8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1FD0, 0x0399,0x0306,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH VRACHY 
/* 1FD9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1FD1, 0x0399,0x0304,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH MACRON 
/* 1FDA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F76, 0x0399,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH VARIA 
/* 1FDB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F77, 0x038A,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER IOTA WITH OXIA 
/* 1fdc */ { 0x0000, 0x0000, 0x0000 },
/* 1FDD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x1FFE,0x0300,0x0000,0x0000 }, // GREEK DASIA AND VARIA 
/* 1FDE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x1FFE,0x0301,0x0000,0x0000 }, // GREEK DASIA AND OXIA 
/* 1FDF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x1FFE,0x0342,0x0000,0x0000 }, // GREEK DASIA AND PERISPOMENI 
/* 1FE0 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FE8, 0x03C5,0x0306,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH VRACHY 
/* 1FE1 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FE9, 0x03C5,0x0304,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH MACRON 
/* 1FE2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03CB,0x0300,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND VARIA 
/* 1FE3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03B0,0x0000,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND OXIA 
/* 1FE4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03C1,0x0313,0x0000,0x0000 }, // GREEK SMALL LETTER RHO WITH PSILI 
/* 1FE5 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FEC, 0x03C1,0x0314,0x0000,0x0000 }, // GREEK SMALL LETTER RHO WITH DASIA 
/* 1FE6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03C5,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH PERISPOMENI 
/* 1FE7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03CB,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND PERISPOMENI 
/* 1FE8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1FE0, 0x03A5,0x0306,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH VRACHY 
/* 1FE9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1FE1, 0x03A5,0x0304,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH MACRON 
/* 1FEA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F7A, 0x03A5,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH VARIA 
/* 1FEB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F7B, 0x038E,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER UPSILON WITH OXIA 
/* 1FEC */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1FE5, 0x03A1,0x0314,0x0000,0x0000 }, // GREEK CAPITAL LETTER RHO WITH DASIA 
/* 1FED */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x00A8,0x0300,0x0000,0x0000 }, // GREEK DIALYTIKA AND VARIA 
/* 1FEE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0385,0x0000,0x0000,0x0000 }, // GREEK DIALYTIKA AND OXIA 
/* 1FEF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0060,0x0000,0x0000,0x0000 }, // GREEK VARIA 
/* 1ff0 */ { 0x0000, 0x0000, 0x0000 },
/* 1ff1 */ { 0x0000, 0x0000, 0x0000 },
/* 1FF2 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1F7C,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH VARIA AND YPOGEGRAMMENI 
/* 1FF3 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x1FFC, 0x03C9,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH YPOGEGRAMMENI 
/* 1FF4 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03CE,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI 
/* 1ff5 */ { 0x0000, 0x0000, 0x0000 },
/* 1FF6 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x03C9,0x0342,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PERISPOMENI 
/* 1FF7 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x1FF6,0x0345,0x0000,0x0000 }, // GREEK SMALL LETTER OMEGA WITH PERISPOMENI AND YPOGEGRAMMENI 
/* 1FF8 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F78, 0x039F,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH VARIA 
/* 1FF9 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F79, 0x038C,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMICRON WITH OXIA 
/* 1FFA */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F7C, 0x03A9,0x0300,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH VARIA 
/* 1FFB */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Upper, 0x1F7D, 0x038F,0x0000,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH OXIA 
/* 1FFC */ { lem::CP_Char_Flags::Char, 0x0000, 0x03A9,0x0345,0x0000,0x0000 }, // GREEK CAPITAL LETTER OMEGA WITH PROSGEGRAMMENI 
/* 1FFD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x00B4,0x0000,0x0000,0x0000 }, // GREEK OXIA 
/* 1FFE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GREEK DASIA 
/* 1fff */ { 0x0000, 0x0000, 0x0000 },
/* 2000 */ { lem::CP_Char_Flags::Space, 0x0000, 0x2002,0x0000,0x0000,0x0000 }, // EN QUAD 
/* 2001 */ { lem::CP_Char_Flags::Space, 0x0000, 0x2003,0x0000,0x0000,0x0000 }, // EM QUAD 
/* 2002 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EN SPACE 
/* 2003 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EM SPACE 
/* 2004 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THREE-PER-EM SPACE 
/* 2005 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FOUR-PER-EM SPACE 
/* 2006 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SIX-PER-EM SPACE 
/* 2007 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FIGURE SPACE 
/* 2008 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PUNCTUATION SPACE 
/* 2009 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THIN SPACE 
/* 200A */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HAIR SPACE 
/* 200B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ZERO WIDTH SPACE 
/* 200C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ZERO WIDTH NON-JOINER 
/* 200D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ZERO WIDTH JOINER 
/* 200E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT-TO-RIGHT MARK 
/* 200F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT-TO-LEFT MARK 
/* 2010 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HYPHEN 
/* 2011 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NON-BREAKING HYPHEN 
/* 2012 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FIGURE DASH 
/* 2013 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EN DASH 
/* 2014 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EM DASH 
/* 2015 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HORIZONTAL BAR 
/* 2016 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE VERTICAL LINE 
/* 2017 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE LOW LINE 
/* 2018 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT SINGLE QUOTATION MARK 
/* 2019 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT SINGLE QUOTATION MARK 
/* 201A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINGLE LOW-9 QUOTATION MARK 
/* 201B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINGLE HIGH-REVERSED-9 QUOTATION MARK 
/* 201C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT DOUBLE QUOTATION MARK 
/* 201D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT DOUBLE QUOTATION MARK 
/* 201E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE LOW-9 QUOTATION MARK 
/* 201F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE HIGH-REVERSED-9 QUOTATION MARK 
/* 2020 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DAGGER 
/* 2021 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE DAGGER 
/* 2022 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BULLET 
/* 2023 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TRIANGULAR BULLET 
/* 2024 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ONE DOT LEADER 
/* 2025 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TWO DOT LEADER 
/* 2026 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HORIZONTAL ELLIPSIS 
/* 2027 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HYPHENATION POINT 
/* 2028 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LINE SEPARATOR 
/* 2029 */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PARAGRAPH SEPARATOR 
/* 202A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT-TO-RIGHT EMBEDDING 
/* 202B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT-TO-LEFT EMBEDDING 
/* 202C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // POP DIRECTIONAL FORMATTING 
/* 202D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT-TO-RIGHT OVERRIDE 
/* 202E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT-TO-LEFT OVERRIDE 
/* 202F */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NARROW NO-BREAK SPACE 
/* 2030 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PER MILLE SIGN 
/* 2031 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PER TEN THOUSAND SIGN 
/* 2032 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PRIME 
/* 2033 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE PRIME 
/* 2034 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TRIPLE PRIME 
/* 2035 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // REVERSED PRIME 
/* 2036 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // REVERSED DOUBLE PRIME 
/* 2037 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // REVERSED TRIPLE PRIME 
/* 2038 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CARET 
/* 2039 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINGLE LEFT-POINTING ANGLE QUOTATION MARK 
/* 203A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK 
/* 203B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // REFERENCE MARK 
/* 203C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE EXCLAMATION MARK 
/* 203D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // INTERROBANG 
/* 203E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // OVERLINE 
/* 203F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // UNDERTIE 
/* 2040 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CHARACTER TIE 
/* 2041 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CARET INSERTION POINT 
/* 2042 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ASTERISM 
/* 2043 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HYPHEN BULLET 
/* 2044 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FRACTION SLASH 
/* 2045 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LEFT SQUARE BRACKET WITH QUILL 
/* 2046 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RIGHT SQUARE BRACKET WITH QUILL 
/* 2047 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOUBLE QUESTION MARK 
/* 2048 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // QUESTION EXCLAMATION MARK 
/* 2049 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EXCLAMATION QUESTION MARK 
/* 204A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TIRONIAN SIGN ET 
/* 204B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // REVERSED PILCROW SIGN 
/* 204C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BLACK LEFTWARDS BULLET 
/* 204D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // BLACK RIGHTWARDS BULLET 
/* 204E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LOW ASTERISK 
/* 204F */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // REVERSED SEMICOLON 
/* 2050 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CLOSE UP 
/* 2051 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TWO ASTERISKS ALIGNED VERTICALLY 
/* 2052 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMMERCIAL MINUS SIGN 
/* 2053 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SWUNG DASH 
/* 2054 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // INVERTED UNDERTIE 
/* 2055 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FLOWER PUNCTUATION MARK 
/* 2056 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // THREE DOT PUNCTUATION 
/* 2057 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // QUADRUPLE PRIME 
/* 2058 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FOUR DOT PUNCTUATION 
/* 2059 */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FIVE DOT PUNCTUATION 
/* 205A */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TWO DOT PUNCTUATION 
/* 205B */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FOUR DOT MARK 
/* 205C */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DOTTED CROSS 
/* 205D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TRICOLON 
/* 205E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // VERTICAL FOUR DOTS 
/* 205F */ { lem::CP_Char_Flags::Space, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MEDIUM MATHEMATICAL SPACE 
/* 2060 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // WORD JOINER 
/* 2061 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FUNCTION APPLICATION 
/* 2062 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // INVISIBLE TIMES 
/* 2063 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // INVISIBLE SEPARATOR 
/* 2064 */ { 0x0000, 0x0000, 0x0000 },
/* 2065 */ { 0x0000, 0x0000, 0x0000 },
/* 2066 */ { 0x0000, 0x0000, 0x0000 },
/* 2067 */ { 0x0000, 0x0000, 0x0000 },
/* 2068 */ { 0x0000, 0x0000, 0x0000 },
/* 2069 */ { 0x0000, 0x0000, 0x0000 },
/* 206A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // INHIBIT SYMMETRIC SWAPPING 
/* 206B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ACTIVATE SYMMETRIC SWAPPING 
/* 206C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // INHIBIT ARABIC FORM SHAPING 
/* 206D */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // ACTIVATE ARABIC FORM SHAPING 
/* 206E */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NATIONAL DIGIT SHAPES 
/* 206F */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NOMINAL DIGIT SHAPES 
/* 2070 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT ZERO 
/* 2071 */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT LATIN SMALL LETTER I 
/* 2072 */ { 0x0000, 0x0000, 0x0000 },
/* 2073 */ { 0x0000, 0x0000, 0x0000 },
/* 2074 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT FOUR 
/* 2075 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT FIVE 
/* 2076 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT SIX 
/* 2077 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT SEVEN 
/* 2078 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT EIGHT 
/* 2079 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT NINE 
/* 207A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT PLUS SIGN 
/* 207B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT MINUS 
/* 207C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT EQUALS SIGN 
/* 207D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT LEFT PARENTHESIS 
/* 207E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT RIGHT PARENTHESIS 
/* 207F */ { lem::CP_Char_Flags::Char | lem::CP_Char_Flags::Lower, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUPERSCRIPT LATIN SMALL LETTER N 
/* 2080 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT ZERO 
/* 2081 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT ONE 
/* 2082 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT TWO 
/* 2083 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT THREE 
/* 2084 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT FOUR 
/* 2085 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT FIVE 
/* 2086 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT SIX 
/* 2087 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT SEVEN 
/* 2088 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT EIGHT 
/* 2089 */ { lem::CP_Char_Flags::Digit, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT NINE 
/* 208A */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT PLUS SIGN 
/* 208B */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT MINUS 
/* 208C */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT EQUALS SIGN 
/* 208D */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT LEFT PARENTHESIS 
/* 208E */ { lem::CP_Char_Flags::Punkt, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // SUBSCRIPT RIGHT PARENTHESIS 
/* 208f */ { 0x0000, 0x0000, 0x0000 },
/* 2090 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER A 
/* 2091 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER E 
/* 2092 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER O 
/* 2093 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER X 
/* 2094 */ { lem::CP_Char_Flags::Char, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LATIN SUBSCRIPT SMALL LETTER SCHWA 
/* 2095 */ { 0x0000, 0x0000, 0x0000 },
/* 2096 */ { 0x0000, 0x0000, 0x0000 },
/* 2097 */ { 0x0000, 0x0000, 0x0000 },
/* 2098 */ { 0x0000, 0x0000, 0x0000 },
/* 2099 */ { 0x0000, 0x0000, 0x0000 },
/* 209a */ { 0x0000, 0x0000, 0x0000 },
/* 209b */ { 0x0000, 0x0000, 0x0000 },
/* 209c */ { 0x0000, 0x0000, 0x0000 },
/* 209d */ { 0x0000, 0x0000, 0x0000 },
/* 209e */ { 0x0000, 0x0000, 0x0000 },
/* 209f */ { 0x0000, 0x0000, 0x0000 },
/* 20A0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EURO-CURRENCY SIGN 
/* 20A1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COLON SIGN 
/* 20A2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CRUZEIRO SIGN 
/* 20A3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // FRENCH FRANC SIGN 
/* 20A4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // LIRA SIGN 
/* 20A5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // MILL SIGN 
/* 20A6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NAIRA SIGN 
/* 20A7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PESETA SIGN 
/* 20A8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // RUPEE SIGN 
/* 20A9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // WON SIGN 
/* 20AA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // NEW SHEQEL SIGN 
/* 20AB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DONG SIGN 
/* 20AC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // EURO SIGN 
/* 20AD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // KIP SIGN 
/* 20AE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // TUGRIK SIGN 
/* 20AF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // DRACHMA SIGN 
/* 20B0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GERMAN PENNY SIGN 
/* 20B1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // PESO SIGN 
/* 20B2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // GUARANI SIGN 
/* 20B3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // AUSTRAL SIGN 
/* 20B4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // HRYVNIA SIGN 
/* 20B5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // CEDI SIGN 
/* 20b6 */ { 0x0000, 0x0000, 0x0000 },
/* 20b7 */ { 0x0000, 0x0000, 0x0000 },
/* 20b8 */ { 0x0000, 0x0000, 0x0000 },
/* 20b9 */ { 0x0000, 0x0000, 0x0000 },
/* 20ba */ { 0x0000, 0x0000, 0x0000 },
/* 20bb */ { 0x0000, 0x0000, 0x0000 },
/* 20bc */ { 0x0000, 0x0000, 0x0000 },
/* 20bd */ { 0x0000, 0x0000, 0x0000 },
/* 20be */ { 0x0000, 0x0000, 0x0000 },
/* 20bf */ { 0x0000, 0x0000, 0x0000 },
/* 20c0 */ { 0x0000, 0x0000, 0x0000 },
/* 20c1 */ { 0x0000, 0x0000, 0x0000 },
/* 20c2 */ { 0x0000, 0x0000, 0x0000 },
/* 20c3 */ { 0x0000, 0x0000, 0x0000 },
/* 20c4 */ { 0x0000, 0x0000, 0x0000 },
/* 20c5 */ { 0x0000, 0x0000, 0x0000 },
/* 20c6 */ { 0x0000, 0x0000, 0x0000 },
/* 20c7 */ { 0x0000, 0x0000, 0x0000 },
/* 20c8 */ { 0x0000, 0x0000, 0x0000 },
/* 20c9 */ { 0x0000, 0x0000, 0x0000 },
/* 20ca */ { 0x0000, 0x0000, 0x0000 },
/* 20cb */ { 0x0000, 0x0000, 0x0000 },
/* 20cc */ { 0x0000, 0x0000, 0x0000 },
/* 20cd */ { 0x0000, 0x0000, 0x0000 },
/* 20ce */ { 0x0000, 0x0000, 0x0000 },
/* 20cf */ { 0x0000, 0x0000, 0x0000 },
/* 20D0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT HARPOON ABOVE 
/* 20D1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RIGHT HARPOON ABOVE 
/* 20D2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LONG VERTICAL LINE OVERLAY 
/* 20D3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING SHORT VERTICAL LINE OVERLAY 
/* 20D4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ANTICLOCKWISE ARROW ABOVE 
/* 20D5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CLOCKWISE ARROW ABOVE 
/* 20D6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT ARROW ABOVE 
/* 20D7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RIGHT ARROW ABOVE 
/* 20D8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING RING OVERLAY 
/* 20D9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING CLOCKWISE RING OVERLAY 
/* 20DA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ANTICLOCKWISE RING OVERLAY 
/* 20DB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING THREE DOTS ABOVE 
/* 20DC */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING FOUR DOTS ABOVE 
/* 20DD */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ENCLOSING CIRCLE 
/* 20DE */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ENCLOSING SQUARE 
/* 20DF */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ENCLOSING DIAMOND 
/* 20E0 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ENCLOSING CIRCLE BACKSLASH 
/* 20E1 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFT RIGHT ARROW ABOVE 
/* 20E2 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ENCLOSING SCREEN 
/* 20E3 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ENCLOSING KEYCAP 
/* 20E4 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ENCLOSING UPWARD POINTING TRIANGLE 
/* 20E5 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING REVERSE SOLIDUS OVERLAY 
/* 20E6 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING DOUBLE VERTICAL STROKE OVERLAY 
/* 20E7 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING ANNUITY SYMBOL 
/* 20E8 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING TRIPLE UNDERDOT 
/* 20E9 */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING WIDE BRIDGE ABOVE 
/* 20EA */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LEFTWARDS ARROW OVERLAY 
/* 20EB */ { lem::CP_Char_Flags::Unknown, 0x0000, 0x0000,0x0000,0x0000,0x0000 }, // COMBINING LONG DOUBLE SOLIDUS OVERLAY 
 };
#endif
