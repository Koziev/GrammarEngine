using System.Linq;

namespace CorporaLib
{
    public class ConlluItem
    {
        public string word;
        public string ud_class;
        public string ud_lemma;
        public string[] ud_tags;

        public bool Contains(string tag, string value)
        {
            return ud_tags.Contains(tag + "=" + value);
        }
    }
}