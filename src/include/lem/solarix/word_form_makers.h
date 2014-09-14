#ifndef WORD_FORM_MAKERS__H
#define WORD_FORM_MAKERS__H
#pragma once

 #include <lem/solarix/tree_node.h>

 namespace Solarix
 {

 class SE_Operator : public Word_Form_Maker
 {
  protected:
   PlainArgumentList arg_list; // Список аргументов.

   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
                        SynGram& gram
                       );
   #endif

  public:
   SE_Operator( SE_Type iType );
   SE_Operator( const SE_Operator &e );

   virtual ~SE_Operator(void) {}

   virtual int GetMaxContextLen(void) const;

   #if defined SOL_LOADBIN
   virtual void LoadBin( lem::Stream &bin );
   #endif

   #if defined SOL_SAVEBIN
   virtual void SaveBin( lem::Stream &bin ) const;
   #endif

   virtual void GetRefNames( IntCollect &refnames ) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txtfile, SynGram &gram ) const;
   #endif
 };


 class SE_Convolve : public SE_Operator
 {
  private:
   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
                        SynGram& gram
                       );
   #endif

   #if defined SOL_CAA
   Word_Form* Convolve(
                       Dictionary *dict,
                       const PM_Yield &yield,
                       const Word_Form **slist,
                       int n
                      ) const;
   #endif

   lem::MCollect<int> arg_index;
   lem::MCollect<Solarix::GramCoordAdr> arg_coord;

  public:
   SE_Convolve(void);
   SE_Convolve( const SE_Convolve &e );

   virtual Word_Form_Maker* clone(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txtfile, SynGram &gram ) const;
   #endif

   #if defined SOL_LOADBIN
   virtual void LoadBin( lem::Stream &bin );
   #endif

   #if defined SOL_SAVEBIN
   virtual void SaveBin( lem::Stream &bin ) const;
   #endif

   #if defined SOL_CAA
   Res_Pack* Build(
                   Dictionary *dict,
                   const PM_Input &input,
                   const PM_Yield &yield,
                   const PM_SuperIndex &CONFIG
                  ) const;
   #endif
 };



 class SE_NetMovement : public SE_Operator
 {
  private:
   MCollect<Tree_Node*> NetMovement(
                                    const Tree_Node *root,
                                    SynGram &gram
                                   ) const;
   MCollect<Tree_Link> path;                                

   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
                        SynGram& gram
                       );
   #endif

  public:
   SE_NetMovement(void);
   SE_NetMovement( const SE_Convolve &e );

   virtual Word_Form_Maker* clone(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txtfile, SynGram &gram ) const;
   #endif

   #if defined SOL_LOADBIN
   virtual void LoadBin( lem::Stream &bin );
   #endif

   #if defined SOL_SAVEBIN
   virtual void SaveBin( lem::Stream &bin ) const;
   #endif

   #if defined SOL_CAA
   Res_Pack* Build(
                   Dictionary *dict,
                   const PM_Input &input,
                   const PM_Yield &yield,
                   const PM_SuperIndex &CONFIG
                  ) const;
   #endif
 };


 class SE_Merge : public SE_Operator
 {
  public:
   SE_Merge(void);
   SE_Merge( const SE_Merge &e );

   virtual Word_Form_Maker* clone(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txtfile, SynGram &gram ) const;
   #endif

   #if defined SOL_CAA
   Res_Pack* Build(
                   Dictionary *dict,
                   const PM_Input &input,
                   const PM_Yield &yield,
                   const PM_SuperIndex &CONFIG
                  ) const;
   #endif
 };


 class SE_Rnd : public SE_Operator
 {
  public:
   SE_Rnd(void);
   SE_Rnd( const SE_Merge &e );

   virtual Word_Form_Maker* clone(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txtfile, SynGram &gram ) const;
   #endif

   #if defined SOL_CAA
   Res_Pack* Build(
                   Dictionary *dict,
                   const PM_Input &input,
                   const PM_Yield &yield,
                   const PM_SuperIndex &CONFIG
                  ) const;
   #endif
 };

 class PA_PredicateMaker;
 class SE_Query : public Word_Form_Maker
 {
  private:
   PA_PredicateMaker *query; // Сам запрос (точнее его построитель).

  protected:
   #if defined SOL_LOADTXT
   virtual void LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
                        SynGram& gram
                       );
   #endif

  public:
   SE_Query(void);
   SE_Query( const SE_Query &e );

   virtual ~SE_Query(void);

   virtual Word_Form_Maker* clone(void) const;

   #if defined SOL_LOADBIN
   virtual void LoadBin( lem::Stream &bin );
   #endif

   #if defined SOL_SAVEBIN
   virtual void SaveBin( lem::Stream &bin ) const;
   #endif

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txtfile, SynGram &gram ) const;
   #endif

   #if defined SOL_CAA
   virtual Res_Pack* Build(
                           Dictionary *dict,
                           const PM_Input &input,
                           const PM_Yield &yield,
                           const PM_SuperIndex &CONFIG
                          ) const;
   #endif

   virtual void GetRefNames( IntCollect &refnames ) const;
 };



 class SE_Impart : public SE_Operator
 {
  public:
   SE_Impart(void);
   SE_Impart( const SE_Impart &e );

   virtual Word_Form_Maker* clone(void) const;

   #if defined SOL_SAVETXT
   virtual void SaveTxt( OFormatter &txtfile, SynGram &gram ) const;
   #endif

   #if defined SOL_CAA
   Res_Pack* Build(
                   Dictionary *dict,
                   const PM_Input &input,
                   const PM_Yield &yield,
                   const PM_SuperIndex &CONFIG
                  ) const;
   #endif
 };

 }

#endif
