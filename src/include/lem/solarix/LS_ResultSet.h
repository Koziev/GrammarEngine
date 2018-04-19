#if !defined LS_ResultSet__H
 #define LS_ResultSet__H

 #include <lem/ucstring.h>
 #include <lem/noncopyable.h>
 #include <lem/solarix/TransactionGuard.h>
 #include <memory>

 namespace Solarix
 {
  class LS_ResultSet : lem::NonCopyable
  {
   protected:
    std::unique_ptr<TransactionGuard> read_tx;

   public:
    LS_ResultSet( TransactionGuard *tx ) : read_tx(tx) {}
    virtual ~LS_ResultSet(void) {}
    virtual bool Fetch(void)=0;
    virtual int GetInt( int FieldIndex )=0;
    virtual lem::UCString GetUCString( int FieldIndex )=0;
    virtual lem::UFString GetUFString( int FieldIndex )=0;
    virtual lem::FString GetFString( int FieldIndex )=0;
  };

 }

#endif

