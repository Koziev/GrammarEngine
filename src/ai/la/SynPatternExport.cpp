// CD->13.06.2012

#if defined SOL_LOADTXT && defined SOL_COMPILER

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/SG_Coordinates.h>
#include <lem/solarix/PatternLinks.h>
#include <lem/solarix/PatternNGrams.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

SynPatternExport::SynPatternExport(void)
{}




SynPatternExport::SynPatternExport( const SynPatternExport &x )
 : export_coords(x.export_coords), null_export_coords(x.null_export_coords),
   export_nodes(x.export_nodes), null_export_nodes(x.null_export_nodes)
{
}



void SynPatternExport::operator=( const SynPatternExport &x )
{
 export_coords = x.export_coords;
 null_export_coords = x.null_export_coords;
 export_nodes = x.export_nodes;
 null_export_nodes = x.null_export_nodes;
 return;
}



void SynPatternExport::LoadTxt(
                               Dictionary &dict,
                               lem::Iridium::Macro_Parser & txtfile
                              )
{
 txtfile.read_it( B_OFIGPAREN );

 while( !txtfile.eof() )
  {
   bool null_export = txtfile.probe( B_OROUNDPAREN );
   lem::Iridium::BethToken coord_name = txtfile.read();
 
   if( coord_name.GetToken()==B_CFIGPAREN )
    break;

   if( coord_name.string().eqi( L"node" ) )
    {
     txtfile.read_it( B_COLON );
     lem::Iridium::BethToken t_node_name = txtfile.read();
     lem::UCString node_name = t_node_name.string();
     node_name.to_upper();

     if( export_nodes.find(node_name)!=UNKNOWN )
      {
       dict.GetIO().merr().printf( "Wordform %us is already mentioned in export section\n", t_node_name.string().c_str() );
       lem::Iridium::Print_Error(t_node_name,txtfile);
       throw lem::E_BaseException();
      }

     export_nodes.push_back( node_name );
     null_export_nodes.push_back( null_export ? 1 : 0 );

     if( null_export )
      txtfile.read_it( B_CROUNDPAREN );

     continue;
    }

   const GramCoordAdr iglob_coord = dict.GetSynGram().FindCoord(coord_name.string());
 
   if( !iglob_coord.IsDefined() )
    {
     dict.GetIO().merr().printf( "Unknown coordinate %us\n", coord_name.c_str() );
     lem::Iridium::Print_Error(coord_name,txtfile);
     throw lem::E_BaseException();
    }
 
   if( export_coords.find( iglob_coord.GetIndex() )!=UNKNOWN )
    {
     dict.GetIO().merr().printf( "Coordinate %us is already mentioned in export section\n", coord_name.c_str() );
     lem::Iridium::Print_Error(coord_name,txtfile);
     throw lem::E_BaseException();
    }
 
   export_coords.push_back(iglob_coord.GetIndex());
   null_export_coords.push_back( null_export ? 1 : 0 );

   if( null_export )
    txtfile.read_it( B_CROUNDPAREN );
  }

 return;
}




void SynPatternExport::RegisterExport( SynPatternCompilation &compilation_context )
{
 for( lem::Container::size_type i=0; i<export_nodes.size(); ++i )
  compilation_context.AddExportNode( export_nodes[i], null_export_nodes[i]==1 );

 for( lem::Container::size_type i=0; i<export_coords.size(); ++i )
  compilation_context.AddExportCoord( export_coords[i], null_export_coords[i]==1 );
 
 return;
}




bool SynPatternExport::Empty(void) const
{
 return export_coords.empty() && export_nodes.empty();
}


// ¬ернет true, если указанна€ координата присутствует в списке экспортируемых.
bool SynPatternExport::ContainsCoord( int CoordID ) const
{
 LEM_CHECKIT_Z( CoordID!=UNKNOWN );
 return export_coords.find(CoordID)!=UNKNOWN;
}



#endif
