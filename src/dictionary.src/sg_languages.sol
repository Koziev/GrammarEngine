// This file contains the declarations of language implementations
// More info: http://www.solarix.ru/for_developers/docs/languages.shtml
//
// 30.08.2010 - для русского языка добавлены символы «» как разделители
// 03.09.2010 - правки списка разделителей для японского, китайского, французского языков
// 09.06.2011 - в описания языков добавлены параметры UpperCase и LowerCase, задающие имена символьных операций для изменения регистра
// 21.07.2011 - в описание евроязыков добавлен параметр UseCaseFilter = true, чтобы проектор учитывал регистр слов там, где это
//              возможно, для отсева вариантов.
// 25.10.2011 - для русского языка в разделители предложений добавлены !.. и ?..
// 02.01.2012 - для русского языка добавлен параметр HasOptionalDiacritics=true
// 09.05.2012 - для китайского языка добавлен латинский алфавит
// 13.07.2012 - у французского языка из разделителей убран апостроф '
// 14.07.2012 - у английского языка из разделителей убран апостроф '
// 26.01.2014 - символ троеточия … добавлен в разделители слов
// 22.08.2016 - символ – добавлен в разделители
//
// CD->04.07.2005
// LC->22.02.2016


automat sg
{
 language Neutral
 language Russian
 language English
 language French
 language Spanish
 language Chinese
 language Japanese


 language Neutral
 {
  alphabet Neutral
 }  


 language Russian as RUSSIAN_LANGUAGE
 {
  NativeName = русский
  Name2 = ru
  
  alphabet Russian
  alphabet Latin
  alphabet Neutral

  link <to_english> language English
  link <to_french>  language French
  link <to_spanish> language Spanish
  link <to_japanese> language Japanese

  ParadigmSubst = { "\\&а"  "АЕЁИОУЫЭЮЯ" }
  ParadigmSubst = { "\\&б"  "БВГДЖЗКЛМНПРСТФХЦЧШЩ" }
  ParadigmSubst = { "\\&й"  "ЙЪЬ" }
  ParadigmSubst = { "\\@а"  "[АЕЁИОУЫЭЮЯ]" }
  ParadigmSubst = { "\\@б"  "[БВГДЖЗКЛМНПРСТФХЦЧШЩ]" }
  ParadigmSubst = { "\\@й"  "[ЙЪЬ]" }

  TokenizerSubst = { "\\@А" "АЕЁИОУЫЭЮЯ" }
  TokenizerSubst = { "\\@Б" "БВГДЖЗКЛМНПРСТФХЦЧШЩ" }
  TokenizerSubst = { "\\@Й" "ЙЪЬ" }
  TokenizerSubst = { "\\@а" "аеёиоуыэюя" }
  TokenizerSubst = { "\\@б" "бвгджзклмнпрстфхцчшщ" }
  TokenizerSubst = { "\\@й" "йъь" }

  Segmentation = whitespace 
  WordDelimiters = ";:-–—<>\"'.,!?&=+(){}[]\r\n\t« »“”„/…"
  SentenceDelimiters = { "." "?" "!" ";" "..." "…" "?!" "?.." "!.." "!!!" }
  SentenceBrokerFlags = { UseLexicon "MinFormLen=3" }
  MaxSentenceLen = 1024
  CasingSentBroker = { "т.д." "пр." "др." "т.п." }
  UpperCase = UpperRus
  LowerCase = LowerRus
  UseCaseFilter = true
  DefaultCasing = Lower
  HasOptionalDiacritics = true
  CharsWithOptionalDiacritics = "ёЁ"
  AuxTypeForDiacritics = "yo"

  MIN_STEM_LEN = 3 // минимально допускаемая длина основы (стема)

  SyntacticAnalyzer = "SyntacticAnalysis_ru" // имя процедуры, вызываемой для полного синтаксического анализа
 }


 language English as ENGLISH_LANGUAGE
 {
  NativeName = English
  Name2 = en

  alphabet English
  alphabet Neutral

  link <to_russian> language Russian
  link <to_french>  language French

  ParadigmSubst = { "\\@v" "[aeiouy]" }
  ParadigmSubst = { "\\@c" "[bcdfgjklmnpqrstvz]" }

  TokenizerSubst = { "\\@v" "aeiouy" }
  TokenizerSubst = { "\\@c" "bcdfgjklmnpqrstvxz" }
  TokenizerSubst = { "\\@V" "AEIOUY" }
  TokenizerSubst = { "\\@C" "BCDFGJKLMNPQRSTVXZ" }
  TokenizerSubst = { "\\@L" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" }
  TokenizerSubst = { "\\@l" "abcdefghijklmnopqrstuvwxyz" }


  Segmentation = whitespace 
  WordDelimiters = { "':;-–—<>\"/.,!?&=+(){}[] \r\n\t…|“”’" }

  SentenceDelimiters = { "." "?" "!" ";" "..." "…" "?!" "?.." "!.." "!!!" }
  SentenceBrokerFlags = { UseLexicon MinFormLen=3 }
  MaxSentenceLen = 1024

  UpperCase = UpperEng
  LowerCase = LowerEng
  UseCaseFilter = true
  DefaultCasing = Lower
 }

 
 language French as FRENCH_LANGUAGE
 {
  NativeName = français
  Name2 = fr

  alphabet French 
  alphabet Neutral

  link <to_english> language English
  link <to_russian> language Russian

  WordDelimiters = { ":;-—<>\".,!?&=+(){}[ ]…" "\r\n\t" "«‹›»" }

  ParadigmSubst = { "\\@v" "[aàáâeèéêëiîoòóôuùúû]" }
  ParadigmSubst = { "\\@c" "[bcçdfgjklmnpqrstvz]" }

  Segmentation = whitespace 

  UpperCase = UpperFr
  LowerCase = LowerFr
  UseCaseFilter = true
  DefaultCasing = Lower
 }



 language Spanish as SPANISH_LANGUAGE
 {
  NativeName = { español castellano }
  Name2 = es

  alphabet Spanish
  alphabet Neutral

  link <to_english> language English
  link <to_russian> language Russian

  ParadigmSubst = { "\\@v" "[aàáâeèéêëiìíîïoòóôõöuùúûü]" }

  ParadigmSubst = { "\\@c" "[bcdfgjklmnñpqrstvz]" }

  WordDelimiters = { ";:-<>\".,!¡?¿&=+(){}[] \r\n\t…" }
  SentenceDelimiters = { "." "?" "¿" "!" "¡" ";" "..." "…" "?!" }

  Segmentation = whitespace 
  UseCaseFilter = true
  DefaultCasing = Lower
 }



 language German as GERMAN_LANGUAGE
 {
  NativeName = Deutsch 
  Name2 = de

  alphabet German
  alphabet Neutral

  link <to_english> language English
  link <to_russian> language Russian

  ParadigmSubst = { "\\@v" "[aeiou]" }

  ParadigmSubst = { "\\@c" "[bcdfgjklmnpqrsßtvz]" }

  Segmentation = whitespace 
 } 



 language Chinese as CHINESE_LANGUAGE
 {
  NativeName = { 汉语 漢語 }
  Name2 = ch

  alphabet Neutral
  alphabet Chinese 
  alphabet Latin

  link <to_english> language English
  link <to_russian> language Russian

  WordDelimiters = { " .,!?&-=+(){}[ ]" "\r\n\t" "『』" }

  Segmentation = dictionary_lookup
 } 

 
 
 language Japanese as JAPANESE_LANGUAGE
 {
  NativeName = 日本語
  Name2 = ja

  alphabet Neutral
  alphabet Latin
  alphabet Japanese

  link <to_english> language English
  link <to_russian> language Russian

  // Hiragana
  //SymbolSubset = { "\\@h" "[ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむめもゃやゅゆょよらりるれろゎわゐゑをんゔ゙゚゛゜ゝゞ・]" }

  // Katakana
  //SymbolSubset = { "\\@k" "[ガャヤギグゲゴザジヅズゼゾダヂデドハバビベボパピペポィーマナタサカォァアリミヒニチシッンソノキイルムワヴプラフブヌツスクウレメヘネテヰセケエェユュヲゥロヨョモホトコオヽヾ〃仝々〆ヱ]" }

  // Hiragana+Katakana
  //SymbolSubset = { "\\@x" "[ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむめもゃやゅゆょよらりるれろゎわゐゑをんゔ゙゚゛゜ゝゞ・ガャヤギグゲゴザジヅズゼゾダヂデドハバビベボパピペポィーマナタサカォァアリミヒニチシッンソノキイルムワヴプラフブヌツスクウレメヘネテヰセケエェユュヲゥロヨョモホトコオヽヾ〃仝々〆ヱ]" }

  Segmentation = external
  SegmentationEngine = cabocha_segmenter  // используем внешний сегментатор в виде cabocha_segmenter.dll
  //SyntaxEngine = cabocha_segmenter
  WordDelimiters = { "> ?。！？.,!?&-=+(){}[ ]" "\r\n\t" "「」〝〟“”‘’『』" }
  SentenceDelimiters = { "." "?" "" "!" ";" "。" "！" "？" }
 } 

 language ThesaurusLanguage as THESAURUS_LANGUAGE
 {
  alphabet Latin
 }
  
}
