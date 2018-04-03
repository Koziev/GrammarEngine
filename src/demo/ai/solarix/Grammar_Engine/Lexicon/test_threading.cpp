// Mutlithreading tests for Morphology and Syntax Analyzers
//
// API documentation: http://www.solarix.ru/for_developers/api/grammar-engine-api.shtml
// Other samples: http://www.solarix.ru/for_developers/api/grammar-engine-examples.shtml
// Troubleshooting: http://www.solarix.ru/contacts/contacts.shtml

#include <assert.h>
//#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#if defined WIN32
#include <process.h>
#include <windows.h>
#else
#define USE_PTHREAD
#include <pthread.h>
#include <unistd.h>
#endif


// Grammar Engine API
#include "../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../include/lem/solarix/_sg_api.h"

extern void failed( HGREN hEngine );
extern void TestMorphologicalAnalyzer( HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, bool use_model, int thread_no );
extern void TestSyntacticAnalyzer( HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, int thread_no );


struct ThreadRes
{
 int ithread;
 HGREN hEngine;
 int id_language;
 const char *infile_morph;
 const char *infile_syntax;

 int beam_size;

 int n_sent; // total number of sentences
 int n_fail; // total number of failed syntax analyses
 int n_roots; // total number of roots in variators
 int n_complete; // total number of complete syntax analyses
 int n_toks;

 ThreadRes(void) : ithread(-1), hEngine(NULL), id_language(-1), n_sent(0), n_fail(0), n_roots(0), n_complete(0), n_toks(0),
 infile_morph(NULL), infile_syntax(NULL), beam_size(30) {}

 bool operator==( const ThreadRes & x ) const
 {
  return n_sent==x.n_sent &&
         n_fail==x.n_fail &&
         n_roots==x.n_roots &&
         n_complete==x.n_complete &&
         n_toks==x.n_toks;
 }

 bool operator!=( const ThreadRes & x ) const { return !operator==(x); }

 void print(void) const
 {
  printf( "n_sent=%d\n", n_sent );
  printf( "n_toks=%d\n", n_toks );
  printf( "n_fail=%d\n", n_fail );
  printf( "n_roots=%d\n", n_roots );
  printf( "n_complete=%d\n", n_complete );
  return;
 }

};


#if defined WIN32
static HANDLE hSem = NULL;
#else
static pthread_mutex_t hSem;
static pthread_mutexattr_t hSemAttr;
#endif


#if defined WIN32
static volatile LONG tcount=0;
#else
static volatile int tcount=0;
#endif


// Эта функция выполняется в отдельном треде.
#if defined WIN32
void __cdecl ThreadFun( void * arg )
#else
void* ThreadFun( void * arg )
#endif
{
 ThreadRes * res = (ThreadRes*)arg;

 HGREN hEngine = res->hEngine;

 if( !(res->ithread%2) )
  {
   TestMorphologicalAnalyzer( hEngine, res->id_language, res->beam_size, res->infile_morph, false, false, res->ithread );
   TestSyntacticAnalyzer( hEngine, res->id_language, res->beam_size, res->infile_syntax, false, res->ithread );
  }
 else
  {
   TestSyntacticAnalyzer( hEngine, res->id_language, res->beam_size, res->infile_syntax, false, res->ithread );
   TestMorphologicalAnalyzer( hEngine, res->id_language, res->beam_size, res->infile_morph, false, false, res->ithread );
  } 

 #if defined WIN32
 if( hSem!=NULL )
  {
   LONG c = InterlockedDecrement(&tcount);
   if( c==0 )
    {
     SetEvent( hSem );
    }
  }
 #else
 pthread_mutex_lock(&hSem);
 tcount--;
 printf( "\nThread %d has exited, tcount=%d\n", res->ithread, tcount );
 pthread_mutex_unlock(&hSem);
 #endif

 #if defined USE_PTHREAD
 return NULL;
 #else
 return;
 #endif
}


void Test_Threading( HGREN hEngine, int id_language, const char *infile_morph, const char *infile_syntax )
{
 // Define the number of threads to run simultaneously
 
 #if defined WIN32
 const int NTHREAD = 3;
 #else
 const int NTHREAD = 3;
 #endif
 
 printf( "Start multithreading test...\n" );
 
 ThreadRes tres[NTHREAD];
 tcount = NTHREAD;

 #if defined USE_PTHREAD
 pthread_t hThread[NTHREAD];

 pthread_mutexattr_init( &hSemAttr );
 pthread_mutexattr_settype( &hSemAttr, PTHREAD_MUTEX_NORMAL );
 pthread_mutex_init(&hSem,&hSemAttr);
 #else
 hSem = CreateEventA( NULL, true, false, "SolarixThreadEvent" );
 #endif

 for( int i=0; i<NTHREAD; ++i )
  {
   tres[i].hEngine = hEngine;
   tres[i].ithread = i;
   tres[i].infile_morph = infile_morph;
   tres[i].infile_syntax = infile_syntax;
   tres[i].id_language = id_language;

   #if defined WIN32
   _beginthread( &ThreadFun, 0, &tres[i] );
   #else
   pthread_create( &hThread[i], NULL, ThreadFun, (void*)&tres[i] );
   #endif
  }

 #if defined WIN32
 // Ждем окончания работы всех нитей
 WaitForSingleObject( hSem, INFINITE );
 CloseHandle(hSem);
 #else

 while(1)
 {
  if( tcount==0 )
   break;

  sleep(2);
  printf( "-zzz(%d)-", tcount ); fflush(stdout);
 }

 pthread_mutex_destroy(&hSem);
 pthread_mutexattr_destroy(&hSemAttr);
 #endif

 printf( "\nMultithreading test hase completed.\n" );

 return;
}
