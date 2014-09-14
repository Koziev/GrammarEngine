// Wrapper для вызова API грамматического движка из программы на Delphi.
// (c) by Koziev Elijah, Solarix Intellectronix Project
//
// CD->27.11.2008
// LC->13.07.2009

unit SolarixEngineApi;

interface

uses SysUtils;

const FG_LOGICS                    : integer = $00000001;
const FG_GERUND1                   : integer = $00000002;
const FG_GERUND2                   : integer = $00000004;
const FG_QUEST                     : integer = $00000008; // генерировать вопросительные
const FG_EXCLAM                    : integer = $00000010; // генерировать восклицательные
const FG_INTRO                     : integer = $00000020;
const FG_COMPLEX                   : integer = $00000040;
const FG_MULTISENT                 : integer = $00000080;
const FG_SUBSTWORDS                : integer = $00000100;
const FG_COMSENT                   : integer = $00000200; // генерировать повествовательные предложения
const FG_USE_LEX_WHEN_EXHAUSTED    : integer = $00000400; // если фильтрованные слова закончились,
                                                          // то использовать полный лексикон, а не
                                                          // исходный фильтрованный список
const FG_EXTRACT_FIRST             : integer = $00000800; // извекать не рандомно из фильтрованного
                                                          // списка, а один за одним
const FG_DONT_REMOVE_USED          : integer = $00001000; // не удалять из фильтрованного списка использованные.
const FG_GENERATOR_USES_NGRAMS     : integer = $00002000; // генератор текста использует базу N-грамм




const FG_TOKENIZE                  : integer = $00000001; // токенизация (для проверки)
const FG_TRANSFORM                 : integer = $00000002; // перефразирование - быстрые не-консервативные методы
const FG_SYNONYMIZE                : integer = $00000004; // выполнять синонимизацию
const FG_SYNONYMIZER_MULTIWORD     : integer = $00000008; // использовать сложные (многословные) синонимы
const FG_PARAFRASE_REORDER         : integer = $00000010; // перефразирование - изменять порядок слов
const FG_PARAFRASE_CONSERVATIVE    : integer = $00000020; // перефразирование - перестраивать причастные и деепричастные обороты, активный и пассивный залоги и т.д.


// Флаги управления N-граммами
const FG_NO_NGRAMS                : integer = $00000000; // не использовать N-граммы
const FG_SYNONYMIZER_USES_NGRAMS  : integer = $00000001; // проверять возможность синонимизации по таблице N-грамм
const FG_PEDANTIC_NGRAMS          : integer = $00000002; // тщательный и трудоемкий отсев вариантов
const FG_OMIT_FREQ1               : integer = $00000010; // Игнорировать N-граммы с частотой 1
const FG_2GRAMS                   : integer = $00000020; // Фильтровать по 2граммам
const FG_23GRAMS                  : integer = $00000040; // Фильтровать по 2граммам, 3граммы для сортировки частоты
const FG_3GRAMS                   : integer = $00000100; // Фильтровать по 2 и 3граммам
const FG_4GRAMS                   : integer = $00000200; // Фильтровать по 2, 3 и 4граммам
const FG_5GRAMS                   : integer = $00000400; // Фильтровать по 2, 3, 4 и 5граммам
const FG_2345GRAMS                : integer = $00000800; // Фильтровать по 2граммам, 3, 4 и 5 граммы для сортировки частоты

// Results format
const FG_YIELD_PLAIN_TEXT         : integer = $00000000;
const FG_YIELD_XML                : integer = $00000001;
const FG_YIELD_ALL_SYNS           : integer = $00000002; // выводить в XML результатах все найденные синонимы для каждого исходного слова

// Debug options
const FG_NO_DEBUG                 : integer = $00000000;
const FG_DEBUG                    : integer = $00000001; // выполнять отладочную трассировку синонимизаций
const FG_DEBUG_HTML               : integer = $00000002; // выполнять отладочную трассировку синонимизаций в формате HTML

// Syntax analyzer flags
const FG_SIMPLE_ANALYSIS          : integer = $00000001; // Упрощенный, быстрый анализ
const FG_PEDANTIC_ANALYSIS        : integer = $00000002; // использовать медленный, но более точный синтаксический анализ



function sol_CreateGrammarEngineA( DictionaryXml: PChar ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_CreateGrammarEngineA';
function sol_DeleteGrammarEngine( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_DeleteGrammarEngine';
function sol_CountEntries( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountEntries';
function sol_CountForms( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountForms';
function sol_CountLinks( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountLinks';
function sol_MaxLexemLen( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_MaxLexemLen';
function sol_LemmatizeWord( hEngine: PInteger; Word: PWideChar; Allow_Dynforms: LongBool ): integer; stdcall; external 'faind.win32.dll' name 'sol_LemmatizeWord';
function sol_FindEntry( hEngine: PInteger; Word: PWideChar; iClass: integer; Language: integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_FindEntry';
function sol_GetVersion( hEngine: PInteger; Major: PInteger; Minor: PInteger; Build: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetVersion';
function sol_DictionaryVersion( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_DictionaryVersion';

function sol_FindStringsEx( hEngine: PInteger; Word: PWideChar;
                            Allow_Dynforms: LongBool;
                            Synonyms: LongBool;
                            Grammar_Links: LongBool;
                            Translations: LongBool;
                            Semantics: LongBool;
                            nJumps: integer
                           ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_FindStringsEx';


function sol_CountStrings( hStrList: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountStrings';
function sol_GetString( hStrList: PInteger; i: integer; Word: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetString';
function sol_DeleteStrings( hStrList: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_DeleteStrings';

function sol_GetEntryName( hEngine: PInteger; EntryIndex: integer; Result: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetEntryName';
function sol_GetEntryClass( hEngine: PInteger; EntryIndex: integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetEntryClass';
function sol_GetClassName( hEngine: PInteger; ClassIndex: integer; Word: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetClassName';
function sol_GetNounGender( hEngine: PInteger; EntryIndex: integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetNounGender';
function sol_EnumInClass( hEngine: PInteger; ClassIndex: integer; Enum: integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_EnumInClass';
function sol_FindClass( hEngine: PInteger; ClassName: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_FindClass';
function sol_FindEnum( hEngine: PInteger; EnumName: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_FindEnum';
function sol_FindEnumState( hEngine: PInteger; Enum: integer; StateName: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_FindEnumState';
function sol_GetNounForm( Engine: PInteger; EntryIndex: integer; Number: integer; iCase: integer; Result: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetNounForm';

function sol_GetVerbForm( Engine: PInteger; EntryIndex: integer;
                          Number: Integer;
                          Gender: Integer;
                          Tense: Integer;
                          Person: Integer;
                          Result: PWideChar
                         ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetVerbForm';


function sol_GetAdjectiveForm( Engine: PInteger; EntryIndex: integer;
                               Number: Integer;
                               Gender: Integer;
                               ICase: Integer;
                               Anim: Integer;
                               Shortness: Integer;
                               Compar_Form: Integer;
                               Result: PWideChar
                              ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetAdjectiveForm';

function sol_CorrNounNumber( Engine: PInteger; EntryIndex: integer;
                             Value: Integer;
                             ICase: Integer;
                             Anim: Integer;
                             Result: PWideChar
                            ): integer; stdcall; external 'faind.win32.dll' name 'sol_CorrNounNumber';

function sol_CorrVerbNumber( Engine: PInteger; EntryIndex: integer;
                             Value: Integer;
                             Gender: Integer;
                             Tense: Integer;
                             Result: PWideChar
                            ): integer; stdcall; external 'faind.win32.dll' name 'sol_CorrVerbNumber';

function sol_CorrAdjNumber( Engine: PInteger; EntryIndex: integer;
                            Value: Integer;
                            Iase: Integer;
                            Gender: Integer;
                            Anim: Integer;
                            Result: PWideChar
                           ): integer; stdcall; external 'faind.win32.dll' name 'sol_CorrAdjNumber';

function sol_FindWord( Engine: PInteger;
                       Word: PWideChar;
                       EntryIndex: PInteger;
                       Form: PInteger;
                       ClassIndex: PInteger
                      ): integer; stdcall; external 'faind.win32.dll' name 'sol_FindWord';

function sol_Value2Text(
                        Engine: PInteger;
                        Result: PWideChar;
                        Value: Integer;
                        Gender: Integer
                       ): integer; stdcall; external 'faind.win32.dll' name 'sol_Value2Text';

function sol_SeekWord( Engine: PInteger; word: PWideChar; Allow_Dynforms: LongBool ): integer; stdcall; external 'faind.win32.dll' name 'sol_SeekWord';
function sol_TranslateToNoun( Engine: PInteger; EntryIndex: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_TranslateToNoun';
function sol_TranslateToInfinitive( Engine: PInteger; EntryIndex: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_TranslateToInfinitive';
function sol_TranslateToBase( Engine: PInteger; Word: PWideChar; AllowDynforms: LongBool ): integer; stdcall; external 'faind.win32.dll' name 'sol_TranslateToBase';
function sol_TranslateToBases( Engine: PInteger; Word: PWideChar; AllowDynforms: LongBool ): integer; stdcall; external 'faind.win32.dll' name 'sol_TranslateToBases';


function sol_ProjectWord( Engine: PInteger; Word: PWideChar; Allow_Dynforms: LongBool ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_ProjectWord';
function sol_ProjectMisspelledWord( Engine: PInteger; Word: PWideChar; Allow_Dynforms: LongBool; nmaxmiss: Integer ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_ProjectMisspelledWord';

function sol_CountProjections( hCoordList: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountProjections';

procedure sol_DeleteProjections( hCoordList: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_DeleteProjections';

function sol_GetIEntry( hCoordList: PInteger; Index: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetIEntry';

function sol_GetProjCoordState(
                               Engine: PInteger;
                               hCoordList: PInteger;
                               Index: Integer;
                               Coord: Integer
                              ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetProjCoordState';




function sol_SyntaxAnalysis( Engine: PInteger; Sentence: PWideChar; Allow_Dynforms: LongBool; Allow_Unknown: LongBool ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_SyntaxAnalysis';

procedure sol_DeleteResPack( hPack: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_DeleteResPack';

function sol_CountGrafs( hPack: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountGrafs';

function sol_CountRoots( hPack: PInteger; iGraf: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountRoots';

function sol_GetRoot( hPack: PInteger; iGraf: PInteger; iRoot: PInteger ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_GetRoot';

function sol_CountLeafs( hNode: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountLeafs';

function sol_GetLeaf( hNode: PInteger; iLeaf: Integer ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_GetLeaf';

function sol_GetNodeIEntry( Engine: PInteger; hNode: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetNodeIEntry';

procedure sol_GetNodeContents( hNode: PInteger; Buffer: PWideChar ); stdcall; external 'faind.win32.dll' name 'sol_GetNodeContents';

function sol_SeekThesaurus(
                           Engine: PInteger;
                           iEntry: Integer;
                           Synonyms: Integer;
                           Grammar_Links: Integer;
                           Translations: Integer;
                           Semantics: Integer;
                           nJumps: Integer
                          ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_SeekThesaurus';

function sol_CreateSentenceBroker( Engine: PInteger; Filename: PWideChar; DefaultCodepage: PWideChar; Language: integer ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_CreateSentenceBroker';
function sol_CreateSentenceBrokerMem( Engine: PInteger; Text: PWideChar; Language: integer ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_CreateSentenceBrokerMem';
function sol_FetchSentence( hBroker: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_FetchSentence';
function sol_GetFetchedSentence( hBroker: PInteger; Buffer: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetFetchedSentence';
procedure sol_DeleteSentenceBroker( hBroker: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_DeleteSentenceBroker';

function sol_Tokenize( Engine: PInteger; Sentence: PWideChar ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_Tokenize';

function sol_CountInts( hIntList: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountInts';
function sol_GetInt( hIntList: PInteger; i: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetInt';
procedure sol_DeleteInts( hIntList: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_DeleteInts';

function sol_CreatePhraseGenerator( hEngine: PInteger; ilang: integer ): PInteger; stdcall; external 'faind.win32.dll' name 'sol_CreatePhraseGenerator';
function sol_DeletePhraseGenerator( hBuilder: PInteger ): Integer; stdcall; external 'faind.win32.dll' name 'sol_DeletePhraseGenerator';

function sol_Paraphrase(
                        hBuilder: PInteger;
                        PhraseTypeFlags: Integer;
                        SyntaxAnalysisFlags: Integer;
                        NGramFlags: Integer;
                        ThesaurusFlags: Integer;
                        DebugFlags: Integer;
                        ResultsFormat: Integer;
                        MaxSubst: Integer;
                        OrgPhrase: PWideChar;
                        NewPhrase: PWideChar;
                        maxlen: Integer;
                        max_elapsed_msec: Integer
                       ): integer; stdcall; external 'faind.win32.dll' name 'sol_Paraphrase';



function sol_StopSynonyms( hBuilder: PInteger {HGREN_PHRASOMAT}; n: integer; words_ie: PInteger; use_thesaurus: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_StopSynonyms';
function sol_SetWordsForPhrase( hBuilder: PInteger {HGREN_PHRASOMAT}; n: integer; words_ie: PInteger; use_thesaurus: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_SetWordsForPhrase';
function sol_Set2GramsForPhrase( hBuilder: PInteger {HGREN_PHRASOMAT}; npairs: integer; words_ie: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_Set2GramsForPhrase';
function sol_GeneratePhrase( hBuilder: PInteger {HGREN_PHRASOMAT}; PhraseType: integer; DebugFlags: Integer ): PWideChar; stdcall; external 'faind.win32.dll' name 'sol_GeneratePhrase';
function sol_GeneratePhrase2( hBuilder: PInteger {HGREN_PHRASOMAT}; PhraseType: integer; DebugFlags: Integer; Buffer: PWideChar; maxlen: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_GeneratePhrase2';
function sol_DeleteGeneratedPhrase( Phrase: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_DeleteGeneratedPhrase';
procedure sol_RandomizePhraseGenerator( hBuilder: PInteger {HGREN_PHRASOMAT} ); stdcall; external 'faind.win32.dll' name 'sol_RandomizePhraseGenerator';
function sol_LoadKnowledgeBase( hBuilder: PInteger {HGREN_PHRASOMAT}; FolderPath: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_LoadKnowledgeBase';
function sol_BuildKnowledgeBase( hEngine: PInteger {HFAIND}; DocumentsFolder: PWideChar; DestinationFolder: PWideChar; LanguageId: Integer; Flags: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_BuildKnowledgeBase';


function sol_Seek2Gram( Engine: PInteger; Flags: Integer; Word1: PWideChar; Word2: PWideChar; ): Integer; stdcall; external 'faind.win32.dll' name 'sol_Seek2Gram';
function sol_Seek3Gram( Engine: PInteger; Flags: Integer; Word1: PWideChar; Word2: PWideChar; Word3: PWideChar; ): Integer; stdcall; external 'faind.win32.dll' name 'sol_Seek3Gram';
function sol_Seek4Gram( Engine: PInteger; Flags: Integer; Word1: PWideChar; Word2: PWideChar; Word3: PWideChar; Word4: PWideChar; ): Integer; stdcall; external 'faind.win32.dll' name 'sol_Seek4Gram';
function sol_Seek5Gram( Engine: PInteger; Flags: Integer; Word1: PWideChar; Word2: PWideChar; Word3: PWideChar; Word4: PWideChar; Word5: PWideChar; ): Integer; stdcall; external 'faind.win32.dll' name 'sol_Seek5Gram';


implementation

end.

