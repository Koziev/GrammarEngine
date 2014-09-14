#ifndef SE_SQLITE_TOOLS__H
#define SE_SQLITE_TOOLS__H
#pragma once

 #include <lem/ufstring.h>
 #include <lem/afstring.h>

 namespace Solarix
 {
  namespace Search_Engine
  { 
   extern void encode_sqlite_path( lem::UFString &s );
   extern void decode_sqlite_path( lem::UFString &s );
   extern lem::FString escape_sqlite_quotes( const lem::FString &s );

  }
 }

#endif
