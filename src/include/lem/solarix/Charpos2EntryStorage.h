#if !defined Charpos2EntryStorage__H
 #define Charpos2EntryStorage__H

 #include <set>
 #include <lem/containers.h>

 namespace Solarix
 {
  class Charpos2EntryEnumerator;
  class Charpos2EntryStorage
  {
   protected:
    Charpos2EntryStorage(void) {}

   public:
    virtual ~Charpos2EntryStorage(void) {}
 
    virtual void ClearCharpos( lem::uint32_t c, int pos )=0;
    virtual void BeginTx(void)=0;
    virtual void CommitTx(void)=0;
    virtual void Store( lem::uint32_t c, int pos, const std::set<int> &ies )=0;
    virtual void Get( lem::uint32_t c, int pos, std::set<int> &ies )=0;
    virtual void GetIntersected( lem::uint32_t c, int pos, const std::set<int> &ies0, std::set<int> &ies )=0;
    virtual Charpos2EntryEnumerator* Enumerate(void)=0;
  };
 }

#endif
