// Wrapper для вызова API грамматического движка из программы на Delphi.
// (c) by Koziev Elijah, Solarix Intellectronix Project
//
// List of API functions: http://www.solarix.ru/api/ru/list.shtml
//                        http://www.solarix.ru/api/en/list.shtml
//
// CD->27.11.2008
// LC->22.10.2011

unit GrammarEngineApi;

interface

uses SysUtils;

// http://www.solarix.ru/api/ru/sol_CreateGrammarEngine.shtml
function sol_CreateGrammarEngineA( DictionaryXml: PChar ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CreateGrammarEngineA';
function sol_CreateGrammarEngineW( DictionaryXml: PWideChar ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CreateGrammarEngineW';

// http://www.solarix.ru/api/ru/sol_DeleteGrammarEngine.shtml
function sol_DeleteGrammarEngine( hEngine: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteGrammarEngine';

// http://www.solarix.ru/api/ru/sol_CountEntries.shtml
function sol_CountEntries( hEngine: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountEntries';

function sol_CountForms( hEngine: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountForms';

// http://www.solarix.ru/api/ru/sol_CountLinks.shtml
function sol_CountLinks( hEngine: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountLinks';

// http://www.solarix.ru/api/en/sol_MaxLexemLen.shtml
function sol_MaxLexemLen( hEngine: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_MaxLexemLen';

function sol_LemmatizeWord( hEngine: PInteger; Word: PWideChar; Allow_Dynforms: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_LemmatizeWord';

// http://www.solarix.ru/api/ru/sol_FindEntry.shtml
function sol_FindEntry( hEngine: PInteger; Word: PWideChar; iClass: integer; Language: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FindEntry';

function sol_GetVersion( hEngine: PInteger; Major: PInteger; Minor: PInteger; Build: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetVersion';

function sol_DictionaryVersion( hEngine: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_DictionaryVersion';

function sol_FindStringsEx( hEngine: PInteger; Word: PWideChar;
                            Allow_Dynforms: Integer;
                            Synonyms: Integer;
                            Grammar_Links: Integer;
                            Translations: Integer;
                            Semantics: Integer;
                            nJumps: integer
                           ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FindStringsEx';


function sol_CountStrings( hStrList: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountStrings';
function sol_GetStringLen( hStrList: PInteger; i: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetStringLen';
function sol_GetStringW( hStrList: PInteger; i: integer; Word: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetStringW';
function sol_GetStringA( hStrList: PInteger; i: integer; Word: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetStringA';
function sol_GetString8( hStrList: PInteger; i: integer; Word: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetString8';
function sol_DeleteStrings( hStrList: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteStrings';

// http://www.solarix.ru/api/ru/sol_GetEntryName.shtml
function sol_GetEntryName( hEngine: PInteger; EntryIndex: integer; Result: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetEntryName';

// http://www.solarix.ru/api/ru/sol_GetEntryClass.shtml
function sol_GetEntryClass( hEngine: PInteger; EntryIndex: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetEntryClass';

// http://www.solarix.ru/api/ru/sol_GetClassName.shtml
function sol_GetClassName( hEngine: PInteger; ClassIndex: integer; Word: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetClassName';

// http://www.solarix.ru/api/ru/sol_GetCoordType.shtml
function sol_GetCoordType( hEngine: PInteger; CoordId: integer; ClassId: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetCoordType';

// http://www.solarix.ru/api/ru/sol_FindClass.shtml
function sol_FindClass( hEngine: PInteger; ClassName: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FindClass';

// http://www.solarix.ru/api/ru/sol_FindEnum.shtml
function sol_FindEnum( hEngine: PInteger; EnumName: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FindEnum';

// http://www.solarix.ru/api/ru/sol_FindEnumState.shtml
function sol_FindEnumState( hEngine: PInteger; Enum: integer; StateName: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FindEnumState';

// http://www.solarix.ru/api/ru/sol_GetNounGender.shtml
function sol_GetNounGender( hEngine: PInteger; EntryIndex: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetNounGender';

function sol_GetNounForm( Engine: PInteger; EntryIndex: integer; Number: integer; iCase: integer; Result: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetNounForm';




function sol_GetVerbForm( Engine: PInteger; EntryIndex: integer;
                          Number: Integer;
                          Gender: Integer;
                          Tense: Integer;
                          Person: Integer;
                          Result: PWideChar
                         ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetVerbForm';


function sol_GetAdjectiveForm( Engine: PInteger; EntryIndex: integer;
                               Number: Integer;
                               Gender: Integer;
                               ICase: Integer;
                               Anim: Integer;
                               Shortness: Integer;
                               Compar_Form: Integer;
                               Result: PWideChar
                              ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetAdjectiveForm';

function sol_CorrNounNumber( Engine: PInteger; EntryIndex: integer;
                             Value: Integer;
                             ICase: Integer;
                             Anim: Integer;
                             Result: PWideChar
                            ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CorrNounNumber';

function sol_CorrVerbNumber( Engine: PInteger; EntryIndex: integer;
                             Value: Integer;
                             Gender: Integer;
                             Tense: Integer;
                             Result: PWideChar
                            ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CorrVerbNumber';

function sol_CorrAdjNumber( Engine: PInteger; EntryIndex: integer;
                            Value: Integer;
                            Iase: Integer;
                            Gender: Integer;
                            Anim: Integer;
                            Result: PWideChar
                           ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CorrAdjNumber';

function sol_FindWord( Engine: PInteger;
                       Word: PWideChar;
                       EntryIndex: PInteger;
                       Form: PInteger;
                       ClassIndex: PInteger
                      ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FindWord';

function sol_Value2Text(
                        Engine: PInteger;
                        Result: PWideChar;
                        Value: Integer;
                        Gender: Integer
                       ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_Value2Text';

function sol_SeekWord( Engine: PInteger; word: PWideChar; Allow_Dynforms: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_SeekWord';
function sol_TranslateToNoun( Engine: PInteger; EntryIndex: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_TranslateToNoun';
function sol_TranslateToInfinitive( Engine: PInteger; EntryIndex: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_TranslateToInfinitive';
function sol_TranslateToBase( Engine: PInteger; Word: PWideChar; AllowDynforms: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_TranslateToBase';
function sol_TranslateToBases( Engine: PInteger; Word: PWideChar; AllowDynforms: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_TranslateToBases';


function sol_ProjectWord( Engine: PInteger; Word: PWideChar; Allow_Dynforms: Integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_ProjectWord';
function sol_ProjectMisspelledWord( Engine: PInteger; Word: PWideChar; Allow_Dynforms: Integer; nmaxmiss: Integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_ProjectMisspelledWord';

function sol_CountProjections( hCoordList: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountProjections';

procedure sol_DeleteProjections( hCoordList: PInteger ); stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteProjections';

function sol_GetIEntry( hCoordList: PInteger; Index: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetIEntry';

function sol_GetProjCoordState(
                               Engine: PInteger;
                               hCoordList: PInteger;
                               Index: Integer;
                               Coord: Integer
                              ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetProjCoordState';



// http://www.solarix.ru/api/ru/sol_SyntaxAnalysis.shtml
function sol_SyntaxAnalysis( Engine: PInteger; Sentence: PWideChar; MorphologicalFlags: Integer; SyntacticFlags: Integer; MaxMillisecTimeout: Integer; LanguageID: Integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_SyntaxAnalysis';
function sol_SyntaxAnalysisA( Engine: PInteger; Sentence: PAnsiChar; MorphologicalFlags: Integer; SyntacticFlags: Integer; MaxMillisecTimeout: Integer; LanguageID: Integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_SyntaxAnalysisA';

// http://www.solarix.ru/api/ru/sol_MorphologyAnalysis.shtml
function sol_MorphologyAnalysis( Engine: PInteger; Sentence: PWideChar; Flags: Integer; UnusedFlags: Integer; MaxMillisecTimeout: Integer; LanguageID: Integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_MorphologyAnalysis';
function sol_MorphologyAnalysisA( Engine: PInteger; Sentence: PAnsiChar; Flags: Integer; UnusedFlags: Integer; MaxMillisecTimeout: Integer; LanguageID: Integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_MorphologyAnalysisA';

// http://www.solarix.ru/api/ru/sol_DeleteResPack.shtml
procedure sol_DeleteResPack( hPack: PInteger ); stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteResPack';

// http://www.solarix.ru/api/ru/sol_CountGrafs.shtml
function sol_CountGrafs( hPack: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountGrafs';

// http://www.solarix.ru/api/ru/sol_CountRoots.shtml
function sol_CountRoots( hPack: PInteger; iGraf: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountRoots';

// http://www.solarix.ru/api/ru/sol_GetRoot.shtml
function sol_GetRoot( hPack: PInteger; iGraf: Integer; iRoot: Integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetRoot';

// http://www.solarix.ru/api/ru/sol_CountLeafs.shtml
function sol_CountLeafs( hNode: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountLeafs';

// http://www.solarix.ru/api/ru/sol_GetLeaf.shtml
function sol_GetLeaf( hNode: PInteger; iLeaf: Integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetLeaf';

// http://www.solarix.ru/api/ru/sol_GetNodeIEntry.shtml
function sol_GetNodeIEntry( Engine: PInteger; hNode: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetNodeIEntry';

// http://www.solarix.ru/api/ru/sol_GetNodeContents.shtml
procedure sol_GetNodeContents( hNode: PInteger; Buffer: PWideChar ); stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetNodeContents';

// http://www.solarix.ru/api/ru/sol_GetNodePairsCount.shtml
function sol_GetNodePairsCount( hNode: PInteger ): integer;  stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetNodePairsCount';

// http://www.solarix.ru/api/ru/sol_GetNodeCoordState.shtml
function sol_GetNodeCoordState( hNode: PInteger; CoordID: Integer ): integer;  stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetNodeCoordState';

// http://www.solarix.ru/api/ru/sol_GetNodePairCoord.shtml
function sol_GetNodePairCoord( hNode: PInteger; ipair: Integer ): integer;  stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetNodePairCoord';

// http://www.solarix.ru/api/ru/sol_GetNodePairState.shtml
function sol_GetNodePairState( hNode: PInteger; ipair: Integer ): integer;  stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetNodePairState';


function sol_SeekThesaurus(
                           Engine: PInteger;
                           iEntry: Integer;
                           Synonyms: Integer;
                           Grammar_Links: Integer;
                           Translations: Integer;
                           Semantics: Integer;
                           nJumps: Integer
                          ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_SeekThesaurus';


// Группа функций сегментатора - разбивка текста на предложения и разбивка предложений на слова

// http://www.solarix.ru/api/ru/sol_CreateSentenceBroker.shtml
function sol_CreateSentenceBroker( Engine: PInteger; Filename: PWideChar; DefaultCodepage: PWideChar; Language: integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CreateSentenceBroker';

// http://www.solarix.ru/api/ru/sol_CreateSentenceBrokerMem.shtml
function sol_CreateSentenceBrokerMemW( Engine: PInteger; Text: PWideChar; Language: integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CreateSentenceBrokerMemW';
function sol_CreateSentenceBrokerMemA( Engine: PInteger; Text: PAnsiChar; Language: integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CreateSentenceBrokerMemA';
function sol_CreateSentenceBrokerMem8( Engine: PInteger; TextUtf8: PAnsiChar; Language: integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CreateSentenceBrokerMem8';

// http://www.solarix.ru/api/ru/sol_FetchSentence.shtml
function sol_FetchSentence( hBroker: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FetchSentence';

// http://www.solarix.ru/api/ru/sol_GetFetchedSentence.shtml
function sol_GetFetchedSentenceW( hBroker: PInteger; Buffer: PWideChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetFetchedSentenceW';
function sol_GetFetchedSentenceA( hBroker: PInteger; Buffer: PAnsiChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetFetchedSentenceA';
function sol_GetFetchedSentence8( hBroker: PInteger; Buffer: PAnsiChar ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetFetchedSentence8';

// http://www.solarix.ru/api/ru/sol_DeleteSentenceBroker.shtml
procedure sol_DeleteSentenceBroker( hBroker: PInteger ); stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteSentenceBroker';

// http://www.solarix.ru/api/ru/sol_Tokenize.shtml
function sol_TokenizeW( Engine: PInteger; Sentence: PWideChar; id_lang: integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_TokenizeW';
function sol_TokenizeA( Engine: PInteger; Sentence: PAnsiChar; id_lang: integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_TokenizeA';
function sol_Tokenize8( Engine: PInteger; Sentence: PAnsiChar; id_lang: integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_Tokenize8';

// http://www.solarix.ru/api/ru/sol_CountInts.shtml
function sol_CountInts( hIntList: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountInts';

// http://www.solarix.ru/api/ru/sol_GetInt.shtml
function sol_GetInt( hIntList: PInteger; i: Integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetInt';

// http://www.solarix.ru/api/ru/sol_DeleteInts.shtml
procedure sol_DeleteInts( hIntList: PInteger ); stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteInts';


{ --- NGRAMS DATABASE ACCESS FUNCTIONS --- }

{ http://www.solarix.ru/api/en/sol_CountNGrams.shtml }
function sol_CountNGrams( hEngine: PInteger; Flags: Integer; Order: Integer; Hi: PInteger; Lo: PInteger ): Integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountNGrams';

function sol_CountNGrams64( hEngine: PInteger; Flags: Integer; Order: Integer ): Int64;

{ http://www.solarix.ru/api/en/sol_Seek1Grams.shtml }
function sol_Seek1Grams( hEngine: PInteger; Flags: Integer; Word1: PWideChar ): Integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_Seek1Grams';

{ http://www.solarix.ru/api/en/sol_Seek2Grams.shtml }
function sol_Seek2Grams( hEngine: PInteger; Flags: Integer; Word1: PWideChar; Word2: PWideChar ): Integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_Seek2Grams';

{ http://www.solarix.ru/api/en/sol_Seek3Grams.shtml }
function sol_Seek3Grams( hEngine: PInteger; Flags: Integer; Word1: PWideChar; Word2: PWideChar; Word3: PWideChar ): Integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_Seek3Grams';

{ http://www.solarix.ru/api/en/sol_Seek4Grams.shtml }
function sol_Seek4Grams( hEngine: PInteger; Flags: Integer; Word1: PWideChar; Word2: PWideChar; Word3: PWideChar; Word4: PWideChar ): Integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_Seek4Grams';

{ http://www.solarix.ru/api/en/sol_Seek5Grams.shtml }
function sol_Seek5Grams( hEngine: PInteger; Flags: Integer; Word1: PWideChar; Word2: PWideChar; Word3: PWideChar; Word4: PWideChar; Word5: PWideChar ): Integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_Seek5Grams';




function sol_FindFlexionHandlers(
                                 hEngine: PInteger;
                                 WordBasicForm: PWideChar;
                                 SearchEntries: integer
                                ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FindFlexionHandlers';

function sol_CountEntriesInFlexionHandlers(
                                           hEngine: PInteger;
                                           hFlexs: PInteger
                                          ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountEntriesInFlexionHandlers';

function sol_CountParadigmasInFlexionHandlers(
                                              hEngine: PInteger;
                                              hFlexs: PInteger
                                             ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountParadigmasInFlexionHandlers';

function sol_GetEntryInFlexionHandlers(
                                       hEngine: PInteger;
                                       hFlexs: PInteger;
                                       Index: integer
                                      ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetEntryInFlexionHandlers';

function sol_GetParadigmaInFlexionHandlers(
                                           hEngine: PInteger;
                                           hFlexs: PInteger;
                                           Index: integer;
                                           ParadigmaName: PWideChar
                                          ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetParadigmaInFlexionHandlers';

function sol_BuildFlexionHandler(
                                 hEngine: PInteger;
                                 hFlexs: PInteger;
                                 ParadigmaName: PWideChar;
                                 EntryIndex: integer
                                ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_BuildFlexionHandler';

function sol_GetFlexionHandlerWordform(
                                       hEngine: PInteger;
                                       hFlex: PInteger;
                                       dims: PWideChar
                                      ): PWideChar; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetFlexionHandlerWordform';


function sol_DeleteFlexionHandlers(
                                   hEngine: PInteger;
                                   hFlexs: PInteger
                                  ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteFlexionHandlers';

function sol_DeleteFlexionHandler(
                                  hEngine: PInteger;
                                  hFlex: PInteger
                                 ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteFlexionHandler';

// http://www.solarix.ru/api/ru/sol_GetCoordName.shtml
function sol_GetCoordName(
                          hEngine: PInteger;
                          id_coord: integer;
                          name: PWideChar
                         ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetCoordName';

// http://www.solarix.ru/api/ru/sol_GetCoordStateName.shtml
function sol_GetCoordStateName(
                               hEngine: PInteger;
                               id_coord: integer;
                               id_state: integer;
                               name: PWideChar
                              ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetCoordStateName';

// http://www.solarix.ru/api/ru/sol_CountCoordStates.shtml
function sol_CountCoordStates(
                              hEngine: PInteger;
                              id_coord: integer
                             ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_CountCoordStates';


// http://www.solarix.ru/api/ru/sol_FindPhrase.shtml
function sol_FindPhrase( hEngine: PInteger; Phrase: PWideChar; Flags: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_FindPhrase';

// http://www.solarix.ru/api/ru/sol_AddPhrase.shtml
function sol_AddPhrase( hEngine: PInteger; text: PWideChar; LanguageID: integer; ClassID: integer; ProcessingFlags: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_AddPhrase';

// http://www.solarix.ru/api/ru/sol_DeletePhrase.shtml
function sol_DeletePhrase( hEngine: PInteger; PhraseID: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeletePhrase';

// http://www.solarix.ru/api/ru/sol_GetPhraseLanguage.shtml
function sol_GetPhraseLanguage( hEngine: PInteger; PhraseID: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetPhraseLanguage';

// http://www.solarix.ru/api/ru/sol_GetPhraseClass.shtml
function sol_GetPhraseClass( hEngine: PInteger; PhraseID: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetPhraseClass';

// http://www.solarix.ru/api/ru/sol_GetPhraseText.shtml
function sol_GetPhraseText( hEngine: PInteger; PhraseID: integer ): PWideChar; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetPhraseText';
function sol_GetPhraseTextPAS( hEngine: PInteger; PhraseID: integer ): WideString;

// http://www.solarix.ru/api/en/sol_Free.shtml
function sol_Free( hEngine: PInteger; Ptr: Pointer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_Free';

// http://www.solarix.ru/api/ru/sol_GetErrorLen.shtml
function sol_GetErrorLen( hEngine: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetErrorLen';

// http://www.solarix.ru/api/ru/sol_GetError.shtml
function sol_GetError( hEngine: PInteger; TextBuffer: PWideChar; TextBufferLen: integer ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_GetError';
function sol_GetErrorPAS( hEngine: PInteger ): WideString;

// http://www.solarix.ru/api/ru/sol_ClearError.shtml
function sol_ClearError( hEngine: PInteger ): integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_ClearError';


// http://www.solarix.ru/api/en/sol_ListLinksTxt.shtml
function sol_ListLinksTxt( hEngine: PInteger; EntryID1: integer; LinkType: integer; Flags: integer ): PInteger; stdcall; external 'solarix_grammar_engine.dll' name 'sol_ListLinksTxt';

// http://www.solarix.ru/api/en/sol_DeleteLinksInfo.shtml
function sol_DeleteLinksInfo( hEngine: PInteger; hList: PInteger {HLINKSINFO} ) : integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_DeleteLinksInfo';

// http://www.solarix.ru/api/en/sol_LinksInfoCount.shtml
function sol_LinksInfoCount( hEngine: PInteger; hList: PInteger {HLINKSINFO} ) : integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_LinksInfoCount';

// http://www.solarix.ru/api/en/sol_LinksInfoType.shtml
function sol_LinksInfoType( hEngine: PInteger; hList: PInteger {HLINKSINFO}; Index: integer ) : integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_LinksInfoType';

// http://www.solarix.ru/api/en/sol_LinksInfoID.shtml
function sol_LinksInfoID( hEngine: PInteger; hListhList: PInteger {HLINKSINFO}; Index: integer ) : integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_LinksInfoID';

// http://www.solarix.ru/api/ru/sol_LinksInfoCode.shtml
function sol_LinksInfoCode( hEngine: PInteger; hListhList: PInteger {HLINKSINFO}; Index: integer ) : integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_LinksInfoCode';

// http://www.solarix.ru/api/en/sol_LinksInfoEKey1.shtml
function sol_LinksInfoEKey1( hEngine: PInteger; hListhList: PInteger {HLINKSINFO}; Index: integer ) : integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_LinksInfoEKey1';

// http://www.solarix.ru/api/en/sol_LinksInfoEKey2.shtml
function sol_LinksInfoEKey2( hEngine: PInteger; hListhList: PInteger {HLINKSINFO}; Index: integer ) : integer; stdcall; external 'solarix_grammar_engine.dll' name 'sol_LinksInfoEKey2';



implementation

function sol_GetErrorPAS( hEngine: PInteger ): WideString;
var len: integer;
var ptr_str: PWideChar;
begin

 sol_GetErrorPAS := '';
 len := sol_GetErrorLen( hEngine );

 if( len<>0 )
  then begin
   ptr_str := PWideChar(StrAlloc( (len+1)*2 ));
   if( ptr_str<>nil )
    then begin
     sol_GetError( hEngine, ptr_str, len );
     sol_ClearError(hEngine);
     sol_GetErrorPAS := WideString( PWideChar(ptr_str) );
    end
  end

end;


function sol_CountNGrams64( hEngine: PInteger; Flags: Integer; Order: Integer ): Int64;
var Hi, Lo: integer;
var Res: Int64;
var rc: integer;
begin

 rc := sol_CountNGrams( hEngine, Flags, Order, @Hi, @Lo );
 
 Res := (Int64(Hi) Shl 32) OR Int64(Lo);
 
 sol_CountNGrams64 := Res; 

end;


function sol_GetPhraseTextPAS( hEngine: PInteger; PhraseID: integer ): WideString;
var str_ptr: PWideChar;
var res: WideString;
begin
 str_ptr := sol_GetPhraseText( hEngine, PhraseID );
 if( str_ptr<>nil )
  then begin
   res := str_ptr;
   sol_Free( hEngine, str_ptr );
   sol_GetPhraseTextPAS := res;
  end else
  begin
   sol_GetPhraseTextPAS := '';
  end;
end;

end.
