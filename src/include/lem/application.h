#ifndef LEM_APPLICATION__H
#define LEM_APPLICATION__H
#pragma once

 #include <lem/config.h>

 namespace lem
 {
  namespace Application
  {
   // Process all GUI events in the app main queue
   extern void DoEvents(void);

   // Return the application handle if possible
   extern void* GetHandle(void);
  }
 }

#endif
