// Утилита для обучения модели лемматизации, работающей поверх POS Tagger.
// Обученная модель используется в проекте Парсера https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/ParseText/Parser.

using System;
using System.Collections.Generic;

using CorporaLib;

public class LemmatizerDatasetBuilder
{
    public static string dictionary_path;

    public static List<ICorpusReader> corpora = new List<ICorpusReader>();
    public static string sematags_path = null;
    public static int NSAMPLE = int.MaxValue; // Максимальное кол-во предложений, которые будут взяты из корпуса для получения тренировочного набора
    public static int MIN_SENT_LEN = 0; // Предлождения короче данного значения не будут браться для генерации тренировочного и тестового наборов
    public static string tmp_folder = "."; // папка для генерируемых временных файлов - логи, датасеты.

    static void Main(string[] args)
    {
        List<string> model_params = new List<string>();

        try
        {
            if (args.Length > 0)
            {
                for (int i = 0; i < args.Length; ++i)
                {
                    if (args[i] == "-dict")
                    {
                        // Путь к файлу с конфигурацией словарной базы.
                        dictionary_path = args[i + 1];
                        ++i;
                    }
                    else if (args[i] == "-tmp")
                    {
                        // Временный каталог для сохранения датасетов.
                        tmp_folder = args[i + 1];
                        ++i;
                    }
                    else if (args[i] == "-autocorpus")
                    {
                        // В датасет добавляем слова, которые имеют только один лемматизации.
                        corpora.Add(new AutoLemmaCorpusGenerator());
                    }
                    else if (args[i] == "-corpus")
                    {
                        // Путь к бинарному корпусу в формате Solarix.
                        string corpus_path = args[i + 1];
                        corpora.Add(new SolarixBinaryCorpusReader(corpus_path));
                        ++i;
                    }
                    else if (args[i] == "-ud_corpus")
                    {
                        // Путь к корпусу в формате Universal Dependencies
                        string corpus_path = args[i + 1];
                        corpora.Add(new UniversalDependenciesCorpusReader(corpus_path));
                        ++i;
                    }
                    else if (args[i] == "-dme_corpus")
                    {
                        // Путь к корпусу в формате Dialog MorphEval
                        string corpus_path = args[i + 1];
                        corpora.Add(new DialogMorphEvalCorpus(corpus_path));
                        ++i;
                    }
                    else if (args[i] == "-nsample")
                    {
                        if (!int.TryParse(args[i + 1], out NSAMPLE))
                        {
                            throw new ApplicationException("Integer argument expected for -nsample");
                        }
                        i++;
                    }
                    else if (args[i] == "-minsentlen")
                    {
                        MIN_SENT_LEN = int.Parse(args[i + 1]);
                        ++i;
                    }
                    else if (args[i] == "-params")
                    {
                        string[] px = args[i + 1].Split(",".ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
                        model_params.AddRange(px);
                        ++i;
                    }
                    else
                    {
                        throw new ApplicationException(string.Format("Unknown option [{0}] in command line", args[i]));
                    }
                }
            }

            Console.WriteLine("Loading dictionary from {0}...", dictionary_path);
            SolarixGrammarEngineNET.GrammarEngine2 gren;
            gren = new SolarixGrammarEngineNET.GrammarEngine2();
            gren.Load(dictionary_path, true);

            Build_LemmByPostags(gren, model_params);
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error: {0}", ex.Message);
        }

        return;
    }


    private static void Build_LemmByPostags(SolarixGrammarEngineNET.GrammarEngine2 gren, List<string> model_params)
    {
        Builder_LEMM_ByPOSTag builder = new Builder_LEMM_ByPOSTag();

        builder.ChangeModelParams(model_params);
        builder.SetDictionary(gren);
        builder.SetTmpFolder(tmp_folder);
        builder.Init();

        int counter = 0;
        int MAX_COUNT = NSAMPLE == 0 ? int.MaxValue : NSAMPLE;

        int TEST_SHARE = 10; // каждый такой пример идет на валидацию

        foreach (var corpus in corpora)
        {
            foreach (SentenceData sample in corpus.Read(gren))
            {
                counter++;
                if (counter >= MAX_COUNT) break;
                Console.WriteLine("{0}: {1}", counter, sample.GetSentenceStr());

                if ((counter % TEST_SHARE) == 0)
                {
                    builder.ProcessValidationSample(sample);
                }
                else
                {
                    builder.ProcessTrainingSample(sample);
                }
            }
        }

        builder.FinishLearning();
        builder.StartTesting();
        builder.PrintTestResults();
        return;
    }
}
