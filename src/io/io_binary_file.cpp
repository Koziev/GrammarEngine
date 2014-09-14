// -----------------------------------------------------------------------------
// File IO_BINARY_FILE.CPP
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
// Бинарные потоки ввода-вывода: класс BinaryFile - дисковый файл.
//
// 18.04.2007 - введен макрос LEM_FILE64, который определяется в конфигурационных
//              файлах для платформ, поддерживающих 64-битные смещения файлов.
//
// 14.07.2007 - вызов reopen принудительно закрывает поток, если он не был
//              явно закрыт до этого.
//
// 12.04.2008 - исправлена ошибка в GetTimes() - в исключительно редких случаях
//              для аргумента -1 функция localtime возвращает NULL, что приводит
//              затем к Access Violation при преобразованиях времени.  
//
// 20.06.2008 - добавлены классы BinaryReader и BinaryWriter
// 08.10.2009 - добавлен класс BinaryUpdater
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->08.10.2009
// --------------

#include <lem/config.h>

#if defined LEM_WINDOWS
 #include <io.h>
 #include <sys/stat.h>
#endif

#if defined LEM_UNIX
 #include <sys/types.h>
 #include <sys/stat.h>
#endif

#include <lem/system_config.h>
#include <lem/unicode.h>
#include <lem/streams.h>

using namespace lem;

// Для отладки: счетчик открытых файлов.
int BinaryFile::n_opened=0;

/*************************************************************************
 Внимание! Библиотека стандартных процедур компилятора Borland C++ версий
 4.0 и выше (4.0, 4.5, 5.0 C++ Builder) содержит фатальную ошибку. 32-бит
 приложение не должно пользоваться режимом "t" для fopen, так как в
 некоторых случаях процедура ftell возвращает смещённое на 1 положение
 курсора в файле.
**************************************************************************/

BinaryFile::BinaryFile(void):Stream(false,false)
{
 file=NULL;
 closable=false;
 binary=true;
 return;
}


BinaryFile::BinaryFile( const lem::Path& filename )
:Stream(false,false,filename)
{
 file=NULL;
 closable=false;
 binary=true;
 return;
}

BinaryFile::BinaryFile( FILE *f )
:Stream(true,true)
{
 file=f;
 closable = false; // Внешний код сам должен закрыть файл f.
 binary   = is_binary_file(f);
 return;
}

BinaryFile::BinaryFile( FILE *f, const lem::Path& filename )
:Stream(true,true,filename)
{
 file=f;
 closable = false; // Внешний код сам должен закрыть файл f.
 binary   = is_binary_file(f);
 return;
}



BinaryFile::BinaryFile(
                       FILE *File,
                       bool for_read,
                       bool for_write,
                       bool /*for_append*/,
                       bool text_mode
                      ):Stream(for_read,for_write)
{
 file=File;
 closable=false;
 binary = !text_mode;
 return;
}

BinaryFile::BinaryFile(
                       const lem::Path& filename,
                       bool for_read,
                       bool for_write,
                       bool for_append,
                       bool text_mode,
                       bool do_throw
                      ):Stream(for_read,for_write,filename)
{
 file=NULL;
 reopen( for_read, for_write, for_append, text_mode, do_throw );
 return;
}


BinaryFile::~BinaryFile(void)
{
 if( closable )
  close();
 else
  file=NULL;

 return;
}


void BinaryFile::reopen( 
                        bool for_read,
                        bool for_write,
                        bool for_append,
                        bool text_mode,
                        bool do_throw
                       )  
{
 if( file!=NULL )
  close();

 binary = !text_mode;

 const char *amode=NULL;
 const wchar_t *umode=NULL;

 if( for_read && !for_write )
  {
   amode = "rb";
   umode = L"rb";
  }

 if( for_write && !for_read )
  {
   if( for_append )
    { 
     amode = "ab";
     umode = L"ab";
    }
   else
    {
     amode = "wb";
     umode = L"wb";
    }
  }

 if( for_write && for_read )
  {
   amode = "rb+";
   umode = L"rb+";
  } 

 SetMode( for_read, for_write, seekable );
 OpenDiskFile( amode, umode, do_throw );

 return;
}


void BinaryFile::OpenDiskFile( const char *amode, const wchar_t *umode, bool do_throw )
{
 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   #if defined LEM_WINDOWS
   const UFString n = GetName().GetUnicode();

   // У стандартной CRT Borland CBuilder 6.0 проблема - не может
   // открыть файл "nul" через UNICODE-функцию.
   if( n==L"nul" )
    file=/*std::*/::fopen( "nul", amode );
   else
    #if defined LEM_BORLAND
     file=/*std::*/::fopen( GetName().GetAscii().c_str(), amode );
    #else
     file=_wfopen( n.c_str(), umode );
    #endif 

   #elif defined LEM_UNIX

   // перекодируем в utf-8

   if( GetName().IsAscii() )
    {
     file=::fopen( GetName().GetAscii().c_str(), amode );
    }
   else
    {
     file=::fopen( lem::to_utf8(GetName().GetUnicode()).c_str(), amode );
    }

   #endif
  }
 else
  {
   file=/*std::*/::fopen( GetName().GetAscii().c_str(), amode );
  }

 if( file==NULL )
  {
   if( do_throw )
    {
//printf( "File error: %s\n", filename.Get_Ascii().c_str() );
     lem::UFString fn( GetName().GetUnicode() );
     throw E_BaseException( wstring( L"File open error: " )+fn.c_str() );
    }
  }

 #if LEM_DEBUGGING==1
 n_opened++;
 #endif

// check_file(file,filename);
 closable=true;

 IFDEBUG(Assert());
 return;
}


void BinaryFile::close(void)
{
 IFDEBUG(Assert());

 if( file!=NULL )
  {
   check_file(file);
   ::fclose(file);

   #if LEM_DEBUGGING==1
   n_opened--;
   #endif
  }

 file=NULL;
 closable=false;
 return;
}

void BinaryFile::write( const void* src, pos_type size )
{
 IFDEBUG(Assert());
 LEM_CHECKIT_Z(file!=NULL);

 CheckWritable();

 if( src && size>0 )
  {
   #if LEM_DEBUGGING
   size_t s = fwrite( src, size, 1, file );
   LEM_CHECKIT_Z( s==1 ); 
   #else
   fwrite( src, size, 1, file );
   #endif
  }

 IFDEBUG( Check() );
 return;
}

Stream::pos_type BinaryFile::read( void* dest, pos_type size )
{
 IFDEBUG(Assert());
 LEM_CHECKIT_Z(file!=NULL);

 CheckReadable();

 pos_type res=0;
 if( dest && size )
  {
   res=fread( dest, 1, size, file );
  }

 IFDEBUG( Check() );
 return res;
}

int BinaryFile::get(void)
{
 IFDEBUG(Assert());
 LEM_CHECKIT_Z(file!=NULL);

 CheckReadable();
 const int res=fgetc(file);

 IFDEBUG( Check() );

 return res;
}

void BinaryFile::put( char ch )
{
 IFDEBUG(Assert());
 LEM_CHECKIT_Z(file!=NULL);

 CheckWritable();
 fputc(ch,file);

 IFDEBUG( Check() );
 return;
}


void BinaryFile::unget( char c )
{
 IFDEBUG(Assert());
 LEM_CHECKIT_Z(file!=NULL);
 ungetc( c, file );
}


Stream::pos_type BinaryFile::fsize(void) const
{
 IFDEBUG(Assert());
 LEM_CHECKIT_Z(file!=NULL);
 return get_file_size((FILE*)file);
}


lem::uint64_t BinaryFile::fsize64(void) const
{
 #if !defined LEM_FILE64
  return this->fsize();
 #else
  IFDEBUG(Assert());
  LEM_CHECKIT_Z(file!=NULL);

  const int fd = _fileno(file);

  __int64 curp = _telli64( fd );
  if( _lseeki64( fd, 0, SEEK_END ) == -1L )
   {
    _lseeki64( fd, curp, SEEK_SET );
    return 0;
   }

  __int64 size = _telli64( fd );
  _lseeki64( fd, curp, SEEK_SET );
  return size;
 #endif
}


bool BinaryFile::GetTimes(
                          boost::posix_time::ptime &creat,
                          boost::posix_time::ptime &modif
                         )
{
 IFDEBUG(Assert());
 LEM_CHECKIT_Z(file!=NULL);

 if(file==NULL)
  // файл не был открыт
  return false;

 #if defined LEM_WINDOWS

 struct _stat buf;
 if( _fstat( _fileno(file), &buf ) )
  return false;

 #elif defined LEM_UNIX

 struct stat buf;
 if( fstat( fileno(file), &buf ) )
  return false;

 #endif

 struct tm *tm_creat = localtime( &buf.st_ctime );
 if( tm_creat!=NULL )
  creat = boost::posix_time::from_time_t(mktime(tm_creat));

 struct tm *tm_modif = localtime( &buf.st_mtime );
 if( tm_modif!=NULL )
  modif = boost::posix_time::from_time_t(mktime(tm_modif));

 return true;
}



BinaryFile::pos64_type BinaryFile::seekp64( off64_type to, int whereto )
{
 #if LEM_DEBUGGING==1
 Assert();
 LEM_CHECKIT_Z(file!=NULL);
 #endif

 switch(whereto)
 {
  case SEEK_SET:
   {
    #if defined LEM_FILE64
    int ret = fsetpos(file,&to);
    LEM_CHECKIT_Z(ret==0);
    #else
    int ret = fseek(file,to,SEEK_SET);
    LEM_CHECKIT_Z(ret==0);
    #endif 
    break;
   }

  case SEEK_END:
   {
    if( to==0 )
     {
      #if defined LEM_WINDOWS && defined LEM_MSC && _MSC_VER>=1300
       fflush(file);
       int ret=-1;
       HANDLE h = (HANDLE)_get_osfhandle( _fileno(file) );
       LARGE_INTEGER p;
       if( GetFileSizeEx( h, &p )!=0 )
        {
         pos64_type p64=p.QuadPart;
         fsetpos(file,&p64);
         ret=0;
        }
      #else
       int ret = fseek(file,0,SEEK_END);
       #if LEM_DEBUGGING==1 && defined LEM_MSC && _MSC_VER>=1300
       pos64_type p;
       fgetpos(file,&p);
       #endif
      #endif

      LEM_CHECKIT_Z(ret==0);
     }
    else
     {
      LEM_STOPIT;
     }
    break;
   }

  default: LEM_STOPIT;
 }

 return to; 
}



BinaryFile::pos64_type BinaryFile::tellp64(void) const
{
 #if LEM_DEBUGGING==1
 Assert();
 LEM_CHECKIT_Z(file!=NULL);
 #endif

 #if defined LEM_FILE64
 pos64_type res;
 fgetpos( file, &res );
 return res;
 #else
 return ftell(file); 
 #endif
}


// отмена буферизации (setvbuf).
void BinaryFile::NoBuffer(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 LEM_CHECKIT_Z(file!=NULL);
 #endif
 
 setvbuf( file, NULL, _IONBF, 0 );
 return;
}



bool BinaryFile::is_failed(void) const
{ return !file; }



void BinaryFile::Check(void) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 check_file(file,GetName());
}

void BinaryFile::flush(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 ::fflush(file);

 #if defined LEM_WINDOWS
//    _commit( fileno(file) );
 #endif
}

bool BinaryFile::eof(void) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 return !!feof(file);
}

lem::Stream::pos_type BinaryFile::tellp(void) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 return ::ftell(file);
}

lem::Stream::pos_type BinaryFile::seekp( lem::Stream::off_type to, int whereto )
{
 #if LEM_DEBUGGING==1
 Assert();
 int ret = ::fseek(file,to,whereto);
 LEM_CHECKIT_Z(ret==0);
 #else
 ::fseek(file,to,whereto);
 #endif
 return to;
}


bool BinaryFile::move( lem::Stream::off_type offset )
{
 #if LEM_DEBUGGING==1
 Assert();
 int ret = ::fseek(file,offset,SEEK_CUR);
 LEM_CHECKIT_Z(ret==0);
 #else
 int ret = ::fseek(file,offset,SEEK_CUR);
 #endif
 return ret==0;
}



bool BinaryFile::IsDiskFile(void) const { return true; }

BinaryReader::BinaryReader( const Path& filename )
 : BinaryFile( filename, true, false )
{
}

BinaryWriter::BinaryWriter( const Path& filename )
 : BinaryFile( filename, false, true )
{
}


BinaryUpdater::BinaryUpdater( const Path& filename )
 : BinaryFile( filename, true, true, true )
{
}

