using System;
using System.Collections.Generic;
using System.Text;
using SolarixGrammarEngineNET;


class Program
{
    public static bool IsLinux
    {
        get
        {
#if NETCOREAPP1_0 || NETCOREAPP1_1 || NETCOREAPP2_0
            // https://github.com/dotnet/corefx/blob/master/src/System.Runtime.InteropServices.RuntimeInformation/ref/System.Runtime.InteropServices.RuntimeInformation.cs
            return System.Runtime.InteropServices.RuntimeInformation.IsOSPlatform(System.Runtime.InteropServices.OSPlatform.Linux);
#else
            int p = (int)Environment.OSVersion.Platform;
            return (p == 4) || (p == 6) || (p == 128);
#endif
        }
    }


    static int Main(string[] args)
    {
        string dictionary_xml = null;
        if (IsLinux)
        {
            dictionary_xml = @"../../../../../bin-linux64/dictionary.xml";
        }
        else
        {
            // пути к словарной базе под Windows
            dictionary_xml = IntPtr.Size == 8 ? @"e:\MVoice\lem\bin-windows64\dictionary.xml" : @"e:\MVoice\lem\bin-windows\dictionary.xml";
        }


        for (int i = 0; i < 2; ++i)
        {
            IntPtr hEngine = SolarixGrammarEngineNET.GrammarEngine.sol_CreateGrammarEngineW("");

            Console.WriteLine($"Loading {dictionary_xml}");
            int loading_ok = SolarixGrammarEngineNET.GrammarEngine.sol_LoadDictionaryFX(hEngine, dictionary_xml);
            if (loading_ok != 1)
            {
                if (!System.IO.File.Exists(dictionary_xml))
                {
                    Console.WriteLine($"Отсутствует словарь {dictionary_xml}. Работа программы невозможна.");
                    return 1;
                }
                else
                {
                    string engine_error = "";
                    if (hEngine != null)
                    {
                        engine_error = SolarixGrammarEngineNET.GrammarEngine.sol_GetErrorFX(hEngine);
                    }

                    Console.WriteLine($"При загрузке словаря {dictionary_xml} возникла внутренняя ошибка {engine_error}. Работа программы невозможна.");
                    return 1;
                }
            }

            Console.WriteLine($"Словарь {dictionary_xml} успешно загружен");

            IntPtr hList = SolarixGrammarEngineNET.GrammarEngine.sol_ProjectMisspelledWord(hEngine, "КОЩКА", 0, 1);

            int nproj = SolarixGrammarEngineNET.GrammarEngine.sol_CountProjections(hList);

            for (int j = 0; j < nproj; j++)
            {
                int ientry = SolarixGrammarEngineNET.GrammarEngine.sol_GetIEntry(hList, j);
                int iclass = SolarixGrammarEngineNET.GrammarEngine.sol_GetEntryClass(hEngine, ientry);
                string entry_name = SolarixGrammarEngineNET.GrammarEngine.sol_GetEntryNameFX(hEngine, ientry);
                string pos_name = SolarixGrammarEngineNET.GrammarEngine.sol_GetClassNameFX(hEngine, iclass);
                Console.WriteLine($"вариант распознавания {j} ientry={ientry} name={entry_name} часть речи={pos_name}");
            }

            SolarixGrammarEngineNET.GrammarEngine.sol_DeleteProjections(hList);

            // ...

            SolarixGrammarEngineNET.GrammarEngine.sol_DeleteGrammarEngine(hEngine);
        }

        return 0;
    }
}
