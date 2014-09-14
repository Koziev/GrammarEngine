#ifndef LEM_ZEROED__H
#define LEM_ZEROED__H
#pragma once

 #include <lem/config.h>

 // 15.08.2008 - для удобства работы с указателями добавил перегруженный operator->
 // 11.10.2008 - добавлен тип zfloat

 namespace lem
 {
  template < typename T >
  struct zeroed_ptr
  {
   T* value;

   zeroed_ptr() : value(0) {}
   zeroed_ptr( T* t ) : value(t) {}
   zeroed_ptr( const zeroed_ptr<T>& x ) : value(x.value) {}

   const zeroed_ptr<T*>& operator=( T* t ) { value=t; return *this; }
   const zeroed_ptr<T*>& operator=( const zeroed_ptr<T*>& x ) { value=x.value; return *this; }

   inline bool operator==( T* t ) const { return value==t; }
   inline bool operator!=( T* t ) const { return value!=t; }
   inline bool operator==( const zeroed_ptr<T*>& x ) const { return value==x.value; }
   inline bool operator!=( const zeroed_ptr<T*>& x ) const { return value!=x.value; }

   inline operator T*(void) const { return value; }

   inline T* operator++(int) { return value++; }
   inline T* operator--(int) { return value++; }

   inline T* operator++() { return ++value; }
   inline T* operator--() { return ++value; }

   inline const T** operator&(void) const { return &value; }
   inline       T** operator&(void)       { return &value; }

   inline const T* operator->(void) const { return value; }
   inline       T* operator->(void)       { return value; }
  };

  template < class T >
  struct zeroed
  {
   T value;

   zeroed() : value(0) {}
   zeroed( T t ) : value(t) {}
   zeroed( const zeroed<T>& x ) : value(x.value) {}

   const zeroed<T>& operator=( T t ) { value=t; return *this; }
   const zeroed<T>& operator=( const zeroed<T>& x ) { value=x.value; return *this; }

   inline bool operator==( T t ) const { return value==t; }
   inline bool operator!=( T t ) const { return value!=t; }
   inline bool operator==( const zeroed<T>& x ) const { return value==x.value; }
   inline bool operator!=( const zeroed<T>& x ) const { return value!=x.value; }

   inline operator T(void) const { return value; }

   inline T operator++(int) { return value++; }
   inline T operator--(int) { return value++; }

   inline T operator++() { return ++value; }
   inline T operator--() { return ++value; }

   inline const T* operator&(void) const { return &value; }
   inline       T* operator&(void)       { return &value; }
  };


  template < class T, T default_value >
  struct preset_value
  {
   T value;

   preset_value() : value(default_value) {}
   preset_value( const preset_value<T,default_value>& x ) : value(x.value) {}

   const preset_value<T,default_value>& operator=( T t ) { value=t; return *this; }
   const preset_value<T,default_value>& operator=( const preset_value<T,default_value>& x ) { value=x.value; return *this; }

   inline bool operator==( T t ) const { return value==t; }
   inline bool operator!=( T t ) const { return value!=t; }
   inline bool operator==( const preset_value<T,default_value>& x ) const { return value==x.value; }
   inline bool operator!=( const preset_value<T,default_value>& x ) const { return value!=x.value; }

   inline operator T(void) const { return value; }

   inline T operator++(int) { return value++; }
   inline T operator--(int) { return value++; }

   inline T operator++() { return ++value; }
   inline T operator--() { return ++value; }

   inline const T* operator&(void) const { return &value; }
   inline       T* operator&(void)       { return &value; }
  };


  typedef zeroed<bool>  zbool;
  typedef zeroed<int>   zint;
  typedef zeroed<float> zfloat;

  typedef preset_value<bool,true>  tbool;
 }

#endif

