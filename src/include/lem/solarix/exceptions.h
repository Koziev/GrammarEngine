// -----------------------------------------------------------------------------
// File EXCEPTIONS.H
//
// (c) Koziev Elijah
//
// Content:
// Определения некоторых типов исключений, генерируемых кодом Solarix'а.
// -----------------------------------------------------------------------------
//
// CD->14.11.2003
// LC->18.05.2009
// --------------

#ifndef SOL_EXCEPTIONS__H
#define SOL_EXCEPTIONS__H
#pragma once

 #include <lem/cstring.h>
 #include <lem/conversions.h>
 #include <string>

 #if defined LEM_BORLAND && !defined LEM_CODEGEAR
  #include <exception.h>
 #endif

 namespace Solarix
 {
  using lem::to_wstr;
  using lem::E_BaseException;
  using lem::E_ParserError;
  using lem::UCString;

  // *******************************************************************
  // Базовый класс для исключений, порождаемых кодом SOLARIX'а
  // Обращаю внимание на существенное отличие от стандартного
  // класса exception: поле с описанием ошибки является UNICODE-строкой,
  // поскольку постоянно требуется выводить текст с национальными
  // символами, а привязываться к одной конкретной кодировке (допустим,
  // переводить кириллицу в ASCII-коды по кодовой странице 1251) было бы
  // неразумно.
  //
  // Более того, поле текста ошибки базового класса exception
  // НЕ ИНИЦИАЛИЗИРУЕТСЯ!
  // *******************************************************************
  class E_Solarix : public E_BaseException
  {
   public:
    E_Solarix(void) {};
    explicit E_Solarix( const std::wstring &Text ):E_BaseException(Text) {};
    explicit E_Solarix( const wchar_t *Text ):E_BaseException( to_wstr(Text) ) {};

    // Конструктор с аргументом char* отсутствует - чтобы не возникало
    // ошибок с заданием текста ошибки в какой-либо ASCII-кодировке,
    // что означало бы потерю портабельности.

    #if defined LEM_GNUC
    virtual ~E_Solarix(void) throw() {};
    #endif
  };

  // *****************************************
  // Базовый класс для RUN TIME ошибок.
  // *****************************************
  class E_RunTime : public E_Solarix
  {
   public:
    E_RunTime(void):E_Solarix(L"run-time error") {};
    explicit E_RunTime( const std::wstring &Text ):E_Solarix(Text) {};
    explicit E_RunTime( const wchar_t *Text ):E_Solarix(Text) {};
  };

  // ********************************************************************
  // 'Form not found' - для заданного списка координатных пар не удалось
  // подобрать форму в словарной статье.
  // ********************************************************************
  class E_SG_NoForm : public E_Solarix
  {
   public:
    E_SG_NoForm(void) {};
  };

  // *******************************************
  // Не найден грамматический класс
  // *******************************************
  class E_SG_NoClass : public E_ParserError
  {
   public:
    UCString class_name;
    E_SG_NoClass( const UCString &Class_name ):class_name(Class_name) {};
  };

  class E_LoadBinError : public E_RunTime
  {
   public:
    E_LoadBinError(void):E_RunTime( L"Loading from binary file error" ) {};
  };

  class E_AA_Error : public E_RunTime
  {
   public:
    E_AA_Error(void):E_RunTime(L"generic AA error") {};
    explicit E_AA_Error( const std::wstring &Text ):E_RunTime(Text) {};
    explicit E_AA_Error( const wchar_t *Text ):E_RunTime(Text) {};
  };

  // *************************************************************
  // Maximum number of variators reached during the AA iterations
  // *************************************************************
  class E_AA_MaxVars : public E_AA_Error
  {
   public:
    E_AA_MaxVars(void)
     :E_AA_Error(L"maximum number of variators has been reached") {};
  };
 }

#endif
