// -----------------------------------------------------------------------------
// File QARRAY.H
//
// (c) Koziev Elijah
//
// Content:
// Класс BaseArray - вектор-шаблон, хорошо подходит для работы с математическими
// векторами чисел. Позволяет задавать начальное значение индекса явно (а не
// полагать его равным 0, как для других контейнеров).
//
// Класс QCArray - добавляет к предыдущему контейнеру операции сравнения.
// -----------------------------------------------------------------------------
//
// CD->21.05.1996
// LC->19.04.2007
// --------------

#ifndef LEM_BaseArray__H
#define LEM_BaseArray__H
#pragma once

 #include <lem/containers.h>

 namespace lem
 {

 /****************************************************************************
  Чтобы в процессе математических вычислений не ковыряться с динамической
  памятью, а оное серьезно повышает вероятность ошибок, лучше использовать
  класс BaseArray (или производные от него), который инкапсулирует всю возню
  с глобальной кучей. Сам класс LemBaseArray является наследником MCollect и
  предоставляет таким образом обширный набор сервисных методов дл
  динамического изменения своего размера.

  !!! Мы рассматриваем объекты типа ITEM как не выделяющие себе динамическую
      память. Кроме того, принимаем, что нулевые значения получаются простым
      занулением всех битов поля ITEM. Подробнее смотрите класс MCollect
      в файле [lem_marr.h].
 ****************************************************************************/
 template <class ITEM>
 class BaseArray : public MCollect<ITEM>
 {
  protected:
   int i0,in; // Левый и правый граничные индексы. Сами значения i0 и in
              // также являются корректными индексами.

   inline void Init( int I0, int In, const ITEM *A=NULL )
   {
    LEM_CHECKIT_Z( I0>=0 && In>=0 );

    if( I0>In )
     {
      // Создаем полностью пустой вектор - он не содержит
      // ни одного элемента. Обращаю внимание, что при вызове
      // Init( 0, 0, NULL ) вектор БУДЕТ состоять из ОДНОГО элемента.
      // Чтобы получить пустой вектор, надо делать вызов Init( 0, -1, NULL )
      i0=I0;
      in=I0-1;
     }
    else
     {
      // Общее число элементов в векторе.
      const int N = (in=In) - (i0=I0) + 1;

      // Выделяем необходимое место.
      AddAll(N);

      if( A!=NULL )
       {
//        LEM_LOOP( i, N )
        ::memcpy( (void*) MCollect<ITEM>::get_Container(), (const void*)A, (size_t)sizeof(ITEM)*N );
       }
      else
       {
        // Обнуляем его.
        MCollect<ITEM>::Nullify();
       }
     }

    return;
   }

/*
   inline void Init( const BaseArray<ITEM>& q )
   {
    MCollect<ITEM>::Init(q);

    i0 = q.i0;
    in = q.in;

    return;
   }
*/

   inline int norm( int i ) const
   {
    LEM_CHECKIT_Z( i>=i0 && i<=in );
    return i-i0;
   }

  
  public:
   #if defined LEM_GNUC
   typedef typename MCollect<ITEM>::size_type size_type;
   #else
   typedef MCollect<ITEM>::size_type size_type;
   #endif  

   #if defined __MINGW__ || defined LEM_GNUC
   inline size_type size(void) const { return MCollect<ITEM>::size(); }
   #endif    
  
  
  public:
   BaseArray(void):MCollect<ITEM>()
   {
    Init(0,0,NULL);
    Again();
    return;
   }

   /***************************************************************************
    Особое внимание на этот конструктор: он позволяет сразу задать
    граничные значения индекса ОТ-ДО включительно. Итак, сразу после
    отработки конструктора к элементам вектора можно обращаться.

    Конструктор создаёт вектор элементов, индексы котрых начинаются с From
    и идут до To включительно. Обращение по индексам i<From и i>To будет
    считаться некорректным и возможно вызовет выдачу диагностики. Входной
    аргумент A указывает на вектор инициализирующих значений. Если A=NULL,
    то инициализации не производится. Обращаю внимание, что при инициализации
    элемент с индексом From будет установлен как A[0], элемент From+1 как
    A[1], и так далее. Внешний код полностью сохраняет контроль над указателем
    A, и может освободить его. Кроме того, A может указывать на вектор
    статических данных.
   ****************************************************************************/
   BaseArray( int I0, int In, const ITEM *A=NULL )
   :MCollect<ITEM>()
   { Init(I0,In,A); }

   // *************************************************************************
   // Единственным отличием от предыдущего конструктора является принимаема
   // нумерация элементов - от 0 до NI, так что NI задает количество элементов
   // в векторе.
   // *************************************************************************
   BaseArray( int NI, const ITEM *A=NULL )
   :MCollect<ITEM>()
   { Init(0,NI-1,A); }

   // ******************************************************************
   // Создается вектор элементов с заданным диапазоном индексов и каждый
   // элемент получает указанное значение BY.
   // ******************************************************************
   BaseArray( int I0, int In, const ITEM& BY )
   :MCollect<ITEM>()
   {
    Init(I0,In,NULL);

    for( int i=0; i<size(); i++ )
     MCollect<ITEM>::operator[](i) = BY;

    return;
   }

   BaseArray( const BaseArray<ITEM>& q )
   :MCollect<ITEM>(q)
   {
    i0 = q.i0;
    in = q.in;
   }

   BaseArray<ITEM>& operator=( const BaseArray<ITEM>& q )
   {
    MCollect<ITEM>::operator=(q); 
    i0 = q.i0;
    in = q.in;
    return *this;
   }

   /***************************************************
    Всем элементам вектора присваивается значение k.
   ****************************************************/
   BaseArray<ITEM>& operator=( const ITEM& a )
   {
    #if defined LEM_GNUC
    typedef typename BaseArray<ITEM>::size_type SZ;
    #else
    typedef BaseArray<ITEM>::size_type SZ;
    #endif  
   
    for( SZ i=0; i<size(); i++ )
     operator[](i)=a;

    return *this;
   }

  inline int GetFrom(void) const { return i0; }
  inline int GetTo(void)   const { return in; }

  // Оператор добавления пришлось переопределить, так как у нас есть свое
  // поле граничного значения индекса 'in'.
  inline void Add( const ITEM& a )
  {
   MCollect<ITEM>::push_back(a);
   in++;
   return;
  }

//  inline BaseArray<ITEM>& operator<<( const ITEM& a )
//  {
//   Add(a);
//   return *this;
//  }

//  inline BaseArray<ITEM>& operator<<( const BaseArray<ITEM>& a )
//  {
//   ReshapeBy(a.size() );
//   LEM_LOOP( i, a.size() )
//    Add(a(i));
//
//   return *this;
//  }

  inline void Remove( int i )
  {
   MCollect<ITEM>::Remove(i-i0);
   in--;
   return;
  }

  // ***********************************************************************
  // С помощью этого метода можно создать пустой вектор, вообще не содержащий
  // элементов. Обращаю внимание, что по умолчанию конструктор создаст вектор
  // с одним элементом!
  // ***********************************************************************
  inline void Again(void)
  {
   MCollect<ITEM>::clear();
   in=i0-1;
   return;
  }

  inline void AddAll( int N )
  {
   MCollect<ITEM>::resize( size() + N );
   // Считаем, что i0 не меняется.
   in=i0+N-1;
   return;
  }

  inline ITEM& operator[]( int i ) { return MCollect<ITEM>::operator[](norm(i)); }
  inline const ITEM& operator[]( int i ) const { return MCollect<ITEM>::operator[](norm(i)); }

  inline const ITEM& get( int i ) const { return MCollect<ITEM>::operator[](norm(i)); }
  inline const ITEM& operator()( int i ) const { return MCollect<ITEM>::operator[](norm(i)); }

  inline bool operator==( const BaseArray<ITEM> &x ) const
  {
   if( i0!=x.i0 || in!=x.in )
    return false;

   for( int i=0; i<size(); i++ )
    if( MCollect<ITEM>::operator[](i) != static_cast<const MCollect<ITEM>&>(x)[i] )
     return false;

   return true;
  }

  inline bool operator!=( const BaseArray<ITEM> &x ) const
  {
   if( in!=x.in || i0!=x.i0 )
    return true;

   for( int i=0; i<size(); i++ )
    if( MCollect<ITEM>::operator[](i) != static_cast<const MCollect<ITEM>&>(x)[i] )
     return true;

   return false;
  }

  /***************************************************
   Все элементы вектора домножаются на коэффициент k.
  ****************************************************/
  inline BaseArray<ITEM>& operator*=( const ITEM& k )
  {
   for( int i=0; i<size(); i++ )
    MCollect<ITEM>::operator[](i) *= k;

   return *this;
  }

  /***************************************************
   Все элементы вектора делятся на коэффициент k.
  ****************************************************/
  inline BaseArray<ITEM>& operator/=( const ITEM& k )
  {
   for( int i=0; i<size(); i++ )
    MCollect<ITEM>::operator[](i) /= k;

   return *this;
  }

  /***************************************************
   К каждому элементу вектора прибавляется k.
  ****************************************************/
  inline BaseArray<ITEM>& operator+=( const ITEM& k )
  {
   for( int i=0; i<size(); i++ )
    MCollect<ITEM>::operator[](i) += k;

   return *this;
  }

  /***************************************************
   От каждого элемента вектора отнимается k.
  ****************************************************/
  BaseArray<ITEM>& operator-=( const ITEM& k )
  {
   for( int i=0; i<size(); i++ )
    MCollect<ITEM>::operator[](i) -= k;

   return *this;
  }

  /***************************************************************************
   Элементы вектора s прибавляются к соответствующим элементам нашего вектора.
   Контролируем равенство границ индексов для обоих векторов.
  ****************************************************************************/
  BaseArray<ITEM>& operator+=( const BaseArray<ITEM> &s )
  {
   LEM_CHECKIT_Z( s.i0==i0 && s.in==in );

   for( int i=0; i<size(); i++ )
    MCollect<ITEM>::operator[](i) += static_cast<const MCollect<ITEM>&>(s)[i];

   return *this;
  }

  /****************************************************************************
   Элементы вектора s отнимаются от соответствующих элементов нашего вектора.
   Контролируем равенство границ индексов для обоих векторов.
  ****************************************************************************/
  BaseArray<ITEM>& operator-=( const BaseArray<ITEM> &s )
  {
   LEM_CHECKIT_Z( s.i0==i0 && s.in==in );

   for( int i=0; i<size(); i++ )
    MCollect<ITEM>::operator[](i) -= static_cast<const MCollect<ITEM>&>(s)[i];

   return *this;
  }

  inline const BaseArray<ITEM> operator*( const ITEM& k ) const
  {
   BaseArray<ITEM> b(*this);

   for( int i=0; i<b.size(); i++ )
    static_cast<const MCollect<ITEM>&>(b)[i] *= k;

   return b;
  }


  /*************************************************************
   Скалярное произведение двух векторов - результатом являетс
   число. Контролируем соответствие границ индексов для обоих
   векторов.
  **************************************************************/
  const ITEM operator*( const BaseArray<ITEM> &b ) const
  {
   LEM_CHECKIT_Z(b.GetFrom()==GetFrom());
   LEM_CHECKIT_Z(b.GetTo()==GetTo());

   ITEM res(0);

   for( int i=0; i<size(); i++ )
    res += MCollect<ITEM>::operator[](i) * static_cast<const MCollect<ITEM>&>(b)[i];

   return res;
  }



  const BaseArray<ITEM> operator/( const ITEM& k ) const
  {
   BaseArray<ITEM> b(*this);

   for( int i=0; i<size(); i++ )
    static_cast<const MCollect<ITEM>&>(b)[i] /= k;

   return b;
  }
 };

  /***********************************************************
   Вычисляем и возвращаем сумму всех элементов вектора a. Если
   вектор a пуст, то результатом будет 0.
  ************************************************************/
  template<class ITEM>
  inline const ITEM sum_up( const BaseArray<ITEM> &a )
  {
   ITEM s(0);

   for( int i=0; i<a.size(); i++ )
    s += static_cast<const MCollect<ITEM>&>(a)[i];

   return s;
  }


  #if !defined LEM_NOREAL
  typedef BaseArray<double> RArray;
  #endif // !defined SOL_NOREAL

  typedef BaseArray<int>  IntArray;
  typedef BaseArray<bool> BoolArray;

 } // namespace 'lem'

#endif
