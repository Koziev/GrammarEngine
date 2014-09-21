// -----------------------------------------------------------------------------
// File LEM_CYCS.H
//
// (c) Koziev Elijah
//
// Content:
// Шаблон CyclicStack - контейнер типа 'СТЕК' для указателей или для
// элементов. Отличается от родительского класса lem::Stack тем, что для него
// определен макимальный размер стека. Как только число добавляемых элементов
// превышает эту границу, класс начинает автоматически выталкивать элементы
// из хвоста при помещении в голову новых. Эта операция реализована без
// фактического перемещения элементов в контейнере за счет того, что индекс
// первого элемента в хвосте динамически изменяется, то есть введено понятие
// внешней, логической индексации, и внутренней физической.
// -----------------------------------------------------------------------------
//
// CD->02.04.1999
// LC->12.10.2005
// --------------

#ifndef LEM_CYCLICSTACK__H
#define LEM_CYCLICSTACK__H
#pragma once

 #include <lem/stack.h>

 namespace lem
 {
  template<class ITEM> class CyclicStack : public Stack<ITEM>
  {
   private:
    int maxn; // Максимальное допустимое число хранимых элементов.
    int i0;   // Физический индекс элемента с внешним индексом '0'.

    // Две операции заблокированы.
    const ITEM pop(void);
    void drop( int ND );
    void push_back( const ITEM &x );

   public:
    #if defined __MINGW__ || defined LEM_GNUC
    typedef typename Stack<ITEM>::size_type size_type;
    
    inline size_type size(void) const { return Stack<ITEM>::size(); }  
    #endif    

   public:
    CyclicStack():Stack<ITEM>()
    { maxn=1; i0=0; }

    inline void SetMax( int nItems ) { maxn=nItems; }


    // #####################################################################
    // Операции явной индексации должны быть перегружены у базового класса,
    // так как мы ввели логическую индексацию.
    // #####################################################################
    inline ITEM& operator[]( int i )
    { LEM_CHECKIT_Z(i>=0 && i<size()); return Stack<ITEM>::operator[]((i+i0)%size()); }

    inline const ITEM& operator[]( int i ) const
    { LEM_CHECKIT_Z(i>=0 && i<size()); return Stack<ITEM>::operator[]((i+i0)%size()); }

    inline const ITEM& get( int i ) const
    { LEM_CHECKIT_Z(i>=0 && i<size()); return Stack<ITEM>::operator[]((i+i0)%size()); }

    inline const ITEM& back(void) const
    { LEM_CHECKIT_Z(size()>0); return Stack<ITEM>::operator[]((size()-1+i0)%size()); }

    inline       ITEM& back(void)
    { LEM_CHECKIT_Z(size()>0); return Stack<ITEM>::operator[]((size()-1+i0)%size()); }

    // ***********************************************
    // Добавление элемента на вершину стека.
    // ***********************************************
    inline void push( const ITEM& item )
    {
     if( size() >= maxn )
      {
       // --------------------------------------------------------------------
       // Один элемент из хвоста нужно убрать и сдвинуть элементы в стеке.
       // Вместо явного перемещения мы просто считаем, что элемент с нулевым
       // внешним индексом теперь переместился на 1 шаг к голове:
       //
       //  Добавляем 555:
       //
       //  было:
       //       000 111 222 333 444
       //        |               |
       //        текущий нулевой текущая вершина
       //
       //       555 111 222 333 444
       //        |   |
       //        |   новый нулевой
       //        |
       //        текущая вершина
       //
       // --------------------------------------------------------------------
       Stack<ITEM>::operator[](i0++) = item;
      }
     else
      Stack<ITEM>::push_back(item);

     return;
    }

    //***********************************************************
    // Возвращаем ссылку на элемент, отстоящий на depth позиций
    // от верхушки. Если depth=0, то - ссылку на верхушку.
    //***********************************************************
    inline ITEM& top( int depth=0 )
    {
     LEM_CHECKIT_Z(size()-1-depth>=0);
     return Stack<ITEM>::get( (size()-1-depth+i0)%size() );
    }

    inline const ITEM& top( int depth=0 ) const
    {
     LEM_CHECKIT_Z(size()-1-depth>=0);
     return Stack<ITEM>::get( (size()-1-depth+i0)%size() );
    }
  };

 } // end of namespace 'lem'

#endif
// -------------------------- End Of File [LEM_CYCS.H] -------------------------
