#include <lem/config.h>

#if defined LEM_WINDOWS

#include <windows.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <exdisp.h>
#include <lem/shell.h>

// ************************************************************
// Возвращает текущий выбранный каталог в активном Проводнике.
// ************************************************************
lem::Path lem::Shell::GetCurrentFolder(void)
{
 #if (defined LEM_MSC && _MSC_VER<1300) || defined LEM_WIN98

 lem::Path res;
 return res;

 #else

 TCHAR g_szPath[MAX_PATH];
 TCHAR g_szItem[MAX_PATH];

 HWND hwndFind = GetForegroundWindow();

 #if LEM_DEBUGGING==1
  TCHAR wndTitle[261];
  GetWindowText( hwndFind, wndTitle, sizeof(wndTitle) );
 #endif


 g_szPath[0] = TEXT('\0');
 g_szItem[0] = TEXT('\0');

 IShellWindows *psw=NULL;
 if( SUCCEEDED(CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_ALL, IID_IShellWindows, (void**)&psw)))
  {
   VARIANT v;
   V_VT(&v) = VT_I4;
   IDispatch *pdisp=NULL;
   BOOL fFound = FALSE;

   for( V_I4(&v) = 0; !fFound && psw->Item(v, &pdisp) == S_OK; V_I4(&v)++ )
    {
     IWebBrowserApp *pwba=NULL;
     HRESULT rc = pdisp->QueryInterface(IID_IWebBrowserApp, (void**)&pwba);

     if( SUCCEEDED(rc) )
      {
       HWND hwndWBA=NULL;
       rc = pwba->get_HWND((LONG_PTR*)&hwndWBA);

       if( SUCCEEDED(rc) && hwndWBA == hwndFind )
        {
         fFound = TRUE;
         IServiceProvider *psp=NULL;
         if( SUCCEEDED(pwba->QueryInterface(IID_IServiceProvider, (void**)&psp)) )
          {
           IShellBrowser *psb=NULL;
           if( SUCCEEDED(psp->QueryService(SID_STopLevelBrowser, IID_IShellBrowser, (void**)&psb)))
            {
             IShellView *psv=NULL;
             if( SUCCEEDED(psb->QueryActiveShellView(&psv)) )
              {
             IFolderView *pfv=NULL;
             if (SUCCEEDED(psv->QueryInterface(IID_IFolderView,
                                               (void**)&pfv))) {
               IPersistFolder2 *ppf2=NULL;
               if (SUCCEEDED(pfv->GetFolder(IID_IPersistFolder2,
                                            (void**)&ppf2))) {
                 LPITEMIDLIST pidlFolder=NULL;
                 if (SUCCEEDED(ppf2->GetCurFolder(&pidlFolder))) {
                   if (!SHGetPathFromIDList(pidlFolder, g_szPath))
                    {
                     //lstrcpyn(g_szPath, TEXT("<not a directory>"), MAX_PATH);
                    }
                   int iFocus=0;
                   if (SUCCEEDED(pfv->GetFocusedItem(&iFocus))) {
                     LPITEMIDLIST pidlItem=NULL;
                     if (SUCCEEDED(pfv->Item(iFocus, &pidlItem))) {
                       IShellFolder *psf=NULL;
                       if (SUCCEEDED(ppf2->QueryInterface(IID_IShellFolder,
                                                          (void**)&psf))) {
                         STRRET str;
                         if (SUCCEEDED(psf->GetDisplayNameOf(pidlItem,
                                                   SHGDN_INFOLDER,
                                                   &str))) {
                           StrRetToBuf(&str, pidlItem, g_szItem, MAX_PATH);
                         }
                         psf->Release();
                       }
                       CoTaskMemFree(pidlItem);
                     }
                   }
                   CoTaskMemFree(pidlFolder);
                 }
                 ppf2->Release();
               }
               pfv->Release();
             }
             psv->Release();
           }
           psb->Release();
         }
         psp->Release();
       }
     }
     pwba->Release();
   }
    pdisp->Release();
  }
  psw->Release();
 }

 lem::Path res(g_szPath);
 return res;
 #endif
}

#else

lem::Path lem::Shell::GetCurrentFolder(void)
{
 char b[ lem::Path::MaxLen+1 ];
 memset( b, 0, sizeof(b) );
 if( getcwd(b,lem::Path::MaxLen)!=NULL )
  return lem::Path(b);

 return lem::Path();
}

#endif
