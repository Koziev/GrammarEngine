// -----------------------------------------------------------------------------
// File MSTACK.H
//
// (c) Koziev Elijah
//
// Content:
// Шаблон MStack - контейнер типа 'СТЕК' для указателей или для элементов,
// которые могут быть корректно скопированы простым вызовом memcpy, то есть не
// содержащих полей с динамическим выделением памяти.
// -----------------------------------------------------------------------------
//
// CD->06.10.1994
// LC->11.02.2006
// --------------

#ifndef LEM_M_STACK__H
#define LEM_M_STACK__H
#pragma once

 #include <lem/containers.h>

 namespace lem
 {

 template<class ITEM> class MStack : public MCollect<ITEM>
 {
  public:
   MStack(void):MCollect<ITEM>() {}

   inline const ITEM pop(void)
   {
    LEM_CHECKIT_Z(!empty());
    const ITEM x = back();
    ReduceBy(1);
    return x;
   }

   // ***********************************************
   // Самые верхние ND элементов удаляются со стека.
   // ***********************************************
   inline void drop( int ND )
   {
    LEM_CHECKIT_Z(ND>=0);
    ReduceBy(ND);
    return;
   }

   // ***********************************************
   // Добавление элемента на вершину стека.
   // ***********************************************
   inline void push( const ITEM& item )
   {
    push_back(item);
    return;
   }

   //***********************************************************
   // Возвращаем ссылку на элемент, отстоящий на depth позиций
   // от верхушки. Если depth=0, то - ссылку на верхушку.
   //***********************************************************
   inline ITEM& top( int depth=0 )
   {
    LEM_CHECKIT_Z(n-1-depth>=0);
    return container[n-1-depth];
   }

   inline const ITEM& top( int depth=0 ) const
   {
    LEM_CHECKIT_Z( n-1-depth>=0 );
    return container[n-1-depth];
   }
 };

 } // end of namespace 'lem'

#endif
