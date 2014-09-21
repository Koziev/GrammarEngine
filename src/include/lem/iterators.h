// -----------------------------------------------------------------------------
// File LEM_ITER.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2003
//
// Content:
// Basic iterator for LEM containers.
// -----------------------------------------------------------------------------
//
// CD->15.10.2003
// LC->29.09.2005
// --------------

#ifndef LEM_ITERATOR__H
#define LEM_ITERATOR__H
#pragma once

 #include <iterator>
 #include <lem/config.h>
 #include <lem/quantors.h>

 namespace lem
 {
  template < class T, class Container >
  class StlIterator
  {
   public:
    typedef T value_type;
    typedef int difference_type; // type to hold difference between the items
    typedef T* pointer;
    typedef T& reference;
    #if defined LEM_WATCOM 
    typedef random_access_iterator_tag iterator_category;
    #else
    typedef std::random_access_iterator_tag iterator_category;
    #endif  

   protected:
    int i;
    Container *ptr;

   public:
    StlIterator(void) { i=UNKNOWN; ptr=NULL; }

    StlIterator( int Pos, Container *pContainer )
    { i=Pos; ptr=pContainer; }

    inline int index(void) const { return i; }

    inline StlIterator< T, Container >& operator++(void)
    {
     i++;
     return *this;
    }

    inline StlIterator< T, Container >& operator--(void)
    {
     i--;
     return *this;
    }

    inline StlIterator< T, Container > operator+( int a )
    { return StlIterator<T,Container>( i+a, ptr ); }

    inline StlIterator< T, Container > operator-( int a )
    { return StlIterator<T,Container>( i-a, ptr ); }

    inline T& operator*(void) { return (*ptr)[i]; }
    inline T* operator->(void) { return &((*ptr)[i]); }

    inline bool operator==( const StlIterator< T, Container > &x ) const
    { return i==x.i; }

    inline bool operator!=( const StlIterator< T, Container > &x ) const
    { return i!=x.i; }

    inline bool operator>( const StlIterator< T, Container > &x ) const
    { return i>x.i; }

    inline bool operator<( const StlIterator< T, Container > &x ) const
    { return i<x.i; }
  };

  template < class T, class Container >
  inline int operator-(
                       const StlIterator<T,Container> &a,
                       const StlIterator<T,Container> &b
                      )
  { return a.index() - b.index(); }


  // Spezialization for StlIterator
/*
  template < class T, class Container >
  struct iterator_traits < StlIterator< T, Container > >
  {
   typedef random_access_iterator_tag iterator_category;
   typedef T value_type;
   typedef int difference_type; // type to hold difference between the items
   typedef T* pointer;
   typedef T& reference;
  };
*/
 } // namespace 'lem'

  namespace lem
  {
   // ****************************************
   // Forward declaration.
   // ****************************************
   template < class T > class MCollect;
  }

#endif
