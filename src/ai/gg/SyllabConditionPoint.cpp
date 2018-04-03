#include <lem/WideStringUcs4.h>
#include <lem/macro_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/SyllabRule.h>

using namespace Solarix;


SyllabConditionPoint::SyllabConditionPoint(void)
{
    id_class = id_entry = id_coord0 = id_state0 = UNKNOWN;
    is_left_boundary = is_right_boundary = false;
    is_positive = true;
    return;
}


SyllabConditionPoint::SyllabConditionPoint(
    const lem::MCollect<lem::uint32_t> &ucs4,
    int _id_class,
    int _id_entry,
    int _id_coord0,
    int _id_state0,
    bool _is_left_boundary,
    bool _is_right_boundary,
    bool _is_positive
)
    : codes(ucs4), id_class(_id_class), id_entry(_id_entry), id_coord0(_id_coord0), id_state0(_id_state0),
    is_left_boundary(_is_left_boundary), is_right_boundary(_is_right_boundary), is_positive(_is_positive)
{
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SyllabConditionPoint::LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict)
{
    lem::Iridium::BethToken t = txtfile.read();

    if (t.GetToken() == B_NEGATIVE)
    {
        is_positive = false;
        t = txtfile.read();
    }

    GraphGram & alphabet = dict.GetGraphGram();

    if (t.string().front() == L'\'' && t.string().back() == L'\'')
    {
        if (t.string().length() != 3)
        {
            lem::Iridium::Print_Error(t, txtfile);
            dict.GetIO().merr().printf("Error in %us: character definition must have length=1\n", t.c_str());
            throw lem::E_BaseException();
        }

        lem::WideStringUcs4 convertor(t.c_str());
        codes.push_back(convertor.Fetch());
    }
    else if (t.GetToken() == B_OROUNDPAREN)
    {
        while (!txtfile.eof())
        {
            lem::Iridium::BethToken t_ch = txtfile.read();
            lem::UCString ch = t_ch.string();
            ch.strip_apostrophes();

            lem::WideStringUcs4 convertor(ch.c_str());
            codes.push_back(convertor.Fetch());

            if (txtfile.probe(B_CROUNDPAREN))
                break;

            txtfile.read_it(B_COMMA);
        }
    }
    else if (t.eqi(L"begin"))
    {
        is_left_boundary = true;
    }
    else if (t.eqi(L"end"))
    {
        is_right_boundary = true;
    }
    else
    {
        if (t.GetToken() != B_ANY)
        {
            lem::Iridium::BethToken t_class = txtfile.read();
            id_class = alphabet.FindClass(t_class.string());
            if (id_class == UNKNOWN)
            {
                lem::Iridium::Print_Error(t_class, txtfile);
                dict.GetIO().merr().printf("Unknown character class %us\n", t_class.c_str());
                throw lem::E_BaseException();
            }

            txtfile.read_it(B_COLON);

            lem::Iridium::BethToken t_entry = txtfile.read();
            if (t_entry.GetToken() != B_ANY)
            {
                const lem::UCString & ename = t_entry.string();
                id_entry = alphabet.entries().FindEntry(ename.front(), id_class);
                if (id_entry == UNKNOWN)
                {
                    lem::Iridium::Print_Error(t_class, txtfile);
                    dict.GetIO().merr().printf("Entry %us:%us is not found\n", t_class.c_str(), ename.c_str());
                    throw lem::E_BaseException();
                }
            }
        }

        txtfile.read_it(B_OFIGPAREN);

        if (!txtfile.probe(B_CFIGPAREN))
        {
            lem::Iridium::BethToken t_coord = txtfile.read();
            txtfile.read_it(B_COLON);
            lem::Iridium::BethToken t_state = txtfile.read();

            id_coord0 = alphabet.FindCoord(t_coord.string()).GetIndex();
            if (id_coord0 == UNKNOWN)
            {
                lem::Iridium::Print_Error(t_coord, txtfile);
                dict.GetIO().merr().printf("Coordinate %us is not found\n", t_coord.c_str());
                throw lem::E_BaseException();
            }

            id_state0 = alphabet.coords()[id_coord0].FindState(t_state.string());
            if (id_state0 == UNKNOWN)
            {
                lem::Iridium::Print_Error(t_coord, txtfile);
                dict.GetIO().merr().printf("Coordinate state %us:%us is not found\n", t_coord.c_str(), t_state.c_str());
                throw lem::E_BaseException();
            }

            txtfile.read_it(B_CFIGPAREN);
        }
    }

    return;
}
#endif


void SyllabConditionPoint::Store(AlphabetStorage * storage, int id_rule, int point_index) const
{
    storage->StoreSyllabConditionPoint(
        id_rule,
        point_index,
        codes,
        id_class,
        id_entry,
        id_coord0, id_state0,
        is_left_boundary, is_right_boundary,
        is_positive
    );

    return;
}

bool SyllabConditionPoint::Check(const SyllabContext &ctx, int cursor_pos) const
{
    const SyllabContextPoint &p = ctx.GetPoint(cursor_pos);

    if (is_left_boundary)
        return Positive(p.IsLeftBoundary());

    if (is_right_boundary)
        return Positive(p.IsRightBoundary());

    if (!codes.empty())
    {
        return Positive(codes.find(p.GetNormalizedChar()) != UNKNOWN);
    }

    if (id_entry != UNKNOWN)
    {
        return Positive(p.GetEntryID() == id_entry);
    }

    if (id_class != UNKNOWN && p.GetClassID() != id_class)
        return Positive(false);

    if (id_coord0 != UNKNOWN && !p.FindPair(id_coord0, id_state0))
        return Positive(false);

    return Positive(true);
}

bool SyllabConditionPoint::Positive(bool r) const
{
    return is_positive ? r : !r; // is_positive ^^ r
}
