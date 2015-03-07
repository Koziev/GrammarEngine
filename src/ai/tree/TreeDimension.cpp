// 11.10.2011 - добавлена сериализация в XML

// CD->06.07.2009
// LC->11.10.2011

#if !defined SOL_NO_AA

#include <lem/solarix/dictionary.h>
#include <lem/solarix/tree_node.h>

using namespace lem;
using namespace Solarix;

TreeDimension::TreeDimension(void)
{
}

TreeDimension::TreeDimension( const UCString &x )
 : name(x)
{
}


TreeDimension::TreeDimension( const TreeDimension &x )
{
 name = x.name;
 for( lem::Container::size_type i=0; i<x.nodes.size(); ++i )
  nodes.push_back( new Tree_Node( *x.nodes[i] ) );

 return;
}

TreeDimension::~TreeDimension(void)
{
 Clear();
 return;
}

void TreeDimension::operator=( const TreeDimension &x )
{
 name = x.name;
 for( lem::Container::size_type i=0; i<x.nodes.size(); ++i )
  nodes.push_back( new Tree_Node( *x.nodes[i] ) );

 return;
}

void TreeDimension::Clear(void)
{
 for( lem::Container::size_type i=0; i<nodes.size(); ++i )
  delete nodes[i];

 nodes.clear();

 return;
}

void TreeDimension::Remove( int i )
{
 nodes.Remove(i);
 return;
}


void TreeDimension::Add( Tree_Node *x )
{
 if( x==NULL )
  throw E_BaseException( L"TreeDimension::Add(NULL) is not valid usage" );

 nodes.push_back(x);
 return;
}


void TreeDimension::Add( const TreeDimension &src )
{ 
 for( lem::Container::size_type i=0; i<src.size(); ++i )
  nodes.push_back( new Tree_Node( src[CastSizeToInt(i)] ) );

 return;
}


#if defined SOL_SAVEBIN
void TreeDimension::SaveBin( lem::Stream &bin ) const
{
 bin.write( &name, sizeof(name) );

 bin.write_int( CastSizeToInt(nodes.size()) );
 for( lem::Container::size_type i=0; i<nodes.size(); ++i )
  nodes[i]->SaveBin(bin);

 return; 
}
#endif


#if defined SOL_LOADBIN
void TreeDimension::LoadBin( lem::Stream &bin )
{
 bin.read( &name, sizeof(name) );
 const int n = bin.read_int();
 for( int i=0; i<n; ++i )
  nodes.push_back( new Tree_Node(bin) );
 
 return;
}
#endif


void TreeDimension::Print( const Solarix::Dictionary & dict, lem::OFormatter & out, bool detailed ) const
{
 if( !nodes.empty() )
  {
   out.printf( "%vf6<<%vn%vfB%us%vn%vf6>>:%vn", name.c_str() );
   if( nodes.size()>1 )
    out.printf( "%vf6{%vn" );
 
   for( lem::Container::size_type i=0; i<nodes.size(); ++i )
    {
     out.printf( ' ' );
     nodes[i]->Print( out, dict.GetSynGram(), 0, detailed );
    }

   if( nodes.size()>1 )
    out.printf( " %vf6}%vn" );
  }

 return;
}


void TreeDimension::PrintXML( lem::OFormatter & xml, const Solarix::Dictionary & dict ) const
{
 xml.printf( "<dimension>\n" ); 
 xml.printf( "<name>%us</name>\n", name.c_str() );

 xml.printf( "<trees count=\"%d\">\n", CastSizeToInt(nodes.size()) );
 for( lem::Container::size_type i=0; i<nodes.size(); ++i )
 {
  xml.printf( "<tree n=\"%d\">\n", CastSizeToInt(i) );
  nodes[i]->PrintXML( xml, dict.GetSynGram() );
  xml.printf( "</tree>\n" );
 }
 xml.printf( "</trees>\n" );

 xml.printf( "</dimension>\n" ); 

 return;
}

namespace {
static bool node_sorter( const Tree_Node * x, const Tree_Node * y )
{
 return x->GetNode().GetOriginPos() < y->GetNode().GetOriginPos();
}
}

void TreeDimension::SortByWordIndex()
{
 std::sort( nodes.begin(), nodes.end(), node_sorter );

 for( int i=0; i<nodes.size(); ++i )
  nodes[i]->leafs().SortByWordIndex();

 return;
}



#endif
