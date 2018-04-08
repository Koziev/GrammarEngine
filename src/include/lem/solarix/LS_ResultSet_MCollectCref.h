#if !defined LS_ResultSet_MCollectCref__H
#define LS_ResultSet_MCollectCref__H

#include <lem/solarix/LS_ResultSet.h>
#include <lem/containers.h>


namespace Solarix
{
    class LS_ResultSet_MCollectCref : public LS_ResultSet
    {
    private:
        int i, n;
        const lem::MCollect<int> &int_dataset;

    public:
        LS_ResultSet_MCollectCref(const lem::MCollect<int> &_list);
        virtual ~LS_ResultSet_MCollectCref() {}
        virtual bool Fetch();
        virtual int GetInt(int FieldIndex);
        virtual lem::UCString GetUCString(int FieldIndex);
        virtual lem::UFString GetUFString(int FieldIndex);
        virtual lem::FString GetFString(int FieldIndex);
    };
}

#endif

