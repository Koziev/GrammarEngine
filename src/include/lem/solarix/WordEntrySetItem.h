#if !defined WordEntrySetItem__H
 #define WordEntrySetItem__H

 #include <set>
 #include <lem/noncopyable.h>
 #include <lem/ucstring.h>
 #include <lem/quantors.h>

 namespace Solarix
 {
  struct WordEntrySetItem : lem::NonCopyable
  {
   int id;
   std::set<int> ies;
   lem::UCString name;

   WordEntrySetItem(void) : id(UNKNOWN) {}

   int GetId(void) const { return id; }
   const lem::UCString& GetName(void) const { return name; }
   bool Contains( int ekey ) const { return ies.find(ekey)!=ies.end(); }
   bool Empty(void) const { return ies.empty(); }
   void InsertEntryKey( int ekey ) { ies.insert(ekey); }

   const std::set<int>& GetIDs() const { return ies; }
  };

 }

#endif
