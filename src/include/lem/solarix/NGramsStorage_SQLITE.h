#if !defined(NGRAMS_STORAGE_SQLITE__H) && !defined( SOL_NO_NGRAMS)
#define NGRAMS_STORAGE_SQLITE__H
#pragma once

 #include <lem/path.h>
 #include <lem/containers.h>
 #include <lem/sqlite_helpers.h>
 #include <lem/solarix/ngrams_dbms.h>

 namespace Solarix
 {
  class LS_ResultSet;

  class NGramsStorage_SQLITE : public NGramsDBMS
  {
   private:
    int open_tx;
    struct sqlite3* hdb;

   public:
    NGramsStorage_SQLITE(void);
    virtual ~NGramsStorage_SQLITE(void);

    virtual NGramsDBMS* CreateDisconnectedClone() const;
    virtual bool IsRemote(void) const;

    virtual int MaxBulkInsert(void) const;

    virtual void Connect( const lem::Path &connection_string );

    virtual void Disconnect(void);

    virtual bool Connected(void) const;
    virtual void BeginTx(void);
    virtual void BeginReadTx(void);
    virtual void CommitTx(void);
    virtual void CommitReadTx(void);
    virtual void CommitRetaining(void);

    virtual void ExecuteSql( const char *sql, bool check=true );
    virtual void ExecuteSql( const lem::FString &sql, bool check=true );
    virtual bool TableExists( const lem::FString &table );
    virtual bool IndexExists( const lem::FString &idx, const lem::FString &table_name );
    virtual void DropIndex( const lem::FString &idx, const lem::FString &table_name  );
    virtual void SetDBCache( int cache_size );
    virtual void CommitCreatedIndeces(void);

    virtual int SelectInt( const lem::FString &Select, int def=-1 );
    virtual int SelectInt( const char *Select, int def=-1 );
    virtual std::pair<int,int> SelectIntPair( const lem::FString &Select );
    virtual void SelectInts( const lem::FString &Select, lem::MCollect<int> &list );
    virtual void SelectFStrings( const lem::FString &Select, lem::Collect<lem::FString> &list );

    virtual lem::UFString SelectStr( const char *Select );

    virtual LS_ResultSet* Select( const lem::FString &sql );

    virtual void CreateTable_Words( const lem::FString &suffix );
    virtual void CreateTable_NGrams1( const lem::FString &suffix );
    virtual void CreateTable_NGrams2( const lem::FString &suffix );
    virtual void CreateTable_NGrams3( const lem::FString &suffix );
    virtual void CreateTable_NGrams4( const lem::FString &suffix );
    virtual void CreateTable_NGrams5( const lem::FString &suffix );
    virtual void CreateTable_Segments(void);

    virtual lem::FString StartBulkInsert( const lem::FString &suffix, int order );

    virtual lem::FString AppendBulkInsert(
                                          const lem::FString &suffix,
                                          int counter,
                                          int id,
                                          int id_word1,
                                          int w
                                         );

    virtual lem::FString AppendBulkInsert(
                                          const lem::FString &suffix,
                                          int counter,
                                          int id,
                                          int id_word1,
                                          int id_word2,
                                          int w
                                         );

    virtual lem::FString AppendBulkInsert(
                                          const lem::FString &suffix,
                                          int counter,
                                          int id,
                                          int id_word1,
                                          int id_word2,
                                          int id_word3,
                                          int w
                                         );

    virtual lem::FString AppendBulkInsert(
                                          const lem::FString &suffix,
                                          int counter,
                                          int id,
                                          int id_word1,
                                          int id_word2,
                                          int id_word3,
                                          int id_word4,
                                          int w
                                         );

    virtual lem::FString AppendBulkInsert(
                                          const lem::FString &suffix,
                                          int counter,
                                          int id,
                                          int id_word1,
                                          int id_word2,
                                          int id_word3,
                                          int id_word4,
                                          int id_word5,
                                          int w
                                         );

    virtual void UpdateNGrams(
                              const lem::FString &suffix,
                              int order, 
                              const lem::MCollect< std::pair<int,int> > & list
                             );

   };
 }

#endif
