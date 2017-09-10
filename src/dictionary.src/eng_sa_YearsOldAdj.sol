
patterns YearsOldAdj export { node:root_node }



// Zhang Liao was 27 years old then.
//                ^^^^^^^^^^^^
// His brother Wilhelm was four years older.
//                         ^^^^^^^^^^^^^^^^
pattern YearsOldAdj
{
 cnt=NumberGroup
 n=eng_noun:year{}
 a=eng_adjective:old{} : export { node:root_node }
}
: links { a.<ATTRIBUTE>n.<ATTRIBUTE>cnt }
: ngrams { 2 }


// 32-years old Melissa Lawson won.
// ^^^^^^^^^^^^
pattern YearsOldAdj
{
 cnt=NumberGroup
 t='-'
 n=eng_noun:year{}
 a=eng_adjective:old{} : export { node:root_node }
}
: links { a.<ATTRIBUTE>n.<NEXT_COLLOCATION_ITEM>t.<ATTRIBUTE>cnt }
: ngrams { 2 }


patterns DirectObj export { node:root_node }

// He was 32 years older than her.
//        ^^^^^^^^^^^^^^^^^^^^^^^
pattern YearsOldAdj
{
 cnt=NumberGroup
 n=eng_noun:year{}
 a=eng_adjective:old{ adj_form:comparative } : export { node:root_node }
 conj=eng_conj:than{}
 obj=DirectObj
}
: links { a.{ <ATTRIBUTE>n.<ATTRIBUTE>cnt <NEXT_COLLOCATION_ITEM>conj.<OBJECT>obj } }
: ngrams { 2 }


// This tree is hundreds of years old.
//              ^^^^^^^^^^^^^^^^^^^^^
pattern YearsOldAdj
{
 cnt=eng_noun:*{}
 prep=eng_prep:of{}
 n=eng_noun:year{ NUMBER:PLURAL }
 a=eng_adjective:old{} : export { node:root_node }
}
: links { a.<ATTRIBUTE>cnt.<PREPOS_ADJUNCT>prep.<OBJECT>n }
: ngrams { 2 }
