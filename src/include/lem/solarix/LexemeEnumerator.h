#if !defined LexemeEnumerator__H
 #define LexemeEnumerator__H

 namespace Solarix
 {
  class Lexem;
  class LexemeEnumerator
  {
   public:
    LexemeEnumerator(void) {}
    virtual ~LexemeEnumerator(void) {}
    
    virtual bool Fetch(void)=0;
    virtual const Lexem* Get( Solarix::Lexem &lex )=0;
  };
 }

#endif
