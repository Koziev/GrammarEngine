// -----------------------------------------------------------------------------
// File SG_LD_SEEKER.CPP
//
// (c) 2005 by Elijah Koziev
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// ����� LD_Seeker - ������� ����� � ����������� ������.
//
// 27.11.2005 ������� �������� ������������ �������, ��� ��� ������ ����������
//            ������ ������ ��� ������� ����� ������������ � ������
//            SynGram::GetEntry(...), � ���������� ��������� ���������� �
//            ������� ������� � ��������� ����� ����������� �������.
//
// 22.06.2006 - ���������� ������ � ������� ���� � ��������������� ����������.
//
// 15.05.2007 - ������� ���������� ������� �������� "������"
// -----------------------------------------------------------------------------
//
// CD->06.08.2005
// LC->19.11.2010
// --------------

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/LexemDictionary.h>
#include <lem/solarix/LD_Seeker.h>


using namespace std;
using namespace lem;
using namespace Solarix;


LD_Seeker::LD_Seeker()
{
    ld = nullptr;
    la = nullptr;
    hash_2_ilexem = nullptr;
    Allocate();
    return;
}



LD_Seeker::LD_Seeker(const LexemDictionary *ptr, LexicalAutomat *La)
{
    ld = ptr;
    la = La;
    hash_2_ilexem = nullptr;
    Allocate();
}



void LD_Seeker::Clear(void)
{
    ilexem_2_ientry.clear();

    if (hash_2_ilexem != nullptr)
    {
        for (int i = 0; i < 65536; i++)
            hash_2_ilexem[i].clear();
    }

    return;
}



static const LexemDictionary *Ref = NULL;
static bool HashComp(int a, int b)
{
    return Ref->get_list()[a].GetHash() > Ref->get_list()[b].GetHash();
}


LD_Seeker::LD_Seeker(const LexemDictionary *ptr, LexicalAutomat *La, SynGram &sg)
{
    hash_2_ilexem = nullptr;

    ld = ptr;
    la = La;
    Allocate();

    ilexem_2_ientry.resize(ptr->get_list().size());

    std::map< const Lexem*, int > lex_2_index;

    for (lem::Container::size_type i1 = 0; i1 < ptr->get_list().size(); ++i1)
    {
        hash_2_ilexem[ptr->get_list()[i1].GetHash16()].push_back(i1);

        lex_2_index.insert(std::make_pair(&ptr->get_list()[i1], i1));
        ilexem_2_ientry[i1] = UNKNOWN;
    }

    // ��� ��������� ������ ������ - ����������� ������ �� �������.
    Ref = ptr;
    for (int i2 = 0; i2 < 65536; ++i2)
    {
        if (hash_2_ilexem[i2].size() > 1)
            std::sort(hash_2_ilexem[i2].begin(), hash_2_ilexem[i2].end(), &HashComp);
    }

    std::unique_ptr<WordEntryEnumerator> wenum(sg.GetEntries().ListEntries());
    while (wenum->Fetch())
    {
        const int ekey = wenum->GetId();
        const SG_Entry &e = wenum->GetItem();

        for (auto& form : e.forms())
        {
            // ��������� �� ������� �����������.
            const Lexem *form_name = &form.name();

            auto it = lex_2_index.find(form_name);

            if (it != lex_2_index.end())
                ilexem_2_ientry[it->second] = ekey;
        }
    }

    lex_2_index.clear();

    return;
}



void LD_Seeker::Allocate(void)
{
    // �� ������ ������ �� ������ �������� ���-����
    LEM_CHECKIT_Z(hash_2_ilexem == nullptr);
    hash_2_ilexem = new lem::MCollect<int>[65536];
    return;
}



LD_Seeker::~LD_Seeker(void)
{
    delete[] hash_2_ilexem;
    hash_2_ilexem = nullptr;
}


#if defined SOL_CAA
int LD_Seeker::Find(const UCString &x, bool dynforms) const
{
#if LEM_DEBUGGING==1
    const int xi = x.GetHash16();
#endif

    const lem::MCollect<int> &hlist = hash_2_ilexem[x.GetHash16()];

#if LEM_DEBUGGING==1
    const int nx = hlist.size();
#endif

    if (!hlist.empty())
    {
        // ����������, �� ������� ��������� ������� � hlist, ������������� � �������
        // ����������� ����� �����. ������� �� ����� ������������ ��������� ���
        // �������� ����������� ������ ���������
        const UCString::hash_type H = x.GetHash();

        int i0 = 0;
        int i1 = CastSizeToInt(hlist.size()) - 1;
        int h0 = ld->get_list()[hlist.front()].GetHash();
        int h1 = ld->get_list()[hlist.back()].GetHash();

        // ��� �������� ����� ���������� ���-���
        if (h0 == h1)
        {
            for (Container::size_type i = 0; i < hlist.size(); i++)
            {
                int ilexem = hlist[i];

                //const UCString &l = ld->get_list()[ilexem];
                //const int h16 = Calc_Hash(l);

                if (ld->get_list()[ilexem] == x)
                    // ��� ������ ������ �� ���������� ������� - ���������� ������ �����������
                    // ��������� ���������� ��������� ������, ��� ��� ������ ������ ����� ���������
                    // ���������. �� ����� ��������������� ������ ��������� ������ ������� �
                    // ������ ������. 
                    return ilexem_2_ientry[ilexem];
            }
        }
        else
        {
            int i_pos = UNKNOWN;

            while (true)
            {
                if ((i1 - i0) < 4)
                {
                    for (int i = i0; i <= i1; i++)
                        if (ld->get_list()[hlist[i]].GetHash() == H)
                        {
                            i_pos = i;
                            break;
                        }

                    break;
                }

                int i_mid = (i1 + i0) / 2;
                int h_mid = ld->get_list()[hlist[i_mid]].GetHash();

                if (h_mid == H)
                {
                    i_pos = i_mid;
                    break;
                }

                if (h_mid < H)
                {
                    i1 = i_mid;
                    h1 = h_mid;
                }
                else
                {
                    i0 = i_mid;
                    h0 = h_mid;
                }
            }

            if (i_pos != UNKNOWN)
            {
                // �������� �����, ������ ������ ������� � ����������� ������.

                while (i_pos > 0)
                    if (ld->get_list()[hlist[i_pos - 1]].GetHash() != H)
                        break;
                    else
                        i_pos--;

                // ������ ���������� �� ������� � ����� �����
                while (i_pos < CastSizeToInt(hlist.size()))
                    if (ld->get_list()[hlist[i_pos]].GetHash() != H)
                        break;
                    else if (ld->get_list()[hlist[i_pos]] == x)
                    {
                        //mout->printf( "[%us]\n", ld->get_list()[ hlist[i_pos] ].c_str() );
                        return ilexem_2_ientry[hlist[i_pos]];
                    }
                    else
                        i_pos++;
            }
        }
    }


    if (dynforms)
    {
        // ����� ���� ������������ ���� ��������� �����������, �� ��� ���
        // ������� ��������� ����������� ���������� �� ���� (���������� ��������� �
        // ���������), �� ���� ����������� ������������� �� �������� ����� �������
        // ��������.

        return la->Project_Dynforms(x, UNKNOWN, *this);
    }

    return UNKNOWN;
}
#endif


/*
#if defined SOL_CAA
bool LD_Seeker::Normalize(const UCString &word, UCString &normalized) const
{
    return false;
}
#endif
*/

#if defined SOL_CAA
// ���� ������� ����, ��� ������� ������ ��������� � 'x'
bool LD_Seeker::FindRoots(const UCString &x, std::set<int> &result) const
{
    bool found = false;
    for (lem::Container::size_type i = 0; i < ld->get_list().size(); i++)
    {
        const UCString &kw = ld->get_list()[i];

        if (kw.eq_beg(x))
        {
            found = true;
            result.insert(ilexem_2_ientry[i]);
        }
    }

    return found;
}
#endif


#if defined SOL_SAVEBIN
void LD_Seeker::SaveBin(lem::Stream &bin) const
{
    bin.write_int(ilexem_2_ientry.size());
    bin.write(&*ilexem_2_ientry.begin(), sizeof(ilexem_2_ientry.front())*ilexem_2_ientry.size());

    for (int i = 0; i < 65536; i++)
        hash_2_ilexem[i].SaveBin(bin);
}
#endif


#if defined SOL_LOADBIN
void LD_Seeker::LoadBin(lem::Stream &bin, Solarix::Dictionary *dict, const LexemDictionary *_ld)
{
    LEM_CHECKIT_Z(dict);

    la = &dict->GetLexAuto();
    ld = _ld;

    LoadBin(bin);
    return;
}


void LD_Seeker::LoadBin(lem::Stream &bin)
{
    bin.Check();

    const int n = bin.read_int();
    ilexem_2_ientry.resize(n);
    bin.read(&*ilexem_2_ientry.begin(), sizeof(ilexem_2_ientry.front())*ilexem_2_ientry.size());

    for (int i = 0; i < 65536; i++)
        hash_2_ilexem[i].LoadBin(bin);

    bin.Check();

    return;
}
#endif
