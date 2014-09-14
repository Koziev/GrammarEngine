#ifndef SOL_DICTIONARY_CONFIG_OPTIONS__H
#define SOL_DICTIONARY_CONFIG_OPTIONS__H
#pragma once

 namespace Solarix
 {

  struct Dictionary_Config
  {
   int ldsize; // размер справочника лексем
   lem::zint internal_offset;

   Dictionary_Config(void)
   {
    #if defined SOL_OFFSET
     #if SOL_OFFSET==AUTO
     internal_offset = UNKNOWN;
     #else
     internal_offset = SOL_OFFSET;
     #endif
    #endif
    ldsize = 1000000;
   }
  };

 } // namespace Solarix

#endif
