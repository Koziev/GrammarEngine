// -----------------------------------------------------------------------------
// File LA_PhoneticRule.cpp
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс LA_PhoneticRule - правило фонетической замены для Фонетического Алеф-Автомата
// (в Лексическом Автомате).
//
// 18.05.2006 - в описании правила теперь можно задавать целевой язык
//
// 10.06.2006 - добавлена операция сравнения двух правил для выполнения
//              оптимизации набора правил - поиска одинаковых.
// -----------------------------------------------------------------------------
//
// CD->26.02.1997
// LC->17.04.2018
// --------------

#include <lem/conversions.h>
#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/LA_PhoneticRule.h>

using namespace lem;
using namespace Solarix;



LA_PhoneticRule::LA_PhoneticRule() : id(UNKNOWN), id_lang(UNKNOWN), val(100), src_location(UNKNOWN)
{}

LA_PhoneticRule::LA_PhoneticRule(int Id, const lem::UCString &Name, int Id_Lang, bool IsPrefix,
    bool IsAffix, const lem::UCString &Condition, const lem::UCString &Result, lem::Real1 Rel, int SourceID)
    : id(Id), name(Name), id_lang(Id_Lang), is_prefix(IsPrefix), is_affix(IsAffix),
    head(Condition, IsPrefix, IsAffix), body(Result), val(Rel), src_location(SourceID)
{
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
// *******************************************************************
// Общий формат:
//       similarity Имя if Условие then Продукция [ = Достоверность ]
//
// *******************************************************************
void LA_PhoneticRule::LoadTxt(Macro_Parser &txtfile, GraphGram &gram)
{
    src_location = gram.GetDict().GetDebugSymbols().RegisterLocation(txtfile, txtfile.tellp());

    id_lang = UNKNOWN;
    const BethToken t = txtfile.read();
    val = Real1(100);

    name = t.string();
    name.strip_quotes();

    // Может быть указан целевой язык
    BethToken tlang = txtfile.read();
    if (tlang.GetToken() != B_LANGUAGE)
    {
        txtfile.seekp(tlang);
    }
    else
    {
        txtfile.read_it(B_EQUAL);
        tlang = txtfile.read(); // название языка

        id_lang = gram.GetDict().GetSynGram().Find_Language(tlang.string());

        if (id_lang == UNKNOWN)
        {
            lem::Iridium::Print_Error(tlang, txtfile);
            gram.GetIO().merr().printf(
                "Undefined language [%us] for rule [%us]\n"
                , tlang.string().c_str(), name.c_str()
            );
            throw E_ParserError();
        }
    }

    txtfile.read_it(B_OFIGPAREN);

    txtfile.read_it(B_IF);
    head.LoadTxt(txtfile, gram);
    txtfile.read_it(B_THEN);
    body.LoadTxt(txtfile, gram);

    const BethToken tt = txtfile.read();
    if (tt.GetToken() == B_EQUAL)
    {
        int v;
        const BethToken t = txtfile.read();

        if (!to_int(t.string().c_str(), &v))
        {
            lem::Iridium::Print_Error(t, txtfile);
            gram.GetIO().merr().printf(
                "Incorrect reliability %us of phonetic production: must "
                "be an integer 0 to 100.\n"
                , t.string().c_str()
            );
            throw E_ParserError();
        }

        val = Real1(v);
    }
    else
        txtfile.seekp(tt.GetBegin());

    if (val <= Real1(0) || val > Real1(100))
    {
        lem::Iridium::Print_Error(txtfile);
        gram.GetIO().merr().printf(
            "Incorrect reliability of phonetic production:"
            " must be an integer 0 to 100.\n"
        );
        throw E_ParserError();
    }

    txtfile.read_it(B_CFIGPAREN);

    return;
}
#endif



#if defined SOL_CAA
void LA_PhoneticRule::Subst(const UCString &org, UCString &res) const
{
    if (head.IsPrefix())
    {
        res = body.GetContext() +
            UCString(org.c_str() + head.length());
    }
    else if (head.IsAffix())
    {
        res = org;
        res.reduce(head.length());
        res += body.GetContext();
    }
    else
    {
        LEM_STOPIT;
    }
}
#endif


int LA_PhoneticRule::GetHash() const
{
    const UCString& s = head.GetContext();

    if (is_prefix)
        // первая буква префикса
        return lem::to_uupper(s.front());
    else if (is_affix)
        // Для аффикса - последняя буква
        return lem::to_uupper(s.back());
    else
    {
        LEM_STOPIT;
        return 0;
    }
}
