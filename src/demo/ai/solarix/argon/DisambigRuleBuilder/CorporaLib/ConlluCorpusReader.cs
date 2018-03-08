using System;
using System.Collections.Generic;
using System.Linq;

namespace CorporaLib
{
    public class ConlluCorpusReader : ICorpusReader
    {
        private string corpus_path;

        // Индексы столбцов в корпусе определяются конкретной реализацией формата,
        // для Universal Dependencies и корпуса ДИАЛОГ MorphoEval они разные.
        private int word_column = -1;
        private int lemma_column = -1;
        private int class_column = -1;
        private int tags_column = -1;


        public ConlluCorpusReader(string corpus_path,
            int word_column,
            int lemma_column,
            int class_column,
            int tags_column)
        {
            this.corpus_path = corpus_path;
            this.word_column = word_column;
            this.lemma_column = lemma_column;
            this.class_column = class_column;
            this.tags_column = tags_column;
        }


        public IEnumerable<SentenceData> Read(SolarixGrammarEngineNET.GrammarEngine2 gren)
        {
            int beth_class = gren.FindPartOfSpeech("BETH");
            int entry_begin_id = gren.FindEntry("BEGIN", beth_class);
            int entry_end_id = gren.FindEntry("END", beth_class);

            string[] files = System.IO.Directory.GetFiles(System.IO.Path.GetDirectoryName(corpus_path), System.IO.Path.GetFileName(corpus_path));

            foreach (string path1 in files)
            {
                using (System.IO.StreamReader rdr = new System.IO.StreamReader(path1))
                {
                    List<ConlluItem> items = new List<ConlluItem>();
                    while (!rdr.EndOfStream)
                    {
                        string line = rdr.ReadLine();
                        if (line == null) break;

                        if (string.IsNullOrEmpty(line))
                        {
                            if (items.Count > 0)
                            {
                                string sample = string.Join(" ", items.Select(z => z.word));

                                SentenceData sent = new SentenceData(sample);

                                bool all_ok = true; // если не сможем выполнить конверию морфологической разметки, то 
                                                    // выставим этот флаг в false и не будем возвращать объект SentenceData.
                                int word_index = 0;

                                SolarixGrammarEngineNET.AnalysisResults tokenization = gren.AnalyzeMorphology(sample, -1, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY, 0);

                                if (tokenization.Count - 2 == items.Count)
                                {
                                    // Добавить <BEGIN>
                                    WordData wd_begin = new WordData();
                                    wd_begin.word_index = 0;
                                    wd_begin.word = "BEGIN";
                                    wd_begin.entry_id = entry_begin_id;
                                    wd_begin.part_of_speech = beth_class;
                                    wd_begin.all_projs = tokenization[word_index];
                                    sent.AddWord(wd_begin);

                                    word_index++;

                                    foreach (var item in items)
                                    {
                                        var projs = SolarixGrammarEngineNET.GrammarEngine.sol_ProjectWord(gren.GetEngineHandle(), item.word, 1);

                                        int selected_proj = 0;

                                        int nproj = SolarixGrammarEngineNET.GrammarEngine.sol_CountProjections(projs);
                                        if (nproj > 1)
                                        {
                                            List<Tuple<int, int>> proj_scores = new List<Tuple<int, int>>();

                                            int required_class = -1;
                                            List<Tuple<int, int>> required_tags = new List<Tuple<int, int>>();

                                            if (item.ud_class == "NOUN" || item.ud_class == "PROPN")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.NOUN_ru;
                                            }
                                            else if (item.ud_class == "PUNCT")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.PUNCTUATION_class;
                                            }
                                            else if (item.ud_class == "ADJ" || item.ud_class == "DET")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.ADJ_ru;
                                            }
                                            else if (item.ud_class == "AUX" || item.ud_class == "VERB")
                                            {
                                                if (item.Contains("VerbForm ", "Inf"))
                                                {
                                                    required_class = SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru;
                                                }
                                                else if (item.Contains("VerbForm", "Trans"))
                                                {
                                                    required_class = SolarixGrammarEngineNET.GrammarEngineAPI.GERUND_2_ru;
                                                }
                                                else
                                                {
                                                    required_class = SolarixGrammarEngineNET.GrammarEngineAPI.VERB_ru;
                                                }
                                            }
                                            else if (item.ud_class == "ADP")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.PREPOS_ru;
                                            }
                                            else if (item.ud_class == "ADV")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.ADVERB_ru;
                                            }
                                            else if (item.ud_class == "PRON")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.PRONOUN_ru;
                                            }
                                            else if (item.ud_class == "PART")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.PARTICLE_ru;
                                            }
                                            else if (item.ud_class == "NUM")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.NUMBER_CLASS_ru;
                                            }
                                            else if (item.ud_class == "CONJ" || item.ud_class == "SCONJ")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.CONJ_ru;
                                            }
                                            else if (item.ud_class == "INTJ")
                                            {
                                                required_class = SolarixGrammarEngineNET.GrammarEngineAPI.PARTICIPLE_ru;
                                            }
                                            else
                                            {
                                                all_ok = false;
                                                break;
                                            }


                                            foreach (string tv in item.ud_tags)
                                            {
                                                int coord_id = -1;
                                                int state_id = -1;

                                                string[] tv2 = tv.Split('=');
                                                string tag = tv2[0].Trim();
                                                string val = tv2[1].Trim();

                                                if (tag == "Animacy")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.FORM_ru;
                                                    if (val == "Inan")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.INANIMATIVE_FORM_ru;
                                                    }
                                                    else
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.ANIMATIVE_FORM_ru;
                                                    }
                                                }


                                                if (tag == "Case")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.CASE_ru;
                                                    if (val == "Nom")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.NOMINATIVE_CASE_ru;
                                                    }
                                                    else if (val == "Acc")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.NOMINATIVE_CASE_ru;
                                                    }
                                                    else if (val == "Gen")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.GENITIVE_CASE_ru;
                                                    }
                                                    else if (val == "Ins")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.INSTRUMENTAL_CASE_ru;
                                                    }
                                                    else if (val == "Loc")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.PREPOSITIVE_CASE_ru;
                                                    }
                                                    else if (val == "Dat")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.DATIVE_CASE_ru;
                                                    }
                                                    else if (val == "Par")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.PARTITIVE_CASE_ru;
                                                    }
                                                    else if (val == "Voc")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.VOCATIVE_CASE_ru;
                                                    }
                                                    else
                                                    {
                                                        all_ok = false;
                                                        break;
                                                    }
                                                }

                                                if (tag == "Gender")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.GENDER_ru;

                                                    if (val == "Fem")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.FEMININE_GENDER_ru;
                                                    }
                                                    else if (val == "Masc")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.MASCULINE_GENDER_ru;
                                                    }
                                                    else if (val == "Neut")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.NEUTRAL_GENDER_ru;
                                                    }
                                                    else
                                                    {
                                                        all_ok = false;
                                                        break;
                                                    }
                                                }

                                                // Number = Sing
                                                if (tag == "Number")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.NUMBER_ru;
                                                    if (val == "Sing")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.SINGULAR_NUMBER_ru;
                                                    }
                                                    else
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.PLURAL_NUMBER_ru;
                                                    }
                                                }

                                                // Degree=Pos
                                                if (tag == "Degree")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.COMPAR_FORM_ru;

                                                    if (val == "Pos")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.ATTRIBUTIVE_FORM_ru;
                                                    }
                                                    else if (val == "Sup")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.SUPERLATIVE_FORM_ru;
                                                    }
                                                    else if (val == "Cmp")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.COMPARATIVE_FORM_ru;
                                                    }
                                                }

                                                if (tag == "Variant" && val == "Brev")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.SHORTNESS_ru;
                                                    state_id = 1;
                                                }


                                                if (tag == "Person")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.PERSON_ru;
                                                    if (val == "1")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.PERSON_1_ru;
                                                    }
                                                    else if (val == "2")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.PERSON_2_ru;
                                                    }
                                                    else if (val == "3")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.PERSON_3_ru;
                                                    }
                                                }

                                                if (tag == "Tense")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.TENSE_ru;
                                                    if (val == "Pres")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.PRESENT_ru;
                                                    }
                                                    else if (val == "Past")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.PAST_ru;
                                                    }
                                                    else if (val == "Fut")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.FUTURE_ru;
                                                    }
                                                }

                                                if (tag == "Mood")
                                                {
                                                    coord_id = SolarixGrammarEngineNET.GrammarEngineAPI.VERB_FORM_ru;
                                                    if (val == "Ind")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.VB_INF_ru;
                                                    }
                                                    else if (val == "Imp")
                                                    {
                                                        state_id = SolarixGrammarEngineNET.GrammarEngineAPI.VB_ORDER_ru;
                                                    }
                                                }

                                                if (coord_id != -1 && state_id != -1)
                                                {
                                                    required_tags.Add(Tuple.Create(coord_id, state_id));
                                                }
                                            }

                                            for (int iproj = 0; iproj < nproj; ++iproj)
                                            {
                                                int proj_score = 0;
                                                int entry_id = SolarixGrammarEngineNET.GrammarEngine.sol_GetIEntry(projs, iproj);
                                                int class_id = gren.GetEntryClass(entry_id);
                                                if (class_id == required_class)
                                                {
                                                    proj_score++;
                                                }

                                                foreach (var required_tag in required_tags)
                                                {
                                                    int state_id = SolarixGrammarEngineNET.GrammarEngine.sol_GetProjCoordState(gren.GetEngineHandle(), projs, iproj, required_tag.Item1);

                                                    if (state_id == required_tag.Item2)
                                                    {
                                                        proj_score++;
                                                    }
                                                }
                                                proj_scores.Add(Tuple.Create(iproj, proj_score));
                                            }

                                            selected_proj = proj_scores.OrderByDescending(z => z.Item2).Select(z => z.Item1).First();
                                        }



                                        // теперь выбранную проекцию слова selected_proj векторизуем
                                        WordData word_data = new WordData();
                                        word_data.word = item.word;
                                        word_data.word_index = word_index;
                                        word_data.all_projs = tokenization[word_index];
                                        word_data.entry_id = SolarixGrammarEngineNET.GrammarEngine.sol_GetIEntry(projs, selected_proj);
                                        word_data.part_of_speech = gren.GetEntryClass(word_data.entry_id);

                                        // Лемму определяем в несколько шагов.
                                        // Прежде всего пытаемся взять наименование словарной статьи в лексиконе Solarix.
                                        word_data.lemma = gren.GetEntryName(word_data.entry_id).ToLower();

                                        // Если получили наменование статьи "???", то значит это несловарный элемент и
                                        // надо брать лемму из корпуса.
                                        if (word_data.lemma == "???")
                                        {
                                            word_data.lemma = item.ud_lemma;
                                        }
                                        else if (word_data.lemma == "NUMBER_")
                                        {
                                            // Для чисел берем исходный токен в качестве леммы.
                                            word_data.lemma = item.word;
                                        }


                                        for (int j = 0; j < SolarixGrammarEngineNET.GrammarEngine.sol_GetProjCoordCount(gren.GetEngineHandle(), projs, selected_proj); ++j)
                                        {
                                            int coord_id = SolarixGrammarEngineNET.GrammarEngine.sol_GetProjCoordId(gren.GetEngineHandle(), projs, selected_proj, j);
                                            int state_id = SolarixGrammarEngineNET.GrammarEngine.sol_GetProjStateId(gren.GetEngineHandle(), projs, selected_proj, j);
                                            word_data.tags.Add(Tuple.Create(coord_id, state_id));
                                        }

                                        sent.AddWord(word_data);

                                        SolarixGrammarEngineNET.GrammarEngine.sol_DeleteProjections(projs);

                                        // DEBUG
                                        //Console.WriteLine("\nDEBUG word={0}\ncorpus:{1}({2})\nselected:{3}", item.word, item.ud_class, string.Join(" ", item.ud_tags), GetTokenMorph(word_data, gren));

                                        word_index++;
                                    }

                                    // Добавить <END>
                                    WordData wd_end = new WordData();
                                    wd_end.word_index = word_index;
                                    wd_end.word = "END";
                                    wd_end.entry_id = entry_end_id;
                                    wd_end.part_of_speech = beth_class;
                                    wd_end.all_projs = tokenization[word_index];
                                    sent.AddWord(wd_end);

                                    // Для отладки - выведем текстовое представление тегов в выбранной проекции.



                                    if (all_ok)
                                    {
                                        yield return sent;
                                    }
                                }
                            }

                            items.Clear();
                        }
                        else
                        {
                            string[] tx = line.Trim().Split('\t');

                            ConlluItem item = new ConlluItem();
                            item.word = tx[word_column];
                            item.ud_lemma = tx[lemma_column];
                            item.ud_class = tx[class_column];
                            item.ud_tags = tx[tags_column].Split('|')
                                .Select(z => z.Split('='))
                                .Where(z => z.Length == 2)
                                .Select(z => z[0].Trim() + '=' + z[1].Trim())
                                .ToArray();

                            items.Add(item);
                        }
                    }
                }
            }
        }

        private string GetTokenMorph(WordData token, SolarixGrammarEngineNET.GrammarEngine2 gren)
        {
            string part_of_speech = gren.GetClassName(token.part_of_speech);
            string tags = string.Join(" ", token.GetTags().Select(z => string.Format("{0}={1}", gren.GetCoordName(z.Item1), gren.GetCoordStateName(z.Item1, z.Item2))).ToArray());
            return part_of_speech + "(" + tags + ")";
        }
    }
}
