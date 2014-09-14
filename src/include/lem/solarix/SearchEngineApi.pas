// Wrapper для вызова API поискового движка из программы на Delphi.
// (c) by Koziev Elijah, Solarix Intellectronix Project
//
// CD->13.04.2010
// LC->13.04.2010

unit SearchEngineApi;

interface

uses SysUtils;

// Инициализация движка и грамматической машины.
// Словарь и другие внешние компоненты пока не загружаются.
function sol_CreateSearchEngine(): PInteger {HFAIND}; stdcall; external 'faind.win32.dll' name 'sol_CreateSearchEngine';
function sol_CreatePortableSearcher( flags: Integer ): PInteger {HFAIND}; stdcall; external 'faind.win32.dll' name 'sol_CreatePortableSearcher';

// Load the dictionary (morphology and syntax analyzer + thesaurus)
// Return: 2 - already loaded, 1 - ok, 0 - error has occured.
function sol_LoadDictionaryA( hEngine: PInteger; Filename: PAnsiChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_LoadDictionaryA';
function sol_LoadDictionaryW( hEngine: PInteger; PWideCharFilename: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_LoadDictionaryW';

// Удаление экземпляра движка, освобождение всех ресурсов.
function sol_DeleteSearchEngine( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_DeleteSearchEngine';

// Для портабельного поисковика (sol_CreatePortableSearcher) - подцепляем индекс в
// указанной папке для последующего поиска.
function sol_AttachPortableIndex( hEngine: PInteger; IndexFolder: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_AttachPortableIndex';

// Завершение инициализации поискового движка - загрузка параметров
// из указанного конфигурационного файла.
function sol_ReadIniW( hEngine: PInteger; ini_filename: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_ReadIniW';
function sol_ReadIniA( hEngine: PInteger; ini_filename: PAnsiChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_ReadIniA';


// Включение трассировки активности поискового движка в указанный файл.
// Возвращается: 0 - трассировка включена, -1 ошибка открытия файла журнала
function sol_OpenLogFileA( hEngine: PInteger; logfilename: PAnsiChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_OpenLogFileA';
function sol_OpenLogFileW( hEngine: PInteger; logfilename: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_OpenLogFileW';


// Выключение трассировки в журнал, файл журнала закрывается.
procedure sol_CloseLogFile( hEngine: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_CloseLogFile';

// Генерировать результаты поиска как HTML страницу, а не XML по умолчанию.
procedure sol_GenerateHtml( hEngine: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_GenerateHtml';

// Generate XML results (this is default behaviour of the engine).
procedure sol_GenerateXml( hEngine: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_GenerateXml';

// Result page is not needed.
procedure sol_NoResults( hEngine: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_NoResults';


// В HTML результатах не размещать заголовок
// (тэги <html><title>...</title><body> и закрывающие </body></html>).
procedure sol_StripHtml( hEngine: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_StripHtml';


// Заполняет буфер текстом с описанием последней ошибки. Возвращает
// 0, если ошибок не было, 1 если были. Указатель на буфер может быть NULL,
// тогда просто возвращается признак наличия ошибки.
function sol_GetError( hEngine: PInteger; buffer: PWideChar; buffer_len: integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetError';


// Очищает внутренний признак ошибки
procedure sol_ClearError( hEngine: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_ClearError';

// Процедуры для работы с группой параметров для подстановки в запросах.
function sol_CreateParams( hEngine: PInteger ): PInteger {HFAINDPARAMS}; stdcall; external 'faind.win32.dll' name 'sol_CreateParams';
function sol_DeleteParams( {HFAINDPARAMS} hParams: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_DeleteParams';
function sol_AddParam( {HFAINDPARAMS} hParams: PInteger; ParamName: PWideChar; ParamValue: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_AddParam';

// Parse the query and return the executor handle.
function sol_ParseQuery( hEngine: PInteger; query: PWideChar ): PInteger {HFAINDCMD}; stdcall; external 'faind.win32.dll' name 'sol_ParseQuery';
function sol_ParseSqlQuery( hEngine: PInteger; query: PWideChar ): PInteger {HFAINDCMD}; stdcall; external 'faind.win32.dll' name 'sol_ParseSqlQuery';
function sol_ParseQueryWithParams( hEngine: PInteger; query: PWideChar; {HFAINDPARAMS} hParams: PInteger ): PInteger {HFAINDCMD}; stdcall; external 'faind.win32.dll' name 'sol_ParseQueryWithParams';
function sol_ParseSqlQueryWithParams( hEngine: PInteger; query: PWideChar; {HFAINDPARAMS} hParams: PInteger ): PInteger {HFAINDCMD}; stdcall; external 'faind.win32.dll' name 'sol_ParseSqlQueryWithParams';

// Run the executor which executes the query.
function sol_ExecuteQuery( hEngine: PInteger; {HFAINDCMD} hCmd: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_ExecuteQuery';

// Delete the executor after all.
procedure sol_DeleteQuery( {HFAINDCMD} hCmd: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_DeleteQuery';

// Do sol_ParseQuery, sol_ExecuteQuery, sol_DeleteQuery
function sol_Execute( hEngine: PInteger; query: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_Execute';
function sol_ExecuteSql( hEngine: PInteger; query: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_ExecuteSql';
function sol_ExecuteWithParams( hEngine: PInteger; query: PWideChar; {HFAINDPARAMS} hParams: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_ExecuteWithParams';
function sol_ExecuteSqlWithParams( hEngine: PInteger; query: PWideChar; {HFAINDPARAMS} hParams: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_ExecuteSqlWithParams';


// Возвращает длину (в символах char) буфера результата.
function sol_GetResultLen( {HFAINDCMD} hCmd: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetResultLen';

// Копирует результаты поиска в указанный буфер, который должен иметь достаточную
// длину (см. sol_GetResultLen).
procedure sol_GetResult( {HFAINDCMD} hCmd: PInteger; buffer: PAnsiChar ); stdcall; external 'faind.win32.dll' name 'sol_GetResult';
procedure sol_GetResultW( {HFAINDCMD} hCmd: PInteger; buffer: PWideChar ); stdcall; external 'faind.win32.dll' name 'sol_GetResultW';


// Установка пользовательских callback-процедур для отображения процесса сканирования
// файлов при поиске или индексировании.
//
// Return value:
//              0  - callback function is installed
//              -1 - an error has occured

type EngineCallbackProc_StartFile = procedure( Filename: PWideChar ); stdcall;
type EngineCallbackProc_StartFolder = procedure( Folder: PWideChar ); stdcall;
type EngineCallbackProc_Success = procedure( Filename: PWideChar; Location: PWideChar; TmpFilename: PWideChar ); stdcall;

function sol_SetCallback_StartFile( hEngine: PInteger; ptrFunction: EngineCallbackProc_StartFile ): integer; stdcall; external 'faind.win32.dll' name 'sol_SetCallback_StartFile';
function sol_SetCallback_StartFolder( hEngine: PInteger; ptrFunction: EngineCallbackProc_StartFolder ): integer; stdcall; external 'faind.win32.dll' name 'sol_SetCallback_StartFolder';
function sol_SetCallback_Success( hEngine: PInteger; ptrFunction: EngineCallbackProc_Success ): integer; stdcall; external 'faind.win32.dll' name 'sol_SetCallback_Success';

// Returns the size (in wchar_t's + 1) of the buffer needed for storing the list of
// index names. The list can be retrieved via sol_GetDomainsList call.
function sol_GetDomainsListSize( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetDomainsListSize';

// Returns the number of indexes whose names are listed in 'Buffer'.
// Each index name is followed  by 'Delimiter' char
function sol_GetDomainsList( hEngine: PInteger; Delimiter: WideChar; Buffer: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetDomainsList';
function sol_GetDomainsListXml( hEngine: PInteger ): PInteger {HFAINDXML}; stdcall; external 'faind.win32.dll' name 'sol_GetDomainsListXml';

function sol_XmlTextLen( {HFAINDXML} xml: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_XmlTextLen';
function sol_GetXmlText( {HFAINDXML} xml: PInteger; Buffer: PAnsiChar; BufferSize: integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetXmlText';
procedure sol_DeleteXml( {HFAINDXML} xml: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_DeleteXml';

// Возвращает количество актуальных индексов
function sol_CountDomains( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountDomains';

// Возвращает указатель (или NULL) на строку комменария к индексу.
function sol_GetDomainComment( hEngine: PInteger; Domain_Name: PWideChar ): PWideChar; stdcall; external 'faind.win32.dll' name 'sol_GetDomainComment';

// Поиск актуального индекса с заданным именем, возвращается id индекса либо -1, если
// поиск безуспешен.
function sol_FindDomain( hEngine: PInteger; Domain_Name: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_FindDomain';


// ***************************************************************************
// Группа процедур для работы с расширенными регулярными выражениями (RegexEx)
// ***************************************************************************

// Конструктор и деструктор
function sol_CreateRx( hEngine: PInteger; Pattern: PWideChar ): PInteger {HREGEXEX}; stdcall; external 'faind.win32.dll' name 'sol_CreateRx';
procedure sol_DeleteRx( {HREGEXEX} hRegex: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_DeleteRx';

// Изменение параметров
procedure sol_SetMorphologyRx( {HREGEXEX} hRegexex: PInteger; Mode: Integer ); stdcall; external 'faind.win32.dll' name 'sol_SetMorphologyRx';
procedure sol_SetSyntaxRx( {HREGEXEX} hRegexex: PInteger; Mode: Integer ); stdcall; external 'faind.win32.dll' name 'sol_SetSyntaxRx';
procedure sol_SetSameSentenceRx( {HREGEXEX} hRegex: PInteger ); stdcall; external 'faind.win32.dll' name 'sol_SetSameSentenceRx';
procedure sol_SetDistanceRx( {HREGEXEX} hRegexex: PInteger; Distance: Integer ); stdcall; external 'faind.win32.dll' name 'sol_SetDistanceRx';
procedure sol_SetOrderedRx( {HREGEXEX} hRegexex: PInteger; Ordered: Integer ); stdcall; external 'faind.win32.dll' name 'sol_SetOrderedRx';
procedure sol_EnableThesaurusRx(
                                      hEngine: PInteger;
                                      {HREGEXEX} hRegexex: PInteger;
                                      Jumps: Integer;
                                      Synonyms: Integer;
                                      Grammar: Integer;
                                      Semantics: Integer;
                                      Translations: Integer
                                     ); stdcall; external 'faind.win32.dll' name 'sol_EnableThesaurusRx';
procedure sol_SetSoundexRx( {HREGEXEX} hRegexex: PInteger; Enable: Integer ); stdcall; external 'faind.win32.dll' name 'sol_SetSoundexRx';
procedure sol_AllowPartialMatchingRx( {HREGEXEX} hRegexex: PInteger; Allow: Integer ); stdcall; external 'faind.win32.dll' name 'sol_AllowPartialMatchingRx';
procedure sol_SetStripAccentsRx( {HREGEXEX} hRegexex: PInteger; Strip: Integer ); stdcall; external 'faind.win32.dll' name 'sol_SetStripAccentsRx';
procedure sol_SetOnlyOneMatchRx( {HREGEXEX} hRegexex: PInteger; OnlyOne: Integer ); stdcall; external 'faind.win32.dll' name 'sol_SetOnlyOneMatchRx';

// Поиск и анализ результатов
function sol_SearchRx( {HREGEXEX} hRegexex: PInteger; BeginStr: PWideChar; EndStr: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_SearchRx';
function sol_CountMatchesRx( {HREGEXEX} hRegex: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountMatchesRx';
function sol_GetMatchTextLenRx( {HREGEXEX} hRegexex: PInteger; Index: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetMatchTextLenRx';
procedure sol_GetMatchTextRx( {HREGEXEX} hRegexex: PInteger; Index: Integer; Buffer: PWideChar; BufferSize: Integer ); stdcall; external 'faind.win32.dll' name 'sol_GetMatchTextRx';
function sol_GetMatchRankRx( {HREGEXEX} hRegexex: PInteger; Index: Integer ): Double; stdcall; external 'faind.win32.dll' name 'sol_GetMatchRankRx';

function sol_FindTaggedDocument( hEngine: PInteger; Filename: PWideChar; Location: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_FindTaggedDocument';
//function sol_GetDocumentTag( hEngine: PInteger, int Id_doc, Tag: PWideChar; wchar_t **Value );
function sol_AddTaggedDocument( hEngine: PInteger; Filename: PWideChar; Location: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_AddTaggedDocument';
function sol_SetDocumentTag( hEngine: PInteger; Id_doc: Integer; Tag: PWideChar; Value: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_SetDocumentTag';


// Return the Solarix project version info.
// Если указатели Major, Minor, Build не равны NULL, то через них
// возвращаются соответствующие части номера версии компонента.
//
// Возвращает 0 для LITE, 1 для PRO, 2 для PREMIUM
function sol_GetVersion( hEngine: PInteger; Major: PInteger; Minor: PInteger; Build: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetVersion';

// Возвращает номер версии загруженного словаря.
function sol_DictionaryVersion( hEngine: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_DictionaryVersion';

function sol_CountStrings( {HGREN_STR} hStr: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_CountStrings';
//function sol_GetStrings( {HGREN_STR} hStr: PInteger;, wchar_t **Res );
function sol_GetString( {HGREN_STR} hStr: PInteger; i: Integer; Res: PWideChar ): integer; stdcall; external 'faind.win32.dll' name 'sol_GetString';
function sol_DeleteStrings( {HGREN_STR} hStr: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_DeleteStrings';

function sol_Free( hEngine: PInteger; Ptr: PInteger ): integer; stdcall; external 'faind.win32.dll' name 'sol_Free';

// Probe the lexicon for language entries.
// Returns 1 if language is present in lexicon, 0 if not,
function sol_HasLanguage( hEngine: PInteger; ilanguage: Integer ): integer; stdcall; external 'faind.win32.dll' name 'sol_HasLanguage';


implementation

end.
