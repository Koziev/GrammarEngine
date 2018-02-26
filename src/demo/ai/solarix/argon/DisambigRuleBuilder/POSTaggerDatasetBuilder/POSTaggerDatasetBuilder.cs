using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



class POSTaggerDatasetBuilder
{
/*
    static void MainOld(string[] args)
    {
        string syntagrus_path = @"f:\Corpus\Universal Dependencies 1.4\ud-treebanks-v1.4\ud-treebanks-v1.4\UD_Russian-SynTagRus\ru_syntagrus-ud-train.conllu";
        string dict_path = @"e:\MVoice\lem\bin-windows64\dictionary.xml";
        string solarix_treebank = @"f:\Corpus\CompiledCorpus\ru\x64\corpus_*.bin";

        int LanguageID = SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE;
        int Constraints = 60000 | (30 << 22); // 1 минута и 30 альтернатив

        Console.WriteLine("Loading dictionary from {0}...", dict_path);
        SolarixGrammarEngineNET.GrammarEngine2 gren;
        gren = new SolarixGrammarEngineNET.GrammarEngine2();
        gren.Load(dict_path, true);

        int nb_sents = 0;
        int nb_words = 0;


        // Тестируем чтение ConllU корпуса.
        ConlluCorpusReader corpus = new ConlluCorpusReader(syntagrus_path, gren);
        foreach (SentenceData sent in corpus.Read())
        {
            nb_sents++;
            Console.WriteLine("{0}: {1}", nb_sents, sent.GetSentenceStr());

            foreach (WordData word in sent.GetWords())
            {
                nb_words++;
                // ...
            }
        }



        // Тестируем чтение из бинарного treebank Solarix.
        SolarixBinaryCorpusReader corpus2 = new SolarixBinaryCorpusReader(solarix_treebank, gren);
        foreach (SentenceData sent in corpus2.Read())
        {
            nb_sents++;
            Console.WriteLine("{0}: {1}", nb_sents, sent.GetSentenceStr());

            foreach (WordData word in sent.GetWords())
            {
                nb_words++;
                // ...
            }
        }



        Console.WriteLine("{0} sentences, {1} words processed.", nb_sents, nb_words);

        return;
    }
*/


    public static string dictionary_path;

    public static List<ICorpusReader> corpora = new List<ICorpusReader>();
    public static string sematags_path = null;
    public static int NSAMPLE = 0; // Максимальное кол-во предложений, которые будут взяты из корпуса для получения тренировочного набора
    public static int MIN_SENT_LEN = 0; // Предлождения короче данного значения не будут браться для генерации тренировочного и тестового наборов
    public static int CONTEXT_SPAN = -1;
    public static int SUFFIX_LEN = -1;
    public static string WORD_FEATURES = "";

    static void Main(string[] args)
    {
        List<string> model_params = new List<string>();

        if (args.Length > 0)
        {
            for (int i = 0; i < args.Length; ++i)
            {
                if (args[i] == "-dict")
                {
                    dictionary_path = args[i + 1];
                    ++i;
                }
                else if (args[i] == "-corpus")
                {
                    string corpus_path = args[i + 1];
                    corpora.Add(new SolarixBinaryCorpusReader(corpus_path));
                    ++i;
                }
                else if (args[i] == "-conllu_corpus")
                {
                    string corpus_path = args[i + 1];
                    corpora.Add(new ConlluCorpusReader(corpus_path));
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

        if (!string.IsNullOrEmpty(sematags_path))
        {
            builder.LoadSemanticTags(sematags_path);
        }

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        int TEST_SHARE = 10; // каждый такой пример идет на валидацию

        foreach( var corpus in corpora )
        {
            foreach (SentenceData sample in corpus.Read(gren))
            {
                counter++;
                if (counter >= MAX_COUNT) break;
                Console.WriteLine("{0}: {1}", counter, sample.GetSentenceStr());

                if ((counter % TEST_SHARE) == 0)
                    builder.ProcessValidationSample(sample);
                else
                    builder.ProcessTrainingSample(sample);
            }
        }

        builder.FinishLearning();
        Console.WriteLine("Storing the model files...");
        builder.FinishTesting();

        return;
    }

}
