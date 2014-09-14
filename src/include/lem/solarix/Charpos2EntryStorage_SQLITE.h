#if !defined Charpos2EntryStorage_SQLITE__H
 #define Charpos2EntryStorage_SQLITE__H

 #include <lem/sqlite.h>
 #include <lem/solarix/Charpos2EntryStorage.h>
 

 namespace Solarix
 {
  class Charpos2EntryStorage_SQLITE : public Charpos2EntryStorage
  {
   private:
    lem::UFString sqlite_connection_string;
    struct sqlite3* hdb;

   public:
    Charpos2EntryStorage_SQLITE( const lem::UFString &connection_string );
    virtual ~Charpos2EntryStorage_SQLITE(void);
 
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
