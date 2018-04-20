// -----------------------------------------------------------------------------
// File LEM_FP1.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Специализированный класс для работы с действительными неотрицательными
// числами в диапазоне [0,1]. Обычно - для представления вероятностей.
// -----------------------------------------------------------------------------
//
// CD->24.07.1996
// LC->20.04.2018
// --------------

#include <lem/conversions.h>
#include <lem/math/fp1.h>

using namespace lem;

/****************************************************************
 Число преобразуем в текстовую строку так, как если бы мы были
 обычным числом с плавающей точкой. Сначала будет идти 0, затем
 десятичная точка '.', и далее - собственно цифры. Иногда
 вместо лидирующего нуля может получаться 1.
*****************************************************************/
const UCString lem::to_ustr(Real1 x)
{
    UCString fp = to_ustr(x.GetInt() - 100 * (x.GetInt() / 100));

    if (fp.length() < 2)
        fp = UCString(get_unumerique(0)) + fp;

    return to_ustr(x.GetInt() / 100) + UCString('.') + fp;
}


const CString lem::to_str(Real1 x)
{
    CString fp = to_str(x.GetInt() - 100 * (x.GetInt() / 100));

    if (fp.length() < 2)
        fp = CString(get_numerique(0)) + fp;

    return to_str(x.GetInt() / 100) + CString(".") + fp;
}



Real1 lem::to_fp1(const wchar_t* src)
{
    LEM_CHECKIT_Z(!!(src));
    Real1 res;

    int int_signum, exp_signum;
    wchar_t int_part[LEM_CSTRING_LEN1], frac_part[LEM_CSTRING_LEN1],
        exp_part[LEM_CSTRING_LEN1];

    LEM_CHECKIT(
        split(
            src,
            &int_signum, int_part,
            frac_part,
            &exp_signum, exp_part
        )
    );

    // К строковому представлению допишем справа символьные нули...
    if (frac_part[0] == 0)
        frac_part[0] = frac_part[1] = L'0';

    if (frac_part[1] == 0)
        frac_part[1] = 0;

    frac_part[2] = 0;

    int intp, fracp;
    LEM_CHECKIT(to_int(int_part, &intp));
    LEM_CHECKIT(to_int(frac_part, &fracp));
    LEM_CHECKIT_Z(exp_signum == 1 && exp_part[0] == 0);

    int A = intp * 100 + fracp;
    LEM_CHECKIT_Z(A >= 0 && A <= 100);
    res = A;

    return res;
}
