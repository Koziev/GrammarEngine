// -----------------------------------------------------------------------------
// File LEM_USTR.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Вспомогательные операции над C-строками. Используются для классов UString
// и UFString, или автономно. Частично перекрывают стандартные C-функции
// работы со строками для новых 2-х байтовых символов wchar_t.
//
// 02.06.2004 - перенос всех функций из глобального namespace'а в 'lem'
//
// 18.03.2006 - исправлена ошибка в процедурах лексикографического
//              упорядочивания строк lt(...) и gt(...), из-за которых
//              неправильно работали стандартные контейнеры set и map
//
// 23.05.2006 - процедура trim() убирает не только пробелы, но и символы \t
//
// 27.01.2007 - добавлена lem_findi - поиск без учета регистра
//
// 02.05.2007 - PRECONDITIONS checks have been added to some functions.
//
// 05.06.2007 - * expands to (.*) instead of (.+) in wildcards_to_regex().
// -----------------------------------------------------------------------------
//
// CD->01.09.1997
// LC->16.07.2009
// --------------

#include <stdio.h>
#include <stdarg.h>

#include <boost/static_assert.hpp>

#include <lem/conversions.h>
#include <lem/math/integer_math.h>
#include <lem/streams.h>
#include <lem/cstring.h>
#include <lem/fstring.h>
#include <lem/ucstring_functions.h>

#undef min
#undef max

using namespace boost;
using namespace lem;

/***************************************************************************
 Операция получения хеш-кода строки символов. Используется как классом
 CString, так и классом FString (см. LEM_FSTR.H) для инициализаций своего
 поля хеш-кода у каждого объекта. Используется умолчание, что для нулевой
 строки хеш-код будет нулем (!!!). Данная реализация хэш-функции для строк
 оптимизирована по эффективности для словоформ русского языка, но, по всей
 видимости, так же эффективна и для других алфавитов.
***************************************************************************/
lem::uint8_t lem::lem_calc_string_hash( const wchar_t *buffer )
{
 if( !buffer )
  return 0;

 int i=0;
 uint8_t hash=0;

 while( buffer[i] )
  hash += buffer[i++];

 return hash;
}

lem::uint8_t lem::lem_calc_string_hash_len( const wchar_t *buffer, int *len )
{
 if( !buffer )
  return 0;

 int i=0;
 uint8_t hash=0;
 *len=0;

 while( buffer[i] )
  {
   hash += buffer[i++];
  }

 *len = i;

 return hash;
}

// ***********************************************************************
// В отличие от предыдущей функции вычисляет одновременно хэш-код и длину
// строки=-аргумента, возвращая их в двух байтах uint16_t-результата.
// Обращаю внимание, что длина строки не должна превышать 255 символов!
// ***********************************************************************
lem::uint16_t lem::lem_calc_string_hash_len( const wchar_t *buffer )
{
 if( !buffer )
  return 0x0000;

 // Просто просуммируем все символы строки.
 uint8_t i=0;
 uint8_t res=0;

 while( buffer[i] )
  res+=buffer[i++];

 return ((uint16_t(i)<<8) & 0xff00u) |
         ( 0x00ffu & uint16_t(res) ) |
         ( 0x00ffu & (uint16_t(res)>>8) );
}



/*********************************************************************
 Определяет длину строки с учетом конечного SOL_NULL_CHAR. Для пустых
 строк возвращает 1, для строки с нулевым указателем - 0.
 Таким образом, возвращается размер блока памяти, потребного
 для хранения строки s.
**********************************************************************/
int lem::lem_fullstrlen( const wchar_t *s )
{
 if( !s )
  return 0;

 int i=0;
 while( s[i++] );
 return i;
}

/*****************************************************
  Сравнение двух строк. Регистр букв роли не играет.
******************************************************/
bool lem::lem_eqi( const wchar_t* s1, const wchar_t* s2 )
{
 if( !s1 )
  return !s2 || !*s2;

 while( *s1 && *s2 && to_ulower(*s1)==to_ulower(*s2) ) { s1++; s2++; }
 return *s1==*s2;
}

int lem::lem__strcmp( const char *a, const wchar_t *b )
{
 if( !a )
  return (!b || !*b) ? 0 : 1;

 while( *a && *b && *b==SOL_INT_TO_CHAR(*a) )
  { a++; b++; }

 return SOL_INT_TO_CHAR(*a)==*b ? 0 : 1;
}

int lem::lem__strcmp( const wchar_t *a, const char *b )
{
 if( !a )
  return (!b || !*b) ? 0 : 1;

 while( *a && *b && *a==SOL_INT_TO_CHAR(*b) )
  { a++; b++; }

 return SOL_INT_TO_CHAR(*b)==*a ? 0 : 1;

}

int lem::lem_nentry( const wchar_t *s, wchar_t ch )
{
 const int l=lem_strlen(s);
 int n=0;
 for( int i=0; i<l; i++ )
  if( s[i]==ch )
   n++;

 return n;
}

/***********************************************************
 Находит n-ое (по умолчанию первое) вхождение символа ch
 в строку-аргумент s. Если символ не найден, или число его
 вхождений менее nentry, то возвращается -1.
***********************************************************/
int lem::lem_find( const wchar_t *s, wchar_t ch, int nentry )
{
 const int l=lem_strlen(s);
 int n=1;
 for( int i=0; i<l; i++ )
  if( s[i]==ch )
   {
    if( n==nentry )
     return i;
    else
     n++;
   }

 return UNKNOWN;
}

/***************************************************************************
 Определяет положение nentry-го вхождения подстроки [f] в строку [s].
 Возвращает индекс первого совпавшего символа. Если подстрока не
 обнаружена, или число ее появлений в строке менее nentry, то возвращаем -1.
****************************************************************************/
int lem::lem_find( const wchar_t *s, const char *f, int nentry )
{
 const int l1=lem_strlen(s);
 const int l2=lem_strlen(f);

 if( !l1 || !l2 )
  return UNKNOWN;

 int n=1;
 char f0=f[0];

 for( int i=0; i<l1; i++ )
  if( s[i]==SOL_INT_TO_CHAR(f0) )
   {
    bool eq=true;
    int ii=i+1,j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( s[ii]==SOL_INT_TO_CHAR(f[j]) );

    if( eq )
     {
      if(n==nentry)
       return i;
      else
       n++;
     }
   }

 return UNKNOWN;
}


int lem::lem_find( const wchar_t *s, const wchar_t *f, int nentry )
{
 const int l1=lem_strlen(s);
 const int l2=lem_strlen(f);

 if( !l1 || !l2 )
  return UNKNOWN;

 if( nentry==1 )
  {
   const wchar_t *where = wcsstr( s, f );
   return where==NULL ? UNKNOWN : int(where-s);
  }

 int n=1;
 wchar_t f0=f[0];

 for( int i=0; i<l1; i++ )
  if( s[i]==f0 )
   {
    bool eq=true;
    int ii=i+1,j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( s[ii]==f[j] );

    if( eq )
     {
      if(n==nentry)
       return i;
      else
       n++;
     }
   }

 return UNKNOWN;
}


int lem::lem_findi( const wchar_t *s, const wchar_t *f, int nentry )
{
 const int l1=lem_strlen(s);
 const int l2=lem_strlen(f);

 if( !l1 || !l2 )
  return UNKNOWN;

 int n=1;
 wchar_t f0=lem::to_uupper(f[0]);

 for( int i=0; i<l1; i++ )
  if( to_uupper(s[i])==f0 )
   {
    bool eq=true;
    int ii=i+1,j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( to_uupper(s[ii])==to_uupper(f[j]) );

    if( eq )
     {
      if(n==nentry)
       return i;
      else
       n++;
     }
   }

 return UNKNOWN;
}


int lem::lem_find( const char *s, const wchar_t *f, int nentry )
{
 const int l1=lem_strlen(s);
 const int l2=lem_strlen(f);

 if( !l1 || !l2 )
  return UNKNOWN;

 int n=1;
 wchar_t f0=f[0];

 for( int i=0; i<l1; i++ )
  if( s[i]==(char)f0 )
   {
    bool eq=true;
    int ii=i+1,j=1;
    for( ; eq && f[j] && j<l2; j++, ii++ )
     eq=( s[ii]==(char)f[j] );

    if( eq )
     {
      if(n==nentry)
       return i;
      else
       n++;
     }
   }

 return UNKNOWN;
}


/*********************************************************************
 Процедура проверяет, обрамляют ли строку двойные апострофы ["] и
 удаляет их, сдвигая строку влево (длина уменьшается на 2). Допустимо
 указывать str=NULL, тогда операция не выполняется.
*********************************************************************/
void lem::lem_strip_apostrophes( wchar_t *str )
{
 if( !(str) )
  return;

 const int l = lem_strlen(str);
 if( l<2 )
  return; // Строка слишком коротка и явно не может содержать апострофы!

 if( *str==L'\'' && str[l-1]==L'\'' )
  {
   // Перемещаем содержимое строки на 1 позицию влево.
   memcpy( str, str+1, sizeof(*str)*(l-2) );

   // Вписываем терминатор.
   str[l-2]=0;
  }

 return;
}


/**************************************************************************
 DESCRIPTION: Copies the bytes of source string (src) into destination
              string (dst) and stops after copying the terminating null
              character of source. Is the same as standard strcpy
              function, except that the information action is calculated.

 PARAMETERS:  dst - pointer to destination memory block, src - pointer to
              source string.

 NOTE:        dst must have enough size to receive all characters of
              src including terminator '\0'. If does not, consequences
              are unknown (possibly crash).
***************************************************************************/
void lem::lem_strcpy( wchar_t *dst, const wchar_t *src )
{
 if( !!(src) )
  #if defined LEM_BORLAND
  wcscpy( dst, src );
  #else
  while( (*(dst++) = *(src++)) );
  #endif

 return;
}

void lem::lem_strcpy_nn( wchar_t *dst, const wchar_t *src )
{
 #if defined LEM_BORLAND
 wcscpy( dst, src );
 #else
 while( (*(dst++) = *(src++)) );
 #endif
}

void lem::lem_strcpy( wchar_t *dst, const char *src )
{
 if( !!(src) )
  while( (*(dst++) = SOL_INT_TO_CHAR(*(src++))) );

 return;
}

void lem::lem_strcpy( char *dst, const wchar_t *src )
{
 if( !!(src) )
  while( (*(dst++) = char(*(src++))) );

 return;
}

/***************************************************************************
 DESCRIPTION: Copies the ASCIIZ string, pointed by src, to the buffer *dest.
              No check takes place to ensure that the destination buffer is
              large enough to contain the source string.

              The length of source copied will be trimmed to n bytes,
              including terminator ('\0'). If source string is shorter than
              n, then accordingly less number of bytes is copied to the target
              buffer.

              If the source needs to be truncated then the target is not
              zero terminated.

 PARAMETERS:  dest - pointer to destination buffer.
              src  - pointer to source string.
              n    - top number of bytes to copy.

 NOTE:        1) If less than n bytes is copied then the tail of destination
              buffer remains unchanged. This is quite different to standard
              strncpy function!
              2) Information action is computed.
              3) Если копирование обрывается по исчерпанию заданного
                 параметра n, то в приемный буфер будет принудительно
                 вписан нулевой символ-терминатор.
              4) Если n меньше или равен нулю, то ни один симол не будет
                 скопирован, и только нулевой символ-терминатор будет
                 впечатан в dest.
**************************************************************************/
void lem::lem_strncpy( wchar_t *dest, const wchar_t *src, int n )
{
 LEM_CHECKIT_Z(n>=0);
 
 if( !!(src) )
  {
   int N=n;
   while( N-->0 && (*(dest++) = *(src++)) );

   if( N<=0 )
    {
     if( n>=0 )
      dest[N]=0; // Вписываем терминатор.
     else
      *dest=0;
    }
  }

 return;
}


void lem::lem_strncpy( wchar_t *dest, const char *src, int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( !!(src) )
  {
   int N=n;
   while( (N-->0) && ( *(dest++) = SOL_INT_TO_CHAR(*(src++)) ) );

   if( N<=0 )
    {
     if( n>=0 )
      dest[N]=0; // Вписываем терминатор.
     else
      *dest=0;
    }
  }

 return;
}


void lem::lem_strncpy( char *dest, const wchar_t *src, int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( !!(src) )
  {
   int N=n;
   while( (N-->0) && (*(dest++) = (char)*(src++))!=0 );

   if( N<=0 )
    {
     if( n>=0 )
      dest[N]=0; // Вписываем терминатор.
     else
      *dest=0;
    }
  }

 return;
}




/*************************************************************************
 Возвращаем 0 если строки лексически совпадают, иначе 1.
*************************************************************************/
/*
int lem::lem_strcmp( const wchar_t *a, const wchar_t *b )
{
 if( !(a) )
  return b==a ? 0 : 1;

 if( !(b) )
  return 1;

 int i=0;
 while( SOL_ISNT_NC(a[i]) && SOL_ISNT_NC(b[i]) && a[i]==b[i] )
  i++;

 return a[i]!=b[i] ? 1 : 0;
}

int lem::lem_strcmp( const wchar_t *a, const char *b )
{
 if( !(a) )
  return !(b) ? 0 : 1;

 if( !(b) )
  return 1;

 int i=0;
 while( SOL_ISNT_NC(a[i]) && (b[i]) && a[i]==SOL_INT_TO_CHAR(b[i]) )
  i++;

 return a[i]!=b[i] ? 1 : 0;
}

int lem::lem_strcmp( const char *a, const wchar_t *b )
{
 if( !(a) )
  return !(b) ? 0 : 1;

 if( !(b) )
  return 1;

 int i=0;
 while( a[i] && b[i] && SOL_INT_TO_CHAR(a[i])==b[i] )
  i++;

 return a[i]!=b[i] ? 1 : 0;
}
*/


/***********************************************************************
 Отыскиваем символ ch в строке s, заканчивающейся нулевым символом, и
 возвращаем либо NULL (не найден), либо указатель на найденную позицию.

 Если указатель s равен NULL, то процедура вернёт NULL вне зависимости
 от ch.
************************************************************************/
const wchar_t* lem::lem_strrchr( const wchar_t *s, wchar_t ch )
{
 if( s )
  {
   int i=0;
   while( s[i] )
    if( s[i++]==ch )
     return s+i-1;
  }

 return NULL;
}

/*************************************************************************
 Символы строки src, терминированной нулём, добавляются в хвост строки dst.
 При этом нулевой терминатор dst переносится. Внимание! Проверки на
 переполнение буфера dst не предпринимаются!

 Если указатель на приемный буфер dst равен NULL, то процедура ничего не
 будет делать. Также допустимо указывать src=NULL.
**************************************************************************/
void lem::lem_strcat( wchar_t *dst, const wchar_t *src )
{
 if( src && dst )
  {
   #if defined LEM_BORLAND
   wcscat( dst, src );
   #else
   dst += lem_strlen_nn(dst);
   int i=0;
   while( (dst[i]=src[i]) )
    i++;
   #endif
  }

 return;
}

void lem::lem_strcat( wchar_t *dst, const char *src )
{
 if( src && dst )
  {
   dst += lem_strlen_nn(dst);
   int i=0;
   while( (dst[i]=SOL_INT_TO_CHAR(src[i])) )
    i++;
  }

 return;
}

void lem::lem_strcat( char *dst, const wchar_t *src )
{
 if( src && dst )
  {
   dst += lem_strlen_nn(dst);
   int i=0;
   while( (dst[i]=(char)src[i]) )
    i++;
  }

 return;
}




/*****************************************************************
 К строке в dst присоединяем содержимое строки src (но не более
 n символов из src), и терминируем результат.
 Допустимо указывать dst и/или src равными NULL, процедура тогда
 просто ничего не выполнит.

 Если n равен или меньше, чем нуль, то ни один символ из src не
 будет перенесен.

 При любых обстоятельствах строка dst окажется терминированной
 нулевым символом.
******************************************************************/
void lem::lem_strncat( wchar_t *dst, const wchar_t *src, int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( !!(src) )
  {
   dst += lem_strlen(dst);
   int src_len = std::min( lem_strlen_nn(src), n );
   if( src_len<0 )
    src_len=0;

   while( src_len-->0 && (*(dst++) = *(src++)) );

   *dst=0; // Вписываем терминатор.
  }

 return;
}

void lem::lem_strncat( wchar_t *dst, const char *src, int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( !!(src) )
  {
   dst += lem_strlen(dst);
   int src_len = std::min( lem_strlen_nn(src), n );
   if( src_len<0 )
    src_len=0;

   while( src_len-->0 && (*(dst++) = SOL_INT_TO_CHAR(*(src++))) );

   *dst=0; // Вписываем терминатор.
  }

 return;
}

void lem::lem_strncat( char *dst, const wchar_t *src, int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( src )
  {
   dst += lem_strlen(dst);
   int src_len = std::min( lem_strlen(src), n );
   if( src_len<0 )
    src_len=0;

   while( src_len-->0 && (*(dst++) = (char)*(src++)) );

   *dst=0; // Вписываем терминатор.
  }

 return;
}


/*******************************************************************
 Вычисляем длину строки s - до нулевого символа (терминатора). Если
 s=NULL, то возвращается 0.
********************************************************************/
int lem::lem_strlen( const wchar_t *s )
{
 if( !(s) )
  return 0;

 int ires=0;
 while( s[ires++] );
 return ires-1;
}

// ****************************************
// Нет проверки на s==NULL.
// ****************************************
int lem::lem_strlen_nn( const wchar_t *s )
{
 int ires=0;
 while( s[ires++] );
 return ires-1;
}


/******************************************************************
 Сколько первых символов у строк a и b совпадают?
*******************************************************************/
int lem::lem_str_match_len( const wchar_t *a, const wchar_t *b )
{
 if( !(a) || !(b) )
  return 0;

 int i=0;
 while( a[i] && b[i] && a[i]==b[i] )
  i++;

 return i;
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


bool lem::lem_gt( const wchar_t *s1, const wchar_t *s2 )
{
 if( lem_is_empty(s1) )
  return false;

 if( lem_is_empty(s2) )
  return true;

 int i=0;
 while( s1[i]!='\0' )
  {
   if( uint16_t(s1[i]) < uint16_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint16_t(s1[i]) > uint16_t(s2[i]) )
    return true;

   i++;
  }

 // Строки имеют одинаковую длину, либо s1 закончилась раньше
 return uint16_t(s1[i])>uint16_t(s2[i]);
}

bool lem::lem_gt( const char *s1, const wchar_t *s2 )
{
 if( lem_is_empty(s1) )
  return false;

 if( lem_is_empty(s2) )
  return true;

 int i=0;
 while( s1[i] )
  {
   if( uint8_t(s1[i]) < uint16_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint8_t(s1[i]) > uint16_t(s2[i]) )
    return true;

   i++;
  }

 // Строки имеют одинаковую длину, либо s1 закончилась раньше
 return uint8_t(s1[i])>uint8_t(s2[i]);
}

bool lem::lem_gt( const wchar_t *s1, const char *s2 )
{
 if( lem_is_empty(s1) )
  return false;

 if( lem_is_empty(s2) )
  return true;

 int i=0;
 while( s1[i] )
  {
   if( uint16_t(s1[i]) < uint8_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint16_t(s1[i]) > uint8_t(s2[i]) )
    return true;

   i++;
  }

 // Строки имеют одинаковую длину, либо s1 закончилась раньше
 return uint16_t(s1[i])>uint8_t(s2[i]);
}



bool lem::lem_ge( const wchar_t *s1, const wchar_t *s2 )
{
 if( lem_is_empty(s2) )
  return true;

 if( lem_is_empty(s1) )
  return false;

 int i=0;
 while( s1[i] )
  {
   if( uint16_t(s1[i]) < uint16_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint16_t(s1[i]) > uint16_t(s2[i]) )
    return true;

   i++;
  }

 return true;
}

bool lem::lem_ge( const char *s1, const wchar_t *s2 )
{
 if( lem_is_empty(s2) )
  return true;

 if( lem_is_empty(s1) )
  return false;

 int i=0;
 while( s1[i] )
  {
   if( uint8_t(s1[i]) < uint16_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint8_t(s1[i]) > uint16_t(s2[i]) )
    return true;

   i++;
  }

 return true;
}

bool lem::lem_ge( const wchar_t *s1, const char *s2 )
{
 if( lem_is_empty(s2) )
  return true;

 if( lem_is_empty(s1) )
  return false;

 int i=0;
 while( s1[i] )
  {
   if( uint16_t(s1[i]) < uint8_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint16_t(s1[i]) > uint8_t(s2[i]) )
    return true;

   i++;
  }

 return true;
}


bool lem::lem_lt( const wchar_t *s1, const wchar_t *s2 )
{
 if( lem_is_empty(s2) )
  return false;

 if( lem_is_empty(s1) )
  return true;

 int i=0;
 while( s1[i] )
  {
   if( uint16_t(s1[i]) > uint16_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint16_t(s1[i]) < uint16_t(s2[i]) )
    return true;

   i++;
  }

 // Строки имеют одинаковую длину, либо s1 закончилась раньше
 return uint16_t(s1[i])<uint16_t(s2[i]);
}


bool lem::lem_lt( const char *s1, const wchar_t *s2 )
{
 if( lem_is_empty(s2) )
  return false;

 if( lem_is_empty(s1) )
  return true;

 int i=0;
 while( s1[i] )
  {
   if( uint8_t(s1[i]) > uint16_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint8_t(s1[i]) < uint16_t(s2[i]) )
    return true;

   i++;
  }

 // Строки имеют одинаковую длину, либо s1 закончилась раньше
 return uint8_t(s1[i])<uint16_t(s2[i]);
}


bool lem::lem_lt( const wchar_t *s1, const char *s2 )
{
 if( lem_is_empty(s2) )
  return false;

 if( lem_is_empty(s1) )
  return true;

 int i=0;
 while( s1[i] )
  {
   if( uint16_t(s1[i]) > uint8_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint16_t(s1[i]) < uint8_t(s2[i]) )
    return true;

   i++;
  }

 // Строки имеют одинаковую длину, либо s1 закончилась раньше
 return uint16_t(s1[i])<uint8_t(s2[i]);
}

bool lem::lem_le( const wchar_t *s1, const wchar_t *s2 )
{
 if( lem_is_empty(s1) )
  return true;

 if( lem_is_empty(s2) )
  return false;

 int i=0;
 while( s1[i] )
  {
   if( uint16_t(s1[i]) > uint16_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint16_t(s1[i]) < uint16_t(s2[i]) )
    return true;

   i++;
  }

 return true;
}

bool lem::lem_le( const char *s1, const wchar_t *s2 )
{
 if( lem_is_empty(s1) )
  return true;

 if( lem_is_empty(s2) )
  return false;

 int i=0;
 while( s1[i] )
  {
   if( uint8_t(s1[i]) > uint16_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint8_t(s1[i]) < uint16_t(s2[i]) )
    return true;

   i++;
  }

 return true;
}

bool lem::lem_le( const wchar_t *s1, const char *s2 )
{
 if( lem_is_empty(s1) )
  return true;

 if( lem_is_empty(s2) )
  return false;

 int i=0;
 while( s1[i] )
  {
   if( uint16_t(s1[i]) > uint8_t(s2[i]) )
    return false; // Код символа в s1 оказался меньше, чем в s2.

   if( uint16_t(s1[i]) < uint8_t(s2[i]) )
    return true;

   i++;
  }

 return true;
}




int lem::lem_find_from( const char *s, const wchar_t *f,  int start_pos )
{
 LEM_CHECKIT_Z(start_pos>=0);

 if( lem_is_empty(s) )
  return lem_is_empty(f) ? 0 : UNKNOWN;

 int l1=lem_strlen(s);
 int l2=lem_strlen(f);
 wchar_t f0=f[0];

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

 return -1;
}

int lem::lem_find_from( const wchar_t *s,  const wchar_t *f, int start_pos )
{
 LEM_CHECKIT_Z(start_pos>=0);

 if( lem_is_empty(s) )
  return lem_is_empty(f) ? 0 : UNKNOWN;

 int l1=lem_strlen(s);
 int l2=lem_strlen(f);
 wchar_t f0=f[0];

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

 return -1;
}

int lem::lem_find_from( const wchar_t *s,  const char *f, int start_pos )
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

 return -1;
}

// *******************************************
// Убираем все лидирующие пробельные символы.
// *******************************************
void lem::lem_strip_leading_spaces( wchar_t *str )
{
 // Сканируем строку и считаем начальные пробелы.
 int n=0, i=0;
 while( (str[i]) && ( str[i]==L' ' || str[i]==L'\t' ) )
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
void lem::lem_strip_final_spaces( wchar_t *str )
{
 int i=lem_strlen(str)-1;

 while( i>=0 )
  if( str[i]!=L' ' && str[i]!=L'\t' )
   break;
  else
   str[i--]='\0';

 return;
}

// ****************************************
// Сохранение строки в упакованном виде.
// ****************************************

namespace
{
 // Флаги упаковки (применяется один из них).
 typedef enum {
               NOTPACKED=0x00,      // неупакованная строка
               ASCII_CHARS=0x40,    // все символы - однобайтовые ASCII
               UNICODE_PACKED=0x80  // Хранится первый символ и однобайтовые
                                    // разницы кодов для ост альных
              } Pack_Flag;
}

void lem::Save_Packed( const UCString &s, lem::Stream &bin )
{
 BOOST_STATIC_ASSERT( UCString::max_len < 64 );
 uint8_t pack_flags = NOTPACKED;

 if( s.empty() )
  {
   bin.write( &pack_flags, 1 );
  }
 else
  {
   bool all_ascii=true;
   bool use_based_unicode=true;

   wchar_t base = s.front();

   for( UCString::const_iterator i=s.begin(); i!=s.end(); i++ )
    {
     if( 0xff00 & static_cast<uint16_t>(*i) )
      // Нашли не-ASCII символ
      all_ascii=false;

     int16_t dc = lem::Math::iabs( (*i) - base );

     if( 0xff00 & static_cast<uint16_t>(dc) )
      // Смещение от базового символа больше 255
      use_based_unicode=false;

     if( !all_ascii && !use_based_unicode )
      // Дальше проверять нет смысла.
      break;
    }

   if( all_ascii )
    {
     pack_flags = ASCII_CHARS | static_cast<uint8_t>( s.length() );
     bin.write( &pack_flags, 1 );

     for( UCString::const_iterator i=s.begin(); i!=s.end(); i++ )
      {
       uint8_t ch = static_cast<uint8_t>(*i);
       bin.write( &ch, 1 );
      }
    }
   else if( use_based_unicode )
    {
     pack_flags = UNICODE_PACKED | static_cast<uint8_t>( s.length() );
     bin.write( &pack_flags, 1 );

     int16_t base16 = static_cast<int16_t>(base);
     bin.write( &base16, sizeof(base16) );

     for( UCString::const_iterator i=s.begin()+1; i!=s.end(); i++ )
      {
       uint8_t dc = static_cast<uint8_t>( (*i) - base );
       bin.write( &dc, 1 );
      }
    }
   else
    {
     pack_flags = NOTPACKED | static_cast<uint8_t>( s.length() );
     bin.write( &pack_flags, 1 );
     bin.write( s.begin(), s.length()*sizeof(wchar_t) );
    }
  }

 return;
}



void lem::Load_Packed( UCString *s, lem::Stream &bin )
{
 BOOST_STATIC_ASSERT( UCString::max_len < 64 );

 uint8_t f=0;
 bin.read( &f, 1 );

 uint8_t l = 0x3fu & f;
 uint8_t pack_flags = 0xc0u & f;

 switch( pack_flags )
 {
  case NOTPACKED:
   bin.read( s->ptr(), l*sizeof(wchar_t) );
   break;

  case ASCII_CHARS:
  {	   
   for( int i=0; i<l; i++ )
    {
     uint8_t c;
     bin.read( &c, 1 );
     s->ptr()[i]=c;
    }
   break;
  }

  case UNICODE_PACKED:
   {
    int16_t base;
    bin.read( &base, sizeof(base) );
    s->ptr()[0] = static_cast<wchar_t>(base);

    for( int i=1; i<l; i++ )
     {
      int8_t dc;
      bin.read( &dc, 1 );
      
      s->ptr()[i] = static_cast<wchar_t>( base + static_cast<int16_t>(dc) );
     }

    break;
   }
 }

 s->ptr()[l]=0;
 s->calc_hash();
 return;
}


// ******************************************************************
// Из строки str удаляются все символы, присутствующие в строке chs.
// ******************************************************************
void lem::lem_remove_chars( wchar_t *str, const wchar_t *chs )
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


void lem::lem_remove_char( wchar_t *str, wchar_t chs )
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


const UFString lem::encode_chars_to_html( const UFString &str )
{
 UFString res;

 for( UFString::const_iterator i=str.begin(); i!=str.end(); i++ )
  {
   wchar_t ch = *i;

   if( ch == L'&' )
    res += L"&amp;";
   else if( ch == L'<' )
    res += L"&lt;";
   else if( ch == L'>' )
    res += L"&gt;";
   else if( ch == L'"' )
    res += L"&quot;";
   else if( ch == 0x00a7 )
    res += L"&sect;";
   else if( ch == 0x00ab )
    res += L"&raquo;";
   else if( ch == 0x00bb )
    res += L"&laquo;";
   else
    res += ch;   
  }

 return res;
}

const UFString lem::encode_chars_to_xml( const UFString &str )
{
 UFString res;
 char nnnn[10];
 for( UFString::const_iterator i=str.begin(); i!=str.end(); i++ )
  {
   if( is_lat(*i) || is_udigit(*i) )
    res += *i;
   else
    { 
     uint16_to_str( *i, nnnn, 10 );

     res += L"&#";
     res += nnnn;
     res += L';';
    }
  }

 return res;
}


// Строка из кодировки SGML (с представлением некоторых символов через
// последовательности &entity;) преобразуется к обычному виду.
const UFString lem::encode_html_to_chars( const UFString &str )
{
 UFString res;
 for( UFString::const_iterator i=str.begin(); i!=str.end(); i++ )
  {
   if( *i == L'&' )
    {
     // Читаем имя SGML entity - до символа ;
     FString entity;
     i++;

     for( ; i!=str.end(); i++ )
      {
       if( *i == L';' )
        {
         break;
        }

       entity += static_cast<char>(*i);
      } 
     
     res += CodeConverter::Sgml_2_Char( entity.c_str() );
    }
   else
    res += *i;
  }

 return res;
}


const UFString lem::encode_str_to_sql( const UFString &str )
{
 UFString res;

 for( UFString::const_iterator i=str.begin(); i!=str.end(); i++ )
  {
   wchar_t ch = *i;

   if( ch == L'\'' )
    res += L"''";
   else if( ch == L'&' )
    res += L"& ";
   else
    res += ch;   
  }

 return res;
}


UFString lem::wildcards_to_regex( const UFString &str, bool supress_front_asterix )
{
 UFString res;

 bool first_wc=true;

 UFString::const_iterator END = str.end();

 if( str.length()==1 )
  return res;

/*
 if( str.back()==L'*' || str.back()==L'?' )
  {
   END--;
  }
*/

 for( UFString::const_iterator i=str.begin(); i!=END; i++ )
  {
   wchar_t ch = *i;

   switch(ch)
   {
    case L'\\': res += L"\\\\"; break;
    case L'.':  res += L"\\.";  break;

    case L'*':
     if( !first_wc || !supress_front_asterix )
      res += L"(.*)";
     break;

    case L'?':
     if( !first_wc || !supress_front_asterix )
      res += L".";
     break;

    default:
     res += ch;
     first_wc=false;
     break;
   }
  }

 return res;
}




bool lem::lem_eq_begin( const wchar_t *a1, const wchar_t *a2 )
{
 while( *a1 && *a2 && *a1==*a2 )
  { a1++; a2++; }

 return !*a1 || !*a2;
}



/*
void lem::split( const UFString &s, Collect<UFString> &list, wchar_t delim )
{
 const int l = s.length();
 for( int i=0; i<l; )
  {
   UFString ss;
   
   while( s[i]!=delim && s[i]!=0 )
    ss.AddDirty(s[i++]);  

   ss.calc_hash();
   list.push_back(ss);

   i++;   
  }

 return;  
}
*/


// *****************************************************
// Срисовано с соответствующего участка кода в wxWindows
// *****************************************************
FString lem::format_str( const char *fmt, ... )
{
 if( fmt==NULL )
  return FString();

 va_list argptr;
 va_start(argptr,fmt);

 #if LEM_DEBUGGING==1
 // По историческим причинам класс OFormatter использует спецификатор %us для вывода широких
 // строк и %uc для широких символов. Для sprintf это недопустимые спецификаторы, приводящие
 // к неправильному выводу.
 if( strstr( fmt, "%us" )!=NULL || strstr( fmt, "%uc" )!=NULL )
  {
   LEM_STOPIT;
  }
 #endif

 int size = 1024;

 char *buf=NULL;
 while(true)
  {
   buf = (char*)malloc( sizeof(char)*(size+1) );
   if( !buf )
    {
     // out of memory
     va_end(argptr);
     return FString();
    }

   #if defined LEM_WINDOWS
   int len = _vsnprintf( buf, size, fmt, argptr );
   #else
   int len = vsnprintf( buf, size, fmt, argptr ); 
//   int len = strlen(buf);
   #endif


   // some implementations of vsnprintf() don't NUL terminate the string
   // if there is not enough space for it so always do it manually
   buf[size] = '\0';

   if( (len>=0) && (len<=size) )
    break;

   // still not enough, double it again
   size *= 2;
   free(buf);
  }

 va_end(argptr);

 return FString(buf,true);
}


UFString lem::format_str( const wchar_t *fmt, ... )
{
 if( fmt==NULL )
  return UFString();

 va_list argptr;
 va_start(argptr, fmt);

 #if LEM_DEBUGGING==1
 // По историческим причинам класс OFormatter использует спецификатор %us для вывода широких
 // строк и %uc для широких символов. Для sprintf это недопустимые спецификаторы, приводящие
 // к неправильному выводу.
 if( wcsstr( fmt, L"%us" )!=NULL || wcsstr( fmt, L"%uc" )!=NULL )
  {
   LEM_STOPIT;
  }
 #endif

 int size = 1024;
 
 wchar_t *buf=NULL;
 while(true)
  {
   buf = (wchar_t*)malloc( sizeof(wchar_t)*(size+1) );
   if( !buf )
    {
     // out of memory
     va_end(argptr);
     return UFString();
    }

   #if defined LEM_WINDOWS
   int len = _vsnwprintf( buf, size, fmt, argptr ); 
   #else
   int len = vswprintf( buf, size, fmt, argptr ); 
   #endif

   // some implementations of vsnprintf() don't NUL terminate the string
   // if there is not enough space for it so always do it manually
   buf[size] = L'\0';

   if( (len>=0) && (len<=size) )
    break;

   // still not enough, double it again
   size *= 2;
   free(buf); 
  }

 va_end(argptr);

 return UFString(buf,true);
}
