// 26.06.2007 - исправлена печать номера версии wxWidgets в PrintCompilationInfo
// 06.03.2010 - доработка под Qt

#include <lem/config.h>

#if defined LEM_UNIX
 #include <stdlib.h> // realpath()
#endif 

#include <lem/math/math.h>
#include <lem/path.h>
#include <lem/system_config.h>
#include <lem/reflection.h>

#include <boost/version.hpp>

#if defined LEM_ICU
 #include <icu/include/unicode/uversion.h>
#endif

#if defined LEM_WXWIDGETS
 #include <wx/wx.h>
 #include <wx/version.h>
#endif

#if defined LEM_QT
 #include <QLibraryInfo>
 #include <QDir>
 #include <QApplication>
 #include <lem/conversions.h>
#endif

using namespace lem;


// **********************************************************
// ƒл€ какой платформы компилировалась программа.
// Application target OS. It can differ from current host OS.
// **********************************************************
const std::string lem::Reflection::TargetOs(void)
{
 #if defined LEM_GUI
 std::string ui(" GUI");
 #elif defined LEM_CONSOLE
 std::string ui(" console");
 #else
 std::string ui("");
 #endif
 
 #if defined LEM_DOT_NET
  return std::string(".NET Framework")+ui;
 #elif defined LEM_WINDOWS || defined LEM_DOS
  return std::string( "Win32" )+ui;
 #elif defined LEM_LINUX
  return std::string( "GNU/Linux" )+ui;
 #elif defined BOOST_PLATFORM
  return std::string( BOOST_PLATFORM )+ui;
 #else
  return std::string( "unknown" )+ui;
 #endif
}

// **************************************
// Information about the compiler
// **************************************
const std::string lem::Reflection::CompilerInfo(void)
{
 #if defined LEM_COMPILER_NAME && defined LEM_COMPILER_VERSION
  return std::string( LEM_COMPILER_NAME ) + std::string(" v.") + std::string(LEM_COMPILER_VERSION);
 #elif defined BOOST_COMPILER
  return std::string( BOOST_COMPILER );
 #else
  return std::string( "unknown" );
 #endif
}


// *****************************************************************
// List of used libraries with their versions, compiler information,
// and some other data.
// *****************************************************************
void lem::Reflection::PrintCompilationInfo( OFormatter &txt )
{
 const char *bits = "";

 if( sizeof(int)==2 )
  bits = "16bit";
 else if (sizeof(int)==4 && sizeof(void*)==4)
  bits = "32bit";
 else if( sizeof(void*)==8 )
  bits = "64bit";

 txt.printf( "Compiler: %s %s\n", lem::Reflection::CompilerInfo().c_str(), bits );
 txt.printf( "Target platform: %s\n", lem::Reflection::TargetOs().c_str() );

 txt.printf( "sizeof(char)=%d ", sizeof(char) );
 if( char(0xff)<0 )
  txt.printf( "char is signed\n" );
 else
  txt.printf( "char is unsigned\n" );

 txt.printf( "sizeof(wchar_t)=%d ", sizeof(wchar_t) );
 if( wchar_t(0xffffffff)<0 )
  txt.printf( "wchar_t is signed\n" );
 else
  txt.printf( "wchar_t is unsigned\n" );

 txt.printf( "sizeof(int)=%d\n", sizeof(int) );
 txt.printf( "sizeof(void*)=%d\n", sizeof(void*) );
 txt.printf( "sizeof(bool)=%d\n", sizeof(bool) );

 txt.printf( "\nBOOST C++ library v.%s\n", BOOST_LIB_VERSION );

 #if defined LEM_ICU
 txt.printf( "ICU C library v.%s\n", U_ICU_VERSION );
 #endif

 #if defined LEM_WXWIDGETS
  #if defined(_UNICODE) || defined(UNICODE)
  txt.printf( "wxWidgets C++ library v.%us\n", wxVERSION_STRING );
  #else
  txt.printf( "wxWidgets C++library v.%s\n", wxVERSION_STRING );
  #endif
 #endif 

 #if defined LEM_QT
  txt.printf( "Qt library v.%us\n", lem::to_ustr( QLibraryInfo::buildKey() ).c_str() );
 #endif
       
 return;   
}


static lem::Path startup_filename;
static lem::Path startup_folder;

static void InitStartupPath(void)
{
 if( startup_filename.empty() )
  {
   #if defined LEM_QT

    QString qs = QDir::toNativeSeparators( QApplication::applicationDirPath() );
    UFString us(qs);
    startup_folder = lem::Path(us);

    qs = QDir::toNativeSeparators( QApplication::applicationFilePath() );
    us = qs;
    startup_filename = lem::Path(us);

   #else

    lem::Path prog_name;

    #if defined LEM_WINDOWS
     if( lem::System_Config::SupportUnicodeFilenames() )
     {
      wchar_t p[ lem::Path::MaxLen ];
      memset( p, 0, sizeof(p) );
      GetModuleFileNameW( NULL, p, lem::Path::MaxLen );
      prog_name = lem::Path(p);
      lem::Reflection::SetStartupFilename(prog_name);
     }
    else
     {
      char p[ lem::Path::MaxLen ];
      memset( p, 0, sizeof(p) );
      GetModuleFileNameA( NULL, p, lem::Path::MaxLen );
      prog_name = lem::Path(p);
      lem::Reflection::SetStartupFilename(prog_name);
     }
    #elif defined LEM_UNIX
  
    // используем псевдо‘— /proc, если она доступна

    FILE *f = fopen( "/proc/self/cmdline", "r" );
    if( f!=NULL )
     {
      FString buf;
      while( !feof(f) && buf.length()<lem::Path::MaxLen && buf.length()<1024 )
       {
        int c = fgetc(f);
        if( c==EOF || c==0 )
         break;

        buf.Add_Dirty(c);
       }

      fclose(f);
      buf.calc_hash();
      prog_name = lem::Path(buf);
      lem::Reflection::SetStartupFilename(prog_name);
     }

    #endif

   #endif // LEM_QT
  }

 return;
}


void lem::Reflection::SetStartupFilename( const lem::Path &prog_path )
{
 #if !defined LEM_QT

 #if defined LEM_UNIX
 lem::Path p(prog_path);
 FString rel_path = p.GetAscii();
 if( rel_path.empty()==false && !lem::Path::IsPathDelimiter(rel_path.front()) )
  {
   char abs_path[ lem::Path::MaxLen ];
   memset( abs_path, 0, sizeof(abs_path) );
   const char *s = realpath( rel_path.c_str(), abs_path );
   if( s!=NULL )
    p = lem::Path(abs_path);
  }

 startup_filename = p;
 startup_folder = p;
 startup_folder.RemoveLastLeaf();
 #else
 startup_filename = prog_path;
 startup_folder = prog_path;
 startup_folder.RemoveLastLeaf();
 #endif

 #endif

 return;
}


const lem::Path& lem::Reflection::GetStartupFolder(void)
{
 InitStartupPath();
 return startup_folder;
}

const lem::Path& lem::Reflection::GetStartupFilename(void)
{
 InitStartupPath();
 return startup_filename;
}

