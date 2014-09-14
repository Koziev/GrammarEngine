// -----------------------------------------------------------------------------
// File IR_MACRO.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Класс IR_Macro - хранилище для определения одного макроса.
// -----------------------------------------------------------------------------
//
// CD->30.07.1997
// LC->17.02.2010
// --------------

#include <lem/conversions.h>
#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro::IR_Macro( Sol_IO &io, UTextParser &txtfile )
{
 LoadTxt(io,txtfile);
 return;
}

// *****************************************************************
// Создание макроса - с именем Flag_name и содержимым Flag_Content
// *****************************************************************
IR_Macro::IR_Macro( const UCString &Flag_Name, const UCString &Flag_Content )
{
 head = Flag_Name;
 body = new IR_Macro_Text(Flag_Content);
 return;
}

/********************************************************************
 Загрузка определения макроса из текстового потока. Курсор чтени
 должен стоять на имени макроса, то есть токен define уже прочитан.
*********************************************************************/
void IR_Macro::LoadTxt( Sol_IO &io, UTextParser &txtfile )
{
 /*
 // Допустим, мы загружаем макрос
 //
 //              #define MACRO \
 //              #begin
 //              ...
 //              #end
 //
 // Тогда символ продолжения '\' после имени макроса должен быть считан и
 // выброшен, ибо он просто позволяет использовать развернутый формат
 // описания макроса.
 */

 head.LoadTxt(io,txtfile);

 const SourceState back = txtfile.tellp();
 if( txtfile.read() != Macro_Parser::t_Backslash )
  txtfile.seekp(back);
 else
  // Прочитываем символ перевода строки
  txtfile.read();

 body = IR_Operator::LoadOperatorTxt(io,txtfile);
 return;
}

/*********************************************************************
 Если определение макроса имело вид #define name xxx, то данный метод
 создает переменную для препроцессорного калькулятора. Если xxx есть
 целое число, то создаваемая переменная будет целочисленной, иначе
 будет строковой. Если же макрос был определен по-другому, то
 возвращаем NULL.
**********************************************************************/
IR_Parser_Variable* IR_Macro::GetVariable( Sol_IO &io ) const
{
 if( !body )
  return NULL;

 IR_Parser_Variable *res=NULL;

 Collect<UFString>     ll;
 Collect<IR_Macro_Subst> subst;

 IR_Var_Table table(NULL);
 IR_Macro_Table mt;
 body->Perform( io, ll, subst, table, mt );

 if( !is_name(head.GetName().c_str()) || head.GetnArg() || ll.size()>1 )
  return NULL;

 const UFString content = !ll.empty() ? ll.front() : UFString(L"");
 int dummy;
 if( to_int(content.c_str(),&dummy) )
  res = new IR_Parser_Variable( head.GetName(), dummy, content.c_str() );
 else
  res = new IR_Parser_Variable( head.GetName(), content.c_str() );

 return res;
}

