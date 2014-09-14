#if !defined WordSetItem__H
 #define WordSetItem__H

 #include <lem/noncopyable.h>
 #include <set>
 #include <lem/ucstring.h>
 #include <lem/quantors.h>

 namespace Solarix
 {
  struct WordSetItem : lem::NonCopyable
  {
   int id;
   bool case_sensitive;
   std::set<lem::UCString> words;
   lem::UCString name;

   WordSetItem(void) : id(UNKNOWN), case_sensitive(false) {}

   int GetId(void) const { return id; }
   const lem::UCString& GetName(void) const { return name; }
   bool Contains( const lem::UCString &word ) const
   {
    if( case_sensitive )
     return words.find(word)!=words.end();
    else
     return words.find( lem::to_upper(word) )!=words.end();
   }

   bool Empty(void) const { return words.empty(); }
   void InsertWord( const lem::UCString &word ) { words.insert(word); }
   const std::set<lem::UCString>& GetWords() const { return words; }
  };

 }

#endif
