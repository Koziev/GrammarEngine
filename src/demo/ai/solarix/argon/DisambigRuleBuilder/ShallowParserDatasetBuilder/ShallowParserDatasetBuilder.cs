// Тренер для чанкера.
// Используется консольный интерфейс CRFSuite.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class ShallowParserDatasetBuilder
{
    static int shingle_len = 3;
    static int window = 3;
    static bool emit_shingles = true;
    static bool emit_morphtags = true;


    static Dictionary<string, int> shingle2index = new Dictionary<string, int>();

    static void GetChunkNodes(SolarixGrammarEngineNET.SyntaxTreeNode node,
        int chunk_index,
        Dictionary<int/*word_index*/, int/*chunk_index*/> labels)
    {
        labels[node.GetWordPosition()] = chunk_index;

        for (int i = 0; i < node.leafs.Count; ++i)
        {
            GetChunkNodes(node.leafs[i], chunk_index, labels);
        }
    }

    static void FindChunks(SolarixGrammarEngineNET.AnalysisResults root, Dictionary<int/*word_index*/, int/*chunk_index*/> labels)
    {
        var root_node = root[1];

        labels[root_node.GetWordPosition()] = root_node.GetWordPosition();

        for (int i = 0; i < root_node.leafs.Count; ++i)
        {
            var child_node = root_node.leafs[i];
            int chunk_index = child_node.GetWordPosition();
            GetChunkNodes(child_node, chunk_index, labels);
        }
    }

    static List<int> GetShingles(string word)
    {
        List<int> shingles = new List<int>();

        string word2 = "\t" + word.ToLower() + "\t";

        for (int i = 0; i < word2.Length - shingle_len + 1; ++i)
        {
            string shingle = word2.Substring(i, shingle_len);
            int shingle_index = -1;
            if (!shingle2index.TryGetValue(shingle, out shingle_index))
            {
                shingle_index = shingle2index.Count;
                shingle2index[shingle] = shingle_index;
            }

            shingles.Add(shingle_index);
        }

        return shingles;
    }


    static List<string> GetWordFeatures(SolarixGrammarEngineNET.GrammarEngine2 gren, SolarixGrammarEngineNET.SyntaxTreeNode word, string feature_prefix)
    {
        List<string> features = new List<string>();

        if (emit_shingles)
        {
            // шинглы
            features.AddRange(GetShingles(word.GetWord()).Select(z => $"shingle[{feature_prefix}]={z}"));
        }

        if (emit_morphtags)
        {
            // морфологические фичи
            int id_class = gren.GetEntryClass(word.GetEntryID());
            features.Add(string.Format("class[{0}]={1}", feature_prefix, id_class));

            int nfeat = SolarixGrammarEngineNET.GrammarEngine.sol_GetNodePairsCount(word.hNode);
            for (int i = 0; i < nfeat; ++i)
            {
                int id_coord = SolarixGrammarEngineNET.GrammarEngine.sol_GetNodePairCoord(word.hNode, i);
                int id_state = SolarixGrammarEngineNET.GrammarEngine.sol_GetNodePairState(word.hNode, i);
                features.Add(string.Format("{0}[{2}]={1}", id_coord, id_state, feature_prefix));
            }
        }

        return features;
    }


    static string GetFeatures(SolarixGrammarEngineNET.GrammarEngine2 gren, SolarixGrammarEngineNET.AnalysisResults words, int focus_index)
    {
        List<string> features = new List<string>();

        for (int offset = -window; offset <= window; ++offset)
        {
            int word_index = focus_index + offset;
            if (word_index >= 1 && word_index < words.Count-1)
            {
                features.AddRange(GetWordFeatures(gren, words[word_index], offset.ToString()));

                if( word_index == 1 )
                {
                    features.Add($"start[{offset}]");
                }

                if( word_index == words.Count-2)
                {
                    features.Add($"end[{offset}]");
                }
            }
        }

        return string.Join("\t", features);
    }


    static void Main(string[] args)
    {
        string corpus_path="";
        string dict_path="";
        string data_folder="";

        for( int iarg=0; iarg<args.Length; ++iarg)
        {
            string cmd = args[iarg].Substring(1);
            if(cmd == "corpus")
            {
                corpus_path = args[iarg + 1];
                iarg++;
            }
            else if( cmd=="dict")
            {
                dict_path = args[iarg + 1];
                iarg++;
            }
            else if (cmd == "workdir")
            {
                data_folder = args[iarg + 1];
                iarg++;
            }
            else if( cmd == "window")
            {
                window = int.Parse(args[iarg+1]);
                iarg++;
            }
            else if (cmd == "emit_shingles")
            {
                emit_shingles = bool.Parse(args[iarg+1]);
                iarg++;
            }
            else if (cmd == "emit_morphtags")
            {
                emit_morphtags = bool.Parse(args[iarg+1]);
                iarg++;
            }
            else
            {
                throw new ApplicationException($"Unknown option [{args[iarg]}]");
            }
        }



        string train_path = System.IO.Path.Combine(data_folder, "chunker_train.dat");
        string test_path = System.IO.Path.Combine(data_folder, "chunker_test.dat");
        string test_result_path = System.IO.Path.Combine(data_folder, "chunker_eval.txt");

        Console.WriteLine("Loading dictionary from {0}...", dict_path);
        SolarixGrammarEngineNET.GrammarEngine2 gren;
        gren = new SolarixGrammarEngineNET.GrammarEngine2();
        gren.Load(dict_path, true);

        int counter = 0;
        int MAX_COUNT = 10000000;

        string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

        System.IO.StreamWriter wrt_train = new System.IO.StreamWriter(train_path);
        System.IO.StreamWriter wrt_test = new System.IO.StreamWriter(test_path);

        foreach (string path1 in bin_corpora)
        {
            Console.WriteLine("Reading corpus {0}...", path1);

            IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(gren.GetEngineHandle(), path1, false);
            if (hCorpus == IntPtr.Zero)
                throw new ApplicationException(string.Format("Can not open corpus {0}", path1));

            while (true)
            {
                IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(gren.GetEngineHandle(), hCorpus);
                if (hSample1 == IntPtr.Zero)
                    break;

                IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(gren.GetEngineHandle(), hCorpus);
                IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(gren.GetEngineHandle(), hCorpus);

                if (counter >= MAX_COUNT)
                    break;

                string sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                var morphology = new SolarixGrammarEngineNET.AnalysisResults(gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                var tokenization = new SolarixGrammarEngineNET.AnalysisResults(gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                var syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                counter++;
                Console.WriteLine("0.{1}: {0}", sample, counter);

                bool test_sample = false, train_sample = true;
                if ((counter % 10) == 0)
                {
                    test_sample = true;
                    train_sample = false;
                }

                if (syntax_tree.Count == 3)
                {
                    System.IO.StreamWriter wrt = train_sample ? wrt_train : wrt_test;


                    // Получаем список слов с прикрепленными к ним номерами чанков.
                    Dictionary<int/*word_index*/, int/*chunk_index*/> labels = new Dictionary<int, int>();
                    FindChunks(syntax_tree, labels);

                    // Вставим специальный чанк для фиктивного слова слева от первого, чтобы первое слово
                    // автоматом пометилось как начало чанка.
                    labels[-1] = -1;

                    for (int i = 1; i < morphology.Count - 1; ++i)
                    {
                        int label = 0;

                        int word_index = i - 1;

                        // Если слово начинает новый чанк, то есть слева было слово из другого чанка,
                        // то метка будет 1.
                        try
                        {
                            if (labels[word_index - 1] != labels[word_index])
                            {
                                label = 1;
                            }
                        }
                        catch (KeyNotFoundException ex)
                        {
                            Console.WriteLine("Missing word {0} in syntax tree for sample {1}", morphology[i].GetWord(), sample);
                        }


                        string features = GetFeatures(gren, morphology, i);
                        wrt.WriteLine("{0}\t{1}", label, features);
                    }

                    wrt.WriteLine("");
                    wrt.Flush();
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
            }

            SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(gren.GetEngineHandle(), hCorpus);
        }

        wrt_train.Close();
        wrt_test.Close();


        // Сохраним информацию о кодировке фич, чтобы потом в C++ коде формировать данные для разбора.
        string codebook_path = System.IO.Path.Combine(data_folder, "chunker.codebook");
        Console.WriteLine("Writing feature codebook to {0}", codebook_path);
        if (System.IO.File.Exists(codebook_path))
        {
            System.IO.File.Delete(codebook_path);
        }

        using (System.IO.BinaryWriter wr = new System.IO.BinaryWriter(System.IO.File.OpenWrite(codebook_path)))
        {
            wr.Write(0);

            wr.Write(window);
            wr.Write(shingle_len);
            wr.Write(emit_shingles);
            wr.Write(emit_morphtags);

            wr.Write(shingle2index.Count);
            foreach (var k in shingle2index)
            {
                byte[] l8 = System.Text.Encoding.UTF8.GetBytes(k.Key);
                wr.Write(l8.Length);
                wr.Write(l8);
                wr.Write(k.Value);
            }
        }


        Console.WriteLine("Start training with CRFSuite on {0}...", train_path);
        System.Diagnostics.Process p = new System.Diagnostics.Process();
        p.StartInfo.Arguments = train_path + " " + data_folder;
        p.StartInfo.FileName = string.Format("{0}\\chunker_train.cmd", System.IO.Directory.GetCurrentDirectory());

        Console.WriteLine("Executing {0} {1}", p.StartInfo.FileName, p.StartInfo.Arguments);
        bool r = false;
        r = p.Start();
        p.WaitForExit();

        // Оценка точности
        p = new System.Diagnostics.Process();
        p.StartInfo.Arguments = test_path + " " + test_result_path + " " + data_folder;
        p.StartInfo.FileName = string.Format("{0}\\chunker_test.cmd", System.IO.Directory.GetCurrentDirectory());

        Console.WriteLine("Executing {0} {1}", p.StartInfo.FileName, p.StartInfo.Arguments);
        r = p.Start();
        p.WaitForExit();

        int nb_instance_errors = 0;
        int nb_word_errors = 0;
        int nb_instances = 0;
        int nb_words = 0;
        using (System.IO.StreamReader rdr = new System.IO.StreamReader(test_result_path))
        {
            bool instance_ok = true;
            while (!rdr.EndOfStream)
            {
                string line = rdr.ReadLine();
                if (line == null)
                {
                    break;
                }

                if (line == "")
                {
                    nb_instances++;
                    if (!instance_ok) nb_instance_errors++;

                    instance_ok = true;
                }
                else
                {
                    nb_words++;
                    string[] tx = line.Split('\t');
                    if (tx[0] != tx[1])
                    {
                        instance_ok = false;
                        nb_word_errors++;
                    }
                }
            }
        }

        Console.WriteLine("Per word accuracy={0}", ((float)(nb_words - nb_word_errors)) / nb_words);
        Console.WriteLine("Per instance accuracy={0}", ((float)(nb_instances - nb_instance_errors)) / nb_instances);

        return;
    }
}
