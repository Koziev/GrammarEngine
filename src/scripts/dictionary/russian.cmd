@echo off

rem (c) by Elijah Koziev www.solarix.ru
rem The script builds the russian dictionary (lexicon + thesaurus + syntax analyzer), version 'PRO'
rem More info about dictionary compilation:
rem http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

Call cleanup

..\..\exe64\compiler -j=2 -optimize -dir=..\..\dictionary.src -outdir=..\..\bin-windows64 -ldsize=3000000 -save_paradigmas -save_prefix_entry_searcher -save_seeker -save_affixes -save_lemmatizer ..\..\dictionary.src\version-pro ..\..\dictionary.src\dictionary -file=..\..\dictionary.src\russian-language-only.sol ..\..\dictionary.src\shared-resources ..\..\dictionary.src\russian-lexicon ..\..\dictionary.src\russian-stat ..\..\dictionary.src\common-syntax  ..\..\dictionary.src\russian-syntax ..\..\dictionary.src\russian-thesaurus ..\..\dictionary.src\dictionary-russian ..\..\dictionary.src\common_dictionary_xml
 

Call post-compile.cmd
