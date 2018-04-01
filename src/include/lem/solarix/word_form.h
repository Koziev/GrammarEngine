// -----------------------------------------------------------------------------
// File WORD_FORM.H
//
// (c) 1995 Koziev Elijah
// Licensed under LGPL 
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// ����� Word_Form � ��� ��������� ����� - �������� ����������.
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->30.03.2018
// --------------

#ifndef SOL_WORDFORM__H
#define SOL_WORDFORM__H
#pragma once

#include <set>
#include <lem/containers.h>
#include <lem/process.h>
#include <lem/math/fp1.h>

#include <lem/solarix/compilation_context.h>
#include <lem/solarix/coord_pair.h>
#include <lem/solarix/lexem.h>

namespace lem
{
    namespace Iridium { class Macro_Parser; }
    class Stream;
}

namespace Solarix
{
    using lem::Real1;
    using lem::Iridium::Macro_Parser;
    using lem::Stream;

    class SynGram;

    // ************************************************************
    // ����� ������������ ���������� �, ������������, ����������.
    // ************************************************************
    class Word_Form
    {
    private:
        static lem::Process::InterlockedInt seq_iversion;
        int iversion;

        RC_Lexem name;      // ����������� ���������� ���������� � �������� ��������
        RC_Lexem normalized; // � ��������������� ��������� � ��������������� ��������

        CPE_Array pair;     // ������ ������������ ��� (��������� � ���������) ��� ������.

        int entry_key;      // ���� ������� ������ (������) � ������ �������������� ����������.

        //Real1 val;           // ������ ������������� ���������� ����������
        float score;           // �������
        int origin_pos;      // ��������� ������� � ����������� (UNKNOWN, ���� ����������).

        lem::Ptr<lem::UFString> tokenizer_flags;

        lem::MCollect<Word_Form*> alt; // �������������� ��������

        void Init(const Word_Form& fw, bool copy_versions);

        void SaveTxtPreciser(
            OFormatter &txtfile,
            const SynGram *gram
        ) const;

#if defined SOL_LOADTXT
        void LoadPreciser(
            CompilationContext &context,
            Macro_Parser& txtfile,
            SynGram& gram,
            int iclass
        );
#endif

    public:
        Word_Form(void);
        Word_Form(lem::Stream &bin);

        Word_Form(const lem::MCollect<const Word_Form*> &variants);
        Word_Form(const Lexem &name, int entry_key = UNKNOWN);
        Word_Form(const Lexem &name, int entry_key, const CP_Array& Pair);

        Word_Form(
            const RC_Lexem& ml,
            const RC_Lexem &NormalizedName,
            int entry_key,
            float form_score//Real1 v
        );

        Word_Form(
            const RC_Lexem& ml,
            const RC_Lexem &NormalizedName,
            int entry_key,
            const CP_Array& Pair,
            float form_score//Real1 v
        );

        Word_Form(const Word_Form& fw, bool copy_versions = true);

        ~Word_Form(void);

        void operator=(const Word_Form& fw);

        void SelectAlt(int i);
        bool HasAlt(void) const { return !alt.empty(); }
        const lem::MCollect<Word_Form*> & GetAlts(void) const { return alt; }
        int VersionCount(void) const { return 1 + CastSizeToInt(alt.size()); }
        const Word_Form* GetVersion(int index) const { return index == 0 ? this : alt[index - 1]; }

        bool DoesMatch(SynGram &sg, const Word_Form& fw) const;

        bool AreEqualExcept(
            const Word_Form& wf,
            const CA_Array& excoord
        ) const;

        inline int GetEntryKey(void) const { return entry_key; }

        void SetName(const RC_Lexem& Name);
        void SetName(const lem::UCString &x);
        inline const RC_Lexem& GetName(void) const { return name; }
        inline const RC_Lexem& GetNormalized(void) const { return normalized; }
        inline bool IsSingleLexem(void) const { return true; } //lexem_owner.size()==1; }

        bool CanMatch(const Lexem &word) const;

        inline bool CanMatch(const Word_Form &word) const
        {
            return entry_key == word.entry_key;
        }

        inline int GetOriginPos(void) const { return origin_pos; }
        void SetOriginPos(int p);
        int GetVersionKey(void) const { return iversion; }

        inline int GetnPair(void) const { return CastSizeToInt(pair.size()); }
        inline const GramCoordEx& GetPair(int ipair) const
        {
            return pair[ipair];
        }

        int GetState(int Internal_Pair_Index) const;

        inline const CPE_Array& pairs(void) const { return pair; }
        inline       CPE_Array& pairs(void) { return pair; }

#if defined SOL_CAA
        // ������ ��������� ������������ ����. iCoord - ������ ���� ��
        // ���������� ������.
        void SetState(int Internal_Pair_Index, int istate);
#endif

        inline const CPE_Array& GetPairs(void) const { return pair; }

        //inline Real1 GetVal(void) const { return val; }

        inline float GetScore() const { return score; }
        void SetScore(float _score) { score = _score; }

        // ������������ �������� ������ ����� ���� ������ 
        float GetMaxScore() const;

#if defined SOL_CAA
        /******************************************************
         ��������� ������ ������������� ���������� �����������
         ���������� �� ��������� ����������� Factor.
        *******************************************************/
        //inline void Multiply( Real1 f ) { val = val*f; }
#endif

        const lem::IntCollect GetStates(const GramCoordAdr& pair_index) const;

        bool FindStateForCoord(
            const GramCoordAdr& pair_index,
            int istate
        ) const;

        bool FindStateForCoord(int icoord, int istate) const;
        int GetState(const GramCoordAdr& id_coord) const;

#if defined SOL_CAA
        void RemoveCoord(int Internal_Pair_Index);

        // ������� ��� ����, ����������� � �������� ����������.
        void Remove_Coord_States(const GramCoordAdr &coord);

        const CA_Array GetIndeces(void) const;

        // �������� ��������� ���������� ��������������� � ������
        // ���������.
        void SetState(const GramCoordPair& toset, bool do_add = true, bool apply_versions = true);

        Word_Form* CreateNewVersioned(const std::set<int> & ialt) const;
        Word_Form* CreateNewVersionedSorted(const std::set<int> & ialt) const;
#endif

#if defined SOL_CAA
        bool DoesPresent(const GramCoordAdr& pair_index) const;
        bool Find(const GramCoordPair& pair) const;
#endif

        void Print(OFormatter &txt, SynGram *gram, bool detailed) const;
        void PrintPlain(OFormatter &txt, bool EntryKey) const;
        void PrintXML(OFormatter &xml, SynGram &gram) const;

        //   bool is_beth_type( SynGram &sg ) const;
        //   int GetBethType( SynGram &sg ) const;
        //   bool IsAnyQuantor(void) const;
        //   bool IsUnknownQuantor(void) const;
        //   bool IsMultyplicator( SynGram &sg ) const;
        //   bool IsReplacer( SynGram &sg ) const;
        //   bool IsQuantor( SynGram &sg ) const;

#if defined SOL_LOADTXT
        void LoadTxt(
            CompilationContext &context,
            Macro_Parser &txtfile,
            SynGram &gram
        );
#endif

#if defined SOL_LOADBIN
        void LoadBin(lem::Stream &binfile);
#endif

#if defined SOL_COMPILER || defined SOL_SAVEBIN_PA
        void SaveBin(lem::Stream &binfile) const;
#endif

        /*
           Word_Form* GetCreated(
                                 SynGram *gram
                                 #if defined SOL_CAA
                                 , const PM_SupContext &context
                                 , const PM_Yield &yield
                                 , const PM_SuperIndex &CONFIG
                                 #endif
                                ) const;*/

#if defined SOL_SAVETXT
        void SaveTxt(
            OFormatter &txtfile,
            SynGram &gram,
            bool detailed
        ) const;
#endif

#if defined SOL_CAA
        void Rename_By_States(SynGram &sg, bool apply_versions = true);
        //   void Clear_Convolution();
        void AddAlt(Word_Form *wf);
#endif

        //   int GetMaxContextLen(void) const;

        void SetTokenizerFlag(const lem::UFString &str);
        bool MatchTokenizerFlag(const lem::UFString &str) const;
    };

    class Predef_Word_Form : public Word_Form
    {
    public:
        Predef_Word_Form(int ientry_key, SynGram &gram);
    };


    extern bool eq_states(
        const Word_Form &Node1,
        const GramCoordAdr &Coord1,
        const Word_Form &Node2,
        const GramCoordAdr &Coord2
    );

} // namespace 'Solarix'

#endif
