// -----------------------------------------------------------------------------
// File EMPIR.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// EMPIR program
// Всевозможная статистическая обработка текстов (морфология, синтаксис и т.д.).
//
// Заголовочный файл программы ЭМПИР - объявления классов.
//
// 17.11.2005 - в результате рефакторинга кода в обновленную программу EMPIR 
//              теперь входят ранее автономные модули SENTAN и CHARS. 
//
// 31.10.2006 - добавлен новый режим работы (команда -tonouns): слова из
//              обрабатываемых файлов приводятся к форме существительных и
//              результат записывается в выходной файл.
// -----------------------------------------------------------------------------
//
// CD->04.09.2002
// LC->10.06.2011
// --------------

#if !defined EMPIR__H
 #define EMPIR__H

 #include <utility>
 #include <map>

 #include <lem/math/statkeep.h>
 #include <lem/math/histogram.h>
 #include <lem/qarray.h>
 #include <lem/mqueue.h>
 #include <lem/mset.h>
 #include <lem/stl.h>
 #include <lem/oformatter.h>
 #include <lem/math/integer_math.h>
 #include <lem/cstring.h>
 #include <lem/date_time.h>

 #include <lem/solarix/la_autom.h>
 #include <lem/solarix/sg_autom.h>
 #include <lem/solarix/lexem.h>
 #include <lem/solarix/dictionary.h>
 #include <lem/solarix/phrasema.h>
 #include <lem/solarix/se_scan_options.h>
 #include <lem/solarix/file_factory.h>
 #include <lem/solarix/search_engine.h>

 #include <lem/solarix/MultiwordMerger.h>
 #include <lem/solarix/NGramsCollectors.h>
 #include <lem/solarix/Sg_CoordContext.h>

 using namespace lem;
 //using namespace lem::File_Factory;
 using namespace Solarix;

 const int W_QUEUE_LEN = 4; // Длина очереди истории обработанных слов.
// const int NCHAR     = 33;  // Число символов в алфавите

 const int NSUBLIST  = LEM_CSTRING_LEN; // Сколько делать подсписков слов для длин 1, 2,
                            // 3, ..., прочие.

 const int NCSL=256; // Кол-во подсписков для накопления контекстов

 // ****************************************************************
 // Следующие две функции выполняют вычисление двух составляющих в
 // ключе слова: номер подсписка и номер элемента в списке.
 // ****************************************************************
 inline int e_block( int key ) { return (key>>26) & 0x4fUL; }
 inline int e_hash( int key )  { return (key>>18) & 0xffUL; }
 inline int e_item( int key )  { return key & 0x4ffffUL; }

 // *****************************************************************
 // Собираем ключ из двух компонентов.
 // *****************************************************************
 inline int e_key( int iblock, lem::uint8_t hash_key )
 {  return hash_key | (iblock<<26); }

 inline int hash_to_key( lem::uint8_t hash, int item )
 {  return item | (hash<<18); }


 // ****************************
 // Список пар слово-частота
 // ****************************

 // ********************************************************
 // List of words that have equal hash code and length
 // ********************************************************
 class w_hash_list : public MCollect< std::pair<UCString,lem::int64_t /*frequency*/> >
 {
  public:
   w_hash_list(void):MCollect< std::pair<UCString,lem::int64_t> >() { reserve(256); }

   w_hash_list( const w_hash_list &x ) : MCollect< std::pair<UCString,lem::int64_t> >(x) {}

   inline void operator=( const w_hash_list &x )
   {
    MCollect< std::pair<UCString,lem::int64_t> >::operator=(x);
   }
 };


 // ************************************************************
 // Sectainer - the list of lists of words. All words in this
 // sectainer have equal length (but different hash codes).
 // ************************************************************
 class w_list : public Collect< w_hash_list >
 {
  public:
   w_list(void) : Collect< w_hash_list >(256)
   {}

   inline int add_lexem( const UCString &Word )
   {
    int ifound=UNKNOWN;

    w_hash_list &words_n = operator[]( static_cast<unsigned>(Word.GetHash()) );

    // Попытаемся найти слово...
    for( Container::size_type j=0; j<words_n.size(); j++ )
     if( words_n[j].first==Word )
      {
       words_n[ifound=CastSizeToInt(j)].second++;
       break;
      }

    // Слова нет в списке - добавляем.
    if( ifound==UNKNOWN )
     {
      ifound = CastSizeToInt(words_n.size());
      words_n.push_back( std::make_pair( Word, 1 ) );
     }

    return hash_to_key( static_cast<unsigned>(Word.GetHash()), ifound );
   }

   lem::int64_t GetWordFrequency( const lem::UCString &word ) const
   {
    const w_hash_list &words_n = operator[]( static_cast<unsigned>(word.GetHash()) );

    // Попытаемся найти слово...
    for( Container::size_type j=0; j<words_n.size(); j++ )
     if( words_n[j].first==word )
      {
       return words_n[j].second;
      }

    return 0;
   }
 };


 // ************************************************************************
 // Выполняет быструю проекцию - получение кода словарной статьи по лексеме.
 // ************************************************************************
 class Class_Mapper
 {
  private:
   lem::MCollect<Solarix::Lexem> ld;

   MCollect<int> ilexem_2_ientry;

   std::multimap<int /*хэш*/, int /*индекс в справочнике*/> list;
   typedef std::multimap< int, int >::const_iterator ITER;
   typedef std::pair< int, int > VALUE;

   inline int Calc_Hash( const UCString &s ) const
   { return (int(s.GetHash()) & 0x000000ff) + (s.back()<<16) + (s.length()<<20); }

  public:
   Class_Mapper( SynGram &sg );

   int Find_Entry( const UCString &x ) const;
 };



 class EmpirTextProcessor;

 

 // **************************************************************
 // Основной класс накопления статистики по словам.
 // **************************************************************
 class WordProcessor
 {
  private:
   int id_language;

   bool merge_words; // пытаться ли сливать слова для получения мультилексем, или внешний парсер файлов уже сделал это сам.
   lem::Ptr<MultiwordMerger> word_merger;

   lem::MCollect<UCString> sentence_word;


   // Накопленные списки пар слово-частота
   // Для ускорения отдельно ведутся списки слов длиной 1 символ,
   // 2 символа и далее, плюс последний список - для слов произвольной
   // длины больше заданной (NSUBLIST-1).
   w_list words[NSUBLIST]; // Длиной 1,2,3,4, и прочие
   lem::int64_t total_wlen; // Сумма длин слов - для вычисления средней длины
   lem::int64_t nlex; // Сколько слов обработано

   void ProcessInternal( const UCString &w );
   void PurgeMerger(void);

  public:
   lem::Path outdir; // в какой каталог сбрасывать файлы отчетов
   lem::Path GetOutPath( const wchar_t *filename ) const;
   lem::zbool erase_freq1, segmentation;
   Solarix::LexicalAutomat *la;

   std::set<UCString> stopwords;

  public:
   WordProcessor( Solarix::LexicalAutomat *LA, bool tokenized_is_used, int language );

   void Process( const UCString &w );
   void Report( OFormatter &to, EmpirTextProcessor &Holder );

   void EndDocument(void);

   inline const std::pair<UCString,lem::int64_t>& get_by_key( int key ) const
   { return words[ e_block(key) ] [ e_hash(key) ] [ e_item(key) ]; }

   int GetWordFrequency( const lem::UCString &word ) const;
 };


/*
 #if !defined SOL_NO_AA
 class SentanTextProcessor : public Solarix::Text_Processor
 {
  private:
   typedef enum { Scheme1, Scheme2, LexiconProbing } Scheme; // тип работающего алгоритма
   Scheme scheme;   

   lem::Math::Statis stat_sent; // Статистика длины предложени
   lem::Math::Statis aa_res;    // Статистика длины результата обработки в АА
   lem::Math::Statis aa_succ;
   lem::Histogramma start_vars; // Статистика по начальному числу вариаторов в пачке решений
   int n_success_sent; // Сколько предложений успешно подготовлено
   int n_sent_applied_aa;
   int n_success_aa; // Number of sents completely analysed by aa

   bool print_la_detailed; // Do print sentence preparation results
   bool print_aa_detailed; // Print results of AA performance for each sentence
   bool persentence_echo;  // При обработке каждого предложения выводить пояснения на терминал
   bool persentence_log;   //
   bool write_bin;         // Сохранять ли результаты анализа каждого предложения в бинарном файле

   Sentence sent; // Буфер для накопления предложения.

   #if LEM_DEBUGGING==1
   Solarix::FB_StatInfo fb_stat_info; // для накопления статистики по фразоблокам
   #endif

   OUFormatter ok_out;
   OUFormatter bad_out;
   OUFormatter skip_out;
   OUFormatter log_out;

   BinaryFile *bin_out; // For resulting frasoblocks

   void process_sentence(void);

   virtual void Projected( PhrasoBlock *fblo );
   virtual void Analysed( PhrasoBlock *fblo );
   virtual void AA_Applied( PhrasoBlock *fblo );
   virtual void LoopPassed( int n_pass );

  public:
   lem::Path outdir; // в какой каталог сбрасывать файлы отчетов

   lem::Path GetOutPath( const wchar_t *filename ) const;

  public:
   SentanTextProcessor( Dictionary *Sol_id );

   virtual ~SentanTextProcessor(void);

   void PrepareStreams(void);

   void Process( const UCString &l );
   void Report(void);

   inline void SetScheme1(void) { scheme=Scheme1; PerformSyntacticAnalysis(true); }
   inline void SetScheme2(void) { scheme=Scheme2; PerformSyntacticAnalysis(false); }

   inline void Print_AA_Detailed(void)      { print_aa_detailed=true; }
   inline void Print_LA_Detailed(void)      { print_la_detailed=true; }
   inline void Print_PerSentence_Echo(void) { persentence_echo=true;  }
   inline void Log_PerSentence_Echo(void)   { persentence_log=true;   }

   void Do_Write_Bin(void);

   inline bool Echo_PerSentence(void) const
   { return persentence_echo; }
 };
 #endif
*/


 // **************************************************************
 // Класс обработчика побуквенной статистики.
 // **************************************************************
 class CharProcessor
 {
  private:
   lem::int64_t nchar; // Сколько букв обработано
   lem::int64_t n_lim; // Сколько первых (или последних) букв обработано

   lem::MCollect<lem::int64_t> ch_freq;  // Частотная таблица для букв (256 элементов)
   lem::MCollect<lem::int64_t> org_freq; // Частотная таблица для первой буквы слова
   lem::MCollect<lem::int64_t> end_freq; // Частотная таблица для последней буквы слова

   Dictionary* sol_id;

   int unique_chars;
   std::map<wchar_t,int> chars; // список распознаваемых символов
   lem::MCollect<wchar_t> char_names;

   inline int get_ichar( wchar_t Ch ) const
   {
    std::map<wchar_t,int>::const_iterator wh = chars.find(Ch);
    return wh==chars.end() ? UNKNOWN : wh->second;
   }

  public:
   lem::Path outdir; // в какой каталог сбрасывать файлы отчетов

   lem::Path GetOutPath( const wchar_t *filename ) const;

  public:
   CharProcessor(void);

   void Add( const UCString &s, lem::int64_t word_freq );

   void Report( OFormatter &to ) const;

   double Calc_Val( const UCString &s, lem::int64_t wFreq ) const;

   void SetSol( Dictionary* SolId );

   inline int Total_Chars(void) const { return unique_chars; }
 };


 class ws_list : public lem::MCollect< std::pair<UCString,int> >
 {
  public:
   ws_list(void) { reserve(1024); }
 };


 #if defined EMPIR_SYLLAB
 class Syllab_Ctx
 {
  private:
   Syllab_Ctx( const Syllab_Ctx& );
   void operator=( const Syllab_Ctx& );

  public:
   UCString syllab;
   int freq; // Syllab frequency
   lem::Collect< std::pair<SG_CoordContext,int> > gram_contx;

   Syllab_Ctx( const UCString &Syllab, int nOrgFreq )
   { syllab=Syllab; freq=nOrgFreq; }

   void Add( int iClass, const CP_Array& dims, int Freq );
 };
 #endif 


 #if defined EMPIR_SYLLAB
 // **************************************************************
 // Класс обработчика послоговой информации.
 // **************************************************************
 class SyllabProcessor
 {
  private:
   int words_count; // Счетчик обработанных слов

   ws_list syllabs_2; // Накопленный список пар слог - частота
                     // для слогов длиной 2 буквы

   ws_list syllabs_3; // Накопленный список пар слог - частота
                     // для слогов длиной 3 буквы

   ws_list endings_2; // Накопленный список пар слог - частота для окончаний
                     // длиной 2 символа

   ws_list endings_3; // Накопленный список пар слог - частота для окончаний
                     // длиной 3 символа


   ws_list real_org_slb;
   ws_list real_mid_slb;
   ws_list real_end_slb;

   Ptr_NC_Collect<Syllab_Ctx> real_ctx;

   Dictionary* sol_id;

   void process_syllab_2( const UCString &e, int word_freq );
   void process_syllab_3( const UCString &e, int word_freq );

   void process_ending_2( const UCString &e, int word_freq );
   void process_ending_3( const UCString &e, int word_freq );

   void process_real_mid( const UCString &e, int word_freq );
   void process_real_end( const UCString &e, int word_freq );
   void process_real_org( const UCString &e, int word_freq );

   void Dump_Syllabs( OFormatter &out, const ws_list &slb ) const;

   int id_language;

  public:
   lem::Path outdir; // в какой каталог сбрасывать файлы отчетов

   lem::Path GetOutPath( const wchar_t *filename ) const;

  public:
   SyllabProcessor(void);

   void SetSol( Dictionary* SolId ) { sol_id=SolId; }
   void SetLanguage( int id ) { id_language=id; }

   void Add( const UCString &word, int word_freq );
   void Report( OFormatter &to, const CharProcessor &CH ) const;
   void Post_Process( const WordProcessor &words );
 };
 #endif 


 class WordStatProcessor
 {
  private:
   Dictionary* sol_id;
   lem::int64_t words_count;

   IntCollect  Nfreq;
   double tot_freq;

   void Report_Chars( OFormatter &to ) const;
   void Report_Syllabs( OFormatter &to ) const;

  public:
   lem::Path outdir; // в какой каталог сбрасывать файлы отчетов

   lem::Path GetOutPath( const wchar_t *filename ) const;

  public:
   WordStatProcessor(void);

   inline void SetSol( Dictionary* SolId ) { sol_id=SolId; }

   void Add( const UCString &u, lem::int64_t word_freq );

   void Report( OFormatter &to ) const;
   void Post_Process(void);
 };





 // *****************************************************
 // Контейнер, координирующий обработку входных лексем
 // классами-обработчиками (CharProcessor и др.)
 // *****************************************************
 class EmpirTextProcessor
 {
  private:
   friend class WordProcessor;

   lem::Path outdir; // в какой каталог сбрасывать файлы отчетов
   lem::Path dictdir; // в каком каталоге искать словарь lem::Path p2(outdir);

   typedef enum { Undefined, Scheme1, NGrams, Sentan, LexiconProbing, ToNouns, Tokenize } Scheme;
   Scheme scheme;

   lem::zbool merge_words;
   lem::Ptr<MultiwordMerger> word_merger;

   lem::Ptr<OUFormatter> tokenizer_out;

   lem::Ptr<NGramsCollectors> ngrams;
   lem::zbool merging;
   lem::zbool dump_unfound_words;
   lem::zbool dump_unfound_synonyms;
   std::set<lem::UCString> ngrams_unfound_words;
   std::set< std::pair<lem::UCString,lem::UCString> > ngrams_unfound_synonyms;
   Solarix::Sentence prev_sent, cur_sent;
   int prev_line; // номер строки последней обработанной лексемы
   lem::UFString source_format;
   bool upload_to_db;
   bool use_disk_cache;
   bool print_ngrams; // сохранять накопленные Nграммы в текстовый файл указанного формата
   lem::zbool main_ngrams; // использовать хранилище N-грамм, открытое по файлу dictionary.xml, а не создавать новое во временном каталоге
   lem::zbool eol_breaks; // перевод строки считать концом предложения
   lem::FString print_format; // "csv", "xml"
   lem::Path print_filename;
   lem::Ptr<OFormatter> print_file; // в этот файл будут печататься Nграммы

   lem::zbool erase_freq1; // удалять из итоговой БД N-граммы с частотой=1
   lem::zbool segmentation; // делать ли аккуратное слияние многолексемных слов типа "don't" и "кем-либо"
   lem::zbool lemmatization; // приводить словоформы к базовой форме для Raw N-грамм

   const lem::CodeConverter *default_cp; // Кодовая страница по умолчанию для PLAIN ASCII файлов
   const lem::CodeConverter *force_cp; // Принудительное задание кодовой страницы

   boost::posix_time::ptime t0;             // Зафиксированное время начала работы

   OFormatter nul_tty;

   WordProcessor *words; // Аккумулятор слов

   bool run_chars;
   CharProcessor char_stat;
   #if defined EMPIR_SYLLAB
   SyllabProcessor syllab_stat;
   #endif    
   WordStatProcessor word_stat;

   Language language;
   int language_sx_code; // SOLARIX-код языка

   Solarix::Search_Engine::Scan_Options scanning;
   lem::Ptr<Solarix::Search_Engine::File_Type_Detector> detector;

   lem::Ptr<Dictionary> sol_id;
   Solarix::SynGram *sg;
   Solarix::LexicalAutomat *la;
   lem::Ptr<Solarix::LemmatizatorStorage> lemm;

   Class_Mapper *class_mapper;
   const Class_Mapper* GetClassMapper(void);

   int file_counter; // число обработанных файлов

   lem::Collect< lem::Path > scan_files, scan_folders; // папки и файлы для обработки

   void NeedsCharStatistics(void);

   void LoadConfig( const lem::Path & force_dir );

   // Метод (в классе Crawler) вызывается для каждого найденного
   // и прошедшего фильтры файла.

   virtual void ProcessFile( const lem::Path &filename );
   virtual bool ProcessFile( const lem::Path &filename, Solarix::Search_Engine::Base_File_Reader *reader, lem::Stream * raw_file );

   void Report1(void);
   void Report2(void);

   void BeginDocument(void);
   void EndDocument(void);
   void EndAll(void);

   lem::Path GetOutPath( const wchar_t *filename ) const;

   // *********************************************************
   // Слово 'l' поступило на обработку.
   // *********************************************************
   inline void Process( const UCString &l )
   {
    words->Process( l );
   }

   void Process2( const UCString &l );
   void ProcessInternal2( const UCString &l );

   bool AcceptLexem( const UCString &bl ) const;


  public:
   EmpirTextProcessor();

   ~EmpirTextProcessor();

   void Show_Banner();
   void Help();

   virtual void Parse_Command( Collect<UFString> &args );
   virtual void Scan();

   void Load_Dictionary();

   void Set_Scheme1();
   void Set_NGrams();
   void Set_Sentan();
   void Set_LexiconProbing();
   void Set_ToNouns();

   void Report();
 };

#endif
