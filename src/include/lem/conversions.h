#ifndef LEM_CONVERT__H
#define LEM_CONVERT__H
#pragma once

// -----------------------------------------------------------------------------
// File CONVERSIONS.H
//
// (c) by Koziev Elijah
//     Solarix Intellectronix project - http://www.solarix.ru
//
// Content:
//
// Various conversion procedures.
//
// Преобразование строк в переменные разных типов, с контролем корректности
// текстового представления. Перекодировки символов для разных кодовых страниц.
//
// Эти же процедуры для UNICODE-строк.
//
// Функции для преобразования строки ASCII-кодированных символов в
// UNICODE-символ, и другие функции того же плана. File contains function
// prototypes of Unicode-ANSI character transcoding facility.
// -----------------------------------------------------------------------------
//
// CD->11.01.1996
// LC->07.11.2014
// --------------

 #include <lem/config.h>

 #include <ctype.h>

 #if defined LEM_MFC
  #include <afxwin.h>
 #endif

 #include <lem/math/real.h>
 #include <lem/cstring.h>
 #include <lem/fstring.h>
 #include <lem/stl.h>
 #include <lem/unicode.h>

 #if defined LEM_DOT_NET
  #using <mscorlib.dll>
  #using <System.dll>
 #endif

 #if defined LEM_WINDOWS
  #include <oleauto.h>
 #endif

 #if defined LEM_WXWIDGETS
  #include <wx/string.h>
 #endif 

 #if defined LEM_QT
  #include <QString>
 #endif

 namespace lem
 {

 extern char dos_to_win( char ch );
 extern char dos_to_koi8( char ch );
 extern char win_to_dos( char ch );
 extern char win_to_koi8( char ch );
 extern char koi8_to_dos( char ch );
 extern char koi8_to_win( char ch );

 extern wchar_t dos_to_uni( char ch );
 extern char uni_to_dos( wchar_t ch );

 extern char recode_char( char ch, int icp_src, int icp_dst );
 extern void recode_string( lem::FString &str, int icp_src, int icp_dst );

 extern void truncate_trailing_dot( char *s );

 const int LEM_RUS=0, LEM_ENG=1;
 extern const wstring to_text( int val, int lang=LEM_ENG, bool masculine=true );

 inline int b2i( bool f ) { return f ? 1 : 0; }

 // **********************************************************************
 // Если аргумент - положительное число, то вернет строковое представление
 // этого числа, если же аргумент равен нулю - вернет строку "null"
 // **********************************************************************
 const CString i2ns( int ival );

 extern wchar_t get_unumerique( int numer );
 extern bool is_unumerique( wchar_t ch );

 extern int uchar_to_digit( wchar_t ch );
 extern int char_to_digit( char ch );


 extern void trunc_zeros( wchar_t *field );
 extern void trunc_zeros( char *field );


 extern void dos_to_win( char *s );
 extern void dos_to_koi( char *s );
 extern void koi_to_dos( char *s );
 extern void win_to_dos( char *s );


 // ***************************************************************


 extern bool split(
                   const char *src,
                   int *int_signum, char *int_part,  int int_len,
                                    char *frac_part, int frac_len,
                   int *exp_signum, char *exp_part,  int exp_len
                  );

 extern bool split(
                   const wchar_t *src,
                   int *int_signum, wchar_t *int_part,  int int_len,
                                    wchar_t *frac_part, int frac_len,
                   int *exp_signum, wchar_t *exp_part,  int exp_len
                  );

 inline bool split(
                   const char *src,
                   int *int_signum, char *int_part,
                                    char *frac_part,
                   int *exp_signum, char *exp_part
                  )
 {
  return split(
               src,
               int_signum, int_part, -1,
                           frac_part, -1,
               exp_signum, exp_part, -1
              );
 }

 inline bool split(
                   const wchar_t *src,
                   int *int_signum, wchar_t *int_part,
                   wchar_t *frac_part,
                   int *exp_signum, wchar_t *exp_part
                  )
 {
  return split(
               src,
               int_signum, int_part, -1,
                           frac_part, -1,
               exp_signum, exp_part, -1
              );
 }

 extern char* int16_to_str(
                           lem::int16_t val,
                           char *buffer,
                           int radix=10
                          );

 extern wchar_t* int16_to_str(
                              lem::int16_t val,
                              wchar_t *buffer,
                              int radix=10
                             );

 extern char* uint16_to_str(
                            lem::uint16_t val,
                            char *buffer,
                            int radix=10
                           );

 extern wchar_t* uint16_to_str(
                               lem::uint16_t val,
                               wchar_t *buffer,
                               int radix=10
                              );

 extern const CString int16_to_str( lem::int16_t val, int radix=10 );
 extern const UCString int16_to_ustr( lem::int16_t val, int radix=10 );

 extern char* int32_to_str(
                           const lem::int32_t val,
                           char *buffer,
                           int radix=10
                          );

 extern char* uint32_to_str(
                            const lem::uint32_t val,
                            char *buffer,
                            int radix=10
                           );


 extern wchar_t* int32_to_str(
                              const lem::int32_t val,
                              wchar_t *buffer,
                              int radix=10
                             );

 extern wchar_t* uint32_to_str(
                               lem::uint32_t val,
                               wchar_t *buffer,
                               int radix=10
                              );

 extern const CString int32_to_str( lem::int32_t val, int radix=10 );
 extern const UCString int32_to_ustr( lem::int32_t val, int radix=10 );


  inline char* int_to_str(
                          const lem::int32_t val,
                          char *buffer,
                          int radix=10
                         )
  { return int32_to_str(val,buffer,radix); }

  inline char* uint_to_str(
                           const lem::uint32_t val,
                           char *buffer,
                           int radix=10
                          )
  { return uint32_to_str(val,buffer,radix); }

  inline const CString int_to_str( lem::int32_t val, int radix=10 )
  { return int32_to_str(val,radix); }

  inline wchar_t* int_to_str( lem::int32_t val, wchar_t *buffer, int radix=10 )
  { return int32_to_str(val,buffer,radix); }

  inline wchar_t* uint_to_str( lem::uint32_t val, wchar_t *buffer, int radix=10 )
  { return uint32_to_str(val,buffer,radix); }

  inline const UCString int_to_ustr( lem::int32_t val, int radix=10 )
  { return int32_to_ustr(val,radix); }


 extern bool to_int( const char *str, lem::int16_t *res, lem::int16_t radix=10 );
 extern bool to_int( const char *str, lem::int32_t *res, int radix=10 );
 extern bool to_int( const wchar_t *str, lem::int16_t *res, lem::int16_t radix=10 );
 extern bool to_int( const wchar_t *str, lem::int32_t *res, int radix=10 );
 extern bool to_int( const char *str, lem::uint16_t *res, int radix=10 );
 extern bool to_int( const wchar_t *str, lem::uint16_t *res, int radix=10 );

 #if defined LEM_INT64
 extern bool to_int( const wchar_t *str, lem::int64_t *res, int radix=10 );
 extern bool to_int( const char *str, lem::int64_t *res, int radix=10 );
 #endif

 extern bool str_c_to_int( const char *str, lem::int16_t *res );
 extern bool str_c_to_int( const char *str, lem::int32_t *res );

 extern bool str_c_to_int( const wchar_t *str, lem::int16_t *res );
 extern bool str_c_to_int( const wchar_t *str, lem::int32_t *res );

  extern int parse_ranges(
                          const char *s,
                          MCollect< std::pair<int,int> > &range
                         );


  // Из строки выделяется список токенов, отделяемых пробелами или
  // обычными разделителями.
  extern void parse( const UFString &str, MCollect<UCString> &words, bool preserve_delimeters );
  extern void parse( const FString &str, MCollect<CString> &words, bool preserve_delimeters );
  extern void parse( const UFString &str, Collect<UFString> &words, const wchar_t *delimeters=L";\r\n", bool unique_only=false );

  inline const CString      to_str(  int val ) { return int_to_str(val); }
  inline const UCString     to_ustr( int val ) { return int_to_ustr(val); }
  inline const std::string  to_cstr( int val ) { return int_to_str(val).c_str(); }
  inline const std::wstring to_wstr( int val ) { return int_to_ustr(val).c_str(); }

  extern const CString to_str( double val, const char *Format="%g" );
  extern const UCString to_ustr( double val, const char *Format="%g" );
  extern const std::string to_cstr( double val, const char *Format="%g" );
  extern const std::wstring to_wstr( double val, const char *Format="%g" );

  inline const std::wstring to_wstr( const char *aText )
  { return std::wstring( UFString(aText).c_str() ); }

  inline const std::wstring to_wstr( const wchar_t *wText )
  { return std::wstring( wText ); }

  extern const std::wstring to_wstr( wchar_t uc );

  inline const std::string to_cstr( const char *aText )
  { return std::string( aText ); }

  #if defined LEM_I64
  extern char* to_str( lem::int64_t val, char *buffer, int radix=10 );
  extern wchar_t* to_ustr( lem::int64_t val, wchar_t *buffer, int radix=10 );
  extern const lem::CString to_str( lem::int64_t val, int radix=10 );
  extern const lem::UCString to_ustr( lem::int64_t val, int radix=10 );
  #endif

  #if defined LEM_UI64
  extern char* to_str( lem::uint64_t val, char *buffer, int radix=10 );
  extern wchar_t* to_ustr( lem::uint64_t val, wchar_t *buffer, int radix=10 );
  extern const lem::CString to_str( lem::uint64_t val, int radix=10 );
  extern const lem::UCString to_ustr( lem::uint64_t val, int radix=10 );
  #endif

  #if defined LEM_INTN
  class integer128;
  extern char* to_str(
                      const integer128 &val,
                      char *buffer,
                      int radix=10
                     );
  #endif

  inline const CString      to_str(  bool val ) { return val ? "true"  : "false";  }
  inline const UCString     to_ustr( bool val ) { return val ? L"true" : L"false"; }
  inline const std::string  to_cstr( bool val ) { return val ? "true"  : "false";  }
  inline const std::wstring to_wstr( bool val ) { return val ? L"true" : L"false"; }


  #if defined LEM_DOT_NET
  extern std::wstring to_wstr( System::String* src );
  extern std::string to_cstr( System::String* src );
  extern lem::UFString to_ustr( System::String* src );

  // Преобразование из System::String в lem::UFString
  extern lem::UFString& to_ustr( System::String* src, UFString &dst );
  #endif

  #if defined LEM_VCL
//  extern lem::UFString to_ustr( AnsiString& src );
//  extern lem::UFString to_ustr( WideString& src );
  #endif

  #if defined LEM_WINDOWS
  extern lem::UFString to_ustr( const BSTR *bstr );
  #endif

  #if defined LEM_WXWIDGETS
  extern lem::UFString to_ustr( const wxString &s );
  #endif

  #if defined LEM_QT
  extern lem::UFString to_ustr( const QString &s );
  #endif

  extern int to_int( const char *s );
  extern int to_int( const wchar_t *s );
  extern int to_int( const lem::UFString &s );
  extern int to_int( const lem::FString &s );
  extern int to_int( const lem::UCString &s );
  extern int to_int( const lem::CString &s );
  extern int to_int( const std::string &s );
  extern int to_int( const std::wstring &s );
  #if defined LEM_QT
  extern int to_int( const QString &s );
  #endif
  #if defined LEM_WXWIDGETS
  extern int to_int( const wxString &s );
  #endif
  #if defined LEM_DOT_NET
  extern int to_int( System::String* s );
  #endif
  #if defined LEM_MFC
  extern int to_int( const CStringA &s );
  extern int to_int( const CStringW &s );
  #endif

  extern bool to_bool( const char *str, bool *res );
  extern bool to_bool( const wchar_t *str, bool *res );


  extern bool to_bool( const char *str );
  extern bool to_bool( const wchar_t *str );
  extern bool to_bool( const lem::FString &str );
  extern bool to_bool( const lem::UFString &str );
  extern bool to_bool( const lem::CString &str );
  extern bool to_bool( const lem::UCString &str );

  extern bool is_value( const wchar_t *s );

  extern bool is_name( const char *s );
  extern bool is_name( const wchar_t *s );

  extern bool is_int( const char *s );
  extern bool is_int( const wchar_t *s );
  extern bool is_int( const lem::FString & s );
  extern bool is_int( const lem::UFString & s );

  extern bool is_c_int( const char *s );
  extern bool is_c_int( const wchar_t *s );

  extern bool is_real( const char *s );
  extern bool is_real( const wchar_t *s );

  #if !defined LEM_NOREAL
  extern bool to_real( const char *str, double *res );
  extern bool to_real( const wchar_t *str, double *res );

  extern double to_real( const char *str );
  extern double to_real( const wchar_t *str );
  extern double to_real( const lem::UFString& str );
  extern double to_real( const lem::FString& str );
  extern double to_real( const std::wstring& str );
  extern double to_real( const std::string& str );
  #if defined LEM_WXWIDGETS
  extern double to_real( const wxString& str );
  #endif
  #if defined LEM_QT
  extern double to_real( const QString &s );
  #endif
  #if defined LEM_MFC
  extern double to_real( const CStringA &s );
  extern double to_real( const CStringW &s );
  #endif

  extern double share_to_real( const char *str );
  #endif

  extern const std::string to_roman( int i );

  extern char* to_lower( char *s );
  extern char* to_lower_w( char *s );
  extern wchar_t* to_lower( wchar_t *s );

  extern char* to_upper( char *s );
  extern wchar_t* to_upper( wchar_t *s );
  extern char* to_upper_w( char* s );
  extern const std::string to_upper( const std::string &s );
  extern const std::string to_upper_w( const std::string &s );
  extern const std::wstring to_upper( const std::wstring &s );

  extern char to_lower( char s );
  extern char to_lower_w( char s );

  extern const std::string to_lower( const std::string &s );
  extern const std::string to_lower_w( const std::string &s );
  extern const std::wstring to_lower( const std::wstring &s );

  extern char to_upper( char s );
  extern char to_upper_w( char s );

   // **********************************************************************
   // Быстрая, но узкоспециализированная функция для приведения одиночного
   // символа к верхнему регистру. 
   // **********************************************************************
   inline wchar_t to_uupper( wchar_t ch )
   {
//   #if defined LEM_MSC
//    return towupper(ch);
//   #else
     // Английские буквы (базовая латиница)
     if( ch>='a' && ch<='z' )
      return char(ch-32);

     if( static_cast<unsigned int>(ch)<128 )
      return ch; 

     // ***************************
     // Русская кириллица.
     // ***************************

     // прочие русские буквы
     if( ch>=0x0430 && ch<=0x044f )
      return ch-0x0020; 

     // особый подход к Ё
     if( ch==0x0451 )
      return 0x0401;
  
     #if defined LEM_UNICODE_EX
     return CodeConverter::to_upper(ch);
     #else
     return ch;
     #endif
  
//   #endif
   }

   inline wchar_t to_ulower( wchar_t ch )
   {
//   #if defined LEM_MSC
//    return towlower(ch);
//   #else
    // Английские буквы (базовая латиница)
    if( ch>='A' && ch<='Z' )
     return char(ch+32);

    if( static_cast<unsigned int>(ch)<128 )
     return ch;

    // ***************************
    // Русская кириллица.
    // *************************** 

    // прочие русские буквы
    if( ch>=0x0410 && ch<=0x042f )
     return ch+0x0020; 

    // особый подход к Ё
    if( ch==0x0401 )
     return 0x0451;

    #if defined LEM_UNICODE_EX
    return CodeConverter::to_lower(ch);
    #else
    return ch;
    #endif
//   #endif
  }


  inline const std::wstring to_Aa( const std::wstring &x )
  {
   wstring res=x;
   res[0] = to_uupper( res[0] );
   return res;
  }

  // *****************************************************************
  // Транслитерация кириллицы - русские буквы заменяем на сочетани
  // латинских.
  // *****************************************************************
  extern const std::string translit_ru( const wchar_t *src );

  extern bool are_mixed_languages( const wchar_t *str );

  // ***************************************************************************
  // Некоторые символы в текстовых файлах HTML и XML имеют специальное значение,
  // и должны поэтому преобразовываться в спецпоследовательности
  // ***************************************************************************
  template < class STR >
  inline STR to_html( const STR &s )
  {
   if( s == "&" )
    return L"&amp;";
   else if( s == "<" )
    return L"&lt;";
   else if( s == ">" )
    return L"&gt;";

   return s;
  }


  extern std::wstring filesize_to_wstr( lem::uint64_t Size );

  // Кодирование символов в адресе: не-ASCII символы представляются в виде %HH
  // UCS-2 переводится в utf-8.
  extern const FString encode_to_url( const UFString &str );

  // Кодирование символов в URL
  extern const FString encode_to_url( const lem::FString &str );
  extern const UFString decode_from_url( const lem::FString &str );

  extern const lem::UFString to_c_literal( const lem::UFString &str );
  extern const lem::FString to_c_literal( const lem::FString &str );
  extern const lem::UFString from_c_literal( const lem::UFString &str );
  extern const lem::FString from_c_literal( const lem::FString &str );
 }

#endif
