using System;
using System.Collections.Generic;
using System.Linq;

namespace CorporaLib
{

    public class TagMatcher
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


        public bool Match(WordData token, SolarixGrammarEngineNET.GrammarEngine2 gren)
        {
            if (lexeme != null)
                return token.GetWord().Equals(lexeme, StringComparison.InvariantCultureIgnoreCase);

            if (id_lemma != null)
            {
                int ekey = token.GetEntryID();
                if (id_lemma.Contains(ekey))
                    return true;

                return false;
            }

            if (pos != null)
            {
                if (!pos.Contains(token.GetClassID()))
                {
                    return false;
                }
            }

            if (pairs != null && pairs.Count > 0)
            {
                bool a_version_matched = true;

                foreach (SolarixGrammarEngineNET.CoordPair p in pairs)
                {
                    if (!token.ContainsTag(p.CoordID, p.StateID))
                    {
                        a_version_matched = false;
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

}
