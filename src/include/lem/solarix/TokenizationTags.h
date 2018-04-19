#ifndef TOKENIZATION_TAGS__H
#define TOKENIZATION_TAGS__H
#pragma once

#include <lem/noncopyable.h>

namespace Solarix
{
    class GramCoordPair;
    class Word_Form;
    class Dictionary;

    class TokenizationTags : lem::NonCopyable
    {
    public:
        TokenizationTags() {}
        virtual ~TokenizationTags() {}

        // проходит ли указанная словоформа данных фильтр
        virtual int Score(const Word_Form &wf, const Dictionary &dict) const = 0;

        virtual TokenizationTags* clone() const = 0;
    };

    class TF_NoFilter : public TokenizationTags
    {
    public:
        TF_NoFilter() {}

        virtual int Score(const Word_Form &, const Dictionary &) const { return 0; }
        virtual TokenizationTags* clone(void) const { return new TF_NoFilter(); }
    };


    class TF_CaseFilter : public TokenizationTags
    {
    public:
        int id_CharCasing;
        int required_casing; // id состояния для координаты CharCasing, которая должна быть у слова
        int id_state_lower;

    public:
        TF_CaseFilter(int id_coord, int id_state, int id_lower) :id_CharCasing(id_coord), required_casing(id_state), id_state_lower(id_lower) {}

        virtual int Score(const Word_Form &wf, const Dictionary &dict) const;
        virtual TokenizationTags* clone() const;
    };


}

#endif
