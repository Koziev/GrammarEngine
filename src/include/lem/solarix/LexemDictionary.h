#if !defined LexemDictionary__H
#define LexemDictionary__H

#include <lem/solarix/SolidRef.h>

namespace Solarix
{
    class SynGram;
    class LexicalAutomat;
    class LD_Seeker;

    class LexemDictionary : public SolidRef<Lexem>
    {
    public:
        LexemDictionary(int Reserve = 0);
        ~LexemDictionary();

#if defined SOL_SAVEBIN
        void SaveBin(lem::Stream &bin) const;
#endif

#if defined SOL_LOADBIN 
        void LoadBin(lem::Stream &bin);
#endif

        LD_Seeker* Get_Seeker(SynGram &sg, LexicalAutomat *La);

#if defined SOL_LOADBIN
        LD_Seeker* Load_Seeker(lem::Stream &bin, LexicalAutomat *La);
#endif
    };

}

#endif
