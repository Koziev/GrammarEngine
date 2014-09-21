// -----------------------------------------------------------------------------
// File IO_DB_STREAM.H
//
// (c) Koziev Elijah
//
// Content:
// Класс DB_Stream - поток для вывода текстовых SQL команд в подключаемую БД.
// -----------------------------------------------------------------------------
//
// CD->16.01.2005
// LC->16.08.2007
// --------------

#ifndef IO_DB_STREAM__H
#define IO_DB_STREAM__H
#pragma once

 #include <lem/streams.h>

 namespace lem
 {
  namespace Database
  {
   class SQL_Data_Source;
  }

  using lem::Database::SQL_Data_Source;

 // Поток вывода SQL-операторов в базу данных. Поступающие символы
 // накапливаются до поступления символа ';' - конца команды.
 // Затем сформированная команда посылается серверу на исполнение.
 class DB_Stream : public Stream
 {
  private:
  int cmd_count;        // number of parsed commands
   SQL_Data_Source *db; // Destination - generic database
   FString sql;         // the SQL command being accumulated
   bool open_1, open_2; // учет открытых кавычек.

  public:
   DB_Stream( SQL_Data_Source *Database );

   virtual void write( const void * /*src*/, pos_type /*size*/ ) {};

   virtual void put( char Ch );

   virtual pos_type read( void * /*dest*/, pos_type /*size*/ ) { LEM_STOPIT; return 0; }
   virtual int get(void) { return 0; }

   virtual void flush(void);
   virtual bool eof(void) const { return false; }
   virtual pos_type tellp(void) const { LEM_STOPIT; return 0; }

   virtual pos_type seekp( off_type /*pos*/, int /*whereto*/=SEEK_SET )
   { return 0; }

   virtual bool move( off_type /*offset*/ ) { return 0; }

   virtual void close(void) {}

   virtual pos_type fsize(void) const { return 0; }

   inline int get_CmdCount(void) const { return cmd_count; }
   inline const FString& get_Sql(void) const { return sql; }
 };

 } // end of namespace 'lem'

#endif
