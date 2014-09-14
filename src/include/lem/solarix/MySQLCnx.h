#if !defined MySQLCnx__H && defined SOL_MYSQL_DICTIONARY_STORAGE
 #define MySQLCnx__H

 #include <lem/config.h>
 
 #if defined LEM_WINDOWS
  #include <windows.h>
 #endif

 #include <lem/mysql/mysql.h>
 #include <lem/process.h>

 namespace Solarix
 {
  struct MySQLCnx
  {
   #if defined LEM_THREADS
   lem::Process::CriticalSection cs;
   #endif
  
   MYSQL * mysql;

   volatile int tx_count;

   MySQLCnx(void) : mysql(NULL), tx_count(0) {}

   bool InTransaction(void) const { return tx_count>0; }
  };
 }

#endif
