// -----------------------------------------------------------------------------
// File IO_TEXT_FILE.CPP
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
// Бинарные потоки ввода-вывода: класс TextFile - текстовые файлы.
//
// 27.12.2008 - для удобства введены классы TextReader и TextWriter.
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->27.12.2008
// --------------

#include <stdio.h> // for _wfopen
#include <lem/path.h>
#include <lem/system_config.h>
#include <lem/streams.h>

using namespace lem;

TextFile::TextFile(void):BinaryFile() {}


TextFile::TextFile(
                   const lem::Path& filename,
                   bool for_read,
                   bool for_write,
                   bool for_append
                  ):BinaryFile(filename,for_read,for_write,for_append)
{
 binary = false;

 const char *amode = NULL;
 const wchar_t *umode = NULL;

 if( for_read && !for_write )
  {
   amode = "rt";
   umode = L"rt";
  }

 if( for_write && !for_read )
  {
   if( for_append )
    {
     amode = "at";
     umode = L"at";
    }
   else
    {
     amode = "wt";
     umode = L"wt";
    }
  }

 if( for_write && for_read )
  {
   amode = "rt+";
   umode = L"rt+";
  }

 OpenDiskFile( amode, umode, true );
 return;
}


// ***********************************************************
// Read characters till EOL ('\n') reached, returns collected
// string.
// ***********************************************************
const FString TextFile::read_till_eol(void)
{
 FString str;

 while( !eof() )
  {
   int ch = get();
   if( ch==EOF || ch=='\n' )
    break;

   str += ch;
  }

 return str; 
}



TextReader::TextReader(void):TextFile() {}


TextReader::TextReader( const Path& filename )
 : TextFile( filename, true, false )
{}


TextWriter::TextWriter(void):TextFile() {}


TextWriter::TextWriter( const Path& filename )
 : TextFile( filename, false, true )
{}
