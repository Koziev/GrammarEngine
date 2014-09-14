// -----------------------------------------------------------------------------
// File ACSTRING.H
//
// (c) Koziev Elijah
//
// Content:
//
// 08.03.2006 - в класс введен enum с константой npos (для совместимости 
//              с std::basic_string)
//
// 19.06.2006 - реализован метод GetHash16(), который достаточно быстро вычисляет
//              неплохой 16-битный хэш с более-менее равномерным распределением. 
//
// 13.08.2006 - классы UCString и CString переделаны в обычные, без
//              использования template'ов.
//
// 01.12.2006 - конструктор CString( const wchar_t* ) сделан explicit
// -----------------------------------------------------------------------------
//
// CD->01.10.1995
// LC->14.09.2010
// --------------

#ifndef LEM_ACSTRING__H
#define LEM_ACSTRING__H
#pragma once

 #include <lem/config.h>
 #include <lem/strings.h>

 namespace lem {

  extern char* to_lower( char *s );
  extern char* to_upper( char *s );

  extern void dos_to_win( char *s );
  extern void win_to_dos( char *s );
  extern void win_to_koi8( char *s );
  extern void koi8_to_win( char *s );
  extern void dos_to_koi8( char *s );
  extern void koi8_to_dos( char *s );

 class CString
 {
  public:
   typedef char value_type;
   typedef const char* const_iterator;
   typedef const char& const_reference;
   typedef unsigned char hash_type;

   typedef int size_type;

   // Доступная для внешнего кода константа - максимальная вместимость
   // объектов класса (без терминирующего нуля).
   enum { max_len=LEM_CSTRING_LEN };

   enum { npos=-1 }; // для совместимости с std::base_string

   static char static_zero; // Для возврата ссылок в операторе [] при переходе
                            // границы строки.

   static const CString& Get_Empty(void);

  protected:
   char str[LEM_CSTRING_LEN+1];     // Символы строки включая терминатор ('\0')
   hash_type hash; // Для ускорения операций сравнения - хэшкод строки.
   unsigned char len;  // Длина строки (одного байта должно хватать), для более длинных строк лучше
                        // использовать BaseFString<...> или base_string<...>

  public:
   // ****************************************************************************
   // Конструктор по умолчанию создает строку с нулевой длиной.
   // Используем соглашение о вычислении хеш-кода - см. процедуру
   // lem_calc_string_hash.
   // ****************************************************************************
   CString(void) { *str=hash=len=0; }

   // ***********************************************************************************
   // в отличие от std::base_string, мы определяем два отдельных конструктора для
   // создания объекта из ASCII и unicode-строк. Поэтому UCString, которая хранит UNICODE
   // строку, можно создать прямо из ASCII-строки.
   // ***********************************************************************************
   CString( const char* s );
   explicit CString( const wchar_t* s );
   CString( const CString& s );
   explicit CString( char c );
   CString( int nTime, char c );

   CString& operator=( const char* );
   CString& operator=( const wchar_t* );
   CString& operator=( const CString& s );
   CString& operator=( char ch );

   // Ahtung: do NOT use it! It is for internal usage only!
   inline char* ptr(void) { return (char*)str; }

   // *** STL compat. ***
   inline const char* c_str(void) const { return str; }

   // ***************************************
   // Recalculating the hash after changes.
   // ***************************************
   void calc_hash(void);

   inline hash_type GetHash(void) const { return hash; }
//   inline hash_type h(void) const { return hash; }

   inline int GetHash16(void) const
   { return 0x0000ffff & ( ( (hash&0x000000ff) ^ (back()<<(len/2+2))) * front() ); }

   // ***************************
   // Accessing the chars.
   // ***************************
   char operator[]( int i ) const;

   char last_char( int i=0 ) const;
   inline char back(void) const { return len ? str[len-1] : 0; }
   inline char front(void) const { return *str; }

   // ********************************
   // Getting the length of string.
   // ********************************
   inline size_type length(void) const { return len; }
   inline size_type size(void) const { return len; }

   inline size_type max_length(void) const { int r=max_len; return r; }

   // return the maximum number of chars that can be stored in string.
   // (see STl vector::capacity).
   inline size_type capacity(void) const { return LEM_CSTRING_LEN; }

   inline bool empty(void) const { return !len; }

   void set( int i, char ch );

   inline void set_dir( int i, char ch )
   { LEM_CHECKIT_Z( i<LEM_CSTRING_LEN ); str[i]=ch; }

   inline void clear(void) { hash=len=0; *str=0; }

   CString& reduce( int n );
   void insert( int pos, char ch );
   void remove( int pos, int nch=1 );

   // For compat. with lem::Collect, lem:MCollect
   inline void ShrinkTo( int nChar ) { reduce(nChar); }
   inline void Insert( int pos, char ch ) { insert(pos,ch); }
   inline void Remove( int pos ) { remove(pos); }

   // Removes last char
   inline void Remove_back(void) { str[len-1]=0; calc_hash(); }

   CString& operator+=( const CString &s     );
   CString& operator+=( const char *s    );
   CString& operator+=( const wchar_t *s );
   CString& operator+=( char ch          );

   bool operator==( const CString &s2     ) const;
   bool operator==( const char *s2    ) const;
   bool operator==( const wchar_t *s2 ) const;
   bool operator==( char ch           ) const;

   bool operator!=( const CString &s2     ) const;
   bool operator!=( const char *s2    ) const;
   bool operator!=( const wchar_t *s2 ) const;
   bool operator!=( char ch           ) const;

   bool operator>( const CString &s2     ) const;
   bool operator>( const char *s2    ) const;
   bool operator>( const wchar_t *s2 ) const;
   bool operator>( char ch           ) const;

   bool operator>=( const CString &s2     ) const;
   bool operator>=( const char *s2    ) const;
   bool operator>=( const wchar_t *s2 ) const;
   bool operator>=( char ch           ) const;

   bool operator<( const CString &s2      ) const;
   bool operator<( const char *s2     ) const;
   bool operator<( const wchar_t *s2  ) const;
   bool operator<( char ch ) const;

   bool operator<=( const CString &s2     ) const;
   bool operator<=( const char *s2    ) const;
   bool operator<=( const wchar_t *s2 ) const;
   bool operator<=( char ch           ) const;

   // ****************************************************
   // Addind the chars or string.
   // For compat. with lem::Collect, lem:MCollect
   // ****************************************************
   inline void Add( char ch ) { operator+=(ch); }
   inline CString& operator<<( char ch )          { return operator+=(ch); }
   inline CString& operator<<( const char* s )    { return operator+=(s); }
   inline CString& operator<<( const wchar_t* s ) { return operator+=(s); }
   inline CString& operator<<( const CString& s )     { return operator+=(s); }

   int count( char ch ) const;
   bool find( char to_find ) const;

   int search( char ch, int nentry=1 ) const;
   int search( const CString &f, int nentry=1 ) const;
   int search( const char *to_find, int nentry=1 ) const;
   int search( const wchar_t *to_find, int nentry=1 ) const;

   bool eq_beg( const CString &to_find     ) const;
   bool eq_beg( const char* to_find    ) const;
   bool eq_beg( const wchar_t* to_find ) const;

   CString& subst( const CString &mask, const CString &text, int nentry=1 );
   CString& subst_all( char mask, char ch );

   CString& to_upper(void);
   CString& to_lower(void);

   CString& to_Aa(void);

   CString& strip( char Bound );
   CString& strip_quotes(void);
   CString& strip_apostrophes(void);

   CString& dress( char Bound );
   CString& dress_quotes(void);
   CString& dress_apostrophes(void);
   CString& dress_spaces(void);

   CString& cut_final_dot(void);
   CString& cut_final_commas(void);

   CString& trim(void);
   CString& trim_left(void);
   CString& trim_right(void);

   CString& add_sp(void);
   CString& add_nl(void);
   CString& add_spaces( int n );
   CString& expand_to( int n );

   CString& remove_trailing_frac_zeroes(void);

   int to_int(void) const;
   bool to_bool(void) const;

   CString& koi8_to_win(void);
   CString& koi8_to_dos(void);
   CString& dos_to_win(void);
   CString& win_to_dos(void);
   CString& dos_to_koi8(void);
   CString& win_to_koi8(void);

   const CString operator+( const CString& s2     ) const;
   const CString operator+( const char *s2    ) const;
   const CString operator+( const wchar_t *s2 ) const;
   const CString operator+( char ch           ) const;

   inline const_iterator begin(void) const { return str; }
   inline const_iterator end(void)   const { return str+len; }


   friend const CString operator+( char ch, const CString& s );
 };

 // ****************************************************************

   // ***********************************************************************************
   // в отличие от std::base_string, мы определяем два отдельных конструктора для
   // создания объекта из ASCII и unicode-строк. Поэтому UCString, которая хранит UNICODE
   // строку, можно создать прямо из ASCII-строки.
   // ***********************************************************************************
   inline CString::CString( const char* s )
   {
    if( s )
     {
      // Обязательно проверяем, вместится ли исходная строка.
      LEM_CHECKIT_Z( strlen(s) <= LEM_CSTRING_LEN );
      strncpy( str, s, LEM_CSTRING_LEN );
      str[LEM_CSTRING_LEN]=0;
      calc_hash();
     }
    else
     *str=hash=len=0;

    return;
   }

   inline CString::CString( const wchar_t* s )
   {
    if( s )
     {
      // Обязательно проверяем, вместится ли исходная строка.
      LEM_CHECKIT_Z( wcslen(s) <= LEM_CSTRING_LEN );
      lem_strncpy( str, s, LEM_CSTRING_LEN );
      str[LEM_CSTRING_LEN]=0;
      calc_hash();
     }
    else
     *str=hash=len=0;

    return;
   }

   inline CString::CString( const CString& s  )
   {
    len  = s.len;
    hash = s.hash;

    // Optimization done during the performance tuning: the for-loop is
    // MUCH faster than 'strcpy'
    for( int i=len; i>=0; i-- )
     str[i] = s.str[i];

    return;
   }

   inline CString::CString( char c )
   {
    *str=c;
    str[1]=0;
    calc_hash();
    return;
   }


   inline CString::CString( int nTime, char c )
   {
    LEM_CHECKIT_Z( nTime<=LEM_CSTRING_LEN && nTime>=0 );
    for( int i=0; i<nTime; i++ )
     str[i] = c;

    str[nTime]=0;
    calc_hash();
    return;
   }


 inline CString& CString::operator=( const CString& s )
 {
  hash = s.hash;
  len  = s.len;

  for( int i=len; i>=0; i-- )
   str[i] = s.str[i];

  return *this;
 }



 inline CString& CString::operator=( const char* s )
 {
  if( s )
   {
    LEM_CHECKIT_Z( strlen(s) <= LEM_CSTRING_LEN );
    strncpy( str, s, LEM_CSTRING_LEN );
    str[LEM_CSTRING_LEN]=0;
    calc_hash();
   }
  else
   *str=hash=len=0;

  return *this;
 }


 inline CString& CString::operator=( const wchar_t* s )
 {
  if( s )
   {
    LEM_CHECKIT_Z( wcslen(s) <= LEM_CSTRING_LEN );

    lem_strncpy( str, s, LEM_CSTRING_LEN );
    str[LEM_CSTRING_LEN]=0;
    calc_hash();
   }
  else
   *str=hash=len=0;

  return *this;
 }



 inline CString& CString::operator=( char ch )
 {
  *str=ch;
  str[1]=0;
  calc_hash();
  return *this;
 }

 // ****************************************************************

 /******************************************************************
  Переписывание символа в указанной позиции. Если позиция задана на
  пределами текущей хранимой строки, то ничего не происходит.
 *******************************************************************/

 inline void CString::set( int i, char ch )
 {
  if( i>=0 && i<len )
   {
    str[i]=ch;
    calc_hash();
   }

  return;
 }

 /************************************************************************
  Оператор доступа к элементам строки - символам. При попытке извлечени
  элемента ЗА пределами строки возвращаем ноль. Прерывания программы
  такая ситуация делать не должна.
 ************************************************************************/

 inline char CString::operator[]( int i ) const
 { return (i<0 || i>len) ? 0 : str[i]; }

 /*****************************************************************
   Возвращает символ, содержащийся в позиции, отсчитываемой
   от конца строки. То есть last_char(0) вернет последний
   символ перед '\0'. При выходе за пределы существующей строки
   возвращаем '\0'.
 *****************************************************************/

 inline char CString::last_char( int i ) const
 {
  int pos=len-i-1;

  return pos<0 || pos>=len ? 0 : str[pos];
 }


 // ****************************************************************



 inline void CString::calc_hash(void)
 {
//  lem::uint16_t h = lem_calc_string_hash_len(str);
//  hash = lem::uint8_t(h);
//  len = lem::uint8_t(h>>8);
  hash=len=0;

  char *p=str;
  while( *p )
   {
    hash += *p++;
    len++;
   }
 }

 // ****************************************************************


 inline const CString CString::operator+( const CString& s2 ) const
 {
  CString res(*this);
  strncat( res.ptr(), s2.str, LEM_CSTRING_LEN );
  res.ptr()[LEM_CSTRING_LEN]=0;
  res.calc_hash();
  return res;
 }


 inline const CString CString::operator+( const char *s2 ) const
 {
  CString res(*this);
  lem_strncat( res.ptr(), s2, LEM_CSTRING_LEN );
  res.ptr()[LEM_CSTRING_LEN]=0;
  res.calc_hash();
  return res;
 }


 inline const CString CString::operator+( const wchar_t *s2 ) const
 {
  CString res(*this);
  lem_strncat( res.ptr(), s2, LEM_CSTRING_LEN );
  res.ptr()[LEM_CSTRING_LEN]=0;
  res.calc_hash();
  return res;
 }


 inline const CString operator+( const char *s1, const CString &s2 )
 {
  CString res(s1);
  strncat( res.ptr(), s2.c_str(), LEM_CSTRING_LEN );
  res.ptr()[LEM_CSTRING_LEN]=0;
  res.calc_hash();
  return res;
 }


 inline const CString operator+( const wchar_t *s1, const CString &s2 )
 {
  CString res(s1);
  strncat( res.ptr(), s2.c_str(), LEM_CSTRING_LEN );
  res.ptr()[LEM_CSTRING_LEN]=0;
  res.calc_hash();
  return res;
 }


 inline const CString operator+( char ch, const CString& s )
 {
  CString res(ch);
  strncat( res.ptr(), s.c_str(), LEM_CSTRING_LEN );
  res.calc_hash();
  return res;
 }


 inline const CString CString::operator+( char ch ) const
 {
  CString res(*this);

  if( len==LEM_CSTRING_LEN ) return res;

  res.str[len]=ch;
  res.str[len+1]=0;
  res.calc_hash();
  return res;
 }


 // ****************************************************************


 inline CString& CString::operator+=( const CString& s )
 {
  const int l=len, sl=s.len;
  const int ncat = (l+sl)>=LEM_CSTRING_LEN ? LEM_CSTRING_LEN-l : sl;
  strncat( str, s.str, ncat );
  str[LEM_CSTRING_LEN]=0;
  calc_hash();
  return *this;
 }


 inline CString& CString::operator+=( const char *s )
 {
  int l=len, sl=lem_strlen(s);
  int ncat = (l+sl)>=LEM_CSTRING_LEN ? LEM_CSTRING_LEN-l : sl;
  lem_strncat( str, s, ncat );
  str[LEM_CSTRING_LEN]=0;
  calc_hash();
  return *this;
 }


 inline CString& CString::operator+=( const wchar_t *s )
 {
  int l=len, sl=lem_strlen(s);
  int ncat = (l+sl)>=LEM_CSTRING_LEN ? LEM_CSTRING_LEN-l : sl;
  lem_strncat( str, s, ncat );
  str[LEM_CSTRING_LEN]=0;
  calc_hash();
  return *this;
 }


 inline CString& CString::operator+=( char ch )
 {
  int l=len;
  if(l==LEM_CSTRING_LEN)
   return *this;

  str[l]=ch; str[l+1]=0;

  calc_hash();
  return *this;
 }

 // ****************************************************************


 inline bool CString::operator==( const CString &s2 ) const
 {
  if( hash!=s2.hash || len!=s2.len )
   return false;

  for( int i=0; i<len; i++ )
   if( str[i]!=s2.str[i] )
    return false;

  return true;
 }


 inline bool CString::operator==( const char *s2 ) const
 { return lem_eq( str, s2 ); }


 inline bool CString::operator==( const wchar_t *s2 ) const
 { return lem_eq( str, s2 ); }


 inline bool CString::operator==( char ch ) const
 { return *str==ch && str[1]=='\0'; }

 inline bool operator==( const char *s1, const CString& s2 )
 { return lem_eq( s2.c_str(), s1 ); }


 inline bool operator==( const wchar_t *s1, const CString& s2 )
 { return lem_eq( s2.c_str(), s1 ); }


 inline bool operator==( char ch, const CString& s )
 { return s.front()==ch && s[1]=='\0'; }


 // ****************************************************************


 inline bool CString::operator!=( const CString &s2 ) const
 {
/*
  return hash!=s2.hash ||
          len!=s2.len ||
          lem_neq_nn( str, s2.str );
*/

  if( hash!=s2.hash || len!=s2.len )
   return true;

  for( int i=0; i<len; i++ )
   if( str[i]!=s2.str[i] )
    return true;

  return false;
 }


 inline bool CString::operator!=( const char *s2 ) const
 { return lem_neq( str, s2 ); }


 inline bool CString::operator!=( const wchar_t *s2 ) const
 { return lem_neq( str, s2 ); }


 inline bool CString::operator!=( char ch ) const
 { return str[0]!=ch || str[1]!='\0'; }


 inline bool operator!=( const char *s1, const CString& s2 )
 { return lem_neq( s2.c_str(), s1 ); }


 inline bool operator!=( const wchar_t *s1, const CString& s2 )
 { return lem_neq( s2.c_str(), s1 ); }


 inline bool operator!=( char ch, const CString& s )
 { return s[0]!=ch || s[1]!='\0'; }

 // ****************************************************************


 inline bool CString::operator>( const CString &s2 ) const
 { return len>s2.len || ( len==s2.len && lem_gt( str, s2.str )); }


 inline bool CString::operator>( const char *s2 ) const
 { return lem_gt( str, s2 ); }


 inline bool CString::operator>( const wchar_t *s2 ) const
 { return lem_gt( str, s2 ); }


 inline bool CString::operator>( char ch ) const
 {
  char s2[2]={ ch, '\0' };
  return lem_gt( str, s2 );
 }

 inline bool operator>( const char *s1, const CString& s2 )
 { return lem_gt( s2.c_str(), s1 ); }


 inline bool operator>( const wchar_t *s1, const CString& s2 )
 { return lem_gt( s2.c_str(), s1 ); }


 inline bool operator>( char ch, const CString& s )
 {
  char s2[2]={ ch, '\0' };
  return lem_gt( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool CString::operator>=( const CString &s2 ) const
 { return len>s2.len || ( len==s2.len && lem_ge( str, s2.str ) ); }


 inline bool CString::operator>=( const char *s2 ) const
 { return lem_ge( str, s2 ); }


 inline bool CString::operator>=( const wchar_t *s2 ) const
 { return lem_ge( str, s2 ); }


 inline bool CString::operator>=( char ch ) const
 {
  char s2[2]={ ch, '\0' };
  return lem_ge( str, s2 );
 }

 inline bool operator>=( const char *s1, const CString& s2 )
 { return lem_ge( s2.c_str(), s1 ); }


 inline bool operator>=( const wchar_t *s1, const CString& s2 )
 { return lem_ge( s2.c_str(), s1 ); }


 inline bool operator>=( const char ch, const CString& s )
 {
  char s2[2]={ ch, '\0' };
  return lem_ge( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool CString::operator<( const CString &s2 ) const
 { return len<s2.len || (len==s2.len && lem_lt( str, s2.c_str() )); }


 inline bool CString::operator<( const char *s2 ) const
 { return lem_lt( str, s2 ); }


 inline bool CString::operator<( const wchar_t *s2 ) const
 { return lem_lt( str, s2 ); }


 inline bool CString::operator<( char ch ) const
 {
  char s2[2]={ ch, '\0' };
  return lem_lt( str, s2 );
 }

 inline bool operator<( const wchar_t *s1, const CString& s2 )
 { return lem_lt( s2.c_str(), s1 ); }


 inline bool operator<( const char *s1, const CString& s2 )
 { return lem_lt( s2.c_str(), s1 ); }


 inline bool operator<( char ch, const CString& s )
 {
  char s2[2]={ ch, '\0' };
  return lem_lt( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool CString::operator<=( const CString &s2 ) const
 { return len<s2.len || (len==s2.len && lem_le( str, s2.c_str() )); }


 inline bool CString::operator<=( const char *s2 ) const
 { return lem_le( str, s2 ); }


 inline bool CString::operator<=( const wchar_t *s2 ) const
 { return lem_le( str, s2 ); }


 inline bool CString::operator<=( char ch ) const
 {
  char s2[2]={ ch, '\0' };
  return lem_le( str, s2 );
 }

 inline bool operator<=( const char *s1, const CString& s2 )
 { return lem_le( s2.c_str(), s1 ); }


 inline bool operator<=( const wchar_t *s1, const CString& s2 )
 { return lem_le( s2.c_str(), s1 ); }


 inline bool operator<=( char ch, const CString& s )
 {
  char s2[2]={ ch, '\0' };
  return lem_le( s2, s.c_str() );
 }

 // ****************************************************************


 /***********************************************************************
  Определяет число появлений символа ch в строке s. Функция может
  использоваться для определения самого факта появления символа в строке
  так как отсутствие таковых дает нулевой результат (то есть 'false'!).
 ************************************************************************/

 inline int CString::count( char ch ) const
 { return lem_nentry( str, ch ); }

 /****************************************************************************
   Находит n-ое (по умолчанию первое) вхождение символа ch в строку-аргумент s.
   Если символ не найден, или число его вхождений менее nentry, то
   возвращается -1.
 ****************************************************************************/

 inline int CString::search( char ch, int nentry ) const
 { return lem_find( str, ch, nentry ); }

 /****************************************************************************
  Определяет положение nentry-го вхождения подстроки [f] в строку [s].
  Возвращает индекс первого совпавшего символа. Если подстрока не
  обнаружена, или число ее появлений в строке менее nentry, то возвращаем -1.
 ****************************************************************************/

 inline int CString::search( const CString &f, int nentry ) const
 { return lem_find( str, f.c_str(), nentry ); }


 inline int CString::search( const char* f, int nentry ) const
 { return lem_find( str, f, nentry ); }


 inline int CString::search( const wchar_t* f, int nentry ) const
 { return lem_find( str, f, nentry ); }



 extern const CString strip( const CString &str, char Bound );
 extern const CString strip_quotes( const CString &str );
 extern const CString strip_apostrophes( const CString &str );
 extern const CString expand_to( const CString &s, int n );
 extern const CString trim( const CString &str );


 extern const CString win_to_dos( const CString &s );
 extern const CString dos_to_win( const CString &s );
 extern const CString koi8_to_dos( const CString &s );
 extern const CString dos_to_koi8( const CString &s );
 extern const CString koi8_to_win( const CString &s );
 extern const CString win_to_koi8( const CString &s );

 extern const CString dressup( const CString &s, char Bound );
 extern const CString dress_quotes( const CString &s );
 extern const CString dress_apostrophes( const CString &s );
 extern const CString dress_spaces( const CString &s );

 extern const CString subst(
                        const CString &s,
                        const CString &mask,
                        const CString &text,
                        int nentry /*-1*/
                       );

 extern const CString to_lower( const CString &s );
 extern const CString to_upper( const CString &s );
 extern const CString cut_final_commas( const CString &s );
 extern const CString to_Aa( const CString &s );

 // *****************************************************************************
 // returns the maximum length of beginning <s1> matching <s2>
 // *****************************************************************************
 template< class CString >
 inline int match_len( const CString& s1, const CString& s2 )
 {
  int cur=0;

  while( s1[cur] && s2[cur] && s1[cur]==s2[cur] )
   cur++;

  return cur;
 }

 extern const CString left( const CString &s, int NCH );
 extern const CString right( const CString &s, int NCH );
 extern const CString mid( const CString& s, int i0, int nch );

 // ***********************************************************
 // Преобразование всех символов строки к верхнему регистру.
 // ***********************************************************

 inline CString& CString::to_upper(void)
 {
//  #if defined LEM_MSC
//  _wcsupr(str); 
//  #else
//  lem::to_upper(str);
//  #endif

  lem::to_upper(str);

  // Содержимое строки изменилось - пересчитываем хэш-код.
  calc_hash();

  return *this;
 }

 // ***********************************************************
 // Преобразование всех символов строки к нижнему регистру.
 // ***********************************************************
 inline CString& CString::to_lower(void)
 {
  lem::to_lower(str);
  calc_hash();
  return *this;
 }



 // ************************************************************
 // Строка text содержит подстроку x, причем x должна быть
 // с самого начала строки text.
 //
 // Например:
 //
 //       text =     ABCDEFG
 //       x    =     ABC
 //
 // ************************************************************

 inline bool CString::eq_beg( const CString &x ) const
 {
  if( x.len>len )
   return false;

  if( x.len==len )
   return operator==(x);

  const int lx = x.len;
  for( int i=0; i<lx; i++ )
   if( x.str[i]!=str[i] )
    return false;

  return true;
 }



 inline bool CString::eq_beg( const char *x ) const
 {
  const int lx = lem_strlen(x);
  if( lx>len )
   return false;

  if( lx==len )
   return operator==(x);

  for( int i=0; i<lx; i++ )
   if( x[i]!=str[i] )
    return false;

  return true;
 }


 inline bool CString::eq_beg( const wchar_t *x ) const
 {
  const int lx = lem_strlen(x);
  if( lx>len )
   return false;

  if( lx==len )
   return operator==(x);

  for( int i=0; i<lx; i++ )
   if( char(x[i])!=str[i] )
    return false;

  return true;
 }

 inline bool CString::find( char x ) const
 {
  for( int i=0; i<len; i++ )
   if( str[i]==x )
    return true;

  return false;
 }


 inline CString& CString::subst_all( char mask, char ch )
 {
  for( int i=0; i<len; i++ )
   if( str[i] == mask )
    str[i] = ch;    

  calc_hash();
  return *this;
 }

  inline bool in_apostrophes( const CString &s )
  { return s.front()=='\'' && s.back()=='\''; }

  inline bool in_quotes( const CString &s )
  { return s.length()>1 && s[0]=='"' && s.back()=='"'; }

 } // end of namespace 'lem'

#endif
