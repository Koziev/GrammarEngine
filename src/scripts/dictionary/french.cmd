@echo off
rem (c) by Elijah Koziev www.solarix.ru
rem More info about dictionary compilation:
rem http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

Call cleanup.cmd

..\..\exe64\compiler /j=2 /ldsize=2000000 -dir=..\..\dictionary.src -outdir=..\..\bin-windows64 -save_seeker -save_affixes -save_lemmatizer -save_prefix_entry_searcher ..\..\dictionary.src\version-pro ..\..\dictionary.src\dictionary -file=..\..\dictionary.src\french-language-only.sol  ..\..\dictionary.src\french-lexicon ..\..\dictionary.src\french-thesaurus ..\..\dictionary.src\french-syntax ..\..\dictionary.src\dictionary-french ..\..\dictionary.src\common_dictionary_xml

Call post-compile.cmd
