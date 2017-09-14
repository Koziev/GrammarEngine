#ifndef LEM_MALLOCATOR__H
#define LEM_MALLOCATOR__H
#pragma once

 #undef max
 #include <map>
 #include <limits>

 namespace lem
 {

/* The following code example is taken from the book
 * "The C++ Standard Library - A Tutorial and Reference"
 * by Nicolai M. Josuttis, Addison-Wesley, 1999
 *
 * (C) Copyright Nicolai M. Josuttis 1999.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */

  class HeapAllocator
  {
   private:
    HeapAllocator(void);
    HeapAllocator( const HeapAllocator & );
    void operator=( const HeapAllocator & );
   
   public:
    int item_size; 
    std::vector<void*> chunks;
    char *chunk;
    int cur_i;
    int left_n;

    HeapAllocator( int ItemSize )
    {
     item_size = ItemSize;
     left_n=0;
     cur_i=0;
     chunk=NULL;
     return;
    }

    ~HeapAllocator(void)
    {
     for( lem::Container::size_type i=0; i<chunks.size(); i++ )
      free( chunks[i] );

     return;
    }

     void* allocate( int num )
     {
      if( num>left_n )
      {
       cur_i=0;
       left_n = 100000;
       chunk = (char*)malloc( item_size*left_n );
       chunks.push_back(chunk); 
      }        

     void * ptr = chunk+cur_i*item_size;
     cur_i += num;
     left_n-=num;
     return ptr;
    }
  };


  template <class T> class MAllocator
  {
   public:
    HeapAllocator *ha;

   public:
       // type definitions
       typedef T        value_type;
       typedef T*       pointer;
       typedef const T* const_pointer;
       typedef T&       reference;
       typedef const T& const_reference;
       typedef std::size_t    size_type;
       typedef std::ptrdiff_t difference_type;

       // rebind allocator to type U
       template <class U>
       struct rebind {
           typedef MAllocator<U> other;
       };

       // return address of values
       pointer address (reference value) const
       {
           return &value;
       }

       const_pointer address(const_reference value) const
       {
           return &value;
       }

       MAllocator(void) throw()
       {
        ha = new HeapAllocator( sizeof(T) );
       }

       MAllocator( const MAllocator& x ) throw()
       {
        ha = new HeapAllocator( sizeof(T) );
        return;         
       }

       template <class U>
         MAllocator (const MAllocator<U> & x) throw()
       {
        //int sz2 = sizeof(U);
        ha = new HeapAllocator( sizeof(T) );
        return;
       }

       ~MAllocator(void) throw()
       {
        delete ha;
       }

       // return maximum number of elements that can be allocated
       size_type max_size (void) const throw()
       {
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
       }

       // allocate but don't initialize num elements of type T
       pointer allocate( size_type num, const void* = 0 )
       {
        T * ptr = (T*)ha->allocate(num);
        return ptr;
       }

       // initialize elements of allocated storage p with value value
       void construct( pointer p, const T& value )
       {
        // initialize memory with placement new
        new((void*)p)T(value);
       }

       // destroy elements of initialized storage p
       void destroy( pointer p )
       {
        // destroy objects by calling their destructor
        //p->~T();
       }

       // deallocate storage p of deleted elements
       void deallocate( pointer p, size_type num )
       {
        //::operator delete((void*)p);
       }
   };



   // return that all specializations of this allocator are interchangeable
   template <class T1, class T2>
   bool operator== (const MAllocator<T1>&,
                    const MAllocator<T2>&) throw() {
       return true;
   }

   template <class T1, class T2>
   bool operator!= (const MAllocator<T1>&,
                    const MAllocator<T2>&) throw() {
       return false;
   }


 } // namespace lem

#endif
