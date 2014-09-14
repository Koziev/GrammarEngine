// -----------------------------------------------------------------------------
// File IR_OPERATOR.CPP
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
// Класс IR_Operator - базовый для создания классов хранения данных
// макрооператоров.
// -----------------------------------------------------------------------------
//
// CD->24.04.1998
// LC->04.01.2009
// --------------

#include <lem/lexers.h>
#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;

/***************************************************************
 Метод считывает из потока txtfile токен и определяет, началом
 какого макрооператора мог бы он оказаться. Возвращается
 указатель на созданный макрооператор.
****************************************************************/
IR_Operator* IR_Operator::LoadOperatorTxt(
                                          Sol_IO &io,
                                          UTextParser &txtfile
                                         )
{
 IR_Operator *res = NULL;

 const UToken tt = txtfile.read();

 if( tt==Macro_Parser::t_Diez )
  {
   const UToken ttt = txtfile.read();

   if( ttt == Macro_Parser::t_Begin )
    {
     res = new IR_Macro_Group;
     txtfile.SeekForToken(LEM_SOURCE_EOL);
    }
   else if( ttt == Macro_Parser::t_If )
    {
     res = new IR_Macro_If;
    }
   else if( ttt == Macro_Parser::t_Error )
    {
     res = new IR_Macro_Error;
    }
   else
    {
     txtfile.Error(ttt,ttt.length());
     throw E_BaseException( L"Unknown macro operator" );
    }
  }
 else
  {
   txtfile.seekp(tt.GetBegin());
   res = new IR_Macro_Text;
  }

 res->LoadTxt(io,txtfile);
 return res;
}

// ---------------------- End Of File [IR_OPERATOR.CPP] ------------------------
