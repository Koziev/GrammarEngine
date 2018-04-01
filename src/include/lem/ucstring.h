#ifndef LEM_UCSTRING__H
#define LEM_UCSTRING__H
#pragma once

// -----------------------------------------------------------------------------
// File UCSTRING.H
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
// 30.11.2006 - конструктор из wchar_t* сделан explicit
// 07.08.2008 - добавлен метод eqi для безрегистрового сравнения строк
// 08.02.2009 - добавлен метод eq_begi для безрегистрового сравнения начальных
//              частей строк
// 16.01.2011 - добавлен метод Add_Dirty для быстрого добавления одного
//              символа без обновления хеш-кода. 
//
// 26.03.2018 - рефакторинг и чистка кода
// -----------------------------------------------------------------------------
//
// CD->01.10.1995
// LC->26.03.2018
// --------------

 #include <lem/config.h>
 #include <lem/strings.h>

 namespace lem {

  extern wchar_t* to_lower( wchar_t *s );
  extern wchar_t* to_upper( wchar_t *s );

 class UCString
 {
  public:
   typedef wchar_t value_type;
   typedef const wchar_t* const_iterator;
   typedef const wchar_t& const_reference;
   typedef unsigned char hash_type;

   typedef int size_type;

   // Доступная для внешнего кода константа - максимальная вместимость
   // объектов класса (без терминирующего нуля).
   enum { max_len=LEM_CSTRING_LEN };

   enum { npos=-1 }; // для совместимости с std::base_string

   static wchar_t static_zero; // Для возврата ссылок в операторе [] при переходе
                            // границы строки.

   static const UCString& Get_Empty(void);

  protected:
   wchar_t str[LEM_CSTRING_LEN+1];     // Символы строки включая терминатор ('\0')
   hash_type hash; // Для ускорения операций сравнения - хэшкод строки.
   unsigned char len;  // Длина строки (одного байта должно хватать), для более длинных строк лучше
                        // использовать BaseFString<...> или base_string<...>

  public:
   // ****************************************************************************
   // Конструктор по умолчанию создает строку с нулевой длиной.
   // Используем соглашение о вычислении хеш-кода - см. процедуру
   // lem_calc_string_hash.
   // ****************************************************************************
   UCString(void) { *str=hash=len=0; }

   explicit UCString( const char* s );
   UCString( const wchar_t* s );
   UCString( const UCString& s );

   UCString( const wchar_t * begin_ptr, const wchar_t * beyond_end_ptr );

   explicit UCString( wchar_t c );
   UCString( int nTime, wchar_t c );

   UCString& operator=( const char*    );
   UCString& operator=( const wchar_t* );
   UCString& operator=( const UCString& s   );
   UCString& operator=( wchar_t ch        );

   // Ahtung: do NOT use it! It is for internal usage only!
   inline wchar_t* ptr(void) { return (wchar_t*)str; }

   // *** STL compat. ***
   inline const wchar_t* c_str(void) const { return str; }

   // ***************************************
   // Recalculating the hash after changes.
   // ***************************************
   void calc_hash(void);

   // Стандартный 8-битовый хэш-код
   inline hash_type GetHash(void) const { return hash; }
//   inline hash_type h(void) const { return hash; }

   // расширенный 16-битовый хэш-код
   inline int GetHash16(void) const
   { return 0x0000ffff & ( ( (hash&0x000000ff) ^ (back()<<(len/2+2))) * front() ); }


   // ***************************
   // Accessing the chars.
   // ***************************
   wchar_t operator[]( int i ) const;

   wchar_t last_char( int i=0 ) const;

   inline wchar_t back(void) const { return len ? str[len-1] : 0; }
   inline wchar_t front(void) const { return *str; }

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

   void set( int i, wchar_t ch );

   inline void set_dir( int i, wchar_t ch )
   { LEM_CHECKIT_Z( i<LEM_CSTRING_LEN ); str[i]=ch; }

   inline void clear(void) { hash=len=(unsigned char)(*str=0); }

   UCString& reduce( int n );
   void insert( int pos, wchar_t ch );
   void remove( int pos, int nch=1 );

   UCString& operator+=( const UCString &s );
   UCString& operator+=( const char *s );
   UCString& operator+=( const wchar_t *s );
   UCString& operator+=( wchar_t ch );

   UCString& Add_Dirty( wchar_t ch );

   bool operator==( const UCString &s2     ) const;
   bool operator==( const char *s2    ) const;
   bool operator==( const wchar_t *s2 ) const;
   bool operator==( wchar_t ch           ) const;

   bool operator!=( const UCString &s2     ) const;
   bool operator!=( const wchar_t *s2 ) const;
   bool operator!=( wchar_t ch           ) const;

   bool operator>( const UCString &s2     ) const;
   bool operator>( const wchar_t *s2 ) const;
   bool operator>( wchar_t ch           ) const;

   bool operator>=( const UCString &s2     ) const;
   bool operator>=( const wchar_t *s2 ) const;
   bool operator>=( wchar_t ch           ) const;

   bool operator<( const UCString &s2      ) const;
   bool operator<( const wchar_t *s2  ) const;
   bool operator<( wchar_t ch ) const;

   bool operator<=( const UCString &s2     ) const;
   bool operator<=( const wchar_t *s2 ) const;
   bool operator<=( wchar_t ch           ) const;

   bool eqi( const UCString &x ) const;

   int count( wchar_t ch ) const;
   bool find( wchar_t to_find ) const;

   int search( wchar_t ch, int nentry=1 ) const;
   int search( const UCString &f, int nentry=1 ) const;
   int search( const wchar_t *to_find, int nentry=1 ) const;

   bool eq_beg( const UCString &to_find ) const;
   bool eq_beg( const wchar_t* to_find ) const;
   bool eq_begi( const UCString &x ) const;

   bool eq_end( const UCString &to_find ) const;
   bool eq_end( const wchar_t* to_find ) const;
   bool eq_endi( const UCString &to_find ) const;


   UCString& subst( const UCString &mask, const UCString &text, int nentry=1 );
   UCString& subst_all( wchar_t mask, wchar_t ch );

   UCString& to_upper(void);
   UCString& to_lower(void);
   UCString& to_Aa(void);

   UCString& strip( wchar_t Bound );
   UCString& strip_quotes(void);
   UCString& strip_apostrophes(void);

   UCString& dress( wchar_t Bound );
   UCString& dress_quotes(void);
   UCString& dress_apostrophes(void);

   UCString& trim(void);
   UCString& trim_left(void);
   UCString& trim_right(void);

   //UCString& add_sp(void);
   //UCString& add_nl(void);
   UCString& add_spaces( int n );
   UCString& expand_to( int n );

   int to_int(void) const;
   bool to_bool(void) const;

   const UCString operator+( const UCString& s2 ) const;
   const UCString operator+( const wchar_t *s2 ) const;
   const UCString operator+( wchar_t ch ) const;

   inline const_iterator begin(void) const { return str; }
   inline const_iterator end(void)   const { return str+len; }

   friend const UCString operator+( wchar_t ch, const UCString& s );
 };



 inline UCString::UCString( const char* s )
 {
  if( s )
   {
    // Обязательно проверяем, вместится ли исходная строка.
    LEM_CHECKIT_Z( strlen(s) <= LEM_CSTRING_LEN );
    lem_strncpy( str, s, LEM_CSTRING_LEN );
    str[LEM_CSTRING_LEN]=0;
    calc_hash();
   }
  else
   *str=hash=len=0;
  return;
 }


 inline UCString::UCString( const wchar_t* s )
 {
  if( s )
   {
    // Обязательно проверяем, вместится ли исходная строка.
    LEM_CHECKIT_Z( wcslen(s) <= LEM_CSTRING_LEN );
    wcsncpy( str, s, LEM_CSTRING_LEN+1 );
    str[LEM_CSTRING_LEN]=0;
    calc_hash();
   }
  else
   *str=hash=len=0;

  return;
 }

 inline UCString::UCString( const UCString& s )
 {
  len  = s.len;
  hash = s.hash;
  wcscpy( str, s.str );
  return;
 }

 inline UCString::UCString( wchar_t c )
 {
  *str=c;
  str[1]=0;
  calc_hash();
  return;
 }


 inline UCString::UCString( int nTime, wchar_t c )
 {
  LEM_CHECKIT_Z( nTime<=LEM_CSTRING_LEN && nTime>=0 );
  for( int i=0; i<nTime; i++ )
   str[i] = c;

  str[nTime]=0;
  calc_hash();
  return;
 }


 // ****************************************************************

 inline UCString& UCString::operator=( const UCString& s )
 {
  hash = s.hash;
  len  = s.len;

//  for( int i=len; i>=0; i-- )
//   str[i] = s.str[i];
  wcscpy( str, s.str );

  return *this;
 }



 inline UCString& UCString::operator=( const char* s )
 {
  if( s )
   {
    LEM_CHECKIT_Z( strlen(s) <= LEM_CSTRING_LEN );
    lem_strncpy( str, s, LEM_CSTRING_LEN+1 );
    str[LEM_CSTRING_LEN]=0;
    calc_hash();
   }
  else
   *str=hash=len=0;

  return *this;
 }


 inline UCString& UCString::operator=( const wchar_t* s )
 {
  if( s )
   {
    LEM_CHECKIT_Z( wcslen(s) <= LEM_CSTRING_LEN );
    wcsncpy( str, s, LEM_CSTRING_LEN );
    str[LEM_CSTRING_LEN]=0;
    calc_hash();
   }
  else
   *str=hash=len=0;

  return *this;
 }


 inline UCString& UCString::operator=( wchar_t ch )
 {
  str[0]=ch;
  str[1]=0;
  calc_hash();
  return *this;
 }

 // ****************************************************************

 /******************************************************************
  Переписывание символа в указанной позиции. Если позиция задана на
  пределами текущей хранимой строки, то ничего не происходит.
 *******************************************************************/
 inline void UCString::set( int i, wchar_t ch )
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
 inline wchar_t UCString::operator[]( int i ) const
 { return (i<0 || i>len) ? 0 : str[i]; }

 /*****************************************************************
   Возвращает символ, содержащийся в позиции, отсчитываемой
   от конца строки. То есть last_char(0) вернет последний
   символ перед '\0'. При выходе за пределы существующей строки
   возвращаем '\0'.
 *****************************************************************/
 inline wchar_t UCString::last_char( int i ) const
 {
  int pos=len-i-1;

  return pos<0 || pos>=len ? 0 : str[pos];
 }


 // ********************************************
 // Вычисление значения хэш-кода и длины строки
 // ********************************************
 inline void UCString::calc_hash(void)
 {
  hash=len=0;

  wchar_t *p=str;
  while( *p )
   {
    hash += *p++;
    len++;
   }
 }

 // ****************************************************************

 inline const UCString UCString::operator+( const UCString& s2 ) const
 {
  UCString res(*this);
  wcsncat( res.ptr(), s2.c_str(), LEM_CSTRING_LEN );
  res.ptr()[LEM_CSTRING_LEN]=0;
  res.calc_hash();
  return res;
 }

 inline const UCString UCString::operator+( const wchar_t *s2 ) const
 {
  UCString res(*this);
  wcsncat( res.ptr(), s2, LEM_CSTRING_LEN );
  res.ptr()[LEM_CSTRING_LEN]=0;
  res.calc_hash();
  return res;
 }

 inline const UCString operator+( const wchar_t *s1, const UCString &s2 )
 {
  UCString res(s1);
  wcsncat( res.ptr(), s2.c_str(), LEM_CSTRING_LEN );
  res.ptr()[LEM_CSTRING_LEN]=0;
  res.calc_hash();
  return res;
 }

 inline const UCString operator+( wchar_t ch, const UCString& s )
 {
  UCString res(ch);
  wcsncat( res.str, s.c_str(), LEM_CSTRING_LEN );
  res.calc_hash();
  return res;
 }

 inline const UCString UCString::operator+( wchar_t ch ) const
 {
  UCString res(*this);

  if( len==LEM_CSTRING_LEN ) return res;

  res.str[len]=ch;
  res.str[len+1]=0;
  res.calc_hash();
  return res;
 }


 // ****************************************************************

 inline UCString& UCString::operator+=( const UCString& s )
 {
  const int l=len, sl=s.len;
  const int ncat = (l+sl)>=LEM_CSTRING_LEN ? LEM_CSTRING_LEN-l : sl;
  wcsncat( str, s.str, ncat );
  str[LEM_CSTRING_LEN]=0;
  calc_hash();
  return *this;
 }



 inline UCString& UCString::operator+=( const char *s )
 {
  int l=len, sl=lem_strlen(s);
  int ncat = (l+sl)>=LEM_CSTRING_LEN ? LEM_CSTRING_LEN-l : sl;
  lem_strncat( str, s, ncat );
  str[LEM_CSTRING_LEN]=0;
  calc_hash();
  return *this;
 }



 inline UCString& UCString::operator+=( const wchar_t *s )
 {
  int l=len, sl=lem_strlen(s);
  int ncat = (l+sl)>=LEM_CSTRING_LEN ? LEM_CSTRING_LEN-l : sl;
  wcsncat( str, s, ncat );
  str[LEM_CSTRING_LEN]=0;
  calc_hash();
  return *this;
 }

 inline UCString& UCString::operator+=( wchar_t ch )
 {
  int l=len;
  if(l==LEM_CSTRING_LEN)
   return *this;

  str[l]=ch; str[l+1]=0;
  calc_hash();
  return *this;
 }

 inline UCString& UCString::Add_Dirty( wchar_t ch )
 {
  int l=len;
  if(l<LEM_CSTRING_LEN)
   {
    str[l]=ch;
    str[l+1]=0;
    len++;
   }

  return *this;
 }



 // ****************************************************************

 inline bool UCString::operator==( const UCString &s2 ) const
 {
  if( hash!=s2.hash || len!=s2.len )
   return false;

  for( int i=0; i<len; i++ )
   if( str[i]!=s2.str[i] )
    return false;

  return true;
 }


 inline bool UCString::operator==( const char *s2 ) const
 { return lem_eq( str, s2 ); }

 inline bool UCString::operator==( const wchar_t *s2 ) const
 { return lem_eq( str, s2 ); }

 inline bool UCString::operator==( wchar_t ch ) const
 { return *str==ch && str[1]=='\0'; }

 inline bool operator==( const wchar_t *s1, const UCString& s2 )
 { return lem_eq( s2.c_str(), s1 ); }

 inline bool operator==( wchar_t ch, const UCString& s )
 { return s.front()==ch && s[1]=='\0'; }


 // ****************************************************************

 inline bool UCString::operator!=( const UCString &s2 ) const
 {
  if( hash!=s2.hash || len!=s2.len )
   return true;

  for( int i=0; i<len; i++ )
   if( str[i]!=s2.str[i] )
    return true;

  return false;
 }

 inline bool UCString::operator!=( const wchar_t *s2 ) const
 { return lem_neq( str, s2 ); }

 inline bool UCString::operator!=( wchar_t ch ) const
 { return str[0]!=ch || str[1]!='\0'; }

 inline bool operator!=( const wchar_t *s1, const UCString& s2 )
 { return lem_neq( s2.c_str(), s1 ); }

 inline bool operator!=( wchar_t ch, const UCString& s )
 { return s[0]!=ch || s[1]!='\0'; }

 // ****************************************************************

 inline bool UCString::operator>( const UCString &s2 ) const
 {
  return /*len<s2.len ||*/ wcscmp( str, s2.c_str() )>0;
 }

 inline bool UCString::operator>( const wchar_t *s2 ) const
 { return lem_gt( str, s2 ); }

 inline bool UCString::operator>( wchar_t ch ) const
 {
  wchar_t s2[2]={ ch, '\0' };
  return lem_gt( str, s2 );
 }

 inline bool operator>( const wchar_t *s1, const UCString& s2 )
 { return lem_gt( s2.c_str(), s1 ); }

 inline bool operator>( wchar_t ch, const UCString& s )
 {
  wchar_t s2[2]={ ch, '\0' };
  return lem_gt( s2, s.c_str() );
 }

 // ****************************************************************

 inline bool UCString::operator>=( const UCString &s2 ) const
 {
  return /*len<s2.len ||*/ wcscmp( str, s2.c_str() )>=0;
 }

 inline bool UCString::operator>=( const wchar_t *s2 ) const
 { return lem_ge( str, s2 ); }

 inline bool UCString::operator>=( wchar_t ch ) const
 {
  wchar_t s2[2]={ ch, '\0' };
  return lem_ge( str, s2 );
 }

 inline bool operator>=( const wchar_t *s1, const UCString& s2 )
 { return lem_ge( s2.c_str(), s1 ); }

 inline bool operator>=( const wchar_t ch, const UCString& s )
 {
  wchar_t s2[2]={ ch, '\0' };
  return lem_ge( s2, s.c_str() );
 }

 // ****************************************************************

 inline bool UCString::operator<( const UCString &s2 ) const
 {
  return /*len>s2.len ||*/ wcscmp( str, s2.c_str() )<0;
 }

 inline bool UCString::operator<( const wchar_t *s2 ) const
 { return lem_lt( str, s2 ); }

 inline bool UCString::operator<( wchar_t ch ) const
 {
  wchar_t s2[2]={ ch, '\0' };
  return lem_lt( str, s2 );
 }

 inline bool operator<( const wchar_t *s1, const UCString& s2 )
 { return lem_lt( s2.c_str(), s1 ); }

 //inline bool operator<( const char *s1, const UCString& s2 )
 //{ return lem_lt( s2.c_str(), s1 ); }

 inline bool operator<( wchar_t ch, const UCString& s )
 {
  wchar_t s2[2]={ ch, '\0' };
  return lem_lt( s2, s.c_str() );
 }

 // ****************************************************************

 inline bool UCString::operator<=( const UCString &s2 ) const
 {
  return /*len>s2.len ||*/ wcscmp( str, s2.c_str() )<=0;
 }

 inline bool UCString::operator<=( const wchar_t *s2 ) const
 { return lem_le( str, s2 ); }

 inline bool UCString::operator<=( wchar_t ch ) const
 {
  wchar_t s2[2]={ ch, '\0' };
  return lem_le( str, s2 );
 }

 inline bool operator<=( const wchar_t *s1, const UCString& s2 )
 { return lem_le( s2.c_str(), s1 ); }

 inline bool operator<=( wchar_t ch, const UCString& s )
 {
  wchar_t s2[2]={ ch, '\0' };
  return lem_le( s2, s.c_str() );
 }

 // ****************************************************************


 /***********************************************************************
  Определяет число появлений символа ch в строке s. Функция может
  использоваться для определения самого факта появления символа в строке
  так как отсутствие таковых дает нулевой результат (то есть 'false'!).
 ************************************************************************/
 inline int UCString::count( wchar_t ch ) const
 { return lem_nentry( str, ch ); }

 /****************************************************************************
   Находит n-ое (по умолчанию первое) вхождение символа ch в строку-аргумент s.
   Если символ не найден, или число его вхождений менее nentry, то
   возвращается -1.
 ****************************************************************************/
 inline int UCString::search( wchar_t ch, int nentry ) const
 { return lem_find( str, ch, nentry ); }

 /****************************************************************************
  Определяет положение nentry-го вхождения подстроки [f] в строку [s].
  Возвращает индекс первого совпавшего символа. Если подстрока не
  обнаружена, или число ее появлений в строке менее nentry, то возвращаем -1.
 ****************************************************************************/
 inline int UCString::search( const UCString &f, int nentry ) const
 { return lem_find( str, f.c_str(), nentry ); }

 inline int UCString::search( const wchar_t* f, int nentry ) const
 { return lem_find( str, f, nentry ); }


 extern const UCString strip( const UCString &str, wchar_t Bound );
 extern const UCString strip_quotes( const UCString &str );
 extern const UCString strip_apostrophes( const UCString &str );



 extern const UCString expand_to( const UCString &s, int n );
 extern const UCString trim( const UCString &str );
 extern const UCString dressup( const UCString &s, wchar_t Bound );
 extern const UCString dress_quotes( const UCString &s );
 extern const UCString dress_apostrophes( const UCString &s );
 extern const UCString subst(
                             const UCString &s,
                             const UCString &mask,
                             const UCString &text,
                             int nentry /*-1*/
                            );



 extern const UCString to_lower( const UCString &s );
 extern const UCString to_upper( const UCString &s );
 extern const UCString to_Aa( const UCString &s );


 // *****************************************************************************
 // returns the maximum length of beginning <s1> matching <s2>
 // *****************************************************************************
 inline int match_len( const UCString& s1, const UCString& s2 )
 {
  int cur=0;

  while( s1[cur] && s2[cur] && s1[cur]==s2[cur] )
   cur++;

  return cur;
 }

 extern const UCString left( const UCString &s, int NCH );
 extern const UCString right( const UCString &s, int NCH );
 extern const UCString mid( const UCString& s, int i0, int nch );


 // ***********************************************************
 // Преобразование всех символов строки к верхнему регистру.
 // ***********************************************************
 inline UCString& UCString::to_upper(void)
 {
  lem::to_upper(str);
  // Содержимое строки изменилось - пересчитываем хэш-код.
  calc_hash();

  return *this;
 }


 // ***********************************************************
 // Преобразование всех символов строки к нижнему регистру.
 // ***********************************************************
 inline UCString& UCString::to_lower(void)
 {
  lem::to_lower(str);
  calc_hash();
  return *this;
 }


 inline UCString& UCString::subst_all( wchar_t mask, wchar_t ch )
 {
  for( int i=0; i<len; i++ )
   if( str[i] == mask )
    str[i] = ch;    

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
 inline bool UCString::eq_beg( const UCString &x ) const
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


 inline bool UCString::eqi( const UCString &x ) const
 {
  if( x.len!=len )
   return false;

  return lem::lem_eqi( str, x.str );
 }


 inline bool UCString::eq_beg( const wchar_t *x ) const
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


 inline bool UCString::find( wchar_t x ) const
 {
  for( int i=0; i<len; i++ )
   if( str[i]==x )
    return true;

  return false;
 }


  inline bool in_apostrophes( const UCString &s )
  { return s.front()==L'\'' && s.back()==L'\''; }

  inline bool in_quotes( const UCString &s )
  { return s.length()>1 && s[0]==L'"' && s.back()==L'"'; }

  extern bool is_udelim( const UCString &s );
  extern bool is_int( const UCString &s );

 } // end of namespace 'lem'

#endif
