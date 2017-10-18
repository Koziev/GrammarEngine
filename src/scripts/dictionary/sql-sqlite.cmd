echo off

rem This script dumps the dictionary as SQL script for SQLite

rem SQL Export Utility:    http://www.solarix.ru/for_developers/exercise/ymap.shtml#sql
rem SQL Dictionary scheme: http://www.solarix.ru/for_developers/docs/sql_dictionary.shtml

..\..\exe64\decompiler.exe ..\..\bin-windows64\dictionary.xml -outdir=..\..\tmp -sql "sqlite,utf8,lemmatizator"
