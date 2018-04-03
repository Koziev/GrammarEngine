#ifndef SOL_GG_ENTRY__H
#define SOL_GG_ENTRY__H
#pragma once

#include <lem/ucstring.h>
#include <lem/cstring.h>
#include <lem/containers.h>
#include <lem/solarix/coord_pair.h>
#include <lem/solarix/form_table.h>

#if defined AddForm
#undef AddForm
#endif

namespace Solarix
{
    class GraphGram;

    extern lem::CString EncodeChar32ToUtf8(lem::uint32_t c);
    extern lem::UCString EncodeChar32ToWide(lem::uint32_t c);

    /***************************************************
     ������������� ������ ������������ �������� �������.
    ****************************************************/
    class GG_EntryForm
    {
    private:
        // ����������� ���� ���������, ���������� ������ ����������.
        lem::MCollect<GramCoordPair> dim;

        // ��� ������� � UCS-4
        lem::uint32_t name;

    public:
        GG_EntryForm(void)
        {
            name = 0;
        }

        GG_EntryForm(const CP_Array& Dim, lem::uint32_t Name);

        inline lem::uint32_t GetName(void) const { return name; }
        lem::CString GetNameUtf8(void) const;
        lem::UCString GetNameWide(void) const;

        inline const lem::MCollect<GramCoordPair>& dims(void) const { return dim; }
        inline lem::MCollect<GramCoordPair>& dims(void) { return dim; }
    };

    /************************************************************
     ������ ����������� ���������� �������� ����������� ���������
     ��������� � ��������� ������ ������� ��������.
    *************************************************************/
    class GG_Entry : public Base_Entry
    {
    private:
        lem::uint32_t name;         // ��� ������ � UCS-4.
        int id_alphabet;            // ������ ��������, � �������� ����������� �����������

        lem::Collect<GG_EntryForm> form; // ������ ���������.

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual void LoadName(Macro_Parser &txtfile, Dictionary &dict) override;
        virtual void AddForm(
            const CP_Array& dim,
            const WordFormName& form_name,
            Dictionary &dict
        ) override;
        virtual bool ProcessSection(
            Macro_Parser &txtfile,
            Grammar &gram,
            const BethToken &t
        ) override;

        virtual int CountForms() const override { return CastSizeToInt(form.size()); }
#endif

        virtual const Grammar& GetGrammar(const Dictionary &dict) override;
        virtual       Grammar& GetGrammar(Dictionary &dict) override;

    public:
        GG_Entry();
        GG_Entry(const GG_Entry& e);
        GG_Entry(lem::uint32_t Ucs4Name, int id_class, int id_alphabet, const lem::MCollect<GramCoordPair> &_attrs);
        GG_Entry& operator=(const GG_Entry& e);


        virtual void PrintName(OFormatter &where_to) const;

        inline lem::uint32_t GetName() const { return name; }

        lem::CString GetNameUtf8() const;
        lem::UCString GetNameWide() const;

        inline const lem::Collect<GG_EntryForm>& forms(void) const { return form; }
        void Add(const GG_EntryForm  &f);

        const GG_EntryForm GetForm(int Index) const;

        inline int GetAlphabet() const { return id_alphabet; }
    };

}
#endif
