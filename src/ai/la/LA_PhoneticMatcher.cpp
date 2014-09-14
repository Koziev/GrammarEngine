#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_PhoneticMatcher.h>

using namespace Solarix;


LA_PhoneticMatcher::LA_PhoneticMatcher( Solarix::Dictionary *Dict )
{
 dict = Dict;
 storage = NULL;
 return;
}

void LA_PhoneticMatcher::Connect( LexiconStorage *Storage )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs_init); 
 #endif

 storage = Storage;
 DeleteRules();
 return;
}


LA_PhoneticMatcher::~LA_PhoneticMatcher(void)
{
 DeleteRules();
 return;
}


void LA_PhoneticMatcher::DeleteRules(void)
{
 for( lem::Container::size_type i=0; i<matcher.size(); ++i )
  {
   delete matcher[i];
  }

 matcher.clear();
 id_langs.clear();

 return;
}


const LA_PhoneticMatcherForLanguage* LA_PhoneticMatcher::GetMatcherForLanguage( int id_language )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs);
 #endif

 const int i = id_langs.find(id_language);
 if( i==UNKNOWN )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   return LoadRules(id_language);
  }
 else
  {
   return matcher[i];
  }
}

const LA_PhoneticMatcherForLanguage* LA_PhoneticMatcher::LoadRules( int id_language )
{
 LA_PhoneticMatcherForLanguage *m = new LA_PhoneticMatcherForLanguage(id_language);
 m->Load( dict, storage );
 matcher.push_back(m);
 id_langs.push_back(id_language);
 return m;
}
