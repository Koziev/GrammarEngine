#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LA_UnbreakableRule.h>

using namespace Solarix;

LA_UnbreakableRule::LA_UnbreakableRule()
 : id_language(UNKNOWN), src_location(UNKNOWN)
{
}


LA_UnbreakableRule::LA_UnbreakableRule( int Id, const lem::UCString &Name, int Id_Lang,
 bool IsRegex, const lem::UFString &Pattern, int SourceID )
: id(Id), name(Name), id_language(Id_Lang), is_regex(IsRegex), pattern(Pattern), src_location(SourceID)
{
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_UnbreakableRule::LoadTxt( Macro_Parser &txtfile, Dictionary &dict )
{
 src_location = dict.GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );

 // опциональное имя
 while( !txtfile.eof() )
  {
   lem::Iridium::BethToken t0 = txtfile.read();
   if( t0.GetToken()==B_OFIGPAREN )
    break;
   else if( t0.GetToken()==B_LANGUAGE )
    {
     // дальше идет наименование языка, в рамках которого действует правило.
     txtfile.read_it( B_EQUAL ); 
     lem::Iridium::BethToken t1 = txtfile.read();
     id_language = dict.GetSynGram().Find_Language(t1.string());
     if( id_language==UNKNOWN )
      {
       lem::Iridium::Print_Error(t1,txtfile);
       dict.GetIO().merr().printf( "Unknown language name %us\n", t1.c_str() );
       throw lem::E_BaseException();
      }

     txtfile.read_it( B_OFIGPAREN );
     break;
    }
   else if( name.empty() )
    {
     // просто имя правила
     name = t0.string();
    }
   else
    {
     lem::Iridium::Print_Error(t0,txtfile);
     dict.GetIO().merr().printf( "Unexpected token %us\n", t0.c_str() );
     throw lem::E_BaseException();
    }
  }

 is_regex = txtfile.probe(L"~");

 pattern = txtfile.read().GetFullStr();
 pattern.strip(L'"'); 

 txtfile.read_it( B_CFIGPAREN );

 return;
}
#endif
