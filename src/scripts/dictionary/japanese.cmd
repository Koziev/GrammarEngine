@echo off

rem (c) by Elijah Koziev www.solarix.ru
rem More info about dictionary compilation:
rem http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

Call cleanup.cmd

..\..\exe64\compiler -j=2 -ldsize=2000000 -optimize -dir=..\..\dictionary.src -outdir=..\..\bin-windows64 -save_lemmatizer -save_seeker -save_affixes -save_prefix_entry_searcher ..\..\dictionary.src\version-pro ..\..\dictionary.src\dictionary -file=..\..\dictionary.src\japanese-language-only.sol ..\..\dictionary.src\japanese-lexicon ..\..\dictionary.src\japanese-thesaurus ..\..\dictionary.src\japanese-prononcation ..\..\dictionary.src\dictionary-japanese ..\..\dictionary.src\japanese-syntax ..\..\dictionary.src\common_dictionary_xml

Call post-compile.cmd
