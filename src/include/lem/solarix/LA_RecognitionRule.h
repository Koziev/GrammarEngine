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

    lem::zbool case_sensitive;
    lem::zbool is_syllab, is_regex, is_prefix, is_affix;
    lem::zbool is_forced; // если правило должно применяеться даже если найдены словарные формы
    boost::wregex rx;
    Solarix::CP_Array coords;
    float score; // штрафы или поощрения за использование правила
    int src_location;

   public:
    LA_RecognitionRule();
    LA_RecognitionRule( int Id, const lem::UCString &Name,
     bool CaseSensitive, int Id_lang,
     bool IsSyllab, bool IsRegex, bool IsPrefix,
     bool IsAffix, bool IsForced,
     const lem::UFString &Condition, int EntryID, float Score, const Solarix::CP_Array &Coord, int SourceID );
    
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    #endif

    int GetSourceLocation() const { return src_location; }

    bool IsSyllab() const { return is_syllab; }
    bool IsRegex() const { return is_regex; }
    bool IsPrefix() const { return is_prefix; }
    bool IsAffix() const { return is_affix; }
    bool IsWordMatcher() const { return !is_regex && !is_syllab && !is_prefix && !is_affix; }
    bool IsCaseSensitive() const { return case_sensitive; }
    bool IsForced() const { return is_forced; }

    int GetId() const { return id; }
    const lem::UCString & GetName() const { return name; }
    const lem::UFString& GetCondition() const { return str; }

    bool Match(
               const lem::UCString & normalized_word,
               const lem::UCString & original_word
              ) const;

    int GetLanguage() const { return id_language; }
    int GetEntryKey() const { return id_entry; }
    float GetScore() const { return score; }
    bool IsPrecise() const { return score==0; }
    const Solarix::CP_Array & GetCoords() const { return coords; }

    LA_RecognitionRule::HashType GetHash() const;
    static LA_RecognitionRule::HashType CalcHash( const wchar_t *str, bool IsPrefix, bool IsAffix );

    void SetId( int Id ) { id=Id; }
  };
 }

#endif
