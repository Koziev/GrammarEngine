#ifndef FAIND_MEDIA_INFO_MANAGER__H
#define FAIND_MEDIA_INFO_MANAGER__H
#pragma once

 #include <lem/process.h>
 #include <lem/ptr_container.h>
 #include <lem/solarix/se_plugin_options.h>
 #include <lem/solarix/igrammar_engine.h>
 #include <lem/solarix/isearch_engine.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
   #if defined FAIND_PLUGINS
   class MediaInfoPlugin
   {
    private:
     lem::Process::Dll dll;

     void *hEngine;

     typedef void*(*Constructor_fun)(void);
     typedef void(*Destructor_fun)( void* This );
     typedef bool(*GetMediaInfoTags_fun)( void* This,
                                         const wchar_t *path_url,
                                         const Solarix::Search_Engine::PluginOptions *Options,
                                         IGrammarEngine *IGrammarEnginePtr, 
                                         ISearchEngine *ISearchEnginePtr,
                                         wchar_t **ShortDescription,
                                         wchar_t **LongDescription,
                                         wchar_t **Tags,
                                         wchar_t **ImageFilename
                                        ); 


     typedef void(*Free_fun)( void* This, wchar_t *Ptr );
     typedef const wchar_t* (*GetSolarixPluginProperty_fun)( void *This, int iProp, int iSub );

     Constructor_fun Constructor;
     Destructor_fun Destructor;
     GetMediaInfoTags_fun GetMediaInfoTags;
     Free_fun Free;
     GetSolarixPluginProperty_fun GetSolarixPluginProperty; 

    public:
     MediaInfoPlugin(void);
     ~MediaInfoPlugin(void);
     
     bool Load( const lem::Path &filename );
     lem::UFString GetDescription(void);

     const lem::Path& GetPath(void) const;

     bool GetMediaInfo(
                       const lem::Path &path,
                       lem::UFString &short_info,
                       lem::UFString &long_info,
                       lem::UFString &tags,
                       lem::UFString &image_filename,
                       const Solarix::Search_Engine::PluginOptions *Options,
                       IGrammarEngine *IGrammarEnginePtr, 
                       ISearchEngine *ISearchEnginePtr
                      );
   }; 
   #endif


   class MediaInfoManager
   {
    private:
     #if defined FAIND_PLUGINS
     lem::PtrCollect<MediaInfoPlugin> plugins;
     #endif

     lem::zbool loaded;
   
    public:
     MediaInfoManager(void);
     
     virtual bool IsLoaded(void) const;

     //! Загрузка плагинов из DLL
     virtual void Load( const lem::Path &plugins );

     //! Когда загружать плагины запрещено, просто устанавливаем флаг "загружено"
     virtual void InitializeWithoutLoading(void);

     virtual void ListAllPlugins( lem::Collect< std::pair<lem::UFString,lem::Path> > &list );
   
     virtual bool GetMediaInfo(
                               const lem::Path &path,
                               lem::UFString &short_info,
                               lem::UFString &long_info,
                               lem::UFString &tags,
                               lem::UFString &image_filename,
                               const Solarix::Search_Engine::PluginOptions *Options,
                               IGrammarEngine *IGrammarEnginePtr, 
                               ISearchEngine *ISearchEnginePtr
                              );
   
   };
  } // Search_Engine
 } // Solarix

#endif
