// CD->11.02.2007
// LC->13.04.2007
// --------------

#ifndef LEM_ILIST__H
#define LEM_ILIST__H
#pragma once

 #include <lem/containers.h>

 namespace lem
 {
  // *************************************
  // Интерфейс для всевозможных списков.
  // *************************************
  template < class T >
  class IList
  {
   public:
    typedef T value_type;
    typedef lem::Container::size_type size_type;

   public:
    IList(void) {}

    virtual bool IsFixedSize(void) const=0;
    virtual bool IsReadOnly(void) const=0;
    virtual void Clear(void)=0;
    virtual bool Empty(void)=0;
    virtual typename IList<T>::size_type Count(void) const=0;
    virtual void SetCur( typename IList<T>::size_type i )=0;
    virtual typename IList<T>::size_type GetCur(void)=0;
 
    virtual void Add( const T &x )=0;
    virtual bool Contains( const T& x ) const=0;
    virtual typename IList<T>::size_type IndexOf( const T& x ) const=0;
    virtual void Insert( typename IList<T>::size_type i, const T& x )=0;
    virtual void RemoveAt( typename IList<T>::size_type i )=0;
    virtual void Remove( const T& x )=0;

    virtual const T& Get( typename IList<T>::size_type i ) const=0;
    virtual       T& Get( typename IList<T>::size_type i )      =0;
  };
 } // namespace lem

#endif
