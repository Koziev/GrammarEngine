// File LEM_CONV.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Lexical conversions.
//
// �������� �������������� ����� ��������� � ���������� �������� ��������������
// ��������� ����� ������.
//
// 29.05.2006 - � ����������� ��������� ������� '<<' � '>>'
//
// 16.11.2006 - � filesize_to_wstr �������� ������� bytes ��� �������� � ������
//
// 01.02.2007 - ���������� ������ � to_real, ���� ������ ������ ������, ��
//              ������������ ���� ������ �������������� (������ �����������
//              �����).
//
// 27.04.2007 - Borland VCL strings, QString, wxString conversion functions
//              have been added
//
// 19.10.2007 - ��������� ��������� decode_from_url
//
// 22.02.2008 - ���������� ������ � lem::parse
// 31.10.2008 - ���������� ������ � to_lower � to_upper ��� char* 
// 10.02.2009 - � ���������� are_cyr_only � ������ �� ��� �� ����� �����������
//              ������� ������������ ��� ���������� ��������� ������� ���� "�.�."
// -----------------------------------------------------------------------------
//
// CD->11.01.1996
// LC->15.01.2011
// --------------

#include <cstdlib>
#include <cctype>
#include <cstring>
#include <utility>

#if defined LEM_ICU
 #include <icu/include/unicode/utypes.h>
 #include <icu/include/unicode/uchar.h>
#endif

#include <lem/cstring.h>
#include <lem/runtime_checks.h>
#include <lem/unicode.h>
#include <lem/lexers.h>

#include <lem/conversions.h>


#if defined LEM_MSC && _MSC_VER<=1200
 #define LEM_MSVC65
#endif


using namespace std;
using namespace lem;

static wchar_t _allowed_lexem_punctuators[] = L" ~`&-_+'\".";

const char* lem::SOURCE_DELIMS=" .()<>?$+-*/%#@!~^'\":[]{}=\\|&,;\t\n\r";

const char* lem::SOURCE_COMPL_DELIMS="+=\0"
                    "-=\0"
                    "/=\0"
                    "*=\0"
                    "|=\0"
                    "&=\0"
                    "%=\0"
                    "^=\0"
                    "<=\0"
                    ">=\0"
                    "==\0"
                    "!=\0"
                    "++\0"
                    "--\0"
                    "||\0"
                    "&&\0"
                    "^^\0"
                    ">>\0"
                    "<<\0"
                    "->\0"
                    "::\0"
                    "<<=\0"
                    ">>=\0"
                    "..\0";

// *********************************
// ��������� � ��������� MSDOS
// Do not edit!
// *********************************
static char rusABC[68]=
"\x80\x81\x82\x83\x84\x85\xf0\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f"
"\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0"
"\xa1\xa2\xa3\xa4\xa5\xf1\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xe0"
"\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef";

// *********************************
// ��������� � ��������� MS Windows
// *********************************
static char rusABC_win[68]=
"�����Ũ�����������������������������������������������������������";

// ********************************
// ��������� � ��������� KOI-8
// Do not edit!
// ********************************
static char rusABC_koi8[68]=
"\xe1\xe2\xf7\xe7\xe4\xe5\xb3\xf6\xfa\xe9\xea\xeb\xec\xed\xee\xef\xf0"
"\xf2\xf3\xf4\xf5\xe6\xe8\xe3\xfe\xfb\xfd\xff\xf9\xf8\xfc\xe0\xf1\xc1"
"\xc2\xd7\xc7\xc4\xc5\xa3\xd6\xda\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd2"
"\xd3\xd4\xd5\xc6\xc8\xc3\xde\xdb\xdd\xdf\xd9\xd8\xdc\xc0\xd1";





// ************************************
// ��������� � UNICODE
// ************************************
static wchar_t rusABC_uni[67]={
// �      �       �        �        �        �        �        �       �
0x0410u, 0x0411u, 0x0412u, 0x0413u, 0x0414u, 0x0415u, 0x0401u, 0x0416u, 0x0417u,
0x0418u, 0x0419u, 0x041au, 0x041bu, 0x041cu, 0x041du, 0x041eu, 0x041fu, 0x0420u,
0x0421u, 0x0422u, 0x0423u, 0x0424u, 0x0425u, 0x0426u, 0x0427u, 0x0428u, 0x0429u,
0x042au, 0x042bu, 0x042cu, 0x042du, 0x042eu, 0x042fu,


// �      �       �        �        �        �        �        �        �
0x0430u, 0x0431u, 0x0432u, 0x0433u, 0x0434u, 0x0435u, 0x0451u, 0x0436u, 0x0437u,
0x0438u, 0x0439u, 0x043au, 0x043bu, 0x043cu, 0x043du, 0x043eu, 0x043fu, 0x0440u,
0x0441u, 0x0442u, 0x0443u, 0x0444u, 0x0445u, 0x0446u, 0x0447u, 0x0448u, 0x0449u,
0x044au, 0x044bu, 0x044cu, 0x044du, 0x044eu, 0x044fu,

0x2116u
};





// *********************************************
// Command line option delimiter
// *********************************************
//const bool lem_is_opchar( const char ch )
//{ return ch=='/' || ch=='-'; }


bool lem::is_delim( char ch )
{
 return ch=='\0' ||
        ch=='.'  ||
        ch==','  ||
        ch=='/'  ||
        ch=='\\' ||
        ch=='|'  ||
        ch==':'  ||
        ch==';'  ||
        ch=='\'' ||
        ch=='"'  ||
        ch=='?'  ||
        ch=='<'  ||
        ch=='>'  ||
        ch=='{'  ||
        ch=='}'  ||
        ch=='['  ||
        ch==']'  ||
        ch=='~'  ||
        ch=='`'  ||
        ch=='!'  ||
        ch=='@'  ||
        ch=='#'  ||
        ch=='$'  ||
        ch=='%'  ||
        ch=='^'  ||
        ch=='&'  ||
        ch=='*'  ||
        ch=='('  ||
        ch==')'  ||
        ch=='-'  ||
        ch=='='  ||
        ch=='+'  ||
        ch=='\t'  ||
        ch=='\r'  ||
        ch=='\n';
}



static char NUMERIQUES[37]="0123456789abcdefghijklmnopqrstuvwxyz";

char lem::get_numerique( int numer )
{
 if( numer>=37 )
  throw ECheckFault( to_wstr("Incorrect character in number field") );
 return NUMERIQUES[numer];
}

bool lem::is_numerique( char ch )
{
 return strrchr( NUMERIQUES, ch ) != NULL;
}

/*********************************************************
  ��������� ��� ���������� �����. � ��������� ANSI Cfront
  ������� itoa, ltoa, ultoa �� �������������, ������
  ����� ������������ ����.
*********************************************************/
char* lem::int16_to_str( lem::int16_t Val, char *buffer, int radix )
{
 lem::int16_t val=Val;

 LEM_CHECKIT_Z( radix>0 && radix<36 );

 if( val==0 )
  {
   buffer[0]='0';
   buffer[1]=0;
   return buffer;
  }

 lem::int16_t maxradix=1;
 while( maxradix<32767 && 32767/maxradix >= radix )
  maxradix *= static_cast<lem::int16_t>(radix);

 int ibpos=-1;
 int numer;
 bool positive=true;

 if(val<0)
  {
   val = static_cast<lem::int16_t>(-val);
   positive=false;

   if(val<0)
    val=-(SHRT_MIN+1);
  }

 while( maxradix>0 )
  {
   numer = val/maxradix;

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = NUMERIQUES[numer];

   val      %= maxradix;
   maxradix /= static_cast<lem::int16_t>(radix);
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 if( !positive )
  {
   memmove( buffer+1, buffer, ibpos+1 );
   buffer[0]='-';
  }

 return buffer;
}

const lem::CString lem::int16_to_str( lem::int16_t val, int radix )
{
 LEM_CHECKIT_Z( radix>0 && radix<36 );

 char buffer[CString::max_len+1];
 int16_to_str( val, buffer, radix );
 return CString(buffer);
}

char* lem::uint16_to_str( lem::uint16_t Val, char *buffer, int radix )
{
 LEM_CHECKIT_Z( radix>0 && radix<36 );

 lem::uint16_t val=Val;

 if( val==0 )
  {
   buffer[0]='0';
   buffer[1]=0;
   return buffer;
  }

 lem::uint16_t maxradix=1;
 while(
       maxradix< uint16_max &&
       uint16_max/maxradix >= radix
      )
  maxradix *= static_cast<lem::uint16_t>(radix);

 int ibpos=-1;
 int numer;

 while( maxradix>0 )
  {
   numer = val/maxradix;

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = NUMERIQUES[numer];

   val      %= maxradix;
   maxradix /= static_cast<lem::uint16_t>(radix);
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 return buffer;
}


char* lem::int32_to_str( lem::int32_t Val, char *buffer, int radix )
{
 LEM_CHECKIT_Z( radix>0 && radix<36 );

 lem::int32_t val=Val;

 if( val==0 )
  {
   buffer[0]='0';
   buffer[1]=0;
   return buffer;
  }

 lem::int32_t maxradix=1;
 while( maxradix< int32_max && int32_max/maxradix >= radix )
  maxradix *= static_cast<lem::int32_t>(radix);

 int ibpos=-1;
 lem::int32_t numer;
 bool positive=true;

 if(val<0)
  {
   val=-val;
   positive=false;

   if(val<0)
    val=-(INT_MIN+1);
  }

 while( maxradix>0 )
  {
   numer = val/maxradix;

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = NUMERIQUES[(int)numer];

   val      %= maxradix;
   maxradix /= radix;
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 if( !positive )
  {
   memmove( buffer+1, buffer, ibpos+1 );
   buffer[0]='-';
  }

 return buffer;
}


const lem::CString lem::int32_to_str( lem::int32_t val, int radix )
{
 LEM_CHECKIT_Z( radix>1 && radix<36 );

 lem::CString buffer;
 int32_to_str( val, buffer.ptr(), radix );
 buffer.calc_hash();
 return buffer;
}

char* lem::uint32_to_str( lem::uint32_t Val, char *buffer, int radix )
{
 LEM_CHECKIT_Z( radix>1 && radix<36 );
 LEM_CHECKIT_Z( buffer!=NULL );

 lem::uint32_t val=Val;

 if( val==0 )
  {
   buffer[0]='0';
   buffer[1]=0;
   return buffer;
  }

 lem::uint32_t maxradix=1;
 while(
       maxradix<uint32_max &&
       int32_max/maxradix >= static_cast<lem::uint32_t>(radix)
      )
  maxradix *= static_cast<lem::uint32_t>(radix);

 int ibpos=-1;
 lem::uint32_t numer;

 while( maxradix>0 )
  {
   numer = val/maxradix;

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = NUMERIQUES[static_cast<int>(numer)];

   val      %= maxradix;
   maxradix /= radix;
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 return buffer;
}


/*************************************************************************
  ��������� ��� ������������ ���������� ����������� �����
  ���� lem::uint64_t. ������������ ������� ������� ��� ����������
  ����� � ������ ���������� ������ OFormatter.


  ������� ���������:

   v      -  �������� ���� lem::uint64_t.

   buffer - ��������� �� ������� ������, � ������� ����� �����������
            ��������� ������ ����� (C-������). ������� �������, �����
            ������ ������ ��� ���������� ��� ���������� ������ �
            ������������� �����, ������������ ����� ��������� ��
            ���������� lem::uint64_t_MAX � ������� ��������� � ����������
            2 - 81 ����.

   radix  - ��������� ������� ���������, � ������� ����� �����������
            �����. ���� �������� ����� ���������� � ��������� [2,36].


  ������������ ��������: ������������ ��������� �� buffer.


  ����������: ANSI Cfront 2.0-�����������.


  ������� ���������: ���������� ������ ANSI-����������� ���������.

  ���������:
            1. ��� ����������� �������� ��������� radix ����������
               ��������� � ������ LEM_DEBUGGING �����������. � �����������
               ������ ���������� buffer ����� ������� ������� �����.

***********************************************************************/

#if defined LEM_UI64
//#include <lem_ui64.h>

char* lem::to_str(
                  lem::uint64_t val,
                  char *buffer,
                  int radix
                 )
{
 LEM_CHECKIT_Z(buffer!=NULL);
 LEM_CHECKIT_Z(radix>1 && radix<36);
 
 #if defined LEM_WINDOWS
 return ::_ui64toa( val, buffer, radix );
 #else
 LEM_CHECKIT_Z( radix>0 && radix<36 );

 if( val==0 )
  {
   buffer[0]='0';
   buffer[1]=0;
   return buffer;
  }

 lem::uint64_t maxradix=1;
 lem::uint64_t foresee=maxradix*radix;

 while( foresee > maxradix )
  {
   maxradix = foresee;
   foresee *= radix;
  }

 lem::uint64_t tval=val;
 int ibpos=-1;
 int numer;

 while( maxradix>0 )
  {
   lem::uint64_t rd = tval/maxradix;
   numer = int(rd);

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = get_numerique(numer);

   tval     %= maxradix;
   maxradix /= radix;
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 return buffer;
 #endif
}
#endif

#if defined LEM_I64
//#include <lem_i64.h>
char* lem::to_str( lem::int64_t val, char *buffer, int radix )
{
 LEM_CHECKIT_Z(buffer!=NULL);
 LEM_CHECKIT_Z(radix>1 && radix<36);
 
 #if defined LEM_WINDOWS
 return ::_ui64toa( val, buffer, radix );
 #else

 if( val==0 )
  {
   buffer[0]='0';
   buffer[1]=0;
   return buffer;
  }

 lem::int64_t tval=val;
 if( tval<0 )
  tval = -tval;

 lem::int64_t maxradix=1,mrd;

 do
  {
   mrd=maxradix*radix;

   if( mrd<=maxradix || mrd>tval )
    break;

   maxradix = mrd;
  }
 while(1);

 int ibpos=-1;
 int numer;

 lem::int64_t rd;
 while( maxradix>0 )
  {
   rd = tval/maxradix;
   numer = int(rd);

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = get_numerique(numer);

   tval     = tval%maxradix;
   maxradix = maxradix/radix;
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 // ���� �����, �� ������ ���.
 if( val<0 )
  {
   for( int i=ibpos+1; i>=0; i-- )
    buffer[i]=buffer[i-1];

   buffer[0]='-';
  }

 return buffer;
 #endif
}
#endif

/*
#if defined LEM_INTN
#include <lem/lem_i128.h>
char* lem::to_str(
                  const integer128& val,
                  char *buffer,
                  int radix
                 )
{ return val.to_str(buffer,radix); }
#endif
*/

/*****************************************************************************
  ������������ ���������� ������������� ����� ���������
  �� ��c��: ����� (�� ���������� �����), ������� (�����
  �����) � ����������. �����, ���� ��� ������������, ��������
  ������ int_signum � exp_signum ������������� �� +/-1.

  ������� ���������:

    src       - ��������� ������, ���������� �������� �����
    int_len, frac_part, exp_part - ������������ ����� ������, ������� �����
                ���������� � �������� ���� int_part, frac_part, exp_part
                ��������������, ������� '\0'. ���� ==-1, �� �������
                ������������ ���� �� �����.

    int_part  - ��������� �� �����, � ������� ����� �������� ������ ��������
                ����� �����. ���� ��������, ���� �� ��������� � ��������
                ����, ������� � int_part �� ����� - ��. ���� int_signum.

    frac_part - ��������� �� �����, � ������� ����� �������� ������ ����
                ������� ����� ����� (��� ������� �����, ����������).

    exp_part  - ��������� �� ����� ��� ���� ����������. ���� ����������
                ������� � ���� �� �����, ��. ���� exp_signum.


    int_signum - ��������� �� ���� ��� ���������� ����� ��������, +1 ��� -1.
    exp_signum - ��������� �� ���� ��� ���������� ����� ����������, +1 ��� -1.

  RETURN: true � ������ ������.
******************************************************************************/
bool lem::split(
                const char *src,
                int *int_signum, char *int_part,  int int_len,
                                 char *frac_part, int frac_len,
                int *exp_signum, char *exp_part,  int exp_len
               )
{
 LEM_CHECKIT_Z( src!=NULL );

 *int_signum = *exp_signum = 1; // �� ��������� ��������� ���� '+'.

 // �������� ��������� ����� �����, � ��������� ����������
 // ������.

 int isrc=int_part[0]=frac_part[0]=exp_part[0]=0;
 int iint_part=0, ifrac_part=0, iexp_part=0;

 // ��������� ������� ����������.
 while( isspace(src[isrc]) ) isrc++;

 // ���� ��������?
 if( is_signum(src[isrc]) )
  *int_signum = src[isrc++]=='+' ? 1 : -1;

 // ������� �� ����� ����� ��������.
 if( isdigit(src[isrc]) )
  {
   int_part[iint_part++]=src[isrc++];

   while(isdigit(src[isrc]))
    {
     if( int_len!=-1 && iint_part==int_len-1 )
      return false; // ������������ ��������� ���� int_part!

     int_part[iint_part++] = src[isrc++];
    }

   // ����� ����� ����� ���������� �� ��������� ������ ���. ������
   // ��� �������� ���������� (���� 'e').
   if(
      !is_exponent(src[isrc]) &&
      !is_dec_point(src[isrc]) &&
      src[isrc]
     )
    return false;

   int_part[iint_part]=0; // force integer part string to be zero-terminated
   trunc_zeros(int_part);
  }

 if( is_dec_point(src[isrc]) )
  {
   // ��������� ������� �����.
   isrc++;

   while( isdigit(src[isrc]) )
    {
     if( frac_len!=-1 && ifrac_part==frac_len-1 )
      {
       // ������������ ��������� ���� frac_part!
       // ������� ���������� ����.
       isrc++;
       continue;
      }
     else
      frac_part[ifrac_part++] = src[isrc++];
    }

   // ������� ����� ����� ���������� ������� �� ��������� ��������:
   //
   // 1. ����� �������� ������ - ���������� \0.
   // 2. ���������� ������ ���������� ( 'E', 'e', 'd', 'D' ).

   if( !is_exponent(src[isrc]) && src[isrc] )
    return false;

   frac_part[ifrac_part] = 0;
  }

 // �������� ���������������� �����.
 if( src[isrc] )
  {
   isrc++;

   if( is_signum(src[isrc]) )
    *exp_signum = src[isrc++]=='+' ? 1 : -1;

   if( isdigit(src[isrc]) || is_exponent(src[isrc]) )
    {
     exp_part[iexp_part++]=src[isrc++];

     while( isdigit(src[isrc]) )
      {
       if( exp_len!=-1 && iexp_part==exp_len-1 )
        return false;

       exp_part[iexp_part++] = src[isrc++];
      }
    }

   if( src[isrc] )
    return false;

   exp_part[iexp_part]=0;
   trunc_zeros(exp_part);
  }

 return true;
}


bool lem::split(
                const wchar_t *src,
                int *int_signum, wchar_t *int_part,  int int_len,
                                 wchar_t *frac_part, int frac_len,
                int *exp_signum, wchar_t *exp_part,  int exp_len
               )
{
 LEM_CHECKIT_Z( src!=NULL );

 *int_signum = *exp_signum = 1; // �� ��������� ��������� ���� '+'.

 // �������� ��������� ����� �����, � ��������� ����������
 // ������.

 int isrc=int_part[0]=frac_part[0]=exp_part[0]=0;
 int iint_part=0, ifrac_part=0, iexp_part=0;

 // ��������� ������� ����������.
 while( isspace(src[isrc]) ) isrc++;

 // ���� ��������?
 if( is_usignum(src[isrc]) )
  *int_signum = src[isrc++]=='+' ? 1 : -1;

 // ������� �� ����� ����� ��������.
 if( is_udigit(src[isrc]) )
  {
   int_part[iint_part++]=src[isrc++];

   while(is_udigit(src[isrc]))
    {
     if( int_len!=-1 && iint_part==int_len-1 )
      return false; // ������������ ��������� ���� int_part!

     int_part[iint_part++] = src[isrc++];
    }

   // ����� ����� ����� ���������� �� ��������� ������ ���. ������
   // ��� �������� ���������� (���� 'e').
   if(
      !is_uexponent(src[isrc]) &&
      !is_udec_point(src[isrc]) &&
      src[isrc]
     )
    return false;

   int_part[iint_part]=0; // force integer part string to be zero-terminated
   trunc_zeros(int_part);
  }

 if( is_udec_point(src[isrc]) )
  {
   // ��������� ������� �����.
   isrc++;

   while( is_udigit(src[isrc]) )
    {
     if( frac_len!=-1 && ifrac_part==frac_len-1 )
      {
       // ������������ ��������� ���� frac_part!
       // ������� ���������� ����.
       isrc++;
       continue;
      }
     else
      frac_part[ifrac_part++] = src[isrc++];
    }

   // ������� ����� ����� ���������� ������� �� ��������� ��������:
   //
   // 1. ����� �������� ������ - ���������� \0.
   // 2. ���������� ������ ���������� ( 'E', 'e', 'd', 'D' ).

   if( !is_uexponent(src[isrc]) && src[isrc] )
    return false;

   frac_part[ifrac_part] = 0;
  }

 // �������� ���������������� �����.
 if( src[isrc] )
  {
   isrc++;

   if( is_usignum(src[isrc]) )
    *exp_signum = src[isrc++]=='+' ? 1 : -1;

   if( is_udigit(src[isrc]) || is_uexponent(src[isrc]) )
    {
     exp_part[iexp_part++]=src[isrc++];

     while( is_udigit(src[isrc]) )
      {
       if( exp_len!=-1 && iexp_part==exp_len-1 )
        return false;

       exp_part[iexp_part++] = src[isrc++];
      }
    }

   if( src[isrc] )
    return false;

   exp_part[iexp_part]=0;
   trunc_zeros(exp_part);
  }

 return true;
}



/******************************************************
  ������������ ������� �����. ���� ���� ������� ������
  �� �����, �� ��������� ���� ����.
******************************************************/
void lem::trunc_zeros( char *field )
{
 if( field!=NULL )
  {
   int isrc=0;

   while( field[isrc] && field[isrc]=='0' ) isrc++;

   int i=0;
   while( (field[i++]=field[isrc++])!='\0' ) {}

   if( field[0]==0 )
    {
     field[0]='0';
     field[1]=0;
    }
  }

 return;
}


void lem::trunc_zeros( wchar_t *field )
{
 if( field!=NULL )
  {
   int isrc=0;

   while( field[isrc] && field[isrc]=='0' ) isrc++;

   int i=0;
   while( (field[i++]=field[isrc++])!='\0' );

   if( field[0]==0 )
    {
     field[0]='0';
     field[1]=0;
    }
  }

 return;
}



// ------------------------------------------------------------
//
// �������������� ����� ���� double18 � �������������� (� �������
// ���� ������) ��������� �������������.
//
// ------------------------------------------------------------

#if defined(SETREAL18) && !defined(LEM_NOREAL)

/*
char* qreal_to_str( const double18& val, char* buffer )
{
 // �������.
 char exponent[10];
 int_to_str( val.get_exponent(), exponent );

 // ��������.
 char mantissa[80];
 const integer128& mant = val.get_mantissa();
 oint_to_str( abs(mant), mantissa );

 char s=' ', es='+';

 if( val.get_exponent()<0 )
  es='-';

 if( mant<0 )
  s='-';

 sprintf( buffer, "%c.%se%c%s", s, mantissa, es, exponent );
}
*/
#endif



// ************************************************************************
// �������������� ������ �������� � 2-� �������� ����� �� ������. � ������
// ������ ������������ false, ��� ���������� �������������� true.
// ************************************************************************
bool lem::to_int( const char *str, lem::int16_t *res, lem::int16_t radix )
{
 LEM_CHECKIT_Z( radix>1 && radix<36 );
 LEM_CHECKIT_Z(res!=NULL);

 if( str==NULL )
  {
   *res = 0;
   return false;
  }

 lem::int16_t factor=1;
 lem::int16_t result=0;
 lem::int16_t numer;
 bool overflow=false;
 char ch;
 int i = CastSizeToInt(strlen(str))-1;

 while(i>=0)
  {
   ch=str[i--];

   if( strrchr(NUMERIQUES,ch)!=NULL )
    {
     // ������������ ������������.
     if( overflow )
      {
       // ���� ������������.
       return false;
      }

     // ������ �������� ������ {0,1,2,3,4,5,6,7,8,9}.
     for( numer=0; numer<10; numer++ )
      if( ch==NUMERIQUES[numer] )
       break;

     // ����� ������ ��������������� ���������� ������� ���������.
     if( numer>=radix )
      return false;

     result += static_cast<lem::int16_t>(factor*numer);
    }
   else
    {
     // ��� ������ ���� ���� '-'/'+'. ������ ���������
     // �� �����������������.
     if( ch!='-' && ch!='+' )
      return false;

     if( ch=='-' )
      result = static_cast<lem::int16_t>(-result);

     // ����� �� ������ ���� ��������!
     if( i!=-1 )
      return false;
    }

   if( 32767/radix < factor )
    overflow = true;
   else
    factor *= radix;
  }

 *res = result;
 return true;
}


bool lem::to_int( const char *str, lem::uint16_t *res, int radix )
{
 LEM_CHECKIT_Z( radix>1 && radix<36 );
 LEM_CHECKIT_Z(res!=NULL);

 if( str==NULL )
  {
   *res = 0;
   return false;
  }

 lem::uint32_t factor=1;
 lem::uint32_t result=0; // �������� ������� ��� �������� ������������
 lem::uint32_t numer;
 bool overflow=false;
 char ch;
 int i = CastSizeToInt(strlen(str))-1;

 while(i>=0)
  {
   ch=str[i--];

   if( strrchr(NUMERIQUES,ch)!=NULL )
    {
     // ������������ ������������.
     if( overflow )
      {
       // ���� ������������.
       return false;
      }

     // ������ �������� ������ {0,1,2,3,4,5,6,7,8,9}.
     for( numer=0; numer<10; numer++ )
      if( ch==NUMERIQUES[numer] )
       break;

     // ����� ������ ��������������� ���������� ������� ���������.
     if( int(numer)>=radix )
      return false;

     result += factor*numer;

     if( result > 0x0000ffffu )
      return false;
    }
   else
    {
     // ��� ������ ���� ���� '+'. ������ ��������� �� �����������������.
     if( ch!='+' )
      return false;

     // ����� �� ������ ���� ��������!
     if( i!=-1 )
      return false;

     continue;
    }

   factor *= radix;
  }

 *res = (lem::uint16_t)result;
 return true;
}

bool lem::to_int( const wchar_t *str, lem::uint16_t *res, int radix )
{
 LEM_CHECKIT_Z( radix>0 && radix<36 );
 LEM_CHECKIT_Z(res!=NULL);

 if( str==NULL )
  {
   *res = 0;
   return false;
  }

 lem::uint32_t factor=1;
 lem::uint32_t result=0; // �������� ������� ��� �������� ������������
 lem::uint32_t numer;
 bool overflow=false;
 char ch;
 int i = lem_strlen(str)-1;

 while(i>=0)
  {
   if( !lem::is_lat(str[i]) && !lem::is_udigit(str[i]) ) 
    return false;

   ch = static_cast<char>(str[i--]);

   if( strrchr(NUMERIQUES,ch)!=NULL )
    {
     // ������������ ������������.
     if( overflow )
      {
       // ���� ������������.
       return false;
      }

     // ������ �������� ������ {0,1,2,3,4,5,6,7,8,9}.
     for( numer=0; numer<10; numer++ )
      if( ch==NUMERIQUES[numer] )
       break;

     // ����� ������ ��������������� ���������� ������� ���������.
     if( numer>=(lem::uint32_t)radix )
      return false;

     result += factor*numer;

     if( result > 0x0000ffffu )
      return false;
    }
   else
    {
     // ��� ������ ���� ���� '+'. ������ ��������� �� �����������������.
     if( ch!='+' )
      return false;

     // ����� �� ������ ���� ��������!
     if( i!=-1 )
      return false;

     continue;
    }

   factor *= radix;
  }

 *res = (lem::uint16_t)result;
 return true;
}


bool lem::to_int( const char *str, lem::int32_t *res, int radix )
{
 LEM_CHECKIT_Z( radix>1 && radix<36 );
 LEM_CHECKIT_Z(res!=NULL);

 if( str==NULL )
  {
   *res = 0;
   return false;
  }

 lem::int32_t factor=1;
 lem::int32_t result=0;
 int numer;
 bool overflow=false;
 char ch;
 int i = CastSizeToInt(strlen(str))-1;

 while(i>=0)
  {
   ch=str[i--];

   if( strrchr(NUMERIQUES,ch)!=NULL )
    {
     // ������������ ������������.
     if( overflow )
      {
       // ���� ������������.
       return false;
      }

     // ������ �������� ������ {0,1,2,3,4,5,6,7,8,9}.
     for( numer=0; numer<10; numer++ )
      if( ch==NUMERIQUES[numer] )
       break;

     // ����� ������ ��������������� ���������� ������� ���������.
     if( numer>=radix )
      return false;

     result += factor*numer;
    }
   else
    {
     // ��� ������ ���� ���� '-'/'+'. ������ ���������
     // �� �����������������.
     if( ch!='-' && ch!='+' )
      return false;

     if( ch=='-' )
      result = -result;

     // ����� �� ������ ���� ��������!
     if( i!=-1 )
      return false;
    }

   if( 0x7fffffff/radix < factor )
    overflow = true;
   else
    factor *= radix;
  }

 *res = result;
 return true;
}


#if defined LEM_INT64
bool lem::to_int( const char *str, lem::int64_t *res, int radix )
{
 LEM_CHECKIT_Z( radix>1 && radix<36 );
 LEM_CHECKIT_Z(res!=NULL);

 if( str==NULL )
  {
   *res = 0;
   return false;
  }

 lem::int64_t factor=1;
 lem::int64_t result=0;
 int numer;
 bool overflow=false;
 char ch;
 int i = CastSizeToInt(strlen(str))-1;

 while(i>=0)
  {
   ch=str[i--];

   if( strrchr(NUMERIQUES,ch)!=NULL )
    {
     // ������������ ������������.
     if( overflow )
      {
       // ���� ������������.
       return false;
      }

     // ������ �������� ������ {0,1,2,3,4,5,6,7,8,9}.
     for( numer=0; numer<10; numer++ )
      if( ch==NUMERIQUES[numer] )
       break;

     // ����� ������ ��������������� ���������� ������� ���������.
     if( numer>=radix )
      return false;

     result += factor*numer;
    }
   else
    {
     // ��� ������ ���� ���� '-'/'+'. ������ ���������
     // �� �����������������.
     if( ch!='-' && ch!='+' )
      return false;

     if( ch=='-' )
      result = -result;

     // ����� �� ������ ���� ��������!
     if( i!=-1 )
      return false;
    }

   if( lemLL(0x7fffffffffffffff)/radix < factor )
    overflow = true;
   else
    factor *= radix;
  }

 *res = result;
 return true;
}
#endif


#if defined LEM_INT64
bool lem::to_int( const wchar_t *str, lem::int64_t *res, int radix )
{
 LEM_CHECKIT_Z(res!=NULL);
 LEM_CHECKIT_Z( radix>1 && radix<36 );

 if( str==NULL ) 
  {
   *res=0;
   return false;
  }

 lem::int64_t factor=1;
 lem::int64_t result=0;

 int numer;
 bool overflow=false;
 wchar_t ch;
 int i = lem_strlen(str)-1;

 while( i>=0 )
  {
   ch=to_uupper(str[i--]);

   if( is_unumerique(ch) )
    {
     // ������������ ������������.
     if( overflow )
      {
       // ���� ������������.
       return false;
      }

     // ������ �������� ������ {0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f}.
     numer = uchar_to_digit(ch);

     // ����� ������ ��������������� ���������� ������� ���������.
     if( numer>=radix )
      return false;

     result += factor*numer;
    }
   else
    {
     // ��� ������ ���� ���� '-'/'+'. ������ ���������
     // �� �����������������.
     if( !is_usignum(ch) )
      return false;

     if( ch=='-' )
      result = -result;

     // ����� �� ������ ���� ��������!
     if( i!=-1 )
      return false;
    }

   if( lemLL(0x7fffffffffffffff)/radix < factor )
    overflow = true;
   else
    factor *= radix;
  }

 *res = result;
 return true;
}
#endif


#if !defined(LEM_NOREAL)
bool lem::to_real( const char *str, double *res )
{
 LEM_CHECKIT_Z(res!=NULL);

 if( !str || !*str )
  {
   *res = 0;
   return true; 
  }

 int i=0;

 if( is_signum(*str) )
  i++;

 while( is_digit(str[i]) )
  i++;

 if( str[i]=='.' )
  {
   i++;

   if( i==1 )
    {
     if( !is_digit(str[i++]) )
      return false;
    }

   while( is_digit(str[i]) ) i++;
  }

 if( str[i] )
  {
   if( !is_exponent(str[i]) )
    return false;

   if( is_signum(str[++i]) ) i++;

   if( !is_digit(str[i]) )
    return false;

   i++;
   while( is_digit(str[i]) ) i++;

   if( str[i] )
    return false;
  }

 #if REAL_TYPE==4 || REAL_TYPE==8
  *res = atof(str);
 #elif REAL_TYPE==10
  #if !defined NOQFUN
   *res = _atold(str);
  #else
   *res = atof(str);
  #endif
 #else
  *res = atof(str);
 #endif

 return true;
}
#endif


bool lem::to_bool( const char *str , bool *res )
{
 LEM_CHECKIT_Z(res!=NULL);

 if(
    lem_eqi(str,"yes")  ||
    lem_eqi(str,"on")   ||
    lem_eqi(str,"y")    ||
    lem_eqi(str,"true") ||

    #if defined RUSSIAN

    lem_eqi(str,"���") ||
    lem_eqi(str,"��")  ||
    lem_eqi(str,"�")   ||

    #endif

    lem_eq(str,"1")
   )
 {
  *res = true;
  return true;
 }

 if(
    lem_eqi(str,"not")  ||
    lem_eqi(str,"no")   ||
    lem_eqi(str,"off")  ||
    lem_eqi(str,"n")    ||
    lem_eqi(str,"false")||

    #if defined RUSSIAN

    lem_eqi(str,"���")  ||
    lem_eqi(str,"����") ||
    lem_eqi(str,"�")    ||

    #endif

    lem_eq(str,"0")
   )
 {
  *res = false;
  return true;
 }

 return false;
}

bool lem::to_bool( const char *str )
{
 bool res=false;
 if( !to_bool( str, &res ) )
  throw ECheckFault( to_wstr("String can not be converted to bool: ")+to_wstr(str) );

 return res;
}

bool lem::to_bool( const wchar_t *str )
{
 bool res=false;
 if( !to_bool( str, &res ) )
  throw ECheckFault( to_wstr("String can not be converted to bool: ")+to_wstr(str) );

 return res;
}

bool lem::to_bool( const lem::FString &str )
{ return to_bool(str.c_str()); }

bool lem::to_bool( const lem::UFString &str )
{ return to_bool(str.c_str()); }

bool lem::to_bool( const lem::CString &str )
{ return to_bool(str.c_str()); }

bool lem::to_bool( const lem::UCString &str )
{ return to_bool(str.c_str()); }

bool lem::str_c_to_int( const char *str, lem::int16_t *res )
{
 LEM_CHECKIT_Z(res!=NULL);

 if( str==NULL )
  {
   *res = 0;
   return false;
  }

 bool correct=false,done=false;

 if( str[0]=='0' )
  {
   if( str[1]=='x' )
    {
     // hex-������ �����.
     str = str + 2;
     correct=to_int( str, res, 16 );
     done=true;
    }

   if( str[1]=='b' )
    {
     // binary-������ �����.
     str = str + 2;
     correct=to_int( str, res, 2 );
     done=true;
    }

   if( str[1]=='o' )
    {
     // octal-������ �����.
     str = str + 2;
     correct=to_int( str, res, 8 );
     done=true;
    }
  }

 if(!done)
  correct = to_int(str,res,10);

 return correct;
}

bool lem::str_c_to_int( const char *str, lem::int32_t *res )
{
 LEM_CHECKIT_Z(res!=NULL);

 if( str==NULL )
  {
   *res = 0;
   return false;
  }

 bool correct=false,done=false;

 if( str[0]=='0' )
  {
   if( str[1]=='x' )
    {
     // hex-������ �����.
     str = str + 2;
     correct=to_int( str, res, 16 );
     done=true;
    }

   if( str[1]=='b' )
    {
     // binary-������ �����.
     str = str + 2;
     correct=to_int( str, res, 2 );
     done=true;
    }

   if( str[1]=='o' )
    {
     // octal-������ �����.
     str = str + 2;
     correct=to_int( str, res, 8 );
     done=true;
    }
  }

 if(!done)
  correct = to_int(str,res,10);

 return correct;
}

// ********************************************************************
// �������������� ������ � int. � ������ ������������� ������� ������
// ������������ ����������.
// ********************************************************************
int lem::to_int( const char *s )
{
 int i=-1;
 if( !to_int( s, &i ) )
  throw ECheckFault( to_wstr("String can not be converted to int: ")+to_wstr(s) );

 return i;
}

int lem::to_int( const wchar_t *s )
{
 //return _wtoi(s);
 int i=-1;
 if( !to_int( s, &i ) )
  throw ECheckFault( to_wstr("String can not be converted to int: ")+to_wstr(s) );

 return i;
}


void lem::truncate_trailing_dot( char *s )
{
 if( s!=NULL )
  {
   const size_t l=strlen(s);
   if( l && s[ l-1 ]=='.' )
    s[l-1]='\0';
  }

 return;
}


/*************************************************************************
  ���������, �������� �� ���������� ������ ���������� ������
  ���������� �� ����������, ������� ��� ��������� ������ ����������������.
**************************************************************************/
bool lem::is_name( const char* s )
{
 if( s==NULL )
  return false;

 if( !is_alpha(s[0]) )
  return false;

 int i=1;
 while( s[i] )
  {
   if( !is_al_num(s[i]) && s[i]!='_' )
    return false;
   else
    i++;
  }

 return true;
}

// *****************************************************************
// ���������� true ������ � ��� ������, ���� ��� ������� - ��
// ���������, ����������� ��� ��������� �� ������� ������� 866.
// *****************************************************************
bool lem::are_cyr_only( const char *s )
{
 if( !s )
  return false;

 int i=0;
 while( s[i] )
  if( !is_russian(s[i]) )
   return false;
  else
   i++;

 return true;
}

bool lem::are_lat_only( const char *s )
{
 if( !s )
  return false;

 int i=0;
 while( s[i] )
  if( !is_latin(s[i]) )
   return false;
  else
   i++;

 return true;
}

bool lem::are_lat_only( const wchar_t *s )
{
 if( !s )
  return false;

 int i=0;
 while( s[i] )
  if( wcschr( _allowed_lexem_punctuators, s[i] )!=NULL )
   i++;
  else if( !is_lat(s[i]) )
   return false;
  else
   i++;

 return true;
}


bool lem::are_french_only( const wchar_t *s )
{
 if( !s )
  return false;

 int i=0;
 while( s[i] )
  if( wcschr( _allowed_lexem_punctuators, s[i] )!=NULL )
   i++;
  else if( !is_french(s[i]) )
   return false;
  else
   i++;

 return true;
}

bool lem::are_german_only( const wchar_t *s )
{
 if( !s )
  return false;

 int i=0;
 while( s[i] )
  if( wcschr( _allowed_lexem_punctuators, s[i] )!=NULL )
   i++;
  else if( !is_german(s[i]) )
   return false;
  else
   i++;

 return true;
}

bool lem::are_italian_only( const wchar_t *s )
{
 if( !s )
  return false;

 int i=0;
 while( s[i] )
  if( wcschr( _allowed_lexem_punctuators, s[i] )!=NULL )
   i++;
  else if( !is_italian(s[i]) )
   return false;
  else
   i++;

 return true;
}


bool lem::are_spanish_only( const wchar_t *s )
{
 if( !s )
  return false;

 int i=0;
 while( s[i] )
  if( wcschr( _allowed_lexem_punctuators, s[i] )!=NULL )
   i++;
  else if( !is_spanish(s[i]) )
   return false;
  else
   i++;

 return true;
}

bool lem::is_int( const char *s )
{
 if( !(s) || *s == 0 )
  return false;

 int i=0;
 while( s[i] )
  if( !is_digit(s[i++] ) )
   return false;

 return true;
}

bool lem::is_int( const lem::FString &s )
{
 return is_int(s.c_str());
}




bool lem::is_digits( const char *s )
{
 if( !(s) || *s == 0 )
  return false;

 return is_digit(*s);
}




// ***********************************************************

// *********************************************
// �������� - ����� (� ��������� MSDOS 866)
// *********************************************
bool lem::is_litera( char ch )
{ return isalpha(ch) || is_russian(ch); }

// ************************************************************
// �������� - ����� �������� �������� (� ��������� MSDOS 866)
// ************************************************************
bool lem::is_russian( char ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC[i] )
   return true;

 return false;
}

bool lem::is_latin( char ch )
{
 return (ch>='a' && ch<='z') ||
        (ch>='A' && ch<='Z');
}


// ***********************************************************
// ������������� ������� �� MSDOS (866) � MSWINDOWS (1251)
// ***********************************************************
char lem::dos_to_win( char ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC[i] )
   return rusABC_win[i];

 return ch;
}

// ***********************************************************
// ������������� ������� �� MSDOS (866) � UNICODE
// ***********************************************************
wchar_t lem::dos_to_uni( char ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC[i] )
   return rusABC_uni[i];

 return SOL_ACHAR_TO_INT(ch);
}

// ***********************************************************
// ������������� ������� �� MSDOS (866) � KOI-8
// ***********************************************************
char lem::dos_to_koi8( char ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC[i] )
   return rusABC_koi8[i];

 return ch;
}

char lem::win_to_koi8( char ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC_win[i] )
   return rusABC_koi8[i];

 return ch;
}

// ***********************************************************
// ������������� ������� �� KOI-8 � MSDOS (866)
// ***********************************************************
char lem::koi8_to_dos( char ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC_koi8[i] )
   return rusABC[i];

 return ch;
}

char lem::koi8_to_win( char ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC_koi8[i] )
   return rusABC_win[i];

 return ch;
}

// ***********************************************************
// ������������� ������� �� MSWINDOWS (1251) � MSDOS (866)
// ***********************************************************
char lem::win_to_dos( char ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC_win[i] )
   return rusABC[i];

 return ch;
}

// ***********************************************************
// ������������� ������� �� UNICODE � MSDOS (866)
// ***********************************************************
char lem::uni_to_dos( wchar_t ch )
{
 for( size_t i=0; i<sizeof(rusABC); i++ )
  if( ch==rusABC_uni[i] )
   return rusABC[i];

 return (char)ch;
}


void lem::dos_to_koi8( char *s )
{
 if( s )
  {
   int i=0;

   while( s[i] )
    {
     s[i] = dos_to_koi8( s[i] );
     i++;
    }
  }

 return;
}

void lem::koi8_to_dos( char *s )
{
 if( s )
  {
   int i=0;

   while( s[i] )
    {
     s[i] = koi8_to_dos(s[i]);
     i++;
    }
  }

 return;
}

void lem::win_to_koi8( char *s )
{
 if( s )
  {
   int i=0;

   while( s[i] )
    {
     s[i] =win_to_koi8( s[i] );
     i++;
    }
  }

 return;
}


void lem::koi8_to_win( char *s )
{
 if( s )
  {
   int i=0;

   while( s[i] )
    {
     s[i] = koi8_to_win(s[i]);
     i++;
    }
  }

 return;
}

// *****************************************************************
// ������������� ������ �������� �� MSDOS (866) � MSWindows (1251)
// *****************************************************************
void lem::dos_to_win( char *s )
{
 if( !!(s) )
  {
   int i=0;
   while( (s[i] = dos_to_win(s[i])) )
    i++;
  }

 return;
}



void lem::win_to_dos( char *s )
{
 if( !!(s) )
  {
   int i=0;

   while( (s[i] = win_to_dos(s[i])) )
    i++;
  }

 return;
}



// ***********************************************************
// �������������� ���� �������� � ������ �������.
// ***********************************************************
char* lem::to_lower( char *s )
{
 #if defined LEM_WINDOWS

  if( s!=NULL )
   CharLowerBuffA( s, (DWORD)strlen(s) );

 #else

 if( !!(s) )
  {
   int i=0;

   while( (s[i]=to_lower(s[i])) )
    i++;
  }

 #endif

 return s;
}


wchar_t* lem::to_lower( wchar_t *s )
{
 if( !!(s) )
  {
   int i=0;

   while( (s[i]=to_ulower(s[i])) )
    i++;
  }

 return s;
}


// ***********************************************************
// �������������� ���� �������� � ������� �������.
// ***********************************************************
char* lem::to_upper( char *s )
{
 #if defined LEM_WINDOWS

 if( s!=NULL )
  CharUpperBuffA( s, (DWORD)strlen(s) );

 #else

 if( s )
  {
   int i=0;
   while( (s[i]=to_upper(s[i])) )
    i++;
  }

 #endif

 return s;
}


wchar_t* lem::to_upper( wchar_t *s )
{
 if( !!(s) )
  {
   int i=0;
   while( (s[i]=to_uupper(s[i])) )
    i++;
  }

 return s;
}

char* lem::to_upper_w( char *s )
{
 if( !!(s) )
  {
   int i=0;
   while( (s[i]=to_upper_w(s[i])) )
    i++;
  }

 return s;
}


// ***********************************************************
// �������������� ������� � ������ �������.
// ***********************************************************
char lem::to_lower( char ch )
{
 if( ch>='A' && ch<='Z' )
  return char(ch+32);

 if( static_cast<unsigned int>(ch)<128 )
  return ch;

 for( int ir=0; ir<33; ir++ )
  #if defined LEM_WINDOWS
  if( rusABC_win[ir]==ch )
   return rusABC_win[ir+33];
  #else
  if( rusABC[ir]==ch )
   return rusABC[ir+33];
  #endif

 return ch;
}


// ***********************************************************
// �������������� ������� � ������� �������.
// ***********************************************************
char lem::to_upper( char ch )
{
 if( ch>='a' && ch<='z' )
  return char(ch-32);

 if( static_cast<unsigned int>(ch)<128 )
  return ch;

 for( int ir=33; ir<66; ir++ )
  #if defined LEM_WINDOWS
  if( rusABC_win[ir]==ch )
   return rusABC_win[ir-33];
  #else
  if( rusABC[ir]==ch )
   return rusABC[ir-33];
  #endif

 return ch;
}

char lem::to_upper_w( char ch )
{
 if( ch>='a' && ch<='z' )
  return char(ch-32);

 if( static_cast<unsigned int>(ch)<128 )
  return ch;

 for( int ir=33; ir<66; ir++ )
  if( rusABC_win[ir]==ch )
   return rusABC_win[ir-33];

 return ch;
}

char lem::to_lower_w( char ch )
{
 if( ch>='a' && ch<='z' )
  return char(ch-32);

 if( static_cast<unsigned int>(ch)<128 )
  return ch;

 for( int ir=0; ir<33; ir++ )
  if( rusABC_win[ir]==ch )
   return rusABC_win[ir+33];

 return ch;
}





bool lem::is_upper( char ch )
{
 for( int j=0; j<33; j++ )
  if( rusABC[j]==ch )
   return true;

 for( int i=33; i<66; i++ )
  if( rusABC[i]==ch )
   return false;

 return !!isupper(ch);
}

bool lem::is_lower( char ch )
{
 for( int j=0; j<33; j++ )
  if( rusABC[j]==ch )
   return false;

 for( int i=33; i<66; i++ )
  if( rusABC[i]==ch )
   return true;

 return !!islower(ch);
}

// ***********************************************************
// �������� - ������ �������� ��� ��������� (��������� MSDOS)
// ***********************************************************
bool lem::is_alpha( char ch )
{
 if( ch>32 && ch<=127 && isalpha(ch) )
  return true;
/*
 for( int i=0; i<66; i++ )
  if( rusABC[i]==ch )
   return true;
*/
 return false;
}

// ***********************************************************
// �������� - ������ �������� ��� ��������� (��������� MSDOS)
// ���� ������
// ***********************************************************
bool lem::is_al_num( char ch )
{
 if(isalnum(ch))
  return true;

 for( int i=0; i<66; i++ )
  if( rusABC[i]==ch )
   return true;

 return false;
}


// *****************************************************************
// ������������� �������� �� ����� ������� icp_src � ������ icp_dst.
// *****************************************************************
char lem::recode_char(
                      char ch,     // char to recode
                      int icp_src, // source CodeConverter index
                      int icp_dst  // target CodeConverter index
                     )
{
 if( icp_src==icp_dst || (ch&0x80)!=0x80 )
  return ch;

 // �������� ����� ������������� ����� - ��������� MSDOS 866. ���
 // ��������� ���������� ����������� �������, ���� � �������� �������������.
 char ch_0=ch;
 switch( icp_src )
 {
  case 847:  ch_0 = koi8_to_dos( ch ); break;
  case 1251: ch_0 = win_to_dos( ch ); break;
 }

 switch( icp_dst )
 {
  case 847:  ch_0 = dos_to_koi8(ch_0); break;
  case 1251: ch_0 = dos_to_win(ch_0); break;
 }

 return ch_0;
}

// ***********************************************************************
// ������� ������ �� ������� - ������� � ������� ���������. � ��������
// ������������ ��������������� �������� �������� �� <is_space>
// � <is_delim>
//
// ���� preserve_delimeters ��������� ��������� � ������ ���������� ������
// ��-���������� �����������.
// *************************************************************************
void lem::parse(
                const FString &str,
                MCollect<CString> &words,
                bool preserve_delimeters
               )
{
 int i=0, l=str.length();

 while( i<l )
  {
   // Skip the white space
   while( i<l && is_space(str[i]) )
    i++;

   lem::CString word;

   if( is_delim(str[i]) )
    {
     if( preserve_delimeters )
      {
       // ��������� ��-���������� ����������� � ������
       word = str[i];
       words.push_back(word);
      }

     i++;

     continue;
    }

   while( i<l && !is_delim(str[i]) && !is_space(str[i]) )
    word += str[i++];

   words.push_back(word);
  }

 return;
}


void lem::parse(
                const UFString &str,
                MCollect<UCString> &words,
                bool preserve_delimeters
               )
{
 int i=0, l=str.length();

 UCString word;

 while( i<l )
  {
   // Skip the white space
   while( i<l && is_uspace(str[i]) )
    i++;

   const wchar_t c=str[i];

   word.clear();

   // ������ ������ � �������� ������� � '...' � "..."
   if( c==L'\'' || c==L'"' )
    {
     const wchar_t opening=c;
     word = c;
    
     // ����� �� ������������ ������� 
     i++;
     while( i<l )
      {
       const wchar_t c2 = str[i++];
       word += c2;
       if( c2==opening )
        break;  
      }

     words.push_back(word);
     continue;
    }

   if( is_udelim(c) )
    {
     if( preserve_delimeters )
      {
       // ��������� ��-���������� ����������� � ������
       word = c;
       words.push_back(word);
      }

     i++;
     continue;
    }

   while( i<l && !is_udelim(str[i]) && !is_uspace(str[i]) )
    word += str[i++];

   if( !word.empty() )
    words.push_back(word);
  }

 return;
}

#if defined LEM_DOT_NET
std::wstring lem::to_wstr( System::String *src )
{
 wchar_t chars __gc [] = src->ToCharArray();
 std::wstring res;
 for( int i=0; i<src->get_Length(); i++ )
  res += chars[i];

 return res;
}


lem::UFString lem::to_ustr( System::String *src )
{
 wchar_t chars __gc [] = src->ToCharArray();
 UFString res;
 res.reserve( src->get_Length() );
 for( int i=0; i<src->get_Length(); i++ )
  res.Add_Dirty( chars[i] );

 res.calc_hash();

 return res;
}


std::string lem::to_cstr( System::String *src )
{
 wchar_t chars __gc [] = src->ToCharArray();
 std::string res;
 for( int i=0; i<src->get_Length(); i++ )
  {
   if( lem::uint16_t(chars[i])>255 )
    throw ECheckFault(
                      to_wstr( "Unicode character can not be converted "
                      " to ascii without code page" )
                     );
   res += (char)chars[i];
  }

 return res;
}


// �������������� �� System::String � lem::UFString
lem::UFString& lem::to_ustr( System::String* src, UFString &dst )
{
 wchar_t chars __gc [] = src->ToCharArray();

 dst.reserve( src->get_Length() );
 for( int i=0; i<src->get_Length(); i++ )
  dst.Add_Dirty( chars[i] );

 dst.calc_hash();
 return dst;
}


#endif



// *****************************************************************
// ���������� true ������ � ��� ������, ���� ��� ������� - ��
// ���������, ����������� ��� ��������� � UNICODE. ����� �����������
// ��������� ����������� (�������� ��� ������ ���� "�.�.").
// *****************************************************************
bool lem::are_cyr_only( const wchar_t *s )
{
 int i=0;
 while( s[i] )
  if( wcschr( _allowed_lexem_punctuators, s[i] )!=NULL )
   i++;
  else if( (s[i]<0x0410 && s[i]!=0x401) || s[i]>0x0451 )
   return false;
  else
   i++;

 return true;
}

// *****************************************************************
// ���������� true ������ � ��� ������, ���� ���� ���� ������
// �������� �������� ��������.
// *****************************************************************
bool lem::find_lat( const wchar_t *s )
{
 int i=0;
 while( !!(s[i]) )
  if(
     (s[i]>=L'a' && s[i]<=L'z' ) ||
     (s[i]>=L'A' && s[i]<=L'Z' )
    )
   return true;
  else
   i++;

 return false;
}




/*********************************************************************
 ���������� true, ���� �������� - ��������� �����. ������� false �����
 ��������, ��� ������ - �� �����, ���� ��� ����� � ������ ��������.
**********************************************************************/
bool lem::is_uupper( wchar_t ch )
{
 if( ch==0x0401 || (ch>=0x0410 && ch<=0x042f) )
  // ������ ��������� � ������� ��������
  return true;

 if( ch>=0x0430 && ch<=0x051f )
  // ������ ��������� � ������ ��������
  return false;
 
 #if defined LEM_ICU
 return !!u_isupper(ch);
 #elif defined LEM_WINDOWS
 return IsCharUpperW(ch)==TRUE;
 #else
 return iswupper(ch);
 #endif
}

bool lem::is_ulower( wchar_t ch )
{
 if( ch>=0x0400 && ch<=0x042f )
  // ������ ��������� � ������� ��������
  return false;

 if( ch>=0x0430 && ch<=0x051f )
  // ������ ��������� � ������ ��������
  return true;

 #if defined LEM_ICU
 return !!u_islower(ch);
 #elif defined LEM_WINDOWS
 return IsCharLowerW(ch)==TRUE;
 #else
 return iswlower(ch);
 #endif
}

/*********************************************************************
 �����?
**********************************************************************/
bool lem::is_ualpha( wchar_t ch )
{
 if( ch>=0x0400 && ch<=0x0451 )
  // ������ ���������
  return true;

 #if defined LEM_ICU
 return !!u_isalpha(ch);
 #elif defined LEM_WINDOWS
 return IsCharAlphaW(ch)==TRUE;
 #else
 return ch>32 && ch<=127 && isalpha(ch);
 #endif
}

/*********************************************************************
 ����� ��� �����?
**********************************************************************/
bool lem::is_ual_num( wchar_t ch )
{
 if( ch>=0x0400 && ch<=0x0451 )
  // ������ ���������
  return true;

 #if defined LEM_ICU
 return !!u_isalnum(ch);
 #elif defined LEM_WINDOWS
 return IsCharAlphaNumericW(ch)==TRUE;
 #else
 return lem::is_al_num( (char)ch );
 #endif
}

/****************************************************************
 ����������� ������ � ����� (��������, 'a' -> 15, '3' -> 3 ).
 ���� ��������, ���������� ������� ������� �������. � ���������
 ������ ������������, ��� ch - �� ������� ����� (128 �����)
 ����������� ASCII-�������.
*****************************************************************/
int lem::uchar_to_digit( wchar_t ch )
{
 if( ch>=L'0' && ch<=L'9' )
  return ch-L'0';

 if( ch>=L'A' && ch<=L'Z' )
  return ch-L'A'+10;

 if( ch>=L'a' && ch<=L'z' )
  return ch-L'a'+10;

 throw ECheckFault(
                   to_wstr("Can not convert chararacter to digit: ") +
                   to_wstr(ch)
                  );
}


int lem::char_to_digit( char ch )
{
 if( ch>='0' && ch<='9' )
  return ch-'0';

 if( ch>='A' && ch<='Z' )
  return ch-'A'+10;

 if( ch>='a' && ch<='z' )
  return ch-'a'+10;

 LEM_STOPIT;
 return 0;
}



/*********************************************************************
 ���������� ������ - ������������� ����������������� ����� numer.
**********************************************************************/
wchar_t lem::get_unumerique( int numer )
{
 return get_numerique( (char)numer );
}

/*********************************************************************
 ��� hexadecimal digit?
**********************************************************************/
bool lem::is_unumerique( wchar_t ch )
{
 return !(ch & 0xff00u) && is_numerique( tolower((char)ch) );
}

/****************************************************************************
 DESCRIPTION:
  ��������� ��� ���������� �����. � ��������� ANSI Cfront ������� itoa, ltoa,
  ultoa �� �������������, ������ ����� ������������ ����. ������ ���������
  ��������-����������.

 INPUT PARAMETERS:
  val - ��������, ������� ������������� � ���������� �����.
  radix - ��������� ������� ���������, � ������� ����� ������������ �����.

 OUTPUT PARAMETERS:
  buffer - ��������� �� ���������� ������-�����, ���� ���������
  ��������� ��������������.

 RETURNS:
  ������������ ������ ��������� buffer.

 REMARKS:
  Size of destination buffer pointed by <buffer> is strictly recommended
  to be enough for storing convertion result. If it is not, the program
  behaviour is unpredictable.
****************************************************************************/
wchar_t* lem::int16_to_str( lem::int16_t val, wchar_t *buffer, int radix )
{
 lem::int16_t Val=val;

 if( !Val )
  {
   buffer[0]=get_unumerique(0);
   buffer[1]=0;
   return buffer;
  }

 lem::int16_t maxradix=1;
 while( maxradix<32767 && 32767/maxradix >= radix )
  maxradix *= (lem::int16_t)radix;

 int ibpos=-1;
 int numer;
 bool positive=true;

 if(Val<0)
  {
   Val=-Val;
   positive=false;

   if(Val<0)
    Val=-(SHRT_MIN+1);
  }

 while( maxradix>0 )
  {
   numer = Val/maxradix;

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = get_unumerique(numer);

   Val      %= maxradix;
   maxradix /= (lem::int16_t)radix;
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 if( !positive )
  {
   memmove( buffer+1, buffer, sizeof(wchar_t)*(ibpos+1) );
   buffer[0]='-';
  }

 return buffer;
}

const UCString lem::int16_to_ustr( lem::int16_t val, int radix )
{
 wchar_t buffer[LEM_CSTRING_LEN1];
 int16_to_str( val, buffer, radix );
 return UCString(buffer);
}

wchar_t* lem::uint16_to_str( lem::uint16_t val, wchar_t *buffer, int radix )
{
 lem::uint16_t Val=val;

 if( Val==0 )
  {
   buffer[0]=get_unumerique(0);
   buffer[1]=0;
   return buffer;
  }

 lem::uint16_t maxradix=1;
 while(
       maxradix< uint16_max &&
       uint16_max/maxradix >= radix
      )
  maxradix *= static_cast<lem::uint16_t>(radix);

 int ibpos=-1;
 int numer;

 while( maxradix>0 )
  {
   numer = Val/maxradix;

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = get_unumerique((int)numer);

   Val      %= maxradix;
   maxradix /= static_cast<lem::uint16_t>(radix);
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 return buffer;
}

wchar_t* lem::int32_to_str( lem::int32_t val, wchar_t *buffer, int radix )
{
 lem::int32_t Val=val;

 if( Val==0 )
  {
   buffer[0]=get_unumerique(0);
   buffer[1]=0;
   return buffer;
  }

 lem::int32_t maxradix=1;
 while( maxradix<0x7fffffff && 0x7fffffff/maxradix >= radix )
  maxradix *= radix;

 int ibpos=-1;
 lem::int32_t numer;
 bool positive=true;
 if(Val<0)
  {
   Val=-Val;
   positive=false;
   if(Val<0)
    Val=-(INT_MIN+1);
  }

 while( maxradix>0 )
  {
   numer = Val/maxradix;

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = get_unumerique((int)numer);

   Val      %= maxradix;
   maxradix /= radix;
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 if(!positive)
  {
   memmove( buffer+1, buffer, sizeof(wchar_t)*(ibpos+1) );
   buffer[0] = L'-';
  }

 return buffer;
}

const UCString lem::int32_to_ustr( lem::int32_t val, int radix )
{
 wchar_t buffer[LEM_CSTRING_LEN1];
 int32_to_str( val, buffer, radix );
 return UCString(buffer);
}

wchar_t* lem::uint32_to_str( lem::uint32_t val, wchar_t *buffer, int radix )
{
 lem::uint32_t Val=val;
 if( Val==0 )
  {
   buffer[0]=get_unumerique(0);
   buffer[1]=0;
   return buffer;
  }

 #if !defined MAXUINT32
 const lem::uint32_t MAXUINT32 = uint32_max;
 #endif

 lem::uint32_t maxradix=1;
 while( maxradix<MAXUINT32 && MAXUINT32/maxradix >= (lem::uint32_t)radix )
  maxradix *= radix;

 int ibpos=-1;
 lem::uint32_t numer;

 while( maxradix>0 )
  {
   numer = Val/maxradix;

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = get_unumerique((int)numer);

   Val      %= maxradix;
   maxradix /= radix;
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 return buffer;
}


bool lem::to_int(
                 const wchar_t *str,
                 lem::int16_t *res,
                 lem::int16_t radix
                )
{
 lem::int16_t factor=1;
 lem::int16_t result=0;
 lem::int16_t numer;
 bool overflow=false;
 wchar_t ch;
 int i = lem_strlen(str)-1;

 while(i>=0)
  {
   ch=to_uupper(str[i--]);

   if( is_unumerique(ch) )
    {
     // ������������ ������������.
     if( overflow )
      {
       // ���� ������������.
       return false;
      }

     // ������ �������� ������ {0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f}.
     numer =uchar_to_digit(ch);

     // ����� ������ ��������������� ���������� ������� ���������.
     if( numer>=radix )
      return false;

     result += factor*numer;
    }
   else
    {
     // ��� ������ ���� ���� '-'/'+'. ������ ���������
     // �� �����������������.
     if( !is_usignum(ch) )
      return false;

     if( ch=='-' )
      result = -result;

     // ����� �� ������ ���� ��������!
     if( i!=-1 )
      return false;
    }

   if( 32767/radix < factor )
    overflow = true;
   else
    factor *= radix;
  }

 *res = result;
 return true;
}

bool lem::to_int(
                 const wchar_t *str,
                 lem::int32_t *res,
                 int radix
                )
{
 lem::int32_t factor=1;
 lem::int32_t result=0;
 int numer;
 bool overflow=false;
 wchar_t ch;
 int i = lem_strlen(str)-1;

 while( i>=0 )
  {
   ch=to_uupper(str[i--]);

   if( is_unumerique(ch) )
    {
     // ������������ ������������.
     if( overflow )
      {
       // ���� ������������.
       return false;
      }

     // ������ �������� ������ {0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f}.
     numer = uchar_to_digit(ch);

     // ����� ������ ��������������� ���������� ������� ���������.
     if( numer>=radix )
      return false;

     result += factor*numer;
    }
   else
    {
     // ��� ������ ���� ���� '-'/'+'. ������ ���������
     // �� �����������������.
     if( !is_usignum(ch) )
      return false;

     if( ch=='-' )
      result = -result;

     // ����� �� ������ ���� ��������!
     if( i!=-1 )
      return false;
    }

   if( 0x7fffffff/radix < factor )
    overflow = true;
   else
    factor *= radix;
  }

 *res = result;
 return true;
}

#if !defined(LEM_NOREAL)
// ***************************************************
// Convert string to double nuber. Returns success flag.
// ***************************************************
bool lem::to_real( const wchar_t *str, double *res )
{
 if( !str || !*str )
  {
   *res = 0;
   return false;
  }

 if(
    !is_udigit( *str ) &&
    *str!='.'              &&
    *str!='-'              &&
    *str!='+'
   )
  // Null string can not be a double number representation. double number have
  // one of the formats:
  //   123
  //   .31
  //   -2.4
  //   +4
  return false;

 int i=0;

 if( is_usignum(*str) && str[1] )
  i++;

 while( is_udigit(str[i]) )
  i++;

 if( str[i]=='.' )
  {
   i++;

   if( i==1 )
    {
     if( !is_udigit(str[i++]) )
      return false;
    }

   while( is_udigit(str[i]) ) i++;
  }

 if( str[i] )
  {
   if( !is_uexponent(str[i]) )
    return false;

   if( is_usignum(str[++i]) ) i++;

   if( !is_udigit(str[i]) )
    return false;

   i++;
   while( is_udigit(str[i]) ) i++;

   if( str[i] )
    return false;
  }

 char aBuf[64];
 lem_unicode_to_ascii(aBuf,str,NULL);

 #if  REAL_TYPE==4 ||  REAL_TYPE==8
  *res = atof(aBuf);
 #elif  REAL_TYPE==10
  #if !defined NOQFUN
   *res = _atold(aBuf);
  #else
   *res = atof(aBuf);
  #endif
 #else
  *res = atof(aBuf);
 #endif

 return true;
}
#endif

bool lem::is_value( const wchar_t *s ) { return is_udigit(*s); }

/*****************************************
 ����� �� ������ �������� ���� int-�����?
******************************************/
bool lem::is_int( const wchar_t *s )
{
 int ichar=0;
 wchar_t ch;
 while( (ch=s[ichar++]) )
  if( !is_udigit(ch) )
   return false;

 return true;
}


bool lem::is_int( const lem::UFString &s )
{
 return is_int(s.c_str());
}

/*******************************************************************
 ���������� true, ���� ������ s ����� ���� �������������
 � int-����, ������ �������������� ����� ������������
 ����������� lem_s_str_to_int(...).

 ��������! ��������� ������������ ������ � ASCII ���������! ������
 ������������� ������� 'x'!
*******************************************************************/
bool lem::is_c_int( const wchar_t *s )
{
 if( s[0]==get_unumerique(0) && s[1]==L'x' )
  return is_int(s+2);

 return is_int(s);
}


bool lem::is_real( const wchar_t *s )
{
 int ichar=0;
 wchar_t ch;
 while( (ch=s[ichar++]) )
  if(
     !is_udigit(ch) &&
     !is_udec_point(ch) &&
     !is_uexponent(ch) &&
     !is_usignum(ch)
    )
   return false;

 return true;
}

// *****************************************************
// ������ ���������� ������������� ��� ������� ��������
// ������/���� � UNICODE
// *****************************************************
const wchar_t SOL_BOOL_1[]  = L"yes";
const wchar_t SOL_BOOL_2[]  = L"on";
const wchar_t SOL_BOOL_3[]  = L"y";
const wchar_t SOL_BOOL_4[]  = L"true";
const wchar_t SOL_BOOL_5[]  = L"1";
const wchar_t SOL_BOOL_6[]  = L"no";
const wchar_t SOL_BOOL_7[]  = L"not";
const wchar_t SOL_BOOL_8[]  = L"off";
const wchar_t SOL_BOOL_9[]  = L"n";
const wchar_t SOL_BOOL_10[] = L"false";
const wchar_t SOL_BOOL_11[] = L"0";

// **************************************************************************
// �������������� ������ � ������ ��������, ������������ ����� ��������� res.
// � ������ ������ ������ true, ��� ������ ������ false.
// **************************************************************************
bool lem::to_bool( const wchar_t *str , bool *res )
{
 if(
    lem_eqi(str,SOL_BOOL_1) ||
    lem_eqi(str,SOL_BOOL_2) ||
    lem_eqi(str,SOL_BOOL_3) ||
    lem_eqi(str,SOL_BOOL_4) ||
    lem_eqi(str,SOL_BOOL_5)
   )
 {
  *res = true;
  return true;
 }

 if(
    lem_eqi(str,SOL_BOOL_6)  ||
    lem_eqi(str,SOL_BOOL_7)  ||
    lem_eqi(str,SOL_BOOL_8)  ||
    lem_eqi(str,SOL_BOOL_9)  ||
    lem_eqi(str,SOL_BOOL_10) ||
    lem_eqi(str,SOL_BOOL_11)
   )
 {
  *res = false;
  return true;
 }

 return false;
}


/****************************************************************************
 Expressing numerical constants in decimal (base 10) or hexadecimal (base 16)
 are the same as in C/C++. To express a numerical constant in binary (base 2)
 notation, the sequence of 1's and 0's are preceded by '0b', with no space in
 between. To express a numerical constant in octal (base 8) notation, the
 sequence of octal digits (0 to 7) are preceded by '0o' with no spaces.

  1234  - decimal
  0x5f  - hexadecimal
  0o177 - octal
  0b010 - binary

 ��������! ��������� ������������, ��� ������� 'x', 'b', 'o' ������������ �
 ASCII ���������!
****************************************************************************/
bool lem::str_c_to_int( const wchar_t *str, lem::int16_t *res )
{
 bool correct=false,done=false;

 if( str[0]==get_unumerique(0) )
  {
   if( str[1]==L'x' )
    {
     // hex-������ �����.
     str += 2;
     correct=to_int( str, res, 16 );
     done=true;
    }

   if( str[1]==L'b' )
    {
     // binary-������ �����.
     str += 2;
     correct=to_int( str, res, 2 );
     done=true;
    }

   if( str[1]==L'o' )
    {
     // octal-������ �����.
     str += 2;
     correct=to_int( str, res, 8 );
     done=true;
    }
  }

 if(!done)
  // ������������, ��� ��� ����� ���������������� ������ - ����������
  correct = to_int(str,res,10);

 return correct;
}


bool lem::str_c_to_int( const wchar_t *str, lem::int32_t *res )
{
 bool correct=false,done=false;

 if( str[0]==get_unumerique(0) )
  {
   if( str[1]==L'x' )
    {
     // hex-������ �����.
     str += 2;
     correct=to_int( str, res, 16 );
     done=true;
    }

   if( str[1]==L'b' )
    {
     // binary-������ �����.
     str += 2;
     correct=to_int( str, res, 2 );
     done=true;
    }

   if( str[1]==L'o' )
    {
     // octal-������ �����.
     str += 2;
     correct=to_int( str, res, 8 );
     done=true;
    }
  }

 if(!done)
  correct = to_int(str,res,10);

 return correct;
}

/*********************************************************************
  ���������, �������� �� ���������� ������ ���������� ������
  ����������, �������, � ��� �����, �� ����������, ������� ��
  ����� ���������������� C/C++.

  Solaris System identifiers must start with either an underscore (_)
  or an upper or lower case letter. They then can be followed by any
  combination of underscores, upper or lower case lettres or numerical
  digits (0 to 9). The only extention relates to the national language
  alphabet letters: in spite of C/C++ restrictions that only latin
  alphabet letters are allowed, the national ABC letters can be freely
  used and mixed with other valid characters.
**********************************************************************/
bool lem::is_name( const wchar_t* name )
{
 int ichar=0;
 wchar_t ch;

 while( (ch=name[ichar++]) )
  {
   // ������ ��������, ��������� ��� ������� ������������� ��������
   // ����� ����������� � ����� ������� � ����������� �����.
   // ������ ������������� '_' ����� ���� � ����� �������.
   // �������� ����� �� ����� ���� ������ - ��� ������������ �����������.
   if( is_ualpha(ch) || ch==L'_' || (ichar>1 && is_udigit(ch)) )
    continue;
   else
    return false;
  }

 // ��� �� ����� ���� ������ �������.
 return ichar!=1;
}

/*************************************************************************
  ��������� ��� ������������ ���������� ����������� �����
  ���� lem::uint64_t. ������������ ������� ������� ��� ����������
  ����� � ������ ���������� ������ OFormatter.


  ������� ���������:

   v      -  �������� ���� lem::uint64_t.

   buffer - ��������� �� ������� ������, � ������� ����� �����������
            ��������� ������ ����� (C-������). ������� �������, �����
            ������ ������ ��� ���������� ��� ���������� ������ �
            ������������� �����, ������������ ����� ��������� ��
            ���������� lem::uint64_t_MAX � ������� ��������� � ����������
            2 - 81 ����.

   radix  - ��������� ������� ���������, � ������� ����� �����������
            �����. ���� �������� ����� ���������� � ��������� [2,36].


  ������������ ��������: ������������ ��������� �� buffer.


  ����������: ANSI Cfront 2.0-�����������.


  ������� ���������: ���������� ������ ANSI-����������� ���������.

  ���������:
            1. ��� ����������� �������� ��������� radix ����������
               ��������� � ������ LEM_DEBUGGING �����������. � �����������
               ������ ���������� buffer ����� ������� ������� �����.

***********************************************************************/

#if defined LEM_UI64
wchar_t* lem::to_ustr( lem::uint64_t val, wchar_t *buffer, int radix )
{
 LEM_CHECKIT_Z(buffer!=NULL);
 LEM_CHECKIT_Z(radix>1 && radix<36);
 
 #if defined LEM_WINDOWS
 return ::_ui64tow( val, buffer, radix );
 #else
 if( val==0 )
  {
   // ���� ����� ������ ����������.
   buffer[0]=get_unumerique(0);
   buffer[1]=0;
   return buffer;
  }

 lem::uint64_t tval=val;
 lem::uint64_t maxradix=1;
 lem::uint64_t foresee=maxradix*lem::uint64_t(radix);
 while( foresee > maxradix )
  {
   maxradix = foresee;
   foresee *= radix;
  }

 int ibpos=-1;
 int numer;

 while( maxradix>0 )
  {
   lem::uint64_t rd = tval/maxradix;
   numer = (int)(rd);

   if( ibpos==-1 && numer!=0 )
    ibpos=0;

   if( ibpos>=0 )
    buffer[ibpos++] = get_unumerique(numer);

   tval     %= maxradix;
   maxradix /= radix;
  }

 if(ibpos>=0)
  buffer[ibpos]=0;

 return buffer;
 #endif
}

const UCString lem::to_ustr( lem::uint64_t val, int radix )
{
 wchar_t buffer[UCString::max_len+1];
 lem::to_ustr( val, buffer, radix );
 return UCString(buffer);
}
#endif

#if defined LEM_I64
//#include <lem_i64.h>
wchar_t* lem::to_ustr( lem::int64_t val, wchar_t *buffer, int radix )
{
 LEM_CHECKIT_Z(buffer!=NULL);
 LEM_CHECKIT_Z(radix>1 && radix<36);
 #if defined LEM_WINDOWS
 return ::_i64tow( val, buffer, radix );
 #else
 if( radix==10 )
  {
   swprintf( buffer, 65, L"%lld", val );
   return buffer; 
  }
 else
  {
   LEM_STOPIT;
  }   
 #endif
}

const UCString lem::to_ustr( lem::int64_t val, int radix )
{
 wchar_t buffer[UCString::max_len+1];
 to_ustr(val,buffer,radix);
 return UCString(buffer);
}
#endif



/*****************************************************************
 *
 *        ROMAN.C  -  Converts integers to Roman numerals
 *
 *             Written by:  Jim Walsh
 *
 *             Compiler  :  Microsoft QuickC v2.5
 *
 *        This Program Is Released To The Public Domain
 *
 *****************************************************************/
//
// Modified by Koziev Elijah 25.09.2001
//
const std::string lem::to_roman( int i )
{
 std::string res;

 if( i>0 )
  {
   int value=i;

   while( value >= 1000 )
    {
     res += "M";
     value -= 1000;
    }

   if( value >= 900 )
    {
     res += "CM";
     value -= 900;
    }

   while( value >= 500 )
    {
     res += "D";
     value -= 500;
    }

   if( value >= 400 )
    {
     res += "CD";
     value -= 400;
    }

   while( value >= 100 )
    {
     res += "C";
     value -= 100;
    }

   if( value >= 90 )
    {
     res += "XC";
     value -= 90;
    }

   while( value >= 50 )
    {
     res += "L";
     value -= 50;
    }

   if( value >= 40 )
    {
     res += "XL";
     value -= 40;
    }

   while( value >= 10 )
    {
     res += "X";
     value -= 10;
    }

   if( value >= 9 )
    {
     res += "IX";
     value -= 9;
    }

   while( value >= 5 )
    {
     res += "V";
     value -= 5;
    }

   if( value >= 4 )
    {
     res += "IV";
     value -= 4;
    }

   while( value > 0 )
    {
     res += "I";
     value--;
    }
  }

 return res;
}


// *********************************************************************
// ��������������� ��������� �������������� ����� � �����: ����������
// ��������� ������������� ����� ��������� 1-999 ��� ������������� �
// ���������������� �������� ���� (������) ��� �������� (�������).
// *********************************************************************
static wstring to_text_ru_1000( int val, char Gender )
{
 LEM_CHECKIT_Z( val>=0 && val<1000 );

 const int n100 = val/100;
 val %= 100;
 const int n10 = val/10;
 val %= 10;
 const int n1 = val;

 string res;

 switch(n100)
 {
  case 0:                    break;
  case 1: res +="���";       break;
  case 2: res +="������";    break;
  case 3: res +="������";    break;
  case 4: res +="���������"; break;
  case 5: res +="�������";   break;
  case 6: res +="��������";  break;
  case 7: res +="�������";   break;
  case 8: res +="���������"; break;
  case 9: res +="���������"; break;
 }

 if( n10 && !res.empty() ) res += " ";

 bool n1_used=false;
 switch(n10)
 {
  case 0: break;
  case 1:
   {
    switch(n1)
    {
     case 0: res +="������";       break;
     case 1: res +="�����������";  break;
     case 2: res +="����������";   break;
     case 3: res +="����������";   break;
     case 4: res +="������������"; break;
     case 5: res +="����������";   break;
     case 6: res +="�����������";  break;
     case 7: res +="����������";   break;
     case 8: res +="������������"; break;
     case 9: res +="������������"; break;
    }

    n1_used = true;
    break;
   }

  case 2: res +="��������";    break;
  case 3: res +="��������";    break;
  case 4: res +="�����";       break;
  case 5: res +="���������";   break;
  case 6: res +="����������";  break;
  case 7: res +="���������";   break;
  case 8: res +="�����������"; break;
  case 9: res +="���������";   break;
 }

 if( !n1_used )
  {
   if( n1 && !res.empty() ) res += " ";

   switch(n1)
   {
    case 0: break;
    case 1: res += Gender=='f' ? "����" : "����";   break;
    case 2: res += Gender=='f' ? "���" : "���";     break;
    case 3: res+="���";    break;
    case 4: res+="������"; break;
    case 5: res+="����";   break;
    case 6: res+="�����";  break;
    case 7: res+="����";   break;
    case 8: res+="������"; break;
    case 9: res+="������"; break;
   }
  }

 return to_unicode( res, cp1251 );
}

#if defined(LEM_OFMT_MICROSOL) 
const wstring lem::to_text( int val, int lang, bool masculine )
{
 const int n1e9 = val/1000000000;
 val %= 1000000000;
 const int n1e6 = val/1000000;
 val %= 1000000;
 const int n1000 = val/1000;
 val %= 1000;
/*
 const int n100 = val/100;
 val %= 100;
 const int n10 = val/10;
 val %= 10;
*/
 const int n1 = val;

 wstring res;

 if( lang==LEM_RUS )
  {
   if( !val )
    {
     return L"����"; 
    }

   if( n1e9 )
    {
     res += to_text_ru_1000( n1e9, 'm' );
     res += to_wstr(" ");
     res += ms_rus.Correlate( to_unicode( CString("��������"),cp1251), n1e9 ).c_str();
     res += to_wstr(" ");
    }

   if( n1e6 )
    {
     res += to_text_ru_1000( n1e6, 'm' );
     res += to_wstr(" ");
     res += ms_rus.Correlate( to_unicode( CString("�������"),cp1251), n1e6 ).c_str();
     res += to_wstr(" ");
    }

   if( n1000 )
    {
     res += to_text_ru_1000( n1000, 'f' );
     res += to_wstr(" ");
     res += ms_rus.Correlate( to_unicode( CString("������"),cp1251), n1000 ).c_str();
     res += to_wstr(" ");
    }

   res += to_text_ru_1000( n1, masculine ? 'm' : 'f' );
  }
 else
  LEM_STOPIT;

 return res;
}
#endif // !LEM_OFMT_NO_MICROSOL

#if !defined LEM_NOREAL
double lem::share_to_real( const char *str )
{
 if( lem_eq( str, "1" ) )
  return 1.;

 if( lem_eq( str, "1/2" ) )
  return .5;

 if( lem_eq( str, "1/3" ) )
  return 1./3.;

 if( lem_eq( str, "2/3" ) )
  return 2./3.;

 // �������� ��������� ����� �����
 const int ii = lem_find( str, "/"  ); // ��� ������ �����
 const lem::CString up = left( CString(str), ii ); // ���������
 const lem::CString bottom = right( CString(str), lem_strlen(str)-ii-1 ); // �����������

 double r1 = to_real( up.c_str() );
 double r2 = to_real( bottom.c_str() );

 if( r2==0.0 )
  LEM_STOPIT;

 return r1/r2;
}
#endif

#if !defined LEM_NOREAL
double lem::to_real( const char *str )
{
 double res;
 if( !to_real( str, &res ) )
  throw ECheckFault( to_wstr("String can not be converted to double: ")+to_wstr(str) );

 return res;
}
#endif

#if !defined LEM_NOREAL
double lem::to_real( const wchar_t *str )
{
 double res;
 if( !to_real( str, &res ) )
  throw ECheckFault( to_wstr("String can not be converted to double: ")+to_wstr(str) );

 return res;
}
#endif


// **************************************************************************
// ���� �������� - ������������� �����, �� ������ ��������� �������������
// ����� �����, ���� �� �������� ����� ���� - ������ ������ "null"
//
// LC: 15.01.2003 �������������� ��� ��� TC 3.1, ������ ? ... : ������������
// ����������� if ....
// **************************************************************************
const lem::CString lem::i2ns( int ival )
{
 if( ival>0 )
  return to_str(ival);

 return lem::CString("null");
}


// ****************************************************************
// ��������� ������ � �������� ���������� ����
//   1, 2, 3-8, 9
//
// � ������ ��� �����.
//
// ������������ ����� ��������� ������.
// ****************************************************************
int lem::parse_ranges(
                      const char *s,
                      lem::MCollect< std::pair<int,int> > &range
                     )
{
 int i=0;
 while( (s[i]) )
  {
   lem::CString a, b;

   while( (s[i]) && s[i]!=',' && s[i]!='-' && s[i]!=';' )
    a += s[i++];

   if( (s[i]) && (s[i]==',' || s[i]=='-' || s[i]!=';') )
    {
     // ��������, ���� ���� a-b
     i++;

     while( (s[i]) && s[i]!=',' && s[i]!='-' && s[i]!=';' )
      b += s[i++];
    }

   if( (s[i]) )
    i++;

   if( !b.length() )
    b = a; // ������ ����� ���� �� ������� - ������ ��������������� �� �� �����

   const int ia = to_int(a.c_str());
   const int ib = to_int(b.c_str());

   range.push_back( make_pair(ia,ib) );
  }

 return CastSizeToInt(range.size());
}

// *****************************************************************
// �������������� ��������� - ������� ����� �������� �� ��������
// ���������.
// *****************************************************************
const std::string lem::translit_ru( const wchar_t *src )
{
 std::string res;

 if( src )
  while( *src )
   {
    if( is_cyr(*src) )
     switch( cp1251->to_ascii( *src ) )
     {
      case '�': res += "A";    break;
      case '�': res += "B";    break;
      case '�': res += "V";    break;
      case '�': res += "G";    break;
      case '�': res += "D";    break;
      case '�': res += "E";    break;
      case '�': res += "E";    break;
      case '�': res += "J";    break;
      case '�': res += "Z";    break;
      case '�': res += "I";    break;
      case '�': res += "J";    break;
      case '�': res += "K";    break;
      case '�': res += "L";    break;
      case '�': res += "M";    break;
      case '�': res += "N";    break;
      case '�': res += "O";    break;
      case '�': res += "P";    break;
      case '�': res += "R";    break;
      case '�': res += "S";    break;
      case '�': res += "T";    break;
      case '�': res += "OU";   break;
      case '�': res += "F";    break;
      case '�': res += "H";    break;
      case '�': res += "TZ";   break;
      case '�': res += "CH";   break;
      case '�': res += "SCH";  break;
      case '�': res += "SHCH"; break;
      case '�': res += "";     break;
      case '�': res += "Y";    break;
      case '�': res += "";     break;
      case '�': res += "E";    break;
      case '�': res += "JU";   break;
      case '�': res += "JA";   break;

      case '�': res += "a";    break;
      case '�': res += "b";    break;
      case '�': res += "v";    break;
      case '�': res += "g";    break;
      case '�': res += "d";    break;
      case '�': res += "e";    break;
      case '�': res += "e";    break;
      case '�': res += "j";    break;
      case '�': res += "z";    break;
      case '�': res += "i";    break;
      case '�': res += "j";    break;
      case '�': res += "k";    break;
      case '�': res += "l";    break;
      case '�': res += "m";    break;
      case '�': res += "n";    break;
      case '�': res += "o";    break;
      case '�': res += "p";    break;
      case '�': res += "r";    break;
      case '�': res += "s";    break;
      case '�': res += "t";    break;
      case '�': res += "ou";   break;
      case '�': res += "f";    break;
      case '�': res += "h";    break;
      case '�': res += "tz";   break;
      case '�': res += "ch";   break;
      case '�': res += "sch";  break;
      case '�': res += "shch"; break;
      case '�': res += "";     break;
      case '�': res += "y";    break;
      case '�': res += "";     break;
      case '�': res += "e";    break;
      case '�': res += "ju";   break;
      case '�': res += "ja";   break;
     }
    else
     // ������ ������� ��������� �����������
     res += static_cast<char>(*src);
    src++;
   }

 return res;
}


const lem::CString lem::to_str( double val, const char *Format )
{
 char buf[32]="";
 sprintf( buf, Format, val );
 return CString(buf);
}


// **********************************************************************
// ������ true, ���� ������ �������� ��� ���������, ��� � ������� �����.
// **********************************************************************
bool lem::are_mixed_languages( const wchar_t *str )
{
 bool has_lat=false;
 bool has_cyr=false;

 while( *str )
  {
   if( is_lat(*str) )
    has_lat=true;
   else if( is_cyr(*str) )
    has_cyr=true;

   str++;
  }

 return has_lat && has_cyr;
}

const lem::UCString lem::to_ustr( double x, const char *fmt )
{
 char res[32];
 *res=0;
 sprintf( res, fmt, x );
 return UCString(res);
}

const std::string lem::to_cstr( double x, const char *fmt )
{
 char buf[64]="";
 sprintf( buf, fmt, x );
 return string(buf);
}

const std::wstring lem::to_wstr( double x, const char *fmt )
{
 char buf[64]="";
 sprintf( buf, fmt, x );
 wstring res;
 int i=0;
 while( buf[i] )
  res += buf[i++];

 return res;
}


bool lem::is_lat_diaktr( wchar_t ch )
{
 if( is_lat(ch) ||
     (ch>=0x00C0 && ch<=0x00D6) ||
     (ch>=0x00D8 && ch<=0x00F6) ||
     (ch>=0x00F8 && ch<=0x0137) ||
     (ch>=0x0139 && ch<=0x0148) ||
     (ch>=0x014C && ch<=0x0184)
   )
  return true;

 return false;
}


void lem::recode_string( FString &str, int icp_src, int icp_dst )
{
 for( int i=0; i<str.size(); i++ )
  str.set( i, lem::recode_char( str[i], icp_src, icp_dst ) );
}


// ****************************************************************
// ���������� ������ ������, ������ � �������������������� � K � M
// ****************************************************************
std::wstring lem::filesize_to_wstr( lem::uint64_t Size )
{
 #if _MSC_VER<1300
 // conversion from unsigned __int64 to double not implemented
 float sz = static_cast<float>( (lem::int64_t)Size ); 
 #else
 float sz = static_cast<float>(Size); 
 #endif

 wchar_t s[32];
 const int n=sizeof(s)-1;

 const bool ru = lem::UI::get_UI().IsRussian();
 const bool fr = lem::UI::get_UI().IsFrench();

 const wchar_t *GB    = ru ? L"\x413\x431" : (fr ? L"Go" : L"Gb");
 const wchar_t *MB    = ru ? L"\x41C\x431" : (fr ? L"Mo" : L"Mb");
 const wchar_t *KB    = ru ? L"\x41A\x431" : (fr ? L"Ko" : L"Kb");
 const wchar_t *BYTES = ru ? L"\x431\x430\x439\x442" : L"bytes";

 #if _MSC_VER<1300 
 #else
 if( sz > lemLL(999999999) )
  {
   // ���������
   sz /= ( lemLL(1024)*lemLL(1024)*lemLL(1024) );

   #if defined LEM_BORLAND || defined LEM_MSVC65 || defined __MINGW32__
   if( sz>9 )
    swprintf( s, L"%3.1f %s", sz, GB );
   else
    swprintf( s, L"%3.2f %s", sz, GB );
   #else
   if( sz>9 )
    swprintf( s, n, L"%3.1f %s", sz, GB );
   else
    swprintf( s, n, L"%3.2f %s", sz, GB );
   #endif
  }  
 else
 #endif	  
  if( sz > 999999 )
  {
   // ���������
   sz /= (1024*1024);

   #if defined LEM_BORLAND || defined LEM_MSVC65 || defined __MINGW32__
   if( sz>9 )
    swprintf( s, L"%3.1f %s", sz, MB );
   else
    swprintf( s, L"%3.2f %s", sz, MB );
   #else
   if( sz>9 )
    swprintf( s, n, L"%3.1f %s", sz, MB );
   else
    swprintf( s, n, L"%3.2f %s", sz, MB );
   #endif
  } 
 else if( sz > 9999 )
  {
   // ���������
   sz /= 1024;

   #if defined LEM_BORLAND || defined LEM_MSVC65 || defined __MINGW32__
   if( sz>9 )
    swprintf( s, L"%3.0f %s", sz, KB );
   else
    swprintf( s, L"%3.1f %s", sz, KB );
   #else
   if( sz>9 )
    swprintf( s, n, L"%3.0f %s", sz, KB );
   else
    swprintf( s, n, L"%3.1f %s", sz, KB );
   #endif
  } 
 else
  {
   // �����
   #if defined LEM_BORLAND || defined LEM_MSVC65 || defined __MINGW32__
   swprintf( s, L"%4.0f %s", sz, BYTES );
   #else
   swprintf( s, n, L"%4.0f %s", sz, BYTES );
   #endif
  }

 return std::wstring(s);
}


// *****************************************************************
// ������ ���� ������ ��� ������ ��������� (����������� �����������
// � delimiters, �� ��������� ';') � str ����������� �� ���������
// �����.
// *****************************************************************
void lem::parse(
                const UFString &str,
                Collect<UFString> &list,
                const wchar_t *delimeters,
                bool unique
               )
{
 int i=0;
 const int l = str.length();

 while( i<l )
  {
   UFString item;
   item.reserve(32);

   while( i<l )
    {
     // �����������?
     if( wcsrchr( delimeters, str[i] )!=NULL || !str[i] )
      break;

     item += str[i];
     i++;
    }

   if( !item.empty() )
    {
     if( !unique || std::find( list.begin(), list.end(), item )==list.end() )
      list.push_back(item);
    }

   if( !str[i] )
    break;

   i++;
  }


 return;
}



// ********************************************
// ���������� ������, �������������� � UTF8
// ********************************************
FString lem::to_utf8( const wchar_t *ustr )
{
 const int srclen = lem_strlen(ustr);
 if( !srclen ) 
  return FString();

 #if defined LEM_WINDOWS
  const int utf8len = srclen*6;
  char *utf8 = new char[ utf8len+1 ];

  int res = WideCharToMultiByte( CP_UTF8, 0, ustr, srclen, utf8, utf8len, NULL, NULL );
  if( res>0 )
   {
    utf8[res] = 0;
    FString res(utf8);
    delete[] utf8;
    return res;
   }
  else
   {
    delete[] utf8;
    return FString();
   }
 #else
  FString res;
  res.reserve( srclen*6 );
  uint8_t utf8[8];

  for( int i=0; i<srclen; i++ )
   {
    lem::UCS4_to_UTF8( ustr[i], utf8 );
 
    int n = utf8[0];
    for( int j=0; j<n; j++ )
     res += utf8[j+1];
   }

  return res; 

 #endif
}





#if defined LEM_VCL
//lem::UFString lem::to_ustr( AnsiString& src )
//{
// return UFString( WideString(src) );
//}

//lem::UFString lem::to_ustr( WideString& src )
//{
// return UFString( src.c_str() );
//}
#endif


#if defined LEM_WINDOWS
lem::UFString lem::to_ustr( const BSTR *bstr )
{
 return UFString( (const wchar_t*)(bstr) );
}
#endif


#if defined LEM_WXWIDGETS
lem::UFString lem::to_ustr( const wxString &s )
{
 return UFString( s.wc_str() );
}
#endif


#if defined LEM_QT
lem::UFString lem::to_ustr( const QString &s )
{
 return UFString( s );
}
#endif


int lem::to_int( const lem::UFString &s )
{ return lem::to_int(s.c_str()); }

int lem::to_int( const lem::FString &s )
{ return lem::to_int(s.c_str()); }

int lem::to_int( const lem::UCString &s )
{ return lem::to_int(s.c_str()); }

int lem::to_int( const lem::CString &s )
{ return lem::to_int(s.c_str()); }

int lem::to_int( const std::string &s )
{ return lem::to_int(s.c_str()); }

int lem::to_int( const std::wstring &s )
{ return lem::to_int(s.c_str()); }

#if defined LEM_QT
int lem::to_int( const QString &s )
{
 return s.toInt();
}
#endif


#if defined LEM_WXWIDGETS
int lem::to_int( const wxString &s )
{
 long v=0;
 s.ToLong( &v );
 return v;
}
#endif


#if defined LEM_DOT_NET
int lem::to_int( System::String* s )
{ 
 #if defined LEM_32
 return System::Convert::ToInt32(s);
 #elif defined LEM_64
 return System::Convert::ToInt64(s);
 #endif
}
#endif


#if defined LEM_MFC
int lem::to_int( const CStringA &s )
{ return lem::to_int((const char*)s); }

int lem::to_int( const CStringW &s )
{ return lem::to_int((const wchar_t*)s); }
#endif




#if !defined LEM_NOREAL
double lem::to_real( const lem::UFString& str )
{ return lem::to_real(str.c_str()); }

double lem::to_real( const lem::FString& str )
{ return lem::to_real(str.c_str()); }

double lem::to_real( const std::wstring& str )
{ return lem::to_real(str.c_str()); }

double lem::to_real( const std::string& str )
{ return lem::to_real(str.c_str()); }


#if defined LEM_WXWIDGETS
double to_real( const wxString& str )
{
 double v=0;
 str.ToDouble(&v);
 return v;
}
#endif

#if defined LEM_QT
double lem::to_real( const QString &s )
{ return s.toDouble(); }
#endif

#if defined LEM_MFC
double lem::to_real( const CStringA &s )
{ return lem::to_real((const char*)s); }

double lem::to_real( const CStringW &s )
{ return lem::to_real((const wchar_t*)s); }
#endif


#endif // LEM_NOREAL


// ********************************************************************
// ������ �������� ���������� ��� ������� � ����� ��������� �� C/C++,
// �� ���� ��������� ������� ������������� ������.
// ********************************************************************
const lem::UFString lem::to_c_literal( const lem::UFString &str )
{
 UFString res;
 res.reserve( str.length()*2 );
 for( int i=0; i<str.length(); i++ )
  {
   const wchar_t c = str[i];

   if( ((unsigned int)c)<32 )
    {
     switch(c)
     {
      case L'\a':  res += L"\\a";  break;
      case L'\f':  res += L"\\f";  break;
      case L'\t':  res += L"\\t";  break;
      case L'\n':  res += L"\\n";  break;
      case L'\r':  res += L"\\r";  break;
      case L'\b':  res += L"\\b";  break;

      default: 
       if( ((unsigned)c)<16 )
        {  
         res += L"\\x000";
         res += lem::int_to_ustr( int(c), 16 ).c_str();
        }  
       else
        { 
         res += L"\\x00";
         res += lem::int_to_ustr( int(c), 16 ).c_str();
        } 
       break;
     }
    }
   else
    {
     if( c==L'\\' || c==L'\'' || c==L'"' )
      res += L'\\';

     res += str[i];
    }
  }

 return res;
}


const lem::FString lem::to_c_literal( const lem::FString &str )
{
 FString res;
 res.reserve( str.length()*2 );
 for( int i=0; i<str.length(); i++ )
  {
   const unsigned char c = (unsigned char)str[i];
  
   if( c<32 )
    {
     switch(c)
     {
      case '\a':  res += "\\a";  break;
      case '\f':  res += "\\f";  break;
      case '\t':  res += "\\t";  break;
      case '\n':  res += "\\n";  break;
      case '\r':  res += "\\r";  break;
      case '\b':  res += "\\b";  break;

      default: 
       if( c<16 )
        {
         res += "\\x0";
         res += lem::int_to_str( int(0x00ff&c), 16 ).c_str();
        }
       else
        {       
         res += "\\x";
         res += lem::int_to_str( int(0x00ff&c), 16 ).c_str();
        }   
       break;
     }
    }
   else
    {
     if( c=='\\' || c=='\'' || c=='"' )
      res += '\\';

     res += c;
    }
  }

 return res;
}



const UFString lem::from_c_literal( const UFString &str )
{
 UFString res;
 res.reserve( str.length()+1 );

 int i=0;
 const int l=str.length();

 while( i<l )
 {
  const wchar_t c = str[i++];
  if( c==L'\\' )
   {
    switch( str[i++] )
    { 
     case L'a':  res += L'\a';  break;
     case L'f':  res += L'\f';  break;
     case L't':  res += L'\t';  break;
     case L'n':  res += L'\n';  break;
     case L'r':  res += L'\r';  break;
     case L'b':  res += L'\b';  break;
     case L'\\': res += L'\\';  break;
     
     case L'x':
      {
       // ��������� 4 hex-�������
       wchar_t hx[5]; 
       for( int j=0; j<4 && str[i]; j++ )
        { hx[j] = str[i++]; hx[j+1]=0; }
        
       lem::uint16_t h=0; 
       bool rc = lem::to_int( hx, &h, 16 );
       LEM_CHECKIT_Z(rc);
       res += (wchar_t)h;
       break;
      }
       
     default:    res += str[i]; break;
    }
   }
  else
   res += c;
 }

 return res;
}


const FString lem::from_c_literal( const FString &str )
{
 FString res;
 res.reserve( str.length()+1 );

 int i=0;
 const int l=str.length();

 while( i<l )
 {
  const char c = str[i++];
  if( c==L'\\' )
   {
    switch( str[i++] )
    { 
     case 'a':  res += '\a';   break;
     case 'f':  res += '\f';   break;
     case 't':  res += '\t';   break;
     case 'n':  res += '\n';   break;
     case 'r':  res += '\r';   break;
     case 'b':  res += '\b';   break;
     case '\\': res += '\\';   break;
     
     case 'x':
      {
       // ��������� 2 hex-�������
       char hx[3]; 
       for( int j=0; j<2 && str[i]; j++ )
        { hx[j] = str[i++]; hx[j+1]=0; }
        
       int h=0; 
       lem::to_int( hx, &h, 16 );
       res += (char)h;
       break;
      }
     
     default:   res += str[i]; break;
    }
   }
  else
   res += c;
 }

 return res;
}





static char* UrlDecode( const char *source, char *dest )
{
 char *ret;
 char hex[3];

 if(!dest)
  dest = NULL;
 else
  *dest = 0;

 ret = dest;

 if(!source)
  return dest;

 while( *source )
  {
   switch(*source)
   {
    case '+':
     *(dest++) = ' ';
     break;
   
    case '%':
     // NOTE: wrong input can finish with "...%" giving
     // buffer overflow, cut string here
     if(source[1])
      {
       hex[0] = source[1];
       ++source;
       if(source[1])
        {
         hex[1] = source[1];
         ++source;
        }
       else
        hex[1] = 0;
      }
     else
      hex[0] = hex[1] = 0;	

     hex[2] = 0;
     *(dest++) = (char)strtol(hex, NULL, 16);
     break;

    default:
     *(dest++) = *source;
   }

   ++source;
  }

 *dest = 0;
 return ret;
}	

/*
const UFString lem::decode_from_url( const lem::FString &str )
{
 char *buf = new char[ str.length()*2+1 ];
 UrlDecode( str.c_str(), buf );

 FString a(buf);
 delete[] buf;

 UFString u = from_utf8(a);

 return u;
}
*/

const std::wstring lem::to_wstr( wchar_t uc )
{
 wchar_t buf[2] = { uc, 0 };
 return std::wstring( buf );
}

