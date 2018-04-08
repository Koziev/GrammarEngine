#if !defined LexemeEnumerator__H
#define LexemeEnumerator__H

namespace Solarix
{
    class Lexem;
    class LexemeEnumerator
    {
    public:
        LexemeEnumerator() {}
        virtual ~LexemeEnumerator() {}

        virtual bool Fetch() = 0;
        virtual const Lexem* Get(Solarix::Lexem &lex) = 0;
    };
}

#endif
