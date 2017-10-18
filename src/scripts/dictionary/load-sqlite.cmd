@echo off

rem http://www.solarix.ru/for_developers/exercise/ymap.shtml#sql
rem http://www.solarix.ru/for_developers/docs/sql_dictionary.shtml
rem email: mentalcomputing@gmail.com

if exist ..\..\tmp\dictionary.sqlite del ..\..\tmp\dictionary.sqlite

echo Loading the dictionary ...
..\..\exe64\sqlite3.exe ..\..\tmp\dictionary.sqlite < ..\..\tmp\dictionary.sql
if errorlevel 1 goto OnError

rem echo Loading the rules ...
rem ..\..\exe64\sqlite3.exe ..\..\tmp\dictionary.sqlite < ..\..\tmp\rules.sql
rem if errorlevel 1 goto OnError

echo Loading the lemmatizer ...
..\..\exe64\sqlite3.exe ..\..\tmp\dictionary.sqlite < ..\..\tmp\lemmatizator.sql
if errorlevel 1 goto OnError

echo Loading the prefix entry searcher ...
..\..\exe64\sqlite3.exe ..\..\tmp\dictionary.sqlite < ..\..\tmp\prefix_entry_searcher.sql
if errorlevel 1 goto OnError

copy ..\..\tmp\dictionary.sqlite ..\..\bin-windows64

goto End

:OnError

echo 'Error'

:End
