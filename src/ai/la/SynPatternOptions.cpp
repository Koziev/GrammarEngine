#if defined SOL_LOADTXT && defined SOL_COMPILER

// CD->27.06.2011
// LC->29.09.2013

#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

SynPatternOptions::SynPatternOptions()
{
 id_language = UNKNOWN;
 greedy = false;
 bottomup = false;
 return;
}


void SynPatternOptions::LoadTxt(
                                Dictionary &dict,
                                lem::Iridium::Macro_Parser & txtfile
                               )
{
 name = txtfile.read().string();
 greedy = false;
 bottomup = false;

 if( txtfile.probe( B_OFIGPAREN ) )
  {
   // далее идут опции.
   while( !txtfile.eof() )
    {
     if( txtfile.probe( B_CFIGPAREN ) )
      break;

     if( txtfile.probe(B_LANGUAGE) )
      {
       txtfile.read_it( B_EQUAL );
       
       lem::Iridium::BethToken lang = txtfile.read();
       id_language = dict.GetSynGram().Find_Language(lang.string());
       if( id_language==UNKNOWN )
        {
         lem::Iridium::Print_Error(lang,txtfile);
         dict.GetIO().merr().printf( "Unknown language name %us\n", lang.c_str() );
         throw lem::E_BaseException();
        }     

       continue;
      }

     lem::Iridium::BethToken opt = txtfile.read();
     if( opt.string().eqi(L"greedy") )
      {
       greedy=true;
      }
     else if( opt.string().eqi(L"bottomup") )
      {
       bottomup=true;
      }
     else
      {
       dict.GetIO().merr().printf( "Unknown pattern option [%us]\n", opt.string().c_str() );
       lem::Iridium::Print_Error(opt,txtfile);
       throw lem::E_BaseException();
      }
    }
  }

 if( txtfile.probe( L"export" ) )
  export_info.LoadTxt( dict, txtfile ); 

 return;
}

#endif
