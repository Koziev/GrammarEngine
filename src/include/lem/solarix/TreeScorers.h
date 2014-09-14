#if !defined TREE_SCORERS__H
#define TREE_SCORERS__H

#include <map>
#include <lem/ucstring.h>
#include <lem/noncopyable.h>

namespace lem
{
 namespace Iridium
 {
  class Macro_Parser;
 }
}


namespace Solarix
{
 class LexiconStorage;
 class Dictionary;
 struct TreeScorerGroupParams;

 class TreeScorers : lem::NonCopyable
 {
  private:
   LexiconStorage * storage;

   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs_names;
   #endif
   std::map<lem::UCString,int> name2id;

   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs_params;
   #endif
   lem::MCollect<TreeScorerGroupParams*> params;
   std::map<int,const TreeScorerGroupParams*> id2params;

   void Clear();

  public:
   TreeScorers();
   ~TreeScorers();

   void Connect( LexiconStorage * _storage );

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadGroup( Dictionary & dict, lem::Iridium::Macro_Parser &txtfile );
   #endif

   int FindGroup( const lem::UCString & name, bool load_from_db );

   const TreeScorerGroupParams& GetGroupParams( int id );
 };
}

#endif
