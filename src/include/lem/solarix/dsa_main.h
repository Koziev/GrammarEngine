#ifndef SOL_DSA__H
#define SOL_DSA__H
#pragma once

#include <lem/config.h>

#include <lem/ptr_container.h>
#include <lem/solarix/lexem.h>
#include <lem/solarix/grammar.h>

namespace Solarix
{
    class SG_DeclensionTable;
    class SynGram;
    class LexiconStorage;
    class ParadigmaFinder;
    class SQL_Production;
    class SG_DeclensionForm;

    class SG_DeclensionAutomat : lem::NonCopyable
    {
    private:
        const SynGram *gram;
        LexiconStorage *storage;
        bool store_auto_tables; // нужно ли сохранять автопарадигмы в БД, или после компиляции парадигмы не нужны

#if defined LEM_THREADS
        lem::Process::RWU_Lock cs_id2decl;
#endif
        lem::MCollect<SG_DeclensionTable*> tables;
        std::map<int, const SG_DeclensionTable*> id2decl;
        std::map<lem::UCString /*название_парадигмы*/, const SG_DeclensionTable*> name2decl;
        std::map<lem::UCString /*название_парадигмы*/, int> name2id;

        ParadigmaFinder *finder;

    public:
        SG_DeclensionAutomat(const SynGram *Gram);

        void Connect(LexiconStorage *_storage);

        ~SG_DeclensionAutomat();

        const Lexem ProduceForm(
            const Lexem &base,
            int id_class,
            const SG_DeclensionForm &driver,
            const SynGram &gram
        ) const;

        void push_back(SG_DeclensionTable *p);

        const SG_DeclensionTable& GetDecl(int id);

        // *************************************************************************
        // Находит таблицу склонения по ее названию
        // *************************************************************************
        int FindDecl(const lem::UCString &paradigma_name);

        // **************************************************************************
        // Подыскивает таблицу склонения, наиболее подходящую для статьи с указанным
        // именем, принадлежащую указанному грамматическому классу. Поиск парадигмы
        // выполняется среди "auto" парадигм по соответствию регэкспа и имени статьи.
        // **************************************************************************
        const SG_DeclensionTable& GetDecl(const lem::UCString &entry_name, int iclass);

        // Возвращает id всех подходящих автопарадигм
        void FindDecl(const lem::UCString &entry_name, lem::MCollect<int>& ids);

        void AutoParadigmasMustBeStored() { store_auto_tables = true; }

        void Save_SQL(lem::OFormatter &out, lem::OFormatter &alters, const SQL_Production &sql_version) const;
    };

} // namespace 'Solarix'

#endif
