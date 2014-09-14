#if !defined SOL_MULTIWORD_MERGER__H
 #define SOL_MULTIWORD_MERGER__H

 namespace Solarix
 {
  class LexicalAutomat;

  class MultiwordMerger
  {
   private:
    Solarix::LexicalAutomat *la;

    lem::MCollect<lem::UCString> words;
    Solarix::Lexem multiword;

    lem::MCollect<lem::UCString> ready_words;

    int n_max_expecting; // какая максимальная длина

    void Purge(void);

   public:
    MultiwordMerger( Solarix::LexicalAutomat *_la );

    void Push( const lem::UCString &word );

    void ForceReady(void);
    bool IsReady(void) const;
    lem::UCString Pop(void);
  };

 }

#endif
