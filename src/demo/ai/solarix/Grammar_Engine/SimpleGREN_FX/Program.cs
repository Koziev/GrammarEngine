using System;
using System.Collections.Generic;
using System.Text;
using SolarixGrammarEngineNET;


class Program
{
 static int Main(string[] args)
 {
  // Закомментированы пути к словарной базе под Windows
  string dictionary_xml = IntPtr.Size==8 ? @"e:\MVoice\lem\bin-windows64\dictionary.xml" : @"e:\MVoice\lem\bin-windows\dictionary.xml";

  //string dictionary_xml = @"../../../../../bin-linux64/dictionary.xml";

  for( int i = 0; i < 2; ++i )
  {
   IntPtr hEngine = SolarixGrammarEngineNET.GrammarEngine.sol_CreateGrammarEngineW("");

   Console.WriteLine($"Loading {dictionary_xml}");
   int loading_ok = SolarixGrammarEngineNET.GrammarEngine.sol_LoadDictionaryW(hEngine, dictionary_xml);
   Console.WriteLine($"loading_ok={loading_ok}");
   if( loading_ok != 1 )
   {
    Console.WriteLine("Debug 1");   
    if( !System.IO.File.Exists(dictionary_xml) )
    {
     Console.WriteLine("Debug 2");   
     Console.WriteLine($"Отсутствует словарь {dictionary_xml}. Работа программы невозможна.");
     return 1;
    }
    else
    {
     Console.WriteLine("Debug 3");   
     string engine_error = "";
     if( hEngine != null )
     {
      Console.WriteLine("Debug 4");   
      engine_error = SolarixGrammarEngineNET.GrammarEngine.sol_GetErrorFX(hEngine);
      Console.WriteLine("Debug 5");   
     }

     Console.WriteLine($"При загрузке словаря {dictionary_xml} возникла внутренняя ошибка {engine_error}. Работа программы невозможна.");
     return 1;
    }
   }
   
   Console.WriteLine($"Словарь {dictionary_xml} успешно загружен");

   IntPtr hList = SolarixGrammarEngineNET.GrammarEngine.sol_ProjectMisspelledWord(hEngine, "КОЩКА", 0, 1);

   int nproj = SolarixGrammarEngineNET.GrammarEngine.sol_CountProjections(hList);

   for( int j = 0; j < nproj; j++ )
   {
    int ientry = SolarixGrammarEngineNET.GrammarEngine.sol_GetIEntry(hList, j);
    int iclass = SolarixGrammarEngineNET.GrammarEngine.sol_GetEntryClass(hEngine, ientry);
    string pos_name = SolarixGrammarEngineNET.GrammarEngine.sol_GetClassNameFX(hEngine, iclass);
    Console.WriteLine($"вариант распознавания {j} ientry={ientry} часть речи={pos_name}");
   }

   SolarixGrammarEngineNET.GrammarEngine.sol_DeleteProjections(hList);

   // ...

   SolarixGrammarEngineNET.GrammarEngine.sol_DeleteGrammarEngine(hEngine);
  }

  return 0;
 }
}
