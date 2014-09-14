// -----------------------------------------------------------------------------
// File IR_VAR.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Реализация класса IR_Parser_Variable - представление переменной для калькулятора
// в парсере препроцессора. Необходимость обусловлена тем, что препроцессор
// должен уметь выполнять некоторые вычисления - со строковыми переменными и
// с целыми числами, в частности при обработке конструкций типа #if A!="$"+C
// -----------------------------------------------------------------------------
//
// CD->02.07.1997
// LC->17.02.2010
// --------------

#include <lem/conversions.h>
#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;

const wchar_t IR_TRUE_STR[] = L"1";
const wchar_t IR_FALSE_STR[] = L"0";


IR_Parser_Variable::IR_Parser_Variable(void)
{
 i_value = 0;
 type    = IR_UNKNOWN_VAR;
 return;
}

IR_Parser_Variable::IR_Parser_Variable( const IR_Parser_Variable& cv )
 : name(cv.name), list( cv.list )
{
 type    = cv.type;
 i_value = cv.i_value;
 s_value = cv.s_value;
 return;
}



IR_Parser_Variable::IR_Parser_Variable(
                                       PVar_Type Type,      // Тип хранимого значения
                                       const UCString& Name // Имя переменной
                                      )
:name(Name)
{
 type    = Type;
 i_value = 0;

 list.push_back( UFString() );

 return;
}

IR_Parser_Variable::IR_Parser_Variable(
                                       const UCString& Name,
                                       int Value,
                                       const wchar_t *repr
                                      ):name(Name)
{
 type    = IR_INT_VAR;
 i_value = Value;

 if( !*repr )
  s_value = to_ustr(Value).c_str();
 else
  s_value = repr;

 list.push_back( UFString(repr) );

 return;
}




// ************************************************************************
// Создание строковой переменной с указанными именем и содержимым
// ************************************************************************
IR_Parser_Variable::IR_Parser_Variable( const UCString& Name, const wchar_t *Value )
:name(Name)
{
 type = IR_STRING_VAR;

 i_value = 0;
 s_value = Value;

 list.push_back( UFString(Value) );

 return;
}


IR_Parser_Variable::IR_Parser_Variable( const UCString& Name, const lem::Collect<UFString> &a_list )
{
 if( a_list.size()<2 )
  {
   type = IR_STRING_VAR;
   i_value = 0;
   s_value = a_list.empty() ? L"" : a_list.front().c_str();
  }
 else
  {
   type = IR_STRLIST_VAR;
   i_value = 0;
   list = a_list;
  }

 return;
}



IR_Parser_Variable& IR_Parser_Variable::operator=( const IR_Parser_Variable &x )
{
 name    = x.name;
 type    = x.type;

 i_value = x.i_value;
 s_value = x.s_value;
 list    = x.list;

 return *this;
}


/********************************************
 Логическое отрицание содержимого переменной.
*********************************************/
const IR_Parser_Variable IR_Parser_Variable::operator!() const
{
 IR_Parser_Variable res(L"",0);
 res.i_value = !i_value;
 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;
 return res;
}

// Логическое ИЛИ
const IR_Parser_Variable IR_Parser_Variable::operator||( const IR_Parser_Variable &v ) const
{
 IR_Parser_Variable res(L"",0);
 res.i_value = i_value || v.i_value;
 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;
 return res;
}

// Логическое И
const IR_Parser_Variable IR_Parser_Variable::operator&&( const IR_Parser_Variable &v ) const
{
 IR_Parser_Variable res(L"",0);
 res.i_value = i_value && v.i_value;
 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;
 return res;
}


// *******************************************************************
// Равенство содержимого. Допускается сравнение строковой переменной
// с целочисленной.
// *******************************************************************
const IR_Parser_Variable IR_Parser_Variable::operator==( const IR_Parser_Variable &v ) const
{
 IR_Parser_Variable res(L"",0);

 if( type==IR_STRLIST_VAR && v.type==IR_STRLIST_VAR )
  res.i_value = list==v.list;
 else if( type==IR_STRING_VAR || v.type==IR_STRING_VAR )
  res.i_value = s_value==v.s_value;
 else
  res.i_value = i_value==v.i_value;

 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;

 return res;
}


const IR_Parser_Variable IR_Parser_Variable::operator!=( const IR_Parser_Variable &v ) const
{
 IR_Parser_Variable res(L"",0);

 if( type==IR_STRLIST_VAR && v.type==IR_STRLIST_VAR )
  res.i_value = list!=v.list;
 else if( type==IR_STRING_VAR || v.type==IR_STRING_VAR )
  res.i_value = s_value!=v.s_value;
 else
  res.i_value = i_value!=v.i_value;

 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;

 return res;
}

const IR_Parser_Variable IR_Parser_Variable::operator>( const IR_Parser_Variable &v ) const
{
 IR_Parser_Variable res(L"",0);

 if( type==IR_STRLIST_VAR && v.type==IR_STRLIST_VAR )
  {
   LEM_STOPIT;
  }
 else if( type==IR_STRING_VAR || v.type==IR_STRING_VAR )
  res.i_value = s_value>v.s_value;
 else
  res.i_value = i_value>v.i_value;

 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;

 return res;
}

const IR_Parser_Variable IR_Parser_Variable::operator>=( const IR_Parser_Variable &v ) const
{
 IR_Parser_Variable res(L"",0);

 if( type==IR_STRLIST_VAR && v.type==IR_STRLIST_VAR )
  {
   LEM_STOPIT;
  }
 else if( type==IR_STRING_VAR || v.type==IR_STRING_VAR )
  res.i_value = s_value>=v.s_value;
 else
  res.i_value = i_value>=v.i_value;

 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;

 return res;
}

const IR_Parser_Variable IR_Parser_Variable::operator<( const IR_Parser_Variable &v ) const
{
 IR_Parser_Variable res(L"",0);

 if( type==IR_STRLIST_VAR && v.type==IR_STRLIST_VAR )
  {
   LEM_STOPIT;
  }
 else if( type==IR_STRING_VAR || v.type==IR_STRING_VAR )
  res.i_value = s_value<v.s_value;
 else
  res.i_value = i_value<v.i_value;

 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;

 return res;
}

const IR_Parser_Variable IR_Parser_Variable::operator<=( const IR_Parser_Variable &v ) const
{
 IR_Parser_Variable res(L"",0);

 if( type==IR_STRLIST_VAR && v.type==IR_STRLIST_VAR )
  {
   LEM_STOPIT;
  }
 else if( type==IR_STRING_VAR || v.type==IR_STRING_VAR )
  res.i_value = s_value<=v.s_value;
 else
  res.i_value = i_value<=v.i_value;

 res.s_value = res.i_value ? IR_TRUE_STR : IR_FALSE_STR;

 return res;
}


void IR_Parser_Variable::BuildFromList( const lem::Collect<UFString> &List )
{
 list = List;
 return;
}
