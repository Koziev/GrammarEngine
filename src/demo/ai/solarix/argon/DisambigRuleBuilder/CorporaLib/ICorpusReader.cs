using System.Collections.Generic;

namespace CorporaLib
{
    public interface ICorpusReader
    {
        IEnumerable<SentenceData> Read(SolarixGrammarEngineNET.GrammarEngine2 gren);
    }
}
