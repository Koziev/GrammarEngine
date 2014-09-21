// -----------------------------------------------------------------------------
// File NULL_CONSOLE.CPP
//
// (c) Koziev Elijah
//
// Content:
// Реализация глобальных объектов вывода на консоль - mout и merr. Данный
// модуль предназначен для создания заглушек - объекты mout и merr ссылаются
// на NUL.
//
// 22.02.2010 - код создания консольных потоков перенесен в lem_startup.cpp
// -----------------------------------------------------------------------------
//
// CD->07.01.2005
// LC->22.02.2010
// --------------

#include <lem/streams.h>
#include <lem/console_streams.h>

using namespace lem;

#if defined LEM_WINDOWS
OFormatter *lem::mout = NULL;
OFormatter *lem::merr = NULL;
#else
OFormatter *lem::mout = NULL;
OFormatter *lem::merr = NULL;
#endif

