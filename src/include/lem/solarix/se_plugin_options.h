#ifndef PLUGIN_OPTIONS__H
#define PLUGIN_OPTIONS__H
#pragma once

 namespace Solarix
 {
  namespace Search_Engine
  {
   // Флаги для поля PluginOptions::flags
   const int PLUGOPT_OCR = 0x00000001; // включать OCR
  
   // **********************************************************************
   // Структура для передачи различных параметров в плагины для распаковки
   // и парсинга файлов.
   // **********************************************************************
   struct PluginOptions
   {
    unsigned short int_count; // кол-во параметров целочисленного типа
    unsigned short str_count; // кол-во параметров строкового типа
    unsigned short flags;     // общие флаги формата (для расширяемости)
 
    PluginOptions(void)
    { clear(); }
 
    void clear(void) { int_count = str_count = flags = 0; }
   };
  }
 }

#endif
