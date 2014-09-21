#include <lem/runtime_checks.h>
#include <lem/WideStringUcs4.h>

using namespace lem;

WideStringUcs4::WideStringUcs4( const wchar_t * _str ) : str(_str), icur(-1), iback(-1), eof(false)
{
}

lem::uint32_t WideStringUcs4::Fetch(void)
{
 if( eof )
  return 0;

 iback = icur;

 if( sizeof(wchar_t)==4 )
  {
   lem::uint32_t c = str[++icur];
   eof = c==0;
   return c;
  }
 else
  {
   wchar_t hi = str[++icur];

   if( hi==0 )
    {
     eof=true;
     return 0;
    }

   if( (hi & 0xF800)==0xD800 )
    {
     // должна быть суррогатная пара
     wchar_t lo = str[++icur];
     if( (lo&0xFC00)!=0xDC00 )
      throw lem::E_BaseException(L"Surrogate expected in wide string");

     lem::uint32_t ucs4 = 0x10000 + ( (lo-0xDC00) & 0x3ff) + ( ((hi-0xD800) & 0x3ff )<<10 );
     return ucs4;
    }
   else
    {
     return lem::uint32_t(lem::uint16_t(hi));
    }
  }
}

void WideStringUcs4::Back(void)
{
 icur = iback;
 return;
}

