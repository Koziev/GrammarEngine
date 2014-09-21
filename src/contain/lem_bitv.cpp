#include <lem/bit_vector.h>

using namespace lem;

void BitVector::LoadBin( Stream &bin )
{
 MCollect<uint32_t>::LoadBin(bin);
 bin.read( &nbit, sizeof(nbit) );
 return;
}



void BitVector::SaveBin( Stream &bin ) const
{
 MCollect<uint32_t>::SaveBin(bin);
 bin.write( &nbit, sizeof(nbit) );
 return;
}



// Сохраняет содержимое вектора со сжатием, благодаря чему
// разреженные векторы могут занимать значительно меньше места 
// на диске.
void BitVector::SaveBin_RLE( Stream &bin, bool Compress ) const
{
//bin.write_int( 0x12345678 );

 int n8 = Blocks32() * 4; // сколько байтовых блоков

 #undef B8
 #define B8(i) (get_Container()[ (i)/4 ] & (0xff000000U >> (8*((i)%4)))) >> ( 8*(3 - (i)%4) )

 BitVector v8(n8);
 for( int i=0; i<n8; i++ )
  if( B8(i) )
   v8.set( i, true );

 v8.SaveBin(bin);

/*
 if( Compress )
  v8.SaveBin_Compressed(bin,0);
 else
  v8.SaveBin_RLE(bin,false);
*/

 for( int i2=0; i2<n8; i2++ )
  if( B8(i2) )
   {
    lem::uint8_t b = B8(i2);
    bin.write( &b, sizeof(b) ); 
   } 

 return;
}


void BitVector::LoadBin_RLE( Stream &bin )
{
// int xxx = bin.read_int();

 BitVector v8;
 v8.LoadBin(bin);

 resize( v8.size()*8 );
 SetAll(0);

 int n8 = Blocks32() * 4; // сколько байтовых блоков

 for( int i=0; i<n8; i++ )
  if( v8.get(i) )
   {
    lem::uint8_t b;
    bin.read( &b, sizeof(b) ); 

    lem::uint32_t bits = static_cast<lem::uint32_t>(b) << 8*(3-(i%4));
    lem::uint32_t mask = 0xff000000 >> (8*(i%4));

    get_Container()[ i/4 ] |= (mask & bits );
   } 

 return;
}



void BitVector::SaveBin_Compressed( Stream &bin, int Depth ) const
{
 int n8 = Blocks32() * 4; // сколько байтовых блоков

 #undef B8
 #define B8(i) (get_Container()[ (i)/4 ] & (0xff000000U >> (8*((i)%4)))) >> (8*(3 - (i)%4))

 BitVector v8(n8);
 for( int i=0; i<n8; i++ )
  if( B8(i) )
   v8.set( i, true );

 if( !Depth )
  v8.SaveBin(bin);
 else
  v8.SaveBin_Compressed(bin,Depth-1);

 for( int i2=0; i2<n8; i2++ )
  if( B8(i2) )
   {
    lem::uint8_t b = B8(i2);
    bin.write( &b, sizeof(b) ); 
   } 

 return;
}


/*
void BitVector::SaveBin_RLE_2( Stream &bin ) const
{
 int n8 = Blocks32() / 4; // сколько байтовых блоков

 #define B8(i) (container[ (i)/4 ] & (0xff000000U >> (8*((i)%4)))) >> (8*(3 - (i)%4))

 int i=0;
 while( i<n8 )
  {
   lem::uint8_t b8 = B8(i); 
   if( !b8 )
    {
     // Сколько пустых 8-битовых блоков
     int n0=0;
     for( ; i<n8 && n0<128; i++, n0++ )
      {
       lem::uint8_t b8 = B8(i); 
       if( b8 )
        break;   
      }

     if( n0 )
      bin.write( &n0, sizeof(n0) );
    }      
   else
    {
     // Сколько НЕпустых 8-битовых блоков
     int nX=0;
     int j=i;
     for( ; i<n8 && nX<128; i++, nX++ )
      {
       lem::uint8_t b8 = B8(i); 
       if( !b8 )
        break;   
      }

     if( nX )
      {
       lem::uint8_t d = 0xf0 | nX;
       bin.write( &d, sizeof(d) );
      }

     for( int k=0; k<nX; k++, j++ )
      {
       lem::uint8_t b8 = B8(j); 
       bin.write( &b8, sizeof(b8) );
      }
    } 
  } 

 return;
}
*/
