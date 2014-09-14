// -----------------------------------------------------------------------------
// File IR_MACRO_IF.CPP
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
//  ласс IR_Macro_If.
// -----------------------------------------------------------------------------
//
// CD->24.04.1998
// LC->17.02.2010
// --------------

#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro_If::~IR_Macro_If(void)
{
 lem_rub_off(then_branch);
 lem_rub_off(else_branch);
 return;
}

/*******************************************************
 ќбщий формат:

  1.    #if condition
         then_branch
        #else
         else_branch
        #endif

  2.    #if condition
         then_branch
        #endif
*******************************************************/

void IR_Macro_If::LoadTxt( Sol_IO &io, UTextParser &txtfile )
{
 // —читываем условие - лексемы до конца текущей строки.
 else_branch=NULL;

 while( !txtfile.eof() )
  {
   const UToken t = txtfile.read();
   if( t.GetToken()==LEM_SOURCE_EOL )
    break;

   condition.push_back( t );
  }

 // «агружаем об€зательную ветку then.
 then_branch = LoadOperatorTxt(io,txtfile);

 // ¬озможно, присутствует ветка else.
 const UToken t1 = txtfile.read();
 const UToken t2 = txtfile.read();
 if( t1==Macro_Parser::t_Diez && t2==Macro_Parser::t_Else )
  {
   txtfile.SeekForToken( LEM_SOURCE_EOL );
   else_branch = LoadOperatorTxt(io,txtfile);
  }
 else
  txtfile.seekp(t1.GetBegin());

 txtfile.read_it( Macro_Parser::t_Diez );
 txtfile.read_it( Macro_Parser::t_Endif );
 
 txtfile.SeekForToken(LEM_SOURCE_EOL);

 return;
}

static UFString convert_to_ucstring( const UFString &s )
{
 if( lem::in_quotes(s) )
  {
   UFString ss(s);
   ss.strip_quotes();
   ss = lem::left( ss, lem::UCString::max_len-2 );
   ss.dress_quotes();
   return lem::left( ss, lem::UCString::max_len );
  } 
 else
  {
   return lem::left( s, lem::UCString::max_len );
  }
}

void IR_Macro_If::Perform(
                          Sol_IO &io,
                          Collect<UFString> &list,
                          const Collect<IR_Macro_Subst> &subst,
                          const IR_Var_Table &table,
                          const IR_Macro_Table &mt
                         ) const
{
 IR_Parser_Stack stack(io);

 for( Container::size_type i=0; i<condition.size(); i++ )
  {
   // ≈сли лексема condition(i) €вл€етс€ именем макропеременной
   // (список table), то подставл€ем ее фактическое значение.
   const IR_Parser_Variable *var = table.Seek( condition[i].string() );
   if( !!(var) )
    {
     if( var->IsList() )
      stack.PushList( var->GetList(), table, mt );
     else
      {
       if( var->GetList().empty() )
        {
         throw lem::E_BaseException();
        }
 
       UFString us = convert_to_ucstring( var->get(0) );
       
       stack.Push(
                  UToken( us.c_str(), condition[i].GetBegin() ),
                  var->get(0),
                  table,
                  mt
                 );
      }
    }
   else
    stack.Push(
               condition[i],
               UFString(condition[i].c_str()),
               table,
               mt
              );
   }

 const bool res = stack.get_bool_exp(table,mt);

 if( res )
  then_branch->Perform( io, list, subst, table, mt );
 else
  if( !!(else_branch) )
   else_branch->Perform( io, list, subst, table, mt );

 return;
}

