@echo off

IF DEFINED PROCESSOR_ARCHITEW6432 GOTO x64

if not exist ..\..\bin-windows md ..\..\bin-windows
if exist ..\..\bin-windows\alphabet.bin del ..\..\bin-windows\alphabet.bin
if exist ..\..\bin-windows\debug.bin del ..\..\bin-windows\debug.bin
if exist ..\..\bin-windows\diction.bin del ..\..\bin-windows\diction.bin
if exist ..\..\bin-windows\affixes.bin del ..\..\bin-windows\affixes.bin
if exist ..\..\bin-windows\seeker.bin del ..\..\bin-windows\seeker.bin
if exist ..\..\bin-windows\syntax.bin del ..\..\bin-windows\syntax.bin
if exist ..\..\bin-windows\thesaurus.bin del ..\..\bin-windows\thesaurus.bin
if exist ..\..\bin-windows\thesaurus.db del ..\..\bin-windows\thesaurus.db
if exist ..\..\bin-windows\lexicon.db del ..\..\bin-windows\lexicon.db
if exist ..\..\bin-windows\dictionary.xml del ..\..\bin-windows\dictionary.xml
if exist ..\..\bin-windows\prefix_entry_searcher.db del ..\..\bin-windows\prefix_entry_searcher.db
if exist ..\..\bin-windows\_sg_api.h del ..\..\bin-windows\_sg_api.h
if exist ..\..\bin-windows\_sg_api.cs del ..\..\bin-windows\_sg_api.cs
if exist ..\..\bin-windows\_sg_api.pas del ..\..\bin-windows\_sg_api.pas
if exist ..\..\bin-windows\_sg_api.py del ..\..\bin-windows\_sg_api.py
if exist ..\..\bin-windows\_sg_api.php del ..\..\bin-windows\_sg_api.php
if exist ..\..\bin-windows\SolarixEngineApi.pas del ..\..\bin-windows\SolarixEngineApi.pas
if exist ..\..\bin-windows\lemmatizer.db del ..\..\bin-windows\lemmatizer.db
if exist ..\..\bin-windows\NGRAMS del ..\..\bin-windows\NGRAMS

GOTO End

:x64

if not exist ..\..\bin-windows64 md ..\..\bin-windows64
if exist ..\..\bin-windows64\alphabet.bin del ..\..\bin-windows64\alphabet.bin
if exist ..\..\bin-windows64\debug.bin del ..\..\bin-windows64\debug.bin
if exist ..\..\bin-windows64\diction.bin del ..\..\bin-windows64\diction.bin
if exist ..\..\bin-windows64\affixes.bin del ..\..\bin-windows64\affixes.bin
if exist ..\..\bin-windows64\seeker.bin del ..\..\bin-windows64\seeker.bin
if exist ..\..\bin-windows64\syntax.bin del ..\..\bin-windows64\syntax.bin
if exist ..\..\bin-windows64\thesaurus.bin del ..\..\bin-windows64\thesaurus.bin
if exist ..\..\bin-windows64\thesaurus.db del ..\..\bin-windows64\thesaurus.db
if exist ..\..\bin-windows64\lexicon.db del ..\..\bin-windows64\lexicon.db
if exist ..\..\bin-windows64\prefix_entry_searcher.db del ..\..\bin-windows64\prefix_entry_searcher.db
if exist ..\..\bin-windows64\dictionary.xml del ..\..\bin-windows64\dictionary.xml
if exist ..\..\bin-windows64\_sg_api.h del ..\..\bin-windows64\_sg_api.h
if exist ..\..\bin-windows64\_sg_api.cs del ..\..\bin-windows64\_sg_api.cs
if exist ..\..\bin-windows64\_sg_api.pas del ..\..\bin-windows64\_sg_api.pas
if exist ..\..\bin-windows64\SolarixEngineApi.pas del ..\..\bin-windows64\SolarixEngineApi.pas
if exist ..\..\bin-windows64\lemmatizer.db del ..\..\bin-windows64\lemmatizer.db
if exist ..\..\bin-windows64\NGRAMS del ..\..\bin-windows64\NGRAMS

:End
