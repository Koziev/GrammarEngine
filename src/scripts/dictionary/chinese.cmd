@echo off
rem (c) by Elijah Koziev www.solarix.ru
rem More info about dictionary compilation:
rem http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml


Call cleanup.cmd

..\..\exe64\compiler /j=2 /ldsize=2000000 -dir=..\..\dictionary.src -outdir=..\..\bin-windows64 -save_seeker -save_affixes -save_lemmatizer -save_prefix_entry_searcher ..\..\dictionary.src\version-pro ..\..\dictionary.src\dictionary -file=..\..\dictionary.src\chinese-language-only.sol ..\..\dictionary.src\chinese_lexicon ..\..\dictionary.src\dictionary-chinese ..\..\dictionary.src\common_dictionary_xml

Call post-compile.cmd
