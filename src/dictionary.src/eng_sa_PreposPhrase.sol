// PREPOSITIONAL PHRASES
// LC->19.01.2016


// ------------------------------------------------------------------------------

// Одиночный предлог или группа предлогов
#region PreposItem

pattern PreposItem
{
 eng_prep:*{} : export { node:root_node }
}


// Eastern Europe before and after 1989
//                ^^^^^^^^^^^^^^^^
pattern PreposItem
{
 p1=eng_prep:*{} : export { node:root_node }
 conj=eng_prep:*{}
 p2=eng_prep:*{}
} : links { p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }


// He will eat cake, pie, and/or brownies
//                        ^^^^^^
pattern PreposItem
{
 p1=eng_prep:*{} : export { node:root_node }
 conj='/'
 p2=eng_prep:*{}
} : links { p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }



// Her curls peeped out from under her hat.
//                      ^^^^^^^^^^
pattern PreposItem
{
 prep=eng_prep:from{}:export{ node:root_node }
 p2=eng_prep:under{}
} : links { prep.<NEXT_COLLOCATION_ITEM>p2 }
  : ngrams { 1 }

  
// -------------------------------------
// наречие атрибутирует предлог
// -------------------------------------

// You can sit next to them
//             ^^^^^^^^^^^^
// lie down here on the table next to your baby until dawn.
//                            ^^^^^^^^^^^^^^^^^
pattern PreposItem
{
 a=AdvGroup
 prep=PreposItem{ adv_prep( a, _ )  } : export { node:root_node }
}
: links { prep.<ATTRIBUTE>a }
: ngrams
{ -5 }

  
  
#endregion PreposItem


// ------------------------------------------------------------------------------

// Сочетание предлога и объекта
// I did it for this.
//          ^^^^^^^^

#region PreposPhrase

// I see the book behind you
//                ^^^^^^^^^^
// The music evolved from what went before.  
//                        ^^^^^^^^^^^^^^^^
pattern PreposPhrase
{
 prep=PreposItem : export{ node:root_node }
 n=PreposObject : export { node:root_node->n2 }
}
: links { prep.<OBJECT>n }
: ngrams { PreposValency(prep) }







// The houses from this point to that point
//            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// I walk from house to house
//        ^^^^^^^^^^^^^^^^^^^
pattern PreposPhrase
{
 prep1=eng_prep:from{}:export{ node:root_node }
 x=PreposObject : export { node:root_node->n2 }
 prep2=eng_prep:to{}
 y=PreposObject
}
: links { prep1.<OBJECT>x.<PREPOS_ADJUNCT>prep2.<OBJECT>y }
: ngrams { PreposValency(prep1) }


// The secrects between you and me 
//              ^^^^^^^^^^^^^^^^^^
pattern PreposPhrase
{
 prep1=eng_prep:between{}:export{ node:root_node }
 x=PreposObject : export { node:root_node->n2 }
 prep2=eng_conj:and{}
 y=PreposObject
}
: links { prep1.<OBJECT>x.<RIGHT_LOGIC_ITEM>prep2.<NEXT_COLLOCATION_ITEM>y }
: ngrams { PreposValency(prep1) }



patterns UnknownRightGroup export { node:root_node }

// что угодно справа от предлога считаем существительным.
pattern PreposPhrase
{
 prep=PreposItem : export{ node:root_node }
 n=UnknownRightGroup : export { node:root_node->n2 }
}
: links { prep.<OBJECT>n }
: ngrams { PreposValency(prep) }




// TODO:
// Spectators place bets on who will survive.
//                       ^^^^^^^^^^^^^^^^^^^

#endregion PreposPhrase
  