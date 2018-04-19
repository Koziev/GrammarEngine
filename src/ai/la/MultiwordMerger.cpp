// -----------------------------------------------------------------------------
// File Multiwordmerger.cpp
//
// (c) Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project
// -----------------------------------------------------------------------------
//
// CD->15.05.2011
// LC->17.04.2018
// --------------

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/MultiwordMerger.h>

using namespace Solarix;

MultiwordMerger::MultiwordMerger(Solarix::LexicalAutomat *_la)
    : la(_la)
{
    n_max_expecting = 0;
    return;
}



// ****************************************************************************************
// ������������� ������������ ����� �� ������� ������� � ��������, ���������� ��� ������,
// ��� �� �������� - �������� ��� ��������� �����.
// ****************************************************************************************
void MultiwordMerger::ForceReady()
{
    while (!words.empty())
    {
        const lem::UCString &w0 = words.front();

        MultiLexemInfo info;
        if (la->GetDict().GetSynGram().GetEntries().IsMultilexemHead(w0, info))
        {
            int ml = info.maxlen; // � ����� ����� ����� ���������� ������������� ����� ������.

            int max_len = 0;
            for (int len = std::min(CastSizeToInt(words.size()), ml); len > 1; --len)
            {
                Solarix::Lexem lex;
                for (int i = 0; i < len; ++i)
                    lex.Add(words[i]);

                if (la->GetDict().GetSynGram().GetEntries().IsMultilexemForm(lex))
                {
                    max_len = len;
                    ready_words.push_back(lex);

                    for (int k = 0; k < max_len; ++k)
                        words.Remove(0);

                    break;
                }
            }

            if (max_len == 0)
            {
                // ���� ��������� ������������� �� �������, �������� ��������� ������ ����� �
                // �������� ������� � ������ ��������� ���������� �����.
                ready_words.push_back(words.front());
                words.Remove(0);
            }
        }
        else
        {
            // ����� �� �������� ������� �������������, ������������ ��� � ��������.
            ready_words.push_back(w0);
            words.Remove(0);
        }
    }

    // ������� ������� ������ ���� �����. 
    LEM_CHECKIT_Z(words.empty());

    return;
}

// ******************************************
// ���������� ����� �� ������� ����������.
// ******************************************
void MultiwordMerger::Push(const lem::UCString &word)
{
    if (words.empty())
    {
        // � ���� ������� ���������� ���� ���� �������������?
        MultiLexemInfo info;
        if (la->GetDict().GetSynGram().GetEntries().IsMultilexemHead(word, info))
        {
            words.push_back(word);
            n_max_expecting = info.maxlen;
        }
        else
        {
            // ���, ��� ����� ������������� ������ ��������.
            ready_words.push_back(word);
            n_max_expecting = 0;
        }
    }
    else
    {
        words.push_back(word);

        if (CastSizeToInt(words.size()) >= n_max_expecting)
        {
            Purge();
        }
    }

    return;
}



void MultiwordMerger::Purge()
{
    // �������� ����������� ������� ����� ������, �� ������� � ������ ������
    // ����� ��������� �������������.

    // ���� ����� ������� �� ���������.
    int max_len = 0;
    for (int len = CastSizeToInt(words.size()); len > 1; --len)
    {
        Solarix::Lexem lex;
        for (int i = 0; i < len; ++i)
            lex.Add(words[i]);

        if (la->GetDict().GetSynGram().GetEntries().IsMultilexemForm(lex))
        {
            max_len = len;
            ready_words.push_back(lex);

            for (int k = 0; k < max_len; ++k)
                words.Remove(0);

            break;
        }
    }

    if (max_len == 0)
    {
        // ����� ������������� �� �������, ������� ������������ � �������� ��������� ������������ ������ �����.
        ready_words.push_back(words.front());
        words.Remove(0);
    }

    n_max_expecting = 0;

    // ���� �� ������� ������ �������� �����, �� �������� ��� ������� �� ���, ��
    // ����� �� ��� ������������ �������������.
    while (!words.empty())
    {
        const lem::UCString &w0 = words.front();
        MultiLexemInfo info;
        if (la->GetDict().GetSynGram().GetEntries().IsMultilexemHead(w0, info))
        {
            n_max_expecting = info.maxlen;
            break;
        }
        else
        {
            ready_words.push_back(w0);
            words.Remove(0);
        }
    }

    return;
}


bool MultiwordMerger::IsReady(void) const
{
    return !ready_words.empty();
}


lem::UCString MultiwordMerger::Pop(void)
{
    lem::UCString w = ready_words.front();
    ready_words.Remove(0);
    return w;
}
