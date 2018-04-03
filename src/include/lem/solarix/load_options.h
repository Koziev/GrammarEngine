#ifndef SOL_LOAD_OPTIONS__H
#define SOL_LOAD_OPTIONS__H
#pragma once

#include <lem/zeroed.h>
#include <lem/noncopyable.h>

namespace Solarix
{
    // This structure is passed to Dictionary::LoadModules in order to control
    // the set of loaded partitions.
    struct Load_Options : lem::NonCopyable
    {
        lem::zbool load_semnet;     // Do load thesaurus
        lem::zbool affix_table;
        lem::zbool seeker;          // Do load the fast word lookup table (necessary for search engine)
        lem::zbool stemmer;         // Do load stemmer
        lem::zbool ngrams;          // Do load N-grams database
        lem::zbool lexicon;         // ��������� �������� �������� � ������ ��� �������� ������� (true) ��� ���������� ��������� ������ �� ���� ������������� (false)
        lem::zbool lemmatizer;      // ������������
        lem::zbool force_lemmatizer_fastest_mode; // ������������� ������������ ����� ������������ �������� �������������

        Load_Options();
    };

} // namespace Solarix

#endif
