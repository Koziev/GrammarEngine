#ifndef SOL_COMPILER__H
#define SOL_COMPILER__H
#pragma once

#if defined SOL_LOADTXT

#include <lem/solarix/solarix_binarization_options.h>
#include <lem/console_application.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/SG_Affixtable.h>

namespace Solarix
{
    class Compiler
    {
    public:
        lem::Ptr<Dictionary> sol_id;

    private:
        lem::Ptr<Solarix::Affix_Table> affix_table;
        const lem::CodeConverter* cp; // кодовая страница для исходников

        lem::PtrCollect<lem::UFString> xml_injection; // добавочные строки в dictionary.xml

        void CompileAsciiProject(lem::Stream &proj_file);
        void CompileXmlProject(lem::Stream &proj_file);

    public:
        Compiler(lem::OFormatter &echo, lem::OFormatter &err, const Dictionary_Config &cfg);
        ~Compiler();

        string defines;    // список define'ов
        int trace_level;   // детальность сообщений по ходу трансляции
        UFString root_dir; // Каталог с текстами компилируемого словаря

        Binarization_Options bin_options; // Options to control storing some parts in dictionary

        void CompileProject(lem::Stream &proj_file);
        void CompileFile(lem::Stream &sol_file);

        void Optimize();
        void PostCompile(const lem::Path &outdir);

        // Создается и инициализируется таблица для стеммера
        void CreateAffixTable();

        // Создается пустая таблица для стеммера
        void EmptyAffixTable();

        void SaveAlphabet(const lem::Path &db_path) const;
        void SaveMorphology(lem::Stream &bin, const lem::Path &lexicon_db_path);
        void SaveSeeker(lem::Stream &bin) const;
        void SaveAffixes(lem::Stream &bin) const;
        void SaveThesaurusDb(const lem::Path &p) const;
        void SavePrefixEntrySearcher(const lem::Path &p) const;
        void SaveLemmatizer(const lem::Path &p, bool verbose) const;
        void ParadigmasStorage(bool save);

        const Solarix::Dictionary& GetDictionary() const;

        void StemmerPrintInfo(lem::OFormatter &out) const;

        inline void SetCodeConverter(const lem::CodeConverter *c) { cp = c; }

        lem::UFString GetDictionaryXmlString() const;
    };

} // end of namespace 'Solarix'

#endif

#endif
