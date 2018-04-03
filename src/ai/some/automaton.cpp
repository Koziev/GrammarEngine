// -----------------------------------------------------------------------------
// File AUTOMATON.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                https://github.com/Koziev/GrammarEngine
// Content:
// Класс Automaton - базовый для создания Автоматов (в том числе Грамматик)
// Системы.
// -----------------------------------------------------------------------------
//
// CD->29.05.1997
// LC->02.04.2018
// --------------

#include <lem/macro_parser.h>
#include <lem/logfile.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/automaton.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;

/****************************************************************************
   Автомат - основная структурная единица деления Системы. Каждый Автомат
 является функционально законченой подсистемой, скрывающей особенности
 внутренней реализации (инкапсулирующей их) и предоставляющей набор
 интерфейсных функций для доступа к хранимым данным и алгоритмам. В
 некоторых случаях Автоматы выполняют пассивную роль с точки зрения
 обработки потоков данных Вербальной Машины. Таковыми являются Грамматики
 (см. файл sol_gram.cpp). Другие Автоматы включаются на одном из этапов в
 поток анализа Вербальной Машины и активно модифицируют данные, применяя
 продукционные правила и итераторы (см. классы SolSynRule и ProcedureBeth).

   Класс Automaton не используется сам по себе, но служит базовым классом
 для других классов Автоматов. Из текстового файла Словаря этот класс
 считывает только определения параметров (объекты класса Criterion),
 предоставляя через механизм перегрузки виртуальных функций возможность
 загружать специфические данные производным классам Автоматов.
*****************************************************************************/
Automaton::Automaton(int Index)
{
    // Еще сам по себе, без связи со Словарем...
    dict = nullptr;
    param = nullptr;

    // Автомат пуст.
    was_loaded = false;

    index = Index;

    return;
}

Automaton::~Automaton()
{
    delete param;
    return;
}


/***************************************************************************
 Налаживаем связь с нашим базовым Словарем. Обладание указателем на Словарь
 позволяет посылать сообщения к другим Автоматам и пользоваться их сервисом.
****************************************************************************/
void Automaton::SetDictPtr(Dictionary *d)
{
    dict = d;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
/********************************************************************
 Класс Словаря Dictionary обнаружил в текстовом файле секцию описания
 Автомата и просит нас загрузить ее тело (шапка уже считана им).
 Перед началом первой загрузки Автомата вызывается метод PreLoad, а
 после считывания очередной порции вызывается PostRead.
*********************************************************************/
void Automaton::LoadTxt(
    Macro_Parser &txtfile,
    const Binarization_Options &options
)
{
    try
    {
        if (!was_loaded)
            PreLoad(txtfile, options);

        was_loaded = true;
        txtfile.read_it(B_OFIGPAREN);
        load(txtfile, options);
        PostRead(txtfile, options);
    }
    catch (E_ParserError &x)
    {
        GetIO().merr().printf(
            "Syntax error in automaton [%us] section\n%us\n"
            , GetName().c_str()
            , x.what()
        );

        was_loaded = false;
        throw(x);
    }

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool Automaton::ProcessLexem2(
    const BethToken &t,
    Macro_Parser &txtfile,
    const Binarization_Options &options
)
{
    return false;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/************************************************************************
 Собственно, загрузка содержимого тела секции Автомата. Дабы позволить
 производным классам автоматов разпознавать и загружать свои собственные
 структуры данных сверх того, что распознает и загружает наш класс,
 вызывается виртуальный метод ProcessLexem.
*************************************************************************/
void Automaton::load(
    Macro_Parser &txtfile,
    const Binarization_Options &options
)
{
    bool looping = true;
    while (looping)
    {
        if (txtfile.eof())
        {
            Print_Error(txtfile);
            GetIO().merr().printf(
                "End of file has been reached before Automaton [%us] section completely loaded\n"
                , GetName().c_str()
            );
            throw E_ParserError();
        }

        const BethToken t = txtfile.read();

        if (!ProcessLexem(t, txtfile, options))
        {
            switch (t.GetToken())
            {
            case B_CRITERION:
                if (param != NULL)
                    param->LoadTxt(GetIO(), txtfile);
                break;

            case B_CFIGPAREN:
                looping = false;
                break;

            default:
            {
                const BSourceState back = txtfile.tellp();

                if (param != NULL)
                {
                    if (txtfile.read().GetToken() == B_EQUAL)
                    {
                        txtfile.seekp(t.GetBegin());
                        param->LoadTxt(GetIO(), txtfile);
                        break;
                    }
                }
                else
                {
                    LEM_STOPIT;
                }

                txtfile.seekp(back);

                // Нераспознанная лексема.
                GetIO().merr().printf("\nIncorrect lexem [%us]\n", t.string().c_str());
                Print_Error(t, txtfile);
                throw E_ParserError();
            }
            }
        }
    }

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/**********************************************************************
 Этот метод предназначен для перегрузки производным классом Автомата
 чтобы загружать специфические данные из своей секции. Если возвращено
 true, то блок данных, начинающийся токеном t, распознан и загружен.
***********************************************************************/
bool Automaton::ProcessLexem(
    const BethToken &/*t*/,
    Macro_Parser& /*txt*/,
    const Binarization_Options& /*options*/
)
{
    return false;
}
#endif


void Automaton::PrintMap(OFormatter &txtfile)
{}


#if defined SOL_LOADBIN
/********************************************************************************
 Метод загружает информацию в контейнеры Автомата из указанного бинарного потока
 (файла). В производном классе метод перегружаем, но наш базовый метод должен
 быть вызван для загрузки таблицы параметров param.
*********************************************************************************/
void Automaton::LoadBin(lem::Stream &bin, const Load_Options &opt)
{
    if (bin.read_bool() && param != nullptr)
        param->LoadBin(bin);

    return;
}
#endif

#if defined SOL_SAVEBIN
/****************************************************************************
 Метод сохраняет информацию в контейнерах Автомата в бинарном потоке (файле).
 Производные классы перегружают метод, но должны в новом методе вызвать наш
 базовый для сохранения содежимого таблицы параметров.
*****************************************************************************/
void Automaton::SaveBin(lem::Stream &bin) const
{
    bin.write_bool(param != nullptr);
    if (param != nullptr)
        param->SaveBin(bin);

    return;
}
#endif


#if defined SOL_REPORT
/********************************************************************
 Метод вызывается обычно для печати в Журнале сведений о занимаемой
 Автоматом памяти, числе загруженных структур и так далее.
*********************************************************************/
void Automaton::Report(OFormatter &mrep)
{
    mrep.printf(
        "Automaton [%us]:\n"
        , GetName().c_str()
    );

    return;
}
#endif


// ****************************************************
// Для упрощения доступа к окружению ввода-вывода...
// ****************************************************
const Sol_IO& Automaton::GetIO() const
{
    return dict->GetIO();
}
