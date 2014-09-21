// -----------------------------------------------------------------------------
// File BIT_VECTOR.H
//
// (c) Koziev Elijah
//
// Content:
//  ласс BitVector - битовый контейнер. ѕостроен на основе контейнерного
// класса MCollect. ќтдельные биты группируютс€ в блоки по 32 штуки и
// запоминаютс€ как uint32_t числа. ћетоды класса MCollect переопределены с
// тем, чтобы задавать число битов, а не число упакованных битовых блоков, до
// которых пользователю нет дела.
//
// Ётот контейнер может хранить произвольное число битов. —уществует другой
// контейнер, который хранит максимум 32 бита, но работает намного быстрее -
// см. класс BitArray32 в файле lem_bita.h
// -----------------------------------------------------------------------------
//
// CD->14.06.1996
// LC->15.10.2009
// --------------

#ifndef LEM_BITVECTOR__H
#define LEM_BITVECTOR__H
#pragma once

 #include <lem/containers.h>
 #include <lem/streams.h>

 namespace lem
 {
  using lem::uint32_t;
  
 // ***************************************************************
 // ¬озвращает число целых чисел (по 4 байта), байтов, необходимых
 // дл€ хранени€ n битов. ƒл€ 0 битов результат - 0 байтов, дл€
 // 1...8 битов - 1 байт, и так далее.
 // ***************************************************************
 inline lem::Container::size_type lbv_nblock( lem::Container::size_type n )
 {
  return n<32 ? (n ? 1 : 0) : ( n%32 ? n/32+1 : n/32 );
 }

 class BitVector;

 // ********************************************************************
 //  ласс дл€ внутреннего использовани€ - ссылка на единичный бит, дл€
 // организации работы перегруженного оператора [] класса BitVector.
 // ********************************************************************
 class BitReference
 {
  private:
   const lem::Container::size_type ibit;
   BitVector *v;

  public:
   BitReference(void):ibit(0),v(NULL) {};
   BitReference( lem::Container::size_type iBit, BitVector *V )
   :ibit(iBit),v(V) {};

   void operator=( bool Bit );
 };

 class BitVector : public MCollect<uint32_t>
 {
  private:
   size_type nbit; // „исло работающих битов (всегда меньше, чем число работающих
                   // битовых блоков.

   inline lem::Container::size_type Blocks32(void) const { return MCollect<uint32_t>::size(); }

   void SaveBin_Compressed( lem::Stream &bin, int Depth ) const;

  public:
   BitVector( lem::Container::size_type n0=0 )
   :MCollect<uint32_t>( lbv_nblock(n0) )
   {
    nbit = n0;
    Nullify();
    return;
   }

   BitVector( const BitVector& bv ) : MCollect<uint32_t>(bv)
   { nbit=bv.nbit; }

   inline BitVector& operator=( const BitVector& bv )
   {
    if( this==&bv )
     return *this;

    MCollect<uint32_t>::operator=(bv);
    nbit=bv.nbit;
    return *this;
   }

//   inline void AddAll( int nBit )
//   {
//    MCollect<uint32_t>::AddAll( lbv_nblock(nbit=nBit) );
//    return;
//   }

   inline void reserve( lem::Container::size_type nBit )
   {
    MCollect<uint32_t>::reserve( lbv_nblock(nbit=nBit) );
    return;
   }

   inline void resize( lem::Container::size_type nBit )
   {
    MCollect<uint32_t>::resize( lbv_nblock(nbit=nBit) );
    return;
   }

   inline void ReshapeBy( lem::Container::size_type nBit )
   {
    MCollect<uint32_t>::ReshapeBy( lbv_nblock(nBit) );
    nbit += nBit;
    return;
   }

   inline BitReference operator[]( lem::Container::size_type ibit )
   { return BitReference(ibit,this); }

   // ************************************************
   // ”станавливаем i-ый бит в состо€ние bit.
   // ************************************************
   inline void set( size_type i, bool bit )
   {
    LEM_CHECKIT_Z( i<nbit );
    const size_type iblock = i/32;
    const uint32_t  maska  = uint32_t( 0x80000000u ) >> (i%32);

    if(bit)
     get_Container()[iblock] |= maska;
    else
     get_Container()[iblock] &= ~maska;

    return;
   }

   // ********************************************
   // ¬озвращает состо€ние i-го бита.
   // ********************************************
   inline bool get( size_type ibit ) const
   {
    LEM_CHECKIT_Z( ibit<nbit );
    const size_type iblock   = ibit/32;
    const uint32_t maska = uint32_t( 0x80000000u ) >> (ibit%32);
    return ( MCollect<uint32_t>::get(iblock)&maska)!=0;
   }

   // ****************************************************
   // ¬озвращаем число хранимых битов.
   // ****************************************************
   inline size_type size(void) const { return nbit; }

   void Add( long nbit, bool bit );

   // *************************************************
   // ƒобавл€етс€ еще один бит с заданным значением.
   // *************************************************
   inline void push_back( bool Bit )
   {
    if( capacity()*32 <= nbit )
     MCollect<uint32_t>::push_back(0);

    size_type ibit=nbit;
    nbit++;

    set( ibit, Bit );
    return;
   }

   int find( int len ) const;

   inline void SetAll( bool Bit )
   {
    if(Bit)
     SetBits( 0xff );
    else
     Nullify();

    return;
   }

   bool IsThere_1(void) const;
   bool IsThere_0(void) const;

   inline void SetAll_1(void) { SetBits(0xff); }
   inline void SetAll_0(void) { SetBits(0);    }

   void LoadBin( lem::Stream &bin );

   void SaveBin( lem::Stream &bin ) const;

   // —охран€ет содержимое вектора со сжатием, благодар€ чему
   // разреженные векторы могут занимать значительно меньше места 
   // на диске.
   void SaveBin_RLE( lem::Stream &bin, bool Compress ) const;
   void LoadBin_RLE( lem::Stream &bin );
 };

 inline void BitReference::operator=( bool Bit )
 { v->set(ibit,Bit); }

 } // namespace 'lem'

#endif
