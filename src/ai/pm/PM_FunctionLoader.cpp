#include <lem/solarix/translation.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/PM_FunctionLoader.h>

using namespace Solarix;

PM_FunctionLoader::PM_FunctionLoader( Solarix::Dictionary *Dict )
{
 dict = Dict;
 storage = NULL;
 functions = NULL;
 loaded=false;
 marker=NULL;
 return;
}

PM_FunctionLoader::~PM_FunctionLoader(void)
{
 Delete();
 return;
}

void PM_FunctionLoader::Delete(void)
{
 lem_rub_off(functions);
 return; 
}

void PM_FunctionLoader::Load(void)
{
 LEM_CHECKIT_Z( marker!=NULL );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 if( !loaded )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   functions = storage->GetFunctions(marker);
   loaded = true;
  }

 return;
}


void PM_FunctionLoader::Connect( LexiconStorage *Storage, const wchar_t *Marker )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs_init); 
 #endif

 Delete();
 marker = Marker;
 storage = Storage;
 return;
}


TrFunctions& PM_FunctionLoader::Get(void)
{
 Load();
 return *functions;
}

void PM_FunctionLoader::CompilationFinished(void)
{
 #if defined SOL_LOADTXT && defined SOL_COMPILER
 Load(); // на случай, если при компиляции ни одной функции не прочитано.
 functions->CompilationFinished();
 Store();
 #endif
 return;
}


void PM_FunctionLoader::Store(void)
{
 storage->StoreFunctions(functions,marker);
 return;
}

