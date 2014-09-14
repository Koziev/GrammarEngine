#if !defined LEM_UCS4_TO_WIDESTRING__H
 #define LEM_UCS4_TO_WIDESTRING__H

 #include <lem/integer.h>
 #include <lem/ucstring.h>
 #include <lem/ufstring.h>

 namespace lem
 {
  class Ucs4ToUCString
  {
   private:
    lem::UCString res;

   public:
    Ucs4ToUCString(void) {}
    bool Add( lem::uint32_t c32 );
    const lem::UCString& ToString(void);
    void Clear(void);
  };

  class Ucs4ToUFString
  {
   private:
    lem::UFString res;

   public:
    Ucs4ToUFString(void) {}
    void Add( lem::uint32_t c32 );
    const lem::UFString& ToString(void);
    void Clear(void);
  };
 }

#endif
