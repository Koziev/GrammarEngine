#if !defined LD_Seeker__H
#define LD_Seeker__H

#include <vector>
#include <lem/containers.h>

namespace Solarix
{
    class SynGram;
    class LexicalAutomat;
    class LexemDictionary;

    class LD_Seeker
    {
    private:
        const LexemDictionary *ld;
        LexicalAutomat *la;

        std::vector<int> ilexem_2_ientry; // ��� �������� ������ ������� � ����������� SG
                                          // � ����� ��������� ������, ����� ������� �������
                                          // ������������.


        lem::MCollect<int> *hash_2_ilexem;

        void Allocate();

    public:
        LD_Seeker();
        LD_Seeker(const LexemDictionary *ptr, LexicalAutomat *La);
        LD_Seeker(const LexemDictionary *ptr, LexicalAutomat *La, SynGram &sg);

        ~LD_Seeker();

        void Clear();

        //void Preset( Solarix::Dictionary &dict );

#if defined SOL_CAA
// ���������� IENTRY ������ ��������� ������ � ���������� �����������
        int Find(const UCString &x, bool dynforms) const;
#endif

#if defined SOL_CAA
        bool FindRoots(const UCString &x, std::set<int> &result) const;
#endif

        //#if defined SOL_CAA
        //bool Normalize( const UCString &word, UCString &normalized  ) const;
        //#endif

#if defined SOL_SAVEBIN
        void SaveBin(lem::Stream &bin) const;
#endif

#if defined SOL_LOADBIN 
        void LoadBin(lem::Stream &bin, Solarix::Dictionary *dict, const LexemDictionary *ptr);
        void LoadBin(lem::Stream &bin);
#endif
    };
}
#endif
