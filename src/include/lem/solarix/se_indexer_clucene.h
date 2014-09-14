#ifndef IDX_INDEXER_CLUCENE__H
#define IDX_INDEXER_CLUCENE__H
#pragma once

 #if defined FAIND_INDEXER_CLUCENE

 #include <lem/solarix/se_text.h>
 #include <CLucene/CLucene.h>
 #include <lem/sqlite/sqlite3.h> 
 #include <lem/solarix/se_crawler_operation.h>
 #include <lem/solarix/se_indexer_active_reader.h>

 namespace lucene
 {
  namespace index
  {
   class IndexWriter;
  }

  namespace analysis
  { 
   namespace standard
   {
    class StandardAnalyzer;
   }
  } 
 }


 namespace Solarix
 {
//  class LD_Seeker;

  namespace Search_Engine
  {
  
   class DocumentIteratorCLucene : public DocumentIterator
   {
    private:
     std::auto_ptr<Assoc_Files> files;

    public:
     DocumentIteratorCLucene( Assoc_Files *_files ) : files(_files) {}
     virtual ~DocumentIteratorCLucene(void) {}

     virtual int Size(void) const;
     virtual int GetDocId( int i ) const;
   };
  
  
   class IndexReaderCLucene : public IndexActiveReader
   {
    private:
     lucene::search::IndexSearcher* reader;
     int64_t reader_version; // для синхронизации с файлами хранилища
     lucene::analysis::standard::StandardAnalyzer *analyzer;
     Storage storage;                // все файлы хранилища
     struct sqlite3* hdb; // дескриптор БД индекса

     virtual Assoc_Files* GetAssocFilesForPhrase( const lem::UFString &phrase, int distance, int maxhitcount, const Pattern &pattern );
     virtual Assoc_Files* GetAssocFiles( const UCString &word, bool Prefix, int maxhitcount, const Pattern &pattern ); // поиск по одному слову
     virtual Assoc_Files* GetAssocFiles( const MCollect<UCString> &words, int maxhitcount, const Pattern &pattern ); // поиск по альтернативным словам (OR)

    public:
     IndexReaderCLucene(
                        IndexManager *Manager,
                        const Domain_Info &Domain_info,
                        Solarix::Dictionary *ptrDict,
                        const LD_Seeker *seeker,
                        const Echo_Options *Echo,
                        const General_Options *Generals
                       );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void ReopenIfNeeded(void);

     virtual void Commit(void);

     virtual ~IndexReaderCLucene(void);

     virtual Zone_Statistics GetZoneStat(void);
     virtual int CountDocuments(void);
     virtual void LoadDocuments(void);
     virtual boost::shared_ptr<File_Entry> GetDocumentByIndex( int idoc );
     virtual boost::shared_ptr<File_Entry> GetDocumentById( int id_doc );
     virtual Assoc_Files* GetAllFiles(void);
     virtual FString GetEngineName(void) const;
     virtual void PrintInfo( OFormatter &out, bool detailed=false );
   };


   // **********************************************************************
   // Индексатор на движке CLucene для первоначального заполнения индекса.
   // **********************************************************************
   class IndexWriterCLucene : public Indexer
   {
    private:
     lucene::index::IndexWriter* writer;
     lucene::analysis::standard::StandardAnalyzer *an;
     Storage storage;                // все файлы хранилища
     struct sqlite3* hdb; // дескриптор БД индекса

     int document_counter; // счетчик проиндексированных документов.

    public:
     IndexWriterCLucene(
                        IndexManager *Manager,
                        const Domain_Info &Domain_info,
                        Solarix::Dictionary *ptrDict,
                        const LD_Seeker *seeker,
                        const Echo_Options *Echo,
                        const General_Options *Generals
                       );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void Commit(void);

     virtual ~IndexWriterCLucene(void);

     virtual void AddDocument( const File_Location &filename, Base_File_Reader *reader );

     virtual bool DoesSupportMorphology(void) const;
   };


   class IndexUpdaterCLucene : public Indexer
   {
    private:
     lem::zbool optimize_on_commit;
     lucene::index::IndexWriter* writer;
     lucene::analysis::standard::StandardAnalyzer *an;
     Storage storage;                // все файлы хранилища
     struct sqlite3* hdb; // дескриптор БД индекса

     lem::Collect<lem::Path> deleted_files; // файлы, которые надо удалить из индекса

     int document_counter; // счетчик проиндексированных документов.

    public:
     IndexUpdaterCLucene(
                         IndexManager *Manager,
                         const Domain_Info &Domain_info,
                         Solarix::Dictionary *ptrDict,
                         const LD_Seeker *seeker,
                         const Echo_Options *Echo,
                         const General_Options *Generals
                        );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void Commit(void);

     virtual ~IndexUpdaterCLucene(void);

     virtual bool IsFileChanged( const File_Location &filename );
     virtual void AddDocument( const File_Location &filename, Base_File_Reader *reader );
     virtual bool DoesSupportMorphology(void) const;
   };


class SolarixReader : public lucene::util::Reader
{
 public: 
  Solarix::Search_Engine::Base_File_Reader *reader;

 public:
  SolarixReader ( Solarix::Search_Engine::Base_File_Reader *r ) { reader=r; }
  ~SolarixReader() { reader=NULL; }

  lem::int64_t available() { return 0; }
  void seek( lem::int64_t position) {}
  lem::int64_t position() { return 0; }
  void close() { reader=NULL; }
  TCHAR readChar(void) { return 0; }
  lem::int32_t read( TCHAR* b, const lem::int64_t start, const lem::int32_t length ) { return 0; }
  TCHAR peek() { return 0; }
};

class SolarixAnalyzer : public lucene::analysis::standard::StandardAnalyzer 
{
 public:
  lem::CPtr<const Solarix::Search_Engine::Lexer_Options> lexer_options;
  const Solarix::LD_Seeker *seeker;
  Solarix::SynGram *sg;
  Solarix::Search_Engine::Morphology morphology;

 public:
  SolarixAnalyzer(void);

  ~SolarixAnalyzer() {}

  lucene::analysis::TokenStream* tokenStream( const TCHAR* fieldName, CL_NS(util)::Reader* reader );
};

// ********************************************
// Removes stop words from a token stream.
// ********************************************
class SolarixFilter: public lucene::analysis::TokenFilter
{
 private:
  lem::CPtr<const Solarix::Search_Engine::Lexer_Options> lexer_options;
  const Solarix::LD_Seeker *seeker;
  Solarix::SynGram *sg;
  Base_File_Reader *reader;
  Solarix::Search_Engine::Morphology morphology;
  lem::zbool dynforms;
  Solarix::Search_Engine::File_Lexem lex;

 public:
  SolarixFilter(
                lucene::analysis::TokenStream* in,
                bool deleteTokenStream,
                Base_File_Reader *sreader,  
                lem::CPtr<const Solarix::Search_Engine::Lexer_Options> _lexer_options,
                const Solarix::LD_Seeker *Seeker,
                Solarix::SynGram *SG,
                Solarix::Search_Engine::Morphology _morphology
               );

  bool next( lucene::analysis::Token* token );
};


class SolarixFilter2: public lucene::analysis::TokenFilter
{
 private:
  lem::CPtr<const Solarix::Search_Engine::Lexer_Options> lexer_options;
  const Solarix::LD_Seeker *seeker;
  const Solarix::SynGram *sg;
  Solarix::Search_Engine::Morphology morphology;
  lem::zbool dynforms;
  Solarix::Search_Engine::File_Lexem lex;

 public:
  SolarixFilter2(
                 lucene::analysis::TokenStream* in,
                 bool deleteTokenStream,
                 lem::CPtr<const Solarix::Search_Engine::Lexer_Options> _lexer_options,
                 const Solarix::LD_Seeker *Seeker,
                 const Solarix::SynGram *SG,
                 Solarix::Search_Engine::Morphology _morphology
                );

  bool next( lucene::analysis::Token* token );
};

   extern void encode_sqlite_path( UFString &s );
   extern void decode_sqlite_path( UFString &s );
  }
 }


#endif

#endif
