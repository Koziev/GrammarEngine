#if !defined TR_FUNS__H
#define TR_FUNS__H
#pragma once

 namespace Solarix
 {

  // *************************************************************
  // Функция для возврата предопределенных переменных типа _0 или
  // локальных переменных.
  // *************************************************************
  class TrFun_Var : public TrFunCall
  {
   private:
    lem::UCString var_name; 

   public:
    TrFun_Var(void);
    TrFun_Var( const UCString &VarName );
    TrFun_Var( const TrFun_Var & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };


  // *************************************************************
  // Функция для создания локальных переменных и их инициализации.
  // *************************************************************
  class TrFun_Declare : public TrFunCall
  {
   private:
    TrType var_type;
    lem::MCollect<lem::UCString> var_name; 
    lem::CloneCollect<TrFunCall> var_value;

   public:
    TrFun_Declare(void);
    TrFun_Declare( const TrFun_Declare & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars,
                                    const TrBuiltInFunSignature *signature  
                                   );
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& binfile );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };


  // ******************************
  // Скомпилированные константы
  // ******************************
  class TrFun_Constant : public TrFunCall
  {
   private:
    TrValue value;

   public:
    TrFun_Constant(void);
    TrFun_Constant( const TrValue &v );
    TrFun_Constant( const TrFun_Constant & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &funs );
    #endif

    const TrValue& GetValue(void) const { return value; }

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& binfile );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };


  // *****************************************
  // Скомпилированный оператор присваивания
  // *****************************************
  class TrFun_Assign : public TrFunCall
  {
   private:
    lem::UCString var_name;
    lem::ClonePtr<TrFunCall> expr; 

   public:
    TrFun_Assign(void);
    TrFun_Assign( const UCString &VarName, TrFunCall *Expr );

    TrFun_Assign( const TrFun_Assign & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };

  class TrFun_Group : public TrFunCall
  {
   private:
    lem::CloneCollect<TrFunCall> items;

   public:
    TrFun_Group(void);

    TrFun_Group( const TrFun_Group & x );
    virtual void operator=( const TrFunCall & x );

    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars,
                                    const TrBuiltInFunSignature *signature  
                                   );
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& binfile );
    virtual void Link( const TrFunctions &functions );
    #endif

    virtual TrFunCall* clone(void) const;
  };



  // *************************************
  // Вызов пользовательской функции.
  // *************************************
  class TrFun_User : public TrFunCall
  {
   private:

   public:
    TrType ret_type;
    lem::UCString name;
    lem::MCollect<lem::UCString> arg_name;
    lem::CloneCollect<TrFunCall> arg_expr;
    const TrFunction* fun;
    const TrFunCall* body; // слинкованное тело вызываемой функции.

   public:
    TrFun_User(void);
    TrFun_User( const TrFun_User & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& binfile );
    virtual void Link( const TrFunctions &functions );
    #endif

    virtual TrFunCall* clone(void) const;
  };



  class TrFun_Return : public TrFunCall
  {
   private:
    lem::Ptr<TrFunCall> expr; 

   public:
    TrFun_Return(void);
    TrFun_Return( TrFunCall *Expr );

    TrFun_Return( const TrFun_Return & x );
    virtual void operator=( const TrFunCall & x );

    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif
   
    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };



  class TrFun_If : public TrFunCall
  {
   private:
    lem::ClonePtr<TrFunCall> cond, f_then, f_else;

   public:
    TrFun_If(void);
    TrFun_If( const TrFun_If & x );
    virtual void operator=( const TrFunCall & x );

    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif
   
    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars,
                                    const TrBuiltInFunSignature *signature  
                                   );
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };

  class TrFun_While : public TrFunCall
  {
   private:
    lem::Ptr<TrFunCall> cond, body; 

   public:
    TrFun_While(void);
    TrFun_While( const TrFun_While & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars,
                                    const TrBuiltInFunSignature *signature  
                                   );
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };



  class TrFun_For : public TrFunCall
  {
   private:
    UCString varname;
    lem::Ptr<TrFunCall> i0, i1, step, body; 

   public:
    TrFun_For(void);
    TrFun_For( const TrFun_For & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars,
                                    const TrBuiltInFunSignature *signature  
                                   );
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };



  class TrFun_BuiltIn : public TrFunCall
  {
   private:
    friend class TrFunctions;

    lem::UCString name;
    lem::CloneCollect<TrFunCall> args;

   public:
    TrFun_BuiltIn(void);
    TrFun_BuiltIn( const TrFun_BuiltIn & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars,
                                    const TrBuiltInFunSignature *signature  
                                   );

    const TrFunCall* GetArg( int i ) const { return args[i]; }
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };


  class TrFun_Break : public TrFunCall
  {
   public:
    TrFun_Break(void);
    TrFun_Break( const TrFun_Break & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& binfile );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };




  class TrFun_CreateWordform : public TrFunCall
  {
   private:
    UCString form_name; // имя формы может быть задано явно, иначе будет использовано имя статьи

    lem::ClonePtr<TrFunCall> ientry;
    lem::CloneCollect<TrFunCall> coords;
    lem::CloneCollect<TrFunCall> states; 

   public:
    TrFun_CreateWordform(void);
    TrFun_CreateWordform( const TrFun_CreateWordform & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars,
                                    const TrBuiltInFunSignature *signature  
                                   );
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& binfile );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };


  class TrFun_Lambda : public TrFunCall
  {
   private:
    TrType ret_type;
    lem::UCString name;
    lem::MCollect<UCString> arg_name;
    const TrFunction* fun;
    const TrFunCall* body; // слинкованное тело вызываемой функции.

    lem::MCollect<UCString> locals; // используемые локальные переменные

   public:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    TrFun_Lambda( const TrFunction *Lambda, const MCollect<UCString> &_locals );
    #endif

    TrFun_Lambda(void);
    TrFun_Lambda( const TrFun_Lambda & x );
    virtual void operator=( const TrFunCall & x );
   
    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const;
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    TrKnownVars &known_vars,
                                    const TrBuiltInFunSignature *signature  
                                   );
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& binfile );
    virtual void Link( const TrFunctions &funs );
    #endif

    virtual TrFunCall* clone(void) const;
  };


 }

#endif
