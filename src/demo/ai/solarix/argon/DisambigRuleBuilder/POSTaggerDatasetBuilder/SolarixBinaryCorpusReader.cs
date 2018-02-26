using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



class SolarixBinaryCorpusReader : ICorpusReader
{
    private string corpus_path;
    public SolarixBinaryCorpusReader(string corpus_path)
    {
        this.corpus_path = corpus_path;
    }

    public IEnumerable<SentenceData> Read(SolarixGrammarEngineNET.GrammarEngine2 gren)
    {
        string[] bin_corpora = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

        Console.WriteLine("There are {0} binary corpus segments", bin_corpora.Length);

        foreach (string path1 in bin_corpora)
        {
            Console.WriteLine("Reading corpus {0}...", path1);

            int corpus_count = 0;

            IntPtr hCorpus = SolarixGrammarEngineNET.GrammarEngine.sol_OpenCorpusStorage8(gren.GetEngineHandle(), path1, false);
            if (hCorpus == IntPtr.Zero)
                throw new ApplicationException(string.Format("Can not open corpus {0}", corpus_path));

            while (true)
            {
                corpus_count++;

                IntPtr hSample1 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(gren.GetEngineHandle(), hCorpus);
                if (hSample1 == IntPtr.Zero)
                    break;

                IntPtr hSample2 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(gren.GetEngineHandle(), hCorpus);
                IntPtr hSample3 = SolarixGrammarEngineNET.GrammarEngine.sol_LoadSyntaxTree(gren.GetEngineHandle(), hCorpus);

                string sample = SolarixGrammarEngineNET.GrammarEngine.sol_GetSentenceW(hSample1);
                var morphology = new SolarixGrammarEngineNET.AnalysisResults(gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample1), false);
                var tokenization = new SolarixGrammarEngineNET.AnalysisResults(gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample2), false);
                var syntax_tree = new SolarixGrammarEngineNET.AnalysisResults(gren, SolarixGrammarEngineNET.GrammarEngine.sol_GetTreeHandle(hSample3), false);

                if (morphology.Count == tokenization.Count)
                {
                    SentenceData sent = new SentenceData(sample);

                    for (int i = 0; i < morphology.Count; ++i)
                    {
                        WordData word_data = new WordData();

                        word_data.word = morphology[i].GetWord();
                        word_data.word_index = morphology[i].GetWordPosition();
                        word_data.entry_id = morphology[i].GetEntryID();
                        word_data.part_of_speech = gren.GetEntryClass(word_data.entry_id);
                        word_data.all_projs = tokenization[i];

                        foreach (var tag in morphology[i].GetPairs())
                        {
                            word_data.tags.Add(Tuple.Create(tag.CoordID, tag.StateID));
                        }

                        sent.AddWord(word_data);
                    }

                    yield return sent;
                }

                SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample1);
                SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample2);
                SolarixGrammarEngineNET.GrammarEngine.sol_FreeSyntaxTree(hSample3);
            }

            SolarixGrammarEngineNET.GrammarEngine.sol_CloseCorpusStorage(gren.GetEngineHandle(), hCorpus);
        }
    }
}


