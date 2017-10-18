// -----------------------------------------------------------------------------
// File YMAP.CPP 
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
// 
// Licensed under the terms of GNU Lesser GPL
//
// Content:
// YMAP program - dictionary dump utility.
//
// Утилита администрирования Словаря: распечатка разнообразной
// служебной информации о скомпилированном словаре. Результат - текстовый
// файл - помогает анализировать структуру словаря.
//
// Программа загружает информацию из бинарного образа словаря (должен быть
// файл dictionary.xml в текущей папке) и создает текстовые (utf8) файлы.
//
// 19.05.2006 - добавлена возможность указывать в командной строке имя файла
//              словаря (по умолчанию ищется файл diction.bin в текущем каталоге)
// 20.04.2007 - добавлена опция -outdir=DDDD для указания каталога для записи
//              листингов.
// 27.05.2007 - загрузка словаря через файл dictionary.xml (каталог модулей).
// 28.05.2007 - опция -decompile выводит в файл lexicon.sol с исходным кодом
//              лексикона в виде, пригодном для компиляции в ygres.
// 13.06.2007 - при попытке обработать LITE версию словаря выдается нормальная
//              диагностика, раньше программа просто валилась при листинге
//              словаря.
// 27.07.2008 - добавлена опция -export для экспорта описания словарных статей
//              лексикона в формате XML для утилиты xml2sol.
// 29.07.2008 - добавлена опция -regenerate_links для формирования списка
//              записей для добавления в тезаурус. 
// 05.08.2008 - добавлена генерация списка инфинитивов без связанных с ними
//              глаголов.
// 10.08.2008 - добавлена генерация списка причастий без связанных с ними
//              инфинитивов.
// 03.09.2008 - добавлена генерация списка прилагательных-кандидатов в
//              причастия, с окончаниями на ШИЙ/ЩИЙ/ШИЙСЯ/ЩИЙСЯ/ННЫЙ, не
//              имеющих тэга ПРИЧАСТИЕ
// 21.01.2009 - реализован экспорт в формат SQL (опция -sql параметры)
// 05.03.2009 - программа переименована в DECOMPILER
// 24.12.2009 - убрана поддержка опции -regenerate_links
// 26.03.2010 - поправлен баг - в XML файлы выгрузки вставлялся BOM
// 08.06.2011 - выгружаются правила морфологического и синтаксического анализа,
//              трансформации и синтеза.
// -----------------------------------------------------------------------------
//
// CD->12.04.2003
// LC->02.07.2012
// --------------

#include <lem/console_application.h>
#include <lem/logfile.h>
#include <lem/shell.h>
#include <lem/startup.h>
#include <lem/system_config.h>
#include <lem/console_streams.h>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/version.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntryEnumerator.h>

using namespace lem;
using namespace lem::Char_Stream;
using namespace Solarix;

#define OK { mout->printf("%vfEOK%vn"); mout->flush(); }

struct XML_ExportParameters
{
 int max_entry_count;

 XML_ExportParameters()
 {
  max_entry_count = lem::int_max;
 }

 void Parse( const char * str )
 {
  lem::MCollect<lem::CString> tokens;
  lem::parse( lem::FString(str), tokens, false );

  for( lem::Container::size_type i=0; i<tokens.size(); ++i )
   {
    const lem::CString &token = tokens[i];

    if( lem::is_int(tokens[i].c_str()) )
     {
      max_entry_count = lem::to_int(tokens[i]);
     }
    else
     {
      lem::UFString msg = format_str( L"Invalid option %s in xml export options string", to_unicode(token).c_str() );
      throw lem::E_BaseException(msg);
     }
   }
  
  return;
 }
};

class Ymap : public Base_Application
{
 public:
  lem::zbool dump; // различная статобработка содержимого словаря
  lem::zbool decompile; // экспорт в формат для утилиты ygres

  lem::zbool export_xml; // экспорт в XML формат для утилиты import
  XML_ExportParameters xml_params;

  lem::zbool export_sql; // экспортировать в SQL
  SQL_Production sql_version; // параметры версии сервера СУБД для экспорта
 
 public:
  Ymap(void) : Base_Application(), sql_version("") {}

  void PrintBanner( OFormatter &txt, bool versbose=false );
  void Print_Heap( OFormatter &txt );
  void Echo( OFormatter &txt );
  void Help(void);
  void Go( const lem::Path &dict, const lem::Path &outdir );
};




void Ymap::PrintBanner( OFormatter &txt, bool verbose )
{
 txt.printf( "%vfEDecompiler%vn version %vfF%s%vn\n", sol_get_version().c_str() );
 Print_Project_Info(txt);
 txt.eol();
 return;
}


// ************************************
// Вывод короткой справки о программе.
// ************************************
void Ymap::Help(void)
{
 mout->printf(
              "\nSome default values for options are listed in %vfAdecompiler.ini%vn file.\n"
              "For example, the messaging language is defined by variable %vfElang%vn in section %vfEui%vn.\n\n"
              "SOLARIS dictionary decompiler: it loads dictionary from binary file\n"
              "%vfFdiction.bin%vn and creates map file %vfFdiction.map%vn, containing a lot of internal\n"
              "information as well as disassembled entries, classes, rules and other\n"
              "structures.\n\n"
              "Usage: %vfEdecompiler%vn %vf8[%vndictionary_filename%vf8]%vn %vf8[%vn-outdir=XXX%vf8]%vn %vf8[%vn-decompile%vf8]%vn\n\n"
             ); 

 exit(1);
}

// **********************************************************
// Печать отметки о времени создания в генерируемых файлах.
// **********************************************************
void Ymap::Print_Heap( OFormatter &txt )
{
 Echo(txt);
 PrintBanner(txt);
 txt.printf( "Created %us\n", timestamp().c_str() );
 return;
}


void Ymap::Echo( OFormatter &txt )
{
 mout->printf( "\nWriting %vfA%us%vn...", txt.GetStream()->GetName().GetUnicode().c_str() );
 mout->flush(); 
 return;
}



void Ymap::Go( const lem::Path &dict, const lem::Path &outdir )
{
 std::auto_ptr<OFormatter> nul_tty( new OFormatter( lem::Path(NULL_DEVICE) ) ); // пустой поток (устройство NUL:)

 lem::Path jpath(outdir);
 jpath.ConcateLeaf(lem::Path("journal"));
 lem::LogFile::Open( jpath ); // файл журнала в указанном каталоге outdir

 PrintBanner( *lem::LogFile::logfile, true );
 lem::System_Config::PrintInfo( *lem::LogFile::logfile );

 // Загружаем модули словаря
 std::auto_ptr<Solarix::Dictionary> sol_id( new Solarix::Dictionary( &*nul_tty, merr ) );

 mout->printf( "Loading dictionary %vfF%us%vn...", dict.GetUnicode().c_str() );
 mout->flush();

 Load_Options opt;

 opt.load_semnet = true;
 opt.ngrams = true;

 bool ok=false;

 try
  {
   ok = sol_id->LoadModules( dict, opt );
  }
 catch(...)
  {
   ok = false;
  }

 if( !ok )
  {
   mout->printf( "\n\nERROR!\nIncompatible dictionary version\n" );
   lem::Process::Exit();
  }

 mout->printf( "%vfE%F$3d%vn entries %vfAOK%vn\n", sol_id->GetSynGram().GetnEntry() );
 CheckMemory();

 if( export_sql )
  {
   // Выгружаем основные модули словаря в SQL формат.

   sql_version.outdir = outdir;

   lem::Path exp( outdir );
   exp.ConcateLeaf( L"dictionary.sql" );

   lem::Path exp2( outdir );
   exp2.ConcateLeaf( L"dictionary-alters.sql" );

   if( sql_version.IsAscii() )
    {
     lem::OFormatter exp_file(exp);
     lem::OFormatter alters_file(exp2);
     sol_id->Save_SQL( exp_file, alters_file, sql_version );
    }
   else
    {
     // UTF8
     lem::OUFormatter exp_file(exp,sql_version.WriteBOM());
     lem::OUFormatter alters_file(exp2,sql_version.WriteBOM());
     sol_id->Save_SQL( exp_file, alters_file, sql_version );
    }


   // В отдельный файл - правила морфологического и синтаксического анализа
   lem::Path exp_rules( outdir );
   exp_rules.ConcateLeaf( L"rules.sql" );

   lem::Path exp2_rules( outdir );
   exp2_rules.ConcateLeaf( L"rules-alters.sql" );

   if( sql_version.IsAscii() )
    {
     lem::OFormatter exp_file(exp_rules);
     lem::OFormatter alters_file(exp2_rules);
     sol_id->SaveRules_SQL( exp_file, alters_file, sql_version );
    }
   else
    {
     // UTF8
     lem::OUFormatter exp_file(exp_rules,sql_version.WriteBOM());
     lem::OUFormatter alters_file(exp2_rules,sql_version.WriteBOM());
     sol_id->SaveRules_SQL( exp_file, alters_file, sql_version );
    }

   if( sql_version.lemmatizator )
    {
     // В отдельный файл выгружаем таблицы лемматизатора.
     lem::Path exp( outdir );
     exp.ConcateLeaf( L"lemmatizator.sql" );

     lem::Path exp2( outdir );
     exp2.ConcateLeaf( L"lemmatizator-alters.sql" );

     if( sql_version.IsAscii() )
      {
       lem::OFormatter exp_file(exp);
       lem::OFormatter alters_file(exp2);
       sol_id->GetSynGram().SaveLemmatizatorSQL( exp_file, alters_file, sql_version );
      }
     else
      {
       // UTF8
       lem::OUFormatter exp_file(exp,sql_version.WriteBOM());
       lem::OUFormatter alters_file(exp,sql_version.WriteBOM());
       sol_id->GetSynGram().SaveLemmatizatorSQL( exp_file, alters_file, sql_version );
      }
    }


   // скрипт для PREFIX ENTRY SEARCHER
   lem::Path exp_pes( outdir );
   exp_pes.ConcateLeaf( L"prefix_entry_searcher.sql" );

   lem::Ptr<PrefixEntrySearcher> pes( sol_id->GetPrefixEntrySearcher() );
   if( pes.NotNull() )
    pes->Save_SQL( exp_pes, sql_version );
  }



 mout->printf( "Decompiling and analyzing the dictionary..." ); mout->flush();

 if( export_xml )
  {
   lem::Path p(outdir);
   p.ConcateLeaf( lem::Path("lexicon.xml") );
   OUFormatter xml( p, false );
   Echo(xml); 
   lem::Path p2(outdir);
   p2.ConcateLeaf( lem::Path("lexicon.xsd") );
   OFormatter xsd(p2);
   sol_id->GetSynGram().Dump_XML( xml, xsd, xml_params.max_entry_count );
   OK; 

   // Чтобы не получился один XML файл гигантского размера, неудобный для
   // обработки утилитой xml2sol, разобъем список статей на блоки.
   const int nentry = CastSizeToInt(sol_id->GetSynGram().GetEntries().CountEntries(ANY_STATE,ANY_STATE));
   const int blocksize = 1000;
   const int nblock = (nentry/blocksize) + ( (nentry%blocksize)==0 ? 0 : 1 );

   lem::Path pe(outdir);
   pe.ConcateLeaf(L"export");
   lem::OUFormatter export_list(pe);

   lem::Ptr<WordEntryEnumerator> wenum( sol_id->GetSynGram().GetEntries().ListEntries() );
 
   int ientry=0;
   for( int iblock=0; iblock<nblock && ientry<nentry; iblock++ )
    {
     lem::UFString filename( lem::format_str(L"export_%d.xml",iblock) );
     export_list.printf( "%us\n", filename.c_str() );
     
     lem::Path p(outdir);
     p.ConcateLeaf(lem::Path(filename));
     lem::OUFormatter xml(p,false);
     xml.printf( "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<dataroot>\n" );

     for( int i=0; i<blocksize && wenum->Fetch(); i++, ientry++ )
      {
       try
        {
         const Solarix::SG_Entry &e = wenum->GetItem();

         if( !e.GetName().empty() )
          {
           e.SaveXML(xml,sol_id->GetSynGram());
           xml.eol();
          }
        }
       catch( const lem::E_BaseException &e )
        {
         lem::mout->printf( "Error occured when exporting entry #%d: %us\n", ientry, e.what() );
         lem::Process::Exit(1); 
        }
       catch( const std::exception &e )
        {
         lem::mout->printf( "Error occured when exporting entry #%d: %s\n", ientry, e.what() );
         lem::Process::Exit(1); 
        }
       catch(...)
        {
         lem::mout->printf( "Error occured when exporting entry #%d\n", ientry );
         lem::Process::Exit(1); 
        }
      } 

     xml.printf( "</dataroot>\n" );
     lem::mout->dot();
    }
  }

 // Text file for dictionary map
 if( dump )
  {
   lem::Path p(outdir);
   p.ConcateLeaf( lem::Path("alphabet.map") );
   OUFormatter map( p );
   Print_Heap(map);
   sol_id->MapAlphabet( map );
   OK;
  }

 if( dump )
  {
   lem::Path p(outdir);
   p.ConcateLeaf( lem::Path("lexicon.map") );
   OUFormatter map( p );
   Print_Heap(map);
   sol_id->MapLexicon( map );
   OK;
  }

 if( decompile )
  {
   lem::Path p(outdir);
   p.ConcateLeaf( lem::Path("lexicon.sol") );
   OUFormatter txt( p );
   txt.printf( "/*\n" );
   Print_Heap(txt);
   txt.printf( "*/\n\n" );
   sol_id->GetSynGram().SaveTxt( txt );
   OK;
  }

 if( dump )
  {
   lem::Path p(outdir);
   p.ConcateLeaf( lem::Path("grammar.map") );
   OUFormatter map( p );
   Print_Heap(map);
   sol_id->MapTransformer( map );
   OK;
  }

 mout->printf( "\n%vfAAll done.%vn\n" );
 return;
}


int main( int argc, char *argv[] )
{
 lem::LemInit initer;
 Ymap app;

 app.Read_Ini( lem::Path("ymap.ini") );

 app.PrintBanner(*mout);

 if(
    argc==2 && (
                !strcmp(argv[1]+1,"help") ||
                !strcmp(argv[1]+1,"?") ||
                !strcmp(argv[1]+1,"h") ||
                !strcmp(argv[1]+1,"-version")
               )
   )
  app.Help();

 // По умолчанию файл словаря ищем в текущем каталоге
 lem::Path dict("dictionary.xml");

 // А результаты декомпиляции сохраняем в текущем каталоге
 lem::Path outdir;

 app.dump = true;

 try
  {
   for( int i=1; i<argc; i++ )
    {
     if( argv[i][0]=='-' || argv[i][0]=='/' )
      {
       if( memcmp( argv[i]+1, "outdir=", 7 )==0 )
        {
         FString s(argv[i]+8);
         s.strip_apostrophes();
         outdir = lem::Path( s );
        }
       else if( lem_eq( argv[i], "-decompile" ) )
        {
         app.dump      = false;
         app.decompile = true;
        } 
       else if( lem_eq( argv[i], "-dump" ) )
        {
         app.dump = true;
        }
       else if( lem_eq( argv[i], "-export" ) || lem_eq( argv[i], "-xml" ) )
        {
         app.dump     = false;
         app.decompile = false;
         app.export_xml = true;
         app.xml_params.Parse( argv[i+1] );
         i++;
        }
       else if( lem_eq( argv[i], "-sql" ) )
        {
         app.dump             = false;
         app.decompile        = false;
         app.export_xml        = false;
         app.export_sql       = true;
         app.sql_version = SQL_Production( argv[i+1] );
         i++; 
        }
      }
     else
      {
       dict = lem::Path(argv[i]);
      }
    }
  }
 LEM_CATCH;

 if( !dict.DoesExist() )
  {
   dict = lem::Shell::AskFilename( true, L"Enter dictionary filename (dictionary.xml): " );
  }

 try
  {
   app.Go(dict,outdir);
  }
 LEM_CATCH;

 return 0;
}
