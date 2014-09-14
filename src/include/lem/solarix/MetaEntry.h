#if !defined SOL_META_ENTRY__H
#define SOL_META_ENTRY__H

#include <lem/noncopyable.h>
#include <lem/containers.h>

namespace lem
{
 namespace Iridium
 {
  class Macro_Parser;
 }
}

namespace Solarix
{
 class SynGram;
 class LexiconStorage;
 class SQL_Production;

 class MetaEntry : lem::NonCopyable
 {
  private:
   int id;
   int id_class;
   lem::UCString name;
   lem::MCollect<int> entries;

  public:
   MetaEntry();
   MetaEntry( int _id, int _id_class, const lem::UCString &_name, lem::MCollect<int> & _entries );

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt( SynGram & sg, lem::Iridium::Macro_Parser & txtfile );
   #endif

   #if defined SOL_REPORT
   void SaveSQL( int * metaentry_item_id, lem::OFormatter & out, const SQL_Production &sql_version ) const;
   #endif

   void Store( LexiconStorage * storage ) const;

 };

}

#endif
