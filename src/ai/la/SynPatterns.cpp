#if defined SOL_LOADTXT && defined SOL_COMPILER

// CD->25.08.2012

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

SynPatterns::SynPatterns(void)
{
 id_tree_seq=1;
}


void SynPatterns::LoadTxt( Dictionary &dict, lem::Iridium::Macro_Parser & txtfile )
{
 lem::Iridium::BSourceState beg = txtfile.tellp();

 SynPatternOptions *x = new SynPatternOptions();
 x->LoadTxt( dict, txtfile );

 if( IsPatternName(x->GetName()) )
  {
   dict.GetIO().merr().printf( "Patterns group [%us] is already declared\n", x->GetName().c_str() );
   lem::Iridium::Print_Error(beg,txtfile);
   throw lem::E_BaseException();
  }

 if( dict.GetLexAuto().GetWordEntrySet().IsSetName(x->GetName()) )
  {
   dict.GetIO().merr().printf( "%vfC%us%vn is a name of word entry set, word set or collocation set\n", x->GetName().c_str() );
   lem::Iridium::Print_Error(beg,txtfile);
   throw lem::E_BaseException();
  }

 const int id = GetNextTreeID();

 options.push_back(x);
 lem::UCString uname( lem::to_upper(x->GetName() ) );
 patterns.insert( std::make_pair( uname, x ) );
 name2id.insert( std::make_pair( uname, id ) );

 return;
}


bool SynPatterns::IsPatternName( const lem::UCString &name ) const
{
 return patterns.find( lem::to_upper(name) )!=patterns.end();
}

const SynPatternOptions& SynPatterns::GetOptions( const lem::UCString &name ) const
{
 return * patterns.find( lem::to_upper(name) )->second;
}


int SynPatterns::GetPatternID( const lem::UCString &name ) const
{
 return name2id.find( lem::to_upper(name) )->second;
}


int SynPatterns::GetNextTreeID()
{
 return id_tree_seq++;
}


void SynPatterns::NamedPatternLoaded( const lem::UCString &name )
{
 int id = GetPatternID(name);
 typedef std::map< int, int >::iterator IT;
 IT it = id2count.find(id);
 if( it==id2count.end() )
  id2count.insert( std::make_pair(id, 1) );
 else
  it->second = it->second + 1;

 return;
}

void SynPatterns::GetUnresolvedForwardDeclarations( lem::MCollect<lem::UCString> & unresolved_names ) const
{
 typedef std::map< lem::UCString, int >::const_iterator IT;
 for( IT it=name2id.begin(); it!=name2id.end(); ++it )
  {
   if( id2count.find( it->second )==id2count.end() )
    unresolved_names.push_back( it->first );
  }

 return;
}


#endif
