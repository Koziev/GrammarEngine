#if !defined TextAnalysisSession__H
#define TextAnalysisSession__H

#include <lem/noncopyable.h>
#include <lem/solarix/TextRecognitionParameters.h>

namespace Solarix {

    class Dictionary;
    class TrTrace;
    class LA_SynPatternTrees;
    class BasicLexer;
    class Res_Pack;
    class PhrasoBlock;
    class TreeMatchingExperience;
    class TrWideContext;
    class SynPatternTreeNodeMatchingResults;
    class ElapsedTimeConstraint;

    // —труктура дл€ хранени€ промежуточных результатов анализа предложени€ или цепочки предложений.
    class TextAnalysisSession : lem::NonCopyable
    {
    protected:
        Dictionary * dict;
        TrTrace * trace;
        LA_SynPatternTrees * rules;
        BasicLexer * lexer;
        Res_Pack * pack;

        virtual void Analyze(bool ApplyPatterns, bool DoSyntaxLinks, const ElapsedTimeConstraint &constraints);

        SynPatternTreeNodeMatchingResults* TopDownParsing(
            bool ApplyPatterns,
            bool DoSyntaxLinks,
            TreeMatchingExperience & experience,
            const ElapsedTimeConstraint & constraints
        );

    public:
        TextRecognitionParameters params;
        bool FindFacts;

    public:
        TextAnalysisSession(Solarix::Dictionary * _dict, TrTrace * _trace);

        virtual ~TextAnalysisSession();

        int GetLanguageID() const { return params.GetLanguageID(); }

        BasicLexer& GetLexer() { return *lexer; }

        // ¬озвращаетс€ ссылка на контейнер с результатами - набором альтернативных вариантов св€зываний.
        const Res_Pack& GetPack() const { return *pack; }
        Res_Pack* PickPack() { Res_Pack *p = pack; pack = nullptr; return p; }
    };

}

#endif
