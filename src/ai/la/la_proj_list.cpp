// -----------------------------------------------------------------------------
// File LA_PROJ_LIST.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс LA_ProjList - список успешных проекций для слов, начинающихся с одной и
// той же буквы. Является элементом кэша успешных проекций слов для Лексического
// Автомата.
// -----------------------------------------------------------------------------
//
// CD->20.08.1997
// LC->17.04.2018
// --------------

#if defined SOL_REPORT
#include <lem/oformatter.h>
#include <lem/solarix/sg_autom.h>
#endif

#include <lem/solarix/LA_WordProjectionBuffer.h>

using namespace lem;
using namespace Solarix;


LA_ProjList::LA_ProjList() :Collect<LA_WordProjection>()
{
    Char = 0;
}

LA_ProjList::LA_ProjList(wchar_t ch) : Collect<LA_WordProjection>()
{
    Char = ch;
}

LA_ProjList::LA_ProjList(const LA_ProjList &l) : Collect<LA_WordProjection>(l)
{
    Char = l.Char;
}

void LA_ProjList::operator=(const LA_ProjList &l)
{
    Collect<LA_WordProjection>::operator=(l);
    Char = l.Char;
    return;
}


#if defined SOL_LOADBIN 
void LA_ProjList::LoadBin(lem::Stream &bin)
{
    bin.read(&Char, sizeof(Char));
    Collect<LA_WordProjection>::LoadBin(bin);
    return;
}
#endif

#if defined SOL_SAVEBIN
void LA_ProjList::SaveBin(lem::Stream &bin) const
{
    bin.write(&Char, sizeof(Char));
    Collect<LA_WordProjection>::SaveBin(bin);
    return;
}
#endif


/*******************************************************************
   Пересортировка элементов в списке в порядке убывания частоты их
 использования, так что чаще используемые элементы группируются в
 голове списка. Поэтому при поиске сначала просматриваются наиболее
 часто используемые, что конечно повышает эффективность.

   Следует заметить, что пиковое потребление ресурсов оперативной
 памяти может быть очень велико: примерно двойной объем списка до
 начал сортировки.
********************************************************************/
void LA_ProjList::ReSort()
{
    // Сначала отсортируем элементы через индексный вектор, а потом
    // перестроим сам список. Это съэкономит процессорное время.
    IntCollect index(size());
    const int N = CastSizeToInt(size());

    for (Container::size_type i = 0; i < size(); i++)
    {
        index[i] = CastSizeToInt(i);
    }

    // Быстрая сортировка Шелла.
    for (int gap = N / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < N; i++)
        {
            for (int j = i - gap; j >= 0; j -= gap)
            {
                if (get(index[j + gap]) < get(index[j]))
                    break;

                const int dummy = index[j];
                index[j] = index[j + gap];
                index[j + gap] = dummy;
            }
        }
    }

    // Мы отсортировали ТОЛЬКО индексный список. Теперь преобразуем
    // хранимый список элементов.
    Collect<LA_WordProjection> adjust(size());
    for (Container::size_type i2 = 0; i2 < size(); i2++)
    {
        adjust[i2] = get(index[i2]);
    }

    Collect<LA_WordProjection>::operator=(adjust);
    return;
}


#if defined SOL_REPORT
void LA_ProjList::PrintInfo(
    OFormatter &txtfile,
    SynGram &gram
) const
{
    if (empty())
        // Чтобы не засорять листинг, пропускаем пустые списки...
        return;

    txtfile.printf(
        "\nList of cached projections beginning with symbol [%uc]:\n"
        , Char
    );

    for (Container::size_type i = 0; i < size(); i++)
        get(CastSizeToInt(i)).PrintInfo(txtfile, gram);

    return;
}
#endif
