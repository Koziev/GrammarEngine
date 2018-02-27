using System;
using System.Collections.Generic;
using System.Text;
using System.Data.Sql;
using System.Data.SqlClient;
using System.Linq;


class Program
{
    public static string dictionary_path = @"e:\MVoice\lem\bin-windows64\dictionary.xml";

    public static string MODEL_NAME = "crf_pos_tagger";
    public static string corpus_path;
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
                    corpus_path = args[i + 1];
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
                else if (args[i] == "-model")
                {
                    MODEL_NAME = args[i + 1];
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

        //ParseRusCorpora4Lemm();

        // ####################
        // СТАТИСТИКА КОРПУСА
        // ####################
        //Facts();

        // ################
        // ЛЕММАТИЗАТОР
        // ################

        //BuildLemmatizationModel();
        //Build_Lemmatizer_HMM_Suffix();
        //BuildLemmatization_BayesNaive();
        //BuildLemmatization_MaxEnt();
        //BuildLemmatization_MEMM();
        //BuildLemmatization_CRF();
        //BuildLemmatization_MaxEnt_CPP_Trainer();


        if (MODEL_NAME == "tokenizer")
            Build_Tokenizer(model_params);
        else if (MODEL_NAME == "crf_pos_tagger")
            Build_Morphology_CRF(model_params);
        else if (MODEL_NAME == "maxent_pos_tagger")
            Build_Morphology_MaxEnt(model_params);
        else if (MODEL_NAME == "svm_pos_tagger")
            Build_SVM();
        else if (MODEL_NAME == "desr_parser")
            Build_DependencySyntax_DESR(model_params);
        else if (MODEL_NAME == "crf_parser")
            Build_DependencySyntax_CRF(model_params);
        else if (MODEL_NAME == "stat")
            Stat(model_params);
        else if (MODEL_NAME == "lemm_bypostaggs")
            Build_LemmByPostags(model_params);
        else if (MODEL_NAME == "rnnsharp_pos_tagger")
        {
            Build_Morphology_RNNSharp(model_params);
        }
        else if (MODEL_NAME == "wordshingles_pos_tagger")
        {
            Build_WordShingles_POSTagger(model_params);
        }
        else if (MODEL_NAME == "syntax_neuro")
        {
            Build_Syntax_Neuro();
        }
        else
        {
            Console.WriteLine("Unknown model {0}", MODEL_NAME);
            return;
        }

        //BuildBayesModel();
        //Build_HMM();
        //Build_HMM_Suffix();

        //BuildBayesModelSuffix();
        //BuildBayesModel_2Factors();


        //BuildRuleInferenceModel();

        // ################
        // СИНТАКСИС
        // ################


        //BuildBottomUpSyntax();

        //Build_LongEdgesSyntax();
        //Build_Chunker_CRF();
        //Build_Syntax_Neuro();
        //AdjacentMatrix();

        return;
    }


    static void BuildBottomUpSyntax()
    {
        EdgeStat builder = new EdgeStat();

        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);

        bool separate_test = true;

        if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            int counter = 0;
            int MAX_COUNT = NSAMPLE;

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

                while (true)
                {
                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("0.{1}: {0}", sample.sample, counter);

                        if (separate_test)
                        {
                            if ((counter % 10) == 0)
                                continue;
                        }

                        builder.ProcessSample(sample);

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
            }

            builder.AfterLearning();

            // --------------------
            // Теперь проверка
            // --------------------

            /*
               // ----~~~~~----
               //Console.WriteLine( "Enter sample: " );
               string str = "отец сослался на его друга";//Console.ReadLine().Trim();
               ParsingContext res = builder.ParseAndReturnBest( str );
               Console.WriteLine( "Result: {0}", res.PrintStructure() );
               // ----~~~~~----
            /**/

            counter = 0;
            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", path1));

                while (true)
                {
                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("0.{1}: {0}", sample.sample, counter);

                        if (separate_test)
                        {
                            if ((counter % 10) != 0)
                                continue;
                        }

                        builder.Check(sample);

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }
            }
        }


        // builder.ListStat( "edges.txt" );

        builder.PrintStat();


        return;
    }



    private static void ParseRusCorpora4Lemm()
    {
        SolarixGrammarEngineNET.GrammarEngine2 gren = new SolarixGrammarEngineNET.GrammarEngine2();
        gren.Load(@"e:\MVoice\lem\bin-windows\dictionary.xml", false);
        //gren.SetLanguage( SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE );
        ParseRusCorpora4Lemm(gren, 1000);
        return;
    }


    private static void ParseRusCorpora4Lemm(SolarixGrammarEngineNET.GrammarEngine2 gren, int n_sample)
    {
        HashSet<string> pronouns = new HashSet<string>("я нему ней ним мы ты вы он она они оно меня нас тебя вас его ее их мной мною нами тобой тобою вами им ей ею ими мне нам тебе вам ему мне нас тебе вас нем ней них нее него них".Split(' '));

        HashSet<string> pronouns2 = new HashSet<string>(
      @"что чего чем чему чем кто кого кем кому ком что-то чего-то чем-то чему-то кто-то кого-то кем-то кому-то ком-то
что-либо чего-либо чем-либо чему-либо чем-либо кто-либо кого-либо кем-либо кому-либо ком-либо
что-нибудь чего-нибудь чем-нибудь чему-нибудь чем-нибудь
кто-нибудь кого-нибудь кем-нибудь кому-нибудь ком-нибудь".Split(" \r\n".ToCharArray(), StringSplitOptions.RemoveEmptyEntries));


        HashSet<string> which = new HashSet<string>(
      @"который которая которое которые которого которой которых которым которой которыми
которому которой которым котором которой которых".Split(" \r\n".ToCharArray(), StringSplitOptions.RemoveEmptyEntries));

        // ДЕЕПРИЧАСТИЕ <t id="d5s327_8" word="делая" lemma="ДЕЛАТЬ" pos="v" morph="v ipf grd npst" />
        System.Text.RegularExpressions.Regex rx = new System.Text.RegularExpressions.Regex("\\<t id=\"(.+)\" word=\"(.+)\" lemma=\"(.+)\" pos=\"(.+)\" morph=\"(.+)\" \\/\\>");

        using (System.IO.StreamWriter wr = new System.IO.StreamWriter("ruscorpora.txt"))
        {
            using (System.IO.StreamWriter wr2 = new System.IO.StreamWriter("ruscorpora_plain.txt"))
            {

                int line_count = 0;
                using (System.IO.StreamReader rdr = new System.IO.StreamReader(@"H:\Ruscorpora\syntagrus.bin.txt"))
                {
                    while (!rdr.EndOfStream)
                    {
                        string line = rdr.ReadLine();
                        if (line == null)
                            break;

                        line = line.Trim();

                        if (line.StartsWith("<s id=\""))
                        {
                            if (line_count > n_sample)
                                break;

                            line_count++;
                            Console.Write("RUSCORPORA.{0}-->", line_count);

                            List<string> words = new List<string>();
                            List<string> pos = new List<string>();
                            List<string> lemmas = new List<string>();

                            // найдем тег <terminals>
                            while (!rdr.EndOfStream)
                            {
                                line = rdr.ReadLine();
                                if (line == null)
                                    break;

                                line = line.Trim();

                                if (line.StartsWith("<terminals"))
                                    break;
                            }

                            words.Clear();
                            pos.Clear();
                            lemmas.Clear();

                            // Читаем токены жо встречи с </terminals>
                            while (!rdr.EndOfStream)
                            {
                                line = rdr.ReadLine();
                                if (line == null)
                                    break;

                                line = line.Trim();

                                if (line.StartsWith("</terminals>"))
                                    break;

                                // NUM_WORD <t id="d1s1_1" word="9" lemma="9" pos="num" morph="num" />
                                // ДЕЕПРИЧАСТИЕ <t id="d5s327_8" word="делая" lemma="ДЕЛАТЬ" pos="v" morph="v ipf grd npst" />
                                // ПРИЧАСТИЕ <t id="d3s289_15" word="переносивший" lemma="ПЕРЕНОСИТЬ" pos="v" morph="v ipf pcp pst sg m nom" />
                                // ГЛАГОЛ <t id="d5s327_1" word="Работал" lemma="РАБОТАТЬ" pos="v" morph="v ipf indic pst sg m" />
                                // МЕСТОИМЕНИЕ <t id="d5s327_2" word="он" lemma="ОН" pos="s" morph="s sg m nom anim" />

                                string word = null;
                                string raw_pos = null;
                                string morph = null;
                                string lemma = null;

                                System.Text.RegularExpressions.Match mx = rx.Match(line.Trim());
                                if (mx.Success)
                                {
                                    word = mx.Groups[2].Value;
                                    lemma = mx.Groups[3].Value;
                                    raw_pos = mx.Groups[4].Value;
                                    morph = mx.Groups[5].Value;
                                }
                                else
                                {
                                    word = mx.Groups[2].Value;
                                    lemma = mx.Groups[3].Value;
                                    raw_pos = "<UNK>";
                                    morph = string.Empty;
                                }


                                // &quot; --> "
                                word = word.Replace("&quot;", "\"");

                                if (lemma == "ДОЛЛАР-ЗНАК")
                                    lemma = "$";


                                string[] attr = morph.Split(' ');

                                // ... TODO приведение к своим тегам
                                if (raw_pos == "_")
                                {
                                    raw_pos = "ПУНКТУАТОР";
                                    lemma = word;
                                }
                                else if (raw_pos == "num")
                                {
                                    raw_pos = "NUM_WORD";
                                }
                                else if (raw_pos == "v")
                                {
                                    // атрибуты глаголов <t id="d1s1_6" word="производят" lemma="ПРОИЗВОДИТЬ" pos="v" morph="v ipf indic npst pl 3rd" />
                                    // ПРИЧАСТИЕ <t id="d3s289_15" word="переносивший" lemma="ПЕРЕНОСИТЬ" pos="v" morph="v ipf pcp pst sg m nom" />
                                    // ДЕЕПРИЧАСТИЕ <t id="d5s327_8" word="делая" lemma="ДЕЛАТЬ" pos="v" morph="v ipf grd npst" />
                                    // ИНФИНИТИВ <t id="d3s68_10" word="сделать" lemma="ДЕЛАТЬ" pos="v" morph="v pf inf" />
                                    // БЕЗЛИЧНЫЙ ГЛАГОЛ <t id="d26s243_3" word="хочется" lemma="ХОТЕТЬСЯ" pos="v" morph="v ipf indic npst sg 3rd" />

                                    if (attr.Contains("grd"))
                                    {
                                        raw_pos = "ДЕЕПРИЧАСТИЕ";
                                        lemma = word;
                                    }
                                    else if (attr.Contains("inf"))
                                    {
                                        raw_pos = "ИНФИНИТИВ";

                                        // перейдем к лемме для совершенного инфинитива.
                                        // для возвратных глаголов на -СЯ также берем свой вариант леммы, так как ruscorpora
                                        // дает лемму с отбрасыванием -СЯ
                                        // <t id="d2s5_6" word="снизить" lemma="СНИЖАТЬ" pos="v" morph="v pf inf" />
                                        using (SolarixGrammarEngineNET.WordProjections projs = gren.FindWordForm(word))
                                        {
                                            for (int i = 0; i < projs.Count; ++i)
                                            {
                                                int id_entry = projs.GetEntryKey(i);
                                                int id_class = gren.GetEntryClass(id_entry);
                                                if (id_class == SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru)
                                                {
                                                    lemma = gren.GetEntryName(id_entry);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    else if (attr.Contains("pcp"))
                                    {
                                        raw_pos = "ПРИЛАГАТЕЛЬНОЕ";
                                        lemma = "<?-todo-?>";

                                        using (SolarixGrammarEngineNET.WordProjections projs = gren.FindWordForm(word))
                                        {
                                            for (int i = 0; i < projs.Count; ++i)
                                            {
                                                int id_entry = projs.GetEntryKey(i);
                                                int id_class = gren.GetEntryClass(id_entry);
                                                if (id_class == SolarixGrammarEngineNET.GrammarEngineAPI.ADJ_ru)
                                                {
                                                    lemma = gren.GetEntryName(id_entry);
                                                    break;
                                                }
                                            }
                                        }

                                    }
                                    //else if( attr.Contains( "npst" ) )
                                    //{
                                    //raw_pos = "БЕЗЛИЧ_ГЛАГОЛ";
                                    //}
                                    else if (attr.Contains("pf"))
                                    {
                                        // <t id="d1s7_12" word="унаследовала" lemma="НАСЛЕДОВАТЬ" pos="v" morph="v pf indic pst sg f" />
                                        // Для совершенных глаголов RUSCORPORA дает лемму несовершенного вида. Нам нужна совершенная лемма.
                                        using (SolarixGrammarEngineNET.WordProjections projs = gren.FindWordForm(word))
                                        {
                                            for (int i = 0; i < projs.Count; ++i)
                                            {
                                                int id_entry = projs.GetEntryKey(i);
                                                int id_class = gren.GetEntryClass(id_entry);
                                                if (id_class == SolarixGrammarEngineNET.GrammarEngineAPI.VERB_ru)
                                                {
                                                    lemma = gren.GetEntryName(id_entry);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    else
                                        raw_pos = "ГЛАГОЛ";
                                }
                                else if (raw_pos == "s")
                                {
                                    // атрибуты сущ: s sg m gen inanim

                                    string u = word.ToLower().Replace("ё", "е");
                                    if (pronouns.Contains(u))
                                    {
                                        raw_pos = "МЕСТОИМЕНИЕ";
                                        lemma = "Я";
                                    }
                                    else if (pronouns2.Contains(u))
                                        raw_pos = "МЕСТИМ_СУЩ";
                                    else if (which.Contains(u))
                                    {
                                        raw_pos = "ПРИЛАГАТЕЛЬНОЕ";
                                        lemma = "КОТОРЫЙ";
                                    }
                                    else
                                        raw_pos = "СУЩЕСТВИТЕЛЬНОЕ";
                                }
                                else if (raw_pos == "pr")
                                {
                                    raw_pos = "ПРЕДЛОГ";
                                }
                                else if (raw_pos == "conj")
                                {
                                    raw_pos = "СОЮЗ";
                                }
                                else if (raw_pos == "part")
                                {
                                    raw_pos = "ЧАСТИЦА";
                                }
                                else if (raw_pos == "a")
                                {
                                    raw_pos = "ПРИЛАГАТЕЛЬНОЕ";

                                    if (lemma == "ДОЛЖЕН")
                                        lemma = "ДОЛЖНЫЙ";
                                    else
                                    {
                                        // превосходные степени надо привести к положительной форме, в RUSCORPORA они видимо все идут как отдельные прилагательные типа ЛУЧШИЙ.

                                        using (SolarixGrammarEngineNET.WordProjections projs = gren.FindWordForm(word))
                                        {
                                            for (int i = 0; i < projs.Count; ++i)
                                            {
                                                if (projs.GetCoordState(i, SolarixGrammarEngineNET.GrammarEngineAPI.COMPAR_FORM_ru) == SolarixGrammarEngineNET.GrammarEngineAPI.SUPERLATIVE_FORM_ru)
                                                {
                                                    int id_entry = projs.GetEntryKey(i);
                                                    int id_class = gren.GetEntryClass(id_entry);
                                                    if (id_class == SolarixGrammarEngineNET.GrammarEngineAPI.ADJ_ru)
                                                    {
                                                        lemma = gren.GetEntryName(id_entry);
                                                        break;
                                                    }
                                                }
                                            }
                                        }



                                    }
                                }
                                else if (raw_pos == "adv")
                                {
                                    raw_pos = "НАРЕЧИЕ";
                                }



                                words.Add(word);
                                pos.Add(raw_pos);
                                lemmas.Add(lemma);
                            }

                            System.Text.StringBuilder b = new StringBuilder();

                            for (int i = 0; i < words.Count; ++i)
                            {
                                if (i > 0)
                                    b.AppendFormat(" | {0}", words[i]);
                                else
                                    b.AppendFormat("{0}", words[i]);
                            }

                            wr.WriteLine("{0}", b.ToString());

                            for (int i = 0; i < words.Count; ++i)
                            {
                                // wr.WriteLine( "{0}\t{1}\t{2}", words[i], pos[i], lemmas[i] );
                                wr.WriteLine("{0}\t{1}", words[i], lemmas[i]);
                            }

                            wr.WriteLine("");
                            wr.Flush();

                            //Console.WriteLine( "{0}", b.ToString() );
                            wr2.WriteLine("{0}", b.ToString().Replace(" | ", " "));
                        }
                    }
                }
            }
        }

        return;
    }



    // ---------------------------------------------- МОДЕЛЬ НА ОСНОВЕ CRF -------------------------------------------------

    static void Build_Morphology_MaxEnt(List<string> model_params)
    {
        Build_CRF(false, true, false, false, model_params);
    }

    static void Build_Morphology_CRF(List<string> model_params)
    {
        Build_CRF(true, true, false, false, model_params);
    }

    static void Build_DependencySyntax_CRF(List<string> model_params)
    {
        Build_CRF(true, false, true, false, model_params);
    }


    static void Build_LongEdgesSyntax(List<string> model_params)
    {
        Build_CRF(false, false, true, true, model_params);
    }

    private static void Build_CRF(bool crf, bool morphology, bool syntax, bool long_edges, List<string> model_params)
    {
        Builder_CRF builder = new Builder_CRF();

        if (morphology)
        {
            if (crf)
                builder.Use_CRF();
            else
                builder.UseMaxEnt();

            builder.SetTarget_Morphology();
        }
        else if (syntax)
        {
            if (long_edges)
            {
                builder.UseMaxEnt();
                builder.SetTarget_LongEdges();
            }
            else
            {
                builder.Use_CRF();
                builder.SetTarget_Syntax();
            }
        }


        builder.ChangeModelParams(model_params);

        builder.LoadDictionary(dictionary_path);

        if (!string.IsNullOrEmpty(sematags_path))
            builder.LoadSemanticTags(sematags_path);


        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        bool separate_test = true; // каждый n-й пример - тест
        int TEST_SHARE = 10; // каждый такой пример в тест


        Console.WriteLine("Processing data in corpus {0}...", corpus_path);

        if (System.IO.Path.GetExtension(corpus_path) == ".xml")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);

            foreach (string sample_str in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                Console.WriteLine("{2} 0.{1}: {0}", sample_str, counter, builder.ModelName());

                using (SampleData sample = new SampleData())
                {
                    sample.sample = sample_str;

                    if (separate_test)
                    {
                        if ((counter % TEST_SHARE) == 0)
                            builder.Check(sample);
                        else
                            builder.ProcessSample(sample);
                    }
                    else
                    {
                        builder.ProcessSample(sample);
                        builder.Check(sample);
                    }
                }
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            Console.WriteLine("There are {0} binary corpus segments", bin_corpora.Length);

            System.IO.StreamWriter wrt_log = new System.IO.StreamWriter("corpus-loading.txt");

            int total_train_count = 0, total_test_count = 0;

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                wrt_log.WriteLine("Reading corpus {0}...", path1);
                int corpus_count = 0;
                int corpus_train_count = 0, corpus_test_count = 0;


                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

                while (true)
                {
                    corpus_count++;

                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("{2} 0.{1}: {0}", sample.sample, counter, builder.ModelName());

                        if (separate_test)
                        {
                            if ((counter % TEST_SHARE) == 0)
                            {
                                builder.Check(sample);
                                corpus_test_count++;
                            }
                            else
                            {
                                builder.ProcessSample(sample);
                                corpus_train_count++;
                            }
                        }
                        else
                        {
                            builder.ProcessSample(sample);
                            builder.Check(sample);
                            corpus_train_count++;
                            corpus_test_count++;
                        }

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                wrt_log.WriteLine("Total number of samples in [{0}]={1}, train_count={2}, test_count={3}\n\n", path1, corpus_count, corpus_train_count, corpus_test_count);
                wrt_log.Flush();

                total_train_count += corpus_train_count;
                total_test_count += corpus_test_count;
            }

            wrt_log.WriteLine("\ntotal_train_count={0}, total_test_count={1}", total_train_count, total_test_count);

            wrt_log.Flush();
            wrt_log.Close();
        }


        builder.FinishLearning();
        Console.WriteLine("Storing the model files...");
        builder.StoreModel();

        builder.FinishTesting();

        return;
    }



    // ***************************************************
    // Вероятностная модель морфологии для ЛЕММАТИЗАТОРА
    // ***************************************************
    private static void BuildLemmatizationModel()
    {
        Builder_LEMM builder = new Builder_LEMM();
        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);

        bool OddEven = false;
        int TrainShare = 6;
        int TestShare = 4;

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        List<int> trained_samples = new List<int>();

        if (System.IO.Path.GetExtension(corpus_path) == ".xml")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);

            foreach (string sample in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;
                if (OddEven)
                {
                    if (counter % (TrainShare + TestShare) >= TrainShare)
                        continue;
                }

                trained_samples.Add(counter);
                Console.WriteLine("0.{1}: {0}", sample, counter);

                SampleData data = new SampleData();
                data.sample = sample;
                builder.ProcessSample(data);
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));


                while (true)
                {
                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("0.{1}: {0}", sample.sample, counter);

                        builder.ProcessSample(sample);

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
            }
        }

        builder.FinishLearning();

        counter = 0;


        // ------ ПРОВЕРКА МОДЕЛИ --------

        if (System.IO.Path.GetExtension(corpus_path) == ".txt")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);

            foreach (string sample in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                if (OddEven)
                {
                    if (trained_samples.Contains(counter))
                        continue;
                }

                Console.WriteLine("1.{1}: {0}", sample, counter);

                SampleData data = new SampleData();
                data.sample = sample;
                builder.Check(data);
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));


                while (true)
                {
                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("0.{1}: {0}", sample.sample, counter);

                        builder.Check(sample);

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
            }
        }





        /*
          // --------------------------------
          // Верификация по внешнему корпусу.
          ParseRusCorpora4Lemm( builder.gren, MAX_COUNT );
          counter = 0;
          samples.Rewind();

          using( System.IO.StreamReader rdr_corpus = new System.IO.StreamReader( "ruscorpora.txt" ) )
          {
           while( !rdr_corpus.EndOfStream )
           {
            string line = rdr_corpus.ReadLine();
            if( line == null )
             break;

            if( counter >= MAX_COUNT ) break;

            string sample = line.Trim().Replace( " | ", " " );

            // Читаем строки с парами СЛОВО-ЛЕММА
            List<string> words = new List<string>();
            List<string> lemmas = new List<string>();
            while( !rdr_corpus.EndOfStream )
            {
             line = rdr_corpus.ReadLine();
             if( string.IsNullOrEmpty( line ) )
              break;

             string[] toks = line.Split( '\t' );
             words.Add( toks[0] );
             lemmas.Add( toks[1] );
            }

            // Можем проверять.
            Console.WriteLine( "2.{1}: {0}", sample, counter++ );
            builder.ExternalCheck( sample, lemmas );
           }
          }
          // --------------------------------
        */

        builder.PrintTestResults();

        builder.StoreModel();

        /*
          using( System.IO.StreamWriter model_file = new System.IO.StreamWriter( "lemm_model.sql", false, new UTF8Encoding( true ) ) )
          {
           builder.StoreModel_SQL( model_file );
           model_file.Close();
          }
         */

        return;
    }


    private static void BuildLemmatization_BayesNaive()
    {
        Builder_LEMM_Bayes builder = new Builder_LEMM_Bayes();
        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(corpus_path);

        int counter = 0;
        int MAX_COUNT = 100000;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;
            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();

        counter = 0;
        samples.Rewind();

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;
            Console.WriteLine("1.{1}: {0}", sample, counter);
            builder.Check(sample);
        }

        builder.PrintTestResults();

        builder.StoreModel();

        return;
    }





    private static void BuildLemmatization_MaxEnt()
    {
        Builder_LEMM_MaxEnt builder = new Builder_LEMM_MaxEnt();
        builder.LoadDictionary(dictionary_path);

        string lemm_path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(dictionary_path), "lemmatizer.db");
        builder.LoadLemmatizer(lemm_path);

        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(corpus_path);

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        List<int> trained_samples = new List<int>();

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;
            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();

        counter = 0;
        samples.Rewind();

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;
            Console.WriteLine("1.{1}: {0}", sample, counter);
            builder.Check(sample);
        }

        builder.PrintTestResults();

        builder.StoreModel();

        return;
    }







    private static void BuildLemmatization_MEMM()
    {
        Builder_LEMM_MEMM builder = new Builder_LEMM_MEMM();
        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(corpus_path);
        //  SampleSource samples = new PlainSamples( @"e:\1\dummy_corpus.txt" );

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        List<int> trained_samples = new List<int>();

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;
            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();

        counter = 0;
        samples.Rewind();

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;
            Console.WriteLine("1.{1}: {0}", sample, counter);
            builder.Check(sample);
        }

        builder.PrintTestResults();

        builder.StoreModel();

        return;
    }



    private static void BuildLemmatization_MaxEnt_CPP_Trainer()
    {
        Trainer_LEMM_MEMM builder = new Trainer_LEMM_MEMM();
        builder.LoadDictionary(dictionary_path);

        string lemm_path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(dictionary_path), "lemmatizer.db");
        builder.LoadLemmatizer(lemm_path);

        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(corpus_path);

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        List<int> trained_samples = new List<int>();

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;
            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();
        builder.FinishTesting();
        builder.PrintTestResults();

        return;
    }





    private static void BuildLemmatization_CRF()
    {
        Builder_LEMM_CRF builder = new Builder_LEMM_CRF();

        builder.LoadDictionary(dictionary_path);

        string lemm_path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(dictionary_path), "lemmatizer.db");
        builder.LoadLemmatizer(lemm_path);

        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(corpus_path);

        int counter = 0;
        int MAX_COUNT = 1000;//NSAMPLE;

        List<int> trained_samples = new List<int>();

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;
            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();
        builder.FinishTesting();
        builder.PrintTestResults();

        return;
    }



    private static void BuildRuleInferenceModel()
    {
        Builder_RuleInference builder = new Builder_RuleInference();
        builder.LoadDictionary(@"e:\MVoice\lem\bin-windows\dictionary.xml");
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);

        List<string> rule_filenames = new List<string>();

        int portion = 0;
        while (builder.IsThereOmonymsToProcess())
        {
            //InlineSampleSource samples = new InlineSampleSource();
            SyntanSamples samples = new SyntanSamples(@"e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lexicon\syntax-ru.txt");
            //PlainSamples samples = new PlainSamples( @"e:\MVoice\lem\tmp\used_samples.txt" );

            List<string> used_samples_list = new List<string>();

            int counter = 0;
            foreach (string sample in samples.Samples())
            {
                Console.WriteLine("{2}.0.{1}: {0}", sample, counter++, portion);
                if (builder.ProcessSample(sample))
                {
                    used_samples_list.Add(sample);
                }
            }

            if (counter > 0)
            {
                counter = 0;

                // Второй проход - более поздние сэмплы должны верифицировать правила, сгенерированные из более ранних.
                foreach (string sample in used_samples_list)
                {
                    Console.WriteLine("{2}.1.{1}: {0}", sample, counter++, portion);
                    builder.ProcessSample(sample);
                }

                string rule_filename = string.Format("rus_ma_filters_auto-{0}.sol", portion);
                builder.DumpRules(rule_filename);
                rule_filenames.Add(rule_filename);
                portion++;
            }
            else
            {
                break;
            }


            builder.NewPortion();
        }

        return;
    }



    // ---------------------------------------------- СТАТИСТИЧЕСКИЙ МНОГОФАКТОРНЫЙ КЛАССИФИКАТОР -------------------------------------------------
    private static void BuildBayesModel_2Factors()
    {
        Builder_Bayes_2Factor builder = new Builder_Bayes_2Factor();
        builder.LoadDictionary(@"e:\MVoice\lem\bin-windows\dictionary.xml");
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(@"e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lexicon\syntax-ru.txt");

        int counter = 0;
        int MAX_COUNT = 10000;

        bool test10 = true; // каждый 10-й пример - это тест, его исключаем из обучающей выборки

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;

            if (test10 && (counter % 10) == 0)
                continue;

            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();
        string rule_filename = "trigrams.sol";
        builder.DumpRules(rule_filename);


        // Проверим релевантность модели
        samples.Rewind();
        counter = 0;
        int total_word_count = 0; // всего обработано слов
        int error_count_no_filter = 0; // сколько ошибок модель допускает без использования фильтров.
        int error_count_with_model = 0; // сколько ошибок допускает модель при использовании рекомендаций 2грамм

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;

            if (test10 && (counter % 10) != 0)
                continue;

            Console.WriteLine("1.{1}: {0}", sample, counter);
            builder.Check(sample, ref total_word_count, ref error_count_no_filter, ref error_count_with_model);
        }

        Console.WriteLine("total_word_count={0}", total_word_count);
        Console.WriteLine("error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent(error_count_no_filter, total_word_count));
        Console.WriteLine("error_count_with_model={0}, i.e. {1}%", error_count_with_model, PercentFormatter.Percent(error_count_with_model, total_word_count));

        return;
    }




    // ---------------------------------------------- СТАТИСТИЧЕСКИЙ КЛАССИФИКАТОР -------------------------------------------------
    // Вероятностная модель морфологии
    private static void BuildBayesModel()
    {
        Builder_Bayes builder = new Builder_Bayes();
        builder.LoadDictionary(@"e:\MVoice\lem\bin-windows\dictionary.xml");
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(@"e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lexicon\syntax-ru.txt");

        int counter = 0;
        int MAX_COUNT = 10000;//NSAMPLE;

        bool test10 = false; // каждый 10-й пример - это тест, его исключаем из обучающей выборки

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;

            if (test10 && (counter % 10) == 0)
                continue;

            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();
        string rule_filename = "trigrams.sol";
        builder.DumpRules(rule_filename);


        // Проверим релевантность модели
        samples.Rewind();
        counter = 0;
        int total_word_count = 0; // всего обработано слов
        int error_count_no_filter = 0; // сколько ошибок модель допускает без использования фильтров.
        int POS_error_count = 0; // сколько ошибок допускает модель при использовании рекомендаций 2грамм
        int FEATURESET_error_count = 0;
        int VERB_error_count = 0;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;

            if (test10 && (counter % 10) != 0)
                continue;

            Console.WriteLine("1.{1}: {0}", sample, counter);
            builder.Check(sample, ref total_word_count, ref error_count_no_filter, ref POS_error_count, ref FEATURESET_error_count, ref VERB_error_count);
        }

        Console.WriteLine("total_word_count={0}", total_word_count);
        Console.WriteLine("error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent(error_count_no_filter, total_word_count));
        Console.WriteLine("POS recognition errors={0}, i.e. {1}%", POS_error_count, PercentFormatter.Percent(POS_error_count, total_word_count));
        Console.WriteLine("FEATURESET recognition errors={0}, i.e. {1}%", FEATURESET_error_count, PercentFormatter.Percent(FEATURESET_error_count, total_word_count));
        Console.WriteLine("VERB recognition errors={0}, i.e. {1}%", VERB_error_count, PercentFormatter.Percent(VERB_error_count, total_word_count));

        return;
    }




    private static void BuildBayesModelSuffix()
    {
        Builder_BayesSuffix builder = new Builder_BayesSuffix();
        builder.LoadDictionary(@"e:\MVoice\lem\bin-windows\dictionary.xml");
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(@"e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lexicon\syntax-ru.txt");

        int counter = 0;
        int MAX_COUNT = 1000;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;

            if ((counter % 2) == 1)
                continue;

            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();
        string rule_filename = "trigrams.sol";
        builder.DumpRules(rule_filename);


        // Проверим релевантность модели
        samples.Rewind();
        counter = 0;
        int total_word_count = 0; // всего обработано слов
        int error_count_no_filter = 0; // сколько ошибок модель допускает без использования фильтров.
        int error_count_with_model = 0; // сколько ошибок допускает модель при использовании рекомендаций 2грамм

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;

            if ((counter % 2) == 0)
                continue;

            Console.WriteLine("1.{1}: {0}", sample, counter);
            builder.Check(sample, ref total_word_count, ref error_count_no_filter, ref error_count_with_model);
        }

        Console.WriteLine("total_word_count={0}", total_word_count);
        Console.WriteLine("error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent(error_count_no_filter, total_word_count));
        Console.WriteLine("error_count_with_model={0}, i.e. {1}%", error_count_with_model, PercentFormatter.Percent(error_count_with_model, total_word_count));

        return;
    }

    // --------------------------------------------------------------------------



    // ---------------------------------------------- HMM -------------------------------------------------
    private static void Build_HMM()
    {
        Builder_HMM builder = new Builder_HMM();
        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(corpus_path);

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            Console.WriteLine("0.{1}: {0}", sample, counter++);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();

        // Проверим релевантность модели
        samples.Rewind();
        counter = 0;
        int total_word_count = 0;
        int error_count_no_filter = 0;
        int POS_error_count = 0;
        int FEATURESET_error_count = 0;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            Console.WriteLine("1.{1}: {0}", sample, counter++);
            builder.Check(sample, ref total_word_count, ref error_count_no_filter, ref POS_error_count, ref FEATURESET_error_count);
        }

        Console.WriteLine("total_word_count={0}", total_word_count);
        Console.WriteLine("error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent(error_count_no_filter, total_word_count));
        Console.WriteLine("POS recognition error count={0}, i.e. {1}%", POS_error_count, PercentFormatter.Percent(POS_error_count, total_word_count));
        Console.WriteLine("FEATURESET recognition error count={0}, i.e. {1}%", FEATURESET_error_count, PercentFormatter.Percent(FEATURESET_error_count, total_word_count));

        return;
    }


    private static void Build_Lemmatizer_HMM_Suffix()
    {
        Builder_Lemmatizer_HMM_Suffix builder = new Builder_Lemmatizer_HMM_Suffix();
        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(corpus_path);

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            Console.WriteLine("0.{1}: {0}", sample, counter++);
            builder.ProcessSample(sample);
        }

        builder.FinishSuffixCollection();

        counter = 0;
        samples.Rewind();

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            Console.WriteLine("1.{1}: {0}", sample, counter++);
            builder.ProcessSample2(sample);
        }

        builder.FinishLearning();

        // Проверим релевантность модели
        samples.Rewind();
        counter = 0;
        int total_word_count = 0;
        int error_count_no_filter = 0;
        int error_count_with_model = 0;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            Console.WriteLine("2.{1}: {0}", sample, counter++);
            builder.Check(sample, ref total_word_count, ref error_count_no_filter, ref error_count_with_model);
        }

        Console.WriteLine("total_word_count={0}", total_word_count);
        Console.WriteLine("error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent(error_count_no_filter, total_word_count));
        Console.WriteLine("error_count_with_model={0}, i.e. {1}%", error_count_with_model, PercentFormatter.Percent(error_count_with_model, total_word_count));

        return;
    }


    private static void Build_HMM_Suffix()
    {
        Builder_HMM_Suffix builder = new Builder_HMM_Suffix();
        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(corpus_path);

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            Console.WriteLine("0.{1}: {0}", sample, counter++);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();

        // Проверим релевантность модели
        samples.Rewind();
        counter = 0;
        int total_word_count = 0;
        int error_count_no_filter = 0;
        int error_count_with_model = 0;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            Console.WriteLine("1.{1}: {0}", sample, counter++);
            builder.Check(sample, ref total_word_count, ref error_count_no_filter, ref error_count_with_model);
        }

        Console.WriteLine("total_word_count={0}", total_word_count);
        Console.WriteLine("error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent(error_count_no_filter, total_word_count));
        Console.WriteLine("error_count_with_model={0}, i.e. {1}%", error_count_with_model, PercentFormatter.Percent(error_count_with_model, total_word_count));

        return;
    }


    // --------------------------------------------------------------------------

    private static void Build_SVM()
    {
        Builder_SVM svm = new Builder_SVM();
        svm.LoadDictionary(Program.dictionary_path);
        svm.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        svm.Init();


        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        bool separate_test = true; // каждый n-й пример - тест
        int TEST_SHARE = 10; // каждый такой пример в тест


        if (System.IO.Path.GetExtension(corpus_path) == ".txt")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);

            foreach (string sample_str in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                Console.WriteLine("{1}: {0}", sample_str, counter);

                using (SampleData sample = new SampleData())
                {
                    sample.sample = sample_str;

                    if (separate_test)
                    {
                        if ((counter % TEST_SHARE) == 0)
                            svm.Check(sample);
                        else
                            svm.ProcessSample(sample);
                    }
                    else
                    {
                        svm.ProcessSample(sample);
                        svm.Check(sample);
                    }
                }
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            System.IO.StreamWriter wrt_log = new System.IO.StreamWriter("corpus-loading.txt");

            int total_train_count = 0, total_test_count = 0;

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                wrt_log.WriteLine("Reading corpus {0}...", path1);
                int corpus_count = 0;
                int corpus_train_count = 0, corpus_test_count = 0;


                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(svm.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

                while (true)
                {
                    corpus_count++;

                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(svm.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(svm.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(svm.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(svm.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(svm.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(svm.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("{1}: {0}", sample.sample, counter);

                        if (separate_test)
                        {
                            if ((counter % TEST_SHARE) == 0)
                            {
                                svm.Check(sample);
                                corpus_test_count++;
                            }
                            else
                            {
                                svm.ProcessSample(sample);
                                corpus_train_count++;
                            }
                        }
                        else
                        {
                            svm.ProcessSample(sample);
                            svm.Check(sample);
                            corpus_train_count++;
                            corpus_test_count++;
                        }

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(svm.GetGrammarEngine().GetEngineHandle(), hCorpus);

                wrt_log.WriteLine("Total number of samples in [{0}]={1}, train_count={2}, test_count={3}\n\n", path1, corpus_count, corpus_train_count, corpus_test_count);
                wrt_log.Flush();

                total_train_count += corpus_train_count;
                total_test_count += corpus_test_count;
            }

            wrt_log.WriteLine("\ntotal_train_count={0}, total_test_count={1}", total_train_count, total_test_count);

            wrt_log.Flush();
            wrt_log.Close();
        }


        svm.FinishLearning();
        //Console.WriteLine( "Сохраняем файл модели..." );
        //svm.StoreModel();

        svm.FinishTesting();

        return;
    }



    private static void Build_Chunker_CRF()
    {
        Builder_Syntax_CRF builder = new Builder_Syntax_CRF();
        builder.LoadDictionary(@"e:\MVoice\lem\bin-windows\dictionary.xml");
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(@"e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lexicon\syntax-ru.txt");

        int counter = 0;
        int MAX_COUNT = 100000;
        bool OddEven = false;

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;

            if (OddEven && (counter % 2) == 1)
                continue;

            Console.WriteLine("0.{1}: {0}", sample, counter);
            builder.ProcessSample(sample);
        }

        builder.FinishLearning();

        samples.Rewind();
        counter = 0;
        int total_word_count = 0; // всего обработано слов
        int error_count_with_model = 0; // сколько ошибок допускает модель при использовании модели

        foreach (string sample in samples.Samples())
        {
            if (counter >= MAX_COUNT) break;

            counter++;

            if (OddEven && (counter % 2) == 0)
                continue;

            Console.WriteLine("1.{1}: {0}", sample, counter);
            builder.Check(sample);
        }

        builder.FinishTesting(out total_word_count, out error_count_with_model);

        Console.WriteLine("total_word_count={0}", total_word_count);
        Console.WriteLine("error_count_with_model={0}, i.e. {1}%", error_count_with_model, PercentFormatter.Percent(error_count_with_model, total_word_count));

        return;
    }



    private static void AdjacentMatrix()
    {
        AdjacentMatrix builder = new AdjacentMatrix();
        builder.LoadDictionary(@"e:\MVoice\lem\bin-windows\dictionary.xml");
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        SyntanSamples samples = new SyntanSamples(@"e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lexicon\syntax-ru.txt");

        int counter = 0;
        int MAX_COUNT = 100000;
        bool OddEven = false;

        using (System.IO.StreamWriter log = new System.IO.StreamWriter("log.txt"))
        {
            foreach (string sample in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                if (OddEven && (counter % 2) == 1)
                    continue;

                log.WriteLine("{0}", sample); log.Flush();

                Console.WriteLine("0.{1}: {0}", sample, counter);
                builder.ProcessSample(sample);
            }
        }

        builder.FinishLearning();


        /*
          samples.Rewind();
          counter = 0;
          int total_word_count = 0; // всего обработано слов
          int error_count_with_model = 0; // сколько ошибок допускает модель при использовании модели

          foreach( string sample in samples.Samples() )
          {
           if( counter >= MAX_COUNT ) break;

           counter++;

           if( OddEven && ( counter % 2 ) == 0 )
            continue;

           Console.WriteLine( "1.{1}: {0}", sample, counter );
           builder.Check( sample );
          }

          builder.FinishTesting( out total_word_count, out error_count_with_model );

          Console.WriteLine( "total_word_count={0}", total_word_count );
          Console.WriteLine( "error_count_with_model={0}, i.e. {1}%", error_count_with_model, PercentFormatter.Percent( error_count_with_model, total_word_count ) );
        */

        return;
    }




    private static void Build_Syntax_Neuro()
    {
        Builder_Syntax_Neuro builder = new Builder_Syntax_Neuro();
        builder.LoadDictionary(dictionary_path);

        //builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);

        // -------------------------------------------------------------------
        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", path1));

                while (true)
                {
                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        if (counter >= MAX_COUNT)
                            break;

                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (sample.morphology.Count >= MIN_SENT_LEN)
                        {
                            counter++;
                            Console.WriteLine("0.{1}: {0}", sample.sample, counter);

                            bool test_sample = false, train_sample = true;
                            if ((counter % 10) == 0)
                            {
                                test_sample = true;
                                train_sample = false;
                            }

                            builder.ProcessSample(sample, train_sample, test_sample);
                        }

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".xml")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);
            foreach (string sample_str in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                Console.WriteLine("{1}: {0}", sample_str, counter);

                using (SampleData sample = new SampleData())
                {
                    sample.sample = sample_str;

                    bool test_sample = false, train_sample = true;
                    if ((counter % 10) == 0)
                    {
                        test_sample = true;
                        train_sample = false;
                    }

                    builder.ProcessSample(sample, train_sample, test_sample);
                }
            }
        }
        // -------------------------------------------------------------------

        builder.FinishLearning();


        builder.FinishTesting();

        return;
    }


    private static void Stat(List<string> model_params)
    {
        StatAssembler assembler = new StatAssembler();
        assembler.WordEntryOnly = false;

        assembler.ChangeModelParams(model_params);
        assembler.LoadDictionary(dictionary_path);
        assembler.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(assembler.gren.GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

                while (true)
                {
                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(assembler.gren.GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(assembler.gren.GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(assembler.gren.GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(assembler.gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(assembler.gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(assembler.gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("0.{1}: {0}", sample.sample, counter);
                        assembler.ProcessSample(sample);

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(assembler.gren.GetEngineHandle(), hCorpus);
            }
        }
        else
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);


            foreach (string line in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;
                Console.WriteLine("0.{1}: {0}", line, counter);

                SampleData sample = new SampleData();
                sample.sample = line;
                assembler.ProcessSample(sample);

                if (sample.morphology != null)
                    SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(sample.morphology.GetHandle());

                if (sample.tokenization != null)
                    SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(sample.tokenization.GetHandle());

                if (sample.syntax_tree != null)
                    SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(sample.syntax_tree.GetHandle());
            }
        }

        assembler.Store();
        assembler.Print();

        Console.WriteLine("{0} samples has been processed", counter);

        return;
    }



    private static void Facts()
    {
        FactAssembler assembler = new FactAssembler();
        assembler.LoadDictionary(dictionary_path);
        assembler.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);

        int counter = 0;
        int MAX_COUNT = 300000;

        using (System.IO.StreamReader rdr = new System.IO.StreamReader(@"e:\trash\МатериалДляСбораАссоциаций\Collocations\bin\Debug\collocations.jap_rus_warodai.txt"))
        {
            while (!rdr.EndOfStream)
            {
                string sample = rdr.ReadLine();
                if (sample == null)
                    break;

                if (sample.Length > 0)
                {
                    if (counter >= MAX_COUNT) break;

                    counter++;
                    Console.WriteLine("0.{1}: {0}", sample, counter);
                    assembler.ProcessSample(sample);
                }
            }
        }

        /*
          SyntanSamples samples = new SyntanSamples( @"e:\MVoice\lem\demo\ai\solarix\Grammar_Engine\Lexicon\syntax-ru.txt" );
          foreach( string sample in samples.Samples() )
          {
           if( counter >= MAX_COUNT ) break;

           counter++;
           Console.WriteLine( "0.{1}: {0}", sample, counter );
           assembler.ProcessSample( sample );
          }
        */

        assembler.Store();
        assembler.Print();

        return;
    }



    static void Build_DependencySyntax_DESR(List<string> model_params)
    {
        DESR_Builder builder = new DESR_Builder();

        builder.ChangeModelParams(model_params);

        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);
        builder.Init();


        // -------------------------------------------------------------------
        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", path1));

                while (true)
                {
                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        if (counter >= MAX_COUNT)
                            break;

                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (sample.morphology.Count >= MIN_SENT_LEN)
                        {
                            counter++;
                            Console.WriteLine("0.{1}: {0}", sample.sample, counter);

                            bool test_sample = false, train_sample = true;
                            if ((counter % 10) == 0)
                            {
                                test_sample = true;
                                train_sample = false;
                            }

                            builder.ProcessSample(sample, train_sample, test_sample);
                        }

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".xml")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);
            foreach (string sample_str in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                Console.WriteLine("{1}: {0}", sample_str, counter);

                using (SampleData sample = new SampleData())
                {
                    sample.sample = sample_str;

                    bool test_sample = false, train_sample = true;
                    if ((counter % 10) == 0)
                    {
                        test_sample = true;
                        train_sample = false;
                    }

                    builder.ProcessSample(sample, train_sample, test_sample);
                }
            }
        }




        builder.AfterLearning();

        return;
    }



    private static void Build_Tokenizer(List<string> model_params)
    {
        TokenizerBuilder builder = new TokenizerBuilder();

        builder.ChangeModelParams(model_params);

        builder.LoadDictionary(dictionary_path);
        builder.SetLanguage(SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE);

        //  if( !string.IsNullOrEmpty( sematags_path ) )
        //   builder.LoadSemanticTags( sematags_path );

        int counter = 0;
        int MAX_COUNT = NSAMPLE;

        bool separate_test = true; // каждый n-й пример - тест
        int TEST_SHARE = 10; // каждый такой пример в тест

        Console.WriteLine("Processing data in corpus {0}...", corpus_path);

        if (System.IO.Path.GetExtension(corpus_path) == ".txt")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);

            foreach (string sample_str in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                Console.WriteLine("0.{1}: {0}", sample_str, counter);

                using (SampleData sample = new SampleData())
                {
                    sample.sample = sample_str;

                    if (separate_test)
                    {
                        if ((counter % TEST_SHARE) == 0)
                            builder.Check(sample);
                        else
                            builder.ProcessSample(sample);
                    }
                    else
                    {
                        builder.ProcessSample(sample);
                        builder.Check(sample);
                    }
                }
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            Console.WriteLine("There are {0} binary corpus segments", bin_corpora.Length);

            System.IO.StreamWriter wrt_log = new System.IO.StreamWriter("corpus-loading.txt");

            int total_train_count = 0, total_test_count = 0;

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                wrt_log.WriteLine("Reading corpus {0}...", path1);
                int corpus_count = 0;
                int corpus_train_count = 0, corpus_test_count = 0;


                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

                while (true)
                {
                    corpus_count++;

                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("0.{1}: {0}", sample.sample, counter);

                        /*
                              if( separate_test )
                              {
                               if( ( counter % TEST_SHARE ) == 0 )
                               {
                                builder.Check( sample );
                                corpus_test_count++;
                               }
                               else
                               {
                                builder.ProcessSample( sample );
                                corpus_train_count++;
                               }
                              }
                              else
                              {
                               builder.ProcessSample( sample );
                               builder.Check( sample );
                               corpus_train_count++;
                               corpus_test_count++;
                              }
                        */

                        builder.ProcessSample(sample);
                        builder.Check(sample);
                        corpus_train_count++;
                        corpus_test_count++;

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                wrt_log.WriteLine("Total number of samples in [{0}]={1}, train_count={2}, test_count={3}\n\n", path1, corpus_count, corpus_train_count, corpus_test_count);
                wrt_log.Flush();

                total_train_count += corpus_train_count;
                total_test_count += corpus_test_count;
            }

            wrt_log.WriteLine("\ntotal_train_count={0}, total_test_count={1}", total_train_count, total_test_count);

            wrt_log.Flush();
            wrt_log.Close();
        }


        builder.FinishLearning();
        Console.WriteLine("Storing the model files...");
        builder.StoreModel();

        builder.FinishTesting();

        return;
    }


    private static void Build_LemmByPostags(List<string> model_params)
    {
        Builder_LEMM_ByPOSTag builder = new Builder_LEMM_ByPOSTag();
        builder.ChangeModelParams(model_params);
        builder.LoadDictionary(dictionary_path);
        builder.Init();

        #region Process_Corpus
        int counter = 0;
        int MAX_COUNT = NSAMPLE;
        if (MAX_COUNT == 0) MAX_COUNT = int.MaxValue;

        bool separate_test = true; // каждый n-й пример - тест
        int TEST_SHARE = 10; // каждый такой пример в тест

        Console.WriteLine("Processing data in corpus {0}...", corpus_path);

        if (System.IO.Path.GetExtension(corpus_path) == ".xml")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);

            foreach (string sample_str in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                Console.WriteLine("{1}: {0}", sample_str, counter);

                using (SampleData sample = new SampleData())
                {
                    sample.sample = sample_str;

                    if (separate_test)
                    {
                        if ((counter % TEST_SHARE) == 0)
                            builder.Check(sample);
                        else
                            builder.ProcessSample(sample);
                    }
                    else
                    {
                        builder.ProcessSample(sample);
                        builder.Check(sample);
                    }
                }
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            Console.WriteLine("There are {0} binary corpus segments", bin_corpora.Length);

            System.IO.StreamWriter wrt_log = new System.IO.StreamWriter("corpus-loading.txt");

            int total_train_count = 0, total_test_count = 0;

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                wrt_log.WriteLine("Reading corpus {0}...", path1);
                int corpus_count = 0;
                int corpus_train_count = 0, corpus_test_count = 0;


                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

                while (true)
                {
                    corpus_count++;

                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("{1}: {0}", sample.sample, counter);

                        if (separate_test)
                        {
                            if ((counter % TEST_SHARE) == 0)
                            {
                                builder.Check(sample);
                                corpus_test_count++;
                            }
                            else
                            {
                                builder.ProcessSample(sample);
                                corpus_train_count++;
                            }
                        }
                        else
                        {
                            builder.ProcessSample(sample);
                            builder.Check(sample);
                            corpus_train_count++;
                            corpus_test_count++;
                        }

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                wrt_log.WriteLine("Total number of samples in [{0}]={1}, train_count={2}, test_count={3}\n\n", path1, corpus_count, corpus_train_count, corpus_test_count);
                wrt_log.Flush();

                total_train_count += corpus_train_count;
                total_test_count += corpus_test_count;
            }

            wrt_log.WriteLine("\ntotal_train_count={0}, total_test_count={1}", total_train_count, total_test_count);

            wrt_log.Flush();
            wrt_log.Close();
        }
        #endregion Process_Corpus

        builder.FinishLearning();
        builder.StartTesting();
        builder.PrintTestResults();
        return;
    }




    private static void Build_Morphology_RNNSharp(List<string> model_params)
    {
        Builder_RNNSharp builder = new Builder_RNNSharp();
        builder.ChangeModelParams(model_params);
        builder.LoadDictionary(dictionary_path);
        builder.Init();

        #region Process_Corpus
        int counter = 0;
        int MAX_COUNT = NSAMPLE;
        if (MAX_COUNT == 0) MAX_COUNT = int.MaxValue;

        Console.WriteLine("Processing data in corpus {0}...", corpus_path);

        if (System.IO.Path.GetExtension(corpus_path) == ".xml")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);

            foreach (string sample_str in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                Console.WriteLine("{1}: {0}", sample_str, counter);

                using (SampleData sample = new SampleData())
                {
                    sample.sample = sample_str;

                    builder.ProcessSample(sample);
                }
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            Console.WriteLine("There are {0} binary corpus segments", bin_corpora.Length);

            System.IO.StreamWriter wrt_log = new System.IO.StreamWriter("corpus-loading.txt");

            int total_train_count = 0, total_test_count = 0;

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                wrt_log.WriteLine("Reading corpus {0}...", path1);
                int corpus_count = 0;
                int corpus_train_count = 0, corpus_test_count = 0;


                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

                while (true)
                {
                    corpus_count++;

                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("{1}: {0}", sample.sample, counter);

                        builder.ProcessSample(sample);

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                wrt_log.WriteLine("Total number of samples in [{0}]={1}, train_count={2}, test_count={3}\n\n", path1, corpus_count, corpus_train_count, corpus_test_count);
                wrt_log.Flush();

                total_train_count += corpus_train_count;
                total_test_count += corpus_test_count;
            }

            wrt_log.WriteLine("\ntotal_train_count={0}, total_test_count={1}", total_train_count, total_test_count);

            wrt_log.Flush();
            wrt_log.Close();
        }
        #endregion Process_Corpus

        builder.FinishLearning();
        builder.StartTesting();
        builder.PrintTestResults();
        return;
    }



    private static void Build_WordShingles_POSTagger(List<string> model_params)
    {
        Builder_WordShingles builder = new Builder_WordShingles();
        builder.ChangeModelParams(model_params);
        builder.LoadDictionary(dictionary_path);
        builder.Init();

        #region Process_Corpus
        int counter = 0;
        int MAX_COUNT = NSAMPLE;
        if (MAX_COUNT == 0) MAX_COUNT = int.MaxValue;

        Console.WriteLine("Processing data in corpus {0}...", corpus_path);

        if (System.IO.Path.GetExtension(corpus_path) == ".xml")
        {
            SyntanSamples samples = new SyntanSamples(corpus_path);

            foreach (string sample_str in samples.Samples())
            {
                if (counter >= MAX_COUNT) break;

                counter++;

                Console.WriteLine("{1}: {0}", sample_str, counter);

                using (SampleData sample = new SampleData())
                {
                    sample.sample = sample_str;

                    builder.ProcessSample(sample);
                }
            }
        }
        else if (System.IO.Path.GetExtension(corpus_path) == ".bin")
        {
            string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            Console.WriteLine("There are {0} binary corpus segments", bin_corpora.Length);

            System.IO.StreamWriter wrt_log = new System.IO.StreamWriter("corpus-loading.txt");

            int total_train_count = 0, total_test_count = 0;

            foreach (string path1 in bin_corpora)
            {
                Console.WriteLine("Reading corpus {0}...", path1);

                wrt_log.WriteLine("Reading corpus {0}...", path1);
                int corpus_count = 0;
                int corpus_train_count = 0, corpus_test_count = 0;


                IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(builder.GetGrammarEngine().GetEngineHandle(), path1, false);
                if (hCorpus == IntPtr.Zero)
                    throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

                while (true)
                {
                    corpus_count++;

                    IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    if (hSample1 == IntPtr.Zero)
                        break;

                    IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);
                    IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                    using (SampleData sample = new SampleData())
                    {
                        sample.sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                        sample.morphology = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                        sample.tokenization = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                        sample.syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(builder.GetGrammarEngine(), SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                        if (counter >= MAX_COUNT) break;

                        counter++;
                        Console.WriteLine("{1}: {0}", sample.sample, counter);

                        builder.ProcessSample(sample);

                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                        SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
                    }
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(builder.GetGrammarEngine().GetEngineHandle(), hCorpus);

                wrt_log.WriteLine("Total number of samples in [{0}]={1}, train_count={2}, test_count={3}\n\n", path1, corpus_count, corpus_train_count, corpus_test_count);
                wrt_log.Flush();

                total_train_count += corpus_train_count;
                total_test_count += corpus_test_count;
            }

            wrt_log.WriteLine("\ntotal_train_count={0}, total_test_count={1}", total_train_count, total_test_count);

            wrt_log.Flush();
            wrt_log.Close();
        }
        #endregion Process_Corpus

        builder.FinishLearning();
        builder.StartTesting();
        builder.PrintTestResults();
        return;
    }
}

