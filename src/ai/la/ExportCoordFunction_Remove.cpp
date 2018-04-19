#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

ExportCoordFunction_Remove::ExportCoordFunction_Remove() : ExportCoordFunction(ExportCoordFunction::ECF_Remove)
{}


ExportCoordFunction* ExportCoordFunction_Remove::Clone()
{
    ExportCoordFunction_Remove * res = new ExportCoordFunction_Remove();
    res->pair = pair;
    return res;
}


#if defined SOL_COMPILER && defined SOL_LOADTXT
void ExportCoordFunction_Remove::LoadTxt(
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    const SynPatterns & pattern_declarations,
    SynPatternCompilation & compilation_context,
    const SynPatternPoint & point
)
{
    txtfile.read_it(B_OROUNDPAREN);
    pair.LoadTxt(txtfile, dict.GetSynGram());
    txtfile.read_it(B_CROUNDPAREN);
    return;
}
#endif


bool ExportCoordFunction_Remove::Equals(const ExportCoordFunction & y) const
{
    const ExportCoordFunction_Remove & yy = (const ExportCoordFunction_Remove&)y;
    return yy.pair == pair;
}


void ExportCoordFunction_Remove::SaveBin(lem::Stream & bin) const
{
    ExportCoordFunction::SaveBin(bin);
    bin.write(&pair, sizeof(pair));
    return;
}


void ExportCoordFunction_Remove::LoadBin(lem::Stream & bin)
{
    bin.read(&pair, sizeof(pair));
    return;
}



#if defined SOL_CAA
void ExportCoordFunction_Remove::Run(SynPatternResult & dest, const PatternExportFuncContext & context) const
{
    std::pair<int, int> p(pair.GetCoord().GetIndex(), pair.GetState());

    typedef EXPORTED_COORDS::const_iterator IT;
    std::pair<IT, IT> pit = dest.exported_coords.equal_range(pair.GetCoord().GetIndex());
    bool found = false;
    for (auto it = pit.first; it != pit.second; ++it)
    {
        if (it->second == pair.GetState())
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        // формируем новый список экспортируемых пар, исключая из него заданную для функции.
        EXPORTED_COORDS new_coords;
        for (auto it = dest.exported_coords.begin(); it != dest.exported_coords.end(); ++it)
        {
            if (it->first != pair.GetCoord().GetIndex() || it->second != pair.GetState())
                new_coords.insert(*it);
        }

        dest.exported_coords = new_coords;
    }

    return;
}
#endif

