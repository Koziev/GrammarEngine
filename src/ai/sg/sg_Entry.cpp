// -----------------------------------------------------------------------------
// File SG_ENTRY.CPP
//
// (c) by Elijah Koziev
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// ����� SG_Entry - �������� ��������� ������ ��� ��������� ��������������
// ����������. ���� ��������� ������ �������� ������������� ������ ��������� �
// ������������ ���-���������.
//
// ������������ ����� ���� ������ ���������� ������ ��� �������� �������� ��
// ���������� �����, ����������/������ � �������� ������� � ������� �
// ��������� ������ � XML.
//
// 27.05.2006 - ��������� ��� ��� ��������� ����: ���� ��������������� �����
//              ��� ���� � ������, �� ����� �� �����������.
//
// 05.06.2006 - �������� ����� �� ����������� ���������
//
// 21.11.2006 - ����������� ���� �������.
//
// 06.06.2007 - ���������� ������ � Sg_Entry::SaveTxt ��� ����������� ���������
// 27.07.2008 - �������� ::SaveXML ��� �������� ��������� ������ � XML
// 23.12.2008 - �������� ������ ��������� �� ������ ��������� ������ �
//              ������������ �������.
// 02.01.2009 - ��������� ������� ������ �������� (����������� ���������� ���
//              ��������� ���������).
// 07.03.2009 - ��������� �������� ��� ����������: ���������� �� �����
//              ���������� � �������.
// 08.07.2009 - ��������� �������� � ������������ �������� ������ paradigm �
//              ����� ������ ����� �� ������ �������� �����.
// ----------------------------------------------------------------------------
//
// CD->11.10.1995
// LC->08.04.2018
// --------------

#include <lem/conversions.h>
#include <lem/oformatter.h>

#include <numeric>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/PartsOfSpeech.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/LexemDictionary.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/dsa_main.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/ParadigmaForm.h>
#include <lem/solarix/ExactWordEntryLocator.h>
#include <lem/solarix/WordEntry.h>

using namespace lem;
using namespace Solarix;

SG_Entry::SG_Entry() :Base_Entry()
{
    Clear();
    return;
}


SG_Entry::SG_Entry(
    int ekey,
    const Lexem *ename_ptr,
    int id_class,
    const CP_Array &_attrs,
    int _flags,
    int _freq
)
    : Base_Entry()
{
    Clear();
    name = ename_ptr;
    iclass = id_class;
    attr = _attrs;
    key = ekey;
    flags = _flags;
    freq = _freq;
    return;
}



#if defined SOL_LOADTXT
SG_Entry::SG_Entry(
    const UCString &Name,
    int iClass,
    LexemDictionary &ml_ref
)
    :Base_Entry()
{
    Clear();

    name = ml_ref.Add(Name);

    iclass = iClass;

#if defined SOL_COMPILER
    HasBeenRealized();
#endif
    return;
}
#endif


void SG_Entry::Clear()
{
    flags = SOL_SG_TERMINAL_ENTRY | SOL_SG_VOICED_ENTRY;
    flags_2 = UNKNOWN;

#if defined SOL_LOADTXT && defined SOL_COMPILER
    decl.clear();
    auto_decl = false;
    allow_auto_import_attrs = true;
#endif

    /*used_n_time =*/ freq = 0;
    max_len = max_ml_len = 0;
    min_len = min_ml_len = 127;

    name = NULL;
    form.clear();

    return;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
/************************************************************************
 ��������! ���� ����� ������ ���������� ��� �������� �� ���������� �����
 ������� ������������� ������� ������ Form_Table, ������ ������
 ��������� ����.
*************************************************************************/
void SG_Entry::AddForm(
    const CP_Array& dim,
    const WordFormName& form_name,
    Dictionary &dict
)
{
    if (lem::is_uspace(form_name.form_name.front()))
    {
        // ���������� �� ����� ���������� � �������
        lem::UFString err = lem::format_str(
            L"Invalid character [%c] code=%X in front of entry form [%s]\n",
            form_name.form_name.front(),
            form_name.form_name.front(),
            form_name.form_name.c_str()
        );
        throw E_BaseException(err.c_str());
    }

    Base_Entry::AddForm(dim, form_name, dict);

    // ����� '?' � �������� ����� ���������� ����������� � ��� ������,
    // ����� ��������� ����������� ����� �� ���������� � �����,
    // � �� ����������� ������������ ������ ��������� ������������
    // �������. ����� ����������, ��������� ���������, �� ��������� � ������.
    if (form_name.form_name == sol_get_token(B_UNKNOWN))
        return;

    // ���� �������������� �����, � �������� ��������� ������, ����� �����������������,
    // ��� ������� � ����� ����� ��������� � ����������� ��������.
    const SG_Class &cls = dict.GetSynGram().GetClass(GetClass());
    const int id_lang = cls.GetLanguage();

    if (id_lang != UNKNOWN)
    {
        const SG_Language &lang = dict.GetSynGram().languages()[id_lang];

        for (int i = 0; i < form_name.form_name.length(); i++)
        {
            wchar_t ch = form_name.form_name[i];

            if (ch == L'"' || ch == Lexem::DelimiterChar)
                continue;

            MCollect<Word_Coord> projs;
            dict.GetGraphGram().FindSymbol(ch, projs);

            bool acceptable_symbol = false;

            for (auto& proj : projs)
            {
                // ������ ����������� ������� ��������.
                int id_alphabet = dict.GetGraphGram().entries()[proj.GetEntry()].GetAlphabet();

                // ������ ������� ������ � ����� ���������� ��� ������ ����� ������?
                if (lang.Find_Alphabet(id_alphabet))
                {
                    // ��. ������ ����� ��� �� ���������. 
                    acceptable_symbol = true;
                    break;
                }
            }

            if (!acceptable_symbol)
            {
                // ��� ���������� ����������� ������������ ������...
                lem::UFString err = lem::format_str(
                    L"Invalid character [%c] code=%X is used for entry form [%s]\n",
                    ch,
                    ch,
                    form_name.form_name.c_str()
                );
                throw E_BaseException(err.c_str());
            }
        }
    }


    // ��� ��� �����. ��� ���� ���������������� � ����� �������.
    Lexem ml(form_name.form_name);
    dict.GetLexAuto().TranslateLexem(ml, true, id_lang);

    // �������� ���������� ����� ����� ������������ ������ � ����� ��������������
    // ��������� (����� ��� dim), �� � ��� �������� ��������� ����� ������.
    CP_Array pairs(dim);

    //const lem::Container::size_type n_attr = attrs().size();
    std::copy(attrs().begin(), attrs().end(), std::back_inserter(pairs));

    const int iform = CastSizeToInt(form.size());

    form.push_back(SG_EntryForm(
        // �������������-�������� ������������ � �������
        dict.GetSynGram().GetEntries().AddLexeme(ml),

        // ������ ������������ ��� ����� ������������ � �������
        dict.GetSynGram().GetEntries().AddCoordPairs(pairs)
    ));

    if (form_name.HasAux())
    {
        // ��� �������������� ����� ���� �������������� ��������, ��������� ������
        for (lem::Container::size_type i = 0; i < form_name.aux.size(); ++i)
        {
            const lem::UCString & aux_type = form_name.aux[i].first; // ��� ���. �������� ����� (��������, ��������, ������������ � �.�.)
            const lem::UFString & aux_data = form_name.aux[i].second; // ��������� ������������� ���. ��������

            int id_aux_type = dict.GetSynGram().GetAuxFormTypes()[aux_type];
            if (id_aux_type == UNKNOWN)
            {
                MemFormatter msg;
                msg.printf("Invalid auxiluary form aux_type=%us aux_data=%us in word entry %us", aux_type.c_str(), aux_data.c_str(), GetName().c_str());
                throw E_BaseException(msg.string());
            }

            dict.GetSynGram().GetStorage().AddAuxForm(GetKey(), iform, id_aux_type, aux_data);
        }
    }

    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
/***************************************************************************
 ��������� ��� ��������� ������ �� ������� � ���������� (����� B_COLON).

                           entry name : xxxx
                                 ^^^^

   ��������� �������� � ��������� ����� ������ ������� ��� � ���. ���
 ������� � ������� ���������� ��� ������ ���������� �������������
 ������������ ����������. ������� ���������� � ������ ���� ��������� ������
 �������� ������, �� ���� ��������� ������������ ���������� ��������
 ������������ �����. �� ����������� �����, � ������ - ����������� ��
 ������������ ����������, ����� �������� � ���� ������� ���������
 �������� � ���� �������� ������. ������������ ���� ������� ����������
 ����� MultyLexem.

   �������, ������ ��� ������, �� �������� ���� name_buffer ��������� ���
 ���, � ����� ���� ����� ������������ ����������. ������ �����������
 ������������ ���������� ���������� ���� ������ ����. ���� ��� ���������,
 ���� �����������, ��� ��������� ������ ������� - ��� ����� ���� �����
 ���������� ����� ��������������� ������. ��� �� ����������� �������������
 ���������� ��� ��������������� �������� ������������ "�������" ����������.
***************************************************************************/
void SG_Entry::LoadName(
    Macro_Parser &txtfile,
    Dictionary &dict
)
{
    lem::Iridium::BSourceState entry_begin = txtfile.tellp();

    Lexem entry_name(sol_read_multyname(dict.GetIO(), txtfile, B_COLON));

    const BethToken class_name = txtfile.read();

    if ((iclass = dict.GetSynGram().FindClass(class_name.string())) == UNKNOWN)
    {
        // �� ������ �����, ���������� ��� ������
        Print_Error(class_name, txtfile);
        dict.GetSynGram().GetIO().merr().printf(
            "The class [%us] is not previously declared in grammar\n"
            , class_name.c_str()
        );
        throw E_ParserError();
    }

    // ��������� ����� ������ ����� ����� � ������ ��������, ���������� ��� ��������������� ������.
    int id_language = UNKNOWN;
    if (!lem::is_quantor(iclass))
    {
        const Solarix::SG_Class &c = dict.GetSynGram().GetClass(iclass);
        id_language = c.GetLanguage();
    }

    dict.GetLexAuto().TranslateLexem(entry_name, false, id_language);

    if (id_language != UNKNOWN)
    {
        const SG_Language &lang = dict.GetSynGram().languages()[id_language];
        const lem::MCollect<int> & id_alphabets = lang.GetAlphabets();
        entry_name.Translate(dict.GetGraphGram(), 1, id_alphabets);
    }
    else
    {
        entry_name.Translate(dict.GetGraphGram(), 1);
    }

    if (entry_name.empty())
    {
        lem::Iridium::Print_Error(entry_begin, txtfile);
        dict.GetIO().mecho().printf("Word entry can not have empty name");
        throw E_BaseException();
    }

    name = dict.GetSynGram().GetEntries().AddLexeme(entry_name);

    if (dict.GetDebugLevel_ir() >= 3)
    {
        // �������� ��� ������������� ������ ��� �������� �� ���������
        // �������� �������.
        dict.GetIO().mecho().printf(
            "%us [%vfE%us%vn]->"
            , sol_get_token(B_ENTRY).c_str()
            , name->c_str()
        );
    }

    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/************************************************************************
 ���������� ������ � �������� ��������� ������. ��� ������ ����������
 ����� (�������� � ���������� ����), �������� ��������� ������ �
 �������������� ���� �������������� ����������.
************************************************************************/
void SG_Entry::SkipNetSection(Macro_Parser &txtfile, Grammar &gram)
{
    if (begin_net.empty())
        begin_net = txtfile.tellp();

    SG_NetLink(txtfile, (SynGram&)gram, false);
    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/****************************************************************************
 ��������� ����������� ������ � �������������� ���� ��� ������, ������������,
 ��� ��� - ������ ������, �� ���� ���������� ������ (����������) ���
 ���������.
*****************************************************************************/
void SG_Entry::ProcessNetSection(
    Macro_Parser &txtfile,
    SynGram &gram,
    const Binarization_Options &options
)
{
    if (begin_net.empty())
        return; // ������ �� ����� ������������ ��������.

       // ������ ������ ������ ����������� ����.
    txtfile.seekp(begin_net); // ������������� � ������ �������� ������.
    begin_net = BSourceState(); // �� ��������� ��������� �������� ������� ����.

    // ���� ��� ������ ����� ������� �������� ������ � ����, �� first ������
    // false, ��� ��� ��������� � �������� ���� ��� ������ ����� �������� ���� ���.
    bool first = true;

    int nparen = 1; // ����� �������� �������� ������.
    while (!txtfile.eof())
    {
        const BethToken t = txtfile.read();

        if (t.GetToken() == B_CFIGPAREN && !--nparen)
        {
            // ����� ������ ������������ �������� ������.
            txtfile.seekp(t);
            break;
        }

        if (t.GetToken() == B_OFIGPAREN)
        {
            nparen++;
            continue;
        }

        if (nparen == 1 && t.GetToken() == B_OTRIPAREN)
        {
            // ����� �������� ����� ������.
            first = false;
            txtfile.seekp(t.GetBegin());

            ExactWordEntryLocator coords_empty;
            if (gram.IsOmonym(GetClass(), GetName()))
                coords_empty.pairs = attrs();

            gram.Get_Net().Load_Declaration(
                txtfile,
                gram.classes()[iclass].GetName(),
                GetName(),
                coords_empty,
                options
            );
        }
    }

    if (!first && gram.GetDict().GetDebugLevel_ir() >= 3)
        gram.GetIO().mecho().printf("%vfAOK%vn\n");

    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/***************************************************************
 ����� ������ ���������� ������ � ������ �������: ���� ������
 ������������ �������� �����������, �� �� ����� ������ ��������
 ������������ ����������.
****************************************************************/
void SG_Entry::AfterFirstRead()
{
    /*
     if( form.empty() )
      {
       // ������� ��������� ��-����� (�� ���� ����� ���� ��������������
       // ����� � ��������� ��-��� ����������� ��������� ����). ��������
       // ������������ ����� �� ������ �������������, ����������� � name_buffer.
       if( GetDecl()!=UNKNOWN )
        {
         form_flag = SOL_SG_BY_DECL_TABLE;
        }
       else
        {
         form_flag = SOL_SG_HAS_NO_FORM;
        }
      }
     else
      form_flag = SOL_SG_HAS_FORMS;
    */

    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/************************************************************************
 ��� ������ ����������, ��� �� � ������ ������������ �������� ������
 ������������� ������ ��� ��������� ������ ��������� ����������, ������
 ��������� ����� ���������� ������������ �������� ��� ����� ��� �������
 �������� t.

 1) ������� ����� ����� �������� ������� ���������:

                         entry name : xxxx
                         {
                          sound filename
                         }

 2) �������� ����������� ������������ ��� ���������� ������ �������
 ����������������:
                         entry name : xxx
                         {
                          123 [, 456, 789 ]
                         }

 3) �������� �������������� ������:
                         entry name : xxx
                         {
                          flag : N
                         }

************************************************************************/
bool SG_Entry::ProcessSection(
    Macro_Parser &txtfile,
    Grammar &gram,
    const BethToken &t
)
{
    if (Base_Entry::ProcessSection(txtfile, gram, t))
        return true;

    if (t.string().eqi(L"aux"))
    {
        SynGram &sg = (SynGram&)gram;

        UCString aux_type = txtfile.read().string();
        aux_type.strip(L'"');

        txtfile.read_it(B_EQUAL);
        UFString aux_data = txtfile.read().GetFullStr();
        aux_data.strip(L'"');
        const int id_aux_type = sg.GetAuxFormTypes()[aux_type];

        if (id_aux_type == UNKNOWN)
        {
            MemFormatter msg;
            msg.printf("Invalid auxiluary entry data aux_type=%us aux_data=%us in word entry %us", aux_type.c_str(), aux_data.c_str(), GetName().c_str());
            throw E_BaseException(msg.string());
        }

        sg.GetStorage().AddAuxEntryData(GetKey(), id_aux_type, aux_data);
        return true;
    }


    if (t.string().eqi(L"no_import_attr"))
    {
        allow_auto_import_attrs = false;
        return true;
    }

    /*
     if( t.GetToken() == B_SOUND )
      {
       // ���������� ��� ����� �� ��������� �������� ���������.
       sound_filename =  strip_quotes( txtfile.read().string() );
       return true;
      }
    */


    if (t.GetToken() == B_FLAG)
    {
        if (txtfile.pick() == B_FLEXER)
        {
            txtfile.read_it(B_FLEXER);

            if (txtfile.pick() == B_OFIGPAREN)
            {
                // flag flexer { "f1" "f2" ... "fN" }
                // ��������� ������ ������� � ���� ����, ��������
                // �� ���������. ���� ������� ������ ��� ��������
                // ������ � ��������������.

                txtfile.read();

                while (!txtfile.eof())
                {
                    const BethToken& f = txtfile.read();
                    if (f == B_CFIGPAREN)
                        break;

                    UFString part = f.c_str();
                    part.strip(L'"');
                    if (!flexer_flags.empty()) flexer_flags += L' ';
                    flexer_flags += part;
                }
            }
            else
            {
                // flag flexer "f1"
                flexer_flags = txtfile.read().c_str();
                flexer_flags.strip(L'"');
            }
        }
        else
        {
            // ��������� �������� ��������� �����. ��� �������� ����� ���� ����������
            // OR-�������� ��������� �����, ����������� ������� '|'.
            txtfile.read_it(B_COLON);

            while (!txtfile.eof())
            {
                flags |= txtfile.read_int();
                const BethToken& ttt = txtfile.read();
                if (ttt.GetToken() != B_ORSIGN)
                {
                    txtfile.seekp(ttt);
                    break;
                }
            }

            // ����� ������� ����� ���� ������ ������ ����������� ����...
            const BethToken comma = txtfile.read();
            if (comma.GetToken() == B_COMMA)
                flags_2 = txtfile.read_int();
            else
                txtfile.seekp(comma);
        }

        return true;
    }

    if (t.GetToken() == B_IMPORT)
    {
        ImportForms(txtfile, (SynGram&)gram);
        return true;
    }

    bool decl_defined = false;

    if (t.GetToken() == B_PARADIGMA)
    {
        if (txtfile.pick().GetToken() == B_AUTO)
        {
            txtfile.read();
            auto_decl = true;
            return true;
        }
        else
        {
            // ����� ���� ������ �������� �������� ����� �������.
            SynGram & sg = (SynGram&)gram;
            SG_DeclensionAutomat & flexer = sg.Get_DSA();

            while (!txtfile.eof())
            {
                const BethToken& decl_name = txtfile.read();
                const int id_decl = flexer.FindDecl(decl_name);

                if (id_decl == UNKNOWN)
                {
                    lem::Iridium::Print_Error(t, txtfile);
                    gram.GetIO().merr().printf("Unknown declension table [%vfE%us%vn]\n", decl_name.c_str());
                    throw E_ParserError();
                }

                decl.push_back(id_decl);
                decl_defined = true;

                if (decl.size() == 1)
                {
                    // ��������� ������������ ���� (��������) �� ������ ������� ���������,
                    // ������ ������� �� ������ ��� ������, � ���� ������.
                    const SG_DeclensionTable &table = sg.Get_DSA().GetDecl(id_decl);
                    std::copy(table.attrs().begin(), table.attrs().end(), std::back_inserter(attr));
                }

                // ���� ������ ���� �������, �� ����� ������� ��������� ������� ����������������
                const BethToken& t2 = txtfile.read();
                if (t2.GetToken() != B_COMMA)
                {
                    txtfile.seekp(t2);
                    break;
                }
            }
        }
    }

    if (decl_defined)
        return true;

    return false;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_Entry::ImportForms(Macro_Parser &txtfile, SynGram &sg)
{
    BeforeFirstForm(sg);

    // ������ ��������� �� ������ ������ � ��������� ������������
    // �� ������������ ��������.

    txtfile.read_it(L"from");

    BethToken class_name = txtfile.read();
    const int iclass = sg.FindClass(class_name.string());
    if (iclass == UNKNOWN)
    {
        lem::Iridium::Print_Error(class_name, txtfile);

        sg.GetIO().merr()
            .printf(
                "The class [%vfE%us%vn] is not previously declared in grammar\n"
                , class_name.c_str()
            );

        throw E_SG_NoClass(class_name.string());
    }


    txtfile.read_it(B_COLON);

    const UCString mname = sol_read_multyname(sg.GetIO(), txtfile, B_OFIGPAREN);
    txtfile.read_it(B_CFIGPAREN);

    lem::Ptr<SG_DeclensionForm> lex_changer;
    lem::UCString postfix, prefix;

    if (txtfile.pick().string() == L"using")
    {
        txtfile.read();

        BethToken t2 = txtfile.read();

        if (t2.GetToken() == B_PARADIGMA)
        {
            CP_Array dims;
            UCString command = txtfile.read();
            command.strip_quotes();
            lex_changer = new SG_DeclensionForm(dims, command);
        }
        else if (t2.string() == L"postfix")
        {
            postfix = txtfile.read();
            postfix.strip_quotes();
        }
        else if (t2.string() == L"prefix")
        {
            prefix = txtfile.read();
            prefix.strip_quotes();
        }
        else
        {
            lem::Iridium::Print_Error(t2, txtfile);
            sg.GetIO().merr().printf("Invalid command [%vfE%us%vn] for 'import' directive\n", t2.c_str());
            throw E_ParserError();
        }
    }

    // ���� ������� ������.

    const int ientry = sg.FindEntry(mname, iclass, false);
    if (ientry == UNKNOWN)
    {
        lem::Iridium::Print_Error(txtfile);
        sg.GetIO().merr().printf("The entry [%vfE%us%vn] is not previously declared in grammar\n", mname.c_str());
        throw E_ParserError();
    }

    const SG_Entry &src = sg.GetEntry(ientry);

    LexicalAutomat &la = sg.GetDict().GetLexAuto();

    for (lem::Container::size_type i = 0; i < src.forms().size(); ++i)
    {
        const SG_EntryForm &src_frm = src.forms()[i];

        const Lexem &src_name = src_frm.name();

        // ������ ��������� �������� ��� ���������.
        const CP_Array &coords = src_frm.coords();

        Lexem new_name;

        if (lex_changer.NotNull())
        {
            new_name = sg.Get_DSA().ProduceForm(src_name, GetClass(), *lex_changer, sg);
        }
        else if (!postfix.empty())
        {
            new_name = src_name + Lexem::DelimiterStr + postfix;
        }
        else if (!prefix.empty())
        {
            new_name = prefix + Lexem::DelimiterStr + src_name;
        }

        la.TranslateLexem(new_name, true);
        SG_EntryForm new_form(sg.GetEntries().AddLexeme(new_name), &coords);
        form.push_back(new_form);
    }

    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_Entry::ImportTags(SynGram &s_gram)
{
    if (is_quantor(iclass) || !allow_auto_import_attrs)
        return;

    // ���� ��� �������������� ����� ��������� ������, �� ��������� ���� �������� 
    // ����������.
    const SG_Class &cls = (const SG_Class&)s_gram.classes()[iclass];
    if (cls.HasImport())
    {
        for (lem::Container::size_type i = 0; i < cls.import_coord.size(); ++i)
        {
            const int iclass_src = cls.import_class[i];
            int ie = UNKNOWN;

            if (cls.import_filters[i]->empty())
            {
                ie = s_gram.FindEntry(GetName(), iclass_src, false);
            }
            else
            {
                const lem::MCollect<Solarix::GramCoordAdr> &a = cls.import_filters[i]->coords;

                ExactWordEntryLocator locator;

                Solarix::CP_Array pairs;
                //for (lem::Container::size_type k = 0; k < a.size(); ++k)
                for (auto& icoord : a)
                {
                    //const Solarix::GramCoordAdr &icoord = a[k];
                    const int istate = GetAttrState(icoord);
                    if (istate != UNKNOWN)
                    {
                        locator.pairs.push_back(Solarix::GramCoordPair(icoord, istate));
                    }
                }

                if (cls.import_filters[i]->aux_type != UNKNOWN)
                {
                    // ��������� �������� aux-������ ��� ��������� ������

                    lem::UFString aux_data;
                    if (s_gram.GetStorage().GetAuxEntryData(GetKey(), cls.import_filters[i]->aux_type, aux_data) != UNKNOWN)
                    {
                        // ��, ������ ����, ������� ��������� � ������ ��������.
                        locator.aux_type = cls.import_filters[i]->aux_type_str;
                        locator.aux_value = aux_data.c_str();
                    }
                }

                ie = s_gram.FindEntryOmonym(GetName(), iclass_src, locator);

                if (ie == UNKNOWN)
                {
                    s_gram.GetIO().merr().printf("Warning: can not find wordentry [%us:%us] with omonym filter: ", s_gram.GetClass(iclass_src).GetName().c_str(), GetName().c_str());
                    locator.Print(s_gram.GetIO().merr(), s_gram);
                    s_gram.GetIO().merr().eol();
                }
            }

            if (ie == UNKNOWN)
            {
                // ���� �������� ��� ���� - ������ ������������ default-����������� ��� ���� ������ 
                // � ������ ����. 
                if (attr.FindOnce(cls.import_coord[i]) == UNKNOWN)
                {
                    lem::zbool def_unk;
                    for (lem::Container::size_type j = 0; j < cls.attr_defaults.size(); ++j)
                    {
                        if (cls.attr_defaults[j].first == cls.import_coord[i] && cls.attr_defaults[j].second == UNKNOWN)
                        {
                            def_unk = true;
                            break;
                        }
                    }

                    if (!def_unk)
                    {
                        // ���� ������������ ����������...
                        if (s_gram.coords()[cls.import_coord[i].GetIndex()].IsBistable())
                        {
                            Solarix::GramCoordPair p(cls.import_coord[i], 0);
                            attr.push_back(p);
                        }
                        else
                        {
                            s_gram.GetDict().GetIO().merr()
                                .printf(
                                    "\nCan not find entry %vfE%us:%us%vn when loading entry %us:%us to import the attribute [%us]\n"
                                    , s_gram.classes()[iclass_src].GetName().c_str()
                                    , GetName().ToString().c_str()
                                    , s_gram.classes()[GetClass()].GetName().c_str()
                                    , GetName().ToString().c_str()
                                    , s_gram.coords()[cls.import_coord[i].GetIndex()].GetName().front().c_str()
                                );

                            throw E_ParserError();
                        }
                    }
                }

                continue;
            }

            // � ��������� ������ ���� ����� ��������� ����������
            IntCollect states = s_gram.GetEntry(ie).GetAttrStates(cls.import_coord[i]);
            if (!states.empty())
            {
                attr.RemoveStates(cls.import_coord[i]);

                for (lem::Container::size_type j = 0; j < states.size(); ++j)
                {
                    Solarix::GramCoordPair p(cls.import_coord[i], states[j]);
                    if (attr.find(p) == UNKNOWN)
                        attr.push_back(p);
                }
            }
        }
    }

    return;
}
#endif


#if defined SOL_LOADTXT
/**********************************************************************
 �������������� ���� ��������� ������ ��� ������ � ���������� ��������
 ������������� ������������ �� ��������.
***********************************************************************/
void SG_Entry::PrepareAfterLoad(
    const GraphGram &g_gram,
    SynGram &s_gram
)
{
#if defined SOL_LOADTXT && defined SOL_COMPILER
    // ���� ���������� ���� �� ����������, � ������ ������� (������) ���������,
    // �� ����������� �����.
    GenerateForms(s_gram);
#endif

    // �������������� "������" ����� - ��� ��������� ��������� ������ ��� ������.
    FindRoot();

    InitializeHashes(g_gram);

    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_Entry::Prepare(const GraphGram &g_gram, const SynGram &s_gram)
{
    return;
}
#endif



// ****************************************************************************
// ����� ��������������� ����� - ��������������� �� ���� ������ ������
// �������� ��������. �������� �� ����� �� ������������, ��� ��� ���������
// "������" ����� ���� ������ ������ �������, �� ����������� ����� ���
// ������������� - ���� ������ ����� ����� � �������, �� ����� ���������� ����
// ��������� ������ ����� �������� ������� ����� � ������, � ���� ������
// ������ � ������� �����, �� ���� ����� ������������� ��� �����.
// ****************************************************************************
void SG_Entry::FindRoot()
{
    // LEM_CHECKIT_Z( !form.empty() );

    if (form.size() > 1)
    {
        const SG_EntryForm &frm = form.front();
        UCString form0;
        if (frm.name().Count_Lexems() == 1)
        {
            form0 = frm.name();
        }
        else
        {
            UCStringSet list;
            frm.name().Split(list);
            form0 = list.front();
        }

        int min_len = lem::int_max;

        for (Container::size_type i = 1; i < form.size(); i++)
        {
            min_len = std::min(
                min_len,
                match_len(
                    form0,
                    static_cast<UCString>(form[i].name())
                )
            );
        }

        if (min_len < lem::int_max)
        {
            // ����� ����������� ����� ���������� ��������� ������ ����.
            // ������ �������� �� ������ ���������� ������� ����� ����� � ��������
            // ������� ������.
            root = left(form0, min_len);
        }
    }

    return;
}




#if defined SOL_LOADTXT && defined SOL_COMPILER
/**************************************************************************
 ���� ������ ������ ����� ����������, �� ������������ ����� ������ �������
 ���������, �� ���������� ��������� ���� ��� ��������� ��������
 ����������������.
***************************************************************************/
void SG_Entry::GenerateForms(SynGram &gram)
{
    if (CountForms() == 0)
        BeforeFirstForm(gram);

    if (!decl.empty() || auto_decl)
    {
        LEM_CHECKIT_Z(form.empty()); // must be no forms!

        // ��������� ���� �� ������� (������� ���������).

        const SG_DeclensionAutomat &DA = gram.Get_DSA();

        // ���� name_buffer �������� ������������� ����� ������ ��� �������������.

        int ndecl = auto_decl ? 1 : decl.size();

        for (int iidecl = 0; iidecl < ndecl; iidecl++)
        {
            const SG_DeclensionTable &table = auto_decl ?
                // ������������� ����������� ������� ���������
                gram.Get_DSA().GetDecl(*name, GetClass())
                :
                // ������� ��������� ������� ����
                gram.Get_DSA().GetDecl(decl[iidecl]);

            const int nform = CastSizeToInt(table.GetForms().size()); // ������� ���� ����� ������� � ���������.
            form.reserve(nform);
            const int n_attr = CastSizeToInt(attrs().size());

            CP_Array pair_list;
            for (int iform = 0; iform < nform; iform++)
            {
                // ����� ������������?
                if (!table.GetForms()[iform]->MatchCondition(*name, flexer_flags))
                    // ��� - ����������
                    continue;

                // ����������� ���������� ��������� �����.
                const Lexem *made = gram.GetEntries().AddLexeme(
                    DA.ProduceForm(
                        *name,
                        GetClass(),
                        *table.GetForms()[iform],
                        gram
                    )
                );

                pair_list = table.GetForms()[iform]->GetDim(); // ��������� �����.

                // ��������� ������ ��������� ����� ������.
                for (int iatr = 0; iatr < n_attr; iatr++)
                {
                    // ��� �������: ���� �� ������ �����������!
                    for (Container::size_type i = 0; i < pair_list.size(); i++)
                    {
                        if (pair_list[i] == attrs()[iatr])
                        {
                            gram.GetIO().merr().printf(
                                "Run-time error: pair [%vfE%us:%us%vn] is doubled in entry form [%vfE%us%vn]\n"
                                , gram.coords()[pair_list[i].GetCoord().GetIndex()].GetName().string().c_str()
                                , gram.coords()[pair_list[i].GetCoord().GetIndex()].GetStateName(pair_list[i].GetState()).c_str()
                                , name->ToString().c_str()
                            );
                            throw E_ParserError();
                        }
                    }

                    pair_list.push_back(attrs()[iatr]);
                }

                const CP_Array *ptr_list = gram.GetEntries().AddCoordPairs(pair_list);

                // ����� ����� �������� ��� � ������?
                bool unique = true;
                for (Container::size_type j = 0; j < form.size(); j++)
                {
                    if (form[j].name() == *made && &(form[j].coords()) == ptr_list)
                    {
                        unique = false;
                        break;
                    }
                }

                if (unique)
                    // ��������� ������� ����������.
                    form.push_back(SG_EntryForm(made, ptr_list));
            }
        }
    }
    else if (!form.size())
    {
        // �������� ������������ ����� ��� ������ ��� ����� ���� (�� ����
        // ��� ��������� - ��������, ��� ���������). ��� ����� ��������� ���������
        // � ������ ������.
        CreateAutoForm(gram);
    }

    return;
}


void SG_Entry::CreateAutoForm(SynGram &gram)
{
    LEM_CHECKIT_Z(form.empty());

    // �� ���������� ������ ���������� ���������� ������ � ������
    // ������������ ��� ��� ��������� ����� ������ ������.
    const Container::size_type n_attr = attrs().size();
    CP_Array pairs;
    pairs.reserve(n_attr + 1);
    for (Container::size_type i = 0; i < n_attr; i++)
        pairs.push_back(attrs()[i]);

    form.push_back(SG_EntryForm(
        name,
        gram.GetEntries().AddCoordPairs(pairs)
    ));
    return;
}
#endif


#if defined SOL_SAVEBIN
/***************************************************************
 ��������� ��� ���������� (����� ���, ��� �������� ������������
 �� ������ ���������� �������) � ��������� �������� ������.
****************************************************************/
void SG_Entry::SaveBin(lem::Stream &bin) const
{
    Base_Entry::SaveBin(bin);

    form.SaveBin(bin);

    bin.write(&name, sizeof(name));

    bin.write(&root, sizeof(root));
    bin.write(&flags, sizeof(flags));
    bin.write(&flags_2, sizeof(flags_2));

    bin.write(&min_len, sizeof(min_len));
    bin.write(&max_len, sizeof(max_len));

    bin.write(&min_ml_len, sizeof(min_ml_len));
    bin.write(&max_ml_len, sizeof(max_ml_len));

    bin.write(&freq, sizeof(freq));

    return;
}
#endif



#if defined SOL_LOADBIN
void SG_Entry::LoadBin(lem::Stream &bin)
{
    Base_Entry::LoadBin(bin);

    form.LoadBin(bin);

    bin.read(&name, sizeof(name));

    bin.read(&root, sizeof(root));
    bin.read(&flags, sizeof(flags));
    bin.read(&flags_2, sizeof(flags_2));

    bin.read(&min_len, sizeof(min_len));
    bin.read(&max_len, sizeof(max_len));

    bin.read(&min_ml_len, sizeof(min_ml_len));
    bin.read(&max_ml_len, sizeof(max_ml_len));

    bin.read(&freq, sizeof(freq));

    return;
}
#endif




#if defined SOL_LOADBIN
void SG_Entry::ReattachToRefs(SynGram &sg)
{
    // �������� ����� ������.
    name = sg.GetEntries().ReattachLexeme(name);

    // ��� ������ ���������� - �������� � ����������.
    for (auto& f : form)
    {
        f.Reattach_To_Refs(sg);
    }

    return;
}
#endif


/**************************************************************************
 ���������� ����������, ��������� ������� ��������������� ������
 ���������, ����������� ����� ���������� ������� � ������� ���������.
 ��������� ���������� ��� ���������� ������������� ������.

 ���� ������ dim ����, �� ������� ������ ����� �� ������.
**************************************************************************/
const SG_EntryForm& SG_Entry::FindForm(
    const CP_Array& dim,
    int *pform,
    int ifmissing
) const
{
    LEM_CHECKIT_Z(!form.empty());

    if (pform)
        *pform = UNKNOWN;

    int ifound = UNKNOWN;

    if (dim.empty())
        ifound = 0;
    else
    {
        for (lem::Container::size_type i = 0; i < form.size(); i++)
        {
            if (form[i].is_equal(dim))
            {
                ifound = CastSizeToInt(i);
                break;
            }
        }
    }

    if (ifound == UNKNOWN)
    {
        if (ifmissing == 0)
        {
            // ���������� ����� �� �������. ������ �� �����������, ����� ����� ��������
            // ���� ������� - ������� ��������� ������ ������������� ���������� � ����������
            // ������ � ������ ����, ��� ������� ����� ���. 
#if LEM_DEBUGGING==1
            lem::mout->printf("Can not find the entry form: entry=%us ", GetName().c_str());
            for (lem::Container::size_type i = 0; i < dim.size(); ++i)
            {
                lem::mout->printf(" (%d:%d)", dim[i].GetCoord().GetIndex(), dim[i].GetState());
            }

            lem::mout->eol();
#endif
            throw E_SG_NoForm();
        }

        if (ifmissing == 1)
        {
            ifound = 0;
        }
    }

    if (!!pform)
        *pform = ifound;

    return form[ifound];
}

// *****************************************************************************
// � ������� �� ����������� ������ ::FindForm(...) ����� �� �� ����� ���������,
// ����� ����������� ��� ���������� �� dim �������������� � �����. ����������,
// ����� �� ���� �� ����� ���������� �����, ��� �� � ������� dim � �����
// ����� ������ ���������.
// *****************************************************************************
const SG_EntryForm& SG_Entry::FindFormAny(const CP_Array& dim, int *pform, int ifmissing) const
{
    LEM_CHECKIT(form.size());

    if (pform)
        *pform = UNKNOWN;

    int ifound = UNKNOWN;

    if (dim.empty())
        ifound = 0;
    else
    {
        int i_form_max = UNKNOWN, max_coords = 0;

        for (Container::size_type i = 0; i < form.size(); i++)
        {
#if LEM_DEBUGGING==1
            const SG_EntryForm &frm = form[i];
            const UCString &frmname = frm.name();
#endif
            int n_match = form[i].get_equal_coords(dim);
            if (n_match > max_coords)
            {
                max_coords = n_match;
                i_form_max = CastSizeToInt(i);
            }
        }

        ifound = i_form_max;
    }

    if (ifound == UNKNOWN)
    {
        if (ifmissing == 0)
        {
            // ���������� ����� �� �������. ������ �� �����������, ����� ����� ��������
            // ���� ������� - ������� ��������� ������ ������������� ���������� � ����������
            // ������ � ������ ����, ��� ������� ����� ���.
            throw E_SG_NoForm();
        }

        if (ifmissing == 1)
        {
            ifound = 0;
        }
    }

    if (!!pform)
        *pform = ifound;

    return form[ifound];
}


// ******************************************************
// ����� ������� ���������� ����������
// ******************************************************
int SG_Entry::FindFormIndex(const CP_Array& dim) const
{
    LEM_CHECKIT_Z(!form.empty());

    if (dim.empty())
        return 0;

    int n_best_match = 0;
    int i_best_match = UNKNOWN;

    for (Container::size_type i = 0; i < form.size(); i++)
    {
        int n_match = form[i].count_matches(dim);

        if (n_match == CastSizeToInt(dim.size()))
            return CastSizeToInt(i);

        if (n_match > n_best_match)
        {
            n_best_match = n_match;
            i_best_match = CastSizeToInt(i);
        }
    }

    return i_best_match;
}


// ******************************************************
// ����� ������� ���������� ���������� � ������ �������� 
// ������������ ���.
// ******************************************************
int SG_Entry::FindFormIndex(const CP_Array& dim, const lem::MCollect<int>& weight) const
{
    LEM_CHECKIT_Z(!form.empty());

    if (dim.empty())
        return 0;

    int sum_w = std::accumulate(weight.begin(), weight.end(), 0);

    int n_best_match = 0;
    int i_best_match = UNKNOWN;

    for (lem::Container::size_type i2 = 0; i2 < form.size(); i2++)
    {
        int n_match = form[i2].count_matches(dim, weight);

        if (n_match == sum_w)
            return CastSizeToInt(i2);

        if (n_match > n_best_match)
        {
            n_best_match = n_match;
            i_best_match = CastSizeToInt(i2);
        }
    }

    return i_best_match;
}



/********************************************
 �������� ��� ������ � ��������� �����.
*********************************************/
void SG_Entry::PrintName(OFormatter &to) const
{
    to.printf("%us", name->c_str());
    return;
}

/***************************************************************
 ����� �������� ����� ���������� � ������� ������, � ����������
 ���������� ������ � ������ ������. ��� �������� ������������
 UNKNOWN. ������� ��������, ��� ���� ��������� ������ ���������,
 �� ���� ���� ������ ��������� �� ��������� �� �������
 ����������������, �� ������������ UNKNOWN, ��� ����������� ��
 ��������������� ���������� ����� � ������.
****************************************************************/

static bool inrange(int x, int a, int b)
{
    return x >= a && x <= b;
}

int SG_Entry::FindForm(const Lexem& name) const
{
    LEM_CHECKIT_Z(!form.empty());

    if (!inrange(name.length(), min_len, max_len))
        return UNKNOWN;

    const int nparts = name.Count_Lexems();
    if (!inrange(nparts, min_ml_len, max_ml_len))
        return UNKNOWN;

    const wchar_t *As = name.c_str();
    if (!GetRoot().empty() && lem_find(As, GetRoot().c_str()) == UNKNOWN)
        return UNKNOWN;

    for (lem::Container::size_type iform = 0; iform < form.size(); iform++)
    {
        if (form[iform].name() == name)
            return CastSizeToInt(iform);
    }

    return UNKNOWN;
}


#if defined SOL_SAVETXT
/***************************************************************************
 �������������� ���������� �������� ��������� ������ �� �� �����������������
 ( ��������� ) �������������.
***************************************************************************/
void SG_Entry::SaveTxt(
    OFormatter& txtfile,
    Grammar& gram
) const
{
    const int iclass = GetClass();
    if (is_quantor(iclass) || GetFlags2() != UNKNOWN)
        return;

    const GramClass &c = gram.classes()[iclass];

    const SynGram *sg = (const SynGram*)&gram;

    txtfile.printf(" // entry [");

    PrintName(txtfile);

    txtfile.printf("] contains %d form(s). key=%d\n", forms().size(), key);

    txtfile.printf(" %us ", sol_get_token(B_ENTRY).c_str());
    PrintName(txtfile);
    txtfile << sol_get_token(B_COLON) << c.GetName();

    txtfile.printf("\n %us\n", sol_get_token(B_OFIGPAREN).c_str());

    if (flags != 0 || flags_2 != lem::uint8_t(UNKNOWN))
    {
        txtfile.printf(
            "  %us%us%d",
            sol_get_token(B_FLAG).c_str(),
            sol_get_token(B_COLON).c_str(),
            flags
        );

        if (flags_2 != lem::uint8_t(UNKNOWN))
            txtfile.printf("%us%d", sol_get_token(B_COLON).c_str(), flags_2);

        txtfile.eol();
    }

    SaveCoordinatesTxt(txtfile, gram);

    for (auto & f : forms())
    {
        f.SaveTxt(txtfile, gram, *this);
    }

    txtfile.printf(
        " %us // %us\n",
        sol_get_token(B_CFIGPAREN).c_str(),
        sol_get_token(B_ENTRY).c_str()
    );

    txtfile.eol();
    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
#if !defined FAIND_NO_BOOST_REGEX
bool SG_Entry::DoesMatch(const boost::wregex &rx) const
{
    for (auto& f : forms())
    {
        if (boost::regex_match(f.name().c_str(), rx))
            return true;
    }

    return false;
}
#endif
#endif



#if defined SOL_SAVETXT
void SG_Entry::SaveXML(lem::OFormatter& xmlfile, Grammar& gram) const
{
    if (IsNonterminal() || is_quantor(iclass))
        return;

    xmlfile.printf("<entry>\n<class>%us</class><name>%us</name>\n",
        gram.classes()[iclass].GetName().c_str(), lem::encode_chars_to_xml(GetName().c_str()).c_str());

    if (!attrs().empty())
    {
        xmlfile.printf("<attrs>\n");

        for (lem::Container::size_type i = 0; i < attrs().size(); ++i)
        {
            const Solarix::GramCoordAdr &c = attrs()[i].GetCoord();

            const int istate = attrs()[i].GetState();
            const Solarix::GramCoord &coord = gram.coords()[c.GetIndex()];

            if (coord.IsBistable())
            {
                if (istate == 1)
                    xmlfile.printf("<attr><name>%us</name></attr>", coord.GetName().front().c_str());
            }
            else
            {
                xmlfile.printf("<attr><name>%us</name>", coord.GetName().front().c_str());
                xmlfile.printf("<state>%us</state></attr>\n", coord.GetStateName(istate).c_str());
            }
        }

        xmlfile.printf("</attrs>\n");
    }

    if (!form.empty())
    {
        bool has_forms = !form.empty();

        // ������ ������ - ��� ������� � ������������ ������ � ���������, ����������� � ���������
        // ������, �������� ���������� � �������. � ����� ������ ������� ����� ������ ����.
        if (form.size() == 1)
        {
            const Solarix::SG_EntryForm &f = form.front();

            bool has_dims = false;
            for (lem::Container::size_type i = 0; i < f.coords().size(); ++i)
            {
                const Solarix::GramCoordAdr &c = f.coords()[i].GetCoord();

                if (gram.classes()[iclass].dims().find(c.GetIndex()) != UNKNOWN)
                {
                    has_dims = true;
                    break;
                }
            }

            has_forms = has_dims;
        }

        if (has_forms)
        {
            xmlfile.printf("<forms>\n");

            for (lem::Container::size_type i = 0; i < form.size(); ++i)
            {
                xmlfile.printf("<form>\n");

                const Solarix::SG_EntryForm &f = form[i];
                xmlfile.printf("<name>%us</name>\n", lem::encode_chars_to_xml(f.name().c_str()).c_str());

                if (!f.coords().empty())
                {
                    xmlfile.printf("<attrs>\n");

                    for (lem::Container::size_type i = 0; i < f.coords().size(); ++i)
                    {
                        const Solarix::GramCoordAdr &c = f.coords()[i].GetCoord();

                        if (gram.classes()[iclass].dims().find(c.GetIndex()) != UNKNOWN)
                        {
                            const int istate = f.coords()[i].GetState();
                            const Solarix::GramCoord &coord = gram.coords()[c.GetIndex()];

                            if (coord.IsBistable())
                            {
                                if (istate == 1)
                                    xmlfile.printf("<attr><name>%us</name></attr>", coord.GetName().front().c_str());
                            }
                            else
                            {
                                xmlfile.printf("<attr><name>%us</name>", coord.GetName().front().c_str());
                                xmlfile.printf("<state>%us</state></attr>\n", coord.GetStateName(istate).c_str());
                            }
                        }
                    }

                    xmlfile.printf("</attrs>\n");
                }

                xmlfile.printf("</form>\n");
            }

            xmlfile.printf("</forms>\n");
        }
    }

    xmlfile.printf("</entry>\n");

    return;
}
#endif


const Grammar& SG_Entry::GetGrammar(const Dictionary &dict)
{
    return dict.GetSynGram();
}

Grammar& SG_Entry::GetGrammar(Dictionary &dict)
{
    return dict.GetSynGram();
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_Entry::BeforeFirstForm(Grammar& gram)
{
    ImportTags((SynGram&)gram);
    Base_Entry::BeforeFirstForm(gram);
    return;
}
#endif



SG_BogusEntry::SG_BogusEntry()
    : SG_Entry()
{
    static Lexem empty;
    name = &empty;
    return;
}

int SG_Entry::CountForms() const
{
    return CastSizeToInt(form.size());
}


SG_Quantor::SG_Quantor() : SG_Entry()
{}



#if defined SOL_LOADTXT
void SG_Entry::LoadBody(SynGram &sg, lem::StrParser<lem::UFString> &txt)
{
    txt.read_it(L"{");

    // ������� ������ ���� �������� � ���� ������
    const SG_Class & cls = sg.GetClass(GetClass());

    lem::MCollect<Solarix::GramCoordAdr> nulled_attrs;

    while (!txt.eof())
    {
        lem::StrParser<lem::UFString>::pos_type pos0 = txt.tellp();

        Solarix::GramCoordAdr icoord = UNKNOWN;
        lem::MCollect<int> istate; // � �������� ����� ���� ��������� ���������, �������� �������� �����������

        UFString t = txt.read();
        if (t == L'~')
        {
            // ����� ������ ���� ��� ������������ ����������, ������� ��������
            // ��������� ��� ����� ������.
            UFString cname = txt.read();

            icoord = sg.FindCoord(cname.c_str());
            if (icoord.IsDefined())
            {
                throw lem::E_BaseException(lem::format_str(L"Unknown coordinate name [%s]", cname.c_str()));
            }

            if (!sg.coords()[icoord.GetIndex()].IsBistable())
            {
                throw lem::E_BaseException(lem::format_str(L"Coordinate [%s] is not bistable", cname.c_str()));
            }

            istate.push_back(0);
        }
        else if (t == L"}")
        {
            // ����� ���� ������.
            break;
        }
        else if (t == L"{")
        {
            txt.seekp(pos0);
            break;
        }
        else
        {
            icoord = sg.FindCoord(t.c_str());
            if (!icoord.IsDefined())
            {
                throw lem::E_BaseException(lem::format_str(L"Unknown coordinate name [%s]", t.c_str()));
            }

            if (sg.coords()[icoord.GetIndex()].IsBistable())
            {
                // ��� ������������ ����������
                istate.push_back(1);
            }
            else
            {
                // ������ ���� ������ ��������� ����� ���������
                // ����� ���� ����� ������ ��������� ����� �������
                txt.read_it(L":");

                while (!txt.eof())
                {
                    UFString sname = txt.read();

                    if (sname == L'~')
                    {
                        nulled_attrs.push_back(icoord);
                        break;
                    }
                    else
                    {
                        const int ist = sg.coords()[icoord.GetIndex()].FindState(sname.c_str());

                        if (ist == UNKNOWN)
                        {
                            throw lem::E_BaseException(lem::format_str(L"Unknown state name [%s] for coordinate [%s]", sname.c_str(), t.c_str()));
                        }

                        istate.push_back(ist);

                        lem::StrParser<lem::UFString>::pos_type pos2 = txt.tellp();

                        if (txt.read() != L",")
                        {
                            txt.seekp(pos2);
                            break;
                        }
                    }
                }
            }
        }

        if (cls.attrs().find(icoord) != UNKNOWN || cls.tags().find(icoord) != UNKNOWN)
        {
            for (lem::Container::size_type i = 0; i < istate.size(); ++i)
                attr.push_back(Solarix::GramCoordPair(icoord, istate[i]));
        }
        else
        {
            // ������ ���� �������������� �����
            txt.seekp(pos0);
            break;
        }
    }

    // ��������, ��� ��� ��-������������ �������� ������
    for (lem::Container::size_type i = 0; i < cls.attrs().size(); ++i)
    {
        const Solarix::GramCoordAdr & icoord = cls.attrs()[i];
        if (nulled_attrs.find(icoord) != UNKNOWN)
            continue;

        if (attr.FindOnce(icoord) == UNKNOWN)
        {
            if (sg.coords()[icoord.GetIndex()].IsBistable())
            {
                attr.push_back(Solarix::GramCoordPair(icoord, 0));
            }
            else if (nulled_attrs.find(icoord) == UNKNOWN)
            {
                throw lem::E_BaseException(lem::format_str(L"Undefined attribute [%s] state", sg.coords()[icoord.GetIndex()].GetName().front().c_str()));
            }
        }
    }

    bool load_forms = true;

    // ������ ��������� �������������� �����.
    // ������ ����� �������� �������� ������� ��������� � ���������� ��������� ��������� �����
    while (load_forms && !txt.eof())
    {
        // ������� ���� ������ ������������ ��� ��� ���������.

        CP_Array form_dims;

        while (!txt.eof())
        {
            Solarix::GramCoordAdr icoord = UNKNOWN;
            int istate = UNKNOWN;

            lem::StrParser<lem::UFString>::pos_type pos1 = txt.tellp();

            UFString t = txt.read();
            if (t == L'{')
            {
                // ����� ���� ����� �����
                break;
            }
            else if (t == L'}')
            {
                txt.seekp(pos1);
                load_forms = false;
                t.clear();
                break;
            }
            else if (t == L'~')
            {
                // ����� ������ ���� ��� ������������ ����������
                UFString cname = txt.read();

                icoord = sg.FindCoord(cname.c_str());
                if (!icoord.IsDefined())
                {
                    throw lem::E_BaseException(lem::format_str(L"Unknown coordinate name [%s]", cname.c_str()));
                }

                if (!sg.coords()[icoord.GetIndex()].IsBistable())
                {
                    throw lem::E_BaseException(lem::format_str(L"Coordinate [%s] is not bistable", cname.c_str()));
                }

                istate = 0;
            }
            else
            {
                icoord = sg.FindCoord(t.c_str());
                if (!icoord.IsDefined())
                {
                    throw lem::E_BaseException(lem::format_str(L"Unknown coordinate name [%s]", t.c_str()));
                }

                if (sg.coords()[icoord.GetIndex()].IsBistable())
                {
                    // ��� ������������ ����������
                    istate = 1;
                }
                else
                {
                    // ������ ���� ������ ��������� ����� ���������
                    txt.read_it(L":");

                    UFString sname = txt.read();
                    istate = sg.coords()[icoord.GetIndex()].FindState(sname.c_str());
                    if (istate == UNKNOWN)
                    {
                        throw lem::E_BaseException(lem::format_str(L"Unknown state name [%s] for coordinate [%s]", sname.c_str(), t.c_str()));
                    }
                }
            }

            if (cls.dims().find(icoord) == UNKNOWN)
            {
                throw lem::E_BaseException(lem::format_str(L"Coordinate [%s] is not a dimension", t.c_str()));
            }

            form_dims.push_back(GramCoordPair(icoord, istate));
        }

        if (!load_forms)
            break;

        // ������ � �������� ������� (����������� ��� �������) ���� ����� �����
        lem::UFString form_name = txt.read();
        form_name.strip(L'"');

        Lexem fname(form_name.c_str());
        sg.GetDict().GetLexAuto().TranslateLexem(fname, false);
        fname.Translate(sg.GetDict().GetGraphGram(), 2);

        txt.read_it(L"}"); // ������ �������� �������������� ����� �������

        // ��������� �������������� ����� � ������
        CP_Array pairs(form_dims);

        const lem::Container::size_type n_attr = attrs().size();
        for (lem::Container::size_type i = 0; i < n_attr; i++)
            pairs.push_back(attrs()[i]);

        // �������������-�������� ������������ � �������
        const Solarix::Lexem *lex_ptr = sg.GetEntries().AddLexeme(fname);
        LEM_CHECKIT_Z(lex_ptr != nullptr);
        if (lex_ptr == nullptr)
        {
            lem::UFString msg(lem::format_str(L"Could not register new lexem '%s'", fname.c_str()));
            throw E_BaseException(msg);
        }

        // ������ ������������ ��� ����� ������������ � �������
        const Solarix::CP_Array *pairs_ptr = sg.GetEntries().AddCoordPairs(pairs);
        LEM_CHECKIT_Z(pairs_ptr != nullptr);
        if (pairs_ptr == nullptr)
        {
            throw E_BaseException(L"Could not register new coordinate pair array");
        }

        form.push_back(SG_EntryForm(lex_ptr, pairs_ptr));
    }

    if (form.empty())
    {
        // ���� �� ����� ����� �� ������, �� �������� ���� � ������, �����������
        // � ������ ������.

        const Solarix::Lexem *lex_ptr = sg.GetEntries().AddLexeme(GetName());
        LEM_CHECKIT_Z(lex_ptr != nullptr);
        if (lex_ptr == nullptr)
        {
            lem::UFString msg(lem::format_str(L"Could not register new lexem '%s'", GetName().c_str()));
            throw E_BaseException(msg);
        }

        CP_Array pairs;

        const lem::Container::size_type n_attr = attrs().size();
        for (lem::Container::size_type i = 0; i < n_attr; i++)
            pairs.push_back(attrs()[i]);

        const Solarix::CP_Array *pairs_ptr = sg.GetEntries().AddCoordPairs(pairs);
        LEM_CHECKIT_Z(pairs_ptr != nullptr);
        if (pairs_ptr == nullptr)
        {
            throw E_BaseException(L"Could not register new coordinate pair array");
        }

        form.push_back(SG_EntryForm(lex_ptr, pairs_ptr));
    }

    return;
}
#endif


void SG_Entry::PrepareAfterLoadingFromDatabase(SynGram &sg)
{
    FindRoot();
    InitializeHashes(sg.GetDict().GetGraphGram());
    return;
}


void SG_Entry::InitializeHashes(const GraphGram &g_gram)
{
    // ������ ����� ���-���������� � ��. ������ �� ������ ������.
    min_len = 127;
    max_len = 0;

    min_ml_len = 127;
    max_ml_len = 0;

    int i;
    const int nform = CastSizeToInt(form.size());

    //LEM_CHECKIT_Z( nform );

    for (i = 0; i < nform; i++)
    {
        // ����������� ���������� ����������...
        const Lexem &cont = form[i].name();
        const int npart = cont.Count_Lexems();

        // ���� ������������� � ������������ ����� ������.
        max_ml_len = std::max(max_ml_len, static_cast<int8_t>(npart));
        min_ml_len = std::min(min_ml_len, static_cast<int8_t>(npart));

        // ---------------------------------------------------------------------
        //                            .1.
        // ��������� ���� ������������ � ����������� ����� ������������
        // ����������� ��������� (����� ����!).
        const lem::int8_t len = cont.length();
        min_len = std::min(min_len, len);
        max_len = std::max(max_len, len);

    } // end for �� ���� �����������

    return;
}
