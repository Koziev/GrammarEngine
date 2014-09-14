// -----------------------------------------------------------------------------
// File IO_SOCKET.H
//
// (c) by Koziev Elijah
//
// Content:
// Поддержка межпрограммного обмена через потоки ввода-вывода на основе
// socket'ов. Пока только для WinNT/Win2000
//
// Создано на основе исходников Trapper McFerron ( trapzz@hotmail.ru )
// -----------------------------------------------------------------------------
//
// CD->11.04.2002
// LC->16.08.2007
// --------------

#ifndef LEM_SOCK__H
#define LEM_SOCK__H
#pragma once

 #if defined LEM_WINDOWS

 #include <lem/cstring.h>
 #include <lem/streams.h>

 #include <winsock.h>
 #include <cstdio>

 namespace lem
 {
  namespace Sockets
  {
   using lem::CString;
   using lem::Stream;

 // ****************************************************************
 // Структура хранит IP-адрес и содержит методы для преобразования
 // в различные форматы.
 // ****************************************************************
 class Lem_IP
 {
  private:
   bool null; // true, если адрес не задан или задан неверно.
   UINT8 addr[4]; // 4 байта адреса
   CString str; // И строковое представление

   int iport; // Номер порта.

  public:
   Lem_IP(void);
   Lem_IP( const char *Str );

   inline bool IsNull(void) const { return null; }

   inline int get_port(void) const { return iport; }
   inline void SetPort( int P ) { iport=P; }

   const CString get_ip(void) const;
 };

 // ********************************************************************
 // Поток пересылки данных на основе системного сервиса Windows Sockets.
 // ********************************************************************
 class SocketStream : public Stream
 {
  protected:
   static bool winsock_inited;
   static WSADATA ws;

   SOCKET sckt;
   sockaddr_in san;
   bool server; // Серверный сокет.

   Lem_IP IP;

   int sanSize;
   bool connected; // connected boolean so I can see if they are connected or not
   bool failed; // Пересылка данных или создание сокета закончились сбоем.

   virtual void openConn(void);
   virtual void openServerConn(void);

   virtual void closeConn(void);

   void InitWinSocket(void);

  public:
   SocketStream( const char *str, bool bServer=false );
   ~SocketStream(void);

   inline const Lem_IP& getIP(void) const { return IP; }

   virtual bool isConnected(void) {return connected;}

   // Запись блока информации, на который указывает src, размером size.
   virtual void write( const void *src, pos_type size );

   // Чтение блока информации в область памяти, на которую указывает dest,
   // размером size.
   virtual pos_type read( void *dest, pos_type size );

   // Проверяет отсутствие ошибок работы с потоком.
   virtual void Check(void) const;

   // Сбрасывает данные из буферов вывода.
   virtual void flush(void);

   // Проверяет достижение конца файла для читаемого потока.
   virtual bool eof(void) const;

   // Сообщает позицию курсора записи-чтения в потоке.
   virtual pos_type tellp(void) const;

   // Перемещает курсор на заданную позицию: отсчитываем позицию от начала
   // файла, текущей позиции или конца файла, согласно константе where_to.
   // Для справки - см. описание стандартной функции fseek(...).
   virtual pos_type seekp( off_type pos, int whereto=SEEK_SET );

   // Перемещение курсора относительно текущей позиции, к началу или к концу
   // файла согласно знаку смещения offset.
   virtual pos_type move( off_type offset );

   // Сбрасывает буфера вывода и закрывает поток.
   virtual void close(void);

   // Возвращает текущий размер потока.
   virtual pos_type fsize(void) const;

   // Готовы ли данные для считывания или готов ли канал принимать данные?
   // Имеет смысл для потоков, которые работают с устройствами типа
   // клавиатуры или сетью.
   virtual bool isready(void) const;

   // Ждем готовности канала данных.
   virtual void wait_ready(void) const;

   // Чтение единичного символа. Может возвращать EOF (-1) при достижении
   // конца файла. Автоматически смещает курсор к концу файла.
   virtual int get(void);

   // Вписывает символ в текущую позицию в файле.
   virtual void put( char ch );

   virtual bool is_failed(void) const { return failed; }
 };

  } // namespace Sockets
 } // namespace lem

 #endif
#endif
// ------------------------- End Of File [IO_SOCKET.H] ------------------------
