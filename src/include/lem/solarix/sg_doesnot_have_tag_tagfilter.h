#ifndef SG_TF_DOESNOT_HAVE_TAG__H
#define SG_TF_DOESNOT_HAVE_TAG__H
#pragma once

 #include <lem/solarix/SG_TagFilter.h>

 namespace Solarix
 {
  class TF_DoesNotHaveTag : public SG_TagFilter
  {
   private:
    int itag;

   public:
    TF_DoesNotHaveTag( const Dictionary &dict, const UCString &tag_name );

    virtual bool Match( SG_TagsList x ) const;

    virtual bool Empty(void) const;
  };

 } // namespace Solarix

#endif
