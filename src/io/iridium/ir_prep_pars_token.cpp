// -----------------------------------------------------------------------------
// File IR_PREP_PARSER_TOKEN.CPP
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
// Реализация класса IrPrepParsToken - считанная препроцессором из текстового
// файла лексема.
// -----------------------------------------------------------------------------
//
// CD->02.07.1997
// LC->01.12.2006
// --------------

#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;

void IrPrepParsToken::Set( int v, const wchar_t* prep )
{
 LEM_CHECKIT_Z(var!=NULL);
 *var=IR_Parser_Variable(L"",v,prep);
 return;
}

void IrPrepParsToken::Set( const wchar_t* v )
{
 LEM_CHECKIT_Z(var!=NULL);
 *var=IR_Parser_Variable(L"",v);
 return;
}

const IrPrepParsToken IrPrepParsToken::operator!(void) const
{
 Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable(!*var) );
}

const IrPrepParsToken IrPrepParsToken::operator && ( const IrPrepParsToken  &t ) const
{
 Check_Var();
 t.Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable( *var && *t.var ) );
}

const IrPrepParsToken IrPrepParsToken::operator || ( const IrPrepParsToken  &t ) const
{
 Check_Var();
 t.Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable( *var || *t.var ) );
}

const IrPrepParsToken IrPrepParsToken::operator == ( const IrPrepParsToken  &t ) const
{
 Check_Var();
 t.Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable( *var == *t.var ) );
}

const IrPrepParsToken IrPrepParsToken::operator != ( const IrPrepParsToken  &t ) const
{
 Check_Var();
 t.Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable( *var != *t.var ) );
}

const IrPrepParsToken IrPrepParsToken::operator > ( const IrPrepParsToken  &t ) const
{
 Check_Var();
 t.Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable( *var > *t.var ) );
}

const IrPrepParsToken IrPrepParsToken::operator >= ( const IrPrepParsToken &t ) const
{
 Check_Var();
 t.Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable( *var >= *t.var ) );
}

const IrPrepParsToken IrPrepParsToken::operator < ( const IrPrepParsToken &t ) const
{
 Check_Var();
 t.Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable( *var < *t.var ) );
}

const IrPrepParsToken IrPrepParsToken::operator <= ( const IrPrepParsToken &t ) const
{
 Check_Var();
 t.Check_Var();
 return IrPrepParsToken( new IR_Parser_Variable( *var <= *t.var ) );
}

// ------------------- End Of File [IR_PREP_PARSER_TOKEN.CPP] ------------------
