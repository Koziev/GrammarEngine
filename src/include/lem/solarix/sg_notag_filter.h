#ifndef SG_TF_NOTAG_FILTER__H
#define SG_TF_NOTAG_FILTER__H
#pragma once

 #include <lem/solarix/SG_TagFilter.h>

 namespace Solarix
 {
  class Dictionary;

  class NoTagFilter : public SG_TagFilter
  {
   public:
    NoTagFilter(void);

    virtual bool Match( SG_TagsList x ) const;
    virtual bool Empty(void) const;
  };

 } // namespace Solarix

#endif
