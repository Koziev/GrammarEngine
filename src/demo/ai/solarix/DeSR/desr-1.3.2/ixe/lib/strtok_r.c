/*
**	IXE
**	lib/strtok_r.c: tokenize string with delimiter in control
** ----------------------------------------------------------------------
**	Copyright (c) 2004  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
*/

#include <string.h>

char* strtok_r(char *s, char const * delim, char **nextoken)
{
  char* token = 0;		/* Initialize to no token. */
  int toklen;

  if (s == 0)			/* If not first time called... */
    s = *nextoken;		/* restart from where we left off. */

  s += strspn(s, delim);	/* Skip past any leading delimiters. */
  toklen = strcspn(s, delim);	/* Find token's end. */
  if (toklen) {			/* got token. */
    token = s;
    s += toklen;
    if (*s)			/* if not at end of string... */
      *s++ = '\0';	 /* Terminate the token and move NEXTOKEN past it.  */
  }
  *nextoken = s;		/* Update nextoken. */
  return token;
}
