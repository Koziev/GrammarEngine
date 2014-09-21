// 08.03.2010 - портирование под Darwin

#include <lem/config.h>

#include <lem/process.h>

using namespace lem::Process;

InterlockedInt::InterlockedInt( const InterlockedInt &x )
#if defined LEM_WINDOWS || defined LEM_DARWIN
: value(x.value)
#endif
{
 #if defined LEM_LINUX
  #if defined HAVE_ATOMIC_H
   atomic_set( &value, x.get() );
  #elif defined USE_GLIB
   g_atomic_int_set( &value, x.get() );
  #else
   value = x.value;
  #endif
 #elif defined LEM_FREEBSD
 atomic_set_int( &value, x.get() );
 #endif
 return;
}


void InterlockedInt::operator=( const InterlockedInt &x )
{
 #if defined LEM_WINDOWS
  #if defined LEM_MSC && _MSC_VER<1300
   InterlockedExchange( (LONG*)&value, x.value );
  #else
   InterlockedExchange( &value, x.value );
  #endif
 #elif defined LEM_LINUX
  #if defined HAVE_ATOMIC_H
   atomic_set( &value, x.get() );
  #elif defined USE_GLIB
   g_atomic_int_set( &value, x.get() );
  #else
   value = x.get();
  #endif 
 #elif defined LEM_FREEBSD
 atomic_set_int( &value, x.get() );
 #else
 value = x.value;
 #endif
 return;
}

void InterlockedInt::operator=( int x )
{
 #if defined LEM_WINDOWS
  #if defined LEM_MSC && _MSC_VER<1300
   InterlockedExchange( (LONG*)&value, x );
  #else
   InterlockedExchange( &value, x );
  #endif
 #elif defined LEM_LINUX
  #if defined HAVE_ATOMIC_H
   atomic_set( &value, x );
  #elif defined USE_GLIB
   g_atomic_int_set( &value, x );
  #else
   value = x;
  #endif 
 #elif defined LEM_FREEBSD
 atomic_set_int( &value, x );
 #else
 value = x;
 #endif
 return;
}



int InterlockedInt::operator++(void)
{
 #if defined LEM_WINDOWS
  #if defined LEM_MSC && _MSC_VER<1300
   InterlockedIncrement((LONG*)&value);
  #else
   InterlockedIncrement(&value);
  #endif
 return value;
 #elif defined LEM_LINUX
  #if defined HAVE_ATOMIC_H
   atomic_inc( &value );
  #elif defined USE_GLIB
   g_atomic_int_inc(&value);
  #else
   value++;
  #endif 
 return get();
 #elif defined LEM_DARWIN

 return __sync_fetch_and_add( &value, 1 );

 #elif defined LEM_FREEBSD
 atomic_add_int( &value, 1 );
 return get();
 #else
 value++; 
 return value;
 #endif
}


int InterlockedInt::operator--(void)
{
 #if defined LEM_WINDOWS
  #if defined LEM_MSC && _MSC_VER<1300
   InterlockedDecrement( (LONG*)&value);
  #else
   InterlockedDecrement(&value);
  #endif
 return value;
 #elif defined LEM_LINUX
  #if defined HAVE_ATOMIC_H
   atomic_dec( &value );
  #elif defined USE_GLIB
   g_atomic_int_dec(&value);
  #else
   value++;
  #endif 
 return get();
 #elif defined LEM_DARWIN

 return __sync_fetch_and_sub( &value, 1 );

 #elif defined LEM_FREEBSD
 atomic_subtract_int( &value, 1 );
 return get();
 #else
 value--;
 return value;
 #endif
}

int InterlockedInt::operator++(int)
{
 #if defined LEM_WINDOWS
  #if defined LEM_MSC && _MSC_VER<1300
   InterlockedIncrement( (LONG*)&value);
  #else
   InterlockedIncrement(&value);
  #endif
 return value;
 #elif defined LEM_LINUX
  #if defined HAVE_ATOMIC_H
   atomic_inc( &value );
  #elif defined USE_GLIB
   g_atomic_int_inc(&value);
  #else
   value++;
  #endif 
 return get();
 #elif defined LEM_DARWIN

 return __sync_add_and_fetch( &value, 1 );

 #elif defined LEM_FREEBSD
 atomic_add_int( &value, 1 );
 return get();
 #else
 value++; 
 return value;
 #endif
}


int InterlockedInt::operator--(int)
{
 #if defined LEM_WINDOWS
  #if defined LEM_MSC && _MSC_VER<1300
   InterlockedDecrement( (LONG*)&value );
  #else
   InterlockedDecrement(&value);
  #endif
 return value;
 #elif defined LEM_LINUX
  #if defined HAVE_ATOMIC_H
   atomic_dec( &value );
  #elif defined USE_GLIB
   g_atomic_dec(&value);
  #else
   value--;
  #endif 
 return get();
 #elif defined LEM_DARWIN

 return __sync_sub_and_fetch( &value, 1 );

 #elif defined LEM_FREEBSD
 atomic_subtract_int( &value, 1 );
 return get();
 #else
 value--;
 return value;
 #endif
}


int InterlockedInt::operator+=( int x )
{
 #if defined LEM_WINDOWS
  #if defined LEM_MSC && _MSC_VER<1300
   InterlockedExchangeAdd( (LONG*)&value, x );
  #else
   InterlockedExchangeAdd(&value,x);
  #endif
 return value;
 #elif defined LEM_LINUX

  #if defined HAVE_ATOMIC_H
   atomic_add( &value );
  #elif defined USE_GLIB
   g_atomic_int_add(&value,x);
  #else
   value+=x;
  #endif 
 return get();

 #elif defined LEM_DARWIN

 return __sync_add_and_fetch( &value, x );

 #elif defined LEM_FREEBSD
 atomic_add_int( &value, x );
 return get();
 #else
 value+=x; 
 return value;
 #endif
}
