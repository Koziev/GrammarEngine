// -----------------------------------------------------------------------------
// File MACROS.H
//
// (c) Koziev Elijah
//
// Content:
// „асто используемые макросы-полезн€шки и константы. —окращенные форматы дл€
// часто используемых синтаксических конструкций C++.
//
// 11.05.2008 - введен макрос CastSizeToInt дл€ преобразовани€ size_t в int,
//              с контролем переполнени€ в Debug под x64.
// -----------------------------------------------------------------------------
//
// CD->03.10.1996
// LC->11.05.2008
// --------------

#ifndef LEM_DEFS___H
#define LEM_DEFS___H
#pragma once

 #include <lem/config.h> 

 #include <assert.h>


 /************************************************************************
  Useful macro to count elements in an array.
  ћакрос дл€ определени€ числа элементов в векторе. “олько дл€ векторов,
  чей размер известен компил€тору, for instance: int a[10];
 ************************************************************************/
 #if !defined DIM_A
  #define DIM_A(a) (sizeof(a)/sizeof(a[0]))
 #endif

 // "¬ечный" цикл, прерываемый по операторами в теле цикла.
 #if !defined FOREVER
  #define FOREVER while(1)
  #define LEM_FOREVER while(1)
 #endif

 #if !defined(LEM_DEBUGON)
  #if defined LEM_DEBUGGING
   #if LEM_DEBUGGING==0
    // ...
   #else
    #define LEM_DEBUGON

   #undef IFDEBUG
    #define IFDEBUG(A) (void)0
    #endif
  #endif
 #else
  #undef IFDEBUG
  #define IFDEBUG(A) A
 #endif

 #if !defined LEM_DEBUGON
  #define LEM_DEBUGOFF
  #undef IFDEBUG
  #define IFDEBUG(A) (void)0
 #endif

 // Memory deallocation macros. Also they set memory pointer to NULL,
 // that makes the debugging process easier, as we can only do 'free' once.
 #define lem_rub_off(ptr) { delete ptr; ptr=NULL; }
 #define lem_rub_off_array(ptr) { delete[] ptr; ptr=NULL; }
 #define lem_free_z(ptr) { lem_free(ptr); ptr=NULL; }

 // ƒл€ более удобной и компактной записи заголовков циклов for(...)

 // ***************************************************************
 // GNU C+ compiler often complains about non-virtual destructors
 // within a class having virtual methods.
 // ***************************************************************
 #if defined LEM_GNUC
  #define LEM_GNUC_VIRTUAL virtual
 #else
  #define LEM_GNUC_VIRTUAL
 #endif

 #define free_z(x) { free(x); x=0; }


 #if defined LEM_MSC
  #define LEM_NO_RET(arg) return arg
 #elif defined BOOST_UNREACHABLE_RETURN
  #define LEM_NO_RET(arg) BOOST_UNREACHABLE_RETURN(arg)
 #elif defined LEM_BORLAND
  #define LEM_NO_RET(arg) (void)(arg)
 #else
  #define LEM_NO_RET(arg) return arg
 #endif

 // ћакрос предназначен дл€ визуально отличимого и легкообнаруживаемого по
 // исходникам каста типа size_t в int дл€ размера контейнеров и т.д.
 #if LEM_DEBUGGING==1 || defined _DEBUG
  inline int CastSizeToInt( size_t x )
  {
   assert( (x & 0x80000000) != 0x80000000 );
   return (int)x;
  }
 #else
  // в релиз-версии макрос раскрываетс€ без накладных расходов
  #define CastSizeToInt(x) ((int)(x))
 #endif


#endif
