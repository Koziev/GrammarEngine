// -----------------------------------------------------------------------------
// File SE_INDEXER.H
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Search engine FAIND. Indexer classes.
// Поисковый движок FAIND. Индексная база данных.
//
// 14.02.2006 - в описании зоны теперь будет хранится признак 'CD/DVD',
//              чтобы при мультизонном поиске делать запрос пользователю - 
//              вставить нужный диск в привод.
//
// 20.02.2006 - в описание зоны введен параметр "версия использованного словаря",
//              чтобы в будущих версиях позволить постепенно наращивать словарь
//              (к примеру - докупать профверсию).
//
// 12.03.2006 - введен новый тип зоны "noindex" - без фактической индексации.
//
// 04.07.2006 - изменения в формате хранения таблицы индексов (для обеспечения
//              более производительного многопоточного доступа) в дисковом файле.
//
// 04.07.2006 - начата работа по введению мониторинга изменений в динамических
//              зонах.
//
// 25.10.2006 - рефакторинг имен методов, приведение их к единому стандарту.
//
// 06.11.2006 - поддержка файлов индексной БД > 2Gb
//
// 24.02.2007 - для версии Pro в качестве локального хранилища корневой таблицы
//              будет использоваться СУБД SQLite
// 
// 11.06.2007 - все std::auto_ptr заменены на boost::shared_ptr, так как
//              реализация std::auto_ptr на MSVC 6.0 лишена ::reset() 
//
// 27.06.2007 - добавлен код для будущей поддержки CLucene.
// -----------------------------------------------------------------------------
//
// CD->19.03.2005
// LC->19.04.2010
// --------------

#if !defined SE_DOCUMENT_INDEX__H && defined FAIND_INDEXER
#define SE_DOCUMENT_INDEX__H
#pragma once

 #include <lem/config.h>

 #if !defined FAIND_NO_BOOST_REGEX
 #include <boost/regex.hpp>
 #endif

 #include <boost/date_time/posix_time/posix_time.hpp>

 #if defined FAIND_SIGNALS
 #include <boost/signal.hpp>
 #endif

 #include <lem/ilist.h> 
 #include <lem/streams.h> 
 #include <lem/containers.h> 
 #include <lem/math/random.h>
 #include <lem/math/fp1.h> 
 //#include <lem/solarix/text_processor.h>
 #include <lem/solarix/file_location.h>
 #include <lem/solarix/se_general_options.h>
 #include <lem/solarix/se_indexer_types.h>
 #include <lem/solarix/se_lexer_options.h>
 #include <lem/solarix/se_index_options.h>
 #include <lem/solarix/se_word_searcher.h>
 #include <lem/solarix/idx_folder_monitor.h>
 
 #undef assert

 namespace lem
 {
  namespace File_Factory
  {
   struct Scan_Options;
  }
 }

 namespace Solarix
 {
  class LD_Seeker;

  namespace Search_Engine
  { 
   struct Pattern;
   class Base_File_Reader;

   using lem::IList;
   using lem::BinaryFile;
   using lem::Stream;
   using lem::FString;
   using lem::UFString;
   using lem::UCString;
   using lem::OFormatter;
   using lem::Collect;
   using Solarix::Search_Engine::File_Location;
   using Solarix::Search_Engine::Morphology;
   using Solarix::LD_Seeker;
   using Solarix::Search_Engine::Pattern;

   struct Search_Options;

   #if defined FAIND_DATAMINE
   class Doc_Topic; 
   #endif

   class Fuzzy_Comparator;

   #if defined FAIND_4G_DOCS
   // Допускаем 2^32 документа в одном индексе. При этом серьезно возрастут
   // затраты оперативной памяти.
   typedef lem::uint32_t DocIndex;
   const int DocIndex_MAX=lem::uint32_max;
   #else
   typedef lem::uint16_t DocIndex;
   const int DocIndex_MAX=lem::uint16_max;
   #endif

   // ************************************************************************
   // Класс для управления списком именованных областей поиска (каталогизатор).
   // Базовый интерфейс содержит также средства по кэшированию таблицы в
   // оперативной памяти для ускорения доступа.
   // ************************************************************************
   class Idb_List : public lem::IList<Domain_Info>, lem::NonCopyable
   {  
    protected:
     virtual const Domain_Info& Get( size_type idx ) const;
     virtual       Domain_Info& Get( size_type idx );

    protected:
     friend class IndexManager;

     const Indexer_Options *flags; // параметры работы индексаторов
     lem::zbool loaded; // список уже загружен?
     lem::PtrCollect<Domain_Info> list; // Список описателей индексов

     lem::Collect<lem::Path> to_del; // загруженный список файлов и каталогов для удаления в ходе монтирования
     lem::zbool to_del_dirty; // список to_del был изменен после загрузки

     #if defined LEM_THREADS
     lem::Process::CriticalSection cs; // для синхронизации изменений в списке индексов
     #endif

     // Удаление файлов и папок из списка to_del
     virtual void PurgeScheduledFiles(void);
     virtual void SaveScheduledFiles(void); 

    public:
     Idb_List( const Indexer_Options *Flags );

     virtual ~Idb_List(void);

     void EnterCS(void);
     void LeaveCS(void);

     // Печать сведений о реализации хранилища.
     virtual void PrintVersion( OFormatter &out, const lem::UI::Resource_List &resx, bool StorageInfo=false ) const=0;

     // создаем новую запись и возвращаем ее id.
     virtual int CreateDomain(
                              const UFString &Domain_Name,
                              const lem::Path &index_db_folder,
                              Domain_Info::ContentMode Mode,
                              bool ReadOnly,
                              const UFString &Cmd,
                              Domain_Info::ChangesMonitorType Refresh=Domain_Info/*::Changes_Monitor*/::Manual,
                              Domain_Info::EngineType engine_type=Domain_Info::FaindEngine,
                              bool shared=false,
                              bool allows_word_wheeled_search=false
                             ) { LEM_STOPIT; LEM_NO_RET(0); }

     // Запоминаем для индекса определение области поиска
     virtual void StoreDomainCommands( int id_zone, const UFString &Cmd )
     { LEM_STOPIT; }

     // Запоминаем, что при индексации зоны использован словарь. Изменения
     // запоминаются в хранилище.
     virtual void SetNeedsDictionary( int id_zone, bool Flag ) 
     { LEM_STOPIT; }

     // Загрузка списка зон из файла (или БД) в оперативную память
     virtual void Load(void) { LEM_STOPIT; }

     // Если мы знаем, что индекс изменен снаружи и надо обновить его описание в оперативной памяти.
     virtual void ReloadDomain( int id ) { LEM_STOPIT; }

     // Запись измененного списка областей в дисковый файл, атомарная
     // операция (либо целиком успешна, либо в хранилище останется старый
     // список).
     virtual void Save(void) { LEM_STOPIT; }

     // Удаление описания зоны и сохранение изменения в хранилище.
     virtual void DeleteDomain( int id_zone ) { LEM_STOPIT; }

     // Очистка зоны - само описание остается.
     virtual void PurgeDomain( int id_zone ) { LEM_STOPIT; }

     // Переименование зоны и сохранение изменений в хранилище
     virtual void Rename( int id_zone, const UFString &new_name ) { LEM_STOPIT; }

     // Изменение описания индекса и сохранение изменений в хранилище
     virtual void SetComment( int id_zone, const UFString &Comment )  { LEM_STOPIT; }

     // Изменение режима общего доступа
     virtual void Share( int id_zone, bool shared ) { LEM_STOPIT; }

     // Для указанного индекса сохраняется только флаг
     // "нуждается в переиндексировании".
     virtual void SaveNeedsRefreshFlag( int id_zone ) { LEM_STOPIT; }

     // Поиск индекса для указанного через s/n CD
     virtual int FindCdrom( lem::uint32_t SericalNumber ) const;

     // IList<>
     virtual bool IsFixedSize(void) const { return false; }
     virtual bool IsReadOnly(void) const { return false; }

     // Очистка внутреннего списка (в хранилище изменений нет).
     virtual void Clear(void);

     virtual bool Empty(void) { return list.empty(); }

     // Общее количество записей, включая неактуальные
     virtual IList<Domain_Info>::size_type Count(void) const { return list.size(); }

     // IList<>
     virtual void SetCur( IList<Domain_Info>::size_type i ) { LEM_STOPIT; }
     virtual IList<Domain_Info>::size_type GetCur(void) { LEM_STOPIT; LEM_NO_RET(0); }
 
     // IList<>
     virtual void Add( const Domain_Info &x )  { LEM_STOPIT; }
     virtual bool Contains( const Domain_Info& x ) const  { LEM_STOPIT; LEM_NO_RET(false); }
     virtual Idb_List::size_type IndexOf( const Domain_Info& x ) const  { LEM_STOPIT; LEM_NO_RET(0); }
     virtual void Insert( size_type i, const Domain_Info& x )  { LEM_STOPIT; }
     virtual void RemoveAt( Idb_List::size_type i )  { LEM_STOPIT; }
     virtual void Remove( const Domain_Info& x )  { LEM_STOPIT; }

     virtual const Domain_Info& GetUnsafe( size_type idx ) const { return *list[idx]; }
     virtual       Domain_Info& GetUnsafe( size_type idx )       { return *list[idx]; }
     const Domain_Info& GetUnsafe( const UFString &Domain_Name );

     // Для потоково-безопасного получения копия описания зоны.
     virtual void GetSafe( int id, Domain_Info &res );

     // Потоко-безопасный метод определения имени для зоны
     virtual lem::UFString GetDomainName( int id_zone );

     // Потоко-безопасный метод определения примечания для зоны
     virtual lem::UFString GetDomainComment( int id_zone );

     virtual bool GetNeedsDictionary( int id_zone );
     virtual bool IsShared( int iDomain ); 
     virtual bool IsActual( int iDomain ); 
     virtual bool IsStatic( int iDomain ); 
     virtual bool IsDynamic( int iDomain ); 
     virtual bool IsNoIndex( int iDomain );
     virtual bool IsReadOnly( int iDomain );
     virtual bool IsMonitored( int iDomain ); 
     virtual void GetDomainCmd( int iDomain, lem::UFString &cmd );
     virtual bool DoesNeedRefresh( int iDomain ); 
     virtual bool IsRemote( int iDomain ); 
     virtual Solarix::Search_Engine::Domain_Info::EngineType GetIndexEngine( int iDomain );
     virtual bool DoesNeedIdleRefresh( int iDomain ); 
     virtual bool AllowsWordWheeledSearch( int iDomain ); 
     boost::posix_time::ptime GetDomainModifTimestamp( int iDomain );

     // Поиск индекса описателя зоны по ее имени
     virtual int Find( const UFString &Domain_Name );
 
     // Поиск индекса описателя зоны по id
     virtual int FindById( int id );

     // Число актуальных индексов (то есть удаленные игнорируются)
     virtual int CountActual(void);

     virtual void DeleteAllIndexes(void)=0;

     virtual bool IsEmptyDomain( int id_zone )=0;

     // Распечатка краткой информации об объявленных зонах.
     virtual void PrintList( OFormatter &out, const lem::UI::Resource_List &resx, bool xml=false, bool shared_only=false );

     // Сохранение корневой таблицы в указанном каталоге.
     virtual void BackupDomainsList( const lem::Path &dest_folder ) { LEM_STOPIT; }

     // Восстановление корневой таблицы из резервной копии в указанном каталоге.
     virtual void RestoreDomainsList( const lem::Path &dest_folder ) { LEM_STOPIT; }

     // Сохранение индекса в указанном каталоге.
     virtual void BackupDomain( const UFString &domain_name, const lem::Path &dest_folder ) { LEM_STOPIT; }

     // Восстановление индекса из резервной копии в указанном каталоге.
     virtual void RestoreDomain( const UFString &domain_name, const lem::Path &dest_folder ) { LEM_STOPIT; }

     // Пытаемся заблокировать указанный индекс, возвращаем true в случае успеха.
     virtual bool LockByReader( int id_index );
     virtual bool LockByWriter( int id_index );

     // Проверяем наличие блокировки. Это не всегда срабатывает ожидаемым
     // образом, так как после успешной проверки блокировка может измениться.
     virtual bool IsLockedByReader( int id_index );
     virtual bool IsLockedByWriter( int id_index );

     // Пытаемся заблокировать указанный индекс, возвращаем true в случае успеха.
     virtual void UnlockByReader( int id_index );
     virtual void UnlockByWriter( int id_index );

     // Принудительное снятие всех блокировок.
     virtual void UnlockAll(void);

     virtual const Domain_Info& ImportDomain( const Domain_Info &d, const Remote_Zone& r );

     // Указанный файл или папка должен быть удален в будущем.
     virtual void AddToDel( const lem::Path &p );

     // Возвращается имя для нового создаваемого индекса.
     virtual lem::Path GetNewDomainFolder(void) const;

   };



   #if defined FAIND_IDBLIST_SQLITE || defined FAIND_IDBLIST_MYSQL
    #define FAIND_IDBLIST_SQL
   #endif
  



   class Indexer;

   class Proximity_Catalog : public lem::MCollect< std::pair<int /*super_index*/, lem::Stream::pos64_type /*beginning*/> >
    , boost::noncopyable
   {
    public:
     Proximity_Catalog(void) {}
   };


   class Assoc_Files;


   const int N_PAIR_HASH  = 4096;
   const int N_HASH_GROUP = 16; 
   inline unsigned CALC_PAIR_HASH( int first, int second )
   { return (first>>16 ^ first ^ second>>16 ^ second) & 0x00000fffu; }


   // Пара ключевых слов
   struct Entry_Pair : public std::pair<int,int>
   {
    Entry_Pair(void) {}
    Entry_Pair( int i, int j ) { first=i; second=j; }

    inline bool operator==( const Entry_Pair &x ) const
    { return first==x.first && second==x.second; }

    inline bool operator!=( const Entry_Pair &x ) const
    { return first!=x.first || second!=x.second; }

    inline bool operator>( const Entry_Pair &x ) const
    {
     return first > x.first ?
             true  :
            ( first==x.first ? second>x.second : false );
    }   

/*
    inline lem::uint8_t hash(void) const
    {
     return  ( first>>24 ^ first>>16 ^ first >>8 ^ first ) ^ 
             ( second>>24 ^ second>>16 ^ second >>8 ^ second );
    }
*/

    enum { NHASH=N_PAIR_HASH };

    inline unsigned hash(void) const { return CALC_PAIR_HASH(first,second); }
   };


   inline unsigned calc_pair_hash( int first, int second )
   { return (first>>16 ^ first ^ second>>16 ^ second) & 0x00000fffu; }




   struct Context2 : public Entry_Pair
   {
    bool more_than_1;
    union {
           DocIndex idoc;
           lem::MCollect<DocIndex> *v;
          };  
    
    Context2(void) { v=NULL; more_than_1=false; }
    
    Context2( int I1, int I2, DocIndex iDoc )
     : Entry_Pair(I1,I2), more_than_1(false), idoc(iDoc) {}

    inline bool operator==( const Entry_Pair &x ) const
    { return first==x.first && second==x.second; }

    inline void Add( DocIndex iDoc )
    {
     if( more_than_1 )
      v->push_back(iDoc);
     else
      {
       const DocIndex iDoc0 = idoc;
       v = new lem::MCollect<DocIndex>();
       v->push_back( iDoc0 );
       v->push_back( iDoc );
      }

     more_than_1 = true; 
    }

    inline void Free(void) { if(more_than_1) lem_rub_off(v); }
 
    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
   };


   // ***************************************
   // Общая матрица близости для всей зоны.
   // ***************************************
   class Zone_Proximity : boost::noncopyable
   {
    private:
     typedef lem::MCollect<Context2> CtxSublist;
     CtxSublist* sublist[ Entry_Pair::NHASH ]; // один подсписок для каждого значения хэш-кода
     typedef std::map<Entry_Pair,int> Accel;
     Accel* accels[ Entry_Pair::NHASH ]; // ускорители наполнения sublists

     lem::Stream::pos64_type beg; // поле используется при сохранении матрицы на диск
     lem::Stream::pos64_type cat[ Entry_Pair::NHASH ]; // каталог - позиции начала подсписков в файле

     void Clear_Sublist( CtxSublist &l ) const;
     void SaveBin( const CtxSublist &l, lem::Stream &bin ) const;
     void LoadBin( CtxSublist &l, lem::Stream &bin );

    public:
     Zone_Proximity(void);
     ~Zone_Proximity(void);

     // Очистка перед индексированием новой зоны
     void Clear(void);

     void Prepare_Range( int i0, int iN );

     void Add_Pair( int sublist, int si1, int si2, DocIndex idoc );

     // Сохранение матрицы близости
     void SaveBin_Head( lem::Stream &bin );
     void SaveBin_Body( lem::Stream &bin, int i0, int iN );
     void SaveBin_Tail( lem::Stream &bin ) const;

     // Возвращается список дескрипторов документов, содержащих пару
     // слов (указанных по индексам в справочнике ключевых слов).
     Assoc_Files* Get_Assoc_Files( lem::Stream &bin, int super_index1, int super_index2 );
   }; 



   // ********************************************
   // Данные для одного обработанного документа
   // ********************************************
   class Document_Index : lem::NonCopyable
   {
    public:
     lem::MCollect<Index_Entry> word_list; // Список слов без стоп-слов.
     lem::MCollect<int> freq_list; // список частот слов

    private:
     #if defined LEM_DEBUGGING==1
     lem::Guardian guard1;
     #endif

     lem::Stream::pos64_type words_beg; // позиция в файле начала списка слов.
     lem::Stream::pos64_type freq_beg; // позиция в файле начала списка частот.
     lem::Stream::pos64_type prox_beg; // позиция в файле начала матрицы близости.
     lem::Stream::pos64_type topic_beg; // позиция в файле начала описателя темы.
     lem::Stream::pos64_type index_end; // первый байт после данных индекса

     Proximity_Catalog prox_cat; // загруженный из файла каталог для матрицы близости в документе
     lem::MCollect< std::pair<Index_Entry,int> > freqs_loaded; // загруженная из файла частотная таблица

     std::vector<int> prox; // индексы слов в одном предложении (рабочий вектор)
     typedef std::map< int /*ientry1*/, std::map< int /*ientry2*/, int /*freq*/ >* > LINKS;
     LINKS links;
     typedef std::map< int /*ientry1*/, std::map< int /*ientry2*/, int /*freq*/ >* >::iterator ITER1;
     typedef std::map< int /*ientry1*/, std::map< int /*ientry2*/, int /*freq*/ >* >::const_iterator CITER1;

     typedef std::map< int /*ientry2*/, int /*freq*/ >::iterator ITER2;
     typedef std::map< int /*ientry2*/, int /*freq*/ >::const_iterator CITER2;

     // Ключевые слова с быстрым поиском
//     std::multimap< int, int /*keywords[*]*/  > keywords_map;
     std::map< int, int > keywords_map;

     #if defined LEM_DEBUGGING==1
     lem::Guardian guard2;
     #endif

     Document_Index( const Document_Index& );
     void operator=( const Document_Index& );

    public:
     const Indexer_Operation *operation;
     bool good; // Можно ли использовать индекс
     DocIndex idoc; // индекс документа в общем списке зоны
     boost::posix_time::ptime build; // Когда создан индекс

     #if defined FAIND_DATAMINE
     Solarix::Search_Engine::Doc_Topic *topic; // найденная или загруженная тема документа
     #endif

     #if defined LEM_DEBUGGING==1
     inline void Assert(void) const
     {
      guard1.Assert();
      guard2.Assert();
     }
     #endif

    public:
     Document_Index( const Indexer_Operation *Operation, DocIndex iDoc );

     ~Document_Index(void);

//     inline void set_Minbound( Real1 v ) { minbound=v; }
//     inline Real1 get_Minbound(void) const { return minbound; }

     // Запоминаем очередное ключевое слово (его индекс
     // в общей таблице ключевых слов который хранится в
     // классе Indexer).
     inline void RegisterWord( int catalog_index )
     {
      IFDEBUG(Assert());
      if( keywords_map.find( catalog_index )==keywords_map.end() )
       {
        keywords_map.insert( std::make_pair( catalog_index, CastSizeToInt(word_list.size()) ) );
        word_list.push_back(catalog_index);
       }
      IFDEBUG(Assert());
     }

     // Альтернатива методу Register_Word - дополнительно
     // накапливаем статистику по частотам слов.
     inline void RegisterFrequency( int catalog_index )
     {
      IFDEBUG(Assert());
      std::map< int, int >::const_iterator i = keywords_map.find( catalog_index );
      if( i==keywords_map.end() )
       {
        keywords_map.insert( std::make_pair( catalog_index, CastSizeToInt(word_list.size()) ) );
        word_list.push_back(catalog_index);
        freq_list.push_back(1);
       }
      else
       freq_list[ i->second ]++;
      IFDEBUG(Assert());
     } 

     inline void RegisterProximity( int catalog_index )
     { prox.push_back(catalog_index); } 


     // Завершено чтение и регистрации лексем очередного предложения
     void SentenceFinished(void);
     void SentenceFinished( Zone_Proximity &zone_prox );

     // Индексация документа завершена, можно выполнять финальные операции
     void Completed(void);
  
     void Build( Indexer *Catalog, Solarix::Dictionary *dict );

     // Для документа построена матрица близости слов?
     inline bool HasProxMatrix(void) const
     {
      return lem::fpos64_not_zero(prox_beg);
     }

     void SaveBin( lem::Stream& bin ) const;
     void LoadBin( lem::Stream& bin );

     // Сколько ключевых слов в документе
     inline int Size(void) const
     {
      IFDEBUG(Assert());
      return CastSizeToInt(word_list.size());
     }

     inline const lem::MCollect<Index_Entry>& GetKeywords(void) const
     {
      IFDEBUG(Assert());
      return word_list;
     }

     inline const lem::MCollect<int>& GetFreqs(void) const
     {
      IFDEBUG(Assert());
      return freq_list;
     }
  

     inline const LINKS& GetLinks(void) const
     {
      IFDEBUG(Assert());
      return links;
     }

     // Поиск точного соответствия (без регистра) слова
     // среди ключевых слов документа.
     bool Find( const Indexer &Catalog, const UCString &Word ) const;

     // Для слова, которое найдено в общем справочнике ключевых слов,
     // выполняется проверка его присутствия в документе.
     inline bool Find( int catalog_index ) const
//     { return keywords_map.find( catalog_index )!=keywords_map.end(); }
     {
      IFDEBUG(Assert());
      return std::find( word_list.begin(), word_list.end(), catalog_index )!=word_list.end();
      // Так как вектор word_list был отсортирован после индексации документа,
      // то для поиска можем применить быстрый поиск дихотомией. 
//      return std::binary_search( word_list.begin(), word_list.end(), catalog_index );
/*
      for( int i=0; i<word_list.size(); i++ )
       if( word_list[i] == catalog_index )
        return true;

      return false; 
*/
     }


    int FindProxCatIndex( int super_index ) const;
    int FindLocalKeywordIndex( int super_index ) const;

    bool TestProximity( lem::Stream &bin, int icat1, int ibit2, int ikey2 ) const;

    void SaveTmpProx( lem::Stream &bin );

    int GetWordFreq( int super_index ) const;
   };


   struct File_Entry;
   class ProximityMatrixProber : boost::noncopyable
   {
    private:
     friend class IndexReaderFaind;
     const File_Entry *file_entry;
     lem::Ptr<lem::BinaryFile> bin;
     
    public:
     ProximityMatrixProber(void); 
     
     bool TestProximity( int icat1, int ibit2, int ikey2 ) const;
   };

   // ***********************************
   // Одна запись в каталоге индексов.
   // ***********************************
   struct File_Entry
   {
    public:
     enum Status {
                  Unknown, Created, Updated, Deleted,
                  Untouched /* документ должен быть проверен на изменения - выставляется перед началом
                               переиндексации динамической зоны */
                 };

     Document_Index *idx; // сам индекс документа
     File_Location name;  // имя документа и прочие хар-ки (время создания, обновления, размер)

     lem::uint16_t i_file; // индекс имени файла (stor_files в Indexer),
                           // где хранится индекс документа.

     DocIndex i_indexed_file; // индекс описателя документа в линейном списке indexed_files    

     lem::Stream::pos64_type offset; // Размещение индекса в файле


    private:
     lem::uint8_t status;

    public:
     File_Entry(void)
     {
      idx=NULL;
      i_file=(lem::uint16_t)UNKNOWN;
      i_indexed_file=(DocIndex)UNKNOWN;
      lem::fpos64_clear(offset);
      status=/*Status::*/Created;
     }


     #if LEM_DEBUGGING==1
     inline void Assert(void) const 
     {
      #if LEM_DEBUGGING==1 && defined LEM_MSC
      LEM_CHECKIT_Z( !idx || _CrtIsValidHeapPointer(idx) == TRUE );
      #endif
     }
     #endif

     void SaveBin( lem::Stream& bin ) const;
     void LoadBin( lem::Stream& bin );

     // Удаляем индекс документа - он хранится на диске и
     // не должен постоянно висеть в памяти.
     inline void Purge(void)
     {
      IFDEBUG(Assert());
      lem_rub_off(idx);
     }

     inline bool IsAvailable(void) const
     {
      IFDEBUG(Assert());
      return i_file != static_cast<lem::uint16_t>(UNKNOWN);
     }

     // Если документ был (пере)индексирован
     inline bool IsChanged(void) const
     { return status==/*Status::*/Created ||
              status==/*Status::*/Updated ||
              status==/*Status::*/Deleted ||
              status==/*Status::*/Untouched;
     }

     inline void SetDeleted(void)
     {
      status=/*Status::*/Deleted;
      name.clear();
     }

     inline void SetUpdated(void)
     {
      status=/*Status::*/Updated;
     }

     inline void SetUnchanged(void)
     {
      status=/*Status::*/Unknown;
     }

     inline void SetUntouched(void)
     {
      status=/*Status::*/Untouched;
     }

     inline bool IsDeleted(void) const
     { return status==/*Status::*/Deleted; }

     void RebasePath( const lem::UFString &old_prefix, const lem::UFString &new_prefix );
   };



   // ********************************************************
   // Описание местоположения блока ассоциированных файлов
   // ********************************************************
   struct Assoc_Handle
   {
    int super_index; // keyword ID
    lem::uint16_t i_stor_file; // database filename
    lem::Stream::pos64_type offset; // Start position of data in the file

    Assoc_Handle(void)
    {
     super_index=UNKNOWN;
     i_stor_file=(lem::uint16_t)UNKNOWN;
     lem::fpos64_clear(offset);
    }
   };


   struct Assoc_Hash_Array
   {   
    enum { N_RANGE=256 }; // на сколько поддиапазонов разбит весь диапазон.    
    enum { RANGE_MASK=N_RANGE-1 };

    lem::uint16_t i_stor_file[N_RANGE];  // индекс имени файла БД, где хранится группа данных (список
                                         // файлов БД - поле stop_files в Indexer). Для каждого 
                                         // значения хэш-кода может быть отдельный файл.

    lem::Stream::pos64_type offset[N_RANGE]; // смещения в файлах для начала данных - по группам хэша
    bool dirty;                             // были ли изменения (нужно записывать в файл)

    Assoc_Hash_Array(void);

    void SaveBin( lem::Stream &bin );
    void LoadBin( lem::Stream &bin );

    void Clear(void);
   };

   // *****************************************************************
   // Keyword ID (or super index) is translated to hash code
   // *****************************************************************
   inline int Superindex_2_Hash( int Index )
   {
    return Assoc_Hash_Array::RANGE_MASK & Index;
/*
    return 0x000000ffU & ((Index >> 24) ^
                          (Index >> 16) ^
                          (Index >> 8));
*/
   }



   // **************************************************
   // Список файлов, ассоциированных с ключевым словом.
   // Список может быть задан либо через id описателей
   // документов, либо через список файловых путей.
   // **************************************************
   class Assoc_Files : public lem::MCollect<DocIndex> // индексы описателей проиндексированых
                                                 // файлов (см. поле data_files в Indexer)
   {
    private:
     bool All; // КВАНТОР "ВСЕ" для работы со стоп-словами.

     friend class IndexWriterFaind;

     lem::PtrCollect<lem::Path> paths; 

     std::map<int,int> i_files; // для быстрого поиска и проверки наличия индекса файла

     void Build(void);

     Assoc_Handle handle; // описатель размещения сохраняем для возможности
                          // сохранения измененного списка. 

//     inline void clear(void) { lem::MCollect<DocIndex>::clear(); }

    public:
     Assoc_Files(void) { All=false; }
     Assoc_Files( Assoc_Handle &Handle ) : handle(Handle) { All=false; }

     void SaveBin( lem::Stream &bin );
     void LoadBin( lem::Stream &bin );

     static void SaveBin( lem::Stream &bin, lem::MCollect<DocIndex> &v );

     void Clear(void);
  
     // Добавление (с контролем уникальности) элемента.
     inline bool Add( int iFile )
     {
      if( i_files.find( iFile )==i_files.end() )
       {
        /*lem::MCollect<DocIndex>::*/push_back(iFile);
        i_files.insert( std::make_pair( iFile, iFile ) );
        return true;
       }

      return false;
     }

     // Добавление (без контроля уникальности) элемента.
     inline void AddDirect( int iFile )
     {
      /*lem::MCollect<DocIndex>::*/push_back(iFile);
      i_files.insert( std::make_pair( iFile, iFile ) );
     }

     void AddDirect( lem::Path *path );

     inline bool Find( int iFile ) const
     { return i_files.find( iFile )!=i_files.end(); }

     inline bool Find( const lem::Path &p ) const;

     // Арифметика над множествами индексов файлов. Используется во время
     // обработки запросов с логическими условиями.
     void Or( const Assoc_Files &b, int limit=lem::int_max );
     void Minus( const Assoc_Files &b );  
     void And( const Assoc_Files &b );

     inline void SetAllFlag(void) { All=true; }
     inline bool IsAll(void) const { return All; }

     // Ограничиваем число элементов в списке документов до
     // указанной величины.
     void LimitTo( int maxhitcount );

     int CountIds(void) const { return CastSizeToInt(size()); }
     int CountPaths(void) const { return CastSizeToInt(paths.size()); }
     bool empty(void) const; 

     const lem::Path& GetPath( int i ) const { return *paths[i]; }
   };

   struct Echo_Options;


   // **************************************************
   // This structure stores the statistics for one zone
   // **************************************************
   struct Zone_Statistics
   {
    int index_count;     // number of zones
    int stor_files;      // number of database files

    lem::uint64_t occupied;  // disk space occupied

    int docs;            // number of indexed documents
    lem::uint64_t docs_size; // total size of indexed docs
    int keywords;        // number of keywords

    Zone_Statistics(void) { index_count=stor_files=docs=keywords=0; occupied=docs_size=0; }

    void operator += ( const Zone_Statistics &x )
    {
     index_count++;
     stor_files += x.stor_files;;
     occupied   += x.occupied;
     docs       += x.docs;
     keywords   += x.keywords;
     docs_size  += x.docs_size;
    }
   };

  
   #if defined FAIND_INDEXER
   // **************************************************
   // Имена файлов, в которых хранятся части индекса
   // **************************************************
   struct Storage : lem::NonCopyable
   {
    lem::Path folder;            // каталог, где размещаются все файлы БД индекса (одна зона - один каталог)

    lem::Path kwd_path;          // путь к файлу "keywords" БД (ключевые слова)

    lem::Path docs_path;         // путь к файлу "documents" БД (проиндексированные документы)
    lem::Path docspos_path;      // путь к файлу с позициями описаний документов в docs_path

    lem::Path files_path;        // путь к файлу "dbfiles" БД (файлы БД) 
    lem::Path assoc_hashes_path; // путь к файлу "assoc_hashes" БД 
    lem::Path prox_path;         // путь к файлу "prox_matrix" БД - матрица близости для зоны и другая общезоновая информация
    lem::Path status_path;       // файл с метками о статусе зоны (степень завершенности индекса)
    lem::Collect<UFString> stor_files; // Файлы, в которых записаны индексы

    lem::Math::RandU rnd_file; // для генерации случайного имени файла

    lem::zeroed<bool> dirty;     // флаг - список нужно записать на диск

    Storage(void) {}

    void SetFolder( const lem::Path &Folder, lem::int32_t trans_id=-1 );

    // Создаем новое незанятое имя для файла данных в БД.
    void CreateNewFilename( lem::Path &new_filename, int &i_new );

    inline void AddStorFile( const UFString &FileName )
    {
     LEM_CHECKIT_Z( !FileName.empty() );
     dirty = true;
     stor_files.push_back(FileName);
    }

    void LoadPath( lem::Path &path, lem::Stream &bin );

    void LoadBin( lem::Stream &bin );
    void SaveBin( lem::Stream &bin );

    // Сколько всего файлов в хранилище этого индекса
    int Count(void) const;

    void Clear(void);
   };
   #endif
 
   #if defined FAIND_INDEXER
   // **************************************************
   // Состояние индекса.
   // **************************************************
   struct Zone_Status
   {
    enum { BadStatus=-1, EmptyStatus=0, CompleteStatus=1000 }; // Степень завершения зоны

    int version;
    boost::posix_time::ptime finished; // время, когда была завершена индексация зоны
    int status; 

    Zone_Status(void)
    { clear(); }

    void clear(void)
    {
     version=0;
     status=BadStatus;
     finished=boost::date_time::not_a_date_time;
    }

    inline bool ok(void) const { return status==CompleteStatus; }

    // Принудительно выставляем нормальный статус
    inline void SetOk(void) { status=CompleteStatus; }

    inline void Failed(void) { status=BadStatus; }

    void LoadBin( lem::Stream &bin );
    void SaveBin( lem::Stream &bin ) const;
   };
   #endif

   // *********************************************
   // Список проиндексированных документов.
   // *********************************************
   struct DocumentsList : lem::NonCopyable
   {
    typedef std::multimap< lem::UFString::hash_type, File_Entry* >::const_iterator C_ITER;
    typedef std::multimap< lem::UFString::hash_type, File_Entry* >::iterator V_ITER;

    std::vector<File_Entry*> indexed_files;
    std::multimap< lem::UFString::hash_type, File_Entry* > files;
    lem::zeroed<bool> dirty; // список был изменен и нужно сохранять его

    DocumentsList(void) {}
    ~DocumentsList(void);

    inline void AddIndexedFile( File_Entry *entry )
    {
     files.insert( std::make_pair( entry->name.GetName().GetHash(), entry ) );
     entry->i_indexed_file = CastSizeToInt(indexed_files.size());
     indexed_files.push_back(entry);
     dirty = true;
    }

    inline int Count(void) const { return CastSizeToInt(indexed_files.size()); }

    inline bool Loaded(void) const { return indexed_files.empty()==false; }

    inline const File_Entry& Get( int i ) const { return *indexed_files[i]; }
    inline       File_Entry& Get( int i )       { return *indexed_files[i]; }

    void Clear(void);

    void LoadBin( lem::Stream &bin );
    void SaveBin( lem::Stream &bin );

    #if LEM_DEBUGGING==1
    void Assert(void) const;
    #endif

    void RebasePaths( const lem::UFString &old_prefix, const lem::UFString &new_prefix );
   };


   class DocumentIterator;
   class IndexManager;
   class Crawler_Operation;
   class Topic_Finder;
   struct Hit_Statistics;


   // *************************************
   // Индексатор
   // *************************************
   class Indexer : lem::NonCopyable
   {
    public:
     Domain_Info domain_info;        // описание индекса. храним копию, а не ссылку,
                                     // которая станет некорректной в условиях многопоточности. 
     Indexer_Operation operation;    // управляющие параметры
     Zone_Status zone_status;        // статус загруженной зоны
     Word_Searcher keywords;         // Общий список ключевых слов


     // Используемые индексатором грамматические модули, подгружаемые
     // и управляемые поисковым движком.
     lem::CPtr<Solarix::Dictionary> sol_id;
     lem::CPtr<Solarix::Search_Engine::Fuzzy_Comparator> fuzzy_eq;
     lem::CPtr<const Solarix::Search_Engine::Lexer_Options> lexer_options;
     #if defined FAIND_DATAMINE
     lem::CPtr<Solarix::Search_Engine::Topic_Finder> topic_finder;
     #endif 
     lem::CPtr<const Solarix::Search_Engine::Search_Options> searching;
     #if !defined SOL_NO_AA
     //lem::CPtr<Solarix::Text_Processor> tpu;
     #endif

     static wchar_t Command_Delimiter_Char;

    protected:
     boost::shared_ptr<DocumentIterator> document_iterator; // открытый интерфейс доступа к списку документов
     const Echo_Options* echo;
     const General_Options* generals;
     IndexManager* manager;
     Solarix::Dictionary *dictionary;
     const Solarix::LD_Seeker *seeker;

     // Должен вернуть имя движка индексатора.
     virtual FString GetEngineName(void) const;

     int GetRealDomainId(void) const;
     virtual void RebaseDocumentPath( File_Entry &entry );

    public:
     Indexer(
             IndexManager *Manager,
             const Domain_Info &Domain_info,
             Solarix::Dictionary *ptrDict,
             const LD_Seeker *seeker,
             const Echo_Options *Echo,
             const General_Options *Generals
            );

     virtual ~Indexer(void);

     // Загрузка индекса в память для читателей, подготовка буферов и 
     // потоков для писателей.
     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );


     // Для обновителей: надо ли переиндексировать документ
     virtual bool IsFileChanged( const File_Location &filename );

     // Индексация области завершена - записываем все необходимые структуры,
     // выполняем построение списков.
     virtual void Commit(void);

     // Добавляется ключевое слово и возвращается его индекс в общем списке.
     inline int AddKeyword( const UCString &Word, Morphology m )
     { return keywords.AddKeyword(Word,m); }

     inline const Word_Searcher& GetSearcher(void) const { return keywords; }

     // Среди накопленных ключевых слов пытаемся найти равное Word. Если успешно,
     // возвращается обобщенный уникальный ключ слова (см. для
     // справки функцию Get_Keyword). Если не найдена - вернет UNKNOWN.
     inline int FindKeyword( const UCString &Word, Morphology morph ) const
     { return keywords.Find(Word,morph); }

     inline void FindKeywords(
                              const UCString &Word,
                              Fuzzy_Comparator *equator,
                              std::set<int> &result
                             ) const
     { keywords.FindKeywords(Word,equator,result); }

     inline void FindKeywordsRoots(
                                   const UCString &Word,
                                   std::set<int> &result
                                  ) const
     { keywords.FindKeywordsRoots(Word,result); }


     #if !defined FAIND_NO_BOOST_REGEX
     void FindKeywordsRegex(
                            const boost::wregex &Word,
                            std::set<int> &ind_list,
                            lem::MCollect<UCString> &str_list
                           ) const
     { keywords.FindKeywordsRegex(Word,ind_list, str_list); }
     #endif 

     virtual int FindKeywordSlow( const UCString &Word, Morphology morph ) const;
     virtual void FindKeywordsSlow(
                                   const UCString &Word,
                                   Fuzzy_Comparator *equator,
                                   std::set<int> &result
                                  ) const;


     inline bool IsSolarixKeyword( int superindex ) const
     { return keywords.IsSolarixKeyword(superindex); }

     inline const UCString& GetKeyword( int super_index ) const
     { return keywords.GetKeyword(super_index); }

//     void Load( File_Entry* pfile );

     // Returns the list of file indeces that associated with keyword.
     virtual Assoc_Files* GetAssocFiles( int super_index, const Pattern &pattern );
     virtual Assoc_Files* GetAssocFiles( int super_index1, int super_index2, const Pattern &pattern );
     virtual Assoc_Files* GetAllFiles(void);
     virtual Assoc_Files* GetAssocFiles( const Pattern &pattern );

     // Интерфейс для запоминания дополнительной метаинформации для файла
     virtual void SetTagForFile(
                                const lem::UFString &path,
                                File_Location::LocType loctype,
                                const lem::UFString &loc, 
                                const lem::UFString &tag,
                                const lem::UFString &value
                               );

     // Получение значения тега для указанного документа.
     virtual bool GetTagForFile(
                                const lem::UFString &filename,
                                File_Location::LocType loctype,
                                const lem::UFString &fileloc, 
                                const lem::UFString &tag,
                                lem::UFString &value
                               );


     // Следующие два метода реализуются индексаторами, которые не
     // поддерживают морфологию и явный справочник лексем.

     // поиск по одному слову, если prefix=true, то выполняется поиск по совпадению начала слова с word
     virtual Assoc_Files* GetAssocFiles( const UCString &word, bool Prefix, int maxhitcount, const Pattern &pattern );
 
     // поиск по альтернативным словам (OR)
     virtual Assoc_Files* GetAssocFiles( const MCollect<UCString> &words, int maxhitcount, const Pattern &pattern );

     virtual void PreparePrefetchingKeywords(void);
     virtual void FinishPrefetchingKeywords(void);
     virtual void PrefetchKeyword( const UCString &Word );

//     virtual Document_Index* CreateDocIndex(void) const;

     #if defined FAIND_DATAMINE
     virtual boost::shared_ptr<Doc_Topic> LoadDocumentTopic( int i_file );
     #endif

     // Распечатка проиндексированных файлов в указанном формате
     virtual void DumpFiles( const lem::Path &filename, const wchar_t *format );

     // Распечатка информации о состоянии текущего индекса.
     virtual void PrintInfo( OFormatter &out, bool detailed=false );

     // Статистическая информация об загруженном индексе.
     virtual Zone_Statistics GetZoneStat(void);

     static void PackDomainCommands( UFString &cmd, const Collect<UFString> & args );
     static void UnpackDomainCommands( const UFString &cmd, Collect<UFString> & args );

     virtual void AddDocument( const File_Location &filename, Base_File_Reader *reader );

     virtual bool LoadDocumentIndex( File_Entry *file_entry );

     // Должно быть перегружено у потомков: поддерживает ли
     // индексатор морфологию.
     virtual bool DoesSupportMorphology(void) const;

     // Должно быть перегружено у потомков: поддерживает ли
     // индексатор операции по справочнику ключевых слов с
     // морфологией.
     virtual bool SupportSolarixKeywordsDictionary(void) const;

     virtual int GetDocumentId( int i );

     // Возвращается указатель на проиндексированный документ по это ID.
     // В зависимости от реализации возвращаемый объект может быть создан
     // только для данного вызова, или находится в ранее загруженном списке.
     virtual boost::shared_ptr<File_Entry> GetDocumentById( int id_doc );

     // Возвращает ID указанного по линейному индексу-перечислителю документа.
     virtual boost::shared_ptr<File_Entry> GetDocumentByIndex( int id_doc );

     // Должен вернуть общее количество проиндексированных документов.
     virtual int CountDocuments(void);

     // Должен вернуть количество ключевых слов в справочнике.
     virtual int CountKeywords(void);

     virtual void DumpHTML( const lem::Path &filename );
     virtual void DumpCSV( const lem::Path &filename );
     virtual void DumpTXT( const lem::Path &filename );
     
     virtual ProximityMatrixProber* GetProximityMatrixProber( const File_Entry *file_entry );

     virtual bool IsActiveSearcher( const Pattern &pattern ) const;

     // Индексатор сам выполнить просмотр области индексирования.
     virtual bool IsActiveWriter(void) const;

     // Индексатор не умеет сам выполнять файловый поиск и нуждается
     // в помощи краулера.
     virtual bool NeedsExternalFilesearch(void) const;

     // Метод вызывается для активных индексаторов - которые сами выполняют
     // просмотр области индексирования. Через аргумент stat возвращается 
     // статистика - кол-во обработанных файлов.
     virtual void Run( Solarix::Search_Engine::Hit_Statistics &stat );


     // Некоторые индексаторы в принципе не поддерживают полнотекстовый поиск,
     // например locate.
     virtual bool SupportFulltextSearch(void) const;

     // Если индексатор умеет запоминать и отдавать тени для файлов
     virtual bool SupportMetainfo(void) const;

     // Для синхронизации открытого ридера с файлами базы на диске
     virtual void ReopenIfNeeded(void) {}


     // Задание максимального количества индексаторов в кэше. 0-кэш отключается.
     virtual void SetMaxPoolSize( int n );
   };

 
   // *********************************************
   // Центр управления индексаторами.
   // *********************************************
   class IndexManager : lem::NonCopyable
   {
    private:
     Solarix::Dictionary* dictionary; // грамматическая машина
     const Solarix::LD_Seeker* seeker;
     lem::Ptr<Idb_List> idb_list; // каталогизатор
  
     #if defined FAIND_FILEMON
     Folder_Monitor folder_monitor;
     #endif

     #if defined LEM_THREADS   
     lem::Process::CriticalSection cs;
     #endif

     int MaxPoolSize; // максимальное количество закэшированных в пуле индексов
     lem::Collect< boost::shared_ptr<Indexer> > index_pool; // пул загруженных индексов

     // Удаляем из пула индексов объект для указанной зоны
     bool PurgeIndexPool( int id_index );

     // Пул соединение с SQL серверами.
     lem::Collect< std::pair< Remote_Zone, lem::Ptr<SQLConnection> > > connections;

     lem::Ptr<SQLConnection> FindConnection( const Remote_Zone &server );

    public:
     enum { Version=12 }; // Код текущей версии индексой БД

     static int count_writer, count_reader, count_updater; // для учета активных индексаторов

     const Echo_Options *echo;
     const General_Options *generals;
     const Indexer_Options *options;

    public:
     IndexManager(
                  Solarix::Dictionary *ptrDict,
                  const Solarix::LD_Seeker* Seeker,
                  const Indexer_Options *Options,
                  const Echo_Options *Echo,
                  const General_Options *Generals
                 );

     virtual ~IndexManager(void);

     // Печать сведений о реализации хранилища.
     virtual void PrintVersion( OFormatter &out, const lem::UI::Resource_List &resx ) const;

     inline       Idb_List& GetDomains(void)       { return *idb_list; }
     inline const Idb_List& GetDomains(void) const { return *idb_list; }

     #if defined FAIND_FILEMON
     void StartMonitoring( Change_Event_Func func );
     void StopMonitoring(void);
     inline const Folder_Monitor& GetFolderMonitor(void) const { return folder_monitor; }
     void MonitorDynamicZone( int id_zone );
     int FindIndexToRefresh(void);
     #endif

     // Удаление всех индексов
     void DeleteAllIndexes(void);

     // Распечатка списка индексов
     virtual void ListDomains( OFormatter &out, const lem::UI::Resource_List &resx );
     virtual void ListSharedDomains( OFormatter &out, const lem::UI::Resource_List &resx );

     // Показ общей статистики по индексам.
     virtual void ShowTotals( OFormatter &out, const lem::UI::Resource_List &resx );

     // Полная очистка индекса, его объявление остается в списке.
     virtual void PurgeDomain( const UFString &domain_name );

     // Задание нового примечания для индекса
     virtual void SetDomainComment( const UFString &domain_name, const UFString &text );

     // Удалание индекса из списка, очистка диска
     virtual void DeleteDomain( const UFString &domain_name );

     // Переименование индекса
     virtual void RenameDomain( const UFString &domain_name, const UFString &new_name );

     // Сохранение корневой таблицы в указанном каталоге.
     virtual void BackupDomainsList( const lem::Path &dest_folder );

     // Восстановление корневой таблицы из резервной копии в указанном каталоге.
     virtual void RestoreDomainsList( const lem::Path &dest_folder );

     // Сохранение индекса в указанном каталоге.
     virtual void BackupDomain( const UFString &domain_name, const lem::Path &dest_folder );

     // Восстановление индекса из резервной копии в указанном каталоге.
     virtual void RestoreDomain( const UFString &domain_name, const lem::Path &dest_folder );

     // Изменение режима общего доступа для индекса
     virtual void ShareDomain( const UFString &domain_name, bool shared );
     virtual void ShareDomain( int id_zone, bool shared );

     // Статистическая информация по всем загруженным зонам
     // Аргумент - для индикации прогресса при обработке большого
     // количества индексных баз.
     virtual Zone_Statistics GetTotalZonesStat(
                                               OFormatter &out 
                                               #if defined FAIND_SIGNALS
                                               , boost::signal2< void, lem::OFormatter&, const wchar_t* > &progress
                                               #endif 
                                              );


     // Краткая статистика по выбранному индексу
     virtual void PrintDomainInfo( const UFString &domain_name, OFormatter &out, bool detailed=false );

    // Для указанного индекса печатается список проиндексированных документов.
    virtual void DumpFiles(
                           const UFString &domain_name,
                           const lem::Path &filename,
                           const wchar_t *format
                          );

    virtual bool IndexNeedsPurgedBeforeUpdate( int id_zone );

    virtual boost::shared_ptr<Indexer> GetReader( const Indexer_Operation &operation, const Crawler_Operation &engine_command );
    virtual boost::shared_ptr<Indexer> GetWriter( const Indexer_Operation &operation, const Crawler_Operation &engine_command );
    virtual boost::shared_ptr<Indexer> GetUpdater( const Indexer_Operation &operation, const Crawler_Operation &engine_command );

    boost::shared_ptr<Indexer> GetReader( const UFString &zone_name );

    virtual void ZoneNeedsReindexing( int id_zone, lem::Collect< lem::Path* > &changed_files );
    virtual void ZoneNeedsReindexing( int id_zone );

    // Пытаемся заблокировать указанный индекс, возвращаем true в случае успеха.
    virtual bool LockByReader( int id_index );
    virtual bool LockByWriter( int id_index );

    virtual bool IsLockedByReader( int id_index );
    virtual bool IsLockedByWriter( int id_index );

    // Пытаемся заблокировать указанный индекс, возвращаем true в случае успеха.
    virtual void UnlockByReader( int id_index );
    virtual void UnlockByWriter( int id_index );

    virtual void UnlockAll(void);
    virtual void Unlock( const UFString &domain_name );

    inline SQLConnection& GetConnection(void) { return *(options->connection); }

    virtual void PrintSessions( OFormatter &out, const lem::UI::Resource_List &resx ) const;

    // Импорт описаний индексов с удаленного сервера
    virtual void ImportDomains( SQLConnection &c );

    // Корректно ли имя индекса, то есть не содержит ли оно запрещенных символов
    bool VerifyNameChars( const lem::UFString &zone_name ) const;

    void SetMaxPoolSize( int n ) { MaxPoolSize=n; }
   };



   class DocumentIterator
   {
    public:
     DocumentIterator(void) {}
     virtual ~DocumentIterator(void) {}

     virtual int Size(void) const=0;
     virtual int GetDocId( int i ) const=0;
   };




  } // namespace Search_Engine
 } // namespace Solarix

#endif
