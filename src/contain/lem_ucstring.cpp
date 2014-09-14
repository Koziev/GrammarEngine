#include <lem/config.h>
#include <lem/conversions.h>
#include <lem/ucstring.h>

#undef min
#undef max

using namespace lem;


UCString::UCString( const wchar_t * begin_ptr, const wchar_t * beyond_end_ptr )
{
 len=0;
 while( begin_ptr!=beyond_end_ptr )
  {
   str[len] = *begin_ptr;
   len++;
   ++begin_ptr;
  }

 str[len]=0;

 calc_hash();
}



// ********************************************************
// Для строк, представляющих действительные числа вида
//
//   1234.56000
//
// производится усекание последних незначащих нулей и конечной
// точки:
//
//   1234.56
// ********************************************************
UCString& UCString::remove_trailing_frac_zeroes(void)
{
 int idot = search( L'.' );
 if( idot!=UNKNOWN )
  {
   while(true)
    {
     if( back() == '0' )
      Remove_back();
     else
      break;
    }

   if( back() == L'.' )
    Remove_back();
  }

 return *this;
}

// *********************************************************************
// Приводим к лексему к виду 'Aaaaa', то есть первая буква - заглавная,
// все остальные - маленькие.
// *********************************************************************
UCString& UCString::to_Aa(void)
{
 if( !len )
  return *this;

 to_lower();

 wchar_t buf[2]= { str[0], '\0' };
 lem::to_upper(buf);

 str[0] = buf[0];

 calc_hash();

 return *this;
}

// ***************************************************
// Удаляем конечные запятые, строка усекается.
// ***************************************************
UCString& UCString::cut_final_commas(void)
{
 // Сколько запятых на конце строки?
 int n_comma=0;

 for( int i=len-1; i>=0; i-- )
  if( str[i]!=L',' )
   break;
  else
   n_comma++;

 // Теперь усекаем строку на n_comma символов.
 reduce( n_comma );

 return *this;
}

UCString& UCString::subst(
                          const UCString &mask,
                          const UCString &text,
                          int nentry
                         )
{
 const int istart = search( mask, nentry );

 if( istart<0 )
  return *this;

 // Часть слева длиной istart
 const UCString s_left = left( *this, istart );

 // Часть справа
 const UCString s_right = right( *this, length()-mask.length()-istart );

 // Результат собираем из 3х частей.
 *this = s_left + text + s_right;
 return *this;
}

// *******************************************************************
// Строка расширяется до длины n символов за счет добавления пробелов
// справа (в конец).
// *******************************************************************
UCString& UCString::add_spaces( int n )
{
 LEM_CHECKIT_Z(n>=0);

 const int l = len;
 if( n>l )
  for( int i=(n-l-1); i>=0; i-- )
   operator+=( L' ' );

 return *this;
}

UCString& UCString::strip( wchar_t Bound )
{
 int l = len;
 if( l<2 )
  // string is too short - it can not be stripped.
  return *this;

 if( str[0]==Bound && str[l-1]==Bound )
  {
   // shift the content to the left
   memcpy( str, str+1, (l-2)*sizeof(wchar_t) );
   str[l-2]='\0';
   calc_hash();
  }

 return *this;
}

UCString& UCString::strip_quotes(void)
{ return strip( L'"' ); }

UCString& UCString::strip_apostrophes(void)
{ return strip( wchar_t('\'') ); }


const UCString lem::strip( const UCString &str, wchar_t Bound )
{
 UCString res(str);
 res.strip(Bound);
 return res;
}

const UCString lem::strip_quotes( const UCString &str )
{ return strip( str, L'"' ); }

const UCString lem::strip_apostrophes( const UCString &str )
{ return strip( str, L'\'' ); }


// ***********************************************************************
// Добавляем пробелы так, чтобы длина строки стала n.
// ***********************************************************************
UCString& UCString::expand_to( int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( len<n )
  add_spaces( len-n );

 return *this;
}

const UCString lem::expand_to( const UCString &s, int n )
{
 LEM_CHECKIT_Z(n>=0);

 UCString res(s);
 res.expand_to( n );
 return res;
}

// ************************************************************************
// Если строка оканчивается точкой '.', то удаляем ее.
// Процедура полезна для преобразования формата числа с плавающей точкой
// "1234." в целочисленный "1234"
// ************************************************************************
UCString& UCString::cut_final_dot(void)
{
 const int l=len;
 if( l && str[ l-1 ]==L'.' )
  {
   str[l-1]='\0';
   calc_hash();
  }
 return *this;
}

// ******************************************
// уничтожение начальных и конечных пробелов.
// ******************************************
UCString& UCString::trim(void)
{
 trim_left();
 trim_right();
 return *this;
}

UCString& UCString::trim_left(void)
{
 lem_strip_leading_spaces(str);
 calc_hash();
 return *this;
}

UCString& UCString::trim_right(void)
{
 lem_strip_final_spaces(str);
 calc_hash();
 return *this;
}


const UCString lem::trim( const UCString &str )
{
 UCString res(str);
 res.trim();
 return res;
}



UCString& UCString::dress( wchar_t Bound )
{
 UCString m = *this;
 (*this) = UCString(Bound) + m + UCString(Bound);
 return *this;
}

UCString& UCString::dress_quotes(void)
{ return dress( L'"' ); }

UCString& UCString::dress_apostrophes(void)
{ return dress( L'\'' ); }

UCString& UCString::dress_spaces(void)
{ return dress( L' ' ); }


const UCString lem::dressup( const UCString &s, wchar_t Bound )
{ return UCString(Bound) + s + UCString(Bound); }

const UCString lem::dress_quotes( const UCString &s )
{ return dressup( s, L'"' ); }

const UCString lem::dress_apostrophes( const UCString &s )
{ return dressup( s, L'\'' ); }

const UCString lem::dress_spaces( const UCString &s )
{ return dressup( s, L' ' ); }

// ****************************************************************
// Фрагмент mask в строке s заменяем на text.
// nentry - номер вхождения маски в исходный текст (-1 by default)
// ****************************************************************
const UCString lem::subst(
                          const UCString &s,
                          const UCString &mask,
                          const UCString &text,
                          int nentry /*-1*/
                         )
{
 UCString res(s);
 res.subst( mask, text, nentry );
 return res;
}

const UCString lem::to_lower( const UCString &s )
{
 UCString res(s);
 res.to_lower();
 return res;
}

const UCString lem::to_upper( const UCString &s )
{
 UCString res(s);
 res.to_upper();
 return res;
}

const UCString lem::cut_final_commas( const UCString &s )
{
 UCString res(s);
 res.cut_final_commas();
 return res;
}

extern const UCString lem::to_Aa( const UCString &s )
{
 UCString res(s);
 res.to_Aa();
 return res;
}

/***********************************************************************
  В указанную позицию вставляется символ, строка раздвигается.
  Если позиция вышла за диапазон [0,...,LEM_CSTRING_LEN1], то со строкой
  ничего не происходит (работа не завершается).
************************************************************************/
void UCString::insert( int pos, wchar_t ch )
{
 if( pos<0 || pos>=len )
  return; // Вне диапазона

 int ifrom=LEM_CSTRING_LEN-2, idest=LEM_CSTRING_LEN-1;
 for( ; ifrom>=pos; idest--, ifrom-- )
  str[idest] = str[ifrom];

 str[LEM_CSTRING_LEN]=0;
 str[pos]=ch;
 calc_hash();
 return;
}

/**********************************************************************
  Удаление nch символов из указанной позиции, строка сдвигается.
  Если позиция вне диапазона [0,...,LEM_CSTRING_LEN1], то со сторокой
  ничего не происходит (работа не завершается, ошибок не генерируется).
***********************************************************************/
void UCString::remove( int pos, int nch )
{
 LEM_CHECKIT_Z(nch>=0);

 if( pos<0 || pos>=len )
  return; // Вне диапазона

 int idest=pos, ifrom=pos+nch;
 while( (str[idest++]=str[ifrom++])!=0 );
 calc_hash();
 return;
}

/****************************************************************************
  Возвращается строка, состоящая из символов строки-аргумента s, начина
  с первого (индекс 0) и длиной nch. Если длина исходной строки недостаточна,
  то результат будет содержать соответственно меньшее количество символов.
*****************************************************************************/
const UCString lem::left( const UCString &s, int NCH )
{
 LEM_CHECKIT_Z(NCH>=0);

 const int l=s.length();

 if( l==NCH )
  {
   return s;
  }
 else if( NCH<=0 )
  {
   return UCString();
  }
 else
  {
   UCString res;
   const int nch = NCH>l ? l : NCH;

   for( int i=0; i<nch; i++ )
    res.set_dir( i, s[i] );

   res.set_dir( nch, '\0' );
   res.calc_hash();
   return res;
  }
}

/*****************************************************************************
  Возвращается строка, состоящая из последних nch символов строки-аргумента s.
  Если длина исходной строки недостаточна, то результат будет содержать
  соответственно меньшее количество символов.
******************************************************************************/
const UCString lem::right( const UCString &s, int NCH )
{
 LEM_CHECKIT_Z(NCH>=0);
 UCString res;

 if( NCH<=0 )
  return res;

 const int l=s.length();
 const int nch = NCH>l ? l : NCH;

 int i0=l-nch;
 for( int i=0; i<nch; i++ )
  res.set_dir( i, s[i+i0] );

 res.set_dir( nch, '\0' );
 res.calc_hash();
 return res;
}


// **************************************************************************
// Из строки, начиная с позиции i0, вырезается nch символов и возвращаются
// как строка. Если i0<0, то подразумевается i0=0. Если (i0+nch) больше,
// чем длина строки s, что в результатную строку будет занесено
// соответственно меньше символов.
// **************************************************************************
const UCString lem::mid( const UCString& s, int i0, int nch )
{
 LEM_CHECKIT_Z(nch>=0);

 if( nch<=0 || i0<0 || i0>=s.length() )
  return lem::UCString();

 wchar_t res[ LEM_CSTRING_LEN + 1 ];

 const int I0 = i0<0 ? 0 : i0;

 const int l=s.length();
 if( I0>=l )
  return UCString(res);

 const int NCH = nch>(l-I0) ? l-I0 : nch;

 lem_strncpy( res, s.c_str()+I0, NCH );

 res[NCH]=0;
 return UCString(res);
}

static UCString _empty_ustr;

const UCString& UCString::Get_Empty(void)
{ return _empty_ustr; }

UCString& UCString::reduce( int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( n<=len )
  {
   str[ len-n ]=0;
   calc_hash();
  }
 else
  {
   *str = 0;
   hash=len=0;
  }
 return *this;
}

int UCString::to_int(void) const  { return lem::to_int(str);  }
bool UCString::to_bool(void) const { return lem::to_bool(str); }



bool UCString::eq_end( const UCString &to_find ) const
{
 if( len<to_find.len )
  return false;

 return !wcscmp( str+len-to_find.len, to_find.str );
}

bool UCString::eq_endi( const UCString &to_find ) const
{
 if( len<to_find.len )
  return false;

 return lem::lem_eqi( str+len-to_find.len, to_find.str );
}



bool UCString::eq_end( const wchar_t* to_find ) const
{
 if( !to_find )
  return false;

 const int l = wcslen(to_find);

 if( len<l )
  return false;

 return !wcscmp( str+len-l, to_find );
}


bool lem::is_udelim( const lem::UCString &s )
{ return s.size()==1 && lem::is_udelim(s.front()); }

bool UCString::eq_begi( const UCString &x ) const
{
 if( x.len>len )
  return false;

 if( x.len==len )
  return eqi(x);

 const int lx = x.len;
 for( int i=0; i<lx; i++ )
  if( lem::to_uupper(x.str[i]) != lem::to_uupper(str[i]) )
   return false;

 return true;
}


bool lem::is_int( const UCString &s )
{ 
 return lem::is_int(s.c_str());
}
