#ifndef CriterionEnumerator__H
#define CriterionEnumerator__H
#pragma once

#include <lem/noncopyable.h>

namespace Solarix
{
    class Criterion;

    class CriterionEnumerator : lem::NonCopyable
    {
    protected:
        CriterionEnumerator() {}

    public:
        virtual ~CriterionEnumerator() {}

        virtual bool Fetch() = 0;
        virtual int GetId() = 0;
        virtual const Criterion& GetItem() = 0;
    };
}

#endif
