#ifndef SOLARIX_GRAMMAR_ENGINE__H
#define SOLARIX_GRAMMAR_ENGINE__H
#pragma once

// -----------------------------------------------------------------------------
// File SOLARIX_GRAMMAR_ENGINE.H
//
// (c) by Elijah Koziev
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://www.wordysoft.com 
//
// Manual page: http://www.solarix.ru/for_developers/grammar-engine-api.shtml
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine API functions.
// API для доступа к грамматическому движку, Windows & Linux & Mac OS X, 32/64
//
// Коды грамматических категорий (индексы классов, координат, состояний и т.д.)
// объявлены в виде символических констант в файле _sg_api.h, который
// генерируется компилятором YGRES.
//
// 09.10.2006 - рефакторинг, в именах процедур API убраны подчеркивания кроме
//              префикса "sol_"
//
// 09.10.2006 - начало интеграции расширенных регулярных выражений (RegexEx)
//
// 12.10.2006 - введена процедура sol_TranslateToBase - слово преобразует к
//              базовой форме. 
//
// 15.10.2006 - компоненты грамматического и поискового движка объединены.
//
// 21.11.2006 - в процедуру sol_TranslateToBase добавлен вызов стеммера.
//
// 05.05.2007 - changing API to implement a new multithreading features of
//              the search engine.
//
// 08.09.2007 - API версий PRO и LITE сделаны полностью идентичными,
//              неподдерживаемые в LITE процедуры являются заглушками.
//
// 27.09.2007 - добавлена sol_GetResultW для получения строки результатов в wchar_t
// 13.11.2008 - добавлены sol_CreatePortableSearcher и sol_AttachPortableIndex
// 15.11.2008 - генератор текста полностью переехал сюда
// 03.02.2009 - добавлен флаг FG_OMIT_FREQ1 для игнорирования в синонимизаторе
//              N-грамм с единичной частотой.
// 13.02.2009 - добавлен API модуля SentenceBroker
// 24.02.2009 - функция sol_EnumInClass возвращает 3 для тэгов
// 25.02.2009 - добавлена sol_PreloadNGramsCaches
// 02.03.2009 - для sol_Tokenize и sol_CreateSentenceBroker добавлено указание
//              языка.
// 08.04.2009 - удален sol_PreloadNGramsCaches
// 10.04.2009 - переделан API синонимизатора (sol_Paraphrase)
// 20.07.2009 - переработка API доступа к базе N-грамм: убрана sol_SeekNGrams,
//              добавлены sol_Seek2Grams, sol_Seek3Grams, sol_Seek4Grams,
//              sol_Seek5Grams
// 03.11.2009 - добавлена процедура sol_MorphologyAnalysis для выполнения
//              морфологического анализа с учетом контекста.
// 22.07.2010 - добавлена множество процедур для поддержки работы переводчика,
//              в том числе sol_ListLinksTxt, sol_FindPhrase, sol_ListEntries,
//              и множество других.
// 15.09.2010 - переработана сигнатура sol_TranslatePhrase, добавлены 
//              sol_DeleteTranslation и др.
// 04.04.2011 - добавлены sol_MorphologyAnalysisA и sol_SyntaxAnalysisA
// 30.07.2011 - добавлена функция sol_GenerateWordforms для вывода всех
//              форм слова, удовлетворяющих указанным грамматическим признакам
// 28.08.2012 - добавлен флаг включения итерационного анализа SOL_GREN_SPARSE
// 12.02.2013 - в sol_MorphologyAnalysis и sol_SyntaxAnalysis изменена семантика
//              параметра таймаута - теперь старшие 10 битов задают максимальное
//              число проверяемых при нисходящем разборе альтернативных путей, а
//              младшие 22 бита - макс. таймаут в миллисекундах.
// -----------------------------------------------------------------------------
//
// CD->20.06.2005
// LC->28.03.2016
// --------------

#if defined DLL_EXPORTS || defined FAIND_IENGINES
 #define FAIND_EXPORTS
#else
 #define FAIND_IMPORTS
#endif

#undef DLL_ENTRY

#if defined FAIND_IMPORTS
 #if defined LEM_WINDOWS || defined WIN32
  #define FAIND_API(RetType) extern RetType __stdcall
  #define SX_STDCALL __stdcall
 #else

  #if defined __cplusplus
  #define FAIND_API(RetType) extern "C" RetType
  #else
  #define FAIND_API(RetType) extern RetType
  #endif

  #define SX_STDCALL
 #endif
#elif defined GREN_EXPORTS || defined FAIND_EXPORTS
 #if defined LEM_WINDOWS || defined WIN32
  #define FAIND_API(RetType) __declspec(dllexport) RetType __stdcall
  #define SX_STDCALL __stdcall
 #else
  #if defined __cplusplus
  #define FAIND_API(RetType) extern "C" RetType __attribute__((visibility("default")))
  #else
  #define FAIND_API(RetType) extern RetType __attribute__((visibility("default")))
  #endif
  #define SX_STDCALL
 #endif
#else
 #error
#endif

#if !defined FAIND_INTERNAL_TYPES

 typedef void* HFAIND;

 typedef void* HSOL_INDEXER;
 typedef void* HGRENCMD;
 typedef void* HGRENXML;
 typedef void* HREGEXEX;
 typedef void* HGRENPARAMS;

 typedef void* HGREN_STR;
 typedef void* HGREN_INTARRAY;
 typedef void* HGREN_WCOORD;
 typedef void* HGREN_RESPACK;
 typedef void* HGREN_LINKAGE;
 typedef const void* HGREN_TREENODE;
 typedef void* HGREN_PHRASOMAT;
 typedef void* HGREN_FGTEMPLATE;
 typedef void* HGREN_SBROKER;

 typedef void* HGREN_SPOKEN;
 typedef void* HGREN_LONGSTRING;

#endif // !defined DLL_EXPORTS

#define HGREN HFAIND

typedef void* HFLEXIONS;
typedef void* HFLEXIONTABLE;

typedef void* HLINKSINFO;
typedef void* HTRANINFO;


// Instance creation flags for sol_CreateGrammarEngineEx and sol_LoadDictionaryEx
#define SOL_GREN_LAZY_LEXICON 0x00000001


// Create the instance of grammatical dictionary and connecti it to the database
// http://www.solarix.ru/api/en/sol_CreateGrammarEngine.shtml

FAIND_API(HGREN) sol_CreateGrammarEngineW( const wchar_t *DictionaryXml );
FAIND_API(HGREN) sol_CreateGrammarEngineA( const char *DictionaryXml );
FAIND_API(HGREN) sol_CreateGrammarEngine8( const char *DictionaryXmlUtf8 );
#if defined UNICODE || defined _UNICODE 
#define sol_CreateGrammarEngine sol_CreateGrammarEngineW
#else
#define sol_CreateGrammarEngine sol_CreateGrammarEngineA
#endif

FAIND_API(HGREN) sol_CreateGrammarEngineExW( const wchar_t *DictionaryXml, int Flag );
FAIND_API(HGREN) sol_CreateGrammarEngineExA( const char *DictionaryXml, int Flag );
FAIND_API(HGREN) sol_CreateGrammarEngineEx8( const char *DictionaryXmlUtf8, int Flag );
#if defined UNICODE || defined _UNICODE
#define sol_CreateGrammarEngineEx sol_CreateGrammarEngineExW
#else
#define sol_CreateGrammarEngineEx sol_CreateGrammarEngineExA
#endif


typedef HGREN (SX_STDCALL * sol_CreateGrammarEngine8_Fun)( const char *DictionaryXmlUtf8 );
typedef HGREN (SX_STDCALL * sol_CreateGrammarEngineEx8_Fun)( const char *DictionaryXmlUtf8, int Flag );


// Destroy the instance of grammatical dicrionary and free all allocated resources
// http://www.solarix.ru/api/en/sol_DeleteGrammarEngine.shtml
FAIND_API(int) sol_DeleteGrammarEngine( HGREN hEngine );

typedef int (SX_STDCALL * sol_DeleteGrammarEngine_Fun)( HGREN hEngine );


// Load the dictionary (morphology and syntax analyzer + thesaurus)
// http://www.solarix.ru/api/en/sol_LoadDictionary.shtml
FAIND_API(int) sol_LoadDictionaryA( HGREN hEngine, const char *Filename );
FAIND_API(int) sol_LoadDictionaryW( HGREN hEngine, const wchar_t *Filename );
FAIND_API(int) sol_LoadDictionary8( HGREN hEngine, const char *FilenameUtf8 );
#if defined UNICODE || defined _UNICODE 
#define sol_LoadDictionary sol_LoadDictionaryW
#else
#define sol_LoadDictionary sol_LoadDictionaryA
#endif


FAIND_API(int) sol_LoadDictionaryExA( HGREN hEngine, const char *Filename, int Flags );
FAIND_API(int) sol_LoadDictionaryExW( HGREN hEngine, const wchar_t *Filename, int Flags );
FAIND_API(int) sol_LoadDictionaryEx8( HGREN hEngine, const char *FilenameUtf8, int Flags );
#if defined UNICODE || defined _UNICODE 
#define sol_LoadDictionaryEx sol_LoadDictionaryExW
#else
#define sol_LoadDictionaryEx sol_LoadDictionaryExA
#endif

typedef int (SX_STDCALL * sol_LoadDictionaryEx8_Fun)( HGREN hEngine, const char *FilenameUtf8, int Flags );


// http://www.solarix.ru/api/en/sol_UnloadDictionary.shtml
FAIND_API(void) sol_UnloadDictionary( HGREN hEngine );
typedef int (SX_STDCALL * sol_UnloadDictionary_Fun)( HGREN hEngine );


// Return the Solarix project version info.
// Если указатели Major, Minor, Build не равны NULL, то через них
// возвращаются соответствующие части номера версии компонента.
//
// Возвращает 0 для DEMO, 1 для PRO, 2 для PREMIUM
FAIND_API(int) sol_GetVersion( HGREN hEngine, int *Major, int *Minor, int *Build );
typedef int (SX_STDCALL * sol_GetVersion_Fun)( HGREN hEngine, int *Major, int *Minor, int *Build );

// Возвращает номер версии загруженного словаря.
// http://www.solarix.ru/api/en/sol_DictionaryVersion.shtml
FAIND_API(int) sol_DictionaryVersion( HGREN hEngine );
typedef int (SX_STDCALL * sol_DictionaryVersion_Fun)( HGREN hEngine );


// Returns the value indicating whether the dictionary has been initialized and loaded
// http://www.solarix.ru/api/en/sol_IsDictionaryLoaded.shtml
FAIND_API(int) sol_IsDictionaryLoaded( HGREN hEngine );


// Count the total number of entries in dictionary.
// Сколько словарных статей в словаре.
// http://www.solarix.ru/api/ru/sol_CountEntries.shtml
FAIND_API(int) sol_CountEntries( HGREN hEngine );
typedef int (SX_STDCALL * sol_CountEntries_Fun)( HGREN hEngine );

// Count the total number of wordforms in dictionary.
// Сколько грамматических форм по всем словарным статьям в лексиконе
FAIND_API(int) sol_CountForms( HGREN hEngine );

// Статистика тезауруса: сколько записей всего.
// http://www.solarix.ru/api/ru/sol_CountLinks.shtml
FAIND_API(int) sol_CountLinks( HGREN hEngine );

// Returns the max lexem length
// Возвращает максимальную длину лексемы
// http://www.solarix.ru/api/en/sol_MaxLexemLen.shtml
FAIND_API(int) sol_MaxLexemLen( HGREN hEngine );
FAIND_API(int) sol_MaxLexemLen8( HGREN hEngine );
typedef int (SX_STDCALL * sol_MaxLexemLen8_Fun)( HGREN hEngine );

// *******************************************
// Set the default language ID.
// Устанавливает язык по умолчанию. Целочисленный код языка
// можно увидеть в файле _sg_api.h
// *******************************************
FAIND_API(int) sol_SetLanguage( HGREN hEngine, int Language );



// Поиск связей в тезаурусе
FAIND_API(HGREN_INTARRAY) sol_SeekThesaurus(
                                            HGREN hEngine,
                                            int iEntry,
                                            int Synonyms,
                                            int Grammar_Links,
                                            int Translations,
                                            int Semantics,
                                            int nJumps
                                           );

// http://www.solarix.ru/api/en/sol_Thesaurus.shtml
FAIND_API(HGREN_INTARRAY) sol_Thesaurus( HGREN hEngine, int EntryID, int LinkType );

// http://www.solarix.ru/api/en/sol_ListLinksTxt.shtml
FAIND_API(HLINKSINFO) sol_ListLinksTxt( HGREN hEngine, int EntryID1, int LinkType, int Flags );

// http://www.solarix.ru/api/en/sol_DeleteLinksInfo.shtml
FAIND_API(int) sol_DeleteLinksInfo( HGREN hEng, HLINKSINFO hList );

// http://www.solarix.ru/api/en/sol_LinksInfoCount.shtml
FAIND_API(int) sol_LinksInfoCount( HGREN hEng, HLINKSINFO hList );

// http://www.solarix.ru/api/en/sol_LinksInfoType.shtml
FAIND_API(int) sol_LinksInfoType( HGREN hEng, HLINKSINFO hList, int Index );

// http://www.solarix.ru/api/en/sol_LinksInfoID.shtml
FAIND_API(int) sol_LinksInfoID( HGREN hEng, HLINKSINFO hList, int Index );

// http://www.solarix.ru/api/ru/sol_LinksInfoCode.shtml
FAIND_API(int) sol_LinksInfoCode( HGREN hEngine, HLINKSINFO hList, int Index );

// http://www.solarix.ru/api/en/sol_LinksInfoEKey1.shtml
FAIND_API(int) sol_LinksInfoEKey1( HGREN hEng, HLINKSINFO hList, int Index );

// http://www.solarix.ru/api/en/sol_LinksInfoEKey2.shtml
FAIND_API(int) sol_LinksInfoEKey2( HGREN hEng, HLINKSINFO hList, int Index );

// http://www.solarix.ru/api/en/sol_LinksInfoTagsTxt.shtml
FAIND_API(const wchar_t*) sol_LinksInfoTagsTxt( HGREN hEng, HLINKSINFO hList, int Index );
FAIND_API(const char*) sol_LinksInfoTagsTxt8( HGREN hEng, HLINKSINFO hList, int Index );

// http://www.solarix.ru/api/en/sol_LinksInfoFlagsTxt.shtml
FAIND_API(const wchar_t*) sol_LinksInfoFlagsTxt( HGREN hEng, HLINKSINFO hList, int Index );
FAIND_API(const char*) sol_LinksInfoFlagsTxt8( HGREN hEng, HLINKSINFO hList, int Index );

// http://www.solarix.ru/api/en/sol_DeleteLink.shtml
FAIND_API(int) sol_DeleteLink( HGREN hEng, int LinkID, int LinkType );

// http://www.solarix.ru/api/en/sol_AddLink.shtml
FAIND_API(int) sol_AddLink( HGREN hEng, int LinkType, int EntryID1, int LinkCode, int EntryID2, const wchar_t *Tags );
FAIND_API(int) sol_AddLink8( HGREN hEng, int LinkType, int EntryID1, int LinkCode, int EntryID2, const char *TagsUtf8 );

// http://www.solarix.ru/api/en/sol_SetLinkTags.shtml
FAIND_API(int) sol_SetLinkTags( HGREN hEngine, int LinkType, int LinkID, const wchar_t *Tags );
FAIND_API(int) sol_SetLinkTags8( HGREN hEngine, int LinkType, int LinkID, const char *TagsUtf8 );

// http://www.solarix.ru/api/en/sol_SetLinkFlags.shtml
FAIND_API(int) sol_SetLinkFlags( HGREN hEngine, int LinkID, const wchar_t *Flags );
FAIND_API(int) sol_SetLinkFlags8( HGREN hEngine, int LinkID, const char *FlagsUtf8 );


// ***************************************************************************
// Find the word entry index.
// Поиск индекса словарной статьи в лексиконе.
// http://www.solarix.ru/api/en/sol_FindEntry.shtml
// ***************************************************************************
FAIND_API(int) sol_FindEntry(
                             HGREN hEngine,
                             const wchar_t *Word, // Entry name
                             int ClassID,         // Required grammatical class (part of speech) ID
                             int LanguageID       // Language ID (if ambiguous)
                            );
FAIND_API(int) sol_FindEntry8( HGREN hEngine, const char *Word, int ClassID, int LanguageID );
typedef int (SX_STDCALL * sol_FindEntry8_Fun)( HGREN hEngine, const char *Word, int ClassID, int LanguageID );


// http://www.solarix.ru/api/en/sol_FindClass.shtml
FAIND_API(int) sol_FindClass( HGREN hEngine, const wchar_t *ClassName );
FAIND_API(int) sol_FindClass8( HGREN hEngine, const char *ClassNameUtf8 );

// http://www.solarix.ru/api/en/sol_FindEnum.shtml
FAIND_API(int) sol_FindEnum( HGREN hEngine, const wchar_t *EnumName );
FAIND_API(int) sol_FindEnum8( HGREN hEngine, const char *EnumNameUtf8 );

// http://www.solarix.ru/api/en/sol_FindEnumState.shtml
FAIND_API(int) sol_FindEnumState( HGREN hEngine, int EnumID, const wchar_t *StateName );
FAIND_API(int) sol_FindEnumState8( HGREN hEngine, int EnumID, const char *StateNameUtf8 );


#define sol_FindStrings( hEngine, Word ) sol_FindStringsEx(hEngine,Word,false,false,false,false,false,0)


// Поиск всех словоформ для указанного слова, с возможным учетом связанных
// по тезаурусу. Возвращается объект со списком строк.
FAIND_API(HGREN_STR) sol_FindStringsEx(
                                       HGREN hEngine,
                                       const wchar_t *Word,
                                       int Allow_Dynforms,
                                       int Synonyms,
                                       int Grammar_Links,
                                       int Translations,
                                       int Semantics,
                                       int nJumps
                                      );


FAIND_API(int) sol_CountStrings( HGREN_STR hStrings );
FAIND_API(int) sol_GetStrings( HGREN_STR hStrings, wchar_t **Res );
FAIND_API(int) sol_GetStringLen( HGREN_STR hStrings, int i );
FAIND_API(int) sol_GetStringW( HGREN_STR hStrings, int i, wchar_t *Res );
FAIND_API(int) sol_GetStringA( HGREN_STR hStrings, int i, char *Res );
FAIND_API(int) sol_GetString8( HGREN_STR hStrings, int i, char *ResUtf8 );
FAIND_API(int) sol_DeleteStrings( HGREN_STR hStrings );

typedef int (SX_STDCALL * sol_CountStrings_Fun)( HGREN_STR hStrings );
typedef int (SX_STDCALL * sol_GetStringLen_Fun)( HGREN_STR hStrings, int i );
typedef int (SX_STDCALL * sol_GetString8_Fun)( HGREN_STR hStrings, int i, char *ResUtf8 );
typedef int (SX_STDCALL * sol_DeleteStrings_Fun)( HGREN_STR hStrings );


// Стеммер - возвращает число символов в слове, которые составляют 
// "корень", неизменный для всех форм этого слова. В случае невозможности
// выделить корень, вернет 0. 
// Только в версии PRO 
FAIND_API(int) sol_Stemmer( HGREN hEngine, const wchar_t *Word );


// Возвращает "имя" словарной статьи - обычно это базовая форма,
// но могут быть особые случаи (например, статьи ЕСТЬ - кушать
// и ЕСТЬ - иметься). Вернет 0 в случае успеха, -1 ошибка.
// http://www.solarix.ru/api/en/sol_GetEntryName.shtml
FAIND_API(int) sol_GetEntryName( HGREN hEngine, int EntryID, wchar_t *Result );
FAIND_API(int) sol_GetEntryName8( HGREN hEngine, int EntryID, char *Result );
typedef int (SX_STDCALL * sol_GetEntryName8_Fun)( HGREN hEngine, int EntryID, char *Result );


FAIND_API(int) sol_GetEntryFreq( HGREN hEngine, int EntryID );


// http://www.solarix.ru/api/en/sol_GetEntryCoordState.shtml
FAIND_API(int) sol_GetEntryCoordState( HGREN hEngine, int EntryID, int CategoryID );

FAIND_API(int) sol_FindEntryCoordPair( HGREN hEngine, int EntryID, int CategoryID, int StateID );


// Возвращает индекс грамматического класса, к которому относится словарная статья.
// Returns the part of speech ID for the word entry
// http://www.solarix.ru/api/en/sol_GetEntryClass.shtml
FAIND_API(int) sol_GetEntryClass( HGREN hEngine, int EntryID );
typedef int (SX_STDCALL * sol_GetEntryClass_Fun)( HGREN hEngine, int EntryID );


// Возвращает имя грамматического класса по его индексу
// Returns the part of speech name
// http://www.solarix.ru/api/en/sol_GetClassName.shtml
FAIND_API(int) sol_GetClassName( HGREN hEngine, int ClassID, wchar_t *Result );
FAIND_API(int) sol_GetClassName8( HGREN hEngine, int ClassID, char *ResultUtf8 );
typedef int ( SX_STDCALL * sol_GetClassName8_Fun)( HGREN hEngine, int ClassID, char *ResultUtf8 );

// Возвращает имя координаты по индексу
// Returns the grammatical category name
// http://www.solarix.ru/api/en/sol_GetCoordName.shtml
FAIND_API(int) sol_GetCoordName( HGREN hEngine, int CoordID, wchar_t *Result );
FAIND_API(int) sol_GetCoordName8( HGREN hEngine, int CoordID, char *ResultUtf8 );
typedef int (SX_STDCALL * sol_GetCoordName8_Fun)( HGREN hEngine, int CoordID, char *ResultUtf8 );



// Проверяем, какую роль играет признак CoordID для части речи ClassID:
// 0 - не имеет отношения,
// 1 - атрибут (общий для всех словоформ статьи),
// 2 - измерение (отличает словоформы),
// 3 - тэг
// http://www.solarix.ru/api/en/sol_GetCoordType.shtml
FAIND_API(int) sol_GetCoordType( HGREN hEngine, int CoordID, int ClassID );
typedef int (SX_STDCALL * sol_GetCoordType_Fun)( HGREN hEngine, int CoordID, int ClassID );


// Возвращает имя состояния координаты по ее ID
// http://www.solarix.ru/api/en/sol_GetCoordStateName.shtml
FAIND_API(int) sol_GetCoordStateName( HGREN hEngine, int CoordID, int StateID, wchar_t *Result );
FAIND_API(int) sol_GetCoordStateName8( HGREN hEngine, int CoordID, int StateID, char *ResultUtf8 );
typedef int (SX_STDCALL * sol_GetCoordStateName8_Fun)( HGREN hEngine, int CoordID, int StateID, char *ResultUtf8 );

// Возвращает количество состояний у координаты. Для бистабильных координат вернет 0
// http://www.solarix.ru/api/en/sol_CountCoordStates.shtml
FAIND_API(int) sol_CountCoordStates( HGREN hEngine, int CoordID );
typedef int (SX_STDCALL * sol_CountCoordStates_Fun)( HGREN hEngine, int CoordID );


// Returns the gender of noun (unapplayable for English) 
//
// Возвращает род существительного (неприменимо для английского)
// http://www.solarix.ru/grammar/gender.shtml
FAIND_API(int) sol_GetNounGender( HGREN hEngine, int EntryIndex );

// Склонение существительного - возвращает в буфере форму указанной через 
// EntryIndex словарной статьи с заданным числом Number и в нужном падеже Case.
// http://www.solarix.ru/for_developers/russian-noun-declension.shtml
FAIND_API(int) sol_GetNounForm(
                               HGREN hEngine,   
                               int EntryIndex,
                               int Number,
                               int Case,
                               wchar_t *Result
                              );


// **************************************************************************
// Спряжение глагола - возвращается форма в нужном числе Number, роде Gender,
// времени Tense и лице Person.
// http://www.solarix.ru/for_developers/russian-verb-conjugation.shtml
// **************************************************************************
FAIND_API(int) sol_GetVerbForm(
                               HGREN hEngine,  
                               int EntryIndex,
                               int Number,
                               int Gender,
                               int Tense,
                               int Person, 
                               wchar_t *Result
                               );


// *************************************************************************
// Склонение прилагательного в нужное число Number, род Gender, падеж Case,
// форму одушевленности Anim, краткую-полную форму Shortness, форму
// сравнения Compar_Form.
// http://www.solarix.ru/for_developers/russian-adjective-declension.shtml
// *************************************************************************
FAIND_API(int) sol_GetAdjectiveForm(
                                    HGREN hEngine,
                                    int EntryIndex,
                                    int Number,
                                    int Gender,
                                    int Case,
                                    int Anim,
                                    int Shortness,
                                    int Compar_Form, 
                                    wchar_t *Result
                                   );

// ***********************************************************************
// Согласование существительного и числительного. Отдельно задается падеж
// и (опционально) - одушевленность/неодушевленность.
// ***********************************************************************
FAIND_API(int) sol_CorrNounNumber(
                                 HGREN hEngine, 
                                 int EntryIndex,   // id_entry
                                 int Value,        // с каким числом согласуется
                                 int Case,         // NOMINATIVE_CASE_ru
                                 int Anim,         // INANIMATIVE_FORM_ru
                                 wchar_t *Result      // буфер для результата
                                 );

FAIND_API(int) sol_CorrVerbNumber(
                                 HGREN hEngine, 
                                 int EntryIndex,
                                 int Value,
                                 int Gender, 
                                 int Tense,
                                 wchar_t *Result
                                 );

FAIND_API(int) sol_CorrAdjNumber(
                                HGREN hEngine, 
                                int EntryIndex,
                                int Value,
                                int Case, 
                                int Gender,
                                int Anim,  
                                wchar_t *Result
                               );

// Поиск словарной статьи и словоформы в ней, для которой лексическое содержимое
// точно соответствует заданной строке Word. Возвращает индекс статьи EntryIndex,
// индекс формы Form, и индекс грамматического класса у найденной статьи.
FAIND_API(int) sol_FindWord(
                            HGREN hEngine, 
                            const wchar_t *Word,
                            int *EntryIndex,
                            int *Form,
                            int *Class 
                           );

FAIND_API(int) sol_GenerateWordform(
                                    HGREN hEngine, 
                                    int EntryID,
                                    int npairs,
                                    const int *pairs,
                                    wchar_t *Result
                                   );


FAIND_API(HGREN_STR) sol_GenerateWordforms(
                                           HGREN hEngine, 
                                           int EntryID,
                                           int npairs,
                                           const int *pairs
                                          );



// ****************************************************************
// Число, заданное целочисленным аргументом value, преобразуем в
// текстовое представление (именительный падеж)
// ****************************************************************
FAIND_API(int)sol_Value2Text(
                             HGREN hEngine, 
                             wchar_t *Result,
                             int Value,
                             int Gender
                            );

// Быстрый поиск слова. Возвращается некий числовой код, одинаковый для всех
// словоформ в рамках одной словарной статьи, либо -1 если поиск не удался.
FAIND_API(int) sol_SeekWord( HGREN hEngine, const wchar_t *word, int Allow_Dynforms );


// Словарная статья приводится к семантически эквивалентному
// существительному, например "ИСКАТЬ->ПОИСК". Для работы необходим
// тезаурус (недоступен в бесплатных версиях словаря)!
// Входной аргумент EntryIndex - результат предыдущего вызова sol_FindEntry.
// Возвращается индекс словарной статьи (существительное) для использования,
// например, в sol_GetNounForm, либо -1 если привести к существительному
// не представляется возможным.
FAIND_API(int) sol_TranslateToNoun( HGREN hEngine, int EntryIndex );


// Приведение словарной статьи к семантически или грамматически связанной
// неопределенной форме глагола (инфинитиву).
// http://www.solarix.ru/for_developers/api/lemmatization.shtml
FAIND_API(int) sol_TranslateToInfinitive( HGREN hEngine, int EntryIndex );


// Приведение к базовой форме.
// Вернет 1, если преобразование имело место, 0 если слово не найдено в словаре.
// Результат возвращается в Word, заменяя исходное слово.
// Если слово допускает несколько альтернативных базовых форм, то будет
// реализовано какое-то (неопределенно) одно.
//
// http://www.solarix.ru/for_developers/api/lemmatization.shtml
FAIND_API(int) sol_TranslateToBase( HGREN hEngine, wchar_t *Word, int AllowDynforms ); 


// Возвращает список базовых форм для слова. 
// http://www.solarix.ru/for_developers/api/lemmatization.shtml
FAIND_API(HGREN_STR) sol_TranslateToBases( HGREN hEngine, const wchar_t *Word, int AllowDynforms );


// http://www.solarix.ru/api/ru/sol_ProjectWord.shtml
// Нахождение всех проекций указанного слова и работа с полученным списком.
// Find all possible mappings of the word to the lexicon and return tha handle of the list. 
FAIND_API(HGREN_WCOORD) sol_ProjectWord( HGREN hEngine, const wchar_t *Word, int Allow_Dynforms );
FAIND_API(HGREN_WCOORD) sol_ProjectWord8( HGREN hEngine, const char *WordUtf8, int Allow_Dynforms );
typedef HGREN_WCOORD (SX_STDCALL * sol_ProjectWord8_Fun)( HGREN hEngine, const char *WordUtf8, int Allow_Dynforms );

FAIND_API(HGREN_WCOORD) sol_ProjectMisspelledWord( HGREN hEngine, const wchar_t *Word, int Allow_Dynforms, int nmaxmiss );

// http://www.solarix.ru/api/ru/sol_CountProjections.shtml
// Count the number of mappings in the list. 
FAIND_API(int) sol_CountProjections( HGREN_WCOORD hList );
typedef int (SX_STDCALL * sol_CountProjections_Fun)( HGREN_WCOORD hList );

// http://www.solarix.ru/api/ru/sol_DeleteProjections.shtml
// Delete the results of sol_ProjectWord
FAIND_API(void) sol_DeleteProjections( HGREN_WCOORD hList );
typedef int (SX_STDCALL * sol_DeleteProjections_Fun)( HGREN_WCOORD hList );

// http://www.solarix.ru/api/ru/sol_GetIEntry.shtml
// Return the entry id (primary key). The entry properties can be accessed 
// via id, see sol_GetEntryName for example.
// Возвращается id (primary key) словарной статьи среди проекций
FAIND_API(int) sol_GetIEntry( HGREN_WCOORD hList, int Index );
typedef int (SX_STDCALL * sol_GetIEntry_Fun)( HGREN_WCOORD hList, int Index );

// http://www.solarix.ru/api/ru/sol_GetProjCoordState.shtml
// Возвращается состояние грамматического признака CoordID у проекции Index
FAIND_API(int) sol_GetProjCoordState( HGREN hEngine, HGREN_WCOORD hList, int Index, int CoordID );
typedef int (SX_STDCALL * sol_GetProjCoordState_Fun)( HGREN hEngine, HGREN_WCOORD hList, int Index, int CoordID );

FAIND_API(int) sol_GetProjCoordCount( HGREN hEngine, HGREN_WCOORD hList, int Index );
typedef int (SX_STDCALL * sol_GetProjCoordCount_Fun)( HGREN hEngine, HGREN_WCOORD hList, int Index );

FAIND_API(int) sol_GetProjCoordId( HGREN hEngine, HGREN_WCOORD hList, int Index, int TagIndex );
typedef int (SX_STDCALL * sol_GetProjCoordId_Fun)( HGREN hEngine, HGREN_WCOORD hList, int Index, int TagIndex );

FAIND_API(int) sol_GetProjStateId( HGREN hEngine, HGREN_WCOORD hList, int Index, int TagIndex );
typedef int (SX_STDCALL * sol_GetProjStateId_Fun)( HGREN hEngine, HGREN_WCOORD hList, int Index, int TagIndex );


#define SOL_GREN_ALLOW_FUZZY           0x00000002
#define SOL_GREN_COMPLETE_ONLY         0x00000004
#define SOL_GREN_PRETOKENIZED          0x00000008
#define SOL_GREN_TOKENIZE_ONLY         0x00000010
#define SOL_GREN_DISABLE_FILTERS       0x00000020
#define SOL_GREN_REORDER_TREE          0x00000400
#define SOL_GREN_MODEL                 0x00000800
#define SOL_GREN_MODEL_ONLY            0x00002000


// http://www.solarix.ru/api/ru/sol_MorphologyAnalysis.shtml
// Morphology analysis
FAIND_API(HGREN_RESPACK) sol_MorphologyAnalysis(
                                                HGREN hEngine,
                                                const wchar_t *Sentence,
                                                int Flags,
                                                int UnusedFlags,
                                                int Constraints,
                                                int Language
                                               );
// Morphology analysis
FAIND_API(HGREN_RESPACK) sol_MorphologyAnalysis8(
                                                 HGREN hEngine,
                                                 const char *SentenceUtf8,
                                                 int Flags,
                                                 int UnusedFlags,
                                                 int Constraints,
                                                 int Language
                                                );

FAIND_API(HGREN_RESPACK) sol_MorphologyAnalysisA(
                                                 HGREN hEngine,
                                                 const char *Sentence,
                                                 int Flags,
                                                 int UnusedFlags,
                                                 int Constraints,
                                                 int Language
                                                );

typedef HGREN_RESPACK (SX_STDCALL * sol_MorphologyAnalysis8_Fun)(
                                                                 HGREN hEngine,
                                                                 const char *SentenceUtf8,
                                                                 int Flags,
                                                                 int UnusedFlags,
                                                                 int Constraints,
                                                                 int Language
                                                                );


// http://www.solarix.ru/api/ru/sol_SyntaxAnalysis.shtml
// **************************************************************************
// Выполнение синтаксического анализа - на входе фраза, на выходе получается
// объект, хранящий альтернативные варианты построения синтаксического графа.
// Ряд функций работает с этим объектом, позволяя анализировать результаты.
// **************************************************************************
FAIND_API(HGREN_RESPACK) sol_SyntaxAnalysis(
                                            HGREN hEngine,
                                            const wchar_t *Sentence,
                                            int MorphologicalFlags,
                                            int SyntacticFlags,
                                            int Constraints,
                                            int Language
                                           );

FAIND_API(HGREN_RESPACK) sol_SyntaxAnalysis8(
                                             HGREN hEngine,
                                             const char *SentenceUtf8,
                                             int MorphologicalFlags,
                                             int SyntacticFlags,
                                             int Constraints,
                                             int Language
                                            );

FAIND_API(HGREN_RESPACK) sol_SyntaxAnalysisA(
                                             HGREN hEngine,
                                             const char *Sentence,
                                             int MorphologicalFlags,
                                             int SyntacticFlags,
                                             int Constraints,
                                             int Language
                                            );

typedef HGREN_RESPACK (SX_STDCALL * sol_SyntaxAnalysis8_Fun)(
                                                             HGREN hEngine,
                                                             const char *SentenceUtf8,
                                                             int MorphologicalFlags,
                                                             int SyntacticFlags,
                                                             int Constraints,
                                                             int Language
                                                            );



FAIND_API(wchar_t*) sol_NormalizePhraseW( HGREN hEngine, HGREN_RESPACK hLinkages );
FAIND_API(char*) sol_NormalizePhrase8( HGREN hEngine, HGREN_RESPACK hLinkages );



// http://www.solarix.ru/api/ru/sol_DeleteResPack.shtml
// Удаление результатов морфологического или синтаксического анализа 
FAIND_API(void) sol_DeleteResPack( HGREN_RESPACK hPack );
typedef void (SX_STDCALL * sol_DeleteResPack_Fun)( HGREN_RESPACK hPack );


// http://www.solarix.ru/api/ru/sol_CountGrafs.shtml
// Сколько альтернативных вариантов анализа фразы?  
FAIND_API(int) sol_CountGrafs( HGREN_RESPACK hPack ); 
typedef int (SX_STDCALL * sol_CountGrafs_Fun)( HGREN_RESPACK hPack );

// http://www.solarix.ru/api/ru/sol_CountRoots.shtml
// Сколько деревьев (узлов верхнего уровня) в заданном графе?
FAIND_API(int) sol_CountRoots( HGREN_RESPACK hPack, int iGraf );
typedef int (SX_STDCALL * sol_CountRoots_Fun)( HGREN_RESPACK hPack, int iGraf );

// http://www.solarix.ru/api/ru/sol_GetRoot.shtml
// Получение указателя на заданный узел верхнего уровня 
FAIND_API(HGREN_TREENODE) sol_GetRoot( HGREN_RESPACK hPack, int iGraf, int iRoot );
typedef HGREN_TREENODE (SX_STDCALL * sol_GetRoot_Fun)( HGREN_RESPACK hPack, int iGraf, int iRoot );

// http://www.solarix.ru/api/ru/sol_CountLeafs.shtml
// Количество прикрепленных к данному узлу веток
FAIND_API(int) sol_CountLeafs( HGREN_TREENODE hNode );
typedef int (SX_STDCALL * sol_CountLeafs_Fun)( HGREN_TREENODE hNode );

// http://www.solarix.ru/api/ru/sol_GetLeafLinkType.shtml
// Тип синтаксической связи между корневым узлом и его потомком, заданным порядковым номером (от 0)
FAIND_API(int) sol_GetLeafLinkType( HGREN_TREENODE hNode, int iLeaf );
typedef int (SX_STDCALL * sol_GetLeafLinkType_Fun)( HGREN_TREENODE hNode, int iLeaf );

// http://www.solarix.ru/api/ru/sol_GetLeaf.shtml
// Возвращает указатель на заданную ветку
FAIND_API(HGREN_TREENODE) sol_GetLeaf( HGREN_TREENODE hNode, int iLeaf );
typedef HGREN_TREENODE (SX_STDCALL * sol_GetLeaf_Fun)( HGREN_TREENODE hNode, int iLeaf );

// http://www.solarix.ru/api/ru/sol_GetNodeIEntry.shtml
// Возвращает индекс словарной статьи в узле
FAIND_API(int) sol_GetNodeIEntry( HGREN hEngine, HGREN_TREENODE hNode );
typedef int (SX_STDCALL * sol_GetNodeIEntry_Fun)( HGREN hEngine, HGREN_TREENODE hNode );

// http://www.solarix.ru/api/ru/sol_GetNodeVerIEntry.shtml
FAIND_API(int) sol_GetNodeVerIEntry( HGREN hEngine, HGREN_TREENODE hNode, int iver );
typedef int (SX_STDCALL * sol_GetNodeVerIEntry_Fun)( HGREN hEngine, HGREN_TREENODE hNode, int iver );

// http://www.solarix.ru/api/ru/sol_GetNodePosition.shtml
// Position of the first word in the node
FAIND_API(int) sol_GetNodePosition( HGREN_TREENODE hNode );
typedef int (SX_STDCALL * sol_GetNodePosition_Fun)( HGREN_TREENODE hNode );

FAIND_API(int) sol_GetNodeContentsLen( HGREN_TREENODE hNode );
typedef int (SX_STDCALL * sol_GetNodeContentsLen_Fun)( HGREN_TREENODE hNode );

// http://www.solarix.ru/api/ru/sol_GetNodeContents.shtml
// Текстовое содержимое узла
FAIND_API(void) sol_GetNodeContents( HGREN_TREENODE hNode, wchar_t *Buffer );
FAIND_API(void) sol_GetNodeContents8( HGREN_TREENODE hNode, char *BufferUtf8 );
typedef void (SX_STDCALL * sol_GetNodeContents_Fun)( HGREN_TREENODE hNode, wchar_t *Buffer );
typedef void (SX_STDCALL * sol_GetNodeContents8_Fun)( HGREN_TREENODE hNode, char *BufferUtf8 );

// http://www.solarix.ru/api/ru/sol_GetNodeCoordState.shtml
// Состояние координаты для узла
FAIND_API(int) sol_GetNodeCoordState( HGREN_TREENODE hNode, int CoordID );
FAIND_API(int) sol_GetNodeVerCoordState( HGREN_TREENODE hNode, int iver, int CoordID );
typedef int (SX_STDCALL * sol_GetNodeCoordState_Fun)( HGREN_TREENODE hNode, int CoordID );
typedef int (SX_STDCALL * sol_GetNodeVerCoordState_Fun)( HGREN_TREENODE hNode, int iver, int CoordID );

// http://www.solarix.ru/api/ru/sol_GetNodeVersionCount.shtml
// Количество альтернативных версий словоформы, включая основную.
FAIND_API(int) sol_GetNodeVersionCount( HGREN hEngine, HGREN_TREENODE hNode );
typedef int (SX_STDCALL * sol_GetNodeVersionCount_Fun)( HGREN hEngine, HGREN_TREENODE hNode );

// http://www.solarix.ru/api/ru/sol_GetNodeCoordPair.shtml
// Проверяем наличие координатной пары у узла
FAIND_API(int) sol_GetNodeCoordPair( HGREN_TREENODE hNode, int CoordID, int StateID );
FAIND_API(int) sol_GetNodeVerCoordPair( HGREN_TREENODE hNode, int iver, int CoordID, int StateID );
typedef int (SX_STDCALL * sol_GetNodeCoordPair_Fun)( HGREN_TREENODE hNode, int CoordID, int StateID );
typedef int (SX_STDCALL * sol_GetNodeVerCoordPair_Fun)( HGREN_TREENODE hNode, int iver, int CoordID, int StateID );

// http://www.solarix.ru/api/ru/sol_GetNodePairsCount.shtml
// Число различных координатных пар у узла
FAIND_API(int) sol_GetNodePairsCount( HGREN_TREENODE hNode );
FAIND_API(int) sol_GetNodeVerPairsCount( HGREN_TREENODE hNode, int iver );
typedef int (SX_STDCALL * sol_GetNodePairsCount_Fun)( HGREN_TREENODE hNode );
typedef int (SX_STDCALL * sol_GetNodeVerPairsCount_Fun)( HGREN_TREENODE hNode, int iver );

// http://www.solarix.ru/api/ru/sol_GetNodePairCoord.shtml
FAIND_API(int) sol_GetNodePairCoord( HGREN_TREENODE hNode, int ipair );
FAIND_API(int) sol_GetNodeVerPairCoord( HGREN_TREENODE hNode, int iver, int ipair );
typedef int (SX_STDCALL * sol_GetNodePairCoord_Fun)( HGREN_TREENODE hNode, int ipair );
typedef int (SX_STDCALL * sol_GetNodeVerPairCoord_Fun)( HGREN_TREENODE hNode, int iver, int ipair );

// http://www.solarix.ru/api/ru/sol_GetNodePairState.shtml
FAIND_API(int) sol_GetNodePairState( HGREN_TREENODE hNode, int ipair );
FAIND_API(int) sol_GetNodeVerPairState( HGREN_TREENODE hNode, int iver, int ipair );
typedef int (SX_STDCALL * sol_GetNodePairState_Fun)( HGREN_TREENODE hNode, int ipair );
typedef int (SX_STDCALL * sol_GetNodeVerPairState_Fun)( HGREN_TREENODE hNode, int iver, int ipair );




FAIND_API(int) sol_RestoreCasing( HGREN hEngine, wchar_t *Word, int EntryIndex );
FAIND_API(int) sol_RestoreCasing8( HGREN hEngine, char *WordUtf8, int EntryIndex );
typedef int (SX_STDCALL * sol_RestoreCasing8_Fun)( HGREN hEngine, char *WordUtf8, int EntryIndex );


FAIND_API(HGREN_SBROKER) sol_CreateSentenceBroker( HGREN hEngine, const wchar_t *Filename, const wchar_t *DefaultCodepage, int LanguageID );
FAIND_API(HGREN_SBROKER) sol_CreateSentenceBroker8( HGREN hEngine, const char *Filename8, const char *DefaultCodepage8, int LanguageID );

FAIND_API(HGREN_SBROKER) sol_CreateSentenceBrokerMemW( HGREN hEngine, const wchar_t *Text, int LanguageID );
FAIND_API(HGREN_SBROKER) sol_CreateSentenceBrokerMemA( HGREN hEngine, const char *Text, int LanguageID );
FAIND_API(HGREN_SBROKER) sol_CreateSentenceBrokerMem8( HGREN hEngine, const char *TextUtf8, int LanguageID );
FAIND_API(int) sol_FetchSentence( HGREN_SBROKER hBroker );
FAIND_API(int) sol_GetFetchedSentenceW( HGREN_SBROKER hBroker, wchar_t *Buffer );
FAIND_API(int) sol_GetFetchedSentenceA( HGREN_SBROKER hBroker, char *Buffer );
FAIND_API(int) sol_GetFetchedSentence8( HGREN_SBROKER hBroker, char *BufferUtf8 );
FAIND_API(int) sol_GetFetchedSentenceLen( HGREN_SBROKER hBroker );
FAIND_API(void) sol_DeleteSentenceBroker( HGREN_SBROKER hBroker );

typedef HGREN_SBROKER (SX_STDCALL * sol_CreateSentenceBrokerMem8_Fun)( HGREN hEngine, char *WordUtf8, int EntryIndex );
typedef int (SX_STDCALL * sol_FetchSentence_Fun)( HGREN_SBROKER hBroker );
typedef int (SX_STDCALL * sol_GetFetchedSentenceLen_Fun)( HGREN_SBROKER hBroker );
typedef int (SX_STDCALL * sol_GetFetchedSentence8_Fun)( HGREN_SBROKER hBroker, char *BufferUtf8 );
typedef int (SX_STDCALL * sol_DeleteSentenceBroker_Fun)( HGREN_SBROKER hBroker );



// Split the string into words, using the rules for language with given ID
// http://www.solarix.ru/api/ru/sol_Tokenize.shtml
FAIND_API(HGREN_STR) sol_TokenizeW( HGREN hEngine, const wchar_t *Sentence, int LanguageID );
FAIND_API(HGREN_STR) sol_TokenizeA( HGREN hEngine, const char *Sentence, int LanguageID );
FAIND_API(HGREN_STR) sol_Tokenize8( HGREN hEngine, const char *SentenceUtf8, int LanguageID );
typedef HGREN_STR (SX_STDCALL * sol_Tokenize8_Fun)( HGREN hEngine, const char *SentenceUtf8, int LanguageID );

#if defined UNICODE || defined _UNICODE 
 #define sol_Tokenize sol_TokenizeW
#else
 #define sol_Tokenize sol_TokenizeA
#endif


// N-grams database lookup
// http://www.solarix.ru/for_developers/api/ngrams-api.shtml
FAIND_API(int) sol_Seek1Grams( HGREN hEngine, int type, const wchar_t *word1 );
FAIND_API(int) sol_Seek2Grams( HGREN hEngine, int type, const wchar_t *word1, const wchar_t *word2 );
FAIND_API(int) sol_Seek3Grams( HGREN hEngine, int type, const wchar_t *word1, const wchar_t *word2, const wchar_t *word3 );
FAIND_API(int) sol_Seek4Grams( HGREN hEngine, int type, const wchar_t *word1, const wchar_t *word2, const wchar_t *word3, const wchar_t *word4 );
FAIND_API(int) sol_Seek5Grams( HGREN hEngine, int type, const wchar_t *word1, const wchar_t *word2, const wchar_t *word3, const wchar_t *word4, const wchar_t *word5 );
FAIND_API(int) sol_CountNGrams( HGREN hEngine, int type, int Order, unsigned int *Hi, unsigned int *Lo );

FAIND_API(int) sol_Seek1Grams8( HGREN hEngine, int type, const char *word1 );
FAIND_API(int) sol_Seek2Grams8( HGREN hEngine, int type, const char *word1, const char *word2 );
FAIND_API(int) sol_Seek3Grams8( HGREN hEngine, int type, const char *word1, const char *word2, const char *word3 );
FAIND_API(int) sol_Seek4Grams8( HGREN hEngine, int type, const char *word1, const char *word2, const char *word3, const char *word4 );
FAIND_API(int) sol_Seek5Grams8( HGREN hEngine, int type, const char *word1, const char *word2, const char *word3, const char *word4, const char *word5 );



FAIND_API(int) sol_CountInts( HGREN_INTARRAY h );
FAIND_API(int) sol_GetInt( HGREN_INTARRAY h, int i );
FAIND_API(void) sol_DeleteInts( HGREN_INTARRAY h );

FAIND_API(int) sol_IsLanguagePhrase( HGREN hEngine, const wchar_t *Phrase, int Language );
FAIND_API(int) sol_GuessPhraseLanguage( HGREN hEngine, const wchar_t *Phrase );

FAIND_API(int) sol_Free( HGREN hEngine, void *Ptr );

FAIND_API(int) sol_MatchNGrams( HGREN hEngine, const wchar_t *Text, int * unmatched_2_ngrams, int *n2, int *n3 );

FAIND_API(int) sol_Syllabs(
                           HGREN hEngine,
                           const wchar_t *OrgWord,
                           wchar_t SyllabDelimiter,
                           wchar_t *Result,
                           int LanguageID
                          );

FAIND_API(int) sol_Syllabs8(
                            HGREN hEngine,
                            const char *OrgWord,
                            char SyllabDelimiter, 
                            char *Result,
                            int LanguageID
                           );

// Find the internal language index by its name (usually English name)
// Returns -1 if no language is found.
FAIND_API(int) sol_FindLanguage( HGREN hEngine, const wchar_t *LanguageName );
FAIND_API(int) sol_FindLanguage8( HGREN hEngine, const char *LanguageNameUtf8 );

// Probe the lexicon for language entries.
// Returns 1 if language is present in lexicon, 0 if not,
FAIND_API(int) sol_HasLanguage( HGREN hEngine, int LanguageID );

// Returns the total number of distinct lexems in lexicon
FAIND_API(int) sol_CountLexems( HGREN hEng );

// Flexion Engine: guess suitable flexion handlers for the word
FAIND_API(HFLEXIONS) sol_FindFlexionHandlers( HGREN hEngine, const wchar_t *WordBasicForm, int SearchEntries );

// Flexion engine: return the number of matching entries
FAIND_API(int) sol_CountEntriesInFlexionHandlers( HGREN hEngine, HFLEXIONS hFlexs );

// Flexion engine: return the number of matching paradigmas
FAIND_API(int) sol_CountParadigmasInFlexionHandlers( HGREN hEngine, HFLEXIONS hFlexs );

// Flexion engine: return the entry ID
FAIND_API(int) sol_GetEntryInFlexionHandlers( HGREN hEngine, HFLEXIONS hFlexs, int Index );

// Flexion engine: return the paradigma internal index and human-friendly name
FAIND_API(int) sol_GetParadigmaInFlexionHandlers( HGREN hEngine, HFLEXIONS hFlexs, int Index, wchar_t *ParadigmaName );

FAIND_API(HFLEXIONTABLE) sol_BuildFlexionHandler(
                                                 HGREN hEng,
                                                 HFLEXIONS hFlexs,
                                                 const wchar_t *ParadigmaName,
                                                 int EntryIndex
                                                );

FAIND_API(const wchar_t*) sol_GetFlexionHandlerWordform( HGREN hEngine, HFLEXIONTABLE hFlex, const wchar_t *dims );

FAIND_API(int) sol_CountFlexionHandlerWordform( HGREN hEngine, HFLEXIONTABLE hFlex );
FAIND_API(const wchar_t*) sol_GetFlexionHandlerWordformText( HGREN hEngine, HFLEXIONTABLE hFlex, int FormIndex );

FAIND_API(int) sol_DeleteFlexionHandlers( HGREN hEng, HFLEXIONS hFlexs );
FAIND_API(int) sol_DeleteFlexionHandler( HGREN hEng, HFLEXIONTABLE hFlex );



// http://www.solarix.ru/api/en/sol_FindPhrase.shtml
FAIND_API(int) sol_FindPhrase( HGREN hEng, const wchar_t *Phrase, int Flags );
FAIND_API(int) sol_FindPhrase8( HGREN hEng, const char *Phrase, int Flags );

FAIND_API(wchar_t*) sol_GetPhraseText( HGREN hEngine, int PhraseID );
FAIND_API(char*) sol_GetPhraseText8( HGREN hEngine, int PhraseID );

FAIND_API(int) sol_GetPhraseLanguage( HGREN hEngine, int PhraseID );
FAIND_API(int) sol_GetPhraseClass( HGREN hEngine, int PhraseID );
FAIND_API(int) sol_AddPhrase( HGREN hEngine, const wchar_t *Phrase, int LanguageID, int PartOfSpeechID, int ProcessingFlags );
FAIND_API(int) sol_AddPhrase8( HGREN hEngine, const char *Phrase, int LanguageID, int PartOfSpeechID, int ProcessingFlags );
FAIND_API(int) sol_SetPhraseNote( HGREN hEngine, int PhraseID, const wchar_t *Name, const wchar_t *Value );

FAIND_API(int) sol_ProcessPhraseEntry(
                                      HGREN hEngine,
                                      int te_id,
                                      const wchar_t *Scenario,
                                      int LanguageID,
                                      wchar_t DelimiterChar
                                     );
FAIND_API(int) sol_DeletePhrase( HGREN hEngine, int te_id );



FAIND_API(HGREN_INTARRAY) sol_ListEntries( HGREN hEngine, int Flags, int EntryType, const wchar_t *Mask, int LanguageID, int PartOfSpeechID );
FAIND_API(HGREN_INTARRAY) sol_ListEntries8( HGREN hEngine, int Flags, int EntryType, const char *MaskUtf8, int LanguageID, int PartOfSpeechID );
FAIND_API(HGREN_STR) sol_ListEntryForms( HGREN hEngine, int EntryKey );


FAIND_API(int) sol_SaveDictionary( HGREN hEngine, int Flags, const wchar_t *Folder );

FAIND_API(int) sol_AddWord( HGREN hEng, const wchar_t *Txt );
FAIND_API(int) sol_AddWord8( HGREN hEng, const char *Txt );

FAIND_API(int) sol_ReserveLexiconSpace( HGREN hEngine, int n );

// Error reporting functions.
FAIND_API(int) sol_GetErrorLen( HGREN hEngine );

FAIND_API(int) sol_GetErrorLen8( HGREN hEngine );
typedef int (SX_STDCALL * sol_GetErrorLen8_Fun)( HGREN hEngine );

FAIND_API(int) sol_GetError( HGREN hEngine, wchar_t *Buffer, int buffer_len );
FAIND_API(int) sol_GetError8( HGREN hEngine, char *BufferUtf8, int buffer_len );
typedef int (SX_STDCALL * sol_GetError8_Fun)( HGREN hEngine, char *BufferUtf8, int buffer_len );

FAIND_API(void) sol_ClearError( HGREN hEngine );

FAIND_API(int) sol_LemmatizeWord( HGREN hEngine, wchar_t *word, int Allow_Dynforms );

FAIND_API(HGREN_INTARRAY) sol_ListPartsOfSpeech( HGREN hEngine, int Language );

FAIND_API(int) sol_FindTagW( HGREN hEngine, const wchar_t *TagName );
FAIND_API(int) sol_FindTagValueW( HGREN hEngine, int TagID, const wchar_t *ValueName );


FAIND_API(HGREN_SPOKEN) sol_PronounceW( HGREN hEngine, const wchar_t * Sentence, int LanguageID, int AnalysisFlags, int SynthesisFlags, void * VoiceOptions );
FAIND_API(int) sol_DeleteSpoken( HGREN_SPOKEN hData );


FAIND_API(int) sol_CountNodeMarks( HGREN_TREENODE hNode );
FAIND_API(int) sol_GetNodeMarkNameW( HGREN_TREENODE hNode, int mark_index, wchar_t * name_buffer );
FAIND_API(HGREN_LONGSTRING) sol_SerializeNodeMark( HGREN hEngine, HGREN_TREENODE hNode, int mark_index, int format );
FAIND_API(int) sol_GetLongStringLenW( HGREN_LONGSTRING hString );
FAIND_API(int) sol_GetLongStringW( HGREN_LONGSTRING hString, wchar_t * buffer );
FAIND_API(int) sol_DeleteLongString( HGREN_LONGSTRING hString );

FAIND_API(const char*) sol_RenderSyntaxTree8( HGREN hEngine, HGREN_RESPACK hSyntaxTree, int RenderOptions );

FAIND_API(void*) sol_OpenCorpusStorage8( HGREN hEngine, const char * filename, int for_writing );
FAIND_API(int) sol_CloseCorpusStorage( HGREN hEngine, void * file_handle );
FAIND_API(int) sol_WriteSyntaxTree( HGREN hEngine, void * file_handle, const wchar_t * sentence_utf8,  HGREN_RESPACK respack );

FAIND_API(void*) sol_LoadSyntaxTree( HGREN hEngine, void * file_handle );
FAIND_API(HGREN_RESPACK) sol_GetTreeHandle( void * ptr );
FAIND_API(const wchar_t*) sol_GetSentenceW( void * ptr );
FAIND_API(int) sol_FreeSyntaxTree( void * tree );
FAIND_API(HGREN_RESPACK) sol_CreateLinkages(HGREN hEngine);
FAIND_API(HGREN_LINKAGE) sol_CreateLinkage(HGREN hEngine, HGREN_RESPACK hLinkages);
FAIND_API(int) sol_AddBeginMarker(HGREN hEngine, HGREN_LINKAGE hLinkage);
FAIND_API(int) sol_AddEndMarker(HGREN hEngine, HGREN_LINKAGE hLinkage);
FAIND_API(int) sol_AddNodeToLinkage(HGREN hEngine, HGREN_LINKAGE hLinkage, HGREN_TREENODE hNode);
FAIND_API(HGREN_TREENODE) sol_CreateTreeNodeW(HGREN hEngine, int id_entry, const wchar_t *word, int n_pair, const int * pairs);



#endif
