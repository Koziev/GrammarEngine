// -----------------------------------------------------------------------------
// File IR_PARSER_STACK.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс IR_Parser_Stack - Калькулятор для Препроцессора Системы. Разбирает
// входной поток лексем, обеспечиваемый классом UTextSource<LEM_CSTRING_LEN>,
// и производит вычисления выражений. Поддерживает стандартные типы данных
// INT и STRING.
// -----------------------------------------------------------------------------
//
// CD->02.07.1997
// LC->01.12.2006
// --------------

#include <lem/conversions.h>
#include <lem/lexers.h>
#include <lem/sol_io.h>
#include <lem/macro_parser.h>
#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Parser_Stack::IR_Parser_Stack( Sol_IO &Io ):io(Io)
{
 TOS        = 0;
 opened_par = 0;
 return;
}

/********************************************************************
 Производит вычисления логического выражения и возвращает результат.
 Входной параметр vt - текущая таблица макросов, которые используютс
 также и как переменные.
*********************************************************************/
bool IR_Parser_Stack::get_bool_exp(
                                   const IR_Var_Table &vt,
                                   const IR_Macro_Table &mt
                                  )
{
 IR_Parser_Variable *res=calculate(vt,mt);
 const int r=res->GetIntValue();
 delete res;
 return !!r;
}

/********************************************************************
 Аналогично методу get_bool_exp, производит вычисления целочисленного
 выражения и возвращает результат. Входной параметр vt - текуща
 таблица макросов, которые используются также и как переменные.
*********************************************************************/
int IR_Parser_Stack::get_int_exp(
                                   const IR_Var_Table &vt,
                                   const IR_Macro_Table &mt
                                  )
{
 IR_Parser_Variable *res = calculate(vt,mt);
 const int r=res->GetIntValue();
 delete res;
 return r;
}

/*********************************************************************
 Обрабатывает строковое выражение и возвращает результат. Входной
 параметр vt - текущая таблица макросов, которые используются также и
 как переменные.
***********************************************************************/
const UFString IR_Parser_Stack::get_string_exp(
                                                 const IR_Var_Table &vt,
                                                 const IR_Macro_Table &mt
                                                )
{
 IR_Parser_Variable *res = calculate(vt,mt);
 const UFString r=res->GetStringValue();
 delete res;
 return r;
}

/*****************************************************************
 Общая функция для вычисления произвольного выражения. Возвращает
 результат - переменную, причем на вызвавшую процедуру ложитс
 обязанность удалить эту переменную.
******************************************************************/
IR_Parser_Variable* IR_Parser_Stack::calculate(
                                             const IR_Var_Table &/*vt*/,
                                             const IR_Macro_Table &mt
                                            )
{
 Reduce(mt);
 const IrPrepParsToken tk_res=Result(mt);
 IR_Parser_Variable *var_res = new IR_Parser_Variable(*tk_res.GetOperand());
 return var_res;
}

/************************************************************************
 Метод считывает токены из потока txtfile до конца текущей строки и
 помещает их на вычислительный стек.
*************************************************************************/
void IR_Parser_Stack::Parse(
                              UTextParser &txtfile,
                              const IR_Var_Table &vt,
                              const IR_Macro_Table &mt
                             )
{
 while( !txtfile.eof() )
  {
   const UToken t = txtfile.read();
   if( t.GetToken()==LEM_SOURCE_EOL )
    break;

   if( GetToken(t).GetType()==IR_PTK_STRING )
    {
     // Строку в двойных апострофах мы должны считать особым образом,
     // ибо длина лексемы-токена ограничена глобальной константой
     // LEM_CSTRING_LEN.
     txtfile.seekp(t.GetBegin());
     const UFString ls = txtfile.read_fstring();
     Push(t,ls,vt,mt);
    }
   else
    Push(t,t.string().c_str(),vt,mt);
 }

 return;
}

bool IR_Parser_Stack::PushList(
                               const lem::Collect<UFString> &list,
                               const IR_Var_Table &vt,
                               const IR_Macro_Table &mt
                              )
{
 push_value( list, mt );
 return true;
}


bool IR_Parser_Stack::Push(
                           const UToken &tok,
                           const UFString &ls,
                           const IR_Var_Table &vt,
                           const IR_Macro_Table &mt
                          )
{
 memoria=tok;
 bool proceed=true;

 if( memoria.string().empty() )
  return false;

 const IR_Prep_Token tk=GetToken(memoria);

 switch( tk.GetType() )
  {
   case IR_PTK_NUMBER:   // Численное значение просто помещаем на стек
    {
     int dummy;
     to_int(memoria.string().c_str(),&dummy);
     push_value(dummy,memoria.string().c_str(),mt);
     break;
    }

   case IR_PTK_STRING:
    {
     // Строковая константа.
     UFString str=ls; str.strip_quotes();
     push_value( str.c_str(), mt );
     break;
    }

   case IR_PTK_VARIABLE:
    {
     const int ivar=vt.Find(memoria.string());

     if(ivar==UNKNOWN)
      // Lexem is not a variable name, so we consider it as a string
      // constant.
      push_value( memoria.string().c_str(), mt );
     else
      {
       IR_Parser_Variable *tv = new IR_Parser_Variable(*vt[ivar]);
       push_tmp_var(tv,mt);
      }

     break;
    }

   case IR_PTK_FUNCTION:
   case IR_PTK_OPERATOR: // Двухместная или одноместная операци
    {
     if( tk.string()==Macro_Parser::t_CroundParen && GetPars()==0 )
      {
       proceed=false;
       break;
      }

     push_com( tk.GetKey(), mt );
     break;
    }

   case IR_PTK_EOL:
    proceed=false;   // Заканчиваем разборку выражения
    break;

   default:
    proceed=false;   // Заканчиваем разборку выражения
    break;
  }

 return proceed;
}

/***********************************************************
 Выполняем операцию на верхушке стека( если это необходимо).
************************************************************/
void IR_Parser_Stack::Reduce( const IR_Macro_Table &mt )
{
 if( TOS==1 )                          // Если на стеке нет выражений,
  return;                              // то не производим урезание

 if( stack[TOS-2].GetCommand()==IR_T_OROUNDPAREN ) // Если операция - открывающая скобка
  return;                              // то выполнять нечего

 const IrPrepParsToken &op2 = pop();
 const Ir_Token_Key      cm = pop().GetCommand();
 const IrPrepParsToken &op1 = IsUnary(cm) ? op2 : pop();

 const IrPrepParsToken t(Compute( op1, cm, op2, mt ));
 const IrPrepParsToken res(t); // Выполняем
 push(res,mt);
 return;
}

/************************************************************************
 Эта функция возвращает условный номер команды, если это возможно.
 Иначе возвращается особый токен с кодом SOL_IR_PTK_ILLEGAL. Для соотнесения
 слова и кода используется таблица - см. файл ir_token.cpp.
*************************************************************************/
const IR_Prep_Token IR_Parser_Stack::GetToken( const UToken &t ) const
{
 const UCString &str = t.string();

 if( str[0]==L'\n' && !str[1] )
  return IR_Prep_Token( str, IR_PTK_EOL );

 if( in_quotes(str) )
  return IR_Prep_Token( strip_quotes(str), IR_PTK_STRING );

 int i=0;

 // Ищем в таблице.
 while( ir_tokens[i].GetKey() != UNKNOWN )
  if( ir_tokens[i].string() == t )
   return ir_tokens[i];
  else
   i++;

 // Слово в таблице не найдено. Это может быть либо имя переменной,
 // либо число. Первый символ слова - не-цифра ?
 if( is_name(str.c_str()) )
  return IR_Prep_Token(str,IR_PTK_VARIABLE);  // Это имя переменной.

 // Это число (должно быть число!).
 int dummy;
 if( to_int(str.c_str(),&dummy) )
  return IR_Prep_Token(str,IR_PTK_NUMBER);

 return IR_Prep_Token(str,IR_PTK_ILLEGAL);
}

/******************************************************
 Определяет по коду, является ли операция одноместной.
*******************************************************/
bool IR_Parser_Stack::IsUnary( Ir_Token_Key cmd ) const
{
 int i=0;

 while( ir_tokens[i].GetKey()!=UNKNOWN )
  if( ir_tokens[i].GetKey()==cmd )
   return ir_tokens[i].GetnArg()==1;
  else
   i++;

 return false;
}

/********************************************************************
 Завершение арифметического разбора. Сведение стека до одного числа.
*********************************************************************/
const IrPrepParsToken IR_Parser_Stack::Result( const IR_Macro_Table &mt )
{
 // Спускаемся вниз по стеку
 while( TOS>1 )
  {
   int OLDTOS=TOS;
   Reduce(mt); // выполняем операцию...

   if( OLDTOS==TOS )
    io.merr().printf("Preprocessor expression syntax \n");
  }

 if( opened_par != 0 ) // Остались открытые скобочки ?
  io.merr().printf("Остались открытые скобки '(' в выражении для Препроцессора\n");

 // Вершина стека должна быть числом, а не командой!
 if( !stack[0].IsNumber() )
  io.merr().printf("Preprocessor expression syntax \n");

 TOS=0;
 return stack[0];
}

void IR_Parser_Stack::push_value(
                                 int arg,
                                 const wchar_t *repr,
                                 const IR_Macro_Table &mt
                                )
{
 IR_Parser_Variable *cv = new IR_Parser_Variable( L"", arg, repr );
 push( IrPrepParsToken( cv ), mt );
 return;
}


void IR_Parser_Stack::push_value(
                                 const lem::Collect<UFString> &list,
                                 const IR_Macro_Table &mt
                                )
{
 push( IrPrepParsToken( new IR_Parser_Variable( L"", list ) ) , mt );
 return;
}


void IR_Parser_Stack::push_value(
                                 const wchar_t *arg,
                                 const IR_Macro_Table &mt
                                )
{
 push( IrPrepParsToken( new IR_Parser_Variable( L"", arg ) ) , mt );
 return;
}

void IR_Parser_Stack::push_tmp_var(
                                   IR_Parser_Variable *arg,
                                   const IR_Macro_Table &mt
                                  )
{
 push( IrPrepParsToken( arg ) , mt );
 return;
}

void IR_Parser_Stack::push(
                           const IrPrepParsToken &tk,
                           const IR_Macro_Table &mt
                          )
{
 if( tk.IsNumber() )
  {
   // Если размещаем на унарную операцию, то попробробуем выполнить сразу

   if(
      TOS>0 &&
      stack[TOS-1].GetCommand()!=IR_T_OROUNDPAREN &&
      IsUnary( stack[TOS-1].GetCommand() )
     )
    {
     push(
          IrPrepParsToken( Compute( tk, pop().GetCommand(), tk, mt ) ),
          mt
         );
     return;
    }
  }

 if( TOS==SOL_IR_MAXPARSERSTACK1 )
  throw ECheckFault( L"Preprocessor stack overflow: too complex expression" );

 stack[TOS++]=tk;
 return;
}

/*************************************************************************
 Помещение оператора на стек. Проверим, возможно удастся урезать стек...
**************************************************************************/
void IR_Parser_Stack::push_com( Ir_Token_Key com, const IR_Macro_Table &mt )
{
 if( com == IR_T_CROUNDPAREN )                   // Если закрывающая скобка...
  {
   // Произведем урезание стека
   if( TOS<2 )  // Если непарные скобки
    io.merr().printf(": the same marque [%us] for different signals\n");

   // Спускаемся вниз по стеку до встречи с парной скобкой
   while( TOS>0 && stack[TOS-2].GetCommand()!=IR_T_OROUNDPAREN )
    Reduce(mt); // выполняем операцию...

   IrPrepParsToken operand=pop(); // теперь уничтожим открывающую скобку
   pop();               // снимаем скобку
   push(operand,mt);    // число вернем на место
   opened_par--;
   return;
  }

 if( TOS==SOL_IR_MAXPARSERSTACK1 ) // Проверка стека на переполнение
  throw ECheckFault( L"Preprocessor stack overflow: too complex expression" );

 // Проверим, возможно это унарный минус или плюс, или функция
 if( TOS==0 || stack[TOS-1].IsCommand() ) // Если это первая операция в стеке
  {                                       // вообще или она пойдет не после числа
   if( !IsUnary(com) )
    throw ECheckFault( L"Macroprocessor expression contains invalid unary operation" );
  }

 if( com!=IR_T_OROUNDPAREN && !IsUnary(com) )
  if( TOS>2 )                               // Если есть предыдущая операция
   if( !stack[TOS-2].IsNumber() )           // и она имеет смысл
    if( Priority(stack[TOS-2].GetCommand()) >= Priority(com) ) // и ее приоритет больше
     {                                     // то спускаемся по стеку
      // Выполняем команды
      Reduce(mt);
      stack[TOS++]=IrPrepParsToken(com);
      return;
     }

 stack[TOS++]=IrPrepParsToken(com);          // Помещаем токен-команду на стек
 if( com == IR_T_OROUNDPAREN )
  opened_par++;

 return;
}

/**********************************************************************
 Возвращает приоритет операции, заданной параметром com как код токена.
***********************************************************************/
int IR_Parser_Stack::Priority( Ir_Token_Key com ) const
{
 // Приоритеты ( в порядке расположения токенов в таблице).
 // 0 - самый младший приоритет.
 struct Prior { Ir_Token_Key key; int prior; };

 static Prior pri[]={
                     { IR_T_LOGNOT,       10 },   //   '!'
                     { IR_T_LOGNE,        5  },   //   '!='
                     { IR_T_LOGEQ,        5  },   //   '=='
                     { IR_T_LOGGT,        5  },   //   '>'
                     { IR_T_LOGGE,        5  },   //   '>='
                     { IR_T_LOGLT,        5  },   //   '<'
                     { IR_T_LOGLE,        5  },   //   '<='
                     { IR_T_AMPERSAND,    4  },   //   '&'
                     { IR_T_LOGAND,       4  },   //   '&&'
                     { IR_T_ORSIGN,       3  },   //   '|'
                     { IR_T_LOGOR,        3  },   //   '||'
                     { IR_T_OROUNDPAREN,  100 },  //   '('
                     { IR_T_CROUNDPAREN,  2   },  //   ')'
                     { IR_T_DEFINED,      1   }   //   'defined'
                    };

 for( size_t i=0; i<DIM_A(pri); i++ )
  if( pri[i].key==com )
   return pri[i].prior;

 return UNKNOWN;
}

/*************************************************************
 Выполнение специфицированной операции op над двумя элементами
 first и second, обычно снятыми с верхушки стека. Для унарных
 операций (префиксных и постфиксных) используется только
 аргумент first.
**************************************************************/
const IrPrepParsToken IR_Parser_Stack::Compute(
                                               const IrPrepParsToken& first,
                                               Ir_Token_Key op,
                                               const IrPrepParsToken& second,
                                               const IR_Macro_Table &mt
                                              ) const
{
 switch(op)
  {
   case IR_T_LOGEQ:     return first == second;
   case IR_T_LOGNE:     return first != second;
   case IR_T_LOGLT:     return first <  second;
   case IR_T_LOGLE:     return first <= second;
   case IR_T_LOGGT:     return first >  second;
   case IR_T_LOGGE:     return first >= second;
   case IR_T_LOGOR:     return first || second;
   case IR_T_ORSIGN:    return first || second;
   case IR_T_LOGAND:    return first && second;
   case IR_T_AMPERSAND: return first && second;
   case IR_T_LOGNOT:    return !first;
   case IR_T_DEFINED:
    {
     const bool ival = mt.Find( first.GetOperand()->GetName() )!=UNKNOWN;
     IR_Parser_Variable *res = new IR_Parser_Variable(
                                              L"",
                                              ival,
                                              to_ustr( int(ival) ).c_str()
                                             );
     return IrPrepParsToken(res);
    }

   default:
    throw ECheckFault( L"Invalid macroprocessor expression - internal error" );
  }

// return first;
}

/*************************************
 Снятие токена с верхушки стека.
*************************************/
IrPrepParsToken& IR_Parser_Stack::pop(void)
{
 if( TOS==0 ) // Контроль стека на антипереполнение
  throw ECheckFault(L"Preprocessor calculator stack underflow");

 return stack[--TOS];
}
