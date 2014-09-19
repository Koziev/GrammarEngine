// -----------------------------------------------------------------------------
// File MSET.H
//
// (c) Koziev Elijah
//
// Content:
// Класс MSet - неповторяющийся набор элементов (аналог std::set).
// -----------------------------------------------------------------------------
//
// CD->01.02.2002
// LC->26.03.2009
// --------------

#ifndef LEM_MSET__H
#define LEM_MSET__H
#pragma once

 #include <lem/containers.h>

 namespace lem
 {

 template <class ITEM>
 class MSet : public MCollect<ITEM>
 {
  private:
   void push_back( const ITEM& ); // hidden!
   
  public:
   #if defined LEM_GNUC
   typedef typename MCollect<ITEM>::size_type size_type;     
   #else
   typedef MCollect<ITEM>::size_type size_type;     
   #endif                   
   
   #if defined __MINGW__ || defined LEM_GNUC
    inline typename MCollect<ITEM>::size_type size(void) const { return MCollect<ITEM>::size(); } 
   #endif    

  public:
   MSet(void):MCollect<ITEM>() {}

   MSet( int n0 ):
   MCollect<ITEM>(n0) {}

   // ********************************************************
   // Добавляем только если такого элемента еще нет в списке.
   // ********************************************************
   inline void insert( const ITEM& a )
   {
    #if defined LEM_GNUC
    typedef typename MCollect<ITEM>::size_type SZ;     
    #else
    typedef MCollect<ITEM>::size_type SZ;     
    #endif                   
   
    for( SZ i=0; i<size(); i++ )
     if( operator[](i)==a )
      return;

    MCollect<ITEM>::push_back(a);
    return;
   }

   void insert( const lem::MSet<ITEM> &src )
   {
    for( lem::Container::size_type i=0; i<src.size(); ++i )
     insert( src[i] );

    return;
   }
 };

 } // namespace 'lem'

#endif
