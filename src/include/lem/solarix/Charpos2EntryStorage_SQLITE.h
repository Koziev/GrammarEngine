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
    virtual ~Charpos2EntryStorage_SQLITE();
 
    virtual void BeginTx() override;
    virtual void CommitTx() override;
    virtual void ClearCharpos( lem::uint32_t c, int pos ) override;
    virtual void Store( lem::uint32_t c, int pos, const std::set<int> &ies ) override;
    virtual void Get( lem::uint32_t c, int pos, std::set<int> &ies ) override;
    virtual void GetIntersected( lem::uint32_t c, int pos, const std::set<int> &ies0, std::set<int> &ies ) override;
    virtual Charpos2EntryEnumerator* Enumerate() override;
  };
 }

#endif
