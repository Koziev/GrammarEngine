using System;
using System.Collections.Generic;
using System.Linq;



class LemmatizationTable
{
    // Для каждого тега, включая -1, собираем статистику пар приставок/окончаний
    Dictionary<int, Dictionary<string, Dictionary<string, int>>> tag2lemma_builder = new Dictionary<int, Dictionary<string, Dictionary<string, int>>>();

    public LemmatizationTable()
    { }

    public void Store(int POS_tag, string wordform, string lemma)
    {
        // Ищем общий префикс
        string u_wordform = wordform.ToLower();
        string u_lemma = lemma.ToLower();

        int minlen = Math.Min(u_wordform.Length, u_lemma.Length);
        int prefix_len = 0;
        for (int i = 0; i < minlen; ++i)
        {
            if (u_wordform[i] != u_lemma[i])
                break;
            else
                prefix_len++;
        }

        string cut_front = "";
        string append_front = "";

        string u_wordform2 = u_wordform;

        if (prefix_len == 0 && u_wordform.Length > 5)
        {
            // Сюда попадем для словоформ типа НАИСИЛЬНЕЙШИЙ или ПОРЕЗВЕЕ.
            // Нам надо обнаружить приставки НАИ-, ПО- и так далее.

            int best_pref_len = 0;
            int best_match = 0;
            for (int pref_len = 1; pref_len <= 4; ++pref_len)
            {
                string unprefixed_wordform = u_wordform.Substring(pref_len);
                int match_len = 0;
                for (int k = 0; k < unprefixed_wordform.Length; ++k)
                {
                    if (unprefixed_wordform[k] != u_lemma[k])
                    {
                        break;
                    }

                    match_len++;
                }

                if (match_len > best_match)
                {
                    best_match = match_len;
                    best_pref_len = pref_len;
                }
            }

            /*
                        if( u_wordform.StartsWith("наи") )
                        {
                            Console.WriteLine( "DEBUG" );
                        }*/


            if (best_pref_len > 0)
            {
                cut_front = u_wordform.Substring(0, best_pref_len);
                u_wordform2 = u_wordform.Substring(best_pref_len);

                // Заново оценим совпадающую левую часть
                minlen = Math.Min(u_wordform2.Length, u_lemma.Length);
                prefix_len = 0;
                for (int i = 0; i < minlen; ++i)
                {
                    if (u_wordform2[i] != u_lemma[i])
                        break;
                    else
                        prefix_len++;
                }
            }
        }

        // Добавим 1 символ, чтобы учесть влияние на выбор окончания.
        if (prefix_len > 0)
        {
            prefix_len--;
        }

        string wordform_ending = u_wordform2.Substring(prefix_len);
        string lemma_ending = u_lemma.Substring(prefix_len);

        string wordform_key = cut_front + '|' + wordform_ending;
        string lemma_builder = append_front + '|' + lemma_ending;


        //if (u_wordform.StartsWith("пре") && u_wordform.Contains("ейш") )
       //{
        //    Console.WriteLine("{0}", u_wordform);
       // }

        for (int k = 0; k < 2; ++k)
        {
            int tag = k == 0 ? -1 : POS_tag;

            Dictionary<string, Dictionary<string, int>> table_for_tag;
            if (tag2lemma_builder.TryGetValue(tag, out table_for_tag))
            {
                Dictionary<string, int> lemma_dict;

                if (table_for_tag.TryGetValue(wordform_key, out lemma_dict))
                {
                    int cnt;
                    if (lemma_dict.TryGetValue(lemma_builder, out cnt))
                    {
                        lemma_dict[lemma_builder] = cnt + 1;
                    }
                    else
                    {
                        lemma_dict.Add(lemma_builder, 1);
                    }
                }
                else
                {
                    lemma_dict = new Dictionary<string, int>();
                    lemma_dict.Add(lemma_builder, 1);
                    table_for_tag.Add(wordform_key, lemma_dict);
                }
            }
            else
            {
                table_for_tag = new Dictionary<string, Dictionary<string, int>>();

                Dictionary<string, int> lemma_builder2count = new Dictionary<string, int>();
                lemma_builder2count.Add(lemma_builder, 1);

                table_for_tag.Add(wordform_key, lemma_builder2count);

                tag2lemma_builder.Add(tag, table_for_tag);
            }

        }

        return;
    }


    // для ускорения теперь для каждого окончания словоформы выберем самое частотное
    // правило (добавляемый префикс+окончание леммы).
    Dictionary<int/*tag_id*/, Dictionary<string/*wordform_ending*/, List<Tuple<string/*wordform_prefix*/, string/*lemma_builder*/>>>> Xtag2lemma_builder = new Dictionary<int, Dictionary<string, List<Tuple<string, string>>>>();
    Dictionary<int, Tuple<int/*min_len*/, int/*max_len*/>> Xtag2builder_len = new Dictionary<int, Tuple<int, int>>();
    public void FinishLearning()
    {
        foreach (var tag_data in tag2lemma_builder)
        {
            int tag = tag_data.Key;

            int min_wordform_len = int.MaxValue;
            int max_wordform_len = int.MinValue;

            Dictionary<string/*wordform_ending*/, List<Tuple<string/*wordform_prefix*/, string/*lemma_builder*/>>> wordform2lemma = new Dictionary<string, List<Tuple<string, string>>>();

            foreach (var wordform_data in tag2lemma_builder[tag].OrderByDescending(z => z.Key.Length))
            {
                string wordform_rule = wordform_data.Key;

                string[] tx = wordform_rule.Split('|');
                string wordform_prefix = tx[0];
                string wordform_ending = tx[1];

                min_wordform_len = Math.Min(min_wordform_len, wordform_ending.Length);
                max_wordform_len = Math.Max(max_wordform_len, wordform_ending.Length);

                string best_lemma_builder = wordform_data.Value.OrderByDescending(z => z.Value).First().Key;

                if (wordform2lemma.ContainsKey(wordform_ending))
                {
                    wordform2lemma[wordform_ending].Add(new Tuple<string, string>(wordform_prefix, best_lemma_builder));
                }
                else
                {
                    List<Tuple<string, string>> list = new List<Tuple<string, string>>();
                    list.Add(new Tuple<string, string>(wordform_prefix, best_lemma_builder));
                    wordform2lemma.Add(wordform_ending, list);
                }
            }

            // Отсортируем списки приставка-правило_леммы так, чтобы сначала шли самые длинные приставки, тогда
            // они будут проверятся в первую очередь.
            Dictionary<string/*wordform_ending*/, List<Tuple<string/*wordform_prefix*/, string/*lemma_builder*/>>> wordform2lemma2 = new Dictionary<string, List<Tuple<string, string>>>();
            foreach (var p in wordform2lemma)
            {
                wordform2lemma2.Add(p.Key, p.Value.OrderByDescending(z => z.Item1.Length).ToList());
            }

            Xtag2lemma_builder.Add(tag, wordform2lemma2);
            Xtag2builder_len.Add(tag, new Tuple<int, int>(min_wordform_len, max_wordform_len));
        }

        return;
    }


    public string BuildLemma(int POS_tag, string wordform)
    {
        string u_wordform = wordform.ToLower();

        // TODO переделать алгоритм с учетом того, что теперь детектор включает в себя также приставку, а
        // правило построения леммы включает в себя новую приставку (для случав типа "С ПОЛУСЛОВА" - "ПОЛСЛОВА")

        for (int itag = 0; itag < 2; ++itag)
        {
            // Сначала ищем с учетом POS-тега
            // Если предыдущий вариант не отработал, ищем лемматизацию без учета POS тега.
            int tag = itag == 0 ? POS_tag : -1;

            Dictionary<string /*wordform_ending*/, List<Tuple<string /*wordform_prefix*/, string/*lemma_builder*/>>> result;
            if (Xtag2lemma_builder.TryGetValue(tag, out result))
            {
                Tuple<int, int> len_range = Xtag2builder_len[tag];

                for (int ending_len = len_range.Item2; ending_len >= len_range.Item1; --ending_len)
                {
                    if (u_wordform.Length >= ending_len)
                    {
                        string wordform_ending = u_wordform.Substring(u_wordform.Length - ending_len);

                        List<Tuple<string /*wordform_prefix*/, string /*lemma_builder*/>> rules;
                        if (result.TryGetValue(wordform_ending, out rules))
                        {
                            foreach (var prefix_rule in rules)
                            {
                                string wordform_prefix = prefix_rule.Item1;
                                string lemma_builder = prefix_rule.Item2;

                                if (wordform_prefix.Length == 0 || u_wordform.StartsWith(wordform_prefix))
                                {
                                    string[] rule_parts = lemma_builder.Split('|');
                                    string lemma_prefix = rule_parts[0];
                                    string lemma_ending = rule_parts[1];

                                    string stem = wordform_prefix.Length == 0 ? u_wordform : u_wordform.Substring(wordform_prefix.Length);
                                    string new_lemma = lemma_prefix + stem.Substring(0, stem.Length - ending_len) + lemma_ending;
                                    return new_lemma;
                                }
                            }
                        }

                    }
                }

            }
        }


        return wordform;
    }


    public bool Test(int POS_tag, string wordform, string lemma, out string built_lemma)
    {
        string new_lemma = BuildLemma(POS_tag, wordform);
        built_lemma = new_lemma;
        return new_lemma.Equals(lemma, StringComparison.OrdinalIgnoreCase);
    }

    private static void WriteStr(string str, System.IO.BinaryWriter wrt)
    {
        byte[] w8 = System.Text.Encoding.UTF8.GetBytes(str);
        wrt.Write((byte)w8.Length);
        wrt.Write(w8);
        return;
    }

    public void Store(System.IO.BinaryWriter wrt)
    {
        wrt.Write((Int32)1);

        /*
                Int32 TotalStringLength = 0;
                foreach (var p in Xtag2lemma_builder)
                {
                    foreach (var q in p.Value)
                    {
                        TotalStringLength += (q.Key.Length + 1 + q.Value.Length + 1);
                    }
                }

                wrt.Write(TotalStringLength);
        */

        wrt.Write((Int32)Xtag2builder_len.Count);

        foreach (var p in Xtag2builder_len)
        {
            wrt.Write((Int32)p.Key); // tag
            wrt.Write((byte)p.Value.Item1); // min ending length
            wrt.Write((byte)p.Value.Item2); // max ending length
        }

        wrt.Write((Int32)Xtag2lemma_builder.Count);
        foreach (var p in Xtag2lemma_builder)
        {
            wrt.Write((Int32)p.Key); // tag
            wrt.Write((Int32)p.Value.Count); // кол-во окончаний

            foreach (var q in p.Value)
            {
                string wordform_ending = q.Key;
                WriteStr(wordform_ending, wrt);

                // для каждого окончания словоформы задан список префиксов и соответствущих правил построения леммы
                int n_builder = q.Value.Count;
                wrt.Write((Int32)n_builder);

                foreach (var rule in q.Value)
                {
                    string wordform_prefix = rule.Item1;
                    string[] lemma_builder = rule.Item2.Split('|');
                    string lemma_prefix = lemma_builder[0];
                    string lemma_ending = lemma_builder[1];

                    WriteStr(wordform_prefix, wrt);
                    WriteStr(lemma_prefix, wrt);
                    WriteStr(lemma_ending, wrt);
                }
            }
        }


        return;
    }

    public void PrintInfo()
    {
        Console.WriteLine("LemmatizationTable: number of tags={0}", Xtag2lemma_builder.Count);

        int n_rules = Xtag2lemma_builder.Select(z => z.Value.Select(q => q.Value.Count()).Sum()).Sum();
        Console.WriteLine("LemmatizationTable: total number of rules={0}", n_rules);

        return;
    }
}



class Builder_LEMM_ByPOSTag
{
    private LemmatizationTable table;
    private TagBook tags;

    class CheckData
    {
        public int POS_tag;
        public string wordform;
        public string lemma;
    }

    List<CheckData> check_data_list = new List<CheckData>();


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

    public Builder_LEMM_ByPOSTag()
    {
    }

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

        table = new LemmatizationTable();

        tags = new TagBook("featureset");

        if (LANGUAGE == "ru")
        {
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
  ПРИЛАГАТЕЛЬНОЕ СТЕПЕНЬ:СОКРАЩ

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

            tags.Load(str_tags, gren);
        }
        else if (LANGUAGE == "en")
        {

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

            tags.Load(str_tags, gren);


        }
        else
        {
            throw new NotImplementedException();
        }




        return;
    }


    int n_learn_samples = 0;
    int n_learn_wordforms = 0;

    public bool ProcessSample(SampleData sample)
    {
        n_learn_samples++;

        for (int iword = 1; iword < sample.morphology.Count - 1; ++iword)
        {
            SolarixGrammarEngineNET.SyntaxTreeNode token = sample.morphology[iword];

            string wordform = token.GetWord().ToLower();

            if (wordform.Contains("  "))
            {
                System.Text.RegularExpressions.Regex rx = new System.Text.RegularExpressions.Regex("[ ]{2,}");
                wordform = rx.Replace(wordform, " ");
            }

            string lemma = gren.GetEntryName(token.GetEntryID());
            if (IsUnknownLexem(lemma) || IsNumword(lemma))
                continue;

            int POS_tag = tags.MatchTags(token, gren);

            table.Store(POS_tag, wordform, lemma);
            n_learn_wordforms++;
        }


        return true;
    }


    public void FinishLearning()
    {
        table.FinishLearning();

        using (System.IO.BinaryWriter wr = new System.IO.BinaryWriter(System.IO.File.OpenWrite("lemmatizer.codebook")))
        {
            wr.Write(0);
            wr.Write(0);
            wr.Write(0);
            wr.Write(0);
            tags.Store(wr);
            wr.Write(0); // n_suffix

            wr.Write(0); // START_id
            wr.Write(0); // END_id
            wr.Write(0); // START_tag_id
            wr.Write(0); // END_tag_id
            wr.Write(0); // n_param;

            wr.Write(0); // n_wordform_tag_items
            wr.Write(0); // n_lemma_tag_items
        }

        using (System.IO.BinaryWriter wr = new System.IO.BinaryWriter(System.IO.File.OpenWrite("lemmatizer.model")))
        {
            table.Store(wr);
        }

        return;
    }


    int n_test_samples = 0;

    public void StartTesting()
    {
        int n_error = 0;

        using (System.IO.StreamWriter wrt_err = new System.IO.StreamWriter("errors.txt"))
        {
            foreach (var d in check_data_list)
            {
                string built_lemma = null;
                bool ok = table.Test(d.POS_tag, d.wordform, d.lemma, out built_lemma);
                if (!ok)
                {
                    n_error++;
                    wrt_err.WriteLine("wordform={0} required_lemma={1} built_lemma={2}", d.wordform, d.lemma, built_lemma);
                }
            }
        }

        Console.WriteLine("Error rate={0:G4}%", n_error * 100.0 / (float)check_data_list.Count);



        // Делаем лемматизацию текста из файла для визуального контроля.
        if (System.IO.File.Exists("lemmatizer_test.txt"))
        {
            using (System.IO.StreamReader rdr = new System.IO.StreamReader("lemmatizer_test.txt"))
            {
                using (System.IO.StreamWriter wrt = new System.IO.StreamWriter("lemmatizer_output.txt"))
                {
                    while (!rdr.EndOfStream)
                    {
                        string line = rdr.ReadLine();
                        if (line == null)
                            break;

                        line = line.Trim();
                        if (line.Length == 0)
                            continue;

                        SolarixGrammarEngineNET.AnalysisResults morph = GetGrammarEngine().AnalyzeMorphology(line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY, Constraints);


                        for (int iword = 1; iword < morph.Count - 1; ++iword)
                        {
                            SolarixGrammarEngineNET.SyntaxTreeNode token = morph[iword];

                            string wordform = token.GetWord().ToLower();

                            if (wordform.Contains("  "))
                            {
                                System.Text.RegularExpressions.Regex rx = new System.Text.RegularExpressions.Regex("[ ]{2,}");
                                wordform = rx.Replace(wordform, " ");
                            }

                            string lemma = wordform;
                            if (!IsNumword(lemma))
                            {
                                int POS_tag = tags.MatchTags(token, gren);
                                lemma = table.BuildLemma(POS_tag, wordform);
                            }

                            wrt.Write("{0} ", lemma);

                        }

                        wrt.WriteLine("");
                    }
                }
            }
        }

        return;
    }


    public void Check(SampleData sample)
    {
        n_test_samples++;

        for (int iword = 1; iword < sample.morphology.Count - 1; ++iword)
        {
            SolarixGrammarEngineNET.SyntaxTreeNode token = sample.morphology[iword];

            string wordform = token.GetWord().ToLower();
            string lemma = gren.GetEntryName(token.GetEntryID());
            if (IsUnknownLexem(lemma) || IsNumword(lemma))
                continue;

            CheckData d = new CheckData();
            d.POS_tag = tags.MatchTags(token, gren);
            d.wordform = wordform;
            d.lemma = lemma;

            check_data_list.Add(d);
        }


        return;
    }


    public void PrintTestResults()
    {
        Console.WriteLine("n_learn_wordforms={0}", n_learn_wordforms);
        table.PrintInfo();
        return;
    }


}
