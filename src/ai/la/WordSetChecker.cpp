#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/WordSetChecker.h>


using namespace Solarix;


WordSetChecker::WordSetChecker(void)
 : set_type(UNKNOWN), positive(false)
{}


WordSetChecker::WordSetChecker( int type, const lem::UCString &Setname, bool Positive, const lem::UCString & ExportNodeName )
 : set_type(type), set_name(Setname), positive(Positive), export_node_name(ExportNodeName)
{}


bool WordSetChecker::operator!=( const WordSetChecker & x ) const
{
 return set_type!=x.set_type ||
        set_name!=x.set_name ||
        positive!=x.positive ||
        export_node_name!=x.export_node_name;
}

WordSetChecker::WordSetChecker( const WordSetChecker & x )
 : set_type(x.set_type), set_name(x.set_name), positive(x.positive), export_node_name(x.export_node_name)
{
}


void WordSetChecker::operator=( const WordSetChecker & x )
{
 set_type = x.set_type;
 set_name = x.set_name;
 positive = x.positive;
 export_node_name = x.export_node_name;
 return;
}


#if defined SOL_SAVEBIN
void WordSetChecker::SaveBin( lem::Stream& bin ) const
{
 bin.write( &set_type, sizeof(set_type) );
 bin.write( &set_name, sizeof(set_name) );
 bin.write( &positive, sizeof(positive) );
 bin.write( &export_node_name, sizeof(export_node_name) );
 return;
}
#endif

#if defined SOL_LOADBIN 
void WordSetChecker::LoadBin( lem::Stream& bin )
{
 bin.read( &set_type, sizeof(set_type) );
 bin.read( &set_name, sizeof(set_name) );
 bin.read( &positive, sizeof(positive) );
 bin.read( &export_node_name, sizeof(export_node_name) );

 LEM_CHECKIT_Z( set_type==0 || set_type==1 || set_type==2 );
 LEM_CHECKIT_Z( positive==0 || positive==1 );

 return;
}
#endif



#if defined SOL_CAA
bool WordSetChecker::Check( SynGram &sg, const Solarix::Word_Form &wf, WordEntrySet & sets ) const
{
 switch(set_type)
 {
  case 0:
   return Affirmate(sets.FindWordSet( set_name, *wf.GetName() ));

  case 1:
   return Affirmate(sets.FindWordEntrySet( set_name, wf.GetEntryKey() ));

  case 2:
   return Affirmate(sets.FindWordformSet( sg, set_name, wf ));

  default: LEM_STOPIT;
 }  

 return false;
}
#endif
