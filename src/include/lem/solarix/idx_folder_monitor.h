// CD->05.07.2006
// LC->26.05.2008
// --------------

#pragma once

#if defined FAIND_FILEMON

#ifndef IDX_FOLDER_MONITOR__H
 #define IDX_FOLDER_MONITOR__H

 #if defined LEM_WINDOWS

 #include <vector>
 #if defined LEM_MFC
  #include <afxwin.h>
 #else 
  #include <windows.h>
 #endif

namespace Solarix
{
 namespace Search_Engine
 {
  typedef void( *Change_Event_Func)(void);

  class IndexManager;

  class Folder_Monitor
  {
   public: 
    struct Monitor_Env  
    {
     lem::UFString path; // контролируемый каталог
     std::set<lem::UFString> ext_filter; // фильтр расширений файлов (если был задан для зоны)
     int id; // id зоны

     HANDLE hEvent;

     HANDLE hDir;
     HANDLE hThread;
     FILE_NOTIFY_INFORMATION *buf;
     int buf_size; 
     OVERLAPPED ovl;

     Monitor_Env(void);
     ~Monitor_Env(void);
    };

    static Folder_Monitor *self;
    static HANDLE hEvent;
    static HANDLE hEventThread; // тред ожидания срабатывания по ивенту hEvent.

    static HANDLE hEventKill; // Событие для выхода из состояния ожидания всех тредов при
                              // остановке монитора.

    static volatile bool Stopping; // Флаг для состояния остановки монитора

    static HANDLE Events[2]; // вспомогательный вектор для WaitForMultipleObjects

    static CRITICAL_SECTION mon_cs;
    static /*volatile*/ long nThread; // сколько мониторов осталось

    IndexManager *index_manager;

    std::vector< lem::triple<UFString,HANDLE/*thread*/,Monitor_Env*> > managed; // каталоги под контролем

//    std::vector< std::pair<int /*id_zone*/, const wchar_t *path> > changed_folders; // список изменившихся каталогов и индексов

   private:
    static unsigned int WINAPI Monitor_Thread( Monitor_Env *Env );
    static void WINAPI T_Wait_Event( Change_Event_Func func );
 
   protected:
    virtual void RefreshZone( Monitor_Env *Env, lem::Collect< lem::Path* >& changed_files );

   public:
    Folder_Monitor(void);

    ~Folder_Monitor(void);

    void StartAllHdds( int id_zone, const std::set<lem::UFString> &ext_filter );
    void Start( const wchar_t *folder, const std::set<lem::UFString> &ext_filter, int id_zone );
    void StopAll(void);

    void WaitEvent( Change_Event_Func func );

    int CountManagedFolders(void) const;
    
    static void EnterCS(void);
    static void LeaveCS(void); 
  };

 } // namespace Search_Engine
} // namespace Solarix

  #endif

 #endif
#endif
