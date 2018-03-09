// -----------------------------------------------------------------------------
// File GRAMMAR_ENGINE_API.CPP
//
// (c) by Koziev Elijah www.wordysoft.com all rights reserved 
//
// Help: http://www.solarix.ru/for_developers/api/grammar-engine-api.shtml
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
//
// This file contains some basic API functions which can be used by other 
// programs under Win32 to perform operations with words and sentences (analysis
// and synthesys).
//
// API ��� ������� � ��������������� ������ � ���� ������� DLL Win32. �������
// ������������ ��� ���������� �������� �� ������� � �������������.
//
// �������� API: http://www.solarix.ru/for_developers/api/grammar-engine-api.shtml
//
//
// 24.05.2007 - ��������� sol_TranslateToBases.
//
// 19.06.2007 - ��������� ������������� ������������ �������� ��������
//              � sol_Stemmer.
//
// 17.09.2007 - ���������� ������ � sol_GetAdjectiveForm � ������������
//              �������������� ����������.
//
// 30.09.2007 - ��������� sol_SeekThesaurus ��� ������ � ����������.
// 01.10.2007 - ��������� sol_ProjectMisspelledWord ��� �������� ��������.
// 06.12.2007 - �������� API ���������� ����, ���������� �������� GM_PHRASE_GENERATOR
// 30.06.2008 - �������� API OCR
// 11.07.2008 - ��������� ���� ����� Allow_Dynforms � sol_SyntaxAnalysis, � ���
//              �� ��������� �������� �������� Allow_Unknown
// 17.07.2008 - ������� API call convention �� stdcall
// 17.07.2008 - �������� ��������� sol_GeneratePhrase2, ��� ���������� �����
//              ��������, ���������� � �����.
// 25.07.2008 - ��������� sol_FindClass, sol_FindEnum, sol_FindEnumState, sol_EnumInClass
// 27.07.2008 - ��������� sol_SeekNGrams
// 29.07.2008 - � ��������� sol_SeekThesaurus ����� ������� ��� �������� �������
//              �� ���� ���������������� ������������ ������� ���������� ������
//              � ���������� �� � ������� ������ 
// 29.07.2008 - ��������� �������� ������ sol_SeekThesaurus ��� ��������, ������
//              �� ������������� ������ ����� ����� ��� ����������.
// 01.08.2008 - ��������� ��� ������������� �������� � sol_LoadDictionary...,
//              ��� ������������ bool'� ���������� �� int'�
// 02.08.2008 - ��� sol_SeekThesaurus ��������� � LexiconAutomat, �����
//              ��� ��������������� ������ �������� ��������� ������ � �
//              ��������� �������.
// 20.11.2008 - ��������� sol_MatchNGrams
// 02.12.2008 - ��������� sol_Syllabs - �������� ����� �� �����
// 14.02.2009 - ��������� API ������������ � SentenceBroker'�
// 25.02.2009 - ��������� sol_PreloadNGramsCaches
// 11.03.2009 - ��������� sol_FindLanguage � sol_HasLanguage
// 08.04.2009 - �� API ������� sol_PreloadCaches
// 20.07.2009 - ����������� API ������� � ���� N-�����: ������ sol_SeekNGrams,
//              ��������� sol_Seek2Grams, sol_Seek3Grams, sol_Seek4Grams,
//              sol_Seek5Grams
// 31.07.2010 - ��������� sol_ProcessPhraseEntry
// 06.08.2010 - ��������� sol_GetPhraseLanguage � sol_GetPhraseClass
// 21.08.2010 - ��������� sol_SetLinkFlags
// 29.08.2010 - ��������� sol_AddWord
// 04.09.2010 - � ��� ������� �������� ��������� ���������� ������������ ������
//              � ����������, ���������� ������� ������������ ����� sol_GetError.
// 29.09.2010 - ��������� sol_SyntaxAnalysis8, sol_MorphologyAnalysis8,
//              sol_LoadDictionary8, sol_CreateGrammarEngine8
// 23.12.2010 - ��������� utf8-������ ������� sol_Seek?Grams
// 27.03.2011 - ��������� critical section ��� Errors API
// 03.04.2011 - � ������ ProjectWord �������� �������� - ID �������� �����,
//              ��� ��� ������ ������� �������� ����� ���� ��������� � �����.
// 19.04.2011 - ������� sol_ListLinksTxt � sol_ListEntries � ����-������ ���������
// 22.06.2011 - ��������� sol_GetLeafLinkType
// 21.08.2011 - ��������� sol_ListPartsOfSpeech
// 26.09.2011 - ��������� � ��������� ������� sol_MorphologyAnalysis � 
//              sol_SyntaxAnalysis, ��-������� �������� ����������� �����.
// 27.09.2011 - �������� ����� ������� �������� ���������.
// 09.01.2012 - ����������� sol_Syllabs � ����� � ���������� ������������ ������,
//              � ��������� � ��������� �������� �������� LanguageID.
// 29.06.2012 - �� API ������ ������, ��������� � ���������.
// 28.07.2012 - �������� ���� SOL_GREN_ENABLE_RECONSTRUCTION ��� sol_MorphologyAnalysis
//              � sol_SyntaxAnalysis, ���������� ������������� �������.
// 07.01.2013 - � sol_MorphologyAnalysis � sol_SyntaxAnalysis ��������� ����������
//              ��������������� ������������� ������� ����� (���� SOL_GREN_MODEL)
// 12.02.2013 - � sol_MorphologyAnalysis � sol_SyntaxAnalysis �������� ���������
//              ��������� �������� - ������ ������� 10 ����� ������ ������������
//              ����� ����������� ��� ���������� ������� �������������� �����, �
//              ������� 22 ���� - ����. ������� � �������������.
// 28.03.2016 - ��������� ��������� ���������� ������� ���������� ��������������
//              � ���������� �����.
// -----------------------------------------------------------------------------
//
// CD->29.04.2007
// LC->13.09.2017
// --------------

#include <lem/config.h>

#if defined DLL_EXPORTS

#include <boost/bind.hpp>
#include <lem/startup.h>
#include <lem/xml_parser.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/version.h>
#include <lem/solarix/tree_node.h>
#include <lem/solarix/sentencebroker.h>
#include <lem/system_config.h>
#include <lem/solarix/sg_only_main_translations_tagfilter.h>
#include <lem/solarix/sg_tag_or_null_tagfilter.h>
#include <lem/solarix/print_variator.h>
#include <lem/solarix/ThesaurusNotesProcessor.h>
#include <lem/solarix/ThesaurusTagDefs.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/WordLinkEnumerator.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/PhraseEnumerator.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/ClassEnumerator.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/TransactionGuard.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/dsa_main.h>
#include <lem/solarix/casing_coder.h>
#include <lem/logfile.h>
#include <lem/sqlite_helpers.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/solarix_grammar_engine.h>
#include "GrammarEngineHolder.h"

#define HFLEXIONTABLE void*
#define HFLEXIONS void*


#if defined LEM_THREADING
#define CATCH_API(hengine) \
 catch( const lem::E_BaseException &x ) \
 { \
  lem::Process::CritSecLocker locker( & HandleEngine(hengine)->cs_error ); \
  HandleEngine(hengine)->error = x.what(); \
 } \
 catch( const std::exception &y ) \
 { \
  lem::Process::CritSecLocker locker( & HandleEngine(hengine)->cs_error ); \
  HandleEngine(hengine)->error = lem::to_unicode(y.what()); \
 } \
 catch(...) \
 { \
  lem::Process::CritSecLocker locker( & HandleEngine(hengine)->cs_error ); \
  HandleEngine(hengine)->error = L"Error"; \
 }
#else
#define CATCH_API(hengine) \
 catch( const lem::E_BaseException &x ) \
 { \
  HandleEngine(hengine)->error = x.what(); \
 } \
 catch( const std::exception &y ) \
 { \
  HandleEngine(hengine)->error = lem::to_unicode(y.what()); \
 } \
 catch(...) \
 { \
  HandleEngine(hengine)->error = L"Unhandled exception"; \
 }
#endif


// ����������� ��� ��������������� ������ - ���������� ��� ��� ������ ��������� ������ �������.
// ��� ������������� �����������, � ������������ ������ ��� ���������� ���.
#if defined SOLARIX_DEMO && defined LEM_THREADS
#define DEMO_SINGLE_THREAD(_hEngine) lem::Process::CritSecLocker guard( & HandleEngine(_hEngine)->cs );
#else
#define DEMO_SINGLE_THREAD(_hEngine)
#endif



// Returns the number of items in array of integers
// http://www.solarix.ru/api/en/sol_CountInts.shtml
// http://www.solarix.ru/api/ru/sol_CountInts.shtml
GREN_API(int) sol_CountInts(HGREN_INTARRAY h)
{
    if (h == NULL)
        return -1;

    return CastSizeToInt(((lem::MCollect<int>*)h)->size());
}


// http://www.solarix.ru/api/en/sol_GetInt.shtml
// http://www.solarix.ru/api/ru/sol_GetInt.shtml
GREN_API(int) sol_GetInt(HGREN_INTARRAY h, int i)
{
    if (h == NULL)
        return -1;

    try
    {
        return ((lem::MCollect<int>*)h)->get(i);
    }
    catch (...)
    {
        return -1;
    }
}


// http://www.solarix.ru/api/en/sol_DeleteInts.shtml
// http://www.solarix.ru/api/ru/sol_DeleteInts.shtml
GREN_API(void) sol_DeleteInts(HGREN_INTARRAY h)
{
    delete h;
}





// ******************************************************************************
// Returns the max lexem length.
// http://www.solarix.ru/api/en/sol_MaxLexemLen.shtml
// Entry names and wordforms can be this length maximum (including C-string '\0')
// 
// ���������� ������������ ����� �������.
// ����� ��������� ������ � ��������� ����� ����� ����� ����� �������� (� ������
// ������������ 0).
// ******************************************************************************
GREN_API(int) sol_MaxLexemLen(HGREN hEngine)
{
    return LEM_CSTRING_LEN + 1;
}

// Maximum length of lexemes, part of speech names and so on, in utf-8.
GREN_API(int) sol_MaxLexemLen8(HGREN hEngine)
{
    return LEM_CSTRING_LEN * 6 + 1;
}



// ************************************************************************ 
// Return version info
// ���� Major, Minor � Build �� NULL, �� ����� ��� ������������ ����������
// ������ ������ ������.
//
// ���������� 0 ��� DEMO, 1 ��� PRO
// ************************************************************************ 
GREN_API(int) sol_GetVersion(HGREN hEngine, int *Major, int *Minor, int *Build)
{
    Solarix::Version_Info ver;

    if (Major != NULL) *Major = ver.major;
    if (Minor != NULL) *Minor = ver.minor;
    if (Build != NULL) *Build = ver.build;

#if defined SOLARIX_DEMO
    return 0;
#else
    return 1;
#endif
}


// ****************************************************************************
// ������� ����� �����. ������������ ����� �������� ���, ���������� ��� ����
// ��������� � ������ ����� ��������� ������, ���� -1 ���� ����� �� ������.
// ****************************************************************************
GREN_API(int) sol_SeekWord(HGREN hEngine, const wchar_t *word, int Allow_Dynforms)
{
    if (!hEngine || word == NULL)
        return -1;

    try
    {
        if (HandleEngine(hEngine)->seeker == NULL)
        {
            lem::MCollect<Solarix::Word_Coord> found_list;
            lem::UCString w(word);
            HandleEngine(hEngine)->dict->GetLexAuto().ProjectWord(w, found_list, UNKNOWN);
            if (!found_list.empty())
                return found_list.front().GetEntry();
            else
                return UNKNOWN;
        }
        else
        {
            // �������� ������� �� �����. �����.
            lem::UCString w(word);
            return HandleEngine(hEngine)->seeker->Find(w, Allow_Dynforms == 1);
        }
    }
    CATCH_API(hEngine)

        return -2;
}






// Releases the memory allocated by the engine and returned to the client code.
GREN_API(int) sol_Free(HGREN hEngine, void *ptr)
{
    try
    {
        free(ptr);
        return 0;
    }
    CATCH_API(hEngine)

        return -1;
}


GREN_API(int) sol_CountStrings(HGREN_STR hStrings)
{
    if (hStrings == NULL)
        return 0;

    try
    {
        return CastSizeToInt(HandleStrList(hStrings)->list.size());
    }
    catch (...)
    {
        return -2;
    }
}


GREN_API(int) sol_GetStrings(HGREN_STR hStrings, wchar_t **Res)
{
    if (hStrings == NULL || Res == NULL)
        return -1;

    try
    {
        for (lem::Container::size_type i = 0; i < HandleStrList(hStrings)->list.size(); i++)
            wcscpy(Res[i], HandleStrList(hStrings)->list[i].c_str());

        return 0;
    }
    catch (...)
    {
        return -2;
    }
}



GREN_API(int) sol_GetStringLen(HGREN_STR hStrings, int i)
{
    if (hStrings == NULL)
        return -1;

    try
    {
        return HandleStrList(hStrings)->list[i].length();
    }
    catch (...)
    {
        return -2;
    }
}

GREN_API(int) sol_GetStringW(HGREN_STR hStrings, int i, wchar_t *Res)
{
    if (hStrings == NULL || Res == NULL)
        return -1;

    try
    {
        *Res = 0;
        wcscpy(Res, HandleStrList(hStrings)->list[i].c_str());
        return 0;
    }
    catch (...)
    {
        return -2;
    }
}


GREN_API(int) sol_GetStringA(HGREN_STR hStrings, int i, char *Res)
{
    if (hStrings == NULL || Res == NULL)
        return -1;

    try
    {
        *Res = 0;
        strcpy(Res, lem::to_ascii(HandleStrList(hStrings)->list[i].c_str()).c_str());
        return 0;
    }
    catch (...)
    {
        return -2;
    }
}

GREN_API(int) sol_GetString8(HGREN_STR hStrings, int i, char *ResUtf8)
{
    if (hStrings == NULL || ResUtf8 == NULL)
        return -1;

    try
    {
        *ResUtf8 = 0;
        strcpy(ResUtf8, lem::to_utf8(HandleStrList(hStrings)->list[i].c_str()).c_str());
        return 0;
    }
    catch (...)
    {
        return -2;
    }
}



GREN_API(int) sol_DeleteStrings(HGREN_STR hStrings)
{
    try
    {
        if (hStrings != NULL)
            delete HandleStrList(hStrings);

        return 0;
    }
    catch (...)
    {
        return -2;
    }
}


#define ENGINE HandleEngine(hEngine)

using namespace lem;
using namespace Solarix;



#if defined SOLARIX_GRAMMAR_ENGINE || defined SOLARIX_SYNONYMIZER_ENGINE
// ***********************************************************************
// Grammar engine is completely removed from memory.
// ������� ��������� ��������� �� ����������� ������.
//
// http://www.solarix.ru/api/en/sol_DeleteGrammarEngine.shtml
// ***********************************************************************
GREN_API(int) sol_DeleteGrammarEngine(HGREN hEngine)
{
    try
    {
        if (hEngine != NULL)
        {
            GrammarEngineHolder * ptr = (GrammarEngineHolder*)hEngine;
            delete ptr;
        }
        return 1;
    }
    CATCH_API(hEngine)

        return 0;
}
#endif


#if defined SOLARIX_GRAMMAR_ENGINE


GREN_API(int) sol_LoadDictionaryExW(HGREN hEngine, const wchar_t *Filename, int Flags);

// Initializes a new instance of the grammatical dictionary in memory.
// http://www.solarix.ru/api/en/sol_CreateGrammarEngine.shtml
GREN_API(HGREN) sol_CreateGrammarEngineExW(const wchar_t *DictionaryXml, int Flags)
{
    lem::Init();

    int rc = 0;

#if defined LEM_THREADS
    if ((Flags & SOL_CREATE_GREN_DONT_INIT_SQLITE) != SOL_CREATE_GREN_DONT_INIT_SQLITE)
    {
        // �������������� SQlite � ���������� ������������� ������, �����
        // ����� ���� ������������ �� ���������� ����� �������� � ����� �����������.
        // ���� ����� ��������� ������������, �� � ������� ����� ����� ��������� �������������.
        static bool SQLiteInitialized = false;
        if (!SQLiteInitialized)
        {
            SQLiteInitialized = true;
            if (!lem::sqlite_init_serialized_mode())
                return NULL;
        }
    }
#endif


    HGREN hEngine = new GrammarEngineHolder();

    if (!lem::lem_is_empty(DictionaryXml))
    {
        rc = sol_LoadDictionaryExW(hEngine, DictionaryXml, Flags);
        if (rc != 1)
            goto Failed;
    }
    else
    {
        rc = 0;
    }

    /*
     // --------- DEBUG
     wchar_t p[ lem::Path::MaxLen ];
     memset( p, 0, sizeof(p) );
     GetModuleFileNameW( GetModuleHandleW(L"solarix_grammar_engine.dll"), p, lem::Path::MaxLen );
     MessageBoxW( NULL, p, L"DEBUG-1", MB_OK );
     // ---------------
    */


    return hEngine;

Failed:;
#if defined SOLARIX_GRAMMAR_ENGINE || defined SOLARIX_SYNONYMIZER_ENGINE
    sol_DeleteGrammarEngine(hEngine);
#else
    sol_DeleteSearchEngine(hEngine);
#endif

    return NULL;
}

GREN_API(HGREN) sol_CreateGrammarEngineW(const wchar_t *DictionaryXml)
{
    return sol_CreateGrammarEngineExW(DictionaryXml, 0);
}

#endif


#if defined SOLARIX_GRAMMAR_ENGINE || defined SOLARIX_SYNONYMIZER_ENGINE
// http://www.solarix.ru/api/en/sol_CreateGrammarEngine.shtml

GREN_API(HGREN) sol_CreateGrammarEngineExA(const char *DictionaryXml, int Flags)
{
    lem::Init();

    int rc = 0;

    HGREN hEngine = new GrammarEngineHolder();

    if (!lem::lem_is_empty(DictionaryXml))
    {
        rc = sol_LoadDictionaryA(hEngine, DictionaryXml);

        if (rc != 1)
            goto Failed;
    }
    else
    {
        rc = 0;
    }

    return hEngine;

Failed:;
    sol_DeleteGrammarEngine(hEngine);

    return NULL;
}

GREN_API(HGREN) sol_CreateGrammarEngineA(const char *DictionaryXml)
{
    return sol_CreateGrammarEngineExA(DictionaryXml, 0);
}

#endif


#if defined SOLARIX_GRAMMAR_ENGINE || defined SOLARIX_SYNONYMIZER_ENGINE
// http://www.solarix.ru/api/en/sol_CreateGrammarEngine.shtml
GREN_API(HGREN) sol_CreateGrammarEngine8(const char *DictionaryXmlUtf8)
{
    lem::Init();
    return sol_CreateGrammarEngineW(lem::from_utf8(DictionaryXmlUtf8).c_str());
}

GREN_API(HGREN) sol_CreateGrammarEngineEx8(const char *DictionaryXmlUtf8, int Flags)
{
    lem::Init();

    return sol_CreateGrammarEngineExW(lem::from_utf8(DictionaryXmlUtf8).c_str(), Flags);
}
#endif



#if defined SOLARIX_GRAMMAR_ENGINE

// http://www.solarix.ru/api/en/sol_LoadDictionary.shtml
GREN_API(int) sol_LoadDictionaryA(HGREN hEngine, const char *Filename)
{
    return sol_LoadDictionaryW(hEngine, to_unicode(Filename).c_str());
}


// ***********************************************************************
// Load the grammatical dictionary engine in memory.
// �������� ������� � ����������� ������ �� ���������� ��������� �����.
// http://www.solarix.ru/api/en/sol_LoadDictionary.shtml
//
// Returns: 
//  0 - dictionary was not loaded
//  1 - dictionary was successfuly loaded
//  2 - dictionary is already loaded
// ***********************************************************************
GREN_API(int) sol_LoadDictionaryW(HGREN hEngine, const wchar_t *Filename)
{
    if (lem::lem_is_empty(Filename) || hEngine == NULL)
        return 0;

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&(HandleEngine(hEngine)->cs));
#endif

    if (!!ENGINE->dict)
        // Dictionary is already loaded.
        return 2;

    int loaded_ok = 0;

    try
    {
        loaded_ok = HandleEngine(hEngine)->Load(Filename, false) ? 1 : 0;
    }
    CATCH_API(hEngine)

        return loaded_ok;
}


// http://www.solarix.ru/api/en/sol_LoadDictionary.shtml
GREN_API(int) sol_LoadDictionary8(HGREN hEngine, const char *FilenameUtf8)
{
    return sol_LoadDictionaryW(hEngine, lem::from_utf8(FilenameUtf8).c_str());
}


GREN_API(int) sol_LoadDictionaryEx8(HGREN hEngine, const char *FilenameUtf8, int Flags)
{
    return sol_LoadDictionaryExW(hEngine, lem::from_utf8(FilenameUtf8).c_str(), Flags);
}


GREN_API(int) sol_LoadDictionaryExA(HGREN hEngine, const char *Filename, int Flags)
{
    return sol_LoadDictionaryExW(hEngine, to_unicode(Filename).c_str(), Flags);
}

GREN_API(int) sol_LoadDictionaryExW(HGREN hEngine, const wchar_t *Filename, int Flags)
{
    if (lem::lem_is_empty(Filename) || hEngine == NULL)
        return 0;

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&ENGINE->cs);
#endif

    if (!!ENGINE->dict)
        // Dictionary is already loaded.
        return 2;

    int loaded_ok = 0;

    try
    {
        const bool LazyLexicon = (Flags & SOL_CREATE_GREN_LAZY_LEXICON) == SOL_CREATE_GREN_LAZY_LEXICON;
        loaded_ok = ENGINE->Load(Filename, LazyLexicon) ? 1 : 0;
    }
    CATCH_API(hEngine)

        return loaded_ok;
}



#endif


// Returns the value indicating whether the dictionary has been initialized and loaded
// http://www.solarix.ru/api/en/sol_IsDictionaryLoaded.shtml
GREN_API(int) sol_IsDictionaryLoaded(HGREN hEngine)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&ENGINE->cs);
#endif
    return (hEngine != NULL && !!HandleEngine(hEngine)->dict) ? 1 : 0;
}



#if defined SOLARIX_GRAMMAR_ENGINE
// Drops the grammatical dictionary in-memory structures, frees the allocated resources.
// http://www.solarix.ru/api/en/sol_UnloadDictionary.shtml
GREN_API(void) sol_UnloadDictionary(HGREN hEngine)
{
    if (hEngine == NULL)
        return;

    try
    {
#if defined LEM_THREADS
        lem::Process::CritSecLocker guard(&ENGINE->cs);
#endif

        ENGINE->dict.reset();
        ENGINE->seeker.reset();
        ENGINE->fuzzy.reset();
    }
    CATCH_API(hEngine)

        return;
}
#endif



// Check the availability of lexicon and thesaurus for specified language
// http://www.solarix.ru/api/en/sol_HasLanguage.shtml
GREN_API(int) sol_HasLanguage(HGREN hEngine, int LanguageID)
{
    if (hEngine == NULL || LanguageID == UNKNOWN || HandleEngine(hEngine)->dict.IsNull())
        return 0;

    int ret = 0;
    try
    {
#if defined SOL_CAA && !defined SOL_NO_AA
        lem::MCollect<int> langs;
        HandleEngine(hEngine)->dict->GetLanguages(langs);
        return langs.find(LanguageID) != UNKNOWN;
#endif
    }
    CATCH_API(hEngine)

        return 0;
}


// ***********************************************************************
// Count the total number of word and phrase entries in dictionary.
// ������� ��������� ������ � �������
//
// http://www.solarix.ru/api/en/sol_CountEntries.shtml
// http://www.solarix.ru/api/ru/sol_CountEntries.shtml
// ***********************************************************************
GREN_API(int) sol_CountEntries(HGREN hEngine)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict)
        return -1;

    int ret = -1;
    try
    {
        const int n_words = HandleEngine(hEngine)->dict->GetSynGram().GetnEntry(ANY_STATE);
        const int n_phrases = HandleEngine(hEngine)->dict->GetSynGram().GetStorage().CountPhrases();
        return n_words + n_phrases;
    }
    CATCH_API(hEngine)

        return ret;
}


// ***********************************************************************
// Count the total number of wordforms in dictionary.
// ������� ��������� (���� ������������) � �������.
// ***********************************************************************
GREN_API(int) sol_CountForms(HGREN h)
{
    if (h == NULL || !HandleEngine(h)->dict)
        return -1;

    try
    {
        return HandleEngine(h)->dict->GetSynGram().Count_Forms();
    }
    CATCH_API(h)

        return -1;
}


// ****************************************************************************
// Returns the total number of links (word and phrase relations) in thesaurus.
// ���������� ���������: ������� ������� �����.
//
// http://www.solarix.ru/api/en/sol_CountLinks.shtml
// ****************************************************************************
GREN_API(int) sol_CountLinks(HGREN hEngine)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict)
        return -1;

    try
    {
        return CastSizeToInt(HandleEngine(hEngine)->dict->GetSynGram().Get_Net().CountAllLinks());
    }
    CATCH_API(hEngine)

        return -1;
}






// ********************************************************
// ���������� ����� ������ �������.
// http://www.solarix.ru/api/ru/sol_DictionaryVersion.shtml
// ********************************************************
GREN_API(int) sol_DictionaryVersion(HGREN hEngine)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict)
        return -1;

    return HandleEngine(hEngine)->dict->version.code;
}






// Set default language ID. This is vital parameter for correct normalization of characters.
GREN_API(int) sol_SetLanguage(HGREN hEngine, int LanguageID)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict)
        return -1;

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&HandleEngine(hEngine)->cs);
#endif

    HandleEngine(hEngine)->DefaultLanguage = LanguageID;
    HandleEngine(hEngine)->dict->SetDefaultLanguage(LanguageID);

    return 0;
}


// ***********************************************************************
// ����� ���������� � ���������.
// � ������ ������ ������������ ����� �������� ��������, � ������� ������
// � ����� � ����� ientry ��� ������ ��������.
// � iform ��������������.
// ����� ���� iclass ������������ ������ ��������������� ������.
//
// ���� ����� �� ������� - ������������ -1.
//
// ***********************************************************************
GREN_API(int) sol_FindWord(
    HGREN h,
    const wchar_t *Word,
    int *EntryIndex,
    int *Form,
    int *Class
)
{
    if (h == NULL || !HandleEngine(h)->dict)
        return -1;

    if (EntryIndex != NULL) *EntryIndex = UNKNOWN;
    if (Form != NULL) *Form = UNKNOWN;
    if (Class != NULL) *Class = UNKNOWN;

    DEMO_SINGLE_THREAD(h)

        try
    {
        UCString uWord(Word);
        uWord.to_upper();

        // Look for it in dictionary
        Lexem ml(uWord);
        HandleEngine(h)->dict->GetLexAuto().TranslateLexem(ml, true);

        RC_Lexem rc(&ml, null_deleter());

        MCollect<Word_Coord> found_list;
        MCollect<ProjScore> val_list;
        PtrCollect<LA_ProjectInfo> inf_list;

        HandleEngine(h)->dict->GetLexAuto().ProjectWord(rc, found_list, val_list, inf_list, LexicalAutomat/*::DynformsMode*/::Wordforms, 0, HandleEngine(h)->DefaultLanguage, NULL);

        if (!found_list.empty())
        {
            const int ientry0 = found_list.front().GetEntry();
            const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(ientry0);

            if (EntryIndex) *EntryIndex = ientry0;
            if (Form)  *Form = found_list.front().GetForm();
            if (Class) *Class = e.GetClass();
        }

        // Returns number of projections
        return CastSizeToInt(found_list.size());
    }
    CATCH_API(h)

        // Missing in dictionary
        return UNKNOWN;
}


static void getForms(
    HGREN h,
    const wchar_t *Word,
    bool Allow_Dynforms,
    bool Synonyms,
    bool Grammar_Links,
    bool Translations,
    bool Semantics,
    int nJumps,
    lem::MCollect<UCString> &res
)
{
    const bool Thesaurus = (Synonyms || Grammar_Links) && nJumps > 0;
    const LexicalAutomat::DynformsMode morphology = Allow_Dynforms ? LexicalAutomat::Dynforms_Last_Chance : LexicalAutomat::Wordforms;

    const bool all_links = Synonyms && Grammar_Links && Translations && Semantics;

    // ��� ������� ��������� ��������� �������, ��� ��� ���� ������ ���������� ������
    // ����������� ������ ��� ��� ������ ���������. 
    lem::MCollect< Tree_Link > allowed_links;
    if (!all_links)
    {
        if (Synonyms)
            allowed_links.push_back(SYNONYM_link);

        if (Grammar_Links)
        {
            allowed_links.push_back(TO_VERB_link);
            allowed_links.push_back(TO_INF_link);
            allowed_links.push_back(TO_PERFECT);
            allowed_links.push_back(TO_UNPERFECT);
            allowed_links.push_back(TO_NOUN_link);
            allowed_links.push_back(TO_ADJ_link);
            allowed_links.push_back(TO_ADV_link);
            allowed_links.push_back(TO_RETVERB);
            allowed_links.push_back(WOUT_RETVERB);
        }

        if (Translations)
        {
            allowed_links.push_back(TO_ENGLISH_link);
            allowed_links.push_back(TO_RUSSIAN_link);
            allowed_links.push_back(TO_FRENCH_link);
            allowed_links.push_back(TO_SPANISH_link);
            allowed_links.push_back(TO_GERMAN_link);
            allowed_links.push_back(TO_CHINESE_link);
            allowed_links.push_back(TO_POLAND_link);
            allowed_links.push_back(TO_ITALIAN_link);
            allowed_links.push_back(TO_PORTUGUAL_link);
            allowed_links.push_back(TO_JAPANESE_link);
        }

        if (Semantics)
        {
            allowed_links.push_back(CLASS_link);
            allowed_links.push_back(ACTION_link);
            allowed_links.push_back(ACTOR_link);
            allowed_links.push_back(TOOL_link);
            allowed_links.push_back(RESULT_link);
        }
    }


    LexicalAutomat &la = HandleEngine(h)->dict->GetLexAuto();
    SynGram &sg = HandleEngine(h)->dict->GetSynGram();

    std::set<int> ientry_set;

    Lexem *lex = new Lexem(Word);
    la.TranslateLexem(*lex, true);
    RC_Lexem rc_ml(lex);

    MCollect<Word_Coord> found_list;
    MCollect<ProjScore> val_list;
    PtrCollect<LA_ProjectInfo> inf_list;

    la.ProjectWord(rc_ml, found_list, val_list, inf_list, morphology, 0, HandleEngine(h)->DefaultLanguage, NULL);

    // ����������� ��������������� ������ �������� ������
    for (Container::size_type i = 0; i < found_list.size(); i++)
    {
        int ie = found_list[i].GetEntry();

        // ����������� ���������� ���� ��������� ������
        const SG_Entry &e = sg.GetEntry(ie);
        const Container::size_type nf = e.forms().size();
        for (Container::size_type k = 0; k < nf; k++)
        {
            const UCString &str = e.forms()[k].name();

            bool f = false;
            for (Container::size_type j = 0; j < res.size(); j++)
                if (res[j] == str)
                {
                    f = true;
                    break;
                }

            if (!f)
                res.push_back(str);
        }

        // ���� ��������� ������ ��������� ��������� ������ �� ���������
        if (Thesaurus)
            ientry_set.insert(ie);
    }

    if (Thesaurus)
    {
        std::set<int> links;

        for (std::set<int>::const_iterator l = ientry_set.begin(); l != ientry_set.end(); l++)
        {
            links.clear();

            // ������
            if (all_links)
                sg.Get_Net().Find_Linked_Entries(sg.GetEntry(*l).GetKey(), nJumps, links);
            else
                sg.Get_Net().Find_Linked_Entries(sg.GetEntry(*l).GetKey(), nJumps, links, true, true, &allowed_links);

            for (std::set<int>::const_iterator k = links.begin(); k != links.end(); k++)
            {
                const SG_Entry &e = sg.GetEntry(*k);

                const Container::size_type nf = e.forms().size();
                for (Container::size_type k = 0; k < nf; k++)
                {
                    const UCString &str = e.forms()[k].name();

                    bool f = false;
                    for (Container::size_type j = 0; j < res.size(); j++)
                        if (res[j] == str)
                        {
                            f = true;
                            break;
                        }

                    if (!f)
                        res.push_back(str);
                }
            }
        }
    }

    return;
}






GREN_API(HGREN_STR) sol_FindStringsEx(
    HGREN h,
    const wchar_t *Word,
    int Allow_Dynforms,
    int Synonyms,
    int Grammar_Links,
    int Translations,
    int Semantics,
    int nJumps
)
{
    if (h == NULL || !HandleEngine(h)->dict)
        return NULL;

    GREN_Strings *res = new GREN_Strings;

    lem::MCollect<UCString> list;
    list.reserve(32);

    try
    {
        getForms(h, Word, Allow_Dynforms == 1, Synonyms == 1, Grammar_Links == 1, Translations == 1, Semantics == 1, nJumps, list);

        for (MCollect<UCString>::const_iterator i = list.begin(); i != list.end(); i++)
            res->list.push_back(*i);
    }
    catch (...)
    {
        delete res;
        return NULL;
    }

    return res;
}




static int Decline(
    HGREN h,
    int ientry, int icase, int number, int anim_form);

static int Correlate_Nom(
    HGREN h,
    int ientry,
    int factor,
    int Anim
);
static int Correlate_Instr(
    HGREN h,
    int ientry,
    int factor,
    int Anim
);
static int Correlate_Accus(
    HGREN h,
    int ientry,
    int factor,
    int Anim
);
static int Correlate_All(
    HGREN h,
    int ientry,
    int factor,
    int Case,
    int Anim
);


// ***********************************************************************
// ������������ ���������������� � �������������. �������� �������� �����
// � (�����������) - ��������������/����������������.
// ***********************************************************************
GREN_API(int) sol_CorrNounNumber(
    HGREN h,
    int EntryIndex,
    int Value,
    int Case,         /*NOMINATIVE_CASE*/
    int Anim,         /*INANIMATIVE_FORM*/
    wchar_t *Result
)
{
    if (h == NULL || !HandleEngine(h)->dict || Result == NULL)
        return -1;

    *Result = 0;

    if (!h || EntryIndex == -1)
        return -1;

    try
    {
        const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex);

        //UCString aaa = e.GetName();

        if (e.GetClass() == NOUN_ru)
        {
            // ����� ����� �������� ��������������� �������� �����

            int factor = Value % 100;
            factor = factor < 20l ? factor % 20l : factor % 10l;

            int iform = UNKNOWN;
            switch (Case)
            {
            case NOMINATIVE_CASE_ru:
                iform = Correlate_Nom(h, EntryIndex, factor, Anim);
                break;

            case ACCUSATIVE_CASE_ru:
                iform = Correlate_Accus(h, EntryIndex, factor, Anim);
                break;

            case INSTRUMENTAL_CASE_ru:
                iform = Correlate_Instr(h, EntryIndex, factor, Anim);
                break;

            default:
                iform = Correlate_All(h, EntryIndex, factor, Case, Anim);
            }

            if (iform == UNKNOWN)
                // �� ������� ���������� ����� ����� 
                return -3;

            // ����� ������ ����� �����.
            // ��������� ����������� ���������� �����
            lem_strcpy(Result, e.forms()[iform].name().c_str());
            return 0;
        }
    }
    catch (...)
    {
        return -1;
    }

    // ����� �� ������� � �������
    return -2;
}




static int Correlate_Nom(
    HGREN h,
    int ientry,
    int factor,
    int Anim
)
{
    if (factor == 0)
        return Decline(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim
        );

    if (factor == 1)
        return Decline(
            h,
            ientry,
            NOMINATIVE_CASE_ru,
            SINGULAR_NUMBER_ru,
            Anim
        );

    if (factor >= 2 && factor <= 4)
    {
        return Decline(
            h,
            ientry,
            GENITIVE_CASE_ru,
            SINGULAR_NUMBER_ru,
            Anim
        );
    }

    return Decline(
        h,
        ientry,
        GENITIVE_CASE_ru,
        PLURAL_NUMBER_ru,
        Anim
    );
}



static int Correlate_Instr(
    HGREN h,
    int ientry,
    int factor,
    int Anim
)
{
    if (factor == 0)
        return Decline(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim
        );

    if (factor == 1)
        return Decline(
            h,
            ientry,
            INSTRUMENTAL_CASE_ru,
            SINGULAR_NUMBER_ru,
            Anim
        );

    return Decline(
        h,
        ientry,
        INSTRUMENTAL_CASE_ru,
        PLURAL_NUMBER_ru,
        Anim
    );
}


static int Correlate_Accus(
    HGREN h,
    int ientry,
    int factor,
    int Anim
)
{
    if (factor == 0)
        return Decline(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim
        );

    if (factor == 1)
        return Decline(
            h,
            ientry,
            ACCUSATIVE_CASE_ru,
            SINGULAR_NUMBER_ru,
            Anim
        );

    if (factor >= 2 && factor <= 4)
    {
        return Decline(
            h,
            ientry,
            GENITIVE_CASE_ru,
            SINGULAR_NUMBER_ru,
            Anim
        );
    }

    return Decline(
        h,
        ientry,
        GENITIVE_CASE_ru,
        PLURAL_NUMBER_ru,
        Anim
    );
}


static int Correlate_All(
    HGREN h,
    int ientry,
    int factor,
    int Case,
    int Anim
)
{
    if (factor == 0)
        return Decline(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim
        );

    if (factor == 1)
        return Decline(
            h,
            ientry,
            Case,
            SINGULAR_NUMBER_ru,
            Anim
        );

    return Decline(
        h,
        ientry,
        Case,
        PLURAL_NUMBER_ru,
        Anim
    );
}


// ********************************************************************
// ����� ���������� � ��������� ������.
// ********************************************************************
static int Decline(
    HGREN h,
    int ientry,
    int icase,
    int number,
    int anim_form
)
{
    try
    {
        const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(ientry);

        CP_Array dim;

        dim.push_back(GramCoordPair(GramCoordAdr(CASE_ru, 0), icase));
        dim.push_back(GramCoordPair(GramCoordAdr(NUMBER_ru, 0), number));

        return e.FindFormIndex(dim);
    }
    catch (...)
    {
        return UNKNOWN;
    }

    return UNKNOWN;
}

// ****************************************************************
// �����, �������� ������������� ���������� value, ����������� �
// ��������� �������������.
// ****************************************************************
GREN_API(int) sol_Value2Text(
    HGREN h,
    wchar_t *Result,
    int Value,
    int Gender
)
{
    if (h == NULL || !HandleEngine(h)->dict || Result == NULL)
        return -1;

#if defined LEM_OFMT_MICROSOL
    try
    {
        wstring res = to_text(Value, LEM_RUS, Gender != FEMININE_GENDER_ru);
        lem_strcpy(Result, res.c_str());
    }
    catch (...)
    {
        return -1;
    }

    return 0;
#else
    return -1;
#endif
}


// ***************************************************************************
// Find the entry ID.
//
// http://www.solarix.ru/api/en/sol_FindEntry.shtml
// http://www.solarix.ru/api/ru/sol_FindEntry.shtml
//
// Other API functions use this index to perform operations on words without
// repeated search in dictionary.
//
// Returns: 
//         -1  word entry not found
//         -2  internal error  
//
// ����� ������� ��������� ������ �� ���������� ������. ������ �������
// �������������� ������ ����� ��������� �������� �� ������� � ��������������
// ����� ������� (����� �� ��������� ����� � �������).
//
// ����������:
//            -1  ��������� ������ �� ������� 
//            -2  ���������� ����
// ***************************************************************************
GREN_API(int) sol_FindEntry(
    HGREN h,
    const wchar_t *Word, // Entry name
    int Class,           // Required grammatical class
    int Language         // Language ID (if ambiguos)
)
{
    if (h == NULL || !HandleEngine(h)->dict)
        return -2;

    DEMO_SINGLE_THREAD(h)

        try
    {
        // Convert to UNICODE lexem
        UCString uWord(Word);
        uWord.to_upper();

        // ���� ��������� ������ � ����� ������
        return HandleEngine(h)->dict->GetSynGram().FindEntry(uWord, Class, false);
    }
    catch (...)
    {
        // Internal error
        return -2;
    }
}


GREN_API(int) sol_FindEntry8(HGREN hEngine, const char *Word, int Class, int Language)
{
    return sol_FindEntry(hEngine, lem::from_utf8(Word).c_str(), Class, Language);
}


// *************************************************************
// Returns the gender of noun (unapplayable for English) 
//
// http://www.solarix.ru/api/en/sol_GetNounGender.shtml
// http://www.solarix.ru/api/ru/sol_GetNounGender.shtml
//
// ���������� ��� ���������������� (����������� ��� �����������)
// *************************************************************
GREN_API(int) sol_GetNounGender(
    HGREN h,
    int EntryIndex  // Entry index (see sol_Find_Entry API functions)
)
{
    if (!h || !HandleEngine(h)->dict || EntryIndex == -1)
        return -2;

    try
    {
        // The language that the entry belongs to.
        int Lang = static_cast<const SG_Class&>(
            HandleEngine(h)->dict->GetSynGram().classes()[HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex).GetClass()]
            ).GetLanguage();

        if (Lang == RUSSIAN_LANGUAGE)
            return HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex).GetAttrState(GramCoordAdr(GENDER_ru, 0));
    }
    catch (...)
    {
    }

    return UNKNOWN;
}

// ***********************************************************************
// Get the noun form for given case and number. Result will contain the 
// lexical content of the wordform (or empty string if not found). 
// 
// ���������� � Result ����� ���������������� � �������� ������� � ������.
// ***********************************************************************
GREN_API(int) sol_GetNounForm(
    HGREN h,
    int EntryIndex,
    int Number,
    int Case,
    wchar_t *Result
)
{
    *Result = 0;

    if (!h || !HandleEngine(h)->dict || EntryIndex == -1 || Result == NULL)
        return -2;

    try
    {
        const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex);

        // The language that the entry belongs to.
        int Lang = static_cast<const SG_Class&>(
            HandleEngine(h)->dict->GetSynGram().classes()[e.GetClass()]
            ).GetLanguage();

        CP_Array dim;

        switch (Lang)
        {
        case RUSSIAN_LANGUAGE:
        {
            dim.push_back(GramCoordPair(GramCoordAdr(CASE_ru, 0), Case));
            dim.push_back(GramCoordPair(GramCoordAdr(NUMBER_ru, 0), Number));
            break;
        }

#if defined SOL_GM_ENGLISH
        case ENGLISH_LANGUAGE:
        {
            dim.push_back(GramCoordPair(GramCoordAdr(NUMBER_xx, 0), Number));

            if (Case != -1)
                dim.push_back(GramCoordPair(GramCoordAdr(CASE_en, 0), Case));
            else
                dim.push_back(GramCoordPair(GramCoordAdr(CASE_en, 0), NOMINATIVE_CASE_en));

            break;
        }
#endif 
        }

        int iform = e.FindFormIndex(dim);
        if (iform == UNKNOWN)
            // �� ������� ���������� ����� ����� 
            return -3;

        // ����� ������ ����� �����.
        // ��������� ����������� ���������� �����
        const SG_EntryForm &f = e.forms()[iform];
        lem_strcpy(Result, e.forms()[iform].name().c_str());
        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// ************************************************************
// Get the proper verb form.
//
// ���� ���������� ����� �������. 
// ************************************************************
GREN_API(int) sol_GetVerbForm(
    HGREN h,
    int EntryIndex,
    int Number,
    int Gender,
    int Tense,
    int Person,
    wchar_t *Result
)
{
    if (!h || !HandleEngine(h)->dict || EntryIndex == -1 || Result == NULL)
        return -2;

    *Result = 0;

    try
    {
        const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex);

        // The language that the entry belongs to.
        int Lang = static_cast<const SG_Class&>(
            HandleEngine(h)->dict->GetSynGram().classes()[e.GetClass()]
            ).GetLanguage();

        CP_Array dim;

        switch (Lang)
        {
        case RUSSIAN_LANGUAGE:
        {
            dim.push_back(GramCoordPair(GramCoordAdr(NUMBER_ru, 0), Number));

            if (
                Number == SINGULAR_NUMBER_ru &&
                Tense == PAST_ru
                )
                dim.push_back(GramCoordPair(GramCoordAdr(GENDER_ru, 0), Gender));

            dim.push_back(GramCoordPair(GramCoordAdr(TENSE_ru, 0), Tense));

            if (Tense == PRESENT_ru || Tense == FUTURE_ru)
                dim.push_back(GramCoordPair(GramCoordAdr(PERSON_ru, 0), Person));

            break;
        }

#if defined SOL_GM_ENGLISH
        case ENGLISH_LANGUAGE:
        {
            dim.push_back(GramCoordPair(GramCoordAdr(NUMBER_xx, 0), Number));
            dim.push_back(GramCoordPair(GramCoordAdr(TENSE_en, 0), Tense));
            dim.push_back(GramCoordPair(GramCoordAdr(PERSON_xx, 0), Person));
            break;
        }
#endif
        }

        int iform = e.FindFormIndex(dim);;
        if (iform == UNKNOWN)
            // �� ������� ���������� ����� ����� 
            return -3;

        // ����� ������ ����� �����.
        // ��������� ����������� ���������� �����
        lem_strcpy(Result, e.forms()[iform].name().c_str());
        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}



GREN_API(int) sol_CorrVerbNumber(
    HGREN h,
    int EntryIndex,
    int Value,
    int Gender,
    int Tense,
    wchar_t *Result
)
{
    if (!h || !HandleEngine(h)->dict || EntryIndex == -1 || Result == NULL)
        return -2;

    *Result = 0;

    int f100 = Value % 100;
    int f10 = Value % 10;

    if (
        (f100 == 1 ||
            f100 > 20) &&
        f10 == 1
        )
        return sol_GetVerbForm(
            h,
            EntryIndex,
            SINGULAR_NUMBER_ru,
            Gender,
            Tense,
            PERSON_3_ru,
            Result
        );

    return sol_GetVerbForm(
        h,
        EntryIndex,
        PLURAL_NUMBER_ru,
        Gender,
        Tense,
        PERSON_3_ru,
        Result
    );
}



GREN_API(int) sol_GetAdjectiveForm(
    HGREN h,
    int EntryIndex,
    int Number,
    int Gender,
    int Case,
    int Anim,
    int Shortness,
    int Compar_Form,
    wchar_t *Result
)
{
    if (!h || !HandleEngine(h)->dict || EntryIndex == -1 || Result == NULL)
        return -2;

    *Result = 0;

    try
    {
        const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex);

        // The language that the entry belongs to.
        int Lang = static_cast<const SG_Class&>(
            HandleEngine(h)->dict->GetSynGram().classes()[e.GetClass()]
            ).GetLanguage();

        CP_Array dim;

        switch (Lang)
        {
        case RUSSIAN_LANGUAGE:
        {
            dim.push_back(GramCoordPair(GramCoordAdr(CASE_ru, 0), Case));
            dim.push_back(GramCoordPair(GramCoordAdr(NUMBER_ru, 0), Number));

            if (Number == SINGULAR_NUMBER_ru)
            {
                dim.push_back(GramCoordPair(GramCoordAdr(GENDER_ru, 0), Gender));

                if (Gender == MASCULINE_GENDER_ru && Case == ACCUSATIVE_CASE_ru)
                    dim.push_back(GramCoordPair(GramCoordAdr(FORM_ru, 0), Anim));
            }
            else if (Number == PLURAL_NUMBER_ru && Case == ACCUSATIVE_CASE_ru)
            {
                dim.push_back(GramCoordPair(GramCoordAdr(FORM_ru, 0), Anim));
            }

            if (Shortness == UNKNOWN)
                dim.push_back(GramCoordPair(GramCoordAdr(SHORTNESS_ru, 0), 0));
            else
                dim.push_back(GramCoordPair(GramCoordAdr(SHORTNESS_ru, 0), Shortness));

            if (Compar_Form == UNKNOWN)
                dim.push_back(GramCoordPair(GramCoordAdr(COMPAR_FORM_ru, 0), ATTRIBUTIVE_FORM_ru));
            else
                dim.push_back(GramCoordPair(GramCoordAdr(COMPAR_FORM_ru, 0), Compar_Form));

            break;
        }

#if defined SOL_GM_ENGLISH
        case ENGLISH_LANGUAGE:
        {
            dim.push_back(GramCoordPair(GramCoordAdr(ADJ_FORM_en, 0), Compar_Form));
            break;
        }
#endif
        }

        int iform = e.FindFormIndex(dim);;
        if (iform == UNKNOWN)
            // �� ������� ���������� ����� ����� 
            return -3;

        // ����� ������ ����� �����.
        // ��������� ����������� ���������� �����
        const SG_EntryForm &f = e.forms()[iform];
        lem_strcpy(Result, f.name().c_str());
        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


static int Decline_Adj(HGREN h, int ientry, int icase, int number, int anim_form, int gender);
static int Correlate_Nom_Adj(
    HGREN h,
    int ientry,
    int factor,
    int Gender,
    int Anim
);
static int Correlate_Instr_Adj(
    HGREN h,
    int ientry,
    int factor,
    int Gender,
    int Anim
);
static int Correlate_Accus_Adj(
    HGREN h,
    int ientry,
    int factor,
    int Gender,
    int Anim
);
static int Correlate_All_Adj(
    HGREN h,
    int ientry,
    int factor,
    int Case,
    int Gender,
    int Anim
);



GREN_API(int) sol_CorrAdjNumber(
    HGREN h,
    int EntryIndex,
    int Value,
    int Case,
    int Gender,
    int Anim,
    wchar_t *Result
)
{
    if (!h || !HandleEngine(h)->dict || EntryIndex == -1 || Result == NULL)
        return -2;

    *Result = 0;

    try
    {
        const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex);

        //UCString aaa = e.GetName();

        if (e.GetClass() == ADJ_ru)
        {
            // ����� ����� �������� ��������������� �������� �����

            int factor = Value % 100;
            factor = factor < 20l ? factor % 20l : factor % 10l;

            int iform = UNKNOWN;
            switch (Case)
            {
            case NOMINATIVE_CASE_ru:
                iform = Correlate_Nom_Adj(h, EntryIndex, factor, Gender, Anim);
                break;

            case ACCUSATIVE_CASE_ru:
                iform = Correlate_Accus_Adj(h, EntryIndex, factor, Gender, Anim);
                break;

            case INSTRUMENTAL_CASE_ru:
                iform = Correlate_Instr_Adj(h, EntryIndex, factor, Gender, Anim);
                break;

            default:
                iform = Correlate_All_Adj(h, EntryIndex, factor, Case, Gender, Anim);
            }

            if (iform == UNKNOWN)
                // �� ������� ���������� ����� ����� 
                return -3;

            // ����� ������ ����� �����.
            // ��������� ����������� ���������� �����
            lem_strcpy(Result, e.forms()[iform].name().c_str());
            return 0;
        }
    }
    catch (...)
    {
        return -1;
    }

    return -2;
}


static int Correlate_Nom_Adj(
    HGREN h,
    int ientry,
    int factor,
    int Gender,
    int Anim
)
{
    if (factor == 0)
        return Decline_Adj(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim,
            Gender
        );

    if (factor == 1)
        return Decline_Adj(
            h,
            ientry,
            NOMINATIVE_CASE_ru,
            SINGULAR_NUMBER_ru,
            Anim,
            Gender
        );
    /*
     if( factor>=2 && factor<=4 )
      {
       return Decline_Adj(
                          ientry,
                          GENITIVE_CASE_ru,
                          SINGULAR_NUMBER_ru,
                          Anim,
                          Gender
                         );
      }
    */
    return Decline_Adj(
        h,
        ientry,
        GENITIVE_CASE_ru,
        PLURAL_NUMBER_ru,
        Anim,
        Gender
    );
}



static int Correlate_Instr_Adj(
    HGREN h,
    int ientry,
    int factor,
    int Gender,
    int Anim
)
{
    if (factor == 0)
        return Decline_Adj(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim,
            Gender
        );

    if (factor == 1)
        return Decline_Adj(
            h,
            ientry,
            INSTRUMENTAL_CASE_ru,
            SINGULAR_NUMBER_ru,
            Anim,
            Gender
        );

    return Decline_Adj(
        h,
        ientry,
        INSTRUMENTAL_CASE_ru,
        PLURAL_NUMBER_ru,
        Anim,
        Gender
    );
}



static int Correlate_Accus_Adj(
    HGREN h,
    int ientry,
    int factor,
    int Gender,
    int Anim
)
{
    if (factor == 0)
        return Decline_Adj(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim,
            Gender
        );

    // ���� ���� ����� ����
    // ���� ���� ������� ������
    // ���� ������ �������� ���
    if (factor == 1)
        return Decline_Adj(
            h,
            ientry,
            ACCUSATIVE_CASE_ru,
            SINGULAR_NUMBER_ru,
            Anim,
            Gender
        );

    // ���� 2 ������� �����
    // ���� 2 �������� �����
    // ���� 2 ����� ����
    if (factor >= 2 && factor <= 4)
    {
        return Decline_Adj(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim,
            Gender
        );
    }

    // ���� 5 ������� ������
    // ���� 5 �������� �����
    return Decline_Adj(
        h,
        ientry,
        GENITIVE_CASE_ru,
        PLURAL_NUMBER_ru,
        Anim,
        Gender
    );
}


static int Correlate_All_Adj(
    HGREN h,
    int ientry,
    int factor,
    int Case,
    int Gender,
    int Anim
)
{
    if (factor == 0)
        return Decline_Adj(
            h,
            ientry,
            GENITIVE_CASE_ru,
            PLURAL_NUMBER_ru,
            Anim,
            Gender
        );

    if (factor == 1)
        return Decline_Adj(
            h,
            ientry,
            Case,
            SINGULAR_NUMBER_ru,
            Anim,
            Gender
        );

    return Decline_Adj(
        h,
        ientry,
        Case,
        PLURAL_NUMBER_ru,
        Anim,
        Gender
    );
}


// ********************************************************************
// ����� ���������� � ��������� ������.
// ********************************************************************
static int Decline_Adj(HGREN h, int ientry, int Case, int Number, int Anim, int Gender)
{
    try
    {
        const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(ientry);

        CP_Array dim;

        dim.push_back(GramCoordPair(GramCoordAdr(CASE_ru, 0), Case));
        dim.push_back(GramCoordPair(GramCoordAdr(NUMBER_ru, 0), Number));

        if (Case == ACCUSATIVE_CASE_ru)
        {
            if (Number == SINGULAR_NUMBER_ru && Gender == MASCULINE_GENDER_ru)
                dim.push_back(GramCoordPair(GramCoordAdr(FORM_ru, 0), Anim));
            else if (Number == PLURAL_NUMBER_ru)
                dim.push_back(GramCoordPair(GramCoordAdr(FORM_ru, 0), Anim));
        }

        if (Number == SINGULAR_NUMBER_ru)
        {
            dim.push_back(GramCoordPair(GramCoordAdr(GENDER_ru, 0), Gender));
        }

        return e.FindFormIndex(dim);
    }
    catch (...)
    {
        return UNKNOWN;
    }

    return UNKNOWN;
}




// **********************************************************
// ������� ������������ ����� - ���������� � ������� �����
// **********************************************************
GREN_API(int) sol_LemmatizeWord(HGREN h, wchar_t *word, int Allow_Dynforms)
{
    if (!h || HandleEngine(h)->seeker == NULL || word == NULL)
        return 0;

    DEMO_SINGLE_THREAD(h)

        // �������� ������� �� �����. �����.
        UCString w(word);
    const int ientry = HandleEngine(h)->seeker->Find(w, Allow_Dynforms == 1);

    if (ientry != UNKNOWN)
    {
        // �������� ��� ������ - ����� ������ ��� ������� �����
        lem_strcpy(word, HandleEngine(h)->sg->GetEntry(ientry).GetName().c_str());
        return 1;
    }

    return 0;
}





// ***************************************************************************
//
// ��������� ������ ���������� � ������������ ��������������
// ����������������, �������� "������->�����". ��� ������ ���������
// ��������!
// ������� �������� EntryIndex - ��������� ����������� ������ sol_Find_Entry.
// ������������ ID ��������� ������ (���������������) ��� �������������,
// ��������, � sol_GetNounForm, ���� -1 ���� �������� � ����������������
// �� �������������� ���������.
//
// http://www.solarix.ru/api/ru/sol_TranslateToNoun.shtml
//
// ***************************************************************************
GREN_API(int) sol_TranslateToNoun(HGREN hEngine, int EntryID)
{
    if (EntryID == -1 || !hEngine || !HandleEngine(hEngine)->dict)
        return -1;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        const SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(EntryID);
        if (
            e.GetClass() == NOUN_ru ||
            e.GetClass() == NOUN_en ||
            e.GetClass() == NOUN_fr ||
            e.GetClass() == NOUN_es
            )
            // �������������� �� ���������, ��� ��� �������� ����� ��� ��������
            // ���������������.
            return EntryID;

        lem::MCollect<int> key_list; // ������ ��������� ���������������
        if (HandleEngine(hEngine)->dict->GetLexAuto().Translate_To_Nouns(EntryID, key_list))
        {
            // ����� ����� ����������������
            if (key_list.size() > 1)
            {
                // ������� ��������������� � ������������ ��������������
                int max_id = UNKNOWN, max_freq = 0;
                for (lem::Container::size_type k = 0; k < key_list.size(); ++k)
                {
                    const int id_entry = key_list[k];
                    const Solarix::SG_Entry & e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(id_entry);
                    if (e.GetFreq() > max_freq)
                    {
                        max_freq = e.GetFreq();
                        max_id = id_entry;
                    }
                }

                return max_id;
            }
            else
                return key_list.front();
        }
    }
    CATCH_API(hEngine);

    return -1;
}


// ************************************************************************
//
// ���������� ��������� ������ � ������������ ��� ������������� ���������
// �������������� ����� ������� (����������).
//
// http://www.solarix.ru/api/ru/sol_TranslateToInfinitive.shtml
//
// ************************************************************************
GREN_API(int) sol_TranslateToInfinitive(HGREN hEngine, int EntryID)
{
    if (EntryID == -1 || !hEngine || !HandleEngine(hEngine)->dict)
        return -1;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        const SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(EntryID);
        const int pos_id = e.GetClass();
        if (pos_id == INFINITIVE_ru || pos_id == VERB_en)
            return EntryID;

        lem::MCollect<int> key_list; // ������ ��������� �����������
        if (HandleEngine(hEngine)->dict->GetLexAuto().Translate_To_Infinitives(EntryID, key_list))
        {
            // ����� ����� ����������
            return key_list.front();
        }
    }
    CATCH_API(hEngine);

    return -1;
}



// ***************************************************************************************
//
// ����� ��������� ����� � ����� � ���������� ������ ����������� ����������.
// ��������� - ������ ��������� ������������� � ���� �������� id ��������� ������, ����.
//
// http://www.solarix.ru/api/ru/sol_ProjectWord.shtml
//
// ***************************************************************************************
GREN_API(HGREN_WCOORD) sol_ProjectWord(HGREN hEngine, const wchar_t *Word, int Allow_Dynforms)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || Word == NULL)
        return NULL;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        UCString uWord(Word);
        uWord.to_upper();

        // Look for it in dictionary
        Lexem ml(uWord);
        HandleEngine(hEngine)->dict->GetLexAuto().TranslateLexem(ml, true);

        RC_Lexem rc(&ml, null_deleter());

        MCollect<ProjScore> val_list;
        PtrCollect<LA_ProjectInfo> inf_list;


        GREN_WordCoords *res = new GREN_WordCoords;
        HandleEngine(hEngine)->dict->GetLexAuto().ProjectWord(
            rc,
            res->list,
            val_list,
            inf_list,
            Allow_Dynforms ? LexicalAutomat::Dynforms_Last_Chance : LexicalAutomat::Wordforms,
            0,
            HandleEngine(hEngine)->DefaultLanguage,
            NULL
        );

        // �������� ������ ����� ��� ������� �������� �������������.
        if (!res->list.empty())
        {
            for (lem::Container::size_type i = 0; i < res->list.size(); ++i)
            {
                CP_Array item_tags;

                const int ientry = res->list[i].GetEntry();
                // ��� ������� �������� ������������� ����� ���� �������� ���� �� id ������+id ����� �����,
                // ��� id UNK-������ � ������ ����� � ������ ����������� ����������.

                if (ientry != UNKNOWN)
                {
                    const SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(ientry);
                    item_tags = e.forms()[res->list[i].GetForm()].coords();
                }

                if (inf_list[i] != NULL && !inf_list[i]->coords.empty())
                {
                    for (lem::Container::size_type j = 0; j < inf_list[i]->coords.size(); ++j)
                    {
                        // ��������� � �������� ������ ����� ��� ��������.
                        if (item_tags.find(inf_list[i]->coords[j]) == UNKNOWN)
                        {
                            item_tags.push_back(inf_list[i]->coords[j]);
                        }
                    }
                }

                // ���������� ������������ ������ ����� ��� ������� �������� �������������.
                res->tags.push_back(item_tags);
            }

            return res;
        }

        // �� ������ �������� �������������.
        delete res;
        return NULL;
    }
    CATCH_API(hEngine)
    {
        return NULL;
    }
}


GREN_API(HGREN_WCOORD) sol_ProjectWord8(HGREN hEngine, const char *WordUtf8, int Allow_Dynforms)
{
    return sol_ProjectWord(hEngine, lem::from_utf8(WordUtf8).c_str(), Allow_Dynforms);
}



// ****************************************************************
// �������� �������� - ����������� nmissmax ������������ ��������.
// ****************************************************************
GREN_API(HGREN_WCOORD) sol_ProjectMisspelledWord(
    HGREN hEngine,
    const wchar_t *Word,
    int Allow_Dynforms,
    int nmaxmiss
)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || Word == NULL)
        return NULL;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        UCString uWord(Word);
        uWord.to_upper();

        // Look for it in dictionary
        Lexem ml(uWord);

        RC_Lexem rc(&ml, null_deleter());

        MCollect<ProjScore> val_list;
        PtrCollect<LA_ProjectInfo> inf_list;


        GREN_WordCoords *res = new GREN_WordCoords;
        HandleEngine(hEngine)->dict->GetLexAuto().ProjectWord(
            rc,
            res->list,
            val_list,
            inf_list,
            Allow_Dynforms ? LexicalAutomat::Dynforms_Last_Chance : LexicalAutomat::Wordforms,
            nmaxmiss,
            HandleEngine(hEngine)->DefaultLanguage,
            NULL
        );

        if (!res->list.empty())
        {
            for (lem::Container::size_type i = 0; i < res->list.size(); ++i)
            {
                CP_Array item_tags;

                const int ientry = res->list[i].GetEntry();

                if (ientry != UNKNOWN)
                {
                    const SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(ientry);
                    item_tags = e.forms()[res->list[i].GetForm()].coords();
                }

                if (inf_list[i] != NULL && !inf_list[i]->coords.empty())
                {
                    for (lem::Container::size_type j = 0; j < inf_list[i]->coords.size(); ++j)
                    {
                        if (item_tags.find(inf_list[i]->coords[j]) == UNKNOWN)
                        {
                            item_tags.push_back(inf_list[i]->coords[j]);
                        }
                    }
                }

                res->tags.push_back(item_tags);
            }


            return res;
        }

        delete res;

        return NULL;
    }
    CATCH_API(hEngine)
    {
        return NULL;
    }
}


GREN_API(HGREN_WCOORD) sol_ProjectMisspelledWord8(
    HGREN hEngine,
    const char *WordUtf8,
    int Allow_Dynforms,
    int nmaxmiss
)
{
    return sol_ProjectMisspelledWord(hEngine, lem::from_utf8(WordUtf8).c_str(), Allow_Dynforms, nmaxmiss);
}


// ***************************************************************************************
// ���������� ���������� ��������� (��������) � ������ hList, ������� ������� � ����������
// ������ sol_ProjectWord ��� sol_ProjectMisspelledWord.
// ***************************************************************************************
GREN_API(int) sol_CountProjections(HGREN_WCOORD hList)
{
    if (hList == NULL)
        return 0;

    return CastSizeToInt(((const Solarix::GREN_WordCoords*)hList)->list.size());
}


GREN_API(void) sol_DeleteProjections(HGREN_WCOORD hList)
{
    delete (Solarix::GREN_WordCoords*)hList;
}



// *************************************************************
// ������������ id (primary key) ��������� ������ ����� ��������
// *************************************************************
GREN_API(int) sol_GetIEntry(HGREN_WCOORD hList, int Index)
{
    if (!hList || Index < 0 || Index >= CastSizeToInt(((const Solarix::GREN_WordCoords*)hList)->list.size()))
        return -1;

    return ((const Solarix::GREN_WordCoords*)hList)->list[Index].GetEntry();
}


// **********************************************************************
// ������������ ��������� ��������������� �������� Coord � �������� Index
// **********************************************************************
GREN_API(int) sol_GetProjCoordState(
    HGREN hEngine,
    HGREN_WCOORD hList,
    int Index,
    int Coord
)
{
    if (!hList || Index < 0 || Index >= CastSizeToInt(((const Solarix::GREN_WordCoords*)hList)->list.size()))
        return -1;

    int istate = UNKNOWN;

    try
    {
        const CP_Array & tags = ((const Solarix::GREN_WordCoords*)hList)->tags[Index];
        int i = tags.FindOnce(Coord);
        if (i != UNKNOWN)
        {
            istate = tags[i].GetState();
        }
    }
    catch (...)
    {
        return UNKNOWN;
    }

    return istate;
}



GREN_API(int) sol_GetProjCoordCount(
    HGREN hEngine,
    HGREN_WCOORD hList,
    int Index
)
{
    if (!hList || Index < 0 || Index >= CastSizeToInt(((const Solarix::GREN_WordCoords*)hList)->list.size()))
        return -1;

    try
    {
        const CP_Array & tags = ((const Solarix::GREN_WordCoords*)hList)->tags[Index];
        return CastSizeToInt(tags.size());
    }
    catch (...)
    {
        return UNKNOWN;
    }
}


GREN_API(int) sol_GetProjCoordId(
    HGREN hEngine,
    HGREN_WCOORD hList,
    int ProjIndex,
    int TagIndex
)
{
    if (!hList || ProjIndex < 0 || TagIndex < 0 || ProjIndex >= CastSizeToInt(((const Solarix::GREN_WordCoords*)hList)->list.size()))
        return -1;

    try
    {
        const CP_Array & tags = ((const Solarix::GREN_WordCoords*)hList)->tags[ProjIndex];
        return tags[TagIndex].GetCoord().GetIndex();
    }
    catch (...)
    {
        return UNKNOWN;
    }
}


GREN_API(int) sol_GetProjStateId(
    HGREN hEngine,
    HGREN_WCOORD hList,
    int ProjIndex,
    int TagIndex
)
{
    if (!hList || ProjIndex < 0 || TagIndex < 0 || ProjIndex >= CastSizeToInt(((const Solarix::GREN_WordCoords*)hList)->list.size()))
        return -1;

    try
    {
        const CP_Array & tags = ((const Solarix::GREN_WordCoords*)hList)->tags[ProjIndex];
        return tags[TagIndex].GetState();
    }
    catch (...)
    {
        return UNKNOWN;
    }
}



#define SOL_GREN_ALLOW_FUZZY           0x00000002
#define SOL_GREN_COMPLETE_ONLY         0x00000004
#define SOL_GREN_PRETOKENIZED          0x00000008
#define SOL_GREN_TOKENIZE_ONLY         0x00000010
#define SOL_GREN_DISABLE_FILTERS       0x00000020
#define SOL_GREN_REORDER_TREE          0x00000400
#define SOL_GREN_MODEL                 0x00000800
#define SOL_GREN_FINDFACTS             0x00001000
#define SOL_GREN_MODEL_ONLY            0x00002000



// ****************************************************************************
// ���������� ���������������� �������.
// ****************************************************************************
GREN_API(HGREN_RESPACK) sol_MorphologyAnalysis(
    HGREN hEngine,
    const wchar_t *Sentence,
    int MorphologicalFlags,
    int SyntacticFlags,
    int Constraints,
    int LanguageID
)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || Sentence == NULL)
        return NULL;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        const bool Allow_Fuzzy = (MorphologicalFlags & SOL_GREN_ALLOW_FUZZY) == SOL_GREN_ALLOW_FUZZY;
        const bool CompleteAnalysisOnly = (MorphologicalFlags & SOL_GREN_COMPLETE_ONLY) == SOL_GREN_COMPLETE_ONLY;
        const bool Pretokenized = (MorphologicalFlags & SOL_GREN_PRETOKENIZED) == SOL_GREN_PRETOKENIZED;
        const int UseLanguageID = LanguageID == -1 ? HandleEngine(hEngine)->DefaultLanguage : LanguageID;
        const bool ApplyModel = (MorphologicalFlags & SOL_GREN_MODEL) == SOL_GREN_MODEL;

        const bool Schedule1 = (MorphologicalFlags == 0 && SyntacticFlags == 0);

        WrittenTextAnalysisSession current_analysis(HandleEngine(hEngine)->dict.get(), NULL);
        current_analysis.params.SetLanguageID(UseLanguageID);
        current_analysis.params.Pretokenized = Pretokenized;
        current_analysis.params.AllowPrimaryFuzzyWordRecog = Allow_Fuzzy;
        current_analysis.params.ApplyModel = ApplyModel;

        // ����������� �� ��������� ����������� ����� � �������������
        const int MaxMillisecTimeout = 0x002fffff & Constraints;
        current_analysis.params.timeout.max_elapsed_millisecs = MaxMillisecTimeout > 0 ? MaxMillisecTimeout : lem::int_max;

        // ����������� �� ����. ����� ����������� ����������� �������������� ����� ���������� ��������������� ������
        const int MaxAlt = ((0xffc00000 & Constraints) >> 22) & 0x000002ff;
        current_analysis.params.timeout.max_alt = MaxAlt;

        if (!CompleteAnalysisOnly)
        {
            current_analysis.params.CompleteAnalysisOnly = false;
            current_analysis.params.ConfigureSkipToken();
        }

        if (Schedule1)
        {
            current_analysis.params.UseTopDownThenSparse = true;
            current_analysis.params.CompleteAnalysisOnly = true;
        }
        else
        {
            current_analysis.params.CompleteAnalysisOnly = CompleteAnalysisOnly;
        }

        if ((MorphologicalFlags&SOL_GREN_TOKENIZE_ONLY) == SOL_GREN_TOKENIZE_ONLY)
        {
            // ��������� ������ �����������.
            current_analysis.Tokenize(Sentence);
        }
        else if ((MorphologicalFlags&SOL_GREN_MODEL_ONLY) == SOL_GREN_MODEL_ONLY)
        {
            // ��������� ������������� ������ ���������� ��� ������ ����������������, �� ������� �� ���������.
            current_analysis.ApplyFilters(Sentence);
        }
        else
        {
            current_analysis.MorphologicalAnalysis(Sentence);
        }

        return current_analysis.PickPack();
    }
    CATCH_API(hEngine)
    {
        return NULL;
    }

    return NULL;
}


GREN_API(HGREN_RESPACK) sol_MorphologyAnalysis8(
    HGREN hEngine,
    const char *SentenceUtf8,
    int Flags,
    int UnusedFlags,
    int Constraints,
    int LanguageID
)
{
    return sol_MorphologyAnalysis(
        hEngine,
        lem::from_utf8(SentenceUtf8).c_str(),
        Flags,
        UnusedFlags,
        Constraints,
        LanguageID
    );
}


GREN_API(HGREN_RESPACK) sol_MorphologyAnalysisA(
    HGREN hEngine,
    const char *Sentence,
    int Flags,
    int UnusedFlags,
    int Constraints,
    int LanguageID
)
{
    return sol_MorphologyAnalysis(
        hEngine,
        lem::to_unicode(Sentence).c_str(),
        Flags,
        UnusedFlags,
        Constraints,
        LanguageID
    );
}




static void collect_nodes(const Solarix::Tree_Node & node, std::vector< std::pair<int, const lem::UCString*> > & result)
{
    result.push_back(std::make_pair(node.GetNode().GetOriginPos(), &*node.GetNode().GetName()));
    for (int i = 0; i < node.leafs().size(); ++i)
    {
        collect_nodes(node.leafs()[i], result);
    }

    return;
}





static lem::UFString NormalizePhrase(HGREN hEngine, HGREN_RESPACK hLinkages)
{
    Solarix::Res_Pack * linkages = (Solarix::Res_Pack*)hLinkages;

    if (!linkages->vars().empty())
    {
        const Variator * linkage = linkages->vars().front();
        const Tree_Node * root = linkage->roots_list()[1];

        Solarix::Dictionary & dict = *HandleEngine(hEngine)->dict;

        lem::UCString func_name = lem::UCString(L"normalize_phrase_") + dict.GetSynGram().languages()[dict.GetDefaultLanguage()].GetName();
        if (dict.GetLexAuto().GetFunctions().Get().IsFunction(func_name))
        {
            const TrFunction * func = dict.GetLexAuto().GetFunctions().Get().Find(func_name);

            TrFunContext ctx0((TrFunContext*)NULL);
            TrContextInvokation ctx2(&ctx0);
            ctx2.AddVar(L"((return))", lem::Ptr<TrValue>(new TrTypeValue(TrTreeType())));

            lem::Ptr<TrValue> v(new TrValue(root, false));
            ctx2.AddVar(func->arg_name[0], v);

            ElapsedTimeConstraint null_constraints(100000, 10000);
            func->GetBody().Run(null_constraints, dict.GetLexAuto(), ctx2, NULL);

            lem::Ptr<TrValue> func_ret(ctx2.GetVar(L"((return))"));

            LEM_CHECKIT_Z(func_ret->GetType().IsTree());
            Solarix::Tree_Node & new_tree = func_ret->GetTree();

            typedef std::pair<int, const lem::UCString*> WORD_POS;
            std::vector< WORD_POS > nodes;
            collect_nodes(new_tree, nodes);

            std::sort(nodes.begin(), nodes.end(), boost::bind(&std::pair<int, const lem::UCString*>::first, _1) < boost::bind(&std::pair<int, const lem::UCString*>::first, _2));

            lem::MemFormatter mem;
            for (std::vector< WORD_POS >::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
            {
                mem.printf("%us ", it->second->c_str());
            }

            return lem::trim(mem.string());
        }
    }

    return L"";
}


GREN_API(wchar_t*) sol_NormalizePhraseW(
    HGREN hEngine,
    HGREN_RESPACK hLinkages
)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || hLinkages == NULL)
        return NULL;

    DEMO_SINGLE_THREAD(hEngine)

        lem::UFString res_string = NormalizePhrase(hEngine, hLinkages);

    wchar_t * w = (wchar_t*)malloc(sizeof(wchar_t)*(res_string.length() + 1));
    lem::lem_strcpy(w, res_string.c_str());
    return w;
}

GREN_API(char*) sol_NormalizePhrase8(HGREN hEngine, HGREN_RESPACK hLinkages)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || hLinkages == NULL)
        return NULL;

    DEMO_SINGLE_THREAD(hEngine)

        lem::FString res_utf8 = lem::to_utf8(NormalizePhrase(hEngine, hLinkages));

    char * w = (char*)malloc(res_utf8.length() + 1);
    lem::lem_strcpy(w, res_utf8.c_str());
    return w;
}



// ****************************************************************************
// ���������� ��������������� ������� - �� ����� �����, �� ������ ����������
// ������, �������� �������������� �������� ���������� ��������������� �����.
// ****************************************************************************
GREN_API(HGREN_RESPACK) sol_SyntaxAnalysis(
    HGREN hEngine,
    const wchar_t *Sentence,
    int MorphologicalFlags,
    int SyntacticFlags,
    int Constraints,
    int LanguageID
)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || Sentence == NULL)
        return NULL;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        const bool Allow_Fuzzy = (MorphologicalFlags & SOL_GREN_ALLOW_FUZZY) == SOL_GREN_ALLOW_FUZZY;
        const bool CompleteAnalysisOnly = (MorphologicalFlags & SOL_GREN_COMPLETE_ONLY) == SOL_GREN_COMPLETE_ONLY;
        const bool Pretokenized = (MorphologicalFlags & SOL_GREN_PRETOKENIZED) == SOL_GREN_PRETOKENIZED;
        const int UseLanguageID = LanguageID == -1 ? HandleEngine(hEngine)->DefaultLanguage : LanguageID;
        const bool ApplyModel = (MorphologicalFlags & SOL_GREN_MODEL) == SOL_GREN_MODEL;

        const bool ReorderTree = (SyntacticFlags&SOL_GREN_REORDER_TREE) == SOL_GREN_REORDER_TREE;
        const bool FindFacts = (SyntacticFlags&SOL_GREN_FINDFACTS) == SOL_GREN_FINDFACTS;
        const bool Schedule1 = (SyntacticFlags & ~SOL_GREN_REORDER_TREE) == 0;

        WrittenTextAnalysisSession current_analysis(HandleEngine(hEngine)->dict.get(), NULL);
        current_analysis.params.SetLanguageID(UseLanguageID);

        current_analysis.params.Pretokenized = Pretokenized;
        current_analysis.params.AllowPrimaryFuzzyWordRecog = Allow_Fuzzy;
        current_analysis.params.ApplyModel = ApplyModel;

        // ����������� �� ��������� ����������� ����� � �������������
        const int MaxMillisecTimeout = 0x002fffff & Constraints;
        //lem::mout->printf( "Constraints=%d MaxMillisecTimeout=%d\n", Constraints, MaxMillisecTimeout );
        current_analysis.params.timeout.max_elapsed_millisecs = MaxMillisecTimeout > 0 ? MaxMillisecTimeout : lem::int_max;

        // ����������� �� ����. ����� ����������� ����������� �������������� ����� ���������� ��������������� ������.
        // ��� �������� � ������� 10 �����
        const int MaxAlt = ((0xffC00000 & Constraints) >> 22) & 0x000002ff;
        current_analysis.params.timeout.max_alt = MaxAlt;
        current_analysis.params.timeout.max_bottomup_trees = MaxAlt;
        current_analysis.params.timeout.max_recursion_depth = 500;

        if ( /*(SyntacticFlags & SOL_GREN_SKIPTOKENS)==SOL_GREN_SKIPTOKENS &&*/ !CompleteAnalysisOnly)
        {
            current_analysis.params.CompleteAnalysisOnly = false;
            current_analysis.params.ConfigureSkipToken();
        }

        if (Schedule1)
        {
            current_analysis.params.UseTopDownThenSparse = true;
            current_analysis.params.CompleteAnalysisOnly = true;
        }
        else
        {
            current_analysis.params.CompleteAnalysisOnly = CompleteAnalysisOnly;
        }

        current_analysis.params.ReorderTree = ReorderTree;
        current_analysis.FindFacts = FindFacts;

        current_analysis.SyntacticAnalysis(Sentence);

        return current_analysis.PickPack();
    }
    CATCH_API(hEngine)
    {
        return NULL;
    }

    return NULL;
}



GREN_API(HGREN_RESPACK) sol_SyntaxAnalysis8(
    HGREN hEngine,
    const char *SentenceUtf8,
    int MorphologicalFlags,
    int SyntacticFlags,
    int Constraints,
    int LanguageID
)
{
    return sol_SyntaxAnalysis(
        hEngine,
        lem::from_utf8(SentenceUtf8).c_str(),
        MorphologicalFlags,
        SyntacticFlags,
        Constraints,
        LanguageID
    );
}

GREN_API(HGREN_RESPACK) sol_SyntaxAnalysisA(
    HGREN hEngine,
    const char *Sentence,
    int MorphologicalFlags,
    int SyntacticFlags,
    int Constraints,
    int LanguageID
)
{
    return sol_SyntaxAnalysis(
        hEngine,
        lem::to_unicode(Sentence).c_str(),
        MorphologicalFlags,
        SyntacticFlags,
        Constraints,
        LanguageID
    );
}


GREN_API(void) sol_DeleteResPack(HGREN_RESPACK hPack)
{
    try
    {
#if !defined SOL_NO_AA
        delete (Solarix::Res_Pack*)hPack;
#endif
    }
    catch (...)
    {
    }
}


// *************************************************************
// ���������� "���" ��������� ������ - ������ ��� ������� �����,
// �� ����� ���� ������ ������ (��������, ������ ���� - ������
// � ���� - �������)
//
// http://www.solarix.ru/api/en/sol_GetEntryName.shtml
// http://www.solarix.ru/api/ru/sol_GetEntryName.shtml
// *************************************************************
GREN_API(int) sol_GetEntryName(
    HGREN h,
    int EntryIndex,
    wchar_t *Result
)
{
    if (!h || EntryIndex == -1 || Result == NULL)
        return -2;

    *Result = 0;

    DEMO_SINGLE_THREAD(h)

        try
    {
        const SG_Entry &e = HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex);

        lem::UFString w(e.GetName().c_str());

        const int icasing = e.GetAttrState(GramCoordAdr(CharCasing));

        switch (icasing)
        {
        case UNKNOWN:
        case DECAPITALIZED_CASED:
        {
            w.to_lower();
            break;
        }

        case FIRST_CAPITALIZED_CASED:
        {
            w.to_Aa();
            break;
        }

        case ALL_CAPITALIZED_CASED:
        {
            w.to_upper();
            break;
        }

        case EACH_LEXEM_CAPITALIZED_CASED:
        {
            Solarix::MakeEachLexemAa(w);
            break;
        }
        }

        w.subst_all(L" - ", L"-");
        w.subst_all(L" ' ", L"'");

        lem::lem_strcpy(Result, w.c_str());

        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


GREN_API(int) sol_GetEntryName8(HGREN h, int EntryIndex, char *Result)
{
    try
    {
        wchar_t buf[lem::UCString::max_len + 1];
        *buf = 0;
        int rc = sol_GetEntryName(h, EntryIndex, buf);
        lem::FString u8 = lem::to_utf8(buf);
        lem::lem_strcpy(Result, u8.c_str());
        return rc;
    }
    catch (...)
    {
        return -1;
    }
}



// ���������� ������ ��������������� ������, � �������� ���������
// ��������� ������.
// http://www.solarix.ru/api/en/sol_GetEntryClass.shtml
// http://www.solarix.ru/api/ru/sol_GetEntryClass.shtml
GREN_API(int) sol_GetEntryClass(HGREN h, int EntryIndex)
{
    if (!h || !HandleEngine(h)->dict || EntryIndex == -1)
        return -2;

    try
    {
        return HandleEngine(h)->dict->GetSynGram().GetEntry(EntryIndex).GetClass();
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// http://www.solarix.ru/api/en/sol_GetEntryCoordState.shtml
GREN_API(int) sol_GetEntryCoordState(HGREN hEngine, int EntryID, int CategoryID)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || CategoryID == -1 || EntryID == -1)
        return -2;

    try
    {
        const Solarix::SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(EntryID);
        const int state = e.GetAttrState(GramCoordAdr(CategoryID));
        return state;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// � ��������� ������� ������ ����� ����� ��������� ��������� ����� ����������. ��������,
// �������� ����������� ������� �������� �������� �����������, ��������� � ������������ ������.
// ������ ��������� ��������� ������, ������������ �� ������������ ���� ����� ���������.
// http://www.solarix.ru/api/ru/sol_FindEntryCoordPair.shtml
GREN_API(int) sol_FindEntryCoordPair(HGREN hEngine, int EntryID, int CategoryID, int StateID)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || EntryID == -1 || CategoryID == -1 || StateID == -1)
        return -2;

    try
    {
        const Solarix::SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(EntryID);
        return e.attrs().FindOnce(Solarix::GramCoordPair(CategoryID, StateID)) != -1;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}




// **********************************************************************************
// ���������� ��� ��������������� ������ (����� ����) �� ��� ID
// http://www.solarix.ru/api/en/sol_GetClassName.shtml
// http://www.solarix.ru/api/ru/sol_GetClassName.shtml
//
// ���������: 0   ��� ������ ���� ����������� � Result
//            -1  ������, �������� ������ ������������ ClassIndex
// **********************************************************************************
GREN_API(int) sol_GetClassName(HGREN hEngine, int ClassID, wchar_t *Result)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || ClassID == -1)
        return -2;

    *Result = 0;

    try
    {
        const Solarix::GramClass &c = HandleEngine(hEngine)->dict->GetSynGram().classes()[ClassID];
        wcscpy(Result, c.GetName().c_str());
        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// http://www.solarix.ru/api/en/sol_GetClassName.shtml
GREN_API(int) sol_GetClassName8(HGREN h, int ClassID, char *ResultUtf8)
{
    if (!h || !HandleEngine(h)->dict || ClassID == -1)
        return -2;

    *ResultUtf8 = 0;

    try
    {
        const Solarix::GramClass &c = HandleEngine(h)->dict->GetSynGram().classes()[ClassID];
        strcpy(ResultUtf8, lem::to_utf8(c.GetName().c_str()).c_str());
        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// http://www.solarix.ru/api/en/sol_GetCoordName.shtml
GREN_API(int) sol_GetCoordName(HGREN hEngine, int CoordID, wchar_t *Result)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || CoordID == -1)
        return -2;

    *Result = 0;

    try
    {
        const Solarix::GramCoord & c = HandleEngine(hEngine)->dict->GetSynGram().coords()[CoordID];
        wcscpy(Result, c.GetName().string().c_str());
        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}




// http://www.solarix.ru/api/en/sol_GetCoordType.shtml
// http://www.solarix.ru/api/ru/sol_GetCoordType.shtml
GREN_API(int) sol_GetCoordType(HGREN hEngine, int CoordId, int ClassId)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || CoordId == -1 || ClassId == -1)
        return -2;

    try
    {
        const Solarix::SG_Class &cls = HandleEngine(hEngine)->dict->GetSynGram().GetClass(ClassId);

        if (cls.attrs().find(CoordId) != UNKNOWN)
            return 0;

        if (cls.dims().find(CoordId) != UNKNOWN)
            return 1;

        if (cls.tags().find(CoordId) != UNKNOWN)
            return 2;

        return UNKNOWN;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}



// http://www.solarix.ru/api/en/sol_GetCoordName.shtml
GREN_API(int) sol_GetCoordName8(HGREN hEngine, int CoordID, char *ResultUtf8)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || CoordID == -1)
        return -2;

    *ResultUtf8 = 0;

    try
    {
        const Solarix::GramCoord & c = HandleEngine(hEngine)->dict->GetSynGram().coords()[CoordID];
        strcpy(ResultUtf8, lem::to_utf8(c.GetName().string().c_str()).c_str());
        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// Return: name of the grammatical coordinate state
// http://www.solarix.ru/api/en/sol_GetCoordStateName.shtml
GREN_API(int) sol_GetCoordStateName(HGREN hEngine, int CoordID, int StateID, wchar_t *Result)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || CoordID == -1)
        return -2;

    *Result = 0;

    try
    {
        const Solarix::GramCoord & c = HandleEngine(hEngine)->dict->GetSynGram().coords()[CoordID];

        if (!c.IsBistable())
            wcscpy(Result, c.GetStateName(StateID).c_str());

        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// http://www.solarix.ru/api/en/sol_GetCoordStateName.shtml
GREN_API(int) sol_GetCoordStateName8(HGREN hEngine, int CoordID, int StateID, char *ResultUtf8)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || CoordID == -1)
        return -2;

    *ResultUtf8 = 0;

    try
    {
        const Solarix::GramCoord & c = HandleEngine(hEngine)->dict->GetSynGram().coords()[CoordID];

        if (!c.IsBistable())
            strcpy(ResultUtf8, lem::to_utf8(c.GetStateName(StateID).c_str()).c_str());

        return 0;
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// Return the number of enumeration items (coordinate states).
// It returns 0 for bistable coordinates without explicit states
// http://www.solarix.ru/api/en/sol_CountCoordStates.shtml
GREN_API(int) sol_CountCoordStates(HGREN hEngine, int CoordID)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || CoordID == -1)
        return -2;

    try
    {
        const Solarix::GramCoord & c = HandleEngine(hEngine)->dict->GetSynGram().coords()[CoordID];

        return c.GetTotalStates();
    }
    catch (...)
    {
    }

    return UNKNOWN;
}


// ***************************************************
// ������� �������������� ��������� ������� �����?  
// ***************************************************
GREN_API(int) sol_CountGrafs(HGREN_RESPACK hPack)
{
#if !defined SOL_NO_AA
    if (hPack == NULL)
        return 0;

    return CastSizeToInt(((Res_Pack*)hPack)->vars().size());
#else
    return 0;
#endif
}


// *************************************************************
// ������� �������� (����� �������� ������) � �������� �����?
// *************************************************************
GREN_API(int) sol_CountRoots(HGREN_RESPACK hPack, int iGraf)
{
    try
    {
#if !defined SOL_NO_AA
        if (hPack == NULL)
            return 0;

        if (iGraf < 0 || iGraf >= CastSizeToInt(((Res_Pack*)hPack)->vars().size()))
            return -1;

        return ((Res_Pack*)hPack)->vars()[iGraf]->size();
#else
        return 0;
#endif
    }
    catch (...)
    {
        return -1;
}
}


// *****************************************************
// ��������� ��������� �� �������� ���� �������� ������ 
// *****************************************************
GREN_API(HGREN_TREENODE) sol_GetRoot(HGREN_RESPACK hPack, int iGraf, int iRoot)
{
#if !defined SOL_NO_AA
    if (hPack == NULL)
        return NULL;

    try
    {
        return &(((Res_Pack*)hPack)->vars()[iGraf]->get(iRoot));
    }
    catch (...)
    {
        return NULL;
    }
#else
    return NULL;
#endif
}


// *****************************************************
// ���������� ������������� � ������� ���� �����
// *****************************************************
GREN_API(int) sol_CountLeafs(HGREN_TREENODE hNode)
{
#if !defined SOL_NO_AA
    if (hNode == NULL)
        return 0;

    return CastSizeToInt(HandleNode(hNode)->leafs().size());
#else
    return 0;
#endif
}


// *****************************************************
// ���������� ��������� �� �������� �����
// http://www.solarix.ru/api/ru/sol_GetLeaf.shtml
// *****************************************************
GREN_API(HGREN_TREENODE) sol_GetLeaf(HGREN_TREENODE hNode, int iLeaf)
{
#if !defined SOL_NO_AA
    if (hNode == NULL)
        return 0;

    try
    {
        return &HandleNode(hNode)->leafs()[iLeaf];
    }
    catch (...)
    {
        return NULL;
    }

#else
    return NULL;
#endif
}



// http://www.solarix.ru/api/ru/sol_GetLeafLinkType.shtml
GREN_API(int) sol_GetLeafLinkType(HGREN_TREENODE hNode, int iLeaf)
{
#if !defined SOL_NO_AA
    if (hNode == NULL)
        return 0;

    try
    {
        return HandleNode(hNode)->leafs()[iLeaf].GetLink().GetState();
    }
    catch (...)
    {
        return -2;
    }
#else
    return UNKNOWN;
#endif
}



// *****************************************************
// ���������� ������ ��������� ������ � ����.
// *****************************************************
GREN_API(int) sol_GetNodeIEntry(HGREN hEngine, HGREN_TREENODE hNode)
{
    if (hEngine == NULL || HandleEngine(hEngine)->dict == NULL)
        return UNKNOWN;

#if !defined SOL_NO_AA
    if (hNode == NULL)
        return 0;

    int ekey = HandleNode(hNode)->GetNode().GetEntryKey();
    return ekey;//HandleEngine(hEngine)->dict->GetSynGram().FindEntryIndexByKey(ekey);
#else
    return UNKNOWN;
#endif  
}


GREN_API(int) sol_GetNodeVerIEntry(HGREN hEngine, HGREN_TREENODE hNode, int iver)
{
    if (hEngine == NULL || HandleEngine(hEngine)->dict == NULL)
        return UNKNOWN;

#if !defined SOL_NO_AA
    if (hNode == NULL)
        return 0;

    int ekey = UNKNOWN;
    if (iver == 0)
        ekey = HandleNode(hNode)->GetNode().GetEntryKey();
    else
        ekey = HandleNode(hNode)->GetNode().GetAlts()[iver - 1]->GetEntryKey();

    return ekey;//HandleEngine(hEngine)->dict->GetSynGram().FindEntryIndexByKey(ekey);
#else
    return UNKNOWN;
#endif  
}


GREN_API(int) sol_GetNodeVersionCount(HGREN hEngine, HGREN_TREENODE hNode)
{
#if !defined SOL_NO_AA
    if (hNode == NULL)
        return 0;

    return CastSizeToInt(HandleNode(hNode)->GetNode().GetAlts().size()) + 1;
#else
    return 0;
#endif  
}


GREN_API(int) sol_GetNodePosition(HGREN_TREENODE hNode)
{
    if (hNode == NULL)
        return -1;

#if !defined SOL_NO_AA
    const Word_Form &wf = HandleNode(hNode)->GetNode();
    return wf.GetOriginPos();
#else
    return -1;
#endif
}



GREN_API(int) sol_CountNodeMarks(HGREN_TREENODE hNode)
{
    if (hNode == NULL)
        return -1;

    try
    {
        return CastSizeToInt(HandleNode(hNode)->GetMarks().size());
    }
    catch (...)
    {
        return -1;
    }
}


GREN_API(int) sol_GetNodeMarkNameW(HGREN_TREENODE hNode, int mark_index, wchar_t * name_buffer)
{
    if (hNode == NULL)
        return -1;

    try
    {
        *name_buffer = 0;
        wcscpy(name_buffer, HandleNode(hNode)->GetMarks()[mark_index]->GetName().c_str());
        return 0;
    }
    catch (...)
    {
        return -1;
    }
}

GREN_API(HGREN_LONGSTRING) sol_SerializeNodeMark(HGREN hEngine, HGREN_TREENODE hNode, int mark_index, int format)
{
    if (hNode == NULL)
        return NULL;

    try
    {
        const TreeMarks & marks = *HandleNode(hNode)->GetMarks()[mark_index];
        lem::MemFormatter mem;
        marks.PrintXML(mem, *HandleEngine(hEngine)->dict);
        lem::UFString * str = new lem::UFString(mem.string());
        return str;
    }
    catch (...)
    {
        return NULL;
    }
}

GREN_API(int) sol_GetLongStringLenW(HGREN_LONGSTRING hString)
{
    if (hString == NULL)
        return 0;

    try
    {
        return ((const lem::UFString*)hString)->length();
    }
    catch (...)
    {
        return -1;
    }
}


GREN_API(int) sol_GetLongStringW(HGREN_LONGSTRING hString, wchar_t * buffer)
{
    if (hString == NULL)
        return 0;

    try
    {
        const lem::UFString & str = *(const lem::UFString*)hString;
        if (str.empty())
            *buffer = 0;
        else
            wcscpy(buffer, str.c_str());

        return str.length();
    }
    catch (...)
    {
        return -1;
    }
}

GREN_API(int) sol_DeleteLongString(HGREN_LONGSTRING hString)
{
    try
    {
        delete (lem::UFString*)hString;
        return 0;
    }
    catch (...)
    {
        return -1;
    }
}



// *****************************************************
// ��������� ���������� ����.
//
// *****************************************************
GREN_API(void) sol_GetNodeContents(HGREN_TREENODE hNode, wchar_t *Buffer)
{
    if (Buffer == NULL)
        return;

    try
    {
        *Buffer = 0;

#if !defined SOL_NO_AA
        if (hNode == NULL)
            return;

        const Word_Form &wf = HandleNode(hNode)->GetNode();
        UCString s = wf.GetName()->ToWord();
        wcscpy(Buffer, s.c_str());
#endif
    }
    catch (...)
    {
    }

    return;
}


GREN_API(void) sol_GetNodeContents8(HGREN_TREENODE hNode, char *BufferUtf8)
{
    if (BufferUtf8 == NULL)
        return;

    try
    {
        *BufferUtf8 = 0;

#if !defined SOL_NO_AA
        if (hNode == NULL)
            return;

        const Word_Form &wf = HandleNode(hNode)->GetNode();
        UCString s = wf.GetName()->ToWord();
        strcpy(BufferUtf8, lem::to_utf8(s.c_str()).c_str());
#endif
    }
    catch (...)
    {
    }

    return;
}



GREN_API(int) sol_GetNodeContentsLen(HGREN_TREENODE hNode)
{
    try
    {
#if !defined SOL_NO_AA
        if (hNode == NULL)
            return -1;

        const int len = HandleNode(hNode)->GetNode().GetName()->ToWord().length();
        return len;
#endif
    }
    catch (...)
    {
    }

    return -1;
}




GREN_API(int) sol_RestoreCasing(HGREN hEngine, wchar_t *Word, int EntryIndex)
{
    if (!hEngine || EntryIndex == -1 || lem::lem_is_empty(Word))
        return -2;

    try
    {
        lem::UFString w(Word);
        CasingCoder& cc = HandleEngine(hEngine)->dict->GetLexAuto().GetCasingCoder();
        cc.RestoreCasing(w, EntryIndex);

        w.subst_all(L" - ", L"-");
        w.subst_all(L" ' ", L"'");

        lem::lem_strcpy(Word, w.c_str());

        return 0;
    }
    CATCH_API(hEngine);

    return 3;
}

GREN_API(int) sol_RestoreCasing8(HGREN hEngine, char *WordUtf8, int EntryIndex)
{
    if (WordUtf8 == NULL || EntryIndex == UNKNOWN)
        return -1;

    wchar_t buf[lem::UCString::max_len + 1];
    lem::lem_strcpy(buf, lem::from_utf8(WordUtf8).c_str());
    int rc = sol_RestoreCasing(hEngine, buf, EntryIndex);
    if (rc == 0)
    {
        strcpy(WordUtf8, lem::to_utf8(buf).c_str());
    }

    return rc;
}



// ***********************************************************************
// ���������� � ������� �����. ������ 1, ���� �������������� ����� �����.
//
// �������� AllowDynforms ��������� �������� ������� ����������.
// ***********************************************************************
GREN_API(int) sol_TranslateToBase(HGREN hEngine, wchar_t *Word, int AllowDynforms)
{
    if (hEngine == NULL || HandleEngine(hEngine)->dict == NULL || Word == NULL)
        return UNKNOWN;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        // ������� ����� ����������.
        UCString w(Word);

        int ientry = UNKNOWN;
        if (HandleEngine(hEngine)->seeker == NULL)
        {
            MCollect<Word_Coord> found_list;
            HandleEngine(hEngine)->dict->GetLexAuto().ProjectWord(w, found_list, UNKNOWN);
            if (!found_list.empty())
                ientry = found_list.front().GetEntry();
        }
        else
        {
            w.to_upper();
            ientry = HandleEngine(hEngine)->seeker->Find(w, AllowDynforms == 1);
        }

        if (ientry == UNKNOWN)
            return 0;

        // ���� ������ ��������� ������, ����� ������������� � �������� ������.
        const SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(ientry);
        wcscpy(Word, e.GetName().c_str());
        sol_RestoreCasing(hEngine, Word, e.GetKey());
        return 1;
    }
    CATCH_API(hEngine)

        return UNKNOWN;
}


// *****************************************************************
// ���������� ������ ������� ���� ��� �����. 
// *****************************************************************
GREN_API(HGREN_STR) sol_TranslateToBases(
    HGREN hEngine,
    const wchar_t *Word,
    int AllowDynforms
)
{
    if (!hEngine || !HandleEngine(hEngine)->dict || Word == NULL)
        return NULL;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        UCString uWord(Word);
        uWord.to_upper();

        // Look for it in dictionary
        Lexem ml(uWord);

        RC_Lexem rc(&ml, null_deleter());

        lem::MCollect<ProjScore> val_list;
        lem::MCollect<Solarix::Word_Coord> coords;
        PtrCollect<LA_ProjectInfo> inf_list;

        HandleEngine(hEngine)->dict->GetLexAuto().ProjectWord(
            rc,
            coords,
            val_list,
            inf_list,
            AllowDynforms ? LexicalAutomat::Dynforms_Last_Chance : LexicalAutomat::Wordforms,
            0,
            HandleEngine(hEngine)->DefaultLanguage,
            NULL
        );

        if (coords.empty())
            return NULL;

        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        GREN_Strings *res = new GREN_Strings;

        wchar_t buf[lem::UCString::max_len + 1];

        for (lem::Container::size_type i = 0; i < coords.size(); i++)
        {
            const int ekey = coords[i].GetEntry();
            const SG_Entry &e = sg.GetEntry(ekey);
            if (!e.IsQuantor())
            {
                const UCString &s = e.GetName();
                lem::lem_strcpy(buf, s.c_str());
                sol_RestoreCasing(hEngine, buf, ekey);
                lem::UCString u(buf);

                if (res->list.find(u) == UNKNOWN)
                    res->list.push_back(u);
            }
        }

        if (res->list.empty())
        {
            res->list.push_back(lem::UCString(Word));
        }

        return res;
    }
    CATCH_API(hEngine)

        return NULL;
}

// *****************************************************************************
// ������� - ���������� ����� �������� � �����, ������� ���������� 
// "������", ���������� ��� ���� ���� ����� �����. � ������ �������������
// �������� ������, ������ 0.
// *****************************************************************************
GREN_API(int) sol_Stemmer(HGREN hEngine, const wchar_t *Word)
{
#if defined GM_STEMMER
    if (!hEngine || !HandleEngine(hEngine)->dict || Word == NULL)
        return -1;

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        // ������� ����� ���������� �� ���������
        UCString w(Word);
        int ientry = HandleEngine(hEngine)->seeker == NULL ? UNKNOWN : HandleEngine(hEngine)->seeker->Find(w, true);
        if (ientry == UNKNOWN)
        {
            // ��� ����� ����������� � ���������.
            // ��������� ��������� ��������� ������� ��������.

            LEM_CHECKIT_Z(HandleEngine(hEngine)->fuzzy != NULL);

            if (HandleEngine(hEngine)->fuzzy == NULL)
                // ����������� ������ ������.
                return -1;

            lem::MCollect<UCString> roots;
            lem::MCollect<float> roots_val;

            HandleEngine(hEngine)->fuzzy->GetAffixTable().GenerateRoots(w, 0.0, roots, roots_val);

            if (!roots.empty())
            {
                // ������ ������, ��� ���� ����� - ���������� ����� ������� ������ ��� ����� ��������.
                int best_len = roots.front().length();

                for (lem::Container::size_type j = 1; j < roots.size(); j++)
                {
                    best_len = std::min(best_len, roots[j].length());
                }

                return best_len;
            }

            if (!!HandleEngine(hEngine)->dict->stemmer)
            {
                // ��������� ������������ ����������� �������.
                UCString stem;
                if (HandleEngine(hEngine)->dict->stemmer->Stem(w, stem))
                    return stem.length();
            }

            return 0;
        }
        else
        {
            // ��� ��� ��������� ������ �������, �� ���������� ��������� ��� ��� ������.
            return HandleEngine(hEngine)->dict->GetSynGram().GetEntry(ientry).GetRoot().length();
        }

        return 0;
    }
    CATCH_API(hEngine)

        return -2;

#else
    return -1;
#endif
}



// **********************************************************
// ����� � ��������� ��������� ������ ��� ��������� iEntry.
// ������������ ������ �������� ������.
// **********************************************************
GREN_API(HGREN_INTARRAY) sol_SeekThesaurus(
    HGREN hEngine,
    int iEntry,
    int Synonyms,
    int Grammar_Links,
    int Translations,
    int Semantics,
    int nJumps
)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict)
        return NULL;

#if defined GM_THESAURUS
    lem::MCollect<int> *list = new lem::MCollect<int>();
    list->reserve(32);

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        HandleEngine(hEngine)->dict->GetLexAuto().SeekThesaurus(HandleEngine(hEngine)->dict->GetSynGram().GetEntry(iEntry).GetKey(), Synonyms == 1, Grammar_Links == 1, Translations == 1, Semantics == 1, nJumps, *list);

        for (lem::Container::size_type i = 0; i < list->size(); ++i)
        {
#if LEM_DEBUGGING==1
            int key = list->get(i);
            int ie = key;
#endif
            (*list)[i] = list->get(i);
        }

        return list;
        }
    CATCH_API(hEngine)

        delete list;
    return NULL;
#endif

    return NULL;
    }


GREN_API(HGREN_INTARRAY) sol_Thesaurus(
    HGREN hEngine,
    int iEntry,
    int Link
)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || iEntry == UNKNOWN || Link == UNKNOWN)
        return NULL;

#if defined SOLARIX_PRO && defined GM_THESAURUS
    lem::MCollect<int> *list = new lem::MCollect<int>();
    list->reserve(32);

    try
    {
        const int ekey = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(iEntry).GetKey();

        Tree_Link l(Link);

        IntCollect links;
        HandleEngine(hEngine)->dict->GetSynGram().Get_Net().Find_Linked_Entries(ekey, l, links, NULL);

        for (lem::Container::size_type i = 0; i < links.size(); ++i)
        {
            const int key = links[i];
            list->push_back(key);
        }

        return list;
    }
    catch (...)
    {
        delete list;
        return NULL;
    }
#endif

    return NULL;
}


// ***********************************************************************
// http://www.solarix.ru/for_developers/api/ngrams-api.shtml
//
// ������������ ���������� N-����� ��������� ������� (Order=1...5) �
// ���� (0-����������,1-���������������).
//
// ��� ��� ������� ����� ����>4 ����, �� 64-������ ��������� ������������
// � ���� ���� 32-������ ������.
//
// ������������ ��������: 1 - �����, 0 - ��� ������� ��� �����-�� ������.
// ************************************************************************
GREN_API(int) sol_CountNGrams(HGREN hEngine, int type, int Order, unsigned int *Hi, unsigned int *Lo)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || type < 0 || type>1 || Order < 1 || Order>5 || Hi == NULL || Lo == NULL)
        return 0;

#if !defined SOL_NO_NGRAMS

    try
    {
        *Hi = *Lo = 0;

        lem::Ptr<Ngrams> ngrams = HandleEngine(hEngine)->dict->GetNgrams();

        if (ngrams.NotNull())
        {
            lem::int64_t c = 0;

            switch (Order)
            {
            case 1: c = type == 1 ? ngrams->CountRaw1() : ngrams->CountLiteral1(); break;
            case 2: c = type == 1 ? ngrams->CountRaw2() : ngrams->CountLiteral2(); break;
            case 3: c = type == 1 ? ngrams->CountRaw3() : ngrams->CountLiteral3(); break;
            case 4: c = type == 1 ? ngrams->CountRaw4() : ngrams->CountLiteral4(); break;
            case 5: c = type == 1 ? ngrams->CountRaw5() : ngrams->CountLiteral5(); break;
            }

            *Hi = (lem::uint32_t)(c >> 32);
            *Lo = (lem::uint32_t)(c);

            return c > 0;
        }

        return 0;
    }
    catch (...)
    {
        return 0;
    }
#endif

    return 0;
}


// http://www.solarix.ru/for_developers/api/ngrams-api.shtml
GREN_API(int) sol_Seek1Grams(HGREN hEngine, int type, const wchar_t *word1)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || word1 == NULL)
        return 0;

#if !defined SOL_NO_NGRAMS

    try
    {
        lem::Ptr<Ngrams> ngrams = HandleEngine(hEngine)->dict->GetNgrams();

        if (ngrams.NotNull())
        {
            float wf = 0;
            int iw = 0;

            if (ngrams->FindNGrams(type == 1, word1, wf, iw))
                return iw;

            return 0;
        }

        return 0;
    }
    catch (...)
    {
        return 0;
    }
#endif

    return 0;
}

GREN_API(int) sol_Seek1Grams8(HGREN hEngine, int type, const char *Word1Utf8)
{
    return sol_Seek1Grams(hEngine, type, lem::from_utf8(Word1Utf8).c_str());
}


// http://www.solarix.ru/for_developers/api/ngrams-api.shtml
GREN_API(int) sol_Seek2Grams(
    HGREN hEngine,
    int type,
    const wchar_t *word1,
    const wchar_t *word2
)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || word1 == NULL || word2 == NULL)
        return 0;

#if !defined SOL_NO_NGRAMS

    try
    {
        lem::Ptr<Ngrams> ngrams = HandleEngine(hEngine)->dict->GetNgrams();

        if (ngrams.NotNull())
        {
            float wf = 0;
            int iw = 0;

            if (ngrams->FindNGrams(type == 1, word1, word2, wf, iw))
                return iw;

            return 0;
        }

        return 0;
    }
    catch (...)
    {
        return 0;
    }
#endif

    return 0;
}

GREN_API(int) sol_Seek2Grams8(
    HGREN hEngine,
    int type,
    const char *Word1Utf8,
    const char *Word2Utf8
)
{
    return sol_Seek2Grams(
        hEngine,
        type,
        lem::from_utf8(Word1Utf8).c_str(),
        lem::from_utf8(Word2Utf8).c_str()
    );
}


// http://www.solarix.ru/for_developers/api/ngrams-api.shtml
GREN_API(int) sol_Seek3Grams(
    HGREN hEngine,
    int type,
    const wchar_t *word1,
    const wchar_t *word2,
    const wchar_t *word3
)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || word1 == NULL || word2 == NULL || word3 == NULL)
        return 0;

#if !defined SOL_NO_NGRAMS

    try
    {
        lem::Ptr<Ngrams> ngrams = HandleEngine(hEngine)->dict->GetNgrams();

        if (ngrams.NotNull())
        {
            float wf = 0;
            int iw = 0;

            if (ngrams->FindNGrams(type == 1, word1, word2, word3, wf, iw))
                return iw;

            return 0;
        }

        return 0;
    }
    catch (...)
    {
        return 0;
    }
#endif

    return 0;
}

GREN_API(int) sol_Seek3Grams8(
    HGREN hEngine,
    int type,
    const char *Word1Utf8,
    const char *Word2Utf8,
    const char *Word3Utf8
)
{
    return sol_Seek3Grams(
        hEngine,
        type,
        lem::from_utf8(Word1Utf8).c_str(),
        lem::from_utf8(Word2Utf8).c_str(),
        lem::from_utf8(Word3Utf8).c_str()
    );
}


// http://www.solarix.ru/for_developers/api/ngrams-api.shtml
GREN_API(int) sol_Seek4Grams(
    HGREN hEngine,
    int type,
    const wchar_t *word1,
    const wchar_t *word2,
    const wchar_t *word3,
    const wchar_t *word4
)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict ||
        word1 == NULL || word2 == NULL || word3 == NULL || word4 == NULL)
        return 0;

#if !defined SOL_NO_NGRAMS

    try
    {
        lem::Ptr<Ngrams> ngrams = HandleEngine(hEngine)->dict->GetNgrams();

        if (ngrams.NotNull())
        {
            float wf = 0;
            int iw = 0;

            if (ngrams->FindNGrams(type == 1, word1, word2, word3, word4, wf, iw))
                return iw;

            return 0;
        }

        return 0;
    }
    catch (...)
    {
        return 0;
    }
#endif

    return 0;
}

GREN_API(int) sol_Seek4Grams8(
    HGREN hEngine,
    int type,
    const char *Word1Utf8,
    const char *Word2Utf8,
    const char *Word3Utf8,
    const char *Word4Utf8
)
{
    return sol_Seek4Grams(
        hEngine,
        type,
        lem::from_utf8(Word1Utf8).c_str(),
        lem::from_utf8(Word2Utf8).c_str(),
        lem::from_utf8(Word3Utf8).c_str(),
        lem::from_utf8(Word4Utf8).c_str()
    );
}

// http://www.solarix.ru/for_developers/api/ngrams-api.shtml
GREN_API(int) sol_Seek5Grams(
    HGREN hEngine,
    int type,
    const wchar_t *word1,
    const wchar_t *word2,
    const wchar_t *word3,
    const wchar_t *word4,
    const wchar_t *word5
)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict ||
        word1 == NULL || word2 == NULL || word3 == NULL || word4 == NULL || word5 == NULL)
        return 0;

#if !defined SOL_NO_NGRAMS

    try
    {
        lem::Ptr<Ngrams> ngrams = HandleEngine(hEngine)->dict->GetNgrams();

        if (ngrams.NotNull())
        {
            float wf = 0;
            int iw = 0;

            if (ngrams->FindNGrams(type == 1, word1, word2, word3, word4, word5, wf, iw))
                return iw;

            return 0;
        }

        return 0;
    }
    catch (...)
    {
        return 0;
    }
#endif

    return 0;
}



GREN_API(int) sol_Seek5Grams8(
    HGREN hEngine,
    int type,
    const char *Word1Utf8,
    const char *Word2Utf8,
    const char *Word3Utf8,
    const char *Word4Utf8,
    const char *Word5Utf8
)
{
    return sol_Seek5Grams(
        hEngine,
        type,
        lem::from_utf8(Word1Utf8).c_str(),
        lem::from_utf8(Word2Utf8).c_str(),
        lem::from_utf8(Word3Utf8).c_str(),
        lem::from_utf8(Word4Utf8).c_str(),
        lem::from_utf8(Word5Utf8).c_str()
    );
}





//////////////////////////////////////////////////////////////////////
///
/// \brief �������� �� ������ ������ �� ��������� �����
///
//////////////////////////////////////////////////////////////////////
GREN_API(int) sol_IsLanguagePhrase(HGREN hEngine, const wchar_t *Phrase, int Language)
{
#if defined SOLARIX_PRO
    if (hEngine == NULL || lem::lem_is_empty(Phrase) || !HandleEngine(hEngine)->dict)
        return 0;

#if defined SOL_CAA
    try
    {
        lem::UFString uphrase(Phrase);

        /*
         lem::MCollect<UCString> words;
         lem::parse( uphrase, words, true );
         int iLang = HandleEngine(hEngine)->dict->GetLexAuto().GuessLanguage(words);
        */

        int iLang = HandleEngine(hEngine)->dict->GetLexAuto().GuessLanguage(uphrase);
        return iLang == Language ? 1 : 0;
    }
    CATCH_API(hEngine);
    return -1;
#else
    return 0;
#endif

#endif
    return 0;
}

//////////////////////////////////////////////////////////////////////
///
/// \brief  ���������� ���� ��� �����
///
/// @param Phrase null terminated ������ � �������
/// @return ��� �����, ��� -1 (�� ������� ���������), ��� -2 (������)
//////////////////////////////////////////////////////////////////////
GREN_API(int) sol_GuessPhraseLanguage(HGREN hEngine, const wchar_t *Phrase)
{
#if defined SOLARIX_PRO
    if (hEngine == NULL || lem::lem_is_empty(Phrase) || !HandleEngine(hEngine)->dict)
        return -2;

#if defined SOL_CAA
    try
    {
        lem::UFString uphrase(Phrase);
        /*
         lem::MCollect<UCString> words;
         lem::parse( uphrase, words, true );
         int iLang = HandleEngine(hEngine)->dict->GetLexAuto().GuessLanguage(words);
        */

        int iLang = HandleEngine(hEngine)->dict->GetLexAuto().GuessLanguage(uphrase);

        return iLang;
    }
    CATCH_API(hEngine);
    return -1;
#else
    return -1;
#endif

#else
    return -1;
#endif
}




// Search for ID of part of speech
// http://www.solarix.ru/api/en/sol_FindClass.shtml
// http://www.solarix.ru/api/ru/sol_FindClass.shtml
GREN_API(int) sol_FindClass(HGREN hEngine, const wchar_t *ClassName)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || lem::lem_is_empty(ClassName))
        return -2;

    try
    {
        return HandleEngine(hEngine)->dict->GetSynGram().FindClass(lem::UCString(ClassName));
    }
    catch (...)
    {
        // Internal error
        return -2;
    }
}


// Search for ID of part of speech - utf8 version
// http://www.solarix.ru/api/en/sol_FindClass.shtml
// http://www.solarix.ru/api/ru/sol_FindClass.shtml
GREN_API(int) sol_FindClass8(HGREN hEngine, const char *ClassNameUtf8)
{
    lem::UFString NameW = lem::from_utf8(ClassNameUtf8);
    return sol_FindClass(hEngine, NameW.c_str());
}


// http://www.solarix.ru/api/en/sol_FindEnum.shtml
// http://www.solarix.ru/api/ru/sol_FindEnum.shtml
GREN_API(int) sol_FindEnum(HGREN hEngine, const wchar_t *EnumName)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || lem::lem_is_empty(EnumName))
        return -2;

    try
    {
        const Solarix::GramCoordAdr ca = HandleEngine(hEngine)->dict->GetSynGram().FindCoord(lem::UCString(EnumName));
        return ca.GetIndex();
    }
    catch (...)
    {
        // Internal error
        return -2;
    }
}

GREN_API(int) sol_FindEnum8(HGREN hEngine, const char *EnumNameUtf8)
{
    lem::UFString NameW = lem::from_utf8(EnumNameUtf8);
    return sol_FindEnum(hEngine, NameW.c_str());
}


// http://www.solarix.ru/api/en/sol_FindEnumState.shtml
// http://www.solarix.ru/api/ru/sol_FindEnumState.shtml
GREN_API(int) sol_FindEnumState(HGREN hEngine, int CoordID, const wchar_t *StateName)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || CoordID < 0 || lem::lem_is_empty(StateName))
        return -2;

    try
    {
        return HandleEngine(hEngine)->dict->GetSynGram().coords()[CoordID].FindState(StateName);
    }
    catch (...)
    {
        // Internal error
        return -2;
    }
}

// http://www.solarix.ru/api/en/sol_FindEnumState.shtml
// http://www.solarix.ru/api/ru/sol_FindEnumState.shtml
GREN_API(int) sol_FindEnumState8(HGREN hEngine, int CoordID, const char *StateNameUtf8)
{
    lem::UFString NameW = lem::from_utf8(StateNameUtf8);
    return sol_FindEnumState(hEngine, CoordID, NameW.c_str());
}


GREN_API(int) sol_MatchNGrams(
    HGREN hEngine,
    const wchar_t *Text,
    int * unmatched_2_ngrams,
    int *n2,
    int *n3
)
{
#if !defined SOL_NO_NGRAMS && !defined SOL_NO_AA
    if (hEngine == NULL || !HandleEngine(hEngine)->ok || Text == NULL)
        return -1;

    try
    {
        Solarix::Sentence sent;
        sent.Parse(Text, false, HandleEngine(hEngine)->dict.get(), HandleEngine(hEngine)->DefaultLanguage, NULL);

        lem::MCollect<lem::UCString> words;
        for (int i = 0; i < CastSizeToInt(sent.size()); ++i)
            words.push_back(sent.GetNormalizedWord(i));

        HandleEngine(hEngine)->dict->MatchNGrams(words, unmatched_2_ngrams, n2, n3);
    }
    catch (...)
    {
        return -1;
    }

    return 0;
#else
    return -1;
#endif
}






GREN_API(int) sol_Syllabs(
    HGREN hEngine,
    const wchar_t *OrgWord,
    wchar_t SyllabDelimiter,
    wchar_t *Result,
    int LanguageID
)
{
#if !defined SOL_NO_AA
    if (hEngine == NULL || !HandleEngine(hEngine)->ok || OrgWord == NULL)
        return -1;

    try
    {
        *Result = 0;

        wchar_t delim[2] = { SyllabDelimiter, 0 };

        lem::UCString word(OrgWord);
        lem::MCollect<lem::UCString> slb_list;

        HandleEngine(hEngine)->dict->GetGraphGram().FindSyllabs(word, LanguageID, false, slb_list, NULL);

        for (lem::Container::size_type i = 0; i < slb_list.size(); ++i)
        {
            if (i > 0)
                wcscat(Result, delim);

            wcscat(Result, slb_list[i].c_str());
        }
    }
    catch (...)
    {
        return -1;
    }

    return 0;
#else
    return -1;
#endif
}


GREN_API(int) sol_Syllabs8(
    HGREN hEngine,
    const char *OrgWord,
    char SyllabDelimiter,
    char *Result,
    int LanguageID
)
{
    try
    {
        wchar_t *buffer = new wchar_t[strlen(OrgWord) * 8];
        *buffer = 0;
        const int rc = sol_Syllabs(hEngine, lem::from_utf8(OrgWord).c_str(), SyllabDelimiter, buffer, LanguageID);

        lem::lem_strcpy(Result, lem::to_utf8(buffer).c_str());

        delete[] buffer;
        return rc;
    }
    CATCH_API(hEngine);

    return -2;

}


// **********************************************************
// ����������� ������ - �������� �� �������.
//
// API Help:
// http://www.solarix.ru/api/en/sol_Tokenize.shtml
// http://www.solarix.ru/api/ru/sol_Tokenize.shtml
//
// Detailed description of underlying algorithms:
// http://www.solarix.ru/for_developers/docs/tokenizer.shtml
//
// **********************************************************
GREN_API(HGREN_STR) sol_TokenizeW(HGREN hEngine, const wchar_t *Sentence, int LanguageID)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->ok || Sentence == NULL)
        return NULL;

#if defined SOL_CAA && !defined SOL_NO_AA
    std::auto_ptr<GREN_Strings> list(new GREN_Strings);

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        lem::UFString sentence(Sentence);

        Solarix::Sentence sent;
        sent.Parse(sentence, false, HandleEngine(hEngine)->dict.get(), LanguageID, NULL);
        for (int i = 0; i < CastSizeToInt(sent.size()); ++i)
            list->list.push_back(sent.GetWord(i));

        return list.release();
    }
    CATCH_API(hEngine)
#endif

        return NULL;
}


GREN_API(HGREN_STR) sol_TokenizeA(HGREN hEngine, const char *Sentence, int LanguageID)
{
    return sol_TokenizeW(hEngine, to_unicode(Sentence).c_str(), LanguageID);
}

GREN_API(HGREN_STR) sol_Tokenize8(HGREN hEngine, const char *SentenceUtf8, int LanguageID)
{
    return sol_TokenizeW(hEngine, lem::from_utf8(SentenceUtf8).c_str(), LanguageID);
}





GREN_API(HGREN_SBROKER) sol_CreateSentenceBroker(
    HGREN hEngine,
    const wchar_t *Filename,
    const wchar_t *DefaultCodepage,
    int LanguageID
)
{
    if (hEngine == NULL || lem::lem_is_empty(Filename))
        return NULL;

    try
    {
        lem::Path filename(Filename);

#if defined SOLARIX_SEARCH_ENGINE
        lem::StreamPtr file(new BinaryReader(filename));

        const lem::CodeConverter *cp = &lem::UI::get_UI().GetSessionCp();

        if (!lem::lem_is_empty(DefaultCodepage))
        {
            try
            {
                cp = lem::CodeConverter::getConverter(to_ascii(DefaultCodepage));
            }
            catch (...)
            {
                return NULL;
            }
        }

        HandleEngine(hEngine)->scanning.prefer_cp_list.clear();
        HandleEngine(hEngine)->scanning.prefer_cp_list.push_back(cp);

        lem::Ptr<Solarix::Search_Engine::Base_File_Reader> reader = HandleEngine(hEngine)->detector->FindReader(
            HandleEngine(hEngine)->scanning,
            filename.GetUnicode(),
            to_upper(filename.GetExtension()),
            file
        );

        if (reader.NotNull())
        {
            lem::Ptr<UFString> text = new UFString;
            reader->read_whole_text(*text);
            lem::Ptr<lem::Char_Stream::WideStream> reader2 = new lem::Char_Stream::UTF16_MemReader(text);
            SentenceBroker *broker = new SentenceBroker(reader2, HandleEngine(hEngine)->dict.get(), LanguageID);
            return broker;
        }

#else

        bool is_utf8 = wcscmp(DefaultCodepage, L"utf-8") == 0 || wcscmp(DefaultCodepage, L"utf8") == 0;
        lem::Ptr<lem::Char_Stream::WideStream> reader = is_utf8 ? new lem::Char_Stream::UTF8_Reader(filename, false) : lem::Char_Stream::WideStream::GetReader(filename);
        SentenceBroker *broker = new SentenceBroker(reader, HandleEngine(hEngine)->dict.get(), LanguageID);
        return broker;

#endif
    }
    CATCH_API(hEngine)

        return NULL;
}

GREN_API(HGREN_SBROKER) sol_CreateSentenceBroker8(
    HGREN hEngine,
    const char *Filename8,
    const char *DefaultCodepage,
    int LanguageID
)
{
    return sol_CreateSentenceBroker(hEngine, lem::from_utf8(Filename8).c_str(), lem::from_utf8(DefaultCodepage).c_str(), LanguageID);
}

GREN_API(HGREN_SBROKER) sol_CreateSentenceBrokerMemW(HGREN hEngine, const wchar_t *Text, int LanguageID)
{
    if (hEngine == NULL || lem::lem_is_empty(Text))
        return NULL;

    try
    {
        lem::Ptr<lem::Char_Stream::WideStream> reader2 = new lem::Char_Stream::UTF16_MemReader(Text);
        SentenceBroker *broker = new SentenceBroker(reader2, HandleEngine(hEngine)->dict.get(), LanguageID);
        return broker;
    }
    CATCH_API(hEngine)

        return NULL;
}


GREN_API(HGREN_SBROKER) sol_CreateSentenceBrokerMemA(HGREN hEngine, const char *Text, int LanguageID)
{
    return sol_CreateSentenceBrokerMemW(hEngine, lem::to_unicode(Text).c_str(), LanguageID);
}


GREN_API(HGREN_SBROKER) sol_CreateSentenceBrokerMem8(HGREN hEngine, const char *TextUtf8, int LanguageID)
{
    if (hEngine == NULL || lem::lem_is_empty(TextUtf8))
        return NULL;

    try
    {
        lem::Ptr<lem::Char_Stream::WideStream> reader2 = new lem::Char_Stream::UTF8_MemReader(TextUtf8);
        SentenceBroker *broker = new SentenceBroker(reader2, HandleEngine(hEngine)->dict.get(), LanguageID);
        return broker;
    }
    CATCH_API(hEngine)

        return NULL;
}



// Fetches next sentence from the input stream.
// Returns: -1 if no more sentence are available, -2 for internal error, N>=0 is sentence length otherwise.
// Note: Empty sentences can be extracted.
GREN_API(int) sol_FetchSentence(HGREN_SBROKER hBroker)
{
    try
    {
        if (hBroker != NULL)
        {
            if (!((SentenceBroker*)hBroker)->Fetch())
                return -1; // no more sentences is available

            const UFString &s = ((SentenceBroker*)hBroker)->GetFetchedSentence();
            return s.length();
        }
    }
    catch (...)
    {
    }

    return -2;
}


GREN_API(int) sol_GetFetchedSentenceLen(HGREN_SBROKER hBroker)
{
    try
    {
        if (hBroker != NULL)
        {
            return ((SentenceBroker*)hBroker)->GetFetchedSentence().length();
        }
    }
    catch (...)
    {
    }

    return -1;
}


GREN_API(int) sol_GetFetchedSentenceW(HGREN_SBROKER hBroker, wchar_t *Buffer)
{
    try
    {
        if (hBroker != NULL && Buffer != NULL)
        {
            lem::lem_strcpy(Buffer, ((SentenceBroker*)hBroker)->GetFetchedSentence().c_str());
            return ((SentenceBroker*)hBroker)->GetFetchedSentence().length();
        }
    }
    catch (...)
    {
    }

    return -1;
}


GREN_API(int) sol_GetFetchedSentenceA(HGREN_SBROKER hBroker, char *Buffer)
{
    try
    {
        if (hBroker != NULL && Buffer != NULL)
        {
            lem::lem_strcpy(Buffer, lem::to_ascii(((SentenceBroker*)hBroker)->GetFetchedSentence()).c_str());
            return lem::lem_strlen(Buffer);
        }
    }
    catch (...)
    {
    }

    return -1;
}


GREN_API(int) sol_GetFetchedSentence8(HGREN_SBROKER hBroker, char *BufferUtf8)
{
    try
    {
        if (hBroker != NULL && BufferUtf8 != NULL)
        {
            lem::lem_strcpy(BufferUtf8, lem::to_utf8(((SentenceBroker*)hBroker)->GetFetchedSentence()).c_str());
            return lem::lem_strlen(BufferUtf8);
        }
    }
    catch (...)
    {
    }

    return -1;
}




GREN_API(void) sol_DeleteSentenceBroker(HGREN_SBROKER hBroker)
{
    try
    {
        delete ((SentenceBroker*)hBroker);
    }
    catch (...)
    {
    }

    return;
}




GREN_API(int) sol_Bits(void)
{
    if (sizeof(int*) == 8)
        return 64;
    else if (sizeof(int*) == 4)
        return 32;
    else - 1;
}


// Get the ID of the language
// http://www.solarix.ru/api/en/sol_FindLanguage.shtml
GREN_API(int) sol_FindLanguage(HGREN hEngine, const wchar_t *LanguageName)
{
    if (hEngine == NULL || lem::lem_is_empty(LanguageName))
        return -1;

    try
    {
        return HandleEngine(hEngine)->dict->GetSynGram().Find_Language(LanguageName);
    }
    catch (...)
    {
        return -1;
    }

    return -1;
}


// http://www.solarix.ru/api/en/sol_FindLanguage.shtml
GREN_API(int) sol_FindLanguage8(HGREN hEngine, const char *LanguageNameUtf8)
{
    lem::UFString w(lem::from_utf8(LanguageNameUtf8));
    return sol_FindLanguage(hEngine, w.c_str());
}


// **********************************
// ��������� ���������� ��� ����
// **********************************
GREN_API(int) sol_GetNodeCoordState(HGREN_TREENODE hNode, int CoordID)
{
    if (hNode == NULL || CoordID == -1)
        return -1;

    try
    {
        const int istate = HandleNode(hNode)->GetNode().GetState(Solarix::GramCoordAdr(CoordID));
        return istate;
    }
    catch (...)
    {
    }

    return -1;
}


// *******************************************
// ��������� ���������� ��� ������ ����������
// *******************************************
GREN_API(int) sol_GetNodeVerCoordState(HGREN_TREENODE hNode, int iver, int CoordID)
{
    if (hNode == NULL || CoordID == -1)
        return -1;

    try
    {
        int istate = -1;
        if (iver == 0)
            istate = HandleNode(hNode)->GetNode().GetState(Solarix::GramCoordAdr(CoordID));
        else
            istate = HandleNode(hNode)->GetNode().GetAlts()[iver - 1]->GetState(Solarix::GramCoordAdr(CoordID));

        return istate;
    }
    catch (...)
    {
    }

    return -1;
}



// Detect the presence of icoord:istate in wordform.
// Return value: 0 - not found, 1 - found.
//
// http://www.solarix.ru/api/ru/sol_GetNodeCoordPair.shtml
GREN_API(int) sol_GetNodeCoordPair(HGREN_TREENODE hNode, int CoordID, int StateID)
{
    if (hNode == NULL || CoordID == -1 || StateID == -1)
        return 0;

    bool res = HandleNode(hNode)->GetNode().GetPairs().FindOnce(Solarix::GramCoordPair(CoordID, StateID)) != UNKNOWN;
    return res ? 1 : 0;
}


// http://www.solarix.ru/api/ru/sol_GetNodeVerCoordPair.shtml
GREN_API(int) sol_GetNodeVerCoordPair(HGREN_TREENODE hNode, int iver, int CoordID, int StateID)
{
    if (hNode == NULL || CoordID == -1 || StateID == -1)
        return 0;

    bool res;

    if (iver == 0)
        res = HandleNode(hNode)->GetNode().GetPairs().FindOnce(Solarix::GramCoordPair(CoordID, StateID)) != UNKNOWN;
    else
        res = HandleNode(hNode)->GetNode().GetAlts()[iver - 1]->GetPairs().FindOnce(Solarix::GramCoordPair(CoordID, StateID)) != UNKNOWN;

    return res ? 1 : 0;
}


// http://www.solarix.ru/api/ru/sol_GetNodePairsCount.shtml
GREN_API(int) sol_GetNodePairsCount(HGREN_TREENODE hNode)
{
    if (hNode == NULL)
        return -1;

    return CastSizeToInt(HandleNode(hNode)->GetNode().GetPairs().size());
}


// http://www.solarix.ru/api/ru/sol_GetNodeVerPairsCount.shtml
GREN_API(int) sol_GetNodeVerPairsCount(HGREN_TREENODE hNode, int iver)
{
    if (hNode == NULL)
        return -1;

    if (iver == 0)
        return CastSizeToInt(HandleNode(hNode)->GetNode().GetPairs().size());
    else
        return CastSizeToInt(HandleNode(hNode)->GetNode().GetAlts()[iver - 1]->GetPairs().size());
}


// http://www.solarix.ru/api/ru/sol_GetNodePairCoord.shtml
GREN_API(int) sol_GetNodePairCoord(HGREN_TREENODE hNode, int ipair)
{
    if (hNode == NULL || ipair < 0 || ipair >= CastSizeToInt(HandleNode(hNode)->GetNode().GetPairs().size()))
        return -1;

    return HandleNode(hNode)->GetNode().GetPairs()[ipair].GetCoord().GetIndex();
}


// http://www.solarix.ru/api/ru/sol_GetNodeVerPairCoord.shtml
GREN_API(int) sol_GetNodeVerPairCoord(HGREN_TREENODE hNode, int iver, int ipair)
{
    if (hNode == NULL || ipair < 0)
        return -1;

    if (iver == 0)
    {
        if (ipair >= CastSizeToInt(HandleNode(hNode)->GetNode().GetPairs().size()))
            return -1;

        return HandleNode(hNode)->GetNode().GetPairs()[ipair].GetCoord().GetIndex();
    }
    else
    {
        if (ipair >= CastSizeToInt(HandleNode(hNode)->GetNode().GetAlts()[iver - 1]->GetPairs().size()))
            return -1;

        return HandleNode(hNode)->GetNode().GetAlts()[iver - 1]->GetPairs()[ipair].GetCoord().GetIndex();
    }
}


// http://www.solarix.ru/api/ru/sol_GetNodePairState.shtml
GREN_API(int) sol_GetNodePairState(HGREN_TREENODE hNode, int ipair)
{
    if (hNode == NULL || ipair < 0 || ipair >= CastSizeToInt(HandleNode(hNode)->GetNode().GetPairs().size()))
        return -1;

    return HandleNode(hNode)->GetNode().GetPairs()[ipair].GetState();
}


// http://www.solarix.ru/api/ru/sol_GetNodeVerPairState.shtml
GREN_API(int) sol_GetNodeVerPairState(HGREN_TREENODE hNode, int iver, int ipair)
{
    if (hNode == NULL || ipair < 0)
        return -1;

    if (iver == 0)
    {
        if (ipair >= CastSizeToInt(HandleNode(hNode)->GetNode().GetPairs().size()))
            return -1;

        return HandleNode(hNode)->GetNode().GetPairs()[ipair].GetState();
    }
    else
    {
        if (ipair >= CastSizeToInt(HandleNode(hNode)->GetNode().GetAlts()[iver - 1]->GetPairs().size()))
            return -1;

        return HandleNode(hNode)->GetNode().GetAlts()[iver - 1]->GetPairs()[ipair].GetState();
    }
}


GREN_API(int) sol_GenerateWordform(
    HGREN hEng,
    int ie,
    int npairs,
    const int *pairs,
    wchar_t *Result
)
{
    if (hEng == NULL || ie == UNKNOWN)
    {
        return -1;
    }

    DEMO_SINGLE_THREAD(hEng)

        try
    {
        const SG_Entry &e = HandleEngine(hEng)->dict->GetSynGram().GetEntry(ie);

        CP_Array apairs;
        for (int i = 0; i < npairs; ++i)
            apairs.push_back(Solarix::GramCoordPair(pairs[i * 2], pairs[i * 2 + 1]));

        //   const SG_EntryForm &f = e.FindFormAny( apairs );
        for (lem::Container::size_type i = 0; i < e.forms().size(); ++i)
        {
            const SG_EntryForm &f = e.forms()[i];
            if (f.does_match(apairs))
            {
                wcscpy(Result, f.name().c_str());
                return 1;
            }
        }

        *Result = 0;
        return 0;
    }
    catch (...)
    {
        return -1;
    }
}



// ***********************************************************************************************
// ��������� ���� ��������� �����, ���������� ��������� �������������� ��������.
// ����� ���� ���������� ������ ������, ���� ���������� ���� �� �������, ��� ����� 1 ������, ����
// ���������� ���� ���������.
// http://www.solarix.ru/api/ru/sol_GenerateWordforms.shtml
// ***********************************************************************************************
GREN_API(HGREN_STR) sol_GenerateWordforms(
    HGREN hEngine,
    int EntryID,
    int npairs,
    const int *pairs
)
{
    if (hEngine == NULL || EntryID == UNKNOWN)
    {
        return NULL;
    }

    DEMO_SINGLE_THREAD(hEngine)

        try
    {
        GREN_Strings *res = new GREN_Strings;

        const SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(EntryID);

        CP_Array apairs;
        for (int i = 0; i < npairs; ++i)
            apairs.push_back(Solarix::GramCoordPair(pairs[i * 2], pairs[i * 2 + 1]));

        for (lem::Container::size_type i = 0; i < e.forms().size(); ++i)
        {
            const SG_EntryForm &f = e.forms()[i];
            if (f.does_match(apairs))
            {
                res->list.push_back(f.name().c_str());
            }
        }

        return res;
    }
    catch (...)
    {
        return NULL;
    }
}






GREN_API(int) sol_CountLexems(HGREN hEng)
{
    if (hEng == NULL)
    {
        return -1;
    }

    try
    {
        SynGram &sg = HandleEngine(hEng)->dict->GetSynGram();
        const int n = sg.GetEntries().CountLexemes();
        return n;
    }
    catch (...)
    {
        return -1;
    }
}



struct MatchingParadigma : lem::NonCopyable
{
    Solarix::Lexem entry_name;
    lem::MCollect<int> ies; // ���� ������� ������ ��������� ������
    lem::MCollect<lem::UCString> paradigmas; // ����� ���������� ��������
    lem::MCollect<int> iparadigmas; // ������� ���������� �������� �� ���������� ������
};



GREN_API(HFLEXIONS) sol_FindFlexionHandlers(HGREN hEngine, const wchar_t *WordBasicForm, int Flags)
{
    if (hEngine == NULL && lem::lem_is_empty(WordBasicForm))
    {
        return NULL;
    }

    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();

        MatchingParadigma *res = new MatchingParadigma;

        res->entry_name = WordBasicForm;
        res->entry_name.to_upper();
        HandleEngine(hEngine)->dict->GetLexAuto().TranslateLexem(res->entry_name, true);

        if (Flags == 1)
        {
            // ��-������, ���� ���������� ��������� ������.
            sg.FindEntries(res->entry_name, res->ies);
        }

        // ��-������, ���� �������������
        sg.Get_DSA().FindDecl(res->entry_name, res->iparadigmas);

        // ��������� ������ �� �������  
        for (lem::Container::size_type i = 0; i < res->iparadigmas.size(); ++i)
            res->paradigmas.push_back(sg.Get_DSA().GetDecl(res->iparadigmas[i]).GetName());

        return res;
    }
    catch (...)
    {
        return NULL;
    }
}

// Flexion engine: return the number of matching entries
GREN_API(int) sol_CountEntriesInFlexionHandlers(HGREN hEng, HFLEXIONS hFlexs)
{
    if (hEng == NULL && hFlexs == NULL)
    {
        return NULL;
    }

    try
    {
        return CastSizeToInt(((const MatchingParadigma*)hFlexs)->ies.size());
    }
    catch (...)
    {
        return -1;
    }
}


// Flexion engine: return the number of matching paradigmas
GREN_API(int) sol_CountParadigmasInFlexionHandlers(HGREN hEng, HFLEXIONS hFlexs)
{
    if (hEng == NULL && hFlexs == NULL)
    {
        return NULL;
    }

    try
    {
        const MatchingParadigma *x = (const MatchingParadigma*)hFlexs;
        return CastSizeToInt(x->iparadigmas.size());
    }
    catch (...)
    {
        return -1;
    }
}


// Flexion engine: return the entry ID
GREN_API(int) sol_GetEntryInFlexionHandlers(HGREN hEng, HFLEXIONS hFlexs, int Index)
{
    if (hEng == NULL && hFlexs == NULL)
    {
        return NULL;
    }

    try
    {
        const MatchingParadigma *x = (const MatchingParadigma*)hFlexs;
        return x->ies[Index];
    }
    catch (...)
    {
        return -1;
    }
}


// Flexion engine: return the paradigma internal index and human-friendly name
GREN_API(int) sol_GetParadigmaInFlexionHandlers(HGREN hEng, HFLEXIONS hFlexs, int Index, wchar_t *ParadigmaName)
{
    if (hEng == NULL && hFlexs == NULL)
    {
        return NULL;
    }

    try
    {
        const MatchingParadigma *x = (const MatchingParadigma*)hFlexs;

        if (ParadigmaName != NULL)
            lem::lem_strcpy(ParadigmaName, x->paradigmas[Index].c_str());

        return x->iparadigmas[Index];
    }
    catch (...)
    {
        return -1;
    }
}


struct FlexionTable : lem::NonCopyable
{
    lem::MCollect<Solarix::Lexem> form_names;
    lem::PtrCollect< CP_Array > form_dims;
};



GREN_API(HFLEXIONTABLE) sol_BuildFlexionHandler(
    HGREN hEng,
    HFLEXIONS hFlexs,
    const wchar_t *ParadigmaName,
    int EntryIndex
)
{
    if (hEng == NULL && (hFlexs == NULL && !lem::lem_is_empty(ParadigmaName)))
    {
        return NULL;
    }

    try
    {
        FlexionTable *res = new FlexionTable;

        SynGram &sg = HandleEngine(hEng)->dict->GetSynGram();

        if (!lem::lem_is_empty(ParadigmaName))
        {
            const MatchingParadigma *xpar = (const MatchingParadigma*)hFlexs;

            // ���������� ������ ���������.
            const int ipar = sg.Get_DSA().FindDecl(ParadigmaName);
            if (ipar != UNKNOWN)
            {
                const SG_DeclensionTable &par = sg.Get_DSA().GetDecl(ipar);

                par.GenerateForms(
                    xpar->entry_name,
                    res->form_names,
                    res->form_dims,
                    sg,
                    sg.Get_DSA()
                );
            }
        }
        else if (EntryIndex != UNKNOWN)
        {
            const Solarix::SG_Entry &e = sg.GetEntry(EntryIndex);
            for (lem::Container::size_type i = 0; i < e.forms().size(); ++i)
            {
                const Solarix::SG_EntryForm &f = e.forms()[i];
                res->form_names.push_back(f.name());
                res->form_dims.push_back(new CP_Array(f.coords()));
            }
        }

        return res;
    }
    catch (...)
    {
        return NULL;
    }
}

GREN_API(int) sol_CountFlexionHandlerWordform(HGREN hEngine, HFLEXIONTABLE hFlex)
{
    try
    {
        if (hFlex == NULL)
            return 0;

        const FlexionTable *table = (const FlexionTable*)hFlex;
        return CastSizeToInt(table->form_names.size());
    }
    CATCH_API(hEngine);

    return -1;
}

GREN_API(const wchar_t*) sol_GetFlexionHandlerWordformText(HGREN hEngine, HFLEXIONTABLE hFlex, int FormIndex)
{
    try
    {
        if (hFlex == NULL)
            return 0;

        const FlexionTable *table = (const FlexionTable*)hFlex;
        return table->form_names[FormIndex].c_str();
    }
    CATCH_API(hEngine);

    return NULL;
}


GREN_API(const wchar_t*) sol_GetFlexionHandlerWordform(
    HGREN hEng,
    HFLEXIONTABLE hFlex,
    const wchar_t *dims
)
{
    try
    {
        const FlexionTable *table = (const FlexionTable*)hFlex;

        // ������� ���� ���������� ������ ��������� dims �� ������������ ����
        lem::UFString sdims(dims);
        lem::Collect< lem::UFString > spairs;
        lem::parse(sdims, spairs, L" ,;");

        const SynGram &sg = HandleEngine(hEng)->dict->GetSynGram();

        lem::MCollect< Solarix::GramCoordPair > req_dims;
        for (lem::Container::size_type i = 0; i < spairs.size(); ++i)
        {
            const UFString &s = spairs[i];
            lem::MCollect<UCString> s2;
            lem::parse(s, s2, false);

            const int icoord = sg.FindCoord(s2[0]).GetIndex();
            if (icoord != UNKNOWN)
            {
                int istate = UNKNOWN;

                // ��� ������������ ��������� ������ ������� ��������� ������� ������:
                // ~������� = �������:0
                // �������  = �������:1

                const Solarix::GramCoord &c = sg.coords()[icoord];

                if (c.IsBistable())
                {
                    if (s2[0].front() == L'~')
                        istate = 0;
                    else
                        istate = 1;
                }
                else
                {
                    istate = c.FindState(s2[1]);
                }

                if (istate != UNKNOWN)
                {
                    req_dims.push_back(Solarix::GramCoordPair(GramCoordAdr(icoord), istate));
                }
            }
        }

        // �������� ������ ������������ ���, ������� ������ �������������� � ������� �����.
        // ���� �����. �������� ������, � ������� ��� ����������� ���������� ���� � �������
        // ������ ���������.
        int ibest_form = UNKNOWN, best_form_dims = lem::int_max;

        for (lem::Container::size_type i = 0; i < table->form_dims.size(); ++i)
        {
            const lem::MCollect<GramCoordPair> &form_dims = *table->form_dims[i];
            if (CastSizeToInt(form_dims.size()) > best_form_dims)
                continue;

            bool all_match = true;
            for (lem::Container::size_type j = 0; j < req_dims.size(); ++j)
                if (form_dims.find(req_dims[j]) == UNKNOWN)
                {
                    all_match = false;
                    break;
                }

            if (all_match && CastSizeToInt(form_dims.size()) < best_form_dims)
            {
                best_form_dims = CastSizeToInt(form_dims.size());
                ibest_form = CastSizeToInt(i);
            }
        }

        if (ibest_form != UNKNOWN)
        {
            return table->form_names[ibest_form].c_str();
        }
        else
        {
            return L"";
        }
    }
    CATCH_API(hEng);

    return NULL;
}




GREN_API(int) sol_DeleteFlexionHandlers(HGREN hEngine, HFLEXIONS hFlexs)
{
    try
    {
        delete (MatchingParadigma*)hFlexs;
        return 0;
    }
    CATCH_API(hEngine);

    return -1;
}



GREN_API(int) sol_DeleteFlexionHandler(HGREN hEng, HFLEXIONTABLE hFlex)
{
    try
    {
        delete (FlexionTable*)hFlex;
        return 0;
    }
    catch (...)
    {
        return -1;
    }
}




// ******************************************************************
// ����� �������� ������. ������������ ��������� ���� ������.
// http://www.solarix.ru/api/en/sol_FindPhrase.shtml
//
// Flags=0 - ignore case
// Flags=1 - case sensitive lookup
// ******************************************************************
GREN_API(int) sol_FindPhrase(HGREN hEngine, const wchar_t *Phrase, int Flags)
{
    if (hEngine == NULL || lem::lem_is_empty(Phrase))
        return -2;

    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        const int ekey = sg.GetStorage().FindPhrase(Phrase, Flags == 0);
        return ekey;
    }
    CATCH_API(hEngine);

    return -1;
}


// http://www.solarix.ru/api/en/sol_FindPhrase.shtml
GREN_API(int) sol_FindPhrase8(HGREN hEngine, const char *PhraseUtf8, int Flags)
{
    return sol_FindPhrase(hEngine, lem::from_utf8(PhraseUtf8).c_str(), Flags);
}



struct LinkInfo : lem::NonCopyable
{
    int type; // 0 - ��� ��������� ������, 1 - ��� ��������
    int id; // ��������� ���� ������ � ��������������� ������� ������.
    int code; // ��� ���� �����
    int ekey1, ekey2; // ����� ��������� ��� �������� ������
    lem::UFString tags_txt; // ������ �����
    lem::FString tags_txt8;
    lem::UFString flags; // ������ ������
    lem::FString flags8;
};

typedef lem::PtrCollect<LinkInfo> LinksInfo;

typedef void* HLINKSINFO;



// ���� ��� ����� � ��������� ��� ��������� ��� �������� ������.
// Key1 - id ��������� (����) ��� �������� ������
// LinkCode - ��������� ���� �����
// Flags - �������������� ����������� �����: 0-��� ��������� ������, 1 - ��� ��������.

// http://www.solarix.ru/api/ru/sol_ListLinksTxt.shtml

GREN_API(HLINKSINFO) sol_ListLinksTxt(
    HGREN hEngine,
    int ie1,
    int LinkCode,
    int Flags
)
{
    LinksInfo * res = NULL;

#if !defined SOLARIX_DEMO
    try
    {
        res = new LinksInfo();

        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        SG_Net &th = sg.Get_Net();

        if (Flags == 0)
        {
            const int Key1 = sg.GetEntry(ie1).GetKey();

            // ���� ����� ��� ��������� ������.
            lem::Ptr<WordLinkEnumerator> links(sg.Get_Net().EnumerateWordLinks(Key1, LinkCode));
            while (links->Fetch())
            {
                LinkInfo *li = new LinkInfo;
                li->type = 0;
                li->id = links->GetLinkId();
                li->code = links->GetLinkType();
                li->ekey1 = ie1;
                li->ekey2 = links->GetEntryKey2();//sg.FindEntryIndexByKey( links->GetEntryKey2() );

#if defined SOL_SAVETXT
                Solarix::PrintTags(links->GetTags(), li->tags_txt, sg);
#endif

                res->push_back(li);
            }
        }
        else if (Flags == 1)
        {
            // ���� ����� ��� �������� ������.
            lem::MCollect<int> tl_id, te_id;

            const int Key1 = ie1;

            lem::PtrCollect<SG_LinkFlag> flist;

            th.FindComplexLinks(Key1, LinkCode, tl_id, te_id);

            for (lem::Container::size_type i = 0; i < tl_id.size(); ++i)
            {
                lem::Ptr<SG_ComplexLink> lnk = th.GetComplexLink(tl_id[i]);

                SG_Phrase frz;
                sg.GetStorage().GetPhrase(te_id[i], frz);

                LinkInfo *li = new LinkInfo;
                li->type = 0;
                li->id = tl_id[i];
                li->code = LinkCode;
                li->ekey1 = Key1;
                li->ekey2 = te_id[i];

                Solarix::PrintTags(lnk->GetTags(), li->tags_txt, sg);

                flist.clear();
                th.GetLinkFlags(tl_id[i], flist);
                for (lem::Container::size_type k = 0; k < flist.size(); ++k)
                {
                    if (!li->flags.empty())
                        li->flags += L' ';

                    li->flags += lem::format_str(L"%s=%s", flist[k]->GetFlag().c_str(), flist[k]->GetValue().c_str());
                }

                res->push_back(li);
            }
        }

        return res;
    }
    CATCH_API(hEngine);
#endif

    return NULL;
}


// http://www.solarix.ru/api/ru/sol_DeleteLinksInfo.shtml
GREN_API(int) sol_DeleteLinksInfo(HGREN hEng, HLINKSINFO hList)
{
    try
    {
        if (hList != NULL)
        {
            delete (LinksInfo*)hList;
        }

        return 0;
    }
    catch (...)
    {
        return -2;
    }
}

// ������������ ����� ��������� ������ � ������.
// http://www.solarix.ru/api/ru/sol_LinksInfoCount.shtml
GREN_API(int) sol_LinksInfoCount(HGREN hEngine, HLINKSINFO hList)
{
    try
    {
        if (hList == NULL)
            return 0;

        return CastSizeToInt(((LinksInfo*)hList)->size());
    }
    CATCH_API(hEngine);

    return -2;
}



// ������������ ��� ����� � ������: 0 - ��� ��������� ������, 1 - ��� ��������
// http://www.solarix.ru/api/ru/sol_LinksInfoType.shtml
GREN_API(int) sol_LinksInfoType(HGREN hEngine, HLINKSINFO hList, int Index)
{
    try
    {
        if (hList == NULL)
            return -1;

        const LinksInfo& list = *(LinksInfo*)hList;
        return list[Index]->type;
    }
    CATCH_API(hEngine);

    return -2;
}


// ������������ �������� ��������� ��� ���� ����� (�� ����������� �����).
// http://www.solarix.ru/api/ru/sol_LinksInfoCode.shtml
GREN_API(int) sol_LinksInfoCode(HGREN hEngine, HLINKSINFO hList, int Index)
{
    try
    {
        if (hList == NULL)
            return -1;

        const LinksInfo& list = *(LinksInfo*)hList;
        return list[Index]->code;
    }
    CATCH_API(hEngine);

    return -2;
}


// *************************************************************************
// ������������ ��������� ���� ������ ��� ����� � ������.
// *************************************************************************
GREN_API(int) sol_LinksInfoID(HGREN hEngine, HLINKSINFO hList, int Index)
{
    try
    {
        if (hList == NULL)
            return -1;

        const LinksInfo& list = *(LinksInfo*)hList;
        return list[Index]->id;
    }
    CATCH_API(hEngine);

    return -2;
}


// *************************************************************************
// ����������� ���� ��������� ��� �������� ������ ����� � �����.
// *************************************************************************
GREN_API(int) sol_LinksInfoEKey1(HGREN hEngine, HLINKSINFO hList, int Index)
{
    try
    {
        if (hList == NULL)
            return -1;

        const LinksInfo& list = *(LinksInfo*)hList;
        return list[Index]->ekey1;
    }
    CATCH_API(hEngine);

    return -2;
}


// *************************************************************************
// ����������� ���� ��������� ��� �������� ������ ������ � �����.
// *************************************************************************
GREN_API(int) sol_LinksInfoEKey2(HGREN hEngine, HLINKSINFO hList, int Index)
{
    try
    {
        if (hList == NULL)
            return -1;

        const LinksInfo& list = *(LinksInfo*)hList;
        return list[Index]->ekey2;
    }
    CATCH_API(hEngine);

    return -2;
}



// ********************************************************************
// ������������ ��������� ������������� ����� ��� ����� � ������.
// ���� ����� � ����� ���, �� ������ NULL.
// ********************************************************************
GREN_API(const wchar_t*) sol_LinksInfoTagsTxt(
    HGREN hEngine,
    HLINKSINFO hList,
    int Index
)
{
    try
    {
        if (hList == NULL)
            return NULL;

        const LinksInfo& list = *(LinksInfo*)hList;
        return list[Index]->tags_txt.c_str();
    }
    CATCH_API(hEngine);

    return NULL;
}

GREN_API(const char*) sol_LinksInfoTagsTxt8(
    HGREN hEngine,
    HLINKSINFO hList,
    int Index
)
{
    try
    {
        if (hList == NULL)
            return NULL;

        LinksInfo& list = *(LinksInfo*)hList;

#if defined LEM_THREADS
        lem::Process::CritSecLocker guard(&ENGINE->cs);
#endif

        if (list[Index]->tags_txt8.empty() && !list[Index]->tags_txt.empty())
        {
            list[Index]->tags_txt8 = lem::to_utf8(list[Index]->tags_txt);
        }

        return list[Index]->tags_txt8.c_str();
    }
    CATCH_API(hEngine);

    return NULL;
}

// ********************************************************************
// ������������ ��������� ������������� ������ ������ ��� �����.
// ���� ����� � ����� ���, �� ������ NULL.
// ********************************************************************
GREN_API(const char*) sol_LinksInfoFlagsTxt8(
    HGREN hEngine,
    HLINKSINFO hList,
    int Index
)
{
    try
    {
        if (hList == NULL)
            return NULL;

        LinksInfo& list = *(LinksInfo*)hList;

#if defined LEM_THREADS
        lem::Process::CritSecLocker guard(&ENGINE->cs);
#endif
        if (list[Index]->flags8.empty() && !list[Index]->flags.empty())
        {
            list[Index]->flags8 = lem::to_utf8(list[Index]->flags);
        }

        return list[Index]->flags8.c_str();
    }
    CATCH_API(hEngine);
    return NULL;
}

GREN_API(const wchar_t*) sol_LinksInfoFlagsTxt(
    HGREN hEngine,
    HLINKSINFO hList,
    int Index
)
{
    try
    {
        if (hList == NULL)
            return NULL;

        const LinksInfo& list = *(LinksInfo*)hList;
        return list[Index]->flags.c_str();
    }
    CATCH_API(hEngine);
    return NULL;
}



// *******************************************************************
// �� ��������������� ������ ������� ������ � �����.
// LinkID - ��������� ���� ��������� ������.
// LinkType - 0 ��� ��������� ������, 1 ��� ��������
//
// �����: ����� ���������� ����� ��� ��������� ������ ���������� �����������
// ��� ����� ���������� id ������.
// *******************************************************************
GREN_API(int) sol_DeleteLink(HGREN hEngine, int LinkID, int LinkType)
{
    try
    {
        if (LinkID == -1)
            return -1;

        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        SG_Net &th = sg.Get_Net();

        lem::Ptr<Solarix::TransactionGuard> tx(th.GetStorage().GetTxGuard());
        tx->Begin();

        if (LinkType == 0)
        {
            th.RemoveWordsLink(LinkID);
        }
        else if (LinkType == 1)
        {
            th.RemoveComplexLink(LinkID);
        }

        tx->Commit();

        return 0;
    }
    CATCH_API(hEngine);

    return -1;
}


// ***************************************************************************
// ��������� ����� ������ � ����� ����� ���������� ��� ��������� ��������.
// LinkType=0 ��� ��������� ������, 1 ��� ��������.
// ������������ ID ����������� ������.
//
// �����: ����� ���������� ����� ��� ��������� ������ ���������� �����������
// ��� ����� ���������� id ������.
// ***************************************************************************
GREN_API(int) sol_AddLink(
    HGREN hEngine,
    int LinkType,
    int IE1,
    int LinkCode,
    int IE2,
    const wchar_t *Tags
)
{
    if (hEngine == NULL || IE1 == UNKNOWN || IE2 == UNKNOWN)
        return -2;

    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        SG_Net &th = sg.Get_Net();

        lem::Ptr<Solarix::TransactionGuard> tx(th.GetStorage().GetTxGuard());
        tx->Begin();

        int id_tags = th.LoadTags(Tags);
        int id_link = UNKNOWN;

        if (LinkType == 0)
        {
            id_link = th.AddWordsLink(IE1, LinkCode, IE2, id_tags);
        }
        else
        {
            id_link = th.AddComplexLink(IE1, LinkCode, IE2, id_tags);
        }

        tx->Commit();

        return id_link;
    }
    CATCH_API(hEngine);

    return -1;
}

GREN_API(int) sol_AddLink8(
    HGREN hEngine,
    int LinkType,
    int EntryID1,
    int LinkCode,
    int EntryID2,
    const char *TagsUtf8
)
{
    lem::UFString w(lem::from_utf8(TagsUtf8));
    return sol_AddLink(hEngine, LinkType, EntryID1, LinkCode, EntryID2, w.c_str());
}



// Manual page: http://www.solarix.ru/api/en/sol_SetLinkFlags.shtml
// ��������:    http://www.solarix.ru/api/ru/sol_SetLinkFlags.shtml
GREN_API(int) sol_SetLinkFlags(
    HGREN hEngine,
    int id_link,
    const wchar_t *Flags
)
{
    if (hEngine == NULL || id_link == UNKNOWN)
        return -2;

    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        SG_Net &th = sg.Get_Net();

        lem::Ptr<Solarix::TransactionGuard> tx(th.GetStorage().GetTxGuard());
        tx->Begin();

        if (lem::lem_is_empty(Flags))
        {
            th.ClearLinkFlags(id_link);
        }
        else
        {
            lem::UFString str(Flags);
            lem::Collect< lem::UFString > pairs;
            lem::parse(str, pairs, L" ");

            for (lem::Container::size_type i = 0; i < pairs.size(); ++i)
            {
                lem::Collect<lem::UFString> toks;
                lem::parse(pairs[i], toks, L"=");
                const lem::UFString &flag = toks[0];
                const lem::UFString &val = toks[1];
                SG_LinkFlag x(UNKNOWN, flag, val);
                th.StoreLinkFlag(id_link, x);
            }
        }

        tx->Commit();

        return 0;
    }
    CATCH_API(hEngine);

    return -1;
}

GREN_API(int) sol_SetLinkFlags8(
    HGREN hEngine,
    int id_link,
    const char *FlagsUtf8
)
{
    lem::UFString w(lem::from_utf8(FlagsUtf8));
    return sol_SetLinkFlags(hEngine, id_link, w.c_str());
}



// Manual page: http://www.solarix.ru/api/ru/sol_SetLinkTags.shtml
// ��������:    http://www.solarix.ru/api/en/sol_SetLinkTags.shtml
GREN_API(int) sol_SetLinkTags(
    HGREN hEngine,
    int LinkType,
    int link_id,
    const wchar_t *Tags
)
{
    if (hEngine == NULL || link_id == -1)
        return -2;

    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        SG_Net &th = sg.Get_Net();

        lem::Ptr<Solarix::TransactionGuard> tx(th.GetStorage().GetTxGuard());
        tx->Begin();

        int tags = th.LoadTags(Tags);

        if (LinkType == 0)
        {
            th.SetLinkTags(link_id, tags);
        }
        else
        {
            th.SetComplexLinkTags(link_id, tags);
        }

        tx->Commit();

        return 0;
    }
    CATCH_API(hEngine);

    return -1;
}


GREN_API(int) sol_SetLinkTags8(
    HGREN hEngine,
    int LinkType,
    int LinkID,
    const char *TagsUtf8
)
{
    lem::UFString w(lem::from_utf8(TagsUtf8));
    return sol_SetLinkTags(hEngine, LinkType, LinkID, w.c_str());
}


// *********************************************************
//
// http://www.solarix.ru/api/en/sol_GetPhraseText.shtml
//
// ������������ ����� �������� ������ �� �� �����.
// ������������ ��������� ����� ���������� ������� sol_Free;
// *********************************************************
GREN_API(wchar_t*) sol_GetPhraseText(HGREN hEngine, int PhraseId)
{
    if (hEngine == NULL || PhraseId == UNKNOWN)
        return NULL;

    try
    {
        SG_Phrase f;
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        if (sg.GetStorage().GetPhrase(PhraseId, f))
        {
            const int len = f.GetText().length();
            wchar_t *str = (wchar_t*)malloc(sizeof(wchar_t)*(len + 1));
            lem::lem_strcpy(str, f.GetText().c_str());
            return str;
        }
        else
        {
            return NULL;
        }
    }
    catch (...)
    {
        return NULL;
    }
}



// http://www.solarix.ru/api/en/sol_GetPhraseText.shtml
GREN_API(char*) sol_GetPhraseText8(HGREN hEngine, int PhraseId)
{
    if (hEngine == NULL || PhraseId == UNKNOWN)
        return NULL;

    try
    {
        SG_Phrase f;
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        if (sg.GetStorage().GetPhrase(PhraseId, f))
        {
            lem::FString utf8 = to_utf8(f.GetText());
            const int len = utf8.length();
            char *str = (char*)malloc(len + 1);
            lem::lem_strcpy(str, utf8.c_str());
            return str;
        }
        else
        {
            return NULL;
        }
    }
    catch (...)
    {
        return NULL;
    }
}


// http://www.solarix.ru/api/en/sol_GetPhraseLanguage.shtml
GREN_API(int) sol_GetPhraseLanguage(HGREN hEngine, int PhraseId)
{
    if (hEngine == NULL || PhraseId == UNKNOWN)
        return NULL;

    try
    {
        SG_Phrase f;
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        if (sg.GetStorage().GetPhrase(PhraseId, f))
        {
            return f.GetLanguage();
        }
        else
        {
            return -1;
        }
    }
    CATCH_API(hEngine);

    return -2;
}


// http://www.solarix.ru/api/en/sol_GetPhraseClass.shtml
GREN_API(int) sol_GetPhraseClass(HGREN hEngine, int PhraseId)
{
    if (hEngine == NULL || PhraseId == UNKNOWN)
        return NULL;

    try
    {
        SG_Phrase f;
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        if (sg.GetStorage().GetPhrase(PhraseId, f))
        {
            return f.GetClass();
        }
        else
        {
            return -1;
        }
    }
    CATCH_API(hEngine);

    return -2;
}


// ****************************************************
// Create new phrasal entry in lexicon.
// ****************************************************
// http://www.solarix.ru/api/en/sol_AddPhrase.shtml
GREN_API(int) sol_AddPhrase(HGREN hEngine, const wchar_t *Phrase, int LanguageID, int ClassID, int Flags)
{
    if (hEngine == NULL || lem::lem_is_empty(Phrase))
        return -2;

    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();

        lem::Ptr<Solarix::TransactionGuard> tx(sg.GetStorage().GetTxGuard());
        tx->Begin();

        SG_Phrase frz(Phrase, LanguageID, ClassID, 0);
        int id = sg.GetStorage().AddPhrase(frz);

        tx->Commit();

        return frz.GetId();
    }
    CATCH_API(hEngine);

    return -1;
}


// http://www.solarix.ru/api/en/sol_AddPhrase.shtml
GREN_API(int) sol_AddPhrase8(HGREN hEngine, const char *Phrase, int Language, int Class, int Flags)
{
    return sol_AddPhrase(hEngine, lem::from_utf8(Phrase).c_str(), Language, Class, Flags);
}


// http://www.solarix.ru/api/en/sol_DeletePhrase.shtml
GREN_API(int) sol_DeletePhrase(HGREN hEngine, int PhraseId)
{
    if (hEngine == NULL || PhraseId == UNKNOWN)
        return -2;

    int res = -1;
    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();

        lem::Ptr<Solarix::TransactionGuard> tx(sg.GetStorage().GetTxGuard());
        tx->Begin();

        sg.GetStorage().DeletePhrase(PhraseId);

        tx->Commit();

        res = 0;
    }
    CATCH_API(hEngine);

    return -1;
}


GREN_API(int) sol_SetPhraseNote(
    HGREN hEngine,
    int PhraseId,
    const wchar_t *Name,
    const wchar_t *Value
)
{
    if (hEngine == NULL || PhraseId == UNKNOWN || lem::lem_is_empty(Name))
        return -2;

    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();

        int tn_type = -1;
        if (lem::lem_eqi(Name, L"pivot"))
        {
            tn_type = Solarix::SynGram::PivotNote;
        }

        if (tn_type == -1)
            return -3;

        lem::Ptr<TransactionGuard> tx(sg.GetStorage().GetTxGuard());

        SG_PhraseNote note;
        int tn_id = sg.GetStorage().GetPhraseNote(PhraseId, tn_type, note);

        tx->Begin();

        if (lem::lem_is_empty(Value))
        {
            if (tn_id != -1)
                sg.GetStorage().DeletePhraseNote(tn_id);
        }
        else
        {
            if (tn_id != -1)
                sg.GetStorage().DeletePhraseNote(tn_id);

            tn_id = sg.GetStorage().AddPhraseNote(PhraseId, tn_type, Value);
        }

        tx->Commit();

        return tn_id;
    }
    CATCH_API(hEngine);

    return 0;
}




GREN_API(int) sol_ProcessPhraseEntry(
    HGREN hEngine,
    int PhraseId,
    const wchar_t *Scenario,
    int Language,
    wchar_t DelimiterChar
)
{
    if (hEngine == NULL || PhraseId == UNKNOWN || lem::lem_is_empty(Scenario))
        return -2;

    try
    {
        Solarix::Dictionary * dict = HandleEngine(hEngine)->dict.get();

        ThesaurusNotesProcessor proc(dict);

        proc.SetLanguage(Language);
        proc.SetScenario(Scenario);
        proc.SetSegmentationDelimiter(DelimiterChar);

        lem::Ptr<TransactionGuard> tx(dict->GetSynGram().GetStorage().GetTxGuard());
        tx->Begin();

        std::pair<bool, bool> res = proc.ProcessPhrase(PhraseId);

        tx->Commit();

        if (res.second == true)
            return -1; // ���� ������

        if (res.first == true)
            return 1; // ����������

        return 0; // ������ ����� ����������� ������ � TNOTES ��� �������.
    }
    CATCH_API(hEngine);

    return -1;
}



// ���������� ����� ��������� ������ �� �� ���������� ��������.
// ������������ ���� ��������� ������, ���� -1 ��� ������������� ������
GREN_API(int) sol_AddWord(HGREN hEngine, const wchar_t *Txt)
{
    try
    {
        int id = UNKNOWN;

#if defined SOL_LOADTXT
        UFString txt(Txt);
        lem::StrParser<lem::UFString> parser(txt);
        Solarix::Dictionary * dict = HandleEngine(hEngine)->dict.get();
        SynGram & sg = dict->GetSynGram();

        lem::Ptr<Solarix::TransactionGuard> tx(sg.GetStorage().GetTxGuard());
        tx->Begin();

        int ekey = sg.LoadEntry(parser);

        if (ekey != UNKNOWN)
        {
            id = ekey;

            tx->Commit();
        }
#endif

        return id;
    }
    CATCH_API(hEngine);

    return -1;
}


GREN_API(int) sol_AddWord8(HGREN hEngine, const char *Txt)
{
    return sol_AddWord(hEngine, lem::from_utf8(Txt).c_str());
}


// ******************************************************************************************
// ������������ ������ ������ ��������� (EntryType=0) ��� �������� (EntryType=1) ������,
// ������� ������������� �������� ����������:
// Flags - ��� ������� ����������, �������� ������ ������:
//         0x00000000 ����� �� ����������� ��������� � ������ ������������� ��������, ��������� ��� �������� ������
//         0x00000001 ���� ����� ���������������� � �������� ����� �� ����������� ���������
//         0x00010000 ���� ����� ����� �� ��������� ����� ��������� ������ ��� ������ ��������
//
// EntryType - 0 ��� ��������� ������, 1 ��� ��������
// Mask - ���������� ��������� ��� ������������� � ������ ������, 
// Language - ��� ����� (-1 �������� ���������� ����������)
// Class - �������������� �����, �� ���� ID ����� ���� (-1 �������� �����)
//
// Manual page: http://www.solarix.ru/api/en/sol_ListEntries.shtml
// ******************************************************************************************
GREN_API(HGREN_INTARRAY) sol_ListEntries(
    HGREN hEngine,
    int Flags,
    int EntryType,
    const wchar_t *Mask,
    int Language,
    int Class
)
{
    if (hEngine == NULL)
        return NULL;

#if !defined SOLARIX_DEMO
    try
    {
        lem::MCollect<int> *list = new lem::MCollect<int>();
        list->reserve(32);

        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        SG_Net &th = sg.Get_Net();

        boost::wregex mask_rx;
        bool use_rx = false;

        if ((Flags & 0x00010000) == 0x00000000)
        {
            if (!lem::lem_is_empty(Mask))
            {
                if (Flags == 1)
                    mask_rx = boost::wregex(Mask);
                else
                    mask_rx = boost::wregex(Mask, boost::regex_constants::icase);

                use_rx = true;
            }
        }

        if (EntryType == 0)
        {
            lem::Ptr<WordEntryEnumerator> wenum;

            if ((Flags & 0x00010000) == 0x00010000)
            {
                UCString exact(Mask);
                exact.to_upper();
                wenum = sg.GetEntries().ListEntries(exact, ANY_STATE);
            }
            else
            {
                wenum = sg.GetEntries().ListEntries();
            }

            while (wenum->Fetch())
            {
                const Solarix::SG_Entry &e = wenum->GetItem();

                if (!lem::lem_is_empty(Mask) && use_rx)
                {
                    if (!boost::regex_match(e.GetName().c_str(), mask_rx))
                        continue;
                }

                if (Class != UNKNOWN || Language != UNKNOWN)
                {
                    const int is_class = e.GetClass();

                    if (Class != UNKNOWN && is_class != Class)
                        continue;

                    if (Language != UNKNOWN)
                    {
                        if (lem::is_quantor(is_class))
                            continue;

                        const SG_Class & c = sg.GetClass(is_class);
                        if (c.GetLanguage() != Language)
                            continue;
                    }
                }

                list->push_back(e.GetKey());
            }
        }
        else if (EntryType == 1)
        {
            lem::Ptr<Solarix::PhraseEnumerator> phrases;

            phrases = sg.GetComplexEntries();

            while (phrases->Fetch())
            {
                const int te_id = phrases->GetPhraseId();

                SG_Phrase f;
                if (sg.GetStorage().GetPhrase(te_id, f))
                {
                    if (!lem::lem_is_empty(Mask) && use_rx)
                    {
                        if (!boost::regex_match(f.GetText().c_str(), mask_rx))
                            continue;
                    }

                    if (Class != UNKNOWN && f.GetClass() != Class)
                        continue;

                    if (Language != UNKNOWN && f.GetLanguage() != Language)
                        continue;

                    list->push_back(te_id);
                }
            }
        }

        return (HGREN_INTARRAY)list;
    }
    catch (...)
    {
        return NULL;
    }
#else
    return NULL;
#endif
}



GREN_API(HGREN_INTARRAY) sol_ListEntries8(
    HGREN hEngine,
    int Flags,
    int EntryType,
    const char *MaskUtf8,
    int Language,
    int Class
)
{
    return sol_ListEntries(hEngine, Flags, EntryType, lem::from_utf8(MaskUtf8).c_str(), Language, Class);
}


GREN_API(int) sol_SaveDictionary(HGREN hEngine, int Flags, const wchar_t *Folder)
{
    if (hEngine == NULL)
        return -1;

#if defined SOL_SAVEBIN && !defined SOLARIX_DEMO
    try
    {
        if ((Flags & 0x00000002))
        {
            SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();

            lem::Xml::Parser p;
            p.Load(HandleEngine(hEngine)->dict->dictionary_xml);

            lem::Path db_file;
            const lem::Xml::Node * nod = p.Find_By_Path(L"dataroot.morphology");
            if (nod != NULL && nod->GetBody().empty() == false)
            {
                db_file = lem::lem_is_empty(Folder) ? HandleEngine(hEngine)->dict->xml_base_path : lem::Path(Folder);
                db_file.ConcateLeaf(lem::Path(nod->GetBody()));

                lem::BinaryWriter bin(db_file);
                HandleEngine(hEngine)->dict->SaveBin(bin);
            }
        }
    }
    catch (...)
    {
        return -2;
    }
    return 0;
#else
    return -1;
#endif
}


GREN_API(int) sol_ReserveLexiconSpace(HGREN hEngine, int n)
{
    if (hEngine == NULL || n < 1)
        return -1;

    try
    {
        HandleEngine(hEngine)->n_lexicon_reserve = n;
        return 0;
    }
    catch (...)
    {
        return -2;
    }
}



// http://www.solarix.ru/api/ru/sol_ListPartsOfSpeech.shtml
GREN_API(HGREN_INTARRAY) sol_ListPartsOfSpeech(HGREN hEngine, int Language)
{
    try
    {
        lem::MCollect<int> *list = new lem::MCollect<int>();
        list->reserve(32);

        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        lem::Ptr<ClassEnumerator> e(sg.classes().Enumerate());

        while (e->Fetch())
        {
            if (Language < 0)
                list->push_back(e->GetId());
            else
            {
                const SG_Class &c = sg.GetClass(e->GetId());
                if (c.GetLanguage() == Language)
                {
                    list->push_back(e->GetId());
                }
            }
        }

        return list;
    }
    CATCH_API(hEngine);

    return NULL;
}


// http://www.solarix.ru/api/ru/sol_GetEntryFreq.shtml
GREN_API(int) sol_GetEntryFreq(HGREN hEngine, int EntryID)
{
    try
    {
        SynGram &sg = HandleEngine(hEngine)->dict->GetSynGram();
        const SG_Entry & e = sg.GetEntry(EntryID);
        int freq = e.GetFreq();
        return freq;
    }
    CATCH_API(hEngine);

    return -1;
}



GREN_API(int) sol_FindTagW(HGREN hEngine, const wchar_t *TagName)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || lem::lem_is_empty(TagName))
        return -2;

    try
    {
        int tag_id = HandleEngine(hEngine)->dict->GetSynGram().Get_Net().FindTag(TagName);
        return tag_id;
    }
    CATCH_API(hEngine);

    // Internal error
    return -2;
}



GREN_API(int) sol_FindTagValueW(HGREN hEngine, int TagID, const wchar_t *ValueName)
{
    if (hEngine == NULL || !HandleEngine(hEngine)->dict || lem::lem_is_empty(ValueName))
        return -2;

    try
    {
        int value_id = HandleEngine(hEngine)->dict->GetSynGram().Get_Net().FindTagValue(TagID, ValueName);
        return value_id;
    }
    CATCH_API(hEngine);
    return -2;
}


struct SolSpokenData
{

};

//typedef SolSpokenData* HGREN_SPOKEN;

GREN_API(HGREN_SPOKEN) sol_PronounceW(HGREN hEngine, const wchar_t * Sentence, int LanguageID, int AnalysisFlags, int SynthesisFlags, void * VoiceOptions)
{
    try
    {
#if defined SOL_SPEAKER

        Speaker * speaker = HandleEngine(hEngine)->dict->GetSpeaker();
        speaker->Say(phrase, LanguageID == UNKNOWN ? HandleEngine(hEngine)->DefaultLanguage : LanguageID);

#endif

        return NULL;
    }
    CATCH_API(hEngine);

    return NULL;
    }


GREN_API(int) sol_DeleteSpoken(HGREN_SPOKEN hData)
{
    try
    {
        delete (SolSpokenData*)hData;
        return 0;
    }
    catch (...)
    {
        return -2;
    }
}


GREN_API(const char*) sol_RenderSyntaxTree8(HGREN hEngine, HGREN_RESPACK hSyntaxTree, int RenderOptions)
{
    if (hSyntaxTree == NULL)
        return NULL;

    const Res_Pack * pack = (const Solarix::Res_Pack*)hSyntaxTree;

    lem::MemFormatter mem;
    Solarix::print_syntax_tree(L"", *pack, *HandleEngine(hEngine)->dict, mem, false, true);
    lem::UFString str = mem.string();
    lem::FString utf8(lem::to_utf8(str));
    char * res = (char*)malloc(utf8.length() + 1);
    strcpy(res, utf8.c_str());
    return res;
}


GREN_API(void*) sol_OpenCorpusStorage8(HGREN hEngine, const char * filename, int for_writing)
{
    if (for_writing)
        return new lem::BinaryFile(lem::Path(lem::from_utf8(filename)), false, true);
    else
        return new lem::BinaryFile(lem::Path(lem::from_utf8(filename)), true, false);
}

GREN_API(int) sol_CloseCorpusStorage(HGREN hEngine, void * file_handle)
{
    delete (lem::BinaryFile*)file_handle;
    return 0;
}

GREN_API(int) sol_WriteSyntaxTree(HGREN hEngine, void * file_handle, const wchar_t * sentence, HGREN_RESPACK respack)
{
    lem::BinaryFile & file = *(lem::BinaryFile*)file_handle;

    int guard = 0xdeadbeef;
    file.write(&guard, sizeof(guard));

    int str_len = wcslen(sentence);
    file.write(&str_len, sizeof(str_len));
    file.write(sentence, sizeof(wchar_t)*(str_len + 1));

    const Solarix::Res_Pack * pack = (const Solarix::Res_Pack*)respack;
    pack->SaveBin(file);

    return 0;
}


struct SyntaxTreeStreamData
{
    Solarix::Res_Pack * pack;
    wchar_t * sentence;

    SyntaxTreeStreamData() : pack(NULL), sentence(NULL) {}
    ~SyntaxTreeStreamData()
    {
        delete pack;
        delete[] sentence;
    }
};


GREN_API(void*) sol_LoadSyntaxTree(HGREN hEngine, void * file_handle)
{
    lem::BinaryFile & file = *(lem::BinaryFile*)file_handle;

    int guard = file.read_int();

    int str_len = 0;
    file.read(&str_len, sizeof(str_len));

    if (file.eof())
        return NULL;

    SyntaxTreeStreamData * data = new SyntaxTreeStreamData();

    data->sentence = new wchar_t[str_len + 1];
    file.read(data->sentence, sizeof(wchar_t)*(str_len + 1));

    data->pack = new Solarix::Res_Pack();
    data->pack->LoadBin(file);

    return data;
}


GREN_API(const wchar_t*) sol_GetSentenceW(void * ptr)
{
    const wchar_t * src = ((SyntaxTreeStreamData*)ptr)->sentence;
#if defined LEM_WINDOWS
    wchar_t * marshal_str = (wchar_t*)::CoTaskMemAlloc((wcslen(src) + 1) * sizeof(wchar_t));
#else  
    wchar_t * marshal_str = (wchar_t*)malloc((wcslen(src) + 1) * sizeof(wchar_t));
#endif
    wcscpy(marshal_str, src);
    return marshal_str;
}

GREN_API(HGREN_RESPACK) sol_GetTreeHandle(void * ptr)
{
    return ((SyntaxTreeStreamData*)ptr)->pack;
}


GREN_API(int) sol_FreeSyntaxTree(void * tree)
{
    delete (SyntaxTreeStreamData*)tree;
    return 0;
}



GREN_API(HGREN_STR) sol_ListEntryForms(HGREN hEngine, int EntryKey)
{
    GREN_Strings *res = new GREN_Strings;

    const SG_Entry &e = HandleEngine(hEngine)->dict->GetSynGram().GetEntry(EntryKey);

    for (lem::Container::size_type i = 0; i < e.forms().size(); ++i)
    {
        const SG_EntryForm &f = e.forms()[i];

        if (res->list.find(f.name().c_str()) == UNKNOWN)
            res->list.push_back(f.name().c_str());
    }

    return res;
}



GREN_API(HGREN_RESPACK) sol_CreateLinkages(HGREN hEngine)
{
    Solarix::Res_Pack * pack = new Solarix::Res_Pack();
    return pack;
}

GREN_API(HGREN_LINKAGE) sol_CreateLinkage(HGREN hEngine, HGREN_RESPACK hLinkages)
{
    Solarix::Variator * linkage = new Solarix::Variator();
    ((Res_Pack*)hLinkages)->Add(linkage);
    return linkage;
}


GREN_API(int) sol_AddNodeToLinkage(HGREN hEngine, HGREN_LINKAGE hLinkage, HGREN_TREENODE hNode)
{
    ((Variator*)hLinkage)->Add((Tree_Node*)hNode);
    return 0;
}

GREN_API(int) sol_AddBeginMarker(HGREN hEngine, HGREN_LINKAGE hLinkage)
{
    Solarix::Dictionary & dict = *HandleEngine(hEngine)->dict;
    Word_Form *wf = new Predef_Word_Form(dict.GetSynGram().I_BEGIN, dict.GetSynGram());
    Tree_Node * begin_node = new Tree_Node(wf, true);
    ((Variator*)hLinkage)->Add(begin_node);

    return 0;
}

GREN_API(int) sol_AddEndMarker(HGREN hEngine, HGREN_LINKAGE hLinkage)
{
    Solarix::Dictionary & dict = *HandleEngine(hEngine)->dict;
    Word_Form *wf = new Predef_Word_Form(dict.GetSynGram().I_END, dict.GetSynGram());
    Tree_Node * begin_node = new Tree_Node(wf, true);
    ((Variator*)hLinkage)->Add(begin_node);
    return 0;
}


GREN_API(HGREN_TREENODE) sol_CreateTreeNodeW(HGREN hEngine, int id_entry, const wchar_t *word, int n_pair, const int * pairs)
{
    Solarix::Dictionary & dict = *HandleEngine(hEngine)->dict;

    RC_Lexem rc_word(new Lexem(word));

    RC_Lexem normalized(new Lexem(word));
    dict.GetLexAuto().TranslateLexem(*normalized, true, dict.GetDefaultLanguage());

    CP_Array cpx;

    for (int i = 0; i < n_pair; ++i)
    {
        int id_coord = pairs[i * 2];
        int id_state = pairs[i * 2 + 1];

        cpx.push_back(Solarix::GramCoordPair(id_coord, id_state));
    }

    Solarix::Word_Form * wf = new Solarix::Word_Form(rc_word, normalized, id_entry, cpx, 0);

    Solarix::Tree_Node * node = new Solarix::Tree_Node(wf, true);

    return node;
}



#endif
