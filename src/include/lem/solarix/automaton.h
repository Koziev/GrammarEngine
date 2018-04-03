#ifndef SOL_AUTOMATON__H
#define SOL_AUTOMATON__H
#pragma once

#include <lem/sol_io.h>
#include <lem/fstring.h>
#include <lem/noncopyable.h>
#include <lem/solarix/solarix_binarization_options.h>
#include <lem/solarix/criterion.h>
#include <lem/solarix/form_table.h>
#include <lem/solarix/load_options.h>
#include <lem/solarix/sql_production.h>

namespace Solarix
{
    using lem::Iridium::BethToken;
    using lem::Iridium::Macro_Parser;
    using lem::OFormatter;
    using lem::Stream;

    class Dictionary;

    class Automaton : lem::NonCopyable
    {
    private:
        bool was_loaded;    // true после первой загрузки из txt-файла.
        int index;          // Индекс (идентификатор) автомата.

        // Запрещаем копировать Автомат (it is frightening to think what would
        // have happened...)
        Automaton(const Automaton&)=delete;
        void operator=(const Automaton&)=delete;

    protected:
        Criteria_List *param;  // Список управляющих параметров.
        Dictionary *dict;      // Указатель на Словарь, поддерживающий Автомат.

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual bool ProcessLexem(
            const BethToken &t,
            Macro_Parser& txt,
            const Binarization_Options &options
        );

        void load(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );

        /**************************************************************************
         Метод вызывается перед первой загрузкой содержимого Автомата из текстового
         файла. Может быть перегружен производными классами, чтобы реализовать
         какую-либо подготовку к считыванию. Следует помнить, что описание автомата
         может быть разнесено в несколько секций с одинаковой шапкой: например,
         для Алфавита в одном файле секция Графической Грамматики содержит
         определения цифр, в другом - определения латиницы, и так далее. Но только
         перед считыванием первой секции будет вызван метод PreLoad.
        ***************************************************************************/
        virtual void PreLoad(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        ) {}

        /************************************************************
         Метод вызывается после загрузки каждой секции для выполнени
         любых ритуалов над загруженной информацией. Например, можно
         организовать второй проход по секции для разрешения ссылок
         вперед.
        *************************************************************/
        virtual void PostRead(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        ) {}
#endif

    public:
        Automaton(int Index);
        virtual ~Automaton();

        virtual void SetDictPtr(Dictionary *d);

        inline Criteria_List& params() const { return *param; }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual void Optimize() {}
#endif

        virtual void BeforeSyntaxRecompilation() {}

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual void LoadTxt(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );

        /*************************************************************************
         После полной загрузки Словаря из текстового файла необходимо подготовить
         все подсистемы к работе в составе Вербальной Машины. Для этого классом
         Dictionary вызывается данный виртуальный метод, переопределяемый
         производными классами Автоматов.
        **************************************************************************/
        virtual void Prepare(const lem::Path &outdir, const Binarization_Options &opts) {}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual bool ProcessLexem2(
            const BethToken &t,
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );
#endif

        inline int GetIndex() const { return index; }

        virtual void PrintMap(OFormatter &dst_stream);

#if defined SOL_LOADBIN
        virtual void LoadBin(lem::Stream &bin, const Load_Options &opt);
#endif

#if defined SOL_LOADBIN
        // Метод вызывается после загрузки автомата из бинарного файла
        // Словаря и может перегружаться автоматами для выполнения
        // развертывания неких своих структур.
        virtual void AfterLoadBin() {}
        virtual void DictionaryLoaded() {}
#endif

#if defined SOL_SAVEBIN
        virtual void SaveBin(lem::Stream &bin) const;
#endif


#if defined SOL_CAA
// ******************************************************************
// Необходимо выполнить инициализацию - подготовку Автомата к работе.
// ******************************************************************
        virtual void Initialize() {}

        // ********************************************************
        // Производится финализация (завершение работы автомата).
        // ********************************************************
        virtual void Finalize() {}
#endif

        /*********************************************************************
         Возвращаем условное имя Автомата. Так как данный класс сам по себе не
         используется для создания объектов-автоматов, то функция нулевая,
         а производные классы перегружают эту функцию.
        **********************************************************************/
        virtual const lem::UCString GetName(void) const = 0;

        inline Dictionary& GetDict() const { return *dict; }

        const lem::Sol_IO& GetIO() const;

#if defined SOL_REPORT
        // Метод распечатывает краткую сводку о загрузке Автомата.
        virtual void Report(lem::OFormatter &dst_stream);
        virtual void Save_SQL(lem::OFormatter &txt, OFormatter &alters, const SQL_Production &sql_version) {}
        virtual void SaveRules_SQL(lem::OFormatter &txt, OFormatter &alters, const SQL_Production &sql_version) {}
#endif
    };

    // Символические имена секций с информацией для Автоматов: используются,
    // к примеру, в директиве automat XXX { ... } языка ПРИИСК. Лексическое
    // наполнение констант - в файле SOL_AUNA.CPP
    extern const wchar_t SOL_GRAPHAUTO_MARK[];
    extern const wchar_t SOL_SYNAUTO_MARK[];
    extern const wchar_t SOL_LEXAUTO_MARK[];
    extern const wchar_t SOL_ALEPHAUTO_MARK[];

} // namespace 'Solarix'

#endif
