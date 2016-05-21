/*

Для модели Siamese Network готовим набор негативных примеров - некорректных
перефразировок предложения. В качестве исходного материала берем результаты синтаксического
парсинга. Ищем предлождения, в которых есть предлоги или наречия. Переносим предлог 
к другому слова, или вставляем наречие между предлогом и объектов, в итоге получаем
гарантированно недопустимую перефразировку.

Также можно менять местами существительные в паттерне сущ+сущ.род.п
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using SolarixGrammarEngineNET;

class SToken
{
    public int index;
    public string word;
    public string lemma;
    public string part_of_speech;
    public List<string> tags;

    public SToken() { index = -1; tags = new List<string>(); }

    public SToken(int _index, XmlNode n_token)
    {
        index = _index;
        word = n_token.SelectSingleNode("word").InnerText;
        lemma = n_token.SelectSingleNode("lemma").InnerText;

        if (n_token.SelectSingleNode("part_of_speech") != null)
            part_of_speech = n_token.SelectSingleNode("part_of_speech").InnerText;

        tags = new List<string>();
        if (n_token.SelectSingleNode("tags") != null)
        {
            tags.AddRange(n_token.SelectSingleNode("tags").InnerText.Split('|'));
        }
    }

    public override string ToString()
    {
        return word;
    }
}

class SNode
{
    public int index;
    public SToken word;
    public SNode parent;
    public List<string> edge_types = new List<string>();
    public List<SNode> children = new List<SNode>();

    public bool children_vector_ready = false;
    public bool parent_vector_ready = false;

    public override string ToString()
    {
        return word.ToString();
    }


    public void WriteCorpus(System.IO.StreamWriter wrt, string edge_type)
    {
        wrt.WriteLine("<node>");

        wrt.WriteLine("<word>{0}</word>", word.word);

        if (!string.IsNullOrEmpty(edge_type))
        {
            wrt.WriteLine("<link>{0}</link>", edge_type);
        }

        wrt.WriteLine("<tag_sets>");
        wrt.WriteLine("<tag_set>");
        wrt.WriteLine("<part_of_speech>{0}</part_of_speech>", word.part_of_speech);

        foreach (string t in word.tags)
        {
            string[] t2 = t.Split(':');

            if (word.part_of_speech == "ГЛАГОЛ")
            {
                if ("НАКЛОНЕНИЕ ВРЕМЯ ЛИЦО ЧИСЛО РОД".Contains(t2[0]))
                    wrt.WriteLine("<tag>{0}</tag>", t);
            }
            else if (word.part_of_speech == "СУЩЕСТВИТЕЛЬНОЕ")
            {
                if ("ПАДЕЖ ЧИСЛО РОД".Contains(t2[0]))
                    wrt.WriteLine("<tag>{0}</tag>", t);
            }
            else if (word.part_of_speech == "МЕСТОИМЕНИЕ")
            {
                if ("ПАДЕЖ ЧИСЛО РОД ЛИЦО".Contains(t2[0]))
                    wrt.WriteLine("<tag>{0}</tag>", t);
            }
            else if (word.part_of_speech == "ЧИСЛИТЕЛЬНОЕ")
            {
                if ("ПАДЕЖ РОД".Contains(t2[0]))
                    wrt.WriteLine("<tag>{0}</tag>", t);
            }
            else if (word.part_of_speech == "МЕСТОИМ_СУЩ")
            {
                if ("ПАДЕЖ".Contains(t2[0]))
                    wrt.WriteLine("<tag>{0}</tag>", t);
            }
            else if (word.part_of_speech == "ПРИЛАГАТЕЛЬНОЕ")
            {
                if ("ПАДЕЖ ЧИСЛО РОД ОДУШ ФОРМА СТЕПЕНЬ".Contains(t2[0]))
                    wrt.WriteLine("<tag>{0}</tag>", t);
            }
            else if (word.part_of_speech == "НАРЕЧИЕ")
            {
                if ("СТЕПЕНЬ".Contains(t2[0]))
                    wrt.WriteLine("<tag>{0}</tag>", t);
            }
        }

        wrt.WriteLine("</tag_set>");
        wrt.WriteLine("</tag_sets>");

        if (children != null && children.Count > 0)
        {
            wrt.WriteLine("<children>");

            List<KeyValuePair<int, int>> index = new List<KeyValuePair<int, int>>();
            for (int i = 0; i < children.Count; ++i)
            {
                index.Add(new KeyValuePair<int, int>(i, children[i].word.index));
            }

            foreach (var i in index.OrderBy(z => z.Value))
            {
                children[i.Key].WriteCorpus(wrt, edge_types[i.Key]);
            }

            wrt.WriteLine("</children>");
        }

        wrt.WriteLine("</node>");
    }

}

class Sentence
{
    string text;
    List<SToken> tokens;
    public SNode root;
    List<SNode> nodes;

    public Sentence(XmlNode n_sent)
    {
        text = n_sent.SelectSingleNode("text").InnerText;

        // токены
        tokens = new List<SToken>();
        int token_index = 0;
        foreach (XmlNode n_token in n_sent.SelectNodes("tokens/token"))
        {
            SToken t = new SToken(token_index, n_token);
            tokens.Add(t);
            token_index++;
        }

        // дерево зависимостей
        List<int> root_index = new List<int>();
        Dictionary<int, int> child2parent = new Dictionary<int, int>();
        Dictionary<KeyValuePair<int, int>, string> edge_type = new Dictionary<KeyValuePair<int, int>, string>();
        Dictionary<int, List<int>> parent2child = new Dictionary<int, List<int>>();

        foreach (XmlNode n_token in n_sent.SelectNodes("syntax_tree/node"))
        {
            int child_index = int.Parse(n_token["token"].InnerText);

            if (n_token.Attributes["is_root"] != null && n_token.Attributes["is_root"].Value == "true")
                root_index.Add(child_index);
            else
            {
                int parent_index = int.Parse(n_token["parent"].InnerText);
                child2parent.Add(child_index, parent_index);

                edge_type.Add(new KeyValuePair<int, int>(child_index, parent_index), n_token["link_type"].InnerText);

                List<int> child_idx;
                if (!parent2child.TryGetValue(parent_index, out child_idx))
                {
                    child_idx = new List<int>();
                    parent2child.Add(parent_index, child_idx);
                }

                child_idx.Add(child_index);
            }
        }

        nodes = new List<SNode>();
        for (int inode = 0; inode < tokens.Count; ++inode)
        {
            SNode n = new SNode();
            n.index = inode;
            n.word = tokens[inode];
            nodes.Add(n);
        }

        // проставим родителей и детей в каждом узле
        for (int inode = 0; inode < nodes.Count; ++inode)
        {
            SNode node = nodes[inode];

            if (!root_index.Contains(node.index))
            {
                SNode parent_node = nodes[child2parent[node.index]];
                node.parent = parent_node;

                parent_node.children.Add(node);
                parent_node.edge_types.Add(edge_type[new KeyValuePair<int, int>(node.index, parent_node.index)]);
            }
            else
            {
                root = node;
            }
        }
    }

    public string GetText()
    {
        return text;
    }


    public override string ToString()
    {
        return text;
    }

    public SNode GetNodeByIndex(int index)
    {
        return nodes[index];
    }

    public void WriteCorpus(System.IO.StreamWriter wrt)
    {
        wrt.WriteLine("\n\n<sample>");
        wrt.WriteLine("<text>{0}</text>", text);
        wrt.WriteLine("<syntax>");

        root.WriteCorpus(wrt, null);

        wrt.WriteLine("</syntax>");
        wrt.WriteLine("</sample>");
        return;
    }

    public List<SToken> Tokens { get { return tokens; } }

    public IEnumerable<SNode> Nodes { get { return nodes; } }
}


class Sentences : IDisposable
{
    System.IO.StreamReader rdr;

    public Sentences(string parsing_path)
    {
        rdr = new System.IO.StreamReader(parsing_path);
    }

    void IDisposable.Dispose()
    {
        rdr.Close();
    }

    Sentence fetched;

    public bool Next()
    {
        fetched = null;

        while (!rdr.EndOfStream)
        {
            string line = rdr.ReadLine();
            if (line == null)
                break;

            if (line.StartsWith("<sentence"))
            {
                System.Text.StringBuilder xmlbuf = new StringBuilder();
                xmlbuf.Append("<?xml version='1.0' encoding='utf-8' ?>");
                xmlbuf.Append("<dataroot>");
                xmlbuf.Append(line);

                while (!rdr.EndOfStream)
                {
                    line = rdr.ReadLine();
                    if (line == null)
                        break;

                    xmlbuf.Append(line);

                    if (line == "</sentence>")
                        break;
                }

                xmlbuf.Append("</dataroot>");

                XmlDocument xml = new XmlDocument();

                xml.LoadXml(xmlbuf.ToString());

                XmlNode n_sent = xml.DocumentElement.SelectSingleNode("sentence");

                fetched = new Sentence(n_sent);

                return true;
            }
        }

        return false;
    }

    public Sentence GetFetched()
    {
        return fetched;
    }
}



class TreeTemplateNode
{
    List<string> parts_of_speech;

    List<string> edge_type;
    List<TreeTemplateNode> children;

    public TreeTemplateNode()
    {
    }

    public void Parse(StringParser.StringTokenizer rdr)
    {
        parts_of_speech = new List<string>();
        edge_type = new List<string>();
        children = new List<TreeTemplateNode>();

        rdr.read_it("[");

        rdr.read_it("class");
        rdr.read_it(":");
        while (!rdr.eof())
        {
            string pos = rdr.read();
            parts_of_speech.Add(pos);
            if (!rdr.probe(","))
                break;
        }

        rdr.read_it("]");

        return;
    }

    public bool Match(SNode node)
    {
        if (!parts_of_speech.Contains(node.word.part_of_speech))
            return false;

        for (int i = 0; i < children.Count; ++i)
        {
            bool child_found = false;

            for (int j = 0; j < node.children.Count; ++j)
                if (node.edge_types[j].Equals(edge_type[i], StringComparison.CurrentCultureIgnoreCase))
                {
                    if (children[i].Match(node.children[j]))
                    {
                        child_found = true;
                        break;
                    }
                }

            if (!child_found)
                return false;
        }

        return true;
    }
}

class TreeTemplate
{
    TreeTemplateNode root;

    public TreeTemplate(string str)
    {
        Parse(str);
    }


    private void Parse(string str)
    {
        StringParser.StringTokenizer rdr = new StringParser.StringTokenizer(str);
        root = new TreeTemplateNode();
        root.Parse(rdr);
    }


    public bool Match(Sentence sent)
    {
        return root.Match(sent.root);
    }
}


class Program
{
    static string Tidy(string sent)
    {
        string sent3 = sent.Replace(" !", "!").Replace(" ,", ",").Replace(" ?", "?").Replace(" :", ":");

        if (sent3.EndsWith(" ."))
            sent3 = sent3.Substring(0, sent3.Length - 2) + ".";
        else if (sent3.EndsWith(" ..."))
            sent3 = sent3.Substring(0, sent3.Length - 4) + "...";
        else if (sent3.EndsWith(" ;"))
            sent3 = sent3.Substring(0, sent3.Length - 2) + ";";

        return sent3;
    }

    static System.IO.StreamWriter wrt;
    static int sample_count = 0;
    static void StoreSample(Sentence sent, List<SToken> tokens)
    {
        string sent3 = Tidy(string.Join(" ", tokens.Select(z => z.index == 0 ? z.word.ToLower() : z.word).ToArray()));

        wrt.WriteLine("{0}\t{1}", sent.GetText(), sent3);
        sample_count++;
        if ((sample_count % 1000) == 0)
        {
            Console.Write("{0} \r", sample_count);
        }
    }


    static void Main(string[] args)
    {
        string parsed_sentences = @"F:\Corpus\parsing\ru\SENT4.parsing.txt";
        string result_path = @"f:\tmp\negative3.dat";
        string dict_path = @"e:\MVoice\lem\bin-windows64\dictionary.xml";

        // Загрузим морфологический словарь, он нам понадобится для смены падежей слов.
        SolarixGrammarEngineNET.GrammarEngine2 gren = new SolarixGrammarEngineNET.GrammarEngine2();
        gren.Load(dict_path, true);


        string[] files = null;
        if (System.IO.Directory.Exists(parsed_sentences))
            files = System.IO.Directory.GetFiles(parsed_sentences, "*.parsing.txt");
        else
            files = new string[1] { parsed_sentences };

        List<TreeTemplate> templates = new List<TreeTemplate>();
        templates.Add(new TreeTemplate("[class:ГЛАГОЛ]( <PREPOS_ADJUNCT>[class:ПРЕДЛОГ].<OBJECT>[class:МЕСТОИМЕНИЕ,СУЩЕСТВИТЕЛЬНОЕ,ПРИЛАГАТЕЛЬНОЕ] )"));

        sample_count = 0;

        using (wrt = new System.IO.StreamWriter(result_path))
        {
            foreach (string file in files)
            {
                Console.WriteLine("Processing {0}...", file);

                using (Sentences src = new Sentences(file))
                {
                    while (src.Next())
                    {
                        Sentence sent = src.GetFetched();
                        if (sent.root != null)
                        {
                            #region AdjNounAdjNoun

                            for (int i1 = 0; i1 < sent.Tokens.Count; ++i1)
                            {
                                if (sent.Tokens[i1].part_of_speech == "СУЩЕСТВИТЕЛЬНОЕ")
                                {
                                    SNode node1 = sent.Nodes.Where(z => z.index == i1).First();
                                    if (node1.edge_types.Count > 0)
                                    {
                                        int edge1 = -1;

                                        for (int j1 = 0; j1 < node1.edge_types.Count; ++j1)
                                        {
                                            if (node1.edge_types[j1] == "ATTRIBUTE")
                                            {
                                                if (sent.Tokens[node1.children[j1].index].part_of_speech == "ПРИЛАГАТЕЛЬНОЕ")
                                                {
                                                    edge1 = j1;
                                                    break;
                                                }
                                            }
                                        }

                                        if (edge1 != -1)
                                        {
                                            // Нашли первое существительное с атрибутирующим прилагательным.
                                            int noun_ie1 = gren.FindEntry(sent.Tokens[i1].word, gren.FindPartOfSpeech(sent.Tokens[i1].part_of_speech));

                                            SToken adj1 = sent.Tokens[node1.children[edge1].index];
                                            adj1.word = adj1.word.ToLower();


                                            for (int i2 = i1 + 2; i2 < sent.Tokens.Count; ++i2)
                                            {
                                                if (sent.Tokens[i2].part_of_speech == "СУЩЕСТВИТЕЛЬНОЕ")
                                                {
                                                    int noun_ie2 = gren.FindEntry(sent.Tokens[i2].word, gren.FindPartOfSpeech(sent.Tokens[i2].part_of_speech));

                                                    if (noun_ie1 != noun_ie2)
                                                    {
                                                        int gender1 = gren.GetEntryAttrState(noun_ie1, SolarixGrammarEngineNET.GrammarEngineAPI.GENDER_ru);
                                                        int gender2 = gren.GetEntryAttrState(noun_ie2, SolarixGrammarEngineNET.GrammarEngineAPI.GENDER_ru);
                                                        if (gender1 == gender2)
                                                        {
                                                            string number1 = sent.Tokens[i1].tags.Where(z => z.StartsWith("ЧИСЛО:")).First().Split(':')[1];
                                                            string number2 = sent.Tokens[i2].tags.Where(z => z.StartsWith("ЧИСЛО:")).First().Split(':')[1];

                                                            if (number1 == number2)
                                                            {
                                                                SNode node2 = sent.Nodes.Where(z => z.index == i2).First();
                                                                if (node2.edge_types.Count > 0)
                                                                {
                                                                    int edge2 = -1;

                                                                    for (int j2 = 0; j2 < node2.edge_types.Count; ++j2)
                                                                    {
                                                                        if (node2.edge_types[j2] == "ATTRIBUTE")
                                                                        {
                                                                            if (sent.Tokens[node2.children[j2].index].part_of_speech == "ПРИЛАГАТЕЛЬНОЕ")
                                                                            {
                                                                                edge2 = j2;
                                                                                break;
                                                                            }
                                                                        }
                                                                    }

                                                                    if (edge2 != -1)
                                                                    {
                                                                        // Нашли второе существительное с атрибутирующим прилагательным.
                                                                        SToken adj2 = sent.Tokens[node2.children[edge2].index];
                                                                        adj2.word = adj2.word.ToLower();


                                                                        // Сгенерируем предложение, в котором эти прилагательные поменяны местами.
                                                                        List<SToken> tokens2 = new List<SToken>();
                                                                        foreach (SToken t in sent.Tokens)
                                                                        {
                                                                            if (t.index == adj1.index)
                                                                            {
                                                                                tokens2.Add(adj2);
                                                                            }
                                                                            else if (t.index == adj2.index)
                                                                            {
                                                                                tokens2.Add(adj1);
                                                                            }
                                                                            else
                                                                            {
                                                                                tokens2.Add(t);
                                                                            }
                                                                        }

                                                                        StoreSample(sent, tokens2);
                                                                    }
                                                                    else
                                                                    {
                                                                        // у второго существительного нет атрибутирующего прилагательного.
                                                                        // перенесем прилагательное от первого ко второму существительному.

                                                                        List<SToken> tokens2 = new List<SToken>();
                                                                        foreach (SToken t in sent.Tokens)
                                                                        {
                                                                            if (t.index == adj1.index)
                                                                            {
                                                                                continue;
                                                                            }
                                                                            else if (t.index == i2)
                                                                            {
                                                                                tokens2.Add(adj1);
                                                                                tokens2.Add(sent.Tokens[i2]);
                                                                            }
                                                                            else
                                                                            {
                                                                                tokens2.Add(t);
                                                                            }
                                                                        }

                                                                        StoreSample(sent, tokens2);

                                                                    }

                                                                }

                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            #endregion AdjNounAdjNoun


                            #region NounNoun
                            // Ищем два существительных, связанных в конструкцию родительного дополнения:
                            // "восход солнца"
                            // Генерируем предложение с перестановкой слов и сменой падежей:
                            // "солнце восхода"
                            foreach (SNode n1 in sent.Nodes)
                            {
                                SToken t1 = sent.Tokens[n1.index]; // восход
                                if (t1.part_of_speech == "СУЩЕСТВИТЕЛЬНОЕ")
                                {
                                    if (n1.children.Count > 0)
                                    {
                                        int gen_edge_index = n1.edge_types.IndexOf("RIGHT_GENITIVE_OBJECT");
                                        if (gen_edge_index != -1)
                                        {
                                            SToken t2 = sent.Tokens[n1.children[gen_edge_index].index]; // солнца

                                            if (gen_edge_index != -1 && t2.part_of_speech == "СУЩЕСТВИТЕЛЬНОЕ")
                                            {
                                                List<SToken> tokens2 = new List<SToken>();
                                                bool t12_ok = true;
                                                foreach (SToken t in sent.Tokens)
                                                {
                                                    if (t.index == t1.index)
                                                    {
                                                        // сюда вставляем слово "солнца" и меняем его падеж на падеж слова t
                                                        string t_case = t.tags.Where(z => z.StartsWith("ПАДЕЖ:")).First().Split(':')[1];
                                                        string t_number = t2.tags.Where(z => z.StartsWith("ЧИСЛО:")).First().Split(':')[1];
                                                        int ie_t2 = gren.FindEntry(t2.lemma, gren.FindPartOfSpeech(t2.part_of_speech));
                                                        if (ie_t2 != -1)
                                                        {
                                                            List<int> coords = new List<int>();
                                                            List<int> states = new List<int>();
                                                            coords.Add(SolarixGrammarEngineNET.GrammarEngineAPI.CASE_ru);
                                                            states.Add(gren.FindState(SolarixGrammarEngineNET.GrammarEngineAPI.CASE_ru, t_case));
                                                            coords.Add(SolarixGrammarEngineNET.GrammarEngineAPI.NUMBER_ru);
                                                            states.Add(gren.FindState(SolarixGrammarEngineNET.GrammarEngineAPI.NUMBER_ru, t_number));
                                                            List<string> forms = gren.GenerateWordforms(ie_t2, coords, states);
                                                            if (forms.Count > 0)
                                                            {
                                                                string new_word = gren.RestoreCasing(ie_t2, forms[0]);
                                                                SToken new_t = new SToken();
                                                                new_t.index = t.index;
                                                                new_t.word = new_word;
                                                                new_t.lemma = t.lemma;
                                                                new_t.part_of_speech = t1.part_of_speech;
                                                                tokens2.Add(new_t);
                                                            }
                                                            else
                                                            {
                                                                t12_ok = false;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            t12_ok = false;
                                                        }
                                                    }
                                                    else if (t.index == t2.index)
                                                    {
                                                        // сюда вставляем слово "восход" и меняем его падеж на родительный
                                                        string t_number = t1.tags.Where(z => z.StartsWith("ЧИСЛО:")).First().Split(':')[1];
                                                        int ie_t1 = gren.FindEntry(t1.lemma, gren.FindPartOfSpeech(t1.part_of_speech));
                                                        if (ie_t1 != -1)
                                                        {
                                                            List<int> coords = new List<int>();
                                                            List<int> states = new List<int>();
                                                            coords.Add(SolarixGrammarEngineNET.GrammarEngineAPI.CASE_ru);
                                                            states.Add(SolarixGrammarEngineNET.GrammarEngineAPI.GENITIVE_CASE_ru);
                                                            coords.Add(SolarixGrammarEngineNET.GrammarEngineAPI.NUMBER_ru);
                                                            states.Add(gren.FindState(SolarixGrammarEngineNET.GrammarEngineAPI.NUMBER_ru, t_number));
                                                            List<string> forms = gren.GenerateWordforms(ie_t1, coords, states);
                                                            if (forms.Count > 0)
                                                            {
                                                                string new_word = gren.RestoreCasing(ie_t1, forms[0]);
                                                                SToken new_t = new SToken();
                                                                new_t.index = t.index;
                                                                new_t.word = new_word;
                                                                new_t.lemma = t.lemma;
                                                                new_t.part_of_speech = t.part_of_speech;
                                                                tokens2.Add(new_t);
                                                            }
                                                            else
                                                            {
                                                                t12_ok = false;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            t12_ok = false;
                                                        }

                                                    }
                                                    else
                                                    {
                                                        tokens2.Add(t);
                                                    }
                                                }

                                                if (t12_ok)
                                                {
                                                    StoreSample(sent, tokens2);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            #endregion NounNoun


                            #region PrepObject
                            // Ищем предлог.
                            foreach (SToken token_prepos in sent.Tokens)
                            {
                                if (token_prepos.part_of_speech == "ПРЕДЛОГ")
                                {
                                    // Нашли предлог. Теперь перенесем его в другую позицию.
                                    List<Tuple<SToken, float>> tokens2 = sent.Tokens.Where(z => z.index != token_prepos.index).Select(z => new Tuple<SToken, float>(z, z.index)).ToList();

                                    foreach (var t2 in tokens2.Where(z => z.Item1.index != token_prepos.index + 1))
                                    {
                                        // Ставим предлог в позицию ПЕРЕД токеном t2 и генерируем предложение.
                                        List<Tuple<SToken, float>> tokens3 = new List<Tuple<SToken, float>>();
                                        tokens3.AddRange(tokens2);
                                        tokens3.Add(new Tuple<SToken, float>(token_prepos, t2.Item2 - 0.5f));

                                        StoreSample(sent, tokens3.OrderBy(z => z.Item2).Select(z => z.Item1).ToList());
                                    }
                                }
                            }
                            #endregion PrepObject


                            /*
                                                        foreach (TreeTemplate t in templates)
                                                        {
                                                            if (t.Match(sent))
                                                            {
                                                            }
                                                        }
                            */
                        }
                    }
                }
            }
        }

        Console.WriteLine("\nsample_count={0}", sample_count);

        return;
    }
}
