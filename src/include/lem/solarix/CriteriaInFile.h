#ifndef SOL_CRITERIA_IN_FILE__H
#define SOL_CRITERIA_IN_FILE__H
#pragma once

#include <lem/solarix/criterion.h>

namespace Solarix
{
    class CriteriaInFile : public Criteria_List
    {
    private:
        lem::Collect<Criterion> list;
        friend class CriterionEnumeratorInFile;

    public:
        CriteriaInFile() {}

        virtual ~CriteriaInFile() {}

#if defined SOL_LOADTXT
        virtual void LoadTxt(const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile) override;
#endif

        virtual int Find(const lem::UCString &name) override;
        virtual const Criterion& operator[](int id) override;
        virtual const Criterion& operator[](const lem::UCString &name) override;

        virtual void SaveBin(lem::Stream &bin) const override;
        virtual void LoadBin(lem::Stream &bin) override;

        virtual CriterionEnumerator* Enumerate() override;
    };

} // end of namespace 'Solarix'

#endif
