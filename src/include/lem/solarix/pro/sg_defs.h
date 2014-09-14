// -----------------------------------------------------------------------------
// File SG_DEFS.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2005
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
// LC->18.01.2005
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


 #define nonterminal_entry       0x0001 | 0x0000 // SOL_SG_NONTERMINAL_ENTRY | SOL_SG_VOICED_ENTRY
 #define terminal_entry          0x0000 | 0x0000 // SOL_SG_TERMINAL_ENTRY | SOL_SG_VOICED_ENTRY
 #define terminal_silent_entry   0x0000 | 0x0002 // SOL_SG_TERMINAL_ENTRY | SOL_SG_SILENT_ENTRY
 #define shadow_entry            0x0001 | 0x0002 // SOL_SG_NONTERMINAL_ENTRY | SOL_SG_SILENT_ENTRY
 #define quantor_entry           0x0004 | 0x0001 // SOL_SG_QUANTOR_ENTRY | SOL_SG_NONTERMINAL_ENTRY 

#endif
// ------------------------- End Of File [SG_DEFS.H] ---------------------------
