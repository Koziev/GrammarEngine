#if !defined Paradigma__H
 #define Paradigma__H

 #include <lem/solarix/ParadigmaMatcher.h>

 namespace Solarix
 {
  class SG_DeclensionAutomat;
  class SG_DeclensionForm;
  class SQL_Production;

  /**************************************************
   Word generation (declension) table.
   “аблица формообразовани€.
   
   It is a sort of TEMPLATE for generation of word
   forms by its basic form (entry name).
  **************************************************/

  class SG_DeclensionTable : public Form_Table
  {
   private:
    lem::UCString name; // условное название парадигмы
    lem::MCollect<lem::UCString> names; // им€ и все алиасы
    ParadigmaMatcher condition;
  
    lem::MCollect<SG_DeclensionForm*> form;

   protected:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void Loaded( const Dictionary &dict );
    virtual void LoadName( Macro_Parser& txtfile, Dictionary &dict );
    virtual void LoadBody( Macro_Parser &txtfile, Grammar &gram );
    virtual void AddForm(
                         const CP_Array& dim,
                         const WordFormName& form_name,
                         Dictionary &dict
                        );
    virtual void ReadAdditionalInfo( Grammar &gram, int iForm, Macro_Parser& txtfile );
    #endif

    virtual const Grammar& GetGrammar( const Dictionary &dict );
    virtual Grammar& GetGrammar( Dictionary &dict );

   public:
    SG_DeclensionTable(void) {}
    SG_DeclensionTable(
                       const lem::MCollect<lem::UCString> & Names,
                       const lem::UFString & matcher_str,
                       int PartOfSpeech,
                       const CP_Array & Attrs,
                       const lem::MCollect<SG_DeclensionForm*> &Forms
                      );

    ~SG_DeclensionTable(void);

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    SG_DeclensionTable( Macro_Parser& txtfile, Grammar& gram );
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void Translate( const GraphGram &g_gram );
    #endif

    inline const lem::MCollect<SG_DeclensionForm*>& GetForms(void) const { return form; }

    bool CanApply( const UCString &entry_name ) const;
    bool IsAuto(void) const;
    const ParadigmaMatcher& GetCondition(void) const { return condition; }

    const lem::UCString& GetName(void) const { return name; }
    const lem::MCollect<lem::UCString>& GetNames(void) const { return names; }
    bool MatchName( const lem::UCString &s ) const;

    virtual int CountForms(void) const;

    void GenerateForms(
                       const Lexem &entry_name,
                       lem::MCollect<Lexem> &res,
                       const SynGram &sg,
                       const SG_DeclensionAutomat &dsa 
                      ) const;

    void GenerateForms(
                       const Lexem &entry_name,
                       lem::MCollect<Lexem> &res,
                       lem::PtrCollect<CP_Array> &dims,
                       const SynGram &sg,
                       const SG_DeclensionAutomat &dsa
                      ) const;
  };

 }
#endif
