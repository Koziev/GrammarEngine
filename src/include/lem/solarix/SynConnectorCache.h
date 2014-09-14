#if !defined SynConnectorCache__H
#define SynConnectorCache__H

#include <lem/noncopyable.h>
#include <lem/RWULock.h>
#include <lem/containers.h>

namespace Solarix
{
 class LexiconStorage;
 class SynConnector;
 class Connectors4Language;

 class SynConnectorCache : lem::NonCopyable
 {
  private:
   lem::MCollect< SynConnector* > rules;
   std::map<int,const SynConnector*> id2rule;

   std::set<int> ekey_no_connectors;
   std::multimap<int,int> ekey2connector;

   Dictionary *dict;
   LexiconStorage *storage;

   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs, cs2;
   #endif   

   const SynConnector* GetConnector( int id );

  public:
   SynConnectorCache( Dictionary *_dict );
   ~SynConnectorCache();

   void Connect( LexiconStorage *stg );

   void GetConnectors( int id_entry, lem::MCollect<const SynConnector*> & connectors );
 };
}

#endif
