#if !defined StorageConnection_FireBird__H && defined SOL_FIREBIRD_DICTIONARY_STORAGE
 #define StorageConnection_FireBird__H

 #include <lem/config.h>
 
 #if defined LEM_WINDOWS
  #include <windows.h>
 #endif

 #include <firebird/ibase.h>
 #include <lem/solarix/StorageConnection.h>

 namespace lem
 {
  class FString;
 }

 namespace Solarix
 {
  #if defined SOL_FIREBIRD_NGRAMS
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
  #endif

  class StorageConnection_FireBird : public StorageConnection
  {
   public:
    isc_db_handle hdb;
    isc_tr_handle htx;
    ISC_STATUS_ARRAY status;

   public:
    StorageConnection_FireBird(
                               const lem::FString &login,
                               const lem::FString &psw,
                               const lem::FString &db
                              );

    virtual ~StorageConnection_FireBird(void);
    virtual TransactionGuard* GetTx(void);

    virtual bool IsConnected(void) const;

    void BeginTx(void);
    void CommitTx(void);
    void CommitRetainingTx(void);
    void RollbackTx(void);  
    void Error( const lem::FString &sql );
    void Execute( const lem::FString &sql );
  };
 }

#endif
