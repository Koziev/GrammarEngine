#ifndef LEM_SHORTCUT__H
#define LEM_SHORTCUT__H
#pragma once

 #include <lem/config.h>

 #if defined LEM_WINDOWS 

  #if defined LEM_MFC
   #include <afxwin.h>
  #else 
   #include <windows.h>
  #endif

  #include <shlwapi.h>
  #include <shobjidl.h>
  #include <lem/path.h>

  namespace lem 
  {
   class Shortcut
   {
    protected:
     IShellLink*     m_pShellLink;    
     IPersistFile*   m_pPersistFile;
     WIN32_FIND_DATA FindData;
     lem::Path filepath;

    public:
     Shortcut(void);
     virtual ~Shortcut(void);

     // Resolves shortcut specified by ANSI path
     bool ResolveShortcut( const char *pFileName );

     // Resolves shortcut specified by Unicode path
     bool ResolveShortcut( const wchar_t *pUnicodeFileName );

     bool ResolveShortcut( const lem::Path &filename );

     // Returns path of a target file
     const lem::Path& GetFilePath(void) const { return filepath; }

     // Returns PIDL for a target file
     LPITEMIDLIST GetIDList(void);

     // Creates link for specified file
     bool CreateLink( const lem::Path& PathObj, const lem::Path& PathLink, const TCHAR *lpszDesc=NULL );

   };

  }

 #endif

#endif
