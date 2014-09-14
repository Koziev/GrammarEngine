#ifndef SOL_TPU__H
#define SOL_TPU__H
#pragma once

 #include <lem/solarix/phrasema.h>
 #include <lem/solarix/pm_autom.h>
 #include <lem/solarix/syntax_analyzer_timeout.h>

 #if defined SOL_CAA && !defined SOL_NO_AA

 namespace Solarix
 {
  class Res_Pack;

  class Text_Processor
  {
   private:
    lem::zbool prevent_alt_burst; // выполнять упрощенный синтаксический анализ,
                                  // если есть подозрение, что альтернатив будет слишком
                                  // много

   protected:
    static SyntaxAnalyzerTimeout default_timeout;

    int LanguageID;
    Dictionary* sol_id;
    bool do_syntactic_analysis; // Do perform grammatic analysis/synthesis

   public:
    Text_Processor( Dictionary* hSolarix );
    virtual ~Text_Processor(void) {}

    virtual Res_Pack* process_syntax(
                                     Solarix::Sentence &sent,
                                     bool AllowFuzzyWordRecognition,
                                     bool AllowSparseAnalysis,
                                     const SyntaxAnalyzerTimeout &timeout=Text_Processor::default_timeout,
                                     TrTrace *trace_log=NULL
                                    );


    virtual Res_Pack* process_morphology(
                                         Solarix::Sentence &sent,
                                         bool AllowFuzzyWordRecognition,
                                         bool AllowSparseAnalysis,
                                         const SyntaxAnalyzerTimeout &timeout=Text_Processor::default_timeout,
                                         TrTrace *trace_log=NULL
                                        );

    inline void PerformSyntacticAnalysis( bool f=true ) { do_syntactic_analysis=f; }
    inline Dictionary* GetDictionary(void) { return sol_id; }
    void SetLanguageID( int id ) { LanguageID=id; }
  };
 } // namespace Solarix

 #endif

#endif

