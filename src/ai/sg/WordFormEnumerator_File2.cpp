#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordFormEnumerator_File.h>

using namespace Solarix;


WordFormEnumerator_File2::WordFormEnumerator_File2(
    WordEntries_File * _entries,
    const lem::UCString &_word,
    const WordEntries_LookUpItem & _lexem_slot,
    const WordEntries_LookUp & _lookup_table
)
    :entries(_entries), word(_word), lexem_slot(_lexem_slot), lookup_table(_lookup_table), icur_entry(-1), icur_form(-1), finished(false)
{
}


bool WordFormEnumerator_File2::Fetch()
{
    if (!finished)
    {
        if (icur_entry == -1)
        {
            FetchEntry();
        }
        else
        {
            // работаем с текущей статьей, просматриваем остаток форм в ней.
            const int id_entry = lookup_table.entry_index[lexem_slot.start_index + icur_entry];
            const SG_Entry &e = entries->GetEntryByKey(id_entry);

            for (lem::Container::size_type i = icur_form + 1; i < e.forms().size(); ++i)
            {
                if (e.forms()[i].name() == word)
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


void WordFormEnumerator_File2::FetchEntry()
{
    if (!finished)
    {
        if (icur_entry < lexem_slot.len - 1)
        {
            icur_entry++;
            icur_form = UNKNOWN;

            const int entry_id = lookup_table.entry_index[lexem_slot.start_index + icur_entry];
            const SG_Entry &e = entries->GetEntryByKey(entry_id);

            // пройдемся по формам статьи до первого попадания.
            for (lem::Container::size_type i = 0; i < e.forms().size(); ++i)
            {
                if (e.forms()[i].name() == word)
                {
                    // нашли и статью и форму в ней.
                    icur_form = CastSizeToInt(i);
                    return;
                }
            }
        }

        finished = true;
    }

    return;
}

int WordFormEnumerator_File2::GetEntryKey()
{
    LEM_CHECKIT_Z(!finished);
    LEM_CHECKIT_Z(icur_entry != UNKNOWN);

    const int entry_id = lookup_table.entry_index[lexem_slot.start_index + icur_entry];
    return entry_id;
}


int WordFormEnumerator_File2::GetFormIndex()
{
    LEM_CHECKIT_Z(!finished);
    LEM_CHECKIT_Z(icur_form != UNKNOWN);
    return icur_form;
}

float WordFormEnumerator_File2::GetValue()
{
    return 1.0F;
}

int WordFormEnumerator_File2::GetMatchedWordIndex()
{
    return 0;
}
