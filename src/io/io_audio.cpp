// -----------------------------------------------------------------------------
// File IO_AUDIO.CPP
//
// Copyright:    Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2000
//
//
// Content:
// Поток обмена данными с виртуальным звуковым устройством.
// ***
// Звуковой драйвер для MS Windows 3.1. Данный код является лишь примитивным
// примером использования MultyMedia-интерфейса среды MS Windows, но вполне
// работоспособен. Я ожидаю, что он будет успешно транслироваться любым
// компилятором C++ для MS Windows.
// -----------------------------------------------------------------------------
//
// CD->27.06.98
// LC->12.02.03
// ------------

#include <lem/config.h>

#if defined SOL_CAA

#include <lem_marr.h>
#include <lem/streams.h>
#include <lem_task.h>
#include <lem/path.h>
#include <cp_table.h>

#include "au_main.h"
#include "krn_main.h"
#include "sol_sys.h"
#include "krn_envi.h"

#if defined SOL_WINDOWS && defined SOL_GUI
 #include <mmsystem.h>
#endif

#if defined SOL_WINDOWS && defined SOL_GUI
LRESULT CALLBACK _export SolWndProc(
                                    HWND hWnd,
                                    UINT iMessage,
                                    WPARAM wParam,
                                    LPARAM lParam
                                   );
#endif

Lem_SND_Stream::Lem_SND_Stream(void):Fragment(0,32),Size(0,32)
{
 #if defined SOL_WINDOWS && defined SOL_GUI
 lem_check_ptr( wnd = new SolSoundWindow );

 // A Windows class should be registered with Windows before any windows
 // of that type are created.
 // Register here all Windows classes that will be used in the program.
 // Windows classes should not be registered if an instance of
 // the program is already running.
 if( sol_active_id->htask.hPrev==NULL )
  wnd->Register();

 wnd->Build();

 #endif
 return;
}

Lem_SND_Stream::~Lem_SND_Stream(void)
{
 ForgetFragments();

 #if defined SOL_WINDOWS && defined SOL_GUI
 lem_rub_off(wnd);
 #endif

 return;
}

/**************************************************************************
 Необходимо воспроизвести блок ptr размером size. В действительности
 мы не будем делать это прямо сейчас, а поместим фрагмент в буфер, и
 только flush заставит нас проиграть записи.

 Формат блока, на который указывает ptr:

  тип_поля       длина_поля       пояснения

  SolString   sizeof(SolString)   Имя файла звукового образа.

  INT32              4            Длина в байтах файла звукообраза.

  UINT8                           Вектора байтов - бинарный образ файла.
**************************************************************************/
void Lem_SND_Stream::write( const void *ptr, const size_t size )
{
 UINT8 *Ptr = (UINT8*)lem_malloc(size);
 lem_check_ptr_z(Ptr);
 lem_memcpy( Ptr, ptr, size );
 Fragment.Add(Ptr);
 Size.Add(size);
 return;
}

/******************************************************************
 Использовать метод для ДАННОГО потока нельзя! Работает только
 метод ::write(...).
*******************************************************************/
void Lem_SND_Stream::put( const int /*ch*/ )
{
 LEM_STOPIT;
}

/*******************************************************************
 Забываем о блоках, которые были предназначены для воспроизведения.
********************************************************************/
void Lem_SND_Stream::ForgetFragments(void)
{
 LEM_DELETE_CONTAINER( Fragment );
 Size.Delete();
 return;
}

/*************************************************************************
 Воспроизводим накопленные в буфере звукозаписи.

 Кратко об алгоритме. Прежде всего, мы проверяем, являются ли фрагменты
 корректными WAV-блоками. Напоминаю, что Система SOLARIS хранит
 звукообразы словоформ, слогов и так далее просто как байтовое содержимое
 файлов произвольного формата. Синтезированный звукообраз - это куски
 памяти, содержащие байты из тех файлов плюс некоторую дополнительную
 информацию (имя исходного файла и его размер). Итак, если хоть один блок
 имеет не-WAV формат, посылаем фрагменты на воспроизведение по отдельности.
 Результат будет очень низкого качества (с разрывами). Но если все
 фрагменты распознаны как WAV-блоки, то мы можем сшить их в единый
 звукообраз и послать его на воспроизведение. Качество гарантируется.
 Тонкость: если WAV-фрагменты имеют разные параметры дискретизации,
 например частоту, то выполняется переоцифровка всех фрагментов под
 некий стандарт (22КГц,8 бит/квант,моно) и результаты опять-таки
 сливаются. Переоцифровка ведёт к появлению нелинейных искажений (шум в
 области высоких частот), но тут уж ничего не попишешь!
***************************************************************************/
void Lem_SND_Stream::flush(void)
{
 // -----------------------------------------------------
 // Во-первый, загрузим в отдельные структуры WAV-блоки.
 const int n_fragment = Fragment.Items();

 LemMCollect_D<Lem_WAV_Block*> sound_list(0,n_fragment);

 // Имена файлов, из которых компилятор Солярис взял звуки,
 // нам тоже пригодятся!
 LemMCollect<LemString> file_name_list(0,n_fragment);

 for( int is=0; is<n_fragment; is++ )
  {
   UINT8 *ptr = Fragment[is];

   LemString org_file_name;
   lem_memcpy( &org_file_name, ptr, sizeof(org_file_name) );
   ptr += sizeof(LemString);
   file_name_list.Add(org_file_name);

   INT32 org_file_size;
   lem_memcpy( &org_file_size, ptr, sizeof(org_file_size) );
   ptr += sizeof(org_file_size);

   LemMemoryFile sound_file( &ptr, true, false, (size_t)org_file_size );

   // Загружаем заголовок звукового файла...
   Lem_WAV_Block *sb = new Lem_WAV_Block;
   lem_check_ptr_z(sb);
   sound_list.Add(sb);

   if( sb->LoadBin((BaseStream&)sound_file)==false )
    {
     // Звукозаписи в каком-то другом формате. Не будет пытаться разобраться
     // более, а просто поручим внешнему драйверу воспроизвести...

     for( int i=1; i<sound_list.Items(); i++ )
      delete sound_list[i];

     DoVoiceThemDirectly();
     ForgetFragments();
     return;
    }
  }

 ForgetFragments();

 // Все звукозаписи должны иметь одинаковые параметры (частоту и так далее).
 // Проверяем это.
 bool do_them_match=true;
 int i;
 for( i=1; i<sound_list.Items(); i++ )
  do_them_match = do_them_match &&
                  sound_list[0]->CanBeConcatinated( sound_list[i] );

 // Если есть несовместимость, то выполним ПЕРЕОЦИФРОВКУ всех фрагментов
 // по единому стандарту (частота 22КГц, моно, 8 бит/квант).
 if( !do_them_match )
  for( i=sound_list.Items()-1; i>=0; i-- )
   sound_list[i]->ReQuantize( LEM_WAV_8_KHz, LEM_WAV_MONO, 8 );

 // Теперь можем проводить конкатенацию звуковых блоков в единый фрагмент,
 // что повысит качество результата - в нем не будет явных разрывов.
 for( i=1; i<sound_list.Items(); i++ )
  {
   sound_list[0]->Concatinate( sound_list[i] );
   delete sound_list[i];
  }

 // Немного убыстряем темп звука (так интереснее).
 lem_wav_scale( sound_list[0], 0.8 );

 // Осталось записать объединённый звуковой блок sound_list[0] на диск, и можем
 // вызывать внешний аудиодрайвер. Тут есть хитрость: чтобы драйвер MS Windows
 // смог корректно распознать тип файла, для него нужно восстановить расширение
 // исходного файла. Это неприятно, но делать придётся.

 LemFString drive,path,name,ext,ext1;
 lem_file_name_split( file_name_list[0], drive, path, name, ext );

 // Исходное расширение используем как маску при построении имени временного...
 snd_tmp_fname = lem_get_tmp_name(ext.string());

 // Теперь сбросим звук в указанный бинарный временный файл.
 LemBinaryFile *sound_file = new LemBinaryFile(
                                               snd_tmp_fname,
                                               false,
                                               true
                                              );
 lem_check_ptr_z(sound_file);
 sound_list[0]->SaveBin(*sound_file);
 delete sound_file;
 delete sound_list[0];

 // Запускаем вокализатор.
 DoVocalize(snd_tmp_fname);

 return;
}

/************************************************************************
 Внутренная процедура - воспроизведение фрагментов неизвестного формата.
*************************************************************************/
void Lem_SND_Stream::DoVoiceThemDirectly(void)
{
 for( int is=0; is<Fragment.Items(); is++ )
  {
   UINT8 *ptr = Fragment[is];

   SolString org_file_name;
   lem_memcpy( &org_file_name, ptr, sizeof(SolString) );
   ptr += sizeof(SolString);

   INT32 org_file_size;
   lem_memcpy( &org_file_size, ptr, sizeof(org_file_size) );
   ptr += sizeof(org_file_size);

   snd_tmp_fname = lem_get_tmp_name();
   LemBinaryFile rec( snd_tmp_fname, false, true );
   rec.write( ptr, Size[is]-sizeof(org_file_name)-sizeof(org_file_size) );
   DoVocalize(snd_tmp_fname);
  }

 return;
}

#if defined LEM_DOS
//REGISTER_STATIC_STRING(SOL_VOCALIZE_COMMAND,"dos_play.exe ");
#elif defined LEM_WINDOWS && defined LEM_TUI_PLAIN
//REGISTER_STATIC_STRING(SOL_VOCALIZE_COMMAND,"dos_play.exe ");
#elif defined LEM_WINDOWS && defined LEM_GUI
// ... nothing ...
#elif defined LEM_LINUX
// ....    cat file | /dev/audio
#else
#error
#endif

void Lem_SND_Stream::DoVocalize( const char *filename )
{
// LEM_CHECKIT_Z(CanBeVocalized());

 #if defined LEM_WINDOWS && defined LEM_GUI

// wnd->DoPlay(filename);

 #elif defined LEM_DOS

// const LemFString x=LemFString(SOL_VOCALIZE_COMMAND)+LemFString(filename);
// lem_system( x.string() );

 #elif defined LEM_WINDOWS && defined LEM_TUI_PLAIN

// const LemFString x=LemFString(SOL_VOCALIZE_COMMAND)+LemFString(filename);
// lem_system( x.string() );

 #elif  defined LEM_LINUX

 // ...
 LEM_STOPIT;

 #else

  #error Lem_SND_Stream::DoVocalize undefined
 #endif

 return;
}

/********************************************************************
 Возвращает true, если звуковой канал (вокализации), через который
 пропускаются все звуковые сообщения, освободился и новое сообщение
 может быть выдано.
*********************************************************************/
const bool Lem_SND_Stream::CanBeVocalized(void) const
{
 #if defined LEM_DOS
  return true;
 #elif defined LEM_WINDOWS && defined LEM_TUI_PLAIN
  LEM_STOPIT;
  return false;
 #elif defined LEM_WINDOWS && defined LEM_GUI
//  return wnd->IsFree();
 #elif defined LEM_LINUX
  return true;
 #else
  #error Lem_SND_Stream::CanBeVocalized is not defined.
 #endif
}

/*********************************************************************
 Начинаем воспроизведение подготовленного звука и возвращаем имя
 временного файла на диске, где мы храним бинарный образ этого звука.
**********************************************************************/
const LemFString Lem_SND_Stream::Play(void)
{
 flush();
 return snd_tmp_fname;
}

#if defined LEM_WINDOWS && defined LEM_GUI
/*
// Do not create unless previously registered.
SolSoundWindow::SolSoundWindow( void )
{
 hWnd        = NULL;
 wDeviceID   = 0;
 is_finished = true;
 return;
}

static char SOLARIS_CLASS_NAME[]="Solaris_Sound_Class";

const int WM_SOL_START = 1998;

SolSoundWindow::~SolSoundWindow(void)
{
 if( hWnd!=NULL )
  {
   DestroyWindow(hWnd);
   SetWindowLong( hWnd, 0, (LONG)NULL );
   UnregisterClass(
                   SOLARIS_CLASS_NAME,
                   sol_active_id->GethInstance().hInstance
                  );
   hWnd = NULL;
  }

 return;
}

// Do not create unless previously registered.
void SolSoundWindow::Build( void )
{
 // Pass 'this' pointer in lpParam of CreateWindow().

 hWnd = CreateWindow(
                     SOLARIS_CLASS_NAME,
                     "Solaris_Sound",
                     WS_OVERLAPPEDWINDOW,
                     CW_USEDEFAULT,
                     CW_USEDEFAULT,
                     128,
                     64,
                     sol_active_id->GethInstance().hWnd,
                     NULL,
                     sol_active_id->GethInstance().hInstance,
                     (LPSTR)this
                    );

 hStatus = CreateWindow(
                        "STATIC",
                        "",
                        WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | ES_LEFT,
                        0,
                        0,
                        64,
                        16,
                        hWnd,
                        NULL,
                        sol_active_id->GethInstance().hInstance,
                        NULL
                       );


 if( hWnd==NULL || hStatus==NULL )
  sol_exit( FALSE );

 Show( SW_SHOW );
 Update();
 PostMessage( GetHandle(), WM_USER+WM_SOL_START, 0, 0 );
 return;
}
*/

/***************************************************************
 Register the class only AFTER WinMain assigns appropriate
 values to static members of Main and only if no previous
 instances of the program exist (a previous instance would
 have already performed the registration).
****************************************************************/
/*
void SolSoundWindow::Register( void )
{
 WNDCLASS wndclass;   // Structure used to register Windows class.
 wndclass.style         = CS_HREDRAW | CS_VREDRAW;
 wndclass.lpfnWndProc   = ::SolWndProc;
 wndclass.cbClsExtra    = 0;

 // Reserve extra bytes for each instance of the window;
 // we will use these bytes to store a pointer to the C++
 // (SolSoundWindow) object corresponding to the window.
 // the size of a 'this' pointer depends on the memory model.
 wndclass.cbWndExtra    = sizeof( SolSoundWindow * );
 wndclass.hInstance     = sol_active_id->htask.hInstance;
 wndclass.hIcon         = NULL;
 wndclass.hCursor       = LoadCursor( NULL, IDC_ARROW );
 wndclass.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
 wndclass.lpszMenuName  = NULL;
 wndclass.lpszClassName = SOLARIS_CLASS_NAME;

 if( !RegisterClass(&wndclass) )
  sol_exit( FALSE );

 return;
}

inline SolSoundWindow *GetPointer( HWND hWnd )
{ return (SolSoundWindow*)GetWindowLong( hWnd, 0 ); }

inline void SetPointer( HWND hWnd, SolSoundWindow *pWindow )
{ SetWindowLong( hWnd, 0, (LONG)pWindow ); }

LRESULT SolSoundWindow::WndProc( UINT iMessage, WPARAM wParam, LPARAM lParam )
{
 switch (iMessage)
  {
   case WM_CREATE: break;
   case WM_DESTROY: PostQuitMessage( 0 ); break;
   case MM_MCINOTIFY: MciNotify(); break;
   default: return DefWindowProc( hWnd, iMessage, wParam, lParam );
  }

 return 0;
}

void SolSoundWindow::DoPlay( const SOLCHAR *filename )
{
 // Ждём освобождения канала вокализации...
 while( !IsFree() )
  sol_yield();

 is_finished = false;

 SOLACHAR *buf = new SOLACHAR[sol_strlen(filename)+1];
 lem_check_ptr_z(buf);
 sol_unicode_to_ascii( buf, filename, sol_cp );

 // MCI APIs to open a device and play a .WAV file, using
 // notification to close
 MciOpenParm.dwCallback       = 0L;
 MciOpenParm.wDeviceID        = 0;
 #if defined SOL_16
 MciOpenParm.wReserved0       = 0;
 #endif
 MciOpenParm.lpstrDeviceType  = NULL;
 MciOpenParm.lpstrElementName = buf;
 MciOpenParm.lpstrAlias       = NULL;

 const UINT32 mci_err=mciSendCommand(
                                     0,
                                     MCI_OPEN,
                                     (DWORD)(MCI_WAIT | MCI_OPEN_ELEMENT),
                                     (DWORD)(LPMCI_OPEN_PARMS)&MciOpenParm
                                    );
 if( mci_err )
  {
   SOLACHAR mci_err_buf[256];
   mciGetErrorString(mci_err,mci_err_buf,sizeof(mci_err_buf));
   lstrcat(mci_err_buf, " [" );
   lstrcat(mci_err_buf, buf  );
   lstrcat(mci_err_buf, "]"  );
   MessageBox(
              GetHandle(),
              mci_err_buf,
              "Sound Play",
              MB_OK | MB_ICONSTOP
             );

   delete buf;
   return;
  }

 delete buf;

 wDeviceID = MciOpenParm.wDeviceID;

 WAVEOUTCAPS wOutCaps;

 if(
    !waveOutGetDevCaps(
                       wDeviceID,
                       (LPWAVEOUTCAPS)&wOutCaps,
                       sizeof(wOutCaps)
                      )
   )
 {
  MessageBox( GetHandle(), "GetDevCaps Error", "Sound Play", MB_OK );
 	return;
 }

 // The time format in this demo is in Samples.
 MciSetParm.dwCallback = 0L;
 MciSetParm.dwTimeFormat = MCI_FORMAT_SAMPLES;
 if(
    mciSendCommand(
                   wDeviceID,
                   MCI_SET,
                   MCI_SET_TIME_FORMAT,
                   (DWORD)(LPMCI_SET_PARMS)&MciSetParm
                  )
   )
  {
   MessageBox( GetHandle(), "SetTime Error", "Sound Play", MB_OK );
   return;
  }

 MciPlayParm.dwCallback = (unsigned long)GetHandle();
 MciPlayParm.dwFrom = 0;
 MciPlayParm.dwTo = 0;
 mciSendCommand(
                wDeviceID,
                MCI_PLAY,
                MCI_NOTIFY,
                (DWORD)(LPMCI_PLAY_PARMS)&MciPlayParm
               );

 SendMessage( hStatus, WM_SETTEXT, 0, (LPARAM)"Playing..." );

 return;
}

void SolSoundWindow::MciNotify( void )
{
 if( wDeviceID )
  StopPlaying();

 return;
}

void SolSoundWindow::StopPlaying( void )
{
 SendMessage( hStatus, WM_SETTEXT, 0, (LPARAM)"Idle..." );

 // Stop playing the waveform file and close the waveform device.
 MciGenParm.dwCallback = 0L;
 mciSendCommand(
                wDeviceID,
                MCI_STOP,
                MCI_WAIT,
                (DWORD)(LPMCI_GENERIC_PARMS)&MciGenParm
               );

 mciSendCommand(
                wDeviceID,
                MCI_CLOSE,
                MCI_WAIT,
                (DWORD)(LPMCI_GENERIC_PARMS)&MciGenParm
               );

 wDeviceID = 0;
 is_finished=true;
 return;
}

LRESULT CALLBACK _export SolWndProc(
                                    HWND hWnd,
                                    UINT iMessage,
                                    WPARAM wParam,
                                    LPARAM lParam
                                   )
{
 // Pointer to the (C++ object that is the) window.
 SolSoundWindow *pWindow = GetPointer( hWnd );

 // The pointer pWindow will have an invalid value if the WM_CREATE
 // message has not yet been processed (we respond to the WM_CREATE
 // message by setting the extra bytes to be a pointer to the
 // (C++) object corresponding to the Window identified by hWnd).
 // The messages that precede WM_CREATE must be processed without using
 // pWindow so we pass them to DefWindowProc.
 // How do we know in general if the pointer pWindow is invalid?
 // Simple: Windows allocates the window extra bytes using LocalAlloc
 // which zero initializes memory; thus, pWindow will have a value of
 // zero before we set the window extra bytes to the 'this' pointer.
 // Caveat emptor: the fact that LocalAlloc will zero initialize the
 // window extra bytes is not documented; therefore, it could change
 // in the future.

 if( pWindow == NULL )
  {
   if( iMessage == WM_CREATE )
    {
     LPCREATESTRUCT lpcs;

     lpcs = (LPCREATESTRUCT) lParam;
     pWindow = (SolSoundWindow *) lpcs->lpCreateParams;

     // Store a pointer to this object in the window's extra bytes;
     // this will enable us to access this object (and its member
     // functions) in WndProc where we are
     // given only a handle to identify the window.
     SetPointer( hWnd, pWindow );
     // Now let the object perform whatever
     // initialization it needs for WM_CREATE in its own
     // WndProc.
     return pWindow->WndProc( iMessage, wParam, lParam );
    }
   else
    return DefWindowProc( hWnd, iMessage, wParam, lParam );
  }
 else
  return pWindow->WndProc( iMessage, wParam, lParam );
}
*/
#endif // defined SOL_WINDOWS && defined SOL_GUI

#endif // defined SOL_CAA
// --------------------------- End Of File [IO_AUDIO.CPP] ----------------------

