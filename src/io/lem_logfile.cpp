// 02.10.2007 - введена синхронизаци€ дл€ мультитредовых приложений.
// 11.01.2008 - введены методы Begin() и Commit() дл€ принудительного блокировани€ записи
//              с конкурирующих тредов. 

#include <lem/streams.h>
#include <lem/console_streams.h>
#include <lem/logfile.h>

using namespace lem;

lem::Ptr<OFormatter> lem::LogFile::logfile;

#if defined LEM_BORLAND
 namespace std
 {
  void swap( lem::OFormatter *a, lem::OFormatter *b )
  {
   OFormatter *c = a;
   a=b;
   b=c;  
  }
 }
#endif


#if defined LEM_THREADS
lem::Process::CriticalSection lem::LogFile::cs;
#endif 

LogFile::LogFile(void)
{
}


void LogFile::Open( const lem::Path& filename )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker cs_quard(&cs);
 #endif

 logfile = lem::Ptr<OFormatter>( new OUFormatter(filename) );
 logfile->GetStream()->NoBuffer();
 logfile->SetAutoflush();

 return;
}


void LogFile::Set( lem::Ptr<OFormatter> file )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker cs_quard(&cs);
 #endif

 logfile=file;

 return;
}


// *****************************************
// ¬ыводить отладочные сообщени€ на консоль
// *****************************************
void LogFile::Tty(void)
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker cs_quard(&cs);
 #endif

 #if defined LEM_CONSOLE
 logfile = lem::Ptr<OFormatter>( lem::mout, null_deleter() );
 #else
 logfile.reset();
 #endif
 return;
}



void LogFile::Close(void)
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker cs_quard(&cs);
 #endif

 if( logfile )
  {
   logfile.reset();
  }

 return;
}

bool LogFile::IsOpen(void)
{
 return !!logfile;
}

void LogFile::TimeStamp(void)
{
 if( logfile )
  logfile->printf( "%W24us ", timestamp().c_str() ); 

 return;
}



void LogFile::Print( const char *mes )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker cs_quard(&cs);
 #endif

 if( logfile )
  {
   TimeStamp();
   logfile->printf( "%s\r\n", mes );
  }

 return;
}


void LogFile::Print( const wchar_t *mes )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker cs_quard(&cs);
 #endif

 if( logfile )
  {
   TimeStamp();
   logfile->printf( "%us\r\n", mes );
  }

 return;
}

void LogFile::Print( const lem::UFString & mes )
{ Print(mes.c_str()); }

void LogFile::Print( const std::wstring & mes )
{ Print(mes.c_str()); }


// ******************************************************
// ƒл€ записи нескольких сообщений можно принудительно
// запретить другим тредам вмешиватьс€ в запись.
// ******************************************************
void LogFile::Begin(void)
{
 #if defined LEM_THREADS
 cs.Enter();
 #endif
}


// *******************************************
// –азрешаем другим тредам запись в журнал
// *******************************************
void LogFile::Commit(void)
{
 #if defined LEM_THREADS
 cs.Leave();
 #endif
}
