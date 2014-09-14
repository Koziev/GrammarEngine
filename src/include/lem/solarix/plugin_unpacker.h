// -----------------------------------------------------------------------------
// File PLUGIN_ARCHIVE.H
//
// (c) 2006 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ supplementary library
//
// -----------------------------------------------------------------------------
//
// CD->24.09.2006
// LC->16.08.2007
// --------------

#ifndef PLUGIN_ARCHIVE__H
#define PLUGIN_ARCHIVE__H
#pragma once

 #include <lem/solarix/base_archive.h>
 #include <lem/solarix/search_engine.h>

 namespace lem
 {
  namespace Pack
  {
   class Base_Archive;
  }
 }

 namespace Solarix
 {
  namespace Search_Engine
  {
   class Plugin_Archive : public lem::Pack::Base_Archive
   {
    private:
     Unpacker_Plugin *plugin;
     void *context;
     lem::Path tmp_src;

     void File_Extracted( const lem::Path &filename );
     void CloseContext(void);

    public:
     Plugin_Archive( Unpacker_Plugin *Plugin );

     virtual ~Plugin_Archive(void);
 
     virtual bool Open( boost::shared_ptr<Stream> Stream, const PluginOptions *Options );
     virtual void Extract_Files( lem::Pack::Base_File_Processor &x );
     virtual const lem::Path Extract_File( const lem::UFString &filename, lem::Pack::Base_File_Processor &x );
   };

    class IPluginUnpacker : public lem::Pack::IUnpackerFactory
    {
     public:
      IPluginUnpacker(void) {}

      virtual lem::Pack::Base_Archive* New( void *ptr=NULL ) const;
      virtual bool CanExtractSingleFile(void) const { return true; }
    };


  } // namespace Pack
 } // namespace lem

#endif
