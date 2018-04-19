#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordFormEnumerator_File.h>

using namespace Solarix;


WordFormEnumerator_File3::WordFormEnumerator_File3(
    WordEntries_File * _entries,
    const lem::MCollect<lem::UCString> &_words
)
    :entries(_entries), words(_words), icur_entry(-1), icur_form(-1), imatched_word(-1), finished(false)
{
}


bool WordFormEnumerator_File3::Fetch()
{
    if (!finished)
    {
        if (icur_entry == -1)
        {
            icur_entry = 0;
            FetchEntry();
        }
        else
        {
            // работаем с текущей статьей, просматриваем остаток форм в ней.
            const SG_Entry &e = entries->GetWordEntry(icur_entry);

            for (lem::Container::size_type i = icur_form + 1; i < e.forms().size(); ++i)
            {
                imatched_word = words.find(e.forms()[i].name());
                if (imatched_word != UNKNOWN)
                {
                    // нашли очередную подходящую форму в текущей статье
                    icur_form = CastSizeToInt(i);
                    return true;
                }
            }

            // в текущей статье больше нет подходящих форм, ищем следующую статью.
            FetchEntry();
        }
    }

    return !finished;
}


void WordFormEnumerator_File3::FetchEntry()
{
    if (!finished)
    {
        while (icur_entry < (CastSizeToInt(entries->entry.size()) - 1))
        {
            icur_entry++;
            icur_form = UNKNOWN;

            const SG_Entry &e = entries->GetWordEntry(icur_entry);

            for (lem::Container::size_type k = 0; k < words.size(); ++k)
            {
                const lem::UCString &word = words[k];

                if (e.GetMinLen() > word.length() || e.GetMaxLen() < word.length())
                {
                    // не подходит по длине.
                    continue;
                }

                // в этой статье может быть такая форма?
                if (!e.GetRoot().empty() && !word.eq_begi(e.GetRoot()))
                {
                    // корень не подходит.
                    continue;
                }

                // предварительные проверки прошли, теперь пройдемся по формам статьи до первого попадания.
                for (lem::Container::size_type i = 0; i < e.forms().size(); ++i)
                {
                    imatched_word = words.find(e.forms()[i].name());
                    if (imatched_word != UNKNOWN)
                    {
                        // нашли и статью и форму в ней.
                        icur_form = CastSizeToInt(i);
                        return;
                    }
                }
            }
        }

        finished = true;
    }

    return;
}

int WordFormEnumerator_File3::GetEntryKey()
{
    LEM_CHECKIT_Z(!finished);
    LEM_CHECKIT_Z(icur_entry != UNKNOWN);

    return entries->GetWordEntry(icur_entry).GetKey();
}


int WordFormEnumerator_File3::GetFormIndex()
{
    LEM_CHECKIT_Z(!finished);
    LEM_CHECKIT_Z(icur_form != UNKNOWN);
    return icur_form;
}


float WordFormEnumerator_File3::GetValue()
{
    return 1.0F;
}

int WordFormEnumerator_File3::GetMatchedWordIndex()
{
    return imatched_word;
}
