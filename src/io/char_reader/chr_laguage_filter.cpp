// CD->08.09.2005
// LC->08.09.2005
// --------------

#include <lem/conversions.h>
#include <lem/ustreams.h>

using namespace lem;
using namespace lem::Char_Stream;


wchar_t Russian_Filter::operator()( wchar_t c ) const
{
 if( is_cyr(c) || is_lat(c) || is_udelim(c) || is_udigit(c) || is_uspace(c) )
  return c;

 return L' ';
}


wchar_t Latin_Filter::operator()( wchar_t c ) const
{
 if( is_lat(c) || is_udelim(c) || is_udigit(c) || is_uspace(c) )
  return c;

 return L' ';
}


wchar_t Central_European_Filter::operator()( wchar_t c ) const
{
 if( is_lat_diaktr(c) || is_lat(c) || is_udelim(c) || is_udigit(c) || is_uspace(c) )
  return c;

 return L' ';
}
