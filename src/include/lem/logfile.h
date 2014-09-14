// 02.10.2007 - добавлена критическа€ секци€ дл€ разруливани€ инициализации

#ifndef LEM_LOGGING__H
#define LEM_LOGGING__H
#pragma once

 #include <lem/streams.h>
 #include <lem/config.h>
 #include <lem/smart_pointers.h>
 #include <lem/oformatter.h>

 #if defined LEM_THREADS
  #include <lem/process.h>
 #endif

 namespace lem
 {
  class LogFile
  {
   private:
    #if defined LEM_THREADS
    static lem::Process::CriticalSection cs;
    #endif 

   public:
    LogFile(void);

    static lem::Ptr<OFormatter> logfile;

    static void Open( const lem::Path& filename );
    static void Set( lem::Ptr<OFormatter> file );

    // ¬ыводить отладочные сообщени€ на консоль
    static void Tty(void);

    static bool IsOpen(void);

    static void Close(void);

    // «аписываетс€ отметка времени
    static void TimeStamp(void);

    static void Print( const char *mes );
    static void Print( const wchar_t *mes );
    static void Print( const lem::UFString &mes );
    static void Print( const std::wstring &mes );
    
    // ƒл€ записи нескольких сообщений можно принудительно
    // запретить другим тредам вмешиватьс€ в запись.
    static void Begin(void);
    static void Commit(void);
  };

 } // namespace lem

#endif
