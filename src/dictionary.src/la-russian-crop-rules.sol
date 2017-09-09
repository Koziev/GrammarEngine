// -----------------------------------------------------------------------------
// File LA-RUSSIAN-CROP-RULES.SOL
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
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->10.10.2011
// --------------


automat la
{
 // *************************************************************************************
 // *************************************************************************************
 // Правила для применения продуктивных префиксов и аффиксов (динамические словоформы)
 // *************************************************************************************
 // *************************************************************************************

 // ***********************************
 // УМЕНЬШИТЕЛЬНАЯ ФОРМА --> БАЗОВАЯ
 // ***********************************
 crop "КОШЕЧКА" language=Russian
 { if  "ечка$" then  "ка" }

 crop "КОШЕЧКИ" language=Russian
 { if  "ечки$" then  "ки" }

 crop "КОШЕЧКУ" language=Russian
 { if  "ечку$" then  "ку" }

 crop "КОШЕЧЕК" language=Russian
 { if  "ечек$" then  "ек" }

 crop "КОШЕЧКОЙ" language=Russian
 { if  "ечкой$" then  "кой" }

 crop "КОШЕЧКОЮ" language=Russian
 { if  "ечкою$" then  "кою" }

 crop "КОШЕЧКАМИ" language=Russian
 { if  "ечками$" then  "ками" }

 crop "КОШЕЧКЕ" language=Russian
 { if  "ечке$" then  "ке" }

 crop "КОШЕЧКАХ" language=Russian
 { if  "ечках$" then  "ках" }


 crop "СКАЗАВ-СКАЗАВШИ" language=Russian { if  "вши$" then  "в" }

 // *************************

 crop "СИЯНЬЕ"   language=Russian { if  "ье$"   then  "ие"  }
 crop "СИЯНЬЯ"   language=Russian { if  "ья$"   then  "ия"  }
 crop "СИЯНЬЕМ"  language=Russian { if  "ьем$"  then  "ием"  }
 crop "СИЯНЬЯМИ" language=Russian { if  "ьями$" then  "иями"  }
 crop "СИЯНЬЮ"   language=Russian { if  "ью$"   then  "ию"  }
 crop "СИЯНЬЯМ"  language=Russian { if  "ьям$"  then  "иям"  }
 crop "СИЯНЬЯХ"  language=Russian { if  "ьях$"  then  "иях"  }


 crop "СИЯНИЕ"   language=Russian { if  "ие$"   then  "ье"  }
 crop "СИЯНИЯ"   language=Russian { if  "ия$"   then  "ья"  }
 crop "СИЯНИЕМ"  language=Russian { if  "ием$"  then  "ьем"  }
 crop "СИЯНИЯМИ" language=Russian { if  "иями$" then  "ьями"  }
 crop "СИЯНИЮ"   language=Russian { if  "ию$"   then  "ью"  }
 crop "СИЯНИЯМ"  language=Russian { if  "иям$"  then  "ьям"  }
 crop "СИЯНИЯХ"  language=Russian { if  "иях$"  then  "ьях"  }



// ****************************************
// СУЩЕСТВИТЕЛЬНОЕ ---> СУЩЕСТВИТЕЛЬНОЕ
// ****************************************

 // КРУГ - КРУЖОК

 crop "КРУЖОК"   language=Russian { if  "жок$"    then  "г"  }
 crop "КРУЖКИ"   language=Russian { if  "жки$"    then  "ги"  }
 crop "КРУЖКА"   language=Russian { if  "жка$"    then  "га"  }
 crop "КРУЖКОВ"  language=Russian { if  "жков$"   then  "гов"  }
 crop "КРУЖКОМ"  language=Russian { if  "жком$"   then  "гом"  }
 crop "КРУЖКАМИ" language=Russian { if  "жками$"  then  "гами"  }
 crop "КРУЖКУ"   language=Russian { if  "жку$"    then  "гу"  }
 crop "КРУЖКАМ"  language=Russian { if  "жкам$"   then  "гам"  }
 crop "КРУЖКЕ"   language=Russian { if  "жке$"    then  "ге"  }
 crop "КРУЖКАХ"  language=Russian { if  "жках$"   then  "гах"  }



 // ГРЕХ - ГРЕШОК

 crop "ГРЕШОК"   language=Russian { if  "шок$"    then  "х"  }
 crop "ГРЕШКИ"   language=Russian { if  "шки$"    then  "хи"  }
 crop "ГРЕШКА"   language=Russian { if  "шка$"    then  "ха"  }
 crop "ГРЕШКОВ"  language=Russian { if  "шков$"   then  "хов"  }
 crop "ГРЕШКОМ"  language=Russian { if  "шком$"   then  "хом"  }
 crop "ГРЕШКАМИ" language=Russian { if  "шками$"  then  "хами"  }
 crop "ГРЕШКУ"   language=Russian { if  "шку$"    then  "ху"  }
 crop "ГРЕШКАМ"  language=Russian { if  "шкам$"   then  "хам"  }
 crop "ГРЕШКЕ"   language=Russian { if  "шке$"    then  "хе"  }
 crop "ГРЕШКАХ"  language=Russian { if  "шках$"   then  "хах"  }



 // РЕСТРОРАН - РЕСТОРАНЧИК

 crop "РЕСТОРАНЧИК"    language=Russian { if  "чик$"     then  ""  }
 crop "РЕСТОРАНЧИКИ"   language=Russian { if  "чики$"    then  "ы"  }
 crop "РЕСТОРАНЧИКА"   language=Russian { if  "чика$"    then  "а"  }
 crop "РЕСТОРАНЧИКОВ"  language=Russian { if  "чиков$"   then  "ов"  }
 crop "РЕСТОРАНЧИКОМ"  language=Russian { if  "чиком$"   then  "ом"  }
 crop "РЕСТОРАНЧИКАМИ" language=Russian { if  "чиками$"  then  "ами"  }
 crop "РЕСТОРАНЧИКУ"   language=Russian { if  "чику$"    then  "у"  }
 crop "РЕСТОРАНЧИКАМ"  language=Russian { if  "чикам$"   then  "ам"  }
 crop "РЕСТОРАНЧИКЕ"   language=Russian { if  "чике$"    then  "е"  }
 crop "РЕСТОРАНЧИКАХ"  language=Russian { if  "чиках$"   then  "ах"  }


 
 // СТАРУХА - СТАРУШКА

 crop "СТАРУШКА"   language=Russian { if  "шка$"   then  "ха"  }
 crop "СТАРУШКИ"   language=Russian { if  "шки$"   then  "хи"  }
 crop "СТАРУШЕК"   language=Russian { if  "шек$"   then  "х"  }
 crop "СТАРУШКОЙ"  language=Russian { if  "шкой$"  then  "хой"  }
 crop "СТАРУШКОЮ"  language=Russian { if  "шкою$"  then  "хой"  }
 crop "СТАРУШКАМИ" language=Russian { if  "шками$" then  "хами"  }
 crop "СТАРУШКУ"   language=Russian { if  "шку$"   then  "ху"  }
 crop "СТАРУШКАМ"  language=Russian { if  "шкам$"  then  "хам"  }
 crop "СТАРУШКЕ"   language=Russian { if  "шке$"   then  "хе"  }
 crop "СТАРУШКАХ"  language=Russian { if  "шках$"  then  "хах"  }


 
 // ГОРШОК - ГОРШОЧЕК

 crop "ГОРШОЧЕК"   language=Russian { if  "очек$"   then  "ок"  }
 crop "ГОРШОЧКИ"   language=Russian { if  "очки$"   then  "ки"  }
 crop "ГОРШОЧКА"   language=Russian { if  "очка$"   then  "ка"  }
 crop "ГОРШОЧКОВ"  language=Russian { if  "очков$"  then  "ков"  }
 crop "ГОРШОЧКОМ"  language=Russian { if  "очком$"  then  "ком"  }
 crop "ГОРШОЧКАМИ" language=Russian { if  "очками$" then  "ками"  }
 crop "ГОРШОЧКУ"   language=Russian { if  "очку$"   then  "ку"  }
 crop "ГОРШОЧКАМ"  language=Russian { if  "очкам$"  then  "кам"  }
 crop "ГОРШОЧКЕ"   language=Russian { if  "очке$"   then  "ке"  }
 crop "ГОРШОЧКАХ"  language=Russian { if  "очках$"  then  "ках"  }



 // ПОРОГ - ПОРОЖЕК
 
 crop "ПОРОЖЕК"   language=Russian { if  "жек$"    then  "г"  }
 // остальные правила как в КРУГ-КРУЖОК



 // КОСА-КОСИЧКА

 crop "КОСИЧКА"   language=Russian { if  "ичка$"   then  "а"  }
 crop "КОСИЧКИ"   language=Russian { if  "ички$"   then  "ы"  }
 crop "КОСИЧЕК"   language=Russian { if  "ичек$"   then  ""  }
 crop "КОСИЧКОЙ"  language=Russian { if  "ичкой$"  then  "ой"  }
 crop "КОСИЧКОЮ"  language=Russian { if  "ичкою$"  then  "ой"  }
 crop "КОСИЧКАМИ" language=Russian { if  "ичками$" then  "ами"  }
 crop "КОСИЧКУ"   language=Russian { if  "ичку$"   then  "у"  }
 crop "КОСИЧКАМ"  language=Russian { if  "ичкам$"  then  "ам"  }
 crop "КОСИЧКЕ"   language=Russian { if  "ичке$"   then  "е"  }
 crop "КОСИЧКАХ"  language=Russian { if  "ичках$"  then  "ах"  }



 // КОЗА-КОЗОЧКА
 
 crop "КОЗОЧКА"   language=Russian { if  "очка$"   then  "а" }
 crop "КОЗОЧКИ"   language=Russian { if  "очки$"   then  "ы" }
 crop "КОЗОЧЕК"   language=Russian { if  "очек$"   then  "" }
 crop "КОЗОЧКОЙ"  language=Russian { if  "очкой$"  then  "ой" }
 crop "КОЗОЧКОЮ"  language=Russian { if  "очкою$"  then  "ой" }
 crop "КОЗОЧКАМИ" language=Russian { if  "очками$" then  "ами" }
 crop "КОЗОЧКУ"   language=Russian { if  "очку$"   then  "у" }
 crop "КОЗОЧКАМ"  language=Russian { if  "очкам$"  then  "ам" }
 crop "КОЗОЧКЕ"   language=Russian { if  "очке$"   then  "е" }
 crop "КОЗОЧКАХ"  language=Russian { if  "очках$"  then  "ах" }



 // СТОЛ-СТОЛИК

 crop "СТОЛИК"    language=Russian { if  "ик$"    then  "" }
 crop "СТОЛИКИ"   language=Russian { if  "ики$"   then  "ы" }
 crop "СТОЛИКА"   language=Russian { if  "ика$"   then  "а" }
 crop "СТОЛИКОВ"  language=Russian { if  "иков$"  then  "ов" }
 crop "СТОЛИКОМ"  language=Russian { if  "иком$"  then  "ом" }
 crop "СТОЛИКАМИ" language=Russian { if  "иками$" then  "ами" }
 crop "СТОЛИКУ"   language=Russian { if  "ику$"   then  "у" }
 crop "СТОЛИКАМ"  language=Russian { if  "икам$"  then  "ам" }
 crop "СТОЛИКЕ"   language=Russian { if  "ике$"   then  "е" }
 crop "СТОЛИКАХ"  language=Russian { if  "иках$"  then  "ах" }




 // СТУЛ-СТУЛЬЧИК

 crop "СТУЛЬЧИК"    language=Russian { if  "ьчик$"    then  "ок" }
 crop "СТУЛЬЧИКИ"   language=Russian { if  "ьчики$"   then  "ки" }
 crop "СТУЛЬЧИКА"   language=Russian { if  "ьчика$"   then  "ка" }
 crop "СТУЛЬЧИКОВ"  language=Russian { if  "ьчиков$"  then  "ков" }
 crop "СТУЛЬЧИКОМ"  language=Russian { if  "ьчиком$"  then  "ком" }
 crop "СТУЛЬЧИКАМИ" language=Russian { if  "ьчиками$" then  "ками" }
 crop "СТУЛЬЧИКУ"   language=Russian { if  "ьчику$"   then  "ку" }
 crop "СТУЛЬЧИКАМ"  language=Russian { if  "ьчикам$"  then  "кам" }
 crop "СТУЛЬЧИКЕ"   language=Russian { if  "ьчике$"   then  "ке" }
 crop "СТУЛЬЧИКАХ"  language=Russian { if  "ьчиках$"  then  "ках" }




 // ПАПКА - ПАПОЧКА


 crop "ПАПОЧКА"   language=Russian { if  "очка$"   then  "ка" }
 crop "ПАПОЧКИ"   language=Russian { if  "очки$"   then  "ки" }
 crop "ПАПОЧЕК"   language=Russian { if  "очек$"   then  "ок" }
 crop "ПАПОЧКОЙ"  language=Russian { if  "очкой$"  then  "кой" }
 crop "ПАПОЧКОЮ"  language=Russian { if  "очкою$"  then  "кой" }
 crop "ПАПОЧКАМИ" language=Russian { if  "очками$" then  "ками" }
 crop "ПАПОЧКУ"   language=Russian { if  "очку$"   then  "ку" }
 crop "ПАПОЧКАМ"  language=Russian { if  "очкам$"  then  "кам" }
 crop "ПАПОЧКЕ"   language=Russian { if  "очке$"   then  "ке" }
 crop "ПАПОЧКАХ"  language=Russian { if  "очках$"  then  "ках" }



 // БРАТ-БРАТИШКА

 crop "БРАТИШКА"   language=Russian { if  "ишка$"    then  "" }
 crop "БРАТИШКИ"   language=Russian { if  "ишки$"   then  "ья" }
 crop "БРАТИШЕК"   language=Russian { if  "ишек$"  then  "ьев" }
 crop "БРАТИШКОЙ"  language=Russian { if  "ишкой$"  then  "ом" }
 crop "БРАТИШКАМИ" language=Russian { if  "ишками$" then  "ьями" }
 crop "БРАТИШКУ"   language=Russian { if  "ишку$"   then  "у" }
 crop "БРАТИШКАМ"  language=Russian { if  "ишкам$"  then  "ьям" }
 crop "БРАТИШКЕ"   language=Russian { if  "ишке$"   then  "е" }
 crop "БРАТИШКАХ"  language=Russian { if  "ишках$"  then  "ьях" }



 // РУЧКА-РУЧЕЧКА

 crop "РУЧЕЧКА"   language=Russian { if  "ечка$"   then  "ка" }
 crop "РУЧЕЧКИ"   language=Russian { if  "ечки$"   then  "ки" }
 crop "РУЧЕЧЕК"   language=Russian { if  "ечек$"   then  "ок" }
 crop "РУЧЕЧКОЙ"  language=Russian { if  "ечкой$"  then  "кой" }
 crop "РУЧЕЧКОЮ"  language=Russian { if  "ечкою$"  then  "кой" }
 crop "РУЧЕЧКАМИ" language=Russian { if  "ечками$" then  "ками" }
 crop "РУЧЕЧКУ"   language=Russian { if  "ечку$"   then  "ку" }
 crop "РУЧЕЧКАМ"  language=Russian { if  "ечкам$"  then  "кам" }
 crop "РУЧЕЧКЕ"   language=Russian { if  "ечке$"   then  "ке" }
 crop "РУЧЕЧКАХ"  language=Russian { if  "ечках$"  then  "ках" }
 


 
 // РЕКА - РЕЧКА

 crop "РЕЧКА"   language=Russian { if  "чка$"   then  "ка" }
 crop "РЕЧКИ"   language=Russian { if  "чки$"   then  "ки" }
 crop "РЕЧЕК"   language=Russian { if  "чек$"   then  "ок" }
 crop "РЕЧКОЙ"  language=Russian { if  "чкой$"  then  "кой" }
 crop "РЕЧКОЮ"  language=Russian { if  "чкою$"  then  "кой" }
 crop "РЕЧКАМИ" language=Russian { if  "чками$" then  "ками" }
 crop "РЕЧКУ"   language=Russian { if  "чку$"   then  "ку" }
 crop "РЕЧКАМ"  language=Russian { if  "чкам$"  then  "кам" }
 crop "РЕЧКЕ"   language=Russian { if  "чке$"   then  "ке" }
 crop "РЕЧКАХ"  language=Russian { if  "чках$"  then  "ках" }
 

 // ПОПА-ПОПКА

 crop "ПОПКА"   language=Russian { if  "ка$"   then  "а" }
 crop "ПОПКИ"   language=Russian { if  "ки$"   then  "ы" }
 crop "ПОПОК"   language=Russian { if  "ок$"   then  "" = 90 }
 crop "ПОПКОЙ"  language=Russian { if  "кой$"  then  "ой" }
 crop "ПОПКОЮ"  language=Russian { if  "кою$"  then  "ой" }
 crop "ПОПКАМИ" language=Russian { if  "ками$" then  "ами" }
 crop "ПОПКУ"   language=Russian { if  "ку$"   then  "у"  }
 crop "ПОПКАМ"  language=Russian { if  "кам$"  then  "ам" }
 crop "ПОПКЕ"   language=Russian { if  "ке$"   then  "е" }
 crop "ПОПКАХ"  language=Russian { if  "ках$"  then  "ах" }



 // *************************************************
 // ПРИЛАГАТЕЛЬНОЕ ---> УМЕНЬШИТЕЛЬНОЕ ПРИЛАГАТЕЛЬНОЕ
 // *************************************************


 crop "КРАСНЫЙ-КРАСНЕНЬКИЙ"             language=Russian { if  "ЕНЬКИЙ$"   then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКАЯ"             language=Russian { if  "ЕНЬКАЯ$"   then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКОЕ"             language=Russian { if  "ЕНЬКОЕ$"   then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКИЕ"             language=Russian { if  "ЕНЬКИЕ$"   then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКОГО"            language=Russian { if  "ЕНЬКОГО$"  then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКОЙ"             language=Russian { if  "ЕНЬКОЙ$"   then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКИХ"             language=Russian { if  "ЕНЬКИХ$"   then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКИМ"             language=Russian { if  "ЕНЬКИМ$"   then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКИМИ"            language=Russian { if  "ЕНЬКИМИ$"  then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКУЮ"             language=Russian { if  "ЕНЬКУЮ$"   then  "ЫЙ"  }
 crop "КРАСНЫЙ-КРАСНЕНЬКОМ"             language=Russian { if  "ЕНЬКОМ$"   then  "ЫЙ"  }

// ****************************************


 crop PREFIX_###seq language=Russian { if  "$астро" then  ""  }    // АСТРОНАВИГАЦИЯ
 crop PREFIX_###seq language=Russian { if  "$анти" then  ""  }     // антигравитация
 crop PREFIX_###seq language=Russian { if  "$аэро" then  ""  }     // АЭРОДИНАМИЧЕСКИЙ
 crop PREFIX_###seq language=Russian { if  "$аудио" then  ""  }    // аудиокассета
 crop PREFIX_###seq language=Russian { if  "$авто" then  ""  }     // авторотация

 crop PREFIX_###seq language=Russian { if  "$бое" then  ""  }      // боекомплект
 crop PREFIX_###seq language=Russian { if  "$бомбо" then  ""  }    // бомбометание
 crop PREFIX_###seq language=Russian { if  "$борт" then  ""  }     // бортпроводник
 crop PREFIX_###seq language=Russian { if  "$броне" then  ""  }    // бронетранспортер
 crop PREFIX_###seq language=Russian { if  "$био" then  ""  }      // биоробот
 crop PREFIX_###seq language=Russian { if  "$бес" then  ""  }      // бесконечный
 crop PREFIX_###seq language=Russian { if  "$без" then  ""  }      // безалаберный

 crop PREFIX_###seq language=Russian { if  "$вы" then  ""  }       // "ВЫБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$в" then  ""  }        // "ВБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$въ" then  ""  }       // "ВЪЕХАТЬ"
 crop PREFIX_###seq language=Russian { if  "$видео" then  ""  }    // видеоконференция
 crop PREFIX_###seq language=Russian { if  "$водо" then  ""  }     // водоснабжение
 crop PREFIX_###seq language=Russian { if  "$вело" then  ""  }     // велотренажер
 crop AFFIX_###seq  language=Russian { if  "воз$" then  ""  }       // бомбовоз
 crop AFFIX_###seq  language=Russian { if  "вод$" then  ""  }       // 

 crop PREFIX_###seq language=Russian { if  "$гига" then  ""  }     // "ГИГАГЕРЦ"
 crop PREFIX_###seq language=Russian { if  "$гидро" then  ""  }    // гидроцилиндр
 crop PREFIX_###seq language=Russian { if  "$гипер" then  ""  }    // гиперзвук
 crop PREFIX_###seq language=Russian { if  "$грави" then  ""  }    // гравиметр
 crop PREFIX_###seq language=Russian { if  "$гео" then  ""  }      // геология
 crop PREFIX_###seq language=Russian { if  "$гос" then  ""  }      // госструктура

 crop PREFIX_###seq language=Russian { if  "$до" then  ""  }       // ДОБИТЬ
 crop PREFIX_###seq language=Russian { if  "$двух" then  ""  }     // ДВУХЦИЛИНДРОВЫЙ
 crop PREFIX_###seq language=Russian { if  "$трех" then  ""  }     // ТРЕХКРАТНЫЙ
 crop PREFIX_###seq language=Russian { if  "$четырех" then  ""  }  // ЧЕТЫРЕХКРАТНЫЙ
 crop PREFIX_###seq language=Russian { if  "$пяти" then  ""  }     // ПЯТИКРАТНЫЙ
 crop PREFIX_###seq language=Russian { if  "$шести" then  ""  }    // ШЕСТИКРАТНЫЙ
 crop PREFIX_###seq language=Russian { if  "$семи" then  ""  }     // СЕМИКРАТНЫЙ
 crop PREFIX_###seq language=Russian { if  "$восьми" then  ""  }   // ВОСЬМИКРАТНЫЙ
 crop PREFIX_###seq language=Russian { if  "$девяти" then  ""  }   // ДЕВЯТИКРАТНЫЙ
 crop PREFIX_###seq language=Russian { if  "$десяти" then  ""  }   // ДЕСЯТИКРАТНЫЙ
 crop PREFIX_###seq language=Russian { if  "$сто" then  ""  }      // СТОКРАТНЫЙ

 crop PREFIX_###seq language=Russian { if  "$за" then  ""  }       // "ЗАБИТЬ"

 crop PREFIX_###seq language=Russian { if  "$ир" then  ""  }       // иррациональный

 crop PREFIX_###seq language=Russian { if  "$ксено" then  ""  }    // ксенобиолог
 crop PREFIX_###seq language=Russian { if  "$контр" then  ""  }    // контрреволюция
 crop PREFIX_###seq language=Russian { if  "$кино" then  ""  }     // кинопроектор
 crop PREFIX_###seq language=Russian { if  "$квази" then  ""  }     // квазинародный

 crop PREFIX_###seq language=Russian { if  "$лже" then  ""  }      // лженаука
 crop PREFIX_###seq language=Russian { if  "$льно" then  ""  }     // льнокомбинат

 crop PREFIX_###seq language=Russian { if  "$мега" then  ""  }     // "МЕГАГЕРЦ"
 crop PREFIX_###seq language=Russian { if  "$мета" then  ""  }     // "МЕТАЯЗЫК"
 crop PREFIX_###seq language=Russian { if  "$микро" then  ""  }    // "МИКРОМЕТР"
 crop PREFIX_###seq language=Russian { if  "$милли" then  ""  }    // "МИЛЛИМЕТР"
 crop PREFIX_###seq language=Russian { if  "$мало" then  ""  }     // малопонятный
 crop PREFIX_###seq language=Russian { if  "$мульти" then  ""  }   // мультиметр
 crop PREFIX_###seq language=Russian { if  "$мини" then  ""  }     // миникомпьютер
 crop PREFIX_###seq language=Russian { if  "$мото" then  ""  }     // мотоколяска
 crop PREFIX_###seq language=Russian { if  "$металло" then  ""  }  // металлоконструкция
 crop PREFIX_###seq language=Russian { if  "$мех" then  ""  }      // мехобработка
 crop PREFIX_###seq language=Russian { if  "$механо" then  ""  }   // 
 crop PREFIX_###seq language=Russian { if  "$мезо" then  ""  }     // мезоуровено

 crop PREFIX_###seq language=Russian { if  "$не" then  ""  }       // неважный
 crop PREFIX_###seq language=Russian { if  "$нейро" then  ""  }    // нейрохирург
 crop PREFIX_###seq language=Russian { if  "$на" then  ""  }       // "НАБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$над" then  ""  }      // "НАДКУСИТЬ"
 crop PREFIX_###seq language=Russian { if  "$недо" then  ""  }     // "НЕДОБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$невро" then  ""  }    // невропатолог
 crop PREFIX_###seq language=Russian { if  "$нано" then  ""  }     // нанотехнология

 crop PREFIX_###seq language=Russian { if  "$от" then  ""  }       // "ОТБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$одно" then  ""  }     // ОДНОРАЗОВЫЙ
 crop PREFIX_###seq language=Russian { if  "$огне" then  ""  }     // огнестойкий

 crop PREFIX_###seq language=Russian { if  "$полу" then  ""  }     // "ПОЛУЭКТ"
 crop PREFIX_###seq language=Russian { if  "$предпо" then  ""  }   // "ПРЕДПОЛАГАТЬ"
 crop PREFIX_###seq language=Russian { if  "$пере" then  ""  }     // "ПЕРЕБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$под" then  ""  }      // "ПОДБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$подъ" then  ""  }     // "ПОДЪЕЗД"
 crop PREFIX_###seq language=Russian { if  "$по" then  ""  }       // "ПОБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$про" then  ""  }      // "ПРОБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$прото" then  ""  }    // протоплазма
 crop PREFIX_###seq language=Russian { if  "$псевдо" then  ""  }   // псевдографика
 crop PREFIX_###seq language=Russian { if  "$противо" then  ""  }  // противопехотный
 crop PREFIX_###seq language=Russian { if  "$пере" then  ""  }     // "перепоказать"


 crop PREFIX_###seq language=Russian { if  "$радио" then  ""  }    // радиомаяк
 crop PREFIX_###seq language=Russian { if  "$ретро" then  ""  }    // ретрошлягер
 crop PREFIX_###seq language=Russian { if  "$ре" then  ""  }       // репродукция
 crop PREFIX_###seq language=Russian { if  "$разъ" then  ""  }     // разъединенный
 crop PREFIX_###seq language=Russian { if  "$раз" then  ""  }      // разделенный

 crop PREFIX_###seq language=Russian { if  "$супер" then  ""  }    // "СУПЕРКЛЕЙ"
 crop PREFIX_###seq language=Russian { if  "$с" then  ""  }        // "СБИТЬ"
 crop PREFIX_###seq language=Russian { if  "$съ" then  ""  }       // "СЪЕХАТЬ"
 crop PREFIX_###seq language=Russian { if  "$сверх" then  ""  }    // сверхчеловек
 crop PREFIX_###seq language=Russian { if  "$стерео" then  ""  }   // стереосистема
 crop PREFIX_###seq language=Russian { if  "$спец" then  ""  }     // спецсигнал
 crop PREFIX_###seq language=Russian { if  "$само" then  ""  }     // самоуправление
 crop PREFIX_###seq language=Russian { if  "$сан" then  ""  }      // санобработка
 crop PREFIX_###seq language=Russian { if  "$суб" then  ""  }      // субкультура
 crop PREFIX_###seq language=Russian { if  "$субъ" then  ""  }     // 
 crop PREFIX_###seq language=Russian { if  "$свеже" then  ""  }     // свежепоказанный
 crop PREFIX_###seq language=Russian { if  "$слабо" then  ""  }     // слабодействующий
 crop PREFIX_###seq language=Russian { if  "$сильно" then  ""  }     // сильнодействующий

 crop PREFIX_###seq language=Russian { if  "$теле" then  ""  }     // телеуправление
 crop PREFIX_###seq language=Russian { if  "$техно" then  ""  }    // технопарк

 crop PREFIX_###seq language=Russian { if  "$у" then  ""  }        // "УКУСИТЬ"
 crop PREFIX_###seq language=Russian { if  "$ультра" then  ""  }   // ультразвук

 crop PREFIX_###seq language=Russian { if  "$ФОТО" then  ""  }     // ФОТОСЕССИЯ
 crop PREFIX_###seq language=Russian { if  "$Фин" then  ""  }      // Финдиректор
 crop AFFIX_###seq language=Russian { if  "ФОБИЯ$" then  ""  }     // водофобия
 crop AFFIX_###seq language=Russian { if  "ФОБ$" then  ""  }       // ксенофоб
 crop AFFIX_###seq language=Russian { if  "ФОБКА$" then  ""  }     // ксенофобка
 crop AFFIX_###seq language=Russian { if  "ФИЛ$" then  ""  }       // русофил

 crop PREFIX_###seq language=Russian { if  "$энерго" then  ""  }   // энергосбережение
 crop PREFIX_###seq language=Russian { if  "$электро" then  ""  }  // электросеть
 crop PREFIX_###seq language=Russian { if  "$экстра" then  ""  }   // экстраординарный
}
