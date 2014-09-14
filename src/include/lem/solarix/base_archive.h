// ----------------------------------------------------------------------------
// File BASE_ARCHIVE.H
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
// LEM C++ library  http://www.solarix.ru
// Базовый класс для распаковщиков стандартных архивов.
// ----------------------------------------------------------------------------
//
// CD->22.12.2004
// LC->17.08.2007
// --------------

#ifndef LEM_BASE_ARCHIVE__H
#define LEM_BASE_ARCHIVE__H
#pragma once

#include <lem/streams.h>
#include <lem/path.h>
#include <lem/smart_pointers.h>
#include <lem/solarix/file_factory.h>
#include <lem/solarix/se_plugin_options.h>

namespace lem
{
 namespace Pack
 {
  // ***********************************************************
  // Объект класса (это на самом деле интерфейс!) вызывается
  // для обработки каждого очередного файла в архиве.
  // ***********************************************************
  class Base_File_Processor
  {
   public:
    Base_File_Processor(void) {}

    virtual Solarix::Search_Engine::Detected_Format DoUnpack( const lem::Path& name )=0;
    virtual void FileDone(
                          const lem::Path& name, // имя файла в архиве
                          lem::Stream &buffer // поток с распакованным файлом
                         )=0;
  };

  // *******************************************
  // Базовый класс для распаковщика архивов.
  // *******************************************

  class Base_Archive
  {
   protected:
    boost::shared_ptr<Stream> in; // Входной поток - сам архив.
    lem::MemStream *outfile; // Подготавливаемый к обработке файл из архива

    Base_File_Processor *processor;

    virtual void File_Extracted( const lem::Path &name );

   public:
    Base_Archive(void);
    virtual ~Base_Archive(void);

    virtual bool Open( boost::shared_ptr<Stream> Stream, const Solarix::Search_Engine::PluginOptions *Options );

    // Извлекаем и обрабатываем все файлы из архива
    virtual void Extract_Files( Base_File_Processor &x )=0;

    // Нужно извлечь и обработать единственный указанный файл
    // Возвращается путь к временному файлу, если распаковка не в оперативной памяти.
    virtual const lem::Path Extract_File( const UFString &filename, lem::Pack::Base_File_Processor &x )=0;

    // Если формат архива позволяет, возвращает комментарий для открытого архива.
    virtual void Extract_Commentary( UFString &buffer ) {}
  };

  // **************************************
  // Интерфейс для создания распаковщиков
  // **************************************
  class IUnpackerFactory
  {
   public:
    IUnpackerFactory(void) {}

    virtual Base_Archive* New(void* ptr=NULL) const=0;

    // Умеет ли распаковщик извлекать одиночный файл?
    virtual bool CanExtractSingleFile(void) const { return false; }
  };

 } // namespace Pack

} // namespace lem


#endif
