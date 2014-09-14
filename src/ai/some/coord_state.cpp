// -----------------------------------------------------------------------------
// File COORD_STATE.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine
// Состояние координаты - class GramCoordState.
// 26.10.2011 - добавлена генерация экспортного модуля для PHP
// -----------------------------------------------------------------------------
//
// CD->24.03.1996
// LC->26.10.2011
// --------------

#include <lem/config.h>

#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/coordinate.h>

using namespace Solarix;


GramCoordState::GramCoordState(void):UCStringSet(), weight(1) {}

GramCoordState::GramCoordState( const GramCoordState &x ) : UCStringSet(x)
#if defined SOL_LOADTXT
, c_name( x.c_name), weight(x.weight), c_names(x.c_names)
#else
, weight(1)
#endif
{}


GramCoordState::GramCoordState( const lem::UCString &name )
 : weight(1)
{
 UCStringSet::Add(name);
}

GramCoordState::GramCoordState( const lem::UCString &name, int w )
 : weight(w)
{
 UCStringSet::Add(name);
}


void GramCoordState::operator=( const GramCoordState &x )
{
 UCStringSet::operator=(x);
 weight = x.weight;
 #if defined SOL_LOADTXT
 c_name = x.c_name;
 c_names = x.c_names;
 #endif
 return;
} 


#if defined SOL_LOADTXT
void GramCoordState::LoadTxt( const Sol_IO &io, Macro_Parser &txtfile )
{
 LoadSubstates(io,txtfile);

 while( !txtfile.eof() )
  {
   BethToken t = txtfile.read();

   if( t.GetToken() == B_AS )
    {
     c_name = txtfile.read();
     continue;
    }
   else if( t.GetToken() == B_EQUAL )
    {
     weight = txtfile.read_int();
     continue;
    }
   else
    {
     txtfile.backward();  
     break;
    }
  }

 return;
}


void GramCoordState::LoadSubstates( const Sol_IO &io, Macro_Parser &txtfile )
{
 BethToken t = txtfile.read();

 if( t.GetToken()!=B_OFIGPAREN )
  {
   Add(t.string(),1);
   c_names.push_back( UCString() );
  }
 else
  {
   while( !txtfile.eof() )
    {
     if( txtfile.eof() )
      {
       Print_Error(t,txtfile);
       io.merr().printf(
                        "End of file has been reached before "
                        "set of lexems completely loaded\n"
                       );
       LEM_STOPIT;
      }

     t = txtfile.read();

     if( t.GetToken()==B_CFIGPAREN )
      break;

     UCStringSet::Add(t.string(),1);

     if( txtfile.probe(B_AS) )
      {
       c_names.push_back( txtfile.read().string() ); 
      }
     else
      {
       c_names.push_back( UCString() );
      }
    }
  }

 return;
}

#endif

#if defined SOL_SAVEBIN
void GramCoordState::SaveBin( lem::Stream &bin ) const
{
 UCStringSet::Save_Packed(bin);
 bin.write_int(weight);
 return;
}
#endif


void GramCoordState::LoadBin( lem::Stream &bin )
{
 UCStringSet::Load_Packed(bin);
 weight = bin.read_int();
 return; 
}

#if defined SOL_COMPILER
void GramCoordState::Save_API( int istate0, OFormatter &cpp, lem::Binding::Language lang ) const
{
 for( lem::Container::size_type i=0; i<size(); ++i )
  if( !c_names[i].empty() )
   {
    const int idx = istate0 + CastSizeToInt(i);
    
     if( lang==lem::Binding::CPP || lang==lem::Binding::CSharp )
      {
       if( lang==lem::Binding::CSharp )
        cpp.printf( " public " );

       cpp.printf(
                  "const int %us = %d; %50t // %us\n", 
                  c_names[i].c_str(),
                  idx,
                  get(i).c_str()
                 );   
      }
     else if( lang==lem::Binding::Pascal )
      {
       cpp.printf(
                  "const %us: integer = %d; %50t // %us\n", 
                  c_names[i].c_str(),
                  idx,
                  get(i).c_str()
                 );
      }
     else if( lang==lem::Binding::Python )
      {
       cpp.printf(
                  "%us = %d %50t # %us\n", 
                  c_names[i].c_str(),
                  idx,
                  get(i).c_str()
                 );
      }
     else if( lang==lem::Binding::PHP )
      {
       cpp.printf(
                  "define( '%us', %d ); %50t # %us\n", 
                  c_names[i].c_str(),
                  idx,
                  get(i).c_str()
                 );
      }
     else
      {
       LEM_STOPIT;
      } 
   }


 return;
}
#endif

#if defined SOL_COMPILER
void GramCoordState::Clear_API_Names(void)
{
 c_name.clear();
 for( lem::Container::size_type i=0; i<c_names.size(); ++i )
  c_names[i].clear();

 return;
}
#endif
