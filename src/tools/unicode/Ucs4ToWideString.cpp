#include <lem/Ucs4ToWideString.h>

using namespace lem;

bool Ucs4ToUCString::Add(lem::uint32_t c)
{
    if (res.length() == lem::UCString::max_len)
        return false;
    else
    {
        if (c < 0x00010000 || sizeof(wchar_t) == 4)
        {
            // ������� � ��������� 0x00000000...0x0000ffff ���������� ������������� ������� 16 �����.
            res.Add_Dirty((wchar_t)c);
        }
        else
        {
            // ���������� 2 ������� - ����������� ����.

            if (res.length() >= lem::UCString::max_len - 1)
                return false; // ��� ����� ��� ����

            lem::uint32_t x = c - 0x00010000;
            lem::uint16_t high_surrogate = 0xD800 + lem::uint16_t((x >> 10) & 0x3FF);
            lem::uint16_t low_surrogate = 0xDC00 + lem::uint16_t(x & 0x3FF);
            res.Add_Dirty(high_surrogate);
            res.Add_Dirty(low_surrogate);
        }

        return true;
    }
}


const lem::UCString& Ucs4ToUCString::ToString(void)
{
    res.calc_hash();
    return res;
}


void Ucs4ToUCString::Clear()
{
    res.clear();
    return;
}


void Ucs4ToUFString::Add(lem::uint32_t c)
{
    if (c < 0x00010000 || sizeof(wchar_t) == 4)
    {
        // ������� � ��������� 0x00000000...0x0000ffff ���������� ������������� ������� 16 �����.
        res += (wchar_t)c;
    }
    else
    {
        // ���������� 2 ������� - ����������� ����.
        lem::uint32_t x = c - 0x00010000;
        lem::uint16_t high_surrogate = 0xD800 + lem::uint16_t((x >> 10) & 0x3FF);
        lem::uint16_t low_surrogate = 0xDC00 + lem::uint16_t(x & 0x3FF);
        res += high_surrogate;
        res += low_surrogate;
    }

    return;
}

const lem::UFString& Ucs4ToUFString::ToString(void)
{
    return res;
}


void Ucs4ToUFString::Clear()
{
    res.clear();
    return;
}

