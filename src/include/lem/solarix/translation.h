#if !defined LA_TRANSLATION__H
#define LA_TRANSLATION__H
#pragma once

 // Запчасти для движка перевода
 //
 // CD->13.06.2009
 // LC->23.08.2014

 #include <lem/noncopyable.h>
 #include <lem/ptr_container.h>

 #undef match

 #include <boost/regex.hpp>
 #include <lem/RWULock.h>
 #include <lem/tuple.h>
 #include <lem/macro_parser.h>
 #include <lem/solarix/coord_pair.h>
 #include <lem/solarix/lexem.h>
 #include <lem/solarix/tree_link.h>
 #include <lem/solarix/tree_node.h>
 #include <lem/solarix/word_form.h>
 #include <lem/solarix/trace_log.h>
 #include <lem/solarix/BackRefCorrel.h>
 #include <lem/solarix/BackTraceItem.h>
 #include <lem/solarix/VariableChecker.h>
 #include <lem/solarix/SlotProperties.h>
 
 namespace Solarix
 {
  class Dictionary;
  class SynGram;
  class PM_Automat;
  class Word_Form;
  class Variator;
  

  #if defined SOL_LOADTXT && defined SOL_COMPILER
  // ******************************************************
  // Объявления процедур, групп правил, функций, итераторов
  // в рамках модуля.
  // ******************************************************
  class TrProcedureDeclaration : lem::NonCopyable
  {
   private:
    lem::MCollect<UCString> procs; // объявленные процедуры
    lem::MCollect<UCString> rulegroups;

   public:
    TrProcedureDeclaration(void);
   
    bool IsProcedure( const UCString &name ) const;
    bool IsRuleGroup( const UCString &name ) const;

    void RegisterProcedure( const UCString &name );
    void RegisterRuleGroup( const UCString &name );
  };
  #endif

  class TrFunctions;
  class TrType
  {
   public:
    enum { Variant, Void, Bool, Int, String, Tree, Trees, Fun, Tuple };

   private:
    int type;
    friend class TrValue;
    lem::zbool is_const;

   public:
    TrType(void) : type(TrType::Void), is_const(true) {}
    explicit TrType( int Type, bool Const=false ) : type(Type), is_const(Const) {}
 
    int GetType(void) const { return type; }
    bool IsBool(void) const { return type==TrType::Bool; }
    bool IsInt(void) const { return type==TrType::Int; }
    bool IsString(void) const { return type==TrType::String; }
    bool IsTree(void) const { return type==TrType::Tree; }
    bool IsTrees(void) const { return type==TrType::Trees; }
    bool IsFun(void) const { return type==TrType::Fun; }
    bool IsVoid(void) const { return type==TrType::Void; }
    bool IsVariant(void) const { return type==TrType::Variant; }
    bool IsTuple(void) const { return type==TrType::Tuple; }

    bool IsConst(void) const { return is_const; }
    void MakeConstant(void) { is_const=true; }
    void MakeMutable(void) { is_const=false; }

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt(
                 PM_Automat &pm,
                 lem::Iridium::Macro_Parser &txtfile,
                 const TrFunctions &funs
                );
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    void LoadBin( lem::Stream& bin );
    #endif

    lem::UFString GetName(void) const;
  };

  class TrVoidType : public TrType
  {
   public:
    TrVoidType(void) : TrType(TrType::Void,true) {}
  };

  class TrVariantType : public TrType
  {
   public:
    TrVariantType(void) : TrType(TrType::Variant,true) {}
  };

  class TrTreeType : public TrType
  {
   public:
    TrTreeType(void) : TrType(TrType::Tree,false) {}
  };

    
  class TrTreesType : public TrType
  {
   public:
    TrTreesType(void) : TrType(TrType::Trees,false) {}
  };

  class TrIntType : public TrType
  {
   public:
    TrIntType(void) : TrType(TrType::Int,false) {}
  };

  class TrValue;
  class TrValuePrinterDecorator;

  class TrTuple
  {
   public: 
    lem::MCollect<TrValue*> values;

    TrTuple(void);
    ~TrTuple(void);
    TrTuple( const TrTuple &x );
    void operator=( const TrTuple &x );

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif


    #if defined SOL_LOADBIN 
    void LoadBin( lem::Stream &bin );
    void Link( const TrFunctions &funs );
    #endif


    bool operator==( const TrTuple &x ) const;
    bool operator!=( const TrTuple &x ) const;

    void Clear(void);
    void Set( int i, TrValue& x );
    void Add( const TrValue& x );
    void Add( TrValue* x );
    void Remove( int i );
    void Insert( int i, const TrValue& x );
    int Count(void) const { return CastSizeToInt(values.size()); }
    const TrValue& operator[]( int i ) const { return *values[i]; }
    bool In_Y( const TrTuple &y ) const;
    int Find( const TrValue& x ) const;

    void Print( const Solarix::Dictionary &dict, lem::OFormatter &out, const TrValuePrinterDecorator *decorator=NULL ) const;
    void PrintXML( lem::OFormatter &xml, const Solarix::Dictionary &dict ) const;
  };


  class TrFunCall;
  class TrFunctions;
  class TrClosureVars;


  class TrValue
  {
   protected:
    TrType type;
    
    lem::Ptr<bool> v_bool;
    lem::Ptr<int> v_int;
    lem::Ptr<lem::UCString> v_string;
    lem::Ptr<Solarix::Tree_Node> v_tree;
    lem::Ptr<Solarix::Variator> v_trees;
    lem::Ptr<TrTuple> v_tuple;

    TrFunCall *v_fun;
    int *v_fun_count;

    TrClosureVars *v_closure;
    int *v_closure_count;

   public:
    TrValue(void);
    TrValue( const TrValue &x );
    TrValue( const lem::Ptr<TrValue> & x );

    TrValue( const Variator &v );
    TrValue( Variator *v, bool do_delete );

    TrValue( Tree_Node &v );
    TrValue( const Tree_Node &v );
    TrValue( Tree_Node *v, bool do_delete );
    TrValue( const Tree_Node *v, bool always_false_do_delete );
    TrValue( const TrFunCall *v, TrClosureVars *closure_vars=NULL );

    TrValue( TrTuple *x, bool do_delete );

    TrValue( const lem::UCString & v );
    TrValue( const wchar_t * v );

    void operator=( const TrValue &x );

    ~TrValue(void);

    bool IsNull(void) const;

    bool eq( const lem::Ptr<TrValue> &x ) const;
    bool eq( const TrValue &x ) const;

    bool eqi( const lem::Ptr<TrValue> &x ) const;
    bool eqi( const TrValue &x ) const;

    const TrType& GetType(void) const { return type; }

    bool GetBool(void) const;
    int GetInt(void) const;
    const lem::UCString& GetString(void) const;

    const Solarix::Tree_Node& GetTree(void) const;
          Solarix::Tree_Node& GetTree(void);

    const Solarix::Variator& GetTrees(void) const;
          Solarix::Variator& GetTrees(void);

    const TrTuple& GetTuple(void) const;
          TrTuple& GetTuple(void);

    const TrFunCall & GetFun(void) const;
    const TrClosureVars * GetClosureVars(void) const;

    void Assign( TrValue &v );
    void Copy( const TrValue &v );

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    void LoadBin( lem::Stream& bin );
    void Link( const TrFunctions &funs );
    #endif

    #if defined SOL_COMPILER
    void RefreshArgumentNames( const TrFunctions &declarations );
    #endif

    void Print( const Solarix::Dictionary &dict, lem::OFormatter &out, const TrValuePrinterDecorator *decorator=NULL ) const;
    void PrintXML( lem::OFormatter &out, const Solarix::Dictionary &dict ) const;
  };



  class TrValuePrinterDecorator : lem::NonCopyable
  {
   public:
    TrValuePrinterDecorator(void) {}
    virtual ~TrValuePrinterDecorator(void) {}

    virtual void PrintString( const wchar_t *str, lem::OFormatter &out ) const=0;
    virtual void OpenTuple( const TrTuple &t, lem::OFormatter &out ) const=0;
    virtual void CloseTuple( const TrTuple &t, lem::OFormatter &out ) const=0;
    virtual void NextTupleItem( const TrTuple &t, lem::OFormatter &out ) const=0;
  };




  class TrTypeValue : public TrValue
  {
   public: TrTypeValue( const TrType &t );
  };

  class TrBoolValue : public TrValue
  {
   public: TrBoolValue( bool v );
  }; 

  class TrIntValue : public TrValue
  {
   public: TrIntValue( int v );
  }; 

  class TrClosureVars
  {
   public:
    #if defined SOL_CAA && !defined SOL_NO_AA
    // Имена и значения локальных переменных из контекста создания лямбда-функции.
    lem::MCollect<lem::UCString> local_name;
    lem::PtrCollect<TrValue> local_value;

    // Имена формальных аргументов вызываемой функции
    lem::MCollect<lem::UCString> arg_name;
    #endif
    
    TrClosureVars(void) {}

    #if defined SOL_CAA && !defined SOL_NO_AA
    TrClosureVars( const TrClosureVars &x );
    void operator=( const TrClosureVars &x );

    void AddVar( const UCString &name, const TrValue &value );
    #endif
  };

  #if defined SOL_CAA
  // ******************************************************
  // Контекст вызова функции - обеспечивает доступ к
  // локальным или внешним переменным.
  // ******************************************************
  class TrYield;
  class TrTrace;
  class TrWideContext;
  class TrMapContext;
  class TrFunContext
  {
   public:
    lem::zbool e_break; // прервать исполнение группы операторов в {...}
    lem::zbool e_return; // для выхода из функции оператором return
    TrWideContext *env;
    TrTrace *trace_log;

   private:
    TrFunContext *parent;

   public:
    TrFunContext( TrWideContext *e ):env(e),trace_log(NULL),parent(NULL) {}
    TrFunContext( TrFunContext *Parent ) : env(NULL),trace_log(NULL),parent(Parent) {}
    TrFunContext( TrFunContext *Parent, TrWideContext *e ) : env(e),trace_log(NULL),parent(Parent) {}

    virtual ~TrFunContext(void) {}

    virtual lem::Ptr<TrValue> GetVar( const UCString &name );
    virtual void AddVar( const UCString &name, lem::Ptr<TrValue> value );

    virtual TrYield* GetYield(void);
    virtual TrWideContext* GetWideContext(void);
    virtual TrTrace* GetTrace(void);
    virtual TrMapContext* GetMapping(void);
    virtual Solarix::Variator* GetCurrentVariator(void);
    virtual int GetCurrentPosition(void);
    virtual void PrintVars( Solarix::Dictionary &dict, lem::OFormatter &out ) const;
  };
  #endif


  #if defined SOL_CAA
  // Контекст вызова функции - заданы значения формальных параметров.
  class TrContextInvokation : public TrFunContext
  {
   public:
    lem::MCollect<lem::UCString> arg_name;
    lem::PtrCollect<TrValue> arg_value;
    
   public:
    TrContextInvokation( TrFunContext *parent );
    virtual lem::Ptr<TrValue> GetVar( const UCString &name );
    virtual void AddVar( const UCString &name, lem::Ptr<TrValue> value );
    virtual void PrintVars( Solarix::Dictionary &dict, lem::OFormatter &out ) const;
  };
  #endif



 

  #if defined SOL_LOADTXT && defined SOL_COMPILER
  // ***************************************************************
  // Контекст компиляции - известные на данной стадии  компиляции 
  // (в текущем компилируемом scope) переменные.
  // ***************************************************************
  class TrKnownVars : lem::NonCopyable
  {
   private:
    const TrKnownVars *parent;
    std::map< UCString, TrType > vars;
   
   public:
    TrKnownVars(void);
    TrKnownVars( const TrKnownVars *OuterBlock );
    ~TrKnownVars(void);

    bool IsVariable( const UCString &name ) const;
    const TrType& GetVarType( const UCString &name ) const;
    void RegisterVar( const TrType &type, const UCString &name );
  };
  #endif



  class TrBuiltInFunSignature
  {
   private:
    wchar_t sign;
    lem::MCollect<int> n_args;

   public:
    TrBuiltInFunSignature( const wchar_t *str );
    TrBuiltInFunSignature( const TrBuiltInFunSignature &x );

    void operator=( const TrBuiltInFunSignature &x );

    bool Check( int n ) const;
  };
 

  class ElapsedTimeConstraint;

  class TrFunctions;
  class TrFunCall
  {
   protected:
    enum { Var, Constant, Assign, Group, User, Return, Declare, If,
           While, For, Break, BuiltIn, CreateWordform, Lambda };

   private:
    int type;

   public:
    int src_location;

   public:
    TrFunCall( int Type );
    TrFunCall( const TrFunCall& x );
    virtual void operator=( const TrFunCall &x );
    virtual ~TrFunCall(void) {}

    #if defined SOL_CAA && !defined SOL_NO_AA
    virtual lem::Ptr<TrValue> Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const=0;
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

    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations ) {}
    #endif

    #if defined SOL_LOADBIN 
    static TrFunCall* load_bin( lem::Stream& binfile );
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &functions ) {}
    #endif

    virtual TrFunCall* clone(void) const=0;
  };



  // *************************
  // Определение функции.
  // *************************
  class TrFunction : lem::NonCopyable
  {
   public:
    lem::UCString name;
    TrType ret_type; // возвращаемый тип

    lem::MCollect<lem::UCString> arg_name; // имена формальных аргументов
    lem::Collect<TrType> arg_type; // типы формальных аргументов

    lem::Ptr<TrFunCall> body;

   public:
    TrFunction(void):ret_type(TrVoidType()) {}
    virtual ~TrFunction(void) {}

    TrFunction* MakeForwardDeclaration(void) const;

    const UCString& GetName(void) const { return name; }

    #if LEM_DEBUGGING==1
    void PrintSignature( lem::OFormatter &out ) const;
    #endif

    // Вернет true, если функция была только объявлена без определения.
    bool IsForwardDeclaration(void) const { return body.IsNull(); }

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    static bool CorrectName( const UCString &x );

    virtual void CompileDeclaration(
                                    PM_Automat &pm,
                                    lem::Iridium::Macro_Parser &txtfile,
                                    TrFunctions &functions,
                                    const TrProcedureDeclaration &procs,
                                    const TrKnownVars *lambda_caller=NULL
                                   );

    virtual TrFunCall* CompileCall(
                                   PM_Automat &pm,
                                   lem::Iridium::Macro_Parser &txtfile, 
                                   TrFunctions &functions,
                                   const TrProcedureDeclaration &procs,
                                   TrKnownVars &known_vars
                                  );
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    virtual void Link( const TrFunctions &functions );
    #endif

    #if defined SOL_COMPILER
    virtual void RefreshArgumentNames( const TrFunctions &declarations );
    #endif
  };


  class TrFun_Lambda;
  class TrFunctions
  {
   public:
    #if defined SOL_CAA
     #if defined LEM_THREADS 
     lem::Process::RWU_Lock cs; // мьютекс для инициализации глобальных переменных
     #endif
    lem::Process::InterlockedInt stat_vars_initialized;
    lem::Ptr<TrContextInvokation> static_vars; // инциализированные глобальные переменные
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    TrKnownVars global_known_vars;
    #endif 

    typedef std::map< lem::UCString, TrFunction* > NAME2FUN;
    NAME2FUN name2fun;

   private:
    lem::PtrCollect<TrFunction> funs;
    std::map<UCString,TrBuiltInFunSignature> builtin;
    std::set<UCString> statements;
    std::set<UCString> condictor_point_funs;
    lem::CloneCollect<TrFunCall> static_functions; // инициализаторы для глобальных переменных

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    TrFun_Lambda* CompileLambdaDeclaration(
                                           PM_Automat &pm,
                                           lem::Iridium::Macro_Parser &txtfile,
                                           const TrProcedureDeclaration &procs,
                                           const TrKnownVars &lambda_caller
                                          );
    #endif

   public:
    TrFunctions(void);
    virtual ~TrFunctions(void) {}

    bool IsFunction( const UCString &fun_name ) const;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    bool IsType( const UCString &t ) const;
    void AddForwardDeclaration( TrFunction *fun );
    const TrFunction * CompileDeclaration(
                                          PM_Automat &pm,
                                          lem::Iridium::Macro_Parser &txtfile,
                                          const TrProcedureDeclaration &procs
                                         );

    TrFunCall* CompileCall(
                           PM_Automat &pm,
                           lem::Iridium::Macro_Parser &txtfile,
                           const TrProcedureDeclaration &procs,
                           TrKnownVars &known_vars
                          );
    bool IsCondictorPointFunction( const lem::UCString &fun ) const;
    void CompileStatic(
                       PM_Automat &pm, 
                       lem::Iridium::Macro_Parser &txtfile,
                       const TrProcedureDeclaration &procs
                      );

    void CompilationFinished(void);
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream& bin );
    #endif

    const TrFunction* Find( const UCString &name ) const;
 
    int CountUserFuns(void) const;

    #if defined SOL_CAA
    void InitializeStatics(
                           const ElapsedTimeConstraint & constraints,
                           PM_Automat &pm,
                           TrTrace *trace_log
                          );
    #endif
  };



  #if defined SOL_LOADTXT && defined SOL_COMPILER
  // *****************************************************
  // Декларации локальных переменных для трансформанты
  // или процедуры.
  // *****************************************************
  class TrCompilationContext : public VariableChecker
  {
   public:
    lem::MCollect<UCString> vars; // объявленные переменные

   private:
    void RegisterVariable( const UCString &name );

   public:
    TrCompilationContext(void);
   
    bool IsVariable( const UCString &name ) const;
    void LoadTxt( PM_Automat &pm, lem::Iridium::Macro_Parser & txtfile, int BrokerToken );
    const lem::MCollect<UCString>& GetVars(void) const { return vars; }

    virtual int Find( const lem::UCString & variable_name ) const;
  };
  #endif



 #if defined SOL_CAA
  // Реализация терминала трассировки - вывод на текстовую консоль
  class TrTraceTTY : public TrTrace
  {
   private:
    Dictionary *dict;
    lem::PtrCollect<TrTraceActor> call_stack;

   public:
    TrTraceTTY( Dictionary *d );

    virtual void Enter( TrTraceActor *a );
    virtual void Leave( TrTraceActor *a );
    virtual void Print( const UFString &str );
  };
  #endif

 }

#endif
