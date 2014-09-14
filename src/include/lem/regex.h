// -----------------------------------------------------------------------------
// File REGEX.H
//
// (c) Koziev Elijah
//
// Content:
// Работа с регулярными выражениями - сревнение строки с паттерном.
// Благодаря использованию template'ов можно работать с 1- и 2-байтовыми
// символами.
//
// Смотрите сервисную функцию regex_does_match в самом конце файла.
//
// Реализация алгоритма - см. сноски в файле.
// -----------------------------------------------------------------------------
//
// CD->28.09.2000
// LC->11.10.2009
// --------------

#ifndef LEM_REGEX__H
#define LEM_REGEX__H
#pragma once

 #include <lem/config.h>

 namespace lem
 {
 /*
  EPSHeader

    File: match.h
    Author: J. Kercheval
    Created: Sat, 01/05/1991  22:27:18
 */
 /*
  EPSRevision History

    J. Kercheval  Wed, 02/20/1991  22:28:37  Released to Public Domain
    J. Kercheval  Sun, 03/10/1991  18:02:56  add is_valid_pattern
    J. Kercheval  Sun, 03/10/1991  18:25:48  add error_type in is_valid_pattern
    J. Kercheval  Sun, 03/10/1991  18:47:47  error return from matche()
    J. Kercheval  Tue, 03/12/1991  22:24:49  Released as V1.1 to Public Domain
 */

// Wildcard Pattern Matching

 /* match defines */
 const int REGEX_PATTERN  = 6;    /* bad pattern */
 const int REGEX_LITERAL  = 5;    /* match failure on literal match */
 const int REGEX_RANGE    = 4;    /* match failure on [..] construct */
 const int REGEX_ABORT    = 3;    /* premature end of text string */
 const int REGEX_END      = 2;    /* premature end of pattern string */
 const int REGEX_VALID    = 1;    /* valid match */

 /* pattern defines */
 const int REGEX_PATTERN_VALID  = 0;    /* valid pattern */
 const int REGEX_PATTERN_ESC    = -1;    /* literal escape at end of pattern */
 const int REGEX_PATTERN_RANGE  = -2;    /* malformed range in [..] construct */
 const int REGEX_PATTERN_CLOSE  = -3;    /* no end bracket in [..] construct */
 const int REGEX_PATTERN_EMPTY  = -4;    /* [..] contstruct is empty */

 /*----------------------------------------------------------------------------
 *
 *  Match the pattern PATTERN against the string TEXT;
 *
 *       match() returns TRUE if pattern matches, FALSE otherwise.
 *       matche() returns MATCH_VALID if pattern matches, or an errorcode
 *           as follows otherwise:
 *
 *            REGEX_PATTERN  - bad pattern
 *            REGEX_LITERAL  - match failure on literal mismatch
 *            REGEX_RANGE    - match failure on [..] construct
 *            REGEX_ABORT    - premature end of text string
 *            REGEX_END      - premature end of pattern string
 *            REGEX_VALID    - valid match
 *
 *
 *  A match means the entire string TEXT is used up in matching.
 *
 *  In the pattern string:
 *       `*' matches any sequence of characters (zero or more)
 *       `?' matches any character
 *       [SET] matches any character in the specified set,
 *       [!SET] or [^SET] matches any character not in the specified set.
 *
 *  A set is composed of characters or ranges; a range looks like
 *  character hyphen character (as in 0-9 or A-Z).  [0-9a-zA-Z_] is the
 *  minimal set of characters allowed in the [..] pattern construct.
 *  Other characters are allowed (ie. 8 bit characters) if your system
 *  will support them.
 *
 *  To suppress the special syntactic significance of any of `[]*?!^-\',
 *  and match the character exactly, precede it with a `\'.
 *
 ----------------------------------------------------------------------------*/

 /*---------------- ------------------------------------------------------------
 *
 * Return true if PATTERN has any special wildcard characters
 *
 ----------------------------------------------------------------------------*/
 template< class CHAR>
 inline bool regex_is_pattern( const CHAR *p )
 {
  if( !p )
   return false;

  while( *p )
   switch ( *p++ )
   {
    case '?':
    case '*':
    case '[':
    case '\\': return true;
   }

  return false;
 }

 /*----------------------------------------------------------------------------
 *
 * Return true if PATTERN has is a well formed regular expression according
 * to the above syntax
 *
 * error_type is a return code based on the type of pattern error.  Zero is
 * returned in error_type if the pattern is a valid one.  error_type return
 * values are as follows:
 *
 *   REGEX_PATTERN_VALID - pattern is well formed
 *   REGEX_PATTERN_ESC   - pattern has invalid escape ('\' at end of pattern)
 *   REGEX_PATTERN_RANGE - [..] construct has a no end range in a '-' pair (ie [a-])
 *   REGEX_PATTERN_CLOSE - [..] construct has no end bracket (ie [abc-g )
 *   REGEX_PATTERN_EMPTY - [..] construct is empty (ie [])
 *
 ----------------------------------------------------------------------------*/
 template< class CHAR >
 inline bool regex_is_valid_pattern( const CHAR *p, int *error_type )
 {
  /* init error_type */
  *error_type = REGEX_PATTERN_VALID;

  /* loop through pattern to EOS */
  while( *p )
  {
   /* determine pattern type */
   switch( *p )
   {
    /* check literal escape, it cannot be at end of pattern */
    case '\\':
     if( !*++p )
      {
       *error_type = REGEX_PATTERN_ESC;
       return false;
      }
     p++;
     break;

    /* the [..] construct must be well formed */
    case '[':
     p++;
     /* if the next character is ']' then bad pattern */
     if( *p == ']' )
      {
       *error_type = REGEX_PATTERN_EMPTY;
       return false;
      }

     /* if end of pattern here then bad pattern */
     if( !*p )
      {
       *error_type = REGEX_PATTERN_CLOSE;
       return false;
      }

     /* loop to end of [..] construct */
     while( *p != ']' )
      {
       /* check for literal escape */
       if( *p == '\\' )
        {
         p++;

          /* if end of pattern here then bad pattern */
          if( !*p++ )
           {
            *error_type = REGEX_PATTERN_ESC;
            return false;
           }
        }
       else
        p++;

       /* if end of pattern here then bad pattern */
       if( !*p )
        {
         *error_type = REGEX_PATTERN_CLOSE;
         return false;
        }

       /* if this a range */
       if( *p == '-' )
        {
         /* we must have an end of range */
         if( !*++p || *p == ']' )
          {
           *error_type = REGEX_PATTERN_RANGE;
           return false;
          }
         else
          {
           /* check for literal escape */
           if( *p == '\\' )
            p++;

           /* if end of pattern here then bad pattern */
           if( !*p++ )
            {
             *error_type = REGEX_PATTERN_ESC;
             return false;
            }
          }
        }
      }
     break;

    /* all other characters are valid pattern elements */
    case '*':
    case '?':
    default:
     p++;                              /* "normal" character */
     break;
   }
  }

  return true;
 }


 /*----------------------------------------------------------------------------
 *
 *  Match the pattern PATTERN against the string TEXT;
 *
 *  returns LEM_REGEX_VALID if pattern matches, or an errorcode as follows
 *  otherwise:
 *
 *            REGEX_PATTERN  - bad pattern
 *            REGEX_LITERAL  - match failure on literal mismatch
 *            REGEX_RANGE    - match failure on [..] construct
 *            REGEX_ABORT    - premature end of text string
 *            REGEX_END      - premature end of pattern string
 *            REGEX_VALID    - valid match
 *
 *
 *  A match means the entire string TEXT is used up in matching.
 *
 *  In the pattern string:
 *       `*' matches any sequence of characters (zero or more)
 *       `?' matches any character
 *       [SET] matches any character in the specified set,
 *       [!SET] or [^SET] matches any character not in the specified set.
 *
 *  A set is composed of characters or ranges; a range looks like
 *  character hyphen character (as in 0-9 or A-Z).  [0-9a-zA-Z_] is the
 *  minimal set of characters allowed in the [..] pattern construct.
 *  Other characters are allowed (ie. 8 bit characters) if your system
 *  will support them.
 *
 *  To suppress the special syntactic significance of any of `[]*?!^-\',
 *  and match the character exactly, precede it with a `\'.
 *
 ----------------------------------------------------------------------------*/
 template < class CHAR >
 inline int regex_matche( const CHAR *p, const CHAR *t )
 {
  CHAR range_start, range_end;  /* start and end in range */

  bool invert;             /* is this [..] or [!..] */
  bool member_match;       /* have I matched the [..] construct? */
  bool loop;               /* should I terminate? */

  for( ; *p; p++, t++ )
   {
    /* if this is the end of the text then this is the end of the match */
    if(!*t)
     return ( *p == '*' && *++p == '\0' ) ? REGEX_VALID : REGEX_ABORT;

    /* determine and react to pattern type */
    switch ( *p )
    {
     /* single any character match */
     case '?': break;

     /* multiple any character match */
     case '*': return matche_after_star( p, t );

     /* [..] construct, single member/exclusion character match */
     case '[':
      {
       /* move to beginning of range */
       p++;

       /* check if this is a member match or exclusion match */
       invert = false;
       if( *p == '!' || *p == '^' )
        {
         invert = true;
         p++;
        }

       /* if closing bracket here or at range start then we have a
          malformed pattern */
       if( *p == ']' )
        return REGEX_PATTERN;

       member_match = false;
       loop = true;

       while( loop )
        {
         /* if end of construct then loop is done */
         if(*p == ']')
          {
           loop = false;
           continue;
          }

         /* matching a '!', '^', '-', '\' or a ']' */
         if( *p == '\\' )
          range_start = range_end = *++p;
         else
          range_start = range_end = *p;

         /* if end of pattern then bad pattern (Missing ']') */
         if(!*p)
          return REGEX_PATTERN;

         /* check for range bar */
         if(*++p == '-')
          {
           /* get the range end */
           range_end = *++p;

           /* if end of pattern or construct then bad pattern */
           if( range_end == '\0' || range_end == ']' )
            return REGEX_PATTERN;

           /* special character range end */
           if( range_end == '\\' )
            {
             range_end = *++p;

             /* if end of text then we have a bad pattern */
             if(!range_end)
              return REGEX_PATTERN;
            }

           /* move just beyond this range */
           p++;
          }

         /* if the text character is in range then match found.
            make sure the range letters have the proper
            relationship to one another before comparison */
         if( range_start < range_end  )
          {
           if( *t >= range_start && *t <= range_end )
            {
             member_match = true;
             loop = false;
            }
          }
         else
          {
           if( *t >= range_end && *t <= range_start )
            {
             member_match = true;
             loop = false;
            }
          }
        }

       /* if there was a match in an exclusion set then no match */
       /* if there was no match in a member set then no match */
       if(
          (invert && member_match) ||
          !(invert || member_match)
         )
        return REGEX_RANGE;

       /* if this is not an exclusion then skip the rest of the [...]
          construct that already matched. */
       if(member_match)
        {
         while( *p != ']' )
          {
           /* bad pattern (Missing ']') */
           if(!*p)
            return REGEX_PATTERN;

           /* skip exact match */
           if(*p == '\\')
            {
             p++;

             /* if end of text then we have a bad pattern */
             if(!*p)
              return REGEX_PATTERN;
            }

           /* move to next pattern char */
           p++;
          }
        }

        break;
       }

      /* next character is quoted and must match exactly */
      case '\\':
       /* move pattern pointer to quoted char and fall through */
       p++;

       /* if end of text then we have a bad pattern */
       if(!*p)
        return REGEX_PATTERN;

       /* must match this character exactly */
       default:
        if(*p != *t)
         return REGEX_LITERAL;
    } // switch
   } // for

  /* if end of text not reached then the pattern fails */
  if( *t )
   return REGEX_END;
  else
   return REGEX_VALID;
 }

 /*----------------------------------------------------------------------------
 *
 * recursively call matche() with final segment of PATTERN and of TEXT.
 *
 ----------------------------------------------------------------------------*/
 template < class CHAR >
 inline int matche_after_star( const CHAR *p, const CHAR *t )
 {
  int match = 0;
  int nextp;

  /* pass over existing ? and * in pattern */
  while( *p == '?' || *p == '*' )
   {
    /* take one char for each ? and + */
    if( *p == '?' )
     {
      /* if end of text then no match */
      if( !*t++ )
       return REGEX_ABORT;
     }

    /* move to next char in pattern */
    p++;
   }

   /* if end of pattern we have matched regardless of text left */
   if( !*p )
    return REGEX_VALID;

   /* get the next character to match which must be a literal or '[' */
   nextp = *p;
   if( nextp == '\\' )
    {
     nextp = p[1];

     /* if end of text then we have a bad pattern */
     if(!nextp)
      return REGEX_PATTERN;
    }

   /* Continue until we run out of text or definite result seen */
   do
    {
     /* a precondition for matching is that the next character
        in the pattern match the next character in the text or that
        the next pattern char is the beginning of a range.  Increment
        text pointer as we go here */
     if( nextp == *t || nextp == '[' )
      match = regex_matche(p, t);

     /* if the end of text is reached then no match */
     if( !*t++ )
      match = REGEX_ABORT;
    }
   while(
         match != REGEX_VALID &&
         match != REGEX_ABORT &&
         match != REGEX_PATTERN
        );

  /* return result */
  return match;
 }

 /*----------------------------------------------------------------------------
 *
 * match() is a shell to matche() to return only bool values.
 *
 ----------------------------------------------------------------------------*/
 template < class CHAR >
 inline bool regex_match( const CHAR *Pattern, const CHAR *Text )
 {
  int error_type = regex_matche(Pattern,Text);
  return (error_type == REGEX_VALID ) ? true : false;
 }

  // ********************************************************
  // Функция для использования в прикладных программах.
  // ********************************************************
  template < class CHAR >
  inline bool regex_does_match( const CHAR *Pattern, const CHAR *Text )
  {
   if( !regex_is_pattern(Pattern) )
    return lem_eq( Text, Pattern );

   const int error = regex_matche(Pattern,Text);
   if( error==REGEX_VALID )
    return true;

   return false;
  }
 } // namespace 'lem'

#endif
