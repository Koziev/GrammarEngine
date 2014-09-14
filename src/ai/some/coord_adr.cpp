// -----------------------------------------------------------------------------
// File COORD_ADR.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine
// Класс GramCoordAdr - структура для однозначной идентификации координаты
// в списке Грамматики.
// -----------------------------------------------------------------------------
//
// CD->19.06.1996
// LC->05.09.2010
// --------------

#include <lem/config.h>

#include <lem/solarix/coord_pair.h>

using namespace lem;
using namespace Solarix;

/******************************************************************
  Двухпроходный поиск координатного индекса в списке.

  В первый проход пытаемся найти в списке ТОЧНО такой же индекс,
  как и ca. Если это не удалось, пытаемся найти структуру с равным
  полем icoord, не обращая внимания на номер синонима.
*******************************************************************/
int CA_Array::FindTwice( const GramCoordAdr ca ) const
{
 const int ires = find(ca);
 if(ires!=UNKNOWN)
  return ires;

 for( Container::size_type i=0; i<size(); i++ )
  if( operator[](i).GetIndex()==ca.GetIndex() )
   return CastSizeToInt(i);

 return UNKNOWN;
}
