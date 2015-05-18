/*
**	Tanl
**	text/RegExp.cpp: regular expression matcher
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
*/
//
// Copyright (C) 2000-2003 by Roger Rene Kommer / artefaktur, Kassel, Germany.
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License (LGPL) or the Q public License (QPL).
// 
// Modified for use with DeSR.
// Copyright (c) 2003 by Giuseppe Attardi (attardi@di.unipi.it).
//

#include "text/RegExp.h"
#include <assert.h>

#include "text/strings.h" 	// overloaded +(string, int)

using namespace std;

namespace Tanl {
namespace Text {
namespace RegExp {

const unsigned char* Pattern::setLocale(char const* locale)
{
  free((void*)CharTables);
  char* oldLocale = setlocale(LC_CTYPE, NULL);
  setlocale(LC_CTYPE, locale);
  CharTables = pcre_maketables();
  setlocale(LC_CTYPE, oldLocale);
  return CharTables;
}

const unsigned char* Pattern::CharTables = Pattern::setLocale(setlocale(LC_CTYPE, 0));

Pattern::Pattern(char const* regExpr, int cflags) :
  _errorCode(0), _pcre_extra(0)
{
  cflags |= PCRE_UTF8;		// force UTF-8 handling
  const char* errtext = 0;
  int offset = -1;
  _pcre = pcre_compile(regExpr, cflags, &errtext, &offset, CharTables);
  if (_pcre == 0)
    throw RegExpException(string("Error compiling Pattern: [") + regExpr +
			 "] at " + offset + ": " + errtext);
  pcre_refcount(_pcre, 1); // increment refcount
  if (!(cflags & Anchored))
    // useful only for non anchored patterns
    _pcre_extra = pcre_study(_pcre, 0, &errtext);
  pcre_fullinfo(_pcre, 0, PCRE_INFO_CAPTURECOUNT, &subpatterns);
  ++subpatterns;		// the whole string is a match
}

Pattern::Pattern(string const& regExpr, int cflags) :
  _errorCode(0), _pcre_extra(0)
{
  cflags |= PCRE_UTF8;		// force UTF-8 handling
  const char* errtext = 0;
  int offset = -1;
  _pcre = pcre_compile(regExpr.c_str(), cflags, &errtext, &offset, CharTables);
  if (_pcre == 0)
    throw RegExpException("Error compiling Pattern: [" + regExpr + "] at " + offset + ": " + errtext);
  pcre_refcount(_pcre, 1); // increment refcount
  if (!(cflags & Anchored))
    // useful only for non anchored patterns
    _pcre_extra = pcre_study(_pcre, 0, &errtext);
  pcre_fullinfo(_pcre, 0, PCRE_INFO_CAPTURECOUNT, &subpatterns);
  ++subpatterns;		// the whole string is a match
}

Pattern::~Pattern()
{
  if (_pcre && pcre_refcount(_pcre, -1) == 0) {
    if (pcre_refcount(_pcre, -1) == 0) {
      pcre_free(_pcre);
      _pcre = 0;
      if (_pcre_extra) {
	pcre_free(_pcre_extra);
	_pcre_extra = 0;
      }
    }
  }
}

bool Pattern::test(string const& str, int eflags) const
{
  MatchGroups matches(subpatterns);
  return pcre_exec(_pcre, _pcre_extra, (const char*)&str[0], str.length(),
		   0, eflags, (int*)&matches[0], 3 * subpatterns) >= 0;
}

bool Pattern::test(char const* str, size_t len, int eflags)
{
  MatchGroups matches(subpatterns);
  if (len == 0)
    len = strlen(str);
  return pcre_exec(_pcre, _pcre_extra, str, len,
		   0, eflags, (int*)&matches[0], 3 * subpatterns) >= 0;
}

int Pattern::matchSize(string const& text, int eflags)
{
  const char* it = (const char*)&*text.begin();
  const char* end = (const char*)&*text.end();

  MatchGroups matches(subpatterns);

  int mcount = pcre_exec(_pcre, _pcre_extra, it, end - it, 0, eflags,
			 (int*)&matches[0], 3 * subpatterns);
  if (mcount < 0)
    return 0;
  return matches[0].second - matches[0].first;
}

int Pattern::match(string const& text, MatchGroups& pos, int eflags)
{
  const char* it = text.c_str();
  const char* end = it + text.length();
  return match(it, end, pos, eflags);
}

int Pattern::match(const char* it, const char* end, MatchGroups& pos,
		   int eflags)
{
  int slotnum = pos.size() * 3;
  int mcount = pcre_exec(_pcre, _pcre_extra, it, end - it, 0, eflags,
			 (int*)&pos[0], slotnum);
  if (mcount < 0)
    return 0;
  return mcount;
}

//virtual 
vector<string> Pattern::match(string const& str, int eflags)
{
  MatchGroups matches(subpatterns);
  int mcount = match(str, matches, eflags);
  if (mcount < 0)
    return vector<string>(0);
  vector<string> sa(mcount);
  for (int i = 0; i < mcount; ++i)
    sa[i] = str.substr(matches[i].first, matches[i].second);
  return sa;
}

// Maximum number of groups in a replace pattern.
static const int maxReplaceGroups = 16;

/**
 * Put in @c out a rewrite of the portion of @c text corresponding to m[0]
 * according to @a rewrite,
 * i.e. replacing backslash-escaped digits (\0 to \9) with
 * substrings from m[i].first to m[i].second.
 */
static bool rewrite(string& out, const string& text, string const& rewrite, 
		    MatchGroups& m, int mcount)
{
  assert (mcount);
  for (string::const_iterator s = rewrite.begin(), end = rewrite.end(); s < end; s++) {
    int c = *s;
    if (c == '\\') {
      c = *++s;
      if (isdigit(c)) {
	int n = c - '0'; 
	if (n >= mcount)
	  return false;
	int start = m[n].first;
	if (start >= 0)
	  out.append(text.data() + start, m[n].second); 
      } else if (c == '\\')
	out += '\\';
      else
	return false; 
    } else
      out += c; 
  } 
  return true; 
}

string Pattern::replace(string const& text, string const& replwith, bool replaceAll)
{
  string rest = text;
  MatchGroups sa(maxReplaceGroups);

  string ret;
  int mcount;
  while ((mcount = match(rest, sa, 0))) {
    ret.append(rest.data(), sa[0].first); 
    if (!rewrite(ret, rest, replwith, sa, mcount))
      break;
    rest.erase(0, sa[0].second);
    if (!replaceAll)
      break;
  }
  ret += rest;
  return ret;
}

bool Pattern::modify(string& text, string const& replwith, bool replaceAll)
{
  string rest = text;
  MatchGroups sa(maxReplaceGroups);

  bool done = false;
  text.clear();
  int mcount;
  while ((mcount = match(rest, sa, 0))) {
    done = true;
    text.append(rest.data(), sa[0].first); 
    if (!rewrite(text, rest, replwith, sa, mcount))
      break;
    rest.erase(0, sa[0].second);
    if (!replaceAll)
      break;
  }
  text += rest;
  return done;
}

//static
string Pattern::escape(string& str)
{
  string sb;
  string::iterator end = str.end();
  for (string::iterator it = str.begin(); it < end; it++) {
    char c = *it;
    if (!((c >= 'a' && c <= 'z') ||
	  (c >= 'A' && c <= 'Z') ||
	  (c >= '0' && c <= '9')))
      sb += '\\';
    sb += c;
  }
  return sb;
}

} // namespace RegExp
} // namespace Text
} // namespace Tanl
