#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/PredicateTemplate.h>

using namespace Solarix;


bool PredicateTemplates::operator==( const PredicateTemplates & x ) const
{
 return predicates == x.predicates;
}



bool PredicateTemplates::operator!=( const PredicateTemplates & x ) const
{
 return predicates != x.predicates;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void PredicateTemplates::LoadTxt( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, const PredicateTemplateParams & param_list )
{
 txtfile.read_it( B_OFIGPAREN );

 while( !txtfile.eof() )
 {
  if( txtfile.probe( B_CFIGPAREN ) )
   break;

  PredicateTemplate * p = new PredicateTemplate();
  p->LoadTxt( dict, txtfile, param_list );
  predicates.push_back(p);
 }

 return;
}
#endif




void PredicateTemplates::SaveBin( lem::Stream & bin ) const
{
 predicates.SaveBin(bin);
 return;
}


void PredicateTemplates::LoadBin( lem::Stream & bin )
{
 predicates.LoadBin(bin);
 return;
}
