#if !defined PhraseNoteEnumerator__H
#define PhraseNoteEnumerator__H

namespace Solarix
{
    class LS_ResultSet;
    class SynGram;

    class PhraseNoteEnumerator
    {
    private:
        int id_phrase;
        LS_ResultSet *rs;
        SynGram *sg;

    public:
        PhraseNoteEnumerator(SynGram *_sg, int _id_phrase);
        ~PhraseNoteEnumerator();

        bool Fetch();
        int GetNoteId();
        void GetNote(SG_PhraseNote &note);
    };

}

#endif
