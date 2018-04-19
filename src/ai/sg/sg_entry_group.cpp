// -----------------------------------------------------------------------------
// File SG_ENTRY_GROUP.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс SG_EntryGroup. Структура для внутреннего использования. Применяется в
// алгоритме быстрого поиска статьи в Синтаксической Грамматике. Хранит индексы
// статей Лексикона, начинающиеся с одной и той же буквы. Благодаря специальному
// подходу может хранить последовательность индексов в сжатом виде (начальный
// индекс + количество индексов) и в произвольном (вектор индексов).
// -----------------------------------------------------------------------------
//
// CD->15.03.1996
// LC->16.04.2018
// --------------

#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/SG_EntryGroup.h>

using namespace lem;
using namespace Solarix;

SG_EntryGroup::SG_EntryGroup(const KEY & k) : key(k)
{
}


#if defined SOL_COMPILER
SG_EntryGroup::SG_EntryGroup(const KEY & k, const IntCollect& indeces) : key(k)
{
    Compress(indeces);
    return;
}
#endif


SG_EntryGroup::SG_EntryGroup()
    : key(0, 0, 0)
{
}


SG_EntryGroup::SG_EntryGroup(const KEY & k, int from, int n) : key(k)
{
    int1.from = from;
    int1.n = n;
    return;
}


SG_EntryGroup::SG_EntryGroup(const SG_EntryGroup& eg)
    : key(eg.key), ientry(eg.ientry), int1(eg.int1), int2(eg.int2)
{}

#if defined SOL_LOADBIN 
SG_EntryGroup::SG_EntryGroup(lem::Stream& bin)
{
    LoadBin(bin);
}
#endif

void SG_EntryGroup::operator=(const SG_EntryGroup& eg)
{
    key = eg.key;
    int1 = eg.int1;
    int2 = eg.int2;
    ientry = eg.ientry;

    return;
}


void SG_EntryGroup::clear()
{
    key = KEY(0, 0, 0); int1.clear(); int2.clear(); ientry.clear();
}


#if defined SOL_COMPILER
/**********************************************************************
   Упаковка входного списка индексов indeces для экономного внутреннего
 представления.

   Если возникает ситуация, что индексы словоформ суть непрерывный ряд
 начиная с некоторого, то будем хранить не список, а лишь два числа -
 индекс первого и число последовательных. Если хранящиеся символы
 разбросаны слишком случайным образом, хранение в виде диапазона не
 используется. Может случиться, что хранимые индексы отчасти представляют
 из себя компактифицирующийся диапазон плюс случайный "шум": тогда пол
 int1 и ientry хранят информацию одновременно. Нередко можно выделить два
 диапазона.

   Допустим, что входной вектор indeces содержит:

                    1 5 7 8 9 10 11 15

 Тогда внутреннее представление этого списка будет содержать две части:
 один диапазон [7,11] и список дискретных {1,5,15}.

**********************************************************************/
void SG_EntryGroup::Compress(const IntCollect& indeces)
{
    ientry = indeces;

    Compress_Interval_1(ientry);

    if (!ientry.empty())
        Compress_Interval_2(ientry);

    return;
}

void SG_EntryGroup::Compress_Interval_1(IntCollect& indeces)
{
    Compress_Interval(indeces, int1);
    return;
}


void SG_EntryGroup::Compress_Interval_2(IntCollect& indeces)
{
    Compress_Interval(indeces, int2);
    return;
}


void SG_EntryGroup::Compress_Interval(IntCollect& indeces, SG_Interval &range)
{
    int i, j;
    const int n = indeces.size();

    // Шаг 1.
    // Найдем самый длинный диапазон индексов, который будет компактно
    // представлен двумя числами n_from и n_sequent.
    int n_from_max = 0, n_sequent_max = 0;
    for (i = 0; i < n; i++)
    {
        // Определяем длину последовательно идущих индексов, начиная с i.
        int nn = 1, iprev = indeces[i], inew;
        for (j = i + 1; j < n; j++, nn++)
            if ((inew = indeces[j]) != iprev + 1)
                break;
            else
                iprev = inew;

        if (n_sequent_max < nn)
        {
            n_from_max = i;
            n_sequent_max = nn;
        }
    }

    // Если найденный максимальный диапазон охватывает больше 2 индексов, или
    // он охватывает все индексы списка (когда их <=2), то сохраняем этот
    // диапазон в полях n_from и n_sequent.
    if (n_sequent_max > 2 || (n_from_max == 0 && n_sequent_max == n))
    {
        range.from = indeces[n_from_max];
        range.n = n_sequent_max;

        // Теперь индексы из списка indeces, вошедшие в сохраненный диапазон,
        // исключаем.
        IntCollect tmp;
        tmp.reserve(indeces.size());

        const int n_to = range.from + range.n;
        int ii;
        if (range.from != 0 || range.n != n)
            for (i = 0; i < n; i++)
            {
                ii = indeces[i];

                if (ii<range.from || ii>n_to)
                    tmp.push_back(ii);
            }

        indeces = tmp;
    }

    return;
}
#endif


#if defined SOL_LOADBIN
void SG_EntryGroup::LoadBin(Stream &bin)
{
    ientry.LoadBin(bin);
    bin.read(&int1, sizeof(int1));
    bin.read(&int2, sizeof(int2));
    bin.read(&key, sizeof(key));

    return;
}
#endif

#if defined SOL_SAVEBIN
void SG_EntryGroup::SaveBin(Stream &bin) const
{
    ientry.SaveBin(bin);
    bin.write(&int1, sizeof(int1));
    bin.write(&int2, sizeof(int2));
    bin.write(&key, sizeof(key));
    return;
}
#endif

// ********************************************************************
// Распечатка карты: краткая информация для прочтения программистом в
// отладочных целях.
// ********************************************************************
void SG_EntryGroup::Print(OFormatter &out) const
{
    if (std::get<1>(key) == 0)
        out.printf("%uc -> ", std::get<0>(key));
    else if (std::get<2>(key) == 0)
        out.printf("%uc%uc -> ", std::get<0>(key), std::get<1>(key));
    else
        out.printf("%uc%uc%uc -> ", std::get<0>(key), std::get<1>(key), std::get<2>(key));

    const int n = CastSizeToInt(size());
    out.printf("%d item(s), ", n);

    if (!int1.empty())
        out.printf("[%d...%d] ", int1.from, int1.from + int1.n - 1);

    if (!int2.empty())
        out.printf("[%d...%d] ", int2.from, int2.from + int2.n - 1);

    if (!ientry.empty())
    {
        out.printf("{ ");

        for (Container::size_type i = 0; i < ientry.size(); i++)
            out.printf("%d ", ientry[i]);

        out.printf("}");
    }

    return;
}


SG_EntryGroup::KEY SG_EntryGroup::BuildKey(const lem::UCString &str)
{
    switch (str.length())
    {
    case 1: return KEY(str.front(), 0, 0);
    case 2: return KEY(str.front(), str[1], 0);
    default: return KEY(str.front(), str[1], str[2]);
    }
}
