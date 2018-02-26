using System.Collections.Generic;


interface ICorpusReader
{
    IEnumerable<SentenceData> Read(SolarixGrammarEngineNET.GrammarEngine2 gren);
}

