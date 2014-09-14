#if defined SOL_CAA

// CD->06.03.2011
// LC->05.09.2014

#include <lem/oformatter.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/TrMorphologyTracer.h>

using namespace lem;
using namespace Solarix;


 
TrMorphologyTracerTx::TrMorphologyTracerTx( TrMorphologyTracer *_log, int _tx )
{
 log = _log;
 tx = _tx;
 return;
}

TrMorphologyTracerTx::~TrMorphologyTracerTx(void)
{
 if( log!=NULL )
  Rollback();
}

void TrMorphologyTracerTx::Rollback(void)
{
 LEM_CHECKIT_Z( log!=NULL );

 log->RollbackTx(this);
 log=NULL;
 tx=UNKNOWN;
 return;
}

void TrMorphologyTracerTx::Commit(void)
{
 LEM_CHECKIT_Z( log!=NULL );

 log=NULL;
 tx=UNKNOWN;
 return;
}


TrMorphologyTracer::TrMorphologyTracer(void)
{}

TrMorphologyTracer::~TrMorphologyTracer(void)
{
 Clear();
}


void TrMorphologyTracer::Clear(void)
{
 for( lem::Container::size_type i=0; i<wordforms.size(); ++i )
  delete wordforms[i];
 wordforms.clear();

 wordform_src_ptr.clear();
 str_wordforms.clear();
 points.clear();
 str_points.clear();
 tree_names.clear();

 return;
}


void TrMorphologyTracer::AddMatchingPoint(
                                          const Solarix::Word_Form * head_wordform,
                                          const lem::UFString & wordform_str,
                                          const SynPatternPoint * point,
                                          const lem::UFString & point_str
                                         )
{
 lem::UFString tree_name = GetCurrentTree();

 for( lem::Container::size_type i=0; i<wordforms.size(); ++i )
  if( wordform_src_ptr[i]==head_wordform )
   {
    if( wordform_str==str_wordforms[i] && point==points[i] && tree_name==tree_names[i] )
     return;
   }

 wordform_src_ptr.push_back( head_wordform );
 wordforms.push_back(new Solarix::Word_Form(*head_wordform) );
 str_wordforms.push_back(wordform_str);
 points.push_back(point);
 str_points.push_back(point_str);
 tree_names.push_back(tree_name);
 return;
}



void TrMorphologyTracer::PrintMatchingPoints( lem::OFormatter &to ) const
{
 std::multimap<int,int> x;
 lem::MCollect<int> ordered_forms;

 for( lem::Container::size_type i=0; i<wordforms.size(); ++i )
  {
   x.insert( std::make_pair( wordforms[i]->GetOriginPos(), i ) );
   if( ordered_forms.find(wordforms[i]->GetOriginPos())==UNKNOWN )
    ordered_forms.push_back(wordforms[i]->GetOriginPos());
  }
 
 std::sort( ordered_forms.begin(), ordered_forms.end() );

 for( lem::Container::size_type i=0; i<ordered_forms.size(); ++i )
  {
   const int ipos = ordered_forms[i];

   to.printf( "%60h-\n%vfFPosition%vn: %vfE%d%vn\n", ipos );

   typedef std::multimap<int,int>::iterator IT;
   std::pair<IT,IT> p = x.equal_range(ipos);

   for( IT it=p.first; it!=p.second; ++it )
    {
     int idx = it->second;

     to.printf( "Wordform: %us\n", str_wordforms[idx].c_str() );
     to.printf( "Point:    %us\n", str_points[idx].c_str() );
     to.printf( "Tree:     %us\n", tree_names[idx].c_str() );
    }
  }

 return;
}


void TrMorphologyTracer::PushCurrentTree( const lem::UCString &tree_name )
{
 current_tree.push( lem::UFString(tree_name.c_str()) );
 return;
}


void TrMorphologyTracer::PopCurrentTree(void)
{
 if( current_tree.size()>0 )
  current_tree.pop();

 return;
}

lem::UFString TrMorphologyTracer::GetCurrentTree(void)
{
 return current_tree.empty() ? lem::UFString() : lem::UFString(current_tree.top().c_str());
}


TrMorphologyTracerTx* TrMorphologyTracer::BeginTx(void)
{
 return new TrMorphologyTracerTx( this, CastSizeToInt(wordforms.size()) );
}


void TrMorphologyTracer::RollbackTx( const TrMorphologyTracerTx * x )
{
 const int tx = x->tx;

 if( tx<CastSizeToInt(wordforms.size()) )
  {
   for( int k=tx; k<CastSizeToInt(wordforms.size()); ++k )
    delete wordforms[k];
  }

 wordforms.resize(tx);

 str_wordforms.resize(tx);
 points.resize(tx);
 str_points.resize(tx);
 tree_names.resize(tx);
 return;
}


#endif
