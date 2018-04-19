// -----------------------------------------------------------------------------
// File LA_WORD_PROJECTION.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс LA_WordProjection - хранение информации об успешном проецировании
// слова на Лексикон.
// -----------------------------------------------------------------------------
//
// CD->17.04.1997
// LC->17.04.2018
// --------------

#include <lem/unicode.h>

#if defined SOL_REPORT
#include <lem/solarix/sg_autom.h>
#endif

#include <lem/solarix/dictionary.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_WordProjectionBuffer.h>

using namespace lem;
using namespace Solarix;


LA_WordProjection::LA_WordProjection()
{
    used_n_time = 0;
}

LA_WordProjection::LA_WordProjection(const LA_WordProjection &x) :A(x.A), WC(x.WC), val(x.val)
{
    used_n_time = 0;
}

LA_WordProjection::LA_WordProjection(
    const RC_Lexem &a,
    const MCollect<Word_Coord> &wc,
    const MCollect<ProjScore> &v,
    long Used_n_Time
) : A(a), WC(wc), val(v)
{
    used_n_time = Used_n_Time;
}


#if defined SOL_LOADBIN
LA_WordProjection::LA_WordProjection(lem::Stream &bin)
{
    LoadBin(bin);
}
#endif



#if defined SOL_LOADBIN 
void LA_WordProjection::LoadBin(lem::Stream &bin)
{
    Lexem *m = new Lexem;
    m->LoadBin(bin);
    A = RC_Lexem(m);

    WC.LoadBin(bin);
    val.LoadBin(bin);

    bin.read(&used_n_time, sizeof(used_n_time));
    return;
}
#endif

#if defined SOL_SAVEBIN
void LA_WordProjection::SaveBin(lem::Stream &bin) const
{
    A->SaveBin(bin);

    WC.SaveBin(bin);
    val.SaveBin(bin);

    bin.write(&used_n_time, sizeof(used_n_time));
    return;
}
#endif


const LA_WordProjection& LA_WordProjection::operator=(const LA_WordProjection &wp)
{
    Init(wp); return *this;
}


/*************************************************************************
 Добавляем в свои списки описания проекций из src. При этом если очередная
 проекция уже присутствует в нашем списке, то мы должны посмотреть, не
 увеличилась ли оценка ее достоверности в src, и если да, то следует
 запомнить новую оценку.
*************************************************************************/
void LA_WordProjection::Add(const LA_WordProjection &src)
{
    used_n_time += src.used_n_time;
    const int n_src = CastSizeToInt(src.WC.size());
    const int n_our = CastSizeToInt(WC.size()); // Будем просматривать только свои старые!

    for (int i = 0; i < n_src; i++)
    {
        const Word_Coord &wc = src.WC[i];
        bool found = false;

        for (int j = 0; j < n_our; j++)
        {
            if (WC[j] == wc)
            {
                if (val[j].score < src.val[i].score)
                    val[j] = src.val[i];

                found = true;
                break;
            }
        }

        if (!found)
        {
            WC.push_back(wc);
            val.push_back(src.val[i]);
        }
    }

    return;
}


#if defined SOL_REPORT
void LA_WordProjection::Print(
    OFormatter &dst_stream,
    const LexicalAutomat &la
) const
{
    dst_stream.printf(
        "%vfA%us"
        "%vn"
        " %d time(s)\n"
        , A->c_str()
        , used_n_time
    );

    return;
}
#endif


#if defined SOL_REPORT
/********************************************************************
 Распечатываем детальную информацию о содержимом кэшированной
 проекции слова. Этот метод обычно вызывается при печати содержимого
 Словаря (PrintMap), и помогает оценить и проверить работу кэша
 проекций слов Лексического Автомата.
*********************************************************************/
void LA_WordProjection::PrintInfo(
    OFormatter &txtfile,
    SynGram &gram
) const
{
    txtfile.printf("\n  Multylexem projection:");

    Print(txtfile, gram.GetDict().GetLexAuto());

    for (Container::size_type i = 0; i < WC.size(); i++)
    {
        const int ientry = WC[i].GetEntry();
        const SG_Entry &e = gram.GetEntry(ientry);
        const int iform = WC[i].GetForm();

        txtfile.printf(
            "  Entry #%d %20Y, %40Y form #%d, %60Y score=%g:%80Y ",
            e.GetKey(),
            iform,
            val[i].score
        );

        sol_print_class_entry(txtfile, gram, e.GetKey());
        txtfile.eol();
    }

    txtfile.eol();
    return;
}
#endif

