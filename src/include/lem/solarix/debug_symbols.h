#ifndef SOL_DEBUG_SYMBOLS__H
#define SOL_DEBUG_SYMBOLS__H
#pragma once

 #include <lem/path.h>
 #include <lem/ptr_container.h>

 namespace lem
 {
  namespace Iridium
  {
   class BSourceState;
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class LexiconStorage;

  class SourceFilenameEnumerator;

  class DebugSymbols
  {
   private:
    Solarix::LexiconStorage *storage;
 
   public:
    DebugSymbols(void);
    ~DebugSymbols(void);

    void SetStorage( Solarix::LexiconStorage * _storage );

    #if defined SOL_COMPILER && defined SOL_LOADTXT
    int RegisterLocation( const lem::Iridium::Macro_Parser &txt, const lem::Iridium::BSourceState &pos );
    #endif
  
    lem::Path GetFileName( int id_filename );
    bool GetLocation( int iloc, lem::Path &filename, int &line, int &column );
    bool GetLocation( int iloc, int &id_file, int &line, int &column );
    int Find( int ifile, int line, bool prox=false );
    SourceFilenameEnumerator *ListFiles(void);
  };


 } // namespace Solarix


#endif
