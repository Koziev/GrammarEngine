// -----------------------------------------------------------------------------
// File YMAP.CPP 
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                https://github.com/Koziev/GrammarEngine
// 
// Licensed under the terms of GNU Lesser GPL
//
// Content:
// YMAP program - dictionary dump utility.
//
// ������� ����������������� �������: ���������� �������������
// ��������� ���������� � ���������������� �������. ��������� - ���������
// ���� - �������� ������������� ��������� �������.
//
// ��������� ��������� ���������� �� ��������� ������ ������� (������ ����
// ���� dictionary.xml � ������� �����) � ������� ��������� (utf8) �����.
//
// 19.05.2006 - ��������� ����������� ��������� � ��������� ������ ��� �����
//              ������� (�� ��������� ������ ���� diction.bin � ������� ��������)
// 20.04.2007 - ��������� ����� -outdir=DDDD ��� �������� �������� ��� ������
//              ���������.
// 27.05.2007 - �������� ������� ����� ���� dictionary.xml (������� �������).
// 28.05.2007 - ����� -decompile ������� � ���� lexicon.sol � �������� �����
//              ��������� � ����, ��������� ��� ���������� � ygres.
// 13.06.2007 - ��� ������� ���������� LITE ������ ������� �������� ����������
//              �����������, ������ ��������� ������ �������� ��� ��������
//              �������.
// 27.07.2008 - ��������� ����� -export ��� �������� �������� ��������� ������
//              ��������� � ������� XML ��� ������� xml2sol.
// 29.07.2008 - ��������� ����� -regenerate_links ��� ������������ ������
//              ������� ��� ���������� � ��������. 
// 05.08.2008 - ��������� ��������� ������ ����������� ��� ��������� � ����
//              ��������.
// 10.08.2008 - ��������� ��������� ������ ��������� ��� ��������� � ����
//              �����������.
// 03.09.2008 - ��������� ��������� ������ ��������������-���������� �
//              ���������, � ����������� �� ���/���/�����/�����/����, ��
//              ������� ���� ���������
// 21.01.2009 - ���������� ������� � ������ SQL (����� -sql ���������)
// 05.03.2009 - ��������� ������������� � DECOMPILER
// 24.12.2009 - ������ ��������� ����� -regenerate_links
// 26.03.2010 - ��������� ��� - � XML ����� �������� ���������� BOM
// 08.06.2011 - ����������� ������� ���������������� � ��������������� �������,
//              ������������� � �������.
// 25.04.2018 - ����������� ���� � ������ C++11, ���������� ������ ����������.
// -----------------------------------------------------------------------------
//
// CD->12.04.2003
// LC->25.04.2018
// --------------

#include <lem/console_application.h>
#include <lem/logfile.h>
#include <lem/shell.h>
#include <lem/startup.h>
#include <lem/system_config.h>
#include <lem/console_streams.h>

#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/version.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntryEnumerator.h>

using namespace lem;
using namespace lem::Char_Stream;
using namespace Solarix;


struct XML_ExportParameters
{
    int max_entry_count = lem::int_max;

    XML_ExportParameters() {}

    void Parse(const char * str)
    {
        lem::MCollect<lem::CString> tokens;
        lem::parse(lem::FString(str), tokens, false);

        for (auto& token : tokens)
        {
            if (lem::is_int(token.c_str()))
            {
                max_entry_count = lem::to_int(token);
            }
            else
            {
                lem::UFString msg = format_str(L"Invalid option %s in xml export options string", to_unicode(token).c_str());
                throw lem::E_BaseException(msg);
            }
        }

        return;
    }
};

class Decompiler : public Base_Application
{
public:
    lem::zbool dump; // ��������� ������������� ����������� �������
    lem::zbool decompile; // ������� � ������ ��� ������� ygres

    lem::zbool export_xml; // ������� � XML ������ ��� ������� import
    XML_ExportParameters xml_params;

    lem::zbool export_sql; // �������������� � SQL
    SQL_Production sql_version; // ��������� ������ ������� ���� ��� ��������

    void OK() { mout->printf("%vfEOK%vn"); mout->flush(); }

public:
    Decompiler() : Base_Application(), sql_version("") {}

    void PrintBanner(OFormatter &txt, bool versbose = false);
    void Print_Heap(OFormatter &txt);
    void Echo(OFormatter &txt);
    void Help();
    void Go(const lem::Path &dict, const lem::Path &outdir);
};


void Decompiler::PrintBanner(OFormatter &txt, bool verbose)
{
    txt.printf("%vfEDecompiler%vn version %vfF%s%vn\n", sol_get_version().c_str());
    Print_Project_Info(txt);
    txt.eol();
    return;
}


// ************************************
// ����� �������� ������� � ���������.
// ************************************
void Decompiler::Help()
{
    mout->printf(
        "\nSome default values for options are listed in %vfAdecompiler.ini%vn file.\n"
        "For example, the messaging language is defined by variable %vfElang%vn in section %vfEui%vn.\n\n"
        "SOLARIS dictionary decompiler: it loads dictionary from binary file\n"
        "%vfFdiction.bin%vn and creates map file %vfFdiction.map%vn, containing a lot of internal\n"
        "information as well as disassembled entries, classes, rules and other\n"
        "structures.\n\n"
        "Usage: %vfEdecompiler%vn %vf8[%vndictionary_filename%vf8]%vn %vf8[%vn-outdir=XXX%vf8]%vn %vf8[%vn-decompile%vf8]%vn\n\n"
    );

    exit(1);
}

// **********************************************************
// ������ ������� � ������� �������� � ������������ ������.
// **********************************************************
void Decompiler::Print_Heap(OFormatter &txt)
{
    Echo(txt);
    PrintBanner(txt);
    txt.printf("Created %us\n", timestamp().c_str());
}


void Decompiler::Echo(OFormatter &txt)
{
    mout->printf("\nWriting %vfA%us%vn...", txt.GetStream()->GetName().GetUnicode().c_str());
    mout->flush();
}



void Decompiler::Go(const lem::Path &dict, const lem::Path &outdir)
{
    std::unique_ptr<OFormatter> nul_tty(new OFormatter(lem::Path(NULL_DEVICE))); // ������ ����� (���������� NUL:)

    lem::Path jpath(outdir);
    jpath.ConcateLeaf(lem::Path("journal"));
    lem::LogFile::Open(jpath); // ���� ������� � ��������� �������� outdir

    PrintBanner(*lem::LogFile::logfile, true);
    lem::System_Config::PrintInfo(*lem::LogFile::logfile);

    // ��������� ������ �������
    std::unique_ptr<Solarix::Dictionary> sol_id(new Solarix::Dictionary(&*nul_tty, merr));

    mout->printf("Loading dictionary %vfF%us%vn...", dict.GetUnicode().c_str());
    mout->flush();

    Load_Options opt;

    opt.load_semnet = true;
    opt.ngrams = true;

    bool ok = false;

    try
    {
        ok = sol_id->LoadModules(dict, opt);
    }
    catch (...)
    {
        ok = false;
    }

    if (!ok)
    {
        mout->printf("\n\nERROR!\nIncompatible dictionary version\n");
        lem::Process::Exit();
    }

    mout->printf("%vfE%F$3d%vn entries %vfAOK%vn\n", sol_id->GetSynGram().GetnEntry());
    CheckMemory();

    if (export_sql)
    {
        // ��������� �������� ������ ������� � SQL ������.

        sql_version.outdir = outdir;

        lem::Path exp(outdir);
        exp.ConcateLeaf(L"dictionary.sql");

        lem::Path exp2(outdir);
        exp2.ConcateLeaf(L"dictionary-alters.sql");

        if (sql_version.IsAscii())
        {
            lem::OFormatter exp_file(exp);
            lem::OFormatter alters_file(exp2);
            sol_id->Save_SQL(exp_file, alters_file, sql_version);
        }
        else
        {
            // UTF8
            lem::OUFormatter exp_file(exp, sql_version.WriteBOM());
            lem::OUFormatter alters_file(exp2, sql_version.WriteBOM());
            sol_id->Save_SQL(exp_file, alters_file, sql_version);
        }


        // � ��������� ���� - ������� ���������������� � ��������������� �������
        lem::Path exp_rules(outdir);
        exp_rules.ConcateLeaf(L"rules.sql");

        lem::Path exp2_rules(outdir);
        exp2_rules.ConcateLeaf(L"rules-alters.sql");

        if (sql_version.IsAscii())
        {
            lem::OFormatter exp_file(exp_rules);
            lem::OFormatter alters_file(exp2_rules);
            sol_id->SaveRules_SQL(exp_file, alters_file, sql_version);
        }
        else
        {
            // UTF8
            lem::OUFormatter exp_file(exp_rules, sql_version.WriteBOM());
            lem::OUFormatter alters_file(exp2_rules, sql_version.WriteBOM());
            sol_id->SaveRules_SQL(exp_file, alters_file, sql_version);
        }

        if (sql_version.lemmatizator)
        {
            // � ��������� ���� ��������� ������� �������������.
            lem::Path exp(outdir);
            exp.ConcateLeaf(L"lemmatizator.sql");

            lem::Path exp2(outdir);
            exp2.ConcateLeaf(L"lemmatizator-alters.sql");

            if (sql_version.IsAscii())
            {
                lem::OFormatter exp_file(exp);
                lem::OFormatter alters_file(exp2);
                sol_id->GetSynGram().SaveLemmatizatorSQL(exp_file, alters_file, sql_version);
            }
            else
            {
                // UTF8
                lem::OUFormatter exp_file(exp, sql_version.WriteBOM());
                lem::OUFormatter alters_file(exp, sql_version.WriteBOM());
                sol_id->GetSynGram().SaveLemmatizatorSQL(exp_file, alters_file, sql_version);
            }
        }


        // ������ ��� PREFIX ENTRY SEARCHER
        lem::Path exp_pes(outdir);
        exp_pes.ConcateLeaf(L"prefix_entry_searcher.sql");

        lem::Ptr<PrefixEntrySearcher> pes(sol_id->GetPrefixEntrySearcher());
        if (pes.NotNull())
            pes->Save_SQL(exp_pes, sql_version);
    }



    mout->printf("Decompiling and analyzing the dictionary..."); mout->flush();

    if (export_xml)
    {
        lem::Path p(outdir);
        p.ConcateLeaf(lem::Path("lexicon.xml"));
        OUFormatter xml(p, false);
        Echo(xml);
        lem::Path p2(outdir);
        p2.ConcateLeaf(lem::Path("lexicon.xsd"));
        OFormatter xsd(p2);
        sol_id->GetSynGram().Dump_XML(xml, xsd, xml_params.max_entry_count);
        OK();

        // ����� �� ��������� ���� XML ���� ����������� �������, ��������� ���
        // ��������� �������� xml2sol, �������� ������ ������ �� �����.
        const int nentry = CastSizeToInt(sol_id->GetSynGram().GetEntries().CountEntries(ANY_STATE, ANY_STATE));
        const int blocksize = 1000;
        const int nblock = (nentry / blocksize) + ((nentry%blocksize) == 0 ? 0 : 1);

        lem::Path pe(outdir);
        pe.ConcateLeaf(L"export");
        lem::OUFormatter export_list(pe);

        std::unique_ptr<WordEntryEnumerator> wenum(sol_id->GetSynGram().GetEntries().ListEntries());

        int ientry = 0;
        for (int iblock = 0; iblock < nblock && ientry < nentry; iblock++)
        {
            lem::UFString filename(lem::format_str(L"export_%d.xml", iblock));
            export_list.printf("%us\n", filename.c_str());

            lem::Path p(outdir);
            p.ConcateLeaf(lem::Path(filename));
            lem::OUFormatter xml(p, false);
            xml.printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<dataroot>\n");

            for (int i = 0; i < blocksize && wenum->Fetch(); i++, ientry++)
            {
                try
                {
                    const Solarix::SG_Entry &e = wenum->GetItem();

                    if (!e.GetName().empty())
                    {
                        e.SaveXML(xml, sol_id->GetSynGram());
                        xml.eol();
                    }
                }
                catch (const lem::E_BaseException &e)
                {
                    lem::mout->printf("Error occured when exporting entry #%d: %us\n", ientry, e.what());
                    lem::Process::Exit(1);
                }
                catch (const std::exception &e)
                {
                    lem::mout->printf("Error occured when exporting entry #%d: %s\n", ientry, e.what());
                    lem::Process::Exit(1);
                }
                catch (...)
                {
                    lem::mout->printf("Error occured when exporting entry #%d\n", ientry);
                    lem::Process::Exit(1);
                }
            }

            xml.printf("</dataroot>\n");
            lem::mout->dot();
        }
    }

    // Text file for dictionary map
    if (dump)
    {
        lem::Path p(outdir);
        p.ConcateLeaf(lem::Path("alphabet.map"));
        OUFormatter map(p);
        Print_Heap(map);
        sol_id->MapAlphabet(map);
        OK();
    }

    if (dump)
    {
        lem::Path p(outdir);
        p.ConcateLeaf(lem::Path("lexicon.map"));
        OUFormatter map(p);
        Print_Heap(map);
        sol_id->MapLexicon(map);
        OK();
    }

    if (decompile)
    {
        lem::Path p(outdir);
        p.ConcateLeaf(lem::Path("lexicon.sol"));
        OUFormatter txt(p);
        txt.printf("/*\n");
        Print_Heap(txt);
        txt.printf("*/\n\n");
        sol_id->GetSynGram().SaveTxt(txt);
        OK();
    }

    if (dump)
    {
        lem::Path p(outdir);
        p.ConcateLeaf(lem::Path("grammar.map"));
        OUFormatter map(p);
        Print_Heap(map);
        sol_id->MapTransformer(map);
        OK();
    }

    mout->printf("\n%vfAAll done.%vn\n");
    return;
}


int main(int argc, char *argv[])
{
    lem::LemInit initer;
    Decompiler app;

    app.Read_Ini(lem::Path("ymap.ini"));

    app.PrintBanner(*mout);

    if (
        argc == 2 && (
            !strcmp(argv[1] + 1, "help") ||
            !strcmp(argv[1] + 1, "?") ||
            !strcmp(argv[1] + 1, "h") ||
            !strcmp(argv[1] + 1, "-version")
            )
        )
        app.Help();

    // �� ��������� ���� ������� ���� � ������� ��������
    lem::Path dict("dictionary.xml");

    // � ���������� ������������ ��������� � ������� ��������
    lem::Path outdir;

    app.dump = true;

    try
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-' || argv[i][0] == '/')
            {
                if (memcmp(argv[i] + 1, "outdir=", 7) == 0)
                {
                    FString s(argv[i] + 8);
                    s.strip_apostrophes();
                    outdir = lem::Path(s);
                }
                else if (lem_eq(argv[i] + 1, "decompile"))
                {
                    app.dump = false;
                    app.decompile = true;
                }
                else if (lem_eq(argv[i] + 1, "dump"))
                {
                    app.dump = true;
                }
                else if (lem_eq(argv[i] + 1, "export") || lem_eq(argv[i] + 1, "xml"))
                {
                    app.dump = false;
                    app.decompile = false;
                    app.export_xml = true;
                    app.xml_params.Parse(argv[i + 1]);
                    i++;
                }
                else if (lem_eq(argv[i] + 1, "sql"))
                {
                    app.dump = false;
                    app.decompile = false;
                    app.export_xml = false;
                    app.export_sql = true;
                    app.sql_version = SQL_Production(argv[i + 1]);
                    i++;
                }
            }
            else
            {
                dict = lem::Path(argv[i]);
            }
        }

        if (!dict.DoesExist())
        {
            merr->printf("Dictionary configuration file not found.");
            return 1;
        }

        app.Go(dict, outdir);
    }
    catch (const lem::E_BaseException &ex)
    {
        merr->printf("Error: %us\n", ex.what());
    }
    catch (const std::exception &ex)
    {
        merr->printf("Error: %s\n", ex.what());
    }
    catch (...)
    {
        merr->printf("Error\n");
    }

    return 0;
}
