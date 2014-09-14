// ----------------------------------------------------------------------------
// File SE_ECHO_OPTIONS.H
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SEARCH ENGINE Core
//
// 27.02.2007 - структура Echo_Options хранит ссылку на менеджер 
//              локализованных текстовых строк для вывода оных движком по
//              необходимости.
// ----------------------------------------------------------------------------
//
// CD->16.04.2006
// LC->12.06.2007
// --------------

#ifndef LEM_ECHO_OPTIONS__H
#define LEM_ECHO_OPTIONS__H
#pragma once

 #if defined FAIND_SIGNALS
 #include <boost/signal.hpp>
 #endif

 #include <lem/oformatter.h>
 #include <lem/user_interface.h>

 namespace Solarix
 {
  namespace Search_Engine
  { 

  // ******************************************************
  // Echoing options. They describe what is to be printed
  // on TTY when a pattern matches.
  // ******************************************************
  struct Echo_Options
  { 
   bool print_filenames;
   bool show_context; // Показывать зафиксированный контекст
   bool verbose; // Verbose mode - more messages when working
   bool show_query; // Print the structure of query pattern on the TTY
   bool internal_browser; // использовать встроенный браузер результатов
   bool print_zone_name; // в результатах показывать имя индекса (мультизоновый поиск) 
   bool print_topic; // в результатах показывать рубрикацию

   boost::shared_ptr<lem::OFormatter> mout; // Поток для вывода на консоль
   boost::shared_ptr<lem::UI::Resource_List> resx; // Локализация сообщений

   #if defined FAIND_SIGNALS
   typedef enum {
                 Recreate_Whole_Assoc,
                 Percentage,
                 Assoc_Created_Ok,
                 Finish_Create_Assoc,
                 Writing_Assoc,
                 Lists_Written,
                 Direct,
                 Start_Proxy_Matrix,
                 Finish_Proxy_Matrix,
                 Searching_Changed_Files, // поиск изменившихся файлов (для updater'ов)
                 Optimizing_Index, // оптимизация индекса для CLucene
                 All_Done 
                } Messages;

   // для вывода сообщений о длительных
   // операциях (например, при завершении индексирования
   // зоны).
   boost::signal2< void, Messages, const wchar_t* /*message text*/> progress;
   #endif

   Echo_Options(void)
   {
    verbose=true;
    print_filenames=false;
    show_context=true;
    show_query=true;
    mout.reset();
    internal_browser = false;
    print_zone_name = false;
    print_topic = false;
   }

   Echo_Options( const Echo_Options &x ) : mout(x.mout), resx(x.resx)
   {
    verbose=x.verbose;
    print_filenames=x.print_filenames;
    show_context=x.show_context;
    show_query=x.show_query;
    internal_browser = x.internal_browser;
    print_zone_name = x.print_zone_name;
    print_topic = x.print_topic;
   }

   void operator=( const Echo_Options &x )
   {
    verbose=x.verbose;
    print_filenames=x.print_filenames;
    show_context=x.show_context;
    show_query=x.show_query;
    internal_browser = x.internal_browser;
    print_zone_name=x.print_zone_name;
    print_topic = x.print_topic;
    mout = x.mout;
    resx = x.resx;
   }
  };


 } // namespace Search_Engine
 } // namespace Solarix

#endif
