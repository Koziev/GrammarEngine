#if !defined LexemeEnumerator_File__H
 #define LexemeEnumerator_File__H

 #include <lem/solarix/LexemeEnumerator.h>

 namespace Solarix
 {
  class WordEntries_File; 
  class LexemeEnumerator_File : public LexemeEnumerator
  {
   private:
    WordEntries_File *entries;
    int icur;

   public:
    LexemeEnumerator_File( WordEntries_File *_entries );
    virtual ~LexemeEnumerator_File(void) {}
    
    virtual bool Fetch(void);
    virtual const Lexem* Get( Solarix::Lexem &lex );
  };
 }

#endif
