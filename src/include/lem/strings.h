#ifndef LEM_STRINGS_H
#define LEM_STRINGS_H
#pragma once

// -----------------------------------------------------------------------------
// File STRINGS.H
//
// (c) Koziev Elijah
//
// Content:
// ��������������� �������� ��� C-�������� (ASCII - 1 ���� �� ������ � UNICODE
// - 2 ����� �� ������). ������������ ��� ������� CString, FString,
// UCString, UFString ��� ���������. ��������� ����������� C-�������, �
// ��������� ������� - �������� �� ��� ��������� ��������� NULL-����������,
// ������� ���������� ��� ������ ������ (��. inline-��������� lem_is_empty(..)).
//
// � ��������� ������� ������������� ���� ������� ������ ����������� C RTL
// ������� ������ ��-�� ����, ��� ���� ���� ������������� ��� char* � wchar_t*.
//
// 02.06.2004 - ������� ���� ������� �� ����������� namespace'� � 'lem'
// 07.06.2008 - ��������� ��������� ��������� ��������� �����
// -----------------------------------------------------------------------------
//
// CD->16.09.1996
// LC->10.10.2015
// --------------

#include <lem/config.h>
#include <lem/integer.h>
#include <lem/runtime_checks.h>
#include <lem/minmax.h>

 #if defined LEM_BORLAND
  #undef strcpy
  #undef strcmp
  #include <cstring.h>
  using std::strcpy;
  using std::strcmp;
 #else
  #include <cstring>

  #if defined(_MSC_VER) && _MSC_VER<=1200
   // ... MSVC 6.5 �������� �� ���������� std::strcpy � �.�.
  #else
   using std::strcpy;
   using std::strcmp;
  #endif

 #endif

 #if defined LEM_BORLAND
 #include <mem.h>
 #endif

 #undef strcmp
 #undef __strcmp__

 // ************************************************************************
 // ������������ ����� �������� ����� ��� CString � UCString �����
 // ���������� ��� ���������� ������, �� ��������� ����� ����������� ��� 32
 // ����� (2 ��������� iPentium), ������� �������� ����, ���� ��� ���-���� �
 // ���� ��� ����� ������ (�� ���� �������� 29 ������ ��� ����� ������).
 // ************************************************************************
 #if !defined LEM_CSTRING_LEN
  #define LEM_CSTRING_LEN  29
 #endif

 #define LEM_CSTRING_LEN1 (LEM_CSTRING_LEN+1) // ����� ������ � �������� �����.

 #define uch wchar_t

 namespace lem
 {
  // ***********************************************************************
  // ������ ��������� ��������� ������������ ������ ch �� int, ������
  // ������� ����� ���������� ����� �������� ��� ����������� ��
  // ���������� ����������� ���� char. ������� ��������� �������� �������
  // ����� �������������� ��� ������ ��������: ��������, ������� �� �����
  // ���� <0 (������ ��������� � ���������������� ������� � ����������
  // operator[](int) � �� �����������).
  // ***********************************************************************
  #define SOL_ACHAR_TO_INT(ch) ( static_cast<int>( static_cast<unsigned int>(ch) & 0x00ffu ))

  // ***********************************************************************
  // �������� ������� - ���� wchar_t. ������ ��������� ���������, ��������
  // �� ch �������� �� ������ 256-�� ��������, �� ���� ����� �� ������� ch
  // ASCII-�����.
  // ***********************************************************************

  // ������� ������� ����...
  #define SOL_IS_IN_ASCII(ch) ( !( static_cast<unsigned int>(ch) & 0xff00u ) )

  #define L_TO_INT(ch) ( static_cast<int>( static_cast<int>(ch) & 0x0000ffffUL ))

  #define SOL_INT_TO_CHAR(x) ( static_cast<wchar_t>( static_cast<wchar_t>(x) & 0x00ffu))

  const wchar_t SOL_FEOF_CHAR        = 0xffffu;


  // *************************************************************
  // �������� '!=' (������������� �������� .NEQ. 'not equal')
  // *************************************************************
         bool lem_neq( const char*, const char* );
         bool lem_neq( const uch*,  const uch*  );
         bool lem_neq( const char*, char  );
         bool lem_neq( const uch*,  uch   );
  extern bool lem_neq( const char*, const uch*  );
  extern bool lem_neq( const uch*,  const char* );

         bool lem_neq_nn( const char*, const char* );
         bool lem_neq_nn( const uch*,  const uch*  );


  // *************************************************************
  // �������� '==' (������������� �������� .EQ. 'equal')
  // *************************************************************
         bool lem_eq( const char*, const char* );
         bool lem_eq( const wchar_t*, const wchar_t*  );
         bool lem_eq( const char*, char  );
         bool lem_eq( const wchar_t*, wchar_t );
  extern bool lem_eq( const char*, const wchar_t*  );
  extern bool lem_eq( const wchar_t*,  const char* );

         bool lem_eq_nn( const char*, const char* );
         bool lem_eq_nn( const uch*,  const uch*  );

  // ��������� ��� ����� ��������.
  extern bool lem_eqi( const char*, const char* );
  extern bool lem_eqi( const uch*,  const uch*  );
  extern bool lem_eqi( const char*, const uch*  );
  extern bool lem_eqi( const uch*,  const char* );

  // *********************************************************************
  // ������ true � ������, ���� ������ ����� ��������� (�� ����� ��������
  // ������).
  // *********************************************************************
  extern bool lem_eq_begin( const char *a1, const char *a2 );
  extern bool lem_eq_begin( const wchar_t *a1, const wchar_t *a2 );

  // *************************************************************
  // �������� '>' (������������� �������� GT 'greater than')
  // *************************************************************
  extern bool lem_gt( const char*, const char* );
  extern bool lem_gt( const uch*,  const uch*  );
  extern bool lem_gt( const char*, const uch*  );
  extern bool lem_gt( const uch*,  const char* );

  // *************************************************************
  // �������� '>=' (������������� �������� GE 'greater or equal')
  // *************************************************************
  extern bool lem_ge( const char*, const char* );
  extern bool lem_ge( const uch*,  const uch*  );
  extern bool lem_ge( const char*, const uch*  );
  extern bool lem_ge( const uch*,  const char* );

  // *************************************************************
  // �������� '<' (������������� �������� LT 'less than')
  // *************************************************************
  extern bool lem_lt( const char*, const char* );
  extern bool lem_lt( const uch*,  const uch*  );
  extern bool lem_lt( const char*, const uch*  );
  extern bool lem_lt( const uch*,  const char* );

  // *************************************************************
  // �������� '<=' (������������� �������� LE 'less or equal')
  // *************************************************************
  extern bool lem_le( const char*, const char* );
  extern bool lem_le( const uch*,  const uch*  );
  extern bool lem_le( const char*, const uch*  );
  extern bool lem_le( const uch*,  const char* );

 // *******************************************************************
 // ���-���� ������������ ��� ��������� �������� ��������� �����. ���
 // ASCII � UNICODE ����� ����������� ��������� ���-����.
 // ������� ���������� ���-����� ��������� �������� �������������
 // ������ � ��������� ������� ___String �� �������.
 // *******************************************************************
 extern uint8_t  lem_calc_string_hash( const uch *str );
 extern uint16_t lem_calc_string_hash_len( const uch *str );
 extern uint8_t  lem_calc_string_hash_len( const uch *str, int *l );

 extern uint8_t  lem_calc_string_hash( const char *buffer );
 extern uint16_t lem_calc_string_hash_len( const char *buffer );
 extern uint8_t  lem_calc_string_hash_len( const char *str, int *l );

 // *************************************************************************
 // ���������� ����� ��������� �������� ���-���� ������ � ����� ��������� ���
 // ������, ����� ���� �������� ���-����� ������ �� nClasses ����������.
 // *************************************************************************
 inline int lem_get_hash_subrange( int nClasses )
 { return 256/nClasses; }

 // ********************************************************************
 // ������ ����� ������ (� ������ ������ ��� �������������� '\0'). ���
 // NULL-��������� ���������� 0.
 // ********************************************************************
 extern int lem_fullstrlen( const char *s );
 extern int lem_fullstrlen( const uch *s );

 // *****************************************************************
 // ������� ��� ������ ch ������������ � ������ s.
 // *****************************************************************
 extern int lem_nentry( const char *s, char ch );
 extern int lem_nentry( const uch *s,  uch ch  );

 // ******************************************************************************
 // ����� ������� ������� � ������. nentry - ����� ��������� ������ (�� ���������
 // ����� ������, �� ���� nentry=1).
 // ******************************************************************************
 extern int lem_find( const char *s, char ch, int nentry=1 );
 extern int lem_find( const uch *s,  uch ch,  int nentry=1 );

 // ******************************************************************************
 // ���������� �����������, �� ����� ������� ��������� ������.
 // ******************************************************************************
 extern int lem_find( const char *s, const char *f, int nentry=1 );
 extern int lem_find( const char *s, const uch *f,  int nentry=1 );
 extern int lem_find( const uch *s,  const uch *f,  int nentry=1 );
 extern int lem_find( const uch *s,  const char *f, int nentry=1 );

 // case insensitive
 extern int lem_findi( const char *s, const char *ch, int nentry=1 );
 extern int lem_findi( const wchar_t *s, const wchar_t *ch, int nentry=1 );

 extern int lem_find_from( const char *s, const char *f, int start_pos );
 extern int lem_find_from( const char *s, const uch *f,  int start_pos );
 extern int lem_find_from( const uch *s,  const uch *f,  int start_pos );
 extern int lem_find_from( const uch *s,  const char *f, int start_pos );

 extern int lem_find_from( const uch *f, uch c, int start_pos );
 extern int lem_find_from( const char *f, char c, int start_pos );

 extern int lem_findi_from( const uch *s,  const uch *f,  int start_pos );
 extern int lem_findi_from( const char *s, const char *f, int start_pos );

 void lem_strip_apostrophes( char *str );
 void lem_strip_apostrophes( uch *str );

 extern void lem_strip_quotes( char *str );
 extern void lem_strip_quotes( uch *str );
 extern const std::string strip_quotes( const std::string &str );

 extern void lem_strip_leading_spaces( char *str );
 extern void lem_strip_leading_spaces( uch *str );

 extern void lem_strip_final_spaces( char *str );
 extern void lem_strip_final_spaces( uch *str );

 char* lem_trim( char *str );
 uch* lem_trim( uch *str );

 extern void lem_trim_zdat( char *str );

 extern char* lem_add_spaces( char *s, const int n );
 extern uch* lem_add_spaces( uch *s, const int n );

 bool lem_is_in_apostrophes( const char *s );
 bool lem_is_in_apostrophes( const uch *s );

 bool lem_is_in_quotes( const char *s );
 bool lem_is_in_quotes( const uch *s );

 char lem_last_char( const char *s );
 uch lem_last_char( const uch *s );

 bool lem_isnt_empty( const char *s );
 bool lem_isnt_empty( const uch *s );

 bool lem_is_empty( const char *s );
 bool lem_is_empty( const uch *s );

        void lem_strcpy( char *Dst,  const char *Src    );
 extern void lem_strcpy( uch *dest,  const uch *src );
 extern void lem_strcpy( uch *dest,  const char *src    );
 extern void lem_strcpy( char *dest, const uch *src );

        void lem_strcpy_nn( char *Dst,  const char *Src    );
 extern void lem_strcpy_nn( uch *dest,  const uch *src );

        void lem_strcat( char *dest, const char *src    );
 extern void lem_strcat( uch *dest,  const uch *src );
 extern void lem_strcat( uch *dest,  const char *src    );
 extern void lem_strcat( char *dest, const uch *src );

        void lem_strncpy( char *dest, const char *src, int n );
 extern void lem_strncpy( uch *dest,  const uch *src,  int n );
 extern void lem_strncpy( uch *dest,  const char *src, int n );
 extern void lem_strncpy( char *dest, const uch *src,  int n );

        void lem_strncat( char *dest, const char *src, int n );
 extern void lem_strncat( uch *dest,  const uch *src,  int n );
 extern void lem_strncat( uch *dest,  const char *src, int n );
 extern void lem_strncat( char *dest, const uch *src,  int n );

        int lem_strlen( const char *Str  );
 extern int lem_strlen( const uch *s );

        int lem_strlen_nn( const char *Str  );
 extern int lem_strlen_nn( const uch *s );

/*
        bool lem__strcmp( const char *a, const char *b   );
 extern bool lem__strcmp( const uch *a,   const uch *b   );
 extern bool lem__strcmp( const char *a,  const uch *b   );
 extern bool lem__strcmp( const uch *a,   const char *b  );
*/

 extern const uch* lem_strrchr( const uch *s, uch ch );

 inline const char* lem_strrchr( const char *s, char ch )
 { return (!s) ? NULL : strrchr(s,ch); }

 extern int lem_str_match_len( const char *a, const char *b );
 extern int lem_str_match_len( const uch *a, const uch *b );

 // *****************************************************************
 // ������� ��������� � �������� �������. ��� ��������� ����������
 // ������� Trim ������ PowerBuilder, � ������������ ��� �������
 // ������ �� ���� ������.
 // *****************************************************************
 inline char* lem_trim( char *str )
 {
  if( str )
   {
    lem_strip_leading_spaces(str);
    lem_strip_final_spaces(str);
   }

  return str;
 }

 inline uch* lem_trim( uch *str )
 {
  if( str )
   {
    lem_strip_leading_spaces(str);
    lem_strip_final_spaces(str);
   }

  return str;
 }

 // **********************************************************
 // ������ true, ���� ������ - � ������� ����������.
 // **********************************************************
 inline bool lem_is_in_apostrophes( const char *s )
 {
  return s && s[0]=='\'' && s[ strlen(s)-1 ]=='\'';
 }

 // **********************************************************
 // ������ true, ���� ������ - � ��������� ����������.
 // **********************************************************
 inline bool lem_is_in_quotes( const char *s )
 {
  return s && *s=='"' && s[ strlen(s)-1 ]=='"';
 }

 // ************************************************
 // ���������� ��������� ������ ������, ��� �������
 // ������ ��� ������ �����.
 // ************************************************
 inline char lem_last_char( const char *s )
 { return !s ? 0 : s[ strlen(s)-1 ]; }

 inline uch lem_last_char( const uch *s )
 { return !s ? 0 : s[ lem_strlen(s)-1 ]; }


 // ***********************************************************
 // ������ true, ���� ������ �� ������. ��� �������, ���
 // ������ ����� ������ ����� strlen � ���������� �� � 0,
 // ��� ��� �������� ����� strlen ����� ������ �� ����� ������.
 // ***********************************************************
 inline bool lem_isnt_empty( const char *s )
 { return s && *s; }

 inline bool lem_isnt_empty( const uch *s )
 { return s && *s; }

 // *********************************************************************
 // ������ true ���� ������ ����� ������� ����� (���� ��������� = NULL);
 // *********************************************************************
 inline bool lem_is_empty( const char *s )
 { return !s || !(*s); }

 inline bool lem_is_empty( const uch *s )
 { return !s || !(*s); }


 // **********************************************************
 // ���������� ����� ������, ������ ��� NULL ���������� 0.
 // **********************************************************
 inline int lem_strlen( const char * Str )
 { return !Str ? 0 : static_cast<int>(strlen(Str)); }

 inline int lem_strlen_nn( const char * Str )
 { return static_cast<int>(strlen(Str)); }

 // *********************************************************
 // ������ ����������� strcpy - ����������� �� � ����������
 // ���������� NULL'��.
 // *********************************************************
 inline void lem_strcpy( char *Dst, const char *Src )
 {
  if( !Dst && lem_is_empty(Src) )
   // ���������� �������� - ��������� �� NULL � NULL.
   return;

  LEM_CHECKIT_Z( !!(Dst) );

  if( Src )
   strcpy( Dst, Src );

  return;
 }

 inline void lem_strcpy_nn( char *Dst, const char *Src )
 { strcpy( Dst, Src ); }


 inline void lem_strncpy( char *Dst, const char *Src, int n )
 {
  if( !Dst && lem_is_empty(Src) )
   // ���������� �������� - ��������� �� NULL � NULL.
   return;

  LEM_CHECKIT_Z( !!(Dst) );

  if( Src )
   strncpy( Dst, Src, n );

  return;
 }

 // *********************************************************
 // ������ ����������� strcat - �������, �� � ����������
 // ���������� NULL'��.
 // *********************************************************
 inline void lem_strcat( char *Dst, const char *Src )
 {
  if( Dst && lem_is_empty(Src) )
   // ���������� �������� - ��������� ������� ���� NULL'��.
   return;

  LEM_CHECKIT_Z( Dst );

  if( Src )
   strcat( Dst, Src );

  return;
 }

 inline void lem_strncat( char *Dst, const char *Src, int n )
 {
  if( Dst && lem_is_empty(Src) )
   // ���������� �������� - ��������� ������� ���� NULL'��.
   return;

  LEM_CHECKIT_Z( Dst );

  if( Src )
   strncat( Dst, Src, n );

  return;
 }

 // ******************************************************
 // � ������ ��������� ����� ������ FALSE, ����� TRUE
 // ******************************************************
 inline bool lem__strcmp( const char *S1, const char *S2 )
 {
  if( lem_is_empty(S1) )
   return lem_is_empty(S2) ? false : true;

  if( lem_is_empty(S2) )
   return lem_is_empty(S1) ? false : true;

  return !!strcmp( S1, S2 );
 }

 /******************************************************************
   ��������� ���������, ��������� �� ������ ������� ��������� ["] �
   ������� ��, ������� ������.
 ******************************************************************/
 inline void lem_strip_quotes( char *str )
 {
  if( !str )
   return;

  int l = static_cast<int>(strlen(str));
  if( l<2 )
   return;

  if( *str=='"' && str[l-1]=='"' )
   {
    memcpy( str, str+1, l-2 );
    str[l-2]='\0';
   }

  return;
 }

 inline void lem_strip_quotes( uch *str )
 {
  if( !str )
   return;

  const int l = lem_strlen(str);
  if( l<2 )
   return;

  if( *str==L'"' && str[l-1]==L'"' )
   {
    memcpy( str, str+1, sizeof(*str)*(l-2) );
    str[l-2]=0;
   }

  return;
 }

 /*******************************************************************
  ���������� true, ���� ������ s ��������� � ������� ��������� "..."
 ********************************************************************/
 inline bool lem_is_in_apostrophes( const uch *s )
 {
  if( s && *s==L'\'' )
   {
    const int l=lem_strlen(s);
    return l>1 && s[ l-1 ]==L'\'';
   }

  return false;
 }

 /********************************************************************
  ���������� true, ���� ������ s ��������� � ������� "..."
 *********************************************************************/
 inline bool lem_is_in_quotes( const uch *s )
 {
  if( s && *s==L'"' )
   {
    const int l=lem_strlen(s);
    return l>1 && s[ l-1 ]==L'"';
   }

  return false;
 }

 extern int lem__strcmp( const char *a,  const uch *b   );
 extern int lem__strcmp( const uch *a,   const char *b  );

 inline bool lem_eq_nn( const char* s1, const char* s2 )
 { return !strcmp( s1, s2 ); }

 inline bool lem_eq( const char* s1, const char* s2 )
 {
  if( !s1 ) return !s2 || !*s2;
  if( !s2 ) return !s1 || !*s1;
  return !strcmp( s1, s2 );
 }

 inline bool lem_eq( const wchar_t* s1, const wchar_t* s2 )
 {
  if( !s1 ) return !s2 || !*s2;
  if( !s2 ) return !s1 || !*s1;
  return !wcscmp( s1, s2 );
 }

 inline bool lem_eq( const char* s1, const uch* s2 )
 {
  return !lem__strcmp( s1, s2 );
 }

 inline bool lem_eq( const uch* s1, const char* s2 )
 {
  return !lem__strcmp( s1, s2 );
 }

 inline bool lem_eq_nn( const uch* a, const uch* b )
 {
  int i=0;
  while( !!a[i] && !!b[i] && a[i]==b[i] )
   i++;

  return a[i]==b[i];
 }


 inline bool lem_neq( const wchar_t* s1, const wchar_t* s2 )
 {
  if( !s1 ) return s2 && *s2;
  if( !s2 ) return s1 && *s1;
  return !!wcscmp( s1, s2 );
 }


 inline bool lem_neq( const char* s1, const char* s2 )
 {
  if( !s1 ) return s2 && *s2;
  if( !s2 ) return s1 && *s1;
  return !!strcmp( s1, s2 );
 }

 inline bool lem_neq_nn( const char* a, const char* b )
 { return !!strcmp(a,b); }

 inline bool lem_neq( const char* s1, const uch* s2 )
 { return !!lem__strcmp( s1, s2 ); }

 inline bool lem_neq( const uch* s1, const char* s2 )
 { return !!lem__strcmp( s1, s2 ); }


 inline bool lem_neq_nn( const uch* a, const uch* b )
 {
  int i=0;
  while( !!a[i] && !!b[i] && a[i]==b[i] )
   i++;

  return a[i]!=b[i] ? true : false;
 }

 inline bool lem_neq( const uch *s, uch ch )
 {
  return (lem_is_empty(s) && ch==0 ) ||
         s[0]!=ch || !!(s[1]);
 }

 inline bool lem_neq( const char *s, char ch )
 {
  return (lem_is_empty(s) && !ch ) ||
        s[0]!=ch || !!s[1];
 }


 inline bool lem_eq( const uch *s, uch ch )
 {
  return (lem_is_empty(s) && ch==0) ||
         (s[0]==ch && !!s[1]);
 }

 inline bool lem_eq( const char *s, char ch )
 {
  return (lem_is_empty(s) && ch==0) ||
         (s[0]==ch && !s[1]);
 }

 extern void lem_remove_chars( char *str, const char *chs );
 extern void lem_remove_chars( wchar_t *str, const wchar_t *chs );

 extern void lem_remove_char( char *str, char chs );
 extern void lem_remove_char( wchar_t *str, wchar_t chs );

 #undef uch

 extern const std::string trim( const std::string &x );
 extern const std::string expand_to( const std::string &x, int len );
 extern const std::string make_html_spaces( const std::string &str );
 extern const std::string strip( const std::string &str, char Bound );

  // **********************************************************
  // ���� ������ ������� �����, �� ���������� NULL.
  // ���������� ������ ����������� � ��������� ��������� - ���
  // ������������ ���������� SQL �������.
  // **********************************************************
  template< class STR >
  inline const STR to_NULL( const STR &s )
  { return s.empty() ? STR("NULL") : dress_apostrophes(s); }


  // ��������� ��� ��������� ��������� �����
  namespace Fuzzy
  {
   const size_t cost_del = 1;
   const size_t cost_ins = 1;
   const size_t cost_sub = 1;

//   #ifdef  _WIN64
//    inline int abs_t( int x ) { return _abs64(x); }
//   #else
//    inline int abs_t( int x ) { return x>0 ? x : -x; } // abs(x); }
//   #endif

   inline int abs_t( int x ) { return x>0 ? x : -x; } // abs(x); }

   // ��������� �����������
   template < class String >
   inline size_t levinshtein_distance( const String& s1, const String& s2 )
   {
    size_t n1 = s1.length();
    size_t n2 = s2.length();

    size_t* p = new size_t[n2+1];
    size_t* q = new size_t[n2+1];
    size_t* r=NULL;

    p[0] = 0;

    for( size_t j = 1; j <= n2; ++j )
     {
      p[j] = p[j-1] + cost_ins;
     }

    for( size_t i = 1; i <= n1; ++i )
     {
      q[0] = p[0] + cost_del;
 
      for( size_t j = 1; j <= n2; ++j )
       {
        size_t d_del = p[j] + cost_del;
        size_t d_ins = q[j-1] + cost_ins;
        size_t d_sub = p[j-1] + ( s1[i-1] == s2[j-1] ? 0 : cost_sub );

        q[j] = lem::_min( lem::_min( d_del, d_ins ), d_sub );
       }

      r = p;
      p = q;
      q = r;
     }

    size_t tmp = p[n2];

    delete[] p;
    delete[] q;

    return tmp;
   }


   // ���������� ��������
   template < class String >
   inline size_t hemming_distance( const String& s1, const String& s2) 
   {
    size_t m = lem::_min(s1.length(), s2.length());
    size_t t = 0;

    for( size_t i = 0; i<m; i++ )
     {
      if( s1[i] != s2[i] )
       {
        t++;
       }
     }

    t+= abs_t((int)(s1.length() - s2.length()));

    return t;
   }


   // ******************************************************
   // ������������ ������� (0...100) ��������� ���� �����
   // ******************************************************
   template < class String >
   int get_like_percent( const String& s1, const String& s2 )
   {
    LEM_CHECKIT_Z( !s1.empty() );
    LEM_CHECKIT_Z( !s2.empty() );

    size_t d1 = hemming_distance(s1, s2);

    if( s1.length() != s2.length() )
     {
      d1 += abs_t( CastSizeToInt(s1.length()) - CastSizeToInt(s2.length()) );
     }

    const size_t d2 = levinshtein_distance( s1, s2 );

    const int p = 100 - (100*lem::_min(d1,d2))/CastSizeToInt(lem::_min(s1.length(),s2.length()));

    return p;
   }
  } // namespace Fuzzy

 } // namespace lem

#if defined LEM_UNIX
extern int memicmp( const void *a, const void *b, size_t s );
#endif

#endif
