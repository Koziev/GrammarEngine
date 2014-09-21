// Кросс-платформенная обертка для работы с DLL.
//
// 27.06.2007 - перед вызовом LoadLibrary подавляется выдача
//              диалоговых окон по поводу ошибок.
//
// 23.10.2007 - в версии для wx метод Dll::Import сначала
//              проверяет, что импортируемый символ есть,
//              так как иначе wx выдает ошибку.
//
// 03.07.2008 - добавлено журналирование ошибок загрузки DLL
// 11.03.2010 - под Mac OS X (Darwin) умолчальное расширение
//              забито как "dylib"
// 11.03.2010 - на фреймворке Qt используется QLibrary
// ---------------------------------------------------------
//
// CD->08.04.2007
// LC->08.10.2010
// --------------

#include <lem/config.h>
#include <lem/logfile.h>

#if defined LEM_MFC
 #include <afxwin.h>
#elif defined LEM_WINDOWS
 #include <windows.h>
#endif

#if defined LEM_UNIX

 #include <stdlib.h>

 // Apache portable runtime source code is used.

 #define DSO_USE_DLFCN

 #if defined DSO_USE_DLFCN
  #include <dlfcn.h>
 #endif

 #if defined HAVE_MACH_O_DYLD_H
  #include <mach-o/dyld.h>
 #elif defined HAVE_DLFCN_H
  #include <dlfcn.h>
 #elif defined HAVE_DL_H
  #include <dl.h>
 #endif

 #ifndef RTLD_NOW
  #define RTLD_NOW 1
 #endif

 #ifndef RTLD_GLOBAL
  #define RTLD_GLOBAL 0
 #endif

 #if (defined(__DragonFly__) ||\
     defined(__FreeBSD__) ||\
     defined(__OpenBSD__) ||\
     defined(__NetBSD__)     ) && !defined(__ELF__)
  #define DLSYM_NEEDS_UNDERSCORE
 #endif
  
#endif

#include <lem/system_config.h>
#include <lem/conversions.h>
#include <lem/process.h>

using namespace lem::Process;

Dll::Dll(void)
{
 #if defined LEM_QT
 qtdii = NULL;
 #elif defined LEM_WXWIDGETS
 wxdll = NULL;
 #elif defined LEM_WINDOWS
 hlib = NULL;
 #elif defined LEM_UNIX
 hlib = NULL;
 #endif
}


Dll::~Dll(void)
{
 Free();
}


// ***********************************************************
// Стандартное расширение для DLL файлов для текущей платформы
// ***********************************************************
const char* Dll::StdExtension(void)
{
 #if defined LEM_WINDOWS
 return "dll"; 
 #elif defined(__HPUX__)
 return "sl";
 #elif defined LEM_DARWIN
 return "dylib";
 #elif defined LEM_UNIX
 return "so";
 #else 
  #error 
 #endif
}


// *********************************************
// Загрузка DLL из указанного файла
// *********************************************
bool Dll::Load( const lem::Path& _filename, bool add_extension )
{
 LEM_CHECKIT_Z( !_filename.empty() );

 error_msg.clear();
 filename = _filename;

 if( add_extension )
  filename.AddExtension( StdExtension() );

 if( lem::LogFile::IsOpen() )
  {
   lem::LogFile::logfile->printf( "Trying to load DLL '%us'\n", filename.GetUnicode().c_str() );
   
   bool exists = filename.DoesExist();
   lem::LogFile::logfile->printf( "File %us %s\n", filename.GetUnicode().c_str(), exists ? "exists" : "does not exist" );
  }

 #if defined LEM_QT

  LEM_CHECKIT_Z(qtdll==NULL);
  qtdll = new QLibrary( filename.GetUnicode().to_qt() );
  bool res = qtdll->load();

  if( !res )
   {
    error_msg = lem::to_ustr( qtdll->errorString() );
   }

  if( !res && lem::LogFile::IsOpen() )
   {
    lem::LogFile::Print( lem::format_str( L"Could not load DLL '%ls'", filename.GetUnicode().c_str() ).c_str() );
   }
  
  return res;

 #elif defined LEM_WXWIDGETS

  LEM_CHECKIT_Z(wxdll==NULL);
  wxdll = new wxDynamicLibrary();
  bool res = wxdll->Load( wxString(filename.GetUnicode().c_str()) );
  if( !res && lem::LogFile::IsOpen() )
   {
    lem::LogFile::Print( lem::format_str( L"Could not load DLL '%ls'", filename.GetUnicode().c_str() ).c_str() );
   }
  
  return res;

 #elif defined LEM_WINDOWS

 LEM_CHECKIT_Z(hlib==NULL);

 // Подавляем выдачу диалога с сообщением об ошибке, пусть LoadLibrary
 // просто вернет NULL.
 UINT err_mode = SetErrorMode( SEM_FAILCRITICALERRORS );

 if( lem::System_Config::SupportUnicodeFilenames() )
  hlib = LoadLibraryW( filename.GetUnicode().c_str() );
 else
  hlib = LoadLibraryA( filename.GetAscii().c_str() );

 #if LEM_DEBUGGING==0
 SetErrorMode( err_mode );
 #endif

 if( hlib==NULL )
  {
   std::string err = lem::GetErrorString();
   error_msg = to_unicode(err);

   if( lem::LogFile::IsOpen() )
    { 
     lem::LogFile::Print( lem::format_str( L"Could not load DLL '%ls', error=%ls", filename.GetUnicode().c_str(), err.c_str() ).c_str() );
    }
  }

 return hlib!=NULL;

 #elif defined LEM_UNIX

 LEM_CHECKIT_Z(hlib==NULL);

  #if defined(DSO_USE_SHL)

   hlib = shl_load( filename.GetAscii().c_str(), BIND_IMMEDIATE, 0L );

  #elif defined(DSO_USE_DYLD)

   NSObjectFileImage image;
   NSModule os_handle = NULL;
   NSObjectFileImageReturnCode dsoerr;
   const char* err_msg = NULL;
   dsoerr = NSCreateObjectFileImageFromFile(path, &image);

   if( dsoerr == NSObjectFileImageSuccess )
    {
     #if defined(NSLINKMODULE_OPTION_RETURN_ON_ERROR) && defined(NSLINKMODULE_OPTION_NONE)
     hlib = NSLinkModule(
                         image,
                         filename.GetAscii().c_str(),
                         NSLINKMODULE_OPTION_RETURN_ON_ERROR | NSLINKMODULE_OPTION_NONE
                        );
     /* If something went wrong, get the errors... */
     if( !hlib )
      {
/*
       NSLinkEditErrors errors;
            int errorNumber;
            const char *fileName;
            NSLinkEditError(&errors, &errorNumber, &fileName, &err_msg);
*/
      }
     #else
      hLib = NSLinkModule(image, filename.GetAscii().c_str(), FALSE );
     #endif
     NSDestroyObjectFileImage(image);
    }
   else if( (dsoerr == NSObjectFileImageFormat ||
             dsoerr == NSObjectFileImageInappropriateFile) &&
             NSAddLibrary(filename.GetAscii().c_str()) == TRUE)
    {
     hLib = (NSModule)DYLD_LIBRARY_HANDLE;
    }
   else
    {
     //   err_msg = "cannot create object file image or add library";
    }

  #elif defined(DSO_USE_DLFCN)
   #if defined(OSF1) || defined(SEQUENT) || defined(SNI) || \
    (defined(__FreeBSD_version) && (__FreeBSD_version >= 220000)) || \
    defined(__DragonFly__)
//    void *os_handle = dlopen((char *)path, RTLD_NOW | RTLD_GLOBAL);
    hlib = dlopen( filename.GetAscii().c_str(), RTLD_NOW | RTLD_GLOBAL );

   #else
    int flags = RTLD_NOW | RTLD_GLOBAL;
   #ifdef _AIX
    if( strchr(path + 1, '(') && path[strlen(path) - 1] == ')' )
     {
      /* This special archive.a(dso.so) syntax is required for
       * the way libtool likes to build shared libraries on AIX.
       * dlopen() support for such a library requires that the
       * RTLD_MEMBER flag be enabled.
       */
      flags |= RTLD_MEMBER;
     }
    #endif
    
     hlib = dlopen( filename.GetAscii().c_str(), RTLD_NOW );//LAZY );

   #endif
   
   if( hlib==NULL )
    {
     error_msg = lem::to_unicode( dlerror() );
    }
  #endif /* DSO_USE_x */

 if( lem::LogFile::IsOpen() )
  {
   lem::LogFile::logfile->printf( "Library %us %s loaded\n", filename.GetUnicode().c_str(), hlib==NULL ? "is not" : "successfully" );
  } 

 return hlib!=NULL;

 #else

 return false;

 #endif
}



bool Dll::Load( const char *filename, bool add_extension )
{
 LEM_CHECKIT_Z( filename!=NULL );
 lem::Path p(filename);
 return Load(p,add_extension);
}

bool Dll::Load( const wchar_t *filename, bool add_extension )
{
 LEM_CHECKIT_Z( filename!=NULL );
 lem::Path p(filename);
 return Load(p,add_extension);
}
       

// *********************************************
// Выгружаем DLL
// *********************************************
void Dll::Free(void)
{
 filename.empty(); 

 #if defined LEM_QT

  if( qtdll!=NULL )
   {
    qtdll->unload();
    lem_rub_off(qtdll);
   }

 #elif defined LEM_WXWIDGETS

  if( wxdll!=NULL )
   {
    wxdll->Unload();
    lem_rub_off(wxdll);
   }

 #elif defined LEM_WINDOWS

 if( hlib!=NULL )
  { 
   FreeLibrary(hlib);
   hlib=NULL;
  }
 #elif defined LEM_UNIX

 if( hlib!=NULL )
  {
   #if defined(DSO_USE_SHL)
    shl_unload((shl_t)hLib);
   #elif defined(DSO_USE_DYLD)
    if(hLib != DYLD_LIBRARY_HANDLE)
     {
      NSUnLinkModule( hLib, FALSE );
     }
   #elif defined(DSO_USE_DLFCN)
    dlclose(hlib);
   #endif
 
   hlib=NULL;
  } 
 #else
 
 #endif
 
 error_msg.clear();
 return; 
}

 
// *********************************************
// Загружена ли DLL
// *********************************************
bool Dll::IsLoaded(void) const
{
 #if defined LEM_QT
 return qtdll && qtdll->isLoaded();
 #elif defined LEM_WXWIDGETS
 return wxdll && wxdll->IsLoaded();
 #elif defined LEM_WINDOWS
 return hlib!=NULL; 
 #elif defined LEM_UNIX
 return hlib!=NULL;
 #else
 return false;
 #endif
}



// *********************************************
// Возвращает адрес экспортируемого символа
// *********************************************
const void* Dll::Import( const char *name ) const
{
 LEM_CHECKIT_Z( name!=NULL );

 #if defined LEM_QT

 LEM_CHECKIT_Z( qtdll!=NULL );
 if( qtdll==NULL )
  return NULL;

 QString s(name);
 return qtdll->resolve(s);

 #elif defined LEM_WXWIDGETS

 LEM_CHECKIT_Z(wxdll!=NULL);

 if( wxdll==NULL )
  return NULL;

 wxString n( UFString(name).c_str() );

 if( wxdll->HasSymbol(n) )
  return wxdll->GetSymbol( n );
 else
  return NULL;

 #elif defined LEM_WINDOWS

 LEM_CHECKIT_Z(hlib!=NULL);
 if( hlib==NULL )
  return NULL;
 
 return (const void*)GetProcAddress( hlib, name );

 #elif defined LEM_UNIX

 LEM_CHECKIT_Z(hlib!=NULL);

 if( hlib==NULL )
  return NULL;

  #if defined(DSO_USE_SHL)
   void *symaddr = NULL;
   int status;

   errno = 0;
   status = shl_findsym( (shl_t *)&hLib, name, TYPE_PROCEDURE, &symaddr );
   if( status == -1 && errno == 0) /* try TYPE_DATA instead */
    status = shl_findsym( (shl_t *)&hLib, name, TYPE_DATA, &symaddr);
   if(status == -1)
    return NULL;

   return symaddr;

  #elif defined(DSO_USE_DYLD)
   void *retval = NULL;
   NSSymbol symbol;
   char *symname2 = (char*)malloc(sizeof(char)*(strlen(name)+2));
   sprintf(symname2, "_%s", symname);
   #ifdef NSLINKMODULE_OPTION_PRIVATE
    if( handle->handle == DYLD_LIBRARY_HANDLE)
     {
      symbol = NSLookupAndBindSymbol(symname2);
     }
    else
     {
      symbol = NSLookupSymbolInModule((NSModule)hLib, symname2);
     }
   #else
    symbol = NSLookupAndBindSymbol(symname2);
   #endif
    free(symname2);
    if(symbol == NULL)
     {
      //handle->errormsg = "undefined symbol";
	  //return APR_ESYMNOTFOUND;
      return NULL;
     }

    retval = NSAddressOfSymbol(symbol);
    if(retval == NULL)
     {
      //handle->errormsg = "cannot resolve symbol";
	  //return APR_ESYMNOTFOUND;
      return NULL;
     }

    return retval;

  #elif defined(DSO_USE_DLFCN)

   #if defined(DLSYM_NEEDS_UNDERSCORE)
    void *retval;
    char *symbol = (char*)malloc(sizeof(char)*(strlen(name)+2));
    sprintf(symbol, "_%s", name);
    retval = dlsym( hlib, symbol );
    free(symbol);
   #elif defined(SEQUENT) || defined(SNI)
    void *retval = dlsym(hlib, name);
   #else
    void *retval = dlsym(hlib, name);
   #endif /* DLSYM_NEEDS_UNDERSCORE */
   if(retval == NULL)
    {
     //handle->errormsg = dlerror();
     //return APR_ESYMNOTFOUND;
     return NULL;
    }
    
   return retval;
  #endif /* DSO_USE_x */

 #else

 return NULL;

 #endif
}


bool Dll::HasSymbol( const char *name ) const
{
 LEM_CHECKIT_Z( name!=NULL );

 #if defined LEM_QT
 LEM_CHECKIT_Z(qtdll!=NULL);
 return qtdll && qtdll->resolve( QString(name) )!=NULL;
 #elif defined LEM_WXWIDGETS
 LEM_CHECKIT_Z(wxdll!=NULL);
 return wxdll && wxdll->HasSymbol( wxString( UFString(name).c_str() ) );
 #elif defined LEM_WINDOWS
 LEM_CHECKIT_Z(hlib!=NULL);
 return hlib!=NULL && GetProcAddress( hlib, name )!=NULL;
 #elif defined LEM_UNIX
 LEM_CHECKIT_Z(hlib!=NULL);
 return hlib!=NULL && Import(name)!=NULL;
 #else
 return NULL;
 #endif
}

const wchar_t* Dll::Error(void) const
{
 return error_msg.empty() ? L"" : error_msg.c_str();
}
