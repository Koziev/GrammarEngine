@echo off
rem (c) by Elijah Koziev www.solarix.ru
rem English dictionary (lexicon + thesaurus + syntax) version PRO
rem More info about dictionary compilation:
rem http://solarix.ru/for_developers/bootstrap/compile_dictionary.shtml

Call cleanup.cmd

..\..\exe64\compiler /j=2 -dir=..\..\dictionary.src -outdir=..\..\bin-windows64 -ldsize=1000000 -save_paradigmas -save_prefix_entry_searcher -save_lemmatizer -save_seeker -save_affixes ..\..\dictionary.src\version-pro ..\..\dictionary.src\dictionary -file=..\..\dictionary.src\english-language-only.sol ..\..\dictionary.src\shared-resources ..\..\dictionary.src\english-lexicon ..\..\dictionary.src\english-stat ..\..\dictionary.src\english-thesaurus  ..\..\dictionary.src\common-syntax ..\..\dictionary.src\english-syntax ..\..\dictionary.src\dictionary-english ..\..\dictionary.src\common_dictionary_xml

Call post-compile.cmd

:OnError