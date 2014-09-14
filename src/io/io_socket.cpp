// -----------------------------------------------------------------------------
// File IO_SOCKET.CPP
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
// Поддержка межпрограммного обмена через потоки ввода-вывода на основе pipe'ов.
// Пока только для WinNT/Win2000
//
// Создано на основе исходников Trapper McFerron ( trapzz@hotmail.ru )
// -----------------------------------------------------------------------------
//
// CD->11.04.2002
// LC->15.01.2005
// --------------

#include <lem/config.h>

#include <io_socket.h>
#include <lem/conversions.h>

using namespace lem;
using namespace lem::Sockets;


Lem_IP::Lem_IP(void)
{
 memset( addr, 0, sizeof(addr) );
 iport=0;
 null=false;
 return;
}

// **********************************************************************
// Текстовую строку Str разбираем на четыре числа представления IP-адреса
// и при необходимости - на номер порта.
//
//                123.123.123.123:80
//
// **********************************************************************
Lem_IP::Lem_IP( const char *Str )
{
 memset( addr, 0, sizeof(addr) );
 iport=0;

 str = Str;
 null=false;

 // Разбираем на четыре квинтета.
 int i=0, i8=0;
 CString s8;
 int d8;

 while( i<2048 && i8<4 )
  {
   if( Str[i]=='.' || Str[i]==':' || Str[i]=='\0' )
    {
     d8=0;

     if( !to_int(s8.c_str(),&d8) )
      {
       // Адрес задан некорректно - не в форме BBB.BBB.BBB.BBB
       null=true;
       break;
      }

     // Получили очередной квинтет - запоминаем байт.
     addr[i8++] = d8;
     s8 = "";

     if( Str[i]=='.' )
      i++;
     else
      break;
    }
   else
    s8 += Str[i++];
  }

 if( Str[i]==':' )
  {
   // Извлекаем номер порта.
   if( !to_int( Str+i+1, &iport ) )
    {
     // Ошибка задания номера порта.
     null=true;
     return;
    }
  }
 else
  iport=2500; // Номер порта по умолчанию.

 return;
}

// **************************************************
// Возвращает адрес в виде строки 123.123.123.123
// **************************************************
const CString Lem_IP::get_ip(void) const
{
 CString res;

 if( IsNull() )
  // Для некорретного адреса возвращаем пустую строку.
  return res;

 res += to_str( addr[0] );
 res += '.';
 res += to_str( addr[1] );
 res += '.';
 res += to_str( addr[2] );
 res += '.';
 res += to_str( addr[3] );

 return res;
}

// #########################################################

bool SocketStream::winsock_inited=false;
WSADATA SocketStream::ws;

// **********************************************************************
// Задан IP-адрес подключения. Если bServer=true, то - в режиме сервера.
// **********************************************************************
SocketStream::SocketStream( const char *addr, bool bServer )
{
 failed=false;

 InitWinSocket();

 connected = false;
 IP        = addr;
 sckt      = NULL;

 server = bServer;
 if( server )
  openServerConn();
 else
  openConn();

 return;
}

SocketStream::~SocketStream()
{
 closeConn();
 return;
}

void SocketStream::InitWinSocket(void)
{
 if( !winsock_inited )
  {
   winsock_inited=true;

   if( !!WSAStartup(0x0101,&ws) ) // возвращает 0, если ошибок нет.
    {
     // Ошибка запуска библиотеки WinSock!!!
     failed = true;
    }
  }

 return;
}

// ********************************************
// Создаем сокет.
// ********************************************
void SocketStream::openConn(void)
{
 if( failed )
  return;

// int e;

 // Заполняем структуру sockaddr - для использования с протоколом TCP/IP.
 san.sin_family = AF_INET;
 san.sin_port = htons( IP.get_port() );
 san.sin_addr.s_addr = inet_addr( IP.get_ip().c_str() );
 sanSize = sizeof(san);

 sckt = socket( AF_INET, SOCK_DGRAM, 0 );

 if( sckt==INVALID_SOCKET || !!WSAGetLastError() )
  {
   // Ошибка подключения!
   connected=false;
   failed=true;
  }

 if( !failed )
  connected = true;

 return;
}

void SocketStream::closeConn(void)
{
 if( failed )
  return;

 shutdown( sckt, 1 );
 closesocket(sckt);
 connected = false;
 sckt = NULL;
 return;
}

void SocketStream::openServerConn(void)
{
 if( failed )
  return;

 //this acts as its own server and accepts any ip address
 //so we can direct connect to it

 san.sin_family = AF_INET;
 san.sin_port = htons(IP.get_port());
 san.sin_addr.s_addr = htonl(INADDR_ANY); // Адрес будет взят системной по
                                          // умолчанию (присвоенный компьютеру
                                          // в сети).
 sanSize = sizeof(san);

 sckt = socket(AF_INET, SOCK_DGRAM,0);

 if( sckt==INVALID_SOCKET || !!WSAGetLastError() )
  {
   // Ошибка подключения!
   connected=false;
   failed=true;
   return;
  }

 if( bind( sckt, (sockaddr *) &san, sanSize )==SOCKET_ERROR )
  {
   // Ошибка связывания
   connected=false;
   failed=true;
  }

 if( !failed )
  connected = true;

 return;
}

BaseStream::pos_type SocketStream::read( void *dest, size_t size )
{
 int t=recvfrom(sckt,(char*)dest,size,0,(sockaddr *)&san,&sanSize);
 if( t==SOCKET_ERROR )
  failed = true;

 return failed ? -1 : 0;
}

void SocketStream::write( const void *src, size_t size )
{
 int t = sendto(sckt,(char*)src,size,0,(sockaddr *)&san,sanSize);
}

// *************************************************
// Проверяет отсутствие ошибок работы с потоком.
// *************************************************
void SocketStream::Check(void) const
{
}

// Сбрасывает данные из буферов вывода.
void SocketStream::flush(void)
{
}

// *********************************************************
// Проверяет достижение конца файла для читаемого потока.
// *********************************************************
bool SocketStream::eof(void) const
{
 return failed || !connected;
}

// Сообщает позицию курсора записи-чтения в потоке.
BaseStream::pos_type SocketStream::tellp(void) const
{
 LEM_STOPIT;
 return -1;
}

// Перемещает курсор на заданную позицию: отсчитываем позицию от начала
// файла, текущей позиции или конца файла, согласно константе where_to.
// Для справки - см. описание стандартной функции fseek(...).
BaseStream::pos_type SocketStream::seekp( off_type pos, int whereto )
{
 LEM_STOPIT;
 return -1;
}


// Перемещение курсора относительно текущей позиции, к началу или к концу
// файла согласно знаку смещения offset.
BaseStream::pos_type SocketStream::move( off_type offset )
{
 LEM_STOPIT;
 return -1;
}

// Сбрасывает буфера вывода и закрывает поток.
void SocketStream::close(void)
{
 closeConn();
 return;
}

// Возвращает текущий размер потока.
BaseStream::pos_type SocketStream::fsize(void) const
{
 LEM_STOPIT;
 return 0;
}

// Готовы ли данные для считывания или готов ли канал принимать данные?
// Имеет смысл для потоков, которые работают с устройствами типа
// клавиатуры или сетью.
bool SocketStream::isready(void) const
{
 LEM_STOPIT;
 return true;
}

// Ждем готовности канала данных.
void SocketStream::wait_ready(void) const
{
 LEM_STOPIT;
}

// Чтение единичного символа. Может возвращать EOF (-1) при достижении
// конца файла. Автоматически смещает курсор к концу файла.
int SocketStream::get(void)
{
 char ch;
 read(&ch,1);
 return ch;
}

// Вписывает символ в текущую позицию в файле.
void SocketStream::put( char ch )
{
 write(&ch,1);
}

// -------------------------- End Of File [IO_SOCKET.CPP] -----------------------
