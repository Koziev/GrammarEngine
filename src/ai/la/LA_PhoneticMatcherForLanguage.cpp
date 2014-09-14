#include <lem/macro_parser.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_PhoneticRuleEnumerator_MCollect.h>
#include <lem/solarix/LA_PhoneticMatcher.h>

using namespace Solarix;

LA_PhoneticMatcherForLanguage::LA_PhoneticMatcherForLanguage( int Id_Lang )
 : id_language(Id_Lang), min_context(UNKNOWN), max_context(UNKNOWN)
{
}

LA_PhoneticMatcherForLanguage::~LA_PhoneticMatcherForLanguage()
{
 for( lem::Container::size_type i=0; i<rules.size(); ++i )
  delete rules[i];

 return;
}

void LA_PhoneticMatcherForLanguage::Load( Solarix::Dictionary *dict, LexiconStorage *storage )
{
 min_context = lem::int_max;
 max_context = 0;

 if( id_language==UNKNOWN || id_language==ANY_STATE )
  {
   // нам нужны правила для всех имеющихся языков.
   Load( storage, storage->ListPhoneticRules(ANY_STATE) );
  }
 else
  {
   Load( storage, storage->ListPhoneticRules(id_language) );
   Load( storage, storage->ListPhoneticRules(UNKNOWN) );
  }

 return;
}

void LA_PhoneticMatcherForLanguage::Load( LexiconStorage *storage, LS_ResultSet *rs )
{
 while( rs->Fetch() )
  {
   const int id = rs->GetInt(0);
   LA_PhoneticRule *r = storage->GetPhoneticRule(id);
   rules.push_back(r);

   groups[ r->GetCondition().length() ].rules.push_back(r);

   min_context = std::min( min_context, r->GetCondition().length() );
   max_context = std::max( max_context, r->GetCondition().length() );

   if( r->Is_1_to_1() )
    {
     rules_11.insert(
                     std::make_pair(
                                    Rule_1_to_1(
                                                r->GetCondition().single(),
                                                r->GetResult().single()
                                               ),
                                    r->GetVal()
                                   )
                    );  
    } 
  }

 delete rs;
 return;
}

lem::Real1 LA_PhoneticMatcherForLanguage::MatchRule11( const Rule_1_to_1 &r ) const
{
 RULES11::const_iterator it = rules_11.find(r);
 if( it==rules_11.end() )
  return lem::Real1(0);
 else
  return it->second;
}


LA_PhoneticRuleEnumerator* LA_PhoneticMatcherForLanguage::EnumerateRules(void) const
{
 return new LA_PhoneticRuleEnumerator_MCollect(rules);
}
