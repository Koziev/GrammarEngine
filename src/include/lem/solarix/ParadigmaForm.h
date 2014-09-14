#if !defined ParadigmaForm__H
 #define ParadigmaForm__H

 #include <lem/config.h>

 #if !defined FAIND_NO_BOOST_REGEX
 #include <boost/regex.hpp>
 #endif

 namespace Solarix
 {
  class SG_DeclensionTable;
  class SG_DeclensionForm
  {
   private:
    CP_Array dim; // Список координатных пар измерений.
    Lexem form;   // Строка-команда для Автомата Склонений.
    
    bool valid_condition, valid_flexer_flags; // к сожалению, wregex выдает исключение при вызове empty() для неинициализированного объекта.
    lem::UFString condition_str, flexer_flags_str;

    #if !defined FAIND_NO_BOOST_REGEX
    boost::wregex condition, flexer_flags;
    #endif  

    void Init( const SG_DeclensionForm &df );

    void Check(void) const;

   public:
    SG_DeclensionForm(void);
    SG_DeclensionForm( const SG_DeclensionForm &df );
    SG_DeclensionForm( const CP_Array &Dim, const lem::UCString &Command );
    SG_DeclensionForm(
                      const lem::UFString & lexem_generator,
                      const lem::UFString & rx_condition,
                      const lem::UFString & flexer_flags,
                      const CP_Array & dims
                     );

    void operator=( const SG_DeclensionForm &df );

    void Translate( int id_class, const GraphGram &gram );

    inline const Lexem& GetContent(void) const { return form; }
    inline const CP_Array& GetDim(void) const { return dim; }
    const lem::UCString& GetLexemGenerator(void) const { return form; }
    const lem::UFString& GetConditionStr(void) const { return condition_str; }
    const lem::UFString& GetFlexerFlagsStr(void) const { return flexer_flags_str; }
  

    bool MatchCondition( const UCString &str, const UFString &flexer_flags ) const;

    void ReadAdditionalInfo( Grammar &gram, const SG_DeclensionTable &table, Macro_Parser& txtfile );
  };

 }
#endif

