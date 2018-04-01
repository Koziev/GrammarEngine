#ifndef LEM_UNICODE__H
#define LEM_UNICODE__H
#pragma once

 #include <lem/config.h>

 #include <ctype.h> // for isalpha.h 
 #include <map>

 #include <lem/integer.h>
 
 #include <lem/cstring.h>
 #include <lem/fstring.h>
 #include <lem/containers.h>
 #include <lem/noncopyable.h>

 #if defined LEM_THREADS
 #include <lem/RWULock.h>
 #endif

 //#undef assert

 namespace lem
 {
  #if !defined LEM_WATCOM
   using std::string;
   using std::wstring;
  #endif



  extern bool is_delim( char ch );

  // *********************************************
  // Command line option delimiter
  // *********************************************
  inline bool is_opchar( char ch )
  { return ch=='/' || ch=='-'; }

  extern bool is_litera( char ch );
  extern bool is_russian( char ch );

  extern bool is_latin( char ch );

  // Char is cyrillic
  inline bool is_cyr( wchar_t ch ) { return ch==0x401 || (ch>=0x0410 && ch<=0x0451); }

  // Char is latin (do diaktriks!)
  inline bool is_lat( wchar_t ch ) { return ch<128 && isalpha(ch); }

  // Латинский символ с возможным диактрическим значком
  extern bool is_lat_diaktr( wchar_t ch );

  inline bool is_french( wchar_t ch )
  {
   return ch<128 &&
          ( 
           isalpha(ch) ||
           wcsrchr(
                   L"\xC0\xC1\xC2\xC4\xC6\xC7\xC8\xC9\xCA\xCB\xCE\xCF"
                   L"\xD2\xD3\xD4\xD6\xD9\xDA\xDB"
                   L"\xE0\xE1\xE2\xE4\xE6\xE7\xE8\xE9\xEA\xEB\xEE\xEF"
                   L"\xF2\xF3\xF4\xF6\xF9\xFA\xFB"
                   L"\x0152\x0x153" 
                   , ch )
           );
  }

  inline bool is_german( wchar_t ch )
  {
   return ch<128 && ( isalpha(ch) || ch==0xDF );
  }

  inline bool is_spanish( wchar_t ch )
  {
   return ch<128 && ( isalpha(ch) || ch==0xF1 );
  }

  inline bool is_italian( wchar_t ch )
  {
   return ch<128 &&
          ( 
           isalpha(ch) ||
           wcsrchr(
                   L"\xC0\xC1\xC2\xC4\xC7\xC8\xC9\xCA\xCB\xCE\xCF"
                   L"\xD2\xD3\xD4\xD6\xD9\xDA\xDB"
                   L"\xE0\xE1\xE2\xE4\xE7\xE8\xE9\xEA\xEB\xEE\xEF"
                   L"\xF2\xF3\xF4\xF6\xF9\xFA\xFB"
                   , ch )
           );
  }


 inline bool is_exponent( char ch )
 { return ch=='e' || ch=='E' || ch=='d' || ch=='D'; }

 inline bool is_signum( char ch )
 { return ch=='-' || ch=='+'; }

 inline bool is_dec_point( char ch )
 { return ch=='.'; }

 inline bool is_hex_digit( char ch )
 { return !!strrchr( "abcdef", tolower(ch) ); }

 inline bool is_ctrl_ch( char ch )
 { return ch==8; }

 inline bool is_space( char ch ) { return !!isspace(ch); }

 inline bool is_value( const char *c )
 { return !!isdigit(c[0]); }

 inline bool is_digit( char ch )
 {
  return ch=='0' ||
         ch=='1' ||
         ch=='2' ||
         ch=='3' ||
         ch=='4' ||
         ch=='5' ||
         ch=='6' ||
         ch=='7' ||
         ch=='8' ||
         ch=='9';
 }


 inline bool is_uexponent( wchar_t ch )
 { return ch==L'e' || ch==L'E' || ch==L'd' || ch==L'D'; }

 inline bool is_usignum( wchar_t ch )
 { return ch==L'-' || ch==L'+'; }

 inline bool is_udec_point( wchar_t ch )
 { return ch==L'.'; }

 inline bool is_uhex_digit( wchar_t ch )
 { return !(ch & 0xff00u) && !!strrchr( "abcdef", tolower(ch) ); }

 inline bool is_ulitera( wchar_t ch )
 {
  return (!(ch & 0xff00u) && is_litera( static_cast<char>(ch))) || // english letters
         (ch>=0x0410 && ch<=0x044f); // russian letters
 }

 inline bool is_udigit( wchar_t ch )
 {
  return (
         ch==L'0' ||
         ch==L'1' ||
         ch==L'2' ||
         ch==L'3' ||
         ch==L'4' ||
         ch==L'5' ||
         ch==L'6' ||
         ch==L'7' ||
         ch==L'8' ||
         ch==L'9' );
 }


 extern char get_numerique( int numer );
 extern bool is_numerique( char ch );
 extern bool is_unumerique( wchar_t ch );

 inline bool is_upunct( wchar_t ch )
 { return !(ch & 0xff00u) && ispunct(ch); }

 inline bool is_punct( char ch )
 {
  // Это странное условие перед вызовом собственно ispunct связан с тем,
  // что какой-то дебил из команды MS сделал генерацию исключения в 
  // библиотечной функции ispunct при значении аргумента ch за пределами
  // указанного диапазона.
  return ch>0 && ch<127 && !!ispunct(ch);
 }

 inline bool is_punct( const char *s )
 { return s[1]=='\0' && is_punct(*s); }

 extern bool is_punct( const wchar_t *s );

 extern bool is_lower( char ch );
 extern bool is_ulower( wchar_t ch );

 extern bool is_upper( char ch );
 extern bool is_uupper( wchar_t ch );

 extern bool is_alpha( char ch );
 extern bool is_ualpha( wchar_t ch );

 extern bool is_al_num( char ch );
 extern bool is_ual_num( wchar_t ch );

 extern bool is_digits( const char *s );


 // ****************************************************
 // Все символы в строке - относятся к кириллице.
 // Будет ошибка, если UNICODE-строка содержит символы
 // кириллицы, полученные простым добавлением старшего
 // нулевого байта, а не использованием перекодировки
 // по кодовой таблице.
 // ****************************************************
 extern bool are_cyr_only( const wchar_t *s );
 extern bool are_cyr_only( const char *s );

 // All chars in string are latin characters.
 extern bool are_lat_only( const wchar_t *s );
 extern bool are_lat_only( const char *s );

 extern bool are_french_only( const wchar_t *s );
 extern bool are_german_only( const wchar_t *s );
 extern bool are_italian_only( const wchar_t *s );
 extern bool are_spanish_only( const wchar_t *s );

 extern bool find_lat( const wchar_t *s );
 extern bool find_lat( const char *s );



  struct CP_Char_Flags
  {
   typedef enum {
                 Control = 0x0001,
                 Unknown = 0x0002, // некоторые знаки, включая <, > и пр.
                 Space   = 0x0004, // пробельные символы (их много) 
                 Punkt   = 0x0008, // Пунктуаторы
                 Digit   = 0x0010, // Цифры
                 Char    = 0x0020, // Символы (в т.ч. с диактрическими значками)
                 Lower   = 0x2000, // признак символа в нижнем регистре
                 Upper   = 0x4000  // признак символа в верхнем регистре
                } CharType; 

   enum { Delim=Space|Punkt|Unknown|Control }; // разделители
   enum { White=Space|Control };       // пробелы или контрольные символы типа \r \n \t

//   wchar_t u;
//  lem::uint16_t flags; 

//   CP_Char_Flags(void) { u=0; flags=UNKNOWN; }
//   CP_Char_Flags( wchar_t U, lem::uint16_t Flags ) : u(U), flags(Flags) {}
  }; 



 class E_UnknownCodepage : public E_BaseException
 {
  public:
   E_UnknownCodepage( const wchar_t *t ) : E_BaseException(t) {}
   explicit E_UnknownCodepage( const wstring &t ):E_BaseException(t) {}
   E_UnknownCodepage( const E_UnknownCodepage &e ):E_BaseException(e) {}

   virtual ~E_UnknownCodepage(void) {}
 };




 class OFormatter;

 // ****************************************************************************
 // Класс CodeConverter - работа с кодовыми таблицами. Эти таблицы хранят
 // информацию о соответствии ASCII и UNICODE кодов для символов и используются
 // для перекодировки при выводе UNICODE-строк на терминал, в текстовый файл
 // и так далее.
 // ****************************************************************************
 class CodeConverter : public lem::NonCopyable
 {
  private:
   #if LEM_DEBUGGING==1
   Guardian guard1;
   #endif

   #if defined LEM_THREADS
   static lem::Process::RWU_Lock cs_sgml;
   #endif
   typedef std::multimap< UCString::hash_type, int > SGML_MAP;
   static SGML_MAP *sgml_map;
   typedef SGML_MAP::const_iterator SGML_MAP_ITER;
   static void CreateSGML(void);

   struct Sgml_Char { const char *str; wchar_t c; };

   #if defined LEM_UNICODE_EX
   static Sgml_Char sgml_list[921];
   #else
   static Sgml_Char sgml_list[8];
   #endif

   static void Add_CodeConverter_Name( const char *name, int index );
   static void Prepare_CodeConverter_Names(void);

  protected:
   int index; // Условный индекс кодовой страницы: 866 для MSDOS, 1251 для
              // Win, 847 для UNIX Koi-8, и т.д.

   std::string encoding; // расширенное имя кодировки - могут быть такие значения,
                         // как utf8 и т.д.

   lem::zbool is_complex; // если кодировщик реализован более сложным образом, нежели
                          // таблица однобайтовых соответствий. 

   #if LEM_DEBUGGING==1
   Guardian guard2;
   #endif

   #if LEM_DEBUGGING==1
   inline void Assert(void) const
   {
    guard1.Assert();
    guard2.Assert();
   }
   #endif 
 
  protected:
   CodeConverter(void);

  public:
   #if defined LEM_UNICODE_EX
   struct Unicode_Char
   {
    lem::uint16_t type;
    wchar_t casing;
    wchar_t norm1, norm2, norm3, norm4;
   };

   static Unicode_Char unicode_table[0x2100];
   #endif

  public:
   CodeConverter( int Index );
   CodeConverter( const char *Encoding );

   #if defined LEM_GNUC
   virtual ~CodeConverter() {}
   #endif

   static void Prepare_Factory(void);
   static void Delete_Static_Data(void);    

   inline bool operator!=( const CodeConverter &x ) const { return index!=x.index; }
   inline bool operator==( const CodeConverter &x ) const { return index==x.index; }

   inline int get_Index(void) const
   {
    IFDEBUG(Assert());
    return index;
   }

   inline const std::string& getEncodingName(void) const
   {
    IFDEBUG(Assert());
    return encoding;
   }

   // ASCII-текст переводится в UNICODE. Память под буфер результата
   // должна быть выделена заранее. Переполнения не фиксируются.
   virtual wchar_t* to_unicode( const char *src, wchar_t *dst ) const=0;

   // UNICODE-текст переводится в ASCII.
   virtual char* to_ascii( const wchar_t *src, char *dst ) const=0;

   // Преобразование 1 unicode символа в цепочку ascii. Для single byte кодировок
   // есть более эффективная реализация SBCodeConverter::to_ascii.
   virtual int to_ascii( wchar_t uch, char *dst ) const=0;

   //! Calculate maximum required capacity for ascii buffer given the length of Unicode string
   // Для однобайтовых кодировок длина строки в Unicode совпадает с длиной в ASCII,
   // для многобайтных - нет, например utf-8 дает до 6 байтов для одного исходного wide символа.
   virtual int EstimateAsciiLen( int UnicodeLen ) const=0;


   // Returns a new instance of a CodeConverter that can encode and decode
   // the requested encoding.
   // На основе "числового" обозначения кодовой страницы (совпадает с
   // принятой для MS Windows) возвращается объект кодовой страницы.
   static const CodeConverter* getConverter( int index );
   static const CodeConverter* getConverter( const char * Encoding );
   static const CodeConverter* getConverter( const lem::FString & Encoding );
   static const CodeConverter* getConverter( const std::string & Encoding );

   // Returns a new instance of a CodeConverter that is suitable
   // for the target platform.
   static const CodeConverter* getDefaultConverter(void);

   // SGML-представление некоторых символов (в HTML это конструкции
   // типа &nbsp; или &lt;) преобразуем в UNICODE-значение символа.
   static wchar_t Sgml_2_Char( const char *str );
   static wchar_t Sgml_2_Char( const FString& str );

   // Возвращается Windows-номер кодовой таблицы по условному имени (у одной
   // кодовой таблицы может быть много имен).
   // Если преобразование невозможно (например, для кодировок типа utf8),
   // то будет возвращено UNKNOWN.
   static int CP_Name_2_Index( const char* CodeConverter_name );

   // Убирает диактрические значки у символов
   static void Strip_Diaktrices( wchar_t *str );
   static wchar_t Strip_Diaktrices( wchar_t c );

   #if defined LEM_UNICODE_EX
   // Замена лигатур на пары символов
   static void Normalize_Ligatures( wchar_t *str );
   static bool Normalize_Ligatures( wchar_t c, wchar_t &c1, wchar_t& c2 );
   #endif

   static wchar_t to_upper( wchar_t c );
   static wchar_t to_lower( wchar_t c );

   static bool is_upper( wchar_t c );
   static bool is_lower( wchar_t c );
   static bool is_udelim( wchar_t c );

   // Если кодовая страница непосредственно не поддерживается встроенными
   // средствами библиотеки LEM, то объект будет хранить только имя кодировки,
   // и данный метод вернет true.
   inline bool complex(void) const
   {
    IFDEBUG(Assert());
    return is_complex;
   }

   virtual bool IsSingleByte(void) const=0;
   bool IsMultiByte(void) const { return !IsSingleByte(); }

   // Выводит в текстовый поток список всех поддерживаемых
   // кодировок текстовых файлов.
   static void List_Supported_Encodings( OFormatter &out );

   static void Get_Supported_Encodings( lem::Collect<string> &res );
 };


 //! Конвертер для однобайтовых кодировок
 class SBCodeConverter : public CodeConverter
 {
  private:
   const wchar_t *a2u; // однозначное соответствие байтовых кодов и UNICODE - 256 элементов

   // для быстрой перекодировки UNICODE->ASCII
   //std::map<wchar_t,char> u2a;
   struct U_A
   {
    wchar_t u; char a;
    U_A() : u(0), a(0) {}
    U_A( wchar_t U ) : u(U), a(0) {}
    inline bool operator>( const U_A &x ) const { return u>x.u; }
    inline bool operator<( const U_A &x ) const { return u<x.u; }
    inline bool operator==( const U_A &x ) const { return u==x.u; }
   };
  
   U_A u2a[256];

   SBCodeConverter(void);

  public:
   SBCodeConverter( int Index, const wchar_t *A2U );

   #if defined LEM_GNU
   virtual ~SBCodeConverter() {}
   #endif

   inline wchar_t to_unicode( char ch ) const
   {
    IFDEBUG(Assert());
    LEM_CHECKIT_Z(a2u!=NULL);
    return a2u[ 0x00ff & ch ];
   } 

   char to_ascii( wchar_t ch ) const;

   // Символ существует в данной таблице?
   inline bool valid( wchar_t ch ) const
   {
    IFDEBUG(Assert());
    //LEM_CHECKIT_Z( !u2a.empty() );
    //return u2a.find(ch)!=u2a.end();
    return std::binary_search( u2a, u2a+256, U_A(ch) );
   }

   virtual wchar_t* to_unicode( const char *src, wchar_t *dst ) const;
   virtual char* to_ascii( const wchar_t *src, char *dst ) const;
   virtual int to_ascii( wchar_t uch, char *dst ) const;
   virtual int EstimateAsciiLen( int UnicodeLen ) const;
   virtual bool IsSingleByte(void) const;
 };



 //! Конвертер для многобайтовых кодировок
 class MBCodeConverter : public CodeConverter
 {
  public:
   MBCodeConverter( const char *Encoding );

   #if defined LEM_GNU
   virtual ~MBCodeConverter() {}
   #endif

   virtual bool IsSingleByte(void) const;
 };


 class Utf8CodeConverter : public MBCodeConverter
 {
  public:
   Utf8CodeConverter(void);

   virtual wchar_t* to_unicode( const char *src, wchar_t *dst ) const;
   virtual char* to_ascii( const wchar_t *src, char *dst ) const;
   virtual int to_ascii( wchar_t uch, char *dst ) const;
   virtual int EstimateAsciiLen( int UnicodeLen ) const;
 };



 class CP_Dummy : public SBCodeConverter
 {
  public:
   CP_Dummy(void):SBCodeConverter(0,NULL) {}
 };


 #if defined LEM_GNU
  #define CODEPAGE(Index)             \
   class CP_##Index : public SBCodeConverter \
   {                                  \
    public:                           \
     CP_##Index(void);                \
     virtual ~CP_##Index(void) {}     \
   };
 #else
  #define CODEPAGE(Index)             \
   class CP_##Index : public SBCodeConverter \
   {                                  \
    public:                           \
     CP_##Index(void);                \
   };
  #endif




 CODEPAGE( 037  );
 CODEPAGE( 424  );
 CODEPAGE( 1006 );
 CODEPAGE( 1026 ); 
 CODEPAGE( 1250 );
 CODEPAGE( 1251 );
 CODEPAGE( 1252 );
 CODEPAGE( 1253 );
 CODEPAGE( 1254 );
 CODEPAGE( 1255 );
 CODEPAGE( 1256 );
 CODEPAGE( 1257 );
 CODEPAGE( 1258 );
 CODEPAGE( 437 );
 CODEPAGE( 500 );
 CODEPAGE( 737 );
 CODEPAGE( 775 );
 CODEPAGE( 850 );
 CODEPAGE( 847 );
 CODEPAGE( 852 );
 CODEPAGE( 855 );
 CODEPAGE( 856 );
 CODEPAGE( 857 );
 CODEPAGE( 860 );
 CODEPAGE( 861 );
 CODEPAGE( 862 );
 CODEPAGE( 863 );
 CODEPAGE( 864 );
 CODEPAGE( 865 );
 CODEPAGE( 866 );
 CODEPAGE( 869 );
 CODEPAGE( 874 );
 CODEPAGE( 875 );

 CODEPAGE( 8859_1  );
 CODEPAGE( 8859_2  );
 CODEPAGE( 8859_3  );
 CODEPAGE( 8859_4  );
 CODEPAGE( 8859_5  );
 CODEPAGE( 8859_6  );
 CODEPAGE( 8859_7  );
 CODEPAGE( 8859_8  );
 CODEPAGE( 8859_9  );
 CODEPAGE( 8859_10 );
 CODEPAGE( 8859_11 );
// CODEPAGE( 8859_12 );
 CODEPAGE( 8859_13 );
 CODEPAGE( 8859_14 );
 CODEPAGE( 8859_15 );
 CODEPAGE( 8859_16 );


 #if defined LEM_ICU
 class CodeConverter_ICU : public CP_1250
 {
  public:
   // Наследуемся от cp1250, чтобы обеспечить базовую функциональность
   // при неправильном использовании. Может, это неправильно, и надо
   // быть беспощаднее.
   CodeConverter_ICU( const char *Encoding ):CP_1250()
   {
    is_complex = true;
    encoding = Encoding;
   }
 };
 #endif


  // Строка преобразуется от ANSI-формата (1 байт на символ) к UNICODE-формату,
  // то есть 2 байта на символ. При этом создается объект UFString, который
  // будет автоматически удален.
  // Кодовая страница не используется, то есть только латиница преобразуется
  // корректно.
  #define A2U(s) UFString(s)

  // Аналогично предыдущему макросу, только преобразование от UNICODE к ANSI.
  // Кодовая страница не используется, то есть только латиница преобразуется
  // корректно.
  #define U2A(s) FString(s)

  extern lem::FString to_ascii( const wchar_t *uStr );
  extern lem::UFString to_unicode( const char *uStr );

  // Функция введена для удобства работы в шаблонах, которые могут оперировать и
  // char'ами, и wchar_t'ами. Она ничего не делает - возвращает копию строки.
  extern lem::UFString to_unicode( const wchar_t *uStr );

  // перекодировки с Юникодом - если кодовая страница не указана явно (то есть
  // аргумент NULL), то используем текущую локаль.
  //extern const UFString to_unicode( const UFString &str, const CodeConverter *cp=NULL );
  //extern const wstring to_unicode( const wstring &str, const CodeConverter *cp=NULL );
  extern const UFString to_unicode( const FString &str, const CodeConverter *cp=NULL );
  extern const UCString to_unicode( const CString &str, const CodeConverter *cp=NULL );
  extern const wstring to_unicode( const string &str, const CodeConverter *cp=NULL );

  extern void to_unicode( UCString &dest, const CString &src, const CodeConverter *cp=NULL );
  extern void to_unicode( UFString &dest, const FString &src, const CodeConverter *cp=NULL );

  extern void lem_unicode_to_ascii( char *dst, const wchar_t *src, const CodeConverter *cp=NULL );
  extern char* lem_unicode_to_ascii( const wchar_t *src, const CodeConverter *cp=NULL );
//  extern char lem_unicode_to_ascii( wchar_t ch, const CodeConverter *cp=NULL );

  extern void lem_ascii_to_unicode( wchar_t *dst, const char *src, const CodeConverter *cp=NULL );
//  extern wchar_t lem_ascii_to_unicode( char ch, const CodeConverter *cp=NULL );
  extern const UFString lem_ascii_to_unicode( const char *str, const CodeConverter *cp=NULL );

  extern const FString to_ascii( const UFString &str, const CodeConverter *cp=NULL );
  extern const CString to_ascii( const UCString &str, const CodeConverter *cp=NULL );
  extern const string to_ascii( const wstring &str, const CodeConverter *cp=NULL );

  extern void to_ascii( CString &dest, const UCString &src, const CodeConverter *cp=NULL );
  extern void to_ascii( FString &dest, const UFString &src, const CodeConverter *cp=NULL );


  extern lem::uint32_t lem_str_to_unicode( const wchar_t *str );
  extern const UCString lem_unicode_to_str( lem::uint32_t ch );

  // Указатели на эти кодовые страницы доступны всегда
  extern CP_866    *cp866;
  extern CP_847    *cp847;
  extern CP_1250   *cp1250;
  extern CP_1251   *cp1251;
  extern CP_1252   *cp1252;
  extern CP_8859_1 *cp28591;
  extern Utf8CodeConverter *cp_utf8;

  // ********************************************************************************
  // Специфическая штучка - преобразование класса char-строки в класс wchar_t-строки.
  // ********************************************************************************
  template < class FIRST > class ASTR_TO_WSTR;

  #if !defined LEM_WATCOM
  template<>
  #endif
  class ASTR_TO_WSTR< FString >
  {
   public:
    typedef UFString to_u;    
  };

  #if !defined LEM_WATCOM
  template<>
  #endif
  class ASTR_TO_WSTR< CString >
  {
   public:
    typedef UCString to_u;    
  };


  // Является ли строка корректной в UTF-8?
  //extern bool utf8_valid( const lem::FString &buf );
  //extern bool utf8_valid( const std::string &buf );
  //extern bool utf8_valid( const char *buf );
  //extern bool utf8_valid( const unsigned char *buf, unsigned int len );

  // Возвращает строку, закодированную в UTF8
  extern lem::FString to_utf8( const wchar_t *ustr );
  extern lem::FString to_utf8( const lem::UFString &ustr );
  extern std::string  to_utf8( const std::wstring &ustr );

  extern lem::UFString from_utf8( const char *astr );
  extern lem::UFString from_utf8( const lem::FString &astr );
  extern std::wstring  from_utf8( const std::string &astr );

  extern int ucs4_to_utf8( const lem::uint32_t *ucs4_buf, int ucs4_len, unsigned char *utf8_buf );
  extern int UCS4_to_UTF8( lem::uint32_t ucs4, lem::uint8_t utf8[8] );
  extern int utf8_to_ucs4( const unsigned char *utf8_buf, int utf8_len, lem::uint32_t *ucs4_buf );

  extern char* encode_base64( const char *in, int len );
  extern char* decode_base64( const char *in, int len );

  #if defined LEM_WINDOWS 
  #define UTF8STR(s) from_utf8(s).c_str()
  #elif defined LEM_UNIX
  #define UTF8STR(s) L##s
  #else
  #define UTF8STR(s) L##s
  #endif

  inline bool is_udelim( wchar_t c )
  {
   #if defined LEM_UNICODE_EX
   if( c < (wchar_t)DIM_A(lem::CodeConverter::unicode_table) )
    {
     const int t = lem::CodeConverter::unicode_table[ static_cast<lem::uint32_t>(0x0000ffff & c) ].type;
     return (t&CP_Char_Flags::Delim)!=0;
    }  
        
   return false;  
   #else  

   return c>0 && c<255 && (is_delim( static_cast<char>(c) )
         || c==L'\xAB' || c==L'\xBB'
         || c==L'\x2026' || c==L'\xA1' || c==L'\xBF' );  

   #endif
  }

  /*************************************************************
   Determines if ch is a space, tab, carriage return, new line,
   vertical tab, or formfeed (0x09 to 0x0D, 0x20)
  **************************************************************/
  inline bool is_uspace( wchar_t c )
  {
   #if defined LEM_UNICODE_EX
   if( c < (wchar_t)DIM_A(lem::CodeConverter::unicode_table) )
    {
     const int t = lem::CodeConverter::unicode_table[ static_cast<lem::uint32_t>(0x0000ffff & c) ].type;
     return (t&CP_Char_Flags::White)!=0;
    }  
        
   return c==0xFEFF ||
          c==0xFFFE;
   #else  

   // В стандарте UNICODE очень много разных пробелов.
   return c==0x0020 ||
          c==0x00A0 ||
          (c>=0x2000 && c<=0x200B) ||
          c==0x202F ||
          c==0x205F  ||
          c==0x3000  ||
          c==0xFEFF  ||
          c==0xFFFE  ||
          #if defined LEM_WINDOWS
          (!(c & 0xff00u) && isspace(c));
          #elif defined LEM_UNIX
          (!(c & 0xffffff00u) && isspace(c));
          #else
           #error ...
          #endif

   #endif
  }

  extern const CString recode(
                              const CString &x,
                              const CodeConverter &from,
                              const CodeConverter &to
                             );

  extern const FString recode(
                              const FString &x,
                              const CodeConverter &from,
                              const CodeConverter &to
                             );
 } // end of namespace 'lem'

#endif
