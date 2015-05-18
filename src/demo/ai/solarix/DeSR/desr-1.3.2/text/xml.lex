%{

#include "xml.h"

using namespace std;

%}
%option noyywrap

STRING		\"([^"]|\\\")*\"
ATTR_VAL	{STRING}|\'([^']|\\\')*\'
IDENT		[a-zA-Z_][a-zA-Z0-9_.]*
ID		{IDENT}(:{IDENT})?
PCDATA		[^<]+
CDATA		<!\[CDATA\[.*]]>
WS		[ \n\r\t]
CONTENT		EMPTY|ANY|"("{WS}*#PCDATA{WS}*")"
ELEM_DECL	<!ELEMENT{WS}+{IDENT}{WS}+{CONTENT}{WS}*>
DECL_VAL	CDATA|NMTOKEN|NMTOKENS|ID|IDREF|IDREFS|ENTITY|ENTITIES
DEFAULT		{STRING}|#REQUIRED|#IMPLIED|#FIXED{WS}+{STRING}
ATTR_DECL	<!ATTLIST{WS}+{IDENT}({WS}+{IDENT}{WS}+{DECL_VAL}{WS}+{DEFAULT})+{WS}*>
DECLARATIONS	"["({ELEM_DECL}|{ATTR_DECL}|{WS})+"]"
EXT_ID		(SYSTEM{WS}+{STRING}|PUBLIC{WS}+{STRING}{WS}+{STRING})
DOCTYPE		<!DOCTYPE{WS}+{IDENT}{WS}+{EXT_ID}({WS}+{DECLARATIONS})?{WS}*>
NOTATION	<!NOTATION{WS}+{IDENT}{WS}+{EXT_ID}{WS}*>
ENTITY_PAR	<!ENTITY{WS}+%{WS}+{IDENT}{WS}+{EXT_ID}{WS}*>

%x IN_XML
%x IN_TAG
%%

"<?xml"/[^>]*"?>"	{ BEGIN(IN_XML); return XML_DECL; }
<IN_XML>{ID}		return ID;
<IN_XML>"="		return EQ;
<IN_XML>{ATTR_VAL}	{ yytext[yyleng-1] = '\0'; yytext++; return VAL; }
<IN_XML>"?>"		{ BEGIN(INITIAL); return TAG_EMPTY; }
<IN_XML>{WS}
"<?"[^>]*"?>"		return PROC_INST;
"<!--"[^>]*">"		return COMMENT;
{NOTATION}		return NOTATION;
{DOCTYPE}		return DOCTYPE;
{CDATA}			{ yytext[yyleng-3] = '\0'; yytext += 9; return RAW_CHARS; }
"</"{ID}{WS}?>		return TAG_CLOSE;
"<"			{ BEGIN(IN_TAG); return TAG_OPEN; }
[ \t\n\r]*/<		return WHITESPACE;
{PCDATA}		return CHARACTERS;
<IN_TAG>{ID}		return ID;
<IN_TAG>"="		return EQ;
<IN_TAG>{ATTR_VAL}	{ yytext[yyleng-1] = '\0'; yytext++; return VAL; }
<IN_TAG>"/>"		{ BEGIN(INITIAL); return TAG_EMPTY; }
<IN_TAG>">"		{ BEGIN(INITIAL); return TAG_END; }
<IN_TAG>{WS}
<<EOF>>			return EoF;

%%
