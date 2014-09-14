#if !defined PhraseNoteEnumerator__H
 #define PhraseNoteEnumerator__H

 namespace lem
 {
  class UFString;
 }

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
    PhraseNoteEnumerator( SynGram *_sg, int _id_phrase );
    ~PhraseNoteEnumerator(void);

    bool Fetch(void);
    int GetNoteId(void);
    void GetNote( SG_PhraseNote &note );
  };

 }

#endif
