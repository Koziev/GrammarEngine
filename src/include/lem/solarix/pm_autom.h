// -----------------------------------------------------------------------------
// File PM_AUTOM.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// SOLARIX Grammar engine
// Класс PM_Automat - алгоритмы Продукционной Машины, базовый класс для
// Автоматов VA и AA.
// -----------------------------------------------------------------------------
//
// CD->22.03.1998
// LC->23.08.2014
// --------------

#if !defined SOL_CAA_AUTO_H
 #define SOL_CAA_AUTO_H
#pragma once

 #include <lem/ptr_container.h>
 #include <lem/date_time.h>
 #include <lem/solarix/automaton.h>
 #include <lem/solarix/translation.h>
 #include <lem/solarix/trace_log.h>

 namespace Solarix
 {
  // Константа задает число групп правил по признаку значения хэш-кода имени.
  // Чем больше константа, тем меньшее число правил придется просмотреть при
  // поиске заданного по имени, но тем больше будет сектейнер, хранящий список
  // списков индексов правил.

  class Tree_Node;
  class PM_RulesInCategory;
  class Word_Form;
  class Res_Pack;
  class Variator;
  struct SyntaxAnalyzerTimeout;
  class PM_Rules;
  class PM_FunctionLoader;
  class PM_ProcedureLoader;
  class LexiconStorage;

  class PM_Automat : public Automaton
  {
   public:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    lem::MCollect<UCString> needs_chain_scenarios, needs_replace_scenarios;
    void NeedsChainScenario( const UCString &s );
    void NeedsReplaceScenario( const UCString &s );
    #endif

   protected:
    #if defined SOL_CAA
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_sequence;
    #endif
    std::map<UCString,int> sequence; // генераторы неповторяющихся значений
    #endif

    PM_FunctionLoader *functions;

   private:
    const wchar_t *sql_prefix;
    LexiconStorage *storage;

    SynGram& GetSynGram(void) const;

    #if defined SOL_CAA
    void DoDiversifyTree(
                         const Tree_Node &X,
                         const UCString &pred_name,
                         std::vector<PA_PrologSpace*> &pa_spaces,
                         MCollect<Tree_Node*> &created_list
                        ) const;
    #endif


    #if defined SOL_CAA
    bool CanBeFixed(
                    const Tree_Node &A,
                    const Tree_Node &X,
                    IntCollect &map
                   ) const;
    #endif

   protected:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual bool ProcessLexem(
                              const BethToken &t,
                              Macro_Parser &txtfile,
                              const Binarization_Options &options
                             );
    #endif

   #if defined SOL_REPORT
   void SaveRules_SQL( const char *marker, OFormatter &out, OFormatter &alters, const SQL_Production &sql_version ); 
   #endif

   public:
    lem::zbool default_pass_replace_setting;

   public:
    PM_Automat( int Index );

    ~PM_Automat(void);

    void Delete(void);

    virtual void SetDictPtr( Dictionary *d );

    void SetStorage( const wchar_t *SqlPrefix, LexiconStorage *stg );
    virtual void BeforeSyntaxRecompilation(void);

    #if defined SOL_LOADBIN 
    virtual void DictionaryLoaded(void);
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void Prepare( const lem::Path &outdir, const Binarization_Options &opts );
    virtual void Optimize(void);
    #endif

    //PM_RulesInCategory* GetRuleList( const UCString &Name ) const;
    //int Find_Rule_List( const UCString &Name ) const;

    PM_FunctionLoader & GetFunctions() { return *functions; }

    #if defined SOL_REPORT
    virtual void Report( OFormatter &where_to );
    virtual void PrintMap( OFormatter &where_to );
    #endif

    #if defined SOL_CAA && defined SOLARIX_PRO
    bool CreateSequence( const UCString &name, int start_value ) const;
    int GetSequenceValue( const UCString &name, int step ) const;
    #endif
  };
 } // namespace 'Solarix'

#endif
