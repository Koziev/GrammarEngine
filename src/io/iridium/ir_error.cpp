// -----------------------------------------------------------------------------
// File IR_MACRO_ERROR.CPP
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
//  ласс IR_Macro_Error - прерывание трансл€ции с выдачей диагностики
// -----------------------------------------------------------------------------
//
// CD->22.01.2009
// LC->17.02.2010
// --------------

#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro_Error::IR_Macro_Error(void)
{
}


void IR_Macro_Error::LoadTxt( Sol_IO &io, UTextParser &txtfile )
{
 while( !txtfile.eof() )
  {
   const UToken t1 = txtfile.read();

   if( t1.eol() )
    break;

   text.push_back(t1);
  }

 return;
}


void IR_Macro_Error::Perform(
                             Sol_IO &io,
                             Collect<UFString> &list,
                             const Collect<IR_Macro_Subst> &subst,
                             const IR_Var_Table &table,
                             const IR_Macro_Table &mt
                            ) const
{
 io.mecho().printf( "Error" );

 for( lem::Container::size_type i=0; i<text.size(); i++ )
  {
   const UCString &token = text[i];
   int ivar = table.Find(token);
   if( ivar==UNKNOWN )
    {
     io.mecho().printf( " %us", token.c_str() );
    }
   else
    {
     if( table[ivar]->IsList() )
      {
       for( lem::Container::size_type j=0; j<table[ivar]->GetList().size(); j++ )
        io.mecho().printf( " %us", table[ivar]->GetList()[j].c_str() );
      }
     else
      { 
       io.mecho().printf( " %us", table[ivar]->GetStringValue().c_str() );
      }
    }
  }

 io.mecho().eol();
 throw E_ParserError();

 return;
}
