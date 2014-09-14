// -----------------------------------------------------------------------------
// File PM_CONDICTOR.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Кондикторы - опорные части продукционных правил для Продукционной Машины.
// -----------------------------------------------------------------------------
//
// CD->06.09.1997
// LC->19.11.2010
// --------------

#if !defined(PM_CONDICTOR__H) && !defined SOL_NO_AA
 #define PM_CONDICTOR__H
#pragma once

 #include <lem/solarix/pm_sup_context.h>
 #include <lem/solarix/pm_fastdirectchecker.h>
 #include <lem/solarix/translation.h>

 namespace lem
 {
  namespace Iridium { class Macro_Parser; }
  class OFormatter;
  class Stream;
 } 

 namespace Solarix
 {
  class Dictionary;
  class PM_Automat;  
  class SynGram;
  class Word_Form;
  class Compile_Options;
  struct PM_RuleComplexity;
  struct CondictorProperties;
  class TrFunctions;

  /***************************************************************************
   Базовый класс для описания КОНДИКТОРОВ - условий, налагаемых на разные
   пространства Системы.
  ****************************************************************************/
 class PM_Condictor
 {
  private:
   int type;  // поле типа условного элемента, либо один из токенов, либо UNKNOWN

  protected:
   int type2; // подтип для оптимизированных акторов.
   int src_location; // местоположение в исходниках - для отладчика

   virtual void Init( const PM_Condictor &src );

   inline int GetType2(void) const { return type2; }

  public:
   PM_Condictor( int Type );
   PM_Condictor( const PM_Condictor& ba );

   virtual ~PM_Condictor(void);

   virtual PM_Condictor* Clone(void) const;

   void operator=( const PM_Condictor& ba );

   inline int GetType(void)  const { return type;  }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   static PM_Condictor* load_txt(
                                 CompilationContext &context,
                                 Macro_Parser &txtfile,
                                 PM_Automat &pm, 
                                 Dictionary &dict
                                );
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
                        PM_Automat &pm, 
                        Dictionary &dict
                       )=0;
   #endif

   virtual void GetProperties( const Dictionary &dict, CondictorProperties &prop ) const;

   #if defined SOL_LOADBIN 
   virtual void LoadBin( lem::Stream &bin );
   static PM_Condictor* load_bin( lem::Stream &bin );
   virtual void Link( const TrFunctions &funs )=0;
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
                         ) const=0;
   virtual bool DoesMatchFirstPoint(
                                    PM_Automat &pm,
                                    Dictionary &dict,
                                    const Variator &context,
                                    int iroot,
                                    TrTrace *trace_log
                                   ) const;
   #endif

   virtual bool HasGotAContext(void) const;

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual void FindContextLens( int *min_context_len, int *max_context_len ) const;
   #endif

   #if defined SOL_CAA
   virtual void Replicate( Dictionary &dict, PM_Input &input ) {}
   #endif

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual PM_Condictor* Optimize( SynGram &sg );
   virtual void Assemble_Entries_List( BaseSet<int> &entries ) const {}

   // ***********************************************************************
   // По умолчанию кондикторы не поддерживают оптимизацию в виде компиляции
   // в C++-код.
   // ***********************************************************************
   virtual bool AllowsCompilation( std::wstring &explanation ) const
   { return false; }

   // ***********************************************************************
   // Этот метод непосредственно выполняет компиляцию в C++-код.
   // ***********************************************************************
   virtual void Compile_CPP(
                            OFormatter &txtfile,
                            const Grammar &gram,
                            const Compile_Options &options
                           ) const
   {}
   #endif

   #if defined SOL_SAVETXT
   virtual void SaveTxt(
                        OFormatter &txtfile,
                        const Dictionary &dict
                       ) const {}
   #endif

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual void CalcComplexity( PM_RuleComplexity &cx ) const {}
   #endif
 };



  #if defined SOL_CAA && !defined SOL_NO_AA
  class TrTraceCondictor : public TrTraceActor
  {
   private:
    const PM_Condictor *fun;
    const PM_Input *inp;
    const PM_Yield *out;

   public:
    TrTraceCondictor( int mark, int Location, const PM_Condictor *c, const PM_Input *i, const PM_Yield *o );
    virtual void Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening=NULL );
  };

  class TrTraceCondictorFirstPoint : public TrTraceActor
  {
   private:
    const PM_Condictor *fun;
    const Variator *var;
    int iroot;

   public:
    TrTraceCondictorFirstPoint( int mark, int Location, const PM_Condictor *c, const Variator *v, int iRoot );
    virtual void Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening=NULL );
  };

  #endif

 } // namespace 'Solarix'

#endif
