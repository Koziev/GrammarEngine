// -----------------------------------------------------------------------------
// File IR_MACRO_SUBST.CPP
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
// Реализация класса IR_Macro_Subst - замена для макроса (текст, который
// подставляется вместо макроса).
// -----------------------------------------------------------------------------
//
// CD->12.04.1999
// LC->17.02.2010
// --------------

#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro_Subst::IR_Macro_Subst()
{}

IR_Macro_Subst::IR_Macro_Subst( const UCString &Name ):name(Name)
{}

IR_Macro_Subst::IR_Macro_Subst( const IR_Macro_Subst &s )
: lem::Collect<UFString>(s),name(s.name)
{}

void IR_Macro_Subst::operator=( const IR_Macro_Subst &s )
{
 if( this != &s )
  {
   lem::Collect<UFString>::operator=(s);
   name=s.name;
  }

 return;
}



IR_Parser_Variable* IR_Macro_Subst::CreateVar() const
{
 IR_Parser_Variable *var = new IR_Parser_Variable(
                                          GetName().c_str(),
                                          (!empty() ? front() : UFString(L"")).c_str()
                                         );
 var->BuildFromList( *this );
 return var;
}

