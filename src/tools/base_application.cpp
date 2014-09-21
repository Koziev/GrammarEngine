// CD->13.02.2005
// LC->01.11.2008
// --------------

#include <lem/cfg_parser.h>
#include <lem/user_interface.h>
#include <lem/system_config.h>
#include <lem/console_application.h>


using namespace lem;
using namespace lem::Cfg_Parser;
using namespace lem::UI;
using namespace lem::Char_Stream;


void Base_Application::Open_Ini_Parser( Ini_Parser &ini, const lem::Path& filename )
{
/*
 BinaryFile *ini_file = new BinaryFile( filename, true, false );
 StreamPtr ini_file_x(ini_file);

 lem::Char_Stream::Char_Reader *reader = new lem::Char_Stream::Char_Reader(ini_file_x);
 lem::Char_Stream::WideStreamPtr reader_x( reader );
 ini.Open( reader_x );
*/

 ini.Open(filename);

 return;
}

bool Base_Application::Read_Ini( lem::Stream& ini_file )
{
 bool res=false;

 try
  {
   lem::Char_Stream::Char_Reader *reader = NULL;
   
   reader = new lem::Char_Stream::Char_Reader( lem::Ptr<Stream>(&ini_file,null_deleter()), lem::cp1250 );
   
   lem::Char_Stream::WideStreamPtr reader_x( reader );
   Ini_Parser ini;
   ini.Open( reader_x );
   TryRead(ini);
   res = true;
  }
 catch(...)
  {
  }

 return res;
}


bool Base_Application::Read_Ini( const lem::Path& filename )
{
 try
  {
   if( !filename.DoesExist() ) 
    // Config file is not accessible. It is not worth trying to read it.
    return false;

   // Загружаем ini-файл с настройками
   Ini_Parser ini;

   Open_Ini_Parser(ini,filename);
   TryRead(ini);
  }
 catch(...)
  {
   // Файл конфигурации не найден, либо возникли необработанные ошибки
   // при чтении из него.
   #if LEM_DEBUGGING==1
//   merr->printf( "Error occured while loading ini file '%us'\n", filename.Get_Unicode().c_str() );
   #endif
   return false;
  }

 return true;
}



void Base_Application::TryRead( Ini_Parser &ini )
{
 // Текущий язык и кодовая страница
 string lang = ini.get_string( "ui", "lang", "" );

 if( !lang.empty() )
  // Принудительно выставляем
  get_UI().SetCurrLang( lang.c_str() );

 string session_cp = ini.get_string( "ui", "session_CodeConverter", "" );
 string tty_cp = ini.get_string( "ui", "tty_CodeConverter", "" );

 // Если кодовая страница для консоли не переопределена явно в ini-файле, то
 // полагаемся на автоматическую настройку.
 if( !session_cp.empty() )
  {
   int icp = CodeConverter::CP_Name_2_Index( session_cp.c_str() );

   get_UI().SetSessionCp(
                         boost::shared_ptr<CodeConverter>(
                                                          const_cast<CodeConverter*>(CodeConverter::getConverter(icp)), 
                                                          null_deleter()
                                                         )
                        );
  }


 if( !tty_cp.empty() )
  {
   int icp = CodeConverter::CP_Name_2_Index( tty_cp.c_str() );
   get_UI().SetTtyCp(
                     boost::shared_ptr<CodeConverter>(
                                                      const_cast<CodeConverter*>(CodeConverter::getConverter(icp)),
                                                      null_deleter()
                                                     )
                    );
  }

 return;
}
