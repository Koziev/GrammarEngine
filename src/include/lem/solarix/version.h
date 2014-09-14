#ifndef SOL_VERSION__H
#define SOL_VERSION__H
#pragma once

 #include <lem/config.h>
 #include <string>
 #include <lem/oformatter.h>

// Current version signature
extern const std::string sol_get_version(
                                         bool include_build_date=true,
                                         bool include_platform=true
                                        );

// Compiled release brief info
extern const std::string sol_get_release_info(void);

namespace Solarix
{
 // Вывод аккуратно форматированного описания проекта - с информацией 
 // о сайтах и так далее.
 extern void Print_Project_Info( lem::OFormatter &to );

 #undef minor
 #undef major
 #undef build
 struct Version_Info
 {
  int major; // 0.
  int minor; //   70.
  int build; //      35

  Version_Info(void);

  Version_Info( int Mj, int Mi, int Bui )
   : major(Mj), minor(Mi), build(Bui) {}

  inline bool operator==( const Version_Info &x ) const
  { return major==x.major && minor==x.minor && build==x.build; }
 };

}

#endif
