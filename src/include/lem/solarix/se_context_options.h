// -----------------------------------------------------------------------------
// File SE_CONTEXT_OPTIONS.H
//
// (c) by Elijah Koziev
//
// Content:
// SOLARIX Intellectronix Project
// 'faind' SEARCH ENGINE Core
//
// -----------------------------------------------------------------------------
//
// CD->16.10.2006
// LC->16.10.2006
// --------------

#ifndef CONTEXT_OPTIONS__H
#define CONTEXT_OPTIONS__H
#pragma once

 namespace Solarix
 {
  namespace Search_Engine
  {

   // ******************************************
   // Flags for fix context construction.
   // Опции формирования контекста фиксации. 
   // ******************************************
   struct Context_Options
   {
    int fixed_only; // context contains only hit points. No additional 
                    // lexems (margins) are stored.

    int lexems_margin; // number of lexems before beginning
                       // of the hit point and after the ending.

    int max_len; // Maximum number of context lexems to show
    bool lowered; // Печатать контекст в нижнем регистре
    int maxhitcount; // ограничение на число находимых контекстов (0 - все)

    Context_Options(void)
    { Clear(); }

    inline void Clear(void)
    {
     fixed_only = false;
     lexems_margin = 8;
     max_len = 1000;
     lowered = true;
     maxhitcount = lem::int_max;
    }
   };

  } // namespace Search_Engine
 } // namespace Solarix

#endif
