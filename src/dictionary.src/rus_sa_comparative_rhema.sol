// Компаратив в роли предиката:
// твоя задача слегка проще.
// твое задание гораздо важнее.
patterns СравнРема export { node:root_node }


// у меня одна нога короче другой
//                  ^^^^^^^^^^^^^
pattern СравнРема
{
 ГруппаСравнПрил{ /*~ИсклСравнПрил*/ } : export { node:root_node }
}


patterns ОбъектДляСравнПрил export { node:root_node }
pattern ОбъектДляСравнПрил
{
 ГлДополнение{ ПАДЕЖ:РОД } : export { node:root_node }
}

// моя вторая любовь сильнее первой
pattern ОбъектДляСравнПрил
{
 ГруппаПрил2{ ПАДЕЖ:РОД } : export { node:root_node }
}


// Правая рука была сильнее левой
//                  ^^^^^^^^^^^^^
pattern СравнРема
{
 a=ГруппаСравнПрил{ /*~ИсклСравнПрил*/ } : export { node:root_node }
 obj=ОбъектДляСравнПрил
}
: links { a.<OBJECT>obj }
: ngrams { 1 }

// Я ль на свете всех милее?
//               ^^^^^^^^^^
pattern СравнРема
{
 obj=ОбъектДляСравнПрил
 a=ГруппаСравнПрил{ /*~ИсклСравнПрил*/ } : export { node:root_node }
}
: links { a.<OBJECT>obj }
: ngrams { -1 }


// Эта нога была длиннее, чем другая
//               ^^^^^^^^^^^^^^^^^^^
pattern СравнРема
{
 a=ГруппаСравнПрил : export { node:root_node }
 comma1=','
 conj=союз:чем{}
 obj=ГлДополнение{ ПАДЕЖ:ИМ }
 @noshift(ПравыйОграничительОборота)
 comma2=@coalesce(',')
} : links
{
 a.<OBJECT>comma1.
    <NEXT_COLLOCATION_ITEM>conj.
     <NEXT_COLLOCATION_ITEM>obj.
      ~<PUNCTUATION>comma2
   
}
: ngrams { 4 }

/*
// Инверсный порядок слов для паттерна с компаративом в роли предиката:
// гораздо важнее твое согласие.
pattern ГлПредикат
{
 a=ГруппаСравнПрил : export { node:root_node }
 sbj=ГруппаСущ4{ ПАДЕЖ:ИМ }
} : links { a.<SUBJECT>sbj }
*/
