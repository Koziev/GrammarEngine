// Lemmatizer API wrapper for Delphi programming language
// (c) by Elijah Koziev, Solarix Intellectronix Project
//
// API manual page:
// http://www.solarix.ru/for_developers/api/lemmatizator_api.shtml
//
// CD->14.04.2010
// LC->04.04.2011

unit LemmatizatorEngineApi;

interface

uses SysUtils;

{ http://www.solarix.ru/api/en/sol_LoadLemmatizator.shtml }
function sol_LoadLemmatizatorW( DbPath: PWideChar; Flags: Integer ): PInteger {HLEMMA}; stdcall; external 'lemmatizator.dll' name 'sol_LoadLemmatizatorW';
function sol_LoadLemmatizatorA( DbPath: PAnsiChar; Flags: Integer ): PInteger {HLEMMA}; stdcall; external 'lemmatizator.dll' name 'sol_LoadLemmatizatorA';

const LEME_DEFAULT: Integer = 0;
const LEME_FASTER: Integer  = 1;
const LEME_FASTEST: Integer = 2;


{ http://www.solarix.ru/api/en/sol_DeleteLemmatizator.shtml }
function sol_DeleteLemmatizator( hEngine: PInteger ): integer; stdcall; external 'lemmatizator.dll' name 'sol_DeleteLemmatizator';

{ http://www.solarix.ru/api/en/sol_GetLemma.shtml }
function sol_GetLemmaW( hEngine: PInteger; Wordform: PWideChar; LemmaBuffer: PWideChar; LemmaBufferSize: Integer ): integer; stdcall; external 'lemmatizator.dll' name 'sol_GetLemmaW';
function sol_GetLemmaA( hEngine: PInteger; Wordform: PAnsiChar; LemmaBuffer: PAnsiChar; LemmaBufferSize: Integer ): integer; stdcall; external 'lemmatizator.dll' name 'sol_GetLemmaA';

{ http://www.solarix.ru/api/en/sol_GetLemmas.shtml }
function sol_GetLemmasW( hEngine: PInteger; word: PWideChar ): PInteger; stdcall; external 'lemmatizator.dll' name 'sol_GetLemmasW';
function sol_GetLemmasA( hEngine: PInteger; word: PAnsiChar ): PInteger; stdcall; external 'lemmatizator.dll' name 'sol_GetLemmasA';

{ http://www.solarix.ru/api/en/sol_CountLemmas.shtml }
function sol_CountLemmas( hList: PInteger ): integer; stdcall; external 'lemmatizator.dll' name 'sol_CountLemmas'; 

{ http://www.solarix.ru/api/en/sol_GetLemmaString.shtml }
function sol_GetLemmaStringW( hList: PInteger; Index: Integer; result: PWideChar; bufsize: Integer ): integer; stdcall; external 'lemmatizator.dll' name 'sol_GetLemmaStringW'; 
function sol_GetLemmaStringA( hList: PInteger; Index: Integer; result: PAnsiChar; bufsize: Integer ): integer; stdcall; external 'lemmatizator.dll' name 'sol_GetLemmaStringA'; 

{ http://www.solarix.ru/api/en/sol_DeleteLemmas.shtml }
function sol_DeleteLemmas( hList: PInteger ): integer; stdcall; external 'lemmatizator.dll' name 'sol_DeleteLemmas';

implementation

end.
