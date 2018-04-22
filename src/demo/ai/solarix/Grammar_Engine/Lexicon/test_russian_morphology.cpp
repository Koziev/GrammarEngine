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
// Работа с русским разделом грамматической машины.
//
// 25.07.2008 - добавлен регрессионный тест для синтаксического анализа
// 29.07.2008 - для поиска в тезаурусе по глаголам добавлен тест
// 14.08.2008 - добавлены тесты синтасического анализатора - логические конструкции
// 14.08.2008 - добавлены тесты поиска по базе N-грамм
// 23.08.2008 - добавлены регрессионные тесты для логических конструкций
// 24.08.2008 - добавлен тест с логической конструкцией ЕСЛИ-ТО
// 30.08.2008 - полностью переработан тест синтаксического анализатора
// 05.12.2008 - добавлен тест слогоделителя (sol_Syllabs)
// 05.12.2008 - добавлен тест проекции многолесемных словоформ (типа КОЕ-КТО)
// 23.12.2008 - добавлен тест на проекцию многолексемных словоформ
// 15.01.2009 - добавлено несколько регрессионных тестов токенизатора для
//              предложений в синтаксическом анализаторе русского языка.
// 13.02.2009 - добавлены тесты для SentenceBroker'а и токенизатора.
// 19.02.2009 - добавлены новые тесты синтаксического анализатора для
//              групп связанных существительных.
// 20.02.2009 - добавлено еще несколько тестов токенизатора для работы с 
//              ФИО без пробела между ИО и Фамилией.
// 20.11.2009 - обрабатываемые синтаксическим анализатором предложения
//              печатаются в sentences-ru.txt в кодировке utf8.
// 09.04.2011 - добавлены тесты токенизатора
// 14.01.2012 - добавлены тесты для функций sol_TranslateToNoun и
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
// API грамматической машины
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

    // ATTENTION!!! Слова должны быть в верхнем регистре!!!
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
    // Проверим, что словарь сопровождается корректной версией _sg_api.h
    wchar_t ClassName[64];
    sol_GetClassName(hEngine, NOUN_ru, ClassName);
    if (wcscmp(ClassName, L"СУЩЕСТВИТЕЛЬНОЕ") != 0)
    {
        failed(hEngine);
        return;
    }

    {
        int id1 = sol_FindEntry(hEngine, L"ВКЛЮЧИТЬ", INFINITIVE_ru, -1);
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

    // Проверим работу движка формообразования для неизвестных слово с помощью парадигм.
    // Так как в большинстве сборок словарей парадигмы не сохранены, ошибки фиксировать не будем.
    HFLEXIONS hFlexs = sol_FindFlexionHandlers(hEngine, L"Хрюндель", 0);
    if (hFlexs != nullptr)
    {
        // Столько парадигм подходит для данного слова
        const int npar = sol_CountParadigmasInFlexionHandlers(hEngine, hFlexs);

        wchar_t ParadigmaName[64];
        for (int i = 0; i < npar; i++)
        {
            int rc = sol_GetParadigmaInFlexionHandlers(hEngine, hFlexs, i, ParadigmaName);
            wide(L"Best suitable paradigma: "); wide(ParadigmaName); wide(L"\n");


            HFLEXIONTABLE hFlex = sol_BuildFlexionHandler(hEngine, hFlexs, ParadigmaName, -1);
            if (hFlex != nullptr)
            {
                const wchar_t *wf = sol_GetFlexionHandlerWordform(hEngine, hFlex, L"ПАДЕЖ:ТВОР ЧИСЛО:ЕД");
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

    // Условный номер варианта движка. 0 - Lite, 1 - Pro, 2 - Premium (только для поискового движка)
    const int eversion = sol_GetVersion(hEngine, nullptr, nullptr, nullptr);


    // Функция восстановления регистра слова.
    int id_entry0 = sol_FindEntry8(hEngine, "\xD0\x9F\xD0\x9B\xD0\x9E\xD0\xA5\xD0\x9E\xD0\x99", -1, -1);
    wchar_t word_rest[32] = L"ПЛОХАЯ";
    int rest_rc = sol_RestoreCasing(hEngine, word_rest, id_entry0);

    // Проверим graceful cancellation парсинга по истечении заданного максимального времени.
    // Для этого подадим на вход сложное предложение, которое в обычных условиях анализируется более минуты, и
    // установим таймаут в 5 секунд. Примерно по истечении 5-6 секунд функция sol_SyntaxAnalysis вернет управление.
    HGREN_RESPACK hPack0 = sol_SyntaxAnalysis(hEngine, L"Белая лохматая собака бравого молодого капитана большого старого корабля, обогнувшего несколько раз земной шар", 0, 0, 5000, RUSSIAN_LANGUAGE);
    sol_DeleteResPack(hPack0);

    int ie1 = sol_FindEntry(hEngine, L"МАМА", /*Solarix::API::*/NOUN_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);
    // Должен быть женский род
    if (sol_GetNounGender(hEngine, ie1) != FEMININE_GENDER_ru)
        failed(hEngine);

    // Должно быть существительное
    if (sol_GetEntryClass(hEngine, ie1) != NOUN_ru)
        failed(hEngine);

    // Склоняем существительное - получаем форму для множественного числа дательного падежа
    wchar_t Buffer[64];
    if (sol_GetNounForm(hEngine, ie1,
        PLURAL_NUMBER_ru, // множественное число
        DATIVE_CASE_ru, // дательный падеж
        Buffer) != 0)
        failed(hEngine);

    if (!!wcscmp(Buffer, L"МАМАМ"))
        failed(hEngine);

    if (eversion > 0)
    {
        // Тест слогоделителя.
        // Массив содержит пары СЛОВО-ЭТАЛОННОЕ_РАЗБИЕНИЕ_НА_СЛОГИ
        const wchar_t* Word0[] =
        {
         L"кошка", L"кош+ка",
         L"МЫШЬ", L"МЫШЬ",
         L"КОТЁНОК", L"КО+ТЁ+НОК",
         L"МОНСТР", L"МОНСТР",
         L"МОНСТРОВЫЙ", L"МОНСТ+РО+ВЫЙ",
         L"ГАЛАКТИКА", L"ГА+ЛАК+ТИ+КА",
         L"МЕТАГАЛАКТИЧЕСКИМИ", L"МЕ+ТА+ГА+ЛАК+ТИ+ЧЕС+КИ+МИ",
         L"КОРШУНЫ", L"КОР+ШУ+НЫ",
         L"АУРА", L"А+У+РА",
         L"КОЛОКОЛА", L"КО+ЛО+КО+ЛА",
         L"КОЛОКОЛЬНЯ", L"КО+ЛО+КОЛЬ+НЯ",
         L"СПИТ", L"СПИТ",
         L"СПИТЕ", L"СПИ+ТЕ",
         L"СПОЁМТЕ", L"СПО+ЁМ+ТЕ",
         L"ПОЙТЕ", L"ПОЙ+ТЕ",
         L"СТОЙТЕ", L"СТОЙ+ТЕ",
         L"РЕВАЛЬВАЦИОННЫЕ", L"РЕ+ВАЛЬ+ВА+ЦИ+ОН+НЫ+Е",
         L"ПРЕСТИЖ", L"ПРЕС+ТИЖ",
         L"РЕВАЛЬВИРУЙСЯ", L"РЕ+ВАЛЬ+ВИ+РУЙ+СЯ",
         L"ПОЛЬЗИТЕЛЬНОЕ", L"ПОЛЬ+ЗИ+ТЕЛЬ+НО+Е",
         L"КАСТОДИАЛЬНАЯ", L"КАС+ТО+ДИ+АЛЬ+НА+Я",
         L"ЗУБ", L"ЗУБ",
         L"ОМОН", L"О+МОН",
         L"РА", L"РА",
         L"ЩИ", L"ЩИ",
         L"ЩАВЕЛЬ", L"ЩА+ВЕЛЬ",
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
     // Проверка на действия токенизатора при получении некорректного предложения, которое порождает слишком сложный
     // граф токенизации. Внутри токенизатора должен сработать триггер на число развилок в графе и сгененироваться исключение.
     const wchar_t tst1[] = L"А\"        полковник      ЧЕРНЫШЕВ Н. Г. Генерал-лейтенант"
                            L"      МАЛАНДИН Г. К. Полковник,      с 19.9.44 г.      генерал-майор      ВОРОНОВ Н Ф. 18-я"
                            L"      (по 4.8.44 г.) Генерал-лейтенант      ЖУРАВЛЕВ Е. П Генерал-майор      КОЛОНИН С. Е.,"
                            L"        Генерал-майор      НОВИКОВ С. М. Генерал-лейтенант      ОЗЕРОВ Ф. П. Полковник"
                            L"      БРЕЖНЕВ Л. И. 38-я Генерал-полковник      МОСКАЛЕНКО К. С. Генерал-майор      ЕПИШЕВ А. А.,"
                            L"        полковник,      с 28.7 44 г.      генерал-майор      ОЛЕЙНИК Ф. И. Генерал-майор"
                            L"      ВОРОБЬЕВ В. Ф. Генерал-майор      ОРТЕНБЕРГ Д И. 60-я Генерал-полковник      КУРОЧКИН П. Л Полковник,      с 28.7 44 г.      генерал-майор и/с      РОДИОНОВ В. И.,        генерал-майор      ОЛЕНИН В. М. Генерал-майор      ТЕР-ГАСПАРЯН Г. А.,        с 23.7.44 г.      полковник      ПРОТАС С. М.,        с 23.8.44 г.      генерал-майор      ГОНЧАРОВ А. Д Генерал-майор      ИСАЕВ К. П.,        с 11.8.44г.      полковник      ГРИШАЕВ И М.      (с 19.9 44 г. генерал-майор) 1-я гвардейская танковая      (по 6.9 .4";
     HGREN_STR htok1 = sol_TokenizeW( hEngine, tst1, RUSSIAN_LANGUAGE );
     // ----------------------
    */


    // Прокция многолексемных и всяких 'хитрых' слов
    const wchar_t *words[] =
    {
     L"Ящичек", L"*",
     L"Бабой-Ягой", L"*",
     L"СИКОСЬ-НАКОСЬ", L"@",
     L"Кое-кому", L"@",
     L"по-русски", L"@",
     L"Кое - чем", L"@",
     L"Абы  как", L"@",
     L"мЁдОм", L"*",
     L"молодо- Зелено", L"@",
     L"Сначала", L"@",
     L"бОлЕе", L"@",
     L"БЛИЗКО", L"@",
     L"БЛИЖЕ", L"@",
     L"поближе", L"@",
     L"ВО ВСЕУСЛЫШАНИЕ", L"@",
     L"Во много раз", L"@",
     L"ДАВНЫМ-ДАВНО", L"@",
     L"ЕЛЕ-ЕЛЕ", L"@",
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


    // Приведение слова к базовой форме.
    wchar_t Word[64] = L"КОШКОЮ";
    int changed = sol_TranslateToBase(hEngine, Word, 0);
    if (changed != 1 || !!wcscmp(Word, L"кошка"))
        failed(hEngine);

    wcscpy(Word, L"Аргентиной");
    changed = sol_TranslateToBase(hEngine, Word, 0);
    if (changed != 1 || !!wcscmp(Word, L"Аргентина"))
        failed(hEngine);


    // Еще одна процедура приведения к базовой форме, возвращающая
    // все варианты. Для слова ДОМА получаем 2 базовые формы:
    // сущ. ДОМ и наречие ДОМА
    wcscpy(Word, L"ДОМА");
    HGREN_STR hStr = sol_TranslateToBases(hEngine, Word, 0);
    if (eversion > 0)
    {
        if (sol_CountStrings(hStr) != 2)
            failed(hEngine);
    }

    Print_StrList(hEngine, hStr);


    wcscpy(Word, L"ООО");
    hStr = sol_TranslateToBases(hEngine, Word, 1);
    Print_StrList(hEngine, hStr);



    if (eversion == 0)
        // Дальше все тесты - для версий Pro и Premium
        return;


    // Пример работы функции ГМ для поиска словарной статьи и получения нужной
    // грамматической формы слова.
    // http://www.solarix.ru/api/ru/sol_FindEntry.shtml
    // Сначала отыскиваем словарную статью.
    int iv = sol_FindEntry(hEngine, L"СПАТЬ", /*Solarix::API::*/VERB_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);
    if (iv == -1)
        failed(hEngine);

    // http://www.solarix.ru/api/ru/sol_GetEntryClass.shtml
    if (sol_GetEntryClass(hEngine, iv) != VERB_ru)
        failed(hEngine);

    // Теперь просим ГМ сформировать словоформу с нужными грамматическими признаками.
    wchar_t b[64] = L"";
    if (sol_GetVerbForm(
        hEngine,
        iv,
        /*Solarix::API::*/SINGULAR_NUMBER_ru, // единственное число
        /*Solarix::API::*/FEMININE_GENDER_ru, // женский род
        /*Solarix::API::*/PAST_ru, // прошедшее время
        /*Solarix::API::*/PERSON_3_ru, // 3е лицо
        b
    ) != 0)
        failed(hEngine);

    // Множественно число, женский род, прошедшее время, 3е лицо
    if (!!wcscmp(b, L"СПАЛА"))
        failed(hEngine);

    int iadj = sol_FindEntry(hEngine, L"белый", /*Solarix::API::*/ADJ_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);
    int inoun = sol_FindEntry(hEngine, L"кошка", /*Solarix::API::*/NOUN_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);
    int iverb = sol_FindEntry(hEngine, L"спать", /*Solarix::API::*/VERB_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);

    if (iadj == -1 || inoun == -1 || iverb == -1)
        failed(hEngine);

    // Проверим процедуру склонения прилагательного
    if (sol_GetAdjectiveForm(hEngine, iadj,
        SINGULAR_NUMBER_ru, // единственное число
        NEUTRAL_GENDER_ru, // средний род
        GENITIVE_CASE_ru, // родительный падеж
        ANIMATIVE_FORM_ru, // одушевленное
        0, // некраткая форма
        SUPERLATIVE_FORM_ru, // превосходная степень
        b) != 0)
        failed(hEngine);

    if (!!wcscmp(b, L"БЕЛЕЙШЕГО"))
        failed(hEngine);


    int res = 0;

    // Проверим процедуру согласования существительного и глагола с числом.
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

    // в винительном падеже
    for (int i = 0; i < 20; i++)
    {
        const int v = i < 12 ? i : (i == 12 ? 21 : 101 * i);

        wide(L"Вижу ");
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
    // еще склонение прилагательного
    // ********************************

    iadj = sol_FindEntry(hEngine, L"светлый", /*Solarix::API::*/ADJ_ru, /*Solarix::API::*/RUSSIAN_LANGUAGE);

    sol_GetAdjectiveForm(hEngine, iadj, SINGULAR_NUMBER_ru, MASCULINE_GENDER_ru, ACCUSATIVE_CASE_ru, INANIMATIVE_FORM_ru, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"СВЕТЛЫЙ") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, SINGULAR_NUMBER_ru, MASCULINE_GENDER_ru, ACCUSATIVE_CASE_ru, ANIMATIVE_FORM_ru, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"СВЕТЛОГО") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, SINGULAR_NUMBER_ru, FEMININE_GENDER_ru, ACCUSATIVE_CASE_ru, -1, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"СВЕТЛУЮ") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, SINGULAR_NUMBER_ru, NEUTRAL_GENDER_ru, ACCUSATIVE_CASE_ru, -1, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"СВЕТЛОЕ") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, PLURAL_NUMBER_ru, -1, ACCUSATIVE_CASE_ru, INANIMATIVE_FORM_ru, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"СВЕТЛЫЕ") != 0) failed(hEngine);

    sol_GetAdjectiveForm(hEngine, iadj, PLURAL_NUMBER_ru, -1, ACCUSATIVE_CASE_ru, ANIMATIVE_FORM_ru, 0, ATTRIBUTIVE_FORM_ru, buffer);
    if (wcscmp(buffer, L"СВЕТЛЫХ") != 0) failed(hEngine);



    // Проверяем проекцию слова на Словарь
    int ientry = -1, iform = -1, iclass = -1;
    int nproj = sol_FindWord(hEngine, L"мышь", &ientry, &iform, &iclass);
    if (nproj < 1)
        failed(hEngine);


    // Грамматический класс слова возвращен в переменной iclass (константы для 
    // обозначения индексов классов см. в файле sg_api.h).
    if (iclass != NOUN_ru)
        failed(hEngine);


    printf("\n\n");

    // Пример того, как можно отличить причастия от прилагательных.
    const wchar_t* adjs[4] = { L"текущими", L"текучее", L"мыт", L"красив" };
    for (int i = 0; i < 4; ++i)
    {
        int id_entry = -1, iform = -1, iclass = -1;
        int nproj = sol_FindWord(hEngine, adjs[i], &id_entry, &iform, &iclass);

        // Нам надо найти в словарной статье значение грамматического признака с ID=PARTICIPLE_ru
        // http://www.solarix.ru/api/ru/sol_GetEntryCoordState.shtml
        int id_state = sol_GetEntryCoordState(hEngine, id_entry, PARTICIPLE_ru);
        if (id_state == 1)
        {
            // значение 1 - причастие
            wide(adjs[i]);
            printf(" is an adjectival participle; ");

            // определим глагольные признаки - вид, время, залог
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
            // значение 0 - прилагательное
            wide(adjs[i]);
            printf(" is an adjective\n");
        }
    }




    // ************************************************************************************
    // Тесты для модуля сегментатора текста.
    // Подробнее о сегментаторе http://www.solarix.ru/for_developers/docs/tokenizer.shtml
    // ************************************************************************************

    // Проверяем, что пустая строка является терминатором предложений.
    const wchar_t text_with_empty_line[] = L"первое предложение\n\nвторое \n предложение \n\n третье предложение.";
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
                    // Текст полностью разобран.
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
     L"Штатов.",
     L"Экономическая мощь Штатов.",
     L"Экономическая сила Штатов.",
     L"Экономическое могущество США.",
     L"Обеспечить работу институтов.",
     L"Обеспечить функционирование институтов.",
     L"Кто шагает дружно в ряд?",
     L"А.С. Пушкин - великий русский поэт.",
     L"И т.д.",
     L"Кошка, собака и т.д.",
     L"Коршун, воробей, пр. птички!",
     L"Число пи равно 3.1415926!",
     L"Ша!",
     L"Смеркалось...",
     L"Единица=1?",
     L"Пионерский наш отряд!",
     L"И что?!",
     L"А вот!!!",
     L"Не знают...",
     L"И пр. мысли.",
     L"А Пушкин А.С. - великий русский писатель.",
     L"Толстой Л.Н. написал роман Война и Мир.",
     L"Л.Н. Толстой написал Войну и Мир.",
     L"Дж. Буш был президентом.",
     L"Ф.М.Достоевский - известнейший писатель периода махрового царизма.",
     L"Р.Кеннеди был застрелен в Далласе.",
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

    // Разбиваем текст в оперативной памяти. В API есть также процедура для чтения
    // предложений из дисковых файлов, причем понимаются самые разные форматы - фактически
    // любые, поддерживаемые поисковым движком.
    HGREN_SBROKER hBroker = sol_CreateSentenceBrokerMemW(hEngine, slist2.c_str(), RUSSIAN_LANGUAGE);

    if (!hBroker)
        failed(hEngine);

    isent = 0;
    while (true)
    {
        int rc = sol_FetchSentence(hBroker);
        if (rc == -1)
        {
            // Текст полностью разобран.
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



    // Проверим поведение брокера для случая, когда строка в памяти не оканчивается
    // нормальным разделителем предложений.
    const wchar_t rusent[] = L"кошка и собака слядко спят на мягком диване";
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
            // Текст полностью разобран.
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


    // ----------- регрессионный тест для исправленного бага
    const wchar_t rusent2[] = L"Трансмаш  и др.                     ";
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


    // ---------------------- ЗАКОНЧИЛИ ТЕСТЫ СЕГМЕНТАТОРА ПРЕДЛОЖЕНИЙ ----------------------------


    // -------------------- ТЕСТЫ ТОКЕНИЗАТОРА ---------------------
    //
    // Подробнее о токенизаторе http://www.solarix.ru/for_developers/docs/tokenizer.shtml

    const wchar_t *tokenizer[] =
    {
        /* ----- предложение -------   --число лексем--  --допустимы ли пробелы внутри лексем--  */
        L"...",                               L"1",                     L"false",
        L"20:23:01",                          L"1",                     L"false",
        L"„одно слово?“",                     L"5",                     L"false",
        L"«человек-паук»",                    L"5",                     L"false",
        L"\"много слов\"",                    L"4",                     L"false",
        L"«!»",                               L"3",                     L"false",
        L"“одно слово?”",                     L"5",                     L"false",
        L"Да. Хотя.",                         L"4",                     L"false",
        L"Кое-кто кое-где у нас порой",       L"5",                     L"false",
        L"Смешно :-).",                       L"3",                     L"true",
        L"Грустно :-(...",                    L"3",                     L"true",
        L"Кот-хитрюга ;-)",                   L"4",                     L"true",
        L"15:21",                             L"1", L"false",
        L"8:00",                              L"1", L"false",
        L"12/07/2009",                        L"1", L"false",
        L"01-янв-2009",                       L"1", L"true",
        L"31-ДЕК-2012",                       L"1", L"true",
        L"1-Апр-2000",                        L"1", L"true",
        L"12.07.2009",                        L"1", L"false",
        L"Пи равно 3.1415926",                L"3", L"false",
        L"Смеркалось...",                     L"2", L"false",
        L"c=299792458 м/c",                   L"6", L"false", // ??? 4 ???
        //L"Вот!!!",                            L"2", L"false",
        L"т.д.",                              L"1", L"false",
        //  L"баба-яга",                          L"1", L"false",
          L"И т.д. и т.п.",                     L"4", L"false",
          //L"Кошка спит постольку, поскольку она поела!", L"6", L"false",
          L"Вот кто-то с горочки спустился",    L"5", L"false",
          //  L"Баба-яга против",                   L"2", L"false",
            L"А.С. Пушкин - великий русский поэт", L"5", L"true",
            L"А Пушкин А.С. - великий русский писатель", L"6", L"true",
            L"Толстой Л.Н. написал роман Война и Мир", L"6", L"true",
            L"Л.Н. Толстой написал Войну и Мир",  L"5", L"true",
            L"Дж. Буш был президентом",           L"3", L"true",
            L"90-е годы прошлого века",           L"4", L"false",
            L"В 30-х годах 19-го века",           L"5", L"false",
            L"10-я пятилетка",                    L"2", L"false",
            L"123-я статья",                      L"2", L"false",
            L"34567-ти поросят",                  L"2", L"false",
            L"3453-х поросят",                    L"2", L"false",
            L"147-й поросёнок",                   L"2", L"false",
            L"б/у вещь",                          L"2", L"false",
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

        // В некоторых случаях надо особо проверить, что токенизатор не добавляет
        // пробелы внутрь лексем.
        if (nstr == 1)
        {
            wchar_t tok[60];
            sol_GetStringW(hStr, 0, tok);
            if (!space_allowed && wcschr(tok, L' ') != nullptr)
                failed(hEngine);
        }

        // Эта процедура освободит список строк сама.
        Print_StrList(hEngine, hStr);
    }

    // ******** ПОЛУЧЕНИЕ ВСЕХ ФОРМ СЛОВА ********************
    printf("\n");
    hStr = sol_FindStrings(hEngine, L"кошка");
    Print_StrList(hEngine, hStr);

    // *********************************************************
    // Проверим процедуру быстрого поиска словоформ в лексиконе
    // *********************************************************

    int id1 = sol_SeekWord(hEngine, L"КОРОВА", false);
    int id2 = sol_SeekWord(hEngine, L"КОРОВОЙ", false);
    int id3 = sol_SeekWord(hEngine, L"КОРОВАМИ", false);
    int id4 = sol_SeekWord(hEngine, L"ГАЛАКТИКА", false);

    // Сравните id и убедитесь, что словоформы действительно приводятся 
    // к одинаковым целым числам.
    printf("id1=%d id2=%d (must be equal)\n\n", id1, id2);

    if (id1 != id2 || id2 != id3)
        failed(hEngine);

    int id2_1 = sol_SeekWord(hEngine, L"ЯЩИЧЕК", false);
    int id2_2 = sol_SeekWord(hEngine, L"ЯЩИЧКА", false);
    if (id2_1 != id2_2)
        failed(hEngine);

    int id3_1 = sol_SeekWord(hEngine, L"ЯЩИК", false);
    int id3_2 = sol_SeekWord(hEngine, L"ЯЩИКОМ", false);
    if (id3_1 != id3_2)
        failed(hEngine);

    // ****************************************************************
    // Расширенная процедура поиска всевозможных форм слова - с учетом
    // синонимов и прочих связанных форм.
    // Эти возможности будут работать только с полной версией словаря и
    // тезауруса!
    // ****************************************************************

    hStr = sol_FindStringsEx(
        hEngine,
        L"СУПЕРГАЛАКТИКА",
        true, // разрешаем уменьшительные, усилительные и пр. морфологические формы
        true, // синонимы
        true, // грамматически связанные
        false, // без переводов
        false, // без семантических связей
        1     // допускается 1 прыжок по сети тезауруса 
    );
    if (hStr == nullptr || sol_CountStrings(hStr) < 1)
        failed(hEngine);

    Print_StrList(hEngine, hStr);


    // ***************************************************************
    // Приведение к форме существительного, работает только с ГМ Pro,
    // в которой доступен тезаурус.
    // ***************************************************************
    if (eversion > 0)
    {
        int ie00 = sol_FindEntry(hEngine, L"ХРОМИРОВАННЫЙ", -1, -1);
        //   int ie00 = sol_FindEntry( hEngine, L"КОФЕЙНЫЙ", -1, -1 );
        int ie01 = sol_TranslateToNoun(hEngine, ie00);

        if (ie01 == -1 || ie01 == ie00)
        {
            // приведение не выполнено.
            failed(hEngine);
        }

        sol_GetNounForm(hEngine, ie00, SINGULAR_NUMBER_ru, NOMINATIVE_CASE_ru, buffer);
        sol_GetNounForm(hEngine, ie01, SINGULAR_NUMBER_ru, NOMINATIVE_CASE_ru, buffer2);

        WideCharToMultiByte(CP_OEMCP, 0, buffer, wcslen(buffer) + 1, abuffer, sizeof(abuffer), nullptr, nullptr);
        WideCharToMultiByte(CP_OEMCP, 0, buffer2, wcslen(buffer2) + 1, abuffer2, sizeof(abuffer2), nullptr, nullptr);

        cout << abuffer << " -> " << abuffer2 << "\n\n";


        // ********************************************************
        // Приведение к форме инфинитива.
        // ********************************************************
        int ie02 = sol_TranslateToInfinitive(hEngine, ie00);
        if (ie02 == -1 || ie02 == ie00)
        {
            // приведение не выполнено.
            failed(hEngine);
        }

        sol_GetEntryName(hEngine, ie02, buffer2);

        WideCharToMultiByte(CP_OEMCP, 0, buffer, wcslen(buffer) + 1, abuffer, sizeof(abuffer), nullptr, nullptr);
        WideCharToMultiByte(CP_OEMCP, 0, buffer2, wcslen(buffer2) + 1, abuffer2, sizeof(abuffer2), nullptr, nullptr);

        cout << abuffer << " -> " << abuffer2 << "\n\n";
    }

    TranslateToNoun(hEngine, L"ЧАЕВНИЧАТЬ");
    TranslateToNoun(hEngine, L"КОФЕЙНЫЙ");
    TranslateToNoun(hEngine, L"ИСКАТЬ");
    TranslateToInfinitive(hEngine, L"ПОИСК");


    // *******************************************************************
    // Проверим работу процедуры проекции слова на лексикон - она находит
    // все варианты соответствия заданного слова и имеющихся в словаре
    // словоформ. Обратите внимание на омонимию.
    // *******************************************************************
    Test_ProjectWord(hEngine, L"ПИЛА", false, "==", 2);
    cout << "\n\n";
    Test_ProjectWord(hEngine, L"СТОМАЗИЛ", true, ">", 0);
    cout << "\n\n";
    Test_ProjectWord(hEngine, L"БАРМАГЛОТ", true, ">", 0);
    cout << "\n\n";
    Test_ProjectWord(hEngine, L"ЗЮЗИКОМ", true, ">", 0);
    cout << "\n\n";

    // *******************************************************************
    // Нечеткая проекция - поиск слов с опечатками в лексиконе.
    // *******************************************************************
    HGREN_INTARRAY hList = sol_ProjectMisspelledWord(hEngine, L"КОЩКА", 0, 1);

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
    // Работа с тезаурусом
    // *****************************************************
    if (eversion > 0)
    {
        int ieKoshka = sol_FindEntry(hEngine, L"КОШКА", -1, -1);
        if (sol_GetEntryClass(hEngine, ieKoshka) != NOUN_ru)
            failed(hEngine);

        // Найдем все связанные статьи.
        HGREN_INTARRAY hList2 = sol_SeekThesaurus(hEngine, ieKoshka, true, true, true, true, 1);

        if (hList2 == nullptr)
        {
            failed(hEngine);
        }

        Print_IntList(hEngine, hList2);
        sol_DeleteInts(hList2);

        // 29.07.2008 - проверяем усложненный алгоритм работы с тезаурусом для глаголов.
        const int ieLezhat = sol_FindEntry(hEngine, L"ЛЕЖАТЬ", VERB_ru, -1);
        if (ieLezhat == -1)
            failed(hEngine);

        hList2 = sol_SeekThesaurus(hEngine, ieLezhat, true, false, false, false, 0);

        if (hList2 == nullptr)
        {
            failed(hEngine);
        }

        Print_IntList(hEngine, hList2);
        sol_DeleteInts(hList2);


        // Найдем имена людей.
        const int ieName = sol_FindEntry(hEngine, L"ИМЯ", NOUN_ru, -1);
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

        TestLink(hEngine, L"Премьер-министр", NOUN_ru, L"ПРЕМЬЕР", NOUN_ru);
    }


    // Проверим работу стеммера (только в версии Pro).
    // Если словарь многоязычный, то стеммер работать не будет.
    // Обратите внимание, что для подключения стеммера необходимо, чтобы в файле dictionary.xml
    // была запись типа
    // <stemmer>stemmer&#46;dll</stemmer>
    // и, разумеется, вместе с файлами словаря находился модуль стеммера stemmer.dll и его конфиг stemmer.dll.xml,
    // которые можно взять из дистрибутива поисковой системы.

    if (eversion > 0 && CountLanguages(hEngine) == 1)
    {/*
     stem( hEngine, L"файлы" );
     stem( hEngine, L"ГалактическимИ" );
     stem( hEngine, L"Александровичами" );
     stem( hEngine, L"дезоксирибонуклеиновые" );
     stem( hEngine, L"паллером" );*/
    }

    if (eversion > 0)
    {
        // Работа с морфологическим анализатором предложений.
        VisualizeMorphology(hEngine, L"Кошка что-то где-то ищет");
        //TestSyntaxAnalysis( hEngine, L"Под катом описание процесса разрисовывания обычной комнатной двери флуоресцентными акриловыми красками", RUSSIAN_LANGUAGE, false );
    }

    // Далее запускаем проверку морфологического и синтаксического разбора эталонных предложений.
    //TestMorphologicalAnalyzer( hEngine, RUSSIAN_LANGUAGE, "morph.txt", true, false, -1 );
    //TestSyntacticAnalyzer( hEngine, RUSSIAN_LANGUAGE, "syntax-ru.txt", true, -1 );

    // Различные многопоточные тесты.
    //Test_Threading( hEngine, RUSSIAN_LANGUAGE, "morph.txt", "syntax-ru.txt" );

    return;
}
