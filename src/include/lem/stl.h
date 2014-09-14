// -----------------------------------------------------------------------------
// File STL.H
//
// (c) Koziev Elijah
//
// Content:
// Реализация методов сортировки и реорганизации порядка элементов в
// контейнере. Шаблоны. Дополнения к STL.
//
// ВНИМАНИЕ! Код в данном хидере основан на устаревших концепциях и по
// возможности не должен использоваться в программах. По мере рефакторинга он
// будет удаляться.
//
// 08.05.2008 - порт под MSVC6.0 введены std::max и std::min
// -----------------------------------------------------------------------------
//
// CD->06.10.2002
// LC->08.05.2010
// --------------

#ifndef LEM_SORT__H
#define LEM_SORT__H
#pragma once

  #include <lem/config.h>
  #include <utility>
  #include <vector>
  #include <boost/type_traits.hpp>
  #include <lem/containers.h>
  #include <lem/ptr_container.h>
  #include <lem/quantors.h>
  #include <lem/minmax.h>

  namespace lem
  {
  // **********************************************************************
  // Сортируем вектор <a> методом Шелла, причем вектор <w> содержит ВЕСА
  // элементов <a>, и после сортировки элементы <a> будут располагаться в
  // порядке убывания веса (элементы <w> также будут пересортированы).
  // **********************************************************************
  template <class T_Array, class W_Array>
  inline void sort_desc( T_Array& a, W_Array &w )
  {
   LEM_CHECKIT_Z( a.size() == w.size() );

   typedef typename T_Array::size_type SZ;
   const SZ N=a.size();

   for( SZ gap=N/2; gap>0; gap/=2 )
    for( SZ i=gap; i<N; i++ )
     for( int j=CastSizeToInt(i-gap); j>=0; j-=CastSizeToInt(gap) )
      {
       if( w[j+gap] < w[j] )
        break;

       std::swap( a[j], a[j+gap] );
       std::swap( w[j], w[j+gap] );
      }

   return;
  }


  // ******************************************************
  // Sort up the list of pointers to items.
  // ******************************************************
  template <class T>
  inline void sort_desc( Ptr_NC_Collect<T>& a )
  {
   typedef typename Ptr_NC_Collect<T>::size_type SZ;
   const SZ N=a.size();

   for( SZ gap=N/2; gap>0; gap/=2 )
    for( SZ i=gap; i<N; i++ )
     for( int j=i-gap; j>=0; j-=gap )
      if( *(a[j+gap]) < *(a[j]) )
       break;
      else
       std::swap( a[j], a[j+gap] );

   return;
  }

  template <class T>
  inline void sort_asc( Ptr_NC_Collect<T>& a )
  {
   typedef typename Ptr_NC_Collect<T>::size_type SZ;
   const int N=a.size();

   for( SZ gap=N/2; gap>0; gap/=2 )
    for( SZ i=gap; i<N; i++ )
     for( int j=i-gap; j>=0; j-=gap )
      if( *(a[j+gap]) > *(a[j]) )
       break;
      else
       std::swap( a[j], a[j+gap] );

   return;
  }


  // **********************************************************************
  // Сортируем вектор <a> методом Шелла, причем второй элемент каждой
  // пары содержит ВЕСА, и после сортировки элементы <a> будут распологаться
  // в порядке убывания веса.
  // **********************************************************************
  template < class Cont >
  inline void sort_desc_pairs( Cont& a )
  {
   typedef typename Cont::size_type SZ;

   for( SZ gap=a.size()/2; gap>0; gap/=2 )
    for( SZ i=gap; i<a.size(); i++ )
     for( int j=CastSizeToInt(i-gap); j>=0; j-=CastSizeToInt(gap) )
      {
       if( a[j+gap].second < a[j].second )
        break;

       std::swap( a[j], a[j+gap] );
      }

   return;
  }

  // Сортировка по возрастанию
  template < class Cont >
  inline void sort_asc_pairs( Cont& a )
  {
   typedef typename Cont::size_type SZ;
   const SZ N=a.size();

   for( SZ gap=N/2; gap>0; gap/=2 )
    for( SZ i=gap; i<N; i++ )
     for( int j=i-gap; j>=0; j-=gap )
      {
       if( a[j+gap].second > a[j].second )
        break;

       std::swap( a[j], a[j+gap] );
      }

   return;
  }


  // **********************************************************************
  // Аналогично предыдущему методу, но вместо прямой перестановки элементов
  // в сортируемом векторе (что может быть весьма тяжелой операцией)
  // работаем с индексным вектором.
  // **********************************************************************
  template < class ARRAY, class INDECES >
  void sort_desc_pairs( ARRAY& a, INDECES &index )
  {
   typedef typename ARRAY::size_type SZ;
   const SZ N=a.size();

   if( index.empty() )
    index.resize(N);

   // Первоначальное заполнение индексного вектора
   for( int ii=0; ii<CastSizeToInt(N); ii++ )
    index[ii] = ii;

   for( SZ gap=N/2; gap>0; gap/=2 )
    for( SZ i=gap; i<N; i++ )
     for( int j=CastSizeToInt(i-gap); j>=0; j-=CastSizeToInt(gap) )
      {
       if( a[ index[j+gap] ].second < a[ index[j] ].second )
        break;

       std::swap( index[j], index[j+gap] );
      }

   return;
  }

  template < class ARRAY, class INDECES >
  void sort_asc_pairs( ARRAY& a, INDECES &index )
  {
   typedef typename ARRAY::size_type SZ;
   const SZ N=a.size();

   if( index.empty() )
    index.AddAll(N);

   // Первоначальное заполнение индексного вектора
   for( int ii=0; ii<N; ii++ )
    index[ii] = ii;

   for( SZ gap=N/2; gap>0; gap/=2 )
    for( SZ i=gap; i<N; i++ )
     for( int j=i-gap; j>=0; j-=gap )
      {
       if( a[ index[j+gap] ].second > a[ index[j] ].second )
        break;

       swap( index[j], index[j+gap] );
      }

   return;
  }



 template< class T >
 class Comparator
 {
  public:
   Comparator() {};

   inline bool gt( const T &X, const T &Y ) const
   { return X > Y; }

   inline bool eq( const T &X, const T &Y ) const
   { return X == Y; }

   inline bool lt( const T &X, const T &Y ) const
   { return X < Y; }
 };


 template< class ARRAY, class COMPARATOR >
 inline void sort_down( ARRAY& a, COMPARATOR Comp, IntCollect &index )
 {
  typedef typename ARRAY::size_type SZ;
  const SZ N=a.size();

  if( index.empty() )
   index.resize(N);

  // Первоначальное заполнение индексного вектора
  for( SZ i=0; i<N; i++ )
   index[i] = i;

  for( SZ gap=N/2; gap>0; gap/=2 )
   for( SZ i=gap; i<N; i++ )
    for( int j=i-gap; j>=0; j-=gap )
     {
      if( Comp.lt( a[ index[j+gap] ], a[ index[j] ] ) )
       break;

      std::swap( index[j], index[j+gap] );
     }

  return;
 }

 template< class ARRAY, class COMPARATOR >
 inline void sort_up( ARRAY& a, COMPARATOR Comp, IntCollect &index )
 {
  typedef typename ARRAY::size_type SZ;
  const SZ N=a.size();

  if( index.empty() )
   index.resize(N);

  // Первоначальное заполнение индексного вектора
  for( int i=0; i<N; i++ )
   index[i] = i;

  for( SZ gap=N/2; gap>0; gap/=2 )
   for( SZ i=gap; i<N; i++ )
    for( int j=i-gap; j>=0; j-=gap )
     {
      if( Comp.gt( a[ index[j+gap] ], a[ index[j] ] ) )
       break;

      swap( index[j], index[j+gap] );
     }

  return;
 }


 template< class T >
 class Compare_b_Items
 {
  public:
   Compare_b_Items() {};

   inline bool gt( const T &X, const T &Y ) const
   { return X.second > Y.second; }

   inline bool eq( const T &X, const T &Y ) const
   { return X.second == Y.second; }

   inline bool lt( const T &X, const T &Y ) const
   { return X.second < Y.second; }
 };


  // ********************************************
  // Порядок элементов в векторе "a" обращается.
  // ********************************************
/*
  template <class T>
  inline void reverse( Collect<T>& a )
  {
   // Возможны 2 варианта: число элементов в векторе четное и нечетное:
   //
   //      0 1 2      2 1 0
   //      # # #      # # #            - центральный элемент не изменяется
   //
   //
   //      0 1 2 3    3 2 1 0
   //      # # # #    # # # #          - все пары обмениваются

   const int npair = a.size()/2; // Сколько полных пар.

   LEM_LOOP( i, npair )
    swap( a[i], a[ a.size()-1-i ] );

   return;
  }
*/

  // Поиск в отсортированном по возрастанию массиве.
  template< typename Cont, typename T >
  inline int find_bisection( const Cont &v, const T &x )
  {
   typedef typename Cont::size_type SZ;

   SZ i_left=0, i_right=v.size()-1;

   while( (i_right-i_left)>1 )
    {
     SZ i_mid = (i_right+i_left)/2;

     if( v[i_mid] > x )
      i_right = i_mid;
     else if( v[i_mid] < x )
      i_left = i_mid;
     else
      return CastSizeToInt(i_mid);
    }

   if( v[i_left]==x )
    return CastSizeToInt(i_left);

   if( v[i_right]==x )
    return CastSizeToInt(i_right);

   return UNKNOWN;
  }


  // ****************************************************************
  // Basic algorithm which applies given operation on each
  // item in container and stores the result back in container.
  // ****************************************************************
/*
  template < class Cont, class Oper >
  inline void modify_each( _Iter(Cont) from, _Iter(Cont) to, Oper &op )
  {
   for( _Iter(Cont) i=from; i!=to; i++ )
    op( *i );
  }

  template < class Cont, class Oper >
  inline void modify_each( Cont &a, Oper &op )
  {
   for( _Iter(Cont) i=a.begin(); i!=a.end(); i++ )
    op( *i );
  }
*/

  template< class ITEM >
  class add_set
  {
   private:
    ITEM modifier;

   public:
    add_set( const ITEM &Modifier ) : modifier(Modifier) {};

    inline void operator()( ITEM &val ) const { val += modifier; }
  };

  template< class ITEM >
  class sub_set
  {
   private:
    ITEM modifier;

   public:
    sub_set( const ITEM &Modifier ) : modifier(Modifier) {};

    inline void operator()( ITEM &val ) const { val -= modifier; }
  };

  template< class ITEM >
  class mul_set
  {
   private:
    ITEM modifier;

   public:
    mul_set( const ITEM &Modifier ) : modifier(Modifier) {};

    inline void operator()( ITEM &val ) const { val *= modifier; }
  };

  template< class ITEM >
  class div_set
  {
   private:
    ITEM modifier;

   public:
    div_set( const ITEM &Modifier ) : modifier(Modifier) {};

    inline void operator()( ITEM &val ) const { val /= modifier; }
  };

/*
  template < class Cont, class ITEM >
  inline void add_each( Cont &a, const ITEM& k )
  {
   add_set<ITEM> o(k);
   modify_each( a, o );
  }

  template < class Cont, class ITEM >
  inline void sub_each( Cont &a, const ITEM& k )
  {
   sub_set<ITEM> o(k);
   modify_each( a, o );
  }

  template < class Cont, class ITEM >
  inline void mul_each( Cont &a, const ITEM& k )
  {
   mul_set<ITEM> o(k);
   modify_each( a, o );
  }

  template < class Cont, class ITEM >
  inline void div_each( Cont &a, const ITEM& k )
  {
   div_set<ITEM> o(k);
   modify_each( a, o );
  }


   template < class A, class B >
   inline const B max_b( const MCollect< MPair<A,B>  > &cont )
   {
    B top_b = cont.get(0).b;

    for( int i=1; i<cont.size(); i++ )
     top_b = max( top_b, cont(i).b );

    return top_b;
   }
*/


  // ----------------------------------------
  template< class NAME >
  class ByName
  {
   private:
    NAME name;

   public:
    ByName( const NAME &Name ):name(Name) {};

    inline bool operator==( const NAME &x ) const { return name==x; }
  };

  template< class X, class NAME >
  inline bool operator==( const ByName<NAME> &name, const X &x )
  { return name==x.GetName(); }

  template< class X, class NAME >
  inline bool operator==(  const X &x, const ByName<NAME> &name )
  { return name==x.GetName(); }

  template< class NAME >
  inline ByName<NAME> by_name( const NAME &Name )
  { return ByName<NAME>(Name); }

  // ------------------------------------------------------------------

  template< class KEY >
  class ById
  {
   private:
    KEY id;

   public:
    ById( const KEY &Id ):id(Id) {};

    inline bool operator==( const KEY &x ) const { return id==x;  }
    inline bool operator==( const KEY *x ) const { return id==*x; }
  };

  template< class KEY >
  inline ById<KEY> by_id( const KEY &Id )
  { return ById<KEY>(Id); }

  template< class X, class KEY >
  inline bool operator==( const ById<KEY> &Id, const X &x )
  { return Id==x.GetId(); }

  // ------------------------------------------------------------------

  template< class FIRST, class SECOND >
  class By_First
  {
   private:
    FIRST t;

   public:
    By_First( const FIRST &T ):t(T) {};

    bool operator()( const std::pair<FIRST,SECOND> &x ) const { return t==x.first;  }
    bool operator()( const std::pair<FIRST,SECOND> *x ) const { return t==x->first; }

//    inline bool operator==( const pair<FIRST,SECOND> &x ) const { return t==x.first;  }
//    inline bool operator==( const pair<FIRST,SECOND> *x ) const { return t==x->first;  }
  };

  template< class FIRST, class SECOND >
  inline By_First<FIRST,SECOND> by_first( const FIRST &f )
  { return By_First<FIRST,SECOND>(f); }

  // ------------------------------------------------------------



  // ***********************************************
  //            ПОИСК ДАННЫХ В КОНТЕЙНЕРЕ
  // ***********************************************

  // ********************************************************************
  // Безусловный поиск значения в произвольном контейнере с индексным
  // доступом. В случае успеха возвращается индекс найденного элемента,
  // в противном случае - UNKNOWN.
  // ********************************************************************

  template <class ARR,class T>
  inline int find( const ARR &arr, const T& val )
  {
   typedef typename ARR::size_type SZ;

   for( SZ i=0; i<arr.size(); i++ )
    if( arr[i]==val )
     return CastSizeToInt(i);

   return UNKNOWN;
  }

  // ****************************************************************
  // Item finder: it returns the INDEX of item in the array. If fails
  // it returns UNKNOWN.
  // ****************************************************************
  template < class Cont, class Oper >
  inline int find_if( const Cont &arr, const Oper &op )
  {
   typedef typename Cont::size_type SZ;
   for( SZ i=0; i<arr.size(); i++ )
    if( op == arr[i] )
     return i;

   return UNKNOWN;
  }


  template < class Cont, class Oper >
  inline int find_if_ptr( const Cont &arr, const Oper &op )
  {
   typedef typename Cont::size_type SZ;
   for( SZ i=0; i<arr.size(); i++ )
    if( op == *arr[i] )
     return i;

   return UNKNOWN;
  }


  template <class PAIR, class T>
  inline int find_a( const MCollect<PAIR> &arr, const T& val )
  {
   typedef typename MCollect<PAIR>::size_type SZ;
   for( SZ i=0; i<arr.size(); i++ )
    if( arr[i].first==val )
     return i;

   return UNKNOWN;
  }


  template <class PAIR, class T>
  inline int find_a( const Collect<PAIR> &arr, const T& val )
  {
   typedef typename Collect<PAIR>::size_type SZ;
   for( SZ i=0; i<arr.size(); i++ )
    if( arr[i].first==val )
     return i;

   return UNKNOWN;
  }

  // **********************************************************************
  // Подсчет количества элементов в контейнере, удовлетворяющих указанному
  // через предикат условию.
  // **********************************************************************
/*
  template <class ITER,class T>
  inline int count_if( ITER from, ITER to, const T& cond )
  {
   int n=0;
   for( ITER i=from; i!=to; i++ )
    if( cond( *i ) )
     n++;

   return n;
  }
*/

  template <class ITER,class T>
  inline int count_if_ptr( ITER from, ITER to, const T& cond )
  {
   int n=0;
   for( ITER i=from; i!=to; i++ )
    if( cond( **i ) )
     n++;

   return n;
  }


  // ****************************************************************
  // Удаление всех элементов в контейнере, который хранит элементы
  // как указатели
  // ****************************************************************
  template < class Iter >
  inline void zap_array( Iter begin, Iter beyond_end )
  {
   for( Iter i=begin; i!=beyond_end; i++ )
    {
     delete *i;
     *i = NULL;
    }
  }


  #define ZAP_A( C ) \
  {                  \
   if( &(C) != NULL )  \
    {                                 \
     lem::zap_array( (C).begin(), (C).end() ); \
     (C).clear();                       \
    }                                 \
  }



  // *************************************************************
  // Арифметическое суммирование ВСЕХ элементов двух контейнеров.
  //                             a += b
  // *************************************************************

  template < class Cont >
  inline void add_to( Cont &a, const Cont &b )
  {
   #if defined LEM_MSC && _MSC_VER<1300
   typedef Cont::size_type SZ;
   #else
   typedef typename Cont::size_type SZ;
   #endif
   for( SZ i=0; i<a.size(); i++ )
    a[i] += b[i];

   return;
  }



  template < class Inserter >
  inline void load_bin( Inserter p, Stream &bin )
  {
   #if defined LEM_MSC && _MSC_VER<1300
   typedef boost::remove_pointer<Inserter::container_type::value_type>::type T;
   typedef Inserter::container_type::size_type SZ;
   #else
   typedef typename boost::remove_pointer<typename Inserter::container_type::value_type>::type T;
   typedef typename Inserter::container_type::size_type SZ;
   #endif

   SZ ni=0;
   bin.read( &ni, sizeof(ni) );

   if(!ni)
    return;

   for( SZ i=0; i<ni; i++ )
    {
     T *x = new T();
     x->LoadBin(bin);
     (*p++) = x;
    }

   return;
  }

  template < class Iter >
  inline void save_bin( Iter from, Iter to, Stream &bin )
  {
   const size_t ni = static_cast<size_t>( to-from );
   bin.write( &ni, sizeof(ni) );

   for( Iter i=from; i!=to; i++ )
    (*i)->SaveBin(bin);

   return;
  }


  class Stream;

  using std::vector;

  // ********************************************************************

  template < class T >
  inline lem::Stream& operator<<( lem::Stream &bin, const std::vector<T> &x )
  {
   const int n=CastSizeToInt(x.size());
   bin.wr( &n );

   #if defined LEM_MSC && _MSC_VER<1300
   typedef vector<T>::const_iterator IT;
   #else
   typedef typename vector<T>::const_iterator IT;
   #endif
   for( IT i=x.begin(); i!=x.end(); i++ )
    i->SaveBin(bin);

   return bin;
  }


  template < class T >
  inline lem::Stream& operator>>( lem::Stream &bin, std::vector<T> &x )
  {
   int n=0;
   bin.rd(&n);

   x.resize(n);

   #if defined LEM_MSC && _MSC_VER<1300
   typedef std::vector<T>::const_iterator IT;
   #else
   typedef typename std::vector<T>::const_iterator IT;
   #endif

   for( IT i=x.begin(); i!=x.end(); i++ )
    i->LoadBin(bin);

   return bin;
  }

  // ********************************************************************

  template < class T >
  inline Stream& write_pod( Stream &bin, const vector<T> &x )
  {
   typedef typename vector<T>::size_type SZ;

   SZ n=x.size();
   bin.wr( &n );

   typedef typename vector<T>::const_iterator IT;
   for( IT i=x.begin(); i!=x.end(); i++ )
    {
     #if defined LEM_MSC
      const T &t = *i;
      bin.write( &t, sizeof(t) );
     #else
      bin.write( i, sizeof(T) );
     #endif
    }

   return bin;
  }


  template < class T >
  inline Stream& read_pod( Stream &bin, vector<T> &x )
  {
   typedef typename vector<T>::size_type SZ;
   
   SZ n=0;
   bin.rd(&n);

   x.resize(n);

   typedef typename vector<T>::iterator IT;
   for( IT i=x.begin(); i!=x.end(); i++ )
    {
     #if defined LEM_MSC
      T t;
      bin.read( &t, sizeof(t) );
      *i = t;
     #else
      bin.read( i, sizeof(T) );
     #endif
    }

   return bin;
  }

  // ********************************************************************

  template < class T >
  inline Stream& write( Stream &bin, const vector<T*> &x )
  {
   typedef typename vector<T*>::size_type SZ;

   SZ n=x.size();
   bin.write( &n, sizeof(n) );

   typedef typename vector<T*>::const_iterator IT;
   for( IT i=x.begin(); i!=x.end(); i++ )
    (*i)->SaveBin(bin);

   return bin;
  }


  template < class T >
  inline Stream& read( Stream &bin, vector<T*> &x )
  {
   typedef typename vector<T*>::size_type SZ;
   
   SZ n=0;
   bin.read( &n, sizeof(n) );
   x.reserve(n);

   for( Container::size_type i=0; i<n; i++ )
    {
     T *t = new T;
     t->LoadBin(bin);
     x.push_back( t );
    }

   return bin;
  }

  // ********************************************************************


  template < class T >
  inline Stream& operator<<( Stream &bin, const T &x )
  {
   x.SaveBin(bin);
   return bin;
  }


  template < class T >
  inline Stream& operator>>( Stream &bin, T &x )
  {
   x.LoadBin(bin);
   return bin;
  }


 } // end of namespace 'lem'

#endif
