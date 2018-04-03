#if !defined GG_Coordinates__H
#define GG_Coordinates__H

#include <map>
#include <lem/process.h>
#include <lem/containers.h>
#include <lem/ptr_container.h>
#include <lem/ucstring.h>
#include <lem/solarix/coordinate.h>
#include <lem/solarix/CoordList.h>

namespace lem
{
    class UCString;
}

namespace Solarix
{
    class AlphabetStorage;
    class GraphGram;

    class GG_Coordinates : public CoordList
    {
    private:
        GraphGram *gg;
        AlphabetStorage *db;

        lem::PtrCollect< GramCoord > coord_ptr;
        lem::MCollect<int> coord_id;

        std::map< int /*id*/, int/*index*/ > id2coord;
        std::map< lem::UCString, int > name2id;

#if defined LEM_THREADS
        lem::Process::CriticalSection cs;
#endif

        void AddNewCoord(GramCoord *new_coord, bool IsRealized);
        GramCoord* Get(int id);
        int Id2Index(int id);

    public:
        GG_Coordinates(GraphGram *_sg);
        virtual ~GG_Coordinates() {}

        void Connect(AlphabetStorage *_db);

        virtual const GramCoord& operator[](int id) override;
        virtual GramCoord& GetCoord(int id) override;

        virtual int Find(const lem::UCString &name) override;
        virtual int Count() override;

        virtual CoordEnumerator* Enumerate() override;

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual GramCoord* LoadTxt(
            lem::Iridium::Macro_Parser &txtfile,
            bool IsRealized
        ) override;
#endif
    };
}

#endif
