// -----------------------------------------------------------------------------
// File CRITERION.CPP
//
// (c) Koziev Elijah
//
// Content:
// ����� Criterion - �������� ��������� ������������ ���������. ���������
// (��� ��������) ������������ � ��������� ��� ������� ������������� ���������
// ������������� ����������, ����� ������� �� ������� ��������� �����������
// �������� ���������� �������. ��������� ����������� ���������� �� ����� ������
// � ��������� ����� �������.
// -----------------------------------------------------------------------------
//
// CD->24.03.1997
// LC->02.04.2018
// --------------

#include <lem/conversions.h>
#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/criterion.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;


Criterion::Criterion()
{}

Criterion::Criterion(const Criterion &c)
{
    rval = c.rval;
    name = c.name;
    str = c.str;
    return;
}

#if defined SOL_LOADTXT
Criterion::Criterion(const Sol_IO &dict, Macro_Parser &txtfile)
{
    LoadTxt(dict, txtfile);
}
#endif

void Criterion::operator=(const Criterion &c)
{
    rval = c.rval;
    name = c.name;
    str = c.str;
    return;
}

Criterion::Criterion(const lem::UCString &_name, const lem::UFString &_str)
    : name(_name), str(_str)
{
    if (lem::is_real(str.c_str()))
    {
        double dval;
        to_real(str.c_str(), &dval);
        rval = dval;
    }

    return;
}


#if defined SOL_LOADTXT
/********************************************************************
 ���������� �������� �������� �� ���������� �����. ��������� �������:

 1. criterion ��� = �����_�����
 2. criterion ��� = "�������_�����"

 ������� ��������, ��� ��������� ������� ����� �� +0.00 �� +1.00.
*********************************************************************/
void Criterion::LoadTxt(const Sol_IO &io, Macro_Parser &txtfile)
{
    name = txtfile.read().string(); // �������� ��� ��������.

    // ����� ����� ��������� ���� ��������� ��������.
    txtfile.read_it(B_EQUAL);
    const BethToken val = txtfile.read();
    str = val.GetFullStr();
    str.strip_quotes().strip_apostrophes();

    if (lem::is_real(str.c_str()))
    {
        double dval;
        to_real(val.c_str(), &dval);
        rval = dval;
    }

    return;
}
#endif


int Criterion::GetInt() const
{
    if (rval.IsNull())
    {
        lem::MemFormatter mem;
        mem.printf("Can not convert the string %us to number when accessing the criterion [%us]", str.c_str(), name.c_str());
        throw lem::E_BaseException(mem.string());
    }

    return int(rval.get());
}


double Criterion::GetDouble() const
{
    if (rval.IsNull())
    {
        lem::MemFormatter mem;
        mem.printf("Can not convert the string %us to number when accessing the criterion [%us]", str.c_str(), name.c_str());
        throw lem::E_BaseException(mem.string());
    }

    return rval.get();
}


void Criterion::SaveBin(lem::Stream &bin) const
{
    str.SaveBin(bin);
    bin.write_bool(rval.NotNull());
    if (rval.NotNull())
        bin.write(&rval.get(), sizeof(rval.get()));

    return;
}


void Criterion::LoadBin(lem::Stream &bin)
{
    str.LoadBin(bin);
    if (bin.read_bool())
    {
        double x;
        bin.read(&x, sizeof(x));
        rval = x;
    }

    return;
}
