// CD->22.01.2007
// LC->07.03.2010
// --------------

#ifndef SOLARIX_OCR_ENGINE__H
#define SOLARIX_OCR_ENGINE__H
#pragma once

 #if defined SOLARIX_PREMIUM

 #include <lem/noncopyable.h>
 #include <lem/process.h>
 #include <lem/render/gdi.h>
 #include <lem/render/2d.h>

 namespace Solarix
 { 
  namespace Ocr
  { 
   class OCREngine : lem::NonCopyable
   {
    private:
     lem::Process::Dll dll;
     void *hEngine;

     typedef void*(*Constructor_fun)(void);
     typedef void(*Destructor_fun)( void* This );
     typedef int(*RecognizeFile_fun)( void* This, void *IGrammarEnginePtr, const wchar_t *Filename, wchar_t **Buffer );

     #if defined LEM_WINDOWS
     typedef int(*RecognizeDIB_fun)( void* This, void *IGrammarEnginePtr, HBITMAP hDib, wchar_t **Buffer );
     #endif

     typedef void(*Free_fun)( void* This, wchar_t *Ptr );
     typedef const wchar_t* (*GetSolarixPluginProperty_fun)( void *This, int iProp, int iSub );

     Constructor_fun Constructor;
     Destructor_fun Destructor;
     RecognizeFile_fun RecognizeFile_ptr;
     #if defined LEM_WINDOWS
     RecognizeDIB_fun RecognizeDIB_ptr;
     #endif
     Free_fun Free;
     GetSolarixPluginProperty_fun GetSolarixPluginProperty; 

    public:
     OCREngine(void);
     virtual ~OCREngine(void);

     virtual bool Load( const lem::Path &dllpath );
  
     virtual void RecognizeFile( const lem::Path &filename, lem::UFString &result, void *IGrammarEnginePtr );
     lem::UFString GetDescription(void);
     const lem::Path& GetPath(void) const;

     #if defined LEM_WINDOWS
     virtual void RecognizeDIB( HBITMAP hDib, lem::UFString &result, void *IGrammarEnginePtr );
     #endif
   };
  
  } // namespace Ocr
 } // namespace Solarix

 #endif

#endif
