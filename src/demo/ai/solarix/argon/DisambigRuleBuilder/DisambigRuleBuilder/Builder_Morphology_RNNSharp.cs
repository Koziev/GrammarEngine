using System;
using System.Collections.Generic;
using System.Linq;




class Builder_RNNSharp
{
    private TagBook tags;


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

    public Builder_RNNSharp()
    {
    }


    System.IO.StreamWriter wrt_train, wrt_test, wrt_test2;

    string LANGUAGE = "ru";
    int LanguageID = -1;
    int Constraints = 60000 | (40 << 22); // 1 минута и 40 альтернатив
    int MAX_SUFFIX_LEN;

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

        MAX_SUFFIX_LEN = Program.SUFFIX_LEN == -1 ? 3 : Program.SUFFIX_LEN;

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


    string GetSuffix(string word)
    {
        int dummy;
        if (int.TryParse(word, out dummy))
        {
            return "~" + word[word.Length - 1];
        }
        else if (word.Length > MAX_SUFFIX_LEN)
        {
            return "~" + word.Substring(word.Length - MAX_SUFFIX_LEN).ToLower();
        }
        else
        {
            return word.ToLower();
        }
    }


    int sample_count = 0;
    int n_learn_samples = 0;
    int n_test_samples = 0;

    public bool ProcessSample(SampleData sample)
    {
        if (wrt_train == null)
        {
            wrt_train = new System.IO.StreamWriter("rnnsharp_train.txt");
            wrt_test = new System.IO.StreamWriter("rnnsharp_test.txt");
            wrt_test2 = new System.IO.StreamWriter("rnnsharp_test2.txt");
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

            string suffix = GetSuffix(wordform);

            if (is_training)
            {
                wrt_train.WriteLine("{0}\t{1}\t{2}", wordform.ToLower(), suffix, POS_tag);
            }
            else
            {
                wrt_test.WriteLine("{0}\t{1}\t{2}", wordform.ToLower(), suffix, POS_tag);
                wrt_test2.WriteLine("{0}\t{1}", wordform.ToLower(), suffix);
            }
        }

        if (is_training)
        {
            wrt_train.WriteLine("");
        }
        else
        {
            wrt_test.WriteLine("");
            wrt_test2.WriteLine("");
        }


        return true;
    }


    public void FinishLearning()
    {
        wrt_train.Close();
        wrt_test.Close();
        wrt_test2.Close();

        using (System.IO.StreamWriter wrt = new System.IO.StreamWriter("rnnsharp_tags.txt"))
        {
            for (int i = 0; i < tags.Count(); ++i)
            {
                wrt.WriteLine("{1}", i, tags.GetIdByIndex(i));
            }
        }


        string cmd = string.Format("{0}\\rnnsharp_train.cmd", System.IO.Directory.GetCurrentDirectory());

        System.Diagnostics.Process p = new System.Diagnostics.Process();
        p.StartInfo.Arguments = null;
        p.StartInfo.FileName = cmd;

        Console.WriteLine("Executing {0}", p.StartInfo.FileName);

        bool r = p.Start();
        p.WaitForExit();

        return;
    }



    public void StartTesting()
    {
        string cmd = string.Format("{0}\\rnnsharp_test.cmd", System.IO.Directory.GetCurrentDirectory());

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
