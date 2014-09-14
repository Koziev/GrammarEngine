#if !defined Charpos2EntryStorage_MySQL__H
 #define Charpos2EntryStorage_MySQL__H

 #include <lem/sqlite.h>
 #include <lem/solarix/Charpos2EntryStorage.h>
 

 namespace Solarix
 {
  class StorageConnection_MySQL;
  class Charpos2EntryStorage_MySQL : public Charpos2EntryStorage
  {
   private:
    StorageConnection_MySQL *cnx;

   public:
    Charpos2EntryStorage_MySQL( StorageConnection_MySQL *_cnx );
    virtual ~Charpos2EntryStorage_MySQL(void);
 
    virtual void BeginTx(void);
    virtual void CommitTx(void);
    virtual void ClearCharpos( lem::uint32_t c, int pos );
    virtual void Store( lem::uint32_t c, int pos, const std::set<int> &ies );
    virtual void Get( lem::uint32_t c, int pos, std::set<int> &ies );
    virtual void GetIntersected( lem::uint32_t c, int pos, const std::set<int> &ies0, std::set<int> &ies );
    virtual Charpos2EntryEnumerator* Enumerate(void);
  };
 }

#endif
