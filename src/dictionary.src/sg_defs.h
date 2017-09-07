// -----------------------------------------------------------------------------
// File SG_DEFS.H
//
// (c) Koziev Elijah
//
// Content:
// Макросы для использвания одновременно модулем Синтаксической
// Грамматики и в ПРИИСК-программах.
//
// Константы для флагов в словарных статьях (значения для полей SG_Entry::flags
// и SG_Entry::flags_2
// -----------------------------------------------------------------------------
//
// CD->31.03.1998
// LC->01.04.2010
// --------------

#if !defined SOL_SYNGRAM_DEFS__H
 #define SOL_SYNGRAM_DEFS__H

 // Основной флаг для статьи, которая ДОЛЖНА отображаться на экране.
 #define SOL_SG_NONTERMINAL_ENTRY 0x0001

 // Основной флаг для статьи, которая НЕ ОТОБРАЖАЕТСЯ на терминале, то есть
 // не имеет текстового представления.
 #define SOL_SG_TERMINAL_ENTRY    0x0000

 // Статья не имеет звукового представления, хотя она МОЖЕТ иметь
 // тексковое представление.
 #define SOL_SG_SILENT_ENTRY     0x0002

 // Статья имеет звуковое представление.
 #define SOL_SG_VOICED_ENTRY       0x0000

 // Статья представляет собой грамматический квантор для специальных целей
 // грамматического анализа.
 #define SOL_SG_QUANTOR_ENTRY     0x0004

 // Статью не надо выгружать в SQL базу
 #define SOL_SG_NOEXPORT 0x0008


 #define nonterminal_entry        0x0001 | 0x0000 // SOL_SG_NONTERMINAL_ENTRY | SOL_SG_VOICED_ENTRY
 #define terminal_entry           0x0000 | 0x0000 // SOL_SG_TERMINAL_ENTRY | SOL_SG_VOICED_ENTRY
 #define terminal_silent_entry    0x0000 | 0x0002 // SOL_SG_TERMINAL_ENTRY | SOL_SG_SILENT_ENTRY
 #define shadow_entry             0x0001 | 0x0002 // SOL_SG_NONTERMINAL_ENTRY | SOL_SG_SILENT_ENTRY
 #define quantor_entry            0x0004 | 0x0001 // SOL_SG_QUANTOR_ENTRY | SOL_SG_NONTERMINAL_ENTRY 
 #define noexport_entry           0x0000 | 0x0008 // SOL_SG_TERMINAL_ENTRY | SOL_SG_NOEXPORT
 #define terminal_silent_noexport 0x0008 | 0x0002 // SOL_SG_NOEXPORT | SOL_SG_TERMINAL_ENTRY | SOL_SG_SILENT_ENTRY
 
 // Syntax analysis flags for phrasal entries
 #define frz_complete_syntax_analysis 0
 #define frz_no_syntax 1

#endif
