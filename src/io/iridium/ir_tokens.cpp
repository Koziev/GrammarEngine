// -----------------------------------------------------------------------------
// File IR_TOKEN.CPP
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
// Список токенов для препроцессорного парсера. Для каждого токена хранится
// служебная информацию о нем (арность, является ли именем встроенной функции
// типа defined()).
// -----------------------------------------------------------------------------
//
// CD->02.07.97
// LC->07.10.04
// ------------

#include <lem/quantors.h>
#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;

const IR_Prep_Token lem::Iridium::ir_tokens[]=
{
 IR_Prep_Token( L"!",       IR_T_LOGNOT,       1, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"==",      IR_T_LOGEQ,        2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"!=",      IR_T_LOGNE,        2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L">",       IR_T_LOGGT,        2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"<",       IR_T_LOGLT,        2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L">=",      IR_T_LOGGE,        2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"<=",      IR_T_LOGLE,        2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"|",       IR_T_ORSIGN,       2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"||",      IR_T_LOGOR,        2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"&",       IR_T_AMPERSAND,    2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"&&",      IR_T_LOGAND,       2, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"(",       IR_T_OROUNDPAREN,  1, IR_PTK_OPERATOR ),
 IR_Prep_Token( L")",       IR_T_CROUNDPAREN,  1, IR_PTK_OPERATOR ),
 IR_Prep_Token( L"defined", IR_T_DEFINED,      1, IR_PTK_FUNCTION ),
 IR_Prep_Token( L"",        IR_T_UNKNOWN,      0, IR_PTK_NULL     )
};

// ----------------------- End Of File [IR_TOKEN.CPP] --------------------------
