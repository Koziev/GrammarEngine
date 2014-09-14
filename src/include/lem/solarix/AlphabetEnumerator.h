#if !defined ALPHABET_ENUMERATOR__H
 #define ALPHABET_ENUMERATOR__H
 
 #include <lem/noncopyable.h>

 namespace Solarix
 {
  class Alphabet;
  class Alphabets;
  class LS_ResultSet;

  class AlphabetEnumerator : lem::NonCopyable
  {
   private:
    LS_ResultSet *rs;
    Alphabets *alphabets;

   public:
    AlphabetEnumerator( Alphabets *_alphabets, LS_ResultSet *_ts );
    virtual ~AlphabetEnumerator(void);

    virtual bool Fetch(void);
    virtual int GetId(void);
    virtual const Alphabet& GetItem(void);
  };
 }
#endif
