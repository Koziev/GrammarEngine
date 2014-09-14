// -----------------------------------------------------------------------------
// File LEM_BITF.CPP
//
// (c) by Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
//
// Content:
// Побитовый ввод-вывод.
// -----------------------------------------------------------------------------
//
// CD->01.01.95
// LC->16.10.04
// ------------

#include <lem/streams.h>

using namespace lem;

BitStream::BitStream(void)
{
 rack=0x00;
 mask=0x80;
 stream=NULL;
 return;
}

BitStream::BitStream( Stream *Stream, bool Delete_Stream )
{
 rack=0x00;
 mask=0x80;
 stream = Stream;
 del = Delete_Stream;
 return;
}


BitStream::~BitStream(void)
{
 if( del )
  delete stream;

 stream = NULL;
 return;
}

// ---------------------------------------
// Вывод одного бита в выходной поток.
// ---------------------------------------
void BitStream::OutputBit( int bit )
{
 if(bit)
  rack |= mask;
 mask >>= 1;

 if( mask==0 )
  {
   stream->write( &rack, sizeof(rack) ); // Полный байт помещаем в поток.
   rack = 0;
   mask = 0x80;
  }

 return;
}

void BitStream::OutputBits( UINT32 bits, int count )
{
 LEM_CHECKIT_Z( count<=32 );

 unsigned long Mask = 1L << (count-1);

 while(Mask)
 {
  if( Mask & bits )
   rack |= mask;

  mask >>= 1;
  if( mask==0 )
   {
    stream->write( &rack, sizeof(rack) ); // Полный байт помещаем в поток.
    rack = 0;
    mask = 0x80;
   }

  Mask >>= 1;
 }

 return;
}

// ------------------------------------------
// Считывание одного бита из входного потока.
// ------------------------------------------
int BitStream::InputBit(void)
{
 if( mask==0x80 )
  stream->read( &rack, sizeof(rack) );

 int value = rack & mask;

 mask >>= 1;
 if( mask == 0 )
  mask = 0x80;

 return ( value ? 1 : 0 );
}

// ******************************************************************
// Считывание нескольких бит из входного файла.
// ******************************************************************
UINT32 BitStream::InputBits( int bit_count )
{
 LEM_CHECKIT_Z( bit_count<=32 );

 unsigned long Mask = 1L << (bit_count-1);
 unsigned long return_value = 0;

 while( Mask != 0 )
 {
  if( mask==0x80 )
   stream->read( &rack, sizeof(rack) );

  if( rack & mask )
   return_value |= Mask;

  Mask >>= 1;
  mask >>= 1;
  if( mask==0 )
   mask = 0x80;
 }

 return return_value;
}

// -------------------------- End Of File [LEM_BITF.CPP] -----------------------
