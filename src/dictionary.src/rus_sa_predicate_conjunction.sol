patterns СочинитСоюзПредикат export { node:root_node }
pattern СочинитСоюзПредикат
{
 ЛогичСоюз : export { node:root_node }
}

wordentry_set ПротивитСоюзыПредикат = союз:{ а, но, "не то", "а не то", "а то" }
pattern СочинитСоюзПредикат
{
 ПротивитСоюзыПредикат : export { node:root_node }
}


// Попугаи порой улетают, но зато разговаривают.
//                        ^^^^^^^
pattern СочинитСоюзПредикат
{
 head=союз:но{} : export { node:root_node }
 tail=союз:зато{}
} : links { head.<NEXT_COLLOCATION_ITEM>tail }



pattern СочинитСоюзПредикат
{
 conj1=союз:хотя{} : export { node:root_node }
 conj2=союз:и{} 
}
: links { conj1.<NEXT_COLLOCATION_ITEM>conj2 }
: ngrams { 1 }

