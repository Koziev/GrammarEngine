@echo off

if not exist ..\..\tmp md ..\..\tmp

IF DEFINED PROCESSOR_ARCHITEW6432 GOTO x64

move /Y ..\..\bin-windows\journal ..\..\tmp\journal
GOTO End

:x64

move /Y ..\..\bin-windows64\journal ..\..\tmp\journal

:End
 

