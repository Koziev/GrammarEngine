#if !defined LA_RECOGNITION_RULE__H
 #define LA_RECOGNITION_RULE__H

 #include <lem/noncopyable.h>
 #include <lem/ucstring.h>
 #include <lem/ufstring.h>
 #include <lem/zeroed.h>
 #include <lem/math/fp1.h>
 #include <lem/solarix/coord_pair.h>
 #include <boost/regex.hpp>

 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class Dictionary;

  class LA_RecognitionRule : lem::NonCopyable
  {
   public:
    typedef wchar_t HashType;

   private:
    int id;
    lem::UCString name;
    int id_language;
    int id_entry;
    lem::UFString str;

    lem::zbool is_syllab, is_regex, is_prefix, is_affix;
    boost::wregex rx;
    Solarix::CP_Array coords;
    lem::Real1 rel; // достоверность распознавания этим правилом
    int src_location;

   public:
    LA_RecognitionRule(void);
    LA_RecognitionRule( int Id, const lem::UCString &Name, int Id_lang, bool IsSyllab, bool IsRegex, bool IsPrefix,
     bool IsAffix, const lem::UFString &Condition, int EntryID, lem::Real1 Rel, const Solarix::CP_Array &Coord, int SourceID );
    
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    #endif

    int GetSourceLocation(void) const { return src_location; }

    bool IsSyllab(void) const { return is_syllab; }
    bool IsRegex(void) const { return is_regex; }
    bool IsPrefix(void) const { return is_prefix; }
    bool IsAffix(void) const { return is_affix; }
    bool IsWordMatcher(void) const { return !is_regex && !is_syllab && !is_prefix && !is_affix; }

    int GetId(void) const { return id; }
    const lem::UCString & GetName(void) const { return name; }
    const lem::UFString& GetCondition(void) const { return str; }

    bool Match( const lem::UCString & lex ) const;
    int GetLanguage(void) const { return id_language; }
    int GetEntryKey(void) const { return id_entry; }
    lem::Real1 GetRel(void) const { return rel; }
    bool IsPrecise(void) const { return rel==lem::Real1(100); }
    const Solarix::CP_Array & GetCoords(void) const { return coords; }

    LA_RecognitionRule::HashType GetHash(void) const;
    static LA_RecognitionRule::HashType CalcHash( const wchar_t *str, bool IsPrefix, bool IsAffix );

    void SetId( int Id ) { id=Id; }
  };
 }

#endif
