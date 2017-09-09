// ---------------------------------------------------------
// местоименная группа, имеющая признак лица и мн.ч.
// === ВЫ
// Ты, собака, корова и воробей будете жить в лесу
// Гусеница, ты, кошка и тюльпан будете жить в этом домике
//
// === МЫ
// папа и я пляшем
// папа, мама, брат и я любим петь

patterns ГруппаМестВосх0
export
{
 KEYFEATURE_REQUIRED
 ПАДЕЖ ЛИЦО
 node:root_node
}

pattern ГруппаМестВосх0
{
 местоимение:я{ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:1 } : export { KEYFEATURE_REQUIRED:0 ПАДЕЖ ЛИЦО node:root_node }
}

pattern ГруппаМестВосх0
{
 местоимение:я{ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:2 } : export { KEYFEATURE_REQUIRED:0 ПАДЕЖ ЛИЦО node:root_node }
}

pattern ГруппаМестВосх0
{
 местоимение:я{ ПАДЕЖ:ИМ } : export { KEYFEATURE_REQUIRED:1 ПАДЕЖ ЛИЦО node:root_node }
}


pattern ГруппаМестВосх0 export { KEYFEATURE_REQUIRED ПАДЕЖ (ЛИЦО) node:root_node }
{
 ГруппаСущ1{ ПАДЕЖ:ИМ } : export { KEYFEATURE_REQUIRED:1 ПАДЕЖ node:root_node }
}

// ------------------------------------------

patterns ГруппаМестВосх { bottomup }
export
{
 KEYFEATURE_DETECTED // если обнаружен второй или далее элемент перечисления, то будет=1
 KEYFEATURE_REQUIRED
 ПАДЕЖ ЛИЦО
 node:root_node
}

pattern ГруппаМестВосх
{
 ГруппаМестВосх0:export{ KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED ПАДЕЖ ЛИЦО node:root_node }
}

pattern ГруппаМестВосх
{
 n1=ГруппаМестВосх:export{ KEYFEATURE_REQUIRED ПАДЕЖ ЛИЦО node:root_node }
 comma=','
 n2=ГруппаМестВосх0{ =n1:Падеж } : export { KEYFEATURE_DETECTED:1 }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }

pattern ГруппаМестВосх
{
 n1=ГруппаМестВосх:export{ ПАДЕЖ node:root_node }
 comma=','
 n2=ГруппаМестВосх0{ =n1:Падеж }:export{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED ЛИЦО }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }


// Ты и приятель решаете задачи
// ^^^^^^^^^^^^^
// я и приятель решаем задачу
// ^^^^^^^^^^^^
pattern ГруппаМестВосх
{
 n1=ГруппаМестВосх:export { KEYFEATURE_REQUIRED ПАДЕЖ ЛИЦО node:root_node }
 conj=ЛогичСоюз
 n2=ГруппаМестВосх0{ =n1:ПАДЕЖ } : export { KEYFEATURE_DETECTED:1 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }

// Приятель и ты учите стихотворение
// ^^^^^^^^^^^^^
// Сестра и я ходим в одну школу
// ^^^^^^^^^^
pattern ГруппаМестВосх
{
 n1=ГруппаМестВосх:export { ПАДЕЖ node:root_node }
 conj=ЛогичСоюз
 n2=ГруппаМестВосх0{ =n1:ПАДЕЖ }:export { KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED ЛИЦО }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }


// -----------------------------------------------------

pattern ГруппаМест export { ПАДЕЖ ЧИСЛО (РОД) ЛИЦО node:root_node }
{
 n=ГруппаМестВосх{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 }:export{ ПАДЕЖ ЧИСЛО:МН ЛИЦО node:root_node }
}
