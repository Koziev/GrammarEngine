#ifndef SG_TF_EXPLICIT_FILTER__H
#define SG_TF_EXPLICIT_FILTER__H
#pragma once

 #include <lem/solarix/SG_TagFilter.h>

 namespace Solarix
 {
  class Dictionary;

  class TF_ExplicitFilter : public SG_TagFilter
  {
   private:
    int itag, ivalue;

   public:
    TF_ExplicitFilter( const Dictionary &dict, const lem::UCString &tag_name, const lem::UCString &tag_value );

    virtual bool Match( SG_TagsList x ) const;

    virtual bool Empty(void) const;
  };

 } // namespace Solarix

#endif
