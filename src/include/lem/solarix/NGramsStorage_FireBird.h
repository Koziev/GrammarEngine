#if !defined(NGRAMS_STORAGE_FIREBIRD__H) && defined(SOL_FIREBIRD_NGRAMS)
#define NGRAMS_STORAGE_FIREBIRD__H
#pragma once

 #include <lem/path.h>
 #include <lem/containers.h>
 #include <firebird/ibase.h>
 #include <lem/ngrams_dbms.h>

 namespace Solarix
 {
  template< int len >
  struct varchar
  {
   short length;
   char string[len*6+1];

   varchar(void) { length=0; *string=0; }

   void clear(void) { length=0; *string=0; }  
  };

  typedef char sqlchar[710]; // fix me... FireBird client return incorrect return for utf-8 'char' fields

  extern void RTrim( char *word, int len );

  class NGramsStorage_FireBird : public NGramsDBMS
  {
   public:
    isc_db_handle hdb;
    isc_tr_handle htx;
    ISC_STATUS_ARRAY status;

    enum { max_bulk_insert=100 };

    NGramsStorage_FireBird(void);
    virtual ~NGramsStorage_FireBird(void);

    virtual void Connect( const lem::Path &dbfile );
    virtual void Disconnect(void);

    virtual bool IsRemote(void) const;
    virtual int MaxBulkInsert(void) const;

    virtual bool Connected(void) const;
    virtual void BeginTx(void);
    virtual void BeginReadTx(void);
    virtual void Commit(void);
    virtual void CommitRetaining(void);

    virtual void ExecuteSql( const char *sql, bool check=true );
    virtual void ExecuteSql( const lem::FString &sql, bool check=true );
    virtual bool TableExists( const lem::FString &table );
    virtual bool IndexExists( const lem::FString &idx );
    virtual void DropIndex( const lem::FString &idx );
    virtual void SetDBCache( int cache_size );
    virtual void CommitCreatedIndeces(void);

    virtual int SelectInt( const lem::FString &Select, int def=-1 );
    virtual int SelectInt( const char *Select, int def=-1 );
    virtual std::pair<int,int> SelectIntPair( const lem::FString &Select );
    virtual void SelectInts( const lem::FString &Select, lem::MCollect<int> &list );

    virtual lem::UFString SelectStr( const char *Select );

    virtual LS_ResultSet* Select( const lem::FString &sql );
    virtual void CreateTable_Words( const lem::FString &suffix );
    virtual void CreateTable_NGrams1( const lem::FString &suffix );
    virtual void CreateTable_NGrams2( const lem::FString &suffix );
    virtual void CreateTable_NGrams3( const lem::FString &suffix );
    virtual void CreateTable_NGrams4( const lem::FString &suffix );
    virtual void CreateTable_NGrams5( const lem::FString &suffix );

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

#endif
