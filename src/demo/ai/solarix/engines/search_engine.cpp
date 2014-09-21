// -----------------------------------------------------------------------------
// File SEARCH_ENGINE.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project   http://www.solarix.ru
// SEARCH ENGINE Core
//
// Win32 DLL интерфейс к поисковой машине.
// Old-fashioned Win32 DLL interface to the search engine.
//
// 24.01.2006 - API переделан, введен хэндл для создаваемого объекта ГМ
//
// 24.01.2006 - API fuctions use wchar_t strings.
//
// 29.05.2006 - в вызовах API введен параметр 'HFAIND' - хэндл созданного
//              поискового движка.
//
// 06.08.2006 - изменен API - callback функция "начало обработки каталога" в
//              качестве аргумента получает UNICODE имя каталога
//
// 20.08.2006 - добавлена sol_Translate_To_Noun для приведения слов к форме
//              существительных.
//
// 25.08.2006 - добавлена процедура sol_Project_Word для получения всех
//              проекций слова на лексикон, а также группа процедур для работы
//              с получившимся списком координат проекций. 
//
// 30.08.2006 - добавлены процедуры для синтаксического анализа и работы с 
//              получающейся пачкой решений. 
//
// 08.10.2006 - в версию Pro добавлены процедуры API для работы с RegexEx -
//              расширенными регулярными выражениями.
//
// 15.10.2006 - введен низкоуровневый API для работы с индексатором.
//
// 21.11.2006 - подключен стеммер для нормализации.
//
// 25.11.2006 - изменена sol_GetError - возвращает wchar_t строку описания
//              ошибки. 
//
// 28.11.2006 - введена sol_UnloadDictionary.
//
// 27.09.2011 - добавлен режим ленивой загрузки лексикона.
// 05.03.2012 - если вызван ::Load(...) с указанием несуществующего пути к конфигу словаря,
//              то в поле ошибки сохраняется описание ситуации, а не просто возвращается флаг "ошибка при загрузке"
// -----------------------------------------------------------------------------
//
// CD->01.03.2005
// LC->05.03.2012
// --------------

#include <lem/config.h>

#if defined FAIND_IENGINES || defined DLL_EXPORTS

#include <lem/conversions.h>
#include <lem/ustreams.h>
#include <lem/unicode.h>
#include <lem/solarix/version.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#if defined SOLARIX_SEARCH_ENGINE
#include <lem/solarix/search_engine.h>
#endif
#include <lem/solarix/faind_internal.h>

using namespace lem;
using namespace lem::Char_Stream;
using namespace Solarix;

#if defined SOLARIX_SEARCH_ENGINE
using namespace Solarix::Search_Engine;
#endif


#if defined SOLARIX_SEARCH_ENGINE
Faind_Engine::Faind_Engine( Solarix::Search_Engine::CommandParser *Parser )
#else
Faind_Engine::Faind_Engine(void)
#endif
{
 #if defined SOLARIX_SEARCH_ENGINE
 callback = NULL;
 #endif

 sg = NULL;
 n_lexicon_reserve = 0;

 if( lem::UI::get_UI().IsRussian() )
  DefaultLanguage = RUSSIAN_LANGUAGE;
 else if( lem::UI::get_UI().IsFrench() )
  DefaultLanguage = FRENCH_LANGUAGE;
 else if( lem::UI::get_UI().IsSpanish() )
  DefaultLanguage = SPANISH_LANGUAGE;
 else
  DefaultLanguage = ENGLISH_LANGUAGE;

 #if defined SOLARIX_SEARCH_ENGINE
 dataset_flag = Xml_Dataset;
 html_header_footer = true;
 #endif

 // Подавляем вывод сообщений на консоль
 nul_tty = new OFormatter( Path(NULL_DEVICE) );

 #if defined SOLARIX_SEARCH_ENGINE
 if( Parser==NULL )
  { 
   parser = new Solarix::Search_Engine::CommandParser();
   parser->ini_engine_command->echo.mout.reset(nul_tty);

   // Загружаем локализованные ресурсы.
   try
    {
     lem::Path p("faind.lang");

     if( p.DoesExist() ) 
      parser->LoadResources(p);

     ok = true;
    }
   catch(...)
    {
     ok = false;
    }
  }
 else 
  {
   parser = lem::Ptr<Solarix::Search_Engine::CommandParser>( Parser, null_deleter() );
   ok = true;
  }

 scanning.prefer_cp_list.push_back( &lem::UI::get_UI().GetSessionCp() );
 #else

  #if defined SOLARIX_SYNONYMIZER_ENGINE
  detector = new Solarix::Search_Engine::File_Type_Detector();
  detector->AttachDetectors();
  scanning.prefer_cp_list.push_back( &lem::UI::get_UI().GetSessionCp() );
  #endif

 ok = true;
 #endif

 return;
}

    
void Faind_Engine::PostINI(void)
{
 #if defined SOLARIX_SEARCH_ENGINE

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 crawler = parser->template_crawler;
 detector = crawler->GetFileTypeDetector();

 #endif

 return;
}

Faind_Engine::~Faind_Engine(void)
{
 delete nul_tty;
 return;
}


void Faind_Engine::SetError( const lem::UFString & error_text )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker(&cs_error);
 #endif

 error = error_text;
 return;
}




#if defined SOLARIX_SEARCH_ENGINE
Start_File_Processing_Handler::Start_File_Processing_Handler( Faind_Engine* E )
{
 engine=E;
 cbStartFile   = NULL;
 cbStartFolder = NULL;
 cbSuccess     = NULL;
}


void Start_File_Processing_Handler::Start_File( const wchar_t *filename )
{
 if( cbStartFile )
  cbStartFile(filename);
}


void Start_File_Processing_Handler::Start_Folder( const wchar_t *folder )
{
 if( cbStartFolder )
  cbStartFolder(folder);
}


void Start_File_Processing_Handler::Success(
                                            const wchar_t *filename,
                                            const wchar_t *location,
                                            const wchar_t *tmp
                                           )
{
 if( cbSuccess )
  cbSuccess(filename,location,tmp);
}
#endif

#if defined SOLARIX_SEARCH_ENGINE
bool Faind_Engine::Set_Callback_StartFile( Faind_EngineCallbackProc_StartFile ptr )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 if( !!parser->template_crawler )
  {
   if( !parser->template_crawler->callback )
    {
     // Для поддержания связи с клиентским кодом во время длительных
     // сеансов поиска и индексации в поисковом движке
     parser->template_crawler->callback.reset( new Start_File_Processing_Handler(this) );
    }

   static_cast<Start_File_Processing_Handler*>(&*parser->template_crawler->callback)->cbStartFile = ptr;
   return true;
  }

 return false;
}
#endif

#if defined SOLARIX_SEARCH_ENGINE
bool Faind_Engine::Set_Callback_StartFolder( Faind_EngineCallbackProc_StartFolder ptr )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 if( !!parser->template_crawler )
  {
   if( !parser->template_crawler->callback )
    {
     // Для поддержания связи с клиентским кодом во время длительных
     // сеансов поиска и индексации в поисковом движке
     parser->template_crawler->callback.reset( new Start_File_Processing_Handler(this) );
    }

   static_cast<Start_File_Processing_Handler*>(&*parser->template_crawler->callback)->cbStartFolder = ptr;
   return true;
  }

 return false;
}
#endif

#if defined SOLARIX_SEARCH_ENGINE
bool Faind_Engine::Set_Callback_Success( Faind_EngineCallbackProc_Success ptr )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif

 if( !!parser->template_crawler )
  {
   if( !parser->template_crawler->callback )
    {
     // Для поддержания связи с клиентским кодом во время длительных
     // сеансов поиска и индексации в поисковом движке
     parser->template_crawler->callback.reset( new Start_File_Processing_Handler(this) );
    }

   static_cast<Start_File_Processing_Handler*>(&*parser->template_crawler->callback)->cbSuccess = ptr;
   return true;
  }

 return false;
}
#endif



#if defined SOLARIX_SEARCH_ENGINE
Faind_Executor::Faind_Executor(void) : dump(true)
{ cmd=NULL; result=NULL; }


Faind_Executor::~Faind_Executor(void)
{
 lem_rub_off(cmd);
 lem_rub_off(result);
}


void Faind_Executor::GetResult( char *buffer )
{
 LEM_CHECKIT_Z(buffer!=NULL);

 if( result && !result->empty() )
  {
//   if( !is_unicode )
    lem_strcpy( buffer, result->c_str() );
//   else
//    {
//     lem::UI::get_UI().GetSessionCp().to_ascii( result->c_str(), buffer );
//    }
  }
 else
  {
   buffer[0] = 0;
  } 

 return;
}



void Faind_Executor::GetResult( wchar_t *buffer )
{
 LEM_CHECKIT_Z(buffer!=NULL);

 if( result && !result->empty() )
  {
   char *tmp2 = new char[ result->length()+1 ];   
   lem_strcpy( tmp2, result->c_str() );
   UFString wbuf( lem::from_utf8(tmp2) );
   delete[] tmp2;
   lem::lem_strcpy( buffer, wbuf.c_str() );
  }
 else
  {
   buffer[0] = 0;
  }

 return;
}
#endif




bool Faind_Engine::Load( const wchar_t *DictionaryXml, bool LazyLexicon )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif
 
 lem::zbool loaded_ok;

 Solarix::Dictionary_Config cfg;

 if( n_lexicon_reserve!=0 )
  cfg.ldsize = n_lexicon_reserve;
 
 dict = new Solarix::Dictionary(NULL,NULL,cfg);

 lem::Path p(DictionaryXml);

 if( p.DoesExist() )
  {
   Load_Options opt;

   opt.affix_table     = true;
   opt.seeker          = true;
   opt.load_semnet     = true;
   opt.ngrams          = true;
   opt.lexicon         = !LazyLexicon;

   loaded_ok = dict->LoadModules( p, opt ) ? 1 : 0;

   seeker = dict->seeker;
   sg = &dict->GetSynGram();

   if( !!dict->affix_table )
    { 
     fuzzy = new Solarix::Search_Engine::Fuzzy_Comparator();
     fuzzy->ApplyDictionary( *dict );
    }

   lem::MCollect<int> langs;
   DefaultLanguage = dict->GetLanguages(langs);
  }
 else
  {
   lem::MemFormatter mem;
   mem.printf( "File [%us] does not exist", DictionaryXml );
   SetError(mem.string());
  }

 return loaded_ok;
}

#endif
