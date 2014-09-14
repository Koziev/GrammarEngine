// -----------------------------------------------------------------------------
// File IR_MACRO_GROUP.CPP
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
// Класс IR_Macro_Group - набор макрооператоров в операторных скобочках
// #begin...#end
// -----------------------------------------------------------------------------
//
// CD->24.04.1998
// LC->17.02.2010
// --------------

#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro_Group::~IR_Macro_Group(void)
{
 ZAP_A(*this);
 return;
}

void IR_Macro_Group::LoadTxt( Sol_IO &io, UTextParser &txtfile )
{
 // after #begin may be '\n' token. It must be skipped.
 SourceState back = txtfile.tellp();
 if( txtfile.read().GetToken()!=LEM_SOURCE_EOL )
  txtfile.seekp(back);

 // ---------------------------------------------------------
 // Считываем до встречи с двойным токеном #end
 // Read operators from file until EOF reached or (usually)
 // #end operator loaded.
 // ---------------------------------------------------------
 while( !txtfile.eof() )
  {
   const UToken t1 = txtfile.read();
   const UToken t2 = txtfile.read();

   if( t1==Macro_Parser::t_Diez && t2==Macro_Parser::t_End )
    break;

   txtfile.seekp(t1.GetBegin());
   push_back( LoadOperatorTxt(io,txtfile) );
  }

 txtfile.SeekForToken(LEM_SOURCE_EOL);

 return;
}

void IR_Macro_Group::Perform(
                             Sol_IO &io,
                             Collect<UFString> &list,
                             const Collect<IR_Macro_Subst> &subst,
                             const IR_Var_Table &table,
                             const IR_Macro_Table &mt
                            ) const
{
 // Даём каждому из входящих в наш блок операторов отработать.
 for( Container::size_type i=0; i<size(); i++ )
  at(i)->Perform(io,list,subst,table,mt);

 return;
}

