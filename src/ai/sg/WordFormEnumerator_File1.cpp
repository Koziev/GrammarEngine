#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordFormEnumerator_File.h>

using namespace Solarix;


WordFormEnumerator_File1::WordFormEnumerator_File1(WordEntries_File * _entries, const lem::UCString &_word)
    :entries(_entries), word(_word), icur_entry(-1), icur_form(-1), finished(false)
{
}


bool WordFormEnumerator_File1::Fetch()
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
            // �������� � ������� �������, ������������� ������� ���� � ���.
            const SG_Entry &e = entries->GetWordEntry(icur_entry);

            for (lem::Container::size_type i = icur_form + 1; i < e.forms().size(); ++i)
            {
                if (e.forms()[i].name() == word)
                {
                    // ����� ��������� ���������� ����� � ������� ������
                    icur_form = CastSizeToInt(i);
                    return true;
                }
            }

            // � ������� ������ ������ ��� ���������� ����, ���� ��������� ������.
            FetchEntry();
        }
    }

    return !finished;
}


void WordFormEnumerator_File1::FetchEntry()
{
    if (!finished)
    {
        while (icur_entry < (CastSizeToInt(entries->entry.size()) - 1))
        {
            icur_entry++;
            icur_form = UNKNOWN;

            const SG_Entry &e = entries->GetWordEntry(icur_entry);

            if (e.GetMinLen() > word.length() || e.GetMaxLen() < word.length())
            {
                // �� �������� �� �����.
                continue;
            }

            // � ���� ������ ����� ���� ����� �����?
            if (!e.GetRoot().empty() && !word.eq_begi(e.GetRoot()))
            {
                // ������ �� ��������.
                continue;
            }

            // ��������������� �������� ������, ������ ��������� �� ������ ������ �� ������� ���������.
            for (lem::Container::size_type i = 0; i < e.forms().size(); ++i)
            {
                if (e.forms()[i].name() == word)
                {
                    // ����� � ������ � ����� � ���.
                    icur_form = CastSizeToInt(i);
                    return;
                }
            }
        }

        finished = true;
    }

    return;
}

int WordFormEnumerator_File1::GetEntryKey()
{
    LEM_CHECKIT_Z(!finished);
    LEM_CHECKIT_Z(icur_entry != UNKNOWN);

    return entries->GetWordEntry(icur_entry).GetKey();
}


int WordFormEnumerator_File1::GetFormIndex()
{
    LEM_CHECKIT_Z(!finished);
    LEM_CHECKIT_Z(icur_form != UNKNOWN);
    return icur_form;
}

float WordFormEnumerator_File1::GetValue()
{
    return 1.0F;
}

int WordFormEnumerator_File1::GetMatchedWordIndex()
{
    return 0;
}

