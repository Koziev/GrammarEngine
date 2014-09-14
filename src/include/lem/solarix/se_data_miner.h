#if defined FAIND_DATAMINE && !defined SE_DATA_MINER__H
#define SE_DATA_MINER__H
#pragma once

 #include <map>
 #include <lem/containers.h>
 #include <lem/ufstring.h>
 #include <lem/solarix/se_indexer_types.h>
 #include <lem/solarix/file_location.h>
 #include <lem/solarix/sg_autom.h>
 //#include <lem/solarix/ngrams_collector.h>

 namespace Solarix
 {
  class LexemDictionary;

  namespace Search_Engine
  { 
  // *********************************************************** 
  // Алгоритмы для выявления темы документов (авторубрификации),
  // разнообразной статистической обработки документов.
  // ***********************************************************

  class Crawler;
  class Base_File_Reader;
  class Fix_Context;
  class Word_Searcher;

  // ************************************************************
  // Базовый класс для выполнения разной обработки документов.
  // ************************************************************
  class Base_DataMiner
  {
   protected:
    lem::Path outdir; // каталог для сохранения файлов с отчетами

    // При записи кумулятивных отчетов (для всей совокупности обработанных
    // документов) удобно сформировать еще один файл - перечень созданных
    // файлов-отчетов с описанием информации в них. Тогда GUI фронтэнд может
    // показать пользователю этот "каталог" с предложением просматривать 
    // нужные файлы.
    lem::Collect< std::pair< lem::Path, lem::UFString > > report_files;

   public:
    Base_DataMiner(void);
    virtual ~Base_DataMiner(void);

    // Поступил очередной документ для обработки.
    virtual void Do( 
                    Crawler &engine,
                    const File_Location &filename,
                    Base_File_Reader *reader,
                    lem::MCollect<Fix_Context*> &contexts
                   )=0; 

    // Вывод финальной статистики по результатам обработки.
    virtual void Report( Crawler &engine ); 

    // Фабрика для создания объекта по его строковому имени
    static Base_DataMiner* Create( const lem::UFString& name, const lem::UFString &arg );

    // Для работы модуля нужен загруженный словарь.
    virtual bool DoesNeedDictionary(void) const;

    // Для работы модуля нужен загруженный тезаурус.
    virtual bool DoesNeedThesaurus(void) const;

    // Для работы модуля нужна загруженная база рубрикатораю
    virtual bool DoesNeedClassifier(void) const;
  };


/*
  // *****************************************************************  
  // Подмножество обработчиков текстов: различные алгоритмы выявления
  // темы документы (рубрикация). Базовый класс.
  // *****************************************************************  
  class DM_Topic_Base : public Base_DataMiner
  {
   protected:
    typedef enum { All, English, Russian, French, German, Italian, Spanish } Language;
    Language language;

   private:
    int n_to_list;
    lem::zbool translate_to_noun; // приводить слова к существительным
    lem::zbool normalize; // нормализовать частоты слов
    lem::zbool ngrams; // учитывать частоты N-грамм

    void NormalizeFrequencies(
                              Crawler &engine,
                              std::map< Index_Entry, float > &word_freq,
                              const Word_Searcher &words 
                             );

   protected:
    virtual void ProcessUnsorted(
                                 Crawler &engine,
                                 const File_Location &filename,
                                 lem::MCollect<Fix_Context*> &contexts,
                                 const std::map< Index_Entry, float > &word_freq,
                                 const Word_Searcher &words,
                                 const Solarix::NGramsCollector & ngrams_collector
                                );

    virtual void ProcessSorted(
                               Crawler &engine,
                               const File_Location &filename,
                               lem::MCollect<Fix_Context*> &contexts,
                               const std::map< Index_Entry, float> &word_freq,
                               const lem::MCollect< std::pair<Index_Entry,float> > &sorted,
                               const Word_Searcher &words,
                               const Solarix::NGramsCollector & ngrams_collector
                              ) {}

   public:
    DM_Topic_Base( const lem::UFString &arg );

    virtual void Do( 
                    Crawler &engine,
                    const Solarix::Search_Engine::File_Location &filename,
                    Solarix::Search_Engine::Base_File_Reader *reader,
                    lem::MCollect<Fix_Context*> &contexts
                   ); 


   virtual bool DoesNeedDictionary(void) const { return translate_to_noun; }
   virtual bool DoesNeedThesaurus(void) const { return translate_to_noun; }
  };


  // **********************************************************************
  // Определитель темы документа по заранее обученной базе авторубрикатора.
  // **********************************************************************
  class DM_Topic_Real : public DM_Topic_Base
  {
   private:
    lem::zbool analyzer_mode; // режим вывода для анализатор документов - частоты слов
                              // для файлов печатаются в XML файле, для каждого обработанного
                              // документа - свой вектор частот. 

    lem::Path outfile;
    lem::Ptr<lem::OUFormatter> xml;
    float min_topic_rel; // минимальная относительная достоверносить возвращаемых рубрик

    int boost_monograms, boost_ngrams; // коэффициенты для повышения/уменьшения влияния отдельных
                                       // слов и N-грамм на процесс классификации.


   protected:
    virtual void ProcessUnsorted(
                                 Crawler &engine,
                                 const File_Location &filename,
                                 lem::MCollect<Fix_Context*> &contexts,
                                 const std::map< Index_Entry, float> &word_freq,
                                 const Word_Searcher &words,
                                 const NGramsCollector & ngrams_collector
                                );

   public:
    DM_Topic_Real( const lem::UFString &arg );

    virtual bool DoesNeedClassifier(void) const;
    virtual bool DoesNeedDictionary(void) const;
    virtual void Report( Crawler &engine );
  };


  // ***********************************************************
  // Определитель темы документа по наиболее частым словам.
  // Накопление и печать частотной статистики по встречаемости
  // слов в документах.
  // ***********************************************************
  class DM_Topic_Top_Frequent : public DM_Topic_Base
  {
   private:
    int n_to_list;           // сколько самых частых слов печатать 
    lem::zbool filter_nouns; // только существительные
    lem::zbool accumulate;   // подбивать статистику для ВСЕХ обработанных файлов
    lem::zbool analyzer_mode; // режим вывода для анализатор документов - частоты слов
                              // для файлов печатаются в XML файле, для каждого обработанного
                              // документа - свой вектор частот. 

    std::auto_ptr<Word_Searcher> total_words; // накопленный справочник слов
    std::map< Index_Entry, float> total_word_freq; // накапливаемая по всем док-ам статистика

    // для режима анализатора документов
    lem::Path outfile;
    typedef lem::PtrCollect< std::pair<lem::UFString,float> > Spectrum;
    lem::PtrCollect< lem::Path > docs;
    lem::PtrCollect< Spectrum >  spectra;
  
   protected:
    virtual void ProcessSorted(
                               Crawler &engine,
                               const File_Location &filename,
                               lem::MCollect<Fix_Context*> &contexts,
                               const std::map< Index_Entry, float> &word_freq,
                               const lem::MCollect< std::pair<Index_Entry,float> > &sorted,
                               const Word_Searcher &words,
                               const NGramsCollector & ngrams_collector
                              );

   public:
    DM_Topic_Top_Frequent( const lem::UFString &arg );

    virtual bool DoesNeedDictionary(void) const;

    virtual void Report( Crawler &engine ); 
  };



 namespace Empir
 {
  class WordProcessor;
  #if !defined SOL_NO_AA
  class SentanTextProcessor;
  #endif

  class CharProcessor;
  class SyllabProcessor;
  class WordStatProcessor;

  // ************************************************************************
  // Выполняет быструю проекцию - получение кода словарной статьи по лексеме.
  // ************************************************************************
  class Class_Mapper
  {
   private:
    const Solarix::LexemDictionary *ld;

    lem::MCollect<int> ilexem_2_ientry;

    std::multimap<int, int> list;
    typedef std::multimap< int, int >::const_iterator ITER;
    typedef std::pair< int, int > VALUE;

    inline int Calc_Hash( const lem::UCString &s ) const
    { return (int(s.GetHash()) & 0x000000ff) + (s.back()<<16) + (s.length()<<20); }

   public:
    Class_Mapper( const Solarix::LexemDictionary *ptr, const Solarix::SynGram &sg );

    int Find_Entry( const lem::UCString &x ) const;
  };

 } 
 
 // *********************************************************
 // Многоцелевой модуль для статистической обработки текста. 
 // *********************************************************
 class EmpirTextProcessor : public Base_DataMiner
 {
  private:
   friend class Solarix::Search_Engine::Empir::WordProcessor;

   typedef enum { Undefined, Scheme1, Scheme2, Sentan, LexiconProbing, ToNouns } Scheme;
   Scheme scheme;
    
   lem::zbool analyzer_mode;
   lem::Path outfile;
   lem::Ptr<OFormatter> xml;

   std::vector<int> sentence_ie;

   enum Correl { UnknownCorrel, Nouns, Noun_Adjs, Noun_Verbs };
   Correl correl;
 
   lem::zeroed<bool> verbose; // детальная печать на терминале по ходу обработки

   lem::zeroed<bool> to_nouns; // для Scheme2 флаг 'to_nouns': поступающие слова 
                               // по мере возможности приводятся к форме
                               // существительного.

   lem::zeroed<int> max_distance; // для Scheme2 макс. расстояние между лексемами
                                  // для учета их корреляции 

   lem::UFString report_format;   // csv/xml/sql

   lem::zeroed<bool> raw_pairs; // записывать сведения о накопленных парах без сортировки и фильтрации

   // Накапливаемая по мере обработки файлов статистика 

   // Частота словарных статей
   std::map< int, int > word_freq;
   typedef std::map< int, int >::iterator WORD_FREQ_ITER;

   // Парные корреляции слов
   std::map< int, std::map< int, int >* > links;

   typedef std::map< int, std::map< int, int >* >::iterator ITER1;
   typedef std::map< int, std::map< int, int >* >::const_iterator CITER1;
   typedef std::map< int, std::map< int, int >* >::reverse_iterator RITER1;

   typedef std::map< int, int >::iterator ITER2;
   typedef std::map< int, int >::const_iterator CITER2;

   boost::posix_time::ptime t0;             // Зафиксированное время начала работы

   std::auto_ptr<Solarix::Search_Engine::Empir::WordProcessor> words; // Аккумулятор слов

   #if !defined SOL_NO_AA
   std::auto_ptr<Solarix::Search_Engine::Empir::SentanTextProcessor> sentan; // Модуль обработки предложений SENTAN
   #endif

   bool run_chars;
   std::auto_ptr<Solarix::Search_Engine::Empir::CharProcessor> char_stat;
   std::auto_ptr<Solarix::Search_Engine::Empir::SyllabProcessor> syllab_stat;
   std::auto_ptr<Solarix::Search_Engine::Empir::WordStatProcessor> word_stat;

   int n_words_2; // сколько обработано слов по схеме 2

   typedef enum { All, English, Russian, French, German, Italian, Spanish } Language;
   Language language;

   Solarix::Dictionary* sol_id;
   const Solarix::SynGram *sg;
   Solarix::LexicalAutomat *la;
   
   std::auto_ptr<Solarix::Search_Engine::Empir::Class_Mapper> cls_mapper; 

   int file_counter; // число обработанных файлов

   void Report1( Solarix::Search_Engine::Crawler &crawler );
   void Report2( Solarix::Search_Engine::Crawler &crawler );

   // Обработка очередной лексемы по схеме 1 (частоные характеристики 
   // отдельных слов в совокупности).
   void Process1( const lem::UCString &l );

   // Обработка очередной лексемы по схеме 2 (корреляции пар слов).
   void Process2( const lem::UCString &l );

   void Set_Scheme1(void);
   void Set_Scheme2(void);
   void Set_Sentan(void);
   void Set_LexiconProbing(void);
   void Set_ToNouns(void);
   void ParseArgumentsList( lem::Collect<lem::UFString> &args );

   bool CheckClassForCorrel( int iclass ) const;
   bool IsNoun( int iclass ) const;
   bool IsAdj( int iclass ) const;
   bool IsVerb( int iclass ) const;

  public:
   EmpirTextProcessor( const lem::UFString &arg );

   virtual ~EmpirTextProcessor(void);

   virtual void Report( Crawler &engine ); 

   virtual void Do(
                   Crawler &engine,
                   const File_Location &filename,
                   Base_File_Reader *reader,
                   lem::MCollect<Fix_Context*> &contexts
                  ); 
 };


  // *****************************************************************  
  // Вычисление хэш-кодов (MD5 и др) для документов.
  // *****************************************************************  
  class DM_HashCalc : public Base_DataMiner
  {
   private:
    lem::Path outfile; // имя файла с результатами анализа 

    // Документы и их хэши
    lem::PtrCollect< lem::Path >    docs;
    lem::PtrCollect< lem::FString > md5;

   public:
    DM_HashCalc( const lem::UFString &arg );

    virtual void Do( 
                    Crawler &engine,
                    const Solarix::Search_Engine::File_Location &filename,
                    Solarix::Search_Engine::Base_File_Reader *reader,
                    lem::MCollect<Fix_Context*> &contexts
                   ); 

    virtual void Report( Crawler &engine );
  };
*/
 }
}
#endif
