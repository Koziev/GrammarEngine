// -----------------------------------------------------------------------------
// File SOL_IO.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// —реда ввода-вывода: комплекс потоков дл€ ввода-вывода информации прикладными
// программами.
// -----------------------------------------------------------------------------
//
// CD->14.10.2002
// LC->13.04.2007
// --------------

#ifndef LEM_IO__H
#define LEM_IO__H
#pragma once

 #include <lem/config.h>
 #include <lem/macros.h>
 #include <lem/runtime_checks.h>

 namespace lem
 {

 class OFormatter;

 struct Sol_IO
 {
  OFormatter *err;  // ƒл€ сообщений об ошибках
  OFormatter *echo; // Ёхо-печать - обычно трассировка работы модулей

  Sol_IO(void) { Clear(); }

  inline void SetMerr( OFormatter *Merr ) { err=Merr;  }
  inline void SetEcho( OFormatter *Echo ) { echo=Echo; }

  inline OFormatter& merr(void) const
  { LEM_CHECKIT_Z( !!(err) ); return *err; }

  inline OFormatter& mecho(void) const
  { LEM_CHECKIT_Z( !!(echo) ); return *echo; }

  inline void Clear(void)
  {
   echo    = NULL;
   err     = NULL;
  }

  void Flush(void);
 };

 } // namespace 'lem'

#endif
