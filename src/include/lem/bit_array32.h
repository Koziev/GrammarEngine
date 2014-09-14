// -----------------------------------------------------------------------------
// File BIT_ARRAY32.H
//
// (c) Koziev Elijah
//
// Content:
// Класс BitArray32 - хранилище для 32х однобитовых флагов в виде одного
// целочисленного поля. Позволяет хранить максимум 32 бита.
//
// См. также класс BitVector в файле lem_bitv.h, который может хранить
// произвольное количество битов.
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->16.10.2009
// --------------

#ifndef LEM_BITA32__H
#define LEM_BITA32__H
#pragma once

 #include <boost/integer/integer_mask.hpp>
 #include <lem/containers.h>
 #include <lem/streams.h>

 namespace lem
 {

  // **************************************************
  // Макс. число битов, запом. в поле BitArray32
  // **************************************************
  const int LEM_MAXCATEGORY=32;

  class BitArray32
  {
   protected:
    lem::uint32_t a; // Битовое поле.

   public:
    BitArray32(void) { a=0; }

    inline void SetData( lem::uint32_t d ) { a=d; }
    inline lem::uint32_t GetData(void) const { return a; }

    /**************************************
     Возвращаем содержимое i-го бита.
    ***************************************/
    inline bool Get( int i ) const
    {
     LEM_CHECKIT_Z( i>=0 && i<LEM_MAXCATEGORY );
     //return !!(a & (boost::high_bit_mask_t<31>::high_bit_fast>>i));
     return (a & (0x80000000U>>i))!=0;
    }

    inline bool operator()( int i ) const { return Get(i); }

    /*******************************************************
     Устанавливаем содержимое i-го бита в состояние do_set.
    ********************************************************/
    inline void Set( int i, bool b=true )
    {
     LEM_CHECKIT_Z( i>=0 && i<LEM_MAXCATEGORY );

     if(b)
      a |= (boost::high_bit_mask_t<31>::high_bit_fast>>i);  // Устанавливаем бит...
     else
      a &= ~(boost::high_bit_mask_t<31>::high_bit_fast>>i); // Очищаем бит...

     return;
    }

    inline void operator|=( const BitArray32 bits )
    { a |= bits.a; }

    inline bool operator==( const BitArray32 ba ) const
    { return ba.a==a; }

    inline bool operator!=( const BitArray32 ba ) const
    { return ba.a!=a; }

    /**********************************************************
     Возвращаем вектор индексов единичных или нулевых битов,
     в зависимости от значения аргумента f
    ***********************************************************/
    const IntCollect GetIndeces( bool f=true ) const
    {
     IntCollect res;

     for( int i=0; i<LEM_MAXCATEGORY; i++ )
      if( Get(i)==f )
       res.push_back( i );

     return res;
    }

    // Возвращает максимальный индекса единичного бита (справа)
    int MaxBit(void) const
    {
     for( int i=LEM_MAXCATEGORY-1; i>=0; i-- )
      if( Get(i)==true )
       return i;

     return -1;
    }
  };
 } // namespace 'lem'

#endif
