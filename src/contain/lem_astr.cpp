// -----------------------------------------------------------------------------
// File LEM_ASTR.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Процедуры для работы c С-строками (char*).
//
// Revision log:
// 02.06.2004 - перенос в 'lem' namespace
// 09.06.2004 - добавлены процедуры to_upper и to_lower для std::string и
//              std::wstring
// 02.05.2007 - PRECONDITIONS checks have been added to some functions.
//
// 18.09.2007 - для Unix сделана реализация memicmp
// -----------------------------------------------------------------------------
//
// CD->07.10.2002
// LC->14.09.2010
// --------------

#include <lem/conversions.h>
#include <lem/quantors.h>
#include <lem/strings.h>

using namespace boost;
using namespace lem;

/***************************************************************************
 Операция получения хеш-кода строки символов. Используется как классом
 LemString, так и классом LemFString (см. "LEM_FSTR.H") для инициализаций
 своего поля хеш-кода у каждого объекта. Используется умолчание, что дл
 нулевой строки хеш-код будет нулем.
***************************************************************************/
lem::uint8_t lem::lem_calc_string_hash( const char *buffer )
{
 if( !buffer )
  return '\0';

 // Просто просуммируем все символы строки.
 int i=0;
 lem::uint8_t res=0;

 while( buffer[i] )
  res+=buffer[i++];

 return res;
}

lem::uint8_t lem::lem_calc_string_hash_len( const char *buffer, int *len )
{
 if( !buffer )
  return '\0';

 // Просто просуммируем все символы строки.
 int i=0;
 *len=0;
 lem::uint8_t res=0;

 while( buffer[i] )
  res+=buffer[i++];

 *len = i;

 return res;
}

// **********************************************************************
// Аналогично предыдущей процедуре, но возвращается 16-битовое значение,
// в старшем байте - длина строки (максимум 256), в младшем - хэш-код.
// **********************************************************************
lem::uint16_t lem::lem_calc_string_hash_len( const char *buffer )
{
 if( !buffer )
  return 0x0000;

 // Просто просуммируем все символы строки.
 lem::uint8_t i=0;
 lem::uint8_t res=0;

 while( buffer[i] )
  res+=buffer[i++];

 return (( static_cast<lem::uint16_t>(i)<<8) & 0xff00u) |
        ( 0x00ffu & static_cast<lem::uint16_t>(res));
}

/*******************************************************
            Большие и малые не различаем.
********************************************************/
bool lem::lem_eqi( const char* s1, const char* s2 )
{
 if( !s1 )
  return !s2 || !*s2;

 while( *s1 && *s2 && to_lower(*s1)==to_lower(*s2) ) { s1++; s2++; }
 return *s1==*s2;
}

// *****************************************************************
// Сколько раз символ ch присутствует в строке s. Если s=NULL, то
// функция вернет 1 для ch='\0', и 0 в остальных случаях.
// *****************************************************************
int lem::lem_nentry( const char *s, char ch )
{
 if( lem_is_empty(s) )
  return !ch;

 int n=0, i=0;
 while( s[i] )
  {
   n += s[i]==ch ? 1 : 0;
   i++;
  }

 return n;
}

/***********************************************************
  Находит n-ое (по умолчанию первое) вхождение символа ch
  в строку-аргумент s. Если символ не найден, или число его
  вхождений менее nentry, то возвращается UNKNOWN.
***********************************************************/
int lem::lem_find( const char *s, char ch, int nentry )
{
 if( lem_is_empty(s) )
  return !ch && nentry==1 ? 0 : UNKNOWN;

 int l=CastSizeToInt(strlen(s)), n=1;
 for( int i=0; i<l; i++ )
  if( s[i]==ch )
   {
    if( n==nentry )
     return i;
    else
     n++;
   }

 return -1;
}

/***************************************************************************
 Определяет положение nentry-го вхождения подстроки [f] в строку [s].
 Возвращает индекс первого совпавшего символа. Если подстрока не
 обнаружена, или число ее появлений в строке менее nentry, то возвращаем -1.
****************************************************************************/
int lem::lem_find( const char *s, const char *f, int nentry )
{
 if( lem_is_empty(s) )
  return (lem_is_empty(f) && nentry==1) ? 0 : UNKNOWN;

 int l1=CastSizeToInt(strlen(s));
 int l2=CastSizeToInt(strlen(f));
 int n=1;
 char f0=f[0];

 if( !l1 || !l2 )
  return UNKNOWN;

 for( int i=0; i<l1; i++ )
  if( s[i]==f0 )
   {
    bool eq=true;
    int ii=i+1,j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( s[ii]==f[j] );

    if( eq )
     {
      if( nentry==UNKNOWN || n==nentry )
       return i;
      else
       n++;
     }
   }

 return UNKNOWN;
}



// Поиск подстроки БЕЗ УЧЕТА РЕГИСТРА символов
int lem::lem_findi( const char *s, const char *f, int nentry )
{
 if( lem_is_empty(s) )
  return (lem_is_empty(f) && nentry==1) ? 0 : UNKNOWN;

 int l1=CastSizeToInt(strlen(s));
 int l2=CastSizeToInt(strlen(f));
 int n=1;
 char f0 = toupper(f[0]);

 if( !l1 || !l2 )
  return UNKNOWN;

 for( int i=0; i<l1; i++ )
  if( toupper(s[i]) == f0 )
   {
    bool eq=true;
    int ii=i+1,j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( toupper(s[ii]) == toupper(f[j]) );

    if( eq )
     {
      if( nentry==UNKNOWN || n==nentry )
       return i;
      else
       n++;
     }
   }

 return UNKNOWN;
}



// ************************************************************
// Полная длина строки - с учетом терминирующего '\0'. Однако
// если аргумент NULL, то возвращается 0.
// ************************************************************
int lem::lem_fullstrlen( const char *s )
{
 if( !(s) )
  return 0;

 int i=0;
 while( (s[i++]) );
 return i;
}

// *******************************************
// Убираем все лидирующие пробельные символы.
// *******************************************
void lem::lem_strip_leading_spaces( char *str )
{
 // Сканируем строку и считаем начальные пробелы.
 int n=0, i=0;
 while( (str[i]) && str[i]==' ' )
  {
   i++;
   n++;
  }

 // перемещаем строку на n символов к началу.
 if( n )
  {
   int ito=0, ifrom=n;

   do
    str[ito++] = str[ifrom];
   while( (str[ifrom++]) );
  }

 return;
}

// *******************************************
// Убираем все конечные пробельные символы.
// *******************************************
void lem::lem_strip_final_spaces( char *str )
{
 int i=lem_strlen(str)-1;

 while( i>=0 )
  if( str[i]!=' ' )
   break;
  else
   str[i--]='\0';

 return;
}

/******************************************************************
 Сколько первых символов у строк a и b совпадают?
*******************************************************************/
int lem::lem_str_match_len( const char *a, const char *b )
{
 if( !(a) || !(b) )
  return 0;

 int i=0;
 while( a[i]!=0 && b[i]!=0 && a[i]==b[i] )
  i++;

 return i;
}

void lem::lem_trim_zdat( char *str )
{
 const int i = lem_find( str, " 00:00:00" );
 if( i!=UNKNOWN )
  str[i]='\0';

 return;
}


// ************************************************************************
// Вернем true, если s1 длиннее s2, или если при равной длине один из
// символов слева в s1 больше (по числовому коду) соответствующего
// символа в s2.
//
//   "abc" > "ab"   -> true
//   "bcd" > "abc"  -> true
//   "aaa" > "aaa"  -> false
// ************************************************************************
bool lem::lem_gt( const char *s1, const char *s2 )
{
 if( s1==NULL )
  return false;

 if( s2==NULL )
  return *s1!=0;

 return strcmp(s1,s2)>0;
}

/******************************************************************
 "abc" >= "abc"  -> true
 "abc" >= "bcd"  -> false
 "bcs" >= "abc"  -> true
*******************************************************************/
bool lem::lem_ge( const char *s1, const char *s2 )
{
 if( s1==NULL )
  return s2==NULL || *s2==0;

 if( s2==NULL )
  return true;

 return strcmp(s1,s2)>=0;
}

bool lem::lem_lt( const char *s1, const char *s2 )
{
 if( s2==NULL )
  return false;

 if( s1==NULL )
  return *s2!=0;

 return strcmp(s1,s2)<0;
}

bool lem::lem_le( const char *s1, const char *s2 )
{
 if( s1==NULL )
  return true;

 if( s2==NULL )
  return *s1==0;

 return strcmp(s1,s2)<=0;
}

// ******************************************************************
// Из строки str удаляются все символы, присутствующие в строке chs.
// ******************************************************************
void lem::lem_remove_chars( char *str, const char *chs )
{
 if( !(str) || !(chs) )
  return;

 int i_dst=0, i_src=0;
 while( str[i_src] )
  {
   if( lem_find( chs, str[i_src] )!=UNKNOWN )
    i_src++; // Символ присутствует - пропускаем
   else
    str[i_dst++] = str[i_src++];
  }

 str[i_dst] = '\0';

 return;
}


void lem::lem_remove_char( char *str, char chs )
{
 if( !(str) || !chs )
  return;

 int i_dst=0, i_src=0;
 while( str[i_src] )
  {
   if( str[i_src]==chs )
    i_src++; // Символ присутствует - пропускаем
   else
    str[i_dst++] = str[i_src++];
  }

 str[i_dst] = '\0';

 return;
}

// ***********************************************
// Строка справа расширяется до n символов за счет
// присоединения пробелов.
// ***********************************************
char* lem::lem_add_spaces( char *s, int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( !!(s) )
  {
   const int l = CastSizeToInt(strlen(s));
   const int nn = n - l;

   // Есть что добавить?
   if( nn>0 )
    {
     for( int i=0; i<nn; i++ )
      s[ l+i ] = ' ';

     s[n] ='\0';
    }
  }

 return s;
}

const std::string lem::trim( const std::string &x )
{
 std::string res(x);

 // ...

 return res;
}


const std::string lem::expand_to( const std::string &x, int len )
{
 LEM_CHECKIT_Z(len>=0);

 std::string res=x;

 int l = CastSizeToInt(x.length());

 if( l<len )
  for( int i=0; i<(len-l); i++ )
   res += " ";

 return res;
}


bool lem::lem_eq_begin( const char *a1, const char *a2 )
{
 while( *a1 && *a2 && *a1==*a2 )
  { a1++; a2++; }

 return !*a1 || !*a2;
}


// ******************************************************************
// Заменяем стартовые пробелы на специальные токены &nbsp;
// Это позволяет на HTML странице сохранять форматирование текста.
// ******************************************************************
const std::string lem::make_html_spaces( const std::string &str )
{
 std::string res;
 int l=CastSizeToInt(str.length()), n_lead_spaces=0;
 for( int i1=0; i1<l; i1++, n_lead_spaces++ )
  if( str[i1]!=' ' )
   break;

 for( int i2=0; i2<n_lead_spaces; i2++ )
  res += "&nbsp;";

 res += str.c_str()+n_lead_spaces;
 return res;
}


int lem::lem_find_from( const char *s, const char *f, int start_pos )
{
 LEM_CHECKIT_Z(start_pos>=0);

 if( lem_is_empty(s) )
  return lem_is_empty(f) ? 0 : UNKNOWN;

 int l1=lem_strlen(s);
 int l2=lem_strlen(f);
 char f0=f[0];

 if( !l1 || !l2 )
  return UNKNOWN;

 for( int i=start_pos; i<l1; i++ )
  if( s[i]==f0 )
   {
    bool eq=true;
    int ii=i+1,j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( s[ii]==f[j] );

    if( eq )
     return i;
   }

 return UNKNOWN;
}



int lem::lem_find_from( const wchar_t *s, wchar_t ch, int start_pos )
{
 LEM_CHECKIT_Z(start_pos>=0);

 if( lem_is_empty(s) )
  return ch ? 0 : UNKNOWN;

 int i=start_pos;
 while( s[i] )
  if( s[i] == ch )
   return i;
  else
   i++;
 
 return UNKNOWN;
}

int lem::lem_find_from( const char *s, char ch, int start_pos )
{
 LEM_CHECKIT_Z(start_pos>=0);

 if( lem_is_empty(s) )
  return ch ? 0 : UNKNOWN;

 const char *where = strchr( s+start_pos, ch );

 if( !where )
  return UNKNOWN;

 return int(where-s);
/*
 int i=start_pos;
 while( s[i] )
  if( s[i] == ch )
   return i;
  else
   i++;

 return UNKNOWN;
*/ 
}

// без учета регистра
int lem::lem_findi_from( const wchar_t *s,  const wchar_t *f,  int start_pos )
{
 LEM_CHECKIT_Z(start_pos>=0);

 if( lem_is_empty(s) )
  return lem_is_empty(f) ? 0 : UNKNOWN;

 int l1=lem_strlen(s);
 int l2=lem_strlen(f);
 wchar_t f0 = to_uupper(f[0]);

 if( !l1 || !l2 )
  return UNKNOWN;

 for( int i=start_pos; i<l1; i++ )
  if( to_uupper(s[i])==f0 )
   {
    bool eq=true;
    int ii=i+1, j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( to_uupper(s[ii]) == to_uupper(f[j]) );

    if( eq )
     return i;
   }

 return UNKNOWN;
}


// ******************************************************************
// без учета регистра
// ******************************************************************
int lem::lem_findi_from( const char *s,  const char *f,  int start_pos )
{
 LEM_CHECKIT_Z(start_pos>=0);

 if( lem_is_empty(s) )
  return lem_is_empty(f) ? 0 : UNKNOWN;

 int l1=lem_strlen(s);
 int l2=lem_strlen(f);
 char f0 = to_upper(f[0]);

 if( !l1 || !l2 )
  return UNKNOWN;

 for( int i=start_pos; i<l1; i++ )
  if( to_upper(s[i])==f0 )
   {
    bool eq=true;
    int ii=i+1,j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( to_upper(s[ii]) == to_upper(f[j]) );

    if( eq )
     return i;
   }

 return UNKNOWN;
}


// ***********************************************************
// Если строка str в двойных апострофах "...", то убираем их.
// ***********************************************************
const std::string lem::strip_quotes( const std::string &str )
{
 if(
    str.empty() ||
    str.length()<2 ||
    str[0]!='"' || str[ str.length()-1 ]!='"'
   )
  return str;

 std::string res( str.begin()+1, str.end()-1 );
 return res;
}

const std::string lem::to_upper( const std::string &s )
{
 std::string res=s;
 size_t l = res.length();
 for( size_t i=0; i<l; i++ )
  res[i] = to_upper( s[i] );

 return res;
}

const std::wstring lem::to_upper( const std::wstring &s )
{
 std::wstring res=s;
 size_t l = res.length();
 for( size_t i=0; i<l; i++ )
  res[i] = to_uupper( s[i] );

 return res;
}

const std::string lem::to_upper_w( const std::string &s )
{
 std::string res;

 int l=CastSizeToInt(s.length());
 for( int i=0; i<l; i++ )
  res += to_upper_w( s[i] );

 return res;
}

const std::string lem::to_lower( const std::string &s )
{
 std::string res=s;
 size_t l = res.length();
 for( size_t i=0; i<l; i++ )
  res[i] = to_lower( s[i] );

 return res;
}

const std::wstring lem::to_lower( const std::wstring &s )
{
 std::wstring res=s;
 size_t l = res.length();
 for( size_t i=0; i<l; i++ )
  res[i] = to_ulower( s[i] );

 return res;
}

const std::string lem::to_lower_w( const std::string &s )
{
 std::string res=s;
 size_t l = res.length();
 for( size_t i=0; i<l; i++ )
  res[i] = to_lower_w( s[i] );

 return res;
}

const std::string lem::strip( const std::string &str, char Bound )
 {
  std::string res=str;

  size_t l = str.length();
  if( l && str[0]==Bound && str[l-1]==Bound )
   {
//    #if defined LEM_WATCOM
    res = str.substr( 1, str.length()-2 );
//    #else 
//    res = std::string( (const char*)str.begin()+1, (const char*)str.end()-1 );
//    #endif 
   }  

  return res;
 }


#if defined LEM_UNIX
int memicmp( const void *a, const void *b, size_t count )
{
 int f = 0, l = 0;
 const char *dst = (const char*)a, *src = (const char*)b;
 while( count-- && f==l )
 {
  f = tolower( (unsigned char)(*(dst++)) );
  l = tolower( (unsigned char)(*(src++)) );
 }

 return ( f - l );
}
#endif
