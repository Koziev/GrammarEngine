#ifndef SE_JOURNAL_OPTIONS__H
#define SE_JOURNAL_OPTIONS__H
#pragma once

 #define SE_DETAILED_JOURNAL

 #if defined SE_DETAILED_JOURNAL
  #define DETAILED_LOG if( lem::LogFile::IsOpen() ) \
                         lem::LogFile::logfile->printf( "Detailed log, file=%s line=%d\n", __FILE__, __LINE__ );
 #else
  #define DETAILED_LOG
 #endif

#endif
