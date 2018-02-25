using System;
using System.Collections.Generic;
using System.Linq;




class Builder_WordShingles
{
    private TagBook tags;
    private WordEncoder encoder;

    // CRFSuite
    // FlexCRFs
    // CRF-ADF
    string format = "CRFSuite";

    string TRAIN_FILENAME = "wordshingles_train.txt";
    string TEST_FILENAME = "wordshingles_test.txt";


    bool IsUnknownLexem(string s)
    {
        return s.Equals("UNKNOWNENTRY", System.StringComparison.InvariantCultureIgnoreCase) ||
               s == "???" ||
               s.Equals("number_", System.StringComparison.InvariantCultureIgnoreCase);
    }

    bool IsNumword(string s)
    {
        return char.IsDigit(s[0]);
    }

    public Builder_WordShingles()
    {
    }


    System.IO.StreamWriter wrt_train, wrt_test;

    string LANGUAGE = "ru";
    int LanguageID = -1;
    int Constraints = 60000 | (40 << 22); // 1 минута и 40 альтернатив

    public void ChangeModelParams(List<string> model_params)
    {
        foreach (string p in model_params)
        {
            string[] tx = p.Split('=');
            string pname = tx[0].Trim();
            string pval = tx[1].Trim();

            switch (pname.ToUpper())
            {
                case "LANGUAGE": LANGUAGE = pval; break;
                case "FORMAT": format = pval; break;

                default: throw new ApplicationException(string.Format("Unknown model param {0}={1}", pname, pval));
            }
        }
    }

    public SolarixGrammarEngineNET.GrammarEngine2 gren;

    public SolarixGrammarEngineNET.GrammarEngine2 GetGrammarEngine() { return gren; }
    public void LoadDictionary(string filepath)
    {
        gren = new SolarixGrammarEngineNET.GrammarEngine2();
        gren.Load(filepath, false);
        Init();
        return;
    }

    public void Init()
    {
        if (LANGUAGE == "ru")
        {
            LanguageID = SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE;
        }
        else if (LANGUAGE == "en")
        {
            LanguageID = SolarixGrammarEngineNET.GrammarEngineAPI.ENGLISH_LANGUAGE;
        }

        encoder = new WordEncoder();
        encoder.load(@"e:\MVoice\lem\demo\ai\solarix\argon\WordShingles\bin\Debug");



        tags = new TagBook("featureset");

        if (LANGUAGE == "ru")
        {
            #region ru
            string str_tags =
          @"
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:СР
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:МН

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:СР
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:МН

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ЗВАТ

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:СР
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:МН

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПАРТ ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПАРТ ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПАРТ ЧИСЛО:ЕД РОД:СР

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ ОДУШ:ОДУШ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:СР
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:МН ОДУШ:ОДУШ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:МН

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:СР
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:МН

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:СР
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:МЕСТ ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:МЕСТ ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:МЕСТ ЧИСЛО:ЕД РОД:СР

  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:СЧЕТН ЧИСЛО:ЕД РОД:ЖЕН
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:СЧЕТН ЧИСЛО:ЕД РОД:МУЖ
  СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:СЧЕТН ЧИСЛО:ЕД РОД:СР

  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:МУЖ
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:СР
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:МН

  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:ЖЕН
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:МУЖ
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:СР
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:МН

  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:МУЖ
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:СР
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:МН

  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:ЖЕН
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ ОДУШ:ОДУШ
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:СР
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:МН
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:МН ОДУШ:ОДУШ

  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:ЖЕН
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:МУЖ
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:СР
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:МН

  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:ЖЕН
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:МУЖ
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:СР
  ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН

  ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ РОД:ЖЕН ЧИСЛО:ЕД
  ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ РОД:МУЖ ЧИСЛО:ЕД
  ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ РОД:СР ЧИСЛО:ЕД
  ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ ЧИСЛО:МН

  ПРИЛАГАТЕЛЬНОЕ СТЕПЕНЬ:СРАВН

  МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:1
  МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:МН ЛИЦО:1

  МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:2
  МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:МН ЛИЦО:2

  МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:3 РОД:МУЖ
  МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:3 РОД:ЖЕН
  МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:3 РОД:СР
  МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:МН ЛИЦО:3

  МЕСТОИМЕНИЕ ПАДЕЖ:РОД ЧИСЛО:ЕД
  МЕСТОИМЕНИЕ ПАДЕЖ:РОД ЧИСЛО:МН

  МЕСТОИМЕНИЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД
  МЕСТОИМЕНИЕ ПАДЕЖ:ТВОР ЧИСЛО:МН

  МЕСТОИМЕНИЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД
  МЕСТОИМЕНИЕ ПАДЕЖ:ВИН ЧИСЛО:МН

  МЕСТОИМЕНИЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД
  МЕСТОИМЕНИЕ ПАДЕЖ:ДАТ ЧИСЛО:МН

  МЕСТОИМЕНИЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД
  МЕСТОИМЕНИЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН

  МЕСТОИМ_СУЩ ПАДЕЖ:ИМ
  МЕСТОИМ_СУЩ ПАДЕЖ:РОД
  МЕСТОИМ_СУЩ ПАДЕЖ:ТВОР
  МЕСТОИМ_СУЩ ПАДЕЖ:ВИН
  МЕСТОИМ_СУЩ ПАДЕЖ:ДАТ
  МЕСТОИМ_СУЩ ПАДЕЖ:ПРЕДЛ

  ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ИМ
  ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:РОД
  ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ТВОР
  ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ВИН
  ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ДАТ
  ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ
  ЧИСЛИТЕЛЬНОЕ

ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:МУЖ ЧИСЛО:ЕД
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:ЖЕН ЧИСЛО:ЕД
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР ЧИСЛО:ЕД
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ЛИЦО:1 ЧИСЛО:ЕД
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ЛИЦО:1 ЧИСЛО:МН
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ЛИЦО:2 ЧИСЛО:ЕД
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ЛИЦО:2 ЧИСЛО:МН
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ЛИЦО:3 ЧИСЛО:ЕД
ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ ЛИЦО:3 ЧИСЛО:МН

  ГЛАГОЛ НАКЛОНЕНИЕ:ИЗЪЯВ
  ГЛАГОЛ НАКЛОНЕНИЕ:ПОБУД
  ГЛАГОЛ

  ВВОДНОЕ
  БЕЗЛИЧ_ГЛАГОЛ
  NUM_WORD
  ИНФИНИТИВ
  ДЕЕПРИЧАСТИЕ
  ПРЕДЛОГ
  ПОСЛЕЛОГ
  СОЮЗ
  ЧАСТИЦА
  ПУНКТУАТОР
  НАРЕЧИЕ
  BETH:BEGIN{}
  BETH:END{}
  UNKNOWNENTRIES
  ПРИТЯЖ_ЧАСТИЦА
  ЕДИНИЦА_ИЗМЕРЕНИЯ
  ВОСКЛ_ГЛАГОЛ

  ПРЕФИКС_СОСТАВ_ПРИЛ
  ПРЕФИКС_СОСТАВ_СУЩ
  ";
            #endregion ru

            tags.Load(str_tags, gren);
        }
        else if (LANGUAGE == "en")
        {
            #region en
            string str_tags =
          @"
   ENG_VERB
   ENG_ARTICLE
   ENG_NOUN
   ENG_ADVERB
   ENG_ADJECTIVE
   ENG_PREP
   ENG_CONJ
   ENG_PRONOUN
   ENG_POSTPOS
   ENG_NUMERAL
   ENG_INTERJECTION
   ENG_POSSESSION
   ENG_COMPOUND_PRENOUN
   ENG_COMPOUND_PREADJ
   ENG_COMPOUND_PREVERB
   ENG_COMPOUND_PREADV
   ENG_PARTICLE

  NUM_WORD
  ПУНКТУАТОР
  BETH:BEGIN{}
  BETH:END{}
  UNKNOWNENTRIES
";
            #endregion en

            tags.Load(str_tags, gren);
        }
        else
        {
            throw new NotImplementedException();
        }

        return;
    }


    int sample_count = 0;
    int n_learn_samples = 0;
    int n_test_samples = 0;

    public bool ProcessSample(SampleData sample)
    {
        if (wrt_train == null)
        {
            wrt_train = new System.IO.StreamWriter(TRAIN_FILENAME);
            wrt_test = new System.IO.StreamWriter(TEST_FILENAME);
        }


        bool is_training = false;
        if ((sample_count++ % 10) == 0)
        {
            is_training = false;
            n_test_samples++;
        }
        else
        {
            is_training = true;
            n_learn_samples++;
        }


        for (int iword = 1; iword < sample.morphology.Count - 1; ++iword)
        {
            SolarixGrammarEngineNET.SyntaxTreeNode token = sample.morphology[iword];

            string wordform = token.GetWord().ToLower();

            if (wordform.Contains("  "))
            {
                System.Text.RegularExpressions.Regex rx = new System.Text.RegularExpressions.Regex("[ ]{2,}");
                wordform = rx.Replace(wordform, " ");
            }

            int POS_tag = tags.MatchTags(token, gren);

            System.Text.StringBuilder features = new System.Text.StringBuilder();

            for (int word_pos = -Program.CONTEXT_SPAN; word_pos <= Program.CONTEXT_SPAN; ++word_pos)
            {
                int iwordi = iword + word_pos;
                if (iwordi >= 0 && iwordi < sample.morphology.Count)
                {
                    if (iwordi == 0)
                    {
                        features.Append(string.Format("\tU_BEGIN[{0}]", word_pos));
                    }
                    else if (iwordi == sample.morphology.Count - 1)
                    {
                        features.Append(string.Format("\tU_END[{0}]", word_pos));
                    }
                    else
                    {
                        SolarixGrammarEngineNET.SyntaxTreeNode tokeni = sample.morphology[iwordi];

                        string wordformi = tokeni.GetWord().ToLower();

                        if (wordformi.Contains("  "))
                        {
                            System.Text.RegularExpressions.Regex rx = new System.Text.RegularExpressions.Regex("[ ]{2,}");
                            wordformi = rx.Replace(wordformi, " ");
                        }

                        float[] v = encoder.EncodeWord(wordformi);

                        int n_nonzero = 0;
                        for (int i = 0; i < v.Length; ++i)
                        {
                            if (v[i] > 0)
                            {
                                features.AppendFormat("\tU[{0},{1}]", word_pos, i);
                                n_nonzero++;
                            }
                        }

                        if (n_nonzero == 0)
                        {
                            features.Append(string.Format("\tUNO_FEATURES[{0}]", word_pos));
                        }
                    }
                }
            }

            if (is_training)
            {
                if (format == "CRFSuite" || format == "CRF_ADF")
                {
                    wrt_train.WriteLine("{0}\t{1}\t{2}", wordform.ToLower(), features.ToString().Trim(), POS_tag);
                }
                else if (format == "FlexCRFs")
                {
                    wrt_train.WriteLine("{0}\t{1}", features.ToString().Trim(), POS_tag);
                }
                else
                {
                    throw new NotImplementedException();
                }
            }
            else
            {
                if (format == "CRFSuite" || format == "CRF_ADF")
                {
                    wrt_test.WriteLine("{0}\t{1}\t{2}", wordform.ToLower(), features.ToString().Trim(), POS_tag);
                }
                else if (format == "FlexCRFs")
                {
                    wrt_test.WriteLine("{0}\t{1}", features.ToString().Trim(), POS_tag);
                }
                else
                {
                    throw new NotImplementedException();
                }
            }
        }

        if (is_training)
        {
            wrt_train.WriteLine("");
        }
        else
        {
            wrt_test.WriteLine("");
        }


        return true;
    }


    public void FinishLearning()
    {
        wrt_train.Close();
        wrt_test.Close();

        if (format == "CRF_ADF")
        {
            string train_file = TRAIN_FILENAME;
            string test_file = TEST_FILENAME;

            // Конвертанем файл в формат CRF-ADF
            Dictionary<string, int> tag2index = new Dictionary<string, int>();
            Dictionary<string, int> feature2index = new Dictionary<string, int>();

            foreach (string p in new string[] { train_file, test_file })
            {
                Console.WriteLine("Collecting features and tags in {0}", p);
                using (System.IO.StreamReader rdr = new System.IO.StreamReader(p))
                {
                    int line_count = 0;

                    while (!rdr.EndOfStream)
                    {
                        string line = rdr.ReadLine();
                        if (line == null)
                        {
                            break;
                        }

                        line_count++;
                        if ((line_count % 10000) == 0)
                        {
                            Console.Write("{0}\r", line_count);
                        }


                        if (line.Length > 0)
                        {
                            string[] toks = line.Split('\t');
                            string tag = toks[toks.Length - 1];

                            if (!tag2index.ContainsKey(tag))
                            {
                                tag2index.Add(tag, tag2index.Count);
                            }

                            foreach (string feature in toks.Skip(1).Take(toks.Length - 2))
                            {
                                if (!feature2index.ContainsKey(feature))
                                {
                                    feature2index.Add(feature, feature2index.Count);
                                }
                            }
                        }

                    }
                }
            }

            int n_feature = feature2index.Count;
            int n_result_tag = tag2index.Count;

            for (int k = 0; k < 2; ++k)
            {
                string filename_stem = k == 0 ? "train" : "test";
                string src_filename = k == 0 ? train_file : test_file;

                Console.WriteLine("Converting {0} to CRF ADF format", src_filename);

                using (System.IO.StreamReader rdr = new System.IO.StreamReader(src_filename))
                {
                    System.IO.StreamWriter wrt_f = new System.IO.StreamWriter(string.Format("f{0}.txt", filename_stem));
                    System.IO.StreamWriter wrt_g = new System.IO.StreamWriter(string.Format("g{0}.txt", filename_stem));

                    wrt_f.WriteLine("{0}\n", n_feature);
                    wrt_g.WriteLine("{0}\n", n_result_tag);

                    int words_in_sent = 0;

                    int line_count = 0;
                    while (!rdr.EndOfStream)
                    {
                        string line = rdr.ReadLine();
                        if (line == null) break;

                        line_count++;
                        if ((line_count % 10000) == 0)
                        {
                            Console.Write("{0}\r", line_count);
                        }

                        if (line.Length == 0)
                        {
                            wrt_f.WriteLine("");
                            wrt_g.WriteLine("\n");
                            words_in_sent = 0;
                        }
                        else
                        {
                            string[] toks = line.Split('\t');

                            /*
                                                    foreach (string f in toks.Skip(1).Take(toks.Length - 2))
                                                    {
                                                        if (!feature2index.ContainsKey(f))
                                                        {
                                                            Console.WriteLine("line={0} feature={1}", line, f);
                                                            return;
                                                        }
                                                    }
                            */

                            wrt_f.WriteLine("{0}", string.Join(",", toks.Skip(1).Take(toks.Length - 2).Select(z => feature2index[z].ToString()).ToArray()));

                            if (words_in_sent > 0)
                            {
                                wrt_g.Write(",");
                            }

                            wrt_g.Write("{0}", tag2index[toks[toks.Length - 1]]);
                            words_in_sent++;
                        }
                    }

                    wrt_f.Close();
                    wrt_g.Close();
                }
            }



        }
        else if (format == "CRFSuite")
        {
            Console.WriteLine("Start training CRFSuite...");
            string input_file = string.Format("{0}\\wordshingles_train.txt", System.IO.Directory.GetCurrentDirectory());
            string cmd = string.Format("{0}\\wordshingles_train.cmd", System.IO.Directory.GetCurrentDirectory());

            System.Diagnostics.Process p = new System.Diagnostics.Process();
            p.StartInfo.Arguments = input_file;
            p.StartInfo.FileName = cmd;

            Console.WriteLine("Executing {0} {1}", p.StartInfo.FileName, p.StartInfo.Arguments);

            bool r = p.Start();
            p.WaitForExit();
        }

        return;
    }



    public void StartTesting()
    {
        string cmd = string.Format("{0}\\crfsuite_test.cmd", System.IO.Directory.GetCurrentDirectory());

        System.Diagnostics.Process p = new System.Diagnostics.Process();
        p.StartInfo.Arguments = null;
        p.StartInfo.FileName = cmd;

        Console.WriteLine("Executing {0}", p.StartInfo.FileName);

        bool r = p.Start();
        p.WaitForExit();

        int n_token = 0;
        int n_error = 0;
        using (System.IO.StreamReader rdr = new System.IO.StreamReader("rnnsharp_result.txt"))
        using (System.IO.StreamReader rdr2 = new System.IO.StreamReader("rnnsharp_test.txt"))
        {
            while (!rdr.EndOfStream)
            {
                string result_line = rdr.ReadLine();
                if (result_line == null)
                    break;

                if (result_line.StartsWith("<s>") || result_line.StartsWith("</s>"))
                {
                    continue;
                }

                string goal_line = rdr2.ReadLine();

                if (result_line.Length > 0)
                {
                    n_token++;

                    string[] goal_tx = goal_line.Split('\t');
                    string goal_tag = goal_tx[goal_tx.Length - 1];

                    string[] yield_tx = result_line.Split('\t');
                    string yield_tag = yield_tx[yield_tx.Length - 1];

                    if (goal_tag != yield_tag)
                    {
                        n_error++;
                    }
                }
            }
        }

        Console.WriteLine("Tag error rate={0}%", 100.0 * n_error / (double)n_token);


        return;
    }

    public void PrintTestResults()
    {
        return;
    }


}
