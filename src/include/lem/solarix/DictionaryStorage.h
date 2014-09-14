#if !defined DictionaryStorage__H
 #define DictionaryStorage__H

 #include <lem/noncopyable.h>

 namespace Solarix
 {
  class TransactionGuard;

  class DictionaryStorage : lem::NonCopyable
  {
   protected:
    DictionaryStorage(void) {}

   public:
    virtual ~DictionaryStorage(void) {}

    virtual void CreateSchema(void)=0;
    virtual void CopyDatabase( const lem::Path & db_path )=0;

    virtual TransactionGuard* GetTxGuard(void)=0;

    virtual void BeginTx(void)=0;
    virtual void CommitTx(void)=0;
    virtual void RollBackTx(void)=0;
  };

 }

#endif
