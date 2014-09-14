#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/PatternConstraints.h>

using namespace Solarix;


PatternConstraints::PatternConstraints(void)
{
}


PatternConstraints::PatternConstraints( const PatternConstraints & x )
 : constraints(x.constraints)
{
}



void PatternConstraints::operator=( const PatternConstraints &x )
{
 constraints = x.constraints;
 return;
}


bool PatternConstraints::operator!=( const PatternConstraints &x ) const
{
 return constraints != x.constraints;
}





#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternConstraints::LoadTxt( 
                                 Dictionary &dict,
                                 lem::Iridium::Macro_Parser & txtfile,
                                 SynPatternCompilation & compilation_context
                                )
{
 txtfile.read_it( B_OFIGPAREN ); 

 lem::Iridium::BSourceState beg = txtfile.tellp();

 while( !txtfile.eof() )
 {
  if( txtfile.probe( B_CFIGPAREN ) )
   break;

  PatternConstraint * c = new PatternConstraint();
  c->LoadTxt( dict, txtfile, compilation_context );
  constraints.push_back(c);
 }

 return;
}
#endif    


void PatternConstraints::SaveBin( lem::Stream &bin ) const
{
 constraints.SaveBin(bin);
 return;
}

void PatternConstraints::LoadBin( lem::Stream &bin )
{
 constraints.LoadBin(bin);
 return;
}



#if defined SOL_CAA
PatternConstraintResult PatternConstraints::Check(
                                                  const LexicalAutomat & la,
                                                  const BackTrace * parent_trace,
                                                  const lem::MCollect<int> & PatternSequenceNumber,
                                                  const SynPatternResult * cur_result
                                                 ) const
{
 PatternConstraintResult res;
 res.success = true;

 for( lem::Container::size_type i=0; i<constraints.size(); ++i )
  {
   res.Union( constraints[i]->Check( la, parent_trace, PatternSequenceNumber, cur_result ) );
   if( !res.success )
    break;
  }

 return res;
}
#endif
