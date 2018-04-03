#include <lem/oformatter.h>
#include <lem/Ucs4ToWideString.h>
#include <lem/solarix/SyllabRule.h>

using namespace Solarix;

SyllabContextPoint::SyllabContextPoint()
    : is_syllab(false), is_left_boundary(false), is_right_boundary(false),
    char_ucs4(0), normalized_char_ucs4(0), id_entry(UNKNOWN), id_class(UNKNOWN)
{}


lem::UCString SyllabContextPoint::BuildSyllab(bool Normalized) const
{
    if (is_syllab)
        return Normalized ? normalized_syllab : syllab;

    lem::Ucs4ToUCString ucs42wchar;
    ucs42wchar.Add(Normalized ? normalized_char_ucs4 : char_ucs4);
    return ucs42wchar.ToString();
}


SyllabContextPoint::SyllabContextPoint(const SyllabContextPoint &x)
    : is_syllab(x.is_syllab), is_left_boundary(x.is_left_boundary), is_right_boundary(x.is_right_boundary),
    syllab(x.syllab), normalized_syllab(x.normalized_syllab), char_ucs4(x.char_ucs4), normalized_char_ucs4(x.normalized_char_ucs4),
    id_entry(x.id_entry), id_class(x.id_class), coords(x.coords)
{
}


void SyllabContextPoint::Print(lem::OFormatter &to) const
{
    if (is_left_boundary)
        to.printf("[$BEGIN");
    else if (is_right_boundary)
        to.printf("$END]");
    else
        to.printf("%us", BuildSyllab(false).c_str());

    return;
}



bool SyllabContextPoint::FindPair(int id_coord, int id_state) const
{
    for (lem::Container::size_type i = 0; i < coords.size(); ++i)
    {
        if (coords[i].GetCoord().GetIndex() == id_coord && coords[i].GetState() == id_state)
            return true;
    }

    return false;
}

SyllabContextGroup::SyllabContextGroup(const SyllabContext & ctx, int merge_index0, int merge_count)
{
    LEM_CHECKIT_Z(merge_index0 >= 0);
    LEM_CHECKIT_Z(merge_count > 0);
    LEM_CHECKIT_Z((merge_index0 + merge_count) < ctx.Count());

    is_syllab = true;

    lem::Ucs4ToUCString ucs42wchar;

    for (int i = 0; i < merge_count; ++i)
        ucs42wchar.Add(ctx.GetPoint(merge_index0 + i).GetChar());

    syllab = ucs42wchar.ToString();

    ucs42wchar.Clear();
    for (int i = 0; i < merge_count; ++i)
        ucs42wchar.Add(ctx.GetPoint(merge_index0 + i).GetNormalizedChar());

    normalized_syllab = ucs42wchar.ToString();


    return;
}


SyllabContextSymbol::SyllabContextSymbol(lem::uint32_t ucs4, lem::uint32_t normalized_ucs4, int _id_entry, int _id_class, const lem::MCollect<GramCoordPair> &_coords)
{
    char_ucs4 = ucs4;
    normalized_char_ucs4 = normalized_ucs4;
    id_entry = _id_entry;
    id_class = _id_class;
    coords = _coords;
    return;
}

SyllabContextUnknownSymbol::SyllabContextUnknownSymbol(lem::uint32_t ucs4)
{
    char_ucs4 = normalized_char_ucs4 = ucs4;
}

