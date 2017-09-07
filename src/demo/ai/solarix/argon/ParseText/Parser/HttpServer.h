#ifndef PARSE_HTTP_SERVER__H
#define PARSE_HTTP_SERVER__H
#pragma once

#if defined HTTP_PARSER_SERVICE

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
// ----------------------------------------------------------------------------
//
// CD->22.03.2007
// LC->07.01.2016
// --------------

#include <lem/config.h>
#include <lem/afstring.h>
#include <lem/ufstring.h>
#include <lem/httpd.h>

class ParserEngineBase;

class ParserHttpServer : public lem::HttpServer  
{ 
 public:
  enum { DefaultPort=10973 }; // порт поискового сервера по умолчанию

  lem::UFString page_title; // заголовок страницы результатов поиска

 protected:
  ParserEngineBase *parser;

  virtual bool GenerateHtml(
                            const char * url,
                            const char * query,
                            lem::UFString &outdata,
                            char **content_type
                           );

  void ShowQueryPage( const lem::FString &url, lem::UFString &out );
  void ShowResultsPage( const lem::FString &url, lem::UFString &out, char ** content_type );
  void ShowInfoPage( const lem::FString &url, lem::UFString &out );

 public:
  ParserHttpServer( ParserEngineBase *eng );
};

#endif // #if defined HTTP_PARSER_SERVICE

#endif
