// добавляет в экспорт заданную пару, если в экспорте есть состояние заданной координаты
// пример использования: экспортировать признак переходности, если после экспорта с фильтрацией валентностей
// в экспорт попала хоть одна валентность.
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;


ExportCoordFunction_IfExported::ExportCoordFunction_IfExported() : ExportCoordFunction( ExportCoordFunction::ECF_IfExported ), trigger_coord(UNKNOWN)
{
}

ExportCoordFunction* ExportCoordFunction_IfExported::Clone()
{
 ExportCoordFunction_IfExported * res = new ExportCoordFunction_IfExported();

 res->export_pair = export_pair;
 res->trigger_coord = trigger_coord;

 return res;
}


#if defined SOL_COMPILER && defined SOL_LOADTXT
void ExportCoordFunction_IfExported::LoadTxt(
                                             Dictionary &dict,
                                             lem::Iridium::Macro_Parser & txtfile,
                                             const SynPatterns & pattern_declarations,
                                             SynPatternCompilation & compilation_context,
                                             const SynPatternPoint & point
                                            )
{
 // формат: @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
 txtfile.read_it( B_OROUNDPAREN );

 // какая будет экспортирована
 export_pair.LoadTxt( txtfile, dict.GetSynGram() );

 txtfile.read_it( B_COMMA );

 // если в экспорте уже есть вот эта
 trigger_coord = dict.GetSynGram().LoadCoordIdTxt( txtfile, false ).GetIndex();

 txtfile.read_it( B_CROUNDPAREN );
 return;
}
#endif

bool ExportCoordFunction_IfExported::Equals( const ExportCoordFunction & y ) const
{
 const ExportCoordFunction_IfExported & yy = (const ExportCoordFunction_IfExported&)y;
 return yy.trigger_coord == trigger_coord && yy.export_pair == export_pair;
}

void ExportCoordFunction_IfExported::SaveBin( lem::Stream & bin ) const
{
 ExportCoordFunction::SaveBin(bin);
 bin.write( &trigger_coord, sizeof(trigger_coord) );
 bin.write( &export_pair, sizeof(export_pair) );
 return;
}


void ExportCoordFunction_IfExported::LoadBin( lem::Stream & bin )
{
 bin.read( &trigger_coord, sizeof(trigger_coord) );
 bin.read( &export_pair, sizeof(export_pair) );
 return;
}


#if defined SOL_CAA
void ExportCoordFunction_IfExported::Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const
{
 typedef EXPORTED_COORDS::const_iterator IT;
 IT it = dest.exported_coords.find( trigger_coord );
 if( it!=dest.exported_coords.end() )
  dest.exported_coords.insert( std::make_pair( export_pair.GetCoord().GetIndex(), export_pair.GetState() ) );

 return;
}
#endif

