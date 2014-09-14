// -----------------------------------------------------------------------------
// File IO_PIPE.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс PipeStream - операции пересылки данных посредством системного
// сервиса pipe'ов.
// -----------------------------------------------------------------------------
//
// CD->05.11.2000
// LC->16.01.2005
// --------------

#include <io_pipe.h>

using namespace lem;

PipeStream::PipeStream(
                       const lem::Path& Name,
                       bool r,
                       bool w,
                       bool IsItServer,
                       int TimeOut
                      )
:BaseStream( r, w, Name )
{
 failed = false;
 attached = false;
 saPipe.lpSecurityDescriptor = NULL;

 is_it_server = IsItServer;
 if( IsItServer )
  AttachToClient(TimeOut);
 else
  AttachToServer(TimeOut);

 return;
}

PipeStream::~PipeStream(void)
{
 if( is_it_server )
  DetachFromClient();
 else
  DetachFromServer();

 return;
}

// *********************************************************
// Внутренняя процедура - подключаемся к серверу.
// *********************************************************
void PipeStream::AttachToServer( int TimeOut )
{
 bool bSuccess      = false;
 bool bNotConnected = true;

 while( bNotConnected )
  {
   /* attempt to connect to pipe instance */
   hPipe = CreateFile(
                      GetName().Get_Ascii().c_str(),
                      GENERIC_READ | GENERIC_WRITE,
                      0,
                      NULL,
                      OPEN_EXISTING,
                      0,
                      NULL
                     );

   if( GetLastError() == ERROR_PIPE_BUSY )
    {
     // Waiting for a pipe instance...
     bSuccess = WaitNamedPipe( GetName().Get_Ascii().c_str(), TimeOut );
     if( !bSuccess )
      {
       // Подключиться не удалось...
       attached = false;
       break;
      }
    }
   else
    {
     if( hPipe==INVALID_HANDLE_VALUE )
      {
       // fault in 'CreateFile'
       attached = false;
       break;
      }

     bNotConnected = (hPipe == INVALID_HANDLE_VALUE);
     if( !bNotConnected )
      attached = true;
    }
  } /* while */

 // Поле attached будет выставлено как true, если связь установлена успешно.

 if( attached==false )
  failed=true;

 return;
}

// **************************************************
// Отключаемся от сервера.
// **************************************************
void PipeStream::DetachFromServer(void)
{
 CloseHandle(hPipe);
 hPipe = NULL;
 attached = false;
 return;
}

// *********************************************************
// Внутренняя процедура - подключаемся к клиенту.
// *********************************************************
void PipeStream::AttachToClient( int TimeOut )
{
 bool bSuccess;
 char *szPname;

 /* set up a NULL DACL in our pipe security descriptor to allow anyone to
    connect to the pipe server */
 saPipe.lpSecurityDescriptor =
       (PSECURITY_DESCRIPTOR)malloc(SECURITY_DESCRIPTOR_MIN_LENGTH);

 InitializeSecurityDescriptor(
                              saPipe.lpSecurityDescriptor,
                              SECURITY_DESCRIPTOR_REVISION
                             );

 SetSecurityDescriptorDacl(
                           saPipe.lpSecurityDescriptor,
                           TRUE,
                           (PACL)NULL,
                           FALSE
                          );

 saPipe.nLength = sizeof(saPipe);
 saPipe.bInheritHandle = TRUE;

 // Create a named pipe: duplex, type byte, readmode byte, unlimited
 // instances, default timeout of 60s
 hPipe = CreateNamedPipe(
                         GetName().Get_Ascii().c_str(),
                         PIPE_ACCESS_DUPLEX | 0,
                         PIPE_TYPE_BYTE |
                         PIPE_READMODE_BYTE |
                         PIPE_WAIT,
                         PIPE_UNLIMITED_INSTANCES,
                         0,
                         0,
                         TimeOut,
                         &saPipe
                        );

 if( hPipe==INVALID_HANDLE_VALUE )
  {
   attached = false;
   failed = true;
   hPipe = NULL;
   return;
  }

 // Wait for a client application to connent.
 bSuccess = ConnectNamedPipe( hPipe, NULL );

 // check return from either ConnectNamedPipe or GetOverlappedResult.
 // If a client managed to connect between the CreateNamedPipe and
 //  ConnectNamedPipe calls, ERROR_PIPE_CONNECTED will result.
 if( !bSuccess && GetLastError()!=ERROR_PIPE_CONNECTED )
  {
   /* something went wrong, report error, close instance and try again */
   attached = false;
   failed = true;
   CloseHandle(hPipe);
   return;
  }
 else
  attached = true;

 if( attached==false )
  failed=true;

 return;
}

// **************************************************
// Отключаемся от клиента.
// **************************************************
void PipeStream::DetachFromClient(void)
{
 free(saPipe.lpSecurityDescriptor);
 DisconnectNamedPipe(hPipe);
 CloseHandle(hPipe);

 hPipe=NULL;
 attached=false;
 return;
}

// ***********************************************************************
// Запись блока информации, на который указывает src, размером size, в
// поток с текущей позиции.
// **************************************************
void PipeStream::write( const void *src, BaseStream::pos_type size )
{
 if( !attached || failed || hPipe==NULL )
  return;

 /**/ GetLastError(); // Clear error flag...
 DWORD dwWritten;

 // Теперь пересылаем сам блок данных.
 const bool bSuccess = WriteFile(
                                 hPipe,
                                 src,
                                 size,
                                 &dwWritten,
                                 NULL
                                );

 // Пересылка закончена. Проверим успешность операции.
 IFDEBUG(Check());
 if( !bSuccess )
  {
   attached = false;
   failed = true;
  }
 else
  {
   failed = false;
  }

 return;
}

// *********************************************************************
// Чтение блока информации в область памяти, на которую указывает dest,
// размером size, с текущей позиции.
// *********************************************************************
BaseStream::pos_type PipeStream::read( void *dest, BaseStream::pos_type size )
{
 if( !attached || hPipe==NULL )
  return -1;

 DWORD dwRead=0;

 const bool Success = ReadFile(
                               hPipe,
                               dest,
                               size,
                               &dwRead,
                               NULL
                              );

 // If ReadFile fails, check pipe.
 IFDEBUG(Check());
 if( !Success )
  {
   failed = true;
   attached = false;
   return -1;
  }

 return 0;
}

// *********************************************************************
// Готовы ли данные для считывания или готов ли канал принимать данные?
// Имеет смысл для потоков, которые работают с устройствами типа
// клавиатуры или сетью.
// *********************************************************************
bool PipeStream::isready(void) const
{
 return true;
}

// **************************************************
// Ждем готовности канала данных.
// **************************************************
void PipeStream::wait_ready(void) const
{
 return;
}

// ********************************************************************
// Чтение единичного символа. Может возвращать EOF (-1) при достижении
// конца файла. Автоматически смещает курсор к концу файла.
// ********************************************************************
int PipeStream::get(void)
{
 char c;
 read( &c, 1 );
 return 0x00ff & int(c);
}

// **************************************************
// Вписывает символ в текущую позицию в файле.
// **************************************************
void PipeStream::put( char ch )
{
 char b=ch;
 write( &b, 1 );
 return;
}

// **************************************************
// Проверяет отсутствие ошибок работы с потоком.
// **************************************************
void PipeStream::Check(void) const
{
 LEM_CHECKIT( hPipe!=INVALID_HANDLE_VALUE );
 LEM_CHECKIT( !failed );
 LEM_CHECKIT( attached );

 const DWORD dwLastError = GetLastError();
 if( dwLastError == ERROR_BROKEN_PIPE || dwLastError == ERROR_NO_DATA )
  LEM_STOPIT;

 return;
}

// **************************************************
// Сбрасывает данные из буферов вывода.
// **************************************************
void PipeStream::flush(void)
{
 FlushFileBuffers(hPipe);
 return;
}

// ******************************************************
// Проверяет достижение конца файла для читаемого потока.
// ******************************************************
bool PipeStream::eof(void) const
{
 // Считаем, что сбой канала - это конец потока.
 return is_failed();
}

// ***************************************************************************
// Сообщает позицию курсора записи-чтения в потоке - для pipe'ов не работает.
// ***************************************************************************
BaseStream::pos_type PipeStream::tellp(void) const
{
 LEM_STOPIT;
 return 0;
}

// ***************************************************************************
// Перемещает курсор на заданную позицию: отсчитываем позицию от начала
// файла, текущей позиции или конца файла, согласно константе where_to.
// Для справки - см. описание стандартной функции fseek(...).
// Для pipe'ов не работает.
// ***************************************************************************
BaseStream::pos_type PipeStream::seekp( off_type pos, int whereto )
{
 LEM_STOPIT;
 return 0;
}

// ***************************************************************************
// Перемещение курсора относительно текущей позиции, к началу или к концу
// файла согласно знаку смещения offset.
// Для pipe'ов не работает.
// ***************************************************************************
BaseStream::pos_type PipeStream::move( off_type offset )
{
 LEM_STOPIT;
 return 0;
}

// **************************************************
// Сбрасывает буфера вывода и закрывает поток.
// **************************************************
void PipeStream::close(void)
{
 DetachFromServer();
 return;
}

// **************************************************
// Возвращает текущий размер потока.
// Для pipe'ов не работает.
// **************************************************
BaseStream::pos_type PipeStream::fsize(void) const
{
 LEM_STOPIT;
 return 0;
}

// -------------------------- End Of File [IO_PIPE.CPP] ------------------------
