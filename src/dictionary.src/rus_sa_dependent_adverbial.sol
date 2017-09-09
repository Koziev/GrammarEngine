// Правая часть оборотов типа:
//
// Я понял, почему.
// Я знаю, для кого.


patterns ПравПридаточнОбст export { node:root_node }


// Мы не знаем, почему.
//            ^^^^^^^^
pattern ПравПридаточнОбст
{
 comma=',' : export { node:root_node }
 body=ГруппаНареч2
 @noshift(ПравыйОграничительОборота)
} : links { comma.<NEXT_COLLOCATION_ITEM>body }


// Я знаю, для кого.
//       ^^^^^^^^^^
pattern ПравПридаточнОбст
{
 comma=',' : export { node:root_node }
 body=ПредлогИСущ
 @noshift(ПравыйОграничительОборота)
} : links { comma.<NEXT_COLLOCATION_ITEM>body }

