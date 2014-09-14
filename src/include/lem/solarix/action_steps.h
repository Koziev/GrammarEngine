#ifndef ACTION_STEPS__H
#define ACTION_STEPS__H
#pragma once

 #include <lem/solarix/tree_node.h>

 namespace Solarix
 {

 class AS_Group : public PM_ActionStep
 {
  private:
   CloneCollect<PM_ActionStep> list;

  public:
   AS_Group(void);
   AS_Group( const AS_Group &x );

   virtual void operator=( const PM_ActionStep &x );

   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
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

   virtual Res_Pack* Build(
                           Dictionary *dict
                           #if defined SOL_CAA
                           , bool do_deep_copy 
                           , const PM_Input &input
                           , const PM_Yield &yield
                           , const PM_SuperIndex *CONFIG=NULL
                           #endif
                          ) const;

   #if defined SOL_LOADTXT
   virtual void Optimize( SynGram &sg );
   #endif

   virtual bool CanPrebuilt(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txt, const Dictionary &dict ) const;
   #endif

   virtual PM_ActionStep* clone() const;
   virtual bool DoesContainReferences() const;
   virtual void GetRefNames( IntCollect &refnames ) const;
   virtual int GetMaxContextLen(void) const;
 };


 class AS_Or : public PM_ActionStep
 {
  private:
   lem::CloneCollect<PM_ActionStep> list;

  public:
   AS_Or(void);
   AS_Or( const AS_Or &x );

   virtual void operator=( const PM_ActionStep &x );

   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
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

   virtual Res_Pack* Build(
                           Dictionary *dict
                           #if defined SOL_CAA
                           , bool do_deep_copy 
                           , const PM_Input &input
                           , const PM_Yield &yield
                           , const PM_SuperIndex *CONFIG=NULL
                           #endif
                          ) const;

   #if defined SOL_LOADTXT
   virtual void Optimize( SynGram &sg );
   #endif

   virtual bool CanPrebuilt(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txt, const Dictionary &dict ) const;
   #endif
   virtual PM_ActionStep* clone() const;
   virtual bool DoesContainReferences() const;
   virtual void GetRefNames( IntCollect &refnames ) const;
   virtual int GetMaxContextLen(void) const;
 };


 class AS_Oscil : public PM_ActionStep
 {
  private:
   PM_ActionStep* item;

  public:
   AS_Oscil(void);
   AS_Oscil( const AS_Oscil &x );

   virtual void operator=( const PM_ActionStep &x );

   virtual ~AS_Oscil(void);

   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
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

   virtual Res_Pack* Build(
                           Dictionary *dict
                           #if defined SOL_CAA
                           , bool do_deep_copy 
                           , const PM_Input &input
                           , const PM_Yield &yield
                           , const PM_SuperIndex *CONFIG=NULL
                           #endif
                          ) const;

   #if defined SOL_LOADTXT
   virtual void Optimize( SynGram &sg );
   #endif

   virtual bool CanPrebuilt(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txt, const Dictionary &dict ) const;
   #endif

   virtual PM_ActionStep* clone() const;
   virtual bool DoesContainReferences() const;
   virtual void GetRefNames( IntCollect &refnames ) const;
   virtual int GetMaxContextLen(void) const;
 };


 class AS_Word : public PM_ActionStep
 {
  private:
   PlainArgumentList word;

  public:
   AS_Word(void);
   AS_Word( const AS_Word &x );

   virtual void operator=( const PM_ActionStep &x );

   virtual int GetMaxContextLen(void) const;

   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
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

   virtual Res_Pack* Build(
                           Dictionary *dict
                           #if defined SOL_CAA
                           , bool do_deep_copy 
                           , const PM_Input &input
                           , const PM_Yield &yield
                           , const PM_SuperIndex *CONFIG=NULL
                           #endif
                          ) const;

   #if defined SOL_LOADTXT
   virtual void Optimize( SynGram &sg );
   #endif

   virtual bool CanPrebuilt(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txt, const Dictionary &dict ) const;
   #endif

   virtual PM_ActionStep* clone() const;
   virtual bool DoesContainReferences() const;
   virtual void GetRefNames( IntCollect &refnames ) const;
 };


 class AS_Chain : public PM_ActionStep
 {
  private:
   PM_ActionStep *item;

  public:
   AS_Chain(void);

   AS_Chain( const AS_Chain &x );

   virtual void operator=( const PM_ActionStep &x );

   virtual ~AS_Chain(void);

   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
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

   virtual Res_Pack* Build(
                           Dictionary *dict
                           #if defined SOL_CAA
                           , bool do_deep_copy 
                           , const PM_Input &input
                           , const PM_Yield &yield
                           , const PM_SuperIndex *CONFIG=NULL
                           #endif
                          ) const;

   #if defined SOL_LOADTXT
   virtual void Optimize( SynGram &sg );
   #endif

   virtual bool CanPrebuilt(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txt, const Dictionary &dict ) const;
   #endif

   virtual PM_ActionStep* clone() const;
   virtual bool DoesContainReferences() const;
   virtual void GetRefNames( IntCollect &refnames ) const;
   virtual int GetMaxContextLen(void) const;
 };


 class PA_PredicateMaker;
 class AS_Predicate : public PM_ActionStep
 {
  private:
   PA_PredicateMaker *pred;
   UCString base_name;

  public:
   AS_Predicate(void);
   AS_Predicate( const AS_Predicate &x );
   virtual ~AS_Predicate(void);

   virtual void operator=( const PM_ActionStep &x );

   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
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

   virtual Res_Pack* Build(
                           Dictionary *dict
                           #if defined SOL_CAA
                           , bool do_deep_copy 
                           , const PM_Input &input
                           , const PM_Yield &yield
                           , const PM_SuperIndex *CONFIG=NULL
                           #endif
                          ) const;

   #if defined SOL_LOADTXT
   virtual void Optimize( SynGram &sg );
   #endif

   virtual bool CanPrebuilt(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txt, const Dictionary &dict ) const;
   #endif

   virtual PM_ActionStep* clone(void) const;
   virtual bool DoesContainReferences(void) const;
   virtual void GetRefNames( IntCollect &refnames ) const;
 };


 }

#endif
