#if !defined SOL_SYMBOLS__H
#define SOL_SYMBOLS__H

#include <map>
#include <set>
#include <lem/noncopyable.h>
#include <lem/process.h>
#include <lem/containers.h>
#include <lem/ptr_container.h>
#include <lem/RWULock.h>
#include <lem/solarix/WordCoord.h>

namespace lem
{
    namespace Iridium
    {
        class Macro_Parser;
    }
}

namespace Solarix
{
    class SymbolEnumerator;
    class GG_Entry;
    class AlphabetStorage;
    class Dictionary;
    class GraphGram;
    struct Binarization_Options;

    class Symbols : lem::NonCopyable
    {
    private:
        AlphabetStorage *storage;
        GraphGram *gg;

#if defined LEM_THREADS
        lem::Process::RWU_Lock cs_chars, cs_for_alphabet, cs_chars1;
        lem::Process::RWU_Lock cs_count;
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        lem::MCollect<GG_Entry*> compiled_entries;
#endif

        lem::MCollect<GG_Entry*> symbols;

        std::map< int, const GG_Entry* > id2symbol;

        std::map< lem::uint32_t, Word_Coord > char2proj;
        std::multimap< lem::uint32_t, Word_Coord > char2projs;

        lem::MCollect<int> for_alphabet;
        lem::PtrCollect< std::map< lem::uint32_t, Word_Coord > > char2proj_alphabet;
        lem::PtrCollect< std::multimap< lem::uint32_t, Word_Coord > > char2projs_alphabet;
        lem::PtrCollect< std::set< lem::uint32_t > > nochar_alphabet;

        lem::Process::InterlockedInt e_count, f_count;

        void UpdateNoCharCache(GG_Entry *dummy);

    public:
        Symbols(GraphGram *_gg);

        ~Symbols(void);

        void Connect(AlphabetStorage *_storage);

        int Count(void);
        int CountForms(void);

        SymbolEnumerator* Enumerate(void);
        const GG_Entry& operator[](int id);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadEntry(
            lem::Iridium::Macro_Parser& txtfile,
            bool is_extern,
            const Binarization_Options &options
        );
        void FinishCompilation(void);
#endif

        const Word_Coord FindSymbol(lem::uint32_t code);
        const Word_Coord FindSymbol(lem::uint32_t code, int AlphabetID);
        const Word_Coord FindSymbol(lem::uint32_t code, const lem::MCollect<int> &AlphabetID);
        void FindSymbol(lem::uint32_t code, lem::MCollect<Word_Coord> &projs);
        void FindSymbol(lem::uint32_t code, lem::MCollect<Word_Coord> &projs, int AlphabetID);
        void FindSymbol(lem::uint32_t code, lem::MCollect<Word_Coord> &projs, const lem::MCollect<int> &AlphabetID);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        int FindEntry(int id_class, lem::uint32_t code);
#endif
    };
}
#endif
