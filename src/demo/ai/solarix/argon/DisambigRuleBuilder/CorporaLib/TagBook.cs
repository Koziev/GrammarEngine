using System;
using System.Collections.Generic;
using System.Linq;

namespace CorporaLib
{
    public class TagBook
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

        public int MatchTags(WordData token, SolarixGrammarEngineNET.GrammarEngine2 gren)
        {
            foreach (TagMatcher m in matchers)
            {
                if (m.Match(token, gren))
                    return m.GetId();
            }

            int entry_id = token.GetEntryID();
            int pos_id = gren.GetEntryClass(entry_id);
            string part_of_speech = gren.GetClassName(pos_id);
            string tags = string.Join(" ", token.GetTags().Select(z => string.Format("{0}={1}", gren.GetCoordName(z.Item1), gren.GetCoordStateName(z.Item1, z.Item2))).ToArray());
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
}
