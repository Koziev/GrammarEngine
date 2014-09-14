#ifndef LEM_RUNTIME_CHECKS__H
#define LEM_RUNTIME_CHECKS__H
#pragma once

// -----------------------------------------------------------------------------
// File RUNTIME_CHECKS.H
//
// (c) by Elijah Koziev
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// Content:
// Препроцессорно-отключаемая проверка правильности выполнения программы при
// тестировании, и прочее, в том числе отладочные сообщения.
//
// Автоматическая настройка на пользовательский интерфейс ОС.
//
// 22.03.2008 - добавлено определение макроса LEM_DEBUG при отладочной компиляции
// -----------------------------------------------------------------------------
//
// CD->01.01.1995
// LC->16.11.2010
// --------------

#include <lem/config.h>

#include <cstdio>
#include <string>
#include <assert.h>
#include <exception>

#if defined LEM_WXWIDGETS
#include <wx/wx.h>
#include <wx/debug.h>
#endif
 
#if defined LEM_LINUX
 #include <unistd.h>
#else
 #include <cstdlib>
#endif

#if LEM_DEBUGGING==1 && defined LEM_MSC
 #if defined LEM_MFC
  #include <afx.h>
 #endif

 #include <crtdbg.h>
#endif

#include <lem/macros.h>

#undef assert

extern char LEM_ASSERT_MSG1[], LEM_ASSERT_MSG2[], LEM_ASSERT_MSG3[];
extern char LEM_ASSERT_MSG4[], LEM_ASSERT_MSG5[], LEM_ASSERT_MSG6[];
extern char LEM_ASSERT_MSG7[], LEM_ASSERT_MSG8[], LEM_ASSERT_MSG9[];
extern char LEM_ASSERT_MSG10[];

 namespace lem
 {
  class Path;

  #if !defined(LEM_MSC) || _MSC_VER >= 1300
   using std::FILE;
  #endif

  class UFString;
  class FString;

  // **************************************************
  // Базовый класс для всех исключений библиотеки LEM.
  // **************************************************
  class E_BaseException
  {
   private:
    wchar_t *text; // error message
                   // В отличие от std::exception, хранится UNICODE-строка,
                   // так как мы постоянно работаем с русскими сообщениями,
                   // а делать привязку к какой-либо кодовой странице глупо и
                   // непортабельно.

   public:
    E_BaseException(void);
    explicit E_BaseException( const wchar_t *t );
    explicit E_BaseException( const char *t );
    E_BaseException( const E_BaseException& x );
    explicit E_BaseException( const std::wstring &Message );
    explicit E_BaseException( const lem::UFString &Message );
    explicit E_BaseException( const lem::FString &Message );

    ~E_BaseException(void);

    void operator=( const E_BaseException& x );

    inline const wchar_t* what(void) const throw() { return text; }
  };

  // *********************************************
  // Ошибки при трансляции Словаря.
  // *********************************************
  class E_ParserError : public E_BaseException
  {
   public:
    E_ParserError(void) {}
    explicit E_ParserError( const wchar_t * ErrorText )
     :E_BaseException(ErrorText) {}
    explicit E_ParserError( const std::wstring& ErrorText )
     :E_BaseException(ErrorText) {}
    explicit E_ParserError( const lem::UFString& ErrorText )
     :E_BaseException(ErrorText) {}
  };


 // *************************************************
 // General exception for run-time checks.
 // *************************************************
 struct ECheckFault : public E_BaseException
 {
  ECheckFault() : E_BaseException () {}

  explicit ECheckFault( const std::wstring &Message )
   :E_BaseException(Message) {}
 };


 // *************************************************
 // Exception for memory allocation fault
 // *************************************************
 struct EMemFault : public E_BaseException
 {
  EMemFault() : E_BaseException () {}

  explicit EMemFault( const std::wstring &Message )
   :E_BaseException(Message) {}
 };


 // *************************************************
 // Exceptions for file operation
 // *************************************************
 struct EFileFault : public ECheckFault
 {
  EFileFault() : ECheckFault () {}

  explicit EFileFault( const std::wstring &Message )
   :ECheckFault(Message) {}
 };


 // *************************************************
 // Ошибка открытия файла.
 // *************************************************
 struct EFileOpenFault : public EFileFault
 {
  EFileOpenFault() : EFileFault () {}

  explicit EFileOpenFault( const std::wstring &Message )
   :EFileFault(Message) {}
 };


  extern void check_failed(
                           const char *mes,
                           const char *cond,
                           const char *filename,
                           int line
                          );

  extern void check_failed_a(
                             const char *mes,
                             const char *mes1,
                             const char *cond,
                             const char *filename,
                             int line
                            );

  extern void check_failed_a2(
                              const char *mes,
                              const char *mes1,
                              const char *mes2,
                              const char *cond,
                              const char *filename,
                              int line
                             );

 extern std::string GetErrorString(void);


 #if defined LEM_DEBUGON

  #if !defined LEM_DEBUG
   #define LEM_DEBUG 1
  #endif

  #if defined LEM_WXWIDGETS
   #define lem_myAssert(p) wxASSERT(!!(p)) 
   //#define lem_myAssert(p) ((!!(p)) ? (void)0 : (void)lem::check_failed( LEM_ASSERT_MSG5, #p, __FILE__, __LINE__ ) );
   #define lem_myassert_a(p,m) ((!!(p)) ? (void)0 : (void)lem::check_failed_a( LEM_ASSERT_MSG5, m,  #p, __FILE__, __LINE__ ) );
   #define lem_myassert_a2(p,m,txt) ((!!(p)) ? (void)0 : (void)lem::check_failed_a2( LEM_ASSERT_MSG6, m, txt, #p, __FILE__, __LINE__ ) );
   #define LEM_STOPIT      wxFAIL

   #define LEM_STOPIT_A(mes) wxFAIL_MSG(_T(mes))
   #define LEM_STOPIT_A2(mes,txt) wxFAIL_MSG(_T(mes))

   #define LEM_TRAP wxTrap
/*
  #elif defined LEM_DOT_NET
   #define lem_myAssert(p) System::Diagnostics::Debug::Assert(!!(p))
   #define LEM_STOPIT      System::Diagnostics::Debug::Assert(false)
   #define LEM_STOPIT_A(mes) System::Diagnostics::Debug::Assert(!!(p),new System::String(L##mes))
   #define LEM_STOPIT_A2(mes,txt) System::Diagnostics::Debug::Assert(!!(p), System::String::Concat( new System::String(L##mes),  new System::String(L##txt) ) )
   #define LEM_TRAP 
*/
  #elif defined LEM_MSC
   // Microsoft VisualStudio debug macros
   #define lem_myAssert(p)        _ASSERTE(!!(p))
   #define lem_myassert_a(p,mes)      { if(!(p)) { _RPTF1(_CRT_ERROR,"LEM assert macro reached, execution aborted. %s",mes); } }
   #define lem_myassert_a2(p,mes,txt) { if(!(p)) { _RPTF2(_CRT_ERROR,"LEM assert macro reached, execution aborted. %s %s",mes,txt); } }
   #define LEM_STOPIT             { _RPTF0(_CRT_ERROR,"LEM_STOPIT: execution aborted"); }
   #define LEM_STOPIT_A(mes)      { _RPTF1(_CRT_ERROR,"LEM_STOPIT: execution aborted. %s",mes); }
   #define LEM_STOPIT_A2(mes,txt) { _RPTF2(_CRT_ERROR,"LEM_STOPIT: execution aborted. %s %s",mes,txt); }
   #define LEM_TRAP _CrtDbgBreak();
  #else 
   // Default portable implementations
   #define lem_myAssert(p) ( !!(p) ? (void)0 : (void)lem::check_failed( LEM_ASSERT_MSG1,  #p, __FILE__, __LINE__ ) );
   #define lem_myassert_a(p,m) ( !!(p) ? (void)0 : (void)lem::check_failed_a( LEM_ASSERT_MSG5, m,  #p, __FILE__, __LINE__ ) );
   #define lem_myassert_a2(p,m,txt) ( !!(p) ? (void)0 : (void)lem::check_failed_a2( LEM_ASSERT_MSG6, m, txt, #p, __FILE__, __LINE__ ) );
   #define LEM_STOPIT { lem::check_failed( LEM_ASSERT_MSG2, LEM_ASSERT_MSG7, __FILE__, __LINE__  );  throw lem::E_BaseException(); }
   #define LEM_STOPIT_A(mes) { lem::check_failed( LEM_ASSERT_MSG3,  mes, __FILE__, __LINE__  );  throw lem::E_BaseException(); }
   #define LEM_STOPIT_A2(mes,txt) { lem::check_failed_a( LEM_ASSERT_MSG4, mes, txt, __FILE__, __LINE__ ); throw lem::E_BaseException(); }
   #define LEM_TRAP 
  #endif

  #define LEM_CHECKIT( cond ) { lem_myAssert(cond); }
  #define LEM_CHECKIT_Z( cond ) { lem_myAssert(cond); }
  #define LEM_CHECKIT_A( cond, mes ) { lem_myassert_a(cond,mes); }
  #define LEM_CHECKIT_AZ( cond, mes ) { lem_myassert_a(cond,mes); }
  #define LEM_CHECKIT_A2( cond, mes, txt ) { lem_myassert_a2(cond,mes,txt); }
  #define LEM_CHECKIT_A2Z( cond, mes, txt ) { lem_myassert_a2(cond,mes,txt); }

 #else

  #define LEM_TRAP 

  #define LEM_CHECKIT(cond)             { cond; }
  #define LEM_CHECKIT_Z(cond)           {       }
  #define LEM_CHECKIT_A(cond,mes)       { cond; }
  #define LEM_CHECKIT_AZ(cond,mes)      {       }
  #define LEM_CHECKIT_A2(cond,mes,txt)  { cond; }
  #define LEM_CHECKIT_A2Z(cond,mes,txt) {       }

  #define LEM_STOPIT { lem::check_failed( LEM_ASSERT_MSG2, LEM_ASSERT_MSG7, __FILE__, __LINE__  );  throw lem::E_BaseException(); }
  #define LEM_STOPIT_A(mes) { lem::check_failed( LEM_ASSERT_MSG3,  mes, __FILE__, __LINE__  );  throw lem::E_BaseException(); }
  #define LEM_STOPIT_A2(mes,txt) { lem::check_failed_a( LEM_ASSERT_MSG4, mes, txt, __FILE__, __LINE__ ); throw lem::E_BaseException(); }

 #endif


  // *************************************************************************
  // Класс для отлова ошибок типа "memory overrun" или "расстрел памяти".
  // Представляет из себя поле размером в несколько байтов.
  // Конструктор инициализирует байтовое поле эталонным значением, и
  // при каждом вызове Assert() и деструктора проверяется, что значение
  // не изменилось.
  // *************************************************************************
  class Guardian
  {
   private:
    unsigned long t;

   public:
    Guardian(void) { t = 0xa5a5a5a5UL; }

    ~Guardian(void)
    {
     Assert();
     t=0;
    }

    inline void Assert(void) const
    { LEM_CHECKIT_Z( t == 0xa5a5a5a5UL ); }
  };

 // Макрос для неотключаемой проверки указателей.
 #define check_ptr_hard(ptr) if( (ptr)==NULL ) lem::mem_failed(); else (void)0

 // Проверка успешности выделения динамической памяти может быть отключена,
 // если внутри процедур выделения памяти уже встроена таковая.
 #if defined LEM_INTRINSIC_MEMFAULT
  #define check_ptr(ptr) (ptr)
  #define check_ptr_z(ptr) {}
 #else
  #define check_ptr(ptr) lem::check_ptr_hard(ptr)
  #define check_ptr_z(ptr) lem::check_ptr_hard(ptr)
 #endif

 extern void mem_failed(void);

 extern void check_file( const FILE *file, const char *filename=NULL );
 extern void check_file( const FILE *file, const wchar_t *filename );
 extern void check_file( const FILE *file, const lem::Path& filename );

 #if defined LEM_DOT_NET

  #define LEM_DOTNET_CATCH \
   catch( System::Data::OleDb::OleDbException *x ) \
    { \
     lem::Shell::OleDbError(x,S""); \
    } \
   catch( System::Exception *x ) \
    { \
     lem::Shell::Error( to_wstr( x->get_Message() ).c_str() ); \
    } 
 #else
  #define LEM_DOTNET_CATCH 
 #endif

 #define LEM_CATCH  LEM_DOTNET_CATCH \
   catch( const lem::E_BaseException &e1 )      \
    {                                          \
     lem::Shell::Error( e1.what() );            \
    }                                          \
   catch( const std::exception &e2 )            \
    {                                          \
     lem::Shell::Error( e2.what() );            \
    }                                          \
   catch( ... )                                \
    {                                          \
     lem::Shell::Error( "Unhandled error\n" ); \
    }                                          


 #if LEM_DEBUGGING==1
  #if defined LEM_MSC
   #if defined LEM_MFC
    inline void CheckMemory() { LEM_CHECKIT_Z( AfxCheckMemory() ); }
   #else
    inline void CheckMemory() { LEM_CHECKIT_Z( _CrtCheckMemory() ); }
   #endif

	inline void CheckHeapPtr( const void* ptr ) { LEM_CHECKIT_Z( !ptr || _CrtIsValidHeapPointer(ptr)!=0 ); }
  #else
   // Implement for this platform!
   inline void CheckMemory() {}
   inline void CheckHeapPtr( const void * ) {}
  #endif
 #else
 // Disabled for RELEASE version
 #define CheckMemory() {}
 #define CheckHeapPtr(ptr) {}
 #endif

 } // end of namespace 'lem'

#endif
