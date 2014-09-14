// -----------------------------------------------------------------------------
// File SET.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Класс BaseSet - неповторяющийся набор элементов.
// -----------------------------------------------------------------------------
//
// CD->12.08.2002
// LC->19.04.2007
// --------------

#ifndef LEM_SET__H
#define LEM_SET__H
#pragma once

 #include <lem/containers.h>

 namespace lem
 {

 template <class ITEM>
 class BaseSet : public Collect<ITEM>
 {
  private:
   void push_back( const ITEM& ); // hidden!
   
  public:
   #if defined LEM_GNUC
   typedef typename Collect<ITEM>::size_type size_type;
   #else    
   typedef Collect<ITEM>::size_type size_type;
   #endif     

   #if defined __MINGW__ || defined LEM_GNUC
   inline size_type size(void) const { return Collect<ITEM>::size(); }
   #endif    

  public:
   BaseSet(void) {}

   BaseSet( int n0 ) : Collect<ITEM>(n0) {}

   // ********************************************************
   // Добавляем только если такого элемента еще нет в списке.
   // ********************************************************
   inline void insert( const ITEM& a )
   {
    for( size_type i=0; i<size(); i++ )
     if( operator[](i)==a )
       return;

    Collect<ITEM>::push_back(a);
    return;
   }
 };


 template <class ITEM>
 class BaseMSet : public MCollect<ITEM>
 {
  public:
   #if defined LEM_GNUC
   typedef typename MCollect<ITEM>::size_type size_type;
   #else    
   typedef MCollect<ITEM>::size_type size_type;
   #endif     

  private:
   void push_back( const ITEM& ); // hidden!

  public:
   BaseMSet(void) {}
   BaseMSet( int n0 ) : MCollect<ITEM>(n0) {}

   // ********************************************************
   // Добавляем только если такого элемента еще нет в списке.
   // ********************************************************
   inline void insert( const ITEM& a )
   {
    for( size_type i=0; i<MCollect<ITEM>::size(); i++ )
     if( MCollect<ITEM>::operator[](i)==a )
       return;

    MCollect<ITEM>::push_back(a);
    return;
   }
 };

 } // namespace 'lem'

#endif
