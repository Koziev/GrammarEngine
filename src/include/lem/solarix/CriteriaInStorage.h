#ifndef SOL_CRITERIA_IN_STORAGE__H
#define SOL_CRITERIA_IN_STORAGE__H
#pragma once

#include <map>
#include <lem/process.h>
#include <lem/solarix/criterion.h>
#include <lem/ptr_container.h>

namespace Solarix
{
    class CriteriaStorage;

    class CriteriaInStorage : public Criteria_List
    {
    private:
#if defined LEM_THREADS
        lem::Process::CriticalSection cs;
#endif

        CriteriaStorage *storage;
        std::map< lem::UCString, int > name2id;
        std::map< int, const Criterion* > id2x;
        lem::PtrCollect<Criterion> list;

    public:
        CriteriaInStorage();

        void Connect(CriteriaStorage *_storage);

        virtual ~CriteriaInStorage() {}

#if defined SOL_LOADTXT
        virtual void LoadTxt(const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile) override;
#endif

        virtual int Find(const lem::UCString &name) override;
        virtual const Criterion& operator[](int id) override;
        const Criterion& operator[](const lem::UCString &name);

        void SaveBin(lem::Stream &bin) const;
        void LoadBin(lem::Stream &bin);

        virtual CriterionEnumerator* Enumerate();
    };
} // end of namespace 'Solarix'

#endif
