@echo off
rem The script builds an empty dictionary, version 'PRO'
rem More info about dictionary compilation:
rem http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

Call cleanup

..\..\exe64\compiler -j=2 -optimize -dir=..\..\dictionary.src -outdir=..\..\bin-windows64 -ldsize=100000 -save_seeker -save_affixes -save_prefix_entry_searcher ..\..\dictionary.src\version-pro ..\..\dictionary.src\dictionary ..\..\dictionary.src\common_dictionary_xml ..\..\dictionary.src\empty_dictionary_xml
