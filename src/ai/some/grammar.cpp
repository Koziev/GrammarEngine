// -----------------------------------------------------------------------------
// File GRAMMAR.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project      http://www.solarix.ru
// LEM C++ library
//
// ����� Grammar - ��������� ��� ������� ����������. �� ������ ����� ������
// �������� ����������� � �������������� ����������.
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->03.04.2018
// --------------

#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/ClassEnumerator.h>
#include <lem/solarix/CoordEnumerator.h>
#include <lem/solarix/grammar.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;

Grammar::Grammar(int Index) :Automaton(Index)
{
    aclass = nullptr;
    coord = nullptr;
    ilink_type = UNKNOWN;
    return;
}


Grammar::~Grammar()
{
    lem_rub_off(aclass);
    lem_rub_off(coord);
    return;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
/**************************************************************************
   ����� Automaton ������ ��� ���������� ���������� � ������ t1 ������
 ��������� ������, ������� �� ����� ���������. ���� ��� ������� ����������
 � ���������, �� ���������� true. ���������� (��� ����� Grammar - �������
 ��� ���� ���������) ����������: ������, ����������, ������. ����������
 � ������ �� � ��������� ��������� ��������������, � ��� �� ��������
 �������, ��� ��� �� ������ ����������� ������� �� ���������� ����������.
 ������� �� �������� ����������� ����� LoadEntry, ������������ ������������
 ������ ���������� ��������� ���� ������.
***************************************************************************/
bool Grammar::ProcessLexem(
    const BethToken &T1,
    Macro_Parser &txtfile,
    const Binarization_Options &options
)
{
    /*--------------------------------------------------------------------------
     ����� ��������� ����� ���������� �������� �������, ������ �������
     ������ ����� ���� ��������. �� ���� ������ ����� ����������� ���:

                     ���_������ : ���_������ { ... }


     �������� ����� [entry] ������������. ����������� ������������� �������
     ������ ������������� �� ������ ������� ���� ������, ��������� �� ������
     ������. ��������������, ������ ��������� ����� ������, ����������� �
     ��������� ������� �������. ������������ ��������� ����� [entry] �����������
     � ��� �������, ����� ��� �������������, � ����� ��� ��������� ������
     ����������� ����������� ':'.
    --------------------------------------------------------------------------*/

    BethToken t1 = T1;
    BethToken t2 = txtfile.read();

    bool is_extern = false;
    if (t1.GetToken() == B_EXTERN)
    {
        // ���������� ��������!
        is_extern = true;
        t1 = t2;
        t2 = txtfile.read();
    }

    if (
        t1.GetToken() != B_ENTRY &&
        t1.GetToken() != B_CALIBRATE &&
        t2.GetToken() == B_COLON
        )
    {
        t2 = txtfile.read();

        if (t2.GetToken() != B_OFIGPAREN && t2.GetToken() != B_COLON)
        {
            txtfile.seekp(t1);
            LoadEntry(txtfile, is_extern, options);
            return true;
        }
    }

    bool processed = false;
    txtfile.seekp(t2);

    switch (t1.GetToken())
    {
    case B_ENTRY:
    {
        LoadEntry(txtfile, is_extern, options);
        processed = true;
        break;
    }

    case B_COORDINATE:
    {
        LoadCoord(txtfile, is_extern);
        processed = true;
        break;
    }

    case B_CLASS:
    {
        LoadClass(txtfile, is_extern);
        processed = true;
        break;
    }
    }

    return processed;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void Grammar::LoadCoord(Macro_Parser& txtfile, bool is_extern)
{
    GramCoord *added = coord->LoadTxt(txtfile, !is_extern);

    if (ilink_type == UNKNOWN && added != nullptr && added->GetName().front().eqi(sol_get_token(B_NET)))
        ilink_type = FindCoord(sol_get_token(B_NET)).GetIndex();

    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void Grammar::LoadClass(Macro_Parser& txtfile, bool is_extern)
{
    aclass->LoadTxt(txtfile, !is_extern);
    return;
}
#endif


#if defined SOL_LOADBIN
void Grammar::LoadBin(lem::Stream& bin, const Load_Options &opt)
{
    Automaton::LoadBin(bin, opt);
    return;
}
#endif

#if defined SOL_SAVEBIN
void Grammar::SaveBin(lem::Stream& bin) const
{
    Automaton::SaveBin(bin);
    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
GramCoordAdr Grammar::LoadCoordIdTxt(lem::Iridium::Macro_Parser & txtfile, bool allow_quantors) const
{
    lem::Iridium::BethToken t = txtfile.read();
    GramCoordAdr id = FindCoord(t.string());
    if ((!allow_quantors && id.IsAny()) || !id.IsDefined())
    {
        GetIO().merr().printf("Unknown coordinate '%us'\n", t.string().c_str());
        lem::Iridium::Print_Error(t, txtfile);
        throw lem::E_BaseException();
    }

    return id;
}
#endif


/***************************************************************
 ����� ���������� � �������� ������ � ������ ����������.
 ������������ ������ �������� ����������, ���� ��� �������,
 ����� ���������� UNKNOWN.

 ���� ��� ���������� ���������� ��� ������� ����������� '*',
 �� ���������� (ANY_STATE,ANY_STATE).
****************************************************************/
const GramCoordAdr Grammar::FindCoord(const UCString& coord_name) const
{
    if (coord_name == sol_get_token(B_ANY))
        return GramCoordAdr(ANY_STATE, ANY_STATE);

    const int id_coord = coords().Find(coord_name);
    if (id_coord != UNKNOWN)
    {
        const int ivar = coords()[id_coord].IsName(coord_name);
        return GramCoordAdr(id_coord, ivar);
    }

    return GramCoordAdr(UNKNOWN, UNKNOWN);
}

/************************************************************************
 ����� ��������������� ������ �� ��� ����� � ������ ����������.
 ������������ ������ �������� �����, ���� �� ��� ������. � ���������
 ������ ���������� UNKNOWN.

 ���� ��� ������ �������� ��������� �����������, �� ���������� ��������
 ANY_STATE.
*************************************************************************/
int Grammar::FindClass(const UCString& class_name) const
{
    if (class_name == sol_get_token(B_ANY))
        return ANY_STATE;

    return aclass->Find(class_name);
}

#if defined SOL_LOADTXT
/*************************************************************************
 ���� � ������ ���������� ���������� � �� ��������� �� �� �������������
 ������. ����� ���������� � ��������� ����������� � �������� ��������
 � �����.

 � ��������� ������� ����������� (index_ref=true) ����� ������ ������:

                        ���_����������:=������

 ������ ��� ����������� �� �� ���������, ������� ����� ������ ����������
 � �������� �������� ������� ����� ���������. ���������� �������� � ����
 ������ ���������� �� �������� ���� ���, ��� ��������� ����� ���� �����
 � ������ �� ����� ���� �������� �������� ������� ����� �������, ���
 ��� ��������� -1 �������� ������� ����� 0, � ��� �����. ��� �������,
 ����� ��������� �������� ������ ��������� � ������� ��������.
**************************************************************************/
const GramCoordPair Grammar::FindCoordPair(
    Macro_Parser& txtfile,
    bool index_ref
) const
{
    // ������� ������ ����������-��������� � ������ ����������.
    BethToken coord_name = txtfile.read();
    GramCoordAdr icoord = FindCoord(coord_name.string());
    bool confirm = true;

    if (coord_name.GetToken() == B_NEGATIVE)
    {
        // �������� ��������� - ������ ��� ������������ ���������!
        confirm = false;
        coord_name = txtfile.read();
        icoord = FindCoord(coord_name.string());

        if (coords()[icoord.GetIndex()].states().size())
        {
            Print_Error(coord_name, txtfile);
            GetIO().merr().printf("%vfDNegation is forbiden%vn\n");
            throw E_ParserError();
        }
    }

    if (!icoord.IsDefined())
    {
        Print_Error(coord_name, txtfile);
        GetIO().merr().printf(
            "%vfDThe coordinate [%us] is not previously declared in grammar%vn\n"
            , coord_name.c_str()
        );
        throw E_ParserError();
    }

    int istate = UNKNOWN;

    BSourceState back = txtfile.tellp();
    if (
        index_ref &&
        txtfile.read().GetToken() == B_COLON &&
        txtfile.read().GetToken() == B_EQUAL
        )
        istate = -txtfile.read_int() - 1; // ��, ��� ������ ���_�����:=������
    else
    {
        txtfile.seekp(back);

        // �������� �� ��� ������������?
        if (!coords()[icoord.GetIndex()].states().size())
        {
            // �� - ��������� ��� ��������� �� ����.
            istate = confirm;
        }
        else
        {
            // ������ ��������� � ��������� ����������.
            txtfile.read_it(B_COLON);
            BethToken state_name = txtfile.read();
            istate = coords()[icoord.GetIndex()].FindState(state_name.string());

            if (istate == UNKNOWN)
            {
                Print_Error(state_name, txtfile);
                GetIO().merr().printf(
                    "%vfDState [%us] is not declared for coordinate [%us]%vn\n"
                    , state_name.c_str(), coord_name.c_str()
                );
                throw E_ParserError();
            }
        }
    }

    return GramCoordPair(icoord, istate);
}
#endif

#if defined SOL_REPORT
/***********************************************************************
 ����� � ��������� ����� ������� �������������� ���������� � �����������
 ����������.
************************************************************************/
void Grammar::Report(OFormatter &dst_stream)
{
    dst_stream.printf(
        "Grammar: [%us]\n"
        "%W7d class(es)\n"
        "%W7d coord(s)\n"
        , GetName().c_str()
        , classes().Count()
        , coords().Count()
    );

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void Grammar::Prepare(const lem::Path &outdir, const Binarization_Options &opts)
{
    std::unique_ptr<CoordEnumerator> coenum(coord->Enumerate());
    while (coenum->Fetch())
    {
        const GramCoord &c = coenum->GetItem();
        if (!c.IsRealized())
        {
            GetIO().merr().printf(
                "%vfDCoordinate [%us] realization not found.%vn\n"
                , c.GetName().string().c_str()
            );
            throw E_ParserError();
        }
    }

    std::unique_ptr<ClassEnumerator> cenum(classes().Enumerate());
    while (cenum->Fetch())
    {
        const GramClass &c = cenum->GetItem();
        if (!c.IsRealized())
        {
            GetIO().merr().printf(
                "%vfDClass [%us] realization not found for grammar [%us].%vn\n"
                , c.GetName().c_str()
                , GetName().c_str()
            );
            throw E_ParserError();
        }
    }

    return;
}
#endif


int Grammar::GetnLink()
{
    return CastSizeToInt(coords()[ilink_type].states().size());
}

int Grammar::FindLink(const UCString& link_name)
{
    return coords()[ilink_type].FindState(link_name);
}

const UCString& Grammar::GetLink(int i)
{
    return coords()[ilink_type].GetTopState(i).GetName();
}
