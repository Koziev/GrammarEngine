#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordFormEnumerator_File.h>

using namespace Solarix;


WordFormEnumeratorFuzzy_File::WordFormEnumeratorFuzzy_File(
    WordEntries_File * _entries,
    const lem::UCString &_mask,
    float _min_val
)
    : WordFormEnumeratorListing_File(_entries), mask(_mask), min_val(_min_val)
{
    LEM_CHECKIT_Z(!_mask.empty());
    LEM_CHECKIT_Z(_min_val >= 0.0F && _min_val <= 1.0F);
    return;
}


void WordFormEnumeratorFuzzy_File::Prefetch()
{
    const Solarix::LexemDictionary &lex0 = entries->ml_ref;
    const MCollect<Solarix::Lexem> &lex = lex0.get_list();

    int min_ival = int(100 * min_val);

    std::map<const Solarix::Lexem*, int> ptr_lex;
    for (lem::Container::size_type i = 0; i < lex.size(); ++i)
    {
        const int l = lem::Fuzzy::get_like_percent((const lem::UCString&)mask, (const lem::UCString&)lex[i]);

        if (l > min_ival)
        {
            ptr_lex.insert(std::make_pair(&lex[i], l));
        }
    }

    // Имеем список указателей на подходящие лексемы и коэффициент похожести.
    // Соберем список индексов словарных статей.

    const int ne = entries->size();
    for (int i = ne - 1; i >= 0; --i)
    {
        const Solarix::SG_Entry &e = entries->GetWordEntry(i);

        for (lem::Container::size_type j = 0; j < e.forms().size(); ++j)
        {
            const SG_EntryForm &f = e.forms()[j];
            const Solarix::Lexem *ptr = &f.name();

            std::map<const Solarix::Lexem*, int>::const_iterator it = ptr_lex.find(ptr);
            if (it != ptr_lex.end())
            {
                const int l = it->second; // степень похожести 0...100
                WordFormEnumeratorListing_File::Hit h;
                h.ekey = e.GetKey();
                h.iform = CastSizeToInt(j);
                h.val = 0.01F*l;
                hits.push_back(h);
            }
        }
    }

    // Отсортируем его так, чтобы сначала шли самые достоверные
    std::stable_sort(hits.begin(), hits.end(), WordFormEnumeratorListing_File::HitsComparator);

    return;
}
