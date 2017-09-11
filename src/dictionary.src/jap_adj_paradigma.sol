﻿// CD->03.03.2009
// LC->19.03.2010
// --------------

automat sg
{

 // Формообразование предикативных прилагательных
 paradigm あざとい, JapAdj_9700 : JAP_ADJECTIVE for ".+い"
 {
  JAP_ADJ_BASE:I { "" }          // словарная форма с суффиксом い
  JAP_ADJ_BASE:II { "%-1" }      // словообразовательная
  JAP_ADJ_BASE:III { "%-1%+く" }  // наречно-соединительная
  JAP_ADJ_BASE:IV { "%-1%+けれ" } // условная
  JAP_ADJ_BASE:V { "%-1%+かろう" } // вероятностная

  //JAP_ADJ_BASE:T { "%-1%+くて" } // серединная

  JAP_ADJ_BASE:PAST { "%-1%+かった" } // прошедшее время 寒い (холодный) - 寒かった (был холодный)
  
 }

 // Формообразование полупредикативных прилагательных на の или な
 paradigm ながの, JapAdj_9701 : JAP_ADJECTIVE for ".+[のな]"
 {
  JAP_ADJ_BASE:I { "" }          // словарная форма
  JAP_ADJ_BASE:II { "%-1" }      // словообразовательная
  JAP_ADJ_BASE:III { "%-1%+に" }  // наречно-соединительная

  //JAP_ADJ_BASE:T { "%-1%+で" } // серединная
 }

 // Китайские прилагательные на 
 paradigm JapAdj_9702 : JAP_ADJECTIVE
 {
  JAP_ADJ_BASE:I { "" }          // словарная форма
 }


 // Есть только словарная форма
 // 友好的な дружественный
 paradigm JapAdj_9703 : JAP_ADJECTIVE
 {
  JAP_ADJ_BASE:I { "" }          // словарная форма
 }

}
