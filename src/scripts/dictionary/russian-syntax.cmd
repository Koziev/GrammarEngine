@echo off
rem (c) by Elijah Koziev www.solarix.ru
rem The script recompiles the syntax rules for Russian language, version 'PRO'
rem More info about dictionary compilation:
rem http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

..\..\exe64\compiler -recompile_syntax -j=2 -optimize -dir=..\..\dictionary.src -outdir=..\..\bin-windows64 ..\..\dictionary.src\common-syntax  ..\..\dictionary.src\russian-syntax ..\..\dictionary.src\common_dictionary_xml
Call post-compile.cmd

