#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

ExportCoordFunction_Add::ExportCoordFunction_Add() : ExportCoordFunction( ExportCoordFunction::ECF_Add ) 
{}


ExportCoordFunction* ExportCoordFunction_Add::Clone()
{
 ExportCoordFunction_Add * res = new ExportCoordFunction_Add();
 res->pair = pair;
 return res;
}


#if defined SOL_COMPILER && defined SOL_LOADTXT
void ExportCoordFunction_Add::LoadTxt(
                                      Dictionary &dict,
                                      lem::Iridium::Macro_Parser & txtfile,
                                      const SynPatterns & pattern_declarations,
                                      SynPatternCompilation & compilation_context,
                                      const SynPatternPoint & point
                                     )
{
 txtfile.read_it( B_OROUNDPAREN );
 pair.LoadTxt( txtfile, dict.GetSynGram() );
 txtfile.read_it( B_CROUNDPAREN );
 return;
}
#endif


bool ExportCoordFunction_Add::Equals( const ExportCoordFunction & y ) const
{
 const ExportCoordFunction_Add & yy = (const ExportCoordFunction_Add&)y;
 return yy.pair == pair;
}


void ExportCoordFunction_Add::SaveBin( lem::Stream & bin ) const
{
 ExportCoordFunction::SaveBin(bin);
 bin.write( &pair, sizeof(pair) );
 return;
}


void ExportCoordFunction_Add::LoadBin( lem::Stream & bin )
{
 bin.read(&pair,sizeof(pair));
 return;
}



#if defined SOL_CAA
void ExportCoordFunction_Add::Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const
{
 std::pair<int,int> p( pair.GetCoord().GetIndex(), pair.GetState() );

 typedef EXPORTED_COORDS::const_iterator IT;
 std::pair<IT,IT> pit = dest.exported_coords.equal_range( pair.GetCoord().GetIndex() );
 bool found=false;
 for( IT it=pit.first; it!=pit.second; ++it )
 if( it->second==pair.GetState() )
  {
   found=true;
   break;
  }

 if( !found )
  dest.exported_coords.insert( p );

 return;
}
#endif

