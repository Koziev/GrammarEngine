// -----------------------------------------------------------------------------
// File ENGLISH_ALPHABET.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Подробнее об алфавитах: http://www.solarix.ru/for_developers/docs/alphabet.shtml
//
// Content:
// Алфавит - Латиница.
// -----------------------------------------------------------------------------
//
// CD->20.04.1996
// LC->21.10.2015
// --------------

automat gg
{
 A : LETTER
 {
  alphabet English
  VOWELNESS : VOWEL
  SIZE { A a }
  
  SIZE:BIG  { À }
  SIZE:SMALL { à }

  SIZE:BIG  { Á }
  SIZE:SMALL { á }

  SIZE:BIG  { Â }
  SIZE:SMALL { â }
 }

 B : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { B b }
 }

 C : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { C c }
  
  SIZE:BIG { Ç }
  SIZE:SMALL { ç }
 }

 D : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { D d }
 }

 E : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { E e }
  
  SIZE:BIG   { È }
  SIZE:SMALL { è }
  
  SIZE:BIG   { É }
  SIZE:SMALL { é }
  
  SIZE:BIG   { Ê }
  SIZE:SMALL { ê }
  
  SIZE:BIG   { Ë }
  SIZE:SMALL { ë }
 }

 F : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { F f }
 }

 G : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { G g }
 }

 H : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { H h }
 }

 I : LETTER
 {
  alphabet English
  VOWELNESS: VOWEL
  SIZE { I i }
  
  SIZE:BIG { Ì }
  SIZE:SMALL { ì }
  
  SIZE:BIG { Í }
  SIZE:SMALL { í }
  
  SIZE:BIG { Î }
  SIZE:SMALL { î }
  
  SIZE:BIG { Ï }
  SIZE:SMALL { ï }
 }

 J : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { J j }
 }

 K : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { K k }
 }

 L : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { L l }
 }

 M : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { M m }
 }

 N : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { N n }
 }

 O : LETTER
 {
  alphabet English
  VOWELNESS: VOWEL
  SIZE { O o }
  
  SIZE:BIG { Ò }
  SIZE:SMALL { ò }
  
  SIZE:BIG { Ó }
  SIZE:SMALL { ó }
  
  SIZE:BIG { Ô }
  SIZE:SMALL { ô }
  
  SIZE:BIG { Ö }
  SIZE:SMALL { ö }
 }

 P : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { P p }
 }

 Q : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { Q q }
 }

 R : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { R r }
  SIZE { Ř ř }
 }

 S : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { S s }
 }

 T : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { T t }
 }

 U : LETTER
 {
  alphabet English
  VOWELNESS: VOWEL
  SIZE { U u }
  
  SIZE:BIG { Ú }
  SIZE:SMALL { ú }
  
  SIZE:BIG { Ù }
  SIZE:SMALL { ù }
  
  SIZE:BIG { Û }
  SIZE:SMALL { û }
  
  SIZE:BIG { Ü }
  SIZE:SMALL { ü }
 }

 V : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { V v }
 }

 W : LETTER
 {
  alphabet English
  VOWELNESS: SEMIVOWEL
  SIZE { W w }
 }

 X : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { X x }
 }

 Y : LETTER
 {
  alphabet English
  VOWELNESS: VOWEL
  SIZE { Y y }
 }

 Z : LETTER
 {
  alphabet English
  VOWELNESS: CONSONANT
  SIZE { Z z }
  SIZE { Ž ž }
 }
}
