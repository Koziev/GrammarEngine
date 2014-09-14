// -----------------------------------------------------------------------------
// File IO_EKEYS.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2003
//
// Content:
// Расширенные коды для специальных клавиш и сочетаний клавиш.
// -----------------------------------------------------------------------------
//
// CD->30.01.99
// LC->08.12.03
// ------------

#ifndef LEM_IO_EXTENDED_KEYS__H
#define LEM_IO_EXTENDED_KEYS__H
#pragma once

 #define LEM_EKEY_ESC             0x001b  // ESC
 #define LEM_EKEY_ENTER           0x000d  // ENTER
 #define LEM_EKEY_CR              0x000a  // ENTER
 #define LEM_EKEY_SPACE           0x0020  // SPACE
 #define LEM_EKEY_BKSP            0x0008  // BACKSPACE

 #define LEM_EKEY_F1              0x3b00u // F1
 #define LEM_EKEY_F2              0x3c00u // F2
 #define LEM_EKEY_F3              0x3d00u // F3
 #define LEM_EKEY_F4              0x3e00u // F4
 #define LEM_EKEY_F5              0x3f00u // F5
 #define LEM_EKEY_F6              0x4000u // F6
 #define LEM_EKEY_F7              0x4100u // F7
 #define LEM_EKEY_F8              0x4200u // F8
 #define LEM_EKEY_F9              0x4300u // F9
 #define LEM_EKEY_F10             0x4400u // F10

 #define LEM_EKEY_SHIFT_F1        0x5400u // Shift-F1
 #define LEM_EKEY_SHIFT_F2        0x5500u // Shift-F2
 #define LEM_EKEY_SHIFT_F3        0x5600u // Shift-F3
 #define LEM_EKEY_SHIFT_F4        0x5700u // Shift-F4
 #define LEM_EKEY_SHIFT_F5        0x5800u // Shift-F5
 #define LEM_EKEY_SHIFT_F6        0x5900u // Shift-F6
 #define LEM_EKEY_SHIFT_F7        0x5a00u // Shift-F7
 #define LEM_EKEY_SHIFT_F8        0x5b00u // Shift-F8
 #define LEM_EKEY_SHIFT_F9        0x5c00u // Shift-F9
 #define LEM_EKEY_SHIFT_F10       0x5d00u // Shift-F10

 #define LEM_EKEY_CTRL_F1         0x5e00u // Ctrl-F1
 #define LEM_EKEY_CTRL_F2         0x5f00u // Ctrl-F2
 #define LEM_EKEY_CTRL_F3         0x6000u // Ctrl-F3
 #define LEM_EKEY_CTRL_F4         0x6100u // Ctrl-F4
 #define LEM_EKEY_CTRL_F5         0x6200u // Ctrl-F5
 #define LEM_EKEY_CTRL_F6         0x6300u // Ctrl-F6
 #define LEM_EKEY_CTRL_F7         0x6400u // Ctrl-F7
 #define LEM_EKEY_CTRL_F8         0x6500u // Ctrl-F8
 #define LEM_EKEY_CTRL_F9         0x6600u // Ctrl-F9
 #define LEM_EKEY_CTRL_F10        0x6700u // Ctrl-F10

 #define LEM_EKEY_ALT_F1          0x6800u // Alt-F1
 #define LEM_EKEY_ALT_F2          0x6900u // Alt-F2
 #define LEM_EKEY_ALT_F3          0x6a00u // Alt-F3
 #define LEM_EKEY_ALT_F4          0x6b00u // Alt-F4
 #define LEM_EKEY_ALT_F5          0x6c00u // Alt-F5
 #define LEM_EKEY_ALT_F6          0x6d00u // Alt-F6
 #define LEM_EKEY_ALT_F7          0x6e00u // Alt-F7
 #define LEM_EKEY_ALT_F8          0x6f00u // Alt-F8
 #define LEM_EKEY_ALT_F9          0x7000u // Alt-F9
 #define LEM_EKEY_ALT_F10         0x7100u // Alt-F10

 #define LEM_EKEY_ALT_A           0x1e00u // Alt-A
 #define LEM_EKEY_ALT_B           0x3000u // Alt-B
 #define LEM_EKEY_ALT_C           0x2e00u // Alt-C
 #define LEM_EKEY_ALT_D           0x2000u // Alt-D
 #define LEM_EKEY_ALT_E           0x1200u // Alt-E
 #define LEM_EKEY_ALT_F           0x2100u // Alt-F
 #define LEM_EKEY_ALT_G           0x2200u // Alt-G
 #define LEM_EKEY_ALT_H           0x2300u // Alt-H
 #define LEM_EKEY_ALT_I           0x1700u // Alt-I
 #define LEM_EKEY_ALT_J           0x2400u // Alt-J
 #define LEM_EKEY_ALT_K           0x2500u // Alt-K
 #define LEM_EKEY_ALT_L           0x2600u // Alt-L
 #define LEM_EKEY_ALT_M           0x3200u // Alt-M
 #define LEM_EKEY_ALT_N           0x3100u // Alt-N
 #define LEM_EKEY_ALT_O           0x1800u // Alt-O
 #define LEM_EKEY_ALT_P           0x1900u // Alt-P
 #define LEM_EKEY_ALT_Q           0x1000u // Alt-Q
 #define LEM_EKEY_ALT_R           0x1300u // Alt-R
 #define LEM_EKEY_ALT_S           0x1f00u // Alt-S
 #define LEM_EKEY_ALT_T           0x1400u // Alt-T
 #define LEM_EKEY_ALT_U           0x1600u // Alt-U
 #define LEM_EKEY_ALT_V           0x2f00u // Alt-V
 #define LEM_EKEY_ALT_W           0x1100u // Alt-W
 #define LEM_EKEY_ALT_X           0x2d00u // Alt-X
 #define LEM_EKEY_ALT_Y           0x1500u // Alt-Y
 #define LEM_EKEY_ALT_Z           0x2c00u // Alt-Z

 #define LEM_EKEY_ALT_0           0x8100u // Alt-0
 #define LEM_EKEY_ALT_1           0x7800u // Alt-1
 #define LEM_EKEY_ALT_2           0x7900u // Alt-2
 #define LEM_EKEY_ALT_3           0x7a00u // Alt-3
 #define LEM_EKEY_ALT_4           0x7b00u // Alt-4
 #define LEM_EKEY_ALT_5           0x7c00u // Alt-5
 #define LEM_EKEY_ALT_6           0x7d00u // Alt-6
 #define LEM_EKEY_ALT_7           0x7e00u // Alt-7
 #define LEM_EKEY_ALT_8           0x7f00u // Alt-8
 #define LEM_EKEY_ALT_9           0x8000u // Alt-9
 #define LEM_EKEY_ALT_MINUS       0x8200u // Alt--
 #define LEM_EKEY_ALT_EQUAL       0x8300u // Alt-=

 #define LEM_EKEY_SHIFT_TAB       0x0f00u // Shift-Tab
 #define LEM_EKEY_INS             0x5200u // Ins
 #define LEM_EKEY_DEL             0x5300u // Del

 #define LEM_EKEY_DOWN            0x5000u // down  
 #define LEM_EKEY_LEFT            0x4b00u // left  
 #define LEM_EKEY_RIGHT           0x4d00u // right arror
 #define LEM_EKEY_UP              0x4800u // up    
 #define LEM_EKEY_END             0x4f00u // End
 #define LEM_EKEY_HOME            0x4700u // Home
 #define LEM_EKEY_PgDn            0x5100u // PgDn
 #define LEM_EKEY_PgUp            0x4900u // PgUp

 #define LEM_EKEY_CTRL_LEFT       0x7300u // ^left
 #define LEM_EKEY_CTRL_RIGHT      0x7400u // ^right
 #define LEM_EKEY_CTRL_END        0x7500u // ^End
 #define LEM_EKEY_CTRL_HOME       0x7700u // ^Home
 #define LEM_EKEY_CTRL_PgDn       0x7600u // ^PgDn
 #define LEM_EKEY_CTRL_PgUp       0x8400u // ^PgUp

 // 101-key Keyboard Extensions Supported by BIOS
 // K indicates a key on the numeric keypad (when not in NumLock mode)

 #define LEM_EKEY_F11             0x8500u // F11
 #define LEM_EKEY_F12             0x8600u // F12
 #define LEM_EKEY_SHIFT_F11       0x8700u // Shft-F11
 #define LEM_EKEY_SHIFT_F12       0x8800u // Shft-F12
 #define LEM_EKEY_CTRL_F11        0x8900u // Ctrl-F11
 #define LEM_EKEY_CTRL_F12        0x8a00u // Ctrl-F12
 #define LEM_EKEY_ALT_F11         0x8b00u // Alt-F11
 #define LEM_EKEY_ALT_F12         0x8c00u // Alt-F12
 #define LEM_EKEY_ALT_OBRACKET    0x1a00u // Alt-[
 #define LEM_EKEY_ALT_CBRACKET    0x1b00u // Alt-]
 #define LEM_EKEY_ALT_SEMICOLON   0x2700u // Alt-;
 #define LEM_EKEY_ALT_APOST       0x2800u // Alt-'
 #define LEM_EKEY_ALT_QUOT        0x2900u // Alt-`
 #define LEM_EKEY_ALT_BSLASH      0x2b00u // Alt-BackSlash
 #define LEM_EKEY_ALT_COMMA       0x3300u // Alt-,
 #define LEM_EKEY_ALT_PERIOD      0x3400u // Alt-.
 #define LEM_EKEY_ALT_SLASH       0x3500u // Alt-/

 #define LEM_EKEY_ALT_BKSP        0x0e00u // Alt-Bksp
 #define LEM_EKEY_ALT_ENTER       0x1c00u // Alt-Enter
 #define LEM_EKEY_ALT_ESC         0x0100u // Alt-Esc
 #define LEM_EKEY_ALT_TAB         0xa500u // Alt-Tab
 #define LEM_EKEY_CTRL_TAB        0x9400u // Ctrl-Tab

 #define LEM_EKEY_ALT_UP          0x9800u // Alt-up     
 #define LEM_EKEY_ALT_DOWN        0xa000u // Alt-down   
 #define LEM_EKEY_ALT_LEFT        0x9b00u // Alt-left   
 #define LEM_EKEY_ALT_RIGHT       0x9d00u // Alt-right arror

 #define LEM_EKEY_ALT_DEL         0xa300u // Alt-Delete
 #define LEM_EKEY_ALT_END         0x9f00u // Alt-End
 #define LEM_EKEY_ALT_HOME        0x9700u // Alt-Home
 #define LEM_EKEY_ALT_INS         0xa200u // Alt-Insert
 #define LEM_EKEY_ALT_PgUp        0x9900u // Alt-PageUp
 #define LEM_EKEY_ALT_PgDn        0xa100u // Alt-PageDown

 #define LEM_EKEY_ALT_K_SLASH     0xa400u // Alt- K /
 #define LEM_EKEY_ALT_K_ASTERISK  0x3700u // Alt- K *
 #define LEM_EKEY_ALT_K_MINUS     0x4a00u // Alt- K -
 #define LEM_EKEY_ALT_K_PLUS      0x4e00u // Alt- K +
 #define LEM_EKEY_ALT_K_ENTER     0xa600u // Alt- K Enter

 #define LEM_EKEY_CTRL_K_SLASH    0x9500u // Ctrl- K /
 #define LEM_EKEY_CTRL_K_ASTERISK 0x9600u // Ctrl- K *
 #define LEM_EKEY_CTRL_K_MINUS    0x8e00u // Ctrl- K -
 #define LEM_EKEY_CTRL_K_PLUS     0x9000u // Ctrl- K +

 #define LEM_EKEY_CTRL_K_8        0x8d00u // Ctrl- K   [8]
 #define LEM_EKEY_CTRL_K_5        0x8f00u // Ctrl- K 5  [5]
 #define LEM_EKEY_CTRL_K_2        0x9100u // Ctrl- K   [2]
 #define LEM_EKEY_CTRL_K_0        0x9200u // Ctrl- K Ins[0]
 #define LEM_EKEY_CTRL_K_PERIOD   0x9300u // Ctrl- K Del[.]

#endif
// --------------------------- End Of File [IO_EKEYS.H] ------------------------
