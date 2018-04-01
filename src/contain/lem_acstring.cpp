#include <lem/conversions.h>
#include <lem/acstring.h> 

#undef min
#undef max

using namespace lem;

lem::CString& lem::CString::strip( char Bound )
{
 int l = len;
 if( l<2 )
  // string is too short - it can not be stripped.
  return *this;

 if( str[0]==Bound && str[l-1]==Bound )
  {
   // shift the content to the left
   memcpy( str, str+1, (l-2)*sizeof(char) );
   str[l-2]='\0';
   calc_hash();
  }

  return *this;
 }


lem::CString& lem::CString::strip_quotes(void)
{ return strip( '"' ); }


lem::CString& lem::CString::strip_apostrophes(void)
{ return strip( '\'' ); }


const lem::CString lem::strip( const lem::CString &str, char Bound )
{
 lem::CString res=str;
 res.strip(Bound);
 return res;
}


const lem::CString lem::strip_quotes( const lem::CString &str )
{ return strip( str, '"' ); }


const lem::CString lem::strip_apostrophes( const lem::CString &str )
{ return strip( str, '\'' ); }


// ***********************************************************************
// Добавляем пробелы так, чтобы длина строки стала n.
// ***********************************************************************
lem::CString& lem::CString::expand_to( int n )
{
 LEM_CHECKIT_Z(n>=0);

 if( len<n )
  add_spaces( len-n );

 return *this;
}


const lem::CString lem::expand_to( const lem::CString &s, int n )
{
 LEM_CHECKIT_Z(n>=0);

 lem::CString res=s;
 res.expand_to( n );
 return res;
}



// ******************************************
// уничтожение начальных и конечных пробелов.
// ******************************************
lem::CString& lem::CString::trim(void)
{
 trim_left();
 trim_right();
 return *this;
}


lem::CString& lem::CString::trim_left(void)
{
 lem_strip_leading_spaces(str);
 calc_hash();
 return *this;
}


lem::CString& lem::CString::trim_right(void)
{
 lem_strip_final_spaces(str);
 calc_hash();
 return *this;
}



const lem::CString lem::trim( const lem::CString &str )
{
 lem::CString res(str);
 res.trim();
 return res;
}



lem::CString& lem::CString::dos_to_win(void)
{
 lem::dos_to_win( str );
 calc_hash();
 return *this;
}


lem::CString& lem::CString::dos_to_koi8(void)
{
 lem::dos_to_koi8( str );
 calc_hash();
 return *this;
}


lem::CString& lem::CString::win_to_dos(void)
{
 lem::win_to_dos( str );
 calc_hash();
 return *this;
}


lem::CString& lem::CString::koi8_to_dos(void)
{
 lem::koi8_to_dos( str );
 calc_hash();
 return *this;
}


lem::CString& lem::CString::koi8_to_win(void)
{
 lem::koi8_to_win( str );
 calc_hash();
 return *this;
}


lem::CString& lem::CString::win_to_koi8(void)
{
 lem::win_to_koi8( str );
 calc_hash();
 return *this;
}



const lem::CString lem::win_to_dos( const lem::CString &s )
{
 lem::CString res = s;
 res.win_to_dos();
 return res;
}


const lem::CString lem::dos_to_win( const lem::CString &s )
{
 lem::CString res = s;
 res.dos_to_win();
 return res;
}


const lem::CString lem::koi8_to_dos( const lem::CString &s )
{
 lem::CString res = s;
 res.koi8_to_dos();
 return res;
}


const lem::CString lem::dos_to_koi8( const lem::CString &s )
{
 lem::CString res = s;
 res.dos_to_koi8();
 return res;
}


const lem::CString lem::koi8_to_win( const lem::CString &s )
{
 lem::CString res = s;
 res.koi8_to_win();
 return res;
}


const lem::CString lem::win_to_koi8( const lem::CString &s )
{
 lem::CString res = s;
 res.win_to_koi8();
 return res;
}



lem::CString& lem::CString::dress( char Bound )
{
 lem::CString m = *this;
 (*this) = CString(Bound) + m + CString(Bound);
 return *this;
}


lem::CString& lem::CString::dress_quotes(void)
{ return dress( '"' ); }


lem::CString& lem::CString::dress_apostrophes(void)
{ return dress( '\'' ); }


const lem::CString lem::dressup( const lem::CString &s, char Bound )
{ return CString(Bound) + s + CString(Bound); }


const lem::CString lem::dress_quotes( const lem::CString &s )
{ return dressup( s, '"' ); }


const lem::CString dress_apostrophes( const lem::CString &s )
{ return dressup( s, '\'' ); }


const lem::CString lem::to_lower( const lem::CString &s )
{
 lem::CString res=s;
 res.to_lower();
 return res;
}

/***********************************************************************
  В указанную позицию вставляется символ, строка раздвигается.
  Если позиция вышла за диапазон [0,...,LEM_CSTRING_LEN1], то со строкой
  ничего не происходит (работа не завершается).
************************************************************************/
void lem::CString::insert( int pos, char ch )
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
void lem::CString::remove( int pos, int nch )
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
const lem::CString lem::left( const lem::CString &s, int NCH )
{
 LEM_CHECKIT_Z(NCH>=0);

 lem::CString res;

 if( NCH<=0 )
  return res;

 const int l=s.length();
 const int nch = NCH>l ? l : NCH;

 for( int i=0; i<nch; i++ )
  res.set_dir( i, s[i] );

 res.set_dir( nch, '\0' );
 res.calc_hash();
 return res;
}

/*****************************************************************************
  Возвращается строка, состоящая из последних nch символов строки-аргумента s.
  Если длина исходной строки недостаточна, то результат будет содержать
  соответственно меньшее количество символов.
******************************************************************************/
const lem::CString lem::right( const lem::CString &s, int NCH )
{
 LEM_CHECKIT_Z(NCH>=0);

 lem::CString res;

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
const lem::CString lem::mid( const lem::CString& s, int i0, int nch )
{
 LEM_CHECKIT_Z(nch>=0);

 if( nch<=0 || i0<0 || i0>=s.length() )
  return lem::CString();

 char res[ LEM_CSTRING_LEN + 1 ];

 const int I0 = i0<0 ? 0 : i0;

 const int l=s.length();
 if( I0>=l )
  return CString(res);
 const int NCH = nch>(l-I0) ? l-I0 : nch;
 lem_strncpy( res, s.c_str()+I0, NCH );

 res[NCH]=0;
 return CString(res);
}


 
// *******************************************************************
// Строка расширяется до длины n символов за счет добавления пробелов
// справа (в конец).
// *******************************************************************
lem::CString& lem::CString::add_spaces( int n )
{
 LEM_CHECKIT_Z(n>=0);

 const int l = len;
 if( n>l )
  for( int i=(n-l-1); i>=0; i-- )
   operator+=( ' ' );
 return *this;
}




static lem::CString    _empty_astr;

const lem::CString& lem::CString::Get_Empty(void)
{ return _empty_astr; }


lem::CString& lem::CString::reduce( int n )
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

int lem::CString::to_int(void) const
{ return lem::to_int(str);  }

bool lem::CString::to_bool(void) const
{ return lem::to_bool(str); }
