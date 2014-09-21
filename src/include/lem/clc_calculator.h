// -----------------------------------------------------------------------------
// File CLC_CALCULATOR.H
//
// (c) Koziev Elijah
//
// Content:
// Научный калькулятор (парсер выражений) с большим набором специальных функций.
// -----------------------------------------------------------------------------
//
// CD->02.07.1995
// LC->15.08.2009
// --------------

#ifndef LEM_PARSER__H
#define LEM_PARSER__H
#pragma once

 #include <lem/lexers.h>
 #include <lem/ucstring.h>

 #if LEM_PARSER!=1
 #include <lem/math/math.h>
 #endif

 #include <lem/ufstring.h>
 #include <lem/runtime_checks.h>

 namespace lem
 {
  namespace Calc
  { 

 /********************************************************************************
   Настройка пакета на различные области применения осуществляется посредством
   препроцессорных операций. Итак:

    1. Если определен макрос LEM_PARSER и его содержимое == 1, то пакет
       настраивается на поддержку встроенного препроцессора для проекта
       SOLARIS (модуль COMPILER). В этой конфигурации отключается поддержка
       чисел с плавающей точкой, всех функций, исключая преобразователи
       типа string(...) и int(...), а также операторов присваивания '=',
       '+=' и так далее. Добавляется специальная функция defined(...), которая
       помогает определить, была ли уже объявлена переменная.


    2. Если определен макрос LEM_PARSER и его содержимое == 2, то пакет настраивается
       на работу в простом интерпретаторе, к примеру, именно в этой конфигурации
       он работает в программе RULER (УПРАВА), которая входит в состав демонстрационных
       программ Библиотеки INDEPENDENCE. В данной конфигурации подключается
       поддержка операций с плавающей точкой, трансцендентных функций типа sin(..),
       а также операторов присваивания '=', '+=' и так далее.

    3. Если определен макрос LEM_PARSER и его содержимое == 3, то кроме средств,
       описанных в предыдущем пункте, подключается поддержка высших трансцендентных
       (специальных) функций, типа функций Бесселя и так далее.

    4. Если макрос LEM_PARSER не определен, то пакет настраивается для работы
       в простейшем интерпретаторе с поддержкой плавающей точки, но без
       трансцендентных функций.
 *************************************************************************************/

 const int LEM_MAXPARSERSTACK = 64; // Максимальная глубина стека калькулятора

 // -----------------------------------------------------------------
 // Ключевые слова и соответствующие им коды.
 //
 // ВНИМАНИЕ!
 //
 // Коды функций должны лежать в диапазоне между TK_SIN и TK_ROUND.
 //
 // Коды операторов должны лежать в диапазоне между TK_NOT и TK_PAREN.
 // ------------------------------------------------------------------

 enum {
       TK_ILLEGAL     = 0, // Нераспознанный токен
       TK_VARIABLE,        // Специальный внутренний токен

       TK_COMPLEX_END , // }
       TK_COMPLEX_BGN , // {
       TK_INDEX_BGN   , // [
       TK_INDEX_END   , // ]
       TK_APOSTROF    , // '
//       TK_XOR         , // ^^
       TK_ASSIGMENT   , // =
       TK_PLUSASS     , // +=
       TK_MINASS      , // -=
       TK_MULASS      , // *=
       TK_DIVASS      , // /=

       TK_TZ          , // ;
       TK_LIST        , // ,
       TK_TWICE       , // "
       TK_INC         , // ++
       TK_DEC         , // --
       TK_NOT         , // !
       TK_MUL         , // *
       TK_DIV         , // /
       TK_MOD         , // %
       TK_ADD         , // +
       TK_SUB         , // -
       TK_GREATER     , // >
       TK_SMALLER     , // <
       TK_EQU         , // ==
       TK_LE          , // <=
       TK_GE          , // >=
       TK_NE          , // !=
       TK_OR          , // ||
       TK_AND         , // &&
       TK_BITOR       , // |
       TK_BITAND      , // &
       TK_BITXOR      , // ^
       TK_OPAREN      , // (
       TK_CPAREN      , // )

       #if LEM_PARSER==2 || LEM_PARSER==3
       TK_SIN         , // sin(x)
       TK_SEC         , // sec(x)
       TK_COS         , // cos(x)
       TK_COSEC       , // cosec(x)
       TK_TAN         , // tan(x)
       TK_COTAN       , // cotan(x)

       TK_ASIN        , // asin(x)
       TK_ASEC        , // asec(x)
       TK_ACOS        , // acos(x)
       TK_ACOSEC      , // acosec(x)
       TK_ATAN        , // actan(x)
       TK_ACOTAN      , // acotan(x)

       TK_SINH        , // sinh(x)
       TK_SECH        , // sech(x)
       TK_COSH        , // cosh(x)
       TK_COSECH      , // cosech(x)
       TK_TANH        , // tanh(x)
       TK_COTANH      , // cotanh(x)

       TK_ASINH       , // asinh(x)
       TK_ASECH       , // asech(x)
       TK_ACOSH       , // acosh(x)
       TK_ACOSECH     , // acosech(x)
       TK_ATANH       , // atanh(x)
       TK_ACOTANH     , // acotanh(x)

       TK_EXP         , // exp(x)
       TK_EXP10       , // exp10(x)
       TK_LN          , // ln(x)
       TK_LG          , // lg(x)
       TK_ABS         , // abs(x)
       TK_SQRT        , // sqrt(x)
       TK_FACT        , // fact(x)
       TK_POW2        , // pow2(x)
       TK_POW3        , // pow3(x)
       TK_CBRT        , // cbrt(x)
       TK_SIGN        , // sign(x)
       TK_RADTOGRAD   , // radtograd(x)
       TK_GRADTORAD   , // gradtorad(x)
       #endif

       #if LEM_PARSER==3
       TK_BER         , // Ber(x)
       TK_BEI         , // Bei(x)
       TK_KER         , // Ker(x)
       TK_KEI         , // Kei(x)
       TK_J0          , // J0(x)
       TK_I0          , // I0(x)
       TK_Y0          , // Y0(x)
       TK_K0          , // K0(x)
       TK_J1          , // J1(x)
       TK_I1          , // I1(x)
       TK_Y1          , // Y1(x)
       TK_K1          , // K1(x)
       TK_JN          , // J(n,x)
       TK_IN          , // I(n,x)
       TK_YN          , // Y(n,x)
       TK_KN          , // K(n,x)

       TK_TN          , // Tn(n,x)
       TK_UN          , // Un(n,x)
       TK_HN          , // Hn(n,x)

       TK_E1          , // E1(x)
       TK_E3          , // E3(x)
       TK_EN          , // En(n,x)

       TK_GAMMA       , // GAMMA(x)
       TK_LNGAMMA     , // LNGAMMA(x)

       TK_AI          , // Ai(x)
       TK_BI          , // Bi(x)
       TK_AIPRIME     , // Ai_prime(x)
       TK_BIPRIME     , // Bi_prime(x)
       TK_SI          , // Si(x)
       TK_CI          , // Ci(x)
       TK_ERF         , // Erf(x)
       TK_BN          , // Bn(n)
       #endif

       TK_REAL        , // lem::Math::REAL(x)
       TK_ROUND       , // [x]

       TK_DEFINED     , // defined(имя)

       TK_LEN         , // len(str)
       TK_INT         , // int(x)
       TK_STRING      , // string(x)

       TK_UNPLUS      ,
       TK_UNMINUS     ,

       TK_NULL        ,
       TK_FUNCTION    ,
       TK_OPERATOR    ,
       TK_NUMBER      ,
       TK_ANY         ,
       TK_EOL         ,
       TK_TEMP_VAR
      };

 // ----------------------------------------------------------------------
 // При использовании калькулятора для построения интерпретаторов
 // необходимо работать с переменными. Класс VarTable является контейнером
 // для числовых и строковых переменных в программе.
 // ----------------------------------------------------------------------

 // Описатель типа (переменных, функций)
 class VarType
 {
  public:
   // Элементарные типы
   typedef enum {
                 UNKNOWN_TYPE, // тип неизвестен 
                 VOID_VAR,    // void
                 FLOATING_VAR, // Число в формате с плавающей точкой
                 STRING_VAR,   // Строковая константа
                 INT_VAR,      // Целое число
                 BOOL_VAR,     // BOOLEAN
                 STRUCT_VAR,   // Структура (или класс)
                 FUNC_VAR      // Функция
                } SimpleType; 

  private:
   SimpleType type;
   bool constant;
   bool array;
   int array_size; // размер массива (0...array_size-1]

  public:
   VarType(void)
   {
    type = VarType::UNKNOWN_TYPE;
    constant = array = false;
    array_size=-1;
   }

   VarType( SimpleType t )
   {
    type = t;
    constant = array = false;
    array_size=-1;
   }

   VarType( const VarType &x )
   {
    type=x.type;
    constant=x.constant;
    array=x.array;
    array_size=x.array_size;
   }

   const VarType& operator=( const VarType &x )
   {
    type=x.type;
    constant=x.constant;
    array=x.array;
    array_size=x.array_size;
    return *this;
   }

   const VarType& operator=( SimpleType t )
   { 
    type=t;
    constant=array=false;
    array_size=-1;
    return *this;
   }

   inline VarType::SimpleType get_Type(void) const { return type; }

   inline bool is_Defined(void)  const { return type!=UNKNOWN_TYPE;  }
   inline bool is_Floating(void) const { return type==FLOATING_VAR; }   
   inline bool is_Int(void)      const { return type==INT_VAR;      }   
   inline bool is_String(void)   const { return type==STRING_VAR;   }   
   inline bool is_Bool(void)     const { return type==BOOL_VAR;     }   
   inline bool is_Void(void)     const { return type==VOID_VAR;     }   
   inline bool is_Struct(void)   const { return type==STRUCT_VAR;   }   
   inline bool is_Func(void)     const { return type==FUNC_VAR;     }  

   inline bool is_Const(void)    const { return constant;           }
   inline bool is_Array(void)    const { return array;              }
   inline int get_Array_Size(void) const { return array_size; } 

   inline void set_Const(void) { constant=true; }
   inline void set_Void(void) { type=VOID_VAR; }
   inline void set_Int(void) { type=INT_VAR; }
   inline void set_Float(void) { type=FLOATING_VAR; }
   inline void set_String(void) { type=STRING_VAR; }
   inline void set_Bool(void) { type=BOOL_VAR; }
 };


 class CalcVariable
 {
  private:
   VarType type; // Тип переменной.
   lem::UCString name; // Имя переменной.

   // Значение переменной.
   lem::Math::REAL f_value;
   int i_value;
   bool b_value;
    lem::UFString s_value;

  public:
   CalcVariable(void);
   CalcVariable( const CalcVariable& cv );
   CalcVariable( const UCString& Name, const lem::Math::REAL Value );
   CalcVariable( const UCString& Name, int Value );
   CalcVariable( const UCString& Name, bool Value );
   CalcVariable( const UCString& Name, const wchar_t *Value );
   CalcVariable( const UCString& Name, const UFString & Value );
   CalcVariable( VarType Type, const UCString &name );

   CalcVariable& operator=( const CalcVariable &fv );

   CalcVariable& operator=( const lem::Math::REAL x );
   CalcVariable& operator=( int x );
   CalcVariable& operator=( const wchar_t *x );
   CalcVariable& operator=( bool x );

   inline bool operator==( const UCString &Name ) const { return name==Name; }

   inline VarType get_Type(void) const { return type; }
   inline const UCString& get_Name(void) const { return name; }

   inline lem::Math::REAL get_RealValue(void) const { return f_value; }
   inline int get_IntValue(void) const { return i_value; }
   inline const UFString& get_StringValue(void) const { return s_value; }
   inline bool get_BoolValue(void) const { return b_value; }

   CalcVariable& assign( const CalcVariable &t );

   CalcVariable& operator+=( const CalcVariable &t );
   CalcVariable& operator-=( const CalcVariable &t );
   CalcVariable& operator*=( const CalcVariable &t );
   CalcVariable& operator/=( const CalcVariable &t );
   CalcVariable& operator|=( const CalcVariable &t );
   CalcVariable& operator&=( const CalcVariable &t );
   CalcVariable& operator^=( const CalcVariable &t );

   const CalcVariable operator+( const CalcVariable &t ) const;
   const CalcVariable operator-( const CalcVariable &t ) const;
   const CalcVariable operator*( const CalcVariable &t ) const;
   const CalcVariable operator/( const CalcVariable &t ) const;
   const CalcVariable operator%( const CalcVariable &t ) const;
   const CalcVariable operator&&( const CalcVariable &t ) const;
   const CalcVariable operator||( const CalcVariable &t ) const;
   
   const CalcVariable _xor( const CalcVariable &t ) const;
   
   const CalcVariable operator&( const CalcVariable &t ) const;
   const CalcVariable operator|( const CalcVariable &t ) const;
   
   const CalcVariable operator^( const CalcVariable &t ) const;

   const CalcVariable operator==( const CalcVariable &t ) const;
   const CalcVariable operator!=( const CalcVariable &t ) const;
   const CalcVariable operator>=( const CalcVariable &t ) const;
   const CalcVariable operator>( const CalcVariable &t ) const;
   const CalcVariable operator<( const CalcVariable &t ) const;
   const CalcVariable operator<=( const CalcVariable &t ) const;

   const CalcVariable operator++(int);
   CalcVariable& operator++(void);

   const CalcVariable operator--(int);
   CalcVariable& operator--(void);

   const CalcVariable operator-(void) const;
   const CalcVariable operator+(void) const;
   const CalcVariable operator!(void) const;
 };


 // *****************************************
 // Таблица переменных для Интерпретатора.
 // *****************************************
 class VarTable
 {
  private:
   VarTable *parent;
   lem::PtrCollect<CalcVariable> vars;

  public:
   VarTable( VarTable *Parent=NULL );
   virtual ~VarTable(void) {}

   virtual CalcVariable* Find( const UCString &name );
   virtual CalcVariable* FindLocal( const UCString& name );
   virtual void Add( CalcVariable * fv );
   void Clear(void);
 };

 typedef bool(*UserFunction)(
                             const lem::UToken &t,
                             UTextParser &txtfile,
                             CalcVariable **res,
                             bool *did_return
                            );

 // -----------------------------------------------------
 // Элемент стека калькулятора.
 // Может представлять либо команду, либо число-аргумент,
 // либо указатель на переменную в таблице переменных.
 // -----------------------------------------------------
 class ParsToken
 {
  private:
   CalcVariable *var;
   int command; // Если содержит TK_TEMP_VAR, то указатель var должен
                // быть освобожден в деструкторе посредством вызова delete,
                // так как аргументом является временная переменная.

  public:
   ParsToken(void);
   ParsToken( const ParsToken &tk );
   ParsToken( int com );
   ParsToken( CalcVariable *arg, int command );

   ~ParsToken(void);

   ParsToken& operator=( const ParsToken &t );

   lem::Math::REAL Set( lem::Math::REAL v );

   int Set( int v );
   const wchar_t* Set( const wchar_t* v );

   inline bool IsNumber(void) const { return var!=NULL; }
   inline bool IsLValue(void) const { return !!var && command!=TK_TEMP_VAR; }
   inline int get_Command(void) const { return command; }
   inline CalcVariable* get_Operand(void) { return var; }

   ParsToken& assign( const ParsToken &t );
   ParsToken& operator+=( const ParsToken &t );
   ParsToken& operator-=( const ParsToken &t );
   ParsToken& operator*=( const ParsToken &t );
   ParsToken& operator/=( const ParsToken &t );

   const ParsToken operator+( const ParsToken &t ) const;
   const ParsToken operator-( const ParsToken &t ) const;
   const ParsToken operator*( const ParsToken &t ) const;
   const ParsToken operator/( const ParsToken &t ) const;
   const ParsToken operator%( const ParsToken &t ) const;
   const ParsToken operator&&( const ParsToken &t ) const;
   const ParsToken operator||( const ParsToken &t ) const;
   const ParsToken operator&( const ParsToken &t ) const;
   const ParsToken operator|( const ParsToken &t ) const;
   const ParsToken operator^( const ParsToken &t ) const;
   const ParsToken _xor( const ParsToken &t ) const;

   const ParsToken operator==( const ParsToken &t ) const;
   const ParsToken operator!=( const ParsToken &t ) const;
   const ParsToken operator>=( const ParsToken &t ) const;
   const ParsToken operator>( const ParsToken &t ) const;
   const ParsToken operator<( const ParsToken &t ) const;
   const ParsToken operator<=( const ParsToken &t ) const;

   const ParsToken operator++(int);
   ParsToken& operator++(void);

   const ParsToken operator--(int);
   ParsToken& operator--(void);

   const ParsToken operator-(void) const;
   const ParsToken operator+(void) const;
   const ParsToken operator!(void) const;
 };

 struct PToken
 {
  const wchar_t *name;
  int code;
  int noperands;
  int type;

  PToken(
         const wchar_t *Name,
         int Code,
         int Noperands,
         int Type
        )
  {
   name      = Name;
   code      = Code;
   noperands = Noperands;
   type      = Type;
   return;
  }

  PToken( const PToken& pt, int Type )
  {
   name      = pt.name;
   code      = pt.code;
   noperands = pt.noperands;
   type      = Type;
   return;
  }

  PToken( const wchar_t *s, int Type )
  {
   name      = s;
   code      = 0;
   noperands = 0;
   type      = Type;
   return;
  }

  inline int get_Type(void)      const { return type;      }
  inline int get_Code(void)      const { return code;      }
  inline int get_Noperands(void) const { return noperands; }
 };

 extern PToken tokens[];

 // ------------------------------------------------------------------
 // Арифметический стек. Осуществляет разбор выражений, поступающих на
 // вход, и расчет.
 // ------------------------------------------------------------------
 class ParserStack
 {
  private:
   UToken memoria;               // Для информативных сообщений об ошибке сохраняем текущую позицию считывания.
   ParsToken stack[LEM_MAXPARSERSTACK]; // Сам стек
   int TOS;                     // Верхушка стека
   int opened_par;              // Число открытых скобочек
   UTextParser& prg;
   VarTable *var_table;         // Таблица переменных

   inline int get_TOS(void)  const { return TOS; }
   inline int get_Pars(void) const { return opened_par; }

   void push_value( const lem::Math::REAL arg );
   void push_value( int arg );
   void push_value( const wchar_t *arg );
   void push_tmp_var( CalcVariable *arg );
   void push_var( CalcVariable& arg );
   void push_com( int com );
   void push( ParsToken& t );

   ParsToken& pop(void);

   void Reduce(void);
   const ParsToken Result(void);
   int Priority( int com ) const;
   const ParsToken Compute(
                           ParsToken& first,
                           int iFun,
                           ParsToken& second
                          ) const;

   const ParsToken CalcFunction(
                                ParsToken& first,
                                int iFun,
                                ParsToken& second
                               ) const;

   const ParsToken ToReal( ParsToken& ) const;
   int IsDefined(void);

   const ParsToken ToInt( ParsToken& ) const;
   const ParsToken ToString( ParsToken& ) const;
   const ParsToken GetLen( ParsToken& ) const;

   bool IsUnary( int ) const;
   bool IsPostfix( int ) const;

   void error( int code, const wchar_t *dop=NULL ) const;
   void error( int code, const UToken&, const wchar_t *dop=NULL ) const;

   const PToken GetToken( wchar_t *str ) const;

  public:
   ParserStack( UTextParser& src );

   // -----------------------------------------------------------------------------
   // Функция считывает из входного потока лексемы, находит значение выражения
   // и возвращает результат. Хорошо подходит для работы в простых интерпретаторах.
   // -----------------------------------------------------------------------------
   CalcVariable* calculate( VarTable &vt, UserFunction usfunc=NULL );

   lem::Math::REAL get_exp( VarTable &vt, UserFunction usfunc=NULL );
   bool get_bool_exp( VarTable &vt, UserFunction usfunc=NULL );
   int get_int_exp( VarTable &vt, UserFunction usfunc=NULL );
   const UFString get_string_exp( VarTable &vt, UserFunction usfunc=NULL );
 };


   extern void print_error( int code, const wchar_t *dop=NULL );


  } // namespace Calc
 } // namespace lem

#endif
