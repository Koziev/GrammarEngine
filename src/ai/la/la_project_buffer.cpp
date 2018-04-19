// -----------------------------------------------------------------------------
// File LA_PROJECT_BUFFER.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс LA_WordProjBuffer - контейнер-кэш для Лексического Автомата, хранящий
// списки осуществленных проекций мультилексем на Лексикон. Экономит
// процессорное время и снижает пиковую загрузку оперативной памяти за счет
// неповторения попыток проекции часто встречающихся слов. Как нетрудно опытным
// путем установить, всего примерно 100 слов (предлоги, связки, союзы) дают не
// менее 60..70% всего числа поступающих на проекцию.
// -----------------------------------------------------------------------------
//
// CD->04.05.1997
// LC->25.04.2013
// --------------

#include <lem/oformatter.h>

#include <lem/solarix/version.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/SymbolEnumerator.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/LA_WordProjectionBuffer.h>


using namespace lem;
using namespace Solarix;

LA_WordProjBuffer::LA_WordProjBuffer()
{
    nmaxproj = NTOT = 0;
    n_calls = n_succ = n_succ_prim = 0;

    use_compiled = false;
    update_list = true;

#if defined SOL_LOADTXT && defined SOL_COMPILER
    optimized = false;
#endif

    return;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
/********************************************************************
 Подготавливаем кэш для работы: выделяем необходимую память для
 списка списков проекций. Эта процедура должна вызываться уже
 п_о_с_л_е загрузки графической грамматики, так как нам нужно узнать
 число символов в алфавите gram. Запомненные списки сейчас пусты, так
 как осуществленных проекций еще не было.
*********************************************************************/
void LA_WordProjBuffer::Adjust(const GraphGram &gram)
{
    // Число символов в алфавите (не считая буквоформ)
    NTOT = 0;
    const int nchar = CastSizeToInt(gram.entries().Count());
    list.reserve(nchar);
    int i;

    // Будем поддерживать nchar списков списков проекций, каждый список хранит
    // начинающиеся с одной и той же буквы проекции мультилексем.
    std::unique_ptr<SymbolEnumerator> senum(gram.entries().Enumerate());
    while (senum->Fetch())
    {
        list.push_back(LA_ProjList(senum->GetItem().GetName()));
    }

    // Отсортируем список списков по возрастанию параметра КОД СИМВОЛА,
    // чтобы была возможность реализовать быстрый поиск нужного списка
    // методом дихотомии.
    int gap, j;
    const int N = nchar;
    for (gap = N / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < N; i++)
        {
            for (j = i - gap; j >= 0; j -= gap)
            {
                if (list[j + gap].Char > list[j].Char)
                    break;

                std::swap(list[j], list[j + gap]);
            }
        }
    }

    return;
}
#endif

/*********************************************************************
 Устанавливаем максимальный размер кэша. При этом пиковая загрузка
 кэша может достигать n*SOL_CACHE_OVERLOAD/100. Только после операции
 Resort кэш урезается до указанного размера в n элементов, но
 при работе Лексического Автомата снова будет расти.
**********************************************************************/
void LA_WordProjBuffer::SetMaxSize(int n)
{
    nmaxproj = n;
}


#if defined SOL_LOADBIN 
void LA_WordProjBuffer::LoadBin(lem::Stream &bin)
{
    buffer.LoadBin(bin);
    list.LoadBin(bin);
    bin.read(&nmaxproj, sizeof(nmaxproj));
    bin.read(&n_calls, sizeof(n_calls));
    bin.read(&n_succ, sizeof(n_succ));
    bin.read(&n_succ_prim, sizeof(n_succ_prim));
    bin.read(&NTOT, sizeof(NTOT));

    bin.read(&use_compiled, sizeof(use_compiled));
    bin.read(&update_list, sizeof(update_list));

    return;
}
#endif


#if defined SOL_SAVEBIN
void LA_WordProjBuffer::SaveBin(lem::Stream &bin) const
{
    buffer.SaveBin(bin);
    list.SaveBin(bin);
    bin.write(&nmaxproj, sizeof(nmaxproj));
    bin.write(&n_calls, sizeof(n_calls));
    bin.write(&n_succ, sizeof(n_succ));
    bin.write(&n_succ_prim, sizeof(n_succ_prim));
    bin.write(&NTOT, sizeof(NTOT));

    bin.write(&use_compiled, sizeof(use_compiled));
    bin.write(&update_list, sizeof(update_list));

    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_WordProjBuffer::Optimize()
{
    optimized = true;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_WordProjBuffer::Compile(const lem::Path &outdir)
{
    OFormatter cpp_out;
    lem::Path p(outdir);
    p.ConcateLeaf(lem::Path("_la_find.cpp"));
    cpp_out.Open(p);
    cpp_out.SetOutCP(&lem::UI::get_UI().GetSessionCp());

    cpp_out.printf(
        "// Generated by YGRES compiler ver. %s [%us]\n"
        "// This file contains the results of LA_WordProjBuffer::Compile()\n"
        "// compilation.\n"
        "// Do not edit it!\n\n"
        "#if defined SOL_CAA\n\n"
        "#include <lem/solarix/la_autom.h>\n\n"
        "using namespace std;\n"
        "using namespace lem;\n\n"
        "using namespace Solarix;\n\n"
        "\n"
        , sol_get_version().c_str()
        , timestamp().c_str()
    );


    cpp_out.printf(
        "bool LA_WordProjBuffer::Find_In_Compiled_Cache(\n"
        "                                               const RC_Lexem &to_be_found,\n"
        "                                               MCollect<Word_Coord> &coord_list,\n"
        "                                               MCollect<Real1> &val_list\n"
        "                                              )\n"
        "{\n"
    );

    if (!optimized)
    {
        cpp_out.printf(
            " return false;\n"
            "}\n"
            "#endif\n"
        );
        use_compiled = false;
        return;
    }


    cpp_out.printf(
        " // Cache contains %d projection sublist(s), total %d projections\n"
        , list.size()
        , GetN()
    );

    if (!list.empty())
    {
        cpp_out.printf(
            " const wchar_t first_ch = to_be_found->front();\n"
            " const int l = to_be_found->length();\n\n"
        );

        // Естественные языки обладают интересным свойством: чаще всего встречаютс
        // очень короткие слова, в частности - знаки препинания и односимвольные
        // союзы, артикли и так далее. Поэтому односимвольные слова проверяем
        // отдельным быстрым алгоритмом.
        cpp_out.printf(
            " if( l==1 )\n"
            "  {\n"
        );


        cpp_out.printf(
            "   // Here comes the fast algorithm for 1-char length lexems\n"
            "   switch( first_ch )\n"
            "   {\n"
        );

        int j = 0;
        for (auto i = list.begin(); i != list.end(); i++, j++)
        {
            if (!i->empty())
            {
                for (Container::size_type k = 0; k < i->size(); k++)
                {
                    if ((*i)[k].GetContent()->length() == 1)
                    {
                        cpp_out.printf(
                            "    case %d: /* %uc */\n"
                            "     Pick_Projection( &list[%d], %d, coord_list, val_list );\n"
                            "     return true;\n\n"
                            , static_cast<unsigned>(i->Char)
                            , i->Char
                            , j
                            , k
                        );
                    }
                }
            }
        }

        cpp_out.printf(
            "   } // end switch()\n\n"
            "   return false;\n"
            "  } // end if\n\n\n"
        );


        int max_len = 0;

        for (auto i2 = list.begin(); i2 != list.end(); i2++, j++)
        {
            for (Container::size_type k = 0; k < i2->size(); k++)
            {
                int l = (*i2)[k].GetContent()->length();
                max_len = std::max(max_len, l);
            }
        }

        cpp_out.printf(
            " if( l>%d )\n"
            "  return false;\n\n"
            , max_len
        );

        cpp_out.printf(" lem::uint8_t h = to_be_found->GetHash();\n");

        // Теперь общий алгоритм - для более длинных слов.
        cpp_out.printf(
            " switch(first_ch)\n"
            " {\n"
        );

        j = 0;
        for (auto i3 = list.begin(); i3 != list.end(); i3++, j++)
        {
            if (!i3->empty())
            {
                // В этом подсписке есть слова длиной более 1?
                bool has_longer_1 = false;
                for (Container::size_type k = 0; k < i3->size(); k++)
                {
                    if ((*i3)[k].GetContent()->length() > 1)
                    {
                        has_longer_1 = true;
                        break;
                    }
                }


                if (!has_longer_1)
                    continue;

                cpp_out.printf(
                    "  case %ud: /* %uc */\n"
                    "   {\n"
                    , static_cast<unsigned>(i3->Char)
                    , i3->Char
                );

                cpp_out.printf(
                    "    // Sublist contains %d items\n"
                    , i3->size()
                );

                for (Container::size_type k3 = 0; k3 < i3->size(); k3++)
                {
                    if ((*i3)[k3].GetContent()->length() > 1)
                    {
                        cpp_out.printf(
                            "    // %us\n"
                            "    if( h == %ud &&\n"
                            "        l == %d &&\n"
                            "        lem_eq( to_be_found->c_str()+1, L\"%us\" ) )\n"
                            "     {\n"
                            "      Pick_Projection( &list[%d], %d, coord_list, val_list );\n"
                            "      return true;\n"
                            "     }\n\n"
                            , (*i3)[k3].GetContent()->c_str()
                            , (*i3)[k3].GetContent()->GetHash()
                            , (*i3)[k3].GetContent()->length()
                            , (*i3)[k3].GetContent()->c_str() + 1
                            , j
                            , k3
                            , k3
                        );
                    }
                }

                cpp_out.printf(
                    "    break;\n"
                    "   }\n\n"
                );
            }
        }

        cpp_out.printf(" }\n\n");
    }

    cpp_out.printf(
        "\n return false;\n}\n\n"
        "#endif\n"
    );

    cpp_out.GetStream()->close();

    use_compiled = true;
    update_list = false;

    return;
}
#endif

#if defined SOL_CAA
/***************************************************************
 Пытаемся найти проекцию мультилексемы среди хранящихся списков.
 В случае успеха заполняем выходные поля coord_list и val_list.
****************************************************************/
bool LA_WordProjBuffer::Project(
    const RC_Lexem &to_be_found,
    MCollect<Word_Coord> &coord_list,
    MCollect<ProjScore> &val_list,
    PtrCollect<LA_ProjectInfo>& prj_extra_inf,
    int id_lang,
    LA_RecognitionTrace *trace
)
{
    return Find_In_Live_Cache(to_be_found, coord_list, val_list, prj_extra_inf);
}
#endif



#if defined SOL_CAA
bool LA_WordProjBuffer::Find_In_Live_Cache(
    const RC_Lexem &to_be_found,
    MCollect<Word_Coord> &coord_list,
    MCollect<ProjScore> &val_list,
    PtrCollect<LA_ProjectInfo>& prj_extra_inf
)
{
    if (list.empty())
        return false;

#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs);
#endif

    bool found = false;

    // Ищем подсписок по первой букве.
    const int i_sublist = LocateSublist(to_be_found);

    if (i_sublist != UNKNOWN)
    {
        // Нашли нужный список проекций. Теперь проходим по этому списку.
        LA_ProjList &sublist = list[i_sublist];

        const int n = CastSizeToInt(sublist.size());

        for (int i = 0; i < n; i++)
        {
            if (sublist[i].GetContent() == to_be_found)
            {
                // Нашли проекцию для данной мультилексемы!
                Pick_Projection(&sublist, i, coord_list, val_list, prj_extra_inf);
                found = true;
                break;
            }
        }
    }

    return found;
}
#endif


#if defined SOL_CAA
void LA_WordProjBuffer::Pick_Projection(
    LA_ProjList *sublist,
    int i_proj,
    MCollect<Word_Coord> &coord_list,
    MCollect<ProjScore> &val_list,
    PtrCollect<LA_ProjectInfo>& prj_extra_inf
)
{
    // Нашли проекцию для данной мультилексемы!
    n_succ++;

    const MCollect<Word_Coord> &coords_to_copy = (*sublist)[i_proj].GetCoord();
    const MCollect<ProjScore> &vals_to_copy = (*sublist)[i_proj].GetVal();

    for (Container::size_type j = 0; j < coords_to_copy.size(); j++)
    {
        coord_list.push_back(coords_to_copy[j]);
        val_list.push_back(vals_to_copy[j]);
        prj_extra_inf.push_back(NULL);
    }

    (*sublist)[i_proj].Used();
    return;
}
#endif

/************************************************************************
 Найдем список проекций для мультилексемы, начинающейся с той же буквы,
 как и наш аргумент to_be_found. Если список не удается обнаружить,
 то возвращаем UNKNOWN, это - сигнал неблагополучия (где-то что-то не
 так, как должно быть).
*************************************************************************/
int LA_WordProjBuffer::LocateSublist(const RC_Lexem &to_be_found) const
{
    const wchar_t first_char = to_be_found->front();
    int i_left = 0, i_right = CastSizeToInt(list.size()) - 1, i_middle = UNKNOWN;
    wchar_t c_middle;

    FOREVER
    {
     if ((i_right - i_left) < 4)
      {
       for (i_middle = i_left; i_middle <= i_right; i_middle++)
        if (list[i_middle].Char == first_char)
         return i_middle;

       return UNKNOWN;
      }

     i_middle = (i_right + i_left) / 2;
     c_middle = list[i_middle].Char;

     if (c_middle == first_char)
      return i_middle;

     if (c_middle > first_char)
      {
       i_right = i_middle;
       continue;
      }

     if (c_middle < first_char)
      {
       i_left = i_middle;
       continue;
      }
    }

#if defined LEM_BORLAND
#pragma warn-rch
#endif
    return UNKNOWN;
#if defined LEM_BORLAND
#pragma warn+rch
#endif
}


/****************************************************************************
 Была осуществлена успешная проекция мультилексемы на Лексикон, причем не
 средствами нашего кэша. Запоминаем информацию, связанную с этим событием,
 дабы в дальнейшем производить проекции быстрее, без поиска в Лексиконе.
 Если число хранящихся проекций слишком велико (критерий nmaxproj*
 SOL_CACHE_OVERLOAD%), то запоминания не произойдет.
*****************************************************************************/
void LA_WordProjBuffer::Add(const LA_WordProjection &WP)
{
    if (!update_list)
        return;

#if defined LEM_THREADS && defined SOL_CAA
    lem::Process::RWU_ReaderGuard rlock(cs);
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    // Новую информацию вталкиваем в предварительный буфер. Если этот буфер уже
    // достиг максимального размера, то из его головы выталкиваем один элемент и
    // направляем на запоминание во вторичный буфер.
    if (CastSizeToInt(buffer.size()) >= SOL_LA_MAX_PRECACHE)
    {
        const LA_WordProjection &PICKED = buffer.front();

        if (update_list)
        {
            if (list.empty())
                return;

            // В каком списке будем размещать.
            const int i_sublist = LocateSublist(PICKED.GetContent());

            if (i_sublist == UNKNOWN)
                return;

            Collect<LA_WordProjection> &sublist = list[i_sublist];

            const int n = CastSizeToInt(sublist.size());
            const RC_Lexem &mlex = PICKED.GetContent();

            // Может случиться, что мы уже храним проекции для данной мультилексемы.
            // Тогда нужно добавить новые проекции к уже хранящимся.
            bool found = false;
            for (int i = 0; i < n; i++)
            {
                if (sublist[i].GetContent() == mlex)
                {
                    // Добавляем.
                    sublist[i].Add(PICKED);
                    found = true;
                    break;
                }
            }

            // Добавляем новую проекцию.
            if (!found)
            {
                if (NTOT <= nmaxproj * 2)
                {
                    sublist.push_back(PICKED);
                    NTOT++;
                } // Если кэш переполнен, то запоминать нельзя.
            }

            buffer.pop();
        }
    }

    // Проекцию WP без разговоров вталкиваем в хвост предварительного буфера.
    buffer.push_back(WP);

    return;
}

/***********************************************************
 Определяем общее число хранимых в кэше проекций. Для этого
 проходим по всем спискам!
************************************************************/
int LA_WordProjBuffer::GetN() const
{
    int N = 0;
    for (Container::size_type i = 0; i < list.size(); i++)
        N += CastSizeToInt(list[i].size());

    return N;
}


/************************************************************************
 Производим пересортировку содержимого кэша и отсекаем избыточные
 элементы. Так как мы храним не просто список проекций, а список списков
 проекций, то отсечение избыточных элементов производится не совсем
 просто.
*************************************************************************/
void LA_WordProjBuffer::Resort()
{
    if (!update_list)
        return;

#if defined LEM_THREADS && defined SOL_CAS
    lem::Process::RWU_ReaderGuard rlock(cs);
    lem::Process::RWU_WriterGuard wlock(rlock);
#endif

    // Посмотрим, не превысили ли мы максимальное число элементов,
    // хранимых в кэше.
    int n_tot = 0;
    for (Container::size_type i = 0; i < list.size(); i++)
        n_tot += CastSizeToInt(list[i].size());

    if (n_tot > nmaxproj)
    {
        // Приступаем к удалению лишней информации из списка проекций.

        // Вычисляем число избыточных элементов.
        const int nexceed = n_tot - nmaxproj;

        for (Container::size_type i1 = 0; i1 < list.size(); i1++)
        {
            const int nitem = CastSizeToInt(list[i1].size());

            // Вычисляем число отсекаемых элементов.
            const int nreduce = nexceed*(nitem / nmaxproj);

            // Сокращаем список проекций пропорционально его текущему размеру.
            list[i1].ReduceTo(nitem - nreduce);
        }
    }

    // Теперь каждый подсписок проекций пересортируем.
    for (Container::size_type i2 = 0; i2 < list.size(); i2++)
        list[i2].ReSort();

    // Обновим содержимое поля общего числа элементов в кэше.
    NTOT = GetN();

    return;
}


#if defined SOL_REPORT
/**************************************************
 Распечатка краткой справки о состоянии кэша.
***************************************************/
void LA_WordProjBuffer::Report(
    OFormatter &s,
    const LexicalAutomat &la
) const
{
    const int n = NTOT;

    const int perc = int(n_succ * 100l / (n_calls ? n_calls : 1));
    const int stor_use = int((n * 100l) / (nmaxproj ? nmaxproj : 1));
    const int pus = int(n_succ_prim * 100l / (n_succ ? n_succ : 1));

    s.printf(
        "Word Projection Cache:\n"
        "%23h primary buffer contains %d items\n"
        "%23h this buffer successfully does %d%% of all projections through cache\n"
        "%23h secondary buffer contains %d items (%d%%)\n"
        "%23h maximum capacity of the secondary buffer is %d items\n"
        "%23h there were %d cache call(s)\n"
        "%23h there were %d successful cache hit(s) (%d%%)\n\n"
        , buffer.size()
        , pus
        , n
        , stor_use
        , nmaxproj
        , n_calls
        , n_succ
        , perc
    );

    return;
}
#endif


#if defined SOL_REPORT
void LA_WordProjBuffer::PrintMap(
    OFormatter &txtfile,
    SynGram &gram
) const
{
    Report(txtfile, gram.GetDict().GetLexAuto());

    txtfile.printf(
        "There are %d item(s) in word projection cache:\n",
        list.size()
    );

    for (Container::size_type i = 0; i < list.size(); i++)
    {
        list[i].PrintInfo(txtfile, gram);
    }

    txtfile.printf("The end of word projection cache map.\n");

    return;
}
#endif
