// экспортирует все состояния заданной координаты из словоформы, кроме тех, которые
// имеются у указанных маркировок. Это используется для вычитания использованной валентности, например
// для глаголов.
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

ExportCoordFunction_Except::ExportCoordFunction_Except() : ExportCoordFunction(ExportCoordFunction::ECF_Except), export_coord_id(UNKNOWN)
{
}

#if defined SOL_COMPILER && defined SOL_LOADTXT
void ExportCoordFunction_Except::LoadTxt(
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    const SynPatterns & pattern_declarations,
    SynPatternCompilation & compilation_context,
    const SynPatternPoint & point
)
{
    // Формат:
    // @except( [источник:]ПАДЕЖВАЛ, дополнение1:ПАДЕЖ, дополнение2:ПАДЕЖ ... )
    txtfile.read_it(B_OROUNDPAREN);

    const lem::Iridium::BethToken & t0 = txtfile.read();
    const int src_id = compilation_context.Find(t0.string());
    if (src_id == UNKNOWN)
    {
        txtfile.seekp(t0);
    }
    else
    {
        export_source = lem::to_upper(t0.string());
        txtfile.read_it(B_COLON);
    }


    export_coord_id = dict.GetSynGram().LoadCoordIdTxt(txtfile, false).GetIndex();
    while (!txtfile.eof())
    {
        if (!txtfile.probe(B_COMMA))
            break;

        const lem::Iridium::BethToken & t1 = txtfile.read();
        if (txtfile.probe(B_COLON))
        {
            if (t1.string() != L'_')
            {
                marker_name.push_back(lem::to_upper(t1.string()));

                const int i_marker = compilation_context.Find(t1.string());
                if (i_marker == UNKNOWN)
                {
                    dict.GetIO().merr().printf("Unknown marker '%us'\n", t1.string().c_str());
                    lem::Iridium::Print_Error(t1, txtfile);
                    throw lem::E_BaseException();
                }
            }
            else
            {
                marker_name.push_back(L"");
            }
        }
        else
        {
            marker_name.push_back(L"");
            txtfile.seekp(t1);
        }

        const int coord2_id = dict.GetSynGram().LoadCoordIdTxt(txtfile, false).GetIndex();

        subtract_coord_id.push_back(coord2_id);
    }

    txtfile.read_it(B_CROUNDPAREN);

    return;
}
#endif


ExportCoordFunction* ExportCoordFunction_Except::Clone()
{
    ExportCoordFunction_Except * res = new ExportCoordFunction_Except();
    res->export_source = export_source;
    res->export_coord_id = export_coord_id;
    res->marker_name = marker_name;
    res->subtract_coord_id = subtract_coord_id;
    return res;
}

bool ExportCoordFunction_Except::Equals(const ExportCoordFunction & y) const
{
    const ExportCoordFunction_Except & yy = (const ExportCoordFunction_Except&)y;

    return export_source == yy.export_source &&
        export_coord_id == yy.export_coord_id &&
        marker_name == yy.marker_name &&
        subtract_coord_id == yy.subtract_coord_id;
}

void ExportCoordFunction_Except::SaveBin(lem::Stream & bin) const
{
    ExportCoordFunction::SaveBin(bin);
    bin.write(&export_source, sizeof(export_source));
    bin.write(&export_coord_id, sizeof(export_coord_id));
    marker_name.SaveBin(bin);
    subtract_coord_id.SaveBin(bin);
    return;
}

void ExportCoordFunction_Except::LoadBin(lem::Stream & bin)
{
    bin.read(&export_source, sizeof(export_source));
    bin.read(&export_coord_id, sizeof(export_coord_id));
    marker_name.LoadBin(bin);
    subtract_coord_id.LoadBin(bin);
    return;
}


#if defined SOL_CAA
void ExportCoordFunction_Except::Run(SynPatternResult & dest, const PatternExportFuncContext & context) const
{
    lem::MCollect<int> state_ids;

    if (export_source.empty())
        context.GetCoordStates(export_coord_id, state_ids);
    else
        context.GetCoordStates(export_source, export_coord_id, state_ids);

    for (lem::Container::size_type i = 0; i < marker_name.size(); ++i)
    {
        context.SubtractMarkedNodeCoordStates(marker_name[i], subtract_coord_id[i], state_ids);
    }

    dest.ResetCoordStates(export_coord_id, state_ids);

    return;
}
#endif

