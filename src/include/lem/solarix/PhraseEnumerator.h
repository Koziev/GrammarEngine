#if !defined PhraseEnumerator__H
 #define PhraseEnumerator__H

 namespace lem
 {
  class UFString;
 }

 namespace Solarix
 {
  class LS_ResultSet;
  class SynGram;
  class PhraseEnumerator
  {
   private:
    LS_ResultSet *rs;
    SynGram *sg;
    int pk_field;

   public:
    PhraseEnumerator( LS_ResultSet *_rs, int _pk_ifield, SynGram *_sg );
    ~PhraseEnumerator(void);

    bool Fetch(void);
    int GetPhraseId(void);
    void GetText( lem::UFString &text );
  };

 }

#endif
