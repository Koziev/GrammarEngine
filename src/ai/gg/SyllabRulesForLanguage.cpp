#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/SyllabRule.h>

using namespace Solarix;
using namespace lem;


SyllabRulesForLanguage::SyllabRulesForLanguage( int _id_language )
 : id_language(_id_language), min_len(UNKNOWN), max_len(UNKNOWN)
{}


void SyllabRulesForLanguage::Load( AlphabetStorage *storage )
{
 LEM_CHECKIT_Z( rules.empty() );

 lem::Ptr<LS_ResultSet> rs(storage->ListSyllabRulesForLanguage(id_language));

 min_len = lem::int_max;
 max_len = 0;

 while( rs->Fetch() )
  {
   const int id_rule = rs->GetInt(0);
   SyllabRule *rule = storage->LoadSyllabRule(id_rule);
   rules.push_back(rule);

   const int ConditionSize = rule->GetCondition().Count();
   len2rules.insert( std::make_pair( ConditionSize, rule ) );
   min_len = std::min( min_len, ConditionSize );
   max_len = std::max( max_len, ConditionSize );
  }

 return;
}

