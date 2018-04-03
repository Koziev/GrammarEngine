#include <lem/macro_parser.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/SyllabRule.h>

using namespace Solarix;


SyllabResult::SyllabResult(void)
{
    cursor_shift = UNKNOWN;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void SyllabResult::LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict, const SyllabCondition &condition)
{
    txtfile.read_it(B_OFIGPAREN);

    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CFIGPAREN))
            break;

        SyllabResultPoint *point = new SyllabResultPoint();
        point->LoadTxt(txtfile, dict, condition);
        points.push_back(point);
    }

    txtfile.read_it(B_RSHIFT);
    cursor_shift = txtfile.read_int();

    return;
}
#endif


void SyllabResult::Store(AlphabetStorage * storage, int id_rule) const
{
    for (lem::Container::size_type i = 0; i < points.size(); ++i)
    {
        points[i]->Store(storage, id_rule, CastSizeToInt(i));
    }

    return;
}


void SyllabResult::Load(AlphabetStorage * storage, int id_rule, int _cursor_shift)
{
    cursor_shift = _cursor_shift;

    lem::Ptr<LS_ResultSet> rs(storage->ListSyllabResultPointsForRule(id_rule));
    while (rs->Fetch())
    {
        const int copy_index = rs->GetInt(0);
        const int merge_index0 = rs->GetInt(1);
        const int merge_count = rs->GetInt(2);

        SyllabResultPoint * point = new SyllabResultPoint(copy_index, merge_index0, merge_count);
        points.push_back(point);
    }

    return;
}



void SyllabResult::Produce(SyllabContext & ctx, int cursor_pos, lem::MCollect<SyllabContextPoint*> &new_points) const
{
    for (auto point : points)
    {
        SyllabContextPoint * new_point = point->Produce(ctx, cursor_pos);
        new_points.push_back(new_point);
    }

    return;
}

