// экспортирует заданную координатную пару, если она есть в словоформе
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

ExportCoordFunction_IfContains::ExportCoordFunction_IfContains() : ExportCoordFunction( ExportCoordFunction::ECF_IfContains ) 
{}


ExportCoordFunction* ExportCoordFunction_IfContains::Clone()
{
 ExportCoordFunction_IfContains * res = new ExportCoordFunction_IfContains();
 res->pair = pair;
 return res;
}


#if defined SOL_COMPILER && defined SOL_LOADTXT
void ExportCoordFunction_IfContains::LoadTxt(
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


bool ExportCoordFunction_IfContains::Equals( const ExportCoordFunction & y ) const
{
 const ExportCoordFunction_IfContains & yy = (const ExportCoordFunction_IfContains&)y;
 return yy.pair == pair;
}


void ExportCoordFunction_IfContains::SaveBin( lem::Stream & bin ) const
{
 ExportCoordFunction::SaveBin(bin);
 bin.write( &pair, sizeof(pair) );
 return;
}


void ExportCoordFunction_IfContains::LoadBin( lem::Stream & bin )
{
 bin.read(&pair,sizeof(pair));
 return;
}



#if defined SOL_CAA
void ExportCoordFunction_IfContains::Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const
{
 if( context.ContainsCoordPair( pair ) )
  dest.exported_coords.insert( std::make_pair( pair.GetCoord().GetIndex(), pair.GetState() ) );

 return;
}
#endif

