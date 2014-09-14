#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/TreeScorer.h>

using namespace Solarix;


TreeScorerPredicateArg::TreeScorerPredicateArg() : id_class(UNKNOWN)
{}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerPredicateArg::LoadTxt( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile )
{
 const lem::Iridium::BethToken & class_name = txtfile.read();


 id_class = dict.GetSynGram().FindClass(class_name);
 if( id_class==UNKNOWN )
  {
   lem::Iridium::Print_Error(class_name,txtfile);
   dict.GetIO().merr().printf( "Unknown part-of-speesh %us\n", class_name.c_str() );
   throw lem::E_BaseException();
  }

 return;
}
#endif
