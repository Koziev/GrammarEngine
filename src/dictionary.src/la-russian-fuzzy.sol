// -----------------------------------------------------------------------------
// File LA-RUSSIAN-FUZZY.SOL
//
// (c) Koziev Elijah
//
// Content:
// Морфологический анализатор (лексический автомат) - правила для управления
// работой алгоритма нечёткого сравнения лексем для РУССКОГО ЯЗЫКА, продукционные
// правила для синтеза производных форм (уменьшительных и т.п.).
//
// 19.09.2006 - добавлено большое количество продукционных правил для
// формообразования (dynforms).
// 21.05.2011 - правила усечения префиксов и аффиксов перенесены в отдельный файл
// 22.05.2011 - изменен синтаксис объявления правил фонетической похожести
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->12.10.2011
// --------------


automat la
{
 // Довольно часто вместо О в безударных позициях употребляется А
 similarity "A-O" language=Russian
 { if context "а" then context "о" = 95 }

 similarity "О-А" language=Russian
 { if context "о" then context "а" = 90 }

 similarity "ЩЯ-ЩА" language=Russian
 { if context "щя" then context "ща" = 95 }

 // +++++++++++++++++

 similarity "ЩА-СЧА" language=Russian 
 { if context "ща" then context "сча" = 95 }

 similarity "СЧА-ЩА" language=Russian 
 { if context "сча" then context "ща" = 95 }

 // +++++++++++++++++

 similarity "ШИ-ШЫ" language=Russian 
 { if context "шы" then context "ши" = 95 }

 similarity "ШЮ-ШУ" language=Russian 
 { if context "шю" then context "шу" = 95 }

 similarity "ШУ-ШЮ" language=Russian  // парашют
 { if context "шу" then context "шю" = 95 }

 // +++++++++++++++++

 similarity "ЦИ-ЦЫ" language=Russian  // цинк - цынк
 { if context "ци" then context "цы" = 95 }

 similarity "ЦЫ-ЦИ" language=Russian  // цыпочки - ципочки
 { if context "цы" then context "ци" = 95 }

 // +++++++++++++++++

 similarity "ТСЯ-ТЬСЯ" language=Russian  // гнуться - гнутся
 { if context "тся" then context "ться" = 85 }

 similarity "ТЬСЯ-ТСЯ" language=Russian  // знатся - знаться
 { if context "ться" then context "тся" = 85 }

 // +++++++++++++++++

 similarity "ТС-Ц" language=Russian  //
 { if context "тс" then context "ц" = 85 }

 similarity "Ц-ТС" language=Russian 
 { if context "ц" then context "тс" = 85 }

 // +++++++++++++++++

 similarity "ТСТ-ТС" language=Russian  // соответсвующий
 { if context "тс" then context "тст" = 90 }

 similarity "ТСТ-СТ" language=Russian  // соотвествующий
 { if context "ст" then context "тст" = 90 }

 // +++++++++++++++++

 similarity "ННН-НН" language=Russian  // добавлена лишняя Н в суффиксах причастий СДЕЛАНННЫЙ
 { if context "ннн" then context "нн" = 90 }

 similarity "НН-Н" language=Russian  // добавлена лишняя Н в суффиксах прилагательных СЕРЕБРЯННЫЙ
 { if context "нн" then context "н" = 90 }

 // +++++++++++++++++

 similarity "ЗСК-СК"  language=Russian // французский - француский
 { if context "зск" then context "ск" = 85 }

 similarity "СК-ЗСК" language=Russian 
 { if context "ск" then context "зск" = 85 }

 // +++++++++++++++++

 similarity "ЗП-СП" language=Russian  // безпечный - беспечный
 { if context "зп" then context "сп" = 85 }

 similarity "СП-ЗП" language=Russian  // беспечный - безпечный
 { if context "сп" then context "зп" = 85 }

 // +++++++++++++++++

 similarity "СТН-СН" language=Russian  // постный - посный
 { if context "стн" then context "сн" = 85 }

 similarity "СН-СТН" language=Russian  // посный - постный
 { if context "сн" then context "стн" = 85 }

 // +++++++++++++++++

 similarity "СБ-ЗБ" language=Russian  // сбруя - збруя
 { if context "сб" then context "зб" = 85 }

 similarity "ЗБ-СБ" language=Russian  // збруя - сбруя
 { if context "зб" then context "сб" = 85 }

 // +++++++++++++++++

 similarity "СД-ЗД" language=Russian  // сдесь - здесь
 { if context "сд" then context "зд" = 85 }

 similarity "ЗД-СД" language=Russian  // здесь - сдесь
 { if context "зд" then context "сд" = 85 }

 // +++++++++++++++++

 similarity "ЗГ-СГ" language=Russian  // згорел - сгорел
 { if context "зг" then context "сг" = 85 }

 similarity "СГ-ЗГ" language=Russian  // сгорел - згорел
 { if context "сг" then context "зг" = 58 }

 // +++++++++++++++++

 similarity "СЗ-ЗЗ" language=Russian  // сзади - ззади
 { if context "сз" then context "зз" = 85 }

 similarity "ЗЗ-СЗ" language=Russian  // ззади - ссади
 { if context "зз" then context "сз" = 85 }

 // +++++++++++++++++

 similarity "ЧТ-ШТ" language=Russian  // что - што
 { if context "чт" then context "шт" = 85 }

 similarity "ШТ-ЧТ" language=Russian  // што - что
 { if context "шт" then context "чт" = 85 }

 // +++++++++++++++++

 similarity "Ш-Щ" language=Russian 
 { if context "ш" then context "щ" = 95 }

 similarity "Щ-Ш" language=Russian 
 { if context "щ" then context "ш" = 95 }

 // +++++++++++++++++

 similarity "И-Й" language=Russian 
 { if context "и" then context "й" = 95 }

 similarity "Й-И" language=Russian 
 { if context "й" then context "и" = 95 }

 // +++++++++++++++++

 similarity "Ь-Ъ" language=Russian 
 { if context "ь" then context "ъ" = 95 }

 similarity "Ъ-Ь" language=Russian 
 { if context "ъ" then context "ь" = 95 }


 // +++++++++++++++++

 similarity "Ш-ШЬ" language=Russian 
 { if context "Ш" then context "ШЬ" = 95 }

 similarity "ШЬ-Ш" language=Russian 
 { if context "ШЬ" then context "Ш" = 95 }

 // +++++++++++++++++

 // ------------------------

 similarity "Ф->В" language=Russian 
 { if context "ф" then context "в" = 95 }

 similarity "П->Б" language=Russian 
 { if context "п" then context "б" = 95 }

 similarity "К->Г" language=Russian 
 { if context "к" then context "г" = 95 }

 similarity "Т->Д" language=Russian 
 { if context "т" then context "д" = 95 }

 similarity "Е->Э" language=Russian 
 { if context "е" then context "э" = 95 }

 similarity "Э->Е" language=Russian 
 { if context "э" then context "е" = 95 }

 similarity "И->Е" language=Russian 
 { if context "и" then context "е" = 95 }

 similarity "Е->И" language=Russian 
 { if context "е" then context "и" = 95 }

 similarity "С->З" language=Russian 
 { if context "с" then context "з" = 95 }

 similarity "Ш->Ч" language=Russian 
 { if context "ш" then context "ч" = 95 }

 similarity "Ш->Ж" language=Russian 
 { if context "ш" then context "ж" = 95 }

 similarity "НДЖ->ДЖ" language=Russian 
 { if context "ндж" then context "дж" = 85 }


 // Взаимозамены латиницы и одинаковых по написанию букв кириллицы

 similarity "A1" language=Russian { if context "a" then context "а" = 99 }
 similarity "B1" language=Russian { if context "b" then context "в" = 95 }
 similarity "С1" language=Russian { if context "c" then context "с" = 99 }
 similarity "T1" language=Russian { if context "t" then context "т" = 95 }
 similarity "O1" language=Russian { if context "o" then context "о" = 99 }
 similarity "E1" language=Russian { if context "e" then context "е" = 99 }
 similarity "X1" language=Russian { if context "x" then context "х" = 99 }
 similarity "Ь1" language=Russian { if context "b" then context "ь" = 95 }
 similarity "P1" language=Russian { if context "p" then context "р" = 99 }
 similarity "H1" language=Russian { if context "h" then context "н" = 95 }
 similarity "M1" language=Russian { if context "m" then context "м" = 95 }
 similarity "K1" language=Russian { if context "k" then context "к" = 95 }
 similarity "Y1" language=Russian { if context "y" then context "у" = 95 }
 similarity "U1" language=Russian { if context "u" then context "и" = 95 }

 // Буква 'З' и цифра '3'
 similarity "31" language=Russian { if context "3" then context "З" = 95 }

 similarity "01" language=Russian { if context "0" then context "о" = 95 }



 // Транслитерация

 similarity "translit1" language=Russian { if context "b"   then context "б" = 90 }
 similarity "translit2" language=Russian { if context "v"   then context "в" = 90 }
 similarity "translit3" language=Russian { if context "g"   then context "г" = 90 }
 similarity "translit4" language=Russian { if context "d"   then context "д" = 90 }
 similarity "translit5" language=Russian { if context "jo"   then context "е" = 90 }
 similarity "translit6" language=Russian { if context "yo"   then context "е" = 90 }
 similarity "translit7" language=Russian { if context "zh"   then context "ж" = 90 }
 similarity "translit8" language=Russian { if context "j"    then context "ж" = 90 }
 similarity "translit9" language=Russian { if context "g"    then context "ж" = 90 }
 similarity "translit10" language=Russian { if context "z"   then context "з" = 90 }
 similarity "translit11" language=Russian { if context "i"   then context "и" = 90 }
 similarity "translit12" language=Russian { if context "ij"   then context "й" = 90 }
 similarity "translit13" language=Russian { if context "j"    then context "й" = 90 }
 similarity "translit14" language=Russian { if context "l"   then context "л" = 90 }
 similarity "translit15" language=Russian { if context "n"   then context "н" = 90 }
 similarity "translit16" language=Russian { if context "p"   then context "п" = 90 }
 similarity "translit17" language=Russian { if context "r"   then context "р" = 90 }
 similarity "translit18" language=Russian { if context "f"   then context "ф" = 90 }
 similarity "translit19" language=Russian { if context "e"   then context "э" = 90 }
 similarity "translit20" language=Russian { if context "h"    then context "х" = 90 }
 similarity "translit21" language=Russian { if context "kh"   then context "х" = 90 }
 similarity "translit22" language=Russian { if context "ts"   then context "ц" = 90 }
 similarity "translit23" language=Russian { if context "tz"   then context "ц" = 90 }
 similarity "translit24" language=Russian { if context "ch"   then context "ч" = 90 }
 similarity "translit25" language=Russian { if context "tch"  then context "ч" = 90 }
 similarity "translit26" language=Russian { if context "sh"   then context "ш" = 90 }
 similarity "translit27" language=Russian { if context "shch" then context "щ" = 90 }
 similarity "translit28" language=Russian { if context "y"    then context "ы" = 90 }
 similarity "translit29" language=Russian { if context "yu"   then context "ю" = 90 }
 similarity "translit30" language=Russian { if context "ya"   then context "я" = 90 }

}

