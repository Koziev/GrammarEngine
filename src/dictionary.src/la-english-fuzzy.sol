// -----------------------------------------------------------------------------
// File LA-ENGLISH-FUZZY.SOL
//
// (c) Koziev Elijah
//
// Content:
// Лексический Автомат, правила для управления работой Алгоритма Нечёткого
// сравнения мультилексем для АНГЛИЙСКОГО ЯЗЫКА.
// -----------------------------------------------------------------------------
//
// CD->13.07.2005
// LC->22.05.2011
// --------------

automat la
{
 // Довольно часто вместо О в безударных позициях употребляется А
 similarity "th-d" language=English
 { if context "th" then context "d" = 70 }

 similarity "th-t" language=English
 { if context "th" then context "t" = 70 }

 similarity "c-k" language=English
 { if context "c" then context "k" = 90 }

 similarity "k-c" language=English
 { if context "k" then context "c" = 90 }

 similarity "ck-k" language=English
 { if context "ck" then context "k" = 90 }

 similarity "qu-q" language=English
 { if context "qu" then context "q" = 90 }

 similarity "qu-k" language=English
 { if context "qu" then context "k" = 90 }

 similarity "q-k" language=English
 { if context "q" then context "k" = 90 }


 similarity "o-u" language=English
 { if context "c" then context "k" = 80 }

 // *********************************************
 // SHOULD - DO - ROOT - GO
 similarity "ou-oo" language=English
 { if context "ou" then context "oo" = 90 }


 similarity "u-o" language=English
 { if context "u" then context "o" = 90 }

 similarity "ou-o" language=English
 { if context "ou" then context "o" = 90 }

 // *********************************************


 // MULTY
 similarity "y-i" language=English
 { if context "y" then context "i" = 90 }

 
 // *********************************************
 // DIMENSION - REVOLUTION
 similarity "tion-sion" language=English
 { if context "tion" then context "sion" = 90 }

 similarity "sion-tion" language=English
 { if context "sion" then context "tion" = 90 }
 // *********************************************


 similarity "ee-e" language=English
 { if context "ee" then context "e" = 90 }

 // SPEAK
 similarity "ea-e" language=English
 { if context "ee" then context "e" = 90 }

 // intEgration
 similarity "e-i" language=English
 { if context "sion" then context "tion" = 90 }


 // *********************************************


 // FAIND
 similarity "ai-i" language=English
 { if context "ai" then context "i" = 90 }

 // *********************************************


 similarity "ph-f" language=English{ if context "ph" then context "f" = 90 }
 similarity "f-ph" language=English{ if context "f" then context "ph" = 90 }

 // *********************************************


 similarity "s-c" language=English{ if context "s" then context "c" = 80 }
 similarity "c-s" language=English{ if context "c" then context "s" = 80 }

 // *********************************************

 // AUTOMAT
 similarity "au-o" language=English{ if context "au" then context "o" = 90 }
 similarity "o-au" language=English{ if context "o" then context "au" = 90 }

 // *********************************************

 similarity "u-v" language=English{ if context "u" then context "v" = 70 }
 similarity "v-u" language=English{ if context "v" then context "u" = 70 }
 similarity "v-w" language=English{ if context "v" then context "w" = 70 }
 similarity "w-v" language=English{ if context "w" then context "v" = 70 }

 similarity "wh-w" language=English{ if context "wh" then context "w" = 70 }
 similarity "w-wh" language=English{ if context "w"  then context "wh" = 70 }

 // *********************************************

 similarity "ou-au" language=English{ if context "ou" then context "au" = 70 }
 similarity "au-ou" language=English{ if context "au" then context "ou" = 70 }


 // *********************************************

 // XEON - ZEON

 similarity "x-z" language=English{ if context "x" then context "z" = 70 }
 similarity "z-x" language=English{ if context "z" then context "x" = 70 }

 similarity "ks-x" language=English { if context "ks" then context "x" = 70 }
 similarity "x-ks" language=English { if context "x" then context "ks" = 70 }

 similarity "cs-x" language=English { if context "cs" then context "x" = 80 }
 similarity "x-cs" language=English { if context "x" then context "cs" = 80 }

 // *********************************************


 similarity "ss-s" language=English{ if context "ss" then context "s" = 70 }
 similarity "s-ss" language=English{ if context "s" then context "ss" = 70 }

 // *********************************************

 similarity "ll-l" language=English
 { if context "ll" then context "l" = 70 }

 similarity "l-ll" language=English
 { if context "l" then context "ll" = 70 }

 // *********************************************

 similarity "nn-n" language=English
 { if context "nn" then context "n" = 70 }

 similarity "n-nn" language=English
 { if context "n" then context "nn" = 70 }

 // *********************************************

 similarity "tt-t" language=English
 { if context "tt" then context "t" = 70 }

 similarity "t-tt" language=English
 { if context "t" then context "tt" = 70 }

 // *********************************************

 similarity "s-z" language=English
 { if context "s" then context "z" = 70 }

 similarity "z-s" language=English
 { if context "z" then context "s" = 70 }

 // *********************************************

 // HERZ - GYGA

 similarity "h-g" language=English
 { if context "h" then context "g" = 70 }

 similarity "g-h" language=English
 { if context "g" then context "h" = 70 }


 // *********************************************


 similarity "1-l" language=English{ if context "1" then context "l" = 80 }
 similarity "0-o" language=English{ if context "0" then context "o" = 80 }

}

