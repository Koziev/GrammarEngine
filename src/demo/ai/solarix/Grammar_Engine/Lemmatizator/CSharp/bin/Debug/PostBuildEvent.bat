@echo off
copy e:\MVoice\lem\lib\lemmatizator.dll e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lemmatizator\CSharp\bin\Debug\
copy e:\MVoice\lem\lib\lemmatizator_fx.dll e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lemmatizator\CSharp\bin\Debug\

if errorlevel 1 goto CSharpReportError
goto CSharpEnd
:CSharpReportError
echo Project error: A tool returned an error code from the build event
exit 1
:CSharpEnd