#if !defined ClassList__H
#define ClassList__H


namespace lem
{
    class UCString;
    namespace Iridium
    {
        class Macro_Parser;
    }
}

namespace Solarix
{
    class GramClass;
    class Grammar;
    class ClassEnumerator;

    class ClassList
    {
    protected:
        ClassList() {}

    public:
        virtual ~ClassList() {}

        virtual const GramClass& operator[](int id) = 0;
        virtual GramClass& GetClass(int id) = 0;

        virtual int Find(const lem::UCString &name) = 0;
        virtual int Count() = 0;
        virtual ClassEnumerator* Enumerate() = 0;

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual GramClass* LoadTxt(
            lem::Iridium::Macro_Parser &txtfile,
            bool IsRealized
        ) = 0;
#endif
    };
}

#endif
