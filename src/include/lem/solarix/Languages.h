#if !defined Languages__h
#define Languages__h

#include <map>
#include <lem/process.h>
#include <lem/solarix/SG_Language.h>

namespace lem
{
    class OFormatter;
    namespace Iridium
    {
        class Macro_Parser;
    }
}

namespace Solarix
{
    class LexiconStorage;
    class LanguageEnumerator;
    class SynGram;

    class Languages
    {
    private:
        SynGram *sg;
        LexiconStorage *db;

        std::map< lem::UCString /*name*/, int /*id*/> name2id;
        std::map< int, int > id2index;
        lem::PtrCollect<SG_Language> lang_ptr;

#if defined LEM_THREADS
        lem::Process::CriticalSection cs;
#endif

        SG_Language* GetByIndex(int i);

    public:
        Languages(SynGram *_sg);

        void Connect(LexiconStorage *_db);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile);
#endif

        int Count();

        int Find(const lem::UCString &name);
        const SG_Language& operator[](int id);

        LanguageEnumerator* Enumerate();
    };
}

#endif
