// -----------------------------------------------------------------------------
// File CHR_TRANSLIT_READER.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Класс Translit_Reader - чтение PLAIN ASCII-файлов с транслитерацией.
// -----------------------------------------------------------------------------
//
// CD->10.11.2006
// LC->25.02.2010
// --------------


#include <lem/unicode.h>
#include <lem/streams.h>
#include <lem/ustreams.h>

using namespace std;
using namespace lem;
using namespace lem::Char_Stream;


Translit_Reader::Translit_Reader( lem::Ptr<Stream> Bin, lem::Ptr<Transliterator> Translit )
:WideStream(SET_ASCII,Bin), translit(Translit)
{
 return;
}


wchar_t Translit_Reader::Read_Char(void)
{
 last_char_pos = bin->tellp();
 return translit->NextChar(*bin);
}

void Translit_Reader::wput( wchar_t u )
{
 /* ... */
 return;
}

int Translit_Reader::get(void)
{ return bin->get(); }


void Translit_Reader::put( char c )
{ bin->put(c); }


const char* Translit_Reader::GetFormat(void) const
{
 return "translit";
}


