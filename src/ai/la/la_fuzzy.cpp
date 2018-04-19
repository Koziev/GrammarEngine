// -----------------------------------------------------------------------------
// File LA_FUZZY.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Часть кода Лексического Автомата, то есть реализация части методов класса
// LexicalAutomat. Реализация процедуры определения похожести двух мультилексем.
// -----------------------------------------------------------------------------
//
// CD->01.09.1997
// LC->09.06.2011
// --------------

#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_FuzzyMatching.h>
#include <lem/solarix/LA_PhoneticMatcher.h>

#undef min
#undef max

#if defined SOL_CAA

using namespace std;
using namespace lem;
using namespace Solarix;

/******************************************************************
 Алгоритм определения похожести двух мультилексем A и B c учетом
 возможных пропусков и/или искажений букв. Процедура вызывается
 при нечетком проецировании мультилексемы на Лексикон.
******************************************************************/
enum { ml_passive, ml_active, ml_delete };

struct ml_cur {
    int flag; // флаг состояния альтернативного варианта сопоставления
    int nmiss; // сколько ошибок уже допущено
    int equality; // накопленная достоверность совпадения лексем
    int a_cur, b_cur; // позиции сопоставления

    ml_cur() { equality = 0; flag = nmiss = a_cur = b_cur = UNKNOWN; }

    ml_cur(int Equality, int nMiss, int A_Cur, int B_Cur)
    {
        equality = Equality;
        flag = ml_active;
        nmiss = nMiss; a_cur = A_Cur; b_cur = B_Cur;
    }
};


// ********************************************************************
// В поле Equality возвращается степень совпадения.
// ********************************************************************
int LexicalAutomat::CompareThem(
    const Lexem &A,
    const Lexem &B,
    int id_language,
    int NMISSMAX,
    Real1 *Equality
) const
{
    LEM_CHECKIT_Z(!A.empty());
    LEM_CHECKIT_Z(!B.empty());
    LEM_CHECKIT_Z(NMISSMAX >= 0);
    LEM_CHECKIT_Z(Equality != 0);

    int i;
    const int Alen = A.length();
    const int Blen = B.length();

    wchar_t *a_buf = new wchar_t[Alen + 1];
    wchar_t *b_buf = new wchar_t[Blen + 1];

    a_buf[0] = b_buf[0] = 0;

    // Сначала из каждой мультилексемы сделаем одну строку без разрывов.
    lem_strcpy(a_buf, A.c_str());
    lem_strcpy(b_buf, B.c_str());

    MCollect<ml_cur> variant;
    variant.reserve(16);
    variant.push_back(ml_cur(0, 0, 0, 0));

    bool cont = true;
    while (cont)
    {
        cont = false;
        int n = CastSizeToInt(variant.size());

        for (i = 0; i < n; i++)
        {
            ml_cur &Cursor = variant[i];
            if (Cursor.flag == ml_passive)
                continue;

            cont = true;

            const wchar_t cha = a_buf[Cursor.a_cur];
            const wchar_t chb = b_buf[Cursor.b_cur];

            // Символы в позициях Cursor.a_cur и Cursor.b_cur совпадают?
            if (!cha && !chb)
            {
                // Обе строки закончились одновременно.
                Cursor.flag = ml_passive;
                continue;
            }

            if (cha == 0)
            {
                // Строка a_buf оказалась короче.
                Cursor.nmiss += lem::lem_strlen(b_buf + Cursor.b_cur);
                Cursor.flag = ml_passive;
                continue;
            }

            if (chb == 0)
            {
                // Строка b_buf оказалась короче.
                Cursor.nmiss += lem::lem_strlen(a_buf + Cursor.a_cur);
                Cursor.flag = ml_passive;
                continue;
            }

            if (cha == chb)
            {
                Cursor.equality += 100;
                Cursor.a_cur++;
                Cursor.b_cur++;
                continue;
            }

            // Какова недостоверность замены буквы сha на chb? Если найти правило не
            // получится, то - достоверность нулевая.
            lem::Real1 v = phonetic_matcher->GetMatcherForLanguage(id_language)->MatchRule11(Rule_1_to_1(cha, chb));
            Cursor.equality += v.GetInt();

            Cursor.nmiss++;

            if (Cursor.nmiss > NMISSMAX)
            {
                // Дальше вести это решение нет смысла - отличие уже слишком велико.
                Cursor.flag = ml_delete;
                continue;
            }

            // Символы не совпадают. Производим расщепление решения.

            if (Cursor.nmiss <= 1)
            {
                // Во втором варианте считаем, что в строке 'a' присутствует лишний символ,
                // поэтому курсор 'a' продвигаем вперед, а курсор 'b' оставляем в преждей
                // позиции.
                ml_cur var2(Cursor.equality, Cursor.nmiss, Cursor.a_cur + 1, Cursor.b_cur);
                variant.push_back(var2);

                // В третьем варианте считаем, что в строке 'b' присутствует лишний символ,
                // поэтому курсор 'b' продвигаем вперед, а курсор 'a' оставляем в прежней
                // позиции.
                ml_cur var3(Cursor.equality, Cursor.nmiss, Cursor.a_cur, Cursor.b_cur + 1);
                variant.push_back(var3);
            }

            // В основном варианте предполагаем, что имеет место быть локальное
            // искажение одного символа, и дальше символы снова начнут совпадать.
            Cursor.a_cur++;
            Cursor.b_cur++;
        }

        i = 0;
        while (i < n)
            if (variant[i].flag == ml_delete)
            {
                n--;
                variant.Remove(i);
                //      variant.erase( variant.begin()+i );
            }
            else
                i++;
    }

    delete[] a_buf;
    delete[] b_buf;

    int max_eq = 0;
    int min_miss = INT_MAX;

    for (Container::size_type i2 = 0; i2 < variant.size(); i2++)
    {
        max_eq = std::max(max_eq, variant[i2].equality);
        min_miss = std::min(min_miss, variant[i2].nmiss);
    }

    *Equality = Real1(max_eq / A.length());

    return min_miss;
}

#endif

