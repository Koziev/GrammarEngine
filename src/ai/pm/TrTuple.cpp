#if !defined SOL_NO_AA

#include <lem/solarix/pm_autom.h>
#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;

TrTuple::TrTuple(void)
{
}

TrTuple::TrTuple( const TrTuple &x )
{
 values.reserve(x.values.size());
 for( lem::Container::size_type i=0; i<x.values.size(); ++i )
  values.push_back( new TrValue( *x.values[i] ) );

 return;
}

TrTuple::~TrTuple(void)
{
 for( lem::Container::size_type i=0; i<values.size(); ++i )
  delete values[i];
}

void TrTuple::operator=( const TrTuple &x )
{
 for( lem::Container::size_type i=0; i<values.size(); ++i )
  delete values[i];

 values.clear();
 
 for( lem::Container::size_type i=0; i<x.values.size(); ++i )
  values.push_back( new TrValue( *x.values[i] ) );

 return;
}

#if defined SOL_SAVEBIN
void TrTuple::SaveBin( lem::Stream &bin ) const
{
 bin.write_int( CastSizeToInt(values.size()) );
 for( lem::Container::size_type i=0; i<values.size(); ++i )
  values[i]->SaveBin(bin);

 return; 
}
#endif


#if defined SOL_LOADBIN 
void TrTuple::LoadBin( lem::Stream &bin )
{
 const int n = bin.read_int();
 for( int i=0; i<n; ++i )
  {
   values.push_back( new TrValue );
   values.back()->LoadBin(bin);
  }

 return;
}
#endif


bool TrTuple::operator==( const TrTuple &x ) const
{
 if( values.size() != x.values.size() )
  return false;

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  if( !values[i]->eq(*x.values[i]) )
   return false;

 return true;
}


bool TrTuple::operator!=( const TrTuple &x ) const
{
 if( values.size() != x.values.size() )
  return true;

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  if( values[i]->eq(*x.values[i]) )
   return false;

 return true;
}


#if defined SOL_LOADBIN 
void TrTuple::Link( const TrFunctions &funs )
{
 for( lem::Container::size_type i=0; i<values.size(); ++i )
  values[i]->Link(funs);

 return; 
}
#endif

void TrTuple::Set( int i, TrValue &x )
{
 values[i]->Assign(x);
 return;
}

void TrTuple::Add( const TrValue &x )
{
 values.push_back( new TrValue(x) );
 return;
}


void TrTuple::Add( TrValue * x )
{
 values.push_back( x );
 return;
}


void TrTuple::Remove( int i )
{
 delete values[i];
 values.Remove(i);
 return;
}

void TrTuple::Insert( int i, const TrValue& x )
{
 values.Insert( i, new TrValue(x) );
 return;
}

void TrTuple::Print( const Solarix::Dictionary &dict, lem::OFormatter &out, const TrValuePrinterDecorator *decorator ) const
{
 if( decorator==NULL )
  out.printf( "%vf6{%vn");
 else
  decorator->OpenTuple(*this,out);

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  {
   if( i>0 )
    {
     if( decorator==NULL )
      out.printf( "%vf6,%vn" );
     else
      decorator->NextTupleItem(*this,out);
    }

   values[i]->Print(dict,out,decorator);
  }

 if( decorator==NULL )
  out.printf( "%vf6}%vn");
 else
  decorator->CloseTuple(*this,out);

 return;
}

// *************************************************************
// Наш список полностью содержится в y,
// то есть у нас нет элементов, которые отсутствуют в y.
// Порядок элементов роли не играет.
// *************************************************************
bool TrTuple::In_Y( const TrTuple &y ) const
{
 if( values.size() > y.values.size() )
  return false;

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  {
   if( !y.Find( *values[i] ) )
    return false;
  }

 return true;
}


int TrTuple::Find( const TrValue& x ) const
{
 for( lem::Container::size_type i=0; i<values.size(); ++i )
  {
   if( values[i]->eq(x) )
    return i;
  }

 return UNKNOWN;
}

void TrTuple::Clear(void)
{
 values.clear();
}

void TrTuple::PrintXML( lem::OFormatter &xml, const Solarix::Dictionary &dict ) const
{
 xml.printf( "<tuple count=\"%d\">\n", CastSizeToInt(values.size()) );

 for( lem::Container::size_type i=0; i<values.size(); ++i )
  {
   xml.printf( "<item n=\"%d\">", CastSizeToInt(i) );
   values[i]->PrintXML( xml, dict );
   xml.printf( "</item>\n" );
  }

 xml.printf( "</tuple>\n" );

 return;
}


#endif
