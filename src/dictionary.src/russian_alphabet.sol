// -----------------------------------------------------------------------------
// File RUSSIAN_ALPHABET.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Подробнее об алфавитах: http://www.solarix.ru/for_developers/docs/alphabet.shtml
//
// Content:
// Графическая Грамматика: Кириллица.
// -----------------------------------------------------------------------------
//
// CD->20.04.1996
// LC->30.08.2010
// --------------

// ******************************************************************
// Кириллица может быть пропущена при компиляции путем определения
// макроса NORussian в строке запуска транслятора Ygres.
// ******************************************************************
#if !defined(NORussian)

automat gg
{
 А : LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { А а }
 }

 Б : LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Б б }
 }

 В : LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { В в }
 }

 Г: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Г г }
 }

 Д : LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Д д }
 }

 Е : LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { Е е }
  SIZE { Ё ё }
 }

 Ж: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Ж ж }
 }

 З: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { З з }
 }

 И: LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { И и }
 }

 Й: LETTER
 {
  alphabet Russian
  VOWELNESS: SEMIVOWEL
  SIZE { Й й }
 }

 К: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { К к }
 }

 Л: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Л л }
 }

 М: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { М м }
 }

 Н: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Н н }
 }

 О: LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { О о }
 }

 П: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { П п }
 }

 Р: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Р р }
 }

 С: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { С с }
 }

 Т: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Т т }
 }

 У: LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { У у }
 }

 Ф: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Ф ф }
 }

 Х: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Х х }
 }

 Ц: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Ц ц }
 }

 Ч: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Ч ч }
 }

 Ш: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Ш ш }
 }

 Щ: LETTER
 {
  alphabet Russian
  VOWELNESS: CONSONANT
  SIZE { Щ щ }
 }

 Ъ: LETTER
 {
  alphabet Russian
  VOWELNESS: SOUNDLESS
  SIZE { Ъ ъ }
 }

 Ы: LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { Ы ы }
 }

 Ь: LETTER
 {
  alphabet Russian
  VOWELNESS: SOUNDLESS
  SIZE { Ь ь }
 }

 Э: LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { Э э }
 }

 Ю: LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { Ю ю }
 }

 Я: LETTER
 {
  alphabet Russian
  VOWELNESS: VOWEL
  SIZE { Я я }
 }
}

#endif
