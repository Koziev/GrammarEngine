#include <lem/smart_pointers.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/ParadigmaMatcher.h>
#include <lem/solarix/ParadigmaFinder.h>

using namespace Solarix;

ParadigmaFinder::ParadigmaFinder( LexiconStorage *_storage )
{
 loaded = false;
 storage = _storage;
 return;
}


ParadigmaFinder::~ParadigmaFinder(void)
{
 for( CLASS2DECL::iterator it=class2decl.begin(); it!=class2decl.end(); ++it )
  {
   delete it->second;
  }

 return;
}



void ParadigmaFinder::Add( const ParadigmaMatcher &matcher, int PartOfSpeech, int id )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 lem::Process::RWU_WriterGuard wlock(rlock);
 #endif

 if( !loaded )
  LoadFromDB();

 ParadigmaMatcher * m = new ParadigmaMatcher(matcher);
 matchers.push_back( m );
 ids.push_back(id);
 id_class.push_back(PartOfSpeech);

 CLASS2DECL::iterator it=class2decl.find(PartOfSpeech);
 if( it==class2decl.end() )
  {
   lem::MCollect< std::pair< int, const ParadigmaMatcher*> > * mx = new lem::MCollect< std::pair< int, const ParadigmaMatcher*> >();
   mx->push_back( std::make_pair(id,m) );
   class2decl.insert( std::make_pair( PartOfSpeech, mx ) );
  }
 else
  {
   it->second->push_back( std::make_pair(id,m) );
  }

 return;
}



// *************************************************************************************
// Ищем парадигмы, чьи условия подходят для указанной базовой формы, возвращает
// список id таких парадигм.
// *************************************************************************************
void ParadigmaFinder::Find( int PartOfSpeech, const lem::UCString &entry_name, lem::MCollect<int> &found_ids )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 if( !loaded )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif
   LoadFromDB();
  }

 if( PartOfSpeech==UNKNOWN || PartOfSpeech==ANY_STATE )
  {
   for( lem::Container::size_type i=0; i<matchers.size(); ++i )
    if( matchers[i]->Match(entry_name) )
     {
      found_ids.push_back(ids[i]);
     }
  }
 else
  {
   CLASS2DECL::const_iterator it=class2decl.find(PartOfSpeech);
   if( it!=class2decl.end() )
    {
     for( lem::Container::size_type i=0; i<it->second->size(); ++i )
      if( it->second->get(i).second->Match(entry_name) )
       {
        found_ids.push_back( it->second->get(i).first );
       }
    }
  }
 
 return;
}


void ParadigmaFinder::LoadFromDB(void)
{
 // загружаем список условий для автопарадигм из БД

 lem::Ptr<LS_ResultSet> enu( storage->ListParadigmaMatchers() );
 while( enu->Fetch() )
  {
   const int id = enu->GetInt(0);
   lem::UFString str = enu->GetUFString(1);
   const int pos = enu->GetInt(2);
   ParadigmaMatcher *matcher = new ParadigmaMatcher(str);
   matchers.push_back(matcher);
   ids.push_back(id);
   id_class.push_back(pos);

   CLASS2DECL::iterator it=class2decl.find(pos);
   if( it==class2decl.end() )
    {
     lem::MCollect< std::pair<int,const ParadigmaMatcher*> > * mx = new lem::MCollect< std::pair<int,const ParadigmaMatcher*> >();
     mx->push_back( std::make_pair(id,matcher) );
     class2decl.insert( std::make_pair( pos, mx ) );
    }
   else
    {
     it->second->push_back( std::make_pair(id,matcher) );
    }
  }

 loaded = true;

 return;
}
