
patterns NumberCore export { node:root_node }
patterns NumberGroup export { node:root_node }

// Edward Wakefield was now 78 years old;
//                          ^^
// Adams was 45 years old.
//           ^^
// There are 5 main stars.
//           ^
pattern NumberCore
{
 num_word:*{} : export { node:root_node }
}

// I was 19-20 years old.
//       ^^^^^
pattern NumberCore
{
 n1=num_word:*{} : export { node:root_node }
 t='-'
 n2=num_word:*{}
} : links { n1.<NEXT_COLLOCATION_ITEM>t.<NEXT_COLLOCATION_ITEM>n2 }


// This changes to 24/7 during exam season.
//                 ^^^^
// Amir Kabir returned to Tabriz in 1263/1847.
//                                  ^^^^^^^^^
pattern NumberCore
{
 n1=num_word:*{} : export { node:root_node }
 t='/'
 n2=num_word:*{}
} : links { n1.<NEXT_COLLOCATION_ITEM>t.<NEXT_COLLOCATION_ITEM>n2 }



// It was recaptured in 1428 or 1429.
//                      ^^^^^^^^^^^^
pattern NumberCore
{
 n1=num_word:*{} : export { node:root_node }
 c=eng_conj:*{}
 n2=num_word:*{}
} : links { n1.<NEXT_COLLOCATION_ITEM>c.<NEXT_COLLOCATION_ITEM>n2 }



// He had one brother six years older.
//                    ^^^
pattern NumberCore
{
 n1=eng_numeral:*{ numeral_form:cardinal } : export { node:root_node }
}

// That ship has a crew of a hundred men
//                         ^^^^^^^^^
// About a hundred borate minerals are known.
//       ^^^^^^^^^
pattern NumberCore
{
 det=eng_article:a{}
 n=eng_numeral:*{ numeral_form:cardinal } : export { node:root_node }
} : links { n.<ATTRIBUTE>det }



// She was fifty-one years old.
//         ^^^^^^^^^
pattern NumberCore
{
 n1=eng_numeral:*{ numeral_form:cardinal } : export { node:root_node }
 t='-'
 n2=eng_numeral:*{ numeral_form:cardinal }
} : links { n1.<NEXT_COLLOCATION_ITEM>t.<NEXT_COLLOCATION_ITEM>n2 }



pattern NumberGroup
{
 NumberCore : export { node:root_node }
}


// --------------------------------------------------------------------------

// The temple is approximately 300 years old.
//               ^^^^^^^^^^^^^^^^^
// Candidates must be at least forty years old.
//                    ^^^^^^^^^^^^^^
pattern NumberGroup
{
 mod=AdvNumberModifier
 n1=NumberGroup : export { node:root_node }
}
: links { n1.<ATTRIBUTE>mod }
: ngrams { 2 }

// --------------------------------------------------------------------------

wordentry_set NumberModifierPrep=
{
 eng_prep:over{},
 eng_prep:about{},
 eng_prep:around{}
}

// Some specimens are over 100 years old.
//                    ^^^^^^^^
// This school is over 125 years old.
//                ^^^^^^^^
// It is near about 800 years old.
//            ^^^^^^^^^
pattern NumberGroup
{
 p=NumberModifierPrep : export { node:root_node }
 n1=NumberGroup
}
: links { p.<OBJECT>n1 }
: ngrams { 1 }

// Another checklist reports only about 5000 species.
//                           ^^^^^^^^^^^^^^^
pattern NumberGroup
{
 mod=eng_adverb:only{}
 p=NumberModifierPrep : export { node:root_node }
 n1=NumberGroup
}
: links { p.{ <ATTRIBUTE>mod <OBJECT>n1 } }
: ngrams { 1 }



// He was less than three years old.
//        ^^^^^^^^^^^^^^^
pattern NumberGroup
{
 adv=eng_adverb:little{ ADJ_FORM:COMPARATIVE } : export { node:root_node }
 c=eng_conj:than{}
 n1=NumberGroup
} : links { adv.<NEXT_COLLOCATION_ITEM>c.<OBJECT>n1 }

// More than 830,000 people died.
// ^^^^^^^^^^^^^^^^^
pattern NumberGroup
{
 adv=eng_adverb:more{} : export { node:root_node }
 c=eng_conj:than{}
 n1=NumberGroup
} : links { adv.<NEXT_COLLOCATION_ITEM>c.<OBJECT>n1 }

// 16 out of 50 financial institutions faced bankruptcy.
// ^^^^^^^^^^^^
pattern NumberGroup
{
 n1=NumberCore : export { node:root_node }
 p=eng_prep:out of{}
 n2=NumberCore
} : links { n1.<PREPOS_ADJUNCT>p.<OBJECT>n2 }

// Two other surfers saved four more fishermen.
//                         ^^^^^^^^^
pattern NumberGroup
{
 n=NumberCore : export { node:root_node }
 adv=eng_adverb:more{}
} : links { n.<ATTRIBUTE>adv }

