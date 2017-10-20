program Project1;

{$APPTYPE CONSOLE}

uses
  SysUtils, Dialogs,
  LemmatizatorEngineApi in '..\..\..\..\..\..\include\lem\solarix\LemmatizatorEngineApi.pas';

var
  hE: Pointer;
  cl: Integer;
  myLemma: PAnsiChar;
  myStr: String;
  hLemmas: Pointer;
  i, n: integer;

begin

  // Страница справки по функциям API: http://www.solarix.ru/for_developers/api/lemmatizator-api.shtml

  // Инициализируем движок и загружаем базу правил лемматизации
  hE := sol_LoadLemmatizatorA('..\..\..\..\..\..\bin-windows\lemmatizer.db',LEME_DEFAULT);

  myStr := 'которыми';
  GetMem( myLemma, 32 );
  // Функция sol_GetLemma[A,W,8] дает единственный вариант, даже если есть альтернативные.
  cl := sol_GetLemmaA( hE, PAnsiChar(myStr), myLemma, 32 );
  ShowMessage( myLemma );

  // для слова РОЕМ должны получить две леммы - инфинитив РЫТЬ и начальную форму
  // существительного РОЙ. Функция sol_GetLemmas[A,W,8] возвращает дескриптор
  // списка лемм.
  hLemmas := sol_GetLemmasA( hE, PAnsiChar('роем') );
  if( hLemmas<>nil )
   then begin

    n := sol_Countlemmas( hLemmas );
    for i:=0 to n-1
     do begin

      sol_GetLemmaStringA( hLemmas, i, myLemma, 32 );
      ShowMessage( myLemma );

     end;

    sol_DeleteLemmas(hLemmas);

   end;

  sol_DeleteLemmatizator(hE);
  
end.
