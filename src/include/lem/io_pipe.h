// -----------------------------------------------------------------------------
// File LEM_PIPE.H
//
// (c) Koziev Elijah
//
// Content:
// Поддержка межпрограммного обмена через потоки ввода-вывода на основе pipe'ов.
// Пока только для WinNT/Win2000
// -----------------------------------------------------------------------------
//
// CD->05.11.2000
// LC->16.08.2007
// --------------

#ifndef LEM_PIPE__H
#define LEM_PIPE__H
#pragma once

 #include <lem/config.h> 

 #if defined LEM_WINDOWS

 #include <lem/streams.h>
 #include <windows.h>
 #undef AddForm
 #include <lem/ints.h>

 namespace lem
 {

 // *************************************************************
 // Поток пересылки данных на основе системного сервиса pipe'ов.
 // *************************************************************
 class PipeStream : public Stream
 {
  private:
   HANDLE hPipe; // Системный дескриптор канала передачи данных.
   bool failed; // Пересылка данных закончилась сбоем.
   bool attached; // Подключен ли линк...
   bool is_it_server; // Для сервера содержит true, для client'а = false.

   SECURITY_ATTRIBUTES saPipe; // Для сервера в WinNT.

   void AttachToServer( int TimeOut );
   void DetachFromServer(void);

   void AttachToClient( int TimeOut );
   void DetachFromClient(void);

  public:
   PipeStream(
              const lem::Path& Name,
              bool r=true,
              bool w=true,
              bool IsItServer=false,
              int TimeOut=0
             );

   virtual ~PipeStream(void);

   // Запись блока информации, на который указывает src, размером size, в
   // поток с текущей позиции.
   virtual void write( const void *src, pos_type size );

   // Чтение блока информации в область памяти, на которую указывает dest,
   // размером size, с текущей позиции.
   virtual pos_type read( void *dest, pos_type size );

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

   virtual bool is_failed(void) const { return failed; }
 };

 } // namespace 'lem'

 #endif

#endif
// ------------------------ End Of File [LEM_PIPE.H] ---------------------------
