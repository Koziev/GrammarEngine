using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace CorporaLib
{
    public class AutoLemmaCorpusGenerator : ICorpusReader
    {
        public AutoLemmaCorpusGenerator()
        { }

        public IEnumerable<SentenceData> Read(SolarixGrammarEngineNET.GrammarEngine2 gren)
        {
            // Сначала надо получить из словарной список слов, которые дают однозначную лемматизацию.

            HashSet<int> classes = new HashSet<int>();
            foreach (var class_name in "СУЩЕСТВИТЕЛЬНОЕ ПРИЛАГАТЕЛЬНОЕ ГЛАГОЛ ИНФИНИТИВ ДЕЕПРИЧАСТИЕ НАРЕЧИЕ".Split(' '))
            {
                classes.Add(gren.FindPartOfSpeech(class_name));
            }

            HashSet<string> forms = new HashSet<string>();
            MultiValueDictionary<string, string> form2lemma = new MultiValueDictionary<string, string>();
            MultiValueDictionary<string, int> form2entry = new MultiValueDictionary<string, int>();

            Console.WriteLine("Generating the list of words and lemmas...");
            IntPtr hList = SolarixGrammarEngineNET.GrammarEngine.sol_ListEntries(hEngine: gren.GetEngineHandle(),
                Flags: 0, EntryType: 0, Mask: ".+", Language: -1, PartOfSpeech: -1);
            int nb_entries = SolarixGrammarEngineNET.GrammarEngine.sol_CountInts(hList);
            for (int i = 0; i < nb_entries; ++i)
            {
                int id_entry = SolarixGrammarEngineNET.GrammarEngine.sol_GetInt(hList, i);

                if (classes.Contains(gren.GetEntryClass(id_entry)))
                {
                    string lemma = gren.GetEntryName(id_entry);
                    if (char.IsLetter(lemma[0]))
                    {
                        IntPtr hForms = SolarixGrammarEngineNET.GrammarEngine.sol_ListEntryForms(gren.GetEngineHandle(), id_entry);
                        int nb_forms = SolarixGrammarEngineNET.GrammarEngine.sol_CountStrings(hForms);

                        for (int iform = 0; iform < nb_forms; ++iform)
                        {
                            string form = SolarixGrammarEngineNET.GrammarEngine.sol_GetStringFX(hForms, iform);
                            form = gren.RestoreCasing(id_entry, form);
                            if (!form2lemma.Contains(form, lemma))
                            {
                                form2lemma.Add(form, lemma);
                                form2entry.Add(form, id_entry);
                                forms.Add(form);
                            }
                        }
                        SolarixGrammarEngineNET.GrammarEngine.sol_DeleteStrings(hForms);
                    }

                    if ((i % 10000) == 0)
                    {
                        Console.Write("{0}/{1}\r", i, nb_entries);
                    }
                }
            }
            SolarixGrammarEngineNET.GrammarEngine.sol_DeleteInts(hList);

            List<string> unambiguous_forms = forms.Where(z => form2lemma[z].Count == 1).ToList();
            Console.WriteLine("{0} forms are good for lemmatization", unambiguous_forms.Count);

            foreach (string word in unambiguous_forms)
            {
                //SolarixGrammarEngineNET.AnalysisResults morphology = gren.AnalyzeMorphology(word, -1);
                SolarixGrammarEngineNET.AnalysisResults tokenization = gren.AnalyzeMorphology(word, -1, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY, 0);

                bool ok = true;
                SentenceData sent = new SentenceData(word);

                for (int i = 0; i < tokenization.Count; ++i)
                {
                    if (i == 1 && !form2entry[word].Contains(tokenization[i].GetEntryID()))
                    {
                        ok = false;
                    }

                    WordData word_data = new WordData();

                    word_data.word = tokenization[i].GetWord();
                    word_data.word_index = tokenization[i].GetWordPosition();
                    word_data.entry_id = tokenization[i].GetEntryID();
                    word_data.part_of_speech = gren.GetEntryClass(word_data.entry_id);
                    word_data.all_projs = tokenization[i];

                    foreach (var tag in tokenization[i].GetPairs())
                    {
                        word_data.tags.Add(Tuple.Create(tag.CoordID, tag.StateID));
                    }

                    word_data.lemma = gren.GetEntryName(word_data.entry_id).ToLower();

                    if (word_data.lemma == "???")
                    {
                        word_data.lemma = word_data.word;
                    }
                    else if (word_data.lemma == "NUMBER_")
                    {
                        word_data.lemma = word_data.word;
                    }

                    sent.AddWord(word_data);
                }

                if (ok)
                {
                    yield return sent;
                }
            }
        }
    }
}

