// -----------------------------------------------------------------------------
// File IR_PRINT_ERROR.CPP
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
// LEM C++ library
//
// Error reporting procedures - с указанием места ошибки в тексте, когда
// используются классы UTextSource или Macro_Parser.
//
// 19.10.2005 - процедуры печати контекста ошибки переделаны для корректной
//              работы с UTF8 и другими кодировками текста. 
// -----------------------------------------------------------------------------
//
// CD->30.07.1997
// LC->27.07.2008
// --------------

#include <lem/conversions.h>
#include <lem/ustreams.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;
using namespace lem::Char_Stream;

/************************************************************************
   When the Solaris translator detects an error in dictionary text file,
 it displays a message on the screen. The format of message displayed
 depends on the error time and the amount of information available.
 In almost all cases the translator prints the file name being compiled,
 the number of line where an error is located, then the content of
 erroneous line. Under that line the hat character (^) shows where the
 translator was at character-wise when it detected the error. After all,
 the description of error is printed.

   Make note, that sometimes translator shows not the real line with
 error but a line following it.

   Programmer note: the print_ir_error(...) functions do not force
 translator to stop. That is your duty to make decison and to take
 measures.

   Input parameter type, when presents, may be either 0 (error message),
 or 1 (warning message).

   Also you should know, that two groups of error reporting function
 are there: for UTextSource class and for Macro_Parser class.
*************************************************************************/
void lem::Iridium::Print_Error(
                               const BethToken& t,
                               Macro_Parser& src,
                               bool Warn_Only
                              )
{
 Warn_Only ? src.RegWarning() : src.RegError();

 if( t.GetFile()==UNKNOWN || !src.GetnFile() )
  {
   if( src.lexems().empty() )
    return;

   // Информация о файле, из которого были считаны лексемы, недоступна.
   // Поэтому распечатываем контекст ошибки - несколько лексем до и после.

   Macro_Parser::const_iterator beg = src.begin() + std::min( std::max( int(t.GetIndex())-8, 0 ), int(src.lexems().size())-1 );
   Macro_Parser::const_iterator end = src.begin() + t.GetIndex() + 8;

   src.GetIO().merr().eol();
   int pos0=0, cur=0;
   for( Macro_Parser::const_iterator i=beg; i!=src.end() && i!=end; i++ )
    {
     src.GetIO().merr().printf( "%us ", i->c_str() );

     cur += i->length()+1;

     if( i->GetIndex() == t.GetIndex() )
      pos0=cur;
    }

   src.GetIO().merr().eol();
   src.GetIO().merr().printf( "%H %H^\n", (pos0 - static_cast<const UToken&>(*beg).GetBegin().GetSymbolPos()), t.length() );

   return;
  }

 UTextParser txtfile;
 StreamPtr file_x( new BinaryReader( lem::Path(src.GetFileName(t.GetFile())) ) );
 WideStreamPtr reader = WideStream::GetReader( file_x );
 reader->SetEncoding( src.GetCP() );
 txtfile.Open( reader );

 Print_Error( src.GetIO(), t, txtfile, Warn_Only );
 return;
}

void lem::Iridium::Print_Error(
                               Sol_IO &io,
                               const BethToken& t,
                               UTextParser &txtfile,
                               bool Warn_Only
                              )
{
 const UToken tt = t;
 txtfile.seekp( tt.GetBegin() );

 OFormatter *to = Warn_Only ? &(io.mecho()) : &(io.merr());

 to->printf(
            "\n%vfC%s%vn in line %vfE%d%vn column %vfE%d%vn of file %vfE%us%vn\n"
            , Warn_Only ? "Warning" : "Error"
            , tt.GetBegin().GetLine()
            , tt.GetBegin().GetSymbolPos()
            , txtfile.GetName().GetUnicode().c_str()
           );

 txtfile.ToLineBegin();      // Перемещаемся в начало строки с ошибкой

 int tok_len = t.string().length();
 if( tok_len<1 ) tok_len=1;

 txtfile.PrintLine(*to); // Распечатываем строку с ошибкой
 to->eol();

 // В начало токена с ошибкой.
 const int nsp=((const UToken&)t).GetBegin().GetSymbolPos();
 to->printf( "%H ", nsp );
 to->printf( "%vfC%H^%vn\n", tok_len );

 return;
}


void lem::Iridium::Print_Error(
                               const BSourceState& s,
                               Macro_Parser& src,
                               bool Warn_Only
                              )
{
 if( s.GetFile()==UNKNOWN )
  return;

 UTextParser txtfile;


 // Создаем подходящий для данного типа файлов ридер.
 WideStreamPtr reader = WideStream::GetReader( StreamPtr( new BinaryFile( lem::Path(src.GetFileName( s.GetFile() )), true, false ) ) );
 reader->SetEncoding( src.GetCP() );
 txtfile.Open( WideStreamPtr(reader) );

 Warn_Only ? src.RegWarning() : src.RegError();

 const BethToken& t = src.get(s);
 Print_Error( src.GetIO(), t, txtfile, Warn_Only );
 return;
}


/****************************************************************
 Печатаем сообщение об ошибке и выводим проблемную строку.
 Информацией о реальной символьной позиции с ошибкой мы не
 располагаем, поэтому укажем на текущее положение курсора чтения.
*****************************************************************/
void lem::Iridium::Print_Error(
                               Macro_Parser& src,
                               bool Warn_Only
                              )
{
 if( !src.GetnFile() )
  return;

 OFormatter *to = Warn_Only ? &(src.GetIO().mecho()) : &(src.GetIO().merr());

 Warn_Only ? src.RegWarning() : src.RegError();

 UTextParser txtfile;
 const BethToken& t = src.get( src.GetNext()>0 ? src.GetNext()-1 : src.GetNext() );

 WideStreamPtr reader = WideStream::GetReader( StreamPtr( new BinaryFile( lem::Path(src.GetFileName(t.GetFile())), true, false ) ) );

 reader->SetEncoding( src.GetCP() );
 txtfile.Open( WideStreamPtr(reader) );
 txtfile.seekp( static_cast<const UToken&>(t).GetBegin() );

 to->printf(
            "\n%vfC%s%vn near line %vfE%d%vn of file %vfE%us%vn\n"
            , Warn_Only ? "Warning" : "Error"
            , static_cast<const UToken&>(t).GetBegin().GetLine()
            , txtfile.GetName().GetUnicode().c_str()
           );

 txtfile.ToLineBegin(); // Перемещяемся в начало строки с ошибкой
 txtfile.PrintLine((OFormatter&)*to); // Распечатываем строку с ошибкой
 to->eol();
 return;
}


void lem::Iridium::Print_Error(
                               Sol_IO &io,
                               const UToken& t,
                               UTextParser& src
                              )
{
 src.seekp(t.GetBegin());

 io.merr().printf(
                  "\n%vfCError%vn near line %vfE%d%vn of file %vfE%us%vn\n"
                  , t.GetBegin().GetLine()
                  , src.GetName().GetUnicode().c_str()
                 );

 src.ToLineBegin(); // Перемещяемся в начало строки с ошибкой
 src.PrintLine( (OFormatter&)io.merr() );   // Распечатываем строку с ошибкой
 io.merr().printf(L'\n');

 // В начало токена с ошибкой.
 const int nsp=t.GetBegin().GetSymbolPos();
 io.merr().printf( "%H ", nsp );

 int l = t.string().length();
 if( l<1 ) l=1;
 io.merr().printf( "%H^\n", l );
 return;
}

/****************************************************************
 Печатаем сообщение об ошибке и выводим проблемную строку.
 Информацией об реальной символьной позиции с ошибкой мы не
 располагаем, поэтому укажем на текущее положение курсора чтения.
*****************************************************************/
void lem::Iridium::Print_Error( Sol_IO &io, UTextParser& src )
{
 io.merr().printf( "\n\n%vfCError:%vn\n" );
 src.ToLineBegin(); // Перемещяемся в начало строки с ошибкой
 src.PrintLine( (OFormatter&)io.merr() ); // Распечатываем строку с ошибкой
 io.merr().eol();
 return;
}

