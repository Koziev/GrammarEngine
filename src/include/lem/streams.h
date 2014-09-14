#ifndef LEM_BSTREAM__H
#define LEM_BSTREAM__H
#pragma once

// File STREAMS.H
//
// (c) by Elijah Koziev    all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ supplementary library
//
// This header contains declarations of the stream classes which provide
// flexible input/output abstractions for byte character streams as well as
// concrete classes for reading and writing disk files, console and keyboard,
// and memory mapped files.
//
// Бинарные потоки ввода-вывода, в том числе - дисковые файлы. Классы данного
// раздела иногда перекрывают по возможностям классы библиотеки iostreams C++,
// но не отменяют и не заменяют их - разумно использовать их параллельно.
// Обращаю внимание, что используется много виртуальных методов, перегружаемых
// в классах-потомках.
//
// 07.01.2006 - для отладки использован класс Guardian (см. runtime_checks.h).
//
// 05.04.2006 - в базовый класс Stream добавлена константа eof_pos - числовое
//              представление позиции курсора чтения ВНЕ файла.
//
// 30.05.2006 - в базовый класс Stream добавлен виртуальный метод
//              IsDiskFile, который позволяет выяснить, является ли поток
//              реальным дисковым файлом.
//
// 06.11.2006 - введена поддержка операций с файлами > 2Gb
//
// 05.01.2007 - введены методы rewind(), to_end()
//
// 14.04.2007 - для совместимости с gcc введена статическая константа fpos64_t(0)
//
// 24.05.2007 - метод move возвращает bool признак успешности перемещения, а
//              не новую позицию в файле, так как fseek возвращает именно этот
//              признак. 
//
// 20.06.2007 - введен класс UrlFile для чтения с веб-серверов.
//
// 04.08.2007 - рефакторинг: переименование BaseStream в Stream
// 20.06.2008 - добавлены классы BinaryReader и BinaryWriter
// 19.07.2008 - refactoring: часть реализации методов перенесена в *.cpp модули
//              для разгрузки хидера.
// 08.10.2009 - добавлен класс BinaryUpdater
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->08.10.2009
// --------------

 #include <lem/config.h>

 #if defined LEM_MFC
  #include <afxwin.h>
 #endif

 #if defined LEM_WINDOWS
 #include <io.h>
 #endif

 #include <string>
 #include <iostream>
 #include <fstream>

 #include <boost/noncopyable.hpp>

 #include <stdio.h>
 #include <lem/cstring.h>
 #include <lem/path.h>
 #include <lem/runtime_checks.h>
 #include <lem/date_time.h>

 #if !defined LEM_SMART_REF__H
//  #include <lem/smart_pointers.h>
 #endif
 
 #if defined LEM_WINDOWS
  #include <wininet.h>
//  #include <mmsystem.h>
 #endif

 #if defined move
  #undef move
 #endif

 #if !defined LEM_WATCOM
  using std::string;
  using std::wstring;
  using std::ostream;
  using std::fstream;
 #endif

 namespace lem
 {
  // ********************************************************************
  // Базовый класс для файлов (потоков ввода-вывода) различных типов.
  // Абстрактный класс - содержит много чистых виртуальных методов. Я не
  // стал делать его настоящим интерфейсом, так как практической пользы
  // такого архитектурного решения в рамках вспомогательной библиотеки
  // не будет.
  // ********************************************************************
  class Stream : boost::noncopyable
  {
   protected:
    #if LEM_DEBUGGING==1
    Guardian guard1;
    #endif

   private:
    lem::zbool readable, writable; // Права на работу с потоком: чтение и запись
                                   // Stream access flags

   protected:
    lem::zbool closable; // Должен ли деструктор закрывать системные handles потока
    lem::zbool binary;   // В двоичном режиме
    lem::zbool seekable; // можно ли свободно перемещать указатель записи-чтения
                         // does the stream allow random access

    lem::Path name; // Имя потока, обычно - имя файла
                    // Disk file full path


   protected:
    #if LEM_DEBUGGING==1
    Guardian guard2;
    #endif

    // Проверки перед чтением и записью - можно ли так работать с потоком.
    inline void CheckWritable(void) const { LEM_CHECKIT_Z(!!writable); }
    inline void CheckReadable(void) const { LEM_CHECKIT_Z(!!readable); }

    inline void SetMode( bool Readable, bool Writable, bool Seekable=true )
    { readable=Readable; writable=Writable; seekable=Seekable; }

    inline void SetName( const lem::Path &FileName ) { name=FileName; }

    #if LEM_DEBUGGING==1
    inline void Assert(void) const
    {
     guard1.Assert();
     guard2.Assert();
    }
    #endif

    public:
     typedef size_t pos_type; // Положение курсора чтения/записи
                              // (обычно для дисковых файлов).
 
     typedef int off_type; // Смещение курсора (нужен знаковый тип).

     enum { eof_pos=0xffffffffUL }; // позиция "вне файла"

     #if defined LEM_FILE64
     // Поддержка операций с файлами > 2Gb
     typedef fpos_t pos64_type;
     typedef fpos_t off64_type;
     #else
     typedef size_t pos64_type;
     typedef size_t off64_type;
     #endif

   public:
    Stream( bool Readable=true, bool Writable=true );
    Stream( bool Readable, bool Writable, const lem::Path &Name );

    virtual ~Stream(void);

    // Запись блока информации, на который указывает src, размером size, в
    // поток с текущей позиции.
    virtual void write( const void *src, pos_type size )=0;

    // Чтение блока информации в область памяти, на которую указывает dest,
    // размером size, с текущей позиции.
    // Возвращается реально прочитанное число байтов. 
    virtual pos_type read( void *dest, pos_type size )=0;

    // Готовы ли данные для считывания или готов ли канал принимать данные?
    // Имеет смысл для потоков, которые работают с устройствами типа
    // клавиатуры или сетью.
    virtual bool isready(void) const;

    // Ждем готовности канала данных.
    virtual void wait_ready(void) const;

    // Чтение единичного символа. Может возвращать EOF (-1) при достижении
    // конца файла. Автоматически смещает курсор к концу файла.
    virtual int get(void)=0;

    inline int operator()(void) { return get(); }

    // Вписывает символ в текущую позицию в файле.
    virtual void put( char )=0;

    virtual void puts( const char *s );

    virtual void unget( char c );
    
    // Чтение из потока UNICODE-символа.
    virtual wchar_t wget(void);

    // Запись в поток UNICODE-символа
    virtual void wput( wchar_t );

    // Запись в поток UNICODE-строки
    virtual void wputs( const wchar_t *str );

    // Запись int и bool значений
    void write_int(  int d );
    void write_bool( bool d );
    void write_uint8( lem::uint8_t d );

    void wr( const CString* s );
    void wr( const FString* s );
    void wr( const UCString* s );
    void wr( const UFString* s );
    void wr( const string* s );
    void wr( const wstring* s );
    void wr( const int* i );
    void wr( const bool* i );
    void wr( const char* str );

    void wr( const float* i );
    void wr( const double* i );
    void wr( const long double* i );

    void rd( CString* s );
    void rd( FString* s );
    void rd( UCString* s );
    void rd( UFString* s );
    void rd( std::string* s );
    void rd( wstring* s );
    void rd( int* i );
    void rd( bool* i );
    void rd( char* str );

    void scan_str( char* str, int nmax );

    void rd( float* i );
    void rd( double* i );
    void rd( long double* i );

    int read_int(void);
    bool read_bool(void);
    lem::uint8_t read_uint8(void);

    const CString read_string(void);
    const FString read_fstring(void);
    const UCString read_ustring(void);
    const UFString read_ufstring(void);

    virtual const lem::Path& GetName(void) const;

    // Проверка текущего состояния потока - не было ли ошибок в предыдущих
    // операциях. Если были, то обычно выдается сообщение на экран или
    // генерируется исключение.
    virtual void Check(void) const;

    // Синхронизация буферов файла с диском.
    virtual void flush(void)=0;

    // Вернет true, если при чтении достигнут конец файла.
    virtual bool eof(void) const=0;

    // Возвращает текущую позицию курсора в потоке.
    virtual pos_type tellp(void) const=0;

    virtual pos64_type tellp64(void) const;

    // Перемещает курсор на заданную позицию: отсчитываем позицию от начала
    // файла, текущей позиции или конца файла, согласно константе where_to.
    // Для справки - см. описание стандартной функции fseek(...).
    virtual pos_type seekp( off_type pos, int whereto=SEEK_SET )=0;

    // Перемотка потока (установка курсора) в начало.
    virtual void rewind(void); 

    // Перемотка потока в конец.
    virtual void to_end(void); 

    virtual pos64_type seekp64( off64_type pos, int whereto=SEEK_SET );

    // Перемещение курсора относительно текущей позиции, к началу или к концу
    // файла согласно знаку смещения offset.
    virtual bool move( off_type offset )=0;

    // Сбрасывает буфера вывода и закрывает поток.
    virtual void close(void)=0;

    // Возвращает текущий размер потока.
    virtual pos_type fsize(void) const=0;

    virtual lem::uint64_t fsize64(void) const;

    // Управление цветовыми атрибутами при выводе на терминалы...
    // Для большинства потоков эти методы пусты, только для терминальных
    // потоков они определены при условии специальной поддержки (типа ncurses)
    virtual void SetForeGroundColor( int /*iColor*/ );
    virtual void SetBackGroundColor( int /*iColor*/ );
    virtual void SetBlinkMode( bool /*blinks*/ );
    virtual void SetHighLightMode(void);
    virtual void SetLowLightMode(void);
    virtual void SetNormalMode(void);

    // Вернет true, если при открытии потока или работе с ним возникла ошибка и
    // не было сгенерировано исключение
    virtual bool is_failed(void) const;

    // Возвращает признак бинарности потока.
    inline bool IsBinary(void) const
    {
     #if LEM_DEBUGGING==1
     Assert();
     #endif
     return binary;
    }

    // Устанавливает внутренний флаг возможности закрытия потока при
    // срабатывании деструктора класса.
    inline void SetClosable( bool f )  { closable=f; }

    inline bool CanWrite(void) const { return writable; }
    inline bool CanRead(void)  const { return readable; }
    inline bool CanSeek(void)  const { return seekable; }


    // Вернет TRUE если поток работает с реальным дисковым файлом
    virtual bool IsDiskFile(void) const;

    // Возвращает время создания и последней модификации файла
    virtual bool GetTimes(
                          boost::posix_time::ptime &creat,
                          boost::posix_time::ptime &modif
                         );

   // Отключает буферизацию ввода-вывода (если поток ее использует).
   virtual void NoBuffer(void);

   // Если поток поддерживает вывод широких символов через wput и wputs, то вернет >8,
   // иначе 8 - однобайтовый поток. 
   virtual int Bits_Per_Char(void) const;
  };


 //typedef lem::Ptr<Stream> StreamPtr;


 // ********************************************
 // Обычный дисковый файл (через FILE-функции C).
 // ********************************************
 class BinaryFile : public Stream
 {
  protected:
   FILE *file;

   #if LEM_DEBUGGING==1
   Guardian guard3; 
   #endif

   static int n_opened; // Для отладочных целей - счетчик открытых файлов.

   #if LEM_DEBUGGING==1
   inline void Assert(void) const
   {
    #if defined LEM_MSC && _MSC_VER<1300
    // ...
    #else
    lem::Stream::Assert();
    #endif
     
    guard3.Assert();
   }
   #endif

   void OpenDiskFile( const char *amode, const wchar_t *umode, bool do_throw );

  public:
   BinaryFile(void);
   BinaryFile( const lem::Path &filename );
   BinaryFile( FILE *f );
   BinaryFile( FILE *f, const lem::Path &filename );

   BinaryFile(
              const lem::Path &filename,
              bool for_read,
              bool for_write,
              bool for_append=false,
              bool text_mode=false,
              bool do_throw=true
             );

   BinaryFile(
              FILE *File,
              bool for_read,
              bool for_write,
              bool for_append=false,
              bool text_mode=false
             );

   // Деструктор обязательно закроет поток, если он остался открыт.
   ~BinaryFile(void);


   virtual void reopen( 
                       bool for_read,
                       bool for_write,
                       bool for_append=false,
                       bool text_mode=false,
                       bool do_throw=true      // по умолчанию генерируется исключение, если файл не открывается
                      );

   virtual bool is_failed(void) const;

   virtual void write( const void *src, pos_type size );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get(void);
   virtual void put( char ch );

   virtual void unget( char c );
   inline FILE* GetStream(void) { return file; }

   virtual void Check(void) const;
   virtual void flush(void);
   virtual bool eof(void) const;
   virtual pos_type tellp(void) const;
   virtual pos_type seekp( off_type to, int whereto=SEEK_SET );
   virtual bool move( off_type offset );
   virtual pos64_type tellp64(void) const;
   virtual pos64_type seekp64( off64_type to, int whereto=SEEK_SET );
   virtual lem::uint64_t fsize64(void) const;

   virtual void close(void);

   virtual pos_type fsize(void) const;

   virtual bool GetTimes(
                         boost::posix_time::ptime &creat,
                         boost::posix_time::ptime &modif
                        );

   virtual bool IsDiskFile(void) const;

   // отмена буферизации (setvbuf).
   virtual void NoBuffer(void);
 };


 class BinaryReader : public BinaryFile
 {
  public:
   BinaryReader( const Path& filename );
 };

 class BinaryWriter : public BinaryFile
 {
  public:
   BinaryWriter( const Path& filename );
 };

 class BinaryUpdater : public BinaryFile
 {
  public:
   BinaryUpdater( const Path& filename );
 };


 // *******************************************
 // Дисковый файл с текстовым режимом.
 // *******************************************
 class TextFile : public BinaryFile
 {
  public:
   TextFile(void);
   TextFile(
            const Path& filename,
            bool for_read,
            bool for_write,
            bool for_append=false
           );


   // Read characters till EOL ('\n') reached, return collected
   // string.
   const FString read_till_eol(void);
 };


 class TextReader : public TextFile
 {
  public:
   TextReader(void);
   TextReader( const Path& filename );
 };

 class TextWriter : public TextFile
 {
  public:
   TextWriter(void);
   TextWriter( const Path& filename );
 };


 class StdTtyStream : public Stream
 {
  protected:
   ostream *stream;

  public:
   StdTtyStream(void);
   StdTtyStream( std::ostream *s );

   virtual void write( const void *src, pos_type size );
   virtual void put( char Ch );
   virtual pos_type read( void * /*dest*/, pos_type /*size*/ );
   virtual int get(void);

   inline operator ostream*(void) { return stream; }
   inline ostream* GetStream(void) { return stream; }

   virtual void Check(void) const;
   virtual void flush(void);
   virtual void close(void);
   virtual bool eof(void) const;
   virtual pos_type tellp(void) const;
   virtual pos_type seekp( off_type /*to*/, int /*whereto*/=SEEK_SET );
   virtual bool move( off_type /*offset*/ );
   virtual pos_type fsize(void) const;
 };

 // ******************************************************************
 // Дисковые файлы, основанные на стандартном потоковом классе fstream
 // ******************************************************************
 class StdFileStream : public Stream
 {
  protected:
   fstream *stream;
   bool do_del;          // можно ли в деструкторе удалять объект stream.

  public:
   StdFileStream(void);
   StdFileStream( fstream *Stream );
   StdFileStream(
                 const Path& filename,
                 bool for_read,
                 bool for_write,
                 bool for_append=false
                );

   virtual ~StdFileStream(void);
   virtual void write( const void *src, pos_type size );
   virtual void put( char Ch );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get(void);
   virtual void Check(void) const;
   virtual void flush(void);
   virtual void close(void);
   virtual bool eof(void) const;
   virtual pos_type tellp(void) const;
   virtual pos_type seekp( off_type /*to*/, int /*whereto*/=SEEK_SET );
   virtual bool move( off_type offset );
   virtual pos_type fsize(void) const;
 };

 // *********************************************************************
 // Поток с побитовым режимом обмена. Это не производный от Stream
 // класс, поэтому его интерфейс несовместим с Stream. Причина -
 // необходимость манипулирования отдельными битами.
 //
 // В качестве потока для вывода или ввода байтов используется объект
 // класса Stream.
 // *********************************************************************
 class BitStream
 {
  protected:
   unsigned char mask;
   unsigned char rack;

   Stream *stream;
   bool del; // удалять ли stream в деструкторе класса.

  public:
   BitStream(void);
   BitStream( Stream *Stream, bool Delete_Stream );

   ~BitStream(void);

   void OutputBit( int bit );
   void OutputBits( unsigned int bits, int bit_count );
   void put( char c ) { OutputBits( (unsigned char)(c), 8 ); }

   int InputBit(void);
   unsigned int InputBits( int bit_count );
   int get(void) { return int(0x000000ffUL&InputBits(8)); }

   // Этот метод не применим в общем случае, так как если записано количество
   // бит, не выравненное на границу байта, то запись цепочки байтов приведет
   // фактически к появлению нулевых битов в конце.
   void flush(void)
   {
    if( mask!=0x80 )
     {
      put(rack);
      mask=0x80;
     }
   }

   inline bool eof(void) { return stream->eof(); }

   inline Stream* GetStream(void) { return stream; }
 };



 /**************************************************************************
                         Область памяти.

  Выполняет также роль класса-контейнера для символов. Если записать
  очередной байт в отведенную область памяти не удается, то эта область
  увеличивается на величину шага. Ответственность по освобождению выделенной
  памяти лежит на пользователе.
 ***************************************************************************/

 class MemStream : public lem::Stream
 {
  protected:
   // Указатель на указатель блок памяти c информацией.
   // Внимание: это НЕ null-terminated string!!!
   char **block;

   #if LEM_DEBUGGING==1
   Guardian guard4;
   #endif

   char *w_block;   // Вспомогательный блок - для записи

   #if LEM_DEBUGGING==1
   Guardian guard5;
   #endif

   size_t cursor;    // Указатель на след. байт
   size_t step;      // Шаг увеличения блока памяти.
   size_t size;      // Полный размер блока
   size_t occupied;  // Сколько байтов занято в блоке реальной информацией
   lem::zbool allocatable; // Можно ли изменять размеры блока

   void reallocate( size_t new_size );
   void reallocate(void); // Увеличение блока памяти.

   #if LEM_DEBUGGING==1
   inline void Assert(void) const
   {
    #if !defined LEM_MSC || _MSC_VER>=1300
    lem::Stream::Assert();
    #endif
     
    guard4.Assert();
    guard5.Assert();
   }
   #endif

  public:
   MemStream(void);

   MemStream(
             char **Block,
             bool for_read,
             bool for_write,
             size_t Size=0,
             size_t Step=65536
            );

   MemStream( bool for_write );

   ~MemStream(void);

   void SetReadable(void);

   virtual void write( const void *src, pos_type size );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get(void);
   virtual void put( char ch );
   virtual void unget( char c );

   virtual void Check(void) const;

   virtual void flush(void);

   void clear(void);

   char* PickBlock(void);

   const FString string(void) const;

   virtual const char* get_Block(void) const;

   virtual bool eof(void) const;

   virtual pos_type tellp(void) const;

   virtual pos_type seekp( lem::Stream::off_type to, int whereto=SEEK_SET );

   virtual bool move( lem::Stream::off_type offset );

   virtual void close(void);
   virtual pos_type fsize(void) const;
 };


 // *******************************************************************
 // Производный класс для организации потокового чтения из заданной
 // области памяти. Это обычно необходимо для парсинга текстовой строки,
 // введенной к примеру с терминала.
 // *******************************************************************
 class MemReadStream : public MemStream
 {
  private:
   const char *rblock; // Указатель на блок памяти c информацией

  public:
   MemReadStream( const char *rBlock );
   MemReadStream( const void *rBlock, size_t Size );

   virtual pos_type read( void *dest, pos_type size );
   virtual int get(void);
   virtual void unget( char c );

   virtual bool eof(void) const { return cursor>=size; }

   virtual pos_type tellp(void) const { return (long)cursor; }

   virtual void close(void) {};
   virtual pos_type fsize(void) const { return size; }
   virtual void Check(void) const { LEM_CHECKIT_Z(rblock!=NULL); }
   virtual const char* get_Block(void) const { return (const char*)rblock; }
   virtual pos_type seekp( lem::Stream::off_type to, int whereto=SEEK_SET );
 };


 // ***************************************************
 // Sound OUTLET Stream
 // Поток для вывода звуковых данных.
 // ***************************************************
 /*
 class SoundOStream : public Stream
 {
  private:
   FString snd_tmp_fname; // Имя временного файла, куда мы сбросили звукозапись.
   Collect<UINT8*> Fragment; // Список указателей на блоки для воспроизведения.
   Collect<size_t> Size; // Список размеров блоков.

   bool CanBeVocalized(void) const;
   void DoVoiceThemDirectly(void);
   void ForgetFragments(void);

  public:
   SoundOStream(void);
   ~SoundOStream(void);

   virtual bool isready(void) const { return CanBeVocalized(); }

   const FString Play(void);

   void Do_Play_File( const FString &filename );
   void DoVocalize( const char *filename );

   virtual void write( const void *src, size_t size );
   virtual void flush(void);

   virtual void read( void *dest, size_t size ) {};
   virtual int get(void) { return 0; }
   virtual void put( int ch );
   virtual bool eof(void) const { return false; }
   virtual size_t tellp(void) const { return 0; }
   virtual size_t seekp( size_t pos, int whereto=SEEK_SET )
   { return (size_t)-1; }

   virtual bool move( size_t offset ) { return false; }
   virtual void close(void) {};
   virtual size_t fsize(void) const { return 0; }
 };
*/

 // *************************************************************
 // Sound INLET Stream
 // Поток для считывания звуковых данных с внешнего устройства.
 // *************************************************************
 /*
 class SoundIStream : public Stream
 {
  private:
   BaseFString<char> snd_tmp_fname; // Имя временного файла, куда мы поместим звукозапись.
   BinaryFile *record; // Сформированный файл со звуком.

   void Open(void);
   void DoRecord(void);

  public:
   SoundIStream(void);
   ~SoundIStream(void);

   void Record_If_Needed( bool forced );

   virtual bool isready(void) const;
   virtual void read( void *src, size_t size );
   virtual void flush(void);

   virtual int get(void) { return 0; }

   virtual void write( const void *src, size_t size );
   virtual void put( int ch );

   virtual bool eof(void) const;
   virtual size_t tellp(void) const { return (size_t)-1; }
   virtual size_t seekp( size_t pos, int whereto=SEEK_SET ) { return (size_t)-1; }
   virtual bool move( size_t offset ) { return false; }
   virtual void close(void);
   virtual size_t fsize(void) const;
 };
*/

 /*****************************************************************
  Стандартный поток для консоли TTY (печать на алфавитно-цифровом
  терминале или его эмуляции). Физическое устройство терминала роли
  не имеет - мы используем минимальное подмножество сервисных
  функций, которые обычно поддерживаются терминалами.

  Любые операции чтения приведут к исключению - для чтения данных
  с клавиатуры надо использовать std::stdin или lem::KbdStream.
 ******************************************************************/
 class TtyStream : public Stream
 {
  protected:
   #if defined LEM_WINDOWS && !defined LEM_DOT_NET
   int fg, bg; // Foreground and background current colors 
   #endif

   TtyStream( const TtyStream &x );
   void operator =( const TtyStream &x );

  public:
   TtyStream(void);

   virtual ~TtyStream(void);

   virtual void write( const void *src, size_t size );
   virtual pos_type read( void * /*dest*/, size_t /*size*/ );
   virtual int get(void);

   virtual void put( char Ch );
   virtual void puts( const char *s );

   void write_string( const CString& s );
   void write_fstring( const FString& s );

   virtual void flush(void);
   virtual bool eof(void) const;
   virtual lem::Stream::pos_type tellp(void) const;
   virtual lem::Stream::pos_type seekp( off_type /*pos*/, int /*whereto*/=SEEK_SET );
   virtual bool move( off_type /*offset*/ );
   virtual void close(void);
   virtual pos_type fsize(void) const;

   // Управление цветовыми атрибутами при выводе на терминалы...
   virtual void SetForeGroundColor( int iColor );
   virtual void SetBackGroundColor( int iColor );
   virtual void SetBlinkMode( bool blinks );
   virtual void SetHighLightMode(void);
   virtual void SetLowLightMode(void);
   virtual void SetNormalMode(void);
 };


 
 // **********************************************************
 // Basic tty implementation: no colors and other attributes
 // **********************************************************
 class TtyStreamStd : public Stream
 {
  protected:
   TtyStreamStd( const TtyStreamStd &x );
   void operator =( const TtyStreamStd &x );

  public:
   TtyStreamStd(void);

   virtual ~TtyStreamStd(void);

   virtual void write( const void *src, size_t size );
   virtual pos_type read( void * /*dest*/, size_t /*size*/ );

   virtual int get(void);

   virtual void put( char Ch );
   virtual void puts( const char *s );

//   void write_string( const CString& s );
//   void write_fstring( const FString& s );

   virtual void flush(void);
   virtual bool eof(void) const;
   virtual pos_type tellp(void) const;

   virtual pos_type seekp( off_type /*pos*/, int /*whereto*/=SEEK_SET );

   virtual bool move( off_type /*offset*/ );

   virtual void close(void);

   virtual pos_type fsize(void) const;

   virtual void SetForeGroundColor( int iColor );
   virtual void SetBackGroundColor( int iColor );
   virtual void SetBlinkMode( bool blinks );
   virtual void SetHighLightMode(void);
   virtual void SetLowLightMode(void);
   virtual void SetNormalMode(void);
 };

 // ******************************************************
 // ******************************************************
 #if defined LEM_UNICODE_CONSOLE

 #if defined LEM_WINDOWS
 // UNICODE-версия консоли - для MS Windows начиная с W2k
 class TtyUcs2Stream : public TtyStream
 {
  public:
   TtyUcs2Stream(void);

   virtual void wput( wchar_t );
   virtual int Bits_Per_Char(void) const;
 };
 #endif

 // Для вывода на UTF8 консоль под Linux
 #if defined LEM_LINUX || defined LEM_DARWIN
 class TtyUtf8Stream : public TtyStreamStd
 {
  public:
   TtyUtf8Stream(void);

   virtual void put( char Ch );
   virtual void wput( wchar_t );
 };
 #endif

 #endif


 // ****************************************************************
 // Поток для ввода с терминала (или из окна эмуляции терминала).
 // ****************************************************************
 class KbdStream : public Stream
 {
  public:
   KbdStream(void);
   ~KbdStream(void);

   virtual bool isready(void) const;
   virtual const FString read_fstring(void);

   virtual void write( const void * /*src*/, size_t /*size*/ );
   virtual pos_type read( void * /*dest*/, size_t /*size*/ );
   virtual void put( char /*ch*/ );
   virtual int get(void);
   virtual bool eof(void) const;
   virtual pos_type tellp(void) const;
   virtual pos_type seekp( off_type /*pos*/, int /*whereto*/=SEEK_SET );
   virtual bool move( off_type /*offset*/ );
   virtual void close(void);
   virtual pos_type fsize(void) const;
   virtual void flush(void);
 };


 // ********************************************************************
 // Специальный поток выдачи сообщений об ошибках. Может выводить
 // сообщения на терминал, в диалоговые окна и так далее - как принято
 // в конкретной ОС.
 // ********************************************************************
 class ErrStream : public MemStream
 {
  public:
   ErrStream(void):MemStream(true) {}

   virtual void flush(void);
 };

  // ********************************************************************** 
  // Содержимое одного потока целиком копируется в другой поток (или часть,
  // если указано значение size).
  // ********************************************************************** 
  extern void copy_file( lem::Stream &dst, lem::Stream &src, size_t size=0 );

  extern FString* load_whole_file( const lem::Path& filename );
  extern FString* load_whole_file( lem::BinaryFile &bin );

  // Так как реализация под Linux не позволяет непосредственно
  // сравнивать fpos_t с 0, то лучше использовать данную 
  // обертку.
  inline bool fpos64_not_zero( const lem::Stream::pos64_type &p )
  { 
   #if defined LEM_WINDOWS
   return p!=0;
   #else
   const char* pp = (const char*)&p;
   for( size_t i=0; i<sizeof(p); i++ )
    if( pp[i]!=0 )
     return true;

   return false;   
   #endif
  }

  inline void fpos64_clear( lem::Stream::pos64_type &p )
  { 
   #if defined LEM_WINDOWS
   p=0;
   #else
   memset( &p, sizeof(p), 0 );    
   #endif
  }

  
  inline bool fpos64_neq( const lem::Stream::pos64_type &a, const lem::Stream::pos64_type &b )
  { 
   #if defined LEM_WINDOWS
   return a!=b;
   #else
   return !!memcmp( &a, &b, sizeof(a) );
   #endif
  }



 struct ProxyConfig
 {
  typedef enum { NoProxy, AutoProxy, Forced } ProxyType;
  ProxyType type;

  lem::FString ip_port, locals;

  ProxyConfig(void);
  ProxyConfig( const lem::FString &address );
  ProxyConfig( const ProxyConfig &x );
  void operator=( const ProxyConfig &x );

  inline bool IsAuto(void) const { return type==AutoProxy; }
  inline bool IsForced(void) const { return type==Forced; }
  inline bool IsDisabled(void) const { return type==NoProxy; }

  inline void Disable(void) { type = NoProxy; }
 };

 extern ProxyConfig AutoProxy;
 extern ProxyConfig NoProxy;


 // ********************************************
 // Поток для чтения информации с веб-серверов
 // ********************************************
 #if defined LEM_CURL
 struct fcurl_data;
 class UrlFile : public Stream
 {
  protected:
   fcurl_data *file;

  public:
   UrlFile( const lem::Path &url, ProxyType proxy=AutoProxy );
   //UrlFile( const lem::Url &url, ProxyType proxy=AutoProxy );

   // Деструктор обязательно закроет поток, если он остался открыт.
   ~UrlFile(void);

   virtual bool is_failed(void) const;

   virtual void write( const void *src, pos_type size );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get(void);
   virtual void put( char ch );

   virtual void unget( char c );

   virtual void Check(void) const;

   virtual void flush(void);

   virtual bool eof(void) const;

   virtual pos_type tellp(void) const;

   virtual pos_type seekp( off_type to, int whereto=SEEK_SET );

   virtual bool move( off_type offset );

   virtual pos64_type tellp64(void) const;
   virtual pos64_type seekp64( off64_type to, int whereto=SEEK_SET );
   virtual lem::uint64_t fsize64(void) const;

   virtual void close(void);

   virtual pos_type fsize(void) const;

   virtual bool GetTimes(
                         boost::posix_time::ptime &creat,
                         boost::posix_time::ptime &modif
                        );

   virtual bool IsDiskFile(void) const { return false; }
 };

 #elif defined LEM_WINDOWS

 class Url;

 class UrlFile : public MemStream
 {
  public:
 
  protected:
   HINTERNET hInternetSession;
   bool InitSession( const ProxyConfig& proxy );
   void CloseSession(void);

   lem::uint8_t *MemoryBlock;

   void Download( const lem::FString &url );

  public:
   UrlFile( const lem::Path &url, const ProxyConfig& proxy=lem::AutoProxy );
   UrlFile( const lem::Url &url, const ProxyConfig& proxy=lem::AutoProxy );
   ~UrlFile(void);
 };

 #endif


 #if defined LEM_WINDOWS
 // ********************************************
 // Быстрая версия потока для чтения данных из
 // дисковых файлов - через Memory Mapped File.
 // ********************************************
 class FastFileReader : public Stream
 {
  protected:
   HANDLE hFile;
   HANDLE hFileMap;
   lem::uint8_t *OrgAdr; // начальный адрес маппированного файла
   lem::uint8_t *EndAdr; // за-последним байтом
   lem::uint8_t *CurAdr; // текущая позиция курсора для чтения
   LARGE_INTEGER filesize; // размер файла
   
  public:
   FastFileReader( const lem::Path &filename );

   ~FastFileReader(void);

   virtual bool is_failed(void) const;

   virtual void write( const void *src, pos_type size );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get(void);
   virtual void put( char ch );

   virtual void unget( char c );

   virtual void Check(void) const;
   virtual void flush(void);

   virtual bool eof(void) const;

   virtual pos_type tellp(void) const;
   virtual pos_type seekp( off_type to, int whereto=SEEK_SET );

   virtual bool move( off_type offset );
   virtual pos64_type tellp64(void) const;
   virtual pos64_type seekp64( off64_type to, int whereto=SEEK_SET );
   virtual lem::uint64_t fsize64(void) const;
   virtual void close(void);

   virtual pos_type fsize(void) const;
   virtual bool IsDiskFile(void) const;

   #if defined LEM_WINDOWS
   const lem::uint8_t* CurPtr(void) const { return CurAdr; }
   #endif
 };
 #endif


 } // end of namespace 'lem'

#endif
