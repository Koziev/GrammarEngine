#include <memory>
#include <lem/unicode.h>

using namespace lem;




int lem::ucs4_to_utf8(
                      const lem::uint32_t *ucs4_buf,
                      int ucs4_len,
                      unsigned char *utf8_buf
                     )
{
 if( ucs4_buf==NULL || !ucs4_len )
  return 0;

 const lem::uint32_t *ucs4_endbuf = ucs4_buf + ucs4_len;
 int utf8_len = 0;        // return value for UTF8 size
 unsigned char *t_utf8_buf = utf8_buf; // Temporary pointer to load UTF8 values

 while (ucs4_buf != ucs4_endbuf)
  {
   if( *ucs4_buf <= 0x7F)    // ASCII chars no conversion needed
    {
     if( t_utf8_buf )
      *t_utf8_buf++ = (unsigned char) *ucs4_buf;
     utf8_len++;
     ucs4_buf++;
    }
   else if ( *ucs4_buf <= 0x07FF ) // In the 2 byte utf-8 range
    {
     if( t_utf8_buf )
      {
       *t_utf8_buf++= (unsigned char) (0xC0 + (*ucs4_buf/0x40));
       *t_utf8_buf++= (unsigned char) (0x80 + (*ucs4_buf%0x40));
      }

     utf8_len+=2;
     ucs4_buf++;
    }
   else if( *ucs4_buf <= 0xFFFF ) /* In the 3 byte utf-8 range. The
                                     values 0x0000FFFE, 0x0000FFFF
                                     and 0x0000D800 - 0x0000DFFF do
                                     not occur in UCS-4 */
    {
     if( t_utf8_buf )
      {
       *t_utf8_buf++= (unsigned char) (0xE0 + (*ucs4_buf/0x1000));
       *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x40)%0x40));
       *t_utf8_buf++= (unsigned char) (0x80 + (*ucs4_buf%0x40));
      }

     utf8_len+=3;
     ucs4_buf++;
    }
   else if( *ucs4_buf <= 0x1FFFFF ) //In the 4 byte utf-8 range
    {
     if( t_utf8_buf )
      {    
       *t_utf8_buf++= (unsigned char) (0xF0 + (*ucs4_buf/0x040000));
       *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x10000)%0x40));
       *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x40)%0x40));
       *t_utf8_buf++= (unsigned char) (0x80 + (*ucs4_buf%0x40));
      }

     utf8_len+=4;
     ucs4_buf++;
    }
   else if( *ucs4_buf <= 0x03FFFFFF )//In the 5 byte utf-8 range
    {
     if( t_utf8_buf )
      {
       *t_utf8_buf++= (unsigned char) (0xF8 + (*ucs4_buf/0x01000000));
       *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x040000)%0x40));
       *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x1000)%0x40));
       *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x40)%0x40));
       *t_utf8_buf++= (unsigned char) (0x80 + (*ucs4_buf%0x40));
      }

     utf8_len+=5;
     ucs4_buf++;
    }
   else if( *ucs4_buf <= 0x7FFFFFFF )//In the 6 byte utf-8 range
    {
     if( t_utf8_buf )
       {
        *t_utf8_buf++= (unsigned char) (0xF8 +(*ucs4_buf/0x40000000));
        *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x01000000)%0x40));
        *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x040000)%0x40));
        *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x1000)%0x40));
        *t_utf8_buf++= (unsigned char) (0x80 + ((*ucs4_buf/0x40)%0x40));
        *t_utf8_buf++= (unsigned char) (0x80 + (*ucs4_buf%0x40));
       } 
     utf8_len+=6;
     ucs4_buf++;
    }
  }

 return utf8_len;
}


/*************************************************************************
   When moving from UTF-8 encoding to the local character set the
   reverse procedure is used. First the UTF-8 encoding is transformed
   into the UCS-4 character set. The UCS-4 is then converted to the
   local character set from a mapping table (i.e. the opposite of the
   table used to form the UCS-4 character code).

   To convert from UTF-8 to UCS-4 the free bits (those that do not
   define UTF-8 sequence size or signify continuation bytes) in a UTF-8
   sequence are concatenated as a bit string. The bits are then
   distributed into a four-byte sequence starting from the least
   significant bits. Those bits not assigned a bit in the four-byte
   sequence are padded with ZERO bits. The following routine converts
   the UTF-8 encoding to UCS-4 character codes:
**************************************************************************/
int lem::utf8_to_ucs4(
                      const unsigned char *utf8_buf,
                      int utf8_len,
                      lem::uint32_t *ucs4_buf
                     )
{
 if( utf8_buf==NULL || !utf8_len )
  return 0;

 const unsigned char *utf8_endbuf = utf8_buf + utf8_len;
 int ucs_len=0;

 while( utf8_buf != utf8_endbuf )
  {
   if((*utf8_buf & 0x80) == 0x00)  /*ASCII chars no conversion needed */
    {
     *ucs4_buf++ = (lem::uint32_t) *utf8_buf;
     utf8_buf++;
     ucs_len++;
    }
   else if( (*utf8_buf & 0xE0)== 0xC0) //In the 2 byte utf-8 range
    {
     *ucs4_buf++ = (lem::uint32_t) (((*utf8_buf - 0xC0) * 0x40) + ( *(utf8_buf+1) - 0x80));
     utf8_buf += 2;
     ucs_len++;
    }
   else if( (*utf8_buf & 0xF0) == 0xE0 ) /*In the 3 byte utf-8 range */
    {
     *ucs4_buf++ = (lem::uint32_t) (((*utf8_buf - 0xE0) * 0x1000) + (( *(utf8_buf+1) -  0x80) * 0x40) + ( *(utf8_buf+2) - 0x80));
     utf8_buf+=3;
     ucs_len++;
    }
   else if ((*utf8_buf & 0xF8) == 0xF0) /* In the 4 byte utf-8 range */
    {
     *ucs4_buf++ = (lem::uint32_t)
                   (((*utf8_buf - 0xF0) * 0x040000)
                   + (( *(utf8_buf+1) -  0x80) * 0x1000)
                   + (( *(utf8_buf+2) -  0x80) * 0x40)
                   + ( *(utf8_buf+3) - 0x80));
     utf8_buf+=4;
     ucs_len++;
    }
   else if((*utf8_buf & 0xFC) == 0xF8) /* In the 5 byte utf-8 range */
    {
     *ucs4_buf++ = (lem::uint32_t)
                   (((*utf8_buf - 0xF8) * 0x01000000)
                   + ((*(utf8_buf+1) - 0x80) * 0x040000)
                   + (( *(utf8_buf+2) -  0x80) * 0x1000)
                   + (( *(utf8_buf+3) -  0x80) * 0x40)
                   + ( *(utf8_buf+4) - 0x80));
     utf8_buf+=5;
     ucs_len++;
    }
   else if ((*utf8_buf & 0xFE) == 0xFC) /* In the 6 byte utf-8 range */
    {
     *ucs4_buf++ = (lem::uint32_t)
                   (((*utf8_buf - 0xFC) * 0x40000000)
                   + ((*(utf8_buf+1) - 0x80) * 0x010000000)
                   + ((*(utf8_buf+2) - 0x80) * 0x040000)
                   + (( *(utf8_buf+3) -  0x80) * 0x1000)
                   + (( *(utf8_buf+4) -  0x80) * 0x40)
                   + ( *(utf8_buf+5) - 0x80));
     utf8_buf+=6;
     ucs_len++;
    }
  }

 return ucs_len;
}





static lem::uint8_t kUtf8Limits[5] = { 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };


lem::UFString lem::from_utf8( const char *src )
{ return lem::from_utf8( lem::FString(src) ); }


lem::UFString lem::from_utf8( const lem::FString &src )
{
 const int sl = src.length();

 UFString dest;

 if( !sl )
  return dest;

 #if LEM_WCHAR_T==4

 wchar_t * dest_str = new wchar_t[sl+1];
 std::unique_ptr<wchar_t> g_dest_str(dest_str);
 const int ucslen = lem::utf8_to_ucs4( (const unsigned char*)src.c_str(), sl, (lem::uint32_t*)dest_str );
 dest_str[ ucslen ] = 0;
 dest = dest_str;


 #elif LEM_WCHAR_T==2 && defined LEM_WINDOWS

 const int ucslen = MultiByteToWideChar( CP_UTF8, 0, src.c_str(), sl+1, NULL, 0 );

 //dest.reserve( ucslen ); 
 //const int rc = MultiByteToWideChar( CP_UTF8, 0, src.c_str(), sl+1, dest.ptr(), ucslen+1 );

 wchar_t* dest_chars = new wchar_t[ucslen];
 std::unique_ptr<wchar_t[]> g(dest_chars);
 const int rc = MultiByteToWideChar( CP_UTF8, 0, src.c_str(), sl+1, dest_chars, ucslen+1 );
 dest = dest_chars;

 LEM_CHECKIT_Z( rc==ucslen );

 #elif LEM_WCHAR_T==2

 // utf8 -> utf16

 dest.reserve( sl );

 for( int i=0; i<sl; )
  {
   lem::uint8_t c = (lem::uint8_t)src[i++];
   if( c < 0x80 )
    {
     dest.Add_Dirty( (wchar_t)c );
     continue;
    }

   if( c<0xC0 )
    {
     // Error.
     dest.clear();
     return dest;
    }

   int numAdds;
   for( numAdds=1; numAdds<5; numAdds++ )
    if(c < kUtf8Limits[numAdds])
     break;

   lem::uint32_t value = (c - kUtf8Limits[numAdds - 1]);

   do
    {
     if( i >= sl )
      {
       // Error.
       dest.clear();
       return dest;
      }

     lem::uint8_t c2 = (lem::uint8_t)src[i++];
     if( c2 < 0x80 || c2 >= 0xC0 )
      {
       // Error.
       dest.clear();
       return dest;
      }

     value <<= 6;
     value |= (c2 - 0x80);
     numAdds--;
    }
   while(numAdds > 0);

   if( value < 0x10000 )
    dest.Add_Dirty( (wchar_t)(value) );
   else
    {
     value -= 0x10000;

     if(value >= 0x100000)
      {
       // Error.
       dest.clear();
       return dest;
      }

     dest.Add_Dirty( (wchar_t)(0xD800 + (value >> 10)) );
     dest.Add_Dirty( (wchar_t)(0xDC00 + (value & 0x3FF)) );
    }
  }

 #else

  #error Unsupported platform

 #endif

 return dest; 
}



lem::FString lem::to_utf8( const lem::UFString &src )
{
 const int sl = src.length();
 lem::FString dest;
 if( !sl )
  return dest;

 #if LEM_WCHAR_T==4

  const int l6 = sl*6;
  //dest.reserve(l6);

  char * dest_chars = new char[l6];
  std::unique_ptr<char[]> p(dest_chars);

  const int utf8len = lem::ucs4_to_utf8( (const lem::uint32_t*)src.c_str(), sl, (unsigned char*)dest_chars );
  //dest.ptr()[ utf8len ] = 0;
  dest_chars[utf8len] = 0;
  dest = dest_chars;

 #elif LEM_WCHAR_T==2 && defined LEM_WINDOWS

  const int len8 = WideCharToMultiByte( CP_UTF8, 0, src.c_str(), sl+1, NULL, 0, 0, NULL );

  //dest.reserve(len8);
  //const int rc = WideCharToMultiByte( CP_UTF8, 0, src.c_str(), sl+1, dest.ptr(), len8, 0, NULL );

  char * dest_chars = new char[len8];
  std::unique_ptr<char[]> p(dest_chars);
  const int rc = WideCharToMultiByte( CP_UTF8, 0, src.c_str(), sl+1, dest_chars, len8, 0, NULL );
  dest = dest_chars;

  LEM_CHECKIT_Z( rc==len8 );

 #elif LEM_WCHAR_T==2

 dest.reserve( sl );

 for( int i=0; i<sl; )
  {
   lem::uint32_t value = (lem::uint32_t)src[i++];

   if( value < 0x80 )
    {
     dest += (char)value;
     continue;
    }

    if( value >= 0xD800 && value < 0xE000 )
    {
     if( value >= 0xDC00 )
      return FString();

     if( i >= sl )
      return FString();

     lem::uint32_t c2 = (lem::uint32_t)src[i++];
     if( c2 < 0xDC00 || c2 >= 0xE000 )
      return FString();

     value = ((value - 0xD800) << 10) | (c2 - 0xDC00);
    }

   int numAdds;
   for( numAdds = 1; numAdds < 5; numAdds++ )
    if( value < (((lem::uint32_t)1) << (numAdds * 5 + 6)) )
     break;

   dest += (char)(kUtf8Limits[numAdds - 1] + (value >> (6 * numAdds)));

   do
    {
     numAdds--;
     dest += (char)(0x80 + ((value >> (6 * numAdds)) & 0x3F));
    }
   while(numAdds > 0);
  }

 #else

  #error Unsupported platform

 #endif

 return dest;
}



MBCodeConverter::MBCodeConverter( const char *Encoding )
 : CodeConverter(Encoding)
{}


bool MBCodeConverter::IsSingleByte(void) const 
{ return false; }



Utf8CodeConverter::Utf8CodeConverter(void)
 : MBCodeConverter( "utf8" )
{
 index = 65001;
 return;
}



wchar_t* Utf8CodeConverter::to_unicode( const char *src, wchar_t *dst ) const
{
 LEM_CHECKIT_Z(src!=NULL);
 LEM_CHECKIT_Z(dst!=NULL);

 const int l = lem::lem_strlen(src);

 #if defined LEM_WINDOWS
 int r = MultiByteToWideChar( CP_UTF8, 0, src, l+1, dst, l+1 );
 LEM_CHECKIT_Z(r!=0);
 #else
 LEM_CHECKIT_Z( sizeof(wchar_t)==sizeof(lem::uint32_t) );
 int ret_len = utf8_to_ucs4( (unsigned char*)src, l, (lem::uint32_t*)dst );
 dst[ret_len]=0;
 #endif

 return dst;
}




char* Utf8CodeConverter::to_ascii( const wchar_t *src, char *dst ) const
{
 LEM_CHECKIT_Z(src!=NULL);
 LEM_CHECKIT_Z(dst!=NULL);

 const int l = lem::lem_strlen(src);

 #if defined LEM_WINDOWS
 int r = WideCharToMultiByte( CP_UTF8, 0, src, l+1, dst, l+1, NULL, NULL );
 LEM_CHECKIT_Z(r!=0);
 #else
 LEM_CHECKIT_Z( sizeof(wchar_t)==sizeof(lem::uint32_t) );
 int ret_len = ucs4_to_utf8( (lem::uint32_t*)src, l, (unsigned char*)dst );
 dst[ret_len]=0;
 #endif

 return dst;
}




int Utf8CodeConverter::EstimateAsciiLen( int UnicodeLen ) const
{
 LEM_CHECKIT_Z(UnicodeLen>=0);

 // “еоретически может быть до 6 байтов дл€ одного исходного символа,
 // но практически - только 4. “ем не менее дл€ перестраховки умножаем на 6.
 return UnicodeLen*6;
}


int Utf8CodeConverter::to_ascii( wchar_t uch, char *dst ) const
{
 int n;

 if( sizeof(wchar_t)==4 )
  n=UCS4_to_UTF8( (lem::uint32_t)uch, (lem::uint8_t*)dst );
 else
  n=UCS4_to_UTF8( (lem::uint32_t)(0x0000ffff&uch), (lem::uint8_t*)dst );
 
 return n;
}
