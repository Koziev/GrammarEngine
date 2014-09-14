#ifndef LEM_FSTRING__H
#define LEM_FSTRING__H
#pragma once

// -----------------------------------------------------------------------------
// File FSTRING.H
//
// (c) by Elijah Koziev   all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// BaseFString<T> UNICODE mutable strings template class.
// —троки символов с автоматическим выделением динамической пам€ти.
//
// —м. также: класс BaseCString ("lem_cstr.h")
//
// 19.08.2004 - добавлено резервирование пам€ти под расширение строки. ѕри этом
// по умолчанию конструкторы и операторы присваивани€ выдел€ют пам€ти столько,
// сколько точно нужно дл€ хранени€ строки (плюс терминатор). “олько при
// работе оператора += происходит выделение пам€ти с запасом, чтобы уменьшить
// катастрофическое падение скорости посимвольного добавлени€.
//
// ƒобавлены конструкторы сли€ни€ - из двух и из трех строк.
//
// 27.09.2004 - добавлены операции front() и back()
// 01.11.2004 - исправлена груба€ ошибка, приводивша€ к переполнению буфера,
//              в subst(...) 
//
// 13.12.2004 - введены методы SaveBin и LoadBin, чтобы было удобно работать
//              с контейнерами (сохранение и загрузка Collect<FString>). 
//
// 26.01.2005 - устранены два бага в insert(...)
//
// 17.09.2005 - так как функци€ realloc в MSVS иногда дл€ указател€ NULL сбоит,
//              использован условный оператор и malloc
//
// 07.01.2006 - дл€ отладки использован класс Guardian (см. runtime_checks.h).
//
// 23.03.2008 - добавлен шаблон-селектор StringTypeSelector дл€ выбора
//              строкового типа в зависимости от глобального флага компил€ции
//              UNICODE/ASCII
// -----------------------------------------------------------------------------
//
// CD->02.07.1996
// LC->26.05.2008
// --------------

#include <lem/config.h>

#if defined LEM_MFC
 #include <afxwin.h>
#endif

#if defined LEM_WINDOWS
 #include <tchar.h>
#endif

#include <lem/afstring.h>
#include <lem/ufstring.h>

namespace lem
{
 template < typename CHAR >
 struct StringTypeSelector
 {
 };

 template <>
 struct StringTypeSelector<char>
 {
  typedef lem::FString string_type;
  typedef char char_type;
 };

 template <>
 struct StringTypeSelector<wchar_t>
 {
  typedef lem::UFString string_type;
  typedef wchar_t char_type;
 };

 #if defined LEM_WINDOWS && defined LEM_MSC && defined _T
  typedef StringTypeSelector<TCHAR>::string_type TString;
 #elif defined UNICODE || defined _UNICODE
  typedef UFString TString;
 #else
  typedef FString TString;
 #endif
}

#endif
