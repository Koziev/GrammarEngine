#ifndef LEM_INTEGER__H
#define LEM_INTEGER__H
#pragma once

 #include <lem/config.h>
 #include <limits.h>

 #if defined LEM_WXWIDGETS
  #include <wx/wx.h>
 #endif
 
 #if defined LEM_QT
  #include <QtGlobal>
 #endif

 namespace lem
 {
  #if defined LEM_MSC

   typedef __int64 int64_t;

   #if _MSC_VER>1200
    typedef __int32 int32_t;
   #else
    typedef int int32_t;
   #endif

   typedef __int16 int16_t;
   typedef __int8  int8_t;

   typedef unsigned __int64 uint64_t;
   typedef unsigned __int16 uint16_t;

   #if _MSC_VER>1200
    typedef unsigned __int32 uint32_t;
   #else
    typedef unsigned int uint32_t;
   #endif

   typedef unsigned __int8  uint8_t;

   #define LEM_INT64

   #if _MSC_VER>1200
    #define lemUL(x) x##UL 
    #define lemLL(x) x##LL
   #else
    #define lemLL(x) x
    #define lemUL(x) x##U 
   #endif
  
  #elif defined LEM_BORLAND

   typedef __int64 int64_t;
   typedef __int32 int32_t;
   typedef __int16 int16_t;
   typedef __int8  int8_t;

   typedef unsigned __int64 uint64_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef unsigned __int8  uint8_t;

   #define lemLL(x) (x##i64)
   #define lemUL(x) (x##ui64)

   #define LEM_INT64

  #elif defined LEM_QT

   typedef qint64 int64_t;
   typedef qint32 int32_t;
   typedef qint16 int16_t;
   typedef qint8  int8_t;

   typedef quint64 uint64_t;
   typedef quint32 uint32_t;
   typedef quint16 uint16_t;
   typedef quint8  uint8_t;

   #define lemLL(x) Q_INT64_C(x)
   #define lemUL(x) Q_UINT64_C(x)

   #define LEM_INT64

  #elif defined LEM_WXWIDGETS

   typedef wxInt64 int64_t;
   typedef wxInt32 int32_t;
   typedef wxInt16 int16_t;
   typedef wxInt8  int8_t;

   typedef wxUint64 uint64_t;
   typedef wxUint16 uint16_t;
   typedef wxUint32 uint32_t;
   typedef wxUint8  uint8_t;

   #define lemLL(x) wxLL(x)
   #define lemUL(x) wxUL(x)

   #define LEM_INT64

  #else

   typedef long long int64_t;
   typedef int int32_t;
   typedef short int16_t;
   typedef char int8_t;

   typedef unsigned long long uint64_t;
   typedef unsigned int       uint32_t;
   typedef unsigned short     uint16_t;
   typedef unsigned char      uint8_t;

   #define lemLL(x) (x##LL)
   #define lemUL(x) (x##UL)

   #define LEM_INT64

  #endif

  const int8_t int8_max   = 0x7f;
  const int8_t int8_min   = ((int8_t)0x80);

  const uint8_t uint8_min   = 0;
  const uint8_t uint8_max   = 0xffu;

  const int16_t int16_max   = 0x7fff;
  const int16_t int16_min   = ((int16_t)0x8000);

  const uint16_t uint16_max = 0xffffU;
  const uint16_t uint16_min = 0x0000U;

  const uint32_t uint32_max = 0xffffffffUL;
  const uint32_t uint32_min = 0x00000000UL;

  const int32_t int32_max   = 0x7fffffffUL;
  const int32_t int32_min   = ((int32_t)0x80000000L);

  #if defined LEM_INT64
   const int64_t int64_max = lemLL(0x7fffffffffffffff);
   const int64_t int64_min = ((int64_t)lemLL(0x8000000000000000));
   const uint64_t uint64_max = lemLL(0xffffffffffffffff);//_UI64_MAX;
  #endif

  const int int_max = INT_MAX; 
  const int int_min = INT_MIN; 

  typedef int          int_t;
  typedef unsigned int uint_t;

  #if defined LEM_16
   const int size_t_max = uint16_max;
  #elif defined LEM_32
   const int size_t_max = uint32_max;
  #elif defined LEM_64
   #if defined LEM_MSC
   const size_t size_t_max = uint32_max;
   #else
   const size_t size_t_max = uint64_max;
   #endif
  #endif

 } // namespace lem

#endif
