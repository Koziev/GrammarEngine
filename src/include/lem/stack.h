// -----------------------------------------------------------------------------
// File STACK.H
//
// (c) Koziev Elijah
//
// Content:
// Шаблон Stack - контейнер типа 'СТЕК' для классов с определенным
// конструктором копирования.
//
// Расширенная по сравнению с STL stack функциональность - добавлены
// некоторые операции, но стек строится на основе только Collect'а (другими
// словами, это не адаптор STL).
// -----------------------------------------------------------------------------
//
// CD->06.10.1994
// LC->25.04.2007
// --------------

#ifndef LEM_STACK__H
#define LEM_STACK__H
#pragma once

 #include <lem/containers.h>

 namespace lem
 {
 
  template<class ITEM> class Stack : public Collect<ITEM>
  {
   public:
    Stack(void) {}

    #if defined __MINGW__ || defined LEM_GNUC
     inline typename Collect<ITEM>::size_type size(void) const { return Collect<ITEM>::size(); }
     inline const typename Collect<ITEM>::value_type& back(void) const { return Collect<ITEM>::back(); }
     inline typename       Collect<ITEM>::value_type& back(void)       { return Collect<ITEM>::back(); }
    #endif 
  
    // ************************************************************
    // Размер стека уменьшается на 1.
    // В отличие от аналога std::stack::pop(), возвращает снятый
    // с вершины стека элемент.
    // ************************************************************
    inline const ITEM pop(void)
    {
     LEM_CHECKIT_Z(size()>0);
     const ITEM x = back();
     #if defined LEM_MSC && _MSC_VER<=1200
     ReduceBy(1);
     #else 
     lem::Collect<ITEM>::ReduceBy(1);
     #endif
     return x;
    }

    // ***********************************************
    // Самые верхние ND элементов удаляются со стека.
    // ***********************************************
    inline void drop( int ND )
    {
     LEM_CHECKIT_Z(ND>=0);
     #if defined LEM_MSC && _MSC_VER<=1200
     ReduceBy(ND);
     #else
     lem::Collect<ITEM>::ReduceBy(ND);
     #endif
     return;
    }

    // ***********************************************
    // Добавление элемента на вершину стека.
    // ***********************************************
    inline void push( const ITEM& item )
    {
     #if defined LEM_MSC && _MSC_VER<=1200
     push_back(item);
     #else
     lem::Collect<ITEM>::push_back(item);
     #endif
     return;
    }

    //***********************************************************
    // Возвращаем ссылку на элемент, отстоящий на depth позиций
    // от верхушки. Если depth=0, то - ссылку на верхушку.
    //***********************************************************
    inline ITEM& top( int depth=0 )
    {
     LEM_CHECKIT_Z( int(size())-1-depth>=0);
     return at(size()-1-depth);
    }

    inline const ITEM& top( int depth=0 ) const
    {
     LEM_CHECKIT_Z( int(size())-1-depth>=0);
     return at(size()-1-depth);
    }

//    inline const ITEM& get( int i ) const { return operator[](i); }
//    inline       ITEM& get( int i )       { return operator[](i); }
  };

 } // end of namespace 'lem'

#endif
