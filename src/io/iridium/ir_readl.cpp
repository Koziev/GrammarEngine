// -----------------------------------------------------------------------------
// File IR_READL.CPP
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
// Класс BethSourceList - производный от Macro_Parser класс, который черпает
// токены не из текстового потока, а из указанного списка лексем.
// -----------------------------------------------------------------------------
//
// CD->20.02.98
// LC->23.10.04
// ------------

#include <lem/macro_parser.h>

using namespace std;
using namespace lem;
using namespace lem::Iridium;

/****************************************************************************
  List  - список лексем;
  ifrom - начинать копирование лексем с этого индекса.
*****************************************************************************/
BethSourceList::BethSourceList(
                               const MCollect<UToken> &List,
                               int ifrom
                              )
:Macro_Parser()
{
 const int l=List.size();
 text.reserve(l-ifrom);

 for( int i=ifrom; i<l; i++ )
  text.push_back( BethToken( List[i], UNKNOWN, i-ifrom ) );

 next       = 0;
 i_last_tok = -1;
 return;
}

// -------------------------- End Of File [IR_READL.CPP] -----------------------
