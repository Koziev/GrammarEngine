// LC->16.04.2010

#include <lem/streams.h>
#include <lem/conversions.h>
#include <lem/ufstring.h>

using namespace lem;


UFString::UFString( const char *source )
{
 if( source && *source )
  {
   cap = len = CastSizeToInt(strlen(source));
   str=Alloc(len + 1);
   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif
   lem_strcpy( str, source );
   calc_hash();
  }
 else
  {
   // Если аргумент = NULL, то подразумевается пустая строка.
   str=NULL;
   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif
   hash=cap=len=0;
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return;
}



// ************************************************************
// Конструктор копирования - строка собирается из двух строк
// ************************************************************
UFString::UFString( const UFString& s1, const UFString& s2 )
{
 #if LEM_DEBUGGING==1
 s1.Assert();
 s2.Assert();
 #endif

 cap = len = s1.len + s2.len;
 if( len )
  {
   str=Alloc(len+1);
   *str=0;

   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif

   if( !s1.empty() )
    wcscpy( str, s1.str );

   if( !s2.empty() )
    wcscat( str, s2.str );

   calc_hash_only();
  }
 else
  {
   str=NULL;
   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif
   hash=0;
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return;
}


 // ************************************************************
 // Конструктор копирования - строка собирается из трех строк
 // ************************************************************
UFString::UFString( const UFString& s1, const UFString& s2, const UFString& s3 )
{
 #if LEM_DEBUGGING==1
 s1.Assert();
 s2.Assert();
 s3.Assert();
 #endif

 cap = len = s1.len + s2.len + s3.len;

 if( len )
  {
   str=Alloc(len+1);
   *str=0; 

   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif
   if( !s1.empty() )
    wcscpy( str, s1.str );

   if( !s2.empty() )
    wcscat( str, s2.str );

   if( !s3.empty() )
    wcscat( str, s3.str );

   calc_hash_only();
  }
 else
  {
   str=NULL;
   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif
   hash=0;
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return;
}


// ******************************************************
// Создаем строку длиной nch и заполняем символами ch.
// ******************************************************
UFString::UFString( size_type nTime, wchar_t c )
 {
   if( nTime<=0 )
   {
    str=NULL;
    #if defined LEM_STRPOOL
    ref_count = NULL;
    #endif
    hash=len=cap=0;
   }
  else
   {
    #if defined LEM_STRPOOL
    ref_count = new int(1);
    #endif
    str = Alloc(nTime+1);

    #if LEM_DEBUGGING==1
    if(!str)
     throw std::bad_alloc();
    #endif

    for( size_type i=0; i<nTime; i++ )
     str[i] = c;

    str[nTime]='\0';
    cap=len=CastSizeToInt(nTime);
    calc_hash();
   }

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return;
 }


UFString::UFString( const std::wstring &uStr )
{
 if( uStr.empty() )
  {
   str=NULL;
   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif
   cap=len=hash='\0';
   return;
  }

 cap=len=CastSizeToInt(uStr.length());
 str=Alloc(len+1);

 #if LEM_DEBUGGING==1
 if(!str)
  throw std::bad_alloc();
 #endif

 #if defined LEM_STRPOOL
 ref_count = new int(1);
 #endif

 wcscpy( str, uStr.c_str() );
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return;
}


#if defined LEM_DOT_NET
UFString::UFString( System::String *s )
{
 wchar_t chars __gc [] = s->ToCharArray();
 len = s->get_Length();

 if( !len )
  {
   str=NULL;
   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif
   cap=hash='\0';
   return;
  }

 cap=len;
 str=Alloc(len+1);

 #if LEM_DEBUGGING==1
 if(!str)
  throw std::bad_alloc();
 #endif

 #if defined LEM_STRPOOL
 ref_count = new int(1);
 #endif

 for( int i=0; i<len; i++ )
  str[i] = chars[i];

 str[len] = 0;

 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif
}
#endif

#if defined LEM_VCL
//UFString::UFString( const WideString &s )
//{ Init(c.c_str()); }
#endif

#if defined LEM_QT
UFString::UFString( const QString &x )
{
 Init(x);
 return;
}
#endif
  
#if defined LEM_WXWIDGETS && defined LEM_UNICODE
UFString::UFString( const wxString &s )
{ Init(s.c_str()); }
#endif

#if defined LEM_MFC
UFString::UFString( const CStringW &s )
{ Init((const wchar_t*)s); }
#endif

#if defined LEM_ICU 
UFString::UFString( const UnicodeString &s )
{
 // Init( s.getBuffer() );
 LEM_STOPIT;
 return;
}
#endif


#if defined LEM_QT
void UFString::Init( const QString &x )
{
 cap=len=x.length();
 str=Alloc(len+1);

 #if LEM_DEBUGGING==1
 if(!str)
  throw std::bad_alloc();
 #endif

 #if defined LEM_STRPOOL
 ref_count = new int(1);
 #endif

 x.toWCharArray( str );
 str[len]=0;
 calc_hash();

 return;
}
#endif

void UFString::Init( const wchar_t *s )
{
 if( lem_is_empty(s) )
  {
   str=NULL;
   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif
   cap=len=hash='\0';
   return;
  }

 cap=len=lem_strlen(s);
 str=Alloc(len+1);

 #if LEM_DEBUGGING==1
 if(!str)
  throw std::bad_alloc();
 #endif

 #if defined LEM_STRPOOL
 ref_count = new int(1);
 #endif

 wcscpy( str, s );
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return;
}

#if defined LEM_DOT_NET
UFString& UFString::operator=( System::String *s )
{
 #if defined LEM_STRPOOL
 UnShare();
 #endif

 reserve( s->Length );
 
 wchar_t chars __gc [] = s->ToCharArray();
 const int l = s->Length;

 for( int i=0; i<l; i++ )
  str[i] = chars[i];

 str[l] = 0; 
 
 calc_hash();

 return *this;
}
#endif

#if defined LEM_VCL
//UFString& UFString::operator=( const WideString &s )
//{ return operator=(s.c_str()); }
#endif

  
#if defined LEM_WXWIDGETS && defined LEM_UNICODE
UFString& UFString::operator=( const wxString &s )
{ return operator=(s.c_str()); }
#endif

#if defined LEM_QT
lem::UFString& lem::UFString::operator=( const QString &ustr )
{
 #if defined LEM_STRPOOL
 UnShare();
 delete ref_count;
 #endif

 Free(str);

 Init(ustr);
 return *this;
}
#endif


 // ***********************************************************
 // Если строка s не пустая, то добавляем к ее концу пробел.
 // Если на конце строки уже есть побел, то он не добавляется.
 // ***********************************************************

UFString& UFString::add_sp(void)
{
 if( length() && last_char()!=L' ' )
  operator+=(L' ');

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


const UFString lem::add_sp( const UFString& s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 UFString res=s;
 res.add_sp();
 return res;
}



UFString& UFString::add_nl(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( length() && last_char()!=L'\n' )
  operator+=(L'\n');

 return *this;
}



const UFString lem::add_nl( const UFString& s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 UFString res(s);
 res.add_nl();
 return res;
}


const UFString lem::add_spaces( const UFString& s, int n )
{
 LEM_CHECKIT_Z(n>=0);

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif
  
 UFString res(s);
 res.add_spaces(n);
 return res;
}

 // ******************************************************************
 // Обычно для пустой строки класс не выделяет память, а присваивает
 // полю str значение NULL. В некоторых случаях это нежелательно, и
 // вызов данного метода заставляет выделить память и записать туда
 // строку нулевой длины.
 // ******************************************************************

void UFString::re_clear(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( !str )
  {
   str=Alloc(1);
   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif
   *str=hash=cap=len=0;
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif
  
 return;
}


UFString& UFString::trim(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif
 lem_trim(str);
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif
  
 return *this;
}


const UFString lem::trim( const UFString &s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 UFString res(s);
 res.trim();

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 return res;
}


// *********************************************************
// Добавляем пробелы чтобы длина строки стала n.
// *********************************************************
UFString& UFString::expand_to( int n )
{
 LEM_CHECKIT_Z(n>=0);

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int l = length();
 if( n>l )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif

   for( int i=n-l-1; i>=0; i-- )
    Add_Dirty(L' ');

   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif
   
 return *this;
}


const UFString lem::expand_to( const UFString &s, int n )
{
 LEM_CHECKIT_Z(n>=0);

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 UFString res(s);
 res.expand_to( n );

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 return res;
}

const UFString lem::remove_chars( const UFString &str, const UFString &chs )
{
 #if LEM_DEBUGGING==1
 str.Assert();
 chs.Assert();
 #endif

 UFString res=str;
 lem_remove_chars( res.ptr(), chs.c_str() );
 res.calc_hash();

 #if LEM_DEBUGGING==1
 str.Assert();
 chs.Assert();
 #endif

 return res;
}


const UFString lem::remove_char( const UFString &str, wchar_t chs )
{
 #if LEM_DEBUGGING==1
 str.Assert();
 #endif

 UFString res=str;
 lem_remove_char( res.ptr(), chs );
 res.calc_hash();

 #if LEM_DEBUGGING==1
 str.Assert();
 #endif

 return res;
}


UFString& UFString::strip( wchar_t Bound )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( len>=2 && str && *str==Bound && str[len-1]==Bound )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif
   memmove( str, str+1, sizeof(wchar_t)*(len-2) );
   str[len-2]=L'\0';
   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


UFString& UFString::strip_quotes(void)
{ return strip( (wchar_t)'"' ); }


UFString& UFString::strip_apostrophes(void)
{ return strip( (wchar_t)'\'' ); }


const UFString lem::strip( const UFString &fs, wchar_t Bound )
{
 UFString res=fs;
 res.strip(Bound);
 return res;
}


const UFString lem::strip_quotes( const UFString &str )
{ return strip( str, (wchar_t)'"' ); }


const UFString lem::strip_apostrophes( const UFString &str )
{ return strip( str, (wchar_t)'\'' ); }


UFString& UFString::dress( wchar_t Bound )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 UFString m = *this;
 (*this) = UFString(Bound) + m + UFString(Bound);

 #if LEM_DEBUGGING==1
 Assert();
 #endif
  
 return *this;
}


UFString& UFString::dress_quotes(void)
{ return dress( '"' ); }


UFString& UFString::dress_apostrophes(void)
{ return dress( '\'' ); }


UFString& UFString::dress_spaces(void)
{ return dress( ' ' ); }



const UFString lem::dress( const UFString &s, wchar_t Bound )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif
  
 return UFString(Bound) + s + UFString(Bound);
}


const UFString lem::dress_quotes( const UFString &s )
{ return dress( s, wchar_t('"') ); }


const UFString lem::dress_apostrophes( const UFString &s )
{ return dress( s, wchar_t('\'') ); }


const UFString lem::dress_spaces( const UFString &s )
{ return dress( s, wchar_t(' ') ); }


const UFString lem::to_lower( const UFString &s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 UFString res=s;
 res.to_lower();
 return res;
}


const UFString lem::to_upper( const UFString &s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 UFString res=s;
 res.to_upper();
 return res;
}


const UFString lem::subst(
                          const UFString &s,
                          const UFString &mask,
                          const UFString &text,
                          int nentry
                         )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 mask.Assert();
 text.Assert();
 #endif

 UFString res = s;
 res.subst( mask, text, nentry );

 #if LEM_DEBUGGING==1
 res.Assert();
 #endif

 return res;
}


const UFString lem::cut_final_commas( const UFString &s )
{
 UFString res=s;
 res.cut_final_commas();
 return res;
}


const UFString lem::to_Aa( const UFString &s )
{
 UFString res=s;
 res.to_Aa();
 return res;
}

 /***************************************************************
                    ОПЕРАТОР КОПИРОВАНИЯ
 ****************************************************************/


UFString& UFString::operator=( const char *s )
 {
  if( !s || !*s )
   {
    hash=len=0;

    if( str )
     {
      #if defined LEM_STRPOOL
      UnShare();
      #endif

      *str=0;
     }

    return *this;
   }

  #if defined LEM_STRPOOL
  UnShare();

  if( !ref_count )
   ref_count = new int(1);
  #endif

  len=CastSizeToInt(strlen(s));
  if( cap<len )
   {
    // Старый блок памяти слишком мал, чтобы разместить новую строку.
    str=Realloc( str, len+1 );
    cap=len;
   }

  lem_strcpy( str, s );
  calc_hash_only();

  #if LEM_DEBUGGING==1
  Assert();
  #endif


  return *this;
 }



UFString& UFString::operator=( const wchar_t *s )
{
 if( !s || !*s )
  {
   hash='\0';
   len=0;
   if( str )
    {
     #if defined LEM_STRPOOL
     UnShare();
     #endif
     *str=0;
    }
   return *this;
  }

 #if defined LEM_STRPOOL
 UnShare();

 if( !ref_count )
  ref_count = new int(1);
 #endif

 len=lem_strlen_nn(s);
 if( cap<len )
  {
   // Старый блок памяти слишком мал, чтобы разместить новую строку.
   str=Realloc( str, len+1 );
   cap=len;
  }

 lem_strcpy_nn( str, s );
 calc_hash_only();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


UFString& UFString::operator=( const std::wstring &s )
{
 return operator=( s.c_str() );
}


 /***************************************************************

                  ОПЕРАТОРЫ КОНКАТЕНАЦИИ

 ****************************************************************/

const UFString lem::operator+( const UFString& s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif

  const int l1=s1.length();
  const int l2=s2.length();
 
  if( !l1 ) return s2;
  if( !l2 ) return s1;

  wchar_t *sum = lem::UFString::Alloc(l1+l2+1);
  sum[0]='\0';

  if( s1.c_str() )
   lem_strcpy( sum, s1.c_str() );

  if( s2.c_str() )
   lem_strcat( sum, s2.c_str() );

  UFString res(sum,true);

  #if LEM_DEBUGGING==1
  res.Assert();
  s1.Assert();
  s2.Assert();
  #endif

  return res;
 }



const UFString lem::operator+( const UFString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  const int l1 = s1.length();
 
  if( !l1 ) return UFString(s2);

  const int l2 = lem_strlen(s2);

  if( !l2 ) return s1;
 
  wchar_t *sum = lem::UFString::Alloc(l1+l2+1);
  sum[0]='\0';

  if( s1.c_str() )
   lem_strcpy( sum, s1.c_str() );

  if( s2 )
   lem_strcat( sum, s2 );

  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  return UFString(sum,true);
 }



const UFString lem::operator+( const UFString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  const int l1 = s1.length();
  if( !l1 ) return UFString(s2);
  const int l2 = lem_strlen(s2);
  if( !l2 ) return s1;
  wchar_t *sum = lem::UFString::Alloc(l1+l2+1);
  sum[0]='\0';

  if( s1.c_str() )
   lem_strcpy( sum, s1.c_str() );

  if( s2 )
   lem_strcat( sum, s2 );

  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  return UFString(sum,true);
 }



const UFString lem::operator+( const char *s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif

  const int l1 = lem_strlen(s1);
  if( !l1  ) return s2;
  const int l2 = s2.length();
  if( !l2 ) return UFString(s1);

  wchar_t *sum = lem::UFString::Alloc(l1+l2+1);
  sum[0]='\0';

  if( s1 )
   lem_strcpy( sum, s1 );

  if( s2.c_str() )
   lem_strcat( sum, s2.c_str() );

  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif

  return UFString(sum,true);
 }


const UFString lem::operator+( const UFString& s1, wchar_t s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  const int l1=s1.length();
  wchar_t *sum = lem::UFString::Alloc(l1+2);
  sum[0]='\0';

  if( s1.c_str() )
   lem_strcpy( sum, s1.c_str() );

  if( s2!='\0' )
   {
    sum[l1]=s2;
    sum[l1+1]='\0';
   }

  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  return UFString(sum,true);
 }


const UFString lem::operator+( wchar_t ch, const UFString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  const int l2=s.length();
  wchar_t *sum = lem::UFString::Alloc(l2+2);

  sum[0]=ch;
  sum[1]='\0';

  if( !!(s.c_str()) )
   wcscpy( sum, s.c_str() );

  return UFString(sum,true);
 }


 // ***********************************************************************



UFString& UFString::operator+=( const UFString& s )
{
  #if LEM_DEBUGGING==1
  Assert();
  s.Assert();
  #endif

  if( s.empty() )
   return *this;

  const int l=length(), sl=s.length();

  #if defined LEM_STRPOOL
  UnShare();
  #endif

  if( cap < (l+sl) )
   {
    cap = 2*(l+sl+8);

    if( !str )
     {
      str = Alloc(cap+1);
      #if defined LEM_STRPOOL
      ref_count = new int(1);
      #endif
     }
    else
     {
      str = Realloc( str, cap+1 );
     }

    if( !l )
     *str='\0';
   }

//  wcscat( str, s.str );
  wcscpy( str+len, s.str );

  calc_hash();

  #if LEM_DEBUGGING==1
  Assert();
  s.Assert();
  #endif

  return *this;
 }



UFString& UFString::Add_Dirty( const UFString& s )
{
 #if LEM_DEBUGGING==1
 Assert();
 s.Assert();
 #endif

 if( s.empty() )
  return *this;

 const int l=length(), sl=s.length();
 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( cap < (l+sl) )
  {
   cap = 2*(l+sl+8);

   if( !str )
    {
     str = Alloc(cap+1);
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }

   if( !l )
    str[0]='\0';
  }

//  wcscat( str, s.str );
 wcscpy( str+len, s.str );
 len += s.len;

 #if LEM_DEBUGGING==1
 Assert();
 s.Assert();
 #endif
  
 return *this;
}


UFString& UFString::Add_Dirty_Chars( const wchar_t *s, size_t count )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( !count || !s )
  return *this;

 const int l=CastSizeToInt(length()), sl=CastSizeToInt(count);
 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( cap < (l+sl) )
  {
   cap = 2*(l+sl+8);

   if( !str )
    {
     str = Alloc(cap+1);
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }

   if( !l )
    str[0]='\0';
  }

 memcpy( str+len, s, sizeof(wchar_t)*count );
 len += CastSizeToInt(count);
 str[len]=0;

 #if LEM_DEBUGGING==1
 Assert();
 #endif
  
 return *this;
}


UFString& UFString::operator+=( const char *s )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  const int l=length(), sl = lem_strlen(s);

  if( !sl )
   return *this;


  #if defined LEM_STRPOOL
  UnShare();
  #endif

  if( cap < (l+sl) )
   {
    cap = 2*(l+sl+8);

    if( !str )
     {
      str = Alloc(cap+1);
      #if defined LEM_STRPOOL
      ref_count = new int(1);
      #endif
     }
    else
     {
      str = Realloc( str, cap+1 );
     }

    if( !l )
     str[0]='\0';
   }

  lem_strcat( str, s );

  calc_hash();

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return *this;
 }


UFString& UFString::Add_Dirty( const char *s )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  const int l=length();
  const int sl = lem_strlen(s);
  if( !sl ) return *this;

  #if defined LEM_STRPOOL
  UnShare();
  #endif
  if( cap < (l+sl) )
   {
    cap = 2*(l+sl+8);

    if( !str )
     {
      str = Alloc(cap+1);
      #if defined LEM_STRPOOL
      ref_count = new int(1);
      #endif
     }
    else
     {
      str = Realloc( str, cap+1 );
     }

    if( !l )
     str[0]='\0';
   }

  lem_strcat( str, s );
  len += sl;

  #if LEM_DEBUGGING==1
  Assert();
//  s.Assert();
  #endif

  return *this;
 }


UFString& UFString::operator+=( const wchar_t *s )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  const int l=length();
  const int sl = lem_strlen(s);
  if( !sl ) return *this;

  #if defined LEM_STRPOOL
  UnShare();
  #endif

  if( cap < (l+sl) )
   {
    cap = 2*(l+sl+8);

    if( !str )
     {
      str = Alloc(cap+1);
      #if defined LEM_STRPOOL
      ref_count = new int(1);
      #endif
     }
    else
     {
      str = Realloc( str, cap+1 );
     }

    if( !l )
     str[0]='\0';
   }

  //wcscat( str, s );
  wcscpy( str+len, s );
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  calc_hash();
  return *this;
 }


UFString& UFString::Add_Dirty( const wchar_t *s )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  const int l=length();
  const int sl = lem_strlen(s);
  if( !sl ) return *this;

  #if defined LEM_STRPOOL
  UnShare();
  #endif
  if( cap < (l+sl) )
   {
    cap = 2*(l+sl+8);

    if( !str )
     {
      str = Alloc(cap+1);
      #if defined LEM_STRPOOL
      ref_count = new int(1);
      #endif
     }
    else
     {
      str = Realloc( str, cap+1 );
     }

    if( !l )
     str[0]='\0';
   }

  //wcscat( str, s );
  wcscpy( str+len, s );
  len += sl;

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return *this;
 }


UFString& UFString::operator+=( wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  if( !ch )
   return *this;

  #if defined LEM_STRPOOL
  UnShare();
  #endif 
  if( cap < len+1 )
   {
    cap += (len+8);

    if( !str )
     {
      str = Alloc(cap+1);
      #if defined LEM_STRPOOL
      ref_count = new int(1);
      #endif
     }
    else
     {
      str = Realloc( str, cap+1 );
     }
   }

  str[len]=ch;
  str[len+1]='\0';

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  calc_hash();

  return *this;
 }



UFString& UFString::Add_Dirty( wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  if( ch=='\0' )
   return *this;

  #if defined LEM_STRPOOL
  UnShare();
  #endif
  if( cap < len+1 )
   {
    cap += (len+8);

    if( !str )
     {
      str = Alloc(cap+1);
      #if defined LEM_STRPOOL
      ref_count = new int(1);
      #endif
     }
    else
     {
      str = Realloc( str, cap+1 );
     }
   }

  str[len]=ch;
  str[len+1]='\0';
  len++;

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return *this;
 }

 /**************************************************************

                   СЕРВИСНЫЕ ФУНКЦИИ

 **************************************************************/

 /****************************************************************
   В указанную позицию вставляется символ, строка раздвигается.
   Если позиция вышла за диапазон [0,длина_строки), то ничего не
   происходит (это не баг, а ФИЧА).
 ****************************************************************/

void UFString::insert( int pos, wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  if( pos<=len )
   {
    #if defined LEM_STRPOOL
    UnShare();

    if( ref_count==NULL )
     ref_count = new int(1);
    #endif

    // Символ вставляется внутрь строки.

    // Есть еще место в куске памяти?
    if( cap < len+1 )
     {
      // Нет - расширяем.
      cap += (len+8);
      str=Realloc( str, cap+1 );
      if( !len )
       *str=0;
     }

    // Сдвигаем часть строки справа от позиции вставки.
    if( len )
     {
      memmove( str+pos+1, str+pos, sizeof(wchar_t)*(len-pos+1) );
      str[pos]=ch;
     }
    else
     {
      *str=ch;
      str[1]=0;
     } 

    calc_hash();
   }

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return;
 }

 /*********************************************************************
  Удаление символа из указанной позиции, строка сдвигается.
  Если позиция вне диапазона [0,длина_строки), то ничего не происходит.
 **********************************************************************/

void UFString::remove( int pos )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  #if defined LEM_STRPOOL
  UnShare();
  #endif
 
  if( pos == len-1 )
   str[pos]=0;
  else if( pos<len )
   lem_strcpy( str+pos, str+pos+1 );

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  calc_hash();
  return;
 }

 /******************************************************************
   Урезает строку на i символов, вызов reduce(0) не меняет строку.
   При выходе за пределы строки ничего не происходит.
 ******************************************************************/

UFString& UFString::reduce( int i )
 {
 LEM_CHECKIT_Z(i>=0);

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  int l=length();
  int term_pos=l-i;

  if( term_pos>l )
   return *this;

  #if defined LEM_STRPOOL
  UnShare();
  #endif

  str[term_pos]='\0';
  calc_hash();

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return *this;
 }


 /************************************************************************
   Формируем новую строку, состоящую из символов строки-аргумента s
   с i0-го в количестве nch. Если i0<0, то подразумевается i0=0. Если
   (i0+nch) больше, чем длина строки s, что в результатную строку будет
   занесено соответственно меньше символов.
 ************************************************************************/

const UFString lem::mid( const UFString &s, int I0, int nch )
{
 LEM_CHECKIT_Z(nch>=0);

 if( nch<=0 || I0<0 || I0>=s.length() )
  return lem::UFString();

  #if LEM_DEBUGGING==1
  s.Assert();
  #endif


  UFString res(nch,0);

  if( nch>=0 )
   {
    const int i0 = I0<0 ? 0 : I0;

    const int l=s.length();

    if( i0>=l )
     return res;

    for( int i=0; i<nch && (i+i0)<l; i++ )
     {
      res.ptr()[i] = s[i+i0];
      res.ptr()[i+1] = '\0';
     }
   }

  res.calc_hash();
  return res;
 }


 /**************************************************************************
   Возвращается строка, состоящая из символов строки-аргумента s, начина
   с первого (индекс 0) длиной nch. Если длина исходной строки недостаточна,
   то результат будет содержать соответственно меньшее количество символов.
 ***************************************************************************/

const UFString lem::left( const UFString &s, int NCH )
{
 LEM_CHECKIT_Z(NCH>=0);

 if( NCH<=0 )
  return lem::UFString();

  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  UFString res(NCH,'\0');

  if( NCH>0 )
   {
    const int l=s.length();
    const int nch = NCH>l ? l : NCH;

    for( int i=nch-1; i>=0; i-- )
     res.ptr()[i] = s[i];

    res.ptr()[nch] = '\0';
   }

  res.calc_hash();
  return res;
 }


 /*****************************************************************************
   Возвращается строка, состоящая из последних nch символов строки-аргумента s.
   Если длина исходной строки недостаточна, то результат будет содержать
   соответственно меньшее количество символов.
 ******************************************************************************/

const UFString lem::right( const UFString &s,  int NCH )
{
 LEM_CHECKIT_Z(NCH>=0);

 if( NCH<=0 )
  return lem::UFString();

  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  UFString res(NCH,'\0');

  if( NCH>0 )
   {
    const int l=s.length();
    const int nch = NCH>l ? l : NCH;

    int i0=l-nch;
    for( int i=0; i<nch; i++ )
     res.ptr()[i] = s[i+i0];

    res.ptr()[nch] = '\0';
   }

  res.calc_hash();
  return res;
 }


 // ********************************************************************
 // Длина строки увеличивается до n за счет добавления в конец строки
 // пробелов.
 // ********************************************************************

UFString& UFString::add_spaces( int n )
 {
 LEM_CHECKIT_Z(n>=0);

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  const int l = length();
  const int nn = n - l;

  // Есть что добавить?
  if( nn>0 )
   {
    for( int i=0; i<nn; i++ )
     Add_Dirty( static_cast<wchar_t>(' ') );

    calc_hash();
   }

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return *this;
 }



 // *************************************************
 // Фрагмент mask в строке s заменяем на text.
 // nentry - номер вхождения маски в исходный текст.
 // *************************************************

UFString& UFString::subst(
                          const UFString &mask,
                          const UFString &text,
                          int nentry
                         )
 {
  #if LEM_DEBUGGING==1
  Assert();
  mask.Assert();
  text.Assert();
  #endif

  const int istart = search( mask, nentry );

  if( istart==UNKNOWN )
   return *this;

  // Часть слева длиной istart
  const UFString left = lem::left( *this, istart );

  // Часть справа
  const UFString right = lem::right( *this, length()-mask.length()-istart );

  // Результат собираем из 3х частей.
  (*this) = left + text + right;

  #if LEM_DEBUGGING==1
  Assert();
  mask.Assert();
  text.Assert();
  #endif

  return *this;
 }


 // ***************************************************
 // Замена каждого вхождения строки mask на text.
 // ***************************************************

UFString& UFString::subst_all( const UFString &mask, const UFString &text, bool case_sensitive )
{
 #if LEM_DEBUGGING==1
 Assert();
 mask.Assert();
 text.Assert();
 #endif

 if( !str || !*str || !mask.str || !*mask.str )
  // Для пустой строки ничего не делаем.
  return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif 

 if( case_sensitive )
  {
   if( mask.length()>=text.length() )
    {
     // Так как при замене длина строки не увеличивается, то можем применять
     // значительно более быструю процедуру...
     int icur=0;
     wchar_t first = *mask.str;
     int mask_l = mask.length();
     int text_l = text.length();

     while( str[icur] )
      if( str[icur]==first )
       {
        // Нашли, где совпадает первый символ. Остальные символы также совпадают?
        bool match=true;
        for( int i=1; i<mask_l; i++ )
         {
          if( !str[icur+i] || str[icur+i]!=mask.str[i] )
           {
            match=false;
            break; 
           }
         }

        if( match )
         {
          // Нашли полное совпадение. Вписываем новую строку...
          for( int i=0; i<text_l; i++ )
           str[icur++] = text.str[i];
          
          // Сдвигаем результат, если после замены строка укоротилась. 
          if( mask_l>text_l )
           {
            int i_src = icur+mask_l-text_l;
            int i_dst = icur; 
            while( str[i_src] )
             {
              str[i_dst++] = str[i_src++];
             }
            str[i_dst]=0; 
           }
         }
        else
         icur++;   
       }
      else
       icur++;

     calc_hash();
    }
   else
    { 
     int istart=0;
     while( length() )
      {
       istart = search_from( mask, istart );
    
       if( istart==UNKNOWN )
        return *this;

       // Часть слева длиной istart
       // const UFString left = lem::left( *this, istart );

       // Часть справа
       const UFString right = lem::right( *this, length()-mask.length()-istart );

       // Результат собираем из 3х частей.
       // (*this) = left + text + right;
       reserve( istart+text.length()+right.length()+2 );

       // (*this) = left;
       trancate_to(istart);

       Add_Dirty(text);
       Add_Dirty(right);
       calc_hash();
   
       istart += text.length();
      }
    }
  }
 else
  { // поиск и замена без учета регистра
   if( mask.length()>=text.length() )
    {
     // Так как при замене длина строки не увеличивается, то можем применять
     // значительно более быструю процедуру...
     int icur=0;
     wchar_t first = lem::to_ulower(*mask.str);
     int mask_l = mask.length();
     int text_l = text.length();

     while( str[icur] )
      if( lem::to_ulower(str[icur])==first )
       {
        // Нашли, где совпадает первый символ. Остальные символы также совпадают?
        bool match=true;
        for( int i=1; i<mask_l; i++ )
         {
          if( !str[icur+i] || lem::to_ulower(str[icur+i])!=lem::to_ulower(mask.str[i]) )
           {
            match=false;
            break; 
           }
         }

        if( match )
         {
          // Нашли полное совпадение. Вписываем новую строку...
          for( int i=0; i<text_l; i++ )
           str[icur++] = text.str[i];
          
          // Сдвигаем результат, если после замены строка укоротилась. 
          if( mask_l>text_l )
           {
            int i_src = icur+mask_l-text_l;
            int i_dst = icur; 
            while( str[i_src] )
             {
              str[i_dst++] = str[i_src++];
             }
            str[i_dst]=0; 
           }
         }
        else
         icur++;   
       }
      else
       icur++;

     calc_hash();
    }
   else
    { 
     int istart=0;
     while( length() )
      {
       istart = searchi_from( mask, istart );
    
       if( istart==UNKNOWN )
        return *this;

       // Часть слева длиной istart
       // const UFString left = lem::left( *this, istart );

       // Часть справа
       const UFString right = lem::right( *this, length()-mask.length()-istart );

       // Результат собираем из 3х частей.
       // (*this) = left + text + right;
       reserve( istart+text.length()+right.length()+2 );

       // (*this) = left;
       trancate_to(istart);

       Add_Dirty(text);
       Add_Dirty(right);
       calc_hash();
   
       istart += text.length();
      }
    }
  }

 #if LEM_DEBUGGING==1
 Assert();
 mask.Assert();
 text.Assert();
 #endif

 return *this;
}


UFString& UFString::subst_all( wchar_t old_ch, wchar_t new_ch )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  #if defined LEM_STRPOOL
  UnShare();
  #endif

  int l=length();
  for( int i=0; i<l; i++ )
   if( str[i]==old_ch )
    str[i] = new_ch;

  calc_hash();
  return *this;
 }


 // *********************************************************************************
 // Замена всех макросов из списка (первый элемент пары - имя макроса - ЧТО МЕНЯЕМ;
 // второй элемент - НА ЧТО МЕНЯЕМ).
 // *********************************************************************************

UFString& UFString::subst_all( const std::vector< std::pair<UFString,UFString> > &macros )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  if( macros.empty() ) return *this;

  int istart=0;
  while( istart < length() )
   {
    bool found=false;

    // Ищем макрос, начиная с позиции istart, наиболее близкий справа к istart
    int istart_min=length();
    int i_mask=UNKNOWN;
    for( Container::size_type i=0; i<macros.size(); i++ )
     {
      int istart0 = search_from( macros[i].first.c_str(), istart );
  
      if( istart0!=UNKNOWN )
       {
        found=true;

        if( istart0 < istart_min )
         {
          istart_min=istart0;
          i_mask = CastSizeToInt(i);
         }
       }
     }
   
    if( !found )
     return *this;
    
    #if defined LEM_STRPOOL
    UnShare();
    #endif

    const UFString& a = macros[i_mask].first;
    const UFString& b = macros[i_mask].second;

    #if LEM_DEBUGGING==1
    a.Assert();
    b.Assert();
    #endif

    // Часть слева длиной istart
//    const UFString left = lem::left( *this, istart );

    // Результат собираем из 3х частей.
    if( macros[i_mask].second.length() <= macros[i_mask].first.length() )
     {
      // После подстановки длина строки уменьшится - можем применить
      // более быстрый подход.
      memcpy( str+istart_min, b.c_str(), b.length()*sizeof(wchar_t) );
      memmove(
              str+istart_min+b.length(),
              str+istart_min+a.length(),
              sizeof(wchar_t)*(len-istart_min-a.length()+1)
             );
      len -= (a.length()-b.length());
     }
    else
     {
      // Часть справа
      const UFString right = lem::right( *this, length()-a.length()-istart_min );

//    (*this) = left + macros[i_mask].second + right;

      reserve( istart_min+b.length()+right.length()+1 );
      trancate_to(istart_min);
//    (*this) = left;
      Add_Dirty(b);
      Add_Dirty(right);
     }

    istart = istart_min;
   }

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  calc_hash_only();

  return *this;
 }

 // *********************************************************************************
 // Расширение предыдущей процедуры - введена оптимизация поиска макросов с помощью
 // списка первых символов. В случаях, когда макросы имеют имена вида, допустим $aaa,
 // то есть первый символ одинаков, можно значительно ускорить поиск очередного
 // макроса в тексте.
 // *********************************************************************************

UFString& UFString::subst_all(
                                          const std::vector< std::pair<UFString,UFString> > &macros,
                                          const std::set<wchar_t> &first_chars 
                                         )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  int istart=0;
  while( istart < length() )
   {
    bool found=false;

    int istart_min=length();

    // Ищем крайнюю левую позицию, с которой встречаются макросы.
    typedef std::set<wchar_t>::const_iterator IT;
    for( IT ic=first_chars.begin(); ic!=first_chars.end(); ic++ )
     {
      int is = search_from( *ic, istart );

      if( is!=UNKNOWN )
       {
        istart_min = std::min( istart_min, is );
        found=true;
       }
     }

    if( !found )
     // Макросов не найдено
     return *this;


    #if defined LEM_STRPOOL
    UnShare();
    #endif

    istart = istart_min;

    // Ищем любой макрос, стоящий с позиции istart. Учитываем, что первый символ   
    // макроса уже отработан, так что ищем со второго символа (с позиции istart+1).
    found=false;
    int i_mask=UNKNOWN;
    for( Container::size_type i=0; i<macros.size(); i++ )
     {
//      const char *S1 = str+istart;
//      const char *S2 = macros[i].first.c_str();
      if( !memcmp( str+istart+1, macros[i].first.c_str()+1, sizeof(wchar_t)*(macros[i].first.length()-1) ) )
       {
        i_mask = CastSizeToInt(i);
        found = true;
       }  
     }
   
    if( found )
     {
      const UFString& a = macros[i_mask].first;
      const UFString& b = macros[i_mask].second;

      #if LEM_DEBUGGING==1
      a.Assert();
      b.Assert(); 
      #endif

      // Результат собираем из 3х частей.
/*
      if( macros[i_mask].second.length() <= macros[i_mask].first.length() )
       {
        // После подстановки длина строки уменьшится - можем применить
        // более быстрый подход.
        memcpy( str+istart_min, b.c_str(), b.length()*sizeof(wchar_t) );
        memmove(
                str+istart_min+b.length(),
                str+istart_min+a.length(),
                sizeof(wchar_t)*(len-istart_min-b.length()+1)
               );
        len -= (a.length()-b.length());
       }
      else
*/
       {
        // Часть справа
        const UFString right = lem::right( *this, length()-a.length()-istart_min );
  
        reserve( istart_min+b.length()+right.length()+1 );
        trancate_to(istart_min);
        Add_Dirty(b);
        Add_Dirty(right);
       }

      istart += b.length();
     }  
    else
     {
      istart++;
     } 
   }

  calc_hash_only();

  return *this;

 }




UFString& UFString::cut_final_commas(void)
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  // Сколько запятых на конце строки?
  int n_comma=0;

  for( int i=length()-1; i>=0; i-- )
   if( str[i]!=L',' )
    break;
   else
    n_comma++;

  // Теперь усекаем строку на n_comma символов.
  if( n_comma )
   {
    #if defined LEM_STRPOOL
    UnShare();
    #endif

    reduce( n_comma );
   }

  return *this;
 }



// ***********************************************
// Строки совпадают без учета регистра?
// ***********************************************
bool UFString::eqi( const UFString &x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 x.Assert();
 #endif

 if( x.len!=len )
  return false;

 for( int i=0; i<len; i++ )
  if( lem::to_uupper(x.str[i]) != lem::to_uupper(str[i]) )
   return false;

 return true;
}


bool UFString::eqi( const wchar_t *x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 
 if( !len )
  return x==NULL || *x==0;

 if( !x || !*x )
  return !len;

 for( int i=0; i<len+1; i++ )
  if( lem::to_uupper(str[i]) != lem::to_uupper(x[i]) )
   return false;

 return true;
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
bool UFString::eq_beg( const UFString &x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 x.Assert(); 
 #endif

 if( x.len>len )
  return false;

 if( x.len==len )
  return lem::operator==(*this,x);

 const int lx = x.len;
 for( int i=0; i<lx; i++ )
  if( x.str[i]!=str[i] )
   return false;

 return true;
}

// Без учета регистра
bool UFString::eq_begi( const UFString &x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

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


bool UFString::eq_beg( const char *x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int lx = lem_strlen(x);
 if( lx>length() )
  return false;

 if( lx==length() )
  return lem::operator==(*this,x);

 for( int i=0; i<lx; i++ )
  if( x[i]!=str[i] )
   return false;

 return true;
}


bool UFString::eq_beg( const wchar_t *x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int lx = lem_strlen(x);
 if( lx>len )
  return false;

 if( lx==len )
  return lem::operator==(*this,x);

 for( int i=0; i<lx; i++ )
  if( x[i]!=str[i] )
   return false;

 return true;
}


bool UFString::eq_begi( const wchar_t* x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int lx = lem_strlen(x);
 if( lx>len )
  return false;

 if( lx==len )
  return lem::operator==(*this,x);

 for( int i=0; i<lx; i++ )
  if( lem::to_uupper(x[i]) != to_uupper(str[i]) )
   return false;

 return true;
}


 // *********************************************************************
 // Приводим к лексему к виду 'Aaaaa', то есть первая буква - заглавная,
 // все остальные - маленькие.
 // *********************************************************************

UFString& UFString::to_Aa(void)
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  if( !length() )
   return *this;

  #if defined LEM_STRPOOL
  UnShare();
  #endif

  to_lower();

  wchar_t buf[2]= { str[0], '\0' };
  lem::to_upper(buf);

  str[0] = buf[0];
  calc_hash();

  return *this;
 }



 // ***********************************************************************
 // Возвращаемая строка содержит все символы аргумента str за исключением
 // символов, перечисленных в строке chs.
 // ***********************************************************************

const UFString lem::remove_chars( const UFString &str, const wchar_t *chs )
 {
  #if LEM_DEBUGGING==1
  str.Assert();
  #endif

  UFString res;
  res.reserve( str.length() );

  if( !str.empty() )
   {
    int i=0;

    while( str[i]!='\0' )
     {
      if( !find_char_in_string( str[i], chs ) )
       res.Add_Dirty( str[i] );

      i++;
     }

    res.calc_hash();
   }

  return res;
 }


 // *************************************************************
 // Возвращает строку, состоящую из символов ch, которые находятся
 // в начале строки s.
 // *************************************************************

const UFString lem::get_lead_chars( const UFString &s, wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  UFString res;

  const int l=s.length();
  for( int i=0; i<l; i++ )
   if( s[i]!=ch )
    break;
   else
    res += ch;

  return res;
 }



int lem::LastDelimiter( const UFString &s, const wchar_t *delimiters )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  // From end char...
  for( int i=s.length()-1; i>=0; i-- )
   // Is it delimiter?
   if( lem_find( delimiters, s[i] )!=UNKNOWN )
    // Yes - return index of char.
    return i;

  // Nothing matches.
  return UNKNOWN;
 }



 // ***************************************************************
 // Символы '\n' и прочие преобразует в двухсимвольные сочетания,
 // которые обычно транслятор C++ преобразует в '\n' и пр.
 // ***************************************************************

const UFString lem::unpack_c( const wchar_t *Sent )
 {
  UFString res;

  if( !(Sent) )
   return res;

  int i=0;
  while( Sent[i]!=0 )
   {
    switch(Sent[i])
    {
     case L'\n': res+='\\'; res+='n'; break;
     case L'\t': res+='\\'; res+='t'; break;
     case L'\r': res+='\\'; res+='r'; break;
     case L'\f': res+='\\'; res+='f'; break;
     case L'\b': res+='\\'; res+='b'; break;
     default: res+=Sent[i]; break;
    }

    i++;
   }

  return res;
 }



   // ********************************************************
   // Строка урезается до new_len символов (если это возможно)
   // ********************************************************
   UFString& UFString::trancate_to( int new_len )
   {
 LEM_CHECKIT_Z(new_len>=0);

    #if LEM_DEBUGGING==1
    Assert();
    #endif

    if( new_len>=0 && new_len<len )
     {
      len=new_len;
      str[len]=0;
      calc_hash();
     }

    return *this;
   }

   // ******************************************************************
   // Из строки вырезается и выкидывается участок начиная с символа from
   // до (включая) символа upto. Возвращается ссылка на себя же.
   // Для того, чтобы получить строку [from,upto], используй mid(...)
   // ******************************************************************

   UFString& UFString::cut( int from, int upto )
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif

    if( from>=0 && upto<len && from<upto )
     {
      #if defined LEM_STRPOOL
      UnShare();
      #endif

      memmove( str+from, str+upto, sizeof(wchar_t)*(len-upto+1) );
      calc_hash();
     }

    return *this;
   }


UFString& UFString::reserve( lem::UFString::size_type new_cap )
{
 #if defined LEM_64
 LEM_CHECKIT_Z( new_cap!=lem::uint64_max );
 #elif defined LEM_32
 LEM_CHECKIT_Z( new_cap!=lem::uint32_max );
 #else 
  #error Unknown platform
 #endif

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( cap < CastSizeToInt(new_cap) )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif

   if( !cap )
    {
     // Была пустая строка...
     str = Alloc( CastSizeToInt(new_cap)+1);
     *str=0;
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     // Increase the capacity of memory allocated for string, so it will be
     // able to store up to new_cap chars.
     str = Realloc( str, CastSizeToInt(new_cap)+1 );
    }

   cap=CastSizeToInt(new_cap);
  }

 return *this; 
}



 void UFString::LoadBin( lem::Stream &bin )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif
   bin.rd( this );
   #if LEM_DEBUGGING==1
   Assert();
   #endif
  }


 void UFString::SaveBin( Stream &bin ) const
  {
   bin.wr( this );
   #if LEM_DEBUGGING==1
   Assert();
   #endif
  }



void UFString::copy( const wchar_t *beg, const wchar_t *end )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  #if defined LEM_STRPOOL
  UnShare();
  #endif 
  reserve( end-beg+1 );
  std::copy( beg, end, str );
  str[ end-beg ] = 0;
  calc_hash();
  cap=len;
 }

const UFString lem::to_NULL( const UFString &s )
{ return s.empty() ? UFString(L"NULL") : dress_apostrophes(s); }


   // *********************************************
   // Reduce string length to new_len.
   // *********************************************
void UFString::ShrinkTo( int new_len )
{
 LEM_CHECKIT_Z(new_len>=0);

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( new_len<len && len )
  {
   str[new_len]=0;
   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif
}


void UFString::clear(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 hash=len=0;
 if(str) *str=0;

 return;
}


int UFString::to_int(void) const
{
 return lem::to_int(str);
}


bool UFString::to_bool(void) const
{
 return lem::to_bool(str);
}



UFString& UFString::normalize_diaktrics(void)
{
 #if defined LEM_UNICODE_EX
 if( str!=NULL ) 
  {
   lem::CodeConverter::Strip_Diaktrices( str );
   calc_hash();
  }
 #endif

 return *this;
}


// ************************************************
// Поиск символа справа налево.
// @retval индекс найденного символа
// @retval UNKNOWN если символ не найден
// ************************************************
int UFString::find_last_of( wchar_t ch ) const
{
 if( empty() )
  return UNKNOWN;

 int pos=len-1; 
 for( int i=pos; i>=0; i-- )
  if( str[i]==ch )
   return i;

 return UNKNOWN;
}


static UFString soundex_normalize( const UFString &src )
{
 UFString res;
 res.reserve( src.length() );
 int i=0;
 while( i<src.length() )
  {
   #if defined LEM_UNICODE_EX
   wchar_t c0 = lem::CodeConverter::Strip_Diaktrices( to_ulower( src[i] ) );
   #else
   wchar_t c0 = to_ulower( src[i] );
   #endif

   wchar_t c = 0;

   #if defined LEM_UNICODE_EX
   wchar_t c1, c2;
   if( lem::CodeConverter::Normalize_Ligatures( c0, c1, c2 ) )
    c0 = c1;
   #endif

   switch( c0 )
   {
    case L'\x0431': c = L'b'; break;
    case L'\x0432': c = L'v'; break;
    case L'\x0433': c = L'g'; break;
    case L'\x0434': c = L'd'; break;
    case L'\x0436': c = L'j'; break;
    case L'\x0437': c = L'z'; break;
    case L'\x043A': c = L'k'; break;
    case L'\x043B': c = L'l'; break;
    case L'\x043C': c = L'm'; break;
    case L'\x043D': c = L'n'; break;
    case L'\x043F': c = L'p'; break;
    case L'\x0440': c = L'r'; break;
    case L'\x0441': c = L's'; break;
    case L'\x0442': c = L't'; break;
    case L'\x0444': c = L'f'; break;
    case L'\x0445': c = L'h'; break;
    case L'\x0446': c = L'c'; break;
    case L'\x0447': c = L'c'; break;
    case L'\x0448': c = L's'; break;
    case L'\x0449': c = L's'; break;
    case L'b': c = L'b'; break;
    case L'c': c = L'k'; break;  // config==konfig
    case L'd': c = L'd'; break;
    case L'f': c = L'f'; break;
    case L'g': c = L'g'; break;
    case L'k': c = L'k'; break;
    case L'l': c = L'l'; break;
    case L'm': c = L'm'; break;
    case L'n': c = L'n'; break;
    case L'p': c = L'p'; break;
    case L'q': c = L'k'; break;
    case L'r': c = L'r'; break;
    case L's': c = L's'; break;
    case L't': c = L't'; break;
    case L'v': c = L'v'; break;
    case L'w': c = L'v'; break;  // water==vater
    case L'x': c = L'k'; break;
    case L'z': c = L'z'; break;
   }  

   if( c!=0 )
    res.Add_Dirty(c);

   i++;
  }

 res.calc_hash();
 return res;
}


// **************************************************************************
// Сравнение двух строк через фонетическую нормализацию и сравнение согласных
// Возвращается похожесть, 1.0 - полностью совпадают, 0.0 - полностью
// несовпадают. a - строка, b - искомая маска
// **************************************************************************
float lem::eq_soundex( const UFString &a, const UFString &b )
{
 if( a.empty() && b.empty() )
  return 1.0;

 UFString a1( soundex_normalize(a) );
 UFString b1( soundex_normalize(b) );

 if( a1.empty() || b1.empty() )
  return 0.0;

 const int pos = a1.search( b1 );
 if( pos==UNKNOWN )
  {
   // ...

   return 0.0;
  } 

 return 1.0;

/*
 int ia0=0;

 while( ia0<a1.length() ) 
  {
   // Если первые символы не совпадают, то попробуем смещать маску вправо до совпадения.
   int ia=ia0, ib=0;
 
   int l = std::min( a1.length()-ia, b1.length() );
   int miss_count=0, match_count=0;

   for( ; ia<a1.length() && ib<b1.length(); ia++, ib++ )
    if( a1[ia]!=b1[ib] )
     {
//      miss_count++;
//      if( miss_count>2 )
//       {
//        if( match_count>0 )
//         return 0.0;
//
//        // Начальные символы не совпадают, смещаемся вправо.
//        ia++;
//        continue;  
//       }
      // Начальные символы не совпадают, смещаемся вправо.
      ia++;
     }
    else
     {
      match_count++;
     } 

   float v = float(1.0) - float(miss_count)/float(l);
   if( match_count && v>0.3 )
    return v;

   ia0++;
  }

 return 0.0;
*/
}


// *************************************************************
// Первая фаза нечеткого поиска строки в большом массиве строк.
// Подготавливаем более удобный для последующих массовых
// сравнений паттерн.
// *************************************************************
lem::SoundexPattern lem::eq_soundex1( const UFString &pattern )
{ return soundex_normalize(pattern); }

float lem::eq_soundex2( const UFString &a, const lem::SoundexPattern &pattern )
{
 UFString a1( soundex_normalize(a) );

 const int pos = a1.search( pattern );
 if( pos==UNKNOWN )
  {
   // ...

   return 0.0;
  } 

 return 1.0;
}

UFString& UFString::operator+=( const std::wstring &s )
{ return operator+=( s.c_str() ); }


#if defined LEM_DOT_NET
UFString& UFString::operator+=( System::String *s )
{ return operator+=( UFString(s) ); }
#endif

#if defined LEM_VCL
//UFString& UFString::operator+=( const WideString &s )
//{ return operator+=(s.c_str()); }
#endif

#if defined LEM_QT && defined LEM_UNICODE
UFString& UFString::operator+=( const QString &x )
{ return operator+=((const wchar_t*)x.constData()); }
#endif
  
#if defined LEM_WXWIDGETS && defined LEM_UNICODE
UFString& UFString::operator+=( const wxString &s )
{ return operator+=(s.c_str()); }
#endif

#if defined LEM_MFC
UFString& UFString::operator+=( const CStringW &s )
{ return operator+=((const wchar_t*)s); }
#endif


#if defined LEM_DOT_NET
bool UFString::operator==( System::String *s ) const
{ return length() == s->Length && lem::operator==(*this,UFString(s)); }

bool UFString::operator!=( System::String *s ) const
{ return length() != s->Length || !lem::operator==(*this,UFString(s)); }
#endif

#if defined LEM_VCL
//bool lem::operator==( const UFString &s1, const WideString &s )
//{ return s1.length() == s.Length() && lem::operator==(s1,lem::UFString(s)); }

//bool lem::operator!=( const UFString &s1, const WideString &s )
//{ return s1.length() != s.Length() || !lem::operator==(s1,lem::UFString(s)); }
#endif

#if defined LEM_QT && defined LEM_UNICODE
bool lem::operator==( const UFString &s1, const QString &s )
{ return s1.length() == s.length() && lem::operator==(s1,lem::UFString(s)); }

bool lem::operator!=( const UFString &s1, const QString &s )
{ return s1.length() != s.length() || !lem::operator==(s1,lem::UFString(s)); }
#endif
  
#if defined LEM_WXWIDGETS && defined LEM_UNICODE
bool lem::operator==( const UFString &s1, const wxString &s ) 
{ return s1.length() == s.length() && lem::operator==(s1,lem::UFString(s)); }

bool lem::operator!=( const UFString &s1, const wxString &s ) 
{ return s1.length() != s.length() || !lem::operator==(s1,lem::UFString(s)); }
#endif


#if defined LEM_MFC
bool lem::operator==( const UFString &s1, const CStringW &s )
{ return s1.length()==s.GetLength() && lem::operator==(s1,(const wchar_t*)s); }

bool lem::operator!=( const UFString &s1, const CStringW &s )
{ return s1.length()!=s.GetLength() || !lem::operator==(s1,(const wchar_t*)s); }
#endif


#if defined LEM_ICU 
UFString& lem::UFString::operator=( const UnicodeString &s )
{
// operator=( s.getBuffer() );
LEM_STOPIT;
 return *this;
}

UFString& lem::UFString::operator+=( const UnicodeString &s )
{
// operator+=( s.getBuffer() );
LEM_STOPIT;
 return *this;
}

bool lem::UFString::operator==( const UnicodeString &s ) const
{
// return s.length()==s.length() && operator==(s.getBuffer());
LEM_STOPIT;
return false;
}

bool lem::UFString::operator!=( const UnicodeString &s ) const
{
// return s.length()!=s.length() || operator!=(s.getBuffer());
LEM_STOPIT;
return false;
}

#endif



void lem::swap( lem::UFString &x, lem::UFString &y )
{
 std::swap( x.str, y.str );

 #if defined LEM_STRPOOL
 std::swap( x.ref_count, y.ref_count );
 #endif

 std::swap( x.len, y.len );
 std::swap( x.cap, y.cap );
 std::swap( x.hash, y.hash );
 
 return;
}



int lem::UFString::ToInt(void) const
{
 UFString s(*this);
 s.trim();
 return lem::to_int(s);
}

bool lem::UFString::ToBool(void) const
{
 UFString s(*this);
 s.trim();
 return lem::to_bool(s.c_str());
}


bool lem::UFString::eq_end( const wchar_t* to_find ) const
{
 int l = lem_strlen(to_find);
 if( l>length() )
  return false;

 return lem_eq( to_find, str+length()-l );
}


bool lem::UFString::eq_endi( const wchar_t* to_find ) const
{
 int l = lem_strlen(to_find);
 if( l>length() )
  return false;

 return lem_eqi( to_find, str+length()-l );
}


bool lem::UFString::eq_end( const UFString & to_find ) const
{
 int l = to_find.length();
 if( l>length() )
  return false;

 return lem_eq( to_find.c_str(), str+length()-l );
}


bool lem::UFString::eq_endi( const UFString & to_find ) const
{
 int l = to_find.length();
 if( l>length() )
  return false;

 return lem_eqi( to_find.c_str(), str+length()-l );
}


#if defined LEM_QT
QString lem::UFString::to_qt(void) const
{
 return QString::fromWCharArray(str);
}
#endif
