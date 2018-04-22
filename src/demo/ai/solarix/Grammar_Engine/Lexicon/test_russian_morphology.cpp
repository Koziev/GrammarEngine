// -----------------------------------------------------------------------------
// File TEST_RUSSIAN_MORPHOLOGY.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Grammar Engine test suite.
//
// ������ � ������� �������� �������������� ������.
//
// 25.07.2008 - �������� ������������� ���� ��� ��������������� �������
// 29.07.2008 - ��� ������ � ��������� �� �������� �������� ����
// 14.08.2008 - ��������� ����� �������������� ����������� - ���������� �����������
// 14.08.2008 - ��������� ����� ������ �� ���� N-�����
// 23.08.2008 - ��������� ������������� ����� ��� ���������� �����������
// 24.08.2008 - �������� ���� � ���������� ������������ ����-��
// 30.08.2008 - ��������� ����������� ���� ��������������� �����������
// 05.12.2008 - �������� ���� ������������� (sol_Syllabs)
// 05.12.2008 - �������� ���� �������� ������������� ��������� (���� ���-���)
// 23.12.2008 - �������� ���� �� �������� �������������� ���������
// 15.01.2009 - ��������� ��������� ������������� ������ ������������ ���
//              ����������� � �������������� ����������� �������� �����.
// 13.02.2009 - ��������� ����� ��� SentenceBroker'� � ������������.
// 19.02.2009 - ��������� ����� ����� ��������������� ����������� ���
//              ����� ��������� ���������������.
// 20.02.2009 - ��������� ��� ��������� ������ ������������ ��� ������ � 
//              ��� ��� ������� ����� �� � ��������.
// 20.11.2009 - �������������� �������������� ������������ �����������
//              ���������� � sentences-ru.txt � ��������� utf8.
// 09.04.2011 - ��������� ����� ������������
// 14.01.2012 - ��������� ����� ��� ������� sol_TranslateToNoun �
//              sol_TranslateToInfinitive.
// -----------------------------------------------------------------------------
//
// CD->14.10.2006
// LC->21.04.2018
// --------------

#include <assert.h>
#include <iostream>
#include <windows.h>

// Grammar Engine API
// API �������������� ������
#include "..\..\..\..\..\include\lem\solarix\solarix_grammar_engine.h"
#include "..\..\..\..\..\include\lem\solarix\_sg_api.h"

using namespace std;

extern void failed(HGREN hEngine);

extern bool is_delim(wchar_t c);
extern void print8(const char *utf8);

extern int CountLanguages(HGREN hEngine);
extern bool TestSyntaxAnalysis(HGREN hEngine, const wchar_t *Phrase, int Language, bool must_be_complete_analysis);
extern void TestMorphologicalAnalyzer(HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, bool use_model, int thread_no);
extern void TestSyntacticAnalyzer(HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, int thread_no);
extern void Test_Threading(HGREN hEngine, int id_language, const char *infile_morph, const char *infile_syntax);
extern void TestMiscellaneous(HGREN hEngine);
//extern void PrintGraphs( HGREN_RESPACK hPack );


#if defined WIN32
extern void wide(const wchar_t *ustr, FILE *f = stdout, int cp = CP_OEMCP);
#else
extern void wide(const wchar_t *ustr, FILE *f = stdout, int cp = 0);
#endif


static void TranslateToNoun(HGREN hEngine, const wchar_t *word)
{
    int id_entry_src = sol_FindEntry(hEngine, word, -1, -1);
    int id_entry_res = sol_TranslateToNoun(hEngine, id_entry_src);
    if (id_entry_res == -1)
        failed(hEngine);

    wchar_t entry_name[100];
    sol_GetEntryName(hEngine, id_entry_res, entry_name);

    printf("\n");
    wide(word);
    printf(" --> ");
    wide(entry_name);
    printf("\n");

    return;
}

static void TranslateToInfinitive(HGREN hEngine, const wchar_t *word)
{
    int id_entry_src = sol_FindEntry(hEngine, word, -1, -1);
    int id_entry_res = sol_TranslateToInfinitive(hEngine, id_entry_src);
    if (id_entry_res == -1)
        failed(hEngine);

    wchar_t entry_name[100];
    sol_GetEntryName(hEngine, id_entry_res, entry_name);

    printf("\n");
    wide(word);
    printf(" --> ");
    wide(entry_name);
    printf("\n");

    return;
}



extern bool ProbeRussian(HGREN hEngine);

void VisualizeMorphology(HGREN hEngine, const wchar_t *Sentence)
{
    HGREN_RESPACK hs = sol_MorphologyAnalysis(hEngine, Sentence, 0, 0, 60000, -1);

    if (hs != nullptr)
    {
        const int nroot = sol_CountRoots(hs, 0);

        wchar_t buffer[60], ename[60], cname[60], coord_name[60], state_name[60];

        for (int i = 1; i < nroot - 1; ++i)
        {
            HGREN_TREENODE hNode = sol_GetRoot(hs, 0, i);

            printf("\nnode #%d ", i);

            int ipos = sol_GetNodePosition(hNode);
            printf("pos=%d ", ipos);

            printf("name=");
            sol_GetNodeContents(hNode, buffer);
            wide(buffer);

            const int nver = sol_GetNodeVersionCount(hEngine, hNode);
            printf(" versions=%d\n", nver);

            for (int iv = 0; iv < nver; ++iv)
            {
                printf("  version #%d ", iv);

                const int id_entry = sol_GetNodeVerIEntry(hEngine, hNode, iv);
                const int id_class = sol_GetEntryClass(hEngine, id_entry);

                if (sol_GetClassName(hEngine, id_class, cname) == 0 && sol_GetEntryName(hEngine, id_entry, ename) == 0)
                {
                    wide(cname);
                    printf(":");
                    wide(ename);
                    printf("{} ");
                }

                int ncoord = sol_GetNodeVerPairsCount(hNode, iv);
                for (int j = 0; j < ncoord; ++j)
                {
                    int id_coord = sol_GetNodeVerPairCoord(hNode, iv, j);
                    int id_state = sol_GetNodeVerPairState(hNode, iv, j);

                    if (sol_CountCoordStates(hEngine, id_coord) == 0)
                    {
                        if (id_state == 0)
                            printf("~");


                        sol_GetCoordName(hEngine, id_coord, coord_name);
                        wide(coord_name);
                    }
                    else
                    {
                        if (
                            sol_GetCoordName(hEngine, id_coord, coord_name) == 0 &&
                            sol_GetCoordStateName(hEngine, id_coord, id_state, state_name) == 0)
                        {
                            wide(coord_name);
                            printf(":");
                            wide(state_name);
                        }
                    }

                    printf(" ");
                }

                printf("\n");
            }
        }

        sol_DeleteResPack(hs);
    }


    return;
}



extern bool TestLink(HGREN hEngine, const wchar_t *Word1, int Class1, const wchar_t *Word2, int Class2);


void stem(HGREN hEngine, const wchar_t *Word)
{
    wchar_t normalized[64];
    wcsncpy(normalized, Word, 63);

    DWORD r = CharUpperBuffW(normalized, wcslen(normalized));
    assert(r == wcslen(normalized));

    // ATTENTION!!! ����� ������ ���� � ������� ��������!!!
    const int stem_len = sol_Stemmer(hEngine, normalized);

    printf("STEM(");
    wide(Word);
    printf(")=");

    if (stem_len > 0)
    {
        normalized[stem_len] = 0;
        wide(normalized);
    }

    if (wcslen(normalized) >= wcslen(Word))
        failed(hEngine);

    printf("\n");

    return;
}


extern void Print_StrList(HGREN hEngine, HGREN_STR hStr);


extern void Print_IntList(HGREN hEngine, HGREN_INTARRAY hList);





void Test_ProjectWord(
    HGREN hEngine,
    const wchar_t *Word,
    bool AllowDynforms,
    const char *ResLenCondition = nullptr,
    int ResLen = 0
)
{
    HGREN_WCOORD hList = sol_ProjectWord(hEngine, Word, AllowDynforms);
    if (hList == nullptr)
        failed(hEngine);

    if (hList != nullptr)
    {
        const int nproj = sol_CountProjections(hList);

        if (ResLenCondition != nullptr)
        {
            if (strcmp(ResLenCondition, "==") == 0)
            {
                if (nproj != ResLen)
                    failed(hEngine);
            }
            else if (strcmp(ResLenCondition, ">") == 0)
            {
                if (nproj <= ResLen)
                    failed(hEngine);
            }
        }

        cout << "Number of projections: " << nproj << "\n";

        for (int i = 0; i < nproj; i++)
        {
            const int ientry = sol_GetIEntry(hList, i);
            const int iclass = sol_GetEntryClass(hEngine, ientry);

            wchar_t entry_name[32] = L"", class_name[32] = L"";

            sol_GetEntryName(hEngine, ientry, entry_name);
            sol_GetClassName(hEngine, iclass, class_name);

            wide(entry_name);
            cout << ":";
            wide(class_name);
            cout << "\n";
        }
    }

    sol_DeleteProjections(hList);
    return;
}



void Test_Russian_Morphology(HGREN hEngine, bool use_model)
{
    // ��������, ��� ������� �������������� ���������� ������� _sg_api.h
    wchar_t ClassName[64];
    sol_GetClassName(hEngine, NOUN_ru, ClassName);
    if (wcscmp(ClassName, L"���������������") != 0)
    {
        failed(hEngine);
        return;
    }

    {
        int id1 = sol_FindEntry(hEngine, L"��������", INFINITIVE_ru, -1);
        auto hlist1 = sol_ListLinksTxt(hEngine, id1, TO_ADJ_link, 0);
        int nlink = sol_LinksInfoCount(hEngine, hlist1);
        for (int i = 0; i < nlink; ++i)
        {
            int id2 = sol_LinksInfoEKey2(hEngine, hlist1, i);
            int state2 = sol_GetEntryCoordState(hEngine, id2, PASSIVE_PARTICIPLE_ru);
            if (state2 == 1)
            {
                wchar_t name2[33];
                sol_GetEntryName(hEngine, id2, name2);
                wide(name2);
            }
        }
    }



    TestMiscellaneous(hEngine);

    // �������� ������ ������ ���������������� ��� ����������� ����� � ������� ��������.
    // ��� ��� � ����������� ������ �������� ��������� �� ���������, ������ ����������� �� �����.
    HFLEXIONS hFlexs = sol_FindFlexionHandlers(hEngine, L"��������", 0);
    if (hFlexs != nullptr)
    {
        // ������� �������� �������� ��� ������� �����
        const int npar = sol_CountParadigmasInFlexionHandlers(hEngine, hFlexs);

        wchar_t ParadigmaName[64];
        for (int i = 0; i < npar; i++)
        {
            int rc = sol_GetParadigmaInFlexionHandlers(hEngine, hFlexs, i, ParadigmaName);
            wide(L"Best suitable paradigma: "); wide(ParadigmaName); wide(L"\n");


            HFLEXIONTABLE hFlex = sol_BuildFlexionHandler(hEngine, hFlexs, ParadigmaName, -1);
            if (hFlex != nullptr)
            {
                const wchar_t *wf = sol_GetFlexionHandlerWordform(hEngine, hFlex, L"�����:���� �����:��");
                wide(wf);
                wide(L"\n");
            }

            sol_DeleteFlexionHandler(hEngine, hFlex);
        }

        sol_DeleteFlexionHandlers(hEngine, hFlexs);
    }


    if (!ProbeRussian(hEngine))
        return;

    const int MAX_LEN = sol_MaxLexemLen(hEngine);

    // �������� ����� �������� ������. 0 - Lite, 1 - Pro, 2 - Premium (������ ��� ���������� ������)
    const int eversion = sol_GetVersion(hEngine, nullptr, nullptr, nullptr);


    // ������� �������������� �������� �����.
    int id_entry0 = sol_FindEntry8(hEngine, "\xD0\x9F\xD0\x9B\xD0\x9E\xD0\xA5\xD0\x9E\xD0\x99", -1, -1);
    wchar_t word_rest[32] = L"������";
    int rest_rc = sol_RestoreCasing(hEngine, word_rest, id_entry0);

    // �������� graceful cancellation �������� �� ��������� ��������� ������������� �������.
    // ��� ����� ������� �� ���� ������� �����������, ������� � ������� �������� ������������� ����� ������, �
    // ��������� ������� � 5 ������. �������� �� ��������� 5-6 ������ ������� sol_SyntaxAnalysis ������ ����������.
    HGREN_RESPACK hPack0 = sol_SyntaxAnalysis(hEngine, L"����� �������� ������ ������� �������� �������� �������� ������� �������, ����������� ��������� ��� ������ ���", 0, 0, 5000, RUSSIAN_LANGUAGE);
    sol_DeleteResPack(hPack0);

    int ie1 = sol_FindEntry(hEngine, L"����", /*Solarix::API::*/NOUN_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);
    // ������ ���� ������� ���
    if (sol_GetNounGender(hEngine, ie1) != FEMININE_GENDER_ru)
        failed(hEngine);

    // ������ ���� ���������������
    if (sol_GetEntryClass(hEngine, ie1) != NOUN_ru)
        failed(hEngine);

    // �������� ��������������� - �������� ����� ��� �������������� ����� ���������� ������
    wchar_t Buffer[64];
    if (sol_GetNounForm(hEngine, ie1,
        PLURAL_NUMBER_ru, // ������������� �����
        DATIVE_CASE_ru, // ��������� �����
        Buffer) != 0)
        failed(hEngine);

    if (!!wcscmp(Buffer, L"�����"))
        failed(hEngine);

    if (eversion > 0)
    {
        // ���� �������������.
        // ������ �������� ���� �����-���������_���������_��_�����
        const wchar_t* Word0[] =
        {
         L"�����", L"���+��",
         L"����", L"����",
         L"��Ҩ���", L"��+Ҩ+���",
         L"������", L"������",
         L"����������", L"�����+��+���",
         L"���������", L"��+���+��+��",
         L"������������������", L"��+��+��+���+��+���+��+��",
         L"�������", L"���+��+��",
         L"����", L"�+�+��",
         L"��������", L"��+��+��+��",
         L"����������", L"��+��+����+��",
         L"����", L"����",
         L"�����", L"���+��",
         L"��Ψ���", L"���+��+��",
         L"�����", L"���+��",
         L"������", L"����+��",
         L"���������������", L"��+����+��+��+��+��+�",
         L"�������", L"����+���",
         L"�������������", L"��+����+��+���+��",
         L"�������������", L"����+��+����+��+�",
         L"�������������", L"���+��+��+���+��+�",
         L"���", L"���",
         L"����", L"�+���",
         L"��", L"��",
         L"��", L"��",
         L"������", L"��+����",
         nullptr };

        wchar_t Syllabs[64];

        int is = 0;
        while (Word0[is] != nullptr)
        {
            int rc = sol_Syllabs(hEngine, Word0[is], L'+', Syllabs, RUSSIAN_LANGUAGE);
            if (rc != 0)
                failed(hEngine);

            wide(Word0[is]); wprintf(L"->"); wide(Syllabs); wprintf(L"\n");
            if (!!wcscmp(Syllabs, Word0[is + 1]))
                failed(hEngine);

            is += 2;
        }
    }


    /*
     // ----------------------
     // �������� �� �������� ������������ ��� ��������� ������������� �����������, ������� ��������� ������� �������
     // ���� �����������. ������ ������������ ������ ��������� ������� �� ����� �������� � ����� � ��������������� ����������.
     const wchar_t tst1[] = L"�\"        ���������      �������� �. �. �������-���������"
                            L"      �������� �. �. ���������,      � 19.9.44 �.      �������-�����      ������� � �. 18-�"
                            L"      (�� 4.8.44 �.) �������-���������      �������� �. � �������-�����      ������� �. �.,"
                            L"        �������-�����      ������� �. �. �������-���������      ������ �. �. ���������"
                            L"      ������� �. �. 38-� �������-���������      ���������� �. �. �������-�����      ������ �. �.,"
                            L"        ���������,      � 28.7 44 �.      �������-�����      ������� �. �. �������-�����"
                            L"      �������� �. �. �������-�����      ��������� � �. 60-� �������-���������      �������� �. � ���������,      � 28.7 44 �.      �������-����� �/�      �������� �. �.,        �������-�����      ������ �. �. �������-�����      ���-�������� �. �.,        � 23.7.44 �.      ���������      ������ �. �.,        � 23.8.44 �.      �������-�����      �������� �. � �������-�����      ����� �. �.,        � 11.8.44�.      ���������      ������� � �.      (� 19.9 44 �. �������-�����) 1-� ����������� ��������      (�� 6.9 .4";
     HGREN_STR htok1 = sol_TokenizeW( hEngine, tst1, RUSSIAN_LANGUAGE );
     // ----------------------
    */


    // ������� �������������� � ������ '������' ����
    const wchar_t *words[] =
    {
     L"������", L"*",
     L"�����-����", L"*",
     L"������-������", L"@",
     L"���-����", L"@",
     L"��-������", L"@",
     L"��� - ���", L"@",
     L"���  ���", L"@",
     L"����", L"*",
     L"������- ������", L"@",
     L"�������", L"@",
     L"�����", L"@",
     L"������", L"@",
     L"�����", L"@",
     L"�������", L"@",
     L"�� ������������", L"@",
     L"�� ����� ���", L"@",
     L"������-�����", L"@",
     L"���-���", L"@",
     nullptr
    };

    int iw = 0;
    while (words[iw] != nullptr)
    {
        if (*words[iw + 1] != L'*' && eversion == 0)
        {
            iw += 2;
            continue;
        }

        Test_ProjectWord(hEngine, words[iw], false, ">", 0);
        iw += 2;
    }


    // ���������� ����� � ������� �����.
    wchar_t Word[64] = L"������";
    int changed = sol_TranslateToBase(hEngine, Word, 0);
    if (changed != 1 || !!wcscmp(Word, L"�����"))
        failed(hEngine);

    wcscpy(Word, L"����������");
    changed = sol_TranslateToBase(hEngine, Word, 0);
    if (changed != 1 || !!wcscmp(Word, L"���������"))
        failed(hEngine);


    // ��� ���� ��������� ���������� � ������� �����, ������������
    // ��� ��������. ��� ����� ���� �������� 2 ������� �����:
    // ���. ��� � ������� ����
    wcscpy(Word, L"����");
    HGREN_STR hStr = sol_TranslateToBases(hEngine, Word, 0);
    if (eversion > 0)
    {
        if (sol_CountStrings(hStr) != 2)
            failed(hEngine);
    }

    Print_StrList(hEngine, hStr);


    wcscpy(Word, L"���");
    hStr = sol_TranslateToBases(hEngine, Word, 1);
    Print_StrList(hEngine, hStr);



    if (eversion == 0)
        // ������ ��� ����� - ��� ������ Pro � Premium
        return;


    // ������ ������ ������� �� ��� ������ ��������� ������ � ��������� ������
    // �������������� ����� �����.
    // http://www.solarix.ru/api/ru/sol_FindEntry.shtml
    // ������� ���������� ��������� ������.
    int iv = sol_FindEntry(hEngine, L"�����", /*Solarix::API::*/VERB_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);
    if (iv == -1)
        failed(hEngine);

    // http://www.solarix.ru/api/ru/sol_GetEntryClass.shtml
    if (sol_GetEntryClass(hEngine, iv) != VERB_ru)
        failed(hEngine);

    // ������ ������ �� ������������ ���������� � ������� ��������������� ����������.
    wchar_t b[64] = L"";
    if (sol_GetVerbForm(
        hEngine,
        iv,
        /*Solarix::API::*/SINGULAR_NUMBER_ru, // ������������ �����
        /*Solarix::API::*/FEMININE_GENDER_ru, // ������� ���
        /*Solarix::API::*/PAST_ru, // ��������� �����
        /*Solarix::API::*/PERSON_3_ru, // 3� ����
        b
    ) != 0)
        failed(hEngine);

    // ������������ �����, ������� ���, ��������� �����, 3� ����
    if (!!wcscmp(b, L"�����"))
        failed(hEngine);

    int iadj = sol_FindEntry(hEngine, L"�����", /*Solarix::API::*/ADJ_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);
    int inoun = sol_FindEntry(hEngine, L"�����", /*Solarix::API::*/NOUN_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);
    int iverb = sol_FindEntry(hEngine, L"�����", /*Solarix::API::*/VERB_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);

    if (iadj == -1 || inoun == -1 || iverb == -1)
        failed(hEngine);

    // �������� ��������� ��������� ���������������
    if (sol_GetAdjectiveForm(hEngine, iadj,
        SINGULAR_NUMBER_ru, // ������������ �����
        NEUTRAL_GENDER_ru, // ������� ���
        GENITIVE_CASE_ru, // ����������� �����
        ANIMATIVE_FORM_ru, // ������������
        0, // ��������� �����
        SUPERLATIVE_FORM_ru, // ������������ �������
        b) != 0)
        failed(hEngine);

    if (!!wcscmp(b, L"���������"))
        failed(hEngine);


    int res = 0;

    // �������� ��������� ������������ ���������������� � ������� � ������.
    wchar_t ibuffer[1024], buffer[64], buffer2[64], buffer3[64], buffer4[64];
    char abuffer[8000], aibuffer[64], abuffer2[64], abuffer3[64], abuffer4[64];
    for (int i = 0; i < 20; i++)
    {
        const int v = i < 12 ? i : (i == 12 ? 21 : 101 * i);
        *ibuffer = 0;
        sol_Value2Text(hEngine, ibuffer, v, /*Solarix::API::*/FEMININE_GENDER_ru);
        WideCharToMultiByte(CP_OEMCP, 0, ibuffer, wcslen(ibuffer) + 1, aibuffer, sizeof(aibuffer), nullptr, nullptr);

        res = sol_CorrAdjNumber(
            hEngine,
            iadj,
            v,
            /*Solarix::API::*/ NOMINATIVE_CASE_ru,
            sol_GetNounGender(hEngine, inoun),
            /*Solarix::API::*/ANIMATIVE_FORM_ru,
            buffer4
        );

        if (res != 0)
            failed(hEngine);

        int c = WideCharToMultiByte(
            CP_OEMCP,
            0,
            buffer4, wcslen(buffer4) + 1,
            abuffer4, sizeof(abuffer4),
            nullptr, nullptr
        );

        res = sol_CorrNounNumber(
            hEngine,
            inoun,
            v,
            NOMINATIVE_CASE_ru,
            -1,
            buffer
        );

        WideCharToMultiByte(CP_OEMCP, 0, buffer, wcslen(buffer) + 1, abuffer, sizeof(abuffer), nullptr, nullptr);

        res = sol_CorrVerbNumber(hEngine, iverb, v, sol_GetNounGender(hEngine, inoun), /*Solarix::API::*/PAST_ru, buffer2);
        WideCharToMultiByte(CP_OEMCP, 0, buffer2, wcslen(buffer2) + 1, abuffer2, sizeof(abuffer2), nullptr, nullptr);

        res = sol_CorrVerbNumber(hEngine, iverb, v, sol_GetNounGender(hEngine, inoun), /*Solarix::API::*/PRESENT_ru, buffer3);
        WideCharToMultiByte(CP_OEMCP, 0, buffer3, wcslen(buffer3) + 1, abuffer3, sizeof(abuffer3), nullptr, nullptr);

        cout << v << ": " << aibuffer << " " << abuffer4 << " " << abuffer << " " << abuffer2 << "(" << abuffer3 << ")\n";
    }


    printf("\n\n");

    // � ����������� ������
    for (int i = 0; i < 20; i++)
    {
        const int v = i < 12 ? i : (i == 12 ? 21 : 101 * i);

        wide(L"���� ");
        printf("%d ", v);

        res = sol_CorrAdjNumber(
            hEngine,
            iadj,
            v,
            /*Solarix::API::*/ ACCUSATIVE_CASE_ru,
            sol_GetNounGender(hEngine, inoun),
            /*Solarix::API::*/ANIMATIVE_FORM_ru,
            buffer4
        );

        if (res != 0)
            failed(hEngine);

        wide(buffer4);
        printf(" ");

        res = sol_CorrNounNumber(
            hEngine,
            inoun,
            v,
            ACCUSATIVE_CASE_ru, // NOMINATIVE_CASE_ru,
            -1,
            buffer
        );

        wide(buffer);
        printf("\n");
    }



    // ********************************
    // ��� ��������� ���������������
    // ********************************

    iadj = sol_FindEntry(hEngine, L"�������", /*Solarix::API::*/ADJ_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);

    sol_GetAdjectiveForm(hEngine, iadj, SINGULAR_NUMBER_ru, MASCULINE_GENDER_ru, ACCUSATIVE_CASE_ru, INANIMATIVE_FORM_ru, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"�������") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, SINGULAR_NUMBER_ru, MASCULINE_GENDER_ru, ACCUSATIVE_CASE_ru, ANIMATIVE_FORM_ru, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"��������") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, SINGULAR_NUMBER_ru, FEMININE_GENDER_ru, ACCUSATIVE_CASE_ru, -1, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"�������") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, SINGULAR_NUMBER_ru, NEUTRAL_GENDER_ru, ACCUSATIVE_CASE_ru, -1, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"�������") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, PLURAL_NUMBER_ru, -1, ACCUSATIVE_CASE_ru, INANIMATIVE_FORM_ru, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"�������") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, PLURAL_NUMBER_ru, -1, ACCUSATIVE_CASE_ru, ANIMATIVE_FORM_ru, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"�������") != 0) failed(hEngine);



    // ��������� �������� ����� �� �������
    int ientry = -1, iform = -1, iclass = -1;
    int nproj = sol_FindWord(hEngine, L"����", &ientry, &iform, &iclass);
    if (nproj < 1)
        failed(hEngine);


    // �������������� ����� ����� ��������� � ���������� iclass (��������� ��� 
    // ����������� �������� ������� ��. � ����� sg_api.h).
    if (iclass != NOUN_ru)
        failed(hEngine);


    printf("\n\n");

    // ������ ����, ��� ����� �������� ��������� �� ��������������.
    const wchar_t* adjs[4] = { L"��������", L"�������", L"���", L"������" };
    for (int i = 0; i < 4; ++i)
    {
        int id_entry = -1, iform = -1, iclass = -1;
        int nproj = sol_FindWord(hEngine, adjs[i], &id_entry, &iform, &iclass);

        // ��� ���� ����� � ��������� ������ �������� ��������������� �������� � ID=PARTICIPLE_ru
        // http://www.solarix.ru/api/ru/sol_GetEntryCoordState.shtml
        int id_state = sol_GetEntryCoordState(hEngine, id_entry, PARTICIPLE_ru);
        if (id_state == 1)
        {
            // �������� 1 - ���������
            wide(adjs[i]);
            printf(" is an adjectival participle; ");

            // ��������� ���������� �������� - ���, �����, �����
            int aspect = sol_GetEntryCoordState(hEngine, id_entry, ASPECT_ru);
            switch (aspect)
            {
            case PERFECT_ru: printf("perfect "); break;
            case IMPERFECT_ru: printf("imperfect "); break;
            }

            int tense = sol_GetEntryCoordState(hEngine, id_entry, TENSE_ru);
            switch (tense)
            {
            case PAST_ru: printf("past "); break;
            case PRESENT_ru: printf("present "); break;
            case FUTURE_ru: printf("future "); break;
            }

            int voice = sol_GetEntryCoordState(hEngine, id_entry, PASSIVE_PARTICIPLE_ru);
            switch (voice)
            {
            case 1: printf("passive "); break;
            default: printf("active "); break;
            }

            printf("\n");
        }
        else
        {
            // �������� 0 - ��������������
            wide(adjs[i]);
            printf(" is an adjective\n");
        }
    }




    // ************************************************************************************
    // ����� ��� ������ ������������ ������.
    // ��������� � ������������ http://www.solarix.ru/for_developers/docs/tokenizer.shtml
    // ************************************************************************************

    // ���������, ��� ������ ������ �������� ������������ �����������.
    const wchar_t text_with_empty_line[] = L"������ �����������\n\n������ \n ����������� \n\n ������ �����������.";
    HGREN_SBROKER hSegm0 = sol_CreateSentenceBrokerMemW(hEngine, text_with_empty_line, RUSSIAN_LANGUAGE);
    int nsent0 = 0, rc;
    while ((rc = sol_FetchSentence(hSegm0)) != -1)
    {
        char *sentence_buf = new char[rc * 6 + 1];
        sol_GetFetchedSentence8(hSegm0, sentence_buf);

        printf("#%d-->", nsent0);
        print8(sentence_buf);
        printf("\n");
        delete[] sentence_buf;
        nsent0++;
    }
    sol_DeleteSentenceBroker(hSegm0);
    if (nsent0 != 3)
        failed(hEngine);


    const wchar_t etalons_ru[] = L"..\\..\\..\\..\\..\\scripts\\rewriter\\etalons-ru.txt";
    if (GetFileAttributesW(etalons_ru) != (DWORD)-1)
    {
        // http://www.solarix.ru/for_developers/api/morphology-analyzer-api.shtml#sol_CreateSentenceBroker
        HGREN_SBROKER hBroker = sol_CreateSentenceBroker(hEngine, etalons_ru, nullptr, RUSSIAN_LANGUAGE);

        if (!hBroker)
            failed(hEngine);
        else
        {
            while (true)
            {
                int rc = sol_FetchSentence(hBroker);
                if (rc == -2)
                {
                    failed(hEngine);
                    break;
                }

                if (rc == -1)
                    // ����� ��������� ��������.
                    break;

                wchar_t *sentence_buf = new wchar_t[rc + 1];
                if (sol_GetFetchedSentenceW(hBroker, sentence_buf) != rc)
                {
                    failed(hEngine);
                    break;
                }

                delete[] sentence_buf;
            }

            sol_DeleteSentenceBroker(hBroker);
        }
    }


    const wchar_t* slist[] =
    {
     L"������.",
     L"������������� ���� ������.",
     L"������������� ���� ������.",
     L"������������� ���������� ���.",
     L"���������� ������ ����������.",
     L"���������� ���������������� ����������.",
     L"��� ������ ������ � ���?",
     L"�.�. ������ - ������� ������� ����.",
     L"� �.�.",
     L"�����, ������ � �.�.",
     L"������, �������, ��. ������!",
     L"����� �� ����� 3.1415926!",
     L"��!",
     L"����������...",
     L"�������=1?",
     L"���������� ��� �����!",
     L"� ���?!",
     L"� ���!!!",
     L"�� �����...",
     L"� ��. �����.",
     L"� ������ �.�. - ������� ������� ��������.",
     L"������� �.�. ������� ����� ����� � ���.",
     L"�.�. ������� ������� ����� � ���.",
     L"��. ��� ��� �����������.",
     L"�.�.����������� - ������������ �������� ������� ��������� �������.",
     L"�.������� ��� ��������� � �������.",
     nullptr
    };

    int n_sent = 0, isent = 0;
    std::wstring slist2;
    while (slist[isent] != nullptr)
    {
        if (isent > 0) slist2 += L" ";
        slist2 += slist[isent++];
        n_sent++;
    }

    // ��������� ����� � ����������� ������. � API ���� ����� ��������� ��� ������
    // ����������� �� �������� ������, ������ ���������� ����� ������ ������� - ����������
    // �����, �������������� ��������� �������.
    HGREN_SBROKER hBroker = sol_CreateSentenceBrokerMemW(hEngine, slist2.c_str(), RUSSIAN_LANGUAGE);

    if (!hBroker)
        failed(hEngine);

    isent = 0;
    while (true)
    {
        int rc = sol_FetchSentence(hBroker);
        if (rc == -1)
        {
            // ����� ��������� ��������.
            break;
        }
        else if (rc == -2)
        {
            failed(hEngine);
            break;
        }

        wchar_t *sentence_buf = new wchar_t[rc + 1];
        if (sol_GetFetchedSentenceW(hBroker, sentence_buf) != rc)
        {
            failed(hEngine);
            break;
        }

        if (wcscmp(sentence_buf, slist[isent]) != 0)
        {
            failed(hEngine);
            break;
        }

        delete[] sentence_buf;
        isent++;
    }

    sol_DeleteSentenceBroker(hBroker);
    hBroker = nullptr;



    // �������� ��������� ������� ��� ������, ����� ������ � ������ �� ������������
    // ���������� ������������ �����������.
    const wchar_t rusent[] = L"����� � ������ ������ ���� �� ������ ������";
    hBroker = sol_CreateSentenceBrokerMemW(hEngine, rusent, RUSSIAN_LANGUAGE);

    if (!hBroker)
        failed(hEngine);

    isent = 0;
    while (true)
    {
        int rc = sol_FetchSentence(hBroker);
        if (rc == -2)
        {
            failed(hEngine);
            break;
        }

        if (rc == -1)
            // ����� ��������� ��������.
            break;

        wchar_t *sentence_buf = new wchar_t[rc + 1];
        if (sol_GetFetchedSentenceW(hBroker, sentence_buf) != rc)
        {
            failed(hEngine);
            break;
        }

        if (wcscmp(sentence_buf, rusent) != 0)
        {
            failed(hEngine);
            break;
        }

        delete[] sentence_buf;
        isent++;
    }

    sol_DeleteSentenceBroker(hBroker);


    // ----------- ������������� ���� ��� ������������� ����
    const wchar_t rusent2[] = L"��������  � ��.                     ";
    hBroker = sol_CreateSentenceBrokerMemW(hEngine, rusent2, RUSSIAN_LANGUAGE);

    if (!hBroker)
        failed(hEngine);

    isent = 0;
    while (true)
    {
        int rc = sol_FetchSentence(hBroker);
        if (rc == -2)
        {
            failed(hEngine);
            break;
        }

        if (rc == -1) break;

        wchar_t *sentence_buf = new wchar_t[rc + 1];
        if (sol_GetFetchedSentenceW(hBroker, sentence_buf) != rc)
        {
            failed(hEngine);
            break;
        }

        delete[] sentence_buf;
        isent++;
    }

    sol_DeleteSentenceBroker(hBroker);


    // ---------------------- ��������� ����� ������������ ����������� ----------------------------


    // -------------------- ����� ������������ ---------------------
    //
    // ��������� � ������������ http://www.solarix.ru/for_developers/docs/tokenizer.shtml

    const wchar_t *tokenizer[] =
    {
        /* ----- ����������� -------   --����� ������--  --��������� �� ������� ������ ������--  */
        L"...",                               L"1",                     L"false",
        L"20:23:01",                          L"1",                     L"false",
        L"����� �����?�",                     L"5",                     L"false",
        L"��������-����",                    L"5",                     L"false",
        L"\"����� ����\"",                    L"4",                     L"false",
        L"�!�",                               L"3",                     L"false",
        L"����� �����?�",                     L"5",                     L"false",
        L"��. ����.",                         L"4",                     L"false",
        L"���-��� ���-��� � ��� �����",       L"5",                     L"false",
        L"������ :-).",                       L"3",                     L"true",
        L"������� :-(...",                    L"3",                     L"true",
        L"���-������� ;-)",                   L"4",                     L"true",
        L"15:21",                             L"1", L"false",
        L"8:00",                              L"1", L"false",
        L"12/07/2009",                        L"1", L"false",
        L"01-���-2009",                       L"1", L"true",
        L"31-���-2012",                       L"1", L"true",
        L"1-���-2000",                        L"1", L"true",
        L"12.07.2009",                        L"1", L"false",
        L"�� ����� 3.1415926",                L"3", L"false",
        L"����������...",                     L"2", L"false",
        L"c=299792458 �/c",                   L"6", L"false", // ??? 4 ???
        //L"���!!!",                            L"2", L"false",
        L"�.�.",                              L"1", L"false",
        //  L"����-���",                          L"1", L"false",
          L"� �.�. � �.�.",                     L"4", L"false",
          //L"����� ���� ���������, ��������� ��� �����!", L"6", L"false",
          L"��� ���-�� � ������� ���������",    L"5", L"false",
          //  L"����-��� ������",                   L"2", L"false",
            L"�.�. ������ - ������� ������� ����", L"5", L"true",
            L"� ������ �.�. - ������� ������� ��������", L"6", L"true",
            L"������� �.�. ������� ����� ����� � ���", L"6", L"true",
            L"�.�. ������� ������� ����� � ���",  L"5", L"true",
            L"��. ��� ��� �����������",           L"3", L"true",
            L"90-� ���� �������� ����",           L"4", L"false",
            L"� 30-� ����� 19-�� ����",           L"5", L"false",
            L"10-� ���������",                    L"2", L"false",
            L"123-� ������",                      L"2", L"false",
            L"34567-�� �������",                  L"2", L"false",
            L"3453-� �������",                    L"2", L"false",
            L"147-� ��������",                   L"2", L"false",
            L"�/� ����",                          L"2", L"false",
            nullptr
    };

    int itok = 0;
    while (tokenizer[itok] != nullptr)
    {
        const wchar_t *stok = tokenizer[itok];
        itok++;

        // http://www.solarix.ru/for_developers/api/morphology-analyzer-api.shtml#sol_Tokenize
        HGREN_STR hStr = sol_TokenizeW(hEngine, stok, RUSSIAN_LANGUAGE);

        int nstr = sol_CountStrings(hStr);
        int required_nstr = _wtoi(tokenizer[itok++]);
        if (nstr != required_nstr)
        {
            failed(hEngine);
        }

        bool space_allowed = wcscmp(tokenizer[itok++], L"true") == 0;

        // � ��������� ������� ���� ����� ���������, ��� ����������� �� ���������
        // ������� ������ ������.
        if (nstr == 1)
        {
            wchar_t tok[60];
            sol_GetStringW(hStr, 0, tok);
            if (!space_allowed && wcschr(tok, L' ') != nullptr)
                failed(hEngine);
        }

        // ��� ��������� ��������� ������ ����� ����.
        Print_StrList(hEngine, hStr);
    }

    // ******** ��������� ���� ���� ����� ********************
    printf("\n");
    hStr = sol_FindStrings(hEngine, L"�����");
    Print_StrList(hEngine, hStr);

    // *********************************************************
    // �������� ��������� �������� ������ ��������� � ���������
    // *********************************************************

    int id1 = sol_SeekWord(hEngine, L"������", false);
    int id2 = sol_SeekWord(hEngine, L"�������", false);
    int id3 = sol_SeekWord(hEngine, L"��������", false);
    int id4 = sol_SeekWord(hEngine, L"���������", false);

    // �������� id � ���������, ��� ���������� ������������� ���������� 
    // � ���������� ����� ������.
    printf("id1=%d id2=%d (must be equal)\n\n", id1, id2);

    if (id1 != id2 || id2 != id3)
        failed(hEngine);

    int id2_1 = sol_SeekWord(hEngine, L"������", false);
    int id2_2 = sol_SeekWord(hEngine, L"������", false);
    if (id2_1 != id2_2)
        failed(hEngine);

    int id3_1 = sol_SeekWord(hEngine, L"����", false);
    int id3_2 = sol_SeekWord(hEngine, L"������", false);
    if (id3_1 != id3_2)
        failed(hEngine);

    // ****************************************************************
    // ����������� ��������� ������ ������������ ���� ����� - � ������
    // ��������� � ������ ��������� ����.
    // ��� ����������� ����� �������� ������ � ������ ������� ������� �
    // ���������!
    // ****************************************************************

    hStr = sol_FindStringsEx(
        hEngine,
        L"��������������",
        true, // ��������� ��������������, ������������ � ��. ��������������� �����
        true, // ��������
        true, // ������������� ���������
        false, // ��� ���������
        false, // ��� ������������� ������
        1     // ����������� 1 ������ �� ���� ��������� 
    );
    if (hStr == nullptr || sol_CountStrings(hStr) < 1)
        failed(hEngine);

    Print_StrList(hEngine, hStr);


    // ***************************************************************
    // ���������� � ����� ����������������, �������� ������ � �� Pro,
    // � ������� �������� ��������.
    // ***************************************************************
    if (eversion > 0)
    {
        int ie00 = sol_FindEntry(hEngine, L"�������������", -1, -1);
        //   int ie00 = sol_FindEntry( hEngine, L"��������", -1, -1 );
        int ie01 = sol_TranslateToNoun(hEngine, ie00);

        if (ie01 == -1 || ie01 == ie00)
        {
            // ���������� �� ���������.
            failed(hEngine);
        }

        sol_GetNounForm(hEngine, ie00, SINGULAR_NUMBER_ru, NOMINATIVE_CASE_ru, buffer);
        sol_GetNounForm(hEngine, ie01, SINGULAR_NUMBER_ru, NOMINATIVE_CASE_ru, buffer2);

        WideCharToMultiByte(CP_OEMCP, 0, buffer, wcslen(buffer) + 1, abuffer, sizeof(abuffer), nullptr, nullptr);
        WideCharToMultiByte(CP_OEMCP, 0, buffer2, wcslen(buffer2) + 1, abuffer2, sizeof(abuffer2), nullptr, nullptr);

        cout << abuffer << " -> " << abuffer2 << "\n\n";


        // ********************************************************
        // ���������� � ����� ����������.
        // ********************************************************
        int ie02 = sol_TranslateToInfinitive(hEngine, ie00);
        if (ie02 == -1 || ie02 == ie00)
        {
            // ���������� �� ���������.
            failed(hEngine);
        }

        sol_GetEntryName(hEngine, ie02, buffer2);

        WideCharToMultiByte(CP_OEMCP, 0, buffer, wcslen(buffer) + 1, abuffer, sizeof(abuffer), nullptr, nullptr);
        WideCharToMultiByte(CP_OEMCP, 0, buffer2, wcslen(buffer2) + 1, abuffer2, sizeof(abuffer2), nullptr, nullptr);

        cout << abuffer << " -> " << abuffer2 << "\n\n";
    }

    TranslateToNoun(hEngine, L"����������");
    TranslateToNoun(hEngine, L"��������");
    TranslateToNoun(hEngine, L"������");
    TranslateToInfinitive(hEngine, L"�����");


    // *******************************************************************
    // �������� ������ ��������� �������� ����� �� �������� - ��� �������
    // ��� �������� ������������ ��������� ����� � ��������� � �������
    // ���������. �������� �������� �� ��������.
    // *******************************************************************
    Test_ProjectWord(hEngine, L"����", false, "==", 2);
    cout << "\n\n";
    Test_ProjectWord(hEngine, L"��������", true, ">", 0);
    cout << "\n\n";
    Test_ProjectWord(hEngine, L"���������", true, ">", 0);
    cout << "\n\n";
    Test_ProjectWord(hEngine, L"�������", true, ">", 0);
    cout << "\n\n";

    // *******************************************************************
    // �������� �������� - ����� ���� � ���������� � ���������.
    // *******************************************************************
    HGREN_INTARRAY hList = sol_ProjectMisspelledWord(hEngine, L"�����", 0, 1);

    if (hList != nullptr)
    {
        int nproj = sol_CountProjections(hList);

        cout << "Number of projections: " << nproj << "\n";

        for (int i = 0; i < nproj; i++)
        {
            const int ientry = sol_GetIEntry(hList, i);
            const int iclass = sol_GetEntryClass(hEngine, ientry);

            sol_GetEntryName(hEngine, ientry, buffer);
            sol_GetClassName(hEngine, iclass, buffer2);

            WideCharToMultiByte(CP_OEMCP, 0, buffer, wcslen(buffer) + 1, abuffer, sizeof(abuffer), nullptr, nullptr);
            WideCharToMultiByte(CP_OEMCP, 0, buffer2, wcslen(buffer2) + 1, abuffer2, sizeof(abuffer2), nullptr, nullptr);
            cout << abuffer2 << ":" << abuffer << "\n";
        }
    }

    sol_DeleteProjections(hList);


    // *****************************************************
    // ������ � ����������
    // *****************************************************
    if (eversion > 0)
    {
        int ieKoshka = sol_FindEntry(hEngine, L"�����", -1, -1);
        if (sol_GetEntryClass(hEngine, ieKoshka) != NOUN_ru)
            failed(hEngine);

        // ������ ��� ��������� ������.
        HGREN_INTARRAY hList2 = sol_SeekThesaurus(hEngine, ieKoshka, true, true, true, true, 1);

        if (hList2 == nullptr)
        {
            failed(hEngine);
        }

        Print_IntList(hEngine, hList2);
        sol_DeleteInts(hList2);

        // 29.07.2008 - ��������� ����������� �������� ������ � ���������� ��� ��������.
        const int ieLezhat = sol_FindEntry(hEngine, L"������", VERB_ru, -1);
        if (ieLezhat == -1)
            failed(hEngine);

        hList2 = sol_SeekThesaurus(hEngine, ieLezhat, true, false, false, false, 0);

        if (hList2 == nullptr)
        {
            failed(hEngine);
        }

        Print_IntList(hEngine, hList2);
        sol_DeleteInts(hList2);


        // ������ ����� �����.
        const int ieName = sol_FindEntry(hEngine, L"���", NOUN_ru, -1);
        if (ieName == -1)
            failed(hEngine);

        hList2 = sol_SeekThesaurus(hEngine, ieName, false, false, false, true, 0);

        if (hList2 == nullptr)
        {
            failed(hEngine);
        }

        Print_IntList(hEngine, hList2);
        sol_DeleteInts(hList2);

        // ---

        TestLink(hEngine, L"�������-�������", NOUN_ru, L"�������", NOUN_ru);
    }


    // �������� ������ �������� (������ � ������ Pro).
    // ���� ������� ������������, �� ������� �������� �� �����.
    // �������� ��������, ��� ��� ����������� �������� ����������, ����� � ����� dictionary.xml
    // ���� ������ ����
    // <stemmer>stemmer&#46;dll</stemmer>
    // �, ����������, ������ � ������� ������� ��������� ������ �������� stemmer.dll � ��� ������ stemmer.dll.xml,
    // ������� ����� ����� �� ������������ ��������� �������.

    if (eversion > 0 && CountLanguages(hEngine) == 1)
    {/*
     stem( hEngine, L"�����" );
     stem( hEngine, L"��������������" );
     stem( hEngine, L"����������������" );
     stem( hEngine, L"����������������������" );
     stem( hEngine, L"��������" );*/
    }

    if (eversion > 0)
    {
        // ������ � ��������������� ������������ �����������.
        VisualizeMorphology(hEngine, L"����� ���-�� ���-�� ����");
        //TestSyntaxAnalysis( hEngine, L"��� ����� �������� �������� �������������� ������� ��������� ����� ��������������� ���������� ��������", RUSSIAN_LANGUAGE, false );
    }

    // ����� ��������� �������� ���������������� � ��������������� ������� ��������� �����������.
    //TestMorphologicalAnalyzer( hEngine, RUSSIAN_LANGUAGE, "morph.txt", true, false, -1 );
    //TestSyntacticAnalyzer( hEngine, RUSSIAN_LANGUAGE, "syntax-ru.txt", true, -1 );

    // ��������� ������������� �����.
    //Test_Threading( hEngine, RUSSIAN_LANGUAGE, "morph.txt", "syntax-ru.txt" );

    return;
}
