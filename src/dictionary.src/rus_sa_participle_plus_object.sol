// -----------------------------------------------------------------------------
// File RUS_SA_PARTICIPLE_PLUS_OBJECT.SOL
//
// (c) Koziev Elijah
//
// Content:
// Синтаксический анализатор: связь причастия и дополнения
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->28.08.2008
// LC->05.09.2011
// --------------

#include "aa_rules.inc"

automat aa
{

 operator Participle_Obj_Partitive1 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ПОКУШАВШИЙ ЩЕРБЕТУ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД }#a СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:ПАРТ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_Partitive2 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ЩЕРБЕТУ ПОКУШАВШИЙ
  if context { СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:ПАРТ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД }#a }
   then context { #a.<OBJECT>#b }
 }


 // *************** РОДИТЕЛЬНЫЙ *********************

 operator Participle_Obj_10 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ПОКУШАВШИЙ ЩЕРБЕТА
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД }#a СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:РОД } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_11 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // Съевший два яблока
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД }#a ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:РОД } #b }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_20 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ЩЕРБЕТА ПОКУШАВШИЙ
  if context { СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:РОД } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД }#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_21 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДВА ЯБЛОКА ПОКУШАВШИЙ
  if context { ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:РОД } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД }#a }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_25 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДОБАВИВШИЙ ЕГО
  if context {  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД } #a  МЕСТОИМЕНИЕ { ПАДЕЖ:РОД } #b }
   then
    context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_26 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ЕГО ДОБАВИВШИЙ
  if context { МЕСТОИМЕНИЕ { ПАДЕЖ:РОД } #b  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД } #a }
   then
    context { #a.<OBJECT>#b }
 }
 
 
 operator Participle_Obj_31 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НИЧЕГО НЕ КУШАВШИЙ  
  if context { МЕСТОИМ_СУЩ:* { ПАДЕЖ:РОД }#b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД }#a  }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_32 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НЕ КУШАВШИЙ НИЧЕГО 
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:РОД }#a  МЕСТОИМ_СУЩ:* { ПАДЕЖ:РОД }#b }
   then context { #a.<OBJECT>#b }
 }



 operator Participle_Obj_33 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДОПЛЫВШИЙ ДО НЕГО
  if context {  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ} #a  [ПРЕДЛОГ center:МЕСТОИМЕНИЕ] { ПАДЕЖ:РОД } #b }
   then
    context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_34 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДО НЕГО ДОПЛЫВШИЙ
  if context { [ПРЕДЛОГ center:МЕСТОИМЕНИЕ] { ПАДЕЖ:РОД } #b  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ} #a }
   then
    context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_35 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДОПЛЫВШИЙ ДО БЕРЕГА
  if context {  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ} #a  [ПРЕДЛОГ center:Существительное] { ПАДЕЖ:РОД } #b }
   then
    context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_36 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДО БЕРЕГА ДОПЛЫВШИЙ
  if context { [ПРЕДЛОГ center:Существительное] { ПАДЕЖ:РОД } #b  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ} #a }
   then
    context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_37 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДОПЛЫВШИЙ ДО ОДНОГО БЕРЕГА
  if context {  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ} #a  [ПРЕДЛОГ center:Числительное] { ПАДЕЖ:РОД } #b }
   then
    context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_38 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДО ОДНОГО БЕРЕГА ДОПЛЫВШИЙ
  if context { [ПРЕДЛОГ center:Числительное] { ПАДЕЖ:РОД } #b  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ} #a }
   then
    context { #a.<OBJECT>#b }
 }


 // ********************** ДАТЕЛЬНЫЙ ************************ 
 
 operator Participle_Obj_40 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ОТДАВШИЙ МОРЮ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ДАТ }#a СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:ДАТ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_41 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ОТДАВШИЙ ДВУМ МОРЯМ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ДАТ }#a ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:ДАТ } #b }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_43 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ОТДАВШИЙ ЕМУ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ДАТ }#a МЕСТОИМЕНИЕ:* { ПАДЕЖ:ДАТ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_50 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // МОРЮ ОТДАВШИЙ
  if context { СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:ДАТ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ДАТ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_51 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ОДНОМУ МОРЮ ОТДАВШИЙ
  if context { ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:ДАТ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ДАТ}#a }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_60 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ЕМУ ОТДАВШИЙ
  if context { МЕСТОИМЕНИЕ:* { ПАДЕЖ:ДАТ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ДАТ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_61 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НЕ ОТДАВШИЙ НИКОМУ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ДАТ }#a МЕСТОИМ_СУЩ:* { ПАДЕЖ:ДАТ } #b  }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_62 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НИКОМУ НЕ ОТДАВШИЙ 
  if context {  МЕСТОИМ_СУЩ:* { ПАДЕЖ:ДАТ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ДАТ}#a }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_63 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ШАГАЮЩИЙ ПО НЕМУ
  if context { ПРИЛАГАТЕЛЬНОЕ{ПРИЧАСТИЕ}#a [Предлог center:МЕСТОИМЕНИЕ]{ ПАДЕЖ:ДАТ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_64 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ПО НЕМУ ШАГАЮЩИЙ
  if context { [Предлог center:МЕСТОИМЕНИЕ]{ ПАДЕЖ:ДАТ } #b ПРИЛАГАТЕЛЬНОЕ{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_65 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ШАГАЮЩИЙ ПО ВОДЕ
  if context { ПРИЛАГАТЕЛЬНОЕ{ПРИЧАСТИЕ}#a [Предлог center:Существительное]{ ПАДЕЖ:ДАТ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_66 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ПО ВОДЕ ШАГАЮЩИЙ
  if context { [Предлог center:Существительное]{ ПАДЕЖ:ДАТ } #b ПРИЛАГАТЕЛЬНОЕ{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_67 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ШАГАЮЩИЙ ПО ДВУМ ДОРОГАМ
  if context { ПРИЛАГАТЕЛЬНОЕ{ПРИЧАСТИЕ}#a [Предлог center:Числительное]{ ПАДЕЖ:ДАТ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_68 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ПО ДВУМ ДОРОГАМ ШАГАЮЩИЙ
  if context { [Предлог center:Числительное]{ ПАДЕЖ:ДАТ } #b ПРИЛАГАТЕЛЬНОЕ{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }


 // ********************** ТВОРИТЕЛЬНЫЙ ************************ 
 
 operator Participle_Obj_70 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ВИЛЯЮЩИЙ ХВОСТОМ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ТВОР }#a СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:ТВОР }#b  }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_71 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ВИЛЯЮЩИЙ ОДНИМ ХВОСТОМ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ТВОР }#a ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:ТВОР }#b  }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_80 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ВИЛЯЮЩИЙ ИМ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ТВОР }#a МЕСТОИМЕНИЕ:* { ПАДЕЖ:ТВОР }#b  }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_90 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ХВОСТОМ ВИЛЯЮЩИЙ
  if context { СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:ТВОР }#b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ТВОР }#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_91 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ОДНИМ ХВОСТОМ ВИЛЯЮЩИЙ
  if context { ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:ТВОР }#b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ТВОР }#a }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_100 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ИМ ВИЛЯЮЩИЙ
  if context { МЕСТОИМЕНИЕ:* { ПАДЕЖ:ТВОР }#b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ТВОР }#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_101 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НИЧЕМ НЕ ВИЛЯЮЩИЙ
  if context { МЕСТОИМ_СУЩ:* { ПАДЕЖ:ТВОР }#b  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ТВОР }#a  }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_102 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НЕ ВИЛЯЮЩИЙ НИЧЕМ 
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:ТВОР }#a МЕСТОИМ_СУЩ:* { ПАДЕЖ:ТВОР }#b  }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_103 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ИДУЩИЙ ЗА НИМ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a [Предлог center:МЕСТОИМЕНИЕ]{ ПАДЕЖ:ТВОР }#b  }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_104 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ЗА НИМ ИДУЩИЙ
  if context { [Предлог center:МЕСТОИМЕНИЕ]{ ПАДЕЖ:ТВОР }#b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_105 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ИДУЩИЙ ЗА КОТИКОМ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a [Предлог center:Существительное]{ ПАДЕЖ:ТВОР }#b  }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_106 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ЗА КОТИКОМ ИДУЩИЙ
  if context { [Предлог center:Существительное]{ ПАДЕЖ:ТВОР }#b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_107 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ИДУЩИЙ ЗА ПЯТЬЮ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a [Предлог center:Числительное]{ ПАДЕЖ:ТВОР }#b  }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_108 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ЗА ПЯТЬЮ КОТАМИ ИДУЩИЙ
  if context { [Предлог center:Числительное]{ ПАДЕЖ:ТВОР }#b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }


 // ********************** ВИНИТЕЛЬНЫЙ ****************************
 
 operator Participle_Obj_110 : LINK_PARTICIPLE_PLUS_OBJECT
 {
 // ПОСЕЯВШИЙ ОВЕС
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:Вин }#a СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ВИН } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_111 : LINK_PARTICIPLE_PLUS_OBJECT
 {
 // ПОСЕЯВШИЙ ОДИН ОВЕС
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:Вин }#a ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ВИН } #b }
   then context { #a.<OBJECT>#b }
 }
 
 operator Participle_Obj_120 : LINK_PARTICIPLE_PLUS_OBJECT
 {
 // ПОСЕЯВШИЙ ЕГО
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:Вин }#a МЕСТОИМЕНИЕ { ПАДЕЖ:ВИН } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_130 : LINK_PARTICIPLE_PLUS_OBJECT
 {
 // ОВЕС ПОСЕЯВШИЙ
  if context { СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ВИН } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:Вин }#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_131 : LINK_PARTICIPLE_PLUS_OBJECT
 {
 // ОДИН ОВЕС ПОСЕЯВШИЙ
  if context { ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ВИН } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:Вин }#a }
   then context { #a.<OBJECT>#b }
 }
 
 operator Participle_Obj_140 : LINK_PARTICIPLE_PLUS_OBJECT
 {
 // ЕГО ПОСЕЯВШИЙ
  if context { МЕСТОИМЕНИЕ { ПАДЕЖ:ВИН } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:Вин }#a }
   then context { #a.<OBJECT>#b }
 }
 
 operator Participle_Obj_141 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НЕ СЕЯВШИЙ НИЧЕГО
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:Вин }#a МЕСТОИМ_СУЩ:*{ ПАДЕЖ:ВИН } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_142 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НИЧЕГО НЕ СЕЯВШИЙ
  if context { МЕСТОИМ_СУЩ:*{ ПАДЕЖ:ВИН } #b  ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПадежВал:Вин }#a }
   then context { #a.<OBJECT>#b }
 }

 

 operator Participle_Obj_143 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ПРЫГНУВШИЙ НА НЕГО
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a [Предлог center:МЕСТОИМЕНИЕ]{ ПАДЕЖ:ВИН } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_144 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НА НЕГО ПРЫГНУВШИЙ
  if context { [Предлог center:МЕСТОИМЕНИЕ]{ ПАДЕЖ:ВИН } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_145 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ПРЫГНУВШИЙ НА КОВЕР
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a [Предлог center:Существительное]{ ПАДЕЖ:ВИН } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_146 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НА КОВЕР ПРЫГНУВШИЙ
  if context { [Предлог center:Существительное]{ ПАДЕЖ:ВИН } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_147 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ПРЫГНУВШИЙ НА ОДИН КОВЕР
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a [Предлог center:Числительное]{ ПАДЕЖ:ВИН } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_148 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НА ОДИН КОВЕР ПРЫГНУВШИЙ
  if context { [Предлог center:Числительное]{ ПАДЕЖ:ВИН } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }


 // *********************** ПРЕДЛОЖНЫЙ ******************************
 
 operator Participle_Obj_200 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДУМАЮЩИЙ О ЩЕРБЕТЕ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:ПРЕДЛ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_201 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДУМАЮЩИЙ ОБ ОДНОМ ЩЕРБЕТЕ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:ПРЕДЛ } #b }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Obj_210 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // О ЩЕРБЕТЕ ДУМАЮЩИЙ
  if context { СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:ПРЕДЛ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_211 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ОБ ОДНОМ ЩЕРБЕТЕ ДУМАЮЩИЙ
  if context { ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:ПРЕДЛ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }
 
 operator Participle_Obj_220 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // ДУМАЮЩИЙ О НЕМ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a МЕСТОИМЕНИЕ:* { ПАДЕЖ:ПРЕДЛ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_230 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // О НЕМ ДУМАЮЩИЙ
  if context { МЕСТОИМЕНИЕ:* { ПАДЕЖ:ПРЕДЛ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_231 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НЕ ДУМАЮЩИЙ НИ О ЧЕМ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a МЕСТОИМ_СУЩ:* { ПАДЕЖ:ПРЕДЛ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_232 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // НИ О ЧЕМ НЕ ДУМАЮЩИЙ 
  if context { МЕСТОИМ_СУЩ:* { ПАДЕЖ:ПРЕДЛ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }


 // ************************
 // МЕСТНЫЙ ПАДЕЖ
 // ************************

 operator Participle_Obj_Locative1 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // РАСТУЩЕЕ В ЛЕСУ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:МЕСТ } #b }
   then context { #a.<OBJECT>#b }
 }

 operator Participle_Obj_Locative2 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // В ЛЕСУ РАСТУЩЕЕ
  if context { СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:МЕСТ } #b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }






 // БЕЗ-ПАДЕЖНЫЕ формы числительных
 operator Participle_Number_1 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // Съевший 2 яблока
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a NUMBER_#b }
   then context { #a.<OBJECT>#b }
 }


 operator Participle_Number_2 : LINK_PARTICIPLE_PLUS_OBJECT
 {
  // 2 ЯБЛОКА ПОКУШАВШИЙ
  if context { NUMBER_#b ПРИЛАГАТЕЛЬНОЕ:*{ПРИЧАСТИЕ}#a }
   then context { #a.<OBJECT>#b }
 }

}



