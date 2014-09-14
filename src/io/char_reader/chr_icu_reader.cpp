// -----------------------------------------------------------------------------
// File CHR_ICU_READER.CPP
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
// Класс ICU_Reader - чтение текстовых файлов со сложными кодировками через
// средства библиотеки IBM ICU.
// -----------------------------------------------------------------------------
//
// CD->12.10.2005
// LC->20.02.2010
// --------------

#if defined LEM_ICU

#include <icu/include/unicode/ucnv.h>
#include <icu/include/unicode/uclean.h>

#include <lem/unicode.h>
#include <lem/streams.h>
#include <lem/ustreams.h>


using namespace lem;
using namespace lem::Char_Stream;



ICU_Reader::ICU_Reader( const CodeConverter *encoding, lem::Ptr<lem::Stream> Bin )
:WideStream(SET_ICU,Bin)
{
 buf = NULL;
// outbuf = NULL;
 fromoffsets = NULL;

 cp = encoding;

 buf=NULL;
 unibuf=NULL;
 fromoffsets=NULL;
 setBufferSize(4096);

 strcpy( format, cp->getEncodingName().c_str() );

 err = U_ZERO_ERROR;
// infoffset = 0; outfoffset = 0;

 // Create CodeConverter converter. If the CodeConverter or its aliases weren't
 // available, it returns NULL and a failure code.
 convfrom = ucnv_open( cp->getEncodingName().c_str(), &err );

 if(U_FAILURE(err))
  {
   throw std::exception( "ICU_Reader error" );
  }

 ucnv_setToUCallBack( convfrom, UCNV_TO_U_CALLBACK_SKIP, 0, 0, 0, &err );
 if (U_FAILURE(err))
  {
   throw std::exception( "ICU_Reader error" );
  }

 Clear_Fields();

 Fill_Buffer(); 

 return;
}


ICU_Reader::~ICU_Reader(void)
{
 ucnv_close(convfrom);

 delete[] buf;
 delete[] unibuf;
 delete[] fromoffsets;
 return;
}


void ICU_Reader::setBufferSize( size_t bufferSize )
{
 bufsz = bufferSize;

 LEM_CHECKIT_Z( bufsz!=0 );
 LEM_CHECKIT_Z( buf==NULL );
 LEM_CHECKIT_Z( unibuf==NULL );
 LEM_CHECKIT_Z( fromoffsets==NULL );

 buf = new char[ 2 * bufsz ];
 unibuf = new wchar_t[ bufsz ];

 // +1 for an added U+FEFF in the intermediate Unicode buffer
 fromoffsets = new int32_t[bufsz + 1];

 return;
}



wchar_t ICU_Reader::Read_Char(void)
{
 // В выходном буфере есть символы?
 if( out_len<=0 )
  {
   // Нет, прочитаем еще порцию байтов и конвертируем их.
   Fill_Buffer();

   if( !out_len )
    // Все символы считаны, возвращаем конец файла
    return WEOF;
  }

 #if LEM_DEBUGGING==1
  if( i_out>=CastSizeToInt(bufsz) )
   {
    LEM_STOPIT;
   }
 #endif

 // Возвращаем очередной символ из UNICODE-буфера. 
 out_len--;
 last_char_pos = buf_begpos + (fromoffsets[i_out]-fromoffsets[0]);
 return unibuf[ i_out++ ]; 
}




int ICU_Reader::get(void)
{
 LEM_STOPIT;
 return 0;
}



const char* ICU_Reader::GetFormat(void) const
{
 return format;
}


// *************************************************************
// Заполнение выходного буфера порцией декодированных в UNICODE
// символов.
// *************************************************************


void ICU_Reader::Fill_Buffer(void)
{
 if( bin->eof() )
  return;

 bool fromSawEndOfBytes=false;
 bool willexit=false; 

 // Читаем порцию исходных данных. В rd - сколько байтов прочитано.
 if( !buf_offset )
  buf_begpos = bin->tellp();

 Stream::pos_type rd = bin->read( buf+buf_offset, bufsz-buf_offset );

 // Convert the read buffer into the new encoding via Unicode.
 // After the call 'unibufp' will be placed behind the last
 // character that was converted in the 'unibuf'.
 // Also the 'cbufp' is positioned behind the last converted
 // character.
 // At the last conversion in the file, flush should be set to
 // true so that we get all characters converted.
 //
 // The converter must be flushed at the end of conversion so
 // that characters on hold also will be written.

 cbufp = buf;
 do_flush = (UBool)(rd != bufsz);

 // convert until the input is consumed
 do
  {
   // remember the start of the current byte-to-Unicode conversion
   prevbufp = cbufp;

//     unibuf = unibufp = u.getBuffer((int32_t)bufsz);
   unibufp = unibuf;

   // Use bufsz instead of u.getCapacity() for the targetLimit
   // so that we don't overflow fromoffsets[].
   ucnv_toUnicode(
                  convfrom,
                  &unibufp,
                  unibuf + bufsz,
                  &cbufp,
                  buf + rd,
                  fromoffsets,
                  do_flush,
                  &err
                 );

   // Сколько символов записано в выходной буфер
   out_len = unibufp - unibuf;

   LEM_CHECKIT_Z( out_len <= CastSizeToInt(bufsz) );

   // Сколько байтов обработано из входного буфера
   const int c1 = cbufp - buf;

   // Если не все байты входного буфера обработаны, то нужно сдвинуть содержимое
   // этого буфера к началу

   buf_offset = bufsz - c1; // столько байтов необработано.

   if( c1!=bufsz )
    memmove( buf, cbufp, c1 );

   // fromSawEndOfBytes indicates that ucnv_toUnicode() is done
   // converting all of the input bytes.
   // It works like this because ucnv_toUnicode() returns only under the
   // following conditions:
   // - an error occurred during conversion (an error code is set)
   // - the target buffer is filled (the error code indicates an overflow)
   // - the source is consumed
   // That is, if the error code does not indicate a failure,
   // not even an overflow, then the source must be consumed entirely.
   fromSawEndOfBytes = (UBool)U_SUCCESS(err);

   if( err == U_BUFFER_OVERFLOW_ERROR )
    {
     err = U_ZERO_ERROR;
    }
   else if (U_FAILURE(err))
    {
//       throw std::exception( "ICU_Reader error" );

     willexit = TRUE;
     err = U_ZERO_ERROR; // reset the error for the rest of the conversion. 
    }

   // Replaced a check for whether the input was consumed by
   // looping until it is; message key "premEndInput" now obsolete.

   if( !out_len )
    continue;

  }
 while (!fromSawEndOfBytes);

 i_out = 0;

 return;
}


void ICU_Reader::flush(void)
{
 LEM_STOPIT;
}

bool ICU_Reader::eof(void) const
{
 return !out_len && bin->eof();
}


Stream::pos_type ICU_Reader::tellp(void) const
{
 if( back_ch )
  return back_pos;

 LEM_CHECKIT_Z( i_out<CastSizeToInt(bufsz) );

 return buf_begpos + (fromoffsets[i_out]-fromoffsets[0]);
}

Stream::pos_type ICU_Reader::seekp( Stream::off_type pos, int whereto )
{
 if( pos==0 && whereto==SEEK_SET )
  {
   ucnv_resetToUnicode(convfrom);
   Clear_Fields();    
   return bin->seekp(pos,whereto);
  }

 LEM_STOPIT;
 return 0;
}


void ICU_Reader::Clear_Fields(void)
{
 out_len = 0;
 i_out   = 0;
 buf_offset = 0;
 buf_begpos = 0;
 err = U_ZERO_ERROR;
 return;
}

#endif

