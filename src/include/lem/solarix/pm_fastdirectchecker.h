#ifndef PM_FASTDIRECTCHECKER__H
#define PM_FASTDIRECTCHECKER__H
#pragma once

 namespace Solarix
 {
  struct PM_FastDirectChecker
  {
   int index;
   bool check_entry;
   int entry_key;
   bool check_class;
   int iclass;
   Solarix::Lexem wlexem;
   bool check_lexem;

   PM_FastDirectChecker(void)
    : index(UNKNOWN), check_entry(false), entry_key(UNKNOWN), check_class(false), iclass(UNKNOWN), check_lexem(false) {}
  };
 } 

#endif
