#include <lem/oformatter.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/SynPatternResult.h>

using namespace lem;
using namespace Solarix;

#undef GetForm


void SynPatternResult::ResetCoordStates( int coord_id, const lem::MCollect<int> & state_ids )
{
 std::multimap< int /*id_coord*/, int /*id_state*/ > filtered;
 for( std::multimap< int /*id_coord*/, int /*id_state*/ >::const_iterator it=exported_coords.begin(); it!=exported_coords.end(); ++it )
  {
   if(coord_id != it->first )
    filtered.insert(*it);
  }

 for( lem::Container::size_type i=0; i<state_ids.size(); ++i )
  filtered.insert( std::make_pair( coord_id, state_ids[i] ) );

 exported_coords = filtered;

 return;
}


void SynPatternResult::GetExportCoordPairs( lem::MCollect< std::pair<int,int> > & pairs ) const
{
 for( std::multimap< int /*id_coord*/, int /*id_state*/ >::const_iterator it=exported_coords.begin(); it!=exported_coords.end(); ++it )
  {
   pairs.push_back(*it);
  }

 return;
}



void SynPatternResult::FilterExportedCoords( const lem::MCollect<int> & must_be_exported )
{
 if( must_be_exported.empty() )
  exported_coords.clear();
 else
  {
   std::multimap< int /*id_coord*/, int /*id_state*/ > filtered;
   for( std::multimap< int /*id_coord*/, int /*id_state*/ >::const_iterator it=exported_coords.begin(); it!=exported_coords.end(); ++it )
    {
     if( must_be_exported.find(it->first)!=UNKNOWN )
      filtered.insert(*it);
    }

   exported_coords = filtered;
  }

 return;
}


#if defined SOL_DEBUGGING
bool SynPatternResult::FindExportedNode( const lem::UCString & required ) const
{
 for( lem::Container::size_type i=0; i<exported_nodes.size(); ++i )
  {
   const lem::UCString & name = * exported_nodes[i].first;
   if( required == name )
    return true;
  }

 return false;  
}
#endif


void SynPatternResult::FilterExportedNodes( const lem::MCollect< ExportNode > & must_be_exported )
{
 if( must_be_exported.empty() )
  {
   exported_nodes.clear();
  }
 else
  {
   lem::MCollect< std::pair<const lem::UCString*,const Word_Form*> > filtered;
   for( lem::Container::size_type i=0; i<exported_nodes.size(); ++i )
    {
     const lem::UCString & name = * exported_nodes[i].first;
     for( lem::Container::size_type j=0; j<must_be_exported.size(); ++j )
      if( must_be_exported[j].node_name == name )
       {
        // Ќашли ссылку, которую нужно перебросить в новый список, возможно уже под другим именем
        filtered.push_back( std::make_pair( &must_be_exported[j].as_name, exported_nodes[i].second ) );
        break;
       }
    }

   exported_nodes = filtered;
  }

 return;
}



SynPatternResult* SynPatternResult::Copy1( const BackTrace *external_trace ) const
{
 SynPatternResult * x = new SynPatternResult(external_trace);

 x->res = res;
 x->named_tree_invoked = named_tree_invoked;
 x->matched_alts = matched_alts;
 x->exported_coords = exported_coords;
 x->exported_nodes = exported_nodes;
 x->linkage_groups = linkage_groups;
 x->linkage_edges = linkage_edges;

 #if defined SOL_DEBUGGING
 x->debug_trace = debug_trace;
 #endif
 
 return x;
}


namespace {
bool wordform_sorter( const Solarix::Word_Form * x, const Solarix::Word_Form * y )
{ return x->GetOriginPos() < y->GetOriginPos(); }
}


void SynPatternResult::Print( lem::OFormatter &out, SynGram &sg ) const
{
 out.printf( "Length=%vfE%d%vn Ngrams=%vfE%d%vn Edges=%d Groups=%d\n", res.Length(), res.GetNGramFreq().Composite(), CastSizeToInt(linkage_edges.size()), CastSizeToInt(linkage_groups.size()) );

 out.printf( "%vfAMATCHED WORDFORMS%vn:\n" );
 // Ќапечатаем список сопоставленных словоформ.
 lem::MCollect< const Solarix::Word_Form* > wordforms;
 for( MATCHING_ALTS::const_iterator it=matched_alts.begin(); it!=matched_alts.end(); ++it )
  {
   wordforms.push_back( it->first->GetVersion( it->second ) );
  }

 // ќтсортируем в пор€дке возрастани€ позиции, чтобы визуально они были в нормальной последовательности.
 std::sort( wordforms.begin(), wordforms.end(), wordform_sorter );

 for( lem::Container::size_type i=0; i<wordforms.size(); ++i )
  {
   out.printf( "[%vfE%d%vn] ", CastSizeToInt(i) );

   Solarix::Word_Form dummy( *wordforms[i], false );
   dummy.Print( out, &sg, true );
   out.eol();
  }

 out.printf( "%vfATRACE%vn: " );
 trace.Print( out, sg, false );
 out.eol();


/*
 #if defined SOL_DEBUGGING
 for( lem::Container::size_type i=0; i<debug_trace.size(); ++i )
  {
   const SynPatternPoint * point = debug_trace[i].point;

   for( lem::Container::size_type j=0; j<point->GetSources().size(); ++j )
    {
     const int src = point->GetSources()[j];
     lem::Path filename;
     int line=0, column=0;
  
     if( sg.GetDict().GetDebugSymbols().GetLocation( src, filename, line, column ) )
      {
       lem::mout->printf( " %vfA%us%vn:%vfE%d%vn", filename.GetFileName().c_str(), line );
      }
    }
  }
 #endif
*/
 
 return;
}


void SynPatternResult::PrintLinks( lem::OFormatter &out, SynGram &sg ) const
{
 lem::mout->printf( "\nThere are %d edges:\n", CastSizeToInt(linkage_edges.size()) );
 for( lem::Container::size_type k=0; k<linkage_edges.size(); ++k )
  {
   const PatternLinkEdge & edge = linkage_edges[k];

   Solarix::Word_Form wf0( *edge.from, false );
   Solarix::Word_Form wf1( *edge.to, false );

   lem::UCString link_name;
   if( edge.link_type==UNKNOWN )
    link_name = L"((unknown))";
   else
    link_name = sg.coords()[0].GetStateName(edge.link_type);

   wf0.Print( out, &sg, true );
   out.printf( " --(%us)--> ", link_name.c_str() );
   wf1.Print( out, &sg, true );
   out.eol();
  }

 return;
}




void SynPatternResult::PrintLinkageGroups( lem::OFormatter &out, SynGram &sg ) const
{
 lem::mout->printf( "\nThere are %d groups:\n", CastSizeToInt(linkage_groups.size()) );
 for( lem::Container::size_type k=0; k<linkage_groups.size(); ++k )
  {
   const PatternSynLinkedGroup & g = linkage_groups[k];

   Solarix::Word_Form wf0( *g.begin->GetWordform(), false );
   Solarix::Word_Form wf1( *g.end->GetWordform(), false );
   Solarix::Word_Form wfr( *g.root_node, false );

   wf0.Print( out, &sg, true );
   out.printf( " ... " );
   wf1.Print( out, &sg, true );
   out.printf( " ==> " );
   wfr.Print( out, &sg, true );
   out.eol();
  }

 return;
}



void SynPatternResult::PrintExportedNodes( lem::OFormatter &out, SynGram &sg ) const
{
 for( lem::Container::size_type i=0; i<exported_nodes.size(); ++i )
  {
   out.printf( "%us=", exported_nodes[i].first->c_str() );
   exported_nodes[i].second->Print( out, &sg, true );
   out.eol();
  }

 trace.Print( out, sg, true );
 out.eol();

 return;
}


void SynPatternResult::AddExportedNode( const lem::UCString * name, const Word_Form * node )
{
 exported_nodes.push_back( std::make_pair(name,node) );
}


const Word_Form* SynPatternResult::FindExportNode( const lem::UCString & name ) const
{
 for( lem::Container::size_type i=0; i<exported_nodes.size(); ++i )
  if( (*exported_nodes[i].first) == name )
   return exported_nodes[i].second;

/*
 lem::MemFormatter mem;
 mem.printf( "Can not find node %us is export results: {", name.c_str() );
 for( lem::Container::size_type i=0; i<exported_nodes.size(); ++i )
  {
   mem.printf( " %us", exported_nodes[i].first->c_str() );
  }
 mem.printf( " }" );
 throw lem::E_BaseException( mem.string() );
*/

 return NULL;
}


void SynPatternResult::AddLinkageGroup( const PatternSynLinkedGroup & new_group )
{
 linkage_groups.push_back( new_group );
 return;
}



int SynPatternResult::FindLinkageGroup( const LexerTextPos * t1, const LexerTextPos * t2 ) const
{
 for( lem::Container::size_type i=0; i<linkage_groups.size(); ++i )
  {
   if( linkage_groups[i].begin==t1 && linkage_groups[i].end==t2 )
    return CastSizeToInt(i);
  }

 return UNKNOWN;
}




void SynPatternResult::AddLinkageEdge( const PatternLinkEdge & new_edge )
{
 linkage_edges.push_back( new_edge );
 return;
}




#if defined SOL_DEBUGGING
void SynPatternResult::AppendDebugTrace( const lem::MCollect<SynPatternDebugTrace> & debug_trace2 )
{
 for( lem::Container::size_type i=0; i<debug_trace2.size(); ++i )
  {
   debug_trace.push_back( debug_trace2[i] );
  }

 return;
}
#endif


#if defined SOL_DEBUGGING
void SynPatternResult::Append( const SynPatternDebugTrace & dbg )
{
/*
 #if LEM_DEBUGGING==1
 if( dbg.wordform->GetName()->eqi( L"€" ) )
  {
   for( lem::Container::size_type i=0; i<debug_trace.size(); ++i )
    {
     lem::mout->printf( "point=%X16d wordform=%us pattern=%us\n", debug_trace[i].point, debug_trace[i].wordform->GetName()->c_str(), debug_trace[i].pattern_name==NULL ? L"" : debug_trace[i].pattern_name->c_str() );
    }
  }
 #endif
*/

 if( debug_trace.empty() )
  debug_trace.push_back( dbg );
 else if(
         debug_trace.back().wordform == dbg.wordform &&
         debug_trace.back().pattern_name!=NULL && dbg.pattern_name==NULL &&
         dbg.wordform_matching==false
        )
  {
  }
 else if( !debug_trace.back().SamePoint(dbg) )
  debug_trace.push_back( dbg );
 else if( !res.GetNGramFreq().IsZero() )
  debug_trace.back().ngram_freq = res.GetNGramFreq();

 return;
}
#endif



void SynPatternResult::Append( const SynPatternResult & src )
{
 #if defined SOL_DEBUGGING
 AppendDebugTrace( src.debug_trace );
 #endif

 std::copy( src.linkage_groups.begin(), src.linkage_groups.end(), std::back_inserter(linkage_groups) );
 std::copy( src.linkage_edges.begin(), src.linkage_edges.end(), std::back_inserter(linkage_edges) );

 for( MATCHING_ALTS::const_iterator it=src.matched_alts.begin(); it!=src.matched_alts.end(); ++it )
  matched_alts.insert(*it);

 return;
}


void SynPatternResult::AppendMatchedAlts( const SynPatternResult & src )
{
 for( MATCHING_ALTS::const_iterator it=src.matched_alts.begin(); it!=src.matched_alts.end(); ++it )
  matched_alts.insert(*it);
}


void SynPatternResult::AppendLinks( const SynPatternResult & src )
{
 std::copy( src.linkage_groups.begin(), src.linkage_groups.end(), std::back_inserter(linkage_groups) );
 std::copy( src.linkage_edges.begin(), src.linkage_edges.end(), std::back_inserter(linkage_edges) );
 return;
}




namespace
{
 inline int CastPtr2Int( const void * ptr )
 {
  #if defined LEM_64
  return (int)(lem::uint64_t)ptr;
  #else
  return (int)ptr;
  #endif
 }
}

int SynPatternResult::CalcHash() const
{
 int h=0;
 h = this->res.Length();
 h = h ^ (this->res.Matched() ? 0x1000000 : 0x01000000);
 h = h ^ (this->res.GetNGramFreq().Composite() << 8);
 
 h = h ^ (this->exported_coords.size() << 10);
 h = h ^ (this->exported_nodes.size() << 12);
 h = h ^ (this->matched_alts.size() << 18 );

 for( EXPORTED_COORDS::const_iterator it=this->exported_coords.begin(); it!=this->exported_coords.end(); ++it )
  {
   h = h ^ ( (it->first<<3) ^ (it->second<<5) );
  }

 for( EXPORTED_NODES::const_iterator it=this->exported_nodes.begin(); it!=this->exported_nodes.end(); ++it )
  {
   h = h ^ ( it->first->GetHash() ^ CastPtr2Int(it->second) );
  }

/*
 h = h ^ (this->linkage_groups.size() << 16);
 for( LINKAGE_GROUPS::const_iterator it=this->linkage_groups.begin(); it!=this->linkage_groups.end(); ++it )
  {
   h = h ^ ( CastPtr2Int(it->begin) ^ CastPtr2Int(it->end) ^ CastPtr2Int(it->root_node) );
  }
*/

 h = h ^ (this->linkage_edges.size() << 14);
 for( LINKAGE_EDGES::const_iterator it=this->linkage_edges.begin(); it!=this->linkage_edges.end(); ++it )
  {
   h = h ^ ( CastPtr2Int(it->from) ^ CastPtr2Int(it->to) ^ it->link_type );
  }


 return h;
}


bool SynPatternResult::Equals( const SynPatternResult *x, const SynPatternResult *y )
{
 if( x->res.Length() != y->res.Length() )
  return false;

 if( x->res.Matched() != y->res.Matched() )
  return false;

 if( !x->res.GetNGramFreq().Equal( y->res.GetNGramFreq() ) )
  return false;

 if( x->exported_nodes.size() != y->exported_nodes.size() )
  return false;

 for( EXPORTED_NODES::const_iterator it=x->exported_nodes.begin(); it!=x->exported_nodes.end(); ++it )
  {
   if( y->exported_nodes.find( *it )==UNKNOWN )
    return false;
  }

/*
 if( x->linkage_groups.size() != y->linkage_groups.size() )
  return false;

 for( LINKAGE_GROUPS::const_iterator it=x->linkage_groups.begin(); it!=x->linkage_groups.end(); ++it )
  {
   if( y->linkage_groups.find( *it ) == UNKNOWN )
    return false;
  }
*/

 if( x->linkage_edges.size() != y->linkage_edges.size() )
  return false;

 for( LINKAGE_EDGES::const_iterator it=x->linkage_edges.begin(); it!=x->linkage_edges.end(); ++it )
  {
   if( y->linkage_edges.find( *it ) == UNKNOWN )
    return false;
  }

 if( x->exported_coords.size() != y->exported_coords.size() )
  return false;

 lem::MCollect< std::pair<int,int> > x1;
 for( EXPORTED_COORDS::const_iterator it=x->exported_coords.begin(); it!=x->exported_coords.end(); ++it )
  x1.push_back( *it );

 lem::MCollect< std::pair<int,int> > y1;
 for( EXPORTED_COORDS::const_iterator it=y->exported_coords.begin(); it!=y->exported_coords.end(); ++it )
  y1.push_back( *it );
 
 for( lem::Container::size_type i=0; i<x1.size(); ++i )
  {
   std::pair<int,int> p1 = x1[i];

   bool f=false;
   for( lem::Container::size_type j=0; j<y1.size(); ++j )
    if( y1[j]==p1 )
     {
      f=true;
      break;
     }

   if( !f ) return false;
  }

 return true;
}


void SynPatternResult::SelectUnique_WithRemoval( lem::MCollect<SynPatternResult*> & results )
{
 lem::MCollect<int> result_hash;
 lem::PtrCollect<SynPatternResult> unique_result;
 for( lem::Container::size_type k=0; k<results.size(); ++k )
  {
   SynPatternResult * result_k = results[k];
   const int h = result_k->CalcHash();
 
   bool found=false;
   for( lem::Container::size_type i=0; i<unique_result.size(); ++i )
    if( result_hash[i] == h )
     {
      if( SynPatternResult::Equals( result_k, unique_result[i] ) )
       {
        found = true;
        break;
       }
     }

   if( !found )
    {
     result_hash.push_back(h);
     unique_result.push_back(result_k);
     results[k] = NULL;
    }
  }

 results.clear();

 for( lem::Container::size_type i=0; i<unique_result.size(); ++i )
  {
   results.push_back( unique_result[i] );
   unique_result[i] = NULL;
  }

 return;
}


void SynPatternResult::SelectUnique_WithoutRemoval( lem::MCollect<const SynPatternResult*> & results )
{
 lem::MCollect<int> result_hash;
 lem::MCollect<const SynPatternResult*> unique_result;
 for( lem::Container::size_type k=0; k<results.size(); ++k )
  {
   const SynPatternResult * result_k = results[k];
   const int h = result_k->CalcHash();
 
   bool found=false;
   for( lem::Container::size_type i=0; i<unique_result.size(); ++i )
    if( result_hash[i] == h )
     {
      if( SynPatternResult::Equals( result_k, unique_result[i] ) )
       {
        found = true;
        break;
       }
     }

   if( !found )
    {
     result_hash.push_back(h);
     unique_result.push_back(result_k);
    }
  }

 results = unique_result;

 return;
}
