#include "NGramPrinter.h"

using namespace std;
using namespace lem;
using namespace Solarix;

NGramPrinter::NGramPrinter() : NGramHandler()
{
}

bool NGramPrinter::Do(
    Solarix::Ngrams & ngrams,
    int id_ngram,
    int freq,
    int id_word1,
    const lem::UCString &word1
)
{
    mout->printf("%vf6[%vn%us%vf6]%vn %vfE%d%vn\n", word1.c_str(), freq);
    return true;
}

bool NGramPrinter::Do(
    Solarix::Ngrams & ngrams,
    int id_ngram,
    int freq,
    int id_word1,
    int id_word2,
    const lem::UCString &word1,
    const lem::UCString &word2
)
{
    mout->printf("%vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vfE%d%vn\n", word1.c_str(), word2.c_str(), freq);
    return true;
}

bool NGramPrinter::Do(
    Solarix::Ngrams &ngrams,
    int id_ngram,
    int freq,
    int id_word1,
    int id_word2,
    int id_word3,
    const lem::UCString &word1,
    const lem::UCString &word2,
    const lem::UCString &word3
)
{
    mout->printf("%vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vfE%d%vn\n", word1.c_str(), word2.c_str(), word3.c_str(), freq);
    return true;
}

bool NGramPrinter::Do(
    Solarix::Ngrams &ngrams,
    int id_ngram,
    int freq,
    int id_word1,
    int id_word2,
    int id_word3,
    int id_word4,
    const lem::UCString &word1,
    const lem::UCString &word2,
    const lem::UCString &word3,
    const lem::UCString &word4
)
{
    mout->printf("%vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vfE%d%vn\n", word1.c_str(), word2.c_str(), word3.c_str(), word4.c_str(), freq);
    return true;
}

bool NGramPrinter::Do(
    Solarix::Ngrams &ngrams,
    int id_ngram,
    int freq,
    int id_word1,
    int id_word2,
    int id_word3,
    int id_word4,
    int id_word5,
    const lem::UCString &word1,
    const lem::UCString &word2,
    const lem::UCString &word3,
    const lem::UCString &word4,
    const lem::UCString &word5
)
{
    mout->printf("%vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vf6[%vn%us%vf6]%vn %vfE%d%vn\n", word1.c_str(), word2.c_str(), word3.c_str(), word4.c_str(), word5.c_str(), freq);
    return true;
}


