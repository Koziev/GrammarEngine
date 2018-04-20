// -----------------------------------------------------------------------------
// File LEM_COAP.CPP
//
// (c) 2005 by Elijah Koziev     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
//
// Создание глобальных переменных mout и merr - это объекты форматтеров вывода
// на текстовую консоль. При компиляции происходит настройка на целевую OS, в
// частности - используются возможности цветового управления символов (напимер,
// через библиотеку ncurses).
//
// Инициализация текстовой консоли для оконных сред.
// Поддержка потоков вывода на текстовую консоль для Win32.
//
// 03.10.2005 - инициализация потоков консоли перенесена в модуль
//              cp_code_pages.cpp, так как для настройки потоков нужны созданные
//              кодовые страницы.  
// -----------------------------------------------------------------------------
//
// CD->23.10.2000
// LC->20.04.2018
// --------------

#include <lem/config.h>
#include <lem/oformatter.h>
#include <lem/keyboard.h>
#include <lem/console_application.h>

// Standard console streams for common output and for error messages.
lem::OFormatter* lem::mout = nullptr;
lem::OFormatter* lem::merr = nullptr;

// ****************************************
// Форматтер для ввода данных с клавиатуры
// ****************************************
lem::IKbdFormatter* lem::mkey = nullptr;
