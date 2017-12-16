// Правила синтаксического анализа для русского языка - построение синтаксического графа.
// CD->13.06.2009
// LC->10.03.2013


automat aa
{
 rulegroup ПодцепЧастицы
 rulegroup VerbSlots

 // Убираем постфиксные частицы
 transformation(ПодцепЧастицы) ЧастицаСправа
 {
  declare word, postfix;
  if context { @mark(*:*{},word) @mark(ЧАСТИЦА:*{},postfix) }
   then context { AttachLeaf(word,postfix,<POSTFIX_PARTICLE>) }
 }

 // вторую пару отдает девушке левой рукой
 transformation(VerbSlots) Вин_Гл_Дат_Твор
 {
  declare v, obj1, obj2, obj3;
  if like {
           obj1=ГлДополнение{ ПАДЕЖ:ВИН }
           [key]v=глагол:*{ переходность:переходный падеж:вин падеж:дат падеж:твор }
           obj2=ГлДополнение{ ПАДЕЖ:ДАТ }
           obj3=ГлДополнение{ ПАДЕЖ:ТВОР }
          }
   then context
   {
    AttachLeaf3(
                v,
                obj1, <OBJECT>,
                obj2, <OBJECT>,
                obj3, <OBJECT>
               )
   }
 }



 // даю пищу собаке
 transformation(VerbSlots) Гл_Вин_Дат
 {
  declare v, obj1, obj2;
  if like {
           [key]v=глагол:*{ переходность:переходный падеж:вин падеж:дат }
           obj1=ГлДополнение{ ПАДЕЖ:ВИН }
           obj2=ГлДополнение{ ПАДЕЖ:ДАТ }
          }
   then context
   {
    AttachLeaf2(
                v,
                obj1, <OBJECT>,
                obj2, <OBJECT>
               )
   }
 }




 // Теперь вижу сигнал
 transformation(VerbSlots) Гл_Вин
 {
  declare adv, v, obj;
  if like { adv=Обст [key]v=глагол:*{ переходность:переходный падеж:вин } obj=ГлДополнение{ ПАДЕЖ:ВИН } }
   then context
   {
    AttachLeaf2(
                v,
                obj, <OBJECT>,
                adv, <ATTRIBUTE>
               )
   }
 }

 // знаю это
 transformation(VerbSlots) Гл_Вин
 {
  declare v, obj;
  if like { [key]v=глагол:*{ переходность:переходный падеж:вин } obj=ГлДополнение{ ПАДЕЖ:ВИН } }
   then context
   {
    AttachLeaf(
               v,
               obj, <OBJECT>
              )
   }
 }


 procedure void SyntacticAnalysis_ru( trees контекст )
 {
  replace( "ПодцепЧастицы", контекст )

  replace( "VerbSlots", контекст )

  // ... todo
 }
}
