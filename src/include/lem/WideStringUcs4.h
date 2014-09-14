#if !defined LEM_UCS4_ENUMERATOR__H
 #define LEM_UCS4_ENUMERATOR__H

 #include <lem/integer.h>

 namespace lem
 {
  class WideStringUcs4
  {
   private:
    const wchar_t *str;
    int iback;
    int icur;
    bool eof;
   
   public:
    WideStringUcs4( const wchar_t * _str );
    lem::uint32_t Fetch(void);
    void Back(void);
  };
 }

#endif
