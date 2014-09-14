#ifndef SE_REPORT__H
#define SE_REPORT__H
#pragma once

 #include <lem/solarix/se_word_searcher.h>

 namespace Solarix
 {
  namespace Search_Engine
  { 
   class Crawler;

  #if defined FAIND_REPORTS
  // **************************************************
  // Описатель для создаваемого отчета
  // **************************************************
  class Base_Report : public boost::noncopyable
  {
   protected:
    lem::OFormatter *Get_Stream(void) const;
    void Print_Footnote( lem::OFormatter *stream ) const;

   public:
    lem::UFString name;     // внутренее имя (тип отчета)
    lem::UFString format;   // формат отчета
    lem::UFString filename; // имя создаваемого файла   

    Base_Report(void) {};
 
    virtual ~Base_Report(void) {}

    // метод вызывается после загрузки содержимого очередного файла
    virtual void Process( const Solarix::Search_Engine::Text &text ) {}

    // метод вызывается для распечатки отчета
    virtual void Do( const Crawler &crawler )=0;
  };
  #endif

  #if defined FAIND_REPORTS && defined FAIND_WEB
  // **************************************************
  // Отчет о 'битых' ссылках на просмотренных сайтах
  // **************************************************
  class Broken_HRef_Report : public Base_Report
  {
   private:
    void Do_Html( const Crawler &crawler );

   public:
    Broken_HRef_Report(void) {}

    virtual void Do( const Crawler &crawler );
  };
  #endif

  #if defined FAIND_REPORTS
  // **************************************************
  // Отчет о структуре просмотренных сайтов
  // **************************************************
  class HRef_Report : public Base_Report
  {
   private:
    void Do_Html( const Crawler &crawler );

   public:
    HRef_Report(void) {}

    virtual void Do( const Crawler &crawler );
  };
  #endif

  #if defined FAIND_REPORTS
  // **************************************************
  // ОТЧЕТ: статистика слов по обработанным текстам
  // **************************************************
  class Words_Stat_Report : public Base_Report
  {
   private:
    Word_Searcher words; // словарь накопленных слов
    std::map< int /*iword*/, int /*freq*/ > word_freq; // частоты слов
    int n_tot;  // сколько слов обработано
    int n_docs; // сколько документов обработано

    // Подготовленный отсортированный список
    lem::MCollect< std::pair<int,int> > sorted;

    void Do_Html( const Crawler &crawler );

   public:
    Words_Stat_Report(void);

    // метод вызывается после загрузки содержимого очередного файла
    virtual void Process( const Solarix::Search_Engine::Text &text );

    // Генерация отчета (в ранее назначенный файл).
    virtual void Do( const Crawler &crawler );
  };
  #endif

  #if defined FAIND_REPORTS
  class Base_Report_Maker
  {
   public:
    Base_Report_Maker(void) {}

    virtual Base_Report* New(void) const =0;
  };

  template < class T >
  class Report_Maker : public Base_Report_Maker
  {
   public:
    Report_Maker(void) {}
  
    virtual Base_Report* New(void) const { return static_cast<Base_Report*>( new T() ); } 
  };
  #endif
  
  #if defined FAIND_REPORTS
  class Report_Factory
  {
   private:
    typedef std::map< lem::UFString /*name*/, Base_Report_Maker* > map_type;
    map_type list;

   public:
    Report_Factory(void) {}
    virtual ~Report_Factory(void);

    virtual void Add( const lem::UFString &name, Base_Report_Maker *maker );
    virtual Base_Report* Find( const lem::UFString &name ) const;
  };
  #endif

 }
}

#endif
