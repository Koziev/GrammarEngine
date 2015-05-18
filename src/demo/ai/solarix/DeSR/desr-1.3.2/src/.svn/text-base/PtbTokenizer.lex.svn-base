%{

#include "Tokenizer.h"
#include <string>

using namespace std;

static char const* opendblquote = "``";
static char const* closedblquote = "''";
static char const* openparen = "-LRB-";
static char const* closeparen = "-RRB-";
static char const* openbrace = "-LCB-";
static char const* closebrace = "-RCB-";
static char const* ptbmdash = "--";

/** This quotes a character with a backslash, but doesn't do it
 *  if the character is already preceded by a backslash
 */
static char* escape(char const* s, char c) {
  std::string r;
  char const* o;
  while (o = strchr(s, c)) {
    if (o == s || o[-1] != '\\') {
      r.append(s, o - s); r += "\\"; r += c;
    } 
    s = o + 1;
  }
  r += s;
  return strdup(r.c_str());
}

%}

%option  noyywrap
%option case-sensitive

/* Definitions */

SGML	<\/?[A-Za-z!][^>]*>
SPMDASH	&(MD|mdash);
SPPUNC	&(MD|HT|TL|UR|LR|QC|QL|QR|odq|cdq|mdash|lt|gt|amp|AMP|#[0-9]+);
SPLET	&[aeiou](acute|grave|uml);
SPACE	[ \t]+
SPACENL	[ \t\n]+
SENTEND	[ \t\n][ \t\n]+|[ \t\n]+([A-Z]|{SGML})
DIGIT	[0-9]
DATE	{DIGIT}{1,2}[\-\/]{DIGIT}{1,2}[\-\/]{DIGIT}{2,4}
NUM	{DIGIT}+|{DIGIT}*([\.:,]{DIGIT}+)+
NUMBER	[\-+]?{NUM}|\({NUM}\)
FRAC	{DIGIT}+\\?\/{DIGIT}+
DOLSIGN	([A-Z]*\$|#)
/* not used DOLLAR	{DOLSIGN}[ \t]*{NUMBER}  */
/* |\( ?{NUMBER} ?\))	 # is for pound signs */
WORD	([A-Za-z]|{SPLET})+
/* The $ was for things like New$ */
/* WAS: only keep hyphens with short one side like co-ed */
/* But treebank just allows hyphenated things as words! */
THING	[A-Za-z0-9][A-Za-z0-9_]*[A-Za-z0-9]|[A-Z][A-Z&+_;-]+[A-Z+]
THING2	[A-Za-z0-9][A-Za-z0-9%.,]*(-([A-Za-z0-9]+|{ACRO}\.))+
THING3	[A-Za-z0-9]+\\?\/[A-Za-z0-9]+(-[A-Za-z0-9]+)?
APOS	['\222]
HTHING	{THING2}|[dDOlL]{APOS}{THING}
REDAUX1	{APOS}[mMsSdD]
REDAUX2	{APOS}(re|RE|ve|VE|ll|LL)
/* For things that will have n't on the end */
SWORD	[A-Za-z]*[A-MO-Za-mo-z]
SREDAUX	[nN]{APOS}[tT]
/* Tokens you want but already okay: C'mon 'n' '[2-9]0s '[eE]m 'till?
   [Yy]'all 'Cause Shi'ite B'Gosh o'clock.  Here now only need apostrophe
   final words. 'n' is a token from dunno where. */
APOWORD	{APOS}n{APOS}|Dunkin{APOS}|[Ss]omethin{APOS}|ol{APOS}|{APOS}[Ee]m|C{APOS}[Mm][Oo][Nn]|{APOS}[2-9]0s|{APOS}till?|o{APOS}clock|Shi{APOS}ite|{APOS}[cC]ause
FULLURL	http:\/\/[^ \t\n\f\r\"<>|()]+[^ \t\n\f\r\"<>|.!?(){},-]

/* Abbreviations - induced from 1987 WSJ by hand */
ABMONTH	Jan|Feb|Mar|Apr|Jun|Jul|Aug|Sep|Sept|Oct|Nov|Dec
/* Jun and Jul barely occur, but don't seem dangerous */
ABDAYS	Mon|Tue|Tues|Wed|Thu|Thurs|Fri|a\.m|p\.m
/* Sat. and Sun. barely occur and can easily lead to errors, so we omit them */
ABSTATE	Calif|Mass|Conn|Fla|Ill|Mich|Pa|Va|Ariz|Tenn|Mo|Md|Wis|Minn|Ind|Okla|Wash|Kan|Ore|Ga|Colo|Ky|Del|Ala|La|Nev|Neb|Ark|Miss|Vt|Wyo|Tex
ACRO	[A-Za-z](\.[A-Za-z])+|(Canada|Sino|Korean|Japan|non)-U\.S|U\.S\.-(U\.K|U\.S\.S\.R)
ABLIST	[a-e]
ABTITLE	Mr|Mrs|Ms|Dr|Prof|Sen|Reps?|Lt|Col|Gen|Messrs|Gov|Adm|Rev|Maj|Sgt|Capt|Sens|St|Ave
ABPTIT	Jr|Bros|Sr
ABCOMP	Inc|INC|Co|CO|Cos|COS|Corp|CORP|Pty|Ltd|Plc
/* What about capitalization?  CORP. etc. */
ABNUM	p|No
/* ABBREV1 abbreviations are normally followed by lower case words.  If
   they're followed by an uppercase one, we assume there is also a
   sentence boundary */
ABBREV3	{ABMONTH}|{ABDAYS}|{ABSTATE}|{ABCOMP}|{ABNUM}|{ABPTIT}|[Ee]tc|Ph|ft
ABBREV1	{ABBREV3}\.
/* ABRREV2 abbreviations are normally followed by an upper case word.  We
   assume they aren't used sentence finally */
/* ACRO Is a bad case -- can go either way! */
ABBREV4	[A-Z]|{ABTITLE}|{ABLIST}|vs|v|Alex|Cie|a.k.a|TREAS|{ACRO}
ABBREV2	{ABBREV4}\.
/* Cie. is used before French companies */
/* in the WSJ Alex. is generally an abbreviation for Alex. Brown, brokers! */
/* In tables: Mkt. for market Div. for division of company, Chg., Yr.: year */

PHONE	\([0-9]{3}\)\ ?[0-9]{3}[\- ][0-9]{4}
OPBRAC	[<\[]
CLBRAC	[>\]]
HYPHENS	\-+
LDOTS	\.{3,5}|(\.\ ){2,4}\.
ATS	@+
UNDS	_+
ASTS	\*+|(\\*)+
HASHES	#+
FNMARKS	{ATS}|{HASHES}|{UNDS}
INSENTP	[,;:]
QUOTES	`|{APOS}|``|''
DBLQUOT	\"|&quot;
TBSPEC	\-(RRB|LRB|RCB|LCB|RSB|LSB)\-|S&Ls

%%
	/* Rules Section */

{SGML}			{ return Token(strdup(yytext), Tag); }
{SPMDASH}		{ return Token(strdup(ptbmdash), Punct); }
{SPPUNC}		{ return Token(strdup(yytext), Punct); }
{WORD}/{REDAUX1}	{ return Token(strdup(yytext), Word); }
{WORD}/{REDAUX2}	{ return Token(strdup(yytext), Word); }
{SWORD}/{SREDAUX}	{ unput(yytext[yyleng-1]), Token(strdup(yytext), Word); }
{WORD}			{ return Token(strdup(yytext), Word); }
{APOWORD}		{ return Token(strdup(yytext), Word); }
{FULLURL}		{ return Token(strdup(yytext), Url); }
{REDAUX1}/[^A-Za-z]	{ return Token(strdup(yytext), Word); }
{REDAUX2}/[^A-Za-z]	{ return Token(strdup(yytext), Word); }
{SREDAUX}		{ return Token(strdup(yytext), Word); }
{DATE}			{ return Token(strdup(yytext), Date); }
{NUMBER}		{ return Token(strdup(yytext), Number); }
{FRAC}			{ return Token(escape(yytext, '/'), Word); }
{THING3}		{ return Token(escape(yytext, '/'), Word); }
{DOLSIGN}		{ return Token(strdup(yytext), Word); }
{ABBREV1}/{SENTEND}	{ char* abbr = yytext; 
			  unput(yytext[yyleng-1]);
	                  return Token(strdup(abbr), Abbrev); }
{ABBREV1}		{ return Token(strdup(yytext), Abbrev); }
{ABBREV2}		{ return Token(strdup(yytext), Abbrev); }
{ABBREV3}/{SPACE}	{ return Token(strdup(yytext), Abbrev); }
{ABBREV4}/{SPACE}	{ return Token(strdup(yytext), Abbrev); }
{ACRO}/{SPACENL}	{ return Token(strdup(yytext), Abbrev); }
{TBSPEC}/{SPACENL}	{ return Token(strdup(yytext), Word); }
{WORD}\./{INSENTP}	{ return Token(strdup(yytext), Word); }
{PHONE}			{ return Token(strdup(yytext), Phone); }
{DBLQUOT}/[A-Za-z0-9$]	{ return Token(strdup(opendblquote), Punct); }
{DBLQUOT}		{ return Token(strdup(closedblquote), Punct); }
{QUOTES}		{ return Token(strdup(yytext), Punct); }
\+		{ return Token(strdup(yytext), Punct); }
%|&		{ return Token(strdup(yytext), Punct); }
\~|\^		{ return Token(strdup(yytext), Punct); }
\||\\|0x7f	{ /* ignore */ }
{OPBRAC}	{ return Token(strdup(yytext), Punct); }
{CLBRAC}	{ return Token(strdup(yytext), Punct); }
\{		{ return Token(strdup(openbrace), Punct); }
\}		{ return Token(strdup(closebrace), Punct); }
\(		{ return Token(strdup(openparen), Punct); }
\)		{ return Token(strdup(closeparen), Punct); }
{HYPHENS}	{ if (yyleng >= 3 && yyleng <= 4) 
    		    return Token(strdup(ptbmdash), Punct);
                  else
		    return Token(strdup(yytext), Punct);
		}
{LDOTS}		{ return Token(strdup(yytext), Punct); }
{FNMARKS}	{ return Token(strdup(yytext), Punct); }
{ASTS}		{ return Token(escape(yytext, '*'), Punct); }
{INSENTP}	{ return Token(strdup(yytext), Punct); }
\.|\?|\!	{ return Token(strdup(yytext), Punct); }
=		{ return Token(strdup(yytext), Punct); }
\/		{ return Token(strdup(yytext), Punct); }
{HTHING}/[^a-zA-Z0-9\.+]    {  return Token(strdup(yytext), Word); }
{THING}		{ return Token(strdup(yytext), Word); }
\0|{SPACE}	{ /* ignore */ }
&nbsp;		{ /* ignore */ }
.		{ std::cerr << yytext; }
 <<EOF>> { return Token(strdup(""), Eof); }
