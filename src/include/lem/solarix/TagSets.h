#if !defined TagSets__h
#define TagSets__h

#include <map>
#include <lem/process.h>
#include <lem/containers.h>
#include <lem/ptr_container.h>
#include <lem/ucstring.h>
#include <lem/solarix/SG_TagsList.h>


namespace Solarix
{
    class ThesaurusStorage;

    class TagSets
    {
    private:
        ThesaurusStorage *db;

        lem::PtrCollect< lem::MCollect< std::pair<int/*id_tag*/, int/*ivalue*/> > > tag_ptr;
        lem::MCollect<int> tagset_id;

        std::map< int, SG_TagsList > id2tags;

#if defined LEM_THREADS
        lem::Process::CriticalSection cs;
#endif

    public:
        TagSets();

        void Connect(ThesaurusStorage *_db);

        int Register(const lem::MCollect< std::pair<int, int> > &tags);

        int operator[](SG_TagsList tags);
        SG_TagsList operator[](int id);
    };
}

#endif
