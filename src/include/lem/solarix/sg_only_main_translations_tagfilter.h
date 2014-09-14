#ifndef SG_TF_ONLY_MAIN_TRANSLATIONS__H
#define SG_TF_ONLY_MAIN_TRANSLATIONS__H
#pragma once

 #include <lem/solarix/SG_TagFilter.h>

 namespace Solarix
 {
  class Dictionary;
  class TF_TranslOrderZero : public SG_TagFilter
  {
   private:
    int transl_order_itag;

   public:
    TF_TranslOrderZero( const Dictionary &dict );

    virtual bool Match( SG_TagsList x ) const;

    virtual bool Empty(void) const;
  };

  class TF_OnlyMainTransl : public SG_TagFilter
  {
   private:
    int transl_order_itag;

   public:
    TF_OnlyMainTransl( const Dictionary &dict );

    virtual bool Match( SG_TagsList x ) const;

    virtual bool Empty(void) const;
  };

 } // namespace Solarix

#endif
