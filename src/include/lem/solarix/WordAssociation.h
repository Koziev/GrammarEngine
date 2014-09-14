#if !defined WordAssociation__H
#define WordAssociation__H

#include <lem/noncopyable.h>
#include <lem/ucstring.h>
#include <lem/quantors.h>

namespace lem
{
 class OFormatter;

 namespace Iridium
 {
  class Macro_Parser;
 }
}

namespace Solarix
{
 class WordEntrySet;
 class Dictionary;
 class SQL_Production;
 class LexiconStorage;
 class Word_Form;

 class WordAssociation : lem::NonCopyable
 {
  private:
   int id;

   int id_entry;

   int id_entry1, id_metaentry1;
   lem::UCString word1;

   int id_entry2, id_metaentry2;
   lem::UCString word2;

   int ThesaurusCheck_Link;
   int ThesaurusCheck_Entry;

   int set_type; // 0 - wordentry_set, 1 - word_set
   lem::UCString set_name;

   int score;
   int src_location;
   
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadWordEntryPoint( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, int id_language, int * entry, int * metaentry );
   #endif

  public:
   WordAssociation();

   WordAssociation(
                   int id,
                   int id_src,
                   int id_entry,
                   int id_entry1, const lem::UCString & word1, int id_metaentry1,
                   int id_entry2, const lem::UCString & word2, int id_metaentry2,
                   int link_type, int link_entry,
                   const lem::UCString & set_name,
                   int set_type,
                   int score
                  );
   
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, WordEntrySet & sets );
   #endif

   void Save( LexiconStorage & storage );

   bool IsSingleLemma() const { return id_entry1!=UNKNOWN && id_entry2==UNKNOWN && word2.empty(); }
   bool IsSingleMetaEntry() const { return id_metaentry1!=UNKNOWN && id_entry2==UNKNOWN && word2.empty(); }
   bool IsSingleLexem() const { return !word1.empty() && id_entry2==UNKNOWN && word2.empty(); }
   bool IsThesaurusLink() const { return ThesaurusCheck_Link!=UNKNOWN; }
   bool IsWordentrySet() const { return set_type==0; }
   bool IsWordSet() const { return set_type==1; }

   int GetSourceLocation() const { return src_location; }

   #if defined SOL_CAA
   bool Match( const Word_Form & wordform, Dictionary & dict ) const;
   #endif

   #if defined SOL_REPORT
   void SaveSQL( lem::OFormatter &out, const SQL_Production &sql_version ) const;
   #endif

   int GetScore() const { return score; }
 };

}


#endif
