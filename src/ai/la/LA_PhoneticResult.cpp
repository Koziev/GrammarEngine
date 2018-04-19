// -----------------------------------------------------------------------------
// File LA_RULE_RESULT.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс LA_PhoneticResult - результатная часть правила фонетической продукции для
// Фонетического Алеф-Автомата. Выполняет некоторые модификации контекста в
// случае успешной проверки соответствия условной части фонетического правила
// и входного контекста.
// -----------------------------------------------------------------------------
//
// CD->26.02.1997
// LC->17.04.2018
// --------------

#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/LA_PhoneticRule.h>

using namespace lem;
using namespace Solarix;

#if defined SOL_LOADTXT && defined SOL_COMPILER
LA_PhoneticResult::LA_PhoneticResult(Macro_Parser &txtfile, GraphGram &gram)
{
    LoadTxt(txtfile, gram);
}
#endif


LA_PhoneticResult::LA_PhoneticResult(const UCString &str) : context(str)
{}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_PhoneticResult::LoadTxt(Macro_Parser &txtfile, GraphGram &gram)
{
    txtfile.read_it(B_CONTEXT);
    const BethToken t = txtfile.read();
    UCString Context = t.string();

    // Проверим, правильно ли задана строка результатного контекста.
    // Прежде всего, она должна быть в двойных кавычках.
    if (!in_quotes(Context))
    {
        lem::Iridium::Print_Error(t, txtfile);
        gram.GetIO().merr().printf(
            "Строка результатного контекста [%us] в фонетическом правиле должна "
            "быть в двойных кавычках\n"
            , Context.c_str()
        );
        LEM_STOPIT;
    }

    Context.strip_quotes();
    context = Context;

    context.Translate(gram);
    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
bool LA_PhoneticResult::operator==(const LA_PhoneticResult& x) const
{
    return context == x.context;
}
#endif
