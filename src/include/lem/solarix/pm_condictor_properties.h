#ifndef PM_CONDICTOR_PROPERTIES__H
#define PM_CONDICTOR_PROPERTIES__H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/zeroed.h>

 namespace Solarix
 {

  struct CondictorProperties : lem::NonCopyable
  {
   lem::zbool any_at_beginning,
              any_at_ending,
              all_at_beginning,
              all_at_ending,
              has_context;
   lem::MSet<int> obligatory_entries;

   lem::MSet<int> iclasses;
   lem::zbool iclasses_valid;

   CondictorProperties(void):all_at_beginning(true), all_at_ending(true), iclasses_valid(true) {}
  };

 }

#endif
