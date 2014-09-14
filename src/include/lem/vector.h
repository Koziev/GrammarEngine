// -----------------------------------------------------------------------------
// File VECTOR.H
//
// (c) Koziev Elijah
//
// Content:
// Многокомпонентные вектора в общематематическом смысле (не для целей
// машинной графики).
//
// ВНИМАНИЕ !!! Данный класс не имеет никакого отношения к классам из машинной
// графики, в частности, классам Vector2d и Vector3d.
//
// Количество элементов для данного класса задается динамически.
// -----------------------------------------------------------------------------
//
// CD->03.07.1995
// LC->13.08.2006
// --------------

#pragma once
#ifndef LEM_MATH_VECTOR__H
#define LEM_MATH_VECTOR__H

 #include <lem/math/real.h>

 namespace lem
 {

  template < class T >
  class BaseVector
  {
   private:
    int nitems; // Число элементов.
    T *elem; // Элементы вектора.

   public:
    // ---------------------------------------
    // Пустой вектор, не содержащий элементов.
    // ---------------------------------------
    BaseVector(void)
    {
     nitems=0;
     elem=NULL;
    }


    // -----------------------------------------------------------------------
    // Создаем вектор заданного размера и инициализируем его элементы.
    // Если c==NULL, то элементы устанавливаются нулевыми. В противном случае,
    // переписываем содержимое вектора элементов, на которые указывает c.
    // -----------------------------------------------------------------------
    BaseVector( int N, const T *c=NULL )
    {
     LEM_CHECKIT_Z(N!=0); 

     elem = new T[nitems=N];

     if( !!c )
      // По умолчанию инициализируем компоненты нулями.
      memcpy( elem, c, sizeof(T)*nitems );
     else
      memset( elem, 0, sizeof(T)*nitems );

     return;
    }

    // ------------------------
    // Конструктор копирования.
    // ------------------------
    BaseVector( const BaseVector& v )
    {
     LEM_CHECKIT_Z(v.nitems>0);
     LEM_CHECKIT_Z(v.elem);

     elem = new T[nitems=v.nitems];
     memcpy( elem, v.elem, sizeof(T)*nitems );
     return;
    }


    BaseVector( int N, T c0, ... )
    {
     va_list argptr;

     LEM_CHECKIT_Z(N>0);

     elem = new T[nitems=N];

     REAL next=c0;
     va_start( argptr, c0 );

     for( int i=0; i<nitems; i++ )
      {
       elem[i]=next;
       next=(REAL)va_arg( argptr, REAL );
      }

     va_end(argptr);
     return;
    }

    ~BaseVector(void)
    {
     delete[] elem;
     nitems=0;
     return;
    }

   // ---------------------------------
   // Реализация операции присваивания.
   // ---------------------------------
   BaseVector& operator=( const BaseVector& p )
   {
    if( &v!=this ) // Помни об x=x !
     {
      if(nitems!=v.nitems) // Если размеры разные, выделим соотв. блок памяти.
       {
        delete[] elem;
        elem = new T[nitems=v.nitems];
       }

      lem_memcpy( elem, v.elem, sizeof(T)*nitems );
     }

    return *this;
   }


   inline int size(void) const { return nitems; }

   // --------------------------------------
   // Операция доступа к элементам вектора
   // с проверкой выхода индекса за пределы.
   // --------------------------------------
   inline T& operator[]( int i )
   {
    LEM_CHECKIT_Z( i>=0 && i<nitems );
    return elem[i];
   }

   inline const T& operator[]( int i ) const
   {
    LEM_CHECKIT_Z( i>=0 && i<nitems );
    return elem[i];
   }

   inline T get( int i ) const
   { LEM_CHECKIT_Z(i>=0 && i<nitems); return elem[i]; }


   // ---------------------
   // Нормализация вектора.
   // ---------------------
   void normalize(void)
   {
    LEM_CHECKIT_Z(nitems>0);
    LEM_CHECKIT_Z(elem);

    const REAL l=length();
    for( int i=nitems-1; i>=0; i-- )
     elem[i] /= l;

    return;
   }

   // ------------------------------------
   // Модуль вектора - квадратный
   // корень из суммы квадратов элементов.
   // ------------------------------------
   T length(void) const
   {
    LEM_CHECKIT_Z(nitems>0);
    LEM_CHECKIT_Z(elem);

    REAL s=TOREAL(0.);
    for( int i=nitems-1; i>=0; i-- )
     s += qpow2(elem[i]);

    return qsqrt(s);
   }

   // ---------------------------------------------------------------------------
   // Сложение векторов одного порядка.
   //
   // Если длина векторов разная, выполнение программы прерывается (при отладке).
   // ---------------------------------------------------------------------------
   const BaseVector<T> operator+( const BaseVector<T>& b ) const
   {
    const int aord=a.size();

    LEM_CHECKIT_Z(aord==b.size());
    LEM_CHECKIT_Z(aord>0);
    LEM_CHECKIT_Z(a.elem);
    LEM_CHECKIT_Z(b.elem);

    Vector<T> res(aord);

    for( int i=aord-1; i>=0; i-- )
     res.elem[i] = a.elem[i]+b.elem[i];

    return res;
   }


   // -----------------------------------
   // Разность векторов одинаковой длины.
   // -----------------------------------
   const BaseVector<T> operator-( const BaseVector<T>& b ) const
   {
    const int aord=a.size();

    LEM_CHECKIT_Z(aord==b.size());
    LEM_CHECKIT_Z(aord>0);
    LEM_CHECKIT_Z(a.elem);
    LEM_CHECKIT_Z(b.elem);

    Vector<T> res(aord);

    for( int i=aord-1; i>=0; i-- )
     res.elem[i] = a.elem[i]-b.elem[i];

    return res;
   }


   // -------------------------------
   // Проверяем вектора на равенство.
   // -------------------------------
   bool operator==( const BaseVector<T> &b ) const
   {
    const int aord=a.size();

    if( aord!=b.size() )
     return false;

    // Если хоть один элемент не совпадает,
    // то вектора считаются различными.

    for( int i=aord-1; i>=0; i-- )
     if( a.elem[i]!=b.elem[i] )
      return false;

    return true;
   }

   // -------------------------------
   // Проверяем неравенство векторов.
   // -------------------------------
   bool operator!=( const BaseVector<T> &b ) const
   {
    const int aord=a.size();
    const int bord=b.size();

    if( aord!=bord )
     return true;

    // Если хоть один элемент не совпадает,
    // то вектора не равны и условие выполнено.
    for( int i=aord-1; i>=0; i-- )
     if( a.elem[i]!=b.elem[i] )
      return true;

    return false;
   }

  };


  typedef BaseVector<lem::Math::REAL> RVector;

 } // namespace lem
#endif
