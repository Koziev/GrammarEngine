#ifndef LEM_SEARCH_ENGINE_HTTPD__H
#define LEM_SEARCH_ENGINE_HTTPD__H
#pragma once

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
// Веб-сервер для управления поисковой машиной.
// ----------------------------------------------------------------------------
//
// CD->22.03.2007
// LC->28.02.2009
// --------------

#if defined SOLARIX_PREMIUM && defined FAIND_HTTPD

#include <lem/config.h>
#include <lem/afstring.h>
#include <lem/ufstring.h>
#include <lem/httpd.h>

namespace Solarix
{
 namespace Search_Engine
 { 
  class CommandParser;
 
  class FaindHttpServer : public lem::HttpServer  
  { 
   public:
    enum { DefaultPort=10973 }; // порт поискового сервера по умолчанию

    lem::UFString page_title; // заголовок страницы результатов поиска

   protected:
    CommandParser *http_command_parser;

    virtual bool GenerateHtml(
                              const char * url,
                              const char * query,
                              lem::UFString &outdata
                             );

    void ShowCommonLinks( lem::UFString &out );
    void ShowIndexPage( const lem::FString &url, lem::UFString &out );
    void ShowQueryPage( const lem::FString &url, lem::UFString &out );
    void ShowAdminPage( const lem::FString &url, lem::UFString &out );
    void ShowResultsPage( const lem::FString &url, lem::UFString &out );
    void ExecuteCommandPage( const lem::FString &url, lem::UFString &out );
    void ShowInfoPage( const lem::FString &url, lem::UFString &out );

   public:
    FaindHttpServer( CommandParser *eng );
  };

 }
}

#endif

#endif
