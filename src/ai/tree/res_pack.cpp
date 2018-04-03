// -----------------------------------------------------------------------------
// File RES_PACK.CPP
//
// (c) Koziev Elijah https://github.com/Koziev/GrammarEngine
//
// Content:
// Класс Res_Pack - набор альтернативных вариаторов для обработки в Итерациях
// ЦАА Продукционной Машины. Используется Лексическим, Алеф-Автоматом, Речевым
// Автоматом и другими модулями Системы.
// -----------------------------------------------------------------------------
//
// CD->14.11.1995
// LC->02.04.2018
// --------------

#if !defined SOL_NO_AA

#include <lem/solarix/aa_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/res_pack.h>

using namespace lem;
using namespace Solarix;

Res_Pack::Res_Pack(void)
{
    list.reserve(32);
}


Res_Pack::Res_Pack(const Res_Pack &rp)
{
    Init(rp);
}

Res_Pack::~Res_Pack(void)
{
    Delete();
    Clear();
    return;
}

void Res_Pack::Delete(void)
{
    for (auto item : list)
    {
        delete item;
    }

    return;
}

void Res_Pack::Init(const Res_Pack &rp)
{
    LEM_CHECKIT_Z(&rp != nullptr);

    const Container::size_type NI = rp.list.size();
    list.resize(NI);

    for (Container::size_type i = 0; i < NI; i++)
        list[i] = new Variator(*rp.list[i]);

    return;
}


void Res_Pack::operator=(const Res_Pack &rp)
{
    if (this == &rp)
        return;

    Delete();
    Clear();
    Init(rp);
    return;
}


/**********************************************************************
 Печатаем информацию о содержимом Пачки Решений в указанный текстовый
 поток s.
***********************************************************************/
void Res_Pack::Print(
    OFormatter &s,
    SynGram &gram,
    bool detailed
) const
{
    s.printf(
        "Result Pack contains %d variator(s)\n"
        , list.size()
    );

    for (Container::size_type i = 0; i < list.size(); i++)
    {
        s.printf("variator #%d ", i);
        list[i]->Print(s, gram, detailed);
    }

    return;
}


#if defined SOL_LOADBIN
void Res_Pack::LoadBin(Stream &bin)
{
    int n;
    bin.read(&n, sizeof(n));
    list.reserve(n);

    for (int i = 0; i < n; i++)
        Add(new Variator(bin));

    return;
}
#endif

void Res_Pack::SaveBin(Stream &bin) const
{
    int n = list.size();
    bin.write(&n, sizeof(n));
    for (int i = 0; i < n; i++)
        list[i]->SaveBin(bin);

    return;
}

/***********************************************************************
 Переписываем себе указатели на вариаторы из списка src и очищаем
 src, чтобы вариаторы не были удалены при работе деструктора delete src.
************************************************************************/
void Res_Pack::Recevoire(Res_Pack *src)
{
    for (Container::size_type i = 0; i < src->list.size(); i++)
        list.push_back(src->list[i]);

    src->list.clear();
    return;
}


int Res_Pack::GetShortestVar(void) const
{
    int ires = UNKNOWN, min_len = INT_MAX;

    for (Container::size_type i = 0; i < list.size(); i++)
        if (list[i]->size() < min_len)
            // Запоминаем индекс и длину минимального вариатора
            if ((min_len = list[ires = i]->size()) == 1)
                // Длины меньше чем 1 быть не может!
                break;

    return ires;
}

#if defined SOL_CAA
void Res_Pack::PrintRoots(
    OFormatter &s,
    bool Decoration,
    bool EntryKeys
) const
{
    if (Decoration)
        s.printf("Res pack contains %d variator(s):\n", list.size());

    for (Container::size_type i = 0; i < list.size(); i++)
    {
        if (Decoration)
            s.printf("#%W2d ", i);

        list[i]->PrintRoots(s, Decoration, EntryKeys);
        s.eol();
    }

    return;
}
#endif


// Оставляет только вариаторы с минимальным числом корней.
void Res_Pack::Save_Shortest_Vars(void)
{
    if (list.empty())
        return;

    int min_len = INT_MAX;

    for (Container::size_type i = 0; i < list.size(); i++)
    {
        if (list[i]->size() < min_len)
        {
            // Запоминаем индекс и длину минимального вариатора
            if ((min_len = list[i]->size()) == 1)
                // Длины меньше чем 1 быть не может!
                break;
        }
    }

    for (int i2 = list.size() - 1; i2 >= 0; i2--)
    {
        if (list[i2]->size() > min_len)
        {
            delete list[i2];
            list.Remove(i2);
        }
    }

    return;
}

static bool sorter_var_by_len_desc(const Variator *a, const Variator *b)
{
    return a->size() < b->size();
}

// пересортируем так, чтобы сначала шли самые короткие варианты
void Res_Pack::SortByLengthDescending(void)
{
    std::sort(list.begin(), list.end(), sorter_var_by_len_desc);
#if LEM_DEBUGGING==1
    int l_begin = list.front()->size();
    int l_end = list.back()->size();
#endif
    return;
}

#endif
