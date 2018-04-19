// -----------------------------------------------------------------------------
// File LA_PhoneticCondictor.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Класс LA_PhoneticCondictor - условная часть правила фонетической продукции для
// Фонетического Алеф-Автомата. Определяет те состояния опорного контекста при
// фонетических итерациях, которые должны вызывать описанные результатной частью
// правила действия.
// -----------------------------------------------------------------------------
//
// CD->26.02.1997
// LC->17.04.2018
// --------------

#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_PhoneticRule.h>

using namespace lem;
using namespace Solarix;


LA_PhoneticCondictor::LA_PhoneticCondictor() { loc = UNLOCATED; }

LA_PhoneticCondictor::LA_PhoneticCondictor(const UCString &str, bool IsPrefix, bool IsAffix)
    : context(str)
{
    if (IsPrefix) loc = PREFIX;
    else if (IsAffix) loc = AFFIX;
    else loc = UNLOCATED;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
LA_PhoneticCondictor::LA_PhoneticCondictor(Macro_Parser &txtfile, GraphGram &gram)
{
    LoadTxt(txtfile, gram);
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_PhoneticCondictor::LoadTxt(Macro_Parser &txtfile, GraphGram &gram)
{
    txtfile.read_it(B_CONTEXT);
    const BethToken t = txtfile.read();

    context = t.string();

    context.strip_quotes();

    // Каждый символ из строки должен быть известен как буква - то есть
    // быть определен через Алфавит. Допускается также специальный
    // кванторный символ '*'.
    //
    // В двух случаях допускается применение символа $ - для требования на
    // размещение символов: "$aaa" - приставка, "aaa$" - аффикс.

    if (context.front() == L'$')
    {
        loc = PREFIX;
        context.remove(0);
    }
    else if (context.back() == L'$')
    {
        loc = AFFIX;
        context.remove(context.length() - 1);
    }
    else
        loc = UNLOCATED;


    const int cl = context.length();
    for (int i = 0; i < cl; i++)
    {
        const wchar_t ch = context[i];

        if (ch == L'*')
            continue;

        const Word_Coord wc = gram.FindSymbol(ch);
        if (wc.GetEntry() == UNKNOWN)
        {
            lem::Iridium::Print_Error(t, txtfile);
            gram.GetIO().merr().printf(
                "Condictor [%us] contains unknown symbol (neither "
                "char nor quantor '*')\n"
                , context.c_str()
            );
            throw E_ParserError();
        }

        context.set(i, gram.entries()[wc.GetEntry()].GetName());
    }

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool LA_PhoneticCondictor::operator==(const LA_PhoneticCondictor& x) const
{
    return context == x.context && loc == x.loc;
}
#endif


#if defined SOL_CAA
bool LA_PhoneticCondictor::DoesMatch(const wchar_t *example) const
{
    // Длину не сравниваем, так как алгоритм Лексического Автомата
    // предварительно разбивает все правила на группы с равным количеством
    // опорных точек и применяет правила по группам.

    const wchar_t *Condition = context.c_str();
    while (*Condition)
    {
        if (*Condition == '*')
        {
            Condition++;
            example++;
            continue; // Квантор всеобщности в нашем контексте.
        }

        if (*example != *Condition)
            return false;

        example++;
        Condition++;
    }

    return true;
}
#endif

#if defined SOL_CAA
bool LA_PhoneticCondictor::Can_Subst(const UCString &lex) const
{
    if (context.length() > lex.length())
        return false;

    switch (loc)
    {
    case PREFIX:
        // Начало слова lex должно содержать condictor
        return !memcmp(
            lex.c_str(),
            context.c_str(),
            context.length() * sizeof(*lex.c_str())
        );

    case AFFIX:
        // Конец слова lex должен содержать condictor
        return !memcmp(
            lex.c_str() + lex.length() - context.length(),
            context.c_str(),
            context.length() * sizeof(*lex.c_str())
        );

    case UNLOCATED: LEM_STOPIT;
    }

    return false;
}
#endif

