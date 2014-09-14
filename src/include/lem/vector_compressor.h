// CD->18.09.2005
// LC->17.05.2008
// --------------
#ifndef LEM_COLLECT_COMPRESSION__H
#define LEM_COLLECT_COMPRESSION__H
#pragma once

 #include <algorithm>
 #include <lem/integer.h>
 #include <lem/streams.h>
 #include <lem/containers.h>

 namespace lem
 {
  template < class T >
  inline void Save_Compressed_Vector(
                                     Stream &bin,
                                     lem::MCollect<T> &v,
                                     bool allow_0_diff // допускаются ли в векторах одинаковые
                                                       // соседние зрачения (иначе можно немного
                                                       // улучшить сжатие)
                                    )
  {
   // Отсортируем список индексов по возрастанию, это позволит оперировать
   // беззнаковыми приращениями значений.
   std::sort( v.begin(), v.end() );

   // Сначала предполагаем самую экономную схему сжатия, если элементов не совсем
   // мало.
   // 2 - max compression
   // 0 - no compression
   lem::uint8_t compression = v.size()<3 ? 0 : 2;

   const unsigned int v16  = allow_0_diff ? 15  : 16;
   const unsigned int v256 = allow_0_diff ? 255 : 256;
   const unsigned int z1   = allow_0_diff ? 0 : 1;

   if( compression!=0 )
    for( Container::size_type i=1; i<v.size(); i++ )
     {
      unsigned int diff = v[i]-v[i-1]; 

      if( diff>v256 )
       {
        // Сжатие невозможно.
        compression=0;
        break;
       }

      if( diff>v16 )
       {
        // Понижаем степень сжатия и продолжаем проверку.
        compression=1;
       }
     }

/*
     bin.write( &compression, sizeof(compression) );
     lem::uint32_t n32 = static_cast<lem::uint32_t>( v.size() );
     bin.write( &n32, sizeof(n32) );
*/

   // В зависимости от того, сколько элементов в векторе,
   // записываем поле размера минимальной длины.
   // Общий формат флага компресии такой:
   //                000SSCCC 
   // 
   // CCC - биты типа сжатия
   // SS  - биты типа длины вектора (00->1 байт, 01->2 или 10->4 байта)
   if( v.size() < 256 )
    {
     bin.write( &compression, sizeof(compression) );
     lem::uint8_t n8 = static_cast<lem::uint8_t>( v.size() );
     bin.write( &n8, sizeof(n8) );
    } 
   else if( v.size() < 65536 )
    {
     lem::uint8_t f = compression | 0x08; 
     bin.write( &f, sizeof(f) );
     lem::uint16_t n16 = static_cast<lem::uint16_t>( v.size() );
     bin.write( &n16, sizeof(n16) );
    } 
   else
    {
     lem::uint8_t f = compression | 0x10; 
     bin.write( &f, sizeof(f) );
     lem::uint32_t n32 = static_cast<lem::uint32_t>( v.size() );
     bin.write( &n32, sizeof(n32) );
    } 

   if( !compression ) 
    {
     // без сжатия
     bin.write( &*v.begin(), sizeof(T)*v.size() );
    }
   else if( compression==1 ) 
    {
     // последовательные приращения вмещаются в однобайтовые значения
     bin.write( &v.front(), sizeof(T) );
   
     for( Container::size_type i=1; i<v.size(); i++ )
      {
       lem::uint8_t diff = v[i]-v[i-1]-z1;
       bin.write( &diff, sizeof(diff) );
      }
    }   
   else if( compression==2 ) 
    {
     // последовательные приращения вмещаются в 4-х битовые значения
     T i0 = v.front();
     bin.write( &i0, sizeof(T) );
   
     lem::uint8_t mask=0xf0;
     lem::uint8_t pack4=0;

     int nn = (v.size()-1) + ( (v.size()-1) % 2);

     for( int i=0; i<nn; i++ )
      {
       lem::uint8_t diff=0;

       if( i<(CastSizeToInt(v.size())-1) )
        diff = v[i+1]-v[i]-z1;

       if( mask==0xf0 )
        {
         pack4 = diff << 4;
        }
       else
        {
         pack4 |= (diff & mask);
         bin.write( &pack4, sizeof(pack4) );
        }

       mask = ~mask;
      }
    }

   return;
  }


  template < class T >
  inline void Load_Compressed_Vector(
                                     Stream &bin,
                                     lem::MCollect<T> &v,
                                     bool allow_0_diff // допускаются ли в векторах одинаковые
                                                       // соседние зрачения (иначе можно немного
                                                       // улучшить сжатие)
                                    )
  {
   lem::uint8_t f=0;
   bin.read( &f, sizeof(f) );

   lem::uint8_t compression = f & 0x03;
   lem::uint8_t sizing = f & 0x18;

   const int z1   = allow_0_diff ? 0 : 1;

   const unsigned m16   = allow_0_diff ? 0x000f : 0x001f;
   const unsigned m256  = allow_0_diff ? 0x00ff : 0x01ff;

   int n; // сколько элементов в векторе

   switch( sizing )
   {
    case 0x00:
     {
      lem::uint8_t n8;
      bin.read( &n8, sizeof(n8) );
      v.reserve(n8);
      n = static_cast<int>(n8); 
      break; 
     }

    case 0x08:
     {
      lem::uint16_t n16;
      bin.read( &n16, sizeof(n16) );
      v.reserve(n16);
      n = static_cast<int>(n16); 
      break; 
     }

    case 0x10:
     {
      lem::uint32_t n32;
      bin.read( &n32, sizeof(n32) );
      v.reserve(n32);
      n = static_cast<int>(n32); 
      break; 
     }

    default: LEM_STOPIT;
   }

   switch(compression)
   {
    case 0:
     {
      v.resize(n); 
      bin.read( &*v.begin(), sizeof(T)*n );
      break;
     } 

    case 1:
     {
      T i0;
      bin.read( &i0, sizeof(i0) );
      v.push_back(i0);
   
      for( int i=1; i<n; i++ )
       {
        lem::uint8_t diff;
        bin.read( &diff, sizeof(diff) );
        i0 += (m256 & (static_cast<unsigned>(diff)+z1));
        v.push_back(i0);
       }

      break;  
     }

    case 2:
     {
      T i0;
      bin.read( &i0, sizeof(i0) );
      v.push_back(i0);
   
      lem::uint8_t mask=0xf0;
      lem::uint8_t pack4=0;

      int nn = (n-1) + ( (n-1) % 2 );
 
      for( int i=0; i<nn; i++ )
       {
        lem::int8_t diff=0;
 
        if( mask==0xf0 )
         {
          bin.read( &pack4, sizeof(pack4) );
          diff = (pack4 & mask) >> 4;
         }
        else
         {
          diff = (pack4 & mask);
         } 

        if( i<(n-1) )  
         {
          i0 += (m16&(static_cast<unsigned>(diff)+z1));
          v.push_back(i0);
         }

        mask = ~mask;
       }

      break;
     }

    default: LEM_STOPIT;
   }

   return;
  }

 } // namespace lem

#endif

