#include <lem/macro_parser.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/SyllabRule.h>

using namespace Solarix;


SyllabCondition::SyllabCondition(void)
{
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void SyllabCondition::LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict)
{
    txtfile.read_it(B_OFIGPAREN);

    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CFIGPAREN))
            break;

        SyllabConditionPoint *point = new SyllabConditionPoint();
        point->LoadTxt(txtfile, dict);
        points.push_back(point);
    }

    return;
}
#endif


void SyllabCondition::Store(AlphabetStorage * storage, int id_rule) const
{
    for (lem::Container::size_type i = 0; i < points.size(); ++i)
    {
        points[i]->Store(storage, id_rule, CastSizeToInt(i));
    }

    return;
}



void SyllabCondition::Load(AlphabetStorage * storage, int id_rule)
{
    lem::Ptr<LS_ResultSet> rs(storage->ListSyllabConditionPointsForRule(id_rule));
    while (rs->Fetch())
    {
        lem::UFString chars = rs->GetUFString(0);
        const int id_class = rs->GetInt(1);
        const int id_entry = rs->GetInt(2);
        const int id_coord0 = rs->GetInt(3);
        const int id_state0 = rs->GetInt(4);
        const bool is_left_boundary = rs->GetInt(5) == 1;
        const bool is_right_boundary = rs->GetInt(6) == 1;
        const bool is_positive = rs->GetInt(7) == 1;

        lem::Collect<lem::UFString> char_codes;
        lem::parse(chars, char_codes, L" ");
        lem::MCollect<lem::uint32_t> ucs4;
        for (lem::Container::size_type i = 0; i < char_codes.size(); ++i)
        {
            lem::uint32_t code = lem::to_int(char_codes[i]);
            ucs4.push_back(code);
        }

        SyllabConditionPoint * point = new SyllabConditionPoint(ucs4, id_class, id_entry, id_coord0, id_state0, is_left_boundary, is_right_boundary, is_positive);
        points.push_back(point);
    }

    return;
}




bool SyllabCondition::Check(const SyllabContext &ctx, int cursor_pos) const
{
    bool res = true;

    for (lem::Container::size_type i = 0; i < points.size(); ++i)
    {
        if (!points[i]->Check(ctx, cursor_pos + CastSizeToInt(i)))
        {
            res = false;
            break;
        }
    }

    return res;
}
