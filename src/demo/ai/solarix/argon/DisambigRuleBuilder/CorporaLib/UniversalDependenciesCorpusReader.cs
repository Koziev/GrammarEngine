using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CorporaLib
{
    public class UniversalDependenciesCorpusReader : ConlluCorpusReader
    {
        public UniversalDependenciesCorpusReader(string corpus_path)
            : base(corpus_path, word_column: 1, lemma_column: 2, class_column: 3, tags_column: 5)
        {
        }
    }
}
