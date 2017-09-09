
patterns ОбстМеста export { node:root_node }

pattern ОбстМеста
{
 наречие:*{ ОБСТ_ВАЛ:МЕСТО } : export { node:root_node }
}


// Он  же  на  работе.
//         ^^^^^^^^^^
pattern ОбстМеста
{
 prep=предлог:на{} : export { node:root_node }
 obj=ГлДополнение{ ПАДЕЖ:ПРЕДЛ }
} : links { prep.<OBJECT>obj }

// Мы на берегу
//    ^^^^^^^^^
pattern ОбстМеста
{
 prep=предлог:на{} : export { node:root_node }
 obj=ГлДополнение{ ПАДЕЖ:МЕСТ }
} : links { prep.<OBJECT>obj }


// Он в другом цеху
//    ^^^^^^^^^^^^^
pattern ОбстМеста
{
 prep=предлог:в{} : export { node:root_node }
 obj=ГлДополнение{ ПАДЕЖ:ПРЕДЛ }
} : links { prep.<OBJECT>obj }


// Он в другом здании
//    ^^^^^^^^^^^^^^^
pattern ОбстМеста
{
 prep=предлог:в{} : export { node:root_node }
 obj=ГлДополнение{ ПАДЕЖ:МЕСТ }
} : links { prep.<OBJECT>obj }
