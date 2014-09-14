#if !defined Charpos2EntryEnumerator__H
 #define Charpos2EntryEnumerator__H

 namespace Solarix
 {
  class Charpos2EntryEnumerator
  {
   protected:
    Charpos2EntryEnumerator(void) {}

   public:
    virtual ~Charpos2EntryEnumerator(void) {}

    virtual bool Fetch(void)=0;
    virtual lem::uint32_t GetChar(void)=0;
    virtual int GetPos(void)=0; 
  };
 }

#endif
