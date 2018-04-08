#if !defined WordEntry__H
#define WordEntry__H

#include <lem/containers.h>
#include <lem/bit_array32.h>
#include <lem/mset.h>
#include <lem/macro_parser.h>
#include <lem/string_parser.h>
#include <lem/solarix/form_table.h>
#include <lem/solarix/SolidRef.h>
#include <lem/solarix/BaseRef.h>
#include <lem/solarix/sg_defs.h>
#include <boost/regex.hpp>


namespace Solarix
{
    class SynGram;
    class GraphGram;
    class SG_Entry;
    struct Binarization_Options;

    class SG_EntryForm
    {
    private:
        const CP_Array *dim;  // ������������ ���� ���������, ���������� ������
                              // ���������� (��������� �� ������� � ����������� -
                              // ��. SynGram::coord_ref)

        const Lexem *content; // ����������� ���������� ����������
                              // (��������� �� ������� � ����������� - ��.
                              // ���� SynGram::ml_ref).

        bool is_equal_detailed(const CP_Array& Dim) const;

    public:
        SG_EntryForm()
        {
            content = nullptr; dim = nullptr;
        }

        SG_EntryForm(const Lexem* Name)
        {
            content = Name;
            dim = nullptr;
        }

        SG_EntryForm(const Lexem* Name, const CP_Array *Pairs)
        {
            content = Name;
            dim = Pairs;
        }

        inline const CP_Array& coords() const { return *dim; }

        /*********************************************************************
         ���������� ��������� ��������� ����������-���������. ���� ����������
         �� ������� �� ���������� ������ dim, ���������� UNKNOWN.
        **********************************************************************/
        inline int FindDimState(const GramCoordAdr dim_index) const
        {
            const int idim = dim->FindTwice(dim_index);
            return idim == UNKNOWN ? UNKNOWN : (*dim)[idim].GetState();
        }

        inline bool is_equal(const CP_Array& Dim) const
        {
#if LEM_DEBUGGING==1
            int n1 = CastSizeToInt(Dim.size());
            int n2 = CastSizeToInt(dim->size());
            n2 += n1; n1 += n2;
#endif
            if (Dim.size() != dim->size())
                return false;

            if (&Dim == dim)
                // �� ������ ��������� �� ������ ��������� � �����������. ���� ����������
                // ��������� � ������ ��������� �����������, �� ������ ���������
                // ����������� ����� �������� ������ - ��� ��������� ������� �������������
                // ���������� ����� �������.
                return true;

            return is_equal_detailed(Dim);
        }

        // ���������� is_equal, �� �� ���������, ����� Dim �������� ���� ������ ���������
        // ��� ��������� � ������.
        bool does_match(const CP_Array& Dim) const;
        int count_matches(const CP_Array& Dim) const;
        int count_matches(const CP_Array& Dim, const lem::MCollect<int>& weight) const;

        int get_equal_coords(const CP_Array& Dim) const;

        inline const Lexem& name() const { return *content; }

        void Reattach_To_Refs(SynGram &sg);

        void ResetCoords(const CP_Array *new_coords) { dim = new_coords; }

#if defined SOL_SAVETXT
        void SaveTxt(
            OFormatter& txtfile,
            Grammar &gram,
            const SG_Entry& entry
        ) const;
#endif
    }; /* class SG_EntryForm */


    /****************************************************
     ����� ��� �������� ���������� � ��������� ������.
    *****************************************************/
    enum { SOL_SG_HAS_NO_FORM, SOL_SG_BY_DECL_TABLE, SOL_SG_HAS_FORMS };

    class LexemDictionary;

    /*************************************************************************
     ���������� ����� ��� �������� ��������� ������ �������������� ����������.
    **************************************************************************/
    class SG_Entry : public Base_Entry
    {
    private:
        lem::uint8_t flags;   // ������������ ��� �������������� ������...
        lem::uint8_t flags_2; // ����������� �����...

#if defined SOL_LOADTXT && defined SOL_COMPILER
        lem::UFString flexer_flags; // ����� ���������� ���������
        bool allow_auto_import_attrs; // ��������� �������������� ������ ��������� (��� �������� �� ����������� � ������� ���������)
#endif

        int freq; // ������� ������������ ��������� ������ � �������� �������.

        int8_t min_len, max_len; // ���. � ����. ����������� ����� ��������� ������.
                                 // ���� ������������ ��� ��������� ������ � ���������.

        int8_t min_ml_len, max_ml_len; // Min and max number of lexem for all
                                       // wordform names.

        UCString root; // ���������� ��� ���� ��������� ����� (����� ������).

        MCollect<SG_EntryForm> form;  // ������ ���������, ������������ ��������� ����� ������.

#if defined SOL_LOADTXT && defined SOL_COMPILER
// ������������ ��� ��������� ��������� ������� ���������������� (�� ������).
// UNKNOWN, ���� ������� ���������������� �� ������������ �������.
// � ������ 0.96 ����� �������� ������ ������ ����������������, �����
// ����������� ������� ispell
        lem::MCollect<int> decl;
        bool auto_decl; // ���� ��������������� ������� ������� ���������
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
// ��������� ����, �� ������������ � ����� �������, ������������ ��
// ����������� ������ �������� ������ ��� ������������� �� ������ �������
// ���������� ������������� ����.
        lem::Iridium::BSourceState begin_net;
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual bool ProcessSection(
            Macro_Parser &txtfile,
            Grammar &gram,
            const BethToken &t
        );

        void ImportForms(Macro_Parser &txtfile, SynGram &gram);
        void ImportTags(SynGram &s_gram);
        virtual void BeforeFirstForm(Grammar& gram);

        virtual void AddForm(
            const CP_Array& dim,
            const WordFormName& form_name,
            Dictionary &dict
        );

        virtual void SkipNetSection(Macro_Parser &txtfile, Grammar &gram);

#endif

        void FindRoot();
        void InitializeHashes(const GraphGram &g_gram);


        virtual int CountForms() const;

        virtual const Grammar& GetGrammar(const Dictionary &dict);
        virtual Grammar& GetGrammar(Dictionary &dict);

        void Clear();

        // Access to these is blocked
        SG_Entry(const SG_Entry &)=delete;
        void operator=(const SG_Entry &)=delete;

    protected:
        // ���� name_buffer �������� ������������� ����� ������ ��� �������������.
        // ��� ����� ��� ������ �������� ���������, ������� � ������� �����
        // ���� ������� �� ���������� � ������� ��������� ������ ����� ���������
        // ������.
        const Lexem *name;

    public:
        SG_Entry();
#if defined SOL_LOADTXT
        SG_Entry(const UCString &Name, int iClass, LexemDictionary &ml_ref);
#endif

        SG_Entry(int ekey, const Lexem *ename_ptr, int id_class, const CP_Array &_attrs, int _flags, int _freq);

        virtual ~SG_Entry() {}

        void GenerateForms(SynGram &gram);
        void CreateAutoForm(SynGram &gram);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void ProcessNetSection(
            lem::Iridium::Macro_Parser &txtfile,
            Solarix::SynGram &gram,
            const Solarix::Binarization_Options &options
        );
        void Prepare(const GraphGram &g_gram, const SynGram &s_gram);

        virtual void AfterFirstRead();

        const lem::UFString& GetFlexerFlags() const { return flexer_flags; }

        virtual void LoadName(
            Macro_Parser &txtfile,
            Dictionary &dict
        );
#endif


#if defined SOL_LOADTXT
        void PrepareAfterLoad(
            const GraphGram &g_gram,
            SynGram &s_gram
        );
#endif


#if defined SOL_SAVETXT
        void SaveTxt(lem::OFormatter& txtfile, Grammar& gram) const;
        void SaveXML(lem::OFormatter& xmlfile, Grammar& gram) const;
#endif


#if defined SOL_SAVEBIN
        void SaveBin(lem::Stream& bin) const;
#endif

#if defined SOL_LOADBIN
        void LoadBin(lem::Stream& bin);
        void ReattachToRefs(SynGram &sg);
#endif

#if defined SOL_LOADTXT
        void LoadBody(SynGram &sg, lem::StrParser<lem::UFString> &txt);
#endif

        inline const Lexem& GetName() const { LEM_CHECKIT_Z(name != nullptr); return *name; }

        inline const UCString& GetRoot() const { return root; }

        inline lem::MCollect<SG_EntryForm>&       forms() { return form; }
        inline const lem::MCollect<SG_EntryForm>& forms() const { return form; }

        const SG_EntryForm& FindForm(const CP_Array& dim, int *pform = nullptr, int ifmissing = 0) const;
        const SG_EntryForm& FindFormAny(const CP_Array& dim, int *pform = nullptr, int ifmissing = 0) const;
        int FindFormIndex(const CP_Array& dim) const;
        int FindFormIndex(const CP_Array& dim, const lem::MCollect<int>& weight) const;

        int FindForm(const Lexem& name) const;

        inline int GetMinLen() const { return int(min_len); }
        inline int GetMaxLen() const { return int(max_len); }
        inline int GetMinMLLen() const { return int(min_ml_len); }
        inline int GetMaxMLLen() const { return int(max_ml_len); }

        virtual void PrintName(OFormatter &dst_stream) const;

#if defined SOL_LOADTXT && defined SOL_COMPILER
        inline const MCollect<int>& GetDecl() const { return decl; }
#endif

        // ������� ��������, ��� �������� flags=0 ����� ������������ � ������������
        // ������! �� ����, ������������� ���� � flags ��������� ��������� ��������.
        inline bool IsTerminal() const
        {
            return !(flags&SOL_SG_NONTERMINAL_ENTRY);
        }

        inline bool IsNonterminal() const
        {
            return !!(flags&SOL_SG_NONTERMINAL_ENTRY);
        }

        inline bool IsVoiced() const
        {
            return !(flags&SOL_SG_SILENT_ENTRY);
        }

        inline bool IsSilent() const
        {
            return !!(flags&SOL_SG_SILENT_ENTRY);
        }

        // entry is grammatic quantor
        inline bool IsQuantor() const
        {
            return !!(flags&SOL_SG_QUANTOR_ENTRY);
        }

        inline bool IsNoExport() const
        {
            return !!(flags&SOL_SG_NOEXPORT);
        }

        inline int GetFlags2() const
        {
            return flags_2 == 0xff ? UNKNOWN : (static_cast<int>(flags_2) & 0x000000ff);
        }

        void SetQuantor() { flags |= SOL_SG_QUANTOR_ENTRY; }

        inline int GetFreq() const { return freq; }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        inline void UpdateFreq(int n) { freq = std::max(freq, n); }
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        bool DoesMatch(const boost::wregex &rx) const;
#endif

        void PrepareAfterLoadingFromDatabase(SynGram &sg);
    };


    class SG_Quantor : public SG_Entry
    {
    protected:
        virtual bool StoreQuantors() const { return true; }

    public:
        SG_Quantor();
    };


    class SG_BogusEntry : public SG_Entry
    {
    public:
        SG_BogusEntry();
    };

}

#endif
