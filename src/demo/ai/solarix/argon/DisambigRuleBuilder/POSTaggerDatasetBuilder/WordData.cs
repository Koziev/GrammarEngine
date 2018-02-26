using System;
using System.Collections.Generic;

class WordData
{
    public int word_index;
    public string word;

    public int entry_id;
    public int part_of_speech;
    public List<Tuple<int, int>> tags = new List<Tuple<int, int>>();

    public SolarixGrammarEngineNET.SyntaxTreeNode all_projs;

    public string GetWord() { return word; }

    public int GetEntryID() { return entry_id; }

    public int GetClassID() { return part_of_speech; }

    public bool ContainsTag( int coord_id, int state_id )
    {
        return tags.Contains(Tuple.Create(coord_id, state_id));
    }

    public IEnumerable<Tuple<int, int>> GetTags() { return tags; }

    public override string ToString()
    {
        return word;
    }
}

