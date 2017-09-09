// Дополнительная информация для русского токенизатора - исключения из общих правил деления строк на лексемы.
//
// Подробнее: http://www.solarix.ru/for_developers/docs/tokenizer.shtml

// CD->08.02.2009
// LC->04.09.2016


unbreakable language=Russian { "о-в" } // остров
unbreakable language=Russian { "и.о." } // И.о. астраханского губернатора посетит Черноярский район
unbreakable language=Russian { "т.е." }
unbreakable language=Russian { "т.к." } // Мне не пришлось за него платить, т.к. погода была не слишком жаркой
unbreakable language=Russian { "т. е." } // внутри - пробел!
unbreakable language=Russian { "т.д." }
unbreakable language=Russian { "т. д." } // внутри - пробел!
unbreakable language=Russian { "т.п." }
unbreakable language=Russian { "т.ч." } // в т.ч. - в том числе
unbreakable language=Russian { "др." }
unbreakable language=Russian { "пр." }
unbreakable language=Russian { "стр." }
unbreakable language=Russian { "тов." }
unbreakable language=Russian { "г." }
unbreakable language=Russian { "г-н" }
unbreakable language=Russian { "г.г." }
unbreakable language=Russian { "гр." }
unbreakable language=Russian { "долл." }
unbreakable language=Russian { "пр." }
unbreakable language=Russian { "т.ч." }
unbreakable language=Russian { "мл." }            // "младший", - Буш-мл.
unbreakable language=Russian { "д.ф.-м.н." }
unbreakable language=Russian { "к.т.н." }
unbreakable language=Russian { "шт." }
unbreakable language=Russian { "чел." }
//unbreakable language=Russian { "тел." }
unbreakable language=Russian { "б/у" }
unbreakable language=Russian { "м/с" }
unbreakable language=Russian { "км/ч" }
unbreakable language=Russian { "обл." } // В Московской обл.
unbreakable language=Russian { "л.с." }

unbreakable language=Russian { "тыс." }
unbreakable language=Russian { "млн." }
unbreakable language=Russian { "млрд." }

unbreakable language=Russian { "кто-то" }
unbreakable language=Russian { "кого-то" }
unbreakable language=Russian { "кем-то" }
unbreakable language=Russian { "ком-то" }
unbreakable language=Russian { "кому-то" }

unbreakable language=Russian { "что-то" }
unbreakable language=Russian { "чего-то" }
unbreakable language=Russian { "чем-то" }
unbreakable language=Russian { "чему-то" }
unbreakable language=Russian { "чем-то" }
unbreakable language=Russian { "чём-то" }


unbreakable language=Russian { "кто-либо" }
unbreakable language=Russian { "кого-либо" }
unbreakable language=Russian { "кем-либо" }
unbreakable language=Russian { "ком-либо" }
unbreakable language=Russian { "кому-либо" }

unbreakable language=Russian { "что-либо" }
unbreakable language=Russian { "чего-либо" }
unbreakable language=Russian { "чем-либо" }
unbreakable language=Russian { "чему-либо" }
unbreakable language=Russian { "чем-либо" }

unbreakable language=Russian { "где-либо" }
unbreakable language=Russian { "как-либо" }
unbreakable language=Russian { "почему-либо" }
unbreakable language=Russian { "откуда-нибудь" }
unbreakable language=Russian { "как-нибудь" }

unbreakable language=Russian { "какой-либо" }
unbreakable language=Russian { "какая-либо" }
unbreakable language=Russian { "какое-либо" }
unbreakable language=Russian { "какие-либо" }
unbreakable language=Russian { "какого-либо" }
unbreakable language=Russian { "какой-либо" }
unbreakable language=Russian { "каких-либо" }
unbreakable language=Russian { "каким-либо" }
unbreakable language=Russian { "какой-либо" }
unbreakable language=Russian { "какими-либо" }
unbreakable language=Russian { "какого-либо" }
unbreakable language=Russian { "какую-либо" }
unbreakable language=Russian { "какому-либо" }

unbreakable language=Russian { "какой-нибудь" }
unbreakable language=Russian { "какая-нибудь" }
unbreakable language=Russian { "какое-нибудь" }
unbreakable language=Russian { "какие-нибудь" }
unbreakable language=Russian { "какого-нибудь" }
unbreakable language=Russian { "какой-нибудь" }
unbreakable language=Russian { "каких-нибудь" }
unbreakable language=Russian { "каким-нибудь" }
unbreakable language=Russian { "какой-нибудь" }
unbreakable language=Russian { "какими-нибудь" }
unbreakable language=Russian { "какого-нибудь" }
unbreakable language=Russian { "какую-нибудь" }
unbreakable language=Russian { "какому-нибудь" }

unbreakable language=Russian { "кто-нибудь" }
unbreakable language=Russian { "кого-нибудь" }
unbreakable language=Russian { "кем-нибудь" }
unbreakable language=Russian { "кому-нибудь" }
unbreakable language=Russian { "ком-нибудь" }

unbreakable language=Russian { "что-нибудь" }
unbreakable language=Russian { "чего-нибудь" }
unbreakable language=Russian { "чем-нибудь" }
unbreakable language=Russian { "чему-нибудь" }

unbreakable language=Russian { "когда-нибудь" }
unbreakable language=Russian { "где-нибудь" }
unbreakable language=Russian { "почему-нибудь" }
unbreakable language=Russian { "зачем-нибудь" }
unbreakable language=Russian { "сколько-нибудь" }
unbreakable language=Russian { "докуда-нибудь" }

unbreakable language=Russian { "чей-либо" }
unbreakable language=Russian { "чья-либо" }
unbreakable language=Russian { "чьё-либо" }
unbreakable language=Russian { "чьи-либо" }
unbreakable language=Russian { "чьего-либо" }
unbreakable language=Russian { "чьей-либо" }
unbreakable language=Russian { "чьих-либо" }
unbreakable language=Russian { "чьим-либо" }
unbreakable language=Russian { "чьей-либо" }
unbreakable language=Russian { "чьими-либо" }
unbreakable language=Russian { "чьего-либо" }
unbreakable language=Russian { "чью-либо" }
unbreakable language=Russian { "чьему-либо" }
unbreakable language=Russian { "чьём-либо" }

unbreakable language=Russian { "чей-нибудь" }
unbreakable language=Russian { "чья-нибудь" }
unbreakable language=Russian { "чьё-нибудь" }
unbreakable language=Russian { "чьи-нибудь" }
unbreakable language=Russian { "чьего-нибудь" }
unbreakable language=Russian { "чьей-нибудь" }
unbreakable language=Russian { "чьих-нибудь" }
unbreakable language=Russian { "чьим-нибудь" }
unbreakable language=Russian { "чьей-нибудь" }
unbreakable language=Russian { "чьими-нибудь" }
unbreakable language=Russian { "чьего-нибудь" }
unbreakable language=Russian { "чью-нибудь" }
unbreakable language=Russian { "чьему-нибудь" }
unbreakable language=Russian { "чьём-нибудь" }

unbreakable language=Russian { "где-то" }
unbreakable language=Russian { "как-то" }
unbreakable language=Russian { "почему-то" }
unbreakable language=Russian { "откуда-то" }
unbreakable language=Russian { "куда-то" }

unbreakable language=Russian { "какой-то" }
unbreakable language=Russian { "какая-то" }
unbreakable language=Russian { "какое-то" }
unbreakable language=Russian { "какие-то" }
unbreakable language=Russian { "какого-то" }
unbreakable language=Russian { "какой-то" }
unbreakable language=Russian { "каких-то" }
unbreakable language=Russian { "каким-то" }
unbreakable language=Russian { "какими-то" }
unbreakable language=Russian { "какую-то" }
unbreakable language=Russian { "какому-то" }
unbreakable language=Russian { "каком-то" }

unbreakable language=Russian { "чей-то" }
unbreakable language=Russian { "чья-то" }
unbreakable language=Russian { "чье-то" }
unbreakable language=Russian { "чьё-то" }
unbreakable language=Russian { "чьи-то" }
unbreakable language=Russian { "чьего-то" }
unbreakable language=Russian { "чьей-то" }
unbreakable language=Russian { "чьею-то" }
unbreakable language=Russian { "чьих-то" }
unbreakable language=Russian { "чьим-то" }
unbreakable language=Russian { "чьими-то" }
unbreakable language=Russian { "чью-то" }
unbreakable language=Russian { "чьему-то" }
unbreakable language=Russian { "чьем-то" }
unbreakable language=Russian { "чьём-то" }
unbreakable language=Russian { "чьей-то" }

unbreakable language=Russian { "кое-что" }
unbreakable language=Russian { "кое-чего" }
unbreakable language=Russian { "кое-чем" }
unbreakable language=Russian { "кое-чему" }


unbreakable language=Russian { "кое-кто" }
unbreakable language=Russian { "кое-кого" }
unbreakable language=Russian { "кое-кем" }
unbreakable language=Russian { "кое-кому" }

unbreakable language=Russian { "полным-полно" }
unbreakable language=Russian { "кое-как" }
unbreakable language=Russian { "кое-где" }


unbreakable language=Russian { "кое-какой" }
unbreakable language=Russian { "кое-какая" }
unbreakable language=Russian { "кое-какое" }
unbreakable language=Russian { "кое-какие" }
unbreakable language=Russian { "кое-какого" }
unbreakable language=Russian { "кое-какой" }
unbreakable language=Russian { "кое-каких" }
unbreakable language=Russian { "кое-каким" }
unbreakable language=Russian { "кое-какой" }
unbreakable language=Russian { "кое-какими" }
unbreakable language=Russian { "кое-какую" }
unbreakable language=Russian { "кое-какому" }
unbreakable language=Russian { "кое-каком" }


//Санкт-Петербургского
unbreakable language=Russian { "Санкт-Петербургский" }
unbreakable language=Russian { "Санкт-Петербургская" }
unbreakable language=Russian { "Санкт-Петербургское" }
unbreakable language=Russian { "Санкт-Петербургские" }
unbreakable language=Russian { "Санкт-Петербургского" }
unbreakable language=Russian { "Санкт-Петербургской" }
unbreakable language=Russian { "Санкт-Петербургских" }
unbreakable language=Russian { "Санкт-Петербургского" }
unbreakable language=Russian { "Санкт-Петербургский" }
unbreakable language=Russian { "Санкт-Петербургскую" }
unbreakable language=Russian { "Санкт-Петербургские" }
unbreakable language=Russian { "Санкт-Петербургскому" }
unbreakable language=Russian { "Санкт-Петербургской" }
unbreakable language=Russian { "Санкт-Петербургским" }
unbreakable language=Russian { "Санкт-Петербургском" }
unbreakable language=Russian { "Санкт-Петербургской" }
unbreakable language=Russian { "Санкт-Петербургских" }

unbreakable language=Russian { "все-таки" }


// без света остались 5,5 тыс. человек
//                    ^^^
unbreakable language=Russian { ~"[:digit:]*[.,][:digit:]*" }

// снизились на 0,1%
unbreakable language=Russian { ~"[:digit:]*[.,][:digit:]*%" }


#pragma language_mix off
unbreakable language=Russian { ~"[:digit:]{4}г." }   // 2012г.
#pragma language_mix on

unbreakable language=Russian { ~"[:digit:]+-е" }   // 30-е годы прошлого века
unbreakable language=Russian { ~"[:digit:]+-ые" }  // 30-ые годы прошлого века
unbreakable language=Russian { ~"[:digit:]+-ых" }  // в 30-ых годах
unbreakable language=Russian { ~"[:digit:]+-х" }   // в 30-х годах прошлого века
unbreakable language=Russian { ~"[:digit:]+-я" }   // 10-я пятилетка
unbreakable language=Russian { ~"[:digit:]+-го" }  // 19-го века
unbreakable language=Russian { ~"[:digit:]+-ой" }  // 21-й книгой
unbreakable language=Russian { ~"[:digit:]+-й" }   // 121-й поворот

unbreakable language=Russian { ~"[:digit:]+-ти" }  // 10-ти, 20-ти, 160-ти, 11-ти, 12-ти, 13-ти, 25-ти, ... 29-ти
unbreakable language=Russian { ~"[:digit:]+-го" }  // 21-го, 191-го
unbreakable language=Russian { ~"[:digit:]+-x" }   // 22-x
unbreakable language=Russian { ~"[:digit:]+-ми" }  // 27-ми
unbreakable language=Russian { ~"[:digit:]+-ми" }  // об 11-ой главе
unbreakable language=Russian { ~"[:digit:]+-м" }  // на 90-м году

unbreakable language=Russian { ~"[:digit:]+-ти" }  // о 120-ти приемах
unbreakable language=Russian { ~"[:digit:]+-лети[еямюйямхи]+" }  // 70-летие
unbreakable language=Russian { ~"[:digit:]+-летн[ийеюхмягоу]+" }  // 27-летняя
unbreakable language=Russian { ~"[:digit:]+-метров[аоуыийеюхмяг]+" }  // 100-метровая
unbreakable language=Russian { ~"[:digit:]+-килограммов[аоуыийеюхмяг]+" }  // 100-килограммовая
unbreakable language=Russian { ~"[:digit:]+-километров[аоуыийеюхмяг]+" }  // пробежал 10-километровую дистанцию
unbreakable language=Russian { ~"[:digit:]+-комнатн[аоуыийеюхмяг]+" } // Вся правда о 13-комнатной квартире помощницы Сердюкова
unbreakable language=Russian { ~"[:digit:]+-градусн[аоуыийеюхмяг]+" } // Обнаженные российские сноубордистки катались в 30-градусный мороз

unbreakable language=Russian { ~"[:digit:]+-дневн[аоуыийеюмях]+" } // 60-дневная версия
unbreakable language=Russian { ~"[:digit:]+-часов[аоуыийеюмях]+" } // 48-ЧАСОВОЙ
unbreakable language=Russian { ~"[:digit:]+-этажн[аоуыийеюмях]+" } // в 16-этажном жилом доме


unbreakable language=Russian { ~"[:digit:]{1,2}-[\\@А\\@Б]{3}-[:digit:]{4}" }  // 1-янв-2009

unbreakable language=Russian { ~"[<\\@Б\\@АЙ>][<\\@б\\@айьъ>]* [<\\@А\\@Б>]\\.[<\\@А\\@Б>]\\." } // Пушкин А.С.
unbreakable language=Russian { ~"[<\\@А\\@Б>]\\.[<\\@А\\@Б>]\\. [<\\@Б\\@АЙ>][<\\@б\\@айьъ>]*"  } // Л.Н. Толстой
unbreakable language=Russian { ~"[<\\@А\\@Б>]\\.[<\\@А\\@Б>]\\.[<\\@Б\\@АЙ>][<\\@б\\@айьъ>]*"  } // Л.Н.Толстой
unbreakable language=Russian { ~"[<\\@А\\@Б>][<\\@б>]\\. *[<\\@Б\\@АЙ>][<\\@б\\@айьъ>]*"  } // Дж. Буш

unbreakable language=Russian { ~"[<\\@А\\@Б>]\\. [<\\@Б\\@АЙ>][<\\@б\\@айьъ>]*"  } // Р. Кеннеди
unbreakable language=Russian { ~"[<\\@А\\@Б>]\\.[<\\@Б\\@АЙ>][<\\@б\\@айьъ>]*"  } // Р.Кеннеди


// УРЛы: http://www.gutenberg.net
//       ^^^^^^^^^^^^^^^^^^^^^^^^
unbreakable language=Russian
{ ~"http://[abcdefghijklmnopqrstuvwxyz1234567890_-\\.]+" }
