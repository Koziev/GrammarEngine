#ifndef LEM_TUPLES__H
#define LEM_TUPLES__H
#pragma once

// CD->05.05.2006
// LC->20.07.2009


 namespace lem
 {
  // ******************************************************
  // the triple class - an extension of std::pair template
  // ******************************************************

  template < class T1, class T2, class T3 >
  struct triple
  { 
   typedef T1 first_type;
   typedef T2 second_type;
   typedef T3 third_type;

   T1 first;
   T2 second;
   T3 third; 

   triple(void) : first(), second(), third() {}
   
   triple( T1 t1, T2 t2, T3 t3 ) : first(t1), second(t2), third(t3) {}

   triple( const triple<T1,T2,T3>& t2 ) :
     first(t2.first), second(t2.second), third(t2.third)
   {}
  
   // comparison operations
   inline bool operator == ( const triple<T1,T2,T3>& right ) const
   {
    // triples are equal if all elements are equal
    return first == right.first &&
           second == right.second &&
           third == right.third;
   }

   inline bool operator != ( const triple<T1,T2,T3>& right ) const
   {
    // triples are different if any of the elements is different
    return first  != right.first ||
           second != right.second ||
           third  != right.third;
   }


   // Author:    Andy Rushton, from an original by Dan Milton
   bool operator < ( const triple<T1,T2,T3>& right ) const
   {
    // sort according to first element, then second, then third
    // as per pair, define sort order entirely in terms of operator< for elements
    if( first        < right.first  ) return true;
    if( right.first  < first        ) return false;
    if( second       < right.second ) return true;
    if( right.second < second       ) return false;
    if( third        < right.third  ) return true;
    return false;
   }
  };


  ////////////////////////////////////////////////////////////////////////////////
  // the foursome class
  template<typename T1, typename T2, typename T3, typename T4>
  struct foursome
  {
   typedef T1 first_type;
   typedef T2 second_type;
   typedef T3 third_type;
   typedef T4 fourth_type;

   T1 first;
   T2 second;
   T3 third;
   T4 fourth;

   foursome(void): first(), second(), third(), fourth()
   {}

   foursome( const T1& p1, const T2& p2, const T3& p3, const T4& p4 ) :
    first(p1), second(p2), third(p3), fourth(p4)
   {}

   foursome( const foursome<T1,T2,T3,T4>& t2 ) :
    first(t2.first), second(t2.second), third(t2.third), fourth(t2.fourth)
   {}

   inline const foursome<T1,T2,T3,T4>& operator=( const foursome<T1,T2,T3,T4>& t2 )
   {
    first = t2.first;
    second = t2.second;
    third = t2.third;
    fourth = t2.fourth;
    return *this;
   }

   inline bool operator == ( const foursome<T1,T2,T3,T4>& right) const 
   {
    // foursomes are equal if all elements are equal
    return 
          first == right.first && 
          second == right.second && 
          third == right.third &&
          fourth == right.fourth;
   }


   inline bool operator < ( const foursome<T1,T2,T3,T4>& right ) const
   {
    // sort according to first element, then second, then third, then fourth
    // as per pair, define sort order entirely in terms of operator< for elements
    if( first        < right.first ) return true;
    if( right.first  < first ) return false;
    if( second       < right.second ) return true;
    if( right.second < second ) return false;
    if( third        < right.third ) return true;
    if( right.third  < third ) return false;
    if( fourth       < right.fourth ) return true;
    return false; 
   }
  };





  template<typename T1, typename T2, typename T3, typename T4, typename T5>
  struct tuple5
  {
   typedef T1 first_type;
   typedef T2 second_type;
   typedef T3 third_type;
   typedef T4 fourth_type;
   typedef T5 fifth_type;

   T1 first;
   T2 second;
   T3 third;
   T4 fourth;
   T5 fifth;

   tuple5(void): first(), second(), third(), fourth(), fifth()
   {}

   tuple5( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5 ) :
    first(p1), second(p2), third(p3), fourth(p4), fifth(p5)
   {}

   tuple5( const tuple5<T1,T2,T3,T4,T5>& t2 ) :
    first(t2.first), second(t2.second), third(t2.third), fourth(t2.fourth), fifth(t2.fifth)
   {}

   inline const tuple5<T1,T2,T3,T4,T5>& operator=( const tuple5<T1,T2,T3,T4,T5>& t2 )
   {
    first = t2.first;
    second = t2.second;
    third = t2.third;
    fourth = t2.fourth;
    fifth = t2.fifth;
    return *this;
   }

   inline bool operator == ( const tuple5<T1,T2,T3,T4,T5>& right ) const 
   {
    return 
          first  == right.first  && 
          second == right.second && 
          third  == right.third  &&
          fourth == right.fourth &&
          fifth  == right.fifth;
   }


   inline bool operator < ( const tuple5<T1,T2,T3,T4,T5>& right ) const
   {
    if( first        < right.first ) return true;
    if( right.first  < first ) return false;
    if( second       < right.second ) return true;
    if( right.second < second ) return false;
    if( third        < right.third ) return true;
    if( right.third  < third ) return false;
    if( fourth       < right.fourth ) return true;
    if( right.fourth < fourth ) return false;
    if( fifth        < right.fifth ) return true;
    return false; 
   }
  };


  // creation - like 'std::make_pair'
  template < class T1, class T2, class T3 >
  inline triple<T1,T2,T3> make_triple( T1 t1, T2 t2, T3 t3 ) 
  { return triple<T1,T2,T3>(t1,t2,t3); } 


  template< typename T1, typename T2, typename T3, typename T4 >
  inline foursome<T1,T2,T3,T4> make_foursome(
                                             const T1& t1,
                                             const T2& t2,
                                             const T3& t3,
                                             const T4& t4
                                            )
  { return foursome<T1,T2,T3,T4>(t1,t2,t3,t4); } 

  template< typename T1, typename T2, typename T3, typename T4, typename T5 >
  inline tuple5<T1,T2,T3,T4,T5> make_tuple5(
                                            const T1& t1,
                                            const T2& t2,
                                            const T3& t3,
                                            const T4& t4,
                                            const T5& t5
                                           )
  { return tuple5<T1,T2,T3,T4,T5>(t1,t2,t3,t4,t5); } 
  
 } // namespace lem
#endif
