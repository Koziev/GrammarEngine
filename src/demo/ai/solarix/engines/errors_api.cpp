// 27.03.2011 - добавлена critical section для Errors API

#include <lem/config.h>

#if defined FAIND_IENGINES || defined DLL_EXPORTS

#include <lem/solarix/faind_internal.h>


// ******************************************************
// Return the length of the wide string with error text.
// Null terminator is included in a return value.
//
// http://www.solarix.ru/api/en/sol_GetErrorLen.shtml
//
// ******************************************************
FAIND_API(int) sol_GetErrorLen( HFAIND hEngine )
{
 if( hEngine==NULL || !HandleEngine(hEngine)->ok )
  return -1;

 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker( & HandleEngine(hEngine)->cs_error );
 #endif
 
 const int len = HandleEngine(hEngine)->error.length()+1;

 return len;
}


// ******************************************************
// Return the length of UTF-8 string with error text.
// Null terminator is included in a return value.
//
// http://www.solarix.ru/api/en/sol_GetErrorLen.shtml
//
// ******************************************************
FAIND_API(int) sol_GetErrorLen8( HFAIND hEngine )
{
 if( hEngine==NULL || !HandleEngine(hEngine)->ok )
  return -1;

 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker( & HandleEngine(hEngine)->cs_error );
 #endif
 
 const int len = lem::to_utf8(HandleEngine(hEngine)->error).length()+1;
 return len;
}



// ****************************************************************************
//
//
// Заполняет буфер текстом с описанием последней ошибки. Возвращает
// 0, если ошибок не было, 1 если были. Указатель на буфер может быть NULL,
// тогда просто возвращается признак наличия ошибки.
//
//
// http://www.solarix.ru/api/en/sol_GetError.shtml
//
// ****************************************************************************
FAIND_API(int) sol_GetError( HFAIND hEngine, wchar_t *buffer, int buffer_len )
{
 if( hEngine==NULL || buffer==NULL || buffer_len<=0 || !HandleEngine(hEngine)->ok )
  return -1;

 *buffer = 0;

 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker( & HandleEngine(hEngine)->cs_error );
 #endif

 if( buffer!=NULL && buffer_len>0 && !HandleEngine(hEngine)->error.empty() )
  {
   wcsncpy( buffer, HandleEngine(hEngine)->error.c_str(), buffer_len );
   buffer[buffer_len-1]=L'\0';
  }

 return !HandleEngine(hEngine)->error.empty();
}


// *************************************************************************
//
// Copy the error text in UTF-8 buffer.
// Error description is truncated if buffer lenght is not enough
//
// http://www.solarix.ru/api/en/sol_GetError.shtml
//
// *************************************************************************
FAIND_API(int) sol_GetError8( HFAIND hEngine, char *buffer, int buffer_len )
{
 if( hEngine==NULL || buffer==NULL || buffer_len<=0 || !HandleEngine(hEngine)->ok )
  return -1;

 *buffer = 0;

 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker( & HandleEngine(hEngine)->cs_error );
 #endif

 if( buffer!=NULL && buffer_len>0 && !HandleEngine(hEngine)->error.empty() )
  {
   strncpy( buffer, lem::to_utf8(HandleEngine(hEngine)->error).c_str(), buffer_len );
   buffer[buffer_len-1]='\0';
  }

 return !HandleEngine(hEngine)->error.empty();
}


// *************************************************
//
// Clear the error indicator. 
// Очищает внутренний признак ошибки.
//
// http://www.solarix.ru/api/en/sol_ClearError.shtml
//
// *************************************************
FAIND_API(void) sol_ClearError( HFAIND hEngine )
{
 if( hEngine==NULL || !HandleEngine(hEngine)->ok )
  return;

 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker( & HandleEngine(hEngine)->cs_error );
 #endif

 HandleEngine(hEngine)->error.clear();
 return;
}

#endif
