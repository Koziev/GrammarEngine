// -----------------------------------------------------------------------------
// File SMART_POINTERS.H
//
// (c) Koziev Elijah
//
// Content:
// Шаблон RC_Object - для организации копирования объектов через подсчет ссылок.
//
// 20.12.2004 - код изменен для работы с NULL указателями.
//
// 02.20.2005 - код изменен для использования Boost.Smart_Ptr в качестве базы
//
// 28.09.2007 - небольшие правки для совместимости с MSVC 6.0
// 16.07.2008 - небольшие правки ошибок для GCC 4.x
// 19.09.2009 - небольшие правки для совместимости с MSVC 6.5
// -----------------------------------------------------------------------------
//
// CD->16.11.2003
// LC->19.09.2009
// --------------

#ifndef LEM_SMART_REF__H
#define LEM_SMART_REF__H
#pragma once

 #include <lem/config.h>
 #include <lem/runtime_checks.h>
 #include <boost/smart_ptr.hpp>
 #include <lem/streams.h>


 namespace lem
 {
  // No-op deallocator - необходим для передачи неудаляемых объектов
  // через shared_ptr
  struct null_deleter 
  {
   void operator()( const void * ) const {}
  };

  template < typename T > 
  struct T_deleter
  {
   void operator()( T* ptr ) { delete ptr; }
  };

  template < typename T >
  class CPtr
  {
   private:
    T* value;

   public:
    CPtr(void) : value(NULL) {}
    CPtr( T *p ) : value(p) {}

    inline T* operator->(void) { return value; }
    inline const T* operator->(void) const { return value; }
 
    inline T* get(void) { return value; }
    inline const T* get(void) const { return value; }

    inline T& operator*(void) { LEM_CHECKIT_Z(value); return *value; }
    inline const T& operator*(void) const { LEM_CHECKIT_Z(value); return *value; }

    inline void Delete(void) { delete value; value=NULL; }
    inline void SetNull(void) { value=NULL; }
    inline bool IsNull() const { return value==NULL; }
    inline bool NotNull() const { return value!=NULL; }

    inline bool operator!=( const void *p ) const
    {
     LEM_CHECKIT_Z(p==NULL);
     return value!=p;
    }

    inline bool operator==( const void *p ) const
    {
     LEM_CHECKIT_Z(p==NULL);
     return value==p;
    }
  };



  template < typename T >
  class Ptr : public boost::shared_ptr<T>
  {
   public:
    Ptr(void) {}
    Ptr( T *p ) : boost::shared_ptr<T>(p) {}
    Ptr( const T *p ) : boost::shared_ptr<T>( (T*)p,null_deleter()) {}
    Ptr( const lem::Ptr<T>& p ) : boost::shared_ptr<T>(p) {}

    template<class D> Ptr( T* p, D d ) : boost::shared_ptr<T>(p,d) {}


    T* get(void)
    {
     #if defined LEM_MSC && _MSC_VER<1300
     return ((boost::shared_ptr<T>&)*this).get();
     #else
     return boost::shared_ptr<T>::get();
     #endif
    }

    const T* get(void) const
    {
     #if defined LEM_MSC && _MSC_VER<1300
     return ((boost::shared_ptr<T>&)*this).get();
     #else
     return boost::shared_ptr<T>::get();
     #endif
    }

    Ptr<T>& operator=( const Ptr<T> &p )
    {
     #if defined LEM_MSC && _MSC_VER<1300
     // эта фигня исключительно для MSVS 6.0
     ( (boost::shared_ptr<T>&)(*this) ) = (const boost::shared_ptr<T>&)p;
     #else
     boost::shared_ptr<T>::operator=(p);
     #endif

     return *this;
    }

    Ptr<T>& operator=( T* p )
    {
     boost::shared_ptr<T>::reset(p);
     return *this;
    }

    Ptr<T>& operator=( const boost::shared_ptr<T> &p )
    {
     #if defined LEM_MSC && _MSC_VER<1300
     // эта фигня исключительно для MSVS 6.0
     ( (boost::shared_ptr<T>&)(*this) ) = (const boost::shared_ptr<T>&)p;
     #else
     boost::shared_ptr<T>::operator=(p);
     #endif

     return *this;
    }

    inline void Delete(void)
    {
     #if defined LEM_MSC && _MSC_VER<1300
     reset();
     #else
     boost::shared_ptr<T>::reset();
     #endif
    }

    inline void SetNull(void)
    {
     #if defined LEM_MSC && _MSC_VER<1300
     reset();
     #else
     boost::shared_ptr<T>::reset(); 
     #endif
    }

    inline bool IsNull() const
    {
     #if defined LEM_MSC && _MSC_VER<1300
     return operator!();
     #else
     return boost::shared_ptr<T>::operator!();
     #endif
    }

    inline bool NotNull() const
    {
     #if defined LEM_MSC && _MSC_VER<1300
     return !operator!();
     #else
     return !boost::shared_ptr<T>::operator!();
     #endif
    }

    inline bool operator!=( const void *p ) const
    {
     LEM_CHECKIT_Z(p==NULL);
     return get()!=p;
    }

    inline bool operator==( const void *p ) const
    {
     LEM_CHECKIT_Z(p==NULL);
     return get()==p;
    }
  };



  template < typename T >
  class ClonePtr : public boost::shared_ptr<T>
  {
   public:
    ClonePtr(void) {}
    ClonePtr( T *p ) : boost::shared_ptr<T>(p) {}
    ClonePtr( const T *p ) : boost::shared_ptr<T>( (T*)p,null_deleter()) {}
    ClonePtr( const lem::ClonePtr<T>& p ) : boost::shared_ptr<T>(p) {}

    template<class D> ClonePtr( T* p, D d ) : boost::shared_ptr<T>(p,d) {}


    T* get(void) { return boost::shared_ptr<T>::get(); }
    const T* get(void) const { return boost::shared_ptr<T>::get(); }

    ClonePtr<T>& operator=( const ClonePtr<T> &p )
    {
     #if defined LEM_MSC && _MSC_VER<1300
     reset();
     #else
     boost::shared_ptr<T>::reset();
     #endif

     if( p.NotNull() )
      #if defined LEM_MSC && _MSC_VER<1300
      ((boost::shared_ptr<T>&)*this).operator=( boost::shared_ptr<T>(p->clone()) );
      #else
      boost::shared_ptr<T>::operator=( boost::shared_ptr<T>(p->clone()) );
      #endif

     return *this;
    }

    ClonePtr<T>& operator=( T* p )
    {
     boost::shared_ptr<T>::reset(p);
     return *this;
    }

    inline void Delete(void)
    {
     #if defined LEM_MSC && _MSC_VER<1300
     reset();
     #else
     boost::shared_ptr<T>::reset();
     #endif
    }

    inline void SetNull(void)
    {
     #if defined LEM_MSC && _MSC_VER<1300
     reset();
     #else
     boost::shared_ptr<T>::reset();
     #endif
    }

    inline bool IsNull() const
    {
     #if defined LEM_MSC && _MSC_VER<1300
     return operator!();
     #else
     return boost::shared_ptr<T>::operator!(); 
     #endif
    }

    inline bool NotNull() const
    {
     #if defined LEM_MSC && _MSC_VER<1300
     return !operator!();
     #else
     return !boost::shared_ptr<T>::operator!();
     #endif
    }

    inline bool operator!=( const void *p ) const
    {
     LEM_CHECKIT_Z(p==NULL);
     return get()!=p;
    }

    inline bool operator==( const void *p ) const
    {
     LEM_CHECKIT_Z(p==NULL);
     return get()==p;
    }

    void SaveBin( lem::Stream &bin ) const 
    {
     bin.write_bool( NotNull() );
     if( NotNull() )
      get()->SaveBin(bin);

     return;
    }

    void LoadBin( lem::Stream &bin )
    {
     if( bin.read_bool() )
      boost::shared_ptr<T>::reset( T::load_bin(bin) );
     else
      Delete();

     return;
    }
  };

 } // namespace 'lem'

#endif
