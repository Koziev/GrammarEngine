// Генерация датасетов и обучение моделей для частеречной разметки.
// Репозиторий проекта: https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/DisambigRuleBuilder/POSTaggerDatasetBuilder
// Консольная утилита читает текстовый корпус (поддерживаются разные форматы) с ручной
// разметкой морфологических признаков и генерирует датасеты для обучения и валидации CRFSuite модели.
// Обученная модель используется Парсером (https://github.com/Koziev/GrammarEngine/tree/master/src/demo/ai/solarix/argon/ParseText/Parser).
//
// Пример запуска:
// -dict e:\MVoice\lem\bin-windows64\dictionary.xml -conllu_corpus "f:\Corpus\Universal Dependencies 1.4\ud-treebanks-v1.4\ud-treebanks-v1.4\UD_Russian-SynTagRus\ru_syntagrus-ud-train.conllu" -nsample 10000 -context_span 4 -suffix_len 3 -params LANGUAGE=ru,EMIT_POS_TAGS=false,EMIT_MORPH_TAGS=false,EMIT_POS_FOR_CONTEXT=false,EMIT_MORPH_FOR_CONTEXT=false,EMIT_FORM_TAGS=true,EMIT_FORMTAGS_FOR_CONTEXT=true,EMIT_SEMANTIC_TAGS=true,LEMMA_SEMATAGS=true -sematags f:\ModelTrainer\lemma_sematags.txt

using System;
using System.Collections.Generic;
using CorporaLib;

class POSTaggerDatasetBuilder
{
    public static string dictionary_path;

    public static List<ICorpusReader> corpora = new List<ICorpusReader>();
    public static string sematags_path = null;
    public static int NSAMPLE = 0; // Максимальное кол-во предложений, которые будут взяты из корпуса для получения тренировочного набора
    public static int MIN_SENT_LEN = 0; // Предлождения короче данного значения не будут браться для генерации тренировочного и тестового наборов
    public static int CONTEXT_SPAN = -1;
    public static int SUFFIX_LEN = -1;
    public static string WORD_FEATURES = "";
    public static string tmp_folder = "."; // папка для генерируемых временных файлов - логи, датасеты.

    static void Main(string[] args)
    {
        List<string> model_params = new List<string>();

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
                else if (args[i] == "-sematags")
                {
                    sematags_path = args[i + 1];
                    ++i;
                }
                else if (args[i] == "-nsample")
                {
                    NSAMPLE = int.Parse(args[i + 1]);
                    ++i;
                }
                else if (args[i] == "-minsentlen")
                {
                    MIN_SENT_LEN = int.Parse(args[i + 1]);
                    ++i;
                }
                else if (args[i] == "-suffix_len")
                {
                    SUFFIX_LEN = int.Parse(args[i + 1]);
                    ++i;
                }
                else if (args[i] == "-context_span")
                {
                    // полуразмер контекста - число слов вправо или влево от текущего слова.
                    CONTEXT_SPAN = int.Parse(args[i + 1]);
                    ++i;
                }
                else if (args[i] == "-word_features")
                {
                    WORD_FEATURES = args[i + 1];
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

        Build_Morphology_CRF(gren, model_params);

        return;
    }


    static void Build_Morphology_CRF(SolarixGrammarEngineNET.GrammarEngine2 gren, List<string> model_params)
    {
        Builder_CRF builder = new Builder_CRF(SUFFIX_LEN, CONTEXT_SPAN);

        builder.SetModelParams(model_params);

        builder.SetDictionary(gren);

        builder.SetTmpFolder(tmp_folder);

        if (!string.IsNullOrEmpty(sematags_path))
        {
            builder.LoadSemanticTags(sematags_path);
        }

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

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
        Console.WriteLine("Storing the model files...");
        builder.FinishTesting();

        return;
    }

}
