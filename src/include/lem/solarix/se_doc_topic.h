// ----------------------------------------------------------------------------
// File SE_DOC_TOPIC.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SEARCH ENGINE Core
//
// Авторубрикатор. 
//
// 23.05.2006 - введена фильтрация обрабатываемых слов по языку
// 19.06.2008 - расширен метод Topic_Finder::SaveXML для возможности сохранения
//              только списка тем, без наработанных в тренировке правил.
// ----------------------------------------------------------------------------
//
// CD->23.02.2006
// LC->14.10.2011
// --------------

#ifndef SE_DOC_TOPIC__H
#define SE_DOC_TOPIC__H
#pragma once

// #if defined FAIND_DATAMINE

 #include <map>
 #include <lem/mqueue.h>
 #include <lem/oformatter.h>
 #include <lem/solarix/file_location.h>
 #include <lem/solarix/file_factory.h>
 //#include <lem/solarix/text_processor.h>
 #include <lem/solarix/se_fix_context.h>
 #include <lem/solarix/se_word_searcher.h>
 #include <lem/solarix/se_indexer_types.h>
 #include <lem/solarix/se_search_options.h>
 #include <lem/solarix/se_echo_options.h>
 #include <lem/solarix/search_engine_callbacks.h>
 //#include <lem/solarix/ngrams_collector.h>
 #include <lem/solarix/search_engine.h>


 namespace Solarix
 {
  namespace Search_Engine 
  {
   extern const wchar_t CORPUS_TOPIC_NAME[]; // имя рубрики, в которую включается тексты,
                                             // составляющие среднестатистический корпус.


   // Критерий оценки документов (ранее единственный вариант был "ЖАНР")
   struct Id_Criterion
   {
    int id;           // PK
    bool actual;      // false для удаленной записи
    lem::UFString text;    // Текстовое описание

    Id_Criterion(void);

    Id_Criterion( int Id, const lem::UFString &Text );

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
   };



  // ********************************************
  // Таблица CRITERIA
  // ********************************************
  class Tbl_Criteria
  {
   private:
    PtrCollect<Id_Criterion> rows;

    lem::Path GetFileName(void) const;
    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

   public:
    Tbl_Criteria(void);

    int Find( int Id ) const;
    int Find( const UFString &Name ) const;    
    inline const Id_Criterion& operator[]( int i ) const { return *rows[i]; }
    inline       Id_Criterion& operator[]( int i )       { return *rows[i]; }

    inline int size(void) const { return CastSizeToInt(rows.size()); }

    // Возвращает свободный id для создаваемой записи
    int GetNextId(void) const;

    // Удаляет из таблицы запись с заданным id
    bool DeleteById( int Id );

    void AddChecked( Id_Criterion *NewRec );
    void AddUnsafe( Id_Criterion *NewRec );
    void Purge(void);
    void Commit( const lem::Path &folder );
    void Load( const lem::Path &folder );
    void SaveXML( lem::OUFormatter &out ) const;
    void CreateIndex(void);
  };






  // ********************************** 
  // Описание рубрики в таблице TOPIC
  // ********************************** 
  struct Id_Topic //: public boost::noncopyable
  {
   int id;           // PK
   bool actual;      // false для удаленной записи
   int id_criterion; // ID критерия
   UFString text;    // Текстовое описание рубрики
   UFString code;    // Код рубрики (типа УДК)
   UFString info;    // Примечания

   float norma; // вычисляемая при обучении сумма весов всех релевантных слов,
                // используется для нормирования результатов.
   float norma2; // аналогично для диграмм

   Id_Topic(void) { id=UNKNOWN; norma=norma2=1.0F; actual=true; }

   Id_Topic( int Id, int Id_Criterion, const UFString &Text );

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
  };


  // ********************************************
  // Таблица TOPIC
  // ********************************************
  class Tbl_Topic
  {
   private:
    PtrCollect<Id_Topic> rows;
    std::map< int /*PK*/, int /*rows[i]*/ > idx;

    lem::Path GetFileName(void) const;
    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

   public:
    Tbl_Topic(void);

    int Find( int Id ) const;
    int Find( const UFString &Name ) const;    
    inline const Id_Topic& operator[]( int i ) const { return *rows[i]; }
    inline       Id_Topic& operator[]( int i )       { return *rows[i]; }

    inline int size(void) const { return CastSizeToInt(rows.size()); }

    // Возвращает свободный id для создаваемой записи
    int GetNextId(void) const;

    // Удаляет из таблицы запись с заданным id
    bool DeleteById( int Id );

    //! Удаляет все записи, ссылающиеся на id_criterion
    void DeleteCascadeByIdCriteria( int id_criterion );

    //! Есть ли записи, ссылающиеся на id_criterion
    bool DoesReferCriterion( int id_criterion ) const;

    //! Список id записей, ссылающихся на id_criterion
    void SelectByIdCriterion( int id_criterion, lem::MCollect<int> &id_topics ) const;

    void AddChecked( Id_Topic *NewRec );
    void AddUnsafe( Id_Topic *NewRec );
    void Purge(void);
    void Commit( const lem::Path &folder );
    void Load( const lem::Path &folder );
    void SaveXML( lem::OUFormatter &out ) const;
    void CreateIndex(void);
  };



  typedef lem::PtrCollect<Id_Topic> Tbl_Topic_Alias;


  // ******************************************************************
  // Запись в таблице KEYWORD - ключевое слово,
  // присутствие которого в тексте документа доказывает принадлежность
  // документа к одной из рубрик.
  // ******************************************************************
  struct Rec_Keyword
  {
   int id;        // PK записи
   lem::UCString word; // ключевое слово
   int ie1; // проекция слова на лексикон - первичный ключ словарной статьи

   lem::uint16_t hash;

   enum RecType { None, Word, Regex };
   RecType type;      // Тип записи (0 - обычное слово, 1 - рег. выражение ?)

   Rec_Keyword(void) { id=ie1=UNKNOWN; type=None; }

   Rec_Keyword( int Id, const UCString &W );

   // Инициализация хэш-кода после изменения лексического содержимого
   inline void calc_hash(void)
   { hash = word.GetHash(); }

   inline lem::uint16_t GetHash(void) const { return hash; }

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );

   inline int GetId(void) const { return id; }
  };


  // Ключевое словосочетание
  struct Rec_NGram : lem::NonCopyable
  {
   int id;        // PK записи
   lem::MCollect<lem::UCString> words;
   lem::MCollect<int> ies; // проекции слов на лексикон
   Rec_Keyword::RecType type;

   Rec_NGram(void) { id=UNKNOWN; type=Rec_Keyword::None; }
   Rec_NGram( int Id, const lem::MCollect<UCString> &Words, const lem::MCollect<int> &EntryKeys );

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );

   inline int GetId(void) const { return id; }
   inline int Length(void) const { return CastSizeToInt(words.size()); }

   bool Match( const lem::MCollect<lem::UCString> &Words, const lem::MCollect<int> &Ies ) const;
  };


  // Информация о ключевых словах и словосочетаниях, которые связаны с первым словом
  struct Rec_Headword
  {
   int minlen, maxlen;
   Rec_Headword(void) : minlen(UNKNOWN), maxlen(UNKNOWN) {}

   void Apply( int len );
   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
  };

  // ************************************************
  // Таблица KEYWORD - список ключевых слов (или пар)
  // ************************************************
  class Tbl_Keyword
  {
   private:
    int seq_id, seq_id_ngram; // счетчики для выделения новых id

    lem::PtrCollect<Rec_Keyword> rows; // записи

    // Индексы для ускорения доступа
    std::map< int /*PK*/, int /*rows[i]*/ > idx;
    std::map< int /*ie_1*/, int /*rows[i]*/ > idx_ie1;
    std::map< UCString /*word*/, int /*rows[i]*/ > idx_word;

    // NGRAM
    int ngram_maxlen; // макс. длина (число слов) в N-граммах
    lem::PtrCollect<Rec_NGram> rows_ngram;
    std::map< int /*PK*/, int /*rows[i]*/ > idx_ngram;

    lem::PtrCollect<Rec_Headword> headwords;
    std::map<int,Rec_Headword*> ie2headword;
    std::map<lem::UCString,Rec_Headword*> word2headword;
    std::multimap< int /*ie*/, const Rec_NGram* > ie2ngram;
    std::multimap< lem::UCString, const Rec_NGram* > word2ngram;

    void CreateIndex(void);

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
    lem::Path GetFileName(void) const;

   public:
    Tbl_Keyword(void);

    inline int Count(void) const { return CastSizeToInt(rows.size()); }
    inline const Rec_Keyword& operator[]( int i ) const { return *rows[i]; }

    int CountNGram(void) const { return CastSizeToInt(rows_ngram.size()); }
    inline const Rec_NGram& GetNGram( int i_ngram ) const { return *rows_ngram[i_ngram]; }

    int Find( int Id ) const;
    int FindNGram( int Id ) const;
    int Find( const UCString &s ) const;
    int FindIE1( int IE1 ) const;

    int GetNGramMaxLen(void) const { return ngram_maxlen; }
    bool IsHeadword( const lem::UCString &word, int ie, Rec_Headword &info ) const;
    int FindNGram( const lem::MCollect<lem::UCString> &words, const lem::MCollect<int> &ies ) const;

    void AddChecked( Rec_Keyword *NewRec );
    void AddUnsafe( Rec_Keyword *NewRec );

    void AddChecked( Rec_NGram *NewRec );
    void AddUnsafe( Rec_NGram *NewRec );

    void Purge(void);
    void Commit( const lem::Path &folder );
    void Load( const lem::Path &folder );
    void SaveXML( lem::OUFormatter &out ) const;

    inline int GetNextId(void) { return seq_id++; }

    //! Удаляет все записи, ссылающиеся на id_topic
    void DeleteCascadeByIdTopic( int id_topic );
  };


  // таблица связи KW_2_TOPIC

  struct Kw_2_Topic
  {
   int id_kwd; // FK(KEYWORD)
   int id_topic; // FK(TOPIC)
   float w;

   Kw_2_Topic(void) { id_kwd=id_topic=NULL; w=0; }
  };


  class Tbl_Kw_2_Topic
  {
   public:
    typedef std::multimap<int,int>::const_iterator II;

   private:
    MCollect<Kw_2_Topic> rows;
    std::multimap< int /*id_kwd*/, int /*rows[i]*/ >   idx_kwd;
    std::multimap< int /*id_topic*/, int /*rows[i]*/ > idx_topic;

    void CreateIndex(void);
    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
    lem::Path GetFileName(void) const;

   public:
    Tbl_Kw_2_Topic(void);

    std::pair< std::multimap<int,int>::const_iterator, std::multimap<int,int>::const_iterator > Find_Kwd( int Id_Keyword ) const;    
    std::pair< std::multimap<int,int>::const_iterator, std::multimap<int,int>::const_iterator > Find_Topic( int Id_Topic ) const;    

    inline const Kw_2_Topic& operator[]( int i ) const { return rows[i]; }
    inline       Kw_2_Topic& operator[]( int i )       { return rows[i]; }

    void AddChecked(
                    const Kw_2_Topic& NewRec,
                    const Tbl_Topic &Topic,
                    const Tbl_Keyword &Keyword
                   );

    void AddUnsafe( const Kw_2_Topic &NewRec );
    void Purge(void);
    void Commit( const lem::Path &folder );
    void Load( const lem::Path &folder );
    void SaveXML( lem::OUFormatter &out ) const;

    void DeleteCascadeByIdTopic( int id_topic );

    // Для случая, когда одному ключевому слову соответствует одна рубрика,
    // возвращает ID рубрики по ID ключевого слова.
    int /*id_topic*/ Keyword2Topic( int id_keyword ) const;
  };
  






  class Word_Searcher;
  class Document_Index;
  class Topic_Finder;


  struct TF_Total_Statistics : boost::noncopyable
  {
   lem::Collect< lem::triple< int /*id_topic*/, UFString /*text*/, int /*nkwd*/ > > topics;

   int CountTopics(void) const;
   int CountKeywords(void) const;
  };


  // ***************************************************
  // Главный класс рубрикатора.
  // ***************************************************

  class Word;
  class CommandParser;

  class Topic_Finder
  {
   private:
    Solarix::Dictionary *sol_id;

    // Список подготовленных модулей сравнения слов с учетом всех опций
    lem::PtrCollect<Solarix::Search_Engine::Word> word_matchers;
    lem::MCollect<int> word_matchers_ind;

    void Purge(void);

   public:
    Tbl_Criteria tbl_criteria;
    Tbl_Topic tbl_topic;
    Tbl_Keyword tbl_keyword;
    Tbl_Kw_2_Topic tbl_kw_2_topic;

    Solarix::Search_Engine::Progress_Callback *progress;

    lem::zbool filter_nouns;

   public:
    Topic_Finder( Solarix::Dictionary *Sol_id );
    ~Topic_Finder(void);

    // Загрузка содержимого таблиц (справочников) из XML файла - для
    // отладочных целей и начального наполнения БД.
    void LoadXML( lem::Stream &file, Solarix::Dictionary *dict );

    int FindIE( const UCString &word, Solarix::Dictionary *dict ) const;

    void PrepareForMultiwordSearch(
                                   const Search_Options &flags,
                                   Dictionary *dict,
                                   Solarix::Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                   const Lexer_Options &lexer_options
                                   #if !defined SOL_NO_AA
//                                   , Solarix::Text_Processor *tpu
                                   #endif
                                  );

    int FindKeywordDirect( const UCString &word ) const;

    int FindKeywordWordforms(
                             Solarix::Search_Engine::File_Lexem &word,
                             Solarix::Search_Engine::Text &text, 
                             const Search_Options &flags,
                             const Solarix::LD_Seeker *seeker,
                             Solarix::Dictionary *dict,
                             Search_Engine::Fuzzy_Comparator *fuzzy_eq
                            ) const;
  };


 } // namespace Search_Engine

} // namespace Solarix 


// #endif // defined FAIND_DATAMINE

#endif
