// -----------------------------------------------------------------------------
// File CP_RECODINGS.CPP
//
// (c) by Koziev Elijah
//     Solarix Intellectronix project - http://www.solarix.ru
//
// Content:
// LEM C++ supplementary library
// ������� ��� �������������� ������ ASCII-������������ �������� �
// UNICODE-������, � ������ ������� ���� �� �����. ������� ���������� �
// ���������� ������ ������� ��� �������������� ������� ���������� ��
// ���������� �������������, � ��� ���������� ���������� ��� ������ ��
// ������� ����������.
//
// 25.09.2007 - ���������� ��������� ���� ��� ������ � ������� � lem_ascii_to_unicode
//              � � to_unicode, ������ ���������� ����� new, � ����� � FString
//              � UFString ������������� ����� free().
// -----------------------------------------------------------------------------
//
// CD->29.09.1997
// LC->12.01.2011
// --------------

#include <lem/user_interface.h>
#include <lem/conversions.h>
#include <lem/unicode.h>

using namespace lem;


 /*************************************************************************
  ������� ����������� ���������� ������-�������� str � ���� ������������
  ������ � ��������� UNICODE. ������� �������������� ������:

  1. ���� str ���������� � ������������� �������� ["], �� ��������
     ������������� ��������� ������ ���������� � ��� �������, ������������
     ��������� ��� ������ ������ ����� � ����� �� ��������, ����������
     ����:

     1.1 "1"         -> ��� 1
     1.2 "0xaf"      -> ��� 175
     1.3 "0o11"      -> ��� 9
     1.4 "0b0001111" -> ��� 15

  2. ���� ������ ��������� � ���������, �� ��������� ������ ���������� ��
     ������������ ��� ����� �����, �� � �������� ������������� ���� �����
     �������� ������� ������� ���������.

  3. � ��������� ������ ���������� ��� ������� ������� ������ str.

  4. ���� str==NULL, �� ���������� 0.
 **************************************************************************/
 lem::uint32_t lem::lem_str_to_unicode( const wchar_t *str )
 {
  if( !(str) )
   return 0;

  if( !lem_is_in_apostrophes(str) )
   return *str;

  UCString tmp(str);
  tmp=strip_quotes(tmp);

  int code;
  if( str_c_to_int( tmp.c_str(), &code ) )
   {
    return (lem::uint32_t)code;
   }

  return (lem::uint32_t)str[1]; // ��� "s" ������ s.
 }


 /********************************************************************
  ����������� ��������� UNICODE-������ � ������ ANSI-��������, ��� ���
  ����� �������� �������� ���������� �������������� � ������� ������
  ������� lem_str_to_unicode.
 *********************************************************************/
 const UCString lem::lem_unicode_to_str( lem::uint32_t ch )
 {
  if( static_cast<unsigned int>(ch) < 128 )
   // ����������� ����� ASCII-�������.
   return UCString(ch);

  UCString res(L'"');
  res += to_wstr(int(ch)).c_str();
  res += L'"';
  return res;
 }



 /**********************************************************************
  ������ �������� src � ANSI-��������� ������������ � UNICODE ��������
  ������� cp, � ���������� ��������� � dst. ���� cp==NULL, �� ������
  �������� ������� �� src � dst. ����� ��������, ��� ����� dst �����
  � ������ ��������� � src, � ��� ���� ���������� ������ �������������.
  �������, ����� ������ ������ ��� ����������.
  ���� src==NULL, �� ����������� ����� ������ ������� ����� � dst.
 ***********************************************************************/
 void lem::lem_ascii_to_unicode(
                                wchar_t *dst,
                                const char *src,
                                const CodeConverter *cp
                               )
 {
  // src -> 0123456789
  //                 |
  //                 isrc
  // dst -> 00112233445566778899
  //                          |
  //                          idst

  LEM_CHECKIT_Z( !!(dst) );

  if( !!(src) )
   {
    if( cp )
     {
      cp->to_unicode( src, dst );
     }
    else
     {
      const int len = CastSizeToInt(strlen(src));
      for( int isrc=0; isrc<len; isrc++ )
       dst[isrc] = SOL_INT_TO_CHAR( src[isrc] );
      dst[len] = 0;
     }
   }
  else
   dst[0]=0;

  return;
 }

 /****************************************************************
  ��������� ��������, �������� �� ��������� � lem_ansi_to_unicode.
  ���� src=NULL, �� ����������� ����� ������ ������� ����� � dst.
 *****************************************************************/
 void lem::lem_unicode_to_ascii(
                                char *dst,
                                const wchar_t *src,
                                const CodeConverter *cp
                               )
 {
  int isrc=0;
  wchar_t src_ch;

  LEM_CHECKIT_Z( !!(dst) );

  if( src )
   {
    if( cp )
     cp->to_ascii(src,dst);
    else
     {
      while( !!(src_ch=src[isrc]) )
       dst[isrc++]=(char)src_ch;
      dst[isrc]=0;
     }   
   }

  return;
 }

/*
 wchar_t lem::lem_ascii_to_unicode( char ch, const CodeConverter *cp )
 { return cp ? cp->to_unicode(ch) : wchar_t(ch); }

 char lem::lem_unicode_to_ascii( wchar_t ch, const CodeConverter *cp )
 { return cp ? cp->to_ascii(ch) : char(ch); }
*/


 const UFString lem::lem_ascii_to_unicode(
                                          const char *str,
                                          const CodeConverter *cp
                                         )
 {
  if( !str )
   return UFString();

  wchar_t *unicode = new wchar_t[ lem_strlen(str)+1 ];
  std::unique_ptr<wchar_t[]> g(unicode);

  if( cp )
   cp->to_unicode( str, unicode );
  else
   lem::UI::get_UI().GetSessionCp().to_unicode( str, unicode );

  return UFString(unicode);
 }


/*
 const UFString lem::to_unicode( const UFString &str, const CodeConverter *cp )
 {
  if( str.empty() )
   return UFString();

  const int l = str.length();
  wchar_t *unicode = UFString::Alloc(l+1);

  if( cp )
   cp->to_unicode( str.c_str(), unicode );
  else
   lem::UI::get_UI().GetSessionCp().to_unicode( str.c_str(), unicode );

  return UFString(unicode,true);
 }
*/


 const UFString lem::to_unicode( const FString &str, const CodeConverter *cp )
 {
  if( str.empty() )
   return UFString();

  const int l = str.length();
  wchar_t *unicode = new wchar_t[l+1];
  std::unique_ptr<wchar_t[]> g(unicode);

  if( cp )
   cp->to_unicode( str.c_str(), unicode );
  else
   lem::UI::get_UI().GetSessionCp().to_unicode( str.c_str(), unicode );

  return UFString(unicode);
 }


 char* lem::lem_unicode_to_ascii( const wchar_t *src, const CodeConverter *_cp )
 {
  if( !(src) )
   return NULL;

  const CodeConverter *cp = _cp ? _cp : &lem::UI::get_UI().GetSessionCp();
  char *dst = new char[ cp->EstimateAsciiLen( lem_strlen(src)+1 )];
  lem_unicode_to_ascii( dst, src, cp ? cp : &lem::UI::get_UI().GetSessionCp() );
  return dst;
 }


 const FString lem::to_ascii( const UFString &str, const CodeConverter *_cp )
 {
  if( str.empty() )
   return FString();

  const CodeConverter *cp = _cp ? _cp : &lem::UI::get_UI().GetSessionCp();

  const int l = str.length();
  char *ascii = new char[ cp->EstimateAsciiLen(l+1) ];
  cp->to_ascii( str.c_str(), ascii );
  FString res(ascii);
  delete[] ascii;
  return res;
 }


 void lem::to_unicode( UCString &dest, const CString &src, const CodeConverter *cp )
 {
  wchar_t res[LEM_CSTRING_LEN+1];
  lem_ascii_to_unicode( res, src.c_str(), cp );
  dest = res;
  return;
 }


 const std::string lem::to_ascii( const std::wstring &str, const CodeConverter *_cp )
 {
  if( str.empty() )
   return std::string();

  const CodeConverter *cp = _cp ? _cp : &lem::UI::get_UI().GetSessionCp();

  const int l = CastSizeToInt(str.length());
  char *ascii = new char[ cp->EstimateAsciiLen(l+1) ];

  cp->to_ascii( str.c_str(), ascii );

  std::string res(ascii);
  delete[] ascii;
  return res;
 }


 const std::wstring lem::to_unicode( const std::string &str, const CodeConverter *cp )
 {
  wchar_t *res = new wchar_t[ str.length()+1 ];
  lem_ascii_to_unicode( res, str.c_str(), cp ? cp : &lem::UI::get_UI().GetSessionCp() );
  std::wstring R(res);
  delete[] res;
  return R;
 }


/*
 const std::wstring lem::to_unicode( const std::wstring &str, const CodeConverter *cp )
 {
  const int l = str.length();
  wchar_t *res = new wchar_t[ l+1 ];

  for( int i=0; i<l; i++ )
   res[i] = cp->to_unicode( (char)str[i] );
 
  res[ l ] = 0;

  std::wstring R(res);
  delete[] res;
  return R;
 }
*/

const UCString lem::to_unicode( const lem::CString &src, const CodeConverter *cp )
{
 UCString res;
 lem_ascii_to_unicode( res.ptr(), src.c_str(), cp ? cp : &lem::UI::get_UI().GetSessionCp() );
 res.ptr()[src.length()] = 0;
 res.calc_hash();
 return res;
}

const lem::CString lem::to_ascii( const lem::UCString &str, const CodeConverter *cp )
{
 if( str.empty() )
  return CString();

 lem::CString ascii;
 lem_unicode_to_ascii( ascii.ptr(), str.c_str(), cp ? cp : &lem::UI::get_UI().GetSessionCp() );
 ascii.ptr()[str.length()] = 0;
 ascii.calc_hash();
 return ascii;
}

lem::UFString lem::to_unicode( const char *aStr )
{
 if( !aStr )
  return lem::UFString();

 const int l = lem_strlen(aStr);
 wchar_t *uStr = new wchar_t[l+1];
 std::unique_ptr<wchar_t[]> g(uStr);

 lem::UI::get_UI().GetSessionCp().to_unicode( aStr, uStr );
 return UFString(uStr);
}



lem::FString lem::to_ascii( const wchar_t *uStr )
{
 if( !uStr )
  return lem::FString();

 const int l = lem_strlen(uStr);
 char *aStr = new char[ lem::UI::get_UI().GetSessionCp().EstimateAsciiLen(l+1) ];
 lem::UI::get_UI().GetSessionCp().to_ascii( uStr, aStr );
 FString res(aStr);
 delete[] aStr;
 return res;
}



// ������� ������� ��� �������� ������ � ��������, ������� ����� ����������� �
// char'���, � wchar_t'���. ��� ������ �� ������ - ���������� ����� ������.
lem::UFString lem::to_unicode( const wchar_t *uStr )
{ return UFString(uStr); }

