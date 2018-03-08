using System.Collections.Generic;


namespace CorporaLib
{

    public class SentenceData
    {
        private string sentence_str;

        private List<WordData> words = new List<WordData>();


        public SentenceData(string sentence_str)
        {
            this.sentence_str = sentence_str;
        }

        public int CountWords() { return words.Count; }
        public IEnumerable<WordData> GetWords() { return words; }

        public WordData GetWord(int i) { return words[i]; }

        public void AddWord(WordData word_data)
        {
            words.Add(word_data);
        }

        public string GetSentenceStr() { return sentence_str; }
    }

}