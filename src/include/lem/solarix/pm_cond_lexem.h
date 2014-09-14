#if !defined(PM_COND_LEXEM__H) && !defined SOL_NO_AA
 #define PM_COND_LEXEM__H
#pragma once

 #include <lem/config.h>
 #include <string>
 #include <boost/regex.hpp>
 #include <lem/solarix/pm_condictor.h>

 namespace Solarix
 {
 // *****************************************************************
 // Требование на лексическое содержимое единственной опорной точки
 // входного контекста. Используется специально для SoundBuilder'а.
 // *****************************************************************
 class PM_CondLexem : public PM_Condictor
 {
  private:
   int pos;
   Lexem lexem;
   bool use_rx;
   lem::UFString rx_str;
   boost::wregex rx;

   virtual void Init( const PM_Condictor &x );

  public:
   PM_CondLexem(void);
   PM_CondLexem( const PM_CondLexem &c );

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   PM_CondLexem(
                CompilationContext &context,
                Macro_Parser &txtfile,
                PM_Automat &pm, 
                Dictionary &dict
               );
   #endif

   virtual PM_Condictor* Clone(void) const;

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &file,
                        PM_Automat &pm, 
                        Dictionary &dict
                       );
   #endif

   #if defined SOL_LOADBIN 
   virtual void LoadBin( lem::Stream &bin );
   virtual void Link( const TrFunctions &funs );
   #endif

   #if defined SOL_SAVEBIN
   virtual void SaveBin( lem::Stream &bin ) const;
   #endif

   #if defined SOL_CAA
   virtual bool DoesMatch(
                          PM_Automat &pm,
                          Dictionary &dict,
                          PM_Input &input,
                          PM_Yield &yield,
                          TrTrace *trace_log
                         ) const;
   #endif

   virtual bool HasGotAContext(void) const { return true; }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual void FindContextLens(
                                int *min_context_len,
                                int *max_context_len
                               ) const;
   #endif

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual PM_Condictor* Optimize( SynGram &sg );
   #endif

   #if defined SOL_SAVETXT
   virtual void SaveTxt(
                        OFormatter& txtfile,
                        const Dictionary &dict
                       ) const;
   #endif
 };

 } // namespace 'Solarix'

#endif
