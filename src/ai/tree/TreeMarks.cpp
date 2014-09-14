#if !defined SOL_NO_AA

// 11.10.2011 - добавлена сериализация в XML

// LC->11.10.2011

#include <lem/conversions.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tree_node.h>

using namespace lem;
using namespace Solarix;

TreeMarks::TreeMarks(void)
{
}

TreeMarks::TreeMarks( const UCString &Name )
 : name(Name)
{
 LEM_CHECKIT_Z(name.empty()==false );
}

TreeMarks::TreeMarks( const TreeMarks & x )
 : name(x.name)
{
 for( lem::Container::size_type i=0; i<x.values.size(); ++i )
  values.push_back( new TrValue( * x.values[i] ) );

 return;
}

TreeMarks::~TreeMarks(void)
{
 Clear();
 return;
}

 
void TreeMarks::operator=( const TreeMarks &x )
{
 if( this!=&x )
  {
   name = x.name;
   Clear();

   for( lem::Container::size_type i=0; i<x.values.size(); ++i )
    values.push_back( new TrValue( * x.values[i] ) );
  }

 return;
}

void TreeMarks::Add( TrValue *v )
{
 values.push_back(v);
 return;
}


void TreeMarks::Add( const TreeMarks &src )
{
 for( lem::Container::size_type i=0; i<src.values.size(); ++i )
  Add( new TrValue( *src.values[i] ) );

 return;
}


void TreeMarks::Clear(void)
{
 for( lem::Container::size_type i=0; i<values.size(); ++i )
  delete values[i];

 values.clear();
 return; 
}


#if defined SOL_SAVEBIN
void TreeMarks::SaveBin( lem::Stream &bin ) const
{
 bin.write( &name, sizeof(name) );
 bin.write_int( CastSizeToInt(values.size()) );
 for( lem::Container::size_type i=0; i<values.size(); ++i )
  values[i]->SaveBin(bin); 

 return;
}
#endif



#if defined SOL_LOADBIN
void TreeMarks::LoadBin( lem::Stream &bin )
{
 bin.read( &name, sizeof(name) );
 const int n = bin.read_int();
 for( int i=0; i<n; ++i )
  {
   TrValue *v = new TrValue;
   v->LoadBin(bin);
   // todo v->Link(...)
  }
 
}
#endif


void TreeMarks::Print( const Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
 out.printf( "%vfA%us%vn=", name.c_str() );
 if( values.size()>1 )
  out.printf( "%vf6{%vn " );

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  {
   out.printf( ' ' );
   values[i]->Print( dict, out );
  }

 if( values.size()>1 )
  out.printf( " %vf6{%vn" );

 return;
}


void TreeMarks::PrintXML( lem::OFormatter &xml, const Solarix::Dictionary &dict ) const
{
 xml.printf( "<mark>\n" );
 xml.printf( "<name>%us</name>\n", name.c_str() );

 xml.printf( "<values count=\"%d\">\n", CastSizeToInt(values.size()) );

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  {
   xml.printf( "<value n=\"%d\">\n", CastSizeToInt(i) );
   values[i]->PrintXML( xml, dict );
   xml.printf( "</value>\n" );
  }
 xml.printf( "</values>\n" );

 xml.printf( "</mark>\n" );

 return;
}


#endif
