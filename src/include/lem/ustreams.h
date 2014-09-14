// -----------------------------------------------------------------------------
// File USTREAMS.H
//
// (c) by Koziev Elijah
//     Solarix Intellectronix project - http://www.solarix.ru
//
// Content:
// LEM C++ supplementary library
//
// UNICODE character stream classes. They extend the byte char streams so
// the wget() and wput() methods operate the wchar_t objects.
// 
// Классы для работы с текстовыми файлами на UNICODE символьном уровне. Эти потоки
// имеют интерфейс для работы с wchar_t - символами, самостоятельно
// перекодируют char в unicode, когда работают с ASCII-потоками. Представляют
// более высокий уровень работы с потоками в сравнении с Stream.
//
// Декодеры для извлечения текстовой информации из сложно форматированных
// текстовых файлов (HTML, XML, RTF и др).
//
// 04.08.2007 - рефакторинг: переименование Base_Reader в WideStream
// 22.02.2008 - переработано обслуживание кодировок в RTF_Reader'е, добавлена
//              корректная обработка команд deflangXXX и langXXX
// 22.04.2008 - переработан метод Read_Beginning, теперь он кидает исключения
//              опционально (если BOM не прочитан корректно) и возвращает 
//              признак успешности чтения BOM. 
// 15.08.2009 - парсер PDF вынесен в отдельный хидер
// -----------------------------------------------------------------------------
//
// CD->18.11.2004
// LC->11.07.2010
// --------------

#ifndef LEM_CHAR_STREAM
#define LEM_CHAR_STREAM
#pragma once

 #include <lem/config.h>

 #if defined LEM_MFC
  #include <afxwin.h>
 #endif

 #if defined LEM_ICU
  #include <icu/include/unicode/utypes.h>
  #include <icu/include/unicode/putil.h>
  #include <icu/include/unicode/ucnv.h>
  #include <icu/include/unicode/unistr.h>
  #include <icu/include/unicode/uenum.h>
 #endif

 #include <lem/unicode.h>
 #include <lem/streams.h>
 #include <lem/containers.h>
 #include <lem/zeroed.h>
 #include <lem/smart_pointers.h>

 #undef assert

 namespace lem
 {
  class CodeConverter;
  class OUFormatter;

  typedef lem::Ptr<lem::Stream> StreamPtr;

  namespace Char_Stream
  {
   using lem::Stream;
   using lem::CodeConverter;
   using lem::MCollect;
   using lem::E_BaseException;

   typedef enum {
                 SET_UNKNOWN,
                 SET_ASCII,   // однобайтовые потоки, используют CodeConverter для преобразования в UNICODE
                 SET_UTF8,
                 SET_UTF16,
                 SET_UTF16BE,
                 #if defined LEM_ICU 
                 SET_ICU,     // поток использует средства ICU для декодирования потока байтов 
                 #endif
                 SET_RTF,
                 SET_HTML,
                 SET_MSWORD,
                 SET_PLUGIN
                } WideStreamType;

   class Invalid_Charset : public E_BaseException
   {
    public:
     Invalid_Charset(void)
      : E_BaseException( L"Invalid charset" ) {}
   };


   // *****************************************************************
   // Языковой фильтр - применяется в случаях, когда нужно отсечь из
   // потока символов относящиеся к определенным группам (например, 
   // оставить только кириллицу).
   // *****************************************************************
   class Lang_Filter
   {
    public:
     Lang_Filter(void) {}
     virtual ~Lang_Filter(void) {}

     // Общий принцип: если символ не из нужного диапазона, то
     // возвращается пробел.
     virtual wchar_t operator()( wchar_t c ) const=0;
   };

   // *****************************************************************
   // Оставляет символы кириллицы (русские) и цифры, пунктуаторы, ...
   // *****************************************************************
   class Russian_Filter : public Lang_Filter
   {
    public:
     Russian_Filter(void) {}
     virtual wchar_t operator()( wchar_t c ) const; 
   };

   // *****************************************************************
   // Оставляет символы базовой латиницы, цифры, пунктуаторы, т.д.
   // *****************************************************************
   class Latin_Filter : public Lang_Filter
   {
    public:
     Latin_Filter(void) {}
     virtual wchar_t operator()( wchar_t c ) const;
   };

   // *****************************************************************
   // Оставляет символы базовой латиницы и с диактрическими знаками,
   // цифры, пунктуаторы, т.д.
   // *****************************************************************
   class Central_European_Filter : public Lang_Filter
   {
    public:
     Central_European_Filter(void) {}
     virtual wchar_t operator()( wchar_t c ) const;
   };


   // ************************************************************************
   // Базовый класс для иерархии: он расширяет функциональность однобайтового
   // Stream за счет методов чтения и записи юникодных символов.
   // ************************************************************************
   class WideStream : public lem::Stream
   {
    private:
     WideStream( const WideStream & );
     void operator=( const WideStream & );

     virtual void write( const void *src, pos_type size );
     virtual pos_type read( void *dest, pos_type size );

    protected:
     lem::Char_Stream::WideStreamType type;
     StreamPtr bin;
     
     wchar_t back_ch; // Возвращенный в unget() символ
     pos_type back_pos; // Позиция возвращенного символа

     lem::zbool strip_decoration; // отбрасывать ли служебную информацию (тэги,
                                  // форматирование и так далее)

     // Эта кодовая страница используется только для того, чтобы получаемые для
     // записи ASCII-символы преобразовывать в UNICODE. Напоминаю, что этот поток
     // поддерживает весь интерфейс базового класса Stream, который по сути
     // своей формирует поток однобайтовых символов.
     const CodeConverter *cp;

     pos_type last_char_pos;
     virtual wchar_t Read_Char(void)=0;

     WideStream( lem::Char_Stream::WideStreamType t );
     WideStream( lem::Char_Stream::WideStreamType t, StreamPtr Bin );

    public:

     virtual ~WideStream(void);

     // Этот метод пытается подобрать для заданного двоичного потока
     // нужный ридер, который сможет извлечь текстовую информацию.
     // 03.11.2008 - по умолчанию ASCII файлы будут запускать charset guesser для
     //              подбора кодировки, но если задать кодировку явно (cp!=NULL),
     //              то для не-utf файлов будет использована именно она.
     static lem::Ptr<WideStream> GetReader( lem::StreamPtr Bin, const lem::CodeConverter *cp=NULL );
     static lem::Ptr<WideStream> GetReader( const lem::Path &p, const lem::CodeConverter *cp=NULL );

     inline lem::Char_Stream::WideStreamType GetType(void) const { return type; }

     // Путь к открытому документу.
     virtual const lem::Path& GetName(void) const;
     
     // Два метода читают и пишут начальную служебную
     // информацию - например, метку BOM.
     // excp - бросать исключение, если служебная информация не найдена.
     // Возвращается - информация успешно прочитана.
     virtual bool Read_Beginning( bool excp=false )=0;
     virtual void Write_Beginning(void)=0;

     virtual int Bits_Per_Char(void) const { LEM_STOPIT; return -1; }
     virtual const char* GetFormat(void) const=0;

     virtual wchar_t wget(void);
     virtual void wput( wchar_t ) { LEM_STOPIT; }
     virtual void wputs( const wchar_t *str );
     virtual void wputs( const lem::UFString &str );
     virtual void wputs( const std::wstring &str );

     virtual bool eof(void) const;

     virtual int get(void);
     virtual void put( char );

     // Read the whole line from the stream (untill '\n')
     virtual bool read_line( UFString &buffer );

     // Текст целиком загружается в буфер
     virtual void read_text( UFString &buffer ); 

     virtual void unget( wchar_t ch );

     virtual wchar_t wpeek(void);

     virtual void flush(void);
     virtual pos_type tellp(void) const;
     virtual pos_type seekp( off_type pos, int whereto=SEEK_SET );
     virtual bool move( off_type offset );
     virtual void close(void);
     virtual pos_type fsize(void) const;

     virtual void SetEncoding( const CodeConverter *Cp );
     virtual const CodeConverter* GetEncoding(void) const;

     void StripDecoration( bool f );

     bool skip_white(void);
     bool skip_white2(void);
   };

   typedef lem::Ptr<WideStream> WideStreamPtr;

   // **************************************************************************
   // Ридер ASCII-текста. 1 байт на символ. Для получения UNICODE используются
   // кодовые таблицы
   // **************************************************************************
   class Char_Reader : public WideStream
   {
    private:
     char format[32]; // для хранения строки описания формата

    protected:
     virtual wchar_t Read_Char(void);

    public:
     Char_Reader( StreamPtr Bin );
     Char_Reader( StreamPtr Bin, const CodeConverter *Cp );

     virtual void wput( wchar_t u );

     virtual void Write_Beginning(void) {}
     virtual bool Read_Beginning( bool /*excp*/=false ) { return true; }
     virtual int Bits_Per_Char(void) const { return 8; }

     virtual void SetEncoding( const CodeConverter *CP );

     virtual int get(void);
     virtual void put( char );

     virtual const char* GetFormat(void) const;
   };



   class Translit_Reader : public WideStream
   {
    private:
     lem::Ptr<lem::Transliterator> translit;

    protected:
     virtual wchar_t Read_Char(void);

    public:
     Translit_Reader( StreamPtr Bin, lem::Ptr<Transliterator> Translit );

     virtual void wput( wchar_t u );

     virtual void Write_Beginning(void) {}
     virtual bool Read_Beginning( bool /*excp*/=false ) { return true; }
     virtual int Bits_Per_Char(void) const { return 16; }

     virtual int get(void);
     virtual void put( char );

     virtual const char* GetFormat(void) const;
   };



   class Char_Reader_Lang : public Char_Reader
   {
    private:
     const Lang_Filter *filter;
     virtual wchar_t Read_Char(void);

    public:
     Char_Reader_Lang( StreamPtr Bin, const Lang_Filter *Filter )
      : Char_Reader(Bin) { filter=Filter; }
   };


   #if defined LEM_ICU
   class ICU_Reader : public WideStream
   {
    private:
     UConverter *convfrom;
     UErrorCode err;
     UBool do_flush;
     const char *cbufp, *prevbufp;
     char *bufp;

     UChar *unibuf; // буфер перекодированных в Unicode символов
//     const UChar *unibufbp;
     UChar *unibufp;

//     size_t rd, wr;
//     UBool useOffsets;

     int buf_offset;
//     Stream::pos_type rd;

     int out_len; // number of chars in out buffer
     int i_out; // out buffer current position

     void Clear_Fields(void);

     // Преобразуется очередная порция символов и запоминается в выходном
     // буфере для посимвольной выдачи.
     void Fill_Buffer(void);

    protected:
     size_t bufsz;

     char *buf; // буфер считанных из файла байтов
     Stream::pos_type buf_begpos; // начало байтов буфера в файле
     int32_t *fromoffsets;

     char format[48]; // для хранения строки описания формата

     void setBufferSize( size_t bufferSize );

    public:
     ICU_Reader( const CodeConverter *Encoding, StreamPtr Bin );

     virtual ~ICU_Reader(void);

     virtual void wput( wchar_t u ) { LEM_STOPIT; }

     virtual void Write_Beginning(void) { LEM_STOPIT; }
     virtual bool Read_Beginning( bool excp=false ) { return true; }
     virtual int Bits_Per_Char(void) const { return 16; }

     virtual void SetEncoding( const CodeConverter *CP ) { LEM_STOPIT; }

     virtual int get(void);
     virtual void put( char ) { LEM_STOPIT; }

     virtual wchar_t Read_Char(void);
     virtual const char* GetFormat(void) const;

     virtual void flush(void);
     virtual pos_type tellp(void) const;
     virtual pos_type seekp( off_type pos, int whereto=SEEK_SET );
     virtual bool eof(void) const;
   };
   #endif

   class UTF16_Reader : public WideStream
   {
    protected:
     virtual wchar_t Read_Char(void);
     
    public:
     UTF16_Reader( WideStreamType t, StreamPtr Bin );

     virtual int Bits_Per_Char(void) const { return 16; }
     virtual void Write_Beginning(void);
     virtual bool Read_Beginning( bool excp=false );

     virtual void wput( wchar_t u );

     virtual const char* GetFormat(void) const;
   };


   class UTF16_Reader_Lang : public UTF16_Reader
   {
    protected:
     const Lang_Filter *filter;
     virtual wchar_t Read_Char(void);
     
    public:
     UTF16_Reader_Lang( WideStreamType t, StreamPtr Bin, const Lang_Filter *Filter )
      : UTF16_Reader(t,Bin) { filter=Filter; }

     UTF16_Reader_Lang( StreamPtr Bin, const Lang_Filter *Filter )
      : UTF16_Reader(SET_UTF16,Bin) { filter=Filter; }
   };


   class UTF16_MemWriter : public UTF16_Reader
   {
    private:
     UFString *res; // В эту строку записываются символы
     virtual wchar_t Read_Char(void) { LEM_STOPIT; LEM_NO_RET(0); }
     
     UTF16_MemWriter( const UTF16_MemWriter& );
     void operator=( const UTF16_MemWriter& );

    public:
     UTF16_MemWriter(void);
     virtual ~UTF16_MemWriter(void);

     virtual bool Read_Beginning( bool excp=false );

     virtual void wput( wchar_t u );

     virtual int get(void)  { LEM_STOPIT; LEM_NO_RET(0); }

     // Возвращает накопленный результат записи. При этом контроль над указателем
     // переходит к вызвавшему коду, а поток создает новый буфер записи.
     UFString* Pick_String(void);
     const UFString& string(void) const;
     void clear(void);
   };


   // **********************************************
   // Класс для чтения UNICODE-символов из памяти
   // **********************************************
   class UTF16_MemReader : public UTF16_Reader
   {
    private:
     lem::Ptr<UFString> res; // Из этой строки читаются символы
     int icur; // курсор чтения символов
     bool eof_reached;

    protected:
     virtual wchar_t Read_Char(void);
     
    public:
     UTF16_MemReader( const UFString &Src );
     UTF16_MemReader( const wchar_t * Src );
     UTF16_MemReader( lem::Ptr<UFString> Src );

     virtual void Write_Beginning(void);
     virtual bool Read_Beginning( bool excp=false );
     virtual void wput( wchar_t u );
     virtual bool eof(void) const;

     virtual pos_type seekp( off_type pos, int whereto=SEEK_SET );
     virtual Stream::pos_type fsize(void) const;
     virtual Stream::pos_type tellp(void) const;
     virtual void unget( wchar_t ch );
     virtual wchar_t wpeek(void);
   };


   class UTF16_MemReader_Lang : public UTF16_MemReader
   {
    protected:
     const Lang_Filter *filter;
     virtual wchar_t Read_Char(void);
     
    public:
     UTF16_MemReader_Lang( const UFString &Src, const Lang_Filter *Filter );
   };


   class UTF8_Reader : public WideStream
   {
    protected:
     virtual wchar_t Read_Char(void);
     
    public:
     UTF8_Reader( lem::StreamPtr Bin );
     UTF8_Reader( lem::Stream& Bin );
     UTF8_Reader( const lem::Path &filename, bool for_writing=false );

     virtual int Bits_Per_Char(void) const { return 16; }
     virtual void Write_Beginning(void);
     virtual bool Read_Beginning( bool excp=false );

     virtual void wput( wchar_t u );

     #if defined LEM_WINDOWS
     virtual void wputs( const wchar_t *str );
     #endif

     virtual int get(void);
     virtual void put( char );
     virtual const char* GetFormat(void) const { return "utf8"; }
   };

   class UTF8_Reader_Lang : public UTF8_Reader
   {
    private:
     const Lang_Filter *filter;
     virtual wchar_t Read_Char(void);

     UTF8_Reader_Lang( const UTF8_Reader_Lang& );
     void operator=( const UTF8_Reader_Lang& );
     
    public:
     UTF8_Reader_Lang( StreamPtr Bin, const Lang_Filter * /*Filter*/ )
      : UTF8_Reader(Bin) {}
   };


   class UTF8_MemReader : public UTF8_Reader
   {
    private:
     lem::FString utf8_str;

    public:
     UTF8_MemReader( const lem::FString &str );
     UTF8_MemReader( const char *str );
   };



   // ***************************************************************************
   // Класс для чтения контента из HTML-файлов: отбрасывает html-тэги и выполняет
   // другие перекодировки.
   // ***************************************************************************
   class HTML_Decoder : public WideStream
   {
    protected:
     const CodeConverter *force_cp, *missing_cp;
     lem::zbool utf8;
     lem::zbool all_tags_are_wordbreaker; // для XML документов - любой тэг вносит в поток символов пробельный символ

     #if defined LEM_ICU
     lem::zbool icu;
     #endif

     std::string format_buffer;

     void Open_Stream(void);

     virtual wchar_t get2(void);
     virtual wchar_t Read_Char(void);

    public:
     HTML_Decoder(void);

     HTML_Decoder(
                  StreamPtr File,
                  const CodeConverter *Force_cp=NULL,
                  const CodeConverter *Cp_IfMissing=NULL,
                  bool OpenStream=false
                 );

     virtual int get(void) { LEM_STOPIT; LEM_NO_RET(0); }

     virtual void Write_Beginning(void) {}
     virtual bool Read_Beginning( bool /*excp*/=false ) { return true; }

     virtual int Bits_Per_Char(void) const { return 16; }
     virtual const char* GetFormat(void) const { return format_buffer.c_str(); }

     virtual void wput( wchar_t ) { LEM_STOPIT; }

     HTML_Decoder* Optimize(void);
   };


   // ***********************************************
   // Оптимизированный для UTF8 декодер HTML.
   // ***********************************************
   class HTML_UTF8_Decoder : public HTML_Decoder
   {
    private:
     virtual wchar_t get2(void);

    public:
     HTML_UTF8_Decoder(void);
     HTML_UTF8_Decoder( StreamPtr File );
   };

   #if defined LEM_ICU
   // Универсальный декодер HTML - с расширенной поддержкой кодировок.
   // Работает медленее, чем базовый класс для однобайтовых кодировок.
   class HTML_ICU_Decoder : public HTML_Decoder
   {
    private:
     virtual wchar_t get2(void);

     ICU_Reader *icu_reader;

    public:
     HTML_ICU_Decoder( StreamPtr File );
     virtual ~HTML_ICU_Decoder(void);

     virtual pos_type seekp( off_type pos, int whereto=SEEK_SET );
   };
   #endif


   // *************************************************************
   // Класс для чтения текстовой информации из файла формата RTF.
   // *************************************************************
   class RTF_Decoder : public WideStream
   {
    private:
     typedef struct char_prop
     {
      char fBold;
      char fUnderline;
      char fItalic;
     } CHP;                  // CHaracter Properties

     typedef enum {justL, justR, justC, justF } JUST;

     struct PAP
     {
      int xaLeft;                 // left indent in twips
      int xaRight;                // right indent in twips
      int xaFirst;                // first line indent in twips
      JUST just;                  // justification
      const lem::CodeConverter* encoding; // text encoding for paragraph (added by Koziev Elijah)

      PAP(void);
     };                  // PAragraph Properties

     typedef enum {sbkNon, sbkCol, sbkEvn, sbkOdd, sbkPg} SBK;
     typedef enum {pgDec, pgURom, pgLRom, pgULtr, pgLLtr} PGN;
     typedef struct sect_prop
     {
      int cCols;                  // number of columns
      SBK sbk;                    // section break type
      int xaPgn;                  // x position of page number in twips
      int yaPgn;                  // y position of page number in twips
      PGN pgnFormat;              // how the page number is formatted
     } SEP;                  // SEction Properties

     struct DOP
     {
      int xaPage;                 // page width in twips
      int yaPage;                 // page height in twips
      int xaLeft;                 // left margin in twips
      int yaTop;                  // top margin in twips
      int xaRight;                // right margin in twips
      int yaBottom;               // bottom margin in twips
      int pgnStart;               // starting page number in twips
      char fFacingp;              // facing pages enabled?
      char fLandscape;            // landscape or portrait??
      const lem::CodeConverter* encoding; // text encoding (added by Koziev Elijah)

      DOP(void);
     };                  // DOcument Properties

     typedef enum { rdsNorm, rdsSkip } RDS;              // Rtf Destination State
     typedef enum { risNorm, risBin, risHex } RIS;       // Rtf Internal State

     typedef struct save             // property save structure
     {
      struct save *pNext;         // next save
      CHP chp;
      PAP pap;
      SEP sep;
      DOP dop;
      RDS rds;
      RIS ris;
     } SAVE;

     // What types of properties are there?
     typedef enum {ipropBold, ipropItalic, ipropUnderline, ipropLeftInd,
              ipropRightInd, ipropFirstInd, ipropCols, ipropPgnX,
              ipropPgnY, ipropXaPage, ipropYaPage, ipropXaLeft,
              ipropXaRight, ipropYaTop, ipropYaBottom, ipropPgnStart,
              ipropSbk, ipropPgnFormat, ipropFacingp, ipropLandscape,
              ipropJust, ipropPard, ipropPlain, ipropSectd,
              ipropMax } IPROP;

     typedef enum {actnSpec, actnByte, actnWord} ACTN;
     typedef enum {propChp, propPap, propSep, propDop} PROPTYPE;

     typedef struct propmod
     {
      ACTN actn;              // size of value
      PROPTYPE prop;          // structure containing value
      int  offset;            // offset of value from base of structure
     } PROP;

     typedef enum { ipfnBin, ipfnHex, ipfnSkipDest, ipfnCpg } IPFN;
     typedef enum { idestPict, idestSkip } IDEST;
     typedef enum { kwdChar, kwdDest, kwdProp, kwdSpec} KWD;

     typedef struct symbol
     {
      char *szKeyword;        // RTF keyword
      int  dflt;              // default value to use
      bool fPassDflt;         // true to use default value from this table
      KWD  kwd;               // base action to take
      int  idx;               // index into property table if kwd == kwdProp
                              // index into destination table if kwd == kwdDest
                              // character to print if kwd == kwdChar
     } SYM;

     // RTF parser error codes
     enum {
                    ecOK, // Everything's fine!
                    ecStackUnderflow,       // Unmatched '}'
                    ecStackOverflow,       // Too many '{' -- memory exhausted
                    ecUnmatchedBrace,       // RTF ended during an open group.
                    ecInvalidHex,       // invalid hex character found in data
                    ecBadTable,       // RTF table (sym or prop) invalid
                    ecAssertion,       // Assertion failure
                    ecEndOfFile   // End of file reached while reading RTF
                   };

     static PROP rgprop[ ipropMax ];
     static SYM rgsymRtf[];
     static int isymMax;

    private:
     // это кэш-буфер, в котором накапливается порция
     // выделенных из RTF-файла символов, вместе с позицией
     // каждого символа.
     MCollect< std::pair<wchar_t,Stream::pos_type> > buffer;
                               
     int icur; // положение курсора чтения в буфере.
     Stream::pos_type last_char_pos; // позиция в файле последнего считанного символа

     void Fill_Buffer(void);

     virtual wchar_t Read_Char(void);

     int BUFFER_SIZE; // максимальный размер буфера
     int error; // индикатор ошибок парсера
     bool eof_reached; // достигнут конец файла (с учетом кэша).

     int cGroup;
     bool fSkipDestIfUnk;
     long cbBin;
     long lParam;

     RDS rds;
     RIS ris;

     CHP chp;
     PAP pap;
     SEP sep;
     DOP dop;

     SAVE *psave;

     int ecApplyPropChange( IPROP iprop, int val );
     int ecParseSpecialProperty( IPROP iprop, int val );
     int ecTranslateKeyword( char *szKeyword, int param, bool fParam );
     int ecChangeDest(IDEST idest);
     int ecEndGroupAction(RDS rds);
     int ecParseSpecialKeyword(IPFN ipfn);
     int ecPushRtfState(void);
     int ecPopRtfState(void);
     int ecParseRtfKeyword(void);
     int ecParseChar(int ch);
     int ecPrintChar( int ch );

    public:
     RTF_Decoder( StreamPtr File );
     virtual ~RTF_Decoder(void);

     virtual bool eof(void) const { return eof_reached || error!=ecOK; }

     virtual void Write_Beginning(void) {}
     virtual bool Read_Beginning( bool /*excp*/=false ) { return true; }

     virtual int Bits_Per_Char(void) const { return 16; }
     virtual const char* GetFormat(void) const { return "rtf"; }

     virtual void wput( wchar_t ) { LEM_STOPIT; }

     virtual pos_type tellp(void) const { return last_char_pos; }
   };



  class XLS_Decoder : public HTML_UTF8_Decoder
  {
   private:
    lem::Path tmp_file; // файл с временным HTML содержимым,
                        // деструктор должен его удалить

    lem::Path tmp_src; // временный файл с копией XLS, используется если
                       // обрабатывался не дисковый файл.


    std::auto_ptr<lem::OUFormatter> dump_utf8;

    #if defined LEM_WINDOWS
    CRITICAL_SECTION cs;
    #endif

    void Clear_Fields(void);

    void Dump_XLS( 
                  const FString &filename,
                  lem::Stream &dump // destination stream
                 );

   public:
    XLS_Decoder( StreamPtr File );

    virtual ~XLS_Decoder(void);

    // Загружает в предоставленный буффер максимум len символов
    void ReadChunk( UFString &text, int len );
  };


  } // namespace Char_Reader

 } // namespace lem

#endif
