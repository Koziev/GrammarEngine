// -----------------------------------------------------------------------------
// File USER_INTERFACE.H
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// Content:
// Различные параметры среды взаимодействия с пользователем (кодовая страница,
// язык).
// Класс Language - спецификация языка для общения с пользователем.
// Работа с локализованными ресурсами.
//
// 06.02.2006 - упрощена схема хранения ресурсов (числа вместо строк для
//              идентификации) - для экономии памяти и ускорения поиска
// -----------------------------------------------------------------------------
//
// CD->22.11.2004
// LC->08.09.2009
// --------------

#ifndef LEM_USER_INTERFACE__H
#define LEM_USER_INTERFACE__H
#pragma once

 #include <lem/config.h>

 #if defined LEM_MFC
  #include <afxwin.h>
 #endif

 #include <string>
 #include <map>

 #include <boost/shared_ptr.hpp>

 #include <lem/base_container.h>
 #include <lem/fstring.h>
 #include <lem/zeroed.h>

 namespace lem
 {
  class OFormatter;

  namespace Char_Stream
  {
   class WideStream;
  }

  class CodeConverter;

  namespace UI
  {
   using std::string;
   using lem::CodeConverter;

   extern const char RUSSIAN_NAME[3];
   extern const char ENGLISH_NAME[3];
   extern const char FRENCH_NAME[3];
   extern const char SPANISH_NAME[3];
   extern const char PORTUGUESE_NAME[3];
   extern const char ITALIAN_NAME[3];
   extern const char POLISH_NAME[3];
   extern const char GERMAN_NAME[3];

   class User_Interface
   {
    private:
     std::string curr_lang; // Текущий язык - основной для платформы и
                            // текущего сеанса. 2-х буквенное сокращение по стандарту ISO.

     boost::shared_ptr<CodeConverter> tty_cp;     // кодовая страница для консоли
     boost::shared_ptr<CodeConverter> session_cp; // кодовая страница для пользователя
     boost::shared_ptr<CodeConverter> src_cp;     // кодовая страница для сообщений в исходных текстах

     FString date_fmt;  // короткий формат даты 
     FString ldate_fmt; // длинный формат даты 
     FString time_fmt;  // формат времени

     UFString umonth[12]; // обозначения месяцев - краткие
     FString month[12]; 

     UFString umonth1[12]; // обозначения месяцев - полные
     FString month1[12]; 

     void PresetFormats(void);
     void PresetMonthNames(void);
     void PresetAsciiMonthNames(void);
     
     bool Eq( const char *Code ) const;

    public:
     User_Interface(void);

     void AllCodeConvertersInitialized(void);

     inline const std::string& GetCurrLang(void) const { return curr_lang; }  
     void SetCurrLang( const char *Lang );  
     
     inline bool IsRussian(void) const { return Eq( RUSSIAN_NAME ); }
     inline bool IsEnglish(void) const { return Eq( ENGLISH_NAME ); }
     inline bool IsFrench(void)  const { return Eq( FRENCH_NAME );  }
     inline bool IsSpanish(void)  const { return Eq( SPANISH_NAME );  }
     inline bool IsPortuguese(void)  const { return Eq( PORTUGUESE_NAME );  }
     inline bool IsItalian(void)  const { return Eq( ITALIAN_NAME );  }
     inline bool IsPolish(void)  const { return Eq( POLISH_NAME );  }
     inline bool IsGerman(void)  const { return Eq( GERMAN_NAME );  }

     inline const CodeConverter& GetTtyCp(void) const { return *tty_cp; }
     void SetTtyCp( const boost::shared_ptr<CodeConverter> &cp );

     inline const CodeConverter& GetSessionCp(void) const { return *session_cp; }
     void SetSessionCp( const boost::shared_ptr<CodeConverter> &cp );

     inline const CodeConverter& GetSrcCp(void) const { return *tty_cp; }
     void SetSrcCp( const boost::shared_ptr<CodeConverter> &cp );

     inline const lem::FString& GetDateFmt(void) const { return date_fmt; }
     inline const lem::FString& GetTimeFmt(void) const { return time_fmt; }

     inline void SetDateFmt( const char *s ) { date_fmt=s; }
     inline void SetTimeFmt( const char *s ) { time_fmt=s; }

     inline const UFString& GetMonthW( int imonth ) const
     { LEM_CHECKIT_Z(imonth>=0 && imonth<12); return umonth[imonth]; }

     inline const FString& GetMonthA( int imonth ) const
     { LEM_CHECKIT_Z(imonth>=0 && imonth<12); return month[imonth]; }

     inline const UFString& GetMonthFullW( int imonth ) const
     { LEM_CHECKIT_Z(imonth>=0 && imonth<12); return umonth1[imonth]; }

     inline const FString& GetMonthFullA( int imonth ) const
     { LEM_CHECKIT_Z(imonth>=0 && imonth<12); return month1[imonth]; }

     int FindMonth( const FString &m ) const;
     int FindMonth( const UFString &m ) const;

     int FindMonth( const char *m ) const;
     int FindMonth( const wchar_t *m ) const;

     static void AvailableLocales( lem::OFormatter &out );

     // Show some brief info about current UI settings, eg. locale.
     void PrintInfo( OFormatter &dst ) const;

     static lem::FString GetEncodingNameForLang( int langid );
     static const CodeConverter* GetEncodingForLang( int langid );
   };


   extern User_Interface& get_UI(void);

   class Resource_List;
   class Resource
   {
    private:
     friend class Resource_List;

     int name; // индекс ресурса, по которому на него
               // ссылаются программы

     lem::BaseCollect< std::pair< int /*ilang*/, UFString /*string*/ > > list;

     Resource( const Resource& x );
     void operator=( const Resource& x );

    public:
     Resource(void) {}

     // Возвращает локализацию строки для указанного языка
     // (индекс языка в списке каталога ресурсов)
     const UFString& Get_String( int ilang, int idefault_lang=UNKNOWN ) const;
   };


   class Resource_List
   {
    private:
     lem::BaseCollect<Resource*> list;
     std::map< int, Resource* > iname_2_res; // для быстрого поиска ресурса по индексу

     std::vector<std::string> langs; // список языков, для которых есть локализация

    public:
     lem::zbool load_all_languages; // all languages localization are loaded,
                                    // otherwise only the current language 
                                    // resources are loaded. 

    public:
     Resource_List(void);
     ~Resource_List(void);

     // Загрузка файла локализации
     void LoadTxt( const lem::Path &filename );
     void LoadTxt( lem::Char_Stream::WideStream &txt );

     // Поиск строки ресурса с именем name
     const UFString& Find( int name ) const;

     // Поиск строки ресурса с именем name и перекодировка в текущую кодовую страницу
     const FString FindA( int name ) const;

     inline const std::vector< std::string >& Localizations(void) const { return langs; }

     // Поиск числового идентификатора для языка
     int FindLang( const std::string &lang, const char *default_lang="en" ) const;
   };

  } // namespace UI

 } // namespace lem


#endif
