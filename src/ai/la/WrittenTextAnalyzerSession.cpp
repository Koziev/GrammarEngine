#include <lem/solarix/WrittenTextLexer.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>

using namespace Solarix;

WrittenTextAnalysisSession::WrittenTextAnalysisSession( Solarix::Dictionary * _dict, TrTrace * _trace )
 : TextAnalysisSession(_dict,_trace)
{
}


void WrittenTextAnalysisSession::ApplyFilters( const lem::UFString & str )
{
 ElapsedTimeConstraint constraints( params.timeout.max_elapsed_millisecs, params.timeout.max_recursion_depth );
 AnalyzeIt( str, false, false, constraints );
 return;
}

  
void WrittenTextAnalysisSession::MorphologicalAnalysis( const lem::UFString & str )
{
 ElapsedTimeConstraint constraints( params.timeout.max_elapsed_millisecs, params.timeout.max_recursion_depth );
 AnalyzeIt( str, true, false, constraints );
 return;
}



void WrittenTextAnalysisSession::SyntacticAnalysis( const lem::UFString & str )
{
 ElapsedTimeConstraint constraints( params.timeout.max_elapsed_millisecs, params.timeout.max_recursion_depth );
 AnalyzeIt( str, true, true, constraints );

/*
 if( FindFacts )
  {
   const lem::UCString FIND_FACTS_NAME(L"FindFacts");
   if( dict->GetAlephAuto().GetProcedures().FindProcedure(FIND_FACTS_NAME,false)!=UNKNOWN )
    {
     TrWideContext env;
  
     if( pack!=NULL )
     {
      for( int ivar=0; ivar<pack->vars().size() && !constraints.Exceeded(); ++ivar )
       {
        Variator & var = * pack->vars().get(ivar);
        dict->GetAlephAuto().Transform( FIND_FACTS_NAME, var, env, constraints, trace );
       }
     }
    }
  }
*/

 return;
}


void WrittenTextAnalysisSession::SyntacticAnalysis( BasicLexer & _lexer, const ElapsedTimeConstraint & constraints )
{
 lexer = &_lexer;
 Analyze(true,true,constraints);
 lexer = NULL;
 return;
}


void WrittenTextAnalysisSession::AnalyzeIt( const lem::UFString & str, bool ApplyPatterns, bool DoSyntacticLinks, const ElapsedTimeConstraint & constraints )
{
 processed_str = str;

 if( params.LanguageUnknown() )
  {
   // Язык предложения не задан явно, определим его на основе статистических критериев.
   const int id_language = dict->GetLexAuto().GuessLanguage( str );

   if( id_language==UNKNOWN )
    {
     lem::MemFormatter msg;
     msg.printf( "Can not guess the language of the phrase [%us]", str.c_str() );
     throw E_BaseException(msg.string());
    }

   params.SetLanguageID( id_language );

   #if defined SOL_DEBUGGING
   if( trace!=NULL )
    {
     trace->LanguageGuessed( str, id_language );
    }
   #endif
  }

 delete lexer;
 lexer = new WrittenTextLexer( str, params, dict, trace );

 Analyze(ApplyPatterns,DoSyntacticLinks,constraints);

 return;
}



void WrittenTextAnalysisSession::Tokenize( const lem::UFString & str )
{
 ElapsedTimeConstraint constraints( params.timeout.max_elapsed_millisecs, params.timeout.max_recursion_depth );

 processed_str = str;

 if( params.LanguageUnknown() )
  {
   // Язык предложения не задан явно, определим его на основе статистических критериев.
   const int id_language = dict->GetLexAuto().GuessLanguage( str );
   params.SetLanguageID( id_language );

   #if defined SOL_DEBUGGING
   if( trace!=NULL )
    {
     trace->LanguageGuessed( str, id_language );
    }
   #endif
  }

 delete lexer;
 lexer = new WrittenTextLexer( str, params, dict, trace );

 Analyze(false,false,constraints);

 return;
}
