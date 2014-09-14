#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/KnowledgeBase.h>

using namespace Solarix;

KnowledgeBase::KnowledgeBase( Solarix::Dictionary *Dict )
 : dict(Dict), storage(NULL)
{
 LEM_CHECKIT_Z( Dict!=NULL );
}


KnowledgeBase::~KnowledgeBase(void)
{
}


void KnowledgeBase::Connect( LexiconStorage *stg )
{
 LEM_CHECKIT_Z( stg!=NULL );

 fact_groups.clear();
 name2facts.clear(); 
 id2facts.clear();

 #if defined SOL_CAA
 cached_facts.clear();
 id2cached_facts.clear();
 #endif

 storage = stg;

 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
int KnowledgeBase::FindFacts( const lem::UCString & name ) const
{
 LEM_CHECKIT_Z( !name.empty() );

 std::map<lem::UCString,int>::const_iterator it = name2facts.find( lem::to_upper(name) );
 return it==name2facts.end() ? UNKNOWN : it->second;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void KnowledgeBase::LoadFactsTxt( Macro_Parser &txtfile )
{
 lem::Iridium::BSourceState tbeg = txtfile.tellp();

 KB_Facts * x = new KB_Facts();
 x->LoadTxt( *dict, txtfile );

 lem::UCString uname( x->GetName() );
 uname.to_upper();

 std::map<lem::UCString,int>::const_iterator it = name2facts.find(uname);
 if( it!=name2facts.end() )
  {
   lem::Iridium::Print_Error( tbeg, txtfile );
   dict->GetIO().merr().printf( "Fact group [%us] redefinition\n", x->GetName().c_str() );
   throw E_ParserError();
  }

 fact_groups.push_back( x );
 const int id = storage->StoreFacts( x );
 x->SetId(id);

 name2facts.insert( std::make_pair(uname,id) );
 id2facts.insert( std::make_pair(id,x) );

 return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void KnowledgeBase::LoadFactTxt( Macro_Parser &txtfile )
{
 lem::Iridium::BSourceState tbeg = txtfile.tellp();

 KB_Fact * x = new KB_Fact();
 x->LoadTxt( *this, *dict, txtfile );

 KB_Facts & group = * id2facts.find(x->GetGroupId())->second;

 group.UpdateQueryMode( *x );

 storage->StoreFact(group,x);


 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
const KB_Facts& KnowledgeBase::GetFacts( int id ) const
{
 return * (id2facts.find(id)->second);
}
#endif




#if defined SOL_LOADTXT && defined SOL_COMPILER
void KnowledgeBase::AllFactsCompiled(void)
{
 for( lem::Container::size_type i=0; i<fact_groups.size(); ++i )
  {
   storage->UpdateFactsQueryMode( fact_groups[i] );
  }

 return;
}
#endif


#if defined SOL_CAA
const KB_Facts& KnowledgeBase::LoadFacts( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(facts_cs);
 #endif

 std::map< int /*id*/, KB_Facts* >::const_iterator it = id2facts.find( id );

 if( it==id2facts.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif
 
   it = id2facts.find( id );
   if( it==id2facts.end() )
    {
     KB_Facts *x = storage->LoadFacts( id );
     fact_groups.push_back(x);
//     name2facts.insert( std::make_pair(uname,id) );
     id2facts.insert( std::make_pair(id,x) );
     return *x;
    }
   else
    {
     return * it->second;
    }
  }
 else
  {
   return * it->second;
  }
}
#endif

#if defined SOL_CAA
void KnowledgeBase::LoadSingleFact( int id_fact, KB_CachedFacts & cache )
{
 LEM_CHECKIT_Z( id_fact!=UNKNOWN );
 KB_Fact * fact = storage->LoadFact(id_fact);
 cache.AddFact(fact);
 return;
}
#endif

#if defined SOL_CAA
const KB_CachedFacts& KnowledgeBase::LoadAndCacheFacts( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cached_facts_cs);
 #endif

 std::map< int /*id*/, const KB_CachedFacts* >::const_iterator it = id2cached_facts.find( id );

 if( it==id2cached_facts.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif
 
   it = id2cached_facts.find( id );
   if( it==id2cached_facts.end() )
    {
     KB_CachedFacts *x = new KB_CachedFacts(id);

     // перебираем все факты из указанной группы и сохраняем их в кэше
     lem::Ptr<LS_ResultSet> rs( storage->ListFactsInGroup( id ) );
     while( rs->Fetch() )
      {
       const int id_fact = rs->GetInt(0);
       KB_Fact * fact = storage->LoadFact(id_fact);
       x->AddFact(fact);
      }

     cached_facts.push_back(x);
     id2cached_facts.insert( std::make_pair(id,x) );
     return *x;
    }
   else
    {
     return * it->second;
    }
  }
 else
  {
   return * it->second;
  }
}
#endif


#if defined SOL_CAA
KB_CheckingResult KnowledgeBase::Prove( int id_facts, const lem::MCollect< const Solarix::Word_Form * > &args )
{
 LEM_CHECKIT_Z( id_facts!=UNKNOWN );
 LEM_CHECKIT_Z( !args.empty() );

 // нам нужна общая информация о наборе фактов...
 const KB_Facts & facts = LoadFacts(id_facts);

 LEM_CHECKIT_Z( facts.CountOfArg()==CastSizeToInt(args.size()) );

 if( facts.IsQueryableByEntries() )
  {
   KB_CheckingResult res;

   if( facts.NeedsFeaturesCheck() )
    {
     lem::MCollect<int> id_fact;
     switch( args.size() )
     {
      case 1: storage->FindFactsByEntries( id_facts, facts.CountOfArg(), args[0]->GetEntryKey(), UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, id_fact ); break;
      case 2: storage->FindFactsByEntries( id_facts, facts.CountOfArg(), args[0]->GetEntryKey(), args[1]->GetEntryKey(), UNKNOWN, UNKNOWN, UNKNOWN, id_fact ); break;
      case 3: storage->FindFactsByEntries( id_facts, facts.CountOfArg(), args[0]->GetEntryKey(), args[1]->GetEntryKey(), args[2]->GetEntryKey(), UNKNOWN, UNKNOWN, id_fact ); break;
      case 4: storage->FindFactsByEntries( id_facts, facts.CountOfArg(), args[0]->GetEntryKey(), args[1]->GetEntryKey(), args[2]->GetEntryKey(), args[3]->GetEntryKey(), UNKNOWN, id_fact ); break;
      case 5: storage->FindFactsByEntries( id_facts, facts.CountOfArg(), args[0]->GetEntryKey(), args[1]->GetEntryKey(), args[2]->GetEntryKey(), args[3]->GetEntryKey(), args[4]->GetEntryKey(), id_fact ); break;
      default: LEM_STOPIT;
     }

     for( lem::Container::size_type i=0; i<id_fact.size(); ++i )
      {
       // TODO: детальная проверка признаков...
       KB_CachedFacts cache(facts.GetId());
       LoadSingleFact( id_fact[i], cache );
       res = cache.Match( dict, facts, args );
       if( res.IsMatched() )
        break;
      }
    }
   else
    {
     int id_fact=UNKNOWN;
  
     switch( args.size() )
     {
      case 1: id_fact=storage->FindFactByEntries( id_facts, facts.CountOfArg(), facts.GetReturnType(), args[0]->GetEntryKey(), UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, res ); break;
      case 2: id_fact=storage->FindFactByEntries( id_facts, facts.CountOfArg(), facts.GetReturnType(), args[0]->GetEntryKey(), args[1]->GetEntryKey(), UNKNOWN, UNKNOWN, UNKNOWN, res ); break;
      case 3: id_fact=storage->FindFactByEntries( id_facts, facts.CountOfArg(), facts.GetReturnType(), args[0]->GetEntryKey(), args[1]->GetEntryKey(), args[2]->GetEntryKey(), UNKNOWN, UNKNOWN, res ); break;
      case 4: id_fact=storage->FindFactByEntries( id_facts, facts.CountOfArg(), facts.GetReturnType(), args[0]->GetEntryKey(), args[1]->GetEntryKey(), args[2]->GetEntryKey(), args[3]->GetEntryKey(), UNKNOWN, res ); break;
      case 5: id_fact=storage->FindFactByEntries( id_facts, facts.CountOfArg(), facts.GetReturnType(), args[0]->GetEntryKey(), args[1]->GetEntryKey(), args[2]->GetEntryKey(), args[3]->GetEntryKey(), args[4]->GetEntryKey(), res ); break;
      default: LEM_STOPIT;
     }
    }

   if( res.IsUnknown() && facts.violation_score<0 )
    {
     if( facts.DoesReturnInteger() )
      {
       res = KB_IntResult( facts.violation_score );
      }
     else if( facts.DoesReturnBoolean() )
      {
       res = KB_BoolResult( true, facts.violation_score );
      }
     else
      {
       LEM_STOPIT;
      }
    }

   return res;
  }
 else if( facts.IsQueryableByWords() )
  {
   KB_CheckingResult res;
   const lem::UCString * empty_str = NULL;
   int id_fact=UNKNOWN;
   switch( args.size() )
   {
    case 1: id_fact=storage->FindFactByWords( id_facts, facts.CountOfArg(), facts.GetReturnType(), *args[0]->GetName(), *empty_str, *empty_str, *empty_str, *empty_str, res ); break;
    case 2: id_fact=storage->FindFactByWords( id_facts, facts.CountOfArg(), facts.GetReturnType(), *args[0]->GetName(), *args[1]->GetName(), *empty_str, *empty_str, *empty_str, res ); break;
    case 3: id_fact=storage->FindFactByWords( id_facts, facts.CountOfArg(), facts.GetReturnType(), *args[0]->GetName(), *args[1]->GetName(), *args[2]->GetName(), *empty_str, *empty_str, res ); break;
    case 4: id_fact=storage->FindFactByWords( id_facts, facts.CountOfArg(), facts.GetReturnType(), *args[0]->GetName(), *args[1]->GetName(), *args[2]->GetName(), *args[3]->GetName(), *empty_str, res ); break;
    case 5: id_fact=storage->FindFactByWords( id_facts, facts.CountOfArg(), facts.GetReturnType(), *args[0]->GetName(), *args[1]->GetName(), *args[2]->GetName(), *args[3]->GetName(), *args[4]->GetName(), res ); break;
    default: LEM_STOPIT;
   }

   if( id_fact!=UNKNOWN && facts.NeedsFeaturesCheck() )
    {
     // проверка координатных пар в аргументах факта.
     KB_CachedFacts cache(facts.GetId());
     LoadSingleFact( id_fact, cache );
     res = cache.Match( dict, facts, args );
    }

   if( res.IsUnknown() && facts.violation_score<0 )
    {
     if( facts.DoesReturnInteger() )
      {
       res = KB_IntResult( facts.violation_score );
      }
     else if( facts.DoesReturnBoolean() )
      {
       res = KB_BoolResult( true, facts.violation_score );
      }
     else
      {
       LEM_STOPIT;
      }
    }

   return res;
  }
 else
  {
   // Загружаемые из БД факты кэшируем.
   const KB_CachedFacts & cache = LoadAndCacheFacts( id_facts );
   
   // Сканируем загруженные факты.
   KB_CheckingResult res = cache.Match( dict, LoadFacts(id_facts), args );
   return res;
  }

 return KB_BoolResult(-1,0);
}
#endif
