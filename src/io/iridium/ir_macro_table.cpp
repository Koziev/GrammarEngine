// -----------------------------------------------------------------------------
// File IR_MACRO_TABLE.CPP
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
// Класс IR_Macro_Table - таблица макросов для препроцессора.
// -----------------------------------------------------------------------------
//
// CD->02.07.1997
// LC->22.01.2009
// --------------

#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro_Table::IR_Macro_Table(void)
{}

IR_Macro_Table::~IR_Macro_Table(void)
{ ZAP_A(*this); }


/****************************************************
 Добавление макроса в список. Если макрос с таким же
 именем уже определен, то заменяем его тело на новое.
*****************************************************/
void IR_Macro_Table::Add( IR_Macro *to_add )
{
 // Если такая переменная уже есть, просто переинициализируем ее.
 for( Container::size_type i=0; i<size(); i++ )
  if( at(i)->GetHead().GetName()==to_add->GetHead().GetName() )
   {
    delete operator[](i);
    operator[](i)=to_add;
    return;
   }

 // Добавляем макрос...
 push_back(to_add);
 return;
}

/*******************************************************************
 Пытаемся найти в таблице макрос с именем name, возвращаем индекс
 элемента таблицы в случае удачи, либо UNKNOWN при неудачном поиске.
********************************************************************/
int IR_Macro_Table::Find( const UCString& name ) const
{
 if( name.empty() )
  return UNKNOWN;

 for( Container::size_type i=0; i<size(); i++ )
  if( (*this)[i]->GetHead().GetName()==name )
   return i;

 return UNKNOWN;
}

// ------------------- End Of File [IR_MACRO_TABLE.CPP] ------------------------
