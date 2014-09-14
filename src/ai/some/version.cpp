// This file contains SOLARIX Intellectronix VERSION INFO

#include <string>
#include <cstdio>

#include <lem/system_config.h>
#include <lem/user_interface.h>
#include <lem/solarix/version.h>
#include <lem/solarix/project_version.h>

using namespace std;
using namespace Solarix;

Version_Info::Version_Info(void)
{
 major=PROJVER_MAJOR;
 minor=PROJVER_MINOR;
 build=PROJVER_BUILD;
}


// ****************************************************************
// Процедура возвращает строку с сигнатурой версии кода Соляриса.
//
// This routine returns the string containing Solarix Intl.
// version signature.
// ****************************************************************
const std::string sol_get_version( bool include_build_date, bool include_platform )
{
 Version_Info vi;

 char b[256];

 std::string platform;

 if( include_platform )
  {
   platform = lem::System_Config::GetHostOs(false);
   platform += " ";
  } 

 const char pro[]=
 #if defined SOL_TRIAL
 "Trial"
 #elif defined SOLARIX_PREMIUM
 "" //"Professional"
 #elif defined SOLARIX_PRO
 "Standard";
 #else
 "Lite";
 #endif
 ;

 if( include_build_date )
  sprintf(
          b,
          "%d.%02d.%d %s %s (build date %s)",
          vi.major, vi.minor, vi.build, pro, platform.c_str(), __DATE__
         );
 else
  sprintf(
          b,
          "%d.%02d.%d %s %s"
          , vi.major, vi.minor, vi.build, pro, platform.c_str()
         );

 return std::string(b);
}


const std::string sol_get_release_info(void)
{
 return std::string( "SOLARIX Intellectronix Project  http://www.solarix.ru" );  
}


void Solarix::Print_Project_Info( lem::OFormatter &to )
{
 const bool ru = lem::UI::get_UI().IsRussian();

 if( ru )
  to.printf(
            "%vfASOLARIX Intellectronix%vn project %vfEhttp://www.solarix.ru%vn\n" 
           );
 else
  to.printf(
            "%vfASOLARIX Intellectronix%vn project %vfEhttp://www.solarix.ru/index-en.shtml%vn\n" 
           );
}
