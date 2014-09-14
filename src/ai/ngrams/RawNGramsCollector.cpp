#if !defined(SOL_NO_NGRAMS)

#include <lem/logfile.h>
#include <lem/solarix/NGramsCollectors.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/ngrams_hashing.h>

using namespace std;
using namespace lem;
using namespace Solarix;

static lem::FString to_utf8( const lem::UCString &u )
{
 return lem::to_utf8( u.c_str() );
}



class NGrams2DiskCache : public NGrams2Cache
{
 private:
  struct Mark
  {
   lem::int64_t file_pos;
   int n;
   int n_free;

   Mark(void):file_pos(0), n(0), n_free(0) {}
  };

  #if defined LEM_MSC
  __declspec(align(4))
  #elif defined LEM_GNUC
  #pragma pack(4)
  #endif
  struct Cached2Gram
  {
   lem::int32_t first;
   lem::int32_t second;
   lem::int32_t id, w;

   Cached2Gram(void) : first(UNKNOWN), second(UNKNOWN), id(UNKNOWN), w(0) {}

   inline bool operator==( const Cached2Gram &q ) const
   { return first==q.first && second==q.second; }

   inline bool operator>( const Cached2Gram &q ) const
   { return first>q.first || (first==q.first && second>q.second); }
  };

  #if defined LEM_64
  enum { N_BLOCKS=10000000, ITEMS_PER_BLOCK=32 };
  #else
  enum { N_BLOCKS=1000000, ITEMS_PER_BLOCK=128 };
  #endif

  int QUEUE_LEN; // максимальная длина очереди команд на изменение базы

  char mode; // режим записи-чтения ('w'-'r')

  struct QueueItem2
  {
   int i_block;
   int i1, i2;
   int freq;
  }; 

  static bool q_sorter( const QueueItem2 &x, const QueueItem2 &y );
  static bool c_sorter( const Cached2Gram &x, const Cached2Gram &y );

  lem::MCollect<QueueItem2> queue;

  Cached2Gram *ngrams_buffer; // буфер для служебных операций - используется при копировании
  int ngrams_buffer_size;     // списков на новое место, сортировке и так далее.

  Mark *marks;
  lem::Path filename; // полный путь для файла с базой
  lem::Path tmp_filename; // полный путь с черновым вариантом файла базы 
  int id_seq;
  lem::Ptr<lem::BinaryFile> file;

  lem::int32_t max_freq;

  void FlushQueue(void)
  {
   LEM_CHECKIT_Z( mode=='w' );

   if( queue.empty() )
    return;

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( "Entering Cached2Gram::FlushQueue\n" );

   if( echo )
    {
     lem::mout->printf( "%vf3Flushing disk cache%vn - %vfE%d%vn items in queue ", CastSizeToInt(queue.size()) );  
     lem::mout->flush();
    }

   std::sort( queue.begin(), queue.end(), q_sorter );

   int i_block=queue.front().i_block;
   int iq0=0;

   int n_inserted=0, n_updated=0;

   for( lem::Container::size_type i=0; i<=queue.size(); ++i )
    {
     if( echo && !(i%1000000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      }

     if( i==queue.size() || queue[i].i_block!=i_block )
      {
       // Команды от iq0 до i (не включая) применяются к одному блоку в файле.
       Mark &mark = marks[i_block];
       const int n_cmd = i-iq0;

       if( ngrams_buffer_size<(mark.n+n_cmd) )
        {
         delete[] ngrams_buffer;
         ngrams_buffer_size = mark.n+n_cmd+256; 
         ngrams_buffer = new Cached2Gram[ngrams_buffer_size];
        }

       int i_buf=0;   
       if( mark.n>0 )
        {
         // Загрузим имеющиеся записи с диска в буфер
         file->seekp64( mark.file_pos );
         file->read( ngrams_buffer, sizeof(Cached2Gram)*mark.n ); 
         i_buf = mark.n;
        }

       // Просматриваем команды из поддиапазона (iq0,i) и переформируем список N-грамм.
       for( lem::Container::size_type j=iq0; j<i; ++j )
        {
         const int i1 = queue[j].i1; 
         const int i2 = queue[j].i2; 

         bool found=false;
         for( int k=0; k<i_buf; ++k )
          if( ngrams_buffer[k].first==i1 && ngrams_buffer[k].second==i2 )
           {
            ngrams_buffer[k].w += queue[j].freq;
            max_freq = std::max( max_freq, ngrams_buffer[k].w );
            n_updated++;
            found=true;
            break; 
           }

         if( !found )
          {
           // Надо добавить элемент в буфер.
           ngrams_buffer[i_buf].first  = queue[j].i1;
           ngrams_buffer[i_buf].second = queue[j].i2;
           ngrams_buffer[i_buf].w      = queue[j].freq;
           ngrams_buffer[i_buf].id     = id_seq++;
           max_freq = std::max( max_freq, ngrams_buffer[i_buf].w );
           i_buf++;
           n_inserted++;
          } 
        }

       // Проверим, что новый блок вместится на место старого.
       if( i_buf>=(mark.n+mark.n_free) )
        {
         // надо переразмещать блок.
         file->seekp64( 0, SEEK_END );
         mark.file_pos = file->tellp64();
         const int n_expanded = i_buf*2+32;
         mark.n_free = n_expanded-i_buf;
         mark.n = i_buf;

         file->write( ngrams_buffer, sizeof(Cached2Gram)*mark.n ); 
         for( int p=0; p<mark.n_free; ++p ) // допишем свободный хвост
          file->write( ngrams_buffer, sizeof(Cached2Gram) );
        }
       else
        { 
         mark.n_free = (mark.n_free+mark.n)-i_buf; // столько свободных ячеек осталось.
         mark.n = i_buf;
         file->seekp64( mark.file_pos );
         file->write( ngrams_buffer, sizeof(Cached2Gram)*mark.n ); 
        } 

       iq0 = i;

       if( i<queue.size() )
        i_block = queue[i].i_block;
      }  
    }

   if( echo )
    {
     lem::mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated %vfAOK%vn\n", n_inserted, n_updated );
    }

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( "Leaving Cached2Gram::FlushQueue\n" );

   queue.clear();

   return;
  }

 public:
  NGrams2DiskCache( char Mode ) : NGrams2Cache(), mode(Mode)
  {
   QUEUE_LEN = mode=='w' ? 10000000 : 0;

   marks = new Mark[N_BLOCKS];
   echo = false;

   if( QUEUE_LEN>0 )
    queue.reserve(QUEUE_LEN);

   ngrams_buffer = NULL;
   ngrams_buffer_size=0;

   max_freq = 0;

   id_seq=0;

   return;
  }

  virtual ~NGrams2DiskCache(void)
  {
   LEM_CHECKIT_Z( queue.empty() );
   delete[] ngrams_buffer; ngrams_buffer=NULL;
   delete[] marks; marks=NULL;

   // Закрываем файл контейнера, запись в него теперь невозможна.
   file.Delete();

   // Удаляем черновую базу.
   tmp_filename.DoRemove();
 
   return;
  }


  // ******************************************************************
  // Задеется максимальный размер очереди команд добавления,
  // по достижении этого предела начинается выгрузка очереди
  // в дисковый контейнер.
  // ******************************************************************
  virtual void SetBufferSize( int n )
  {
   if( n>0 && mode=='w' )
    {
     QUEUE_LEN=n;
     queue.reserve(n);
    }

   return;
  }

  // ******************************************************************
  // Открываем и готовим дисковый контейнер для накопления данных.
  // folder - это папка, где будет создан файл контейнера
  // table - имя хранимой таблицы N-грамм.
  // ******************************************************************
  void Open( const lem::Path &folder, const lem::FString &table )
  {
   // Формируем файл базы. Сначала мы будем формировать временную базу,
   // а потом скопируем окончательные данные в итоговый файл, одновременно
   // выполняя сжатие и сортировки.
   filename = folder;
   lem::Path fn(table);
   filename.ConcateLeaf( fn );

   if( mode=='w' )
    {
     tmp_filename = folder;
     lem::Path tmp_fn(table+L".tmp");
     tmp_filename.ConcateLeaf( tmp_fn );

     if( echo )
      {
       lem::mout->printf( "%vf3Creating db file %vfE%us%vn %vn...", tmp_filename.GetUnicode().c_str() );  
       lem::mout->flush();
      }

     file = new BinaryFile( tmp_filename, false, true );
     file->reopen( true, true, true );

     // Форматируем контейнер.
     const int block_space = ITEMS_PER_BLOCK; // на каждый поддиапазон N-грамм заранее выделяем
                                  // столько свободных элементов.

     ngrams_buffer_size = block_space*2;
     ngrams_buffer = new Cached2Gram[ngrams_buffer_size];

     for( int i=0; i<N_BLOCKS; ++i )
      {
       Mark &mark = marks[i];
       mark.file_pos = file->tellp64();
       mark.n=0;
       mark.n_free=block_space;
       file->write( ngrams_buffer, sizeof(Cached2Gram)*block_space ); 

       if( !(i%100000) && echo )
        {
         lem::mout->printf( '.' );
         lem::mout->flush();
        }
      }

     file->flush();

     if( echo )
      {
       lem::mout->printf( "%vfAOk%vn\n" );  
       lem::mout->flush();
      }
    }
   else if( mode=='r' )
    {
     // Открываем на чтение уже существующий файл контейнера
     file = new BinaryReader(filename);

     lem::uint64_t dummy=0;
     file->read( &dummy, sizeof(dummy) );

     lem::uint64_t marks_pos=0;
     file->read( &marks_pos, sizeof(marks_pos) );
     file->read( &max_freq, sizeof(max_freq) );

     file->seekp64( marks_pos );
     file->read( marks, sizeof(Mark)*N_BLOCKS );

     // Можем сразу определить максимальный размер буфера для чтения N-грамм.
     int n_max=0;
     for( int i=0; i<N_BLOCKS; i++ )
      n_max = std::max( n_max, marks[i].n );

     ngrams_buffer_size = n_max;
     ngrams_buffer = new Cached2Gram[ngrams_buffer_size];
    }
   
   return; 
  }


  virtual void InsertOrUpdate( int i1, int i2, int freq )
  {
   LEM_CHECKIT_Z( freq>0 );
   LEM_CHECKIT_Z( mode=='w' );

   const int i_block = ngram2hash(i1,i2) % N_BLOCKS;
   LEM_CHECKIT_Z( i_block>=0 && i_block<N_BLOCKS );

   if( CastSizeToInt(queue.size())>=QUEUE_LEN )
    FlushQueue();

   QueueItem2 q;
   q.i1=i1; q.i2=i2; q.i_block=i_block; q.freq=freq;
   #if LEM_DEBUGGING==1
   lem::Container::size_type iqueue = queue.size();
   #endif
   queue.push_back(q);

   return;
  }


  virtual std::pair<int,int> Select( int i1, int i2 )
  {
   LEM_CHECKIT_Z( mode=='r' );

   const int i_block = ngram2hash(i1,i2) % N_BLOCKS;
   LEM_CHECKIT_Z( i_block>=0 && i_block<N_BLOCKS );

   file->seekp64( marks[i_block].file_pos );
   Cached2Gram g;
   for( int i=0; i<marks[i_block].n; ++i )
    {
     file->read( &g, sizeof(g) );
     if( g.first==i1 && g.second==i2 )
      return std::make_pair(g.id,g.w);
    }
 
   return std::make_pair(-1,-1);
  }



  virtual void Commit(void)
  {
   LEM_CHECKIT_Z( mode=='w' );

   FlushQueue();

   if( echo )
    {
     lem::mout->printf( "%vf3Committing disk cache%vn..." );  
     lem::mout->flush();
    }

   // Формируем чистовой файл базы.
   lem::BinaryFile dbf( filename, false, true );
   dbf.reopen( true, true, true );

   // поле пока зарезервировано
   lem::uint64_t dummy=0;
   dbf.write( &dummy, sizeof(dummy) );

   lem::uint64_t marks_pos=0;
   dbf.write( &marks_pos, sizeof(marks_pos) );

   // Общее количество записей
   lem::int64_t n_recs=0;
   for( int i=0; i<N_BLOCKS; ++i )
    n_recs += marks[i].n;

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn 2grams ", n_recs );  
     lem::mout->flush();
    }

   dbf.write( &n_recs, sizeof(n_recs) );

   // Максимальная частота N-граммы
   dbf.write( &max_freq, sizeof(max_freq) );

   // Количество блоков
   lem::int32_t n_block=N_BLOCKS;
   dbf.write( &n_block, sizeof(n_block) );

   // Сортируем блоки и одновременно сжимаем неиспользуемое пространство.
   for( int i=0; i<N_BLOCKS; ++i )
    {
     file->seekp64( marks[i].file_pos );
     file->read( ngrams_buffer, sizeof(*ngrams_buffer)*marks[i].n );
     std::sort( ngrams_buffer, ngrams_buffer+marks[i].n, &c_sorter );
     marks[i].file_pos = dbf.tellp64();
     dbf.write( ngrams_buffer, sizeof(*ngrams_buffer)*marks[i].n );
    }

   // Впишем вектор Marks в конец файла
   marks_pos = dbf.tellp64();
   for( int i=0; i<N_BLOCKS; ++i )
    dbf.write( &marks[i].file_pos, sizeof(marks[i].file_pos) );

   for( int i=0; i<N_BLOCKS; ++i )
    dbf.write( &marks[i].n, sizeof(marks[i].n) );

   // В начало файла впишем позицию вектора
   dbf.seekp64( 0, SEEK_SET );

   dbf.write( &dummy, sizeof(dummy) );
   dbf.write( &marks_pos, sizeof(marks_pos) );

   dbf.seekp64( 0, SEEK_END );
   dbf.flush();

   if( echo )
    lem::mout->printf( " %vfE%qd%vn 2grams, %vfAOK%vn\n", n_recs );  

   return;
  }


  virtual void Upload( NGramsDBMS &db, const FString &sql )
  {
   LEM_CHECKIT_Z( mode=='w' );

/*
   FlushQueue();

   if( echo )
    {
     lem::mout->printf( "%vf3Uploading 2grams to DB%vn" );
     lem::mout->flush();
    }

   lem::int64_t total_count = 0;
   for( int i=0; i<N_BLOCKS; ++i )
    total_count += marks[i].n;

   char asql_buf[512];

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn records ", total_count );
     lem::mout->flush();
    }

   int n_insert=0;
   lem::FString inserts; inserts.reserve(10000);

   for( int i=0; i<N_BLOCKS; ++i )
    {
     if( echo && !(i%100000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      } 

     const Mark &mark = marks[i];
   
     LEM_CHECKIT_Z( mark.n<=ngrams_buffer_size );
     file->seekp64( mark.file_pos );
     file->read( ngrams_buffer, sizeof(Cached2Gram)*mark.n );

     for( int j=0; j<mark.n; ++j )
      {
       const Cached2Gram &g = ngrams_buffer[j];

       if( n_insert>=db.MaxBulkInsert() )
        {
         // пачку ранее накопленных INSERT'ов сбрасываем в базу.
         db.ExecuteSql(inserts.c_str());
         inserts.clear();
         n_insert=0;
        }

       if( n_insert==0 )
        inserts = sql;
    
       if( n_insert>=1 )
        inserts.Add_Dirty( " UNION ALL " );

       sprintf(
               asql_buf,
               #if defined SOL_SQLITE_NGRAMS
               " SELECT %d, %d, %d, %d ",
               #elif defined SOL_FIREBIRD_NGRAMS
               " SELECT %d, %d, %d, %d FROM RDB$DATABASE",
               #endif
               g.id, g.first, g.second, g.w
              );

       inserts.Add_Dirty( asql_buf );
       n_insert++;
      }
    }

   if( n_insert>0 )
    {
     db.ExecuteSql(inserts.c_str()); 
     inserts.clear();
    }

   if( echo )
    lem::mout->printf( " done\n" );
*/ 
   return; 
  }


  virtual void Print( NGramsDBMS &db, const lem::FString &sql, const lem::FString &format, OFormatter &to )
  {
   LEM_CHECKIT_Z( mode=='w' );

   FlushQueue();

/*
   if( echo )
    {
     lem::mout->printf( "%vf3Printing 2grams to text file using '%s' format%vn", format.c_str() );
     lem::mout->flush();
    }

   lem::int64_t total_count = 0;
   for( int i=0; i<N_BLOCKS; ++i )
    total_count += marks[i].n;


   bool csv = format.eqi("csv");
   bool xml = format.eqi("xml");

   char asql_buf[512];

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn records ", total_count );
     lem::mout->flush();
    }

   for( int i=0; i<N_BLOCKS; ++i )
    {
     if( echo && !(i%100000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      } 

     const Mark &mark = marks[i];
   
     LEM_CHECKIT_Z( mark.n<=ngrams_buffer_size );
     file->seekp64( mark.file_pos );
     file->read( ngrams_buffer, sizeof(Cached2Gram)*mark.n );

     for( int j=0; j<mark.n; ++j )
      {
       const Cached2Gram &g = ngrams_buffer[j];

       const int iword1 = g.first;
       const int iword2 = g.second;
       const lem::int32_t w = g.w;

       sprintf( asql_buf, sql.c_str(), iword1 ); 
       UFString word1( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword2 ); 
       UFString word2( db.SelectStr(asql_buf) );

       if( csv )       
        to.printf( "2;%us;%us;%d\n", word1.c_str(), word2.c_str(), w );
      }
    }

   if( echo )
    lem::mout->printf( " done\n" );
*/
   return;
  }

};


bool NGrams2DiskCache::q_sorter( const QueueItem2 &x, const QueueItem2 &y )
{
 return x.i_block<y.i_block;
}


bool NGrams2DiskCache::c_sorter( const Cached2Gram &x, const Cached2Gram &y )
{
 return x > y;
}


// ------------------------------------------------------------------------------



class NGrams3DiskCache : public NGrams3Cache
{
 private:
  struct Mark
  {
   lem::int64_t file_pos;
   int n;
   int n_free;

   Mark(void):file_pos(0), n(0), n_free(0) {}
  };

  #if defined LEM_MSC
  __declspec(align(4))
  #elif defined LEM_GNUC
  #pragma pack(4)
  #endif
  struct Cached3Gram
  {
   lem::int32_t first;
   lem::int32_t second;
   lem::int32_t third;
   lem::int32_t id, w;

   Cached3Gram(void) : first(UNKNOWN), second(UNKNOWN), third(UNKNOWN), id(UNKNOWN), w(0) {}

   inline bool operator==( const Cached3Gram &q ) const
   { return first==q.first && second==q.second && third==q.third; }

   inline bool operator>( const Cached3Gram &q ) const
   {
    return first>q.first ||
           (first==q.first && second>q.second) ||
           (first==q.first && second==q.second && third>q.third);
   }
  };

  #if defined LEM_64
  enum { N_BLOCKS=10000000, ITEMS_PER_BLOCK=64 };
  #else
  enum { N_BLOCKS=1000000, ITEMS_PER_BLOCK=256 };
  #endif

  int QUEUE_LEN; // максимальная длина очереди команд на изменение базы

  char mode; // режим записи-чтения ('w'-'r')

  struct QueueItem3
  {
   int i_block;
   int i1, i2, i3;
   int freq;
  }; 

  static bool q_sorter( const QueueItem3 &x, const QueueItem3 &y );
  static bool c_sorter( const Cached3Gram &x, const Cached3Gram &y );

  lem::MCollect<QueueItem3> queue;

  Cached3Gram *ngrams_buffer; // буфер для служебных операций - используется при копировании
  int ngrams_buffer_size;     // списков на новое место, сортировке и так далее.

  Mark *marks;
  lem::Path filename;
  lem::Path tmp_filename; // полный путь с черновым вариантом файла базы 
  int id_seq;
  lem::Ptr<lem::BinaryFile> file;
  lem::int32_t max_freq;

  void FlushQueue(void)
  {
   LEM_CHECKIT_Z( mode=='w' );

   if( queue.empty() )
    return;

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( "Entering Cached3Gram::FlushQueue\n" );

   if( echo )
    {
     lem::mout->printf( "%vf3Flushing disk cache%vn - %vfE%d%vn items in queue ", CastSizeToInt(queue.size()) );  
     lem::mout->flush();
    }

   std::sort( queue.begin(), queue.end(), q_sorter );

   int i_block=queue.front().i_block;
   int iq0=0;

   int n_inserted=0, n_updated=0;

   for( lem::Container::size_type i=0; i<=queue.size(); ++i )
    {
     if( echo && !(i%1000000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      }

     if( i==queue.size() || queue[i].i_block!=i_block )
      {
       // Команды от iq0 до i (не включая) применяются к одному блоку в файле.
       Mark &mark = marks[i_block];
       const int n_cmd = i-iq0;

       if( ngrams_buffer_size<(mark.n+n_cmd) )
        {
         delete[] ngrams_buffer;
         ngrams_buffer_size = mark.n+n_cmd+256; 
         ngrams_buffer = new Cached3Gram[ngrams_buffer_size];
        }

       int i_buf=0;   
       if( mark.n>0 )
        {
         // Загрузим имеющиеся записи с диска в буфер
         file->seekp64( mark.file_pos );
         file->read( ngrams_buffer, sizeof(Cached3Gram)*mark.n ); 
         i_buf = mark.n;
        }

       // Просматриваем команды из поддиапазона (iq0,i) и переформируем список N-грамм.
       for( lem::Container::size_type j=iq0; j<i; ++j )
        {
         const int i1 = queue[j].i1;
         const int i2 = queue[j].i2;
         const int i3 = queue[j].i3;

         bool found=false;
         for( int k=0; k<i_buf; ++k )
          if( ngrams_buffer[k].first==i1 && ngrams_buffer[k].second==i2 && ngrams_buffer[k].third==i3 )
           {
            ngrams_buffer[k].w += queue[j].freq;
            max_freq = std::max( max_freq, ngrams_buffer[k].w );
            n_updated++; 
            found=true;
            break; 
           }

         if( !found )
          {
           // Надо добавить элемент в буфер.
           ngrams_buffer[i_buf].first  = queue[j].i1;
           ngrams_buffer[i_buf].second = queue[j].i2;
           ngrams_buffer[i_buf].third  = queue[j].i3;
           ngrams_buffer[i_buf].w      = queue[j].freq;
           ngrams_buffer[i_buf].id     = id_seq++;
           max_freq = std::max( max_freq, ngrams_buffer[i_buf].w );
           i_buf++;
           n_inserted++;
          }
        }

       // Проверим, что новый блок вместится на место старого.
       if( i_buf>=(mark.n+mark.n_free) )
        {
         // надо переразмещать блок.
         file->seekp64( 0, SEEK_END );
         mark.file_pos = file->tellp64();
         const int n_expanded = i_buf*2+32;
         mark.n_free = n_expanded-i_buf;
         mark.n = i_buf;

         file->write( ngrams_buffer, sizeof(Cached3Gram)*mark.n ); 
         for( int p=0; p<mark.n_free; ++p ) // допишем свободный хвост
          file->write( ngrams_buffer, sizeof(Cached3Gram) );
        }
       else
        { 
         mark.n_free = (mark.n_free+mark.n)-i_buf; // столько свободных ячеек осталось.
         mark.n = i_buf;
         file->seekp64( mark.file_pos );
         file->write( ngrams_buffer, sizeof(Cached3Gram)*mark.n ); 
        } 

       iq0 = i;

       if( i<queue.size() )
        i_block = queue[i].i_block;
      }  
    }

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( "Leaving Cached3Gram::FlushQueue\n" );

   if( echo )
    {
     lem::mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated %vfAOK%vn\n", n_inserted, n_updated );
    }

   queue.clear();

   return;
  }

 public:
  NGrams3DiskCache( char Mode ) : NGrams3Cache(), mode(Mode)
  {
   QUEUE_LEN = mode=='w' ? 10000000 : 0;

   marks = new Mark[N_BLOCKS];
   echo = false;

   if( QUEUE_LEN>0 )
    queue.reserve(QUEUE_LEN);

   ngrams_buffer = NULL;
   ngrams_buffer_size=0;

   id_seq=0;
   max_freq = 0;

   return;
  }

  virtual ~NGrams3DiskCache(void)
  {
   LEM_CHECKIT_Z( queue.empty() );
   delete[] ngrams_buffer; ngrams_buffer=NULL;
   delete[] marks; marks=NULL;

   // Закрываем файл контейнера, запись в него теперь невозможна.
   file.Delete();

   // Удаляем черновую базу.
   tmp_filename.DoRemove();

   return;
  }


  // ******************************************************************
  // Задеется максимальный размер очереди команд добавления,
  // по достижении этого предела начинается выгрузка очереди
  // в дисковый контейнер.
  // ******************************************************************
  virtual void SetBufferSize( int n )
  {
   if( n>0 && mode=='w' )
    {
     QUEUE_LEN=n;
     queue.reserve(n);
    }

   return;
  }

  // ******************************************************************
  // Открываем и готовим дисковый контейнер для накопления данных.
  // folder - это папка, где будет создан файл контейнера
  // table - имя хранимой таблицы N-грамм.
  // ******************************************************************
  void Open( const lem::Path &folder, const lem::FString &table )
  {
   // Формируем файл базы. Сначала мы будем формировать временную базу,
   // а потом скопируем окончательные данные в итоговый файл, одновременно
   // выполняя сжатие и сортировки.
   filename = folder;
   lem::Path fn(table);
   filename.ConcateLeaf( fn );

   if( mode=='w' )
    {
     tmp_filename = folder;
     lem::Path tmp_fn(table+L".tmp");
     tmp_filename.ConcateLeaf( tmp_fn );

     if( echo )
      {
       lem::mout->printf( "%vf3Creating db file %vfE%us%vn %vn...", tmp_filename.GetUnicode().c_str() );  
       lem::mout->flush();
      }

     file = new BinaryFile( tmp_filename, false, true );
     file->reopen( true, true, true );

     // Форматируем контейнер.
     const int block_space = ITEMS_PER_BLOCK; // на каждый поддиапазон N-грамм заранее выделяем
                                  // столько свободных элементов.

     ngrams_buffer_size = block_space*2;
     ngrams_buffer = new Cached3Gram[ngrams_buffer_size];

     for( int i=0; i<N_BLOCKS; ++i )
      {
       Mark &mark = marks[i];
       mark.file_pos = file->tellp64();
       mark.n=0;
       mark.n_free=block_space;
       file->write( ngrams_buffer, sizeof(Cached3Gram)*block_space ); 

       if( !(i%100000) && echo )
        {
         lem::mout->printf( '.' );
         lem::mout->flush();
        }
      }

     file->flush();

     if( echo )
      {
       lem::mout->printf( "%vfAOk%vn\n" );  
       lem::mout->flush();
      }
    }
   else if( mode=='r' )
    {
     // Открываем на чтение уже существующий файл контейнера
     file = new BinaryReader(filename);

     lem::uint64_t marks_pos=0;
     file->read( &marks_pos, sizeof(marks_pos) );
     file->read( &max_freq, sizeof(max_freq) );

     file->seekp64( marks_pos );
     file->read( marks, sizeof(Mark)*N_BLOCKS );

     // Можем сразу определить максимальный размер буфера для чтения N-грамм.
     int n_max=0;
     for( int i=0; i<N_BLOCKS; i++ )
      n_max = std::max( n_max, marks[i].n );

     ngrams_buffer_size = n_max;
     ngrams_buffer = new Cached3Gram[ngrams_buffer_size];
    }
   
   return; 
  }


  virtual void InsertOrUpdate( int i1, int i2, int i3, int freq )
  {
   LEM_CHECKIT_Z( freq>0 );
   LEM_CHECKIT_Z( mode=='w' );

   const int i_block = ngram3hash(i1,i2,i3) % N_BLOCKS;
   LEM_CHECKIT_Z( i_block>=0 && i_block<N_BLOCKS );

   if( CastSizeToInt(queue.size())>=QUEUE_LEN )
    FlushQueue();

   QueueItem3 q;
   q.i1=i1; q.i2=i2; q.i3=i3; q.i_block=i_block; q.freq=freq;
   #if LEM_DEBUGGING==1
   lem::Container::size_type iqueue = queue.size();
   #endif
   queue.push_back(q);

   return;
  }


  virtual std::pair<int,int> Select( int i1, int i2, int i3 )
  {
   LEM_CHECKIT_Z( mode=='r' );

   const int i_block = ngram3hash(i1,i2,i3) % N_BLOCKS;
   LEM_CHECKIT_Z( i_block>=0 && i_block<N_BLOCKS );

   file->seekp64( marks[i_block].file_pos );
   Cached3Gram g;
   for( int i=0; i<marks[i_block].n; ++i )
    {
     file->read( &g, sizeof(g) );
     if( g.first==i1 && g.second==i2 && g.third==i3 )
      return std::make_pair(g.id,g.w);
    }
 
   return std::make_pair(-1,-1);
  }



  virtual void Commit(void)
  {
   LEM_CHECKIT_Z( mode=='w' );

   FlushQueue();

   if( echo )
    {
     lem::mout->printf( "%vf3Committing disk cache%vn..." );  
     lem::mout->flush();
    }

   // Формируем чистовой файл базы.
   lem::BinaryFile db( filename, false, true );
   db.reopen( true, true, true );

   // поле пока зарезервировано
   lem::uint64_t dummy=0;
   db.write( &dummy, sizeof(dummy) );

   lem::uint64_t marks_pos=0;
   db.write( &marks_pos, sizeof(marks_pos) );

   // Общее количество записей
   lem::int64_t n_recs=0;
   for( int i=0; i<N_BLOCKS; ++i )
    n_recs += marks[i].n;

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn 3grams ", n_recs );  
     lem::mout->flush();
    }

   db.write( &n_recs, sizeof(n_recs) );

   // Максимальная частота N-граммы
   db.write( &max_freq, sizeof(max_freq) );

   // Количество блоков
   lem::int32_t n_block=N_BLOCKS;
   db.write( &n_block, sizeof(n_block) );

   // Сортируем блоки и одновременно сжимаем неиспользуемое пространство.
   for( int i=0; i<N_BLOCKS; ++i )
    {
     file->seekp64( marks[i].file_pos );
     file->read( ngrams_buffer, sizeof(*ngrams_buffer)*marks[i].n );
     std::sort( ngrams_buffer, ngrams_buffer+marks[i].n, &c_sorter );
     marks[i].file_pos = db.tellp64();
     db.write( ngrams_buffer, sizeof(*ngrams_buffer)*marks[i].n );
    }

   // Впишем вектор Marks в конец файла
   marks_pos = db.tellp64();
   for( int i=0; i<N_BLOCKS; ++i )
    db.write( &marks[i].file_pos, sizeof(marks[i].file_pos) );

   for( int i=0; i<N_BLOCKS; ++i )
    db.write( &marks[i].n, sizeof(marks[i].n) );

   // В начало файла впишем позицию вектора
   db.seekp64( 0, SEEK_SET );

   db.write( &dummy, sizeof(dummy) );
   db.write( &marks_pos, sizeof(marks_pos) );

   db.seekp64( 0, SEEK_END );
   db.flush();

   if( echo )
    lem::mout->printf( " %vfE%qd%vn 3grams %vfAOK%vn\n", n_recs );  

   return;
  }


  virtual void Upload( NGramsDBMS &db, const FString &sql )
  {
/*
   LEM_CHECKIT_Z( mode=='w' );

   if( echo )
    {
     lem::mout->printf( "%vf3Uploading 3grams to DB%vn" );
     lem::mout->flush();
    }

   lem::int64_t total_count = 0;
   for( int i=0; i<N_BLOCKS; ++i )
    total_count += marks[i].n;

   char asql_buf[512];

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn records ", total_count );
     lem::mout->flush();
    }

   int n_insert=0;
   lem::FString inserts; inserts.reserve(10000);

   for( int i=0; i<N_BLOCKS; ++i )
    {
     if( echo && !(i%100000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      } 

     const Mark &mark = marks[i];
   
     LEM_CHECKIT_Z( mark.n<=ngrams_buffer_size );
     file->seekp64( mark.file_pos );
     file->read( ngrams_buffer, sizeof(Cached3Gram)*mark.n );

     for( int j=0; j<mark.n; ++j )
      {
       const Cached3Gram &g = ngrams_buffer[j];

       if( n_insert>=NGramsDBMS::max_bulk_insert )
        {
         // пачку ранее накопленных INSERT'ов сбрасываем в базу.
         db.ExecuteSql(inserts.c_str());
         inserts.clear();
         n_insert=0;
        }

       if( n_insert==0 )
        inserts = sql;
    
       if( n_insert>=1 )
        inserts.Add_Dirty( " UNION ALL " );

       sprintf(
               asql_buf,
               #if defined SOL_SQLITE_NGRAMS
               " SELECT %d, %d, %d, %d, %d ",
               #elif defined SOL_FIREBIRD_NGRAMS
               " SELECT %d, %d, %d, %d, %d FROM RDB$DATABASE",
               #endif
               g.id, g.first, g.second, g.third, g.w
              );

       inserts.Add_Dirty( asql_buf );
       n_insert++;
      }
    }

   if( n_insert>0 )
    {
     db.ExecuteSql(inserts.c_str()); 
     inserts.clear();
    }

   if( echo )
    lem::mout->printf( " done\n" );
 */
   return; 
  }

  virtual void Print( NGramsDBMS &db, const lem::FString &sql, const lem::FString &format, OFormatter &to )
  {
   LEM_CHECKIT_Z( mode=='w' );

   if( echo )
    {
     lem::mout->printf( "%vf3Print 3grams to text file using '%s' format%vn", format.c_str() );
     lem::mout->flush();
    }

   lem::int64_t total_count = 0;
   for( int i=0; i<N_BLOCKS; ++i )
    total_count += marks[i].n;

   char asql_buf[512];

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn records ", total_count );
     lem::mout->flush();
    }

   const bool csv = format.eqi("csv");
   const bool xml = format.eqi("xml");

   for( int i=0; i<N_BLOCKS; ++i )
    {
     if( echo && !(i%100000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      } 

     const Mark &mark = marks[i];
   
     LEM_CHECKIT_Z( mark.n<=ngrams_buffer_size );
     file->seekp64( mark.file_pos );
     file->read( ngrams_buffer, sizeof(Cached3Gram)*mark.n );

     for( int j=0; j<mark.n; ++j )
      {
       const Cached3Gram &g = ngrams_buffer[j];

       const int iword1 = g.first;
       const int iword2 = g.second;
       const int iword3 = g.third;

       const lem::int32_t w = g.w;

       sprintf( asql_buf, sql.c_str(), iword1 );
       UFString word1( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword2 ); 
       UFString word2( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword3 ); 
       UFString word3( db.SelectStr(asql_buf) );

       if( csv )       
        to.printf( "3;%us;%us;%us;%d\n", word1.c_str(), word2.c_str(), word3.c_str(), w );
      }
    }

   if( echo )
    lem::mout->printf( " done\n" );

   return;
  }
};


bool NGrams3DiskCache::q_sorter( const QueueItem3 &x, const QueueItem3 &y )
{
 return x.i_block<y.i_block;
}


bool NGrams3DiskCache::c_sorter( const Cached3Gram &x, const Cached3Gram &y )
{
 return x>y;
}





// ------------------------------------------------------------------------------





class NGrams4DiskCache : public NGrams4Cache
{
 private:
  struct Mark
  {
   lem::int64_t file_pos;
   int n;
   int n_free;

   Mark(void):file_pos(0), n(0), n_free(0) {}
  };

  #if defined LEM_MSC
  __declspec(align(4))
  #elif defined LEM_GNUC
  #pragma pack(4)
  #endif
  struct Cached4Gram
  {
   lem::int32_t z1, z2, z3, z4;
   lem::int32_t id, w;

   Cached4Gram(void) : z1(UNKNOWN), z2(UNKNOWN), z3(UNKNOWN), z4(UNKNOWN), id(UNKNOWN), w(0) {}

   inline bool operator==( const Cached4Gram &q ) const
   { return z1==q.z1 && z2==q.z2 && z3==q.z3 && z4==q.z4; }

   inline bool operator>( const Cached4Gram &q ) const
   {
    return z1>q.z1 ||
           (z1==q.z1 && z2>q.z2) ||
           (z1==q.z1 && z2==q.z2 && z3>q.z3) ||
           (z1==q.z1 && z2==q.z2 && z3==q.z3 && z4>q.z4);
   }
  };

  #if defined LEM_64
  enum { N_BLOCKS=10000000, ITEMS_PER_BLOCK=64 };
  #else
  enum { N_BLOCKS=1000000, ITEMS_PER_BLOCK=256 };
  #endif

  int QUEUE_LEN; // максимальная длина очереди команд на изменение базы

  char mode; // режим записи-чтения ('w'-'r')

  struct QueueItem4
  {
   int i_block;
   int i1, i2, i3, i4;
   int freq;
  }; 

  static bool q_sorter( const QueueItem4 &x, const QueueItem4 &y );
  static bool c_sorter( const Cached4Gram &x, const Cached4Gram &y );

  lem::MCollect<QueueItem4> queue;

  Cached4Gram *ngrams_buffer; // буфер для служебных операций - используется при копировании
  int ngrams_buffer_size;     // списков на новое место, сортировке и так далее.

  Mark *marks;
  lem::Path filename;
  lem::Path tmp_filename; // полный путь с черновым вариантом файла базы 
  int id_seq;
  lem::Ptr<lem::BinaryFile> file;
  lem::int32_t max_freq;

  void FlushQueue(void)
  {
   LEM_CHECKIT_Z( mode=='w' );

   if( queue.empty() )
    return;

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( "Entering Cached4Gram::FlushQueue\n" );

   if( echo )
    {
     lem::mout->printf( "%vf3Flushing disk cache%vn - %vfE%d%vn items in queue ", CastSizeToInt(queue.size()) );  
     lem::mout->flush();
    }

   std::sort( queue.begin(), queue.end(), q_sorter );

   int i_block=queue.front().i_block;
   int iq0=0;

   int n_inserted=0, n_updated=0;

   for( lem::Container::size_type i=0; i<=queue.size(); ++i )
    {
     if( echo && !(i%1000000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      }

     if( i==queue.size() || queue[i].i_block!=i_block )
      {
       // Команды от iq0 до i (не включая) применяются к одному блоку в файле.
       Mark &mark = marks[i_block];
       const int n_cmd = i-iq0;

       if( ngrams_buffer_size<(mark.n+n_cmd) )
        {
         delete[] ngrams_buffer;
         ngrams_buffer_size = mark.n+n_cmd+256; 
         ngrams_buffer = new Cached4Gram[ngrams_buffer_size];
        }

       int i_buf=0;   
       if( mark.n>0 )
        {
         // Загрузим имеющиеся записи с диска в буфер
         file->seekp64( mark.file_pos );
         file->read( ngrams_buffer, sizeof(Cached4Gram)*mark.n ); 
         i_buf = mark.n;
        }

       // Просматриваем команды из поддиапазона (iq0,i) и переформируем список N-грамм.
       for( lem::Container::size_type j=iq0; j<i; ++j )
        {
         const int i1 = queue[j].i1;
         const int i2 = queue[j].i2;
         const int i3 = queue[j].i3;
         const int i4 = queue[j].i4;

         bool found=false;
         for( int k=0; k<i_buf; ++k )
          if( ngrams_buffer[k].z1==i1 && ngrams_buffer[k].z2==i2 &&
              ngrams_buffer[k].z3==i3 && ngrams_buffer[k].z4==i4 )
           {
            ngrams_buffer[k].w += queue[j].freq;
            max_freq = std::max( max_freq, ngrams_buffer[k].w );
            n_updated++; 
            found=true;
            break; 
           }

         if( !found )
          {
           // Надо добавить элемент в буфер.
           ngrams_buffer[i_buf].z1 = queue[j].i1;
           ngrams_buffer[i_buf].z2 = queue[j].i2;
           ngrams_buffer[i_buf].z3 = queue[j].i3;
           ngrams_buffer[i_buf].z4 = queue[j].i4;
           ngrams_buffer[i_buf].w      = queue[j].freq;
           ngrams_buffer[i_buf].id     = id_seq++;
           max_freq = std::max( max_freq, ngrams_buffer[i_buf].w );
           i_buf++;
           n_inserted++;
          }
        }

       // Проверим, что новый блок вместится на место старого.
       if( i_buf>=(mark.n+mark.n_free) )
        {
         // надо переразмещать блок.
         file->seekp64( 0, SEEK_END );
         mark.file_pos = file->tellp64();
         const int n_expanded = i_buf*2+32;
         mark.n_free = n_expanded-i_buf;
         mark.n = i_buf;

         file->write( ngrams_buffer, sizeof(Cached4Gram)*mark.n ); 
         for( int p=0; p<mark.n_free; ++p ) // допишем свободный хвост
          file->write( ngrams_buffer, sizeof(Cached4Gram) );
        }
       else
        { 
         mark.n_free = (mark.n_free+mark.n)-i_buf; // столько свободных ячеек осталось.
         mark.n = i_buf;
         file->seekp64( mark.file_pos );
         file->write( ngrams_buffer, sizeof(Cached4Gram)*mark.n ); 
        } 

       iq0 = i;

       if( i<queue.size() )
        i_block = queue[i].i_block;
      }  
    }

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( "Leaving Cached4Gram::FlushQueue\n" );

   if( echo )
    {
     lem::mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated %vfAOK%vn\n", n_inserted, n_updated );
    }

   queue.clear();

   return;
  }

 public:
  NGrams4DiskCache( char Mode ) : NGrams4Cache(), mode(Mode)
  {
   QUEUE_LEN = mode=='w' ? 10000000 : 0;

   marks = new Mark[N_BLOCKS];
   echo = false;

   if( QUEUE_LEN>0 )
    queue.reserve(QUEUE_LEN);

   ngrams_buffer = NULL;
   ngrams_buffer_size=0;

   id_seq=0;
   max_freq = 0;

   return;
  }

  virtual ~NGrams4DiskCache(void)
  {
   LEM_CHECKIT_Z( queue.empty() );
   delete[] ngrams_buffer; ngrams_buffer=NULL;
   delete[] marks; marks=NULL;

   // Закрываем файл контейнера, запись в него теперь невозможна.
   file.Delete();

   // Удаляем черновую базу.
   tmp_filename.DoRemove();

   return;
  }


  // ******************************************************************
  // Задеется максимальный размер очереди команд добавления,
  // по достижении этого предела начинается выгрузка очереди
  // в дисковый контейнер.
  // ******************************************************************
  virtual void SetBufferSize( int n )
  {
   if( n>0 && mode=='w' )
    {
     QUEUE_LEN=n;
     queue.reserve(n);
    }

   return;
  }

  // ******************************************************************
  // Открываем и готовим дисковый контейнер для накопления данных.
  // folder - это папка, где будет создан файл контейнера
  // table - имя хранимой таблицы N-грамм.
  // ******************************************************************
  void Open( const lem::Path &folder, const lem::FString &table )
  {
   // Формируем файл базы. Сначала мы будем формировать временную базу,
   // а потом скопируем окончательные данные в итоговый файл, одновременно
   // выполняя сжатие и сортировки.
   filename = folder;
   lem::Path fn(table);
   filename.ConcateLeaf( fn );

   if( mode=='w' )
    {
     tmp_filename = folder;
     lem::Path tmp_fn(table+L".tmp");
     tmp_filename.ConcateLeaf( tmp_fn );

     if( echo )
      {
       lem::mout->printf( "%vf3Creating db file %vfE%us%vn %vn...", tmp_filename.GetUnicode().c_str() );  
       lem::mout->flush();
      }

     file = new BinaryFile( tmp_filename, false, true );
     file->reopen( true, true, true );

     // Форматируем контейнер.
     const int block_space = ITEMS_PER_BLOCK; // на каждый поддиапазон N-грамм заранее выделяем
                                  // столько свободных элементов.

     ngrams_buffer_size = block_space*2;
     ngrams_buffer = new Cached4Gram[ngrams_buffer_size];

     for( int i=0; i<N_BLOCKS; ++i )
      {
       Mark &mark = marks[i];
       mark.file_pos = file->tellp64();
       mark.n=0;
       mark.n_free=block_space;
       file->write( ngrams_buffer, sizeof(Cached4Gram)*block_space ); 

       if( !(i%100000) && echo )
        {
         lem::mout->printf( '.' );
         lem::mout->flush();
        }
      }

     file->flush();

     if( echo )
      {
       lem::mout->printf( "%vfAOk%vn\n" );  
       lem::mout->flush();
      }
    }
   else if( mode=='r' )
    {
     // Открываем на чтение уже существующий файл контейнера
     file = new BinaryReader(filename);

     lem::uint64_t marks_pos=0;
     file->read( &marks_pos, sizeof(marks_pos) );
     file->read( &max_freq, sizeof(max_freq) );

     file->seekp64( marks_pos );
     file->read( marks, sizeof(Mark)*N_BLOCKS );

     // Можем сразу определить максимальный размер буфера для чтения N-грамм.
     int n_max=0;
     for( int i=0; i<N_BLOCKS; i++ )
      n_max = std::max( n_max, marks[i].n );

     ngrams_buffer_size = n_max;
     ngrams_buffer = new Cached4Gram[ngrams_buffer_size];
    }
   
   return; 
  }


  virtual void InsertOrUpdate( int i1, int i2, int i3, int i4, int freq )
  {
   LEM_CHECKIT_Z( freq>0 );
   LEM_CHECKIT_Z( mode=='w' );

   const int i_block = ngram4hash(i1,i2,i3,i4) % N_BLOCKS;
   LEM_CHECKIT_Z( i_block>=0 && i_block<N_BLOCKS );

   if( CastSizeToInt(queue.size())>=QUEUE_LEN )
    FlushQueue();

   QueueItem4 q;
   q.i1=i1; q.i2=i2; q.i3=i3; q.i4=i4; q.i_block=i_block; q.freq=freq;
   #if LEM_DEBUGGING==1
   lem::Container::size_type iqueue = queue.size();
   #endif
   queue.push_back(q);

   return;
  }


  virtual std::pair<int,int> Select( int i1, int i2, int i3, int i4 )
  {
   LEM_CHECKIT_Z( mode=='r' );

   const int i_block = ngram4hash(i1,i2,i3,i4) % N_BLOCKS;
   LEM_CHECKIT_Z( i_block>=0 && i_block<N_BLOCKS );

   file->seekp64( marks[i_block].file_pos );
   Cached4Gram g;
   for( int i=0; i<marks[i_block].n; ++i )
    {
     file->read( &g, sizeof(g) );
     if( g.z1==i1 && g.z2==i2 && g.z3==i3 && g.z4==i4 )
      return std::make_pair(g.id,g.w);
    }
 
   return std::make_pair(-1,-1);
  }



  virtual void Commit(void)
  {
   LEM_CHECKIT_Z( mode=='w' );

   FlushQueue();

   // Формируем чистовой файл базы.
   lem::BinaryFile db( filename, false, true );
   db.reopen( true, true, true );

   // поле пока зарезервировано
   lem::uint64_t dummy=0;
   db.write( &dummy, sizeof(dummy) );

   lem::uint64_t marks_pos=0;
   db.write( &marks_pos, sizeof(marks_pos) );

   // Общее количество записей
   lem::int64_t n_recs=0;
   for( int i=0; i<N_BLOCKS; ++i )
    n_recs += marks[i].n;

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn 4grams ", n_recs );  
     lem::mout->flush();
    }

   db.write( &n_recs, sizeof(n_recs) );

   // Максимальная частота N-граммы
   db.write( &max_freq, sizeof(max_freq) );

   // Количество блоков
   lem::int32_t n_block=N_BLOCKS;
   db.write( &n_block, sizeof(n_block) );

   // Сортируем блоки и одновременно сжимаем неиспользуемое пространство.
   for( int i=0; i<N_BLOCKS; ++i )
    {
     file->seekp64( marks[i].file_pos );
     file->read( ngrams_buffer, sizeof(*ngrams_buffer)*marks[i].n );
     std::sort( ngrams_buffer, ngrams_buffer+marks[i].n, &c_sorter );
     marks[i].file_pos = db.tellp64();
     db.write( ngrams_buffer, sizeof(*ngrams_buffer)*marks[i].n );
    }

   // Впишем вектор Marks в конец файла
   marks_pos = db.tellp64();
   for( int i=0; i<N_BLOCKS; ++i )
    db.write( &marks[i].file_pos, sizeof(marks[i].file_pos) );

   for( int i=0; i<N_BLOCKS; ++i )
    db.write( &marks[i].n, sizeof(marks[i].n) );

   // В начало файла впишем позицию вектора
   db.seekp64( 0, SEEK_SET );

   db.write( &dummy, sizeof(dummy) );
   db.write( &marks_pos, sizeof(marks_pos) );

   db.seekp64( 0, SEEK_END );
   db.flush();

   if( echo )
    lem::mout->printf( "%vfAOK%vn\n" );  

   return;
  }


  virtual void Upload( NGramsDBMS &db, const FString &sql )
  {
   LEM_CHECKIT_Z( mode=='w' );
/*
   if( echo )
    {
     lem::mout->printf( "%vf3Uploading 4grams to DB%vn" );
     lem::mout->flush();
    }

   lem::int64_t total_count = 0;
   for( int i=0; i<N_BLOCKS; ++i )
    total_count += marks[i].n;

   char asql_buf[512];

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn records ", total_count );
     lem::mout->flush();
    }

   int n_insert=0;
   lem::FString inserts; inserts.reserve(10000);

   for( int i=0; i<N_BLOCKS; ++i )
    {
     if( echo && !(i%100000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      } 

     const Mark &mark = marks[i];
   
     LEM_CHECKIT_Z( mark.n<=ngrams_buffer_size );
     file->seekp64( mark.file_pos );
     file->read( ngrams_buffer, sizeof(Cached4Gram)*mark.n );

     for( int j=0; j<mark.n; ++j )
      {
       const Cached4Gram &g = ngrams_buffer[j];

       if( n_insert>=NGramsDBMS::max_bulk_insert )
        {
         // пачку ранее накопленных INSERT'ов сбрасываем в базу.
         db.ExecuteSql(inserts.c_str());
         inserts.clear();
         n_insert=0;
        }

       if( n_insert==0 )
        inserts = sql;
    
       if( n_insert>=1 )
        inserts.Add_Dirty( " UNION ALL " );

       sprintf(
               asql_buf,
               #if defined SOL_SQLITE_NGRAMS
               " SELECT %d, %d, %d, %d, %d, %d ",
               #elif defined SOL_FIREBIRD_NGRAMS
               " SELECT %d, %d, %d, %d, %d, %d FROM RDB$DATABASE",
               #endif
               g.id, g.z1, g.z2, g.z3, g.z4, g.w
              );

       inserts.Add_Dirty( asql_buf );
       n_insert++;
      }
    }

   if( n_insert>0 )
    {
     db.ExecuteSql(inserts.c_str()); 
     inserts.clear();
    }

   if( echo )
    lem::mout->printf( " done\n" );
 */
   return; 
  }

  virtual void Print( NGramsDBMS &db, const lem::FString &sql, const lem::FString &format, OFormatter &to )
  {
   LEM_CHECKIT_Z( mode=='w' );
/*
   if( echo )
    {
     lem::mout->printf( "%vf3Print 4grams to text file using '%s' format%vn", format.c_str() );
     lem::mout->flush();
    }

   lem::int64_t total_count = 0;
   for( int i=0; i<N_BLOCKS; ++i )
    total_count += marks[i].n;

   char asql_buf[512];

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn records ", total_count );
     lem::mout->flush();
    }

   const bool csv = format.eqi("csv");
   const bool xml = format.eqi("xml");

   for( int i=0; i<N_BLOCKS; ++i )
    {
     if( echo && !(i%100000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      } 

     const Mark &mark = marks[i];
   
     LEM_CHECKIT_Z( mark.n<=ngrams_buffer_size );
     file->seekp64( mark.file_pos );
     file->read( ngrams_buffer, sizeof(Cached4Gram)*mark.n );

     for( int j=0; j<mark.n; ++j )
      {
       const Cached4Gram &g = ngrams_buffer[j];

       const int iword1 = g.z1;
       const int iword2 = g.z2;
       const int iword3 = g.z3;
       const int iword4 = g.z4;

       const lem::int32_t w = g.w;

       sprintf( asql_buf, sql.c_str(), iword1 ); 
       UFString word1( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword2 ); 
       UFString word2( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword3 ); 
       UFString word3( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword4 ); 
       UFString word4( db.SelectStr(asql_buf) );

       if( csv )       
        to.printf( "4;%us;%us;%us;%us;%d\n", word1.c_str(), word2.c_str(), word3.c_str(), word4.c_str(), w );
      }
    }

   if( echo )
    lem::mout->printf( " done\n" );
*/
   return;
  }
};


bool NGrams4DiskCache::q_sorter( const QueueItem4 &x, const QueueItem4 &y )
{
 return x.i_block<y.i_block;
}


bool NGrams4DiskCache::c_sorter( const Cached4Gram &x, const Cached4Gram &y )
{
 return x>y;
}





// ------------------------------------------------------------------------------






class NGrams5DiskCache : public NGrams5Cache
{
 private:
  struct Mark
  {
   lem::int64_t file_pos;
   int n;
   int n_free;

   Mark(void):file_pos(0), n(0), n_free(0) {}
  };

  #if defined LEM_MSC
  __declspec(align(4))
  #elif defined LEM_GNUC
  #pragma pack(4)
  #endif
  struct Cached5Gram
  {
   lem::int32_t z1, z2, z3, z4, z5;
   lem::int32_t id, w;

   Cached5Gram(void) : z1(UNKNOWN), z2(UNKNOWN), z3(UNKNOWN), z4(UNKNOWN), z5(UNKNOWN), id(UNKNOWN), w(0) {}

   inline bool operator==( const Cached5Gram &q ) const
   { return z1==q.z1 && z2==q.z2 && z3==q.z3 && z4==q.z4 && z5==q.z5; }

   inline bool operator>( const Cached5Gram &q ) const
   {
    return z1>q.z1 ||
           (z1==q.z1 && z2>q.z2) ||
           (z1==q.z1 && z2==q.z2 && z3>q.z3) ||
           (z1==q.z1 && z2==q.z2 && z3==q.z3 && z4>q.z4) ||
           (z1==q.z1 && z2==q.z2 && z3==q.z3 && z4==q.z4 && z5>q.z5);
   }
  };

  #if defined LEM_64
  enum { N_BLOCKS=10000000, ITEMS_PER_BLOCK=64 };
  #else
  enum { N_BLOCKS=1000000, ITEMS_PER_BLOCK=256 };
  #endif

  int QUEUE_LEN; // максимальная длина очереди команд на изменение базы

  char mode; // режим записи-чтения ('w'-'r')

  struct QueueItem5
  {
   int i_block;
   int i1, i2, i3, i4, i5;
   int freq;
  }; 

  static bool q_sorter( const QueueItem5 &x, const QueueItem5 &y );
  static bool c_sorter( const Cached5Gram &x, const Cached5Gram &y );

  lem::MCollect<QueueItem5> queue;

  Cached5Gram *ngrams_buffer; // буфер для служебных операций - используется при копировании
  int ngrams_buffer_size;     // списков на новое место, сортировке и так далее.

  Mark *marks;
  lem::Path filename;
  lem::Path tmp_filename; // полный путь с черновым вариантом файла базы 
  int id_seq;
  lem::Ptr<lem::BinaryFile> file;
  lem::int32_t max_freq;

  void FlushQueue(void)
  {
   LEM_CHECKIT_Z( mode=='w' );

   if( queue.empty() )
    return;

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( "Entering Cached5Gram::FlushQueue\n" );

   if( echo )
    {
     lem::mout->printf( "%vf3Flushing disk cache%vn - %vfE%d%vn items in queue ", CastSizeToInt(queue.size()) );  
     lem::mout->flush();
    }

   std::sort( queue.begin(), queue.end(), q_sorter );

   int i_block=queue.front().i_block;
   int iq0=0;

   int n_inserted=0, n_updated=0;

   for( lem::Container::size_type i=0; i<=queue.size(); ++i )
    {
     if( echo && !(i%1000000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      }

     if( i==queue.size() || queue[i].i_block!=i_block )
      {
       // Команды от iq0 до i (не включая) применяются к одному блоку в файле.
       Mark &mark = marks[i_block];
       const int n_cmd = i-iq0;

       if( ngrams_buffer_size<(mark.n+n_cmd) )
        {
         delete[] ngrams_buffer;
         ngrams_buffer_size = mark.n+n_cmd+256; 
         ngrams_buffer = new Cached5Gram[ngrams_buffer_size];
        }

       int i_buf=0;   
       if( mark.n>0 )
        {
         // Загрузим имеющиеся записи с диска в буфер
         file->seekp64( mark.file_pos );
         file->read( ngrams_buffer, sizeof(Cached5Gram)*mark.n ); 
         i_buf = mark.n;
        }

       // Просматриваем команды из поддиапазона (iq0,i) и переформируем список N-грамм.
       for( lem::Container::size_type j=iq0; j<i; ++j )
        {
         const int i1 = queue[j].i1;
         const int i2 = queue[j].i2;
         const int i3 = queue[j].i3;
         const int i4 = queue[j].i4;
         const int i5 = queue[j].i5;

         bool found=false;
         for( int k=0; k<i_buf; ++k )
          if( ngrams_buffer[k].z1==i1 && ngrams_buffer[k].z2==i2 &&
              ngrams_buffer[k].z3==i3 && ngrams_buffer[k].z4==i4 && ngrams_buffer[k].z5==i5 )
           {
            ngrams_buffer[k].w += queue[j].freq;
            max_freq = std::max( max_freq, ngrams_buffer[k].w );
            n_updated++; 
            found=true;
            break; 
           }

         if( !found )
          {
           // Надо добавить элемент в буфер.
           ngrams_buffer[i_buf].z1 = queue[j].i1;
           ngrams_buffer[i_buf].z2 = queue[j].i2;
           ngrams_buffer[i_buf].z3 = queue[j].i3;
           ngrams_buffer[i_buf].z4 = queue[j].i4;
           ngrams_buffer[i_buf].z5 = queue[j].i5;
           ngrams_buffer[i_buf].w  = queue[j].freq;
           ngrams_buffer[i_buf].id = id_seq++;
           max_freq = std::max( max_freq, ngrams_buffer[i_buf].w );
           i_buf++;
           n_inserted++;
          }
        }

       // Проверим, что новый блок вместится на место старого.
       if( i_buf>=(mark.n+mark.n_free) )
        {
         // надо переразмещать блок.
         file->seekp64( 0, SEEK_END );
         mark.file_pos = file->tellp64();
         const int n_expanded = i_buf*2+32;
         mark.n_free = n_expanded-i_buf;
         mark.n = i_buf;

         file->write( ngrams_buffer, sizeof(Cached5Gram)*mark.n ); 
         for( int p=0; p<mark.n_free; ++p ) // допишем свободный хвост
          file->write( ngrams_buffer, sizeof(Cached5Gram) );
        }
       else
        { 
         mark.n_free = (mark.n_free+mark.n)-i_buf; // столько свободных ячеек осталось.
         mark.n = i_buf;
         file->seekp64( mark.file_pos );
         file->write( ngrams_buffer, sizeof(Cached5Gram)*mark.n ); 
        } 

       iq0 = i;

       if( i<queue.size() )
        i_block = queue[i].i_block;
      }  
    }

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( "Leaving Cached5Gram::FlushQueue\n" );

   if( echo )
    {
     lem::mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated %vfAOK%vn\n", n_inserted, n_updated );
    }

   queue.clear();

   return;
  }

 public:
  NGrams5DiskCache( char Mode ) : NGrams5Cache(), mode(Mode)
  {
   QUEUE_LEN = mode=='w' ? 10000000 : 0;

   marks = new Mark[N_BLOCKS];
   echo = false;

   if( QUEUE_LEN>0 )
    queue.reserve(QUEUE_LEN);

   ngrams_buffer = NULL;
   ngrams_buffer_size=0;

   id_seq=0;
   max_freq = 0;

   return;
  }

  virtual ~NGrams5DiskCache(void)
  {
   LEM_CHECKIT_Z( queue.empty() );
   delete[] ngrams_buffer; ngrams_buffer=NULL;
   delete[] marks; marks=NULL;

   // Закрываем файл контейнера, запись в него теперь невозможна.
   file.Delete();

   // Удаляем черновую базу.
   tmp_filename.DoRemove();

   return;
  }


  // ******************************************************************
  // Задается максимальный размер очереди команд добавления,
  // по достижении этого предела начинается выгрузка очереди
  // в дисковый контейнер.
  // ******************************************************************
  virtual void SetBufferSize( int n )
  {
   if( n>0 && mode=='w' )
    {
     QUEUE_LEN=n;
     queue.reserve(n);
    }

   return;
  }

  // ******************************************************************
  // Открываем и готовим дисковый контейнер для накопления данных.
  // folder - это папка, где будет создан файл контейнера
  // table - имя хранимой таблицы N-грамм.
  // ******************************************************************
  void Open( const lem::Path &folder, const lem::FString &table )
  {
   // Формируем файл базы. Сначала мы будем формировать временную базу,
   // а потом скопируем окончательные данные в итоговый файл, одновременно
   // выполняя сжатие и сортировки.
   filename = folder;
   lem::Path fn(table);
   filename.ConcateLeaf( fn );

   if( mode=='w' )
    {
     tmp_filename = folder;
     lem::Path tmp_fn(table+L".tmp");
     tmp_filename.ConcateLeaf( tmp_fn );

     if( echo )
      {
       lem::mout->printf( "%vf3Creating db file %vfE%us%vn %vn...", tmp_filename.GetUnicode().c_str() );  
       lem::mout->flush();
      }

     file = new BinaryFile( tmp_filename, false, true );
     file->reopen( true, true, true );

     // Форматируем контейнер.
     const int block_space = ITEMS_PER_BLOCK; // на каждый поддиапазон N-грамм заранее выделяем
                                  // столько свободных элементов.

     ngrams_buffer_size = block_space*2;
     ngrams_buffer = new Cached5Gram[ngrams_buffer_size];

     for( int i=0; i<N_BLOCKS; ++i )
      {
       Mark &mark = marks[i];
       mark.file_pos = file->tellp64();
       mark.n=0;
       mark.n_free=block_space;
       file->write( ngrams_buffer, sizeof(Cached5Gram)*block_space ); 

       if( !(i%100000) && echo )
        {
         lem::mout->printf( '.' );
         lem::mout->flush();
        }
      }

     file->flush();

     if( echo )
      {
       lem::mout->printf( "%vfAOk%vn\n" );  
       lem::mout->flush();
      }
    }
   else if( mode=='r' )
    {
     // Открываем на чтение уже существующий файл контейнера
     file = new BinaryReader(filename);

     lem::uint64_t marks_pos=0;
     file->read( &marks_pos, sizeof(marks_pos) );
     file->read( &max_freq, sizeof(max_freq) );

     file->seekp64( marks_pos );
     file->read( marks, sizeof(Mark)*N_BLOCKS );

     // Можем сразу определить максимальный размер буфера для чтения N-грамм.
     int n_max=0;
     for( int i=0; i<N_BLOCKS; i++ )
      n_max = std::max( n_max, marks[i].n );

     ngrams_buffer_size = n_max;
     ngrams_buffer = new Cached5Gram[ngrams_buffer_size];
    }
   
   return; 
  }


  virtual void InsertOrUpdate( int i1, int i2, int i3, int i4, int i5, int freq )
  {
   LEM_CHECKIT_Z( freq>0 );
   LEM_CHECKIT_Z( mode=='w' );

   const int i_block = ngram5hash(i1,i2,i3,i4,i5) % N_BLOCKS;
   LEM_CHECKIT_Z( i_block>=0 && i_block<N_BLOCKS );

   if( CastSizeToInt(queue.size())>=QUEUE_LEN )
    FlushQueue();

   QueueItem5 q;
   q.i1=i1; q.i2=i2; q.i3=i3; q.i4=i4; q.i5=i5; q.i_block=i_block; q.freq=freq;
   #if LEM_DEBUGGING==1
   lem::Container::size_type iqueue = queue.size();
   #endif
   queue.push_back(q);

   return;
  }


  virtual std::pair<int,int> Select( int i1, int i2, int i3, int i4, int i5 )
  {
   LEM_CHECKIT_Z( mode=='r' );

   const int i_block = ngram5hash(i1,i2,i3,i4,i5) % N_BLOCKS;
   LEM_CHECKIT_Z( i_block>=0 && i_block<N_BLOCKS );

   file->seekp64( marks[i_block].file_pos );
   Cached5Gram g;
   for( int i=0; i<marks[i_block].n; ++i )
    {
     file->read( &g, sizeof(g) );
     if( g.z1==i1 && g.z2==i2 && g.z3==i3 && g.z4==i4 && g.z5==i5 )
      return std::make_pair(g.id,g.w);
    }
 
   return std::make_pair(-1,-1);
  }



  virtual void Commit(void)
  {
   LEM_CHECKIT_Z( mode=='w' );

   FlushQueue();

   if( echo )
    {
     lem::mout->printf( "%vf3Committing disk cache%vn..." );  
     lem::mout->flush();
    }

   // Формируем чистовой файл базы.
   lem::BinaryFile db( filename, false, true );
   db.reopen( true, true, true );

   // поле пока зарезервировано
   lem::uint64_t dummy=0;
   db.write( &dummy, sizeof(dummy) );

   lem::uint64_t marks_pos=0;
   db.write( &marks_pos, sizeof(marks_pos) );

   // Общее количество записей
   lem::int64_t n_recs=0;
   for( int i=0; i<N_BLOCKS; ++i )
    n_recs += marks[i].n;

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn 5grams ", n_recs );  
     lem::mout->flush();
    }

   db.write( &n_recs, sizeof(n_recs) );

   // Максимальная частота N-граммы
   db.write( &max_freq, sizeof(max_freq) );

   // Количество блоков
   lem::int32_t n_block=N_BLOCKS;
   db.write( &n_block, sizeof(n_block) );

   // Сортируем блоки и одновременно сжимаем неиспользуемое пространство.
   for( int i=0; i<N_BLOCKS; ++i )
    {
     file->seekp64( marks[i].file_pos );
     file->read( ngrams_buffer, sizeof(*ngrams_buffer)*marks[i].n );
     std::sort( ngrams_buffer, ngrams_buffer+marks[i].n, &c_sorter );
     marks[i].file_pos = db.tellp64();
     db.write( ngrams_buffer, sizeof(*ngrams_buffer)*marks[i].n );
    }

   // Впишем вектор Marks в конец файла
   marks_pos = db.tellp64();
   for( int i=0; i<N_BLOCKS; ++i )
    db.write( &marks[i].file_pos, sizeof(marks[i].file_pos) );

   for( int i=0; i<N_BLOCKS; ++i )
    db.write( &marks[i].n, sizeof(marks[i].n) );

   // В начало файла впишем позицию вектора
   db.seekp64( 0, SEEK_SET );

   db.write( &dummy, sizeof(dummy) );
   db.write( &marks_pos, sizeof(marks_pos) );

   db.seekp64( 0, SEEK_END );
   db.flush();

   if( echo )
    lem::mout->printf( "%vfAOK%vn\n" );  

   return;
  }


  virtual void Upload( NGramsDBMS &db, const FString &sql )
  {
   LEM_CHECKIT_Z( mode=='w' );
/*
   if( echo )
    {
     lem::mout->printf( "%vf3Uploading 5grams to DB%vn" );
     lem::mout->flush();
    }

   lem::int64_t total_count = 0;
   for( int i=0; i<N_BLOCKS; ++i )
    total_count += marks[i].n;

   char asql_buf[512];

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn records ", total_count );
     lem::mout->flush();
    }

   int n_insert=0;
   lem::FString inserts; inserts.reserve(10000);

   for( int i=0; i<N_BLOCKS; ++i )
    {
     if( echo && !(i%100000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      } 

     const Mark &mark = marks[i];
   
     LEM_CHECKIT_Z( mark.n<=ngrams_buffer_size );
     file->seekp64( mark.file_pos );
     file->read( ngrams_buffer, sizeof(Cached5Gram)*mark.n );

     for( int j=0; j<mark.n; ++j )
      {
       const Cached5Gram &g = ngrams_buffer[j];

       if( n_insert>=NGramsDBMS::max_bulk_insert )
        {
         // пачку ранее накопленных INSERT'ов сбрасываем в базу.
         db.ExecuteSql(inserts.c_str());
         inserts.clear();
         n_insert=0;
        }

       if( n_insert==0 )
        inserts = sql;
    
       if( n_insert>=1 )
        inserts.Add_Dirty( " UNION ALL " );

       sprintf(
               asql_buf,
               #if defined SOL_SQLITE_NGRAMS
               " SELECT %d, %d, %d, %d, %d, %d, %d ",
               #elif defined SOL_FIREBIRD_NGRAMS
               " SELECT %d, %d, %d, %d, %d, %d FROM RDB$DATABASE",
               #endif
               g.id, g.z1, g.z2, g.z3, g.z4, g.z5, g.w
              );

       inserts.Add_Dirty( asql_buf );
       n_insert++;
      }
    }

   if( n_insert>0 )
    {
     db.ExecuteSql(inserts.c_str()); 
     inserts.clear();
    }

   if( echo )
    lem::mout->printf( " done\n" );
 */
   return; 
  }

  virtual void Print( NGramsDBMS &db, const lem::FString &sql, const lem::FString &format, OFormatter &to )
  {
   LEM_CHECKIT_Z( mode=='w' );
/*
   if( echo )
    {
     lem::mout->printf( "%vf3Print 5grams to text file using '%s' format%vn", format.c_str() );
     lem::mout->flush();
    }

   lem::int64_t total_count = 0;
   for( int i=0; i<N_BLOCKS; ++i )
    total_count += marks[i].n;

   char asql_buf[512];

   if( echo )
    {
     lem::mout->printf( " %vfE%qd%vn records ", total_count );
     lem::mout->flush();
    }

   const bool csv = format.eqi("csv");
   const bool xml = format.eqi("xml");

   for( int i=0; i<N_BLOCKS; ++i )
    {
     if( echo && !(i%100000) )
      {
       lem::mout->printf( '.' );
       lem::mout->flush();
      } 

     const Mark &mark = marks[i];
   
     LEM_CHECKIT_Z( mark.n<=ngrams_buffer_size );
     file->seekp64( mark.file_pos );
     file->read( ngrams_buffer, sizeof(Cached5Gram)*mark.n );

     for( int j=0; j<mark.n; ++j )
      {
       const Cached5Gram &g = ngrams_buffer[j];

       const int iword1 = g.z1;
       const int iword2 = g.z2;
       const int iword3 = g.z3;
       const int iword4 = g.z4;
       const int iword5 = g.z5;

       const lem::int32_t w = g.w;

       sprintf( asql_buf, sql.c_str(), iword1 ); 
       UFString word1( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword2 ); 
       UFString word2( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword3 ); 
       UFString word3( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword4 ); 
       UFString word4( db.SelectStr(asql_buf) );

       sprintf( asql_buf, sql.c_str(), iword5 ); 
       UFString word5( db.SelectStr(asql_buf) );

       if( csv )       
        to.printf( "5;%us;%us;%us;%us;%us;%d\n", word1.c_str(), word2.c_str(), word3.c_str(), word4.c_str(), word5.c_str(), w );
      }
    }

   if( echo )
    lem::mout->printf( " done\n" );
*/
   return;
  }
};


bool NGrams5DiskCache::q_sorter( const QueueItem5 &x, const QueueItem5 &y )
{
 return x.i_block<y.i_block;
}


bool NGrams5DiskCache::c_sorter( const Cached5Gram &x, const Cached5Gram &y )
{
 return x>y;
}





// ------------------------------------------------------------------------------





RawNGramsCollector::RawNGramsCollector(void)
{
 filter=NULL;
 sol_id = NULL;
 sg = NULL;
 la = NULL;
 db = NULL;
 needs_NGRAM1=needs_WORDS=needs_NGRAM2=needs_NGRAM3=needs_NGRAM5=needs_NGRAM5=true;
 needs_index_creation1=needs_index_creation2=needs_index_creation3=
 needs_index_creation4=needs_index_creation5=false;

 ie21=ie22=
 ie31=ie32=ie33=
 ie41=ie42=ie43=ie44=
 ie51=ie52=ie53=ie54=ie55=UNKNOWN;

 #if defined LEM_64
 max_words_cache=10000000;
 #else
 max_words_cache=4000000;
 #endif

 SetNGramsCacheCapacity(10000000);
 SetDocCacheCapacity(5000000);
 
 memset( usql_buf, 0, sizeof(usql_buf) );
 memset( asql_buf, 0, sizeof(asql_buf) );

 use_disk_cache=true;
 upload_to_db=true;
 print_ngrams=false;

 Update1Gram.reserve(1000000);
 Update2Gram.reserve(1000000);
 Update3Gram.reserve(1000000);
 Update4Gram.reserve(1000000);
 Update5Gram.reserve(1000000);

 ngram1_cache_allocator = new NGRAM1_CACHE_ALLOCATOR;
 ngram1_cache = new NGRAM1_CACHE( NGRAM1_CACHE::key_compare(), *ngram1_cache_allocator);

 ngram1_doccache_allocator = new NGRAM1_DOCCACHE_ALLOCATOR;
 ngram1_doccache = new NGRAM1_DOCCACHE( NGRAM1_DOCCACHE::key_compare(), *ngram1_doccache_allocator);


 ngram2_cache_allocator = new NGRAM2_CACHE_ALLOCATOR;
 ngram2_cache = new NGRAM2_CACHE( NGRAM2_CACHE::key_compare(), *ngram2_cache_allocator);

 ngram2_doccache_allocator = new NGRAM2_DOCCACHE_ALLOCATOR;
 ngram2_doccache = new NGRAM2_DOCCACHE( NGRAM2_DOCCACHE::key_compare(), *ngram2_doccache_allocator);


 ngram3_cache_allocator = new NGRAM3_CACHE_ALLOCATOR;
 ngram3_cache = new NGRAM3_CACHE( NGRAM3_CACHE::key_compare(), *ngram3_cache_allocator);

 ngram3_doccache_allocator = new NGRAM3_DOCCACHE_ALLOCATOR;
 ngram3_doccache = new NGRAM3_DOCCACHE( NGRAM3_DOCCACHE::key_compare(), *ngram3_doccache_allocator);


 ngram4_cache_allocator = new NGRAM4_CACHE_ALLOCATOR;
 ngram4_cache = new NGRAM4_CACHE( NGRAM4_CACHE::key_compare(), *ngram4_cache_allocator);

 ngram4_doccache_allocator = new NGRAM4_DOCCACHE_ALLOCATOR;
 ngram4_doccache = new NGRAM4_DOCCACHE( NGRAM4_DOCCACHE::key_compare(), *ngram4_doccache_allocator);


 ngram5_cache_allocator = new NGRAM5_CACHE_ALLOCATOR;
 ngram5_cache = new NGRAM5_CACHE( NGRAM5_CACHE::key_compare(), *ngram5_cache_allocator);

 ngram5_doccache_allocator = new NGRAM5_DOCCACHE_ALLOCATOR;
 ngram5_doccache = new NGRAM5_DOCCACHE( NGRAM5_DOCCACHE::key_compare(), *ngram5_doccache_allocator);

 return;
}





void RawNGramsCollector::SetDocCacheCapacity( int n )
{
 LEM_CHECKIT_Z(n>0);
 max_ngram1_doccache=max_ngram2_doccache=max_ngram3_doccache=
 max_ngram4_doccache=max_ngram5_doccache=n;

 return;
}


void RawNGramsCollector::SetNGramsCacheCapacity( int n )
{
 LEM_CHECKIT_Z(n>0);
 max_ngram1_cache=max_ngram2_cache=max_ngram3_cache=max_ngram4_cache=max_ngram5_cache=n;

 if( disk_cache2.NotNull() )
  disk_cache2->SetBufferSize(n);

 if( disk_cache3.NotNull() )
  disk_cache3->SetBufferSize(n);

 if( disk_cache4.NotNull() )
  disk_cache4->SetBufferSize(n);

 if( disk_cache5.NotNull() )
  disk_cache5->SetBufferSize(n);

 return;
}


RawNGramsCollector::~RawNGramsCollector(void)
{
 return;
}


void RawNGramsCollector::PresetTablesSuffix(void)
{
 if( !lemmatization )
  {
   suffix = "_literal";
   suffix0 = "_literal";
  }

 if( !segment_n.empty() )
  suffix += FString("_")+segment_n;

 suffix.re_clear();
 suffix0.re_clear();

 return;
}


void RawNGramsCollector::Prepare(
                                 lem::Ptr<Solarix::Dictionary> _dict,
                                 const lem::Path &_outdir,
                                 Solarix::Language _language
                                )
{
 LEM_CHECKIT_Z( _dict.NotNull() );
 LEM_CHECKIT_Z( db!=NULL );

 sol_id = _dict;
 outdir = _outdir;

 PresetTablesSuffix();

 sg = &sol_id->GetSynGram();
 la = &sol_id->GetLexAuto();

 // Добавим разделители потока слов, которые сбрасывают очереди N-грамм
 delims.push_back( L"." );
 delims.push_back( L"!" );
 delims.push_back( L"?" );

 // создаем схему в базе, если необходимые таблицы еще не созданы

 needs_index_creation1=needs_index_creation2=needs_index_creation3=
 needs_index_creation4=needs_index_creation5=false;

 lem::zbool create_words;

 if( needs_WORDS )
  {
   // Таблица WORDS%%% уже есть?
   if( db->TableExists(lem::format_str("NGRAM_WORDS%s",suffix.c_str())) )
    {
     if( needs_NGRAM1 && needs_NGRAM2 && needs_NGRAM3 && needs_NGRAM4 && needs_NGRAM5 )
      db->CleanWordsTable( suffix );
    }
   else
    create_words=true;
  }

 if( create_words )
  { 
   db->CreateTable_Words( suffix );
  }

 lem::zbool create_ngram1; 
 if( needs_NGRAM1 )
  {
   if( db->TableExists(lem::format_str("NGRAM1%s",suffix.c_str())) )
    {
     if( clean_database )
      db->CleanTables( suffix, 1 );
    }
   else
    create_ngram1=true;
  }

 if( create_ngram1 )
  {
   db->CreateTable_NGrams1(suffix);
   needs_index_creation1=true;
  }


 lem::zbool create_ngram2;
 if( needs_NGRAM2 )
  {
   if( db->TableExists(lem::format_str("NGRAM2%s",suffix.c_str())) )
    {
     if( clean_database )
      db->CleanTables( suffix, 2 );
    }
   else
    create_ngram2=true;
  }

 if( create_ngram2 )
  {
   db->CreateTable_NGrams2(suffix);
   needs_index_creation2=true;
  }


 lem::zbool create_ngram3;
 if( needs_NGRAM3 )
  {
   if( db->TableExists(lem::format_str("NGRAM3%s",suffix.c_str())) )
    {
     if( clean_database )
      db->CleanTables( suffix, 3 );
    }
   else
    create_ngram3=true;
  }

 if( create_ngram3 )
  {
   db->CreateTable_NGrams3(suffix);
   needs_index_creation3=true;
  }



 lem::zbool create_ngram4;
 if( needs_NGRAM4 )
  {
   if( db->TableExists(lem::format_str("NGRAM4%s",suffix.c_str())) )
    {
     if( clean_database )
      db->CleanTables( suffix, 4 );
    }
   else
    create_ngram4=true;
  }

 if( create_ngram4 )
  {
   db->CreateTable_NGrams4(suffix);
   needs_index_creation4=true;
  }

 lem::zbool create_ngram5;
 if( needs_NGRAM5 )
  {
   if( db->TableExists(lem::format_str("NGRAM5%s",suffix.c_str())) )
    {
     if( clean_database )
      db->CleanTables( suffix, 5 );
    }
   else
    create_ngram5=true;
  }

 if( create_ngram5 )
  {
   db->CreateTable_NGrams5(suffix);
   needs_index_creation5=true;
  }

 db->CommitTx();
 db->BeginTx(); 

 if( needs_NGRAM1 )
  {
   std::pair<int,int> p = db->GetMaxId( suffix, 1 );
   id1 = p.first+1;
   needs_index_creation1 = p.second==0;
  }

 if( !create_ngram2 && needs_NGRAM2 )
  {
   sprintf( asql, "idx23%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM2%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM2%s",suffix.c_str()));

   sprintf( asql, "idx24%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM2%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM2%s",suffix.c_str()));
  }

 if( needs_NGRAM2 )
  {
   std::pair<int,int> p = db->GetMaxId( suffix, 2 );
   int n2 = p.second;
   overload2 = n2>0;
   id2=p.first+1;
  }

 if( !create_ngram3 && needs_NGRAM3 )
  {
   sprintf( asql, "idx33%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM3%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM3%s",suffix.c_str()));

   sprintf( asql, "idx34%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM3%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM3%s",suffix.c_str()));

   sprintf( asql, "idx35%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM3%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM3%s",suffix.c_str()));
  }

 if( needs_NGRAM3 )
  {
   std::pair<int,int> p = db->GetMaxId( suffix, 3 );
   int n3 = p.second;
   overload3 = n3>0;
   id3=p.first+1;
  }


 if( !create_ngram4 && needs_NGRAM4 )
  {
   sprintf( asql, "idx43%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM4%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM4%s",suffix.c_str()));

   sprintf( asql, "idx44%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM4%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM4%s",suffix.c_str()));

   sprintf( asql, "idx45%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM4%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM4%s",suffix.c_str()));

   sprintf( asql, "idx46%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM4%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM4%s",suffix.c_str()));
  }

 if( needs_NGRAM4 )
  {
   std::pair<int,int> p = db->GetMaxId( suffix, 4 );
   int n4 = p.second;
   overload4 = n4>0;
   id4=p.first+1;
  }


 if( !create_ngram5 && needs_NGRAM5 )
  {
   sprintf( asql, "idx53%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM5%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM5%s",suffix.c_str()));

   sprintf( asql, "idx54%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM5%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM5%s",suffix.c_str()));

   sprintf( asql, "idx55%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM5%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM5%s",suffix.c_str()));

   sprintf( asql, "idx56%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM5%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM5%s",suffix.c_str()));

   sprintf( asql, "idx57%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM5%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM5%s",suffix.c_str()));
  }

 if( needs_NGRAM5 )
  {
   std::pair<int,int> p = db->GetMaxId( suffix, 5 );
   int n5 = p.second;
   overload5 = n5>0;
   id5=p.first+1;
  }


 if( !create_words && needs_WORDS )
  {
   sprintf( asql, "idxw1%s", suffix.c_str() );
   if( db->IndexExists(asql,lem::format_str("NGRAM_WORDS%s",suffix.c_str())) )
    db->DropIndex(asql,lem::format_str("NGRAM_WORDS%s",suffix.c_str())); 
  }


 if( needs_WORDS )
  {
   std::pair<int,int> p = db->GetWordsMaxId( suffix );
   const int nw = p.second;
   id_word=p.first+1;
   overload_words = nw>0;
  }

 segment_n.re_clear();

// if( !segment_n.empty() )
//  {
   db->RegisterSegment( segment_n, suffix0 );
//  }

 if( use_disk_cache && needs_NGRAM2 && !overload2 )
  {
   disk_cache2 = new NGrams2DiskCache('w');
   disk_cache2->SetBufferSize(max_ngram2_cache);
   FString table = lem::format_str( "NGRAM2%s", suffix.c_str() );
   disk_cache2->Open(outdir,table);
  } 

 if( use_disk_cache && needs_NGRAM3 && !overload3 )
  {
   disk_cache3 = new NGrams3DiskCache('w');
   disk_cache3->SetBufferSize(max_ngram3_cache);
   FString table3 = lem::format_str( "NGRAM3%s", suffix.c_str() );
   disk_cache3->Open(outdir,table3);
  } 

 if( use_disk_cache && needs_NGRAM4 && !overload4 )
  {
   disk_cache4 = new NGrams4DiskCache('w');
   disk_cache4->SetBufferSize(max_ngram4_cache);
   FString table4 = lem::format_str( "NGRAM4%s", suffix.c_str() );
   disk_cache4->Open(outdir,table4);
  } 


 if( use_disk_cache && needs_NGRAM5 && !overload5 )
  {
   disk_cache5 = new NGrams5DiskCache('w');
   disk_cache5->SetBufferSize(max_ngram5_cache);
   FString table5 = lem::format_str( "NGRAM5%s", suffix.c_str() );
   disk_cache5->Open(outdir,table5);
  } 


 db->CommitTx();
 db->BeginTx();
 

 // ****************** БД готова к записи

 return;
}



void RawNGramsCollector::BeginDocument( bool echo )
{
 return;
}


void RawNGramsCollector::EndDocument( bool echo )
{
 if( !sentence_word.empty() )
  Process( L"." ); // формально оборвем предложение.

 sentence_word.clear();

 doc_count++;

 InternalFlush(echo);

 return;
}




void RawNGramsCollector::PurgeDocCache( bool echo )
{
 const int ng1 = CastSizeToInt(ngram1_doccache->size()); 
 const int ng2 = CastSizeToInt(ngram2_doccache->size()); 
 const int ng3 = CastSizeToInt(ngram3_doccache->size()); 
 const int ng4 = CastSizeToInt(ngram4_doccache->size()); 
 const int ng5 = CastSizeToInt(ngram5_doccache->size()); 

 if( lem::LogFile::IsOpen() )
  lem::LogFile::Print( "Entering RawNGramsCollector::PurgeDocCache\n" );

 if( echo )
  {
   mout->printf( "\n%vf9Merging cache%vn: adding" );
  
   if( ng1>0 )
    mout->printf( " %vfE%d%vn 1grams", ng1 );

   if( ng2>0 )
    mout->printf( " %vfE%d%vn 2grams", ng2 );

   if( ng3>0 )
    mout->printf( " %vfE%d%vn 3grams", ng3 );

   if( ng4>0 )
    mout->printf( " %vfE%d%vn 4grams", ng4 );

   if( ng5>0 )
    mout->printf( " %vfE%d%vn 5grams", ng5 );

   mout->printf( "..." ); mout->flush();
  }

 PurgeDocCache1(echo);
 PurgeDocCache2(echo);
 PurgeDocCache3(echo);
 PurgeDocCache4(echo);
 PurgeDocCache5(echo);

 if( echo )
  mout->printf( " done\n" );

 UCString overload_words, overload_2grams, overload_3grams, overload_4grams, overload_5grams;
 
 if( words_cache_size>max_words_cache )
  overload_words = L"OVERLOAD";

 if( ngram2_cache_size>max_ngram2_cache )
  overload_2grams = L"OVERLOAD";

 if( ngram3_cache_size>max_ngram3_cache )
  overload_3grams = L"OVERLOAD";

 if( ngram4_cache_size>max_ngram4_cache )
  overload_4grams = L"OVERLOAD";

 if( ngram5_cache_size>max_ngram5_cache )
  overload_5grams = L"OVERLOAD";

 if( echo )
  mout->printf(
               "%vf9Words cache%vn:   %vfE%8d%vn items / %vfE%8d%vn capacity  %vfC%us%vn\n"
               "%vf92-grams cache%vn: %vfE%8d%vn items / %vfE%8d%vn capacity  %vfC%us%vn\n" 
               "%vf93-grams cache%vn: %vfE%8d%vn items / %vfE%8d%vn capacity  %vfC%us%vn\n" 
               "%vf94-grams cache%vn: %vfE%8d%vn items / %vfE%8d%vn capacity  %vfC%us%vn\n" 
               "%vf95-grams cache%vn: %vfE%8d%vn items / %vfE%8d%vn capacity  %vfC%us%vn\n" 
               , words_cache_size.value,  max_words_cache, overload_words.c_str()
               , ngram2_cache_size.value, max_ngram2_cache, overload_2grams.c_str()
               , ngram3_cache_size.value, max_ngram3_cache, overload_3grams.c_str()
               , ngram4_cache_size.value, max_ngram4_cache, overload_4grams.c_str()
               , ngram5_cache_size.value, max_ngram5_cache, overload_5grams.c_str()
              );

 if( lem::LogFile::IsOpen() )
  lem::LogFile::Print( "Leaving RawNGramsCollector::PurgeDocCache\n" );

 return;
}

static bool comp_first( const std::pair<int,int> & a, const std::pair<int,int> & b )
{ return a.first>b.first; }


void RawNGramsCollector::PurgeDocCache1( bool echo )
{
 // Объединяем кэш монограмм документа и таблицу на диске

 Update1Gram.clear();
 Update1Gram.reserve(ngram1_doccache->size());

 FString inserts;
 inserts.reserve(100000);

 int n_insert=0;

 const int n = CastSizeToInt(ngram1_doccache->size());
 const int n1 = n/10+1;
 int ip=0, p_prev=0;
 int insert=0, update=0;

 for( NGRAM1_DOCCACHE::const_iterator it = ngram1_doccache->begin();
      it!=ngram1_doccache->end();
      ++it, ++ip )
  {
   if( echo && !(ip%1024) )
    {
     int p = ip/n1;
     if( p>p_prev )
      {
       p_prev = p;
       mout->printf( " %d", p ); mout->flush();
      }
    }
   
   int id=UNKNOWN;

   NGRAM1_CACHE::const_iterator it1 = ngram1_cache->find( it->first );

   if( it1!=ngram1_cache->end() )
    {
     id = it1->second;
    }
   else
    {
     // В кэше не нашлось

     if( overload2 )
      {  
       // Ищем на диске.
       id = db->Find1Gram(suffix,it->first).first;
      }

     if( id!=-1 )
      {
       if( ngram1_cache_size<max_ngram1_cache )
        {
         // Закешируем запись (вариант работает при продолжении накопления в уже существующую базу
         ngram1_cache->insert( std::make_pair( it->first, id ) );
         ngram1_cache_size++;
        } 
       else
        {
         overload1=true;
         CreateIndeces1(echo);
        } 
      } 
    }
 
   if( id!=UNKNOWN )
    {
     // Такая 1-грамма уже есть в таблице - обновим ее частоту
     Update1Gram.push_back( std::make_pair(id,it->second.second) );
     update++;
    }
   else
    {
     if( ngram1_cache_size<max_ngram1_cache )
      {
       // Закешируем запись
//       ngram1_cache->insert( std::make_pair( it->first, id1 ) );
       ngram1_cache->insert( std::make_pair( it->first, it->second.first ) );
       ngram1_cache_size++;
      } 
     else
      {
       overload1=true;
       CreateIndeces1(echo);
      } 

     // Вносим запись в таблицу.

     if( n_insert>=db->MaxBulkInsert() )
      {
       // пачку ранее накопленных INSERT'ов сбрасываем в базу.
       db->FinishBulkInsert(inserts);
       inserts.clear();
       n_insert=0;
      }

     if( n_insert==0 )
      inserts = db->StartBulkInsert(suffix,1);
    
     inserts.Add_Dirty( db->AppendBulkInsert( suffix, n_insert, it->second.first, it->first, it->second.second ) );

     n_insert++;
     insert++;
    }
  }

 if( n_insert>0 )
  {
   db->FinishBulkInsert(inserts.c_str()); 
   inserts.clear();
  }

 if( !Update1Gram.empty() )
  {
   // Отсортируем список обновлений так, чтобы записи формировались в порядке возрастания id.
   std::sort( Update1Gram.begin(), Update1Gram.end(), comp_first );
   db->UpdateNGrams( suffix, 1, Update1Gram );
   Update1Gram.clear();
  }

 ngram1_doccache = new NGRAM1_DOCCACHE( NGRAM1_DOCCACHE::key_compare(), *ngram1_doccache_allocator);

 if( echo && n>0 )
  mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated ", insert, update );

 return;
}





void RawNGramsCollector::PurgeDocCache2( bool echo )
{
 // Объединяем кэш 2грамм документа и таблицу на диске
 
 const bool use_disk_cache = disk_cache2.NotNull();

 Update2Gram.clear();
 
 if( !use_disk_cache )
  Update2Gram.reserve(ngram2_doccache->size());

 FString inserts;

 if( !use_disk_cache )
  inserts.reserve(100000);

 int n_insert=0;

 const int n = CastSizeToInt(ngram2_doccache->size());
 const int n1 = n/10+1;
 int ip=0, p_prev=0;
 int insert=0, update=0;

 if( disk_cache2.NotNull() )
  disk_cache2->echo=echo;

 for( NGRAM2_DOCCACHE::const_iterator it = ngram2_doccache->begin();
      it!=ngram2_doccache->end();
      ++it, ++ip )
  {
   if( echo && !(ip%1024) )
    {
     int p = ip/n1;
     if( p>p_prev )
      {
       p_prev = p;
       mout->printf( " %d", p ); mout->flush();
      }
    }
   
   int id=UNKNOWN;

// ---------------------------
   #if LEM_DEBUGGING==1
   int idw1=it->first.first, idw2=it->first.second;
   int pre_id=it->second.first;
   int pre_w=it->second.second;
   #endif
/*
 if( it->first.first==16 && it->first.second==12910 && lem::LogFile::IsOpen() )
  {
   lem::MemFormatter mem;
   mem.printf( "DEBUG: id=%d w=%d", it->second.first, it->second.second );
   lem::LogFile::Print( mem.string() );
  }*/
// ---------------------------

   if( use_disk_cache )
    {
     disk_cache2->InsertOrUpdate( it->first.first, it->first.second, it->second.second );
    }
   else
    {
     NGRAM2_CACHE::const_iterator it2 = ngram2_cache->find( it->first );

     if( it2!=ngram2_cache->end() )
      {
       id = it2->second;
      }
     else
      {
       // В кэше не нашлось

       if( overload2 )
        {  
         // Ищем на диске.
         id = db->Find2Gram( suffix, it->first.first, it->first.second ).first;
        }

       if( id!=-1 )
        {
         if( ngram2_cache_size<max_ngram2_cache )
          {
           // Закешируем запись (вариант работает при продолжении накопления в уже существующую базу
           ngram2_cache->insert( std::make_pair( it->first, id ) );
           ngram2_cache_size++;
          } 
         else
          {
           overload2=true;
           CreateIndeces2(echo);
          } 
        } 
      }
 
     if( id!=UNKNOWN )
      {
       // Такая 2-грамма уже есть в таблице - обновим ее частоту
       Update2Gram.push_back( std::make_pair(id,it->second.second) );
       update++;
      }
     else
      {
       if( ngram2_cache_size<max_ngram2_cache )
        {
         // Закешируем запись
//         ngram2_cache->insert( std::make_pair( it->first, id2 ) );
         ngram2_cache->insert( std::make_pair( it->first, it->second.first ) );
         ngram2_cache_size++;
        } 
       else
        {
         overload2=true;
         CreateIndeces2(echo);
        } 

       // Вносим запись в таблицу.

       if( n_insert>=db->MaxBulkInsert() )
        {
         // пачку ранее накопленных INSERT'ов сбрасываем в базу.
         db->FinishBulkInsert(inserts);
         inserts.clear();
         n_insert=0;
        }

       if( n_insert==0 )
        inserts = db->StartBulkInsert(suffix,2);
    
       inserts.Add_Dirty( db->AppendBulkInsert( suffix, n_insert, it->second.first, it->first.first, it->first.second, it->second.second ) );
       n_insert++;
       insert++;
      }
    }
  }

 if( n_insert>0 )
  {
   db->FinishBulkInsert(inserts); 
   inserts.clear();
  }

 if( !Update2Gram.empty() )
  {
   // Отсортируем список обновлений так, чтобы записи формировались в порядке возрастания id.
   std::sort( Update2Gram.begin(), Update2Gram.end(), comp_first );
   db->UpdateNGrams( suffix, 2, Update2Gram );
   Update2Gram.clear();
  }

 ngram2_doccache = new NGRAM2_DOCCACHE( NGRAM2_DOCCACHE::key_compare(), *ngram2_doccache_allocator);

 if( echo && n>0 && !use_disk_cache )
  mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated ", insert, update );

 return;
}




void RawNGramsCollector::PurgeDocCache3( bool echo )
{
 // Объединяем кэш 3грамм документа и таблицу на диске

 const bool use_disk_cache = disk_cache3.NotNull();

 Update3Gram.clear();

 if( !use_disk_cache )
  Update3Gram.reserve(ngram3_doccache->size());

 const int n = CastSizeToInt(ngram3_doccache->size());
 const int n1 = n/10+1;
 int ip=0, p_prev=0;
 int insert=0, update=0;

 FString inserts;
 if( !use_disk_cache )
  inserts.reserve(100000);
 int n_insert=0;

 if( disk_cache3.NotNull() )
  disk_cache3->echo=echo;

 for( NGRAM3_DOCCACHE::const_iterator it = ngram3_doccache->begin();
      it!=ngram3_doccache->end();
      ++it, ++ip  )
  {
   if( echo && !(ip%1024) )
    {
     int p = ip/n1;
     if( p>p_prev )
      {
       p_prev = p;
       mout->printf( " %d", p ); mout->flush();
      }
    }

   int id=UNKNOWN;

   NGRAM3_CACHE::const_iterator it3 = ngram3_cache->find( it->first );

   if( use_disk_cache )
    {
     disk_cache3->InsertOrUpdate( it->first.first, it->first.second, it->first.third, it->second.second );
    }
   else
    {
     if( it3!=ngram3_cache->end() )
      {
       id = it3->second;
      }
     else
      {
       // В кэше не нашлось
       if( overload3 )
        {
         // Так как кэш переполнен, то ищем на диске. 
         id = db->Find3Gram( suffix, it->first.first, it->first.second, it->first.third ).first;
        }

       if( id!=-1 )
        {
         if( ngram3_cache_size<max_ngram3_cache )
          {
           // Закешируем запись (вариант работает при продолжении накопления в уже существующую базу
           ngram3_cache->insert( std::make_pair( it->first, id ) );
           ngram3_cache_size++;
          } 
         else
          {
           overload3=true;
           CreateIndeces3(echo);
          } 
        } 
      }
 
     if( id!=UNKNOWN )
      {
       // Такая 3-грамма уже есть в таблице - обновим ее частоту
       Update3Gram.push_back( std::make_pair(id,it->second.second) );
       update++;
      }
     else
      {
       if( ngram3_cache_size<max_ngram3_cache )
        {
         // Закешируем запись
//         ngram3_cache->insert( std::make_pair( it->first, id3 ) );
         ngram3_cache->insert( std::make_pair( it->first, it->second.first ) );
         ngram3_cache_size++;
        } 
       else
        {
         overload3=true;
         CreateIndeces3(echo);
        }

       // Вносим запись в таблицу
       if( n_insert>=db->MaxBulkInsert() )
        {
         // пучку ранее накопленных INSERT'ов сбрасываем в базу.
         db->FinishBulkInsert(inserts);
         inserts.clear();
         n_insert=0;
        }

       if( n_insert==0 )
        inserts = db->StartBulkInsert( suffix, 3 );
    
       inserts.Add_Dirty( db->AppendBulkInsert( suffix,
                                                n_insert,
                                                it->second.first, it->first.first, it->first.second,
                                                it->first.third, it->second.second ) );

       n_insert++;
       insert++;
      }
    }
  }

 if( n_insert>0 )
  {
   db->FinishBulkInsert(inserts);
   inserts.clear();
  }

 if( !Update3Gram.empty() )
  {
   // Отсортируем список обновлений так, чтобы записи формировались в порядке возрастания id.
   std::sort( Update3Gram.begin(), Update3Gram.end(), comp_first );
   db->UpdateNGrams( suffix, 3, Update3Gram );
   Update3Gram.clear();
  }

 ngram3_doccache = new NGRAM3_DOCCACHE( NGRAM3_DOCCACHE::key_compare(), *ngram3_doccache_allocator);

 if( echo && n>0 && !use_disk_cache )
  mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated ", insert, update );

 return;
}





void RawNGramsCollector::PurgeDocCache4( bool echo )
{
 // Объединяем кэш 4грамм документа и таблицу на диске

 const bool use_disk_cache = disk_cache4.NotNull();

 Update4Gram.clear();

 if( !use_disk_cache )
  Update4Gram.reserve(ngram4_doccache->size());

 const int n = CastSizeToInt(ngram4_doccache->size());
 const int n1 = n/10+1;
 int ip=0, p_prev=0;
 int insert=0, update=0;

 FString inserts;
 if( !use_disk_cache )
  inserts.reserve(100000);
 int n_insert=0;

 if( disk_cache4.NotNull() )
  disk_cache4->echo=echo;

 for( NGRAM4_DOCCACHE::const_iterator it = ngram4_doccache->begin();
      it!=ngram4_doccache->end();
      ++it, ++ip  )
  {
   if( echo && !(ip%1024) )
    {
     int p = ip/n1;
     if( p>p_prev )
      {
       p_prev = p;
       mout->printf( " %d", p ); mout->flush();
      }
    }

   int id=UNKNOWN;

   NGRAM4_CACHE::const_iterator it4 = ngram4_cache->find( it->first );

   if( use_disk_cache )
    {
     disk_cache4->InsertOrUpdate( it->first.first, it->first.second, it->first.third, it->first.fourth, it->second.second );
    }
   else
    {
     if( it4!=ngram4_cache->end() )
      {
       id = it4->second;
      }
     else
      {
       // В кэше не нашлось
       if( overload4 )
        {
         // Так как кэш переполнен, то ищем на диске. 
         id = db->Find4Gram( suffix, it->first.first, it->first.second, it->first.third, it->first.fourth ).first;
        }

       if( id!=-1 )
        {
         if( ngram4_cache_size<max_ngram4_cache )
          {
           // Закешируем запись (вариант работает при продолжении накопления в уже существующую базу
           ngram4_cache->insert( std::make_pair( it->first, id ) );
           ngram4_cache_size++;
          } 
         else
          {
           overload4=true;
           CreateIndeces4(echo);
          } 
        } 
      }
 
     if( id!=UNKNOWN )
      {
       // Такая 4-грамма уже есть в таблице - обновим ее частоту
       Update4Gram.push_back( std::make_pair(id,it->second.second) );
       update++;
      }
     else
      {
       if( ngram4_cache_size<max_ngram4_cache )
        {
         // Закешируем запись
//         ngram4_cache->insert( std::make_pair( it->first, id4 ) );
         ngram4_cache->insert( std::make_pair( it->first, it->second.first ) );
         ngram4_cache_size++;
        } 
       else
        {
         overload4=true;
         CreateIndeces4(echo);
        }

       // Вносим запись в таблицу
       if( n_insert>=db->MaxBulkInsert() )
        {
         // пучку ранее накопленных INSERT'ов сбрасываем в базу.
         db->FinishBulkInsert(inserts);
         inserts.clear();
         n_insert=0;
        }

       if( n_insert==0 )
        inserts = db->StartBulkInsert( suffix, 4 );
    
       inserts.Add_Dirty( db->AppendBulkInsert( suffix, n_insert,
            it->second.first, it->first.first, it->first.second, it->first.third,
            it->first.fourth, it->second.second ) );

       n_insert++;
       insert++;
      }
    }
  }

 if( n_insert>0 )
  {
   db->FinishBulkInsert(inserts);
   inserts.clear();
  }

 if( !Update4Gram.empty() )
  {
   // Отсортируем список обновлений так, чтобы записи формировались в порядке возрастания id.
   std::sort( Update4Gram.begin(), Update4Gram.end(), comp_first );
   db->UpdateNGrams( suffix, 4, Update4Gram );
   Update4Gram.clear();
  }

 ngram4_doccache = new NGRAM4_DOCCACHE( NGRAM4_DOCCACHE::key_compare(), *ngram4_doccache_allocator);

 if( echo && n>0 && !use_disk_cache )
  mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated ", insert, update );

 return;
}





void RawNGramsCollector::PurgeDocCache5( bool echo )
{
 // Объединяем кэш 5грамм документа и таблицу на диске

 const bool use_disk_cache = disk_cache5.NotNull();

 Update5Gram.clear();

 if( !use_disk_cache )
  Update5Gram.reserve(ngram5_doccache->size());

 const int n = CastSizeToInt(ngram5_doccache->size());
 const int n1 = n/10+1;
 int ip=0, p_prev=0;
 int insert=0, update=0;

 FString inserts;
 if( !use_disk_cache )
  inserts.reserve(100000);
 int n_insert=0;

 if( disk_cache5.NotNull() )
  disk_cache5->echo=echo;

 for( NGRAM5_DOCCACHE::const_iterator it = ngram5_doccache->begin();
      it!=ngram5_doccache->end();
      ++it, ++ip  )
  {
   if( echo && !(ip%1024) )
    {
     int p = ip/n1;
     if( p>p_prev )
      {
       p_prev = p;
       mout->printf( " %d", p ); mout->flush();
      }
    }

   int id=UNKNOWN;

   NGRAM5_CACHE::const_iterator it5 = ngram5_cache->find( it->first );

   if( use_disk_cache )
    {
     disk_cache5->InsertOrUpdate( it->first.first, it->first.second, it->first.third, it->first.fourth, it->first.fifth, it->second.second );
    }
   else
    {
     if( it5!=ngram5_cache->end() )
      {
       id = it5->second;
      }
     else
      {
       // В кэше не нашлось
       if( overload5 )
        {
         // Так как кэш переполнен, то ищем на диске. 
         id = db->Find5Gram( suffix, it->first.first, it->first.second, it->first.third, it->first.fourth, it->first.fifth ).first;
        }

       if( id!=-1 )
        {
         if( ngram5_cache_size<max_ngram5_cache )
          {
           // Закешируем запись (вариант работает при продолжении накопления в уже существующую базу
           ngram5_cache->insert( std::make_pair( it->first, id ) );
           ngram5_cache_size++;
          } 
         else
          {
           overload5=true;
           CreateIndeces5(echo);
          } 
        } 
      }
 
     if( id!=UNKNOWN )
      {
       // Такая 5-грамма уже есть в таблице - обновим ее частоту
       Update5Gram.push_back( std::make_pair(id,it->second.second) );
       update++;
      }
     else
      {
       if( ngram5_cache_size<max_ngram5_cache )
        {
         // Закешируем запись
//         ngram5_cache->insert( std::make_pair( it->first, id5 ) );
         ngram5_cache->insert( std::make_pair( it->first, it->second.first ) );
         ngram5_cache_size++;
        } 
       else
        {
         overload5=true;
         CreateIndeces5(echo);
        }

       // Вносим запись в таблицу
       if( n_insert>=db->MaxBulkInsert() )
        {
         // пучку ранее накопленных INSERT'ов сбрасываем в базу.
         db->FinishBulkInsert(inserts);
         inserts.clear();
         n_insert=0;
        }

       if( n_insert==0 )
        inserts = db->StartBulkInsert( suffix, 5 );
    
       inserts.Add_Dirty( db->AppendBulkInsert( suffix, n_insert,
            it->second.first, it->first.first, it->first.second, it->first.third, it->first.fourth, it->first.fifth,
            it->second.second ) );
       n_insert++;

       insert++;
      }
    }
  }

 if( n_insert>0 )
  {
   db->FinishBulkInsert(inserts);
   inserts.clear();
  }

 if( !Update5Gram.empty() )
  {
   // Отсортируем список обновлений так, чтобы записи формировались в порядке возрастания id.
   std::sort( Update5Gram.begin(), Update5Gram.end(), comp_first );
   db->UpdateNGrams( suffix, 5, Update5Gram );
   Update5Gram.clear();
  }

 ngram5_doccache = new NGRAM5_DOCCACHE( NGRAM5_DOCCACHE::key_compare(), *ngram5_doccache_allocator);

 if( echo && n>0 && !use_disk_cache )
  mout->printf( " %vfE%d%vn inserted, %vfE%d%vn updated ", insert, update );

 return;
}




void RawNGramsCollector::Process( const UCString &l )
{
 // Будем добавлять прочитанное слово в список предложения.
 sentence_word.push_back(l);

 if( delims.find(l)!=UNKNOWN || sentence_word.size()>=256 )
  {
   // *** Конец предложения ***

//   if( segmentation )
    // Объединяем мультилексемы.
//    la->Segmentation(sentence_word);

   ProcessSentence(sentence_word);
   sentence_word.clear();
  }

 return;
}



void RawNGramsCollector::ProcessSentence( const lem::MCollect<UCString> &sent )
{
 for( lem::Container::size_type i=0; i<sent.size(); ++i )
  {
   const UCString &w = sent[i];
   ProcessSingleWord(w);
  }

 // Сбрасываем накопленные очереди
 Push(UNKNOWN);
 ie21=ie22=
 ie31=ie32=ie33=
 ie41=ie42=ie43=ie44=
 ie51=ie52=ie53=ie54=ie55=UNKNOWN;

 return;
}


void RawNGramsCollector::ProcessSingleWord( const UCString &l )
{
 if( l.empty() ||
     //lem::is_int(l.c_str()) ||
     //(l.size()==1 && lem::is_udelim(l)) ||
     l.front()==L'_' || l.front()==L'.' ||
     (l.length()==1 && delims.find(l)!=UNKNOWN )
   ) 
  {
   // Сбрасываем накопленные очереди
   Push(UNKNOWN);
   ie21=ie22=
   ie31=ie32=ie33=
   ie41=ie42=ie43=ie44=
   ie51=ie52=ie53=ie54=ie55=UNKNOWN;
   return;
  }

 if( /*lem::is_int(l.c_str()) ||*/ l.front()==L'_' || l.front()==L'.' )
  return;

 Push( NormalizeAndRegisterWord(l) );

 return;
}



int RawNGramsCollector::NormalizeAndRegisterWord( const UCString &l )
{
 if( lemmatization )
  {
   // По возможности приводим к базовой форме
   UCString lemma;
   lemm->Lemmatize( l, lemma );
   return RegisterWord(lemma);
  }
 else
  {
   // Без приведения к базовой форме
   return RegisterWord(l);
  }
}



void RawNGramsCollector::Push( int id_word )
{
 if( accum_1grams )
  {
   if( id_word!=UNKNOWN )
    // Сохраняем 1-грамму (или увеличиваем частоту уже сохраненной)
    Store1Gram( id_word, 1 );
  }

 if( accum_2grams )
  {
   if( ie21==UNKNOWN )
    {
     ie21=id_word;
    }
   else if( ie22==UNKNOWN )
    {
     ie22=id_word;
    }
   else
    {
     // Сохраняем 2-грамму (или увеличиваем частоту уже сохраненной)
     Store2Gram( ie21, ie22, 1 );
     ie21 = ie22;
     ie22 = id_word;
    }
  }
 

 if( accum_3grams )
  {
   if( ie31==UNKNOWN )
    {
     ie31 = id_word;
    }
   else if( ie32==UNKNOWN )
    {
     ie32=id_word;
    }
   else if( ie33==UNKNOWN )
    {
     ie33=id_word;
    } 
   else
    {
     Store3Gram( ie31, ie32, ie33, 1 );
    
     ie31 = ie32;
     ie32 = ie33;
     ie33 = id_word;
    }
  }




 if( accum_4grams )
  {
   if( ie41==UNKNOWN )
    {
     ie41 = id_word;
    }
   else if( ie42==UNKNOWN )
    {
     ie42=id_word;
    }
   else if( ie43==UNKNOWN )
    {
     ie43=id_word;
    } 
   else if( ie44==UNKNOWN )
    {
     ie44=id_word;
    } 
   else
    {
     Store4Gram( ie41, ie42, ie43, ie44, 1 );
    
     ie41 = ie42;
     ie42 = ie43;
     ie43 = ie44;
     ie44 = id_word;
    }
  }



 if( accum_5grams )
  {
   if( ie51==UNKNOWN )
    {
     ie51 = id_word;
    }
   else if( ie52==UNKNOWN )
    {
     ie52=id_word;
    }
   else if( ie53==UNKNOWN )
    {
     ie53=id_word;
    } 
   else if( ie54==UNKNOWN )
    {
     ie54=id_word;
    } 
   else if( ie55==UNKNOWN )
    {
     ie55=id_word;
    } 
   else
    {
     Store5Gram( ie51, ie52, ie53, ie54, ie55, 1 );
    
     ie51 = ie52;
     ie52 = ie53;
     ie53 = ie54;
     ie54 = ie55;
     ie55 = id_word;
    }
  }

 return;
}


// *****************************************************************
// Сохраняем 1-грамму (или увеличиваем частоту уже сохраненной)
// *****************************************************************
void RawNGramsCollector::Store1Gram( int ie11, int freq )
{
 if( filter!=NULL && !filter->Probe(this,ie11) )
  return; 

 NGRAM1_DOCCACHE::iterator it = ngram1_doccache->find( ie11 );
 if( it!=ngram1_doccache->end() )
  {
   it->second.second+=freq;
  }
 else
  {
   // В кэше документа нет, добавляем.
   ngram1_doccache->insert( std::make_pair( ie11, std::make_pair( id1, freq ) ) );
   id1++;
  }

 return;
}


// *****************************************************************
// Сохраняем 2-грамму (или увеличиваем частоту уже сохраненной)
// *****************************************************************
void RawNGramsCollector::Store2Gram( int ie21, int ie22, int freq )
{
 if( filter!=NULL && !filter->Probe(this,ie21,ie22) )
  return; 

 NGRAM2_DOCCACHE::iterator it = ngram2_doccache->find( std::make_pair(ie21,ie22) );
 if( it!=ngram2_doccache->end() )
  {
   it->second.second+=freq;
  }
 else
  {
   // В кэше документа нет, добавляем.
   ngram2_doccache->insert( std::make_pair( std::make_pair(ie21,ie22), std::make_pair( id2, freq ) ) );
   id2++;
  }

 return;
}

// *****************************************************************
// Сохраняем 3-грамму (или увеличиваем частоту уже сохраненной)
// *****************************************************************
void RawNGramsCollector::Store3Gram( int ie31, int ie32, int ie33, int freq )
{
 if( filter!=NULL && !filter->Probe(this,ie31,ie32,ie33) )
  return; 

 lem::triple<int,int,int> ie123(ie31,ie32,ie33);
 NGRAM3_DOCCACHE::iterator it = ngram3_doccache->find( ie123 );
 if( it!=ngram3_doccache->end() )
  {
   it->second.second+=freq;
  }
 else
  {
   // В кэше документа нет, добавляем.
   ngram3_doccache->insert( std::make_pair( ie123, std::make_pair( id3, freq ) ) );
   id3++;
  }

 return;
}




// *****************************************************************
// Сохраняем 4-грамму (или увеличиваем частоту уже сохраненной)
// *****************************************************************
void RawNGramsCollector::Store4Gram( int ie41, int ie42, int ie43, int ie44, int freq )
{
 if( filter!=NULL && !filter->Probe(this,ie41,ie42,ie43,ie44) )
  return; 

 lem::foursome<int,int,int,int> ie1234(ie41,ie42,ie43,ie44);
 NGRAM4_DOCCACHE::iterator it = ngram4_doccache->find( ie1234 );
 if( it!=ngram4_doccache->end() )
  {
   it->second.second+=freq;
  }
 else
  {
   // В кэше документа нет, добавляем.
   ngram4_doccache->insert( std::make_pair( ie1234, std::make_pair( id4, freq ) ) );
   id4++;
  }

 return;
}




// *****************************************************************
// Сохраняем 5-грамму (или увеличиваем частоту уже сохраненной)
// *****************************************************************
void RawNGramsCollector::Store5Gram( int ie51, int ie52, int ie53, int ie54, int ie55, int freq )
{
 if( filter!=NULL && !filter->Probe(this,ie51,ie52,ie53,ie54,ie55) )
  return; 

 lem::tuple5<int,int,int,int,int> ie12345(ie51,ie52,ie53,ie54,ie55);
 NGRAM5_DOCCACHE::iterator it = ngram5_doccache->find( ie12345 );
 if( it!=ngram5_doccache->end() )
  {
   it->second.second+=freq;
  }
 else
  {
   // В кэше документа нет, добавляем.
   ngram5_doccache->insert( std::make_pair( ie12345, std::make_pair( id5, freq ) ) );
   id5++;
  }

 return;
}



void RawNGramsCollector::Report(void)
{
 int nw = 0;
 int n1 = 0;
 int n2 = 0;
 int n3 = 0;
 int n4 = 0;
 int n5 = 0;

 db->BeginTx();

 mout->printf( "Performing final DB analysis..." ); mout->flush();

 if( db->TableExists(lem::format_str( "NGRAM1%s", suffix.c_str() ) ) )
  n1 = db->GetMaxId( suffix, 1 ).second;

 if( db->TableExists(lem::format_str( "NGRAM2%s", suffix.c_str() ) ) )
  n2 = db->GetMaxId( suffix, 2 ).second;

 if( db->TableExists(lem::format_str( "NGRAM3%s", suffix.c_str() ) ) )
  n3 = db->GetMaxId( suffix, 3 ).second;

 if( db->TableExists(lem::format_str( "NGRAM4%s", suffix.c_str() ) ) )
  n4 = db->GetMaxId( suffix, 4 ).second;

 if( db->TableExists(lem::format_str( "NGRAM5%s", suffix.c_str() ) ) )
  n5 = db->GetMaxId( suffix, 5 ).second;

 if( db->TableExists(lem::format_str( "NGRAM_WORDS%s", suffix.c_str() ) ) )
  nw = db->GetWordsMaxId( suffix ).second;

 if( n1<0 ) n1=0;
 if( n2<0 ) n2=0;
 if( n3<0 ) n3=0;
 if( n4<0 ) n4=0;
 if( n5<0 ) n5=0;
 if( nw<0 ) nw=0;


 if( needs_NGRAM1 )
  {
   mout->printf( "*" ); mout->flush();
  }

 if( needs_NGRAM2 )
  {
   db->CreateIndeces2(suffix,2);
   mout->printf( "*" ); mout->flush();
  }

 if( needs_NGRAM3 )
  {
   db->CreateIndeces2(suffix,3);
   mout->printf( "*" ); mout->flush();
  }

 if( needs_NGRAM4 )
  {
   db->CreateIndeces2(suffix,4);
   mout->printf( "*" ); mout->flush();
  }

 if( needs_NGRAM5 )
  {
   db->CreateIndeces2(suffix,5);
   mout->printf( "*" ); mout->flush();
  }

 if( needs_WORDS )
  {
   db->CreateIndecesWord2(suffix);
   mout->printf( "*" ); mout->flush();
  }

 db->CommitTx();

 mout->printf( " %vfEdone%vn\n" );

 mout->printf( "Ngrams: %vfE%d%vn words, %vfE%d%vn 1-grams, %vfE%d%vn 2-grams, %vfE%d%vn 3-grams, %vfE%d%vn 4-grams, %vfE%d%vn 5-grams\n", nw, n1, n2, n3, n4, n5 );

 return;
}



int RawNGramsCollector::RegisterWord( const lem::UCString &word )
{
 // Сначала найдем в быстром кэше
 std::map<UCString,int>::const_iterator it = words_cache.find(word);
 if( it!=words_cache.end() )
  // Нашли!
  return it->second;

 int id = UNKNOWN;

 if( overload_words )
  {
   // Так как кэш перегружен, то не все записи находятся в памяти - надо делать
   // трудоемкий поиск на диске.
   id = db->FindWord(suffix,word);
  }

 if( id==UNKNOWN )
  {
   db->InsertWord( suffix, id_word, word );
   id = id_word;
   id_word++;
  }

 // В кэше нет, внесем, если не достигнут предельный размер кэша.
 if( words_cache_size<max_words_cache )
  {
   words_cache_size++;
   words_cache.insert( std::make_pair(word,id) );
  }
 else
  {
   overload_words=true;
  }

 return id;
}


int RawNGramsCollector::FindIE( const lem::UCString &word )
{
 return sol_id->seeker->Find(word,false);
}



const UCString& RawNGramsCollector::IE_2_Word( int ie ) const
{
 LEM_CHECKIT_Z(ie!=UNKNOWN);
 const SG_Entry &e = sol_id->GetSynGram().GetEntry(ie);
 return e.GetName();
}


void RawNGramsCollector::Merge( const lem::Path &dbfolder, bool echo )
{
/*
 lem::Path dbfile( dbfolder );
 if( dbfile.IsFolder() )
  dbfile.ConcateLeaf( L"NGRAMS" );

 mout->printf( "Merging [%vfE%us%vn]...\n", dbfile.GetUnicode().c_str() );
 mout->flush(); 

 NGramsDBMS src;
 src.Connect(dbfile);

 BeginDocument(echo);

 lem::FString sql1= lem::format_str( "SELECT wrd.word, w"
                  " FROM NGRAM1%s, WORDS%s wrd"
                  " WHERE wrd.id=iword1", suffix.c_str(), suffix.c_str() );

 lem::FString sql2 = lem::format_str( "SELECT wrd1.word, wrd2.word, w"
                 " FROM NGRAM2%s, WORDS%s wrd1, WORDS%s wrd2"
                 " WHERE wrd1.id=iword1 AND wrd2.id=iword2", suffix.c_str(), suffix.c_str(), suffix.c_str() ); 

 lem::FString sql3= lem::format_str( "SELECT wrd1.word, wrd2.word, wrd3.word, w"
                 " FROM NGRAM3%s, WORDS%s wrd1, WORDS%s wrd2, WORDS%s wrd3"
                 " WHERE wrd1.id=iword1 AND wrd2.id=iword2 AND wrd3.id=iword3"
    , suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str() );


 lem::FString sql4= lem::format_str( "SELECT wrd1.word, wrd2.word, wrd3.word, wrd4.word w"
                 " FROM NGRAM4%s, WORDS%s wrd1, WORDS%s wrd2, WORDS%s wrd3, WORDS%s wrd4"
                 " WHERE wrd1.id=iword1 AND wrd2.id=iword2 AND wrd3.id=iword3 AND wrd4.id=iword4"
    , suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str() );

 lem::FString sql5= lem::format_str( "SELECT wrd1.word, wrd2.word, wrd3.word, wrd4.word, wrd5.word, w"
                 " FROM NGRAM5%s, WORDS%s wrd1, WORDS%s wrd2, WORDS%s wrd3, WORDS%s wrd4, WORDS%s wrd5"
                 " WHERE wrd1.id=iword1 AND wrd2.id=iword2 AND wrd3.id=iword3 AND wrd4.id=iword4 AND wrd5.id=iword5"
    , suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str(), suffix.c_str() );

 #if defined SOL_SQLITE_NGRAMS

 if( needs_NGRAM1 )
  {
   const int n1 = src.SelectInt( lem::format_str("SELECT count_n1 FROM STATS1%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM1%s ", n1, suffix.c_str() );
     mout->flush();
    }
 
   const int n100 = n1/100;
   int prev_p=0;

   sqlite3_stmt *stmt1=NULL;
   int res = sqlite3_prepare_v2( src.hdb, sql1.c_str(), -1, &stmt1, NULL );
   if( res==SQLITE_OK )
    {
     int i=0; 
     while( sqlite3_step( stmt1 ) == SQLITE_ROW )
      {
       const wchar_t *wrd1 = (const wchar_t*)sqlite3_column_text16(stmt1,0);
       const int freq = sqlite3_column_int(stmt1,1);
       const int i1 = NormalizeAndRegisterWord(wrd1);

       Store1Gram( i1, freq );

       i++;
       if( echo && !(i%100000) )
        if( n100>0 )
         {
          int p = i/n100;
          if( p>prev_p )
           {
            mout->printf( "%d%% ", p ); mout->flush();
            prev_p=p;
           }  
         }  
      } 

     if( echo ) mout->printf( " %vfEDone%vn\n" );
     sqlite3_finalize(stmt1);
    }
  }

 if( needs_NGRAM2 )
  {
   const int n2 = src.SelectInt( lem::format_str("SELECT count_n2 FROM STATS2%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM2%s", n2, suffix.c_str() );
     mout->flush();
    }

   const int n100 = n2/100;
   int prev_p=0;
   int i=0; 

   sqlite3_stmt *stmt2=NULL;
   int res = sqlite3_prepare_v2( src.hdb, sql2.c_str(), -1, &stmt2, NULL );
   if( res==SQLITE_OK )
    {
     while( sqlite3_step( stmt2 ) == SQLITE_ROW )
      {
       const wchar_t *wrd1 = (const wchar_t*)sqlite3_column_text16(stmt2,0);
       const wchar_t *wrd2 = (const wchar_t*)sqlite3_column_text16(stmt2,1);
       const int freq = sqlite3_column_int(stmt2,2);

       const int i1 = NormalizeAndRegisterWord(wrd1);
       const int i2 = NormalizeAndRegisterWord(wrd2);

       Store2Gram( i1, i2, freq );

       i++;
       if( echo && !(i%100000) )
        if( n100>0 )
         {
          int p = i/n100;
          if( p>prev_p )
           {
            mout->printf( "%d%% ", p ); mout->flush();
            prev_p=p;
           }  
         }  
      } 

     if( echo ) mout->printf( " %vfEDone%vn\n" );
     sqlite3_finalize(stmt2);
    }
  }

 if( needs_NGRAM3 )
  {
   const int n3 = src.SelectInt( lem::format_str("SELECT count_n3 FROM STATS3%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM3%s ", n3, suffix.c_str() );
     mout->flush();
    }

   const int n100 = n3/100;
   int prev_p=0;
   int i=0; 

   sqlite3_stmt *stmt3=NULL;
   int res = sqlite3_prepare_v2( src.hdb, sql3.c_str(), -1, &stmt3, NULL );
   if( res==SQLITE_OK )
    {
     while( sqlite3_step( stmt3 ) == SQLITE_ROW )
      {
       const wchar_t *wrd1 = (const wchar_t*)sqlite3_column_text16(stmt3,0);
       const wchar_t *wrd2 = (const wchar_t*)sqlite3_column_text16(stmt3,1);
       const wchar_t *wrd3 = (const wchar_t*)sqlite3_column_text16(stmt3,2);
       const int freq = sqlite3_column_int(stmt3,3);

       const int i1 = NormalizeAndRegisterWord(wrd1);
       const int i2 = NormalizeAndRegisterWord(wrd2);
       const int i3 = NormalizeAndRegisterWord(wrd3);

       Store3Gram( i1, i2, i3, freq );

       i++;
       if( echo && !(i%100000) )
        if( n100>0 )
         {
          int p = i/n100;
          if( p>prev_p )
           {
            mout->printf( "%d%% ", p ); mout->flush();
            prev_p=p;
           }  
         }  
      } 

     if( echo ) mout->printf( " %vfEDone%vn\n" );
     sqlite3_finalize(stmt3);
    }
  }



 if( needs_NGRAM4 )
  {
   const int n4 = src.SelectInt( lem::format_str("SELECT count_n4 FROM STATS4%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM4%s ", n4, suffix.c_str() );
     mout->flush();
    }

   const int n100 = n4/100;
   int prev_p=0;
   int i=0; 

   sqlite3_stmt *stmt3=NULL;
   int res = sqlite3_prepare_v2( src.hdb, sql4.c_str(), -1, &stmt3, NULL );
   if( res==SQLITE_OK )
    {
     while( sqlite3_step( stmt3 ) == SQLITE_ROW )
      {
       const wchar_t *wrd1 = (const wchar_t*)sqlite3_column_text16(stmt3,0);
       const wchar_t *wrd2 = (const wchar_t*)sqlite3_column_text16(stmt3,1);
       const wchar_t *wrd3 = (const wchar_t*)sqlite3_column_text16(stmt3,2);
       const wchar_t *wrd4 = (const wchar_t*)sqlite3_column_text16(stmt3,3);
       const int freq = sqlite3_column_int(stmt3,4);

       const int i1 = NormalizeAndRegisterWord(wrd1);
       const int i2 = NormalizeAndRegisterWord(wrd2);
       const int i3 = NormalizeAndRegisterWord(wrd3);
       const int i4 = NormalizeAndRegisterWord(wrd4);

       Store4Gram( i1, i2, i3, i4, freq );

       i++;
       if( echo && !(i%100000) )
        if( n100>0 )
         {
          int p = i/n100;
          if( p>prev_p )
           {
            mout->printf( "%d%% ", p ); mout->flush();
            prev_p=p;
           }  
         }  
      } 

     if( echo ) mout->printf( " %vfEDone%vn\n" );
     sqlite3_finalize(stmt3);
    }
  }




 if( needs_NGRAM5 )
  {
   const int n5 = src.SelectInt( lem::format_str("SELECT count_n5 FROM STATS5%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM5%s ", n5, suffix.c_str() );
     mout->flush();
    }

   const int n100 = n5/100;
   int prev_p=0;
   int i=0; 

   sqlite3_stmt *stmt3=NULL;
   int res = sqlite3_prepare_v2( src.hdb, sql5.c_str(), -1, &stmt3, NULL );
   if( res==SQLITE_OK )
    {
     while( sqlite3_step( stmt3 ) == SQLITE_ROW )
      {
       const wchar_t *wrd1 = (const wchar_t*)sqlite3_column_text16(stmt3,0);
       const wchar_t *wrd2 = (const wchar_t*)sqlite3_column_text16(stmt3,1);
       const wchar_t *wrd3 = (const wchar_t*)sqlite3_column_text16(stmt3,2);
       const wchar_t *wrd4 = (const wchar_t*)sqlite3_column_text16(stmt3,3);
       const wchar_t *wrd5 = (const wchar_t*)sqlite3_column_text16(stmt3,4);
       const int freq = sqlite3_column_int(stmt3,5);

       const int i1 = NormalizeAndRegisterWord(wrd1);
       const int i2 = NormalizeAndRegisterWord(wrd2);
       const int i3 = NormalizeAndRegisterWord(wrd3);
       const int i4 = NormalizeAndRegisterWord(wrd4);
       const int i5 = NormalizeAndRegisterWord(wrd5);

       Store5Gram( i1, i2, i3, i4, i5, freq );

       i++;
       if( echo && !(i%100000) )
        if( n100>0 )
         {
          int p = i/n100;
          if( p>prev_p )
           {
            mout->printf( "%d%% ", p ); mout->flush();
            prev_p=p;
           }  
         }  
      } 

     if( echo ) mout->printf( " %vfEDone%vn\n" );
     sqlite3_finalize(stmt3);
    }
  }


 #elif defined SOL_FIREBIRD_NGRAMS

 src.BeginReadTx();
 
 if( needs_NGRAM1 )
  {
   const int n1 = src.SelectInt( lem::format_str("SELECT count_n1 FROM STATS1%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM1%s ", n1, suffix.c_str() );
     mout->flush();
    }
 
   const int n100 = n1/100;
   int prev_p=0;
   int i=0;

   isc_stmt_handle stmt = NULL;
   short flag0=0, flag1=1;

   sqlchar word;
   int freq=0;

   XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(2));
   sqlda->sqln = 2;
   sqlda->version = 1;

   sqlda->sqlvar[0].sqldata = (char *)word;
   sqlda->sqlvar[0].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[0].sqlind  = &flag0;

   sqlda->sqlvar[1].sqldata = (char *)&freq;
   sqlda->sqlvar[1].sqltype = SQL_LONG+1;
   sqlda->sqlvar[1].sqllen  = sizeof(freq);
   sqlda->sqlvar[1].sqlind  = &flag1;

   if( !isc_dsql_allocate_statement( src.status, &src.hdb, &stmt ) )
    {
     if( !isc_dsql_prepare( src.status, &src.htx, &stmt, 0, sql1.c_str(), 1, sqlda ) )
      {
       if( !isc_dsql_execute( src.status, &src.htx, &stmt, 1, NULL) )
        {
         while(true)
          {
           *word=0;
           long fetch_stat = isc_dsql_fetch( src.status, &stmt, 1, sqlda );
           if( fetch_stat!=0 )
            {
             if( fetch_stat==100 )
             break;  

             #if LEM_DEBUGGING==1
             isc_print_status(src.status);
             #endif
             break; 
            }

           LEM_CHECKIT_Z( freq>0 );

           RTrim( word, sqlda->sqlvar[0].sqllen );
           UCString uword( from_utf8(word).c_str() );
           const int i1 = NormalizeAndRegisterWord(uword);
           Store1Gram( i1, freq );

           i++;
           if( echo && !(i%100000) )
            if( n100>0 )
             {
              int p = i/n100;
              if( p>prev_p )
               {
                mout->printf( "%d%% ", p ); mout->flush();
                prev_p=p;
               }  
             }  
          }

         if( echo ) mout->printf( " %vfEDone%vn\n" );

         isc_dsql_free_statement( src.status, &stmt, DSQL_drop);
        }
      }
    }

   free(sqlda);
  }

 if( needs_NGRAM2 )
  {
   const int n2 = src.SelectInt( lem::format_str("SELECT count_n2 FROM STATS2%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM2%s ", n2, suffix.c_str() );
     mout->flush();
    }

   const int n100 = n2/100;
   int prev_p=0;
   int i=0; 


   isc_stmt_handle stmt = NULL;
   short flag0=0, flag1=1, flag2=2;

   sqlchar word1, word2;
   int freq=0;

   XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(3));
   sqlda->sqln = 3;
   sqlda->version = 1;

   sqlda->sqlvar[0].sqldata = (char *)word1;
   sqlda->sqlvar[0].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[0].sqlind  = &flag0;

   sqlda->sqlvar[1].sqldata = (char *)word2;
   sqlda->sqlvar[1].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[1].sqlind  = &flag1;

   sqlda->sqlvar[2].sqldata = (char *)&freq;
   sqlda->sqlvar[2].sqltype = SQL_LONG+1;
   sqlda->sqlvar[2].sqllen  = sizeof(freq);
   sqlda->sqlvar[2].sqlind  = &flag2;

   if( !isc_dsql_allocate_statement( src.status, &src.hdb, &stmt ) )
    {
     if( !isc_dsql_prepare( src.status, &src.htx, &stmt, 0, sql2.c_str(), 1, sqlda ) )
      {
       if( !isc_dsql_execute( src.status, &src.htx, &stmt, 1, NULL) )
        {
         while(true)
          {
           *word1=*word2=0;
           long fetch_stat = isc_dsql_fetch( src.status, &stmt, 1, sqlda );
           if( fetch_stat!=0 )
            {
             if( fetch_stat==100 )
              break;  

             #if LEM_DEBUGGING==1
             isc_print_status(src.status);
             #endif
             break; 
            }

           RTrim( word1, sqlda->sqlvar[0].sqllen );
           RTrim( word2, sqlda->sqlvar[1].sqllen );
           UCString uword1( from_utf8(word1).c_str() );
           UCString uword2( from_utf8(word2).c_str() );
           const int i1 = NormalizeAndRegisterWord(uword1);
           const int i2 = NormalizeAndRegisterWord(uword2);

           LEM_CHECKIT_Z( i1!=UNKNOWN );
           LEM_CHECKIT_Z( i2!=UNKNOWN );
           LEM_CHECKIT_Z( freq>0 );

           Store2Gram( i1, i2, freq );

           i++;
           if( echo && !(i%100000) )
            if( n100>0 )
             {
              int p = i/n100;
              if( p>prev_p )
               {
                mout->printf( "%d%% ", p ); mout->flush();
                prev_p=p;
               }  
             }  
          }

         if( echo ) mout->printf( " %vfEDone%vn\n" );

         isc_dsql_free_statement( src.status, &stmt, DSQL_drop);
        }
      }
    }

   free(sqlda);
  }



 if( needs_NGRAM3 )
  {
   const int n3 = src.SelectInt( lem::format_str("SELECT count_n3 FROM STATS3%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM3%s ", n3, suffix.c_str() );
     mout->flush();
    }

   const int n100 = n3/100;
   int prev_p=0;
   int i=0; 

   isc_stmt_handle stmt = NULL;
   short flag0=0, flag1=1, flag2=2, flag3=3;

   sqlchar word1, word2, word3;
   int freq=0;

   XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(4));
   sqlda->sqln = 4;
   sqlda->version = 1;

   sqlda->sqlvar[0].sqldata = (char *)word1;
   sqlda->sqlvar[0].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[0].sqlind  = &flag0;

   sqlda->sqlvar[1].sqldata = (char *)word2;
   sqlda->sqlvar[1].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[1].sqlind  = &flag1;

   sqlda->sqlvar[2].sqldata = (char *)word3;
   sqlda->sqlvar[2].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[2].sqlind  = &flag2;

   sqlda->sqlvar[3].sqldata = (char *)&freq;
   sqlda->sqlvar[3].sqltype = SQL_LONG+1;
   sqlda->sqlvar[3].sqllen  = sizeof(freq);
   sqlda->sqlvar[3].sqlind  = &flag3;

   if( !isc_dsql_allocate_statement( src.status, &src.hdb, &stmt ) )
    {
     if( !isc_dsql_prepare( src.status, &src.htx, &stmt, 0, sql3.c_str(), 1, sqlda ) )
      {
       if( !isc_dsql_execute( src.status, &src.htx, &stmt, 1, NULL) )
        {
         while(true)
          {
           *word1=*word2=*word3=0;
           long fetch_stat = isc_dsql_fetch( src.status, &stmt, 1, sqlda );
           if( fetch_stat!=0 )
            {
             if( fetch_stat==100 )
              break;  

             #if LEM_DEBUGGING==1
             isc_print_status(src.status);
             #endif
             break; 
            }

           RTrim( word1, sqlda->sqlvar[0].sqllen );
           RTrim( word2, sqlda->sqlvar[1].sqllen );
           RTrim( word3, sqlda->sqlvar[2].sqllen );
           UCString uword1( from_utf8(word1).c_str() );
           UCString uword2( from_utf8(word2).c_str() );
           UCString uword3( from_utf8(word3).c_str() );
           const int i1 = NormalizeAndRegisterWord(uword1);
           const int i2 = NormalizeAndRegisterWord(uword2);
           const int i3 = NormalizeAndRegisterWord(uword3);

           LEM_CHECKIT_Z( i1!=UNKNOWN );
           LEM_CHECKIT_Z( i2!=UNKNOWN );
           LEM_CHECKIT_Z( i3!=UNKNOWN );
           LEM_CHECKIT_Z( freq>0 );

           Store3Gram( i1, i2, i3, freq );

           i++;
           if( echo && !(i%100000) )
            if( n100>0 )
             {
              int p = i/n100;
              if( p>prev_p )
               {
                mout->printf( "%d%% ", p ); mout->flush();
                prev_p=p;
               }  
             }  
          }

         if( echo ) mout->printf( " %vfEDone%vn\n" );

         isc_dsql_free_statement( src.status, &stmt, DSQL_drop);
        }
      }
    }

   free(sqlda);
  }




 if( needs_NGRAM4 )
  {
   const int n4 = src.SelectInt( lem::format_str("SELECT count_n4 FROM STATS4%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM4%s ", n4, suffix.c_str() );
     mout->flush();
    }

   const int n100 = n4/100;
   int prev_p=0;
   int i=0; 

   isc_stmt_handle stmt = NULL;
   short flag0=0, flag1=1, flag2=2, flag3=3, flag4=4;

   sqlchar word1, word2, word3, word4;
   int freq=0;

   XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(5));
   sqlda->sqln = 5;
   sqlda->version = 1;

   sqlda->sqlvar[0].sqldata = (char *)word1;
   sqlda->sqlvar[0].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[0].sqlind  = &flag0;

   sqlda->sqlvar[1].sqldata = (char *)word2;
   sqlda->sqlvar[1].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[1].sqlind  = &flag1;

   sqlda->sqlvar[2].sqldata = (char *)word3;
   sqlda->sqlvar[2].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[2].sqlind  = &flag2;

   sqlda->sqlvar[3].sqldata = (char *)word4;
   sqlda->sqlvar[3].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[3].sqlind  = &flag3;

   sqlda->sqlvar[4].sqldata = (char *)&freq;
   sqlda->sqlvar[4].sqltype = SQL_LONG+1;
   sqlda->sqlvar[4].sqllen  = sizeof(freq);
   sqlda->sqlvar[4].sqlind  = &flag4;

   if( !isc_dsql_allocate_statement( src.status, &src.hdb, &stmt ) )
    {
     if( !isc_dsql_prepare( src.status, &src.htx, &stmt, 0, sql4.c_str(), 1, sqlda ) )
      {
       if( !isc_dsql_execute( src.status, &src.htx, &stmt, 1, NULL) )
        {
         while(true)
          {
           *word1=*word2=*word3=*word4=0;
           long fetch_stat = isc_dsql_fetch( src.status, &stmt, 1, sqlda );
           if( fetch_stat!=0 )
            {
             if( fetch_stat==100 )
              break;  

             #if LEM_DEBUGGING==1
             isc_print_status(src.status);
             #endif
             break; 
            }

           RTrim( word1, sqlda->sqlvar[0].sqllen );
           RTrim( word2, sqlda->sqlvar[1].sqllen );
           RTrim( word3, sqlda->sqlvar[2].sqllen );
           RTrim( word4, sqlda->sqlvar[3].sqllen );
           UCString uword1( from_utf8(word1).c_str() );
           UCString uword2( from_utf8(word2).c_str() );
           UCString uword3( from_utf8(word3).c_str() );
           UCString uword4( from_utf8(word4).c_str() );
           const int i1 = NormalizeAndRegisterWord(uword1);
           const int i2 = NormalizeAndRegisterWord(uword2);
           const int i3 = NormalizeAndRegisterWord(uword3);
           const int i4 = NormalizeAndRegisterWord(uword4);

           LEM_CHECKIT_Z( i1!=UNKNOWN );
           LEM_CHECKIT_Z( i2!=UNKNOWN );
           LEM_CHECKIT_Z( i3!=UNKNOWN );
           LEM_CHECKIT_Z( i4!=UNKNOWN );
           LEM_CHECKIT_Z( freq>0 );

           Store4Gram( i1, i2, i3, i4, freq );

           i++;
           if( echo && !(i%100000) )
            if( n100>0 )
             {
              int p = i/n100;
              if( p>prev_p )
               {
                mout->printf( "%d%% ", p ); mout->flush();
                prev_p=p;
               }  
             }  
          }

         if( echo ) mout->printf( " %vfEDone%vn\n" );

         isc_dsql_free_statement( src.status, &stmt, DSQL_drop);
        }
      }
    }

   free(sqlda);
  }






 if( needs_NGRAM5 )
  {
   const int n5 = src.SelectInt( lem::format_str("SELECT count_n5 FROM STATS5%s", suffix.c_str() ), 0 );

   if( echo )
    {
     mout->printf( "Adding %vfE%d%vn records to NGRAM5%s ", n5, suffix.c_str() );
     mout->flush();
    }

   const int n100 = n5/100;
   int prev_p=0;
   int i=0; 

   isc_stmt_handle stmt = NULL;
   short flag0=0, flag1=1, flag2=2, flag3=3, flag4=4, flag5=5;

   sqlchar word1, word2, word3, word4, word5;
   int freq=0;

   XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(6));
   sqlda->sqln = 6;
   sqlda->version = 1;

   sqlda->sqlvar[0].sqldata = (char *)word1;
   sqlda->sqlvar[0].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[0].sqlind  = &flag0;

   sqlda->sqlvar[1].sqldata = (char *)word2;
   sqlda->sqlvar[1].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[1].sqlind  = &flag1;

   sqlda->sqlvar[2].sqldata = (char *)word3;
   sqlda->sqlvar[2].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[2].sqlind  = &flag2;

   sqlda->sqlvar[3].sqldata = (char *)word4;
   sqlda->sqlvar[3].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[3].sqlind  = &flag3;

   sqlda->sqlvar[4].sqldata = (char *)word5;
   sqlda->sqlvar[4].sqltype = SQL_TEXT+1;
   sqlda->sqlvar[4].sqlind  = &flag4;

   sqlda->sqlvar[5].sqldata = (char *)&freq;
   sqlda->sqlvar[5].sqltype = SQL_LONG+1;
   sqlda->sqlvar[5].sqllen  = sizeof(freq);
   sqlda->sqlvar[5].sqlind  = &flag5;

   if( !isc_dsql_allocate_statement( src.status, &src.hdb, &stmt ) )
    {
     if( !isc_dsql_prepare( src.status, &src.htx, &stmt, 0, sql5.c_str(), 1, sqlda ) )
      {
       if( !isc_dsql_execute( src.status, &src.htx, &stmt, 1, NULL) )
        {
         while(true)
          {
           *word1=*word2=*word3=*word4=*word5=0;
           long fetch_stat = isc_dsql_fetch( src.status, &stmt, 1, sqlda );
           if( fetch_stat!=0 )
            {
             if( fetch_stat==100 )
              break;  

             #if LEM_DEBUGGING==1
             isc_print_status(src.status);
             #endif
             break; 
            }

           RTrim( word1, sqlda->sqlvar[0].sqllen );
           RTrim( word2, sqlda->sqlvar[1].sqllen );
           RTrim( word3, sqlda->sqlvar[2].sqllen );
           RTrim( word4, sqlda->sqlvar[3].sqllen );
           RTrim( word5, sqlda->sqlvar[4].sqllen );
           UCString uword1( from_utf8(word1).c_str() );
           UCString uword2( from_utf8(word2).c_str() );
           UCString uword3( from_utf8(word3).c_str() );
           UCString uword4( from_utf8(word4).c_str() );
           UCString uword5( from_utf8(word5).c_str() );
           const int i1 = NormalizeAndRegisterWord(uword1);
           const int i2 = NormalizeAndRegisterWord(uword2);
           const int i3 = NormalizeAndRegisterWord(uword3);
           const int i4 = NormalizeAndRegisterWord(uword4);
           const int i5 = NormalizeAndRegisterWord(uword5);

           LEM_CHECKIT_Z( i1!=UNKNOWN );
           LEM_CHECKIT_Z( i2!=UNKNOWN );
           LEM_CHECKIT_Z( i3!=UNKNOWN );
           LEM_CHECKIT_Z( i4!=UNKNOWN );
           LEM_CHECKIT_Z( i5!=UNKNOWN );
           LEM_CHECKIT_Z( freq>0 );

           Store5Gram( i1, i2, i3, i4, i5, freq );

           i++;
           if( echo && !(i%100000) )
            if( n100>0 )
             {
              int p = i/n100;
              if( p>prev_p )
               {
                mout->printf( "%d%% ", p ); mout->flush();
                prev_p=p;
               }  
             }  
          }

         if( echo ) mout->printf( " %vfEDone%vn\n" );

         isc_dsql_free_statement( src.status, &stmt, DSQL_drop);
        }
      }
    }

   free(sqlda);
  }


 src.Commit();

 #endif

 db->CommitRetaining();

 EndDocument(echo);

 mout->printf( "%vfEAll data merged.%vn\n" );
*/

 return;
}




void RawNGramsCollector::CreateIndeces( bool echo )
{
 CreateIndeces1(echo);
 CreateIndeces2(echo);
 CreateIndeces3(echo);
 CreateIndeces4(echo);
 CreateIndeces5(echo);

 db->CommitCreatedIndeces();

 return;
}



void RawNGramsCollector::CreateIndeces1( bool echo )
{
 if( !needs_index_creation1 )
  return;
 
 needs_index_creation1 = false;

 if( needs_NGRAM1 )
  {
   lem::ElapsedTime et;
   et.start();

   db->CreateIndeces1( suffix, 1 );
  }

 return;
}



void RawNGramsCollector::CreateIndeces2( bool echo )
{
 if( !needs_index_creation2 )
  return;
 
 needs_index_creation2 = false;

 int i=0;

 if( needs_NGRAM2 )
  {
   lem::ElapsedTime et;
   et.start();

   db->CreateIndeces1( suffix, 2 );
  }

 return;
}

void RawNGramsCollector::CreateIndeces3( bool echo )
{
 if( !needs_index_creation3 )
  return;
 
 needs_index_creation3 = false;

 int i=0;

 if( needs_NGRAM3 )
  {
   lem::ElapsedTime et;
   et.start();

   db->CreateIndeces1( suffix, 3 );
  }

 return;
}





void RawNGramsCollector::CreateIndeces4( bool echo )
{
 if( !needs_index_creation4 )
  return;
 
 needs_index_creation4 = false;

 int i=0;

 if( needs_NGRAM4 )
  {
   lem::ElapsedTime et;
   et.start();

   db->CreateIndeces1( suffix, 4 );
  }

 return;
}


void RawNGramsCollector::CreateIndeces5( bool echo )
{
 if( !needs_index_creation5 )
  return;
 
 needs_index_creation5 = false;

 int i=0;

 if( needs_NGRAM5 )
  {
   lem::ElapsedTime et;
   et.start();

   db->CreateIndeces1( suffix, 5 );
  }

 return;
}




void RawNGramsCollector::EndAll( bool echo )
{
 if(echo)
  lem::mout->printf( "%vf2All documents have been processed, flushing caches...%vn\n" );

 // Сбрасываем остатки данных в кэше.
 PurgeDocCache(echo);

 if( disk_cache2.NotNull() )
  {
   disk_cache2->echo=echo;
/*
   if( upload_to_db )
    {
     FString sql;
     sql = lem::format_str( "INSERT INTO NGRAM2%s( id, iword1, iword2, w ) ", suffix.c_str() );
     disk_cache2->Upload( *db, sql );
    }

   if( print_ngrams && print_file.NotNull() )
    {
     FString sql;
     sql = lem::format_str( "SELECT word FROM WORDS%s WHERE id=%%d", suffix.c_str() );
     disk_cache2->Print( *db, sql, print_format, *print_file );
    }
*/
   disk_cache2->Commit();
  }

 if( disk_cache3.NotNull() )
  {
   disk_cache3->echo=echo;
/*
   if( upload_to_db )
    {
     FString sql;
     sql = lem::format_str( "INSERT INTO NGRAM3%s( id, iword1, iword2, iword3, w ) ", suffix.c_str() );
     disk_cache3->Upload( *db, sql );
    }

   if( print_ngrams && print_file.NotNull() )
    {
     FString sql;
     sql = lem::format_str( "SELECT word FROM WORDS%s WHERE id=%%d", suffix.c_str() );
     disk_cache3->Print( *db, sql, print_format, *print_file );
    }
*/
   disk_cache3->Commit();
  }

 if( disk_cache4.NotNull() )
  {
   disk_cache4->echo=echo;
/*
   if( upload_to_db )
    {
     FString sql;
     sql = lem::format_str( "INSERT INTO NGRAM4%s( id, iword1, iword2, iword3, iword4, w ) ", suffix.c_str() );
     disk_cache4->Upload( *db, sql );
    }

   if( print_ngrams && print_file.NotNull() )
    {
     FString sql;
     sql = lem::format_str( "SELECT word FROM WORDS%s WHERE id=%%d", suffix.c_str() );
     disk_cache4->Print( *db, sql, print_format, *print_file );
    }
*/
   disk_cache4->Commit();
  }


 if( disk_cache5.NotNull() )
  {
   disk_cache5->echo=echo;
/*
   if( upload_to_db )
    {
     FString sql;
     sql = lem::format_str( "INSERT INTO NGRAM5%s( id, iword1, iword2, iword3, iword4, iword5, w ) ", suffix.c_str() );
     disk_cache5->Upload( *db, sql );
    }

   if( print_ngrams && print_file.NotNull() )
    {
     FString sql;
     sql = lem::format_str( "SELECT word FROM WORDS%s WHERE id=%%d", suffix.c_str() );
     disk_cache5->Print( *db, sql, print_format, *print_file );
    }
*/
   disk_cache5->Commit();
  }

 // Создадим индексы, так как возможно мы так и не создали их, работая
 // только в кэше.
 CreateIndeces(echo);

 db->CommitRetaining();

 return;
}

// ********************************************************
// Обновим статистику.
// ********************************************************
void RawNGramsCollector::ProcessFinalStat( bool echo )
{
 if( needs_NGRAM1 )
  {
   db->UpdateStatistics( suffix, 1 );
  }

 if( needs_NGRAM2 )
  {
   db->UpdateStatistics( suffix, 2 );
  }

 if( needs_NGRAM3 )
  {
   db->UpdateStatistics( suffix, 3 );
  }

 if( needs_NGRAM4 )
  {
   db->UpdateStatistics( suffix, 4 );
  }

 if( needs_NGRAM5 )
  {
   db->UpdateStatistics( suffix, 5 );
  }

 db->CommitRetaining();

 return;
}




void RawNGramsCollector::EraseFreq1(void)
{
 if( needs_NGRAM1 || needs_NGRAM2 || needs_NGRAM3 || needs_NGRAM4 || needs_NGRAM5 )
  {
   if( needs_NGRAM1 )
    {
     db->EraseFreq1(suffix,1);
    }

   if( needs_NGRAM2 )
    {
     db->EraseFreq1(suffix,2);
    }

   if( needs_NGRAM3 )
    {
     db->EraseFreq1(suffix,3);
    }

   if( needs_NGRAM4 )
    {
     db->EraseFreq1(suffix,4);
    }

   if( needs_NGRAM5 )
    {
     db->EraseFreq1(suffix,5);
    }

   db->CommitRetaining();
  }

 return;
}


int RawNGramsCollector::Find2Gram( int iword1, int iword2 )
{
 NGRAM2_CACHE::const_iterator it = ngram2_cache->find( std::make_pair(iword1,iword2) );
 if( it!=ngram2_cache->end() )
  {
   // Нашли в кэше
   return it->second;
  }
 else
  {
   NGRAM2_DOCCACHE::const_iterator it = ngram2_doccache->find( std::make_pair(iword1,iword2) );
   if( it!=ngram2_doccache->end() )
    {
     // Нашли во временном документом кэше
     return it->second.first;
    }
   else if( overload2 || !needs_NGRAM2 )
    {
     std::pair<int,int> id_w = db->Find2Gram(suffix,iword1,iword2);

     if( id_w.first!=-1 && id_w.second>1 && !needs_NGRAM2 && ngram2_cache_size<max_ngram2_cache )
      {
       // Запомним эту 2-грамму в кэше. Таким образом постепенно в кэш будут вытянуты самые частые
       // 2-граммы.
       ngram2_cache->insert( std::make_pair( std::make_pair(iword1,iword2), id_w.first ) );
       ngram2_cache_size++;
      }

     return id_w.first;
    }
  }

 LEM_STOPIT; 
 return UNKNOWN;
}


void RawNGramsCollector::StoreNGram( const UFString &a, const UFString &b, int freq )
{
 if( needs_NGRAM2 )
  {
   const int ie1 = NormalizeAndRegisterWord(a.c_str());
   const int ie2 = NormalizeAndRegisterWord(b.c_str());

   if( ie1!=UNKNOWN && ie2!=UNKNOWN )
    Store2Gram( ie1, ie2, freq );
  } 

 return;
}



void RawNGramsCollector::StoreNGram( const UFString &a, const UFString &b, const UFString &c, int freq )
{
 if( needs_NGRAM3 )
  {
   const int ie1 = NormalizeAndRegisterWord(a.c_str());
   const int ie2 = NormalizeAndRegisterWord(b.c_str());
   const int ie3 = NormalizeAndRegisterWord(c.c_str());

   if( ie1!=UNKNOWN && ie2!=UNKNOWN && ie3!=UNKNOWN )
    Store3Gram( ie1, ie2, ie3, freq );
  } 

 return;
}



void RawNGramsCollector::StoreNGram(
                                    const UFString &a,
                                    const UFString &b,
                                    const UFString &c,
                                    const UFString &d,
                                    int freq
                                   )
{
 if( needs_NGRAM4 )
  {
   const int ie1 = NormalizeAndRegisterWord(a.c_str());
   const int ie2 = NormalizeAndRegisterWord(b.c_str());
   const int ie3 = NormalizeAndRegisterWord(c.c_str());
   const int ie4 = NormalizeAndRegisterWord(d.c_str());

   if( ie1!=UNKNOWN && ie2!=UNKNOWN && ie3!=UNKNOWN && ie4!=UNKNOWN )
    Store4Gram( ie1, ie2, ie3, ie4, freq );
  } 

 return;
}



void RawNGramsCollector::StoreNGram(
                                    const UFString &a,
                                    const UFString &b,
                                    const UFString &c,
                                    const UFString &d,
                                    const UFString &e,
                                    int freq
                                   )
{
 if( needs_NGRAM5 )
  {
   const int ie1 = NormalizeAndRegisterWord(a.c_str());
   const int ie2 = NormalizeAndRegisterWord(b.c_str());
   const int ie3 = NormalizeAndRegisterWord(c.c_str());
   const int ie4 = NormalizeAndRegisterWord(d.c_str());
   const int ie5 = NormalizeAndRegisterWord(e.c_str());

   if( ie1!=UNKNOWN && ie2!=UNKNOWN && ie3!=UNKNOWN && ie4!=UNKNOWN && ie5!=UNKNOWN )
    Store5Gram( ie1, ie2, ie3, ie4, ie5, freq );
  } 

 return;
}


void RawNGramsCollector::InternalFlush( bool echo )
{
 // Документный кэш N-грамм переполнен?
 if(
    CastSizeToInt(ngram1_doccache->size())>=max_ngram1_doccache ||
    CastSizeToInt(ngram2_doccache->size())>=max_ngram2_doccache ||
    CastSizeToInt(ngram3_doccache->size())>=max_ngram3_doccache ||
    CastSizeToInt(ngram4_doccache->size())>=max_ngram4_doccache ||
    CastSizeToInt(ngram5_doccache->size())>=max_ngram5_doccache
   )
  {
   doc_count=0;
   PurgeDocCache(echo);
  }

 return;
}

void RawNGramsCollector::SetFilter( NGramFilter *_filter )
{
 filter = _filter;
 filter->AttachCollector(this);
 return;
}

#endif
