// -----------------------------------------------------------------------------
// File AA_AUTOM.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine
// Грамматический Алеф-Автомат и поддерживающие структуры.
// -----------------------------------------------------------------------------
//
// CD->27.03.1997
// LC->02.02.2013
// --------------

#if !defined SOL_ALEFAUTO_H
 #define SOL_ALEFAUTO_H
#pragma once

 #include <lem/solarix/pm_autom.h>

 namespace Solarix
 {
  class AlephAutomat : public PM_Automat
  {
   private:
    LexiconStorage *storage;
    bool do_delete_storage;

    SynGram& GetSynGram(void) const;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual bool ProcessLexem(
                              const BethToken &t,
                              Macro_Parser &txtfile,
                              const Binarization_Options &options
                             );
    #endif


    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_language2syntan;
    #endif
    std::map< int, lem::UCString > language2syntan; // имена процедур, выполняющих синтаксический анализ для разных языков
    const lem::UCString & GetSyntacticAnalyzerName( int id_language );

   public:
    AlephAutomat(void);
    ~AlephAutomat(void);

    virtual const UCString GetName(void) const { return SOL_ALEPHAUTO_MARK; }

    void SetStorage( LexiconStorage *stg, bool _do_delete );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void Prepare( const lem::Path &outdir, const Binarization_Options &opts );
    #endif

    #if defined SOL_REPORT
    virtual void SaveRules_SQL( OFormatter &out, OFormatter &alters, const SQL_Production &sql_version );
    #endif

    #if defined SOL_CAA
    Res_Pack* Analyze(
                      BasicLexer & lexer,
                      TrWideContext & env,
                      const ElapsedTimeConstraint & constraints,
                      TrTrace * trace
                     );
    #endif

  };

 } // namespace 'lem'

#endif
