#if !defined SOL_PARADIGMA_MATCHER__H
 #define SOL_PARADIGMA_MATCHER__H

 #include <lem/config.h>

 #if !defined FAIND_NO_BOOST_REGEX
 #include <boost/regex.hpp>
 #endif

 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class SynGram;

  class ParadigmaMatcher
  {
   private:
    lem::UFString condition_str;

    #if !defined FAIND_NO_BOOST_REGEX
    boost::wregex condition;
    #endif  

    void Init(void);

   public:
    ParadigmaMatcher(void);
    ParadigmaMatcher( const lem::UFString & ConditionStr );
    ParadigmaMatcher( const ParadigmaMatcher &x );
    void operator=( const ParadigmaMatcher &x );

    bool Empty(void) const;
    bool Match( const lem::UCString & entry_name ) const;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( lem::Iridium::Macro_Parser &txtfile, int PartOfSpeech, SynGram& gram );
    #endif

    lem::UFString ToString(void) const;
  };
 }

#endif
