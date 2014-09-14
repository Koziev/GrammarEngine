// -----------------------------------------------------------------------------
// File TEXT_PROCESSOR.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine
//
// Модуль грамматического анализа предложений.
// -----------------------------------------------------------------------------
//
// CD->22.11.2003
// LC->06.09.2012
// --------------

#if defined SOL_CAA


#include <lem/solarix/res_pack.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include <lem/solarix/text_processor.h>

using namespace lem;
using namespace Solarix;

SyntaxAnalyzerTimeout Text_Processor::default_timeout;

Text_Processor::Text_Processor( Solarix::Dictionary* hSolarix )
{
 LEM_CHECKIT_Z( hSolarix!=NULL );
 sol_id = hSolarix;
 LanguageID = UNKNOWN;

 return;
}


Res_Pack* Text_Processor::process_morphology(
                                             Sentence &sent,
                                             bool AllowFuzzyWordRecognition,
                                             bool AllowSparseAnalysis,
                                             const SyntaxAnalyzerTimeout &timeout,
                                             TrTrace *trace_log
                                            )
{
 WrittenTextAnalysisSession * current_analysis = new WrittenTextAnalysisSession( sol_id, trace_log );
 current_analysis->params.SetLanguageID(LanguageID);
 current_analysis->params.CompleteAnalysisOnly = true;
 current_analysis->params.AllowPrimaryFuzzyWordRecog = AllowFuzzyWordRecognition;
 current_analysis->params.UseTokenReconstruction = false;
 current_analysis->params.UseSparsePatterns = false;
// current_analysis->params.UseIterative = false;
 current_analysis->params.UseTopDownThenSparse = AllowSparseAnalysis;

 current_analysis->MorphologicalAnalysis(sent.org_phrase);

 Res_Pack * fblo = new Res_Pack( current_analysis->GetPack() );

 return fblo;
}


Res_Pack* Text_Processor::process_syntax(
                                         Sentence &sent,
                                         bool AllowFuzzyWordRecognition,
                                         bool AllowSparseAnalysis,
                                         const SyntaxAnalyzerTimeout &timeout,
                                         TrTrace *trace_log
                                        )
{
 WrittenTextAnalysisSession * current_analysis = new WrittenTextAnalysisSession( sol_id, trace_log );
 current_analysis->params.SetLanguageID(LanguageID);
 current_analysis->params.CompleteAnalysisOnly = !AllowSparseAnalysis;
 current_analysis->params.AllowPrimaryFuzzyWordRecog = AllowFuzzyWordRecognition;
 current_analysis->params.UseTokenReconstruction = false;
 current_analysis->params.UseSparsePatterns = false;
 current_analysis->params.UseTopDownThenSparse = false;

 current_analysis->SyntacticAnalysis(sent.org_phrase);

 Res_Pack * fblo = new Res_Pack( current_analysis->GetPack() );

 return fblo;
}

#endif // defined SOL_CAA
