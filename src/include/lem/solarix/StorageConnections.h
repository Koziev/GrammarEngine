#if !defined StorageConnections__H
 #define StorageConnections__H

 #include <lem/process.h>
 #include <lem/ufstring.h>
 #include <lem/ptr_container.h>
 #include <map>
 #include <lem/solarix/StorageConnection.h>

 namespace Solarix
 {
  class StorageConnections
  {
   private:
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif
   
    lem::PtrCollect<Solarix::StorageConnection> cnx;
    lem::Collect<lem::UFString> cnx_provider;
    lem::Collect<lem::UFString> cnx_string;

   protected:
    virtual StorageConnection* CreateConnection( const lem::UFString &provider, const lem::UFString &connection_string );

   public:
    StorageConnections(void);
    virtual ~StorageConnections(void);

    virtual StorageConnection* Connect( const lem::UFString &provider, const lem::UFString &connection_string );
    virtual void Disconnect( StorageConnection* cnx );

    virtual void Ping(void);
  };
 }

#endif
