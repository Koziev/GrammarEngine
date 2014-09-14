#if !defined LA_PREPROCESSOR_TOK_RULE__H
 #define LA_PREPROCESSOR_TOK_RULE__H

 #include <lem/noncopyable.h>
 #include <lem/ptr_container.h>
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
  class SentenceWord;

  struct LA_PreprocessorRuleToken : lem::NonCopyable
  {
   lem::UFString condition;
   lem::zbool case_sensitive;
   lem::zbool is_regex;
   boost::wregex rx_condition;

   LA_PreprocessorRuleToken( bool IsRegex, bool CaseSensitive, const lem::UFString &Condition );

   bool DoesMatch( const lem::UCString &word ) const;
   const lem::UFString & GetCondition(void) const { return condition; }
  };

  class LA_PreprocessorTokRule : lem::NonCopyable
  {
   private:
    int id;
    lem::UCString name;
    int id_language;

    lem::zbool case_sensitive;
    lem::zbool is_regex;
    bool is_greedy;
    int src_location;

    lem::Ptr_NC_Collect<LA_PreprocessorRuleToken> left, right;
//    bool DoesMatch1( lem::UCString &word ) const;

   public:
    LA_PreprocessorTokRule(void);

    LA_PreprocessorTokRule( int Id, const lem::UCString &Name,
                            int Id_Lang, bool IsRegex, bool CaseSensitive, bool IsGreedy,
                            lem::MCollect<LA_PreprocessorRuleToken*> &Left, 
                            lem::MCollect<LA_PreprocessorRuleToken*> &Right, int id_src );

    
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict );
    #endif

//    bool Apply( lem::MCollect<SentenceWord*> &text ) const;

    const lem::UCString& GetName(void) const { return name; }
    int GetLanguage(void) const { return id_language; }
    int GetId(void) const { return id; }
    bool IsRegex(void) const { return is_regex; }
    bool CaseSensitive(void) const { return case_sensitive; }
    bool IsGreedy() const { return is_greedy; }
    const lem::Ptr_NC_Collect<LA_PreprocessorRuleToken>& GetLeft(void) const { return left; }
    const lem::Ptr_NC_Collect<LA_PreprocessorRuleToken>& GetRight(void) const { return right; }

    int GetSourceLocation(void) const { return src_location; }

    void SetId( int Id ) { id=Id; }
  };

  typedef LA_PreprocessorRuleToken LA_PostprocessorRuleToken;
 }

#endif
