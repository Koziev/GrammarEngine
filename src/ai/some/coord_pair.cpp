// -----------------------------------------------------------------------------
// File COORD_PAIR.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                https://github.com/Koziev/GrammarEngine
// 
// Класс GramCoordPair - координатная пара, используется как в словоформах
// статей, так и в модулях ЦАА.
// -----------------------------------------------------------------------------
//
// CD->19.06.1996
// LC->02.04.2018
// --------------

#include <lem/streams.h>
#include <lem/oformatter.h>
#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/grammar.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/coord_pair.h>

using namespace lem;
using namespace Solarix;

#if defined SOL_LOADTXT
void GramCoordPair::LoadTxt(Macro_Parser &txtfile, const Grammar &gram)
{
    bool affirm = true; // Для бистабильных координат

    BethToken coord_name = txtfile.read();

    if (coord_name.GetToken() == B_NEGATIVE)
    {
        affirm = false;
        coord_name = txtfile.read();
    }

    icoord = gram.FindCoord(coord_name.string());
    if (icoord.GetIndex() == UNKNOWN)
    {
        lem::Iridium::Print_Error(coord_name, txtfile);
        gram.GetIO().merr().printf(
            "The coordinate [%us] is not previously declared in grammar\n"
            , coord_name.c_str()
        );
        throw E_ParserError();
    }

    if (!gram.coords()[icoord.GetIndex()].states().size())
    {
        istate = affirm;
        return;
    }

    if (affirm == false)
    {
        lem::Iridium::Print_Error(coord_name, txtfile);
        gram.GetIO().merr().printf("Negation is firbiden in [%us]\n", coord_name.c_str());
        throw E_ParserError();
    }

    txtfile.read_it(B_COLON);
    const BethToken state_name = txtfile.read();
    if ((istate = gram.coords()[icoord.GetIndex()].FindState(state_name.string())) == UNKNOWN)
    {
        gram.GetIO().merr().printf(
            "State [%us] is not declared for coordinate [%us]\n"
            , state_name.c_str(), coord_name.c_str()
        );

        lem::Iridium::Print_Error(state_name, txtfile);
        throw E_ParserError();
    }

    return;
}
#endif

void GramCoordPair::SaveTxt(
    OFormatter &txtfile,
    const Grammar &gram
) const
{
    const GramCoord &c = gram.coords()[icoord.GetIndex()];
    if (c.IsBistable())
    {
        if (istate)
            txtfile << c.GetName().front();
        else
            txtfile << sol_get_token(B_NEGATIVE) << c.GetName().front();
    }
    else
    {
        txtfile << c.GetName().front() << sol_get_token(B_COLON) << c.GetStateName(istate);
    }

    return;
}


CP_Array::CP_Array(int n0)
    :MCollect<GramCoordPair>(n0)
{}



CP_Array::CP_Array(const CPE_Array &x)
{
    for (lem::Container::size_type i = 0; i < x.size(); ++i)
        push_back(x[i]);

    return;
}



/*****************************************************************
  Двухпроходный поиск координатного индекса в списке.

  В первый проход пытаемся найти в списке ТОЧНО такой же индекс,
  как и ca. Если это не удалось, пытаемся найти структуру с равным
  полем icoord, не обращаяя внимания на номер синонима.
******************************************************************/
int CP_Array::FindTwice(const GramCoordAdr& ca) const
{
    const int ires = FindOnce(ca);
    if (ires != UNKNOWN)
        return ires;

    for (Container::size_type i = 0; i < size(); i++)
    {
        if (get(i).GetCoord().GetIndex() == ca.GetIndex())
            return i;
    }

    return UNKNOWN;
}

int CP_Array::FindOnce(const GramCoordAdr& ca) const
{
    // Первый проход сравнения.
    for (Container::size_type i = 0; i < size(); i++)
    {
        if (get(i).GetCoord() == ca)
            return i;
    }

    return UNKNOWN;
}

void CP_Array::RemoveStates(const GramCoordAdr& ca)
{
    int i = CastSizeToInt(size()) - 1;
    while (i >= 0)
    {
        if (get(i).GetCoord() == ca)
            Remove(i);

        i--;
    }

    return;
}


#if defined SOL_LOADTXT
// Загружаем список координатных пар до токена } (курсор будет после него)
void CP_Array::LoadTxt(Macro_Parser &txtfile, const Grammar &gram)
{
    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CFIGPAREN))
            break;

        Solarix::GramCoordPair p;
        p.LoadTxt(txtfile, gram);
        push_back(p);
    }

    return;
}
#endif


void CP_Array::SaveTxt(OFormatter &txtfile, const Grammar &gram) const
{
    txtfile.printf('{');

    for (Container::size_type i = 0; i < size(); i++)
    {
        txtfile.printf(' ');
        get(i).SaveTxt(txtfile, gram);
    }

    txtfile.printf(" }");
    return;
}

void CP_Array::Parse(const lem::UFString &str)
{
    lem::Collect<lem::UFString> t2;
    lem::Collect<UFString> t3;
    lem::parse(str, t2, L" ");
    for (lem::Container::size_type i = 0; i < t2.size(); ++i)
    {
        const lem::UFString &s2 = t2[i];
        t3.clear();
        lem::parse(s2.c_str(), t3, L":");
        LEM_CHECKIT_Z(t3.size() == 2);
        if (t3.size() == 2)
        {
            const int id_coord = lem::to_int(t3[0]);
            const int id_state = lem::to_int(t3[1]);
            push_back(Solarix::GramCoordPair(id_coord, id_state));
        }
    }

    return;
}
