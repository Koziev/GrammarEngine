// -----------------------------------------------------------------------------
// File GG_FORM.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс GG_EntryForm - вариант графического символа (буквоформы) - аналог
// словоформы Лексикона. Для объектного языка. Из буквоформ собирается
// парадигма буквостатьи, то есть объекты GG_EntryForm хранятся в списке
// GG_Entry.
// -----------------------------------------------------------------------------
//
// CD->10.08.1996
// LC->01.04.2018
// --------------

#include <lem/solarix/Symbol.h>

using namespace std;
using namespace lem;
using namespace Solarix;

/********************************************************************
 Все элементы буквоформы прочитаны, и теперь нам нужно перекопировать
 себе список координатных пар-измерений (Dim) и имя формы (Name).
*********************************************************************/
GG_EntryForm::GG_EntryForm(const CP_Array& Dim, lem::uint32_t Name)
{
    name = Name;
    copy(Dim.begin(), Dim.end(), back_inserter(dim));
    return;
}



lem::CString GG_EntryForm::GetNameUtf8() const
{
    return Solarix::EncodeChar32ToUtf8(name);
}

lem::UCString GG_EntryForm::GetNameWide() const
{
    return Solarix::EncodeChar32ToWide(name);
}
