#if !defined ENGINE_TAG_SEARCH__H && defined SOLARIX_PRO && defined FAIND_PLUGINS
#define ENGINE_TAG_SEARCH__H
#pragma once

 #include <lem/solarix/search_engine.h>

 namespace Solarix
 {
  namespace Search_Engine
  { 

   class Engine_TagSearch : public Engine_Plugin
   {
    private:
     #if defined SOLARIX_PRO
     DocumentTagsCache* document_tags_cache;
     #endif

    public:
     Engine_TagSearch( Crawler *master_crawler );
   
     virtual const wchar_t* GetDescription(void) const;

     virtual bool Load( const lem::Path &filename );

     virtual void Search( const Query_Root *q, const UFString &params, Crawler *engine );

     virtual bool RewriteQuery( UFString &pattern, Scan_Options &scanning, Search_Options &flags, Crawler *engine );

     virtual bool SimpleSearch( const Query_Root *q, UFString &result, UFString &format, Crawler *engine );
   };

  }

 }

#endif

