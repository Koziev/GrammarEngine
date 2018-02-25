using System;
using System.Collections.Generic;
using System.Linq;


class TagMatcher
{
    private string source;
    private static int seq_id = 0;

    private int id;
    private string lexeme;
    private List<int> id_lemma;
    List<string> entry_names;

    List<int> pos; // OR список id частей речи 
    List<string> pos_names;
    List<SolarixGrammarEngineNET.CoordPair> pairs;

    List<int> entry_pos; // если распознается конкретная словарная статья, то здесь сохраним id ее части речи для работы метода MatchPartOfSpeech


    public bool IsStartTag()
    {
        if (!string.IsNullOrEmpty(lexeme))
            return false;

        if (id_lemma == null || id_lemma.Count != 1)
            return false;

        if (pos_names == null || pos_names.Count != 1)
            return false;

        if (!pos_names[0].Equals("BETH", StringComparison.OrdinalIgnoreCase))
            return false;

        if (pairs != null && pairs.Count > 0)
            return false;

        if (entry_names == null || entry_names.Count != 1)
            return false;

        if (!entry_names[0].Equals("BEGIN", StringComparison.OrdinalIgnoreCase))
            return false;

        return true;
    }


    public bool IsEndTag()
    {
        if (!string.IsNullOrEmpty(lexeme))
            return false;

        if (id_lemma == null || id_lemma.Count != 1)
            return false;

        if (pos_names == null || pos_names.Count != 1)
            return false;

        if (!pos_names[0].Equals("BETH", StringComparison.OrdinalIgnoreCase))
            return false;

        if (pairs != null && pairs.Count > 0)
            return false;

        if (entry_names == null || entry_names.Count != 1)
            return false;

        if (!entry_names[0].Equals("END", StringComparison.OrdinalIgnoreCase))
            return false;

        return true;
    }

    public void Store(System.IO.BinaryWriter wr)
    {
        wr.Write(id);

        if (string.IsNullOrEmpty(lexeme))
            wr.Write(0);
        else
        {
            byte[] l8 = System.Text.Encoding.UTF8.GetBytes(lexeme);
            wr.Write(l8.Length);
            wr.Write(l8);
        }

        if (id_lemma == null)
            wr.Write(0);
        else
        {
            wr.Write(id_lemma.Count);
            foreach (int x in id_lemma)
                wr.Write(x);
        }

        if (pos == null)
            wr.Write(0);
        else
        {
            wr.Write(pos.Count);
            foreach (int x in pos)
                wr.Write(x);
        }

        if (pairs == null)
            wr.Write(0);
        else
        {
            wr.Write(pairs.Count);
            foreach (SolarixGrammarEngineNET.CoordPair p in pairs)
            {
                wr.Write(p.CoordID);
                wr.Write(p.StateID);
            }
        }

        return;
    }

    public TagMatcher(string line, SolarixGrammarEngineNET.GrammarEngine2 gren)
    {
        source = line.Trim();
        id = ++seq_id;

        string[] toks = source.Split(" ".ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
        foreach (string tok in toks)
        {
            if (tok[0] == '\'' && tok[tok.Length - 1] == '\'')
            {
                lexeme = tok.Substring(1, tok.Length - 2);
            }
            else if (tok[0] == '"' && tok[tok.Length - 1] == '"')
            {
                lexeme = tok.Substring(1, tok.Length - 2);
            }
            else
            {
                if (tok.IndexOf(':') == -1)
                {
                    string pos_name = tok.Trim();
                    int id_class = gren.FindPartOfSpeech(pos_name);
                    if (id_class != -1)
                    {
                        if (pos == null)
                        {
                            pos = new List<int>();
                            pos_names = new List<string>();
                        }

                        pos.Add(id_class);
                        pos_names.Add(pos_name);
                    }
                    else
                    {
                        int state = 1;

                        string t = tok.Trim();

                        if (t.StartsWith("~"))
                        {
                            t = t.Substring(1);
                            state = 0;
                        }

                        int id_coord = gren.FindCoord(t);
                        if (id_coord == -1)
                            throw new ApplicationException(string.Format("Can not find coord [{0}]", tok));

                        if (gren.CountCoordStates(id_coord) != 0)
                            throw new ApplicationException(string.Format("[{0}] is not bistable", tok));

                        if (pairs == null)
                            pairs = new List<SolarixGrammarEngineNET.CoordPair>();

                        SolarixGrammarEngineNET.CoordPair p;
                        p.CoordID = id_coord;
                        p.StateID = state;
                        pairs.Add(p);
                    }
                }
                else
                {
                    string[] t3 = tok.Split(':');
                    string coord_name = t3[0].Trim();
                    string state_name = t3[1].Trim();

                    int id_class = gren.FindPartOfSpeech(coord_name);
                    if (id_class != -1)
                    {
                        id_lemma = new List<int>();
                        entry_names = new List<string>();
                        pos_names = new List<string>();
                        pos_names.Add(coord_name);

                        int ip = state_name.IndexOf('{');
                        string ename = state_name.Substring(0, ip);
                        int ekey = gren.FindEntry(ename, id_class);

                        if (ekey == -1)
                        {
                            throw new ApplicationException(string.Format("Can not find word entry {0}:{1}", coord_name, ename));
                        }

                        id_lemma.Add(ekey);
                        entry_names.Add(ename);

                        if (entry_pos == null)
                        {
                            entry_pos = new List<int>();
                        }

                        if (!entry_pos.Contains(id_class))
                            entry_pos.Add(id_class);
                    }
                    else
                    {
                        int id_coord = gren.FindCoord(coord_name);
                        if (id_coord == -1)
                            throw new ApplicationException(string.Format("Can not find coord [{0}]", coord_name));

                        int id_state = -1;
                        if (gren.CountCoordStates(id_coord) == 0)
                        {
                            id_state = int.Parse(state_name);
                            if (id_state < 0 || id_state > 1)
                                throw new ApplicationException(string.Format("Invalid state name {0} for bistable coord {1}", state_name, coord_name));
                        }
                        else
                        {
                            id_state = gren.FindState(id_coord, state_name);
                            if (id_state == -1)
                                throw new ApplicationException(string.Format("Can not find state [{0}:{1}]", coord_name, state_name));
                        }

                        if (pairs == null)
                            pairs = new List<SolarixGrammarEngineNET.CoordPair>();

                        SolarixGrammarEngineNET.CoordPair p;
                        p.CoordID = id_coord;
                        p.StateID = id_state;
                        pairs.Add(p);
                    }
                }
            }
        }
    }

    public override string ToString()
    {
        return source;
    }

    public bool SameSource(string src)
    {
        return source.Equals(src, StringComparison.InvariantCultureIgnoreCase);
    }

    public bool MatchPartOfSpeech(int id_class)
    {
        if (pos != null)
            return pos.Contains(id_class);

        if (entry_pos != null)
            return entry_pos.Contains(id_class);

        return false;
    }

    public bool MatchPartOfSpeech(TagMatcher t)
    {
        if (pos != null && t.pos != null)
        {
            foreach (int p2 in t.pos)
                if (pos.Contains(p2))
                    return true;

            return false;
        }
        else if (pos != null && t.entry_pos != null)
        {
            foreach (int p2 in t.entry_pos)
                if (pos.Contains(p2))
                    return true;

            return false;
        }

        throw new ApplicationException();
    }


    public bool Match(SolarixGrammarEngineNET.SyntaxTreeNode token, SolarixGrammarEngineNET.GrammarEngine2 gren)
    {
        if (lexeme != null)
            return token.GetWord().Equals(lexeme, StringComparison.InvariantCultureIgnoreCase);

        if (id_lemma != null)
        {
            for (int iver = 0; iver < token.VersionCount(); ++iver)
            {
                int ekey = token.GetVersionEntryID(iver);
                if (id_lemma.Contains(ekey))
                    return true;
            }

            return false;
        }

        if (pos != null)
        {
            bool pos_matched = false;

            for (int iver = 0; iver < token.VersionCount(); ++iver)
            {
                int ekey = token.GetVersionEntryID(iver);
                if (ekey != -1)
                {
                    int id_class = gren.GetEntryClass(ekey);
                    pos_matched = pos.Contains(id_class);
                    if (pos_matched)
                        break;
                }
            }

            if (!pos_matched)
                return false;
        }

        if (pairs != null && pairs.Count > 0)
        {
            bool a_version_matched = false;

            for (int iver = 0; iver < token.VersionCount(); ++iver)
            {
                bool ver_ok = true;

                foreach (SolarixGrammarEngineNET.CoordPair p in pairs)
                    if (!token.VersionContains(iver, p))
                    {
                        ver_ok = false;
                        break;
                    }

                if (ver_ok)
                {
                    a_version_matched = true;
                    break;
                }
            }

            return a_version_matched;
        }

        return true;
    }



    public bool Match(SolarixGrammarEngineNET.SyntaxTreeNode proj, int iver, SolarixGrammarEngineNET.GrammarEngine2 gren)
    {
        if (lexeme != null)
            return proj.GetWord().Equals(lexeme, StringComparison.InvariantCultureIgnoreCase);

        if (id_lemma != null)
        {
            int ekey = proj.GetVersionEntryID(iver);
            if (id_lemma.Contains(ekey))
                return true;

            return false;
        }

        if (pos != null)
        {
            bool pos_matched = false;

            int ekey = proj.GetVersionEntryID(iver);
            if (ekey != -1)
            {
                int id_class = gren.GetEntryClass(ekey);
                pos_matched = pos.Contains(id_class);
            }

            if (!pos_matched)
                return false;
        }

        if (pairs != null)
        {
            bool contains_all_required_pairs = true;
            foreach (SolarixGrammarEngineNET.CoordPair p in pairs)
                if (!proj.VersionContains(iver, p))
                {
                    contains_all_required_pairs = false;
                    break;
                }

            if (!contains_all_required_pairs)
                return false;
        }

        return true;
    }

    public void Difference(TagMatcher m, List<int> coord_diff_list)
    {
        foreach (var p in pairs)
        {
            if (!m.pairs.Contains(p))
                coord_diff_list.Add(p.CoordID);
        }

        foreach (var p in m.pairs)
        {
            if (!pairs.Contains(p) && !coord_diff_list.Contains(p.CoordID))
                coord_diff_list.Add(p.CoordID);
        }

        return;
    }


    public int GetId() { return id; }
}


class TagBook
{
    string name;
    List<TagMatcher> matchers;

    Dictionary<int, TagMatcher> id2matcher;
    Dictionary<int, int> id2index; // преобразование id в индекс, начинающийся с 0.
    Dictionary<int, int> index2id;

    public TagBook(string _name)
    {
        name = _name;
    }

    public int Count() { return matchers.Count; }

    public void Load(string lines, SolarixGrammarEngineNET.GrammarEngine2 gren)
    {
        matchers = new List<TagMatcher>();
        id2matcher = new Dictionary<int, TagMatcher>();
        id2index = new Dictionary<int, int>();
        index2id = new Dictionary<int, int>();

        foreach (string line in lines.Split('\n'))
        {
            string l = line.Trim();
            if (!string.IsNullOrEmpty(l))
            {
                TagMatcher m = new TagMatcher(line, gren);
                matchers.Add(m);
                id2matcher.Add(m.GetId(), m);
                id2index.Add(m.GetId(), matchers.Count - 1);
                index2id.Add(matchers.Count - 1, m.GetId());
            }
        }

        return;
    }

    public void Store(System.IO.BinaryWriter wr)
    {
        wr.Write(matchers.Count);
        foreach (TagMatcher m in matchers)
        {
            m.Store(wr);
        }

        return;
    }

    public int GetIndexById(int id) { return id == -1 ? -1 : id2index[id]; }

    public int GetIdByIndex(int index) { return index == -1 ? index : index2id[index]; }

    public TagMatcher this[int id] { get { return id2matcher[id]; } }

    public int FindStartTagID()
    {
        for (int i = 0; i < matchers.Count; ++i)
        {
            if (matchers[i].IsStartTag())
                return matchers[i].GetId();
        }

        return -1;
    }

    public int FindEndTagID()
    {
        for (int i = 0; i < matchers.Count; ++i)
        {
            if (matchers[i].IsEndTag())
                return matchers[i].GetId();
        }

        return -1;
    }

    public int MatchTags(SolarixGrammarEngineNET.SyntaxTreeNode token, SolarixGrammarEngineNET.GrammarEngine2 gren)
    {
        foreach (TagMatcher m in matchers)
        {
            if (m.Match(token, gren))
                return m.GetId();
        }

        int entry_id = token.GetEntryID();
        int pos_id = gren.GetEntryClass(entry_id);
        string part_of_speech = gren.GetClassName(pos_id);
        string tags = string.Join(" ", token.GetPairs().Select(z => string.Format("{0}={1}", gren.GetCoordName(z.CoordID), gren.GetCoordStateName(z.CoordID, z.StateID))).ToArray());
        string msg = string.Format("Can not find tag for {0} {{ {1} {2} }}", token.GetWord(), part_of_speech, tags);

        throw new ApplicationException(msg);
    }

    public int MatchTags(SolarixGrammarEngineNET.SyntaxTreeNode proj, int iproj, SolarixGrammarEngineNET.GrammarEngine2 gren)
    {
        foreach (TagMatcher m in matchers)
        {
            if (m.Match(proj, iproj, gren))
            {
                // ---~~~~~ DEBUG ~~~---
#if DEBUG
                string matcher = m.ToString();
                string form = "";

                int npair = SolarixGrammarEngineNET.GrammarEngine.sol_GetNodeVerPairsCount(proj.hNode, iproj);
                for (int j = 0; j < npair; ++j)
                {
                    int id_coord = SolarixGrammarEngineNET.GrammarEngine.sol_GetNodeVerPairCoord(proj.hNode, iproj, j);
                    int id_state = SolarixGrammarEngineNET.GrammarEngine.sol_GetNodeVerPairState(proj.hNode, iproj, j);

                    string coord_name = gren.GetCoordName(id_coord);

                    string state_name = null;
                    if (gren.CountCoordStates(id_coord) == 0)
                        state_name = id_state.ToString();
                    else
                        state_name = gren.GetCoordStateName(id_coord, id_state);

                    form += string.Format(" {0}:{1}", coord_name, state_name);
                }
#endif
                // ---~~~~~ ..... ~~~---

                return m.GetId();
            }
        }

        return -1;
    }


    public int FindBySrc(string src)
    {
        foreach (TagMatcher m in matchers)
            if (m.SameSource(src))
                return m.GetId();

        return -1;
    }

    public string Print()
    {
        System.Text.StringBuilder buf = new System.Text.StringBuilder();

        foreach (var t in matchers)
        {
            buf.AppendLine(t.ToString());
        }

        return buf.ToString();
    }
}




struct NGram2
{
    public int tags0, tags1;

    public NGram2(int _t0, int _t1) { tags0 = _t0; tags1 = _t1; }

    public override bool Equals(object obj)
    {
        NGram2 n2 = (NGram2)obj;
        return n2.tags0 == tags0 && n2.tags1 == tags1;
    }

    public override int GetHashCode()
    {
        return tags0 ^ (tags1 << 8);
    }
}

class NGram2Freq : IComparer<KeyValuePair<NGram2, int>>
{

    public int Compare(KeyValuePair<NGram2, int> x, KeyValuePair<NGram2, int> y)
    {
        if (x.Key.tags0 > y.Key.tags0)
            return 1;
        else if (x.Key.tags0 < y.Key.tags0)
            return -1;
        else if (x.Value < y.Value)
            return 1;
        else if (x.Value > y.Value)
            return -1;
        else
            return 0;
    }
}





struct NGram3
{
    public int tags0, tags1, tags2;

    public NGram3(int _t0, int _t1, int _t2) { tags0 = _t0; tags1 = _t1; tags2 = _t2; }

    public override bool Equals(object obj)
    {
        NGram3 n3 = (NGram3)obj;
        return n3.tags0 == tags0 && n3.tags1 == tags1 && n3.tags2 == tags2;
    }

    public override int GetHashCode()
    {
        return tags0 ^ (tags1 << 8) ^ (tags2 << 16);
    }
}



class NGram3Freq : IComparer<KeyValuePair<NGram3, int>>
{

    public int Compare(KeyValuePair<NGram3, int> x, KeyValuePair<NGram3, int> y)
    {
        if (x.Key.tags0 > y.Key.tags0)
            return 1;
        else if (x.Key.tags0 < y.Key.tags0)
            return -1;
        else if (x.Key.tags1 > y.Key.tags1)
            return 1;
        else if (x.Key.tags1 < y.Key.tags1)
            return -1;
        else if (x.Value < y.Value)
            return 1;
        else if (x.Value > y.Value)
            return -1;
        else
            return 0;
    }
}



struct NGram4
{
    public int tags0, tags1, tags2, tags3;

    public NGram4(int _t0, int _t1, int _t2, int _t3) { tags0 = _t0; tags1 = _t1; tags2 = _t2; tags3 = _t3; }

    public override bool Equals(object obj)
    {
        NGram4 n4 = (NGram4)obj;
        return n4.tags0 == tags0 && n4.tags1 == tags1 && n4.tags2 == tags2 && n4.tags3 == tags3;
    }

    public override int GetHashCode()
    {
        return tags0 ^ (tags1 << 8) ^ (tags2 << 16) ^ (tags3 << 24);
    }
}



class NGram4Freq : IComparer<KeyValuePair<NGram4, int>>
{

    public int Compare(KeyValuePair<NGram4, int> x, KeyValuePair<NGram4, int> y)
    {
        if (x.Key.tags0 > y.Key.tags0)
            return 1;
        else if (x.Key.tags0 < y.Key.tags0)
            return -1;
        else if (x.Key.tags1 > y.Key.tags1)
            return 1;
        else if (x.Key.tags1 < y.Key.tags1)
            return -1;
        else if (x.Key.tags2 > y.Key.tags2)
            return 1;
        else if (x.Key.tags2 < y.Key.tags2)
            return -1;
        else if (x.Value < y.Value)
            return 1;
        else if (x.Value > y.Value)
            return -1;
        else
            return 0;
    }
}



struct Int2
{
    int x, y;
    public Int2(int _x, int _y) { x = _x; y = _y; }
}

struct Int3
{
    int x, y, z;
    public Int3(int _x, int _y, int _z) { x = _x; y = _y; z = _z; }
}


class PercentFormatter
{
    public static string Percent(int top, int denominator)
    {
        float f = top * 100.0F / denominator;
        return f.ToString("##0.##", System.Globalization.CultureInfo.GetCultureInfo("ru-RU"));
    }
}

class VerbPOS
{
    public static bool IsVerb(int pos)
    {
        return pos == SolarixGrammarEngineNET.GrammarEngineAPI.VERB_ru ||
               pos == SolarixGrammarEngineNET.GrammarEngineAPI.IMPERSONAL_VERB_ru ||
               pos == SolarixGrammarEngineNET.GrammarEngineAPI.GERUND_2_ru ||
               pos == SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru ||
               pos == SolarixGrammarEngineNET.GrammarEngineAPI.VERB_ru ||
               pos == SolarixGrammarEngineNET.GrammarEngineAPI.IMPERSONAL_VERB_ru ||
               pos == SolarixGrammarEngineNET.GrammarEngineAPI.GERUND_2_ru ||
               pos == SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru;
    }

}