#ifndef SOL_SQL_PRODUCTION__H
#define SOL_SQL_PRODUCTION__H
#pragma once

 #include <lem/fstring.h>

 namespace Solarix
 {
  using lem::FString;

  // **********************************************************
  // Блок параметров экспорта бинарного словаря в SQL формат
  // **********************************************************
  class SQL_Production
  {
   public:
    typedef enum { Generic, Oracle, MySql, MsSql, FireBird, 
                   SQLite, Postgres, Informix, DB2 } SqlType;
    SqlType type;
    int bulk_inserts;
    int internal_commit_period;
    lem::zbool mssql_bulk_insert; // поддержка TSQL оператора BULK INSERT в скрипте для MS SQL
    lem::zbool loader; // поддержка оператора LOAD DATA INFILE в MySQL
    int top_freq; // если задана выгрузка только NNN самых частотных статей

   private:
    lem::FString version;
    lem::FString comment;
    lem::zbool utf8, bom;
    lem::zbool ascii;
    lem::zbool demo;
    lem::MCollect<wchar_t> demo_ename_front; // для выгрузки демо-версии SQL - фильтры первой буквы имени словарных статей
    lem::FString begin_tx, commit_tx, internal_commit_tx;

   public:
    lem::zbool noschema; // не генерировать операторы CREATE TABLE и подобные
    lem::zbool noformcoords; // не создавать таблицы SG_FORM_COORD
    lem::zbool lemmatizator; // в отдельном скрипте создавать таблицы лемматизатора
    lem::zbool norules; // не выгружать всевозможные правила
    lem::Path outdir; // каталог для записи формируемых дополнительных файлов (например для MS SQL BULK INSERT)
 
   public:
    SQL_Production( const lem::FString &Version );
   
    inline const lem::FString& Get_Version(void) const { return version; }
    inline const lem::FString Get_Comment(void) const { return comment; }
    inline const lem::FString BeginTx(void) const { return begin_tx; }
    inline const lem::FString CommitTx(void) const { return commit_tx; }
    inline const lem::FString InternalCommit(void) const { return internal_commit_tx; }

    // Для демо-режима выгрузки - проверяет, что первый символ имени
    // статьи соответствует ранее определенным фильтрам.
    bool MatchEntryName( const lem::UCString &ename ) const;

    bool IsUtf8(void) const { return utf8; }
    bool IsAscii(void) const { return ascii; }
    bool WriteBOM(void) const { return bom; }
    bool IsDemo(void) const { return demo; }

    lem::UFString SqlStr( const lem::UCString &s ) const;
    lem::UFString SqlStr( const lem::UFString &s ) const;

    // Возвращает префикс для строковых литералов, например для поля типа nvarchar2 для Oracle и MS SQL
    // возвращает N, для других СУБД может вернуть пустую строку (не NULL).
    const wchar_t * GetNPrefix(void) const;

    // Возвращает команду LOAD DATA ... INLINE для MySQL
    const wchar_t * GetLoadInfileText(void) const;

    static lem::UFString Oracle_UNISTR( const lem::UFString & str );

    lem::UFString ClearInvalidChars( const lem::UFString & str ) const;
  };


 } // namespace Solarix

#endif
