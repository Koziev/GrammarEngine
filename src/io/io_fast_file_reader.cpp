// -----------------------------------------------------------------------------
// File IO_FAST_FILE_READER.CPP
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
// Бинарные потоки ввода-вывода: класс FastFileReader - быстрый читатель для
// бинарных дисковых файлов.                             
//
// 12.05.2008 - bugfix в ::seekp и ::seekp64
// 07.01.2009 - добавлена поддержка SEEK_CUR в seekp
// -----------------------------------------------------------------------------
//
// CD->03.10.2007
// LC->06.03.2010
// --------------

#include <lem/config.h>

#if defined LEM_WINDOWS

#if defined LEM_MFC
 #include <afxwin.h>
#else
 #include <windows.h>
#endif

#if defined LEM_QT
 #include <QFileInfo>
#endif

#include <lem/streams.h>

using namespace lem;

FastFileReader::FastFileReader( const lem::Path& filename )
:Stream(true,false,filename)
{
 hFile = NULL;
 hFileMap = NULL;
 OrgAdr = EndAdr = NULL;
 filesize.LowPart = filesize.HighPart = 0;
 binary=true;

 hFile = CreateFileW(
                     filename.GetUnicode().c_str(),
                     GENERIC_READ,
                     FILE_SHARE_READ,
                     NULL,
                     OPEN_EXISTING,
                     0,
                     NULL
                    );

 LEM_CHECKIT_Z(hFile!=(HANDLE)-1);

 if( hFile==(HANDLE)-1 )
  return;

 hFileMap = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, 0, NULL );
 LEM_CHECKIT_Z(hFileMap!=NULL);

 if( hFileMap==NULL )
  return;

 OrgAdr = (lem::uint8_t*)MapViewOfFile( hFileMap, FILE_MAP_READ, 0, 0, 0 );
 LEM_CHECKIT_Z(OrgAdr!=NULL);

 if( OrgAdr==NULL )
  return;

 #if defined LEM_QT
 quint64 i64 = QFileInfo(filename.GetUnicode().to_qt()).size();
 filesize.QuadPart = i64;
 #elif (defined LEM_MSC && _MSC_VER<1300) || defined LEM_WIN98
 filesize.LowPart = GetFileSize( hFile, (unsigned long*)&filesize.HighPart );
 LEM_CHECKIT_Z( filesize.LowPart!=INVALID_FILE_SIZE );
 #else
 BOOL res = GetFileSizeEx( hFile, &filesize );
 LEM_CHECKIT_Z( res!=0 );
 #endif

 CurAdr = OrgAdr;
 EndAdr = OrgAdr+filesize.LowPart;

 return;
}



FastFileReader::~FastFileReader(void)
{
 close();
 return;
}




void FastFileReader::close(void)
{
 UnmapViewOfFile(OrgAdr);
 CloseHandle(hFileMap);
 CloseHandle(hFile);                     

 EndAdr = CurAdr = OrgAdr = NULL;
 hFileMap = NULL;
 hFile = NULL;

 return;
}


void FastFileReader::write( const void* src, pos_type size )
{
 LEM_STOPIT;
 return;
}


Stream::pos_type FastFileReader::read( void* dest, pos_type size )
{
 LEM_CHECKIT_Z(dest!=NULL);

 if( CurAdr+size > EndAdr )
  {
   // Файл закончится раньше
   size = EndAdr-CurAdr;
   memcpy( dest, CurAdr, size );
   CurAdr = EndAdr;
  } 
 else
  {
   memcpy( dest, CurAdr, size );
   CurAdr += size;
  }

 return size;
}


bool FastFileReader::eof(void) const
{
 return CurAdr==EndAdr;
}


int FastFileReader::get(void)
{
 if( CurAdr==EndAdr )
  return EOF;

 return *CurAdr++;
}



void FastFileReader::put( char ch )
{
 LEM_STOPIT;
 return;
}


void FastFileReader::unget( char c )
{
 LEM_STOPIT;
}


Stream::pos_type FastFileReader::fsize(void) const
{
 return filesize.LowPart;
}


lem::uint64_t FastFileReader::fsize64(void) const
{
 return filesize.QuadPart;
}



FastFileReader::pos64_type FastFileReader::seekp64( off64_type to, int whereto )
{
 LEM_CHECKIT_Z( hFile!=NULL );
 LEM_CHECKIT_Z( hFileMap!=NULL );
 LEM_CHECKIT_Z( OrgAdr!=NULL );

 switch(whereto)
 {
  case SEEK_SET:
   {
    if( lem::uint64_t(to) > lem::uint64_t(filesize.LowPart) )
     {
      CurAdr = EndAdr;  
      return filesize.LowPart;
     }

    CurAdr = OrgAdr+to;
    break;
   }

  default: LEM_STOPIT;
 }

 return to; 
}

FastFileReader::pos_type FastFileReader::seekp( off_type to, int whereto )
{
 LEM_CHECKIT_Z( hFile!=NULL );
 LEM_CHECKIT_Z( hFileMap!=NULL );
 LEM_CHECKIT_Z( OrgAdr!=NULL );

 switch(whereto)
 {
  case SEEK_SET:
   {
    if( lem::uint64_t(to) > lem::uint64_t(filesize.LowPart) )
     {
      CurAdr = EndAdr;  
      return filesize.LowPart;
     }

    CurAdr = OrgAdr+to;
    break;
   }

  case SEEK_CUR:
   {
    lem::uint8_t *a = CurAdr+to;

    if( lem::uint64_t( a-OrgAdr ) > lem::uint64_t(filesize.LowPart) )
     {
      CurAdr = EndAdr;
      return filesize.LowPart;
     }

    CurAdr = a;
    break;
   }

  default: LEM_STOPIT;
 }

 return to; 
}



FastFileReader::pos64_type FastFileReader::tellp64(void) const
{
 return CurAdr-OrgAdr;
}

FastFileReader::pos_type FastFileReader::tellp(void) const
{
 return CurAdr-OrgAdr;
}

bool FastFileReader::is_failed(void) const
{
 return OrgAdr==NULL;
}


bool FastFileReader::move( off_type offset )
{
 if( CurAdr+offset > EndAdr )
  { 
   CurAdr = EndAdr;
   return false;
  }

 CurAdr += offset;
 return true;
}

void FastFileReader::flush(void)
{
 LEM_STOPIT;
}

void FastFileReader::Check(void) const
{
 LEM_CHECKIT_Z( !is_failed() );
}

bool FastFileReader::IsDiskFile(void) const
{ return true; }

#endif
