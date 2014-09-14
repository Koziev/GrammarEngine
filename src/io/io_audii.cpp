// -----------------------------------------------------------------------------
// File IO_AUDII.CPP
//
// Copyright:    Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2000
//
//
// Content:
// Поток обмена данными с виртуальным звуковым устройством.
// ***
// Поддержка звукового ввода в Систему (SOUND INLET).
// -----------------------------------------------------------------------------
//
// CD->28.01.99
// LC->03.12.00
// ------------

#include <lem/config.h>

#if defined SOL_CAA

#if defined SOL_DOS
#include <dos.h>
#include <conio.h>
#endif

#include "lem_dir.h"
#include "lem_bstr.h"

Lem_AUI_Stream::Lem_AUI_Stream(void)
{
 record = NULL;
 return;
}

Lem_AUI_Stream::~Lem_AUI_Stream(void)
{
 lem_rub_off(record);
 lem_remove(snd_tmp_fname);
 return;
}

// *****************************************************************
// Внутренняя процедура для подготовки работы с файлом звукоданных.
// Мы открываем поток для считывания.
// *****************************************************************
void Lem_AUI_Stream::Open(void)
{
 LEM_CHECKIT_Z(record==NULL);
 lem_check_ptr( record = new LemBinaryFile(snd_tmp_fname,true,false) );
 return;
}

// ************************************************************************
// Читаем порцию данных из файла со звукоданными. Если поток еще не
// открыт, то пытаемся это сделать. Внимание! Если файл звукоданных вообще
// не существует на диске, то будет сгенерирована исключительная ситуация.
// ************************************************************************
void Lem_AUI_Stream::read( void *ptr, const size_t size )
{
 if( record==NULL )
  Open();

 LEM_CHECKIT_Z( record!=NULL );
 record->read( ptr, size );

 return;
}

// ******************************************************************
// Работу со звукозаписью на диске закончили, можем спокойно удалять
// временный файл и закрывать поток.
// ******************************************************************
void Lem_AUI_Stream::flush(void)
{
 lem_rub_off(record);
 lem_remove(snd_tmp_fname);
 return;
}

const bool Lem_AUI_Stream::isready(void) const
{
 return lem_does_exist(snd_tmp_fname);
}

const bool Lem_AUI_Stream::eof(void) const
{
 LEM_CHECKIT_Z(record!=NULL);
 return record->eof();
}

void Lem_AUI_Stream::fclose(void)
{
 lem_rub_off(record);
 return;
}

const long Lem_AUI_Stream::fsize(void) const
{
 LEM_CHECKIT_Z(record!=NULL);
 return record->fsize();
}

// ********************************************************************
// Запускаем драйвер звукового ввода. Этот драйвер сформирует дисковый
// временный файл, который затем может быть загружен Системой для
// анализа.
// ********************************************************************
#if defined SOL_DOS
REGISTER_STATIC_STRING(SOL_RECORDER,"dos_rec.exe ");
REGISTER_STATIC_STRING(SOL_WAV_EXT,"wav");
#endif

#if defined(SOL_WINDOWS) && defined(SOL_TUI_PLAIN)
REGISTER_STATIC_STRING(SOL_RECORDER,"dos_rec.exe ");
REGISTER_STATIC_STRING(SOL_WAV_EXT,"wav");
#endif

void Lem_AUI_Stream::DoRecord(void)
{
 #if defined SOL_DOS
 snd_tmp_fname = sol_get_tmp_name(SOL_WAV_EXT);
 const SolFString x=SolFString(SOL_RECORDER)+SolFString(snd_tmp_fname);
 sol_system( x.string() );
 #elif defined(SOL_WINDOWS) && defined(SOL_GUI)
  // ...
 #elif defined(SOL_WINDOWS) && defined(SOL_TUI_PLAIN)
 snd_tmp_fname = sol_get_tmp_name(SOL_WAV_EXT);
 const SolFString x=SolFString(SOL_RECORDER)+SolFString(snd_tmp_fname);
 sol_system( x.string() );
 #else
  // ...
 #endif

 return;
}

void Lem_AUI_Stream::Record_If_Needed( const bool forced )
{
 if(forced)
  DoRecord();

 if( isready() && record==NULL )
  Open();

 return;
}

void Lem_AUI_Stream::write( const void* /*src*/, const size_t /*size*/ )
{
 LEM_STOPIT;
}

void Lem_AUI_Stream::put( const int /*ch*/ )
{
 LEM_STOPIT;
}

#endif // defined SOL_CAA
// --------------------------- End Of File [IO_AUDII.CPP] ----------------------
