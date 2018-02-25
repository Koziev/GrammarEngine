using System.Collections.Generic;
using System.Linq;


class Builder_Syntax_Neuro
{
    bool IsUnknownLexem(string s)
    {
        return s.Equals("UNKNOWNENTRY", System.StringComparison.InvariantCultureIgnoreCase) ||
               s == "???" ||
               s.Equals("number_", System.StringComparison.InvariantCultureIgnoreCase);
    }

    public Builder_Syntax_Neuro()
    {
    }

    public void Init() { }

    private SolarixGrammarEngineNET.GrammarEngine2 gren;
    public void LoadDictionary(string filepath)
    {
        gren = new SolarixGrammarEngineNET.GrammarEngine2();
        gren.Load(filepath, false);
        Init();
        return;
    }

    public SolarixGrammarEngineNET.GrammarEngine2 GetGrammarEngine() { return gren; }



    System.IO.StreamWriter wrt_train, wrt_test;


    private void CollectEdges(SolarixGrammarEngineNET.SyntaxTreeNode node, Dictionary<int, int> node2parent, Dictionary<int, string> node2word)
    {
        node2word.Add(node.GetWordPosition(), node.GetWord());

        for (int i = 0; i < node.leafs.Count; ++i)
        {
            SolarixGrammarEngineNET.SyntaxTreeNode child = node.leafs[i];
            node2parent.Add(child.GetWordPosition(), node.GetWordPosition());

            CollectEdges(child, node2parent, node2word);
        }
    }

    public bool ProcessSample(SampleData sample, bool train_sample, bool test_sample)
    {
        if (wrt_train == null)
        {
            wrt_train = new System.IO.StreamWriter("syntax_neuro_train.txt");
            wrt_test = new System.IO.StreamWriter("syntax_neuro_test.txt");
        }

        System.IO.StreamWriter wrt = train_sample ? wrt_train : wrt_test;

        if (sample.syntax_tree.Count == 3)
        {
            SolarixGrammarEngineNET.SyntaxTreeNode root = sample.syntax_tree[1];

            Dictionary<int, int> node2parent = new Dictionary<int, int>();
            Dictionary<int, string> node2word = new Dictionary<int, string>();

            node2parent.Add(root.GetWordPosition(), -1);

            CollectEdges(root, node2parent, node2word);

            foreach (int index in node2word.Select(z => z.Key).OrderBy(z => z))
            {
                wrt.WriteLine("{0}\t{1}\t{2}", index, node2word[index], node2parent[index]);
            }

            wrt.WriteLine("");
        }

        return true;
    }


    public void FinishLearning()
    {
        wrt_train.Close();
        wrt_test.Close();

        return;
    }


    public void FinishTesting()
    {

        return;
    }

}

