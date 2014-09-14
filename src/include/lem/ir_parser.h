// -----------------------------------------------------------------------------
// File IR_PARSER.H
//
// (c) Koziev Elijah, Russia, 1995-2008
//
// Content:
// Объявление класса IR_Parser_Stack - парсер препроцессора для парсера IRIDIUM.
//
// 02.06.2004 - замена MCollect на vector
// 23.08.2004 - весь Iridium перенесен в свой namespace.
// 24.10.2004 - обратная замена std::vector на MCollect и Collect - обнаружилась
//              неприятная ошибка генерации кода в MinGW
// -----------------------------------------------------------------------------
//
// CD->02.07.1997
// LC->11.12.2008
// --------------

#ifndef IR_PARSER__H
#define IR_PARSER__H
#pragma once

 #include <lem/config.h>

 #include <lem/fstring.h>
 #include <lem/cstring.h>
 #include <lem/lexers.h>

 namespace lem
 {
  struct Sol_IO;

  namespace Iridium
  {
   using lem::Sol_IO;

   const int SOL_IR_MAXPARSERSTACK1 = 16; // Макс. глубина стека макропарсера

  typedef enum {
               IR_PTK_ILLEGAL = 0, // Нераспознанный токен
               IR_PTK_VARIABLE   ,

               IR_PTK_NULL       ,
               IR_PTK_FUNCTION   ,
               IR_PTK_OPERATOR   ,
               IR_PTK_NUMBER     ,
               IR_PTK_STRING     ,
               IR_PTK_ANY        ,
               IR_PTK_EOL        ,
               IR_PTK_TEMP_VAR
             } Ir_Ptk_Type;


 typedef enum {
               IR_T_UNKNOWN=-1,
               IR_T_LOGNOT,
               IR_T_LOGEQ,
               IR_T_LOGNE,
               IR_T_LOGGT,
               IR_T_LOGLT,
               IR_T_LOGGE,
               IR_T_LOGLE,
               IR_T_ORSIGN,
               IR_T_LOGOR,
               IR_T_AMPERSAND,
               IR_T_LOGAND,
               IR_T_OROUNDPAREN,
               IR_T_CROUNDPAREN,
               IR_T_DEFINED
              } Ir_Token_Key;

 struct IR_Prep_Token
 {
  UCString name;
  Ir_Token_Key key;
  int narg;
  Ir_Ptk_Type type;

  IR_Prep_Token(
                const wchar_t *Name,
                Ir_Token_Key Key,
                int nArg,
                Ir_Ptk_Type Type
               )
  : name(Name)
  { key=Key; narg=nArg; type=Type; }

  
  IR_Prep_Token( const UCString &s, Ir_Ptk_Type Type ) : name(s)
  {
   key       = IR_T_UNKNOWN;
   narg      = 0;
   type      = Type;
  }


  inline Ir_Token_Key GetKey(void)    const { return key;  }
  inline Ir_Ptk_Type  GetType(void)   const { return type; }
  inline int GetnArg(void)            const { return narg; }
  inline const UCString& string(void) const { return name; }
 };

 extern const IR_Prep_Token ir_tokens[];




 class IR_Parser_Variable;


 // *********************************************************************
 // Список лексем, которые должны быть подставлены вместо одного макроса
 // *********************************************************************
 class IR_Macro_Subst : public lem::Collect<UFString>
 {
  private:
   UCString name;

  public:
   IR_Macro_Subst();
   IR_Macro_Subst( const UCString &Name );
   IR_Macro_Subst( const IR_Macro_Subst &s );

   void operator=( const IR_Macro_Subst &s );

   inline const UCString& GetName(void) const { return name; }

   IR_Parser_Variable* CreateVar(void) const;
 };

 // **********************************************
 // Описание формального аргумента макроса - со
 // значением по умолчанию.
 // **********************************************
 struct IR_Formal_Arg : public UCString
 {
  lem::Collect<UFString> def; // Значение по умолчанию.

  IR_Formal_Arg(void);
  IR_Formal_Arg( const UCString& x );
  IR_Formal_Arg( const UCString& x, const lem::Collect<UFString> &Def );
  IR_Formal_Arg( const IR_Formal_Arg &x );

  void operator=( const IR_Formal_Arg &x );
 };

 /**************************************************************
  Заголовок макроса: его имя и список формальных аргументов.
  Список формальных аргументов может быть пустым!
 ***************************************************************/
 class IR_Var_Table;
 class IR_Macro_Head
 {
  private:
   UCString name;               // Имя макроса.
   MCollect<IR_Formal_Arg> arg; // Список формальных аргументов.

   void Init( const IR_Macro_Head &h );

   const UFString get_next(
                           Sol_IO& io,
                           lem::Collect<UFString> &list,
                           int *icursor,
                           UTextParser &txtfile
                          ) const;

  public:
   IR_Macro_Head(void);
   IR_Macro_Head( Sol_IO &io, UTextParser &txtfile );
   IR_Macro_Head( const IR_Macro_Head &h );

   void operator=( const IR_Macro_Head &h );
   void operator=( const UCString &Name );

   void LoadTxt( Sol_IO &io, UTextParser &txtfile );

   inline const UCString& GetName(void) const { return name; }
   inline int GetnArg(void) const { return CastSizeToInt(arg.size()); }
   inline const IR_Formal_Arg& GetArg( int i ) const { return arg[i]; }

   bool DoesMatch(
                  Sol_IO& io,
                  lem::Collect<UFString> &list,
                  int ifirst,
                  UTextParser &txtfile,
                  Collect<IR_Macro_Subst> &subst,
                  int *n_to_reduce,
                  IR_Var_Table *table
                 ) const;
 };

 class IR_Macro_Table;
 class IR_Operator
 {
  private:
   // Блокируем копирование.
   IR_Operator( const IR_Operator &x );
   void Init( const IR_Operator &x );

  public:
   IR_Operator(void) {}

   virtual ~IR_Operator(void) {}
   virtual void LoadTxt( Sol_IO &/*io*/, UTextParser &/*txtfile*/ ) {}
   virtual void Perform(
                        Sol_IO &/*io*/,
                        lem::Collect<UFString> &/*list*/,
                        const lem::Collect<IR_Macro_Subst> &/*subst*/,
                        const IR_Var_Table &/*table*/,
                        const IR_Macro_Table &/*mt*/
                       ) const {}

   static IR_Operator* LoadOperatorTxt( Sol_IO &io, UTextParser &txtfile );
 };

 // *********************************************************************
 // Разновидность макрооператора - список подставляемых лексем. Обращаю
 // внимание на то, что мы храним просто список лексем, никак не помечая
 // те из них, которые являются подставляемыми формальными аргументами.
 // *********************************************************************
 class IR_Macro_Text : public IR_Operator, public MCollect<UCString>
 {
  private:
   // Блокируем копирование.
   IR_Macro_Text( const IR_Macro_Text &x );
   void Init( const IR_Macro_Text &x );

  public:
   IR_Macro_Text(void) {}
   IR_Macro_Text( const UCString &x );

   virtual void LoadTxt( Sol_IO &io, UTextParser &txtfile );
   virtual void Perform(
                        Sol_IO &io,
                        lem::Collect<UFString> &list,
                        const Collect<IR_Macro_Subst> &subst,
                        const IR_Var_Table &table,
                        const IR_Macro_Table &mt
                       ) const;
 };

 // ***********************************************************************
 // Разновидность макрооператора - группа других макрооператоров в фигурных
 // скобочках (как бы стандартный C-блок {...}). Разумеется, ничто не
 // запрещает формировать многократно вложенные блоки...
 // ***********************************************************************
 class IR_Macro_Group : public IR_Operator, public MCollect<IR_Operator*>
 {
  private:
   // Блокируем копирование.
   IR_Macro_Group( const IR_Macro_Group &x );
   void Init( const IR_Macro_Group &x );

  public:
   IR_Macro_Group(void) {}

   virtual ~IR_Macro_Group(void);

   virtual void LoadTxt( Sol_IO &io, UTextParser &txtfile );
   virtual void Perform(
                        Sol_IO &io,
                        lem::Collect<UFString> &list,
                        const Collect<IR_Macro_Subst> &subst,
                        const IR_Var_Table &table,
                        const IR_Macro_Table &mt
                       ) const;
 };

 // **********************************************************************
 // Разновидность макрооператора - условный оператор, позволяет изменить
 // процедуру развертывания макроса, выбрав один из альтернативных путей
 // в зависимости от значения макропеременных.
 // **********************************************************************
 class IR_Macro_If : public IR_Operator
 {
  private:
   MCollect<UToken> condition;
   IR_Operator *then_branch;
   IR_Operator *else_branch;

  public:
   IR_Macro_If(void) { then_branch=else_branch=NULL; }

   virtual ~IR_Macro_If(void);

   virtual void LoadTxt( Sol_IO &io, UTextParser &txtfile );
   virtual void Perform(
                        Sol_IO &io,
                        lem::Collect<UFString> &list,
                        const Collect<IR_Macro_Subst> &subst,
                        const IR_Var_Table &table,
                        const IR_Macro_Table &mt
                       ) const;
 };


 class IR_Macro_Error : public IR_Operator
 {
  private:
   lem::MCollect<lem::UCString> text; // текст выводимого сообщения

   // Блокируем копирование.
   IR_Macro_Error( const IR_Macro_Error &x );
   void Init( const IR_Macro_Error &x );

  public:
   IR_Macro_Error(void);

   virtual void LoadTxt( Sol_IO &io, UTextParser &txtfile );
   virtual void Perform(
                        Sol_IO &io,
                        lem::Collect<UFString> &list,
                        const Collect<IR_Macro_Subst> &subst,
                        const IR_Var_Table &table,
                        const IR_Macro_Table &mt
                       ) const;
 };





 class IR_Parser_Variable;

 // **********************************************
 // Полное определение макроса - заголовок и тело.
 // **********************************************
 class IR_Macro
 {
  protected:
   IR_Macro_Head head;
   IR_Operator* body;

   void Init( const IR_Macro &m );
   void LoadTxt( Sol_IO &io, UTextParser &txtfile );

   // Блокируем копирование.
   IR_Macro( const IR_Macro &m );
   void operator=( const IR_Macro &m );

  public:
   IR_Macro(void) { body = NULL; }

   IR_Macro( Sol_IO &io, UTextParser &txtfile );
   IR_Macro( const UCString &Flag_Name, const UCString &Flag_Content );

   ~IR_Macro(void) { lem_rub_off(body); }

   inline const IR_Macro_Head& GetHead(void) const { return head; }
   inline const IR_Operator& GetBody(void) const { return *body; }

   IR_Parser_Variable* GetVariable( Sol_IO &io ) const;
 };


 class IR_Parser_Variable
 {
  public:
   // Препроцессорные переменные - бывают только двух типов: строковые
   // и целые числа.
   typedef enum
   {
    IR_UNKNOWN_VAR=UNKNOWN,
    IR_STRING_VAR,          // Строковая константа
    IR_INT_VAR,             // Целое число
    IR_STRLIST_VAR          // Список строк
   } PVar_Type;

  private:
   UCString name;      // Имя переменной.

   PVar_Type type;     // Тип переменной.

   // Значение переменной (содержимое).
   int i_value;       // Целочисленное.
   UFString s_value;  // Строковое.

   lem::Collect<UFString> list; // Списочная переменная - особый случай,
                            // при этом поля type, i_value и s_value
                            // устанавливаются по первому элементу
                            // списка.

  public:
   IR_Parser_Variable(void);
   IR_Parser_Variable( const IR_Parser_Variable& cv );
   IR_Parser_Variable(
                      const UCString& Name,
                      int Value,
                      const wchar_t *repr
                     );
   IR_Parser_Variable( const UCString& Name, const wchar_t *Value );
   IR_Parser_Variable( const UCString& Name, const lem::Collect<UFString> &a_list );
  
   IR_Parser_Variable( PVar_Type Type, const UCString &name );

   IR_Parser_Variable& operator=( const IR_Parser_Variable &x );

   bool operator==( const UCString &Name ) const
   { return name==Name; }

   inline PVar_Type GetType(void) const { return type; }
   inline const UCString& GetName(void) const { return name; }

   inline int GetnList(void) const { return CastSizeToInt(list.size()); }
   inline bool IsList(void) const { return list.size()>1; }
   inline const UFString& get( int i ) const { return list[i]; }
   void BuildFromList( const lem::Collect<UFString> &List );
   inline const Collect<UFString>& GetList(void) const { return list; }

   inline int GetIntValue(void) const { return i_value; }
   inline const UFString& GetStringValue(void) const { return s_value; }

   const IR_Parser_Variable operator&&( const IR_Parser_Variable &t ) const;
   const IR_Parser_Variable operator||( const IR_Parser_Variable &t ) const;

   const IR_Parser_Variable operator==( const IR_Parser_Variable &t ) const;
   const IR_Parser_Variable operator!=( const IR_Parser_Variable &t ) const;
   const IR_Parser_Variable operator>( const IR_Parser_Variable &t ) const;
   const IR_Parser_Variable operator>=( const IR_Parser_Variable &t ) const;
   const IR_Parser_Variable operator<( const IR_Parser_Variable &t ) const;
   const IR_Parser_Variable operator<=( const IR_Parser_Variable &t ) const;
   const IR_Parser_Variable operator!(void) const;
 };

 class IR_Var_Table : public MCollect<IR_Parser_Variable*>
 {
  private:
   const IR_Var_Table *prev;

  public:
   IR_Var_Table( const IR_Var_Table *Prev );
   ~IR_Var_Table(void);

   int Find( const UCString &name ) const;
   const IR_Parser_Variable* Seek( const UCString& name ) const;
   void Remove( const UCString &name );
 };

 /*******************************************
  Таблица макросов для Препроцессора.
 *******************************************/
 class IR_Macro_Table : public MCollect<IR_Macro*>
 {
  public:
   IR_Macro_Table(void);
   ~IR_Macro_Table(void);

   int Find( const UCString &name ) const;
   void Add( IR_Macro* m );
 };



 // -----------------------------------------------------
 // Элемент стека калькулятора.
 // Может представлять либо команду, либо число-аргумент,
 // либо указатель на переменную в таблице переменных.
 // -----------------------------------------------------
 class IrPrepParsToken
 {
  private:
   IR_Parser_Variable *var; // Переменная
   Ir_Token_Key command;    // Код команды

   // *********************************************************************
   // Перед выполнением операций проверяем, что хранится именно значение,
   // а не команда.
   // *********************************************************************
   inline void Check_Var(void) const
   {
    if( !var )
     throw ECheckFault(
                       L"Macro parser expression syntax error: "
                       L"operation applyed to command"
                      );
   }

  public:
   IrPrepParsToken(void)
   {
    var     = NULL;
    command = IR_T_UNKNOWN;
   }

   IrPrepParsToken( const IrPrepParsToken &x )
   {
    if( x.var )
     var = new IR_Parser_Variable(*x.var);

    command = x.command;
   }

   IrPrepParsToken( Ir_Token_Key com )
   {
    var=NULL;
    command=com;
   }

   IrPrepParsToken( IR_Parser_Variable *arg )
   {
    var=arg;
    command=IR_T_UNKNOWN;
   }

   ~IrPrepParsToken(void)
   {
    delete var;
    var=NULL;
    command=IR_T_UNKNOWN;
   }

   IrPrepParsToken& operator=( const IrPrepParsToken &x )
   {
    if( this!=&x )
     {
      if( x.var )
       var = new IR_Parser_Variable(*x.var);

      command = x.command;
     }

    return *this; 
   }

   void Set( int value, const wchar_t *repr );
   void Set( const wchar_t *s );

   inline Ir_Token_Key GetCommand(void) const { return command; }
   inline const IR_Parser_Variable* GetOperand(void) const { return var; }

   const IrPrepParsToken operator&&( const IrPrepParsToken &t ) const;
   const IrPrepParsToken operator||( const IrPrepParsToken &t ) const;

   const IrPrepParsToken operator==( const IrPrepParsToken &t ) const;
   const IrPrepParsToken operator!=( const IrPrepParsToken &t ) const;
   const IrPrepParsToken operator>( const IrPrepParsToken &t ) const;
   const IrPrepParsToken operator>=( const IrPrepParsToken &t ) const;
   const IrPrepParsToken operator<( const IrPrepParsToken &t ) const;
   const IrPrepParsToken operator<=( const IrPrepParsToken &t ) const;
   const IrPrepParsToken operator!(void) const;

   inline bool IsNumber(void)  const { return !!var; }
   inline bool IsCommand(void) const { return command!=IR_T_UNKNOWN; }
 };


 // ------------------------------------------------------------------
 // Арифметический стек. Осуществляет разбор выражений, поступающих на
 // вход, и расчет. Используется в препроцессоре (интерпретаторе и
 // компиляторе).
 // ------------------------------------------------------------------
 class IR_Parser_Stack
 {
  private:
   UToken memoria;            // Для информативных сообщений об ошибке сохраняем текущую позицию считывания.
   IrPrepParsToken stack[SOL_IR_MAXPARSERSTACK1]; // Сам стек
   int TOS;                     // Верхушка стека
   int opened_par;              // Число открытых скобочек
   Sol_IO &io;

   inline int GetTOS(void)  const { return TOS; }
   inline int GetPars(void) const { return opened_par; }

   void push_value(
                   int arg,
                   const wchar_t *repr,
                   const IR_Macro_Table &mt
                  );
   void push_value(
                   const wchar_t *arg,
                   const IR_Macro_Table &mt
                  );

   void push_value(
                   const lem::Collect<UFString> &list,
                   const IR_Macro_Table &mt
                  );

   void push_tmp_var(
                     IR_Parser_Variable *arg,
                     const IR_Macro_Table &mt
                    );
   void push_com(
                 Ir_Token_Key com,
                 const IR_Macro_Table &mt
                );
   void push(
             const IrPrepParsToken& t,
             const IR_Macro_Table &mt
            );

   IrPrepParsToken& pop(void);

   void Reduce( const IR_Macro_Table &mt );
   const IrPrepParsToken Result( const IR_Macro_Table &mt );
   int Priority( Ir_Token_Key com ) const;

   const IrPrepParsToken Compute(
                                 const IrPrepParsToken& first,
                                 Ir_Token_Key Operation,
                                 const IrPrepParsToken& second,
                                 const IR_Macro_Table &mt
                                ) const;

   int IsDefined(void);
   bool IsUnary( Ir_Token_Key com ) const;

   const IR_Prep_Token GetToken( const UToken &t ) const;

  public:
   IR_Parser_Stack( Sol_IO &Io );
   IR_Parser_Variable* calculate( const IR_Var_Table &vt, const IR_Macro_Table &mt );

   void Parse(
              UTextParser &txtfile,
              const IR_Var_Table &vt,
              const IR_Macro_Table &mt
             );

   bool Push(
             const UToken &x,
             const UFString &ls,
             const IR_Var_Table &vt,
             const IR_Macro_Table &mt
            );

   bool PushList(
                 const lem::Collect<UFString> &list,
                 const IR_Var_Table &vt,
                 const IR_Macro_Table &mt
                );

   bool  get_bool_exp( const IR_Var_Table &vt, const IR_Macro_Table &mt );
   int   get_int_exp( const IR_Var_Table &vt, const IR_Macro_Table &mt );
   const UFString get_string_exp( const IR_Var_Table &vt, const IR_Macro_Table &mt );
 };

  } // namespace 'Iridium'
 } // namespace 'lem'

#endif
